#include "Algorithm.h"
#include <mpi.h>
#define MAX_PROCESSES 20

using namespace std;

bool vectorContains(vector<CityGene> vec, CityGene value);
void printGenes(vector<CityGene> genes, int citiesPerSalesman);
void printGenes(Genotype genotype, int citiesPerSalesman, int rank, int iteration);
vector<int> getRandomInts(int endRange, int exception, int count);

Algorithm::Algorithm(int salesmen, int cities, int citiesPerSalesman, int populationSize, Graph* graph) {
	assert(salesmen * citiesPerSalesman == cities);
	this->salesmen = salesmen;
	this->cities = cities;
	this->citiesPerSalesman = citiesPerSalesman;
	this->populationSize = populationSize;
	this->graph = graph;
}

void Algorithm::initializePopulation() {

	for (size_t i = 0; i < populationSize; i++) {
		Genotype genotype = getRandomGenotype();
		//genotype.printGenotype();
		population.push_back(genotype);
	}
}

Genotype Algorithm::getRandomGenotype() {
	vector<CityGene> genes;
	int* citiesIndices = new int[cities];
	for (int i = 0; i < cities; i++) {
		citiesIndices[i] = i + 1;
	}
	random_shuffle(&citiesIndices[0], &citiesIndices[0] + cities);

	for (int i = 0; i < cities; i++) {
		genes.push_back(CityGene(citiesIndices[i]));
	}
	Genotype g = Genotype(genes, this->citiesPerSalesman);
	g.setRate(rateGenotype(g));
	return g;
}


void Algorithm::executeAlgorithm() {


	int numtask, rank;
	int participants;
	int dataLength = cities + 1;
	int table[MAX_PROCESSES][11];
	vector<int> bestGenotypesInIterations;

	int rc = MPI_Init(NULL, NULL);
	if (rc != MPI_SUCCESS)
	{
		printf("Error");
		MPI_Abort(MPI_COMM_WORLD, rc);
	}
	MPI_Comm_size(MPI_COMM_WORLD, &numtask);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	srand((int)time(NULL) + rank * 10000);
	initializePopulation();
	int iteration = 0;

	if (numtask >= MAX_PROCESSES) {
		fprintf(stderr, "Max number of threads is %d\n", MAX_PROCESSES); fflush(stderr);
		MPI_Abort(MPI_COMM_WORLD, 1);
	}



	int block_size = 1;
	int begin_row = rank;
	int end_row = rank + 1;
	int send_count = dataLength;
	int recv_count = dataLength;

	while (iteration < 8) {
		vector<pair<int, int>> indices = getParentPairs();
		for (size_t i = 0; i < indices.size(); i++) {
			Genotype genotype1 = population[indices[i].first];
			Genotype genotype2 = population[indices[i].second];
			makeCrossover(genotype1, genotype2);
		}
		vector<Genotype> newP = getNewPopulation(population);
		cout << "#" << rank << " iteration: " << iteration << endl;;
		for (size_t i = 0; i < newP.size(); i++)
		{
			printGenes(newP[i], citiesPerSalesman, rank, iteration);
		}
		cout << endl;
		population = newP;


		Genotype bestGenotype = newP[0];
		cout << "#" << rank << " iteration: " << iteration << "; begin_row: " << begin_row << ", end_row:" << end_row << ", blocksize" << block_size << ", sendcount: " << send_count << endl;
		for (int i = begin_row; i < end_row; i++) {
			for (int j = 0; j < dataLength-1; j++) {
				table[i][j] = bestGenotype.getAllGenes()[j].getGenes();
			}
			table[i][dataLength - 1] = bestGenotype.getRate();
		}

		MPI_Allgather(&table[begin_row][0], send_count, MPI_INT,
			&table[0][0], recv_count, MPI_INT, MPI_COMM_WORLD);

		
		MPI_Barrier(MPI_COMM_WORLD);

		if (iteration % 3 == 2) {
			int maxSelected = populationSize / 4;
			if (maxSelected == 0)
				maxSelected = 1;
			vector<int> selectedGenotypesIds = getRandomInts(numtask, rank, maxSelected);

			for (int i = 0; i < maxSelected; i++) {
				vector<CityGene> newGenes;
				for (int j = 0; j < cities; j++) {
					newGenes.push_back(CityGene(table[selectedGenotypesIds[i]][j]));
				}
				cout << "#" << rank << " iteration: " << iteration << ", selectedGenotypeId: " << selectedGenotypesIds[i] << endl;
				Genotype newGenotype = Genotype(newGenes, citiesPerSalesman);
				newGenotype.setRate(rateGenotype(newGenotype));
				population.push_back(newGenotype);
			}

			cout << "#" << rank << " iteration: " << iteration << "before cut" << endl;
			population = cutPopulation(population);
			cout << "#" << rank << " iteration: " << iteration << "after cut" << endl;
			for (size_t i = 0; i < population.size(); i++)
			{
				printGenes(population[i], citiesPerSalesman, rank, 100 + iteration);
			}
			cout << "#" << rank << " iteration: " << iteration << "after print genes" << endl;
		}
		if (rank == 0) {
			for (int i = 0; i < numtask; i++) {
				cout << "#" << rank << " iteration: " << iteration << " i=" << i << ": ";
				for (int j = 0; j < dataLength; j++) {
					cout << ", " << table[i][j];
				}
				cout << endl;
			}
		}
		if (rank == 0) {
			int bestGeneRate = 10000000;
			for (int i = 0; i < numtask; i++) {
				int geneRate = table[i][dataLength - 1];
				if (geneRate < bestGeneRate) {
					bestGeneRate = geneRate;
				}
			}
			bestGenotypesInIterations.push_back(bestGeneRate);
		}

		MPI_Barrier(MPI_COMM_WORLD);

		iteration++;
	}
	if (rank == 0) {
		cout << "max iteration: " << iteration << endl;
		for (int i = 0; i < iteration; i++) {
			cout << "Iteration: " << i << ", best gene rate: " << bestGenotypesInIterations[i] << endl;
		}
	}
	
	MPI_Finalize();
}

void Algorithm::makeCrossover(Genotype genotype1, Genotype genotype2) {
	vector<CityGene> parent1 = genotype1.getAllGenes();
	vector<CityGene> parent2 = genotype2.getAllGenes();
	vector<CityGene> child1;
	vector<CityGene> child2;
	orderCrossover(&parent1, &parent2, &child1, &child2);
	Genotype child1genotype = Genotype(child1, citiesPerSalesman);
	child1genotype.setRate(rateGenotype(child1genotype));
	Genotype child2genotype = Genotype(child2, citiesPerSalesman);
	child2genotype.setRate(rateGenotype(child2genotype));
	population.push_back(child1genotype);
	population.push_back(child2genotype);
}

vector<std::pair<int, int>> Algorithm::getParentPairs() {
	int* genotypesIndices;
	vector<pair<int, int>> indicesPairs;
	if (populationSize % 2 == 1) {
		genotypesIndices = new int[populationSize + 1];
		for (int i = 0; i < populationSize; i++) {
			genotypesIndices[i] = i;
		}
		genotypesIndices[populationSize] = rand() % populationSize;
		random_shuffle(&genotypesIndices[0], &genotypesIndices[0] + (populationSize + 1));
		for (size_t i = 0; i <= populationSize; i = i + 2) {
			//cout << "generated pair: [" << genotypesIndices[i] << ", " << genotypesIndices[i + 1] << "]" << endl;
			indicesPairs.push_back(pair<int, int>(genotypesIndices[i], genotypesIndices[i + 1]));
		}
	}
	else {
		genotypesIndices = new int[populationSize];
		for (int i = 0; i < populationSize; i++) {
			genotypesIndices[i] = i;
		}
		random_shuffle(&genotypesIndices[0], &genotypesIndices[0] + populationSize);
		for (size_t i = 0; i < populationSize; i = i + 2) {
			//cout << "generated pair: [" << genotypesIndices[i] << ", " << genotypesIndices[i + 1] << "]" << endl;
			indicesPairs.push_back(pair<int, int>(genotypesIndices[i], genotypesIndices[i + 1]));
		}
	}
	return indicesPairs;
}

void Algorithm::orderCrossover(vector<CityGene>* parent1, vector<CityGene>* parent2,
	vector<CityGene>* child1, vector<CityGene>* child2) {
	int end = (rand() % (cities - 2)) + 1;
	int start = rand() % end;
	end++;
	start++;
	//cout << "start: " << start << ", end: " << end << endl;
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

vector<Genotype> Algorithm::getNewPopulation(std::vector<Genotype> temporaryPopulation) {
	return cutPopulation(temporaryPopulation);
}

vector<Genotype> Algorithm::cutPopulation(std::vector<Genotype> temporaryPopulation) {
	vector<Genotype> tmp = temporaryPopulation;
	sort(tmp.begin(), tmp.end());
	tmp.resize(populationSize);
	return tmp;
}

float Algorithm::rateGenotype(Genotype genotype) {
	float rate = 0;
	for (size_t i = 0; i < salesmen; i++) {
		vector<CityGene> salesmanGenes = genotype.getGenesForSalesman(i);
		rate += getRoadLengthForSalesman(salesmanGenes);
	}
	return rate;
}

int Algorithm::getRoadLengthForSalesman(std::vector<CityGene> salesman) {
	assert(salesman.size() > 2);

	//	static const int arr[] = { 1, 5, 2, 4 };
		//vector<int> genesValues(arr, arr + sizeof(arr) / sizeof(arr[0]));

	vector<int> genesValues;
	genesValues.push_back(0);
	for (vector<CityGene>::iterator it = salesman.begin(); it != salesman.end(); ++it) {
		genesValues.push_back(it->getGenes());
	}

	int fullLength = 0;
	vector<int>::iterator it = genesValues.begin();
	while (it != genesValues.end()) {
		int from = *it;
		int to = *(it + 1);
		vector<int> path = graph->getPath(from, to);
		//cout << "Path: ";
		/*for (std::vector<int>::const_iterator i = path.begin(); i != path.end(); ++i)
			std::cout << *i << ' ';*/
			//cout << endl;
		int pathLength = path.size() - 1;
		fullLength += pathLength;
		//cout << "pathLength " << pathLength << endl;
		if (genesValues.size() <= 2) {
			break;
		}
		//cout << "oldGenesValues: ";
		/*for (std::vector<int>::const_iterator itt = genesValues.begin(); itt != genesValues.end(); ++itt)
			std::cout << *itt << ' ';
		cout << endl;*/
		vector<int> newGenesValues;
		for (vector<int>::iterator it1 = it; it1 != genesValues.end(); it1++) {
			bool found = false;
			for (size_t i = 0; i < path.size() - 1; i++) {
				//cout << "*it1 " << *it1 << ", path[" << i << "] " << path[i] << ", found " << (path[i] == *it1) << endl;
				if (path[i] == *it1) {
					found = true;
					break;
				}
			}
			if (!found) {
				newGenesValues.push_back(*it1);
			}
			//cout << "oldGenesValues: ";
			/*for (std::vector<int>::const_iterator itt = genesValues.begin(); itt != genesValues.end(); ++itt)
				std::cout << *itt << ' ';*/
				//cout << endl;
				//cout << "newGenesValues: ";
				/*for (std::vector<int>::const_iterator itt = newGenesValues.begin(); itt != newGenesValues.end(); ++itt)
					std::cout << *itt << ' ';*/
					//cout << endl;
		}
		genesValues = newGenesValues;
		it = genesValues.begin();
		if (genesValues.size() <= 1)
			break;
	}

	return fullLength;
}

void printGenes(vector<CityGene> genes, int citiesPerSalesman) {
	cout << "Print genes:" << endl;
	for (int i = 0; i < genes.size(); i++) {
		if (i % citiesPerSalesman == 0) {
			cout << " [";
		}
		cout << " " << genes[i].getGenes();
		if (i % citiesPerSalesman == citiesPerSalesman - 1) {
			cout << "] ";
		}
		else {
			cout << ",";
		}
	}

	cout << endl;
}

void printGenes(Genotype genotype, int citiesPerSalesman, int rank, int iteration) {
	vector<CityGene> genes = genotype.getAllGenes();
	cout << "#" << rank << " iteration: " << iteration << " Print genes: ";
	for (int i = 0; i < genes.size(); i++) {
		if (i % citiesPerSalesman == 0) {
			cout << " [";
		}
		cout << " " << genes[i].getGenes();
		if (i % citiesPerSalesman == citiesPerSalesman - 1) {
			cout << "] ";
		}
		else {
			cout << ",";
		}
	}

	cout << ", rate: " << genotype.getRate() << endl;
}

bool vectorContains(vector<CityGene> vec, CityGene value) {
	for (size_t i = 0; i < vec.size(); i++) {
		if (vec[i].getGenes() == value.getGenes()) {
			return true;
		}
	}
	return false;
}

vector<int> getRandomInts(int endRange, int exception, int count) {
	vector<int> ids;
	for (int i = 0; i < endRange; i++) {
		if (i != exception) {
			ids.push_back(i);
		}
	}
	random_shuffle(&ids[0], &ids[0] + endRange - 1);
	random_shuffle(&ids[0], &ids[0] + endRange - 1);
	ids.resize(count);
	return ids;
}
