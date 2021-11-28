#include "ClassCS.h"
#include "Verification.h"
#include <iomanip>


// Инициализация КС
CompressorStation::CompressorStation()
{
	maxIdCS++;
	this->id = maxIdCS;
	this->name = verification::GetStringValue("Введите название КС (длина не больше 30 символов): ",
		"Ошибка!!! Название не может состоять только из пробелов или пустой строки и иметь длину больше чем 30 символов!!!", 30);

	this->countWorkShops = verification::GetNumericValue<size_t>("Введите количество цехов КС (не больше 20): ",
		"Ошибка!!! Количество цехов это целое число, без посторонних символов, в виде букв, точек и также число должно быть меньше 20.", 0, 20);

	this->countWorkShopsInOperation = verification::GetNumericValue<size_t>("Введите количество цехов в работе (оно не должно превышать общее количество цехов): ",
		"Ошибка!!! Количество цехов это целое число, без посторонних символов, ввиде букв, точек, а также число не должно превышать общее количество цехов.", 0, countWorkShops);

	this->effectiveness = verification::GetNumericValue<size_t>("Введите значение эффективности КС (оно измеряется в процентах, поэтому введите число от 0 до 100%): ",
		"Ошибка!!! Вы ввели что-то непонятное.\nЭффективность КС может быть целым числом лежащим в пределах от 0 до 100.\nПовторите ввод!!!", 0, 100);
}

// Считывание из файла
CompressorStation::CompressorStation(std::ifstream& fin)
{
	fin >> this->id;
	fin.ignore(10000, '\n');
	getline(fin, this->name);
	fin >> this->countWorkShops
		>> this->countWorkShopsInOperation
		>> this->effectiveness;
}

// Редактирование КС
void CompressorStation::ChangeCS()
{
	this->countWorkShopsInOperation = verification::GetNumericValue<size_t>("Введите новое количество цехов в работе (оно не должно превышать общее количество цехов): ",
		"Ошибка!!! Количество цехов это целое число, без посторонних символов, ввиде букв, точек, а также число не должно превышать общее количество цехов.", 0,
		this->countWorkShops);
}

// Сохранение КС в файл
void CompressorStation::SaveToFile(std::ofstream& fout)
{
	fout << id << std::endl
		<< name << std::endl
		<< countWorkShops << std::endl
		<< countWorkShopsInOperation << std::endl
		<< effectiveness << std::endl;
}