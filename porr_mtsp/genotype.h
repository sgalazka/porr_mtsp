#pragma once
#include "salesman_gene.h"
#include <vector>

class Genotype {
private:
	std::vector<CityGene> genes;
	int citiesPerSalesman;
public:
	Genotype(std::vector<CityGene> g, int citiesPerSalesman);
	std::vector<CityGene> getAllGenes();
	void printGenotype();
	std::vector<CityGene> getGenesForSalesman(int id);
};
