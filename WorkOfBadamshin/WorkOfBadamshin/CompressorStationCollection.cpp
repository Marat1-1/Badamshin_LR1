#include "CompressorStationCollection.h"
#include "Verification_Class.h"
#include <iomanip>



// ���������� ������������� ������� � ������
void CompressorStationCollection::AddCS(Console& console)
{
	VerificationClass<size_t> verification;
	CompressorStation compressorStation;
	compressorStation.id = CompressorStation::countCS;
	compressorStation.name = verification.GetStringValue("������� �������� �� (����� �� ������ 30 ��������): ",
		"������!!! �������� �� ����� �������� ������ �� �������� ��� ������ ������ � ����� ����� ������ ��� 30 ��������!!!", 30, console);

	compressorStation.countWorkShops = verification.GetNumericValue("������� ���������� ����� �� (�� ������ 20): ",
		"������!!! ���������� ����� ��� ����� �����, ��� ����������� ��������, � ���� ����, ����� � ����� ����� ������ ���� ������ 20.", 0, 20, console);

	compressorStation.countWorkShopsInOperation = verification.GetNumericValue("������� ���������� ����� � ������ (��� �� ������ ��������� ����� ���������� �����): ",
		"������!!! ���������� ����� ��� ����� �����, ��� ����������� ��������, ����� ����, �����, � ����� ����� �� ������ ��������� ����� ���������� �����.", 0, compressorStation.countWorkShops, console);

	compressorStation.effectiveness = verification.GetNumericValue("������� �������� ������������� �� (��� ���������� � ���������, ������� ������� ����� �� 0 �� 100%): ",
			"������!!! �� ����� ���-�� ����������.\n������������� �� ����� ���� ����� ������ ������� � �������� �� 0 �� 100.\n��������� ����!!!", 0, 100, console);
	
	vectorCS.push_back(compressorStation);
}


// �������������� ������������� �������
void CompressorStationCollection::ChangeCS(Console& console)
{
	VerificationClass<size_t> verification;
	std::cout << "����� ��������� ������������� �������: " << CompressorStation::countCS << std::endl;
	if (CompressorStation::countCS == 0)
	{
		console.PrintErrorText("�� �� �������� �� ����� ������������� �������, �������������� ����������!");
		verification.GetPressEscape("\n\n����� ����� � ����, ������� ESC: ", "\n������� �� ����������, ������� ESC �� ����������, ���� ������ ��������� � ����!", console);
		return;
	}
	while (true)
	{
		size_t localId = verification.GetNumericValue("\n������� ����� (id) ������������� �������, ������� �� �� ������ ������������� (id �� ������ ��������� ����� ���������� ������������� �������): ",
			"�� ����� ������������ ��������, id ����� �� ������ ��������� ����� ���������� ������������� �������, � ����� �� �������� ����������� ������!!!",
			1, CompressorStation::countCS, console);
		std::cout << "���������� ����� � ������ ������������� �������: " << vectorCS[localId - 1].countWorkShops << std::endl;
		std::cout << "���������� ����� � ������ � ������ ������������� �������: " << vectorCS[localId - 1].countWorkShopsInOperation << std::endl;
		vectorCS[localId - 1].countWorkShopsInOperation = verification.GetNumericValue("������� ����� ���������� ����� � ������ (��� �� ������ ��������� ����� ���������� �����): ",
			"������!!! ���������� ����� ��� ����� �����, ��� ����������� ��������, ����� ����, �����, � ����� ����� �� ������ ��������� ����� ���������� �����.",
			0, vectorCS[localId - 1].countWorkShops, console);
		bool query = verification.GetBoolValue("\n\n������ �� �� ���������� ������������� ������������ �������, ���� ��, �� �������� \"y\", ���� �� ���, �� ������� �� \"n\": ",
			"\n����������� �������! ��������� ���� �� ��������� ���� ��������, �������� �� \"y\", ���� ��, �� \"n\", ���� ���!!!", console);
		if (query != true)
			break;
	}
}


// ����� ������� ������������� ������� �� �����
void CompressorStationCollection::PrintTableCS(Console& console)
{
	int tabulation_20 = 20, tabulation_30 = 30, tableWidth = 172;
	console.PrintChar('-', tableWidth);
	std::cout << "|" << std::setw(tabulation_20) << "ID" << std::setw(tabulation_30 + 1) << "NAME" << std::setw(tabulation_30) << "CountWorkShops" << std::setw(tabulation_30 + 10) << "CountWorkShopsInOperation" << std::setw(tabulation_30) << "EFFECTIVENESS" << std::setw(tabulation_20) << "|" << std::endl;
	console.PrintChar('-', tableWidth);
	for (const auto& cs : vectorCS)
	{
		std::cout << "|" << std::setw(tabulation_20) << cs.id << std::setw(tabulation_30 + 1) << cs.name << std::setw(tabulation_30) << cs.countWorkShops << std::setw(tabulation_30 + 10) << cs.countWorkShopsInOperation << std::setw(tabulation_30) << cs.effectiveness << std::setw(tabulation_20) << "|" << std::endl;
	}
	console.PrintChar('-', tableWidth);
}

// ����� ������� ������������� ������� �� �����, ��� ���� ������� ����� ����� ������ ��
void CompressorStationCollection::PrintFilterTableCS(Console& console)
{
	int tabulation_20 = 20, tabulation_30 = 30, tableWidth = 172;
	console.PrintTitleText("\n\t\t\t\t������� ��");
	console.PrintChar('-', tableWidth);
	std::cout << "|" << std::setw(tabulation_20) << "ID" << std::setw(tabulation_30 + 1) << "NAME" << std::setw(tabulation_30) << "CountWorkShops" << std::setw(tabulation_30 + 10) << "CountWorkShopsInOperation" << std::setw(tabulation_30) << "EFFECTIVENESS" << std::setw(tabulation_20) << "|" << std::endl;
	console.PrintChar('-', tableWidth);
	for (const auto& id : vectorIdForFilter)
	{
		std::cout << "|" << std::setw(tabulation_20) << vectorCS[id - 1].id << std::setw(tabulation_30 + 1) << vectorCS[id - 1].name << std::setw(tabulation_30) << vectorCS[id - 1].countWorkShops << std::setw(tabulation_30 + 10) << vectorCS[id - 1].countWorkShopsInOperation << std::setw(tabulation_30) << vectorCS[id - 1].effectiveness << std::setw(tabulation_20) << "|" << std::endl;
	}
	console.PrintChar('-', tableWidth);
}

// ����� ������������� ������� � ����
void CompressorStationCollection::SaveToFile(std::ofstream& fout, Console& console)
{
	size_t percent = 0;
	if (fout.is_open())
	{
		for (const auto& v : vectorCS)
		{
			fout << v.name << std::endl
				<< v.countWorkShops << std::endl
				<< v.countWorkShopsInOperation << std::endl
				<< v.effectiveness << std::endl;
		}
		while (percent <= 100)
		{
			std::cout << "\t\t" << "���������� ��: " << percent++ << "%";
			std::cout << '\r';
			Sleep(20);
		}
		console.PrintTitleText("\n\t\t�� ���������!");
	}
	else
	{
		console.PrintErrorText("\n������!!! ���� �� ���������� ���� �� ������, ���� �� �� ����������!");
	}
}

// �������� �� �� �����
void CompressorStationCollection::DownloadFromFile(std::ifstream& fin, Console& console)
{
	size_t percent = 0;
	if (fin.is_open())
	{
		if (fin.peek() != -1)
		{
			while (fin.peek() != ' ' && fin.peek() != -1)
			{
				CompressorStation newCS;
				newCS.id = CompressorStation::countCS;
				getline(fin, newCS.name);
				fin >> newCS.countWorkShops
					>> newCS.countWorkShopsInOperation
					>> newCS.effectiveness;
				vectorCS.push_back(newCS);
				fin.ignore(1000, '\n');
			}
			while (percent <= 100)
			{
				std::cout << "\t\t" << "�������� ��: " << percent++ << "%";
				std::cout << '\r';
				Sleep(20);
			}
			console.PrintTitleText("\n�� ���������!");
		}
		else
		{
			console.PrintErrorText("\n������ ��������� ������ �� ������� �����, ������� ����� ��������� ��� ������!!!");
		}
	}
	else
	{
		console.PrintErrorText("\n������!!! ���� �� ���������� ���� �� ������, ���� �� �� ����������!");
	}
}


// �������� ��
void CompressorStationCollection::DeleteCS(Console& console)
{
	VerificationClass<size_t> verification;
	size_t delId; // id ��, ������� ����� �������
	const size_t& id = delId; // ����������� ������ �� id, ����� �������� � ����������
	bool query;
	std::vector<CompressorStation>::iterator it = vectorCS.begin();
	if (CompressorStation::countCS == 0)
	{
		console.PrintErrorText("�� �� �������� �� ���� ��, �������� ����������!");
		verification.GetPressEscape("\n\n����� ����� � ����, ������� ESC: ", "\n������� �� ����������, ������� ESC �� ����������, ���� ������ ��������� � ����!", console);
		return;
	}
	while (true)
	{
		std::cout << "\n\n����� ����: " << CompressorStation::countCS << std::endl;
		delId = verification.GetNumericValue("������� id ��, ������� �� �� ������ ������� (id �� ������ ��������� ����� ���������� ��): ",
			"�� ����� ������������ ��������, id �� �� ������ ��������� ����� ���������� ��, � ����� id ��� ����������� �����!!!", 1, CompressorStation::countCS, console);
		it += id - 1;
		CompressorStation::countCS--;
		for (auto iter = vectorCS.erase(it); iter != vectorCS.end(); iter++)
		{
			(*iter).id--;
		}
		console.PrintTitleText("�� ���� ������� �������!");
		query = verification.GetBoolValue("\n\n������ �� �� ���������� ������� ��, ���� ��, �� �������� \"y\", ���� �� ���, �� ������� �� \"n\": ",
			"\n����������� �������! ��������� ���� �� ��������� ���� ��������, �������� �� \"y\", ���� ��, �� \"n\", ���� ���!!!", console);
		if (!query)
			break;
	}
}

// ������ ��
void CompressorStationCollection::FilterCS(Console& console)
{
	VerificationClass<size_t> verification;
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
			nameCS = verification.GetStringValue("\n������� �������� ��, �� �������� �� ������ ������������� ������ (����� �� ������ 30 ��������): ",
				"������!!! �������� �� ����� �������� ������ �� �������� ��� ������ ������ � ����� ����� ������ ��� 30 ��������!!!", 30, console);
			for (const auto& v : vectorCS)
				if (v.name == nameCS)
					vectorIdForFilter.push_back(v.id);
			return;
		}
		case '2':
		{
			size_t lowPercent, upPercent, percent;
			lowPercent = verification.GetNumericValue("\n������� ������ ������� ������� �������� ���������������� ����� � �� (����� ����� �� 0 �� 100): ",
				"������!!! �� ����������� ������������ ����, ��������� ��� �� ���� ��������� ��������.", 0, 100, console);
			upPercent = verification.GetNumericValue("\n������� ������� ������� ������� �������� ���������������� ����� � �� (����� ����� �� ������ ������� �� 100): ",
				"������!!! �� ����������� ������������ ����, ��������� ��� �� ���� ��������� ��������.", lowPercent, 100, console);
			for (const auto& v : vectorCS)
			{
				percent = static_cast<size_t>(round((static_cast<double>(v.countWorkShops) - v.countWorkShopsInOperation) / v.countWorkShops * 100));
				if (percent >= lowPercent && percent <= upPercent)
					vectorIdForFilter.push_back(v.id);
			}
			return;
		}
		case '3':
		{
			std::string nameCS;
			size_t lowPercent, upPercent, percent;
			nameCS = verification.GetStringValue("\n������� �������� ��, �� �������� �� ������ ������������� ������ (����� �� ������ 30 ��������): ",
				"������!!! �������� �� ����� �������� ������ �� �������� ��� ������ ������ � ����� ����� ������ ��� 30 ��������!!!", 30, console);
			lowPercent = verification.GetNumericValue("\n������� ������ ������� ������� �������� ���������������� ����� � �� (����� ����� �� 0 �� 100): ",
				"������!!! �� ����������� ������������ ����, ��������� ��� �� ���� ��������� ��������.", 0, 100, console);
			upPercent = verification.GetNumericValue("\n������� ������� ������� ������� �������� ���������������� ����� � �� (����� ����� �� ������ ������� �� 100): ",
				"������!!! �� ����������� ������������ ����, ��������� ��� �� ���� ��������� ��������.", lowPercent, 100, console);
			for (const auto& v : vectorCS)
			{
				percent = static_cast<size_t>(round((static_cast<double>(v.countWorkShops) - v.countWorkShopsInOperation) / v.countWorkShops * 100));
				if (v.name == nameCS && percent >= lowPercent && percent <= upPercent)
					vectorIdForFilter.push_back(v.id);
			}
			return;
		}
		default:
		{
			console.PrintErrorText("\n����� ������� ���� � ������, ���������� ����, ��������� ����!!!\n");
			break;
		}
		}
	}
}

// �������� �������������� ��
void CompressorStationCollection::BatchChangeCS(Console& console)
{
	VerificationClass<size_t> verification;
	bool query;
	if (CompressorStation::countCS == 0)
	{
		console.PrintErrorText("\n�� �� �������� �� ����� ��, �������� �������������� ����������!");
		verification.GetPressEscape("\n\n����� ����� � ����, ������� ESC: ", "\n������� �� ����������, ������� ESC �� ����������, ���� ������ ��������� � ����!", console);
		return;
	}
	query = verification.GetBoolValue("\n������� �� \"y\", ���� ������ ������������� ��� ��, �� \"n\", ���� ������ ����������� ������������: ",
		"\n������!!! �� ������ �� ������������ ������, ����������� ���� �� ��������� ��� ��������!!!", console);
	if (!query)
	{
		FilterCS(console);
		if (size(vectorIdForFilter) != 0)
		{
			PrintFilterTableCS(console);
			for (const auto& p : vectorIdForFilter)
			{
				std::cout << "\n\n������������� ������� ��� id " << p << " ����� ����� ���������� �����: " << vectorCS[p - 1].countWorkShops << std::endl
					<< "���������� ����� � ������: " << vectorCS[p - 1].countWorkShopsInOperation << std::endl;
				vectorCS[p-1].countWorkShopsInOperation = verification.GetNumericValue("������� ����� ���������� ����� � ������ ��� ������ �� (��� �� ������ ��������� ����� ���������� �����): ",
					"������!!! ���������� ����� ��� ����� �����, ��� ����������� ��������, ����� ����, �����, � ����� ����� �� ������ ��������� ����� ���������� �����.", 0, vectorCS[p-1].countWorkShops, console);
			}
			console.PrintTitleText("\n\n�� ���������������!");
		}
		else
			console.PrintErrorText("\n�� ������ ������� �� ���� ������� �� ����� �����!");
	}
	else
	{
		for (auto& v : vectorCS)
		{
			std::cout << "\n\n������������� ������� ��� id " << v.id << " ����� ����� ���������� �����: " << v.countWorkShops << std::endl
				<< "���������� ����� � ������: " << v.countWorkShopsInOperation << std::endl;
			v.countWorkShopsInOperation = verification.GetNumericValue("������� ����� ���������� ����� � ������ ��� ������ �� (��� �� ������ ��������� ����� ���������� �����): ",
				"������!!! ���������� ����� ��� ����� �����, ��� ����������� ��������, ����� ����, �����, � ����� ����� �� ������ ��������� ����� ���������� �����.", 0, v.countWorkShops, console);
		}
		console.PrintTitleText("\n\n�� ���������������!");
	}
	vectorIdForFilter.clear();
	system("pause");
}