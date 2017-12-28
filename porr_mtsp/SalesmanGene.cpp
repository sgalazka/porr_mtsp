#include "salesman_gene.h"

SalesmanGene::SalesmanGene(std::vector<CityGene> g) {
	genes = g;
}

std::vector<CityGene> SalesmanGene::getGenes() {
	return genes;
}