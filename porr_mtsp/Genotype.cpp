#include "Genotype.h"

Genotype::Genotype(std::vector<SalesmanGene> g) {
	genes = g;
}

std::vector<SalesmanGene> Genotype::getGenes() {
	return genes;
}