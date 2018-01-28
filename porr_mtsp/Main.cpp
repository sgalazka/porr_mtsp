#include <iostream>
#include "Algorithm.h"

using namespace std;

void executeSimple_Sequence();
void executeMedium_Sequence();
void executeHard_Sequence();
void executeSimple_Parallel();
void executeMedium_Parallel();
void executeHard_Parallel();

int main() {
	executeSimple_Sequence();
	return 0;
}

void executeSimple_Sequence() {
	Graph* graph = new Graph("graph.gml");
	int salesmen = 2;
	int cities = 10;
	int citiesPerSalesman = 5;
	int populationSize = 3;
	Algorithm algorithm = Algorithm(salesmen, cities, citiesPerSalesman, populationSize, graph, 0.1);
	algorithm.executeSequence();
}

void executeMedium_Sequence() {
	Graph* graph = new Graph("25graph.gml");
	int salesmen = 4;
	int cities = 24;
	int citiesPerSalesman = 6;
	int populationSize = 10;
	Algorithm algorithm = Algorithm(salesmen, cities, citiesPerSalesman, populationSize, graph, 0.05);
	algorithm.executeSequence();
}

void executeHard_Sequence() {
	Graph* graph = new Graph("51graph.gml");
	int salesmen = 5;
	int cities = 50;
	int citiesPerSalesman = 10;
	int populationSize = 10;
	Algorithm algorithm = Algorithm(salesmen, cities, citiesPerSalesman, populationSize, graph, 0.9);
	algorithm.executeSequence();
}

void executeSimple_Parallel() {
	Graph* graph = new Graph("graph.gml");
	int salesmen = 2;
	int cities = 10;
	int citiesPerSalesman = 5;
	int populationSize = 3;
	Algorithm algorithm = Algorithm(salesmen, cities, citiesPerSalesman, populationSize, graph, 0.1);
	algorithm.executeParallel();
}

void executeMedium_Parallel() {
	Graph* graph = new Graph("25graph.gml");
	int salesmen = 4;
	int cities = 24;
	int citiesPerSalesman = 6;
	int populationSize = 10;
	Algorithm algorithm = Algorithm(salesmen, cities, citiesPerSalesman, populationSize, graph, 0.05);
	algorithm.executeParallel();
}

void executeHard_Parallel() {
	Graph* graph = new Graph("51graph.gml");
	int salesmen = 5;
	int cities = 50;
	int citiesPerSalesman = 10;
	int populationSize = 10;
	Algorithm algorithm = Algorithm(salesmen, cities, citiesPerSalesman, populationSize, graph, 0.9);
	algorithm.executeParallel();
}