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
	seven = 55,
	y =	121,
	n = 110
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
	double effectiveness;
};

// Проверка ввода числа double
bool CheckInputDigit(string number)
{
	int counter = 0;
	if (size(number) == 0)
		return false;
	for (size_t i = 0; i < size(number); i++)
	{
		if (!isdigit(number[i]))
			if (number[i] != ',')
				return false;
			else
				counter++;
	}
	return counter <= 1;
};

// Проверка ввода числа int
bool CheckInputDigit(string number, bool thisInt)
{
	if (size(number) == 0 || !isdigit(number[0]))
		return false;
	for (size_t i = 0; i < size(number); i++)
	{
		if (!isdigit(number[i]))
			return false;
	}
	return true;
};

// Переписать код
// Проверка, не состоит ли строка только из пробелов
bool CheckCountSpace(string str)
{
	int counter = 0;
	for (size_t i = 0; i < size(str); i++)
	{
		if (str[i] == ' ')
			++counter;
	}
	if (counter == size(str))
		return false;
	return true;
};

// Вывод ошибки с установкой другого цвета текста
void PrintErrorText(string textError)
{
	SetConsoleTextAttribute(myHandle, FOREGROUND_RED | FOREGROUND_GREEN);
	cout << textError << endl;
	SetConsoleTextAttribute(myHandle, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
};


// Убрать
// Фильтр на ввод id для Трубы и КС
string FilterId(string textRequest, string textError)
{
	string resultId;
	while (true)
	{
		cout << textRequest;
		cin.seekg(cin.eof());
		getline(cin, resultId);
		if (resultId != "" && CheckCountSpace(resultId))
			return resultId;
		else
		{
			PrintErrorText(textError);
		}
	}
};

// Фильтр на ввод названия КС
string FilterNameCS(string textRequest, string textError)
{
	string nameCS;
	while (true)
	{
		cout << textRequest;
		cin.seekg(cin.eof());
		getline(cin, nameCS);
		if (nameCS != "" && CheckCountSpace(nameCS))
			return nameCS;
		else
		{
			PrintErrorText(textError);
		}
	}
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
			PrintErrorText(textError);
		}
	}
};

// Фильтр на ввод типа int количества цехов КС
int FilterValue(string textRequest, string textError, bool thisInt)
{
	string value;
	while (true)
	{
		cout << textRequest;
		cin.seekg(cin.eof());
		getline(cin, value);
		if (CheckInputDigit(value, true))
			return stoi(value);
		else
		{
			PrintErrorText(textError);
		}
	}
};

// Фильтр на ввод количества цехов КС
int FilterCountWorkShopsOperation(CompressorStation& cs)
{
	int value;
	while (true)
	{
		value = FilterValue("Введите количество цехов в работе: ", "Ошибка!!! Количество цехов это целое число, без посторонних символов, ввиде букв, точек и т.д.", true);
		if (value <= cs.countWorkShops)
			return value;
		else
		{
			PrintErrorText("Простите, но количество цехов в работе не может превышать общее количество цехов, осуществите ввод по новой!");
		}
	}
};

// Фильтр на ввод значения эффективности для КС
double FilterEffectiveness()
{
	double value;
	while (true)
	{
		value = FilterValue("Введите значение эффективности КС (оно измеряется в процентах, поэтому введите число от 0 до 100%): ", "Ошибка!!! Вы ввели что-то непонятное.\nЭффективность КС может быть либо целым числом, либо числом с плавающей точкой, лежащим в пределах от 0 до 100.\nПовторите ввод!!!");
		if (value >= 0. && value <= 100.)
			return value;
		else
		{
			PrintErrorText("Простите, но вы ввели число не лежащее в диапазоне от 0 до 100, повторите ввод заново!");
		}
	}
};

// Фильтр на ввод значения "В ремонте" для труб
bool FilterRepair()
{
	char stateRepair;
	cout << "Укажите находится ли труба в ремонте, если да, то нажмите \"y\" на клавиатуре, если же нет, кликните по \"n\": ";
	while (true)
	{
		stateRepair = _getch();
		if (stateRepair == y)
		{
			return true;
		}
		else if (stateRepair == n)
		{
			return false;
		}
		else
		{
			PrintErrorText("\nНеизвестная команда! Повторите ввод по указанным выше правилам, кликните по \"y\", если да, по \"n\", если нет: ");
		}
	}
};

// Создание новой трубы
Pipe NewPipe()
{
	Pipe result;
	result.id = FilterId("Введите id трубы: ", "Ошибка!!! Поле Id не может быть пустым.");
	result.length = FilterValue("Введите длину трубы (необязательно целое число, чтобы отделить дробную часть используйте \",\"): ", "Ошибка!!! Вы ввели что-то непонятное.\nДлина трубы может быть либо целым числом, либо числом с плавающей точкой, повторите ввод!!!");
	result.diameter = FilterValue("Введите диаметр трубы (необязательно целое число, чтобы отделить дробную часть используйте \",\"): ", "Ошибка!!! Вы ввели что-то непонятное.\nДиаметр трубы может быть либо целым числом, либо числом с плавающей точкой, повторите ввод!!!");
	result.repair = FilterRepair();
	return result;
};

// Создание новой компрессорной станции
CompressorStation NewCompressorStation()
{
	CompressorStation result;
	result.id = FilterId("Введите id КС: ", "Ошибка!!! Поле Id не может быть пустым.");
	result.name = FilterNameCS("Введите название КС: ", "Ошибка!!! Название не может состоять только из пробелов или пустой строки.");
	result.countWorkShops = FilterValue("Введите количество цехов КС: ", "Ошибка!!! Количество цехов это целое число, без посторонних символов, ввиде букв, точек и т.д.", true);
	result.countWorkShopsInOperation = FilterCountWorkShopsOperation(result);
	result.effectiveness = FilterEffectiveness();
	return result;
}


// Точка входа в программу
int main()
{
	setlocale(LC_ALL, "Russian");
	char command;
	vector <Pipe> vectorPipes;
	vector <CompressorStation> vectorCompressorStations;
	while (true)
	{
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
			vectorPipes.push_back(NewPipe());
			break;
		}
		case two:
		{
			system("CLS");
			SetConsoleTextAttribute(myHandle, FOREGROUND_GREEN);
			cout << "\t\t\t\t\tИНИЦИАЛИЗАЦИЯ КОМПРЕССОРНОЙ СТАНЦИИ" << endl;
			SetConsoleTextAttribute(myHandle, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
			vectorCompressorStations.push_back(NewCompressorStation());
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
			system("CLS");
			SetConsoleTextAttribute(myHandle, FOREGROUND_GREEN);
			cout << "Итак, вы нажали на выход, на этом программа завершила свой сеанс работы.\nДо скорой встречи! :)" << endl;
			SetConsoleTextAttribute(myHandle, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
			return 0;
		}
		default:
			PrintErrorText("\nНекорректный ввод данных!!! Нажмите на число, которое соотвествует команде из списка!!!\nСообщение пропадёт через 3 секунды");
			Sleep(3000);
			break;
		}
		system("CLS");
	}
};