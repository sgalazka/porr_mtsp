#include "Algorithm.h"

using namespace std;

bool vectorContains(vector<CityGene> vec, CityGene value);
void printGenes(vector<CityGene> genes, int citiesPerSalesman);

Algorithm::Algorithm(int salesmen, int cities, int citiesPerSalesman, int populationSize, Graph* graph) {
	assert(salesmen * citiesPerSalesman == cities);
	this->salesmen = salesmen;
	this->cities = cities;
	this->citiesPerSalesman = citiesPerSalesman;
	this->populationSize = populationSize;
	this->graph = graph;
	initializePopulation();
}

void Algorithm::initializePopulation() {
	srand((int)time(NULL));
	for (size_t i = 0; i < populationSize; i++) {
		Genotype genotype = getRandomGenotype();
		genotype.printGenotype();
		population.push_back(genotype);
	}
}

Genotype Algorithm::getRandomGenotype() {
	vector<CityGene> genes;
	int* citiesIndices = new int[cities];
	for (int i = 0; i < cities; i++) {
		citiesIndices[i] = i;
	}
	random_shuffle(&citiesIndices[0], &citiesIndices[0] + cities);

	for (int i = 0; i < cities; i++) {
		genes.push_back(CityGene(citiesIndices[i]));
	}

	return Genotype(genes, this->citiesPerSalesman);
}


void Algorithm::executeAlgorithm() {
	initializePopulation();
	int condition = 0;
	while (condition < 1) {
		for (size_t i = 0; i < populationSize; i++) {
			Genotype genotype1 = population[i];
			Genotype genotype2 = population[(i + 1) % populationSize];

			vector<CityGene> parent1 = genotype1.getAllGenes();
			vector<CityGene> parent2 = genotype2.getAllGenes();
			vector<CityGene> child1;
			vector<CityGene> child2;
			orderCrossover(&parent1, &parent2, &child1, &child2);
		}
		condition++;
	}

}

void Algorithm::orderCrossover(vector<CityGene>* parent1, vector<CityGene>* parent2,
	vector<CityGene>* child1, vector<CityGene>* child2) {
	int end = (rand() % (cities - 2)) + 1;
	int start = rand() % end;
	end++;
	start++;
	cout << "start: " << start << ", end: " << end << endl;
	for (size_t i = start; i < end; i++) {
		child1->push_back((*parent1)[i]);
		child2->push_back((*parent2)[i]);
	}
	int index = 0;
	CityGene val1 = CityGene(0);
	CityGene val2 = CityGene(0);
	for (size_t i = 0; i < cities; i++) {
		index = (end + i) % cities;
		val1 = (*parent1)[index];
		val2 = (*parent2)[index];
		if (!vectorContains((*child1), val2)) {
			child1->push_back(val2);
		}
		if (!vectorContains((*child2), val1)) {
			child2->push_back(val1);
		}
	}
	rotate(child1->rbegin(), child1->rbegin() + start, child1->rend());
	rotate(child2->rbegin(), child2->rbegin() + start, child2->rend());
}


void printGenes(vector<CityGene> genes, int citiesPerSalesman) {
	cout << "Print genes:" << endl;
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

bool vectorContains(vector<CityGene> vec, CityGene value) {
	for (size_t i = 0; i < vec.size(); i++) {
		if (vec[i].getGenes() == value.getGenes()) {
			return true;
		}
	}
	return false;
}
