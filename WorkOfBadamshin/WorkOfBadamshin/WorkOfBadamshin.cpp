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
	int id;
	double length;
	double diameter;
	bool repair;
};

// Структура КС
struct CompressorStation
{
	int id;
	string name;
	int countWorkShops;
	int countWorkShopsInOperation;
	double effectiveness;
};

// Проверка ввода числа double
bool CheckInputDigit(string number)
{
	int counter = 0;
	if (size(number) == 0 || !isdigit(number[0]))
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


// Проверка, не состоит ли строка только из пробелов
bool CheckCountSpace(string str)
{
	int i = 0;
	while (i != size(str))
	{
		if (str[i] != ' ')
			return true;
		++i;
	}
	return false;
};

// Вывод ошибки с установкой другого цвета текста
void PrintErrorText(string textError)
{
	SetConsoleTextAttribute(myHandle, FOREGROUND_RED | FOREGROUND_GREEN);
	cout << textError << endl;
	SetConsoleTextAttribute(myHandle, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
};


// Запрос на ввод названия КС
string GetNameCS(string textRequest, string textError)
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


// Запрос на ввод значений типа double в диапозоне от 0 до maxValue
double GetValue(string textRequest, string textError, double minValue, double maxValue)
{
	string value;
	while (true)
	{
		cout << textRequest;
		cin.seekg(cin.eof());
		getline(cin, value);
		if (CheckInputDigit(value) && (stod(value) >= minValue && stod(value) <= maxValue))
			return stod(value);
		else
		{
			PrintErrorText(textError);
		}
	}
};

// Запрос на ввод типа int
int GetValue(string textRequest, string textError, bool thisInt)
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


// Запрос на ввод количества цехов КС
int GetCountWorkShopsOperation(CompressorStation& cs)
{
	int value;
	while (true)
	{
		value = GetValue("Введите количество цехов в работе (оно не должно превышать общее количество цехов): ", "Ошибка!!! Количество цехов это целое число, без посторонних символов, ввиде букв, точек и т.д.", true);
		if (value <= cs.countWorkShops)
			return value;
		else
		{
			PrintErrorText("Простите, но количество цехов в работе не может превышать общее количество цехов, осуществите ввод по новой!");
		}
	}
};


// Запрос на ввод значения "В ремонте" для труб
bool GetRepair()
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
Pipe CreatePipe(int id)
{
	Pipe result;
	result.id = id;
	result.length = GetValue("Введите длину трубы, размерность - километры (необязательно целое число, чтобы отделить дробную часть используйте \",\"): ", 
		"Ошибка!!! Вы ввели что-то непонятное.\nДлина трубы может быть либо целым числом, либо числом с плавающей точкой, лежащим в диапазоне от 10 до 100 км, повторите ввод!!!", 10, 100);
	result.diameter = GetValue("Введите диаметр трубы, размерность миллиметры (необязательно целое число, чтобы отделить дробную часть используйте \",\"): ", 
		"Ошибка!!! Вы ввели что-то непонятное.\nДиаметр трубы может быть либо целым числом, либо числом с плавающей точкой, повторите ввод!!!", 0, 200);
	result.repair = GetRepair();
	return result;
};

// Создание новой компрессорной станции
CompressorStation CreateCompressorStation(int id)
{
	CompressorStation result;
	result.id = id;
	result.name = GetNameCS("Введите название КС: ", 
		"Ошибка!!! Название не может состоять только из пробелов или пустой строки.");
	result.countWorkShops = GetValue("Введите количество цехов КС: ", 
		"Ошибка!!! Количество цехов это целое число, без посторонних символов, в виде букв, точек и т.д.", true);
	result.countWorkShopsInOperation = GetCountWorkShopsOperation(result);
	result.effectiveness = GetValue("Введите значение эффективности КС (оно измеряется в процентах, поэтому введите число от 0 до 100%): ", 
		"Ошибка!!! Вы ввели что-то непонятное.\nЭффективность КС может быть либо целым числом, либо числом с плавающей точкой, лежащим в пределах от 0 до 100.\nПовторите ввод!!!", 0, 100);
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
			Pipe NewPipe = CreatePipe(size(vectorPipes) + 1);
			vectorPipes.push_back(NewPipe);
			break;
		}
		case two:
		{
			system("CLS");
			SetConsoleTextAttribute(myHandle, FOREGROUND_GREEN);
			cout << "\t\t\t\t\tИНИЦИАЛИЗАЦИЯ КОМПРЕССОРНОЙ СТАНЦИИ" << endl;
			SetConsoleTextAttribute(myHandle, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
			CompressorStation NewComressorStation = CreateCompressorStation(size(vectorCompressorStations) + 1);
			vectorCompressorStations.push_back(NewComressorStation);
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