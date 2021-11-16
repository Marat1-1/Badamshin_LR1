#include "PipeCollection.h"
#include "Verification.h"
#include <iomanip>

// ���������� ����� � ������
void PipeCollection::AddPipe()
{
	Pipe pipe;
	pipeCollection.emplace(pipe.id, pipe);
}

// �������������� �����
void PipeCollection::ChangePipe()
{
	size_t changeId;
	bool query;
	std::cout << "����� ��������� ����: " << size(pipeCollection) << std::endl
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
void PipeCollection::PrintTablePipes()
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
void PipeCollection::PrintFilterTablePipes()
{
	int tabulation_20 = 20, tabulation_30 = 30, tableWidth = 131;
	Console::PrintTitleText("\n\n\t\t������� ����");
	Console::PrintChar('-', tableWidth);
	std::cout << "|" << std::setw(tabulation_20) << "ID" << std::setw(tabulation_30) << "LENGTH" << std::setw(tabulation_30) << "DIAMETER" << std::setw(tabulation_30) << "REPAIR" << std::setw(tabulation_20) << "|" << std::endl;
	Console::PrintChar('-', tableWidth);
	for (const auto& id : vectorIdForFilter)
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
	if (fin.peek() != -1)
	{
		fin >> Pipe::maxIdPipe;
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
	else
	{
		Console::PrintErrorText("\n������ ��������� ������ �� ������� �����, ������� ����� ��������� ��� ������!!!");
	}
}

// ������ ����
void PipeCollection::FilterPipe()
{
	bool query;
	query = verification::GetBoolValue("\n���� ��� ����� �����, ��������� �������: \"� �������\", �� �������� �� \"y\", ���� �� ����� ��������� �����, �� �������� �� \"n\"",
		"\n����������� �������! ��������� ���� �� ��������� ���� ��������, �������� �� \"y\" ��� �� �� \"n\"!!!");
	for (const auto& el : pipeCollection)
		if (el.second.repair == query)
			vectorIdForFilter.push_back(el.first);
}

// �������� ����
void PipeCollection::DeletePipe()
{
	size_t delId; // id �����, ������� ����� �������
	bool query;
	if (pipeCollection.empty())
	{
		Console::PrintErrorText("�� �� �������� �� ����� �����, �������� ����������!");
		verification::GetPressEscape("\n\n����� ����� � ����, ������� ESC: ", "\n������� �� ����������, ������� ESC �� ����������, ���� ������ ��������� � ����!");
		return;
	}
	query = verification::GetBoolValue("������� �� \"y\", ���� ������ ���������� �������� �� ����� �����, �� \"n\", ���� ������ ���������� �������� �������� �� �������: ",
		"\n����������� �������! ��������� ���� �� ��������� ��������!!!");
	if (query)
	{
		while (true)
		{
			std::cout << "\n\n����� ����: " << size(pipeCollection) << std::endl
				<< "Id ��������� ��� ��������: ";
			for (const auto& el : pipeCollection)
				std::cout << el.first << "  ";
			std::cout << std::endl;
			delId = verification::GetNumericValue<size_t>("������� id �����, ������� �� �� ������ �������: ",
				"������! �� ����� ������������ ��������, �������� �� ����� �������������� id ��� �� ��������� ������������ ����, ������� id ��� �������������, ����� �����!!!", 1, Pipe::maxIdPipe);
			if (pipeCollection.find(delId) != pipeCollection.end())
			{
				pipeCollection.erase(delId);
				Console::PrintTitleText("����� ���� ������� �������!");
			}
			else
				Console::PrintErrorText("�� ���������� id �� ���� ������� �� ����� �����, �������� ����� ��� ���� �������!!!");
			query = verification::GetBoolValue("\n\n������ �� �� ���������� ������� �����, ���� ��, �� �������� \"y\", ���� �� ���, �� ������� �� \"n\": ",
				"\n����������� �������! ��������� ���� �� ��������� ���� ��������, �������� �� \"y\", ���� ��, �� \"n\", ���� ���!!!");
			if (!query)
				break;
		}
	}
	else
	{
		FilterPipe();
		if (size(vectorIdForFilter) != 0)
		{
			std::cout << "\n\n����� ������� ��������� �����:" << std::endl;
			PrintFilterTablePipes();
			for (const auto& i : vectorIdForFilter)
				pipeCollection.erase(i);
			vectorIdForFilter.clear();
			Console::PrintTitleText("\n\n����� ������� �������!");
		}
		else
			Console::PrintErrorText("\n�� ������ ������� �� ���� ������� �� ����� �����!");
	}
	std::cout << std::endl;
	system("pause");
}

// �������� �������������� ����
void PipeCollection::BatchChangePipe()
{
	bool query;
	bool repairStatus;
	if (pipeCollection.empty())
	{
		Console::PrintErrorText("\n�� �� �������� �� ����� �����, �������� �������������� ����������!");
		verification::GetPressEscape("\n\n����� ����� � ����, ������� ESC: ", "\n������� �� ����������, ������� ESC �� ����������, ���� ������ ��������� � ����!");
		return;
	}
	query = verification::GetBoolValue("\n������� �� \"y\", ���� ������ ������������� ��� �����, �� \"n\", ���� ������ ����������� ������������: ",
		"\n������!!! �� ������ �� ������������ ������, ����������� ���� �� ��������� ��� ��������!!!");
	if (!query)
	{
		FilterPipe();
		if (size(vectorIdForFilter) != 0)
		{
			PrintFilterTablePipes();
			repairStatus = verification::GetBoolValue("\n\n������� ����� ��������� ��� ��������� ����, ���� � �������, �� ������� \"y\" �� ����������, ���� �� ���, �������� �� \"n\": ",
				"\n����������� �������! ��������� ���� �� ��������� ���� ��������, �������� �� \"y\", ���� ��, �� \"n\", ���� ���!!!");
			for (const auto& i : vectorIdForFilter)
				pipeCollection[i].repair = repairStatus;
			Console::PrintTitleText("\n����� ���������������!");
		}
		else
			Console::PrintErrorText("\n�� ������ ������� �� ���� ������� �� ����� �����!");
		vectorIdForFilter.clear();
	}
	else
	{
		PrintTablePipes();
		repairStatus = verification::GetBoolValue("\n\n������� ����� ��������� ��� ��������� ����, ���� � �������, �� ������� \"y\" �� ����������, ���� �� ���, �������� �� \"n\": ",
			"\n����������� �������! ��������� ���� �� ��������� ���� ��������, �������� �� \"y\", ���� ��, �� \"n\", ���� ���!!!");
		for (auto& el : pipeCollection)
			el.second.repair = repairStatus;
		Console::PrintTitleText("\n����� ���������������!");
	}
	system("pause");
}