#include "CompressorStationCollection.h"
#include "PipeCollection.h"



#ifndef GASTRANSMISSIONNETWORK_H
#define GASTRANSMISSIONNETWORK_H

class GasTransmissionNetwork
{
private:
	PipeCollection newPipeCollection;
	CompressorStationCollection newCSCollection;
	std::vector<size_t> sortIdCS;
	std::unordered_map<size_t, CompressorStation> mapCSInUse;
	std::unordered_map<size_t, Pipe> mapPipeInUse;
	void printMenu();
	void printFreePipes();
	void printFreeCS();
	void printTableConnections();
	bool checkFreePipes();
	bool checkFreeCS();
	bool checkingConnections();
	void findCSZeroDegreeOfOutcome(std::unordered_map<size_t, CompressorStation>, std::unordered_map<size_t, Pipe>);
	void fillMapCSInUSe();
	void fillMapPipeInUse();
	void printGraph();
	void sortGraph();
	void printSortGraph();
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