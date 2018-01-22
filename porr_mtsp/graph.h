#pragma once
#include <igraph.h>
#include <vector>

class Graph {
private:
	igraph_t* g;
	igraph_vector_t* edges;


public:
	Graph(int noOfVertices, igraph_vector_t* edges);
	Graph();
	~Graph();
	std::vector<int> getPath(int startIndex, int endIndex);
};
