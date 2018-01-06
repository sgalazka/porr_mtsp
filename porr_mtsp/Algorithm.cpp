#include "Algorithm.h"

using namespace std;

Genotype getRandomGenotype();

Algorithm::Algorithm(int salesmen, int cities, int citiesPerSalesman, Graph* graph) {
	assert(salesmen * citiesPerSalesman == cities);
	this->salesmen = salesmen;
	this->cities = cities;
	this->citiesPerSalesman = citiesPerSalesman;
	this->graph = graph;
	initializePopulation();
}

void Algorithm::initializePopulation() {
	srand((int)time(NULL));
	for (size_t i = 0; i < 10; i++) {
		Genotype genotype = getRandomGenotype();
		genotype.printGenotype();
	}
}

Genotype Algorithm::getRandomGenotype() {
	vector<SalesmanGene> salesmanGenes;
	int* citiesIndices = new int[cities];
	for (int i = 0; i < cities; i++) {
		citiesIndices[i] = i;
	}
	random_shuffle(&citiesIndices[0], &citiesIndices[cities - 1]);
	for (size_t iS = 0; iS < salesmen; iS++) {
		vector<CityGene> cityGenes;
		for (size_t iC = 0; iC < citiesPerSalesman; iC++) {
			cityGenes.push_back(CityGene(citiesIndices[(citiesPerSalesman * iS + iC) % cities]));
		}
		salesmanGenes.push_back(SalesmanGene(cityGenes));
	}
	return Genotype(salesmanGenes);
}


void Algorithm::executeAlgorithm() {
	cout << "executeMtspGeneticAlgorithm" << endl;
	cout << "graph.getPathLength(1, 5)" << graph->getPathLength(1, 5) << endl;
}
