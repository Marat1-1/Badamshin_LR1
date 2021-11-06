#include <vector>
#include <fstream>
#include "ClassElements.h"
#include "Console.h"

#ifndef COMPRESSORSTATIONCOLLECTION_H
#define COMPRESSORSTATIONCOLLECTION_H

class CompressorStationCollection
{
private:
	std::vector<CompressorStation> vectorCS;
public:
	void AddCS(Console&);
	void ChangeCS(Console&);
	void PrintTableCS(Console&);
	void SaveToFile(std::ofstream&, Console&);
	void DownloadFromFile(std::ifstream&, Console&);
	void DeleteCS(Console&);
};

#endif // !COMPRESSORSTATIONCOLLECTION_H
