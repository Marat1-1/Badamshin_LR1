#ifndef GASTRANSMISSIONNETWORK_H
#define GASTRANSMISSIONNETWORK_H

#include "CompressorStationCollection.h"
#include "PipeCollection.h"

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
	void fillMapCSInUse();
	void fillMapPipeInUse();
	void printGraph();
	void sortGraph();
	void printSortGraph();
	std::vector<size_t> findPath(size_t, size_t);
	void printPath(const std::vector<size_t>&);
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