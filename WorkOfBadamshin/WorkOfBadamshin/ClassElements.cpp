#include "ClassElements.h"
#include "Verification.h"
#include <iomanip>


// Инициализация трубы
Pipe::Pipe()
{
	maxIdPipe++;
	this->id = maxIdPipe;
	this->length = verification::GetNumericValue<double>("Введите длину трубы, размерность - километры, диапазон от 10 до 100 км (необязательно целое число, чтобы отделить дробную часть используйте \".\"): ",
		"Ошибка!!! Вы ввели что-то непонятное.\nДлина трубы может быть либо целым числом, либо числом с плавающей точкой, лежащим в диапазоне от 10 до 100 км, повторите ввод!!!", 10.0, 100.0);

	this->diameter = verification::GetNumericValue<double>("Введите диаметр трубы, размерность миллиметры, диапазон от 500 до 1420 мм (необязательно целое число, чтобы отделить дробную часть используйте \".\"): ",
		"Ошибка!!! Вы ввели что-то непонятное.\nДиаметр трубы может быть либо целым числом, либо числом с плавающей точкой, лежащим в диапазоне от 500 до 1420 мм, повторите ввод!!!", 500.0, 1420.0);

	this->repair = verification::GetBoolValue("Укажите находится ли труба в ремонте, если да, то нажмите \"y\" на клавиатуре, если же нет, кликните по \"n\": ",
		"\nНеизвестная команда! Повторите ввод по указанным выше правилам, кликните по \"y\", если да, по \"n\", если нет!!!");
}

// Считывание из файла
Pipe::Pipe(std::ifstream& fin)
{
	fin >> this->id >> this->length >> this->diameter >> this->repair;
}

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

// Редактирование Трубы
void Pipe::GhangePipe()
{
	this->repair = verification::GetBoolValue("Укажите новое состояние для трубы, если она в ремонте, то нажмите \"y\" на клавиатуре, если же нет, кликните по \"n\": ",
		"\nНеизвестная команда! Повторите ввод по указанным выше правилам, кликните по \"y\", если да, по \"n\", если нет: ");
}

// Редактирование КС
void CompressorStation::ChangeCS()
{
	this->countWorkShopsInOperation = verification::GetNumericValue<size_t>("Введите новое количество цехов в работе (оно не должно превышать общее количество цехов): ",
		"Ошибка!!! Количество цехов это целое число, без посторонних символов, ввиде букв, точек, а также число не должно превышать общее количество цехов.", 0,
		this->countWorkShops);
}

// Сохранение Трубы в файл
void Pipe::SaveToFile(std::ofstream& fout)
{
	fout << id << std::endl
		<< length << std::endl
		<< diameter << std::endl
		<< repair << std::endl;
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
