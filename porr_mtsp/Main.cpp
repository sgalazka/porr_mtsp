#include <iostream>
#include "Algorithm.h"

using namespace std;

Graph* getSimpleGraph(Graph* graph, igraph_vector_t* edges);

int main() {
	igraph_vector_t edges;
	Graph graph, *graph1;
	graph1 = getSimpleGraph(&graph, &edges);
	int salesmen=2; 
	int cities=10; 
	int citiesPerSalesman=5;
	int populationSize = 7;
	Algorithm algorithm = Algorithm(salesmen, cities, citiesPerSalesman, populationSize, graph1);
	algorithm.executeAlgorithm();

	return 0;
}

Graph* getSimpleGraph(Graph* graph, igraph_vector_t* edges) {
	const int NO_OF_VERTICES = 8;
	igraph_vector_init(edges, 14);
	VECTOR(*edges)[0] = 0; VECTOR(*edges)[1] = 1;
	VECTOR(*edges)[2] = 1; VECTOR(*edges)[3] = 2;
	VECTOR(*edges)[4] = 2; VECTOR(*edges)[5] = 3;
	VECTOR(*edges)[6] = 4; VECTOR(*edges)[7] = 3;
	VECTOR(*edges)[8] = 3; VECTOR(*edges)[9] = 5;
	VECTOR(*edges)[10] = 5; VECTOR(*edges)[11] = 6;
	VECTOR(*edges)[12] = 6; VECTOR(*edges)[13] = 7;
	graph = new Graph(NO_OF_VERTICES, edges);
	return graph;
}