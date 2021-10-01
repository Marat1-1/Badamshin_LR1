#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <Windows.h>
#include <ctime>
#include <iomanip>

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
	n = 110,
	esc = 27
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

// Вывод ошибки с установкой жёлтого цвета текста
void PrintErrorText(string textError)
{
	SetConsoleTextAttribute(myHandle, FOREGROUND_RED | FOREGROUND_GREEN);
	cout << textError << endl;
	SetConsoleTextAttribute(myHandle, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
};

// Вывод заголовков с установкой зелёного цвета
void PrintTitle(string textTitle)
{
	SetConsoleTextAttribute(myHandle, FOREGROUND_GREEN);
	cout << textTitle << endl;
	SetConsoleTextAttribute(myHandle, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
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

// Запрос на ввод названия КС
string GetNameCS(string textRequest, string textError)
{
	string nameCS;
	while (true)
	{
		cout << textRequest;
		cin.seekg(cin.eof());
		getline(cin, nameCS);
		if (nameCS != "" && CheckCountSpace(nameCS) && size(nameCS) <= 30)
			return nameCS;
		else
		{
			PrintErrorText(textError);
		}
	}
};


// Запрос на ввод значений типа double в диапозоне от minValue до maxValue
double GetValue(string textRequest, string textError, double minValue, double maxValue)
{
	string value;
	while (true)
	{
		cout << textRequest;
		cin.seekg(cin.eof());
		getline(cin, value);
		if (CheckInputDigit(value))
		{
			try
			{
				if ((stod(value) >= minValue && stod(value) <= maxValue))
					return stod(value);
				else
					PrintErrorText(textError);
			}
			catch (exception)
			{
				PrintErrorText(textError);
			}
		}
		else
		{
			PrintErrorText(textError);
		}
	}
};

// Запрос на ввод типа int от minValue до maxValue
int GetValue(string textRequest, string textError, int minValue, int maxValue, bool thisInt)
{
	string value;
	while (true)
	{
		cout << textRequest;
		cin.seekg(cin.eof());
		getline(cin, value);
		if (CheckInputDigit(value, true))
		{
			try
			{
				if (stoi(value) >= minValue && stoi(value) <= maxValue)
					return stoi(value);
				else
					PrintErrorText(textError);
			}
			catch (exception)
			{
				PrintErrorText(textError);
			}
		}
		else
		{
			PrintErrorText(textError);
		}
	}
};


// Запрос на ввод значений: "ИСТИНА" или "ЛОЖЬ"
bool GetRepair(string textRequest, string textError)
{
	char stateRepair;
	cout << textRequest;
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
			PrintErrorText(textError);
		}
	}
};

// Прроверка на нажатие esc
void CheckPressEscape(string textRequest, string textError)
{
	while (true)
	{
		cout << textRequest;
		char escCommand;
		escCommand = _getch();
		if (escCommand == esc)
			break;
		else
			PrintErrorText(textError);
	}
};

// Создание новой трубы
Pipe CreatePipe(int id)
{
	Pipe result;
	result.id = id;
	result.length = GetValue("Введите длину трубы, размерность - километры, диапазон от 10 до 100 км (необязательно целое число, чтобы отделить дробную часть используйте \",\"): ", 
		"Ошибка!!! Вы ввели что-то непонятное.\nДлина трубы может быть либо целым числом, либо числом с плавающей точкой, лежащим в диапазоне от 10 до 100 км, повторите ввод!!!", 10, 100);
	result.diameter = GetValue("Введите диаметр трубы, размерность миллиметры, диапазон от 500 до 1420 мм (необязательно целое число, чтобы отделить дробную часть используйте \",\"): ",
		"Ошибка!!! Вы ввели что-то непонятное.\nДиаметр трубы может быть либо целым числом, либо числом с плавающей точкой, лежащим в диапазоне от 500 до 1420 мм, повторите ввод!!!", 500, 1420);
	result.repair = GetRepair("Укажите находится ли труба в ремонте, если да, то нажмите \"y\" на клавиатуре, если же нет, кликните по \"n\": ",
		"\nНеизвестная команда! Повторите ввод по указанным выше правилам, кликните по \"y\", если да, по \"n\", если нет: ");
	return result;
};

// Создание новой компрессорной станции
CompressorStation CreateCompressorStation(int id)
{
	CompressorStation result;
	result.id = id;
	result.name = GetNameCS("Введите название КС (длина не больше 30 символов): ",
		"Ошибка!!! Название не может состоять только из пробелов или пустой строки и иметь длину больше чем 40 символов (сообщение пропадёт через 3 секунды)");
	result.countWorkShops = GetValue("Введите количество цехов КС (не больше 20): ",
		"Ошибка!!! Количество цехов это целое число, без посторонних символов, в виде букв, точек и также число должно быть меньше 20.", 0, 20, true);
	result.countWorkShopsInOperation = GetValue("Введите количество цехов в работе (оно не должно превышать общее количество цехов): ", 
		"Ошибка!!! Количество цехов это целое число, без посторонних символов, ввиде букв, точек, а также число не должно превышать общее количество цехов.", 0, result.countWorkShops,true);
	result.effectiveness = GetValue("Введите значение эффективности КС (оно измеряется в процентах, поэтому введите число от 0 до 100%): ",
		"Ошибка!!! Вы ввели что-то непонятное.\nЭффективность КС может быть либо целым числом, либо числом с плавающей точкой, лежащим в пределах от 0 до 100.\nПовторите ввод!!!", 0, 100);
	return result;
};


// Вывод символа определённое количество раз
void PrintChar(char ch, size_t count)
{
	for (size_t i = 0; i < count; i++)
	{
		cout << ch;
	}
	cout << endl;
};


// Вывод таблицы труб
void PrintTablePipes(vector <Pipe>& vectorPipes)
{
	PrintChar('-', 131);
	cout << "|" << setw(20) << "ID" << setw(30) << "LENGTH" << setw(30) << "DIAMETER" << setw(30) << "REPAIR" << setw(20) << "|" << endl;
	PrintChar('-', 131);
	for (size_t i = 0; i < vectorPipes.size(); i++)
	{
		cout << "|" << setw(20) << vectorPipes[i].id << setw(30) << vectorPipes[i].length << setw(30) << vectorPipes[i].diameter << setw(30) << (vectorPipes[i].repair == true ? "true" : "false") << setw(20) << "|" << endl;
	}
	PrintChar('-', 131);
};


// Вывод таблицы Компрессорных станций
void PrintTableCS(vector <CompressorStation>& vectorCompressorStations)
{
	PrintChar('-', 172);
	cout << "|" << setw(20) << "ID" << setw(31) << "NAME" << setw(30) << "CountWorkShops" << setw(40) << "CountWorkShopsInOperation" << setw(30) << "EFFECTIVENESS" << setw(20) << "|" << endl;
	PrintChar('-', 172);
	for (size_t i = 0; i < vectorCompressorStations.size(); i++)
	{
		cout << "|" << setw(20) << vectorCompressorStations[i].id << setw(31) << vectorCompressorStations[i].name << setw(30) << vectorCompressorStations[i].countWorkShops << setw(40) << vectorCompressorStations[i].countWorkShopsInOperation << setw(30) << vectorCompressorStations[i].effectiveness << setw(20) << "|" << endl;
	}
	PrintChar('-', 172);
};


// Редактирование Труб
void ChangePipe(vector <Pipe>& vectorPipes)
{
	size_t localId;
	bool query;
	cout << "Всего добавлено труб: " << size(vectorPipes) << endl;
	if (size(vectorPipes) == 0)
	{
		PrintErrorText("Вы не добавили ни одной трубы, редактирование недоступно!");
		CheckPressEscape("\n\nЧтобы выйти в меню, нажмите ESC: ", "\nКоманда не распознана, нажмите ESC на клавиатуре, если хотите вернуться в меню!");
		return;
	}
	while (true)
	{
		localId = GetValue("\nВведите номер (id) трубы, которую вы бы хотели редактировать (id не должен превышать общее количество труб): ",
			"Вы ввели недопустимое значение, id трубы не должен превышать общее количество труб, а также он является натуральным числом!!!", 1, size(vectorPipes));
		cout << "Изначальное состояние трубы: " << (vectorPipes[localId - 1].repair == true ? "в ремонте" : "не в ремонте") << endl;
		vectorPipes[localId - 1].repair = GetRepair("Укажите новое состояние для трубы, если она в ремонте, то нажмите \"y\" на клавиатуре, если же нет, кликните по \"n\": ",
			"\nНеизвестная команда! Повторите ввод по указанным выше правилам, кликните по \"y\", если да, по \"n\", если нет: ");
		query = GetRepair("\n\nХотите ли вы продолжить редактировать трубы, если да, то кликните \"y\", если же нет, то нажмите на \"n\": ",
			"\nНеизвестная команда! Повторите ввод по указанным выше правилам, кликните по \"y\", если да, по \"n\", если нет: ");
		if (query != true)
			break;
	}
};


// Редактирование Компрессорных станций
void ChangeCS(vector <CompressorStation>& vectorCompressorStations)
{
	size_t localId;
	bool query;
	cout << "Всего добавлено компрессорных станций: " << size(vectorCompressorStations) << endl;
	if (size(vectorCompressorStations) == 0)
	{
		PrintErrorText("Вы не добавили ни одной компрессорной станции, редактирование недоступно!");
		CheckPressEscape("\n\nЧтобы выйти в меню, нажмите ESC: ", "\nКоманда не распознана, нажмите ESC на клавиатуре, если хотите вернуться в меню!");
		return;
	}
	while (true)
	{
		localId = GetValue("\nВведите номер (id) компрессорной станции, которую вы бы хотели редактировать (id не должен превышать общее количество компрессорных станций): ",
			"Вы ввели недопустимое значение, id трубы не должен превышать общее количество компрессорных станций, а также он является натуральным числом!!!", 
			1, size(vectorCompressorStations));
		cout << "Количество цехов у данной компрессорной станции: " << vectorCompressorStations[localId - 1].countWorkShops << endl;
		cout << "Количество цехов в работе у данной компрессорной станции: " << vectorCompressorStations[localId - 1].countWorkShopsInOperation << endl;
		vectorCompressorStations[localId - 1].countWorkShopsInOperation = GetValue("Введите новое количество цехов в работе (оно не должно превышать общее количество цехов): ",
			"Ошибка!!! Количество цехов это целое число, без посторонних символов, ввиде букв, точек, а также число не должно превышать общее количество цехов.", 
			0, vectorCompressorStations[localId - 1].countWorkShops, true);
		query = GetRepair("\n\nХотите ли вы продолжить редактировать компрессоные станции, если да, то кликните \"y\", если же нет, то нажмите на \"n\": ",
			"\nНеизвестная команда! Повторите ввод по указанным выше правилам, кликните по \"y\", если да, по \"n\", если нет: ");
		if (query != true)
			break;
	}
};


// Установка шрифта в консоли
void ChangeConsoleFont()
{
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;
	cfi.dwFontSize.Y = 20;
	cfi.FontWeight = FW_REGULAR;
	SetCurrentConsoleFontEx(myHandle, FALSE, &cfi);
};


// Точка входа в программу
int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleTitle(L"Лабораторная работа №1, Бадамшин Марат Ринатович, АА-20-05");
	ChangeConsoleFont();
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
			PrintTitle("\t\t\t\t\t\tИНИЦИАЛИЗАЦИЯ ТРУБЫ");
			Pipe NewPipe = CreatePipe(size(vectorPipes) + 1);
			vectorPipes.push_back(NewPipe);
			break;
		}
		case two:
		{
			system("CLS");
			PrintTitle("\t\t\t\t\tИНИЦИАЛИЗАЦИЯ КОМПРЕССОРНОЙ СТАНЦИИ");
			CompressorStation NewComressorStation = CreateCompressorStation(size(vectorCompressorStations) + 1);
			vectorCompressorStations.push_back(NewComressorStation);
			break;
		}
		case three:
		{
			system("ClS");
			PrintTitle("\n\t\t\t\t\t\t\tТАБЛИЦА ТРУБ\n");
			PrintTablePipes(vectorPipes);
			PrintTitle("\n\n\n\n\t\t\t\t\t\t\t\tТАБЛИЦА КОМПРЕССОРНЫХ СТАНЦИЙ\n");
			PrintTableCS(vectorCompressorStations);
			CheckPressEscape("\n\n\nЧтобы выйти в меню, нажмите ESC: ", "\nКоманда не распознана, нажмите ESC на клавиатуре, если хотите вернуться в меню!");
			break;
		}
		case four:
		{
			system("CLS");
			PrintTitle("\n\t\t\t\t\tРЕДАКТИРОВАНИЕ ТРУБ\n");
			ChangePipe(vectorPipes);
			break;
		}
		case five:
		{
			system("CLS");
			PrintTitle("\n\t\t\t\t\tРЕДАКТИРОВАНИЕ КОМПРЕССОРНЫХ СТАНЦИЙ\n");
			ChangeCS(vectorCompressorStations);
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
			PrintTitle("\n\tИтак, вы нажали на выход, на этом программа завершила свой сеанс работы.\n\t\t\t\tДо скорой встречи! :)");
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