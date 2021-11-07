#include <iostream>
#include <Windows.h>
#include "ClassElements.h"

#ifndef CONSOLE_H
#define CONSOLE_H

class Console
{
private:
	HANDLE myHandle;
public:
	void PrintChar(char, size_t);
	void PrintMenu();
	void PrintTitleText(std::string);
	void PrintErrorText(std::string);
	void ChangeConsoleFont();
	void SetRusLocale();
	void SetTitleConsoleWindow();
	Console(HANDLE& myHandle_) : myHandle(myHandle_) {};
};

#endif // !CONSOLE_H