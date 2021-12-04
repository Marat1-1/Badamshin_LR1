#include "ClassPipe.h"
#include "Verification.h"
#include <iomanip>


// Инициализация трубы
Pipe::Pipe() : used(false)
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
Pipe::Pipe(std::ifstream& fin) : used(false)
{
	fin >> this->id >> this->length >> this->diameter >> this->repair;
}

// Редактирование Трубы
void Pipe::GhangePipe()
{
	this->repair = verification::GetBoolValue("Укажите новое состояние для трубы, если она в ремонте, то нажмите \"y\" на клавиатуре, если же нет, кликните по \"n\": ",
		"\nНеизвестная команда! Повторите ввод по указанным выше правилам, кликните по \"y\", если да, по \"n\", если нет: ");
}

// Сохранение Трубы в файл
void Pipe::SaveToFile(std::ofstream& fout)
{
	fout << id << std::endl
		<< length << std::endl
		<< diameter << std::endl
		<< repair << std::endl;
}

// Установить InId и OutId
void Pipe::SetInId(size_t id)
{
	inId = id;
}

void Pipe::SetOutId(size_t id)
{
	outId = id;
}

// Получить InId и OutId
size_t Pipe::GetInId() const
{
	return inId;
}

size_t Pipe::GetOutId() const
{
	return outId;
}

// Установить значение поля used
void Pipe::SetUsed(bool flag)
{
	used = flag;
}

// Узнать значение поля used
bool Pipe::IsUsed() const
{
	return used;
}

// Получить максимальный id
size_t Pipe::GetMaxID()
{
	return maxIdPipe;
}