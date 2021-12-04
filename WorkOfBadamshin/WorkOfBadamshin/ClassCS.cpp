#include "ClassCS.h"
#include "Verification.h"
#include <iomanip>


// ������������� ��
CompressorStation::CompressorStation() : used(false), countInUse(0)
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
CompressorStation::CompressorStation(std::ifstream& fin) : used(false)
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

// ��������� countInUse
void CompressorStation::IncCountUse()
{
	if (countInUse < countWorkShops)
		++countInUse;
	if (countInUse == countWorkShops)
		used = true;
}

// ��������� countInUse
void CompressorStation::DecCountUse()
{
	if (countInUse > 0)
		--countInUse;
	if (countInUse < countWorkShops)
		used = false;
}

bool CompressorStation::IsUsed() const
{
	return used;
}