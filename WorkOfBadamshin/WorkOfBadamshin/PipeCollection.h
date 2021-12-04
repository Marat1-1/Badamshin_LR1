#include <unordered_map>
#include <vector>
#include "ClassPipe.h"
#include "Collection.h"

#ifndef PIPECOLLECTION_H
#define PIPECOLLECTION_H

class PipeCollection : public Collection
{
protected:
	std::unordered_map<size_t, Pipe> pipeCollection;
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

#endif // !PIPECOLLECTION_H