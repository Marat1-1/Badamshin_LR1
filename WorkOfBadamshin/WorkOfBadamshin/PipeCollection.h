#include <unordered_map>
#include <vector>
#include <fstream>
#include "ClassPipe.h"
#include "Console.h"

#ifndef PIPECOLLECTION_H
#define PIPECOLLECTION_H

class PipeCollection
{
private:
	std::unordered_map<size_t,Pipe> pipeCollection;
	std::vector<size_t> vectorIdForFilter;
	void PrintFilterTablePipes();
	void FilterPipe();
public:
	void AddPipe();
	void ChangePipe();
	void PrintTablePipes();
	void SaveToFile(std::ofstream&);
	void DownloadFromFile(std::ifstream&);
	void DeletePipe();
	void BatchChangePipe();
	void AttachPipe();
};

#endif // !PIPECOLLECTION_H