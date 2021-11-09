#include <unordered_map>
#include <vector>
#include <fstream>
#include "ClassElements.h"
#include "Console.h"

#ifndef COMPRESSORSTATIONCOLLECTION_H
#define COMPRESSORSTATIONCOLLECTION_H

class CompressorStationCollection
{
private:
	std::unordered_map<size_t, CompressorStation> csCollection;
	std::vector<size_t> vectorIdForFilter;
	void PrintFilterTableCS();
	void FilterCS();
public:
	void AddCS();
	void ChangeCS();
	void PrintTableCS();
	void SaveToFile(std::ofstream&);
	void DownloadFromFile(std::ifstream&);
	void DeleteCS();
	void BatchChangeCS();
};

#endif // !COMPRESSORSTATIONCOLLECTION_H
