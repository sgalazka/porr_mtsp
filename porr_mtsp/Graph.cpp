#define _CRT_SECURE_NO_DEPRECATE
#include "graph.h"
#include <iostream>
#include <assert.h>


Graph::Graph(int noOfVertices, igraph_vector_t* edges1) {
	this->g = new igraph_t;
	//igraph_create(this->g, edges1, 8, 0);

	/*igraph_barabasi_game((this->g),
		11,
		1, //power
		2,
		0,
		0,
		1, //A
		0,
		IGRAPH_BARABASI_BAG,
		0//start_from
		);
	igraph_write_graph_gml(this->g, stdout, NULL, 0);*/


	FILE *file;
	file = fopen("graph.gml", "r");
	assert(file != 0);
	igraph_read_graph_gml(this->g, file);
	this->edges = edges1;
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