#pragma once
#include "salesman_gene.h"
#include <vector>

class Genotype {
private:
	float rate;
public:
	int citiesPerSalesman;
	std::vector<CityGene> genes;

	Genotype();
	Genotype(std::vector<CityGene> g, int citiesPerSalesman);
	std::vector<CityGene> getAllGenes() const;
	void printGenotype();
	std::vector<CityGene> getGenesForSalesman(int id);
	void setRate(float rate);
	float getRate();
	bool operator < (const Genotype& str) const;
	bool operator==(const Genotype &g) const;

	friend std::ostream& operator<<(std::ostream &strm, const Genotype &a);
};
