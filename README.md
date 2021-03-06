Author: Jun Jiang
Email: jovechiang@gmail.com

##Description:
This is a library for large graph algorithm.


##Development Plan
###1st Step (core part) : the-state-of-art graph algorithms. 
         There are 4 main subgroups:  Paths, Optimization, Traveling and Ordering
		 Paths
			|-------Eulerian Path
			|-------Hamiltonian Cycle
		 Optimization
			|-------Minimum Spanning Tree (Basic Algorithms)
			|			|-------Prim
			|			|-------Kruskal
			|			|-------Sollin(Boruvka)
			|
			|-------Minimum Spanning Tree (Advanced Algorithms)
			|			|-------Minimum Degree-Bounded Spanning Trees
			|			|-------K Minimum Spanning Trees
			|
			|-------Shortest Paths
			|			|-------Single-Source Shortest Paths
			|			|			|------Dijkastra
			|			|			|------Bellman-Ford
			|			|			|------Shortest Path Faster Algorithm			  
			|			|						 
			|			|-------Applications
			|			|			|------System of Difference Constraints
			|			|			|------Shotest paths in DAG
			|			|
			|			|-------All-pairs shortest paths
			|			            |------Floyd-Warshall
			|						|------Johnson
			|			
			|-------Flow Network			
			|			|-------Maximum Flow
			|			|			|------Ford-Fulkerson
			|			|			|		  |------Edmonds-Karp
			|			|			|				   
			|			|			|------Preflow Push method 
			|			|			|------Dinic Method	  
			|			|
			|			|-------Minimum Cost Flow
			|						|------Finding Minimum Cost Path
			|						|------Finding negative circle
			|						|------Network Simplex Algorithm
            |
			|-------Matching
			|			|-------Bipartite Graph
			|						|-----iHopcroft and Karp algorithm (Unweighted)
			|			|			|------Kuhn-Munkres(KM) algorithm (Weighted)
			|			|
			|			|-------General Graph
			|			            |------Blossom (Unweighted)
			|
		 Traveling
			|-------Depth First Search
			|-------Bredth First Search
		 Ordering
			|-------Topological Sort

###2nd Step (scalable ) : turn this version into a distributed version. Need NoSQL database support

###3rd Step (application): Develop a web graph crawler based on this lib

