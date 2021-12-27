#include "GasTransmissionNetwork.h"
#include "Verification.h"
#include "Console.h"
#include <conio.h>
#include <iomanip>
#include <queue>

// ���� ��� ������ � �������������
void GasTransmissionNetwork::printMenu()
{
	Console::PrintTitleText("\n\t\t\t\t���������� ���������������� �����\n");
	std::cout << "\n�������� ���� �� ������� ����: " << std::endl
		<< "1. �������� �����" << std::endl
		<< "2. ������� �����" << std::endl
		<< "3. ������������� ����" << std::endl
		<< "4. ������� ������� ������" << std::endl
		<< "5. ����� ���������� ���� �� ����� ������� � ������" << std::endl
		<< "6. ����� ������������ ����� �� ����� ������� � ������" << std::endl
		<< "0. ����� � ����� ����" << std::endl
		<< "����: ";
}

// ����� ��������� ���� � ��
void GasTransmissionNetwork::printFreePipes()
{
	std::vector<size_t> vectorForOutput;
	for (const auto& el : newPipeCollection.pipeCollection)
		if (!el.second.IsUsed())
			vectorForOutput.push_back(el.first);
	newPipeCollection.PrintFilterTable(vectorForOutput);
}

void GasTransmissionNetwork::printFreeCS()
{
	std::vector<size_t> vectorForOutput;
	for (const auto& el : newCSCollection.csCollection)
		if (!el.second.IsFullyField())
			vectorForOutput.push_back(el.first);
	newCSCollection.PrintFilterTable(vectorForOutput);
}

// �������� �� ������� ��������� ���� � ��
bool GasTransmissionNetwork::checkFreePipes()
{
	for (const auto& el : newPipeCollection.pipeCollection)
		if (!el.second.IsUsed())
			return true;
	return false;
}

bool GasTransmissionNetwork::checkFreeCS()
{
	for (const auto& el : newCSCollection.csCollection)
		if (!el.second.IsFullyField())
			return true;
	return false;
}

// �������� �� ������� ������
bool GasTransmissionNetwork::checkingConnections()
{
	for (const auto& el : newPipeCollection.pipeCollection)
		if (el.second.IsUsed())
			return true;
	return false;
}

// ����� ������� ������
void GasTransmissionNetwork::printTableConnections()
{
	size_t tabulation_20 = 20, tabulation_30 = 30, tableWidth = 131;
	Console::PrintTitleText("\n\t\t\t\t������� ������");
	Console::PrintChar('-', tableWidth);
	std::cout << "|" << std::setw(tabulation_20) << "ID PIPE" << std::setw(tabulation_30) << "ID Output CS" << std::setw(tabulation_30) << "ID Input CS" << std::setw(tabulation_30) << "Weight" << std::setw(tabulation_20) << "|" << std::endl;
	Console::PrintChar('-', tableWidth);
	for (const auto& el : newPipeCollection.pipeCollection)
		if (el.second.IsUsed())
			std::cout << "|" << std::setw(tabulation_20) << el.first << std::setw(tabulation_30) << el.second.GetOutId() << std::setw(tabulation_30) << el.second.GetInId() << std::setw(tabulation_30) << el.second.length << std::setw(tabulation_20) << "|" << std::endl;
	Console::PrintChar('-', tableWidth);
}

// ���������� ����� ���� � �� ��� �����
void GasTransmissionNetwork::fillMapCSInUse()
{
	mapCSInUse.clear();
	for (const auto& el : newCSCollection.csCollection)
		if (el.second.IsUsed())
			mapCSInUse.emplace(el.first, el.second);
}

void GasTransmissionNetwork::fillMapPipeInUse()
{
	mapPipeInUse.clear();
	for (const auto& el : newPipeCollection.pipeCollection)
		if (el.second.IsUsed())
			mapPipeInUse.emplace(el.first, el.second);
}

// ����������� ����� ������ �������� � ������� �������� ������ � ���������� ������� ��������������� id
void GasTransmissionNetwork::findCSZeroDegreeOfOutcome(std::unordered_map<size_t, CompressorStation> mapCS, std::unordered_map<size_t, Pipe> mapPipe)
{
	size_t counter = 0;
	std::vector<size_t> idDelCS;
	std::vector<size_t> idDelPipe;
	for (const auto& elCS : mapCS)
		if (elCS.second.GetDegreeOfEntry() == 0)
		{
			++counter;
			idDelCS.push_back(elCS.first);
			sortIdCS.push_back(elCS.first);
			for (const auto& elPipe : mapPipe)
				if (elPipe.second.GetOutId() == elCS.first)
				{
					idDelPipe.push_back(elPipe.first);
				}
		}
	for (const auto& id : idDelCS)
		mapCS.erase(id);
	for (const auto& id : idDelPipe)
	{
		(*mapCS.find((*mapPipe.find(id)).second.GetInId())).second.DecDegreeOfEntry();
		mapPipe.erase(id);
	}
	idDelCS.clear();
	idDelPipe.clear();
	if (counter == 0)
		throw - 1;
	if (mapCS.empty() && mapPipe.empty())
		return;
	findCSZeroDegreeOfOutcome(mapCS, mapPipe);
}

// ����� ������������������ �����
void GasTransmissionNetwork::printGraph()
{
	Console::PrintTitleText("\n\n����������������� ����:");
	Console::PrintChar('-', mapCSInUse.size() * 20 + 1);
	std::cout << "|";
	for (const auto& el : mapCSInUse)
		std::cout << std::setw(10) << el.first << std::setw(10) << "|";
	std::cout << std::endl;
	Console::PrintChar('-', mapCSInUse.size() * 20 + 1);
}

// ����� ���������������� �����
void GasTransmissionNetwork::printSortGraph()
{
	Console::PrintTitleText("\n\n��������������� ����:");
	Console::PrintChar('-', mapCSInUse.size() * 20 + 1);
	std::cout << "|";
	for (const auto& id : sortIdCS)
		std::cout << std::setw(10) << id << std::setw(10) << "|";
	std::cout << std::endl;
	Console::PrintChar('-', mapCSInUse.size() * 20 + 1);
}

// ���������� �����
void GasTransmissionNetwork::sortGraph()
{
	sortIdCS.clear();
	fillMapCSInUse();
	fillMapPipeInUse();
	try
	{
		findCSZeroDegreeOfOutcome(mapCSInUse, mapPipeInUse);
		printGraph();
		printSortGraph();
	}
	catch (int)
	{
		Console::PrintErrorText("\n�������������� ���������� ����������, ��������� ���� �������� ���������!!!");
	}
}

// ���������� ������� �����
void GasTransmissionNetwork::fillMatrixMapIdIndex()
{
	Matrix.clear();
	mapIdIndex.clear();
	// ��������� ��� ������ ����� id �� � �������� � ������� �����
	size_t counter = 0;
	const size_t SIZE = mapCSInUse.size();
	Matrix.resize(SIZE);
	for (const auto& cs : mapCSInUse)
		mapIdIndex.emplace(cs.first, counter++);
	// ������������� ������� ������
	for (size_t i = 0; i < SIZE; i++)
		Matrix[i].resize(SIZE);

	for (const auto& pipe : mapPipeInUse)
		Matrix[mapIdIndex[pipe.second.GetOutId()]][mapIdIndex[pipe.second.GetInId()]] = pipe.second.length;
}

// ����� ����������� ���� https://prog-cpp.ru/deikstra/
std::vector<size_t> GasTransmissionNetwork::findPath(size_t outID, size_t inID, double& weightPath)
{
	const size_t SIZE = mapCSInUse.size();
	std::vector<size_t> resultPath;
	std::vector<double> d; d.resize(SIZE); // ����������� ����������
	std::vector<size_t> v; v.resize(SIZE); // ���������� �������
	double temp, min;
	size_t minindex;
	fillMatrixMapIdIndex(); // ��������� ������� ����� � ������

	//������������� ������ � ����������
	for (size_t i = 0; i < SIZE; i++)
	{
		d[i] = 10000;
		v[i] = 1;
	}
	size_t begin_index = mapIdIndex[outID];
	d[begin_index] = 0;
	// ��� ���������
	do {
		minindex = 10000;
		min = 10000;
		for (size_t i = 0; i < SIZE; i++)
		{ // ���� ������� ��� �� ������ � ��� ������ min
			if ((v[i] == 1) && (d[i] < min))
			{ // ��������������� ��������
				min = d[i];
				minindex = i;
			}
		}
		// ��������� ��������� ����������� ���
		// � �������� ���� �������
		// � ���������� � ������� ����������� ����� �������
		if (minindex != 10000)
		{
			for (size_t i = 0; i < SIZE; i++)
			{
				if (Matrix[minindex][i] > 0)
				{
					temp = min + Matrix[minindex][i];
					if (temp < d[i])
					{
						d[i] = temp;
					}
				}
			}
			v[minindex] = 0;
		}
	} while (minindex < 10000);
	
	// �������� ��� �� ������ ����, ���� ���, �� ���������� ����������
	if (d[mapIdIndex[inID]] == 10000)
		throw - 1;
	weightPath = d[mapIdIndex[inID]];

	// �������������� ����
	std::vector<size_t> ver; // ������ ���������� ������
	size_t end = mapIdIndex[inID]; // ������ �������� �������
	ver.push_back(end); // ��������� ������� - �������� �������
	size_t weight = d[end]; // ��� �������� �������
	while (end != begin_index) // ���� �� ����� �� ��������� �������
	{
		for (size_t i = 0; i < SIZE; i++) // ������������� ��� �������
			if (Matrix[i][end] != 0)   // ���� ����� ����
			{
				size_t temp = weight - Matrix[i][end]; // ���������� ��� ���� �� ���������� �������
				if (temp == d[i]) // ���� ��� ������ � ������������
				{                 // ������ �� ���� ������� � ��� �������
					weight = temp; // ��������� ����� ���
					end = i;       // ��������� ���������� �������
					ver.push_back(i); // � ���������� �� � ������
				}
			}
	}
	// ������� �� �������� � ID
	for (size_t i = 0; i < ver.size(); i++)
	{
		for(const auto& el : mapIdIndex)
			if (el.second == ver[i])
				resultPath.push_back(el.first);
	}
	std::reverse(resultPath.begin(), resultPath.end());
	return resultPath;
}

// ����� ���������������� ����
void GasTransmissionNetwork::printPath(const std::vector<size_t>& vectorPath)
{
	Console::PrintTitleText("\n\n���������� ����:");
	Console::PrintChar('-', vectorPath.size() * 20 + 1);
	std::cout << "|";
	for (const auto& id : vectorPath)
		std::cout << std::setw(10) << id << std::setw(10) << "|";
	std::cout << std::endl;
	Console::PrintChar('-', vectorPath.size() * 20 + 1);
}


// ���� ������ �����-���������� https://www.geeksforgeeks.org/ford-fulkerson-algorithm-for-maximum-flow-problem/
bool GasTransmissionNetwork::bfs(std::vector<std::vector<size_t>> rGraph, size_t s, size_t t, std::vector<int>& parent)
{
	// Create a visited array and mark all vertices as not
	// visited
	const size_t SIZE = mapCSInUse.size();
	std::vector<bool> visited(SIZE, false);

	// Create a queue, enqueue source vertex and mark source
	// vertex as visited
	std::queue<int> q;
	q.push(s);
	visited[s] = true;
	parent[s] = -1;

	// Standard BFS Loop
	while (!q.empty()) {
		int u = q.front();
		q.pop();

		for (int v = 0; v < SIZE; v++) {
			if (visited[v] == false && rGraph[u][v] > 0) {
				// If we find a connection to the sink node,
				// then there is no point in BFS anymore We
				// just have to set its parent and can return
				// true
				if (v == t) {
					parent[v] = u;
					return true;
				}
				q.push(v);
				parent[v] = u;
				visited[v] = true;
			}
		}
	}

	// We didn't reach sink in BFS starting from source, so
	// return false
	return false;
}

// Returns the maximum flow from s to t in the given graph
int GasTransmissionNetwork::fordFulkerson(size_t outID, size_t inID)
{
	fillMatrixMapIdIndex();
	int u, v;
	size_t s = mapIdIndex[outID];
	size_t t = mapIdIndex[inID];
	const size_t SIZE = mapCSInUse.size();
	// Create a residual graph and fill the residual graph
	// with given capacities in the original graph as
	// residual capacities in residual graph
	std::vector<std::vector<size_t>> rGraph(SIZE); // Residual graph where rGraph[i][j]
			 // indicates residual capacity of edge
			 // from i to j (if there is an edge. If
			 // rGraph[i][j] is 0, then there is not)
	for (auto& el : rGraph)
		el.resize(SIZE);

	for (u = 0; u < SIZE; u++)
		for (v = 0; v < SIZE; v++)
			rGraph[u][v] = Matrix[u][v];

	std::vector<int> parent(SIZE); // This array is filled by BFS and to
				   // store path

	int max_flow = 0; // There is no flow initially

	// Augment the flow while there is path from source to
	// sink
	while (bfs(rGraph, s, t, parent)) {
		// Find minimum residual capacity of the edges along
		// the path filled by BFS. Or we can say find the
		// maximum flow through the path found.
		int path_flow = INT_MAX;
		for (v = t; v != s; v = parent[v]) {
			u = parent[v];
			path_flow = min(path_flow, rGraph[u][v]);
		}

		// update residual capacities of the edges and
		// reverse edges along the path
		for (v = t; v != s; v = parent[v]) {
			u = parent[v];
			rGraph[u][v] -= path_flow;
			rGraph[v][u] += path_flow;
		}

		// Add path flow to overall flow
		max_flow += path_flow;
	}

	// Return the overall flow
	return max_flow;
}


// ������� ���������� ���������������� �����
void GasTransmissionNetwork::manageNetwork()
{
	while (true)
	{
		printMenu();
		switch (_getch())
		{
		case '1':
		{
			if (!checkFreePipes() || !checkFreeCS())
			{
				Console::PrintErrorText("\n��� ��������� ���� ��� ��! ���� �������� ����� �����, ���� ������� ����� � ������ � ����������� ��.");
				system("pause");
				system("CLS");
				break;
			}
			size_t idPipe;
			size_t inId;
			size_t outId;
			bool query;
			std::cout << "\n��������� �����, ������� ����� ������������ ��� ���������� ����: " << std::endl;
			printFreePipes();
			std::cout << "\n��������� ��, ������� ����� ������������ ��� ���������� ����: " << std::endl;
			printFreeCS();
			while (true)
			{
				idPipe = verification::GetNumericValue<size_t>("\n������� id �����, ��� ������� ������ �� �������� �����: ",
					"\n������������ ����! Id ����� ������������� �����, ��� ���� ����� � ����� id ������ ���� �������, ��������� ����!", 1, Pipe::GetMaxID());
				if (newPipeCollection.pipeCollection.find(idPipe) != newPipeCollection.pipeCollection.end() && !(*newPipeCollection.pipeCollection.find(idPipe)).second.IsUsed())
				{
					while (true)
					{
						outId = verification::GetNumericValue<size_t>("\n������� id �� �� ������� ����� �������� ��������� �����: ",
							"\n������������ ����! Id ����� ������������� �����, ��� ���� �� � ����� id ������ ���� �������, ��������� ����!", 1, CompressorStation::GetMaxID());
						if (newCSCollection.csCollection.find(outId) != newCSCollection.csCollection.end() && !(*newCSCollection.csCollection.find(outId)).second.IsFullyField())
						{
							while (true)
							{
								inId = verification::GetNumericValue<size_t>("\n������� id �� � ������� ����� ������� ��������� �����: ",
									"\n������������ ����! Id ����� ������������� �����, ��� ���� �� � ����� id ������ ���� �������, ��������� ����!", 1, CompressorStation::GetMaxID());
								if (inId != outId && newCSCollection.csCollection.find(inId) != newCSCollection.csCollection.end() && !(*newCSCollection.csCollection.find(inId)).second.IsFullyField())
								{
									newPipeCollection.pipeCollection[idPipe].SetInId(inId);
									newPipeCollection.pipeCollection[idPipe].SetOutId(outId);
									newPipeCollection.pipeCollection[idPipe].SetUsed(true);
									newCSCollection.csCollection[inId].IncDegreeOfEntry();
									newCSCollection.csCollection[outId].IncDegreeOfOutcome();
									Console::PrintTitleText("����� ���� �������!");
									break;
								}
								else
									Console::PrintErrorText("������! �� ���������� id �� ������� ��������� �� ��� �� id ������ ������� � id ������ � �����! ��������� ����.");
							}
							break;
						}
						else
						{
							Console::PrintErrorText("�� ���������� id �� ������� ��������� ��! ��������� ����.");
						}
					}
				}
				else
				{
					Console::PrintErrorText("�� ���������� id �� ������� ��������� �����! ��������� ����.");
					continue;
				}
				if (!checkFreePipes() || !checkFreeCS())
				{
					Console::PrintErrorText("��������, �� � ��� �� �������� ���������, ����� �������� �� � ����!");
					break;
				}
				query = verification::GetBoolValue("������ �� ���������� ��������� �����, ������� \"y\", ���� ��, \"n\", ���� ���: ",
					"������������ �������, ��������� ���� �� ��������� ��������.");
				if (!query)
					break;
			}
			std::cout << std::endl;
			system("pause");
			system("CLS");
			break;
		}
		case '2':
		{
			if (!checkingConnections())
			{
				Console::PrintErrorText("\n����� ����������, ������� �������� �����, ������ ����� �� ������� ������� �.");
				system("pause");
				system("CLS");
				break;
			}
			size_t idPipe;
			bool query;
			std::cout << "\n������� ��������� ������:" << std::endl;
			printTableConnections();
			while (true)
			{
				idPipe = verification::GetNumericValue<size_t>("\n������� id ����� �� �������, ������� �� �� ������ ������ �� �����: ",
					"\n������������ ����! Id ����� ������������� �����, ��� ���� ����� � ����� id ������ ���� �������, ��������� ����!", 1, Pipe::GetMaxID());
				if (newPipeCollection.pipeCollection.find(idPipe) != newPipeCollection.pipeCollection.end() && (*newPipeCollection.pipeCollection.find(idPipe)).second.IsUsed())
				{
					(*newCSCollection.csCollection.find((*newPipeCollection.pipeCollection.find(idPipe)).second.GetOutId())).second.DecDegreeOfOutcome();
					(*newCSCollection.csCollection.find((*newPipeCollection.pipeCollection.find(idPipe)).second.GetInId())).second.DecDegreeOfEntry();
					(*newPipeCollection.pipeCollection.find(idPipe)).second.SetInId(0);
					(*newPipeCollection.pipeCollection.find(idPipe)).second.SetOutId(0);
					(*newPipeCollection.pipeCollection.find(idPipe)).second.SetUsed(false);
					Console::PrintTitleText("����� ������� �������!");
				}
				else
				{
					Console::PrintErrorText("�� ���������� id �� ������� �����, �������� �� ��� ������� ��� ����� ��� �� �� ��������� �!");
					continue;
				}
				if (!checkingConnections())
				{
					Console::PrintErrorText("�� ������� ��� �����!!!");
					break;
				}
				query = verification::GetBoolValue("������ �� �� ���������� ������� �����, ������� \"y\", ���� ��, \"n\", ���� ���: ",
					"������������ �������, ��������� ���� �� ��������� ��������.");
				if (!query)
					break;
			}
			std::cout << std::endl;
			system("pause");
			system("CLS");
			break;
		}
		case '3':
		{
			sortGraph();
			system("pause");
			system("CLS");
			break;
		}
		case '4':
		{
			printTableConnections();
			system("pause");
			system("CLS");
			break;
		}
		case '5':
		{
			if (!checkingConnections())
			{
				Console::PrintErrorText("\n����� ����������, ������� �������� �����, ������ ����� �� ������� ����� ���������� ����.");
				system("pause");
				system("CLS");
				break;
			}
			fillMapCSInUse();
			fillMapPipeInUse();
			size_t idCSOut;
			size_t idCSIn;
			std::cout << "\n������� ������:" << std::endl;
			printTableConnections();
			while (true)
			{
				idCSOut = verification::GetNumericValue<size_t>("\n������� id �� �� �����, ������� ����� �������� ������� ����: ",
					"Id �� ������������� ����� �����, ��� ���� �� � ����� id ������ ���� ��������� �����!!!", 1, CompressorStation::GetMaxID());
				if (mapCSInUse.find(idCSOut) == mapCSInUse.end())
				{
					Console::PrintErrorText("�� � ������ ID ����������� � �����, ����������� ������� ������ ����� ����������� � ��������� ����!");
					continue;
				}
				else
					break;
			}
			while (true)
			{
				idCSIn = verification::GetNumericValue<size_t>("\n������� id �� �� �����, ������� ����� �������� ������ ����: ",
					"Id �� ������������� ����� �����, ��� ���� �� � ����� id ������ ���� ��������� �����!!!", 1, CompressorStation::GetMaxID());
				if (mapCSInUse.find(idCSIn) == mapCSInUse.end())
				{
					Console::PrintErrorText("�� � ������ ID ����������� � �����, ����������� ������� ������ ����� ����������� � ��������� ����!");
					continue;
				}
				else
					break;
			}
			try
			{
				double weightPath = 0;
				std::vector<size_t> vectorPath = findPath(idCSOut, idCSIn, weightPath);
				printPath(vectorPath);
				std::cout << "\n��� ����������� ���� �� ������� " << idCSOut << " � ������� " << idCSIn << ": ";
				Console::PrintTitleText(std::to_string(weightPath));
			}
			catch (int)
			{
				Console::PrintErrorText("��������, �� ���� �� ������� " + std::to_string(idCSOut) + " � ������� " + std::to_string(idCSIn) + " �� ����������!");
			}
			system("pause");
			system("CLS");
			break;
		}
		case '6':
		{
			if (!checkingConnections())
			{
				Console::PrintErrorText("\n����� ����������, ������� �������� �����, ������ ����� �� ������� ����� ���������� ����.");
				system("pause");
				system("CLS");
				break;
			}
			fillMapCSInUse();
			fillMapPipeInUse();
			size_t idCSOut;
			size_t idCSIn;
			std::cout << "\n������� ������:" << std::endl;
			printTableConnections();
			while (true)
			{
				idCSOut = verification::GetNumericValue<size_t>("\n������� id �� �� �����, ������� ����� �������� �������: ",
					"Id �� ������������� ����� �����, ��� ���� �� � ����� id ������ ���� ��������� �����!!!", 1, CompressorStation::GetMaxID());
				if (mapCSInUse.find(idCSOut) == mapCSInUse.end())
				{
					Console::PrintErrorText("�� � ������ ID ����������� � �����, ����������� ������� ������ ����� ����������� � ��������� ����!");
					continue;
				}
				else
					break;
			}
			while (true)
			{
				idCSIn = verification::GetNumericValue<size_t>("\n������� id �� �� �����, ������� ����� �������� ������: ",
					"Id �� ������������� ����� �����, ��� ���� �� � ����� id ������ ���� ��������� �����!!!", 1, CompressorStation::GetMaxID());
				if (mapCSInUse.find(idCSIn) == mapCSInUse.end())
				{
					Console::PrintErrorText("�� � ������ ID ����������� � �����, ����������� ������� ������ ����� ����������� � ��������� ����!");
					continue;
				}
				else
					break;
			}
			double maxFlow = fordFulkerson(idCSOut, idCSIn);
			std::cout << "������������ ����� �� ������� " << idCSOut << " � ������� " << idCSIn << ": ";
			Console::PrintTitleText(std::to_string(maxFlow));
			system("pause");
			system("CLS");
			break;
		}
		case '0':
		{
			return;
		}
		default:
		{
			Console::PrintErrorText("\n�� ����������� ������������ ����, ���������� ������� ������� ������!");
			Sleep(2000);
			system("CLS");
			break;
		}
		}
	}
}


// ���������� ���� � ��
void GasTransmissionNetwork::AddPipe()
{
	newPipeCollection.Add();
}

void GasTransmissionNetwork::AddCS()
{
	newCSCollection.Add();
}

// �������������� �� ����� ����� � ��
void GasTransmissionNetwork::ChangePipe()
{
	newPipeCollection.Change();
}

void GasTransmissionNetwork::ChangeCS()
{
	newCSCollection.Change();
}

// ����� ������ ���� � ��
void GasTransmissionNetwork::PrintTablePipes()
{
	newPipeCollection.PrintTable();
}

void GasTransmissionNetwork::PrintTableCS()
{
	newCSCollection.PrintTable();
}

// ���������� ���� � �� � ����
void GasTransmissionNetwork::SaveToFilePipeCollection(std::ofstream& fout)
{
	newPipeCollection.SaveToFile(fout);
}

void GasTransmissionNetwork::SaveToFileCSCollection(std::ofstream& fout)
{
	newCSCollection.SaveToFile(fout);
}

// �������� ���� � �� �� �����
void GasTransmissionNetwork::DownloadFromFilePipeCollection(std::ifstream& fin)
{
	newPipeCollection.DownloadFromFile(fin);
}

void GasTransmissionNetwork::DownloadFromFileCSCollection(std::ifstream& fin)
{
	newCSCollection.DownloadFromFile(fin);
}

// �������� ���� � ��
void GasTransmissionNetwork::DeletePipe()
{
	newPipeCollection.Delete();
}

void GasTransmissionNetwork::DeleteCS()
{
	newCSCollection.Delete();
}

// �������� �������������� ���� � ��
void GasTransmissionNetwork::BatchChangePipeCollection()
{
	newPipeCollection.BatchChange();
}

void GasTransmissionNetwork::BatchChangeCSCollection()
{
	newCSCollection.BatchChange();
}