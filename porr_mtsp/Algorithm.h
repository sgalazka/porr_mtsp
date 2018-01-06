#pragma once
#include <iostream>
#include <vector>
#include "genotype.h"
#include "graph.h"
#include <time.h>
#include <algorithm>
#include <assert.h>

class Algorithm {
private:
	int salesmen;
	int cities;
	int citiesPerSalesman;
	Graph* graph;
	std::vector<Genotype> population;
public:
	Algorithm(int salesmen, int cities, int citiesPerSalesman, Graph* graph);
	void initializePopulation();
	void executeAlgorithm();
	Genotype getRandomGenotype();
	std::string populationToString();
};

