﻿#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <Windows.h>
#include <ctime>
#include <iomanip>
#include <fstream>

using namespace std;

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
				double resultValue = stod(value);
				if (resultValue >= minValue && resultValue <= maxValue)
					return resultValue;
				else
					PrintErrorText(textError);
			}
			catch (const exception& e)
			{
				cout << e.what()<<endl;
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
				int resultValue = stoi(value);
				if (resultValue >= minValue && resultValue <= maxValue)
					return resultValue;
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
bool GetBool(string textRequest, string textError)
{
	char stateRepair;
	cout << textRequest;
	while (true)
	{
		stateRepair = _getch();
		if (stateRepair == 'y')
		{
			return true;
		}
		else if (stateRepair == 'n')
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
		if (escCommand == '\x1b')
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
	result.repair = GetBool("Укажите находится ли труба в ремонте, если да, то нажмите \"y\" на клавиатуре, если же нет, кликните по \"n\": ",
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
	/*for (size_t i = 0; i < count; i++)
	{
		cout << ch;
	}
	cout << endl;*/

	cout << string(count, ch) << endl;
};

//##
// Вывод таблицы труб
void PrintTablePipes(const vector <Pipe>& vectorPipes)
{
	PrintChar('-', 131);
	cout << "|" << setw(20) << "ID" << setw(30) << "LENGTH" << setw(30) << "DIAMETER" << setw(30) << "REPAIR" << setw(20) << "|" << endl;
	PrintChar('-', 131);
	for (const auto& p : vectorPipes)
	{
		cout << "|" << setw(20) << p.id << setw(30) << p.length << setw(30) << p.diameter << setw(30) << (p.repair == true ? "true" : "false") << setw(20) << "|" << endl;
	}
	PrintChar('-', 131);
};


// Вывод таблицы Компрессорных станций
void PrintTableCS(const vector <CompressorStation>& vectorCompressorStations)
{
	PrintChar('-', 172);
	cout << "|" << setw(20) << "ID" << setw(31) << "NAME" << setw(30) << "CountWorkShops" << setw(40) << "CountWorkShopsInOperation" << setw(30) << "EFFECTIVENESS" << setw(20) << "|" << endl;
	PrintChar('-', 172);
	for (const auto& cs : vectorCompressorStations)
	{
		cout << "|" << setw(20) << cs.id << setw(31) << cs.name << setw(30) << cs.countWorkShops << setw(40) << cs.countWorkShopsInOperation << setw(30) << cs.effectiveness << setw(20) << "|" << endl;
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

		cout << "Изначальное состояние трубы: " 
			<< (vectorPipes[localId - 1].repair ? "в ремонте" : "не в ремонте") 
			<< endl;

		vectorPipes[localId - 1].repair = GetBool("Укажите новое состояние для трубы, если она в ремонте, то нажмите \"y\" на клавиатуре, если же нет, кликните по \"n\": ",
			"\nНеизвестная команда! Повторите ввод по указанным выше правилам, кликните по \"y\", если да, по \"n\", если нет: ");
		query = GetBool("\n\nХотите ли вы продолжить редактировать трубы, если да, то кликните \"y\", если же нет, то нажмите на \"n\": ",
			"\nНеизвестная команда! Повторите ввод по указанным выше правилам, кликните по \"y\", если да, по \"n\", если нет: ");
		if (!query)
			break;
	}
};


// Редактирование Компрессорных станций
void ChangeCS(vector <CompressorStation>& vectorCompressorStations)
{
	cout << "Всего добавлено компрессорных станций: " << size(vectorCompressorStations) << endl;
	if (size(vectorCompressorStations) == 0)
	{
		PrintErrorText("Вы не добавили ни одной компрессорной станции, редактирование недоступно!");
		CheckPressEscape("\n\nЧтобы выйти в меню, нажмите ESC: ", "\nКоманда не распознана, нажмите ESC на клавиатуре, если хотите вернуться в меню!");
		return;
	}
	while (true)
	{
		size_t localId = GetValue("\nВведите номер (id) компрессорной станции, которую вы бы хотели редактировать (id не должен превышать общее количество компрессорных станций): ",
			"Вы ввели недопустимое значение, id трубы не должен превышать общее количество компрессорных станций, а также он является натуральным числом!!!", 
			1, size(vectorCompressorStations));
		cout << "Количество цехов у данной компрессорной станции: " << vectorCompressorStations[localId - 1].countWorkShops << endl;
		cout << "Количество цехов в работе у данной компрессорной станции: " << vectorCompressorStations[localId - 1].countWorkShopsInOperation << endl;
		vectorCompressorStations[localId - 1].countWorkShopsInOperation = GetValue("Введите новое количество цехов в работе (оно не должно превышать общее количество цехов): ",
			"Ошибка!!! Количество цехов это целое число, без посторонних символов, ввиде букв, точек, а также число не должно превышать общее количество цехов.", 
			0, vectorCompressorStations[localId - 1].countWorkShops, true);
		bool query = GetBool("\n\nХотите ли вы продолжить редактировать компрессоные станции, если да, то кликните \"y\", если же нет, то нажмите на \"n\": ",
			"\nНеизвестная команда! Повторите ввод по указанным выше правилам, кликните по \"y\", если да, по \"n\", если нет: ");
		if (query != true)
			break;
	}
};


// Сохранение данных в файл
void SaveData(vector <Pipe>& vectorPipes, vector <CompressorStation>& vectorCompressorStations)
{
	ofstream fout;
	fout.open("data.txt");
	size_t percent = 0;
	if (fout.is_open())
	{
		for (size_t i = 0; i < size(vectorPipes); i++)
		{
			fout << vectorPipes[i].length << endl
				<< vectorPipes[i].diameter << endl
				<< vectorPipes[i].repair << endl;
		}
		fout << ' ' << endl;
		for (size_t i = 0; i < size(vectorCompressorStations); i++)
		{
			fout << vectorCompressorStations[i].name << endl
				<< vectorCompressorStations[i].countWorkShops << endl
				<< vectorCompressorStations[i].countWorkShopsInOperation << endl
				<< vectorCompressorStations[i].effectiveness << endl;
		}
		fout.close();
		while (percent <= 100)
		{
			cout << "\t\t\t\t\t\t" << "     Прогресс: " << percent++ << "%";
			cout << '\r';
			Sleep(20);
		}
	}
	else
	{
		PrintErrorText("\nОШИБКА!!! Файл по указанному пути не найден, либо он не существует!");
		Sleep(3000);
	}
};


// Загрузка данных из файла
void UploadData(vector <Pipe>& vectorPipes, vector <CompressorStation>& vectorCompressorStations)
{
	ifstream fin;
	fin.open("data.txt");
	size_t percent = 0;
	if (fin.is_open())
	{
		if (fin.peek() != -1)
		{
			while (fin.peek() != ' ')
			{
				Pipe newPipe;
				newPipe.id = size(vectorPipes);
				fin >> newPipe.length;
				fin >> newPipe.diameter;
				fin >> newPipe.repair;
				vectorPipes.push_back(newPipe);
				fin.ignore(1000, '\n');
			}
			fin.ignore(1000, '\n');
			while (fin.peek() != -1)
			{
				CompressorStation newCompressorStation;
				newCompressorStation.id = size(vectorCompressorStations);
				getline(fin, newCompressorStation.name);
				fin >> newCompressorStation.countWorkShops;
				fin >> newCompressorStation.countWorkShopsInOperation;
				fin >> newCompressorStation.effectiveness;
				vectorCompressorStations.push_back(newCompressorStation);
				fin.ignore(1000, '\n');
			}
			fin.close();
			while (percent <= 100)
			{
				cout << "\t\t\t\t\t\t" << "     Прогресс: " << percent++ << "%";
				cout << '\r';
				Sleep(20);
			}
		}
		else
		{
			PrintErrorText("\nНельзя загружать данные из пустого файла, сначала нужно сохранить там данные!!!");
			Sleep(3000);
		}
	}
	else
	{
		PrintErrorText("\nОШИБКА!!! Файл по указанному пути не найден, либо он не существует!");
		Sleep(3000);
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
	vector <Pipe> vectorPipes;
	vector <CompressorStation> vectorCompressorStations;
	while (true)
	{
		PrintMenu();
		switch (_getch())
		{
		case '1':
		{
			system("CLS");
			PrintTitle("\t\t\t\t\t\tИНИЦИАЛИЗАЦИЯ ТРУБЫ");
			Pipe NewPipe = CreatePipe(size(vectorPipes) + 1);
			vectorPipes.push_back(NewPipe);
			break;
		}
		case '2':
		{
			system("CLS");
			PrintTitle("\t\t\t\t\tИНИЦИАЛИЗАЦИЯ КОМПРЕССОРНОЙ СТАНЦИИ");
			CompressorStation NewComressorStation = CreateCompressorStation(size(vectorCompressorStations) + 1);
			vectorCompressorStations.push_back(NewComressorStation);
			break;
		}
		case '3':
		{
			system("ClS");
			PrintTitle("\n\t\t\t\t\t\t\tТАБЛИЦА ТРУБ\n");
			PrintTablePipes(vectorPipes);
			PrintTitle("\n\n\n\n\t\t\t\t\t\t\t\tТАБЛИЦА КОМПРЕССОРНЫХ СТАНЦИЙ\n");
			PrintTableCS(vectorCompressorStations);
			CheckPressEscape("\n\n\nЧтобы выйти в меню, нажмите ESC: ", "\nКоманда не распознана, нажмите ESC на клавиатуре, если хотите вернуться в меню!");
			break;
		}
		case '4':
		{
			system("CLS");
			PrintTitle("\n\t\t\t\t\tРЕДАКТИРОВАНИЕ ТРУБ\n");
			ChangePipe(vectorPipes);
			break;
		}
		case '5':
		{
			system("CLS");
			PrintTitle("\n\t\t\t\t\tРЕДАКТИРОВАНИЕ КОМПРЕССОРНЫХ СТАНЦИЙ\n");
			ChangeCS(vectorCompressorStations);
			break;
		}
		case '6':
		{
			system("CLS");
			PrintTitle("\n\t\t\t\t\t\tСОХРАНЕНИЕ ДАННЫХ В ФАЙЛ\n");
			SaveData(vectorPipes, vectorCompressorStations);
			break;
		}
		case '7':
		{
			system("CLS");
			PrintTitle("\n\t\t\t\t\t\tЗАГРУЗКА ДАННЫХ ИЗ ФАЙЛА\n");
			UploadData(vectorPipes, vectorCompressorStations);
			break;
		}
		case '0':
		{
			system("CLS");
			PrintTitle("\n\tИтак, вы нажали на выход, на этом программа завершила свой сеанс работы.\n\t\t\t\tДо скорой встречи! :)");
			Sleep(5000);
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