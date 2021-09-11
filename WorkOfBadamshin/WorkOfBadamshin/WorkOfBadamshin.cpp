#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>
#include <ctime>
using namespace std;
HANDLE myHandle = GetStdHandle(STD_OUTPUT_HANDLE);

// Вывод меню на консоль
void PrintMenu()
{
	cout << "Перед вами меню программы, выберите одну из операций!" << endl
		<< "1. Добавить трубу" << endl
		<< "2. Добавить КС" << endl
		<< "3. Просмотр всех объектов" << endl
		<< "4. Редактировать трубу" << endl
		<< "5. Редактировать КС" << endl
		<< "6. Сохранить" << endl
		<< "7. Загрузить" << endl
		<< "0. Выход" << endl
		<< "Введите число, которое и будет являться командой для программы: ";
};

// Проверка корректного ввода данных для команды
bool CheckCommand(string command)
{
	if (!isdigit(command[0]) || command[0] > '7' || size(command) > 1)
		return false;
	return true;
}

// Проверка ввода числа
bool CheckInputDigit(string number)
{
	if (size(number) == 0)
		return false;
	for (size_t i = 0; i < size(number); i++)
	{
		if (!isdigit(number[i]) && number[i] != '.')
			return false;
	}
	return true;
}

// Структура Трубы
struct Pipe
{
	string id;
	double length;
	double diameter;
	bool repair;
};

// Структура КС
struct CompressorStation
{
	string id;
	string name;
	int countWorkShops;
	int countWorkShopsInOperation;
	int effectiveness;
};

// Фильтр на ввод значений типа double длины, диаметра
double FilterValue(string textRequest, string textError)
{
	string value;
	while (true)
	{
		cout << textRequest;
		cin.seekg(cin.eof());
		getline(cin, value);
		if (CheckInputDigit(value))
			return stod(value);
		else
		{
			SetConsoleTextAttribute(myHandle, FOREGROUND_RED);
			cout << textError << endl;
			SetConsoleTextAttribute(myHandle, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
		}
	}
};



// Создание новой трубы
Pipe NewPipe()
{
	Pipe result;
	string strRepair;
	cout << "Введите id трубы: ";
	cin >> result.id;
	result.length = FilterValue("Введите длину трубы (необязательно целое число): ", "Ошибка!!! Вы ввели что-то непонятное.\n Длина трубы может быть либо целым числом, либо числом с плавающей точкой, повторите вввод!!!");
	result.diameter = FilterValue("Введите диаметр трубы (необязательно целое число): ", "Ошибка!!! Вы ввели что-то непонятное.\n Диаметр трубы может быть либо целым числом, либо числом с плавающей точкой, повторите вввод!!!");
	cout << "Укажите находится ли труба в ремонте, если да, то введите \"y\", если же труба не в ремонте, введите \"n\": ";
	while (true)
	{
		cin >> strRepair;
		if (strRepair == "y")
		{
			result.repair = true;
			break;
		}
		else if (strRepair == "n")
		{
			result.repair = false;
			break;
		}
		else
			cout << "Вы ввели что-то непонятное, повторите ввод по указанным выше правилам, \"y\" - это да, \"n\" - это нет: ";
	}
	return result;
};

int main()
{
	setlocale(LC_ALL, "Russian");
	string command;
	vector <Pipe> vectorPipes;
	size_t countPipes = 0, countCompessorStation = 0;
	while (true)
	{
		system("CLS");
		SetConsoleTextAttribute(myHandle, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
		PrintMenu();
		cin.seekg(cin.eof());
		getline(cin, command);
		if (CheckCommand(command))
		{
			switch (stoi(command))
			{
			case 1:
			{
				system("CLS");
				cout << "ИНИЦИАЛИЗАЦИЯ ТРУБЫ" << endl;
				vectorPipes.resize(++countPipes);
				vectorPipes[countPipes - 1] = NewPipe();
				break;
			}
			case 2:
			{
				break;
			}
			case 3:
			{
				break;
			}
			case 4:
			{
				break;
			}
			case 5:
			{
				break;
			}
			case 6:
			{
				break;
			}
			case 7:
			{
				break;
			}
			case 0:
			{
				return 0;
			}
			}
		}
		else
		{
			SetConsoleTextAttribute(myHandle, FOREGROUND_RED);
			cout << "Некорректный ввод данных!!! Осуществите ввод заново!!!" << endl
				<< "Сообщение пропадёт через 5 секунд" << endl;
			Sleep(5000);
		}
	}
}