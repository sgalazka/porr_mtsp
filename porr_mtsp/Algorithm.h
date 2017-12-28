#pragma once
#include <iostream>
#include <vector>
#include "genotype.h"

class Algorithm {
private:
	int salesmen;
	int cities;
	int citiesPerSalesman;
	std::vector<Genotype> population;
public:
	Algorithm(int salesmen, int cities, int citiesPerSalesman);
	void initializePopulation();
	void executeAlgorithm();

};

