#include "ClassElements.h"
#include "Verification.h"
#include <iomanip>


// ������������� �����
Pipe::Pipe()
{
	maxIdPipe++;
	this->id = maxIdPipe;
	this->length = verification::GetNumericValue<double>("������� ����� �����, ����������� - ���������, �������� �� 10 �� 100 �� (������������� ����� �����, ����� �������� ������� ����� ����������� \".\"): ",
		"������!!! �� ����� ���-�� ����������.\n����� ����� ����� ���� ���� ����� ������, ���� ������ � ��������� ������, ������� � ��������� �� 10 �� 100 ��, ��������� ����!!!", 10.0, 100.0);

	this->diameter = verification::GetNumericValue<double>("������� ������� �����, ����������� ����������, �������� �� 500 �� 1420 �� (������������� ����� �����, ����� �������� ������� ����� ����������� \".\"): ",
		"������!!! �� ����� ���-�� ����������.\n������� ����� ����� ���� ���� ����� ������, ���� ������ � ��������� ������, ������� � ��������� �� 500 �� 1420 ��, ��������� ����!!!", 500.0, 1420.0);

	this->repair = verification::GetBoolValue("������� ��������� �� ����� � �������, ���� ��, �� ������� \"y\" �� ����������, ���� �� ���, �������� �� \"n\": ",
		"\n����������� �������! ��������� ���� �� ��������� ���� ��������, �������� �� \"y\", ���� ��, �� \"n\", ���� ���!!!");
}

// ���������� �� �����
Pipe::Pipe(std::ifstream& fin)
{
	fin >> this->id >> this->length >> this->diameter >> this->repair;
}

// ������������� ��
CompressorStation::CompressorStation()
{
	maxIdCS++;
	this->id = maxIdCS;
	this->name = verification::GetStringValue("������� �������� �� (����� �� ������ 30 ��������): ",
		"������!!! �������� �� ����� �������� ������ �� �������� ��� ������ ������ � ����� ����� ������ ��� 30 ��������!!!", 30);

	this->countWorkShops = verification::GetNumericValue<size_t>("������� ���������� ����� �� (�� ������ 20): ",
		"������!!! ���������� ����� ��� ����� �����, ��� ����������� ��������, � ���� ����, ����� � ����� ����� ������ ���� ������ 20.", 0, 20);

	this->countWorkShopsInOperation = verification::GetNumericValue<size_t>("������� ���������� ����� � ������ (��� �� ������ ��������� ����� ���������� �����): ",
		"������!!! ���������� ����� ��� ����� �����, ��� ����������� ��������, ����� ����, �����, � ����� ����� �� ������ ��������� ����� ���������� �����.", 0, countWorkShops);

	this->effectiveness = verification::GetNumericValue<size_t>("������� �������� ������������� �� (��� ���������� � ���������, ������� ������� ����� �� 0 �� 100%): ",
		"������!!! �� ����� ���-�� ����������.\n������������� �� ����� ���� ����� ������ ������� � �������� �� 0 �� 100.\n��������� ����!!!", 0, 100);
}

// ���������� �� �����
CompressorStation::CompressorStation(std::ifstream& fin)
{
	fin >> this->id;
	fin.ignore(10000, '\n');
	getline(fin, this->name);
	fin >> this->countWorkShops
		>> this->countWorkShopsInOperation
		>> this->effectiveness;
}

// �������������� �����
void Pipe::GhangePipe()
{
	this->repair = verification::GetBoolValue("������� ����� ��������� ��� �����, ���� ��� � �������, �� ������� \"y\" �� ����������, ���� �� ���, �������� �� \"n\": ",
		"\n����������� �������! ��������� ���� �� ��������� ���� ��������, �������� �� \"y\", ���� ��, �� \"n\", ���� ���: ");
}

// �������������� ��
void CompressorStation::ChangeCS()
{
	this->countWorkShopsInOperation = verification::GetNumericValue<size_t>("������� ����� ���������� ����� � ������ (��� �� ������ ��������� ����� ���������� �����): ",
		"������!!! ���������� ����� ��� ����� �����, ��� ����������� ��������, ����� ����, �����, � ����� ����� �� ������ ��������� ����� ���������� �����.", 0,
		this->countWorkShops);
}

// ���������� ����� � ����
void Pipe::SaveToFile(std::ofstream& fout)
{
	fout << id << std::endl
		<< length << std::endl
		<< diameter << std::endl
		<< repair << std::endl;
}

// ���������� �� � ����
void CompressorStation::SaveToFile(std::ofstream& fout)
{
	fout << id << std::endl 
		<< name << std::endl
		<< countWorkShops << std::endl
		<< countWorkShopsInOperation << std::endl
		<< effectiveness << std::endl;
}
