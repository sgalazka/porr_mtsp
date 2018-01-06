#include "graph.h"
#include <iostream>
Graph::Graph(int noOfVertices, igraph_vector_t* edges1) {
	this->g = new igraph_t;
	igraph_create(this->g, edges1, 8, 0);
	this->edges = edges1;
}

Graph::Graph() {

}

int Graph::getPathLength(int startIndex, int endIndex) {
	igraph_matrix_t res;
	igraph_vs_t from, to;
	igraph_vs_vector_small(&from, 1, -1);
	igraph_vs_vector_small(&to, 5, -1);
	igraph_matrix_init(&res, 0, 0);
	igraph_shortest_paths(this->g, &res, from, to, IGRAPH_ALL);
	int length = MATRIX(res, 0, 0);
	igraph_vs_destroy(&from);
	igraph_vs_destroy(&to);
	igraph_matrix_destroy(&res);
	return length;
}

Graph::~Graph() {

}