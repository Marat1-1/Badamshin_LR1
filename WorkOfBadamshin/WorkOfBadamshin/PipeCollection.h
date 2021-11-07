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
public:
	void AddPipe(Console&);
	void ChangePipe(Console&);
	void PrintTablePipes(Console&);
	void PrintTablePipes(const std::vector<Pipe>&, Console&);
	void SaveToFile(std::ofstream&, Console&);
	void DownloadFromFile(std::ifstream&, Console&);
	void DeletePipe(Console&);
	void FilterPipe(Console&);
};

#endif // !PIPECOLLECTION_H