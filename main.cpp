#include "graph_adj.h"
#include "traversal.h"
int main(){
	graph_adj G("graph.txt");
	G.printEdges();

	traversal T(G);
	T.clearVisited();
	T.DFS(1);
	T.clearVisited();
	T.BFS(1);
	return 0;
	
}
