#pragma once
#include "salesman_gene.h"
#include <vector>

class Genotype {
private:
	std::vector<CityGene> genes;
	int citiesPerSalesman;
	float rate;
public:
	Genotype();
	Genotype(std::vector<CityGene> g, int citiesPerSalesman);
	std::vector<CityGene> getAllGenes();
	void printGenotype();
	std::vector<CityGene> getGenesForSalesman(int id);
	void setRate(float rate);
	float getRate();
	bool operator < (const Genotype& str) const;
};
