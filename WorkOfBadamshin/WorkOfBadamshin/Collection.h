#include <fstream>

#ifndef COLLECTION_H
#define COLLECTION_H

class Collection
{
public:
	virtual void Add() = 0;
	virtual void Change() = 0;
	virtual void Filter() = 0;
	virtual void PrintTable() = 0;
	virtual void PrintFilterTable(std::vector<size_t>&) = 0;
	virtual void SaveToFile(std::ofstream&) = 0;
	virtual void DownloadFromFile(std::ifstream&) = 0;
	virtual void Delete() = 0;
	virtual void BatchChange() = 0;
};
#endif // !COLLECTION_H