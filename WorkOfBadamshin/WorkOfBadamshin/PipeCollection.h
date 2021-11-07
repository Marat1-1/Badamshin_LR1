#include <vector>
#include <fstream>
#include "ClassElements.h"
#include "Console.h"

#ifndef PIPECOLLECTION_H
#define PIPECOLLECTION_H

class PipeCollection
{
private:
	std::vector<Pipe> vectorPipes;
	std::vector<size_t> vectorIdForFilter;
	void PrintFilterTablePipes(Console&);
	void FilterPipe(Console&);
public:
	void AddPipe(Console&);
	void ChangePipe(Console&);
	void PrintTablePipes(Console&);
	void SaveToFile(std::ofstream&, Console&);
	void DownloadFromFile(std::ifstream&, Console&);
	void DeletePipe(Console&);
	void BatchChangePipe(Console&);
};

#endif // !PIPECOLLECTION_H