#include <unordered_map>
#include <vector>
#include "ClassCS.h"
#include "Collection.h"

#ifndef COMPRESSORSTATIONCOLLECTION_H
#define COMPRESSORSTATIONCOLLECTION_H

class CompressorStationCollection : public Collection
{
protected:
	std::unordered_map<size_t, CompressorStation> csCollection;
	std::vector<size_t> vectorIdForFilter;
public:
	void Add();
	void Change();
	void Filter();
	void PrintTable();
	void PrintFilterTable(std::vector<size_t>&);
	void SaveToFile(std::ofstream&);
	void DownloadFromFile(std::ifstream&);
	void Delete();
	void BatchChange();
	friend class GasTransmissionNetwork;
};

#endif // !COMPRESSORSTATIONCOLLECTION_H