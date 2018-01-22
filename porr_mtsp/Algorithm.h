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
	int populationSize;
	Graph* graph;
	std::vector<Genotype> population;
public:
	Algorithm(int salesmen, int cities, int citiesPerSalesman, int populationSize, Graph* graph);
	void initializePopulation();
	void executeAlgorithm();
	Genotype getRandomGenotype();
	void orderCrossover(std::vector<CityGene>* parent1, std::vector<CityGene>* parent2,
		std::vector<CityGene>* child1, std::vector<CityGene>* child2);
	float rateGenotype(Genotype Genotype);
	std::vector<Genotype> getNewPopulation(std::vector<Genotype> temporaryPopulation);
	int getRoadLengthForSalesman(std::vector<CityGene> salesman);
	std::vector<std::pair<int, int>> getParentPairs();
};

