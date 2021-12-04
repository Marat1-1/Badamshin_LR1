#include "GasTransmissionNetwork.h"
#include "Verification.h"
#include "Console.h"
#include <conio.h>

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

// ���������� ���� id-������ ��������� ����
void GasTransmissionNetwork::fillSetFreePipes()
{
	for (const auto& el : newPipeCollection.pipeCollection)
		if (!el.second.IsUsed())
			freePipes.insert(el.first);
}

// ���������� ���� id-������ ��������� ��
void GasTransmissionNetwork::fillSetFreeCS()
{
	for (const auto& el : newCSCollection.csCollection)
		if (!el.second.IsUsed())
			freeCS.insert(el.first);
}

// ����� ��������� ���� � ��
void GasTransmissionNetwork::printFreePipes()
{
	std::vector<size_t> vectorForOutput;
	for (auto id : freePipes)
		if (!newPipeCollection.pipeCollection[id].IsUsed())
			vectorForOutput.push_back(id);
	newPipeCollection.PrintFilterTable(vectorForOutput);
}

void GasTransmissionNetwork::printFreeCS()
{
	std::vector<size_t> vectorForOutput;
	for (auto id : freeCS)
		if (!newCSCollection.csCollection[id].IsUsed())
			vectorForOutput.push_back(id);
	newCSCollection.PrintFilterTable(vectorForOutput);
}

// ������� ���������� ���������������� �����
void GasTransmissionNetwork::manageNetwork()
{
	fillSetFreePipes();
	fillSetFreeCS();
	while (true)
	{
		printMenu();
		switch (_getch())
		{
		case '1':
		{
			if (freePipes.empty() || freeCS.empty())
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
				if (freePipes.find(idPipe) != freePipes.end())
				{
					while (true)
					{
						outId = verification::GetNumericValue<size_t>("\n������� id �� �� ������� ����� �������� ��������� �����: ",
							"\n������������ ����! Id ����� ������������� �����, ��� ���� �� � ����� id ������ ���� �������, ��������� ����!", 1, CompressorStation::GetMaxID());
						if (freeCS.find(outId) != freeCS.end())
						{
							while (true)
							{
								inId = verification::GetNumericValue<size_t>("\n������� id �� � ������� ����� ������� ��������� �����: ",
									"\n������������ ����! Id ����� ������������� �����, ��� ���� �� � ����� id ������ ���� �������, ��������� ����!", 1, CompressorStation::GetMaxID());
								if (inId != outId && freeCS.find(inId) != freeCS.end())
								{
									newPipeCollection.pipeCollection[idPipe].SetInId(inId);
									newPipeCollection.pipeCollection[idPipe].SetOutId(outId);
									newPipeCollection.pipeCollection[idPipe].SetUsed(true);
									freePipes.erase(idPipe);
									newCSCollection.csCollection[inId].IncCountUse();
									newCSCollection.csCollection[outId].IncCountUse();
									if (newCSCollection.csCollection[inId].IsUsed())
										freeCS.erase(inId);
									if (newCSCollection.csCollection[outId].IsUsed())
										freeCS.erase(outId);
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