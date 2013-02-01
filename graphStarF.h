#ifndef GRAPHSTARF_H
#define GRAPHSTARF_H
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

struct point{
	int id;
	// you can add other properties here for points
};

struct arc{
	int startpoint;
	int endpoint;
	int weight;
	arc(int s, int e, int w): startpoint(s) , endpoint(e) ,weight(w){}
};

class graphStarF{
	public:
		const vector<point> & getpts();
		const vector<arc> & getarcs();
		graphStarF(string filename);
		

	private:
		vector<point> pts;
		vector<arc> arcs;

};
#endif
