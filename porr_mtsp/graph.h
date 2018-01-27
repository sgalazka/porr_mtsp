#pragma once
#include <igraph.h>
#include <vector>

class Graph {
private:
	igraph_t* g;
public:
	Graph(char* filename);
	Graph();
	~Graph();
	std::vector<int> getPath(int startIndex, int endIndex);
};
