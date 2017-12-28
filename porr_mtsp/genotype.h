#pragma once
#include "salesman_gene.h"
#include <vector>

class Genotype {
private:
	std::vector<SalesmanGene> genes;
public:
	Genotype(std::vector<SalesmanGene> genes);
	std::vector<SalesmanGene> getGenes();
};
