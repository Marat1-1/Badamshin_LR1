#include <iostream>
#include <Windows.h>


#ifndef CONSOLE_H
#define CONSOLE_H

class Console
{
private:
	static HANDLE& myHandle;
public:
	static void PrintChar(char, size_t);
	static void PrintMenu();
	static void PrintTitleText(std::string);
	static void PrintErrorText(std::string);
	static void ChangeConsoleFont(short, short);
	static void SetRusLocale();
	static void SetTitleConsoleWindow();
};

#endif // !CONSOLE_H