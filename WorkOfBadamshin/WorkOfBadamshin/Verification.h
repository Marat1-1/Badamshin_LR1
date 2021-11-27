#include <string>
#include <iostream>
#include <conio.h>
#include <vector>
#include "Console.h"

#ifndef VERIFICATION_H
#define VERIFICATION_H

namespace verification
{

	bool CheckCountSpace(std::string);
	std::string GetStringValue(std::string, std::string, size_t);
	bool GetBoolValue(std::string, std::string);
	void GetPressEscape(std::string, std::string);
	template <typename T>
	T GetNumericValue(std::string textRequest, std::string textError, T minValue, T maxValue);
	template <typename T>
	std::vector<T> GetMultipleNumericValues(std::string textRequest, std::string textError);
}

// ќжидание ввода числа
template <typename T>
T verification::GetNumericValue(std::string textRequest, std::string textError, T minValue, T maxValue)
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
				Console::PrintErrorText(textError);
		}
		else
		{
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			Console::PrintErrorText(textError);
		}
	}
}

// ќжидание ввода чисел
template <typename T>
std::vector<T> verification::GetMultipleNumericValues(std::string textRequest, std::string textError)
{
	std::vector<T> resultVector;
	T value;
	bool flag = true;
	while (flag)
	{
		flag = false;
		std::cout << textRequest;
		while(true)
		{
			std::cin >> value;
			if (std::cin.good())
				resultVector.push_back(value);
			else
			{
				Console::PrintErrorText(textError);
				resultVector.clear();
				std::cin.clear();
				std::cin.ignore(1000, '\n');
				flag = true;
				break;
			}
			if (std::cin.peek() == '\n')
				break;
		}
	}
	return resultVector;
}

#endif // !VERIFICATION_H