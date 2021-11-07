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
	Pipe()
	{
		countPipes++;
	}
	friend class PipeCollection;
};

// Структура КС
class CompressorStation
{
private:
	int id;
	static size_t countCS;
public:
	std::string name;
	size_t countWorkShops;
	size_t countWorkShopsInOperation;
	size_t effectiveness;
	CompressorStation()
	{
		countCS++;
	}
	friend class CompressorStationCollection;
};

#endif // !WORKOFBADAMSHIN_H