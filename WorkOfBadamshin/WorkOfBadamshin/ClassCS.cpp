#include "ClassCS.h"
#include "Verification.h"
#include <iomanip>


// ������������� ��
CompressorStation::CompressorStation() : fullyField(false), degreeOfOutcome(0), degreeOfEntry(0)
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
CompressorStation::CompressorStation(std::ifstream& fin) : fullyField(false), degreeOfOutcome(0), degreeOfEntry(0)
{
	fin >> this->id;
	fin.ignore(10000, '\n');
	getline(fin, this->name);
	fin >> this->countWorkShops
		>> this->countWorkShopsInOperation
		>> this->effectiveness;
}

// �������������� ��
void CompressorStation::ChangeCS()
{
	this->countWorkShopsInOperation = verification::GetNumericValue<size_t>("������� ����� ���������� ����� � ������ (��� �� ������ ��������� ����� ���������� �����): ",
		"������!!! ���������� ����� ��� ����� �����, ��� ����������� ��������, ����� ����, �����, � ����� ����� �� ������ ��������� ����� ���������� �����.", 0,
		this->countWorkShops);
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

// �������� �������� ������������� id
size_t CompressorStation::GetMaxID()
{
	return maxIdCS;
}

// ��������� degreeOfOutcome
void CompressorStation::IncDegreeOfOutcome()
{
	if (degreeOfEntry + degreeOfOutcome < countWorkShops)
		++degreeOfOutcome;
	if (degreeOfEntry + degreeOfOutcome == countWorkShops)
		fullyField = true;
}

// ��������� degreeOfEntry
void CompressorStation::IncDegreeOfEntry()
{
	if (degreeOfEntry + degreeOfOutcome < countWorkShops)
		++degreeOfEntry;
	if (degreeOfEntry + degreeOfOutcome == countWorkShops)
		fullyField = true;
}

// ��������� degreeOfOutcome
void CompressorStation::DecDegreeOfOutcome()
{
	if (degreeOfOutcome > 0)
		--degreeOfOutcome;
	if (degreeOfEntry + degreeOfOutcome < countWorkShops)
		fullyField = false;
}

// ��������� degreeOfEntry
void CompressorStation::DecDegreeOfEntry()
{
	if (degreeOfEntry > 0)
		--degreeOfEntry;
	if (degreeOfEntry + degreeOfOutcome < countWorkShops)
		fullyField = false;
}

// �������� �������� �������� ������ � ������
size_t CompressorStation::GetDegreeOfOutcome() const
{
	return degreeOfOutcome;
}

size_t CompressorStation::GetDegreeOfEntry() const
{
	return degreeOfEntry;
}

// ��������� �� ����� � ������ ������� � ��
bool CompressorStation::IsFullyField() const
{
	return fullyField;
}

// ������������ �� ��
bool CompressorStation::IsUsed() const
{
	return degreeOfOutcome > 0 || degreeOfEntry > 0;
}