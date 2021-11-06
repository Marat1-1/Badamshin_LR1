#include <string>
#include <iostream>
#include <conio.h>
#include "Console.h"

#ifndef VERIFICATION_CLASS_H
#define VERIFICATION_CLASS_H

template <typename T>
class VerificationClass
{
private:
	bool CheckCountSpace(std::string);

public:
	std::string GetStringValue(std::string, std::string, size_t, Console);
	T GetNumericValue(std::string, std::string, T, T, Console);
	bool GetBoolValue(std::string, std::string, Console);
	void GetPressEscape(std::string, std::string, Console);
};


// Из-за того, что класс шаблонный пришлось сделать так
// Проверка, не состоит ли строка только из пробелов
template <typename T>
bool VerificationClass<T>::CheckCountSpace(std::string str)
{
	int i = 0;
	while (i != size(str))
	{
		if (str[i] != ' ')
			return true;
		++i;
	}
	return false;
}


// Ожидание ввода Строки в определённое количество символов
template <typename T>
std::string VerificationClass<T>::GetStringValue(std::string textRequest, std::string textError, size_t length, Console console)
{
	std::string nameCS;
	while (true)
	{
		std::cout << textRequest;
		std::cin.seekg(std::cin.eof());
		getline(std::cin, nameCS);
		if (nameCS != "" && CheckCountSpace(nameCS) && size(nameCS) <= length)
			return nameCS;
		else
			console.PrintErrorText(textError);
	}
}

// Ожидание ввода значений разных числовых типов, double, int и т.д.
template <typename T>
T VerificationClass<T>::GetNumericValue(std::string textRequest, std::string textError, T minValue, T maxValue, Console console)
{
	T value;
	while (true)
	{
		std::cout << textRequest;
		std::cin >> value;
		if (std::cin.good() && std::cin.peek() == '\n')
		{
			if (value >= minValue && value <= maxValue)
				return value;
			else
				console.PrintErrorText(textError);
		}
		else
		{
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			console.PrintErrorText(textError);
		}
	}
}

// Ожидание ввода значений "ИСТИНА" или "ЛОЖЬ"
template <typename T>
bool VerificationClass<T>::GetBoolValue(std::string textRequest, std::string textError, Console console)
{
	char stateRepair;
	std::cout << textRequest;
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
			console.PrintErrorText(textError);
	}
}

// Ожидание нажатия esc
template <typename T>
void VerificationClass<T>::GetPressEscape(std::string textRequest, std::string textError, Console console)
{
	while (true)
	{
		std::cout << textRequest;
		char escCommand;
		escCommand = _getch();
		if (escCommand == '\x1b')
			break;
		else
			console.PrintErrorText(textError);
	}
}


#endif // !VERIFICATION_CLASS_H