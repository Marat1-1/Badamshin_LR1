#include "PipeCollection.h"
#include "Verification_Class.h"
#include <iomanip>

// ���������� ����� � ������
void PipeCollection::AddPipe(Console& console)
{
	VerificationClass<double> verification;
	Pipe pipe;
	pipe.id = Pipe::countPipes;

	pipe.length = verification.GetNumericValue("������� ����� �����, ����������� - ���������, �������� �� 10 �� 100 �� (������������� ����� �����, ����� �������� ������� ����� ����������� \".\"): ",
		"������!!! �� ����� ���-�� ����������.\n����� ����� ����� ���� ���� ����� ������, ���� ������ � ��������� ������, ������� � ��������� �� 10 �� 100 ��, ��������� ����!!!", 10.0, 100.0, console);

	pipe.diameter = verification.GetNumericValue("������� ������� �����, ����������� ����������, �������� �� 500 �� 1420 �� (������������� ����� �����, ����� �������� ������� ����� ����������� \".\"): ",
		"������!!! �� ����� ���-�� ����������.\n������� ����� ����� ���� ���� ����� ������, ���� ������ � ��������� ������, ������� � ��������� �� 500 �� 1420 ��, ��������� ����!!!", 500.0, 1420.0, console);

	pipe.repair = verification.GetBoolValue("������� ��������� �� ����� � �������, ���� ��, �� ������� \"y\" �� ����������, ���� �� ���, �������� �� \"n\": ",
		"\n����������� �������! ��������� ���� �� ��������� ���� ��������, �������� �� \"y\", ���� ��, �� \"n\", ���� ���: ", console);
	vectorPipes.push_back(pipe);
}

// �������������� �����
void PipeCollection::ChangePipe(Console& console)
{
	VerificationClass<size_t> verification;
	size_t localId;
	bool query;
	std::cout << "����� ��������� ����: " << Pipe::countPipes << std::endl;
	if (Pipe::countPipes == 0)
	{
		console.PrintErrorText("�� �� �������� �� ����� �����, �������������� ����������!");
		verification.GetPressEscape("\n\n����� ����� � ����, ������� ESC: ", "\n������� �� ����������, ������� ESC �� ����������, ���� ������ ��������� � ����!", console);
		return;
	}
	while (true)
	{
		localId = verification.GetNumericValue("\n������� ����� (id) �����, ������� �� �� ������ ������������� (id �� ������ ��������� ����� ���������� ����): ",
			"�� ����� ������������ ��������, id ����� �� ������ ��������� ����� ���������� ����, � ����� �� �������� ����������� ������!!!", 1, Pipe::countPipes, console);
		std::cout << "����������� ��������� �����: "
			<< (vectorPipes[localId - 1].repair ? "� �������" : "�� � �������")
			<< std::endl;

		vectorPipes[localId - 1].repair = verification.GetBoolValue("������� ����� ��������� ��� �����, ���� ��� � �������, �� ������� \"y\" �� ����������, ���� �� ���, �������� �� \"n\": ",
			"\n����������� �������! ��������� ���� �� ��������� ���� ��������, �������� �� \"y\", ���� ��, �� \"n\", ���� ���: ", console);
		query = verification.GetBoolValue("\n\n������ �� �� ���������� ������������� �����, ���� ��, �� �������� \"y\", ���� �� ���, �� ������� �� \"n\": ",
			"\n����������� �������! ��������� ���� �� ��������� ���� ��������, �������� �� \"y\", ���� ��, �� \"n\", ���� ���: ", console);
		if (!query)
			break;
	}
}

// ����� ������� ���� �� �����
void PipeCollection::PrintTablePipes(Console& console)
{
	int tabulation_20 = 20, tabulation_30 = 30, tableWidth = 131;
	console.PrintChar('-', tableWidth);
	std::cout << "|" << std::setw(tabulation_20) << "ID" << std::setw(tabulation_30) << "LENGTH" << std::setw(tabulation_30) << "DIAMETER" << std::setw(tabulation_30) << "REPAIR" << std::setw(tabulation_20) << "|" << std::endl;
	console.PrintChar('-', tableWidth);
	for (const auto& p : vectorPipes)
	{
		std::cout << "|" << std::setw(tabulation_20) << p.id << std::setw(tabulation_30) << p.length << std::setw(tabulation_30) << p.diameter << std::setw(tabulation_30) << (p.repair == true ? "true" : "false") << std::setw(tabulation_20) << "|" << std::endl;
	}
	console.PrintChar('-', tableWidth);
}

// ����� ���� � ����
void PipeCollection::SaveToFile(std::ofstream& fout, Console& console)
{
	size_t percent = 0;
	if (fout.is_open())
	{
		for (const auto& v : vectorPipes)
		{
			fout << v.length << std::endl
				<< v.diameter << std::endl
				<< v.repair << std::endl;
		}
		while (percent <= 100)
		{
			std::cout << "\t\t" << "���������� ����: " << percent++ << "%";
			std::cout << '\r';
			Sleep(20);
		}
		console.PrintTitleText("\n\t\t����� ���������!");
	}
	else
	{
		console.PrintErrorText("\n������!!! ���� �� ���������� ���� �� ������, ���� �� �� ����������!");
		Sleep(3000);
	}
}

// �������� ���� �� �����
void PipeCollection::DownloadFromFile(std::ifstream& fin, Console& console)
{
	size_t percent = 0;
	if (fin.is_open())
	{
		if (fin.peek() != -1)
		{
			while (fin.peek() != ' ' && fin.peek() != -1)
			{
				Pipe newPipe;
				newPipe.id = Pipe::countPipes;
				fin >> newPipe.length
					>> newPipe.diameter
					>> newPipe.repair;
				vectorPipes.push_back(newPipe);
				fin.ignore(1000, '\n');
			}
			while (percent <= 100)
			{
				std::cout << "\t\t" << "�������� ����: " << percent++ << "%";
				std::cout << '\r';
				Sleep(20);
			}
			console.PrintTitleText("\n����� ���������!");
		}
		else
		{
			console.PrintErrorText("\n������ ��������� ������ �� ������� �����, ������� ����� ��������� ��� ������!!!");
			Sleep(3000);
		}
	}
	else
	{
		console.PrintErrorText("\n������!!! ���� �� ���������� ���� �� ������, ���� �� �� ����������!");
		Sleep(3000);
	}
}


// �������� �����
void PipeCollection::DeletePipe(Console& console)
{
	VerificationClass<size_t> verification;
	size_t delId; // id ������, ������� ����� �������
	const size_t& id = delId; // ����������� ������ �� id, ����� �������� � ����������
	bool query;
	std::vector<Pipe>::iterator it = vectorPipes.begin();
	if (Pipe::countPipes == 0)
	{
		console.PrintErrorText("�� �� �������� �� ����� �����, �������� ����������!");
		verification.GetPressEscape("\n\n����� ����� � ����, ������� ESC: ", "\n������� �� ����������, ������� ESC �� ����������, ���� ������ ��������� � ����!", console);
		return;
	}
	while (true)
	{
		std::cout << "\n\n����� ����: " << Pipe::countPipes << std::endl;
		delId = verification.GetNumericValue("������� id �����, ������� �� �� ������ ������� (id �� ������ ��������� ����� ���������� ����): ",
			"�� ����� ������������ ��������, id ����� �� ������ ��������� ����� ���������� ����, � ����� id ��� ����������� �����!!!", 1, Pipe::countPipes, console);
		it += id - 1;
		Pipe::countPipes--;
		for (auto iter = vectorPipes.erase(it); iter != vectorPipes.end(); iter++)
		{
			(*iter).id--;
		}
		console.PrintTitleText("����� ���� ������� �������!");
		query = verification.GetBoolValue("\n\n������ �� �� ���������� ������� �����, ���� ��, �� �������� \"y\", ���� �� ���, �� ������� �� \"n\": ",
			"\n����������� �������! ��������� ���� �� ��������� ���� ��������, �������� �� \"y\", ���� ��, �� \"n\", ���� ���: ", console);
		if (!query)
			break;
	}
}