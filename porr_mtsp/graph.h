#pragma once
#include <igraph.h>

class Graph {
private:
	igraph_t* g;
	igraph_vector_t* edges;


public:
	Graph(int noOfVertices, igraph_vector_t* edges);
	Graph();
	~Graph();
	int getPathLength(int startIndex, int endIndex);
};
