#include <iostream>
#include "Algorithm.h"

using namespace std;

Graph* getSimpleGraph(Graph* graph, igraph_vector_t* edges);
void executeSimple();
void executeMedium();
void executeHard();

int main() {
	executeSimple();
	//executeMedium();
	return 0;
}

void executeSimple() {
	Graph* graph = new Graph("graph.gml");
	int salesmen = 2;
	int cities = 10;
	int citiesPerSalesman = 5;
	int populationSize = 3;
	Algorithm algorithm = Algorithm(salesmen, cities, citiesPerSalesman, populationSize, graph, 0.1);
	algorithm.executeAlgorithm();
}

void executeMedium() {
	Graph* graph = new Graph("25graph.gml");
	int salesmen = 4;
	int cities = 24;
	int citiesPerSalesman = 6;
	int populationSize = 10;
	Algorithm algorithm = Algorithm(salesmen, cities, citiesPerSalesman, populationSize, graph, 0.05);
	algorithm.executeAlgorithm();
}

void executeHard() {

}