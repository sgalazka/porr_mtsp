#include "salesman_gene.h"
#include <iostream>

SalesmanGene::SalesmanGene(std::vector<CityGene> g) {
	genes = g;
}

std::vector<CityGene> SalesmanGene::getGenes() {
	return genes;
}

void SalesmanGene::printGene() {
	std::cout << "SalesmanGene::toString" << std::endl << "[ ";
	for (std::vector<CityGene>::iterator it = genes.begin(); it != genes.end(); ++it) {
		std::cout << it->getGenes()<< ",\t";
	}
	std::cout << "]" << std::endl;
}