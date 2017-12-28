#pragma once
#include "city_gene.h"
#include <vector>

class SalesmanGene {
private:
	std::vector<CityGene> genes;

public:
	std::vector<CityGene> getGenes();
	SalesmanGene(std::vector<CityGene> genes);
};
