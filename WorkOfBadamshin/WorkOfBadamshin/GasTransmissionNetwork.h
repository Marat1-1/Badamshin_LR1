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
	std::vector<std::vector<size_t>> Matrix;
	std::unordered_map<size_t, size_t> mapIdIndex;
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
	void fillMatrixMapIdIndex();
	std::vector<size_t> findPath(size_t, size_t, double&);
	void printPath(const std::vector<size_t>&);
	bool bfs(std::vector<std::vector<size_t>>, size_t, size_t, std::vector<int>&);
	int fordFulkerson(size_t, size_t);
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