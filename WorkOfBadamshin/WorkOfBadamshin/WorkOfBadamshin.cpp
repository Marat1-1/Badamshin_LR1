#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <Windows.h>
#include <ctime>
using namespace std;

enum TableCommand
{
	zero = 48,
	one = 49,
	two = 50,
	three = 51,
	four = 52,
	five = 53, 
	six = 54,
	seven = 55
};

// Консоль
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
		<< "Итак, нажмите на нужную клавишу на клавиатуре ";
};


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
};

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

//Фильтр на ввод значения "В ремонте" для труб
bool FilterRepair()
{
	string strRepair;
	cout << "Укажите находится ли труба в ремонте, если да, то введите \"y\", если же труба не в ремонте, введите \"n\": ";
	while (true)
	{
		cin.seekg(cin.eof());
		getline(cin, strRepair);
		if (strRepair == "y")
		{
			return true;
		}
		else if (strRepair == "n")
		{
			return false;
		}
		else
		{
			cout << "Вы ввели что-то непонятное, повторите ввод по указанным выше правилам, \"y\" - это да, \"n\" - это нет: ";
		}
	}
};

// Создание новой трубы
Pipe NewPipe()
{
	Pipe result;
	cout << "Введите id трубы: ";
	cin >> result.id;
	result.length = FilterValue("Введите длину трубы (необязательно целое число): ", "Ошибка!!! Вы ввели что-то непонятное.\nДлина трубы может быть либо целым числом, либо числом с плавающей точкой, повторите ввод!!!");
	result.diameter = FilterValue("Введите диаметр трубы (необязательно целое число): ", "Ошибка!!! Вы ввели что-то непонятное.\nДиаметр трубы может быть либо целым числом, либо числом с плавающей точкой, повторите ввод!!!");
	result.repair = FilterRepair();
	return result;
};

int main()
{
	setlocale(LC_ALL, "Russian");
	char command;
	vector <Pipe> vectorPipes;
	size_t countPipes = 0, countCompessorStation = 0;
	while (true)
	{
		system("CLS");
		SetConsoleTextAttribute(myHandle, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
		PrintMenu();
		command = _getch();
		switch (command)
		{
		case one:
		{
			system("CLS");
			SetConsoleTextAttribute(myHandle, FOREGROUND_GREEN);
			cout << "\t\t\t\t\t\tИНИЦИАЛИЗАЦИЯ ТРУБЫ" << endl;
			SetConsoleTextAttribute(myHandle, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
			vectorPipes.resize(++countPipes);
			vectorPipes[countPipes - 1] = NewPipe();
			break;
		}
		case two:
		{
			break;
		}
		case three:
		{
			break;
		}
		case four:
		{
			break;
		}
		case five:
		{
			break;
		}
		case six:
		{
			break;
		}
		case seven:
		{
			break;
		}
		case zero:
		{
			system("cls");
			SetConsoleTextAttribute(myHandle, FOREGROUND_GREEN);
			cout << "Итак, вы нажали на выход, на этом программа завершила свой сеанс работы.\nДо скорой встречи! :)" << endl;
			SetConsoleTextAttribute(myHandle, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
			return 0;
		}
		default:
			SetConsoleTextAttribute(myHandle, FOREGROUND_RED);
			cout << "\nНекорректный ввод данных!!! Осуществите ввод заново!!!" << endl
				<< "Сообщение пропадёт через 5 секунд" << endl;
			Sleep(3000);
			break;
		}
	}
};