#include <string>
#include <fstream>


#ifndef CLASS_CS_H
#define CLASS_CS_H

// Класс КС
class CompressorStation
{
private:
	size_t id;
	static size_t maxIdCS; // максимальный id среди элементов
	size_t countInUse;
	bool used;
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
	static size_t GetMaxID();
	void IncCountUse();
	void DecCountUse();
	bool IsUsed() const;
};

#endif // !CLASS_CS_H