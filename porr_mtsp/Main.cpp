#include <iostream>
#include "Algorithm.h"
#include <mpi.h>
#include <fstream>

#define _CRT_SECURE_NO_WARNINGS

using namespace std;

vector<Result> executeSimple_Sequence(int populationSize, double mutationRatio);
vector<Result> executeHard_Sequence(int populationSize, double mutationRatio);

vector<Result> executeSimple_Parallel(int populationSize, double mutationRatio);
vector<Result> executeHard_Parallel(int populationSize, double mutationRatio);

vector<Result> meanVectorResult(vector<Result> results1, vector<Result> results2);
void writeResultsToFile(vector<Result> results, char* filename);

int main() {
	/*int rc = MPI_Init(NULL, NULL);
	if (rc != MPI_SUCCESS)
	{
		printf("Error");
		MPI_Abort(MPI_COMM_WORLD, rc);
	}*/
	
	int count = 0;
	int pop_size = 2;
		double mutation = 0.5;
		for (int j = 0; j < 3; j++) {
			if (j == 0)
				pop_size = 2;
			else if (j == 1)
				pop_size = 6;
			else if (j == 2)
				pop_size = 12;
			
			vector<Result> averageResults;
			for (int i = 0; i < 2; i++) {
				vector<Result> currentResults = executeSimple_Sequence(pop_size, mutation);
				if (averageResults.size() == 0 && currentResults.size()>0) {
					averageResults = currentResults;
					count++;
				}
				else if (currentResults.size() > 0) {
					averageResults = meanVectorResult(averageResults, currentResults);
					count++;
				}
			}
			if (averageResults.size()>0) {
				const char* name = "mutation";
				char buf[15] = { 0 };
				sprintf_s(buf, 15, "%s%d.txt", name, j);
				writeResultsToFile(averageResults, buf);
			}
		}
	
	/*cout << "########### count: " << count << endl;
	for (int i = 0; i < averageResults.size(); i++) {
		cout << "\t" << i << "\t" << averageResults[i].bestGenotypeRate << "\t" << averageResults[i].milis << endl;
	}*/
	/*MPI_Finalize();*/
	return 0;
}

vector<Result> executeHard_Sequence(int populationSize, double mutationRatio) {
	Graph* graph = new Graph("101graph.gml");
	int salesmen = 10;
	int cities = 100;
	int citiesPerSalesman = 10;
	Algorithm algorithm = Algorithm(salesmen, cities, citiesPerSalesman, populationSize, graph, mutationRatio);
	return algorithm.executeSequence();
}

vector<Result> executeSimple_Sequence(int populationSize, double mutationRatio) {
	Graph* graph = new Graph("25graph.gml");
	int salesmen = 4;
	int cities = 24;
	int citiesPerSalesman = 6;
	Algorithm algorithm = Algorithm(salesmen, cities, citiesPerSalesman, populationSize, graph, mutationRatio);
	return algorithm.executeSequence();
}

vector<Result> executeSimple_Parallel(int populationSize, double mutationRatio) {
	Graph* graph = new Graph("25graph.gml");
	int salesmen = 4;
	int cities = 24;
	int citiesPerSalesman = 6;
	Algorithm algorithm = Algorithm(salesmen, cities, citiesPerSalesman, populationSize, graph, 0.05);
	return algorithm.executeParallel();
}

vector<Result> executeHard_Parallel(int populationSize, double mutationRatio) {
	Graph* graph = new Graph("101graph.gml");
	int salesmen = 10;
	int cities = 100;
	int citiesPerSalesman = 10;
	Algorithm algorithm = Algorithm(salesmen, cities, citiesPerSalesman, populationSize, graph, mutationRatio);
	return algorithm.executeParallel();
}

vector<Result> meanVectorResult(vector<Result> results1, vector<Result> results2) {
	for (int i = 0; i < results1.size(); i++) {
		Result result1 = results1[i];
		Result result2 = results2[i];
		result1.bestGenotypeRate = (result1.bestGenotypeRate + result2.bestGenotypeRate) / 2;
		result1.milis = (result1.milis + result2.milis) / 2;
		results1[i] = result1;
	}
	return results1;
}

void writeResultsToFile(vector<Result> results, char* filename) {
	ofstream file;
	file.open(filename, ios::app);
	if (file.is_open()) {
		for (int i = 0; i < results.size(); i++) {
			file << "\t" << i << "\t" << results[i].bestGenotypeRate << "\t" << results[i].milis << endl;
		}
		file.close();
	}
}
