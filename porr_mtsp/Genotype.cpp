#include "Genotype.h"
#include <iostream>

Genotype::Genotype(std::vector<SalesmanGene> g) {
	genes = g;
}

std::vector<SalesmanGene> Genotype::getGenes() {
	return genes;
}

void Genotype::printGenotype() {
	std::cout << "Print genotype:" << std::endl;
	for (int i = 0; i < genes.size(); i++) {
		std::cout << "gene: " << i; 
		genes[i].printGene();
	}

}