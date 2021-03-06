#include "Genotype.h"
#include <iostream>
#include <assert.h>

using namespace std;

Genotype::Genotype() {

}

Genotype::Genotype(vector<CityGene> g, int citiesPerSalesman): genes(g), citiesPerSalesman(citiesPerSalesman) {
	
}

vector<CityGene> Genotype::getAllGenes() {
	return genes;
}

vector<CityGene> Genotype::getGenesForSalesman(int id) {
	//cout << "getGenesForSalesman" << endl;
	//cout << "id: " << id << ", genes.size: " << genes.size() << ", id*citiesPerSalesman: " << id*citiesPerSalesman << endl;
	assert(id * citiesPerSalesman <= genes.size());
	return vector<CityGene>(&genes[id*citiesPerSalesman], &genes[id*citiesPerSalesman] + citiesPerSalesman);
}

void Genotype::setRate(float rate) {
	this->rate = rate;
}

float Genotype::getRate() {
	return this->rate;
}

bool Genotype::operator < (const Genotype& str) const {
	return(this->rate < str.rate);
}

void Genotype::printGenotype() {
	cout << "Print genotype:" << endl;
	for (int i = 0; i < genes.size(); i++) {
		if (i % citiesPerSalesman == 0) {
			cout << "[";
		}
		cout << " " << genes[i].getGenes();
		if (i % citiesPerSalesman == citiesPerSalesman - 1) {
			cout << "]" << endl;
		}
		else {
			cout << ",";
		}
	}

	cout << endl;
}