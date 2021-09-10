#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>
#include <limits>
using namespace std;

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
	for (size_t i = 0; i < size(number); i++)
	{
		if (!isdigit(number[i]) || number[i] != '.')
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

// Создание новой трубы
Pipe NewPipe()
{
	Pipe result;
	string strRepair;
	cout << "Введите id трубы: ";
	cin >> result.id;
	cout << "Введите длину трубы: ";
	cin >> result.length;
	cout << "Введите диаметр трубы: ";
	cin >> result.diameter;
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
	HANDLE myHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	string command;
	vector <Pipe> vectorPipes;
	size_t countPipes = 0, countCompessorStation = 0;
	while (true)
	{
		system("CLS");
		SetConsoleTextAttribute(myHandle, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
		PrintMenu();
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
		while ((getchar()) != '\n');
	}
}