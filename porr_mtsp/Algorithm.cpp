#include "Algorithm.h"
using namespace std;

Algorithm::Algorithm(int salesmen, int cities, int citiesPerSalesman) {
	this->salesmen = salesmen;
	this->cities = cities;
	this->citiesPerSalesman = citiesPerSalesman;
	initializePopulation();
}

void Algorithm::initializePopulation() {

}

void Algorithm::executeAlgorithm() {
	cout << "executeMtspGeneticAlgorithm" << endl;
}