#include "PipeCollection.h"
#include "Verification.h"
#include <iomanip>


// ������� id
size_t Pipe::maxIdPipe = 0;

// ���������� ����� � ������
void PipeCollection::Add()
{
	Pipe pipe;
	pipeCollection.emplace(pipe.id, pipe);
}

// �������������� �����
void PipeCollection::Change()
{
	size_t changeId;
	bool query;
	std::cout << "����� ��������� ����: " << pipeCollection.size() << std::endl
		<< "Id ��������� ��� ��������������: ";
	for (const auto& el : pipeCollection)
		std::cout << el.first << "  ";
	std::cout << std::endl;
	if (pipeCollection.empty())
	{
		Console::PrintErrorText("�� �� �������� �� ����� �����, �������������� ����������!");
		verification::GetPressEscape("\n\n����� ����� � ����, ������� ESC: ", "\n������� �� ����������, ������� ESC �� ����������, ���� ������ ��������� � ����!");
		return;
	}
	while (true)
	{
		changeId = verification::GetNumericValue<size_t>("\n������� ����� id �����, ������� �� �� ������ �������������: ",
			"������! �� ����� ������������ ��������, �������� �� ����� �������������� id ��� �� ��������� ������������ ����, ������� id ��� �������������, ����� �����!!!", 1, Pipe::maxIdPipe);
		if (pipeCollection.find(changeId) != pipeCollection.end())
		{
			std::cout << "����������� ��������� �����: "
				<< (pipeCollection[changeId].repair ? "� �������" : "�� � �������")
				<< std::endl;
			pipeCollection[changeId].GhangePipe();
		}
		else
			Console::PrintErrorText("�� ���������� id �� ������� �� ����� �����!!!");
		query = verification::GetBoolValue("\n\n������ �� �� ���������� ������������� �����, ���� ��, �� �������� \"y\", ���� �� ���, �� ������� �� \"n\": ",
			"\n����������� �������! ��������� ���� �� ��������� ���� ��������, �������� �� \"y\", ���� ��, �� \"n\", ���� ���!!!");
		if (!query)
			break;
	}
}

// ����� ������� ���� �� ����� (������ ������ ������)
void PipeCollection::PrintTable()
{
	int tabulation_20 = 20, tabulation_30 = 30, tableWidth = 131;
	Console::PrintTitleText("\n\t\t\t\t������� ����");
	Console::PrintChar('-', tableWidth);
	std::cout << "|" << std::setw(tabulation_20) << "ID" << std::setw(tabulation_30) << "LENGTH" << std::setw(tabulation_30) << "DIAMETER" << std::setw(tabulation_30) << "REPAIR" << std::setw(tabulation_20) << "|" << std::endl;
	Console::PrintChar('-', tableWidth);
	for (const auto& p : pipeCollection)
	{
		std::cout << "|" << std::setw(tabulation_20) << p.second.id << std::setw(tabulation_30) << p.second.length << std::setw(tabulation_30) << p.second.diameter << std::setw(tabulation_30) << (p.second.repair == true ? "true" : "false") << std::setw(tabulation_20) << "|" << std::endl;
	}
	Console::PrintChar('-', tableWidth);
}

// ����� ������� ���� �� �����, ��� ���� ������� ������� ����� ������ ����
void PipeCollection::PrintFilterTable(std::vector<size_t>& vectorId)
{
	int tabulation_20 = 20, tabulation_30 = 30, tableWidth = 131;
	Console::PrintTitleText("\n\n\t\t������� ����");
	Console::PrintChar('-', tableWidth);
	std::cout << "|" << std::setw(tabulation_20) << "ID" << std::setw(tabulation_30) << "LENGTH" << std::setw(tabulation_30) << "DIAMETER" << std::setw(tabulation_30) << "REPAIR" << std::setw(tabulation_20) << "|" << std::endl;
	Console::PrintChar('-', tableWidth);
	for (const auto& id : vectorId)
	{
		std::cout << "|" << std::setw(tabulation_20) << pipeCollection[id].id << std::setw(tabulation_30) << pipeCollection[id].length << std::setw(tabulation_30) << pipeCollection[id].diameter << std::setw(tabulation_30) << (pipeCollection[id].repair == true ? "true" : "false") << std::setw(tabulation_20) << "|" << std::endl;
	}
	Console::PrintChar('-', tableWidth);
}

// ����� ���� � ����
void PipeCollection::SaveToFile(std::ofstream& fout)
{
	size_t percent = 0;
	if (pipeCollection.empty())
	{
		Console::PrintErrorText("�� �� �������� �� ����� �����!");
		return;
	}
	fout << Pipe::maxIdPipe << std::endl;
	for (auto& el : pipeCollection)
		el.second.SaveToFile(fout);
	while (percent <= 100)
	{
		std::cout << "\t\t" << "���������� ��: " << percent++ << "%";
		std::cout << '\r';
		Sleep(20);
	}
	Console::PrintTitleText("\n\t\t����� ���������!");
}

// �������� ���� �� �����
void PipeCollection::DownloadFromFile(std::ifstream& fin)
{
	size_t percent = 0;
	size_t maxId;
	fin >> maxId;
	if (maxId > Pipe::maxIdPipe)
		Pipe::maxIdPipe = maxId;
	while (fin.peek() != ' ' && fin.peek() != -1)
	{
		Pipe pipe(fin);
		pipeCollection.emplace(pipe.id, pipe);
		fin.ignore(1000, '\n');
	}
	while (percent <= 100)
	{
		std::cout << "\t\t" << "�������� ����: " << percent++ << "%";
		std::cout << '\r';
		Sleep(20);
	}
	Console::PrintTitleText("\n����� ���������!");
}

// ������ ����
void PipeCollection::Filter()
{
	bool query;
	query = verification::GetBoolValue("\n���� ��� ����� �����, ��������� �������: \"� �������\", �� �������� �� \"y\", ���� �� ����� ��������� �����, �� �������� �� \"n\"",
		"\n����������� �������! ��������� ���� �� ��������� ���� ��������, �������� �� \"y\" ��� �� �� \"n\"!!!");
	for (const auto& el : pipeCollection)
		if (el.second.repair == query)
			vectorIdForFilter.push_back(el.first);
}

// �������� ����
void PipeCollection::Delete()
{
	if (pipeCollection.empty())
	{
		Console::PrintErrorText("�� �� �������� �� ����� �����, �������� ����������!");
		verification::GetPressEscape("\n\n����� ����� � ����, ������� ESC: ", "\n������� �� ����������, ������� ESC �� ����������, ���� ������ ��������� � ����!");
		return;
	}
	bool query;
	query = verification::GetBoolValue("\n������� �� \"y\", ���� ������ ���������� �������� �� ����� �����, �� \"n\", ���� ������ ���������� �������� �������� �� �������: ",
		"\n����������� �������! ��������� ���� �� ��������� ��������!!!");
	if (query) // �������� �� ����� �����
	{
		std::cout << "\n\n����� ����: " << pipeCollection.size() << std::endl
			<< "Id ��������� ��� ��������: ";
		for (const auto& el : pipeCollection)
			std::cout << el.first << "  ";
		std::set<size_t> setIdForDelete = verification::GetMultipleNumericValues<size_t>(
			"\n������� ����� ������ id ����, ������� ������ �� �������: ",
			"\n������, �� ����� ������������ ������, ��������� ���� ������!");
		for (const auto id : setIdForDelete)
		{
			if (pipeCollection.find(id) != pipeCollection.end())
			{
				pipeCollection.erase(id);
				Console::PrintTitleText("����� � id = " + std::to_string(id) + " ���� �������!\n");
			}
			else
				Console::PrintErrorText("����� � id = " + std::to_string(id) + " �� ���� ������� � ������ ���� ����!\n");
		}
	}
	else // �������� ��������
	{
		Filter();
		if (!vectorIdForFilter.empty())
		{
			std::cout << "\n\n�����, ���������� ����� ����������:" << std::endl;
			PrintFilterTable(vectorIdForFilter);
			query = verification::GetBoolValue("\n���� ������ ������� ��� ��������������� �����, ������� \"y\", ���� ����� �� ���, �� ������� \"n\": ",
				"\n����������� �������! ��������� ���� �� ��������� ���� ��������!!!");
			if (query) // ������� ��� ��������������� �����
			{
				for (const auto& i : vectorIdForFilter)
					pipeCollection.erase(i);
				Console::PrintTitleText("\n����� ���� ������� �������!");
			}
			else // ������� ����� ��������������� ����
			{
				std::set<size_t> setIdForDelete = verification::GetMultipleNumericValues<size_t>(
					"\n������� ����� ������ id ����, ������� ������ �� �������: ",
					"\n������, �� ����� ������������ ������, ��������� ���� ������!");
				for (auto id : setIdForDelete)
				{
					auto it = std::find(vectorIdForFilter.begin(), vectorIdForFilter.end(), id);
					if (it != vectorIdForFilter.end())
					{
						pipeCollection.erase(id);
						Console::PrintTitleText("����� � id = " + std::to_string(id) + " ���� �������!\n");
					}
					else
						Console::PrintErrorText("����� � id = " + std::to_string(id) + " �� ���� ������� � ������ ��������������� ����!\n");
				}
			}
			vectorIdForFilter.clear();
		}
		else
			Console::PrintErrorText("\n�� ������ ������� �� ���� ������� �� ����� �����!");
	}
	std::cout << std::endl;
	system("pause");
}

// �������� �������������� ����
void PipeCollection::BatchChange()
{
	if (pipeCollection.empty())
	{
		Console::PrintErrorText("\n�� �� �������� �� ����� �����, �������� �������������� ����������!");
		verification::GetPressEscape("\n\n����� ����� � ����, ������� ESC: ", "\n������� �� ����������, ������� ESC �� ����������, ���� ������ ��������� � ����!");
		return;
	}
	bool query;
	bool repairStatus;
	query = verification::GetBoolValue("\n������� �� \"y\", ���� ������ ������������� ��� �����, �� \"n\", ���� ������ ����������� ������������: ",
		"\n������!!! �� ������ �� ������������ ������, ����������� ���� �� ��������� ��� ��������!!!");
	if (!query) // �������� ��������������
	{
		Filter();
		if (!vectorIdForFilter.empty())
		{
			PrintFilterTable(vectorIdForFilter);
			query = verification::GetBoolValue("\n������� �� \"y\", ���� ������ ������������� ��� ��������������� �����, �� \"n\", ���� ������ ����������� ������������: ",
				"\n������!!! �� ������ �� ������������ ������, ����������� ���� �� ��������� ��� ��������!!!");
			if (!query) // ������������� ��� ��������������� �����
			{
				std::set<size_t> setIdForChange = verification::GetMultipleNumericValues<size_t>(
					"\n������� ����� ������ id ����, ������� ������ �� ���������������: ",
					"\n������, �� ����� ������������ ������, ��������� ���� ������!");
				repairStatus = verification::GetBoolValue("\n\n������� ����� ��������� ��� ��������� ����, ���� � �������, �� ������� \"y\" �� ����������, ���� �� ���, �������� �� \"n\": ",
					"\n����������� �������! ��������� ���� �� ��������� ���� ��������, �������� �� \"y\", ���� ��, �� \"n\", ���� ���!!!");
				for (const auto id : setIdForChange)
				{
					auto it = std::find(vectorIdForFilter.begin(), vectorIdForFilter.end(), id);
					if (it != vectorIdForFilter.end())
					{
						pipeCollection[id].repair = repairStatus;
						Console::PrintTitleText("����� � id - " + std::to_string(id) + " ���� ���������������");
					}
					else
						Console::PrintErrorText("����� � id - " + std::to_string(id) + " �� ���� ������� � ������ ��������������� ����\n");
				}
			}
			else // ��������������� ����� ��������������� ����
			{
				repairStatus = verification::GetBoolValue("\n\n������� ����� ��������� ��� ��������� ����, ���� � �������, �� ������� \"y\" �� ����������, ���� �� ���, �������� �� \"n\": ",
					"\n����������� �������! ��������� ���� �� ��������� ���� ��������, �������� �� \"y\", ���� ��, �� \"n\", ���� ���!!!");
				for (const auto& i : vectorIdForFilter)
					pipeCollection[i].repair = repairStatus;
				Console::PrintTitleText("\n����� ���������������!");
			}
		}
		else
			Console::PrintErrorText("\n�� ������ ������� �� ���� ������� �� ����� �����!");
		vectorIdForFilter.clear();
	}
	else // �������������� ���� ����
	{
		PrintTable();
		repairStatus = verification::GetBoolValue("\n\n������� ����� ��������� ��� ��������� ����, ���� � �������, �� ������� \"y\" �� ����������, ���� �� ���, �������� �� \"n\": ",
			"\n����������� �������! ��������� ���� �� ��������� ���� ��������, �������� �� \"y\", ���� ��, �� \"n\", ���� ���!!!");
		for (auto& el : pipeCollection)
			el.second.repair = repairStatus;
		Console::PrintTitleText("\n����� ���������������!");
	}
	system("pause");
}