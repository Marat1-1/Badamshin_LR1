#include <string>

#ifndef WORKOFBADAMSHIN_H
#define WORKOFBADAMSHIN_H

// Структура Трубы
class Pipe
{
private:
	int id;
	static size_t countPipes;
public:
	double length;
	double diameter;
	bool repair;
	friend class PipeCollection;
	Pipe()
	{
		countPipes++;
	}
};

// Структура КС
class CompressorStation
{
private:
	int id;
	static size_t countCS;
public:
	std::string name;
	int countWorkShops;
	int countWorkShopsInOperation;
	size_t effectiveness;
	friend class CompressorStationCollection;
	CompressorStation()
	{
		countCS++;
	}
};

#endif // !WORKOFBADAMSHIN_H