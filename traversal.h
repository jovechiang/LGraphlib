#ifndef TRAVERSAL_H
#define TRAVERSAL_H
#include "graph_adj.h"
#include <set>
#include <queue>


//Graph Traversal 
//DFS
//BFS

class traversal{
	public:
		traversal(graph_adj & g){G=&g;}
		void DFS(int start);
		void BFS(int start);
		void clearVisited(){visited.clear();}

	private:
		graph_adj* G;
		//Auxilary Datastructure
		//set can find elements with logN (red-black tree)
		set<int> visited;
		set<int> inQueue;
};

void traversal::DFS(int startId){
	//You can also put processor here
	//in next version there should be a functor
	cout<<"DFSvisiting "<<startId<<endl;
	visited.insert(startId);
	edge* e=G->getAdj().at(startId);
	while(e){
		if(visited.find(e->toNodeId)!=visited.end())
			return;
		DFS(e->toNodeId);
		e=e->next;
	}
}

void traversal::BFS(int startId){
	queue<int> Q;
	Q.push(startId);
	inQueue.insert(startId);
	while(!Q.empty()){
		int id=Q.front();
		Q.pop();
		inQueue.erase(id);
		cout<<"BFSvisiting "<<id<<endl;
		visited.insert(id);
		edge* e= G->getAdj().at(id);
		while(e){
			if(visited.find(e->toNodeId)==visited.end()&&inQueue.find(e->toNodeId)==inQueue.end()){
				Q.push(e->toNodeId);
				inQueue.insert(e->toNodeId);
			}
			e=e->next;
		}
	}

}



#endif
