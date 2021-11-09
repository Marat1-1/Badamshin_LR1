#include "CompressorStationCollection.h"
#include "Verification.h"
#include <iomanip>

// ���������� ������������� ������� � ������
void CompressorStationCollection::AddCS()
{
	CompressorStation compressorStation;
	csCollection.emplace(compressorStation.id, compressorStation);
}


// �������������� ������������� �������
void CompressorStationCollection::ChangeCS()
{
	size_t changeId;
	bool query;
	std::cout << "����� ��������� ������������� �������: " << size(csCollection) << std::endl
		<< "Id ��������� ��� ��������������: ";
	for (const auto& el : csCollection)
		std::cout << el.first << "  ";
	std::cout << std::endl;
	if (csCollection.empty())
	{
		Console::PrintErrorText("�� �� �������� �� ����� ������������� �������, �������������� ����������!");
		verification::GetPressEscape("\n\n����� ����� � ����, ������� ESC: ", "\n������� �� ����������, ������� ESC �� ����������, ���� ������ ��������� � ����!");
		return;
	}
	while (true)
	{
		changeId = verification::GetNumericValue<size_t>("\n������� ����� (id) ������������� �������, ������� �� �� ������ �������������: ",
			"������! �� ����� ������������ ��������, �������� �� ����� �������������� id ��� �� ��������� ������������ ����, ������� id ��� �������������, ����� �����!!!",
			1, CompressorStation::countCSCreated);
		if (csCollection.find(changeId) != csCollection.end())
		{
			std::cout << "���������� ����� � ������ ������������� �������: " << csCollection[changeId].countWorkShops << std::endl;
			std::cout << "���������� ����� � ������ � ������ ������������� �������: " << csCollection[changeId].countWorkShopsInOperation << std::endl;
			csCollection[changeId].ChangeCS();
		}
		query = verification::GetBoolValue("\n\n������ �� �� ���������� ������������� ������������ �������, ���� ��, �� �������� \"y\", ���� �� ���, �� ������� �� \"n\": ",
			"\n����������� �������! ��������� ���� �� ��������� ���� ��������, �������� �� \"y\", ���� ��, �� \"n\", ���� ���!!!");
		if (query != true)
			break;
	}
}


// ����� ������� ������������� ������� �� �����
void CompressorStationCollection::PrintTableCS()
{
	int tabulation_20 = 20, tabulation_30 = 30, tableWidth = 172;
	Console::PrintTitleText("\n\t\t\t\t������� ��");
	Console::PrintChar('-', tableWidth);
	std::cout << "|" << std::setw(tabulation_20) << "ID" << std::setw(tabulation_30 + 1) << "NAME" << std::setw(tabulation_30) << "CountWorkShops" << std::setw(tabulation_30 + 10) << "CountWorkShopsInOperation" << std::setw(tabulation_30) << "EFFECTIVENESS" << std::setw(tabulation_20) << "|" << std::endl;
	Console::PrintChar('-', tableWidth);
	for (const auto& cs : csCollection)
	{
		std::cout << "|" << std::setw(tabulation_20) << cs.second.id << std::setw(tabulation_30 + 1) << cs.second.name << std::setw(tabulation_30) << cs.second.countWorkShops << std::setw(tabulation_30 + 10) << cs.second.countWorkShopsInOperation << std::setw(tabulation_30) << cs.second.effectiveness << std::setw(tabulation_20) << "|" << std::endl;
	}
	Console::PrintChar('-', tableWidth);
}

// ����� ������� ������������� ������� �� �����, ��� ���� ������� ����� ����� ������ ��
void CompressorStationCollection::PrintFilterTableCS()
{
	int tabulation_20 = 20, tabulation_30 = 30, tableWidth = 172;
	Console::PrintTitleText("\n\t\t\t\t������� ��");
	Console::PrintChar('-', tableWidth);
	std::cout << "|" << std::setw(tabulation_20) << "ID" << std::setw(tabulation_30 + 1) << "NAME" << std::setw(tabulation_30) << "CountWorkShops" << std::setw(tabulation_30 + 10) << "CountWorkShopsInOperation" << std::setw(tabulation_30) << "EFFECTIVENESS" << std::setw(tabulation_20) << "|" << std::endl;
	Console::PrintChar('-', tableWidth);
	for (const auto& id : vectorIdForFilter)
	{
		std::cout << "|" << std::setw(tabulation_20) << csCollection[id].id << std::setw(tabulation_30 + 1) << csCollection[id].name << std::setw(tabulation_30) << csCollection[id].countWorkShops << std::setw(tabulation_30 + 10) << csCollection[id].countWorkShopsInOperation << std::setw(tabulation_30) << csCollection[id].effectiveness << std::setw(tabulation_20) << "|" << std::endl;
	}
	Console::PrintChar('-', tableWidth);
}

// ����� ������������� ������� � ����
void CompressorStationCollection::SaveToFile(std::ofstream& fout)
{
	size_t percent = 0;
	if (csCollection.empty())
	{
		Console::PrintErrorText("�� �� �������� �� ����� ������������� �������!");
		return;
	}
	if (fout.is_open())
	{
		for (auto& el : csCollection)
			el.second.SaveToFile(fout);
		while (percent <= 100)
		{
			std::cout << "\t\t" << "���������� ��: " << percent++ << "%";
			std::cout << '\r';
			Sleep(20);
		}
		Console::PrintTitleText("\n\t\t�� ���������!");
	}
	else
	{
		Console::PrintErrorText("\n������!!! ���� �� ���������� ���� �� ������, ���� �� �� ����������!");
	}
}

// �������� �� �� �����
void CompressorStationCollection::DownloadFromFile(std::ifstream& fin)
{
	size_t percent = 0;
	if (fin.is_open())
	{
		if (fin.peek() != -1)
		{
			while (fin.peek() != ' ' && fin.peek() != -1)
			{
				CompressorStation compressorStation(fin);
				csCollection.emplace(compressorStation.id, compressorStation);
				fin.ignore(1000, '\n');
			}
			while (percent <= 100)
			{
				std::cout << "\t\t" << "�������� ��: " << percent++ << "%";
				std::cout << '\r';
				Sleep(20);
			}
			Console::PrintTitleText("\n�� ���������!");
		}
		else
		{
			Console::PrintErrorText("\n������ ��������� ������ �� ������� �����, ������� ����� ��������� ��� ������!!!");
		}
	}
	else
	{
		Console::PrintErrorText("\n������!!! ���� �� ���������� ���� �� ������, ���� �� �� ����������!");
	}
}

// ������ ��
void CompressorStationCollection::FilterCS()
{
	char command;
	std::cout << "\n\n�������� ����� ���� ��� ����������:" << std::endl
		<< "1. ������������� �� ��������" << std::endl
		<< "2. ������������� �� �������� ����������������� �����" << std::endl
		<< "3. ��������� ��� �������" << std::endl;
	while (true)
	{
		std::cout << "\n������� �������: ";
		command = _getch();
		switch (command)
		{
		case '1':
		{
			std::string nameCS;
			nameCS = verification::GetStringValue("\n������� �������� ��, �� �������� �� ������ ������������� ������ (����� �� ������ 30 ��������): ",
				"������!!! �������� �� ����� �������� ������ �� �������� ��� ������ ������ � ����� ����� ������ ��� 30 ��������!!!", 30);
			for (const auto& el : csCollection)
				if (el.second.name == nameCS)
					vectorIdForFilter.push_back(el.first);
			return;
		}
		case '2':
		{
			size_t lowPercent, upPercent, percent;
			lowPercent = verification::GetNumericValue<size_t>("\n������� ������ ������� ������� �������� ���������������� ����� � �� (����� ����� �� 0 �� 100): ",
				"������!!! �� ����������� ������������ ����, ��������� ��� �� ���� ��������� ��������.", 0, 100);
			upPercent = verification::GetNumericValue<size_t>("\n������� ������� ������� ������� �������� ���������������� ����� � �� (����� ����� �� ������ ������� �� 100): ",
				"������!!! �� ����������� ������������ ����, ��������� ��� �� ���� ��������� ��������.", lowPercent, 100);
			for (const auto& el : csCollection)
			{
				percent = static_cast<size_t>(round((static_cast<double>(el.second.countWorkShops) - el.second.countWorkShopsInOperation) / el.second.countWorkShops * 100));
				if (percent >= lowPercent && percent <= upPercent)
					vectorIdForFilter.push_back(el.first);
			}
			return;
		}
		case '3':
		{
			std::string nameCS;
			size_t lowPercent, upPercent, percent;
			nameCS = verification::GetStringValue("\n������� �������� ��, �� �������� �� ������ ������������� ������ (����� �� ������ 30 ��������): ",
				"������!!! �������� �� ����� �������� ������ �� �������� ��� ������ ������ � ����� ����� ������ ��� 30 ��������!!!", 30);
			lowPercent = verification::GetNumericValue<size_t>("\n������� ������ ������� ������� �������� ���������������� ����� � �� (����� ����� �� 0 �� 100): ",
				"������!!! �� ����������� ������������ ����, ��������� ��� �� ���� ��������� ��������.", 0, 100);
			upPercent = verification::GetNumericValue<size_t>("\n������� ������� ������� ������� �������� ���������������� ����� � �� (����� ����� �� ������ ������� �� 100): ",
				"������!!! �� ����������� ������������ ����, ��������� ��� �� ���� ��������� ��������.", lowPercent, 100);
			for (const auto& el : csCollection)
			{
				percent = static_cast<size_t>(round((static_cast<double>(el.second.countWorkShops) - el.second.countWorkShopsInOperation) / el.second.countWorkShops * 100));
				if (el.second.name == nameCS && percent >= lowPercent && percent <= upPercent)
					vectorIdForFilter.push_back(el.first);
			}
			return;
		}
		default:
		{
			Console::PrintErrorText("\n����� ������� ���� � ������, ���������� ����, ��������� ����!!!\n");
			break;
		}
		}
	}
}

// �������� ��
void CompressorStationCollection::DeleteCS()
{
	size_t delId; // id ��, ������� ����� �������
	bool query;
	if (csCollection.empty())
	{
		Console::PrintErrorText("�� �� �������� �� ���� ��, �������� ����������!");
		verification::GetPressEscape("\n\n����� ����� � ����, ������� ESC: ", "\n������� �� ����������, ������� ESC �� ����������, ���� ������ ��������� � ����!");
		return;
	}
	query = verification::GetBoolValue("\n������� �� \"y\", ���� ������ ���������� �������� �� ����� ��, �� \"n\", ���� ������ ���������� �������� �������� �� �������: ",
		"\n����������� �������! ��������� ���� �� ��������� ��������!!!");
	if (query)
	{
		while (true)
		{
			std::cout << "\n\n����� ��: " << size(csCollection) << std::endl
				<< "Id ��������� ��� ��������: ";
			for (const auto& el : csCollection)
				std::cout << el.first << "  ";
			std::cout << std::endl;
			delId = verification::GetNumericValue<size_t>("������� id ��, ������� �� �� ������ �������: ",
				"������! �� ����� ������������ ��������, �������� �� ����� �������������� id ��� �� ��������� ������������ ����, ������� id ��� �������������, ����� �����!!!", 1, CompressorStation::countCSCreated);
			if (csCollection.find(delId) != csCollection.end())
			{
				csCollection.erase(delId);
				Console::PrintTitleText("�� ���� ������� �������!");
			}
			else
				Console::PrintErrorText("�� ���������� id �� ���� ������� �� ����� ��, �������� �� ��� ���� �������!!!");
			query = verification::GetBoolValue("\n\n������ �� �� ���������� ������� ��, ���� ��, �� �������� \"y\", ���� �� ���, �� ������� �� \"n\": ",
				"\n����������� �������! ��������� ���� �� ��������� ���� ��������, �������� �� \"y\", ���� ��, �� \"n\", ���� ���!!!");
			if (!query)
				break;
		}
	}
	else
	{
		FilterCS();
		if (size(vectorIdForFilter) != 0)
		{
			std::cout << "\n\n����� ������� ��������� ��:" << std::endl;
			PrintFilterTableCS();
			for (const auto i : vectorIdForFilter)
				csCollection.erase(i);
			vectorIdForFilter.clear();
			Console::PrintTitleText("\n\n�� ������� �������!");
		}
		else
			Console::PrintErrorText("\n�� ������ ������� �� ���� ������� �� ����� ��!");
	}
	std::cout << std::endl;
	system("pause");
}

// �������� �������������� ��
void CompressorStationCollection::BatchChangeCS()
{
	bool query;
	if (csCollection.empty())
	{
		Console::PrintErrorText("\n�� �� �������� �� ����� ��, �������� �������������� ����������!");
		verification::GetPressEscape("\n\n����� ����� � ����, ������� ESC: ", "\n������� �� ����������, ������� ESC �� ����������, ���� ������ ��������� � ����!");
		return;
	}
	query = verification::GetBoolValue("\n������� �� \"y\", ���� ������ ������������� ��� ��, �� \"n\", ���� ������ ����������� ������������: ",
		"\n������!!! �� ������ �� ������������ ������, ����������� ���� �� ��������� ��� ��������!!!");
	if (!query)
	{
		FilterCS();
		if (size(vectorIdForFilter) != 0)
		{
			PrintFilterTableCS();
			for (const auto& i : vectorIdForFilter)
			{
				std::cout << "\n\n������������� ������� ��� id " << csCollection[i].id << " ����� ����� ���������� �����: " << csCollection[i].countWorkShops << std::endl
					<< "���������� ����� � ������: " << csCollection[i].countWorkShopsInOperation << std::endl;
				csCollection[i].countWorkShopsInOperation = verification::GetNumericValue<size_t>("������� ����� ���������� ����� � ������ ��� ������ �� (��� �� ������ ��������� ����� ���������� �����): ",
					"������!!! ���������� ����� ��� ����� �����, ��� ����������� ��������, ����� ����, �����, � ����� ����� �� ������ ��������� ����� ���������� �����.", 0, csCollection[i].countWorkShops);
			}
			Console::PrintTitleText("\n\n�� ���������������!");
		}
		else
			Console::PrintErrorText("\n�� ������ ������� �� ���� ������� �� ����� �����!");
	}
	else
	{
		PrintTableCS();
		for (auto& el : csCollection)
		{
			std::cout << "\n\n������������� ������� ��� id " << el.first << " ����� ����� ���������� �����: " << el.second.countWorkShops << std::endl
				<< "���������� ����� � ������: " << el.second.countWorkShopsInOperation << std::endl;
			el.second.countWorkShopsInOperation = verification::GetNumericValue<size_t>("������� ����� ���������� ����� � ������ ��� ������ �� (��� �� ������ ��������� ����� ���������� �����): ",
				"������!!! ���������� ����� ��� ����� �����, ��� ����������� ��������, ����� ����, �����, � ����� ����� �� ������ ��������� ����� ���������� �����.", 0, el.second.countWorkShops);
		}
		Console::PrintTitleText("\n\n�� ���������������!");
	}
	vectorIdForFilter.clear();
	system("pause");
}