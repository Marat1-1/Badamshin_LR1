#include <string>
#include <fstream>


#ifndef CLASS_CS_H
#define CLASS_CS_H

// ����� ��
class CompressorStation
{
private:
	size_t id;
	static size_t maxIdCS; // ������������ id ����� ���������
	size_t countInUse;
	bool used;
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
	static size_t GetMaxID();
	void IncCountUse();
	void DecCountUse();
	bool IsUsed() const;
};

#endif // !CLASS_CS_H