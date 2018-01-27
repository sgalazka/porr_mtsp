#pragma once

class CityGene {
private:
	int genes;

public:
	int getGenes() const;
	CityGene(int genes);
	bool operator==(const CityGene &c);
};
