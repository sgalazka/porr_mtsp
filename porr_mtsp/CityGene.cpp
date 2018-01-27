#include "city_gene.h"

CityGene::CityGene(int g) {
	genes = g;
}

int CityGene::getGenes() const {
	return genes;
}

bool CityGene::operator==(const CityGene &c) {
	return (getGenes() == c.getGenes());	
}