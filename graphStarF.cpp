#include "graphStarF.h"
graphStarF ::graphStarF(string filename){
	ifstream input;
	input.open(filename.c_str());
	if(input.is_open){
		int start,end,weight;
		while(input.good()){
			input>>start>>end>>weight;
			arcs.push_back(new arc(start,end,weight));
			

		}
	}
	else{
		cout<<"Error in open file"<<endl;
		input.close();
	}

}
