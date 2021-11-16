#include <string>
#include <fstream>

#ifndef CLASSELEMENTS_H
#define CLASSELEMENTS_H

// ��������� �����
class Pipe
{
private:
	size_t id;
	static size_t maxIdPipe; // ���������� ��������� ��������� �� �� �����
public:
	double length;
	double diameter;
	bool repair;
	Pipe(); // � ������������ ��� ������ � �������������, ������������� ������ �� ����
	Pipe(std::ifstream&); // ����������� ��� ���������� �� �����
	void GhangePipe();
	void SaveToFile(std::ofstream&);
	friend class PipeCollection;
};

// ��������� ��
class CompressorStation
{
private:
	size_t id;
	static size_t maxIdCS; // ���������� ��������� ��������� �� �� �����
public:
	std::string name;
	size_t countWorkShops;
	size_t countWorkShopsInOperation;
	size_t effectiveness;
	CompressorStation(); // � ������������ ��� ������ � �������������, ������������� ������ �� ����
	CompressorStation(std::ifstream&);
	void ChangeCS();
	void SaveToFile(std::ofstream&);
	friend class CompressorStationCollection;
};

#endif // !CLASSELEMENTS_H