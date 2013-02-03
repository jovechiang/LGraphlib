#ifndef GRAPH_ADJ_H
#define GRAPH_ADJ_H
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <fstream>

using namespace std;
struct edge{
	int toNodeId;
	int weight;
	edge* next;
	edge():toNodeId(-1),weight(-1),next(NULL){}
	edge(int to, int w):toNodeId(to),weight(w),next(NULL){}
};

class graph_adj{
	public:
		graph_adj(string filename);
		void printEdges();
		edge* getNext(edge* e){return e->next;}
		edge* getEdge(int ID){return adjList[ID];}
		vector<edge*> getAdj(){return adjList};
		
	private:
		//vetex number;
		int vNum;
		//adj list
		vector<edge*> adjList;
};

graph_adj::graph_adj(string filename){
	fstream f(filename.c_str(),ios_base::in);
	if(f.is_open()){
		f>>vNum;
		adjList=vector<edge*>(vNum);
		while(f.good()){
			//s: source node, e:end node, w:weight node;
			int s,e,w;
			f>>s>>e>>w;
			edge *nE=new edge(e,w);
			if(adjList[s]){
				edge* temp=adjList[s]->next;
				adjList[s]->next=nE;
				nE->next=temp;
			}
			else{
				adjList[s]=nE;
			}
		}
	}
}

void graph_adj::printEdges(){
	if(vNum<2){
		return;
	}
	for(int i=0;i<vNum;i++){
		if(!adjList[i])
			continue;
		edge* e=adjList[i];
		while(e){
			cout<<i<<" "<<e->toNodeId<<" "<<e->weight<<endl;

			e=e->next;
		}
	}
}
#endif
