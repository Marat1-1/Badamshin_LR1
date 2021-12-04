#include "CompressorStationCollection.h"
#include "PipeCollection.h"
#include <set>



#ifndef GASTRANSMISSIONNETWORK_H
#define GASTRANSMISSIONNETWORK_H

class GasTransmissionNetwork
{
private:
	PipeCollection newPipeCollection;
	CompressorStationCollection newCSCollection;
	std::set<size_t> freePipes;
	std::set<size_t> freeCS;
	void printMenu();
	void printFreePipes();
	void printFreeCS();
	void printTableConnections();
	bool checkFreePipes();
	bool checkFreeCS();
	bool checkingConnections();
public:
	// Методы управления сетью
	void manageNetwork();
	// Методы для управления коллекциями
	void AddPipe();
	void AddCS();
	void ChangePipe();
	void ChangeCS();
	void PrintTablePipes();
	void PrintTableCS();
	void SaveToFilePipeCollection(std::ofstream&);
	void SaveToFileCSCollection(std::ofstream&);
	void DownloadFromFilePipeCollection(std::ifstream&);
	void DownloadFromFileCSCollection(std::ifstream&);
	void DeletePipe();
	void DeleteCS();
	void BatchChangePipeCollection();
	void BatchChangeCSCollection();
};

#endif // !GASTRANSMISSIONNETWORK_H