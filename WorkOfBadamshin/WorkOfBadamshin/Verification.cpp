#include "Verification.h"


// Проверка не состоит ли строка только из пробелов
bool verification::CheckCountSpace(std::string str)
{
	int i = 0;
	while (i != str.size())
	{
		if (str[i] != ' ')
			return true;
		++i;
	}
	return false;
}

// Ожидание ввода Строки в определённое количество символов
std::string verification::GetStringValue(std::string textRequest, std::string textError, size_t length)
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
			Console::PrintErrorText(textError);
	}
}

// Ожидание ввода значений "ИСТИНА" или "ЛОЖЬ"
bool verification::GetBoolValue(std::string textRequest, std::string textError)
{
	char stateRepair;
	while (true)
	{
		std::cout << textRequest;
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
			Console::PrintErrorText(textError);
	}
}

// Ожидание нажатия esc
void verification::GetPressEscape(std::string textRequest, std::string textError)
{
	while (true)
	{
		std::cout << textRequest;
		char escCommand;
		escCommand = _getch();
		if (escCommand == '\x1b')
			break;
		else
			Console::PrintErrorText(textError);
	}
}