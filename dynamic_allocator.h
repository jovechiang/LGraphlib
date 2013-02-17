#ifndef DALLOC_H
#define DALLOC_H


/*
 *Currently, I'm trying to design the low-level memory mechanism
 *for in-memory graph structure.
 *
 *Since algorithm part are all classic algorithm.
 *Efficiency should be imporved by underlying storage
 *
 *still in the development
 */
static char* mem_start_brk;
static char* mem_brk;
static char* mem_max_brk;

#define WSIZE 4
#define DSIZE 8
#define CHUNKSIZE (1 << 12)
#define OVERHEAD 8

#define PACK(size, alloc)	((size) | (alloc))
#define GET(p)				(*(size_t *)(p))
#define PUT(p, val)			(*(size_t *)(p) = (val))
#define GET_SIZE(p)			(GET(p) & ~0x7)
#define GET_ALLOC(p)		(GET(p) & 0x1)

#define HDRP(bp)			((char*)(bp) - WSIZE)
#define FTRP(bp)			((char*)(bp) + GET_SIZE(HDRP(bp)) - DSIZE)
#define NEXT_BLKP(bp)		((char*)(bp) + GET_SIZE((char*)(bp) - WSIZE))
#define PREV_BLKP(bp)		((char*)(bp) - GET_SIZE((char*)(bp) - DSIZE))

void mem_init(int size)
{
	mem_start_brk = malloc(size);
	mem_brk = mem_start_brk;
	mem_max_brk = mem_start_brk + size;
}

void* mem_sbrk(int incr)
{
	if (incr < 0 || mem_brk + incr > mem_max_brk)
		return (void*)-1;

	char* pRet = mem_brk;
	mem_brk += incr;

	return pRet;
}

static void* find_fit(size_t asize)
{
	char* pIter = mem_start_brk + WSIZE;
	while (pIter < mem_brk)
	{
		if (GET_SIZE(HDRP(pIter-WSIZE)) >= asize)
			return pIter - WSIZE;

		pIter = NEXT_BLKP(pIter);
	}

	return NULL;
}

static void place(void* bp, size_t asize)
{
	size_t lftSize = GET_SIZE(bp) - asize;
	PUT(bp, PACK(asize, 1));
	PUT(bp + asize - WSIZE, PACK(asize, 1));

	if (lftSize == 0) return;

	char* pNew = bp + asize;
	PUT(pNew, PACK(lftSize, 0));
	PUT(bp + lftSize - WSIZE, PACK(lftSize, 0));
}

void* extend_heap(size_t words);
static void* coalesce(void* bp);

static void* extend_heap(size_t words)
{
	void* bp;
	size_t size;

	size = (words%2) ? (words + 1)*WSIZE : words * WSIZE;
	if ((int)(bp = mem_sbrk(size)) < 0)
		return NULL;

	PUT(HDRP(bp), PACK(size, 0));
	PUT(FTRP(bp), PACK(size, 0));
	PUT(HDRP(NEXT_BLKP(bp)), PACK(0, 1));

	return coalesce(bp);
}

static void* coalesce(void* bp)
{
	size_t prev_alloc = GET_ALLOC(FTRP(PREV_BLKP(bp)));
	size_t next_alloc = GET_ALLOC(HDRP(NEXT_BLKP(bp)));
	size_t size = GET_SIZE(HDRP(bp));

	if (prev_alloc && next_alloc)
		return bp;
	else if (prev_alloc && !next_alloc)
	{
		size += GET_SIZE(HDRP(NEXT_BLKP(bp)));
		PUT(HDRP(bp), PACK(size, 0));
		PUT(FTRP(bp), PACK(size, 0));
		return bp;
	}
	else if (!prev_alloc && next_alloc)
	{
		size += GET_SIZE(HDRP(PREV_BLKP(bp)));
		PUT(FTRP(bp), PACK(size, 0));
		PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));

		return HDRP(PREV_BLKP(bp));
	}
	else
	{
		size += GET_SIZE(HDRP(PREV_BLKP(bp))) + GET_SIZE(FTRP(NEXT_BLKP(bp)));
		PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
		PUT(FTRP(NEXT_BLKP(bp)), PACK(size, 0));

		return HDRP(PREV_BLKP(bp));
	}
}

/////////////////////////// service functions /////////////////////////////
int mm_init();
void mm_free(void* bp);
void* mm_malloc(size_t size);
///////////////////////////////////////////////////////////////////////////

int mm_init()
{
	void* heap_listp;
	if (NULL == (heap_listp = mem_sbrk(4*WSIZE)))
		return -1;

	PUT(heap_listp, 0);
	PUT(heap_listp+WSIZE, PACK(OVERHEAD, 1));
	PUT(heap_listp+DSIZE, PACK(OVERHEAD, 1));
	PUT(heap_listp+WSIZE+DSIZE, PACK(0, 1));
	heap_listp += DSIZE;

	if (extend_heap(CHUNKSIZE/WSIZE) == NULL)
		return -1;
	return 0;
}

void mm_free(void* bp)
{
	size_t size = GET_SIZE(HDRP(bp));

	PUT(HDRP(bp), PACK(size, 0));
	PUT(FTRP(bp), PACK(size, 0));
	coalesce(bp);
}

void* mm_malloc(size_t size)
{
	size_t asize;
	char* bp;

	if (size <= 0)
		return NULL;

	if (size <= DSIZE)
		asize = DSIZE + OVERHEAD;
	else 
		asize = DSIZE * ((size + OVERHEAD + DSIZE - 1)/DSIZE);

	if (NULL != (bp = find_fit(asize)))
	{
		place(bp, asize);
		return bp;
	}

	size_t extendsize = max(asize, CHUNKSIZE);
	if (NULL == (bp = extend_heap(extendsize)))
		return NULL;

	place(bp, asize);
	return bp;
}

#endif
