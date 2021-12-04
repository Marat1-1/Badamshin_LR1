#include "GasTransmissionNetwork.h"
#include "Verification.h"
#include "Console.h"
#include <conio.h>
#include <iomanip>

// ���� ��� ������ � �������������
void GasTransmissionNetwork::printMenu()
{
	Console::PrintTitleText("\n\t\t\t\t���������� ���������������� �����\n");
	std::cout << "\n�������� ���� �� ������� ����: " << std::endl
		<< "1. �������� �����" << std::endl
		<< "2. ������� �����" << std::endl
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
		if (!el.second.IsUsed())
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
		if (!el.second.IsUsed())
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
	size_t tabulation_20 = 20, tabulation_30 = 30, tableWidth = 101;
	Console::PrintTitleText("\n\t\t\t\t������� ������");
	Console::PrintChar('-', tableWidth);
	std::cout << "|" << std::setw(tabulation_20) << "ID PIPE" << std::setw(tabulation_30) << "ID Output CS" << std::setw(tabulation_30) << "ID Input CS" << std::setw(tabulation_20) << "|" << std::endl;
	Console::PrintChar('-', tableWidth);
	for (const auto& el : newPipeCollection.pipeCollection)
		if (el.second.IsUsed())
			std::cout << "|" << std::setw(tabulation_20) << el.first << std::setw(tabulation_30) << el.second.GetOutId() << std::setw(tabulation_30) << el.second.GetInId() << std::setw(tabulation_20) << "|" << std::endl;
	Console::PrintChar('-', tableWidth);
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
						if (newCSCollection.csCollection.find(outId) != newCSCollection.csCollection.end() && !(*newCSCollection.csCollection.find(outId)).second.IsUsed())
						{
							while (true)
							{
								inId = verification::GetNumericValue<size_t>("\n������� id �� � ������� ����� ������� ��������� �����: ",
									"\n������������ ����! Id ����� ������������� �����, ��� ���� �� � ����� id ������ ���� �������, ��������� ����!", 1, CompressorStation::GetMaxID());
								if (inId != outId && newCSCollection.csCollection.find(inId) != newCSCollection.csCollection.end() && !(*newCSCollection.csCollection.find(inId)).second.IsUsed())
								{
									newPipeCollection.pipeCollection[idPipe].SetInId(inId);
									newPipeCollection.pipeCollection[idPipe].SetOutId(outId);
									newPipeCollection.pipeCollection[idPipe].SetUsed(true);
									newCSCollection.csCollection[inId].IncCountUse();
									newCSCollection.csCollection[outId].IncCountUse();
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
					(*newCSCollection.csCollection.find((*newPipeCollection.pipeCollection.find(idPipe)).second.GetOutId())).second.DecCountUse();
					(*newCSCollection.csCollection.find((*newPipeCollection.pipeCollection.find(idPipe)).second.GetInId())).second.DecCountUse();
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