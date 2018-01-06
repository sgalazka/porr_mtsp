#include "graph.h"
#include <iostream>
Graph::Graph(int noOfVertices, igraph_vector_t* edges1) {
	
	this->g = new igraph_t;
	std::cout << "Graph1" << std::endl;
	igraph_create(this->g, edges1, 8, 0);
	//this->g = g1;
	std::cout << "Graph" << std::endl;
	this->edges = edges1;
	std::cout << "Graph" << std::endl;
}

Graph::Graph() {

}

int Graph::getPathLength(int startIndex, int endIndex) {
	std::cout << "getPathLength1" << std::endl;

	//igraph_vit_t vit;
	//igraph_vs_t vs;
	igraph_matrix_t res;
	igraph_vs_t from, to;
	std::cout << "getPathLength2" << std::endl;
	
	/*igraph_vs_all(&vs);
	igraph_vit_create(g, vs, &vit);
	while (!IGRAPH_VIT_END(vit)) {
		printf(" %li", (long int)IGRAPH_VIT_GET(vit));
		IGRAPH_VIT_NEXT(vit);
	}*/
	igraph_vs_vector_small(&from, 1, -1);
	igraph_vs_vector_small(&to, 5, -1);
	igraph_matrix_init(&res, 0, 0);
	std::cout << "getPathLength3" << std::endl;
	igraph_shortest_paths(this->g, &res, from, to, IGRAPH_ALL);
	std::cout << "getPathLength4" << std::endl;
	int length = MATRIX(res, 0, 0);
	igraph_vs_destroy(&from);
	igraph_vs_destroy(&to);
	igraph_matrix_destroy(&res);
	std::cout << "getPathLength5" << std::endl;
	return length;
}

Graph::~Graph() {
	//igraph_destroy(this->g);
	//igraph_vector_destroy(edges);
}