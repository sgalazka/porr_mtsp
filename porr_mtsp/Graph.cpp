#define _CRT_SECURE_NO_DEPRECATE
#include "graph.h"
#include <iostream>
#include <assert.h>


Graph::Graph(char* filename) {
	this->g = new igraph_t;
	FILE *file;
	file = fopen(filename, "r");
	assert(file != 0);
	igraph_read_graph_gml(this->g, file);
	
}

Graph::Graph() {

}

std::vector<int> Graph::getPath(int startIndex, int endIndex) {
	//std::cout << "getPath from" << startIndex << " to " << endIndex << std::endl;
	igraph_vector_t vertices;
	igraph_vector_t edges;
	igraph_vector_init(&vertices, 0);
	igraph_vector_init(&edges, 0);
	std::vector<int> pathIndices;
	igraph_get_shortest_path(this->g, &vertices, &edges, startIndex, endIndex, IGRAPH_ALL);
	for (int i = 0; i < igraph_vector_size(&vertices); i++) {
		pathIndices.push_back(VECTOR(vertices)[i]);
	}
	return pathIndices;
}

Graph::~Graph() {

}