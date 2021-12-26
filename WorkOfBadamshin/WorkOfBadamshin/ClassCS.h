#ifndef CLASS_CS_H
#define CLASS_CS_H
#include <string>
#include <fstream>

// Класс КС
class CompressorStation
{
private:
	size_t id;
	static size_t maxIdCS; // максимальный id среди элементов
	bool fullyField;
	size_t degreeOfOutcome = 0;
	size_t degreeOfEntry = 0;
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
	void IncDegreeOfOutcome();
	void IncDegreeOfEntry();
	void DecDegreeOfOutcome();
	void DecDegreeOfEntry();
	size_t GetDegreeOfOutcome() const;
	size_t GetDegreeOfEntry() const;
	bool IsFullyField() const;
	bool IsUsed() const;
};

#endif // !CLASS_CS_H