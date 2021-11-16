#include <string>
#include <fstream>

#ifndef CLASSELEMENTS_H
#define CLASSELEMENTS_H

// Структура Трубы
class Pipe
{
private:
	size_t id;
	static size_t maxIdPipe; // количество созданных элементов за всё время
public:
	double length;
	double diameter;
	bool repair;
	Pipe(); // в конструкторе идёт работа с пользователем, запрашиваются данные на ввод
	Pipe(std::ifstream&); // Конструктор для считывания из файла
	void GhangePipe();
	void SaveToFile(std::ofstream&);
	friend class PipeCollection;
};

// Структура КС
class CompressorStation
{
private:
	size_t id;
	static size_t maxIdCS; // количество созданных элементов за всё время
public:
	std::string name;
	size_t countWorkShops;
	size_t countWorkShopsInOperation;
	size_t effectiveness;
	CompressorStation(); // в конструкторе идёт работа с пользователем, запрашиваются данные на ввод
	CompressorStation(std::ifstream&);
	void ChangeCS();
	void SaveToFile(std::ofstream&);
	friend class CompressorStationCollection;
};

#endif // !CLASSELEMENTS_H