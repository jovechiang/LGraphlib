#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

/*
I use linked-forward-star representation to store graph information
This is efficient data structure in most case and a little bit different with forward star representation
*/
class graph{
	public:
		graph();
		graph(string filename);

	private:
		// number of edges
		long eNum;
		//number of nodes
		long nNum;
		//the first edge index of ith node,   nNum
		vector<long> head;
		//the next edge index of ith edge with same source node,  eNum
		vector<long> next;
		//the end edge index of ith edge with 
		vector<long> end;
}

graph::graph(){
	eNum=0;
	nNum=0;
}

graph::graph(string name){
	eNum=0;
	nNum=0;
	fstream f(name,ios::in);
	f.open(name);
	if(f.is_open()){
		int en,nn;
		//get number of edges and nodes;
		f>>nn>>en;
		eNum=en;
		nNum=nn;
		while(f.good())
		{
			//s: source node, e:end node, w:weight node
			int s,e,w;
			f>>s>>e>>w;

		}
	}
	else{
		cout<<"ERROR: can't open file";
	}
	f.close();
}
#endif
