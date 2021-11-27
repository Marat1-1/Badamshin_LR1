#include <string>
#include <fstream>


#ifndef CLASS_CS_H
#define CLASS_CS_H

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

#endif // !CLASS_CS_H