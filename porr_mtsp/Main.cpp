#include <iostream>
#include "Algorithm.h"

using namespace std;

Graph* getSimpleGraph(Graph* graph, igraph_vector_t* edges);

int main() {
	igraph_vector_t edges;
	Graph graph, *graph1;
	graph1 = getSimpleGraph(&graph, &edges);
	Algorithm algorithm = Algorithm(2, 8, 4, graph1);
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
	std::cout << "getSimpleGraph1" << std::endl;

	graph = new Graph(NO_OF_VERTICES, edges);

	std::cout << "getSimpleGraph2" << std::endl;
	return graph;
	/*igraph_t g;
	igraph_vit_t vit;
	igraph_vs_t vs;
	igraph_matrix_t res;
	igraph_vs_t from, to;
	igraph_create(&g, &edges, 8, 0);

	igraph_vs_all(&vs);
	igraph_vit_create(&g, vs, &vit);
	while (!IGRAPH_VIT_END(vit)) {
		printf(" %li", (long int)IGRAPH_VIT_GET(vit));
		IGRAPH_VIT_NEXT(vit);
	}
	igraph_vs_vector_small(&from, 1, -1);
	igraph_vs_vector_small(&to, 5, -1);
	igraph_matrix_init(&res, 0, 0);
	igraph_shortest_paths(&g, &res, from, to, IGRAPH_ALL);
	int length = MATRIX(res, 0, 0);

	cout << "Length: " << length << endl;
	igraph_vs_destroy(&from);
	igraph_vs_destroy(&to);
	igraph_matrix_destroy(&res);*/
}