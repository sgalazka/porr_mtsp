#include "Genotype.h"
#include <iostream>
#include <assert.h>

using namespace std;

Genotype::Genotype() {

}

Genotype::Genotype(vector<CityGene> g, int citiesPerSalesman): genes(g), citiesPerSalesman(citiesPerSalesman) {
	
}

vector<CityGene> Genotype::getAllGenes() const {
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

std::ostream& operator<<(std::ostream &strm, const Genotype &a) {
	for (int i = 0; i < a.genes.size(); i++) {
		if (i % a.citiesPerSalesman == 0) {
			strm << " [";
		}
		strm << " " << a.genes[i].getGenes();
		if (i % a.citiesPerSalesman == a.citiesPerSalesman - 1) {
			strm << "]";
		}
		else {
			strm << ",";
		}
	}
	return strm;
}

bool Genotype::operator==(const Genotype &g) const {
	const vector<CityGene> genes = this->getAllGenes();
	for (int i = 0; i < genes.size(); i++) {
		if (genes[i].getGenes() != g.getAllGenes()[i].getGenes()) {
			return false;
		}
	}
	return true;
}