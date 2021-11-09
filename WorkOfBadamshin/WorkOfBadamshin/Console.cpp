#include <iostream>
#include <Windows.h>
#include "Console.h"

// ����� ������� ����������� ���������� ���
void Console::PrintChar(char ch, size_t count)
{
	std::cout << std::string(count, ch) << std::endl;
};


// ����� ���� �� �������
void Console::PrintMenu()
{
	std::cout << "����� ���� ���� ���������, �������� ���� �� ��������!" << std::endl
		<< "1. �������� �����" << std::endl
		<< "2. �������� ��" << std::endl
		<< "3. �������� ���� ��������" << std::endl
		<< "4. ������������� �����" << std::endl
		<< "5. ������������� ��" << std::endl
		<< "6. ���������" << std::endl
		<< "7. ���������" << std::endl
		<< "8. ������� �����" << std::endl
		<< "9. ������� ��" << std::endl
		<< "a. �������� �������������� ����" << std::endl
		<< "b. �������� �������������� ��" << std::endl
		<< "0. �����" << std::endl
		<< "����, ������� �� ������ ������� �� ���������� ";
}


// ����� ���������� � ���������� ������� �����
void Console::PrintTitleText(std::string textTitle)
{
	SetConsoleTextAttribute(myHandle, FOREGROUND_GREEN);
	std::cout << textTitle << std::endl;
	SetConsoleTextAttribute(myHandle, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
}


// ����� ������ � ���������� ������ ����� ������
void Console::PrintErrorText(std::string textError)
{
	SetConsoleTextAttribute(myHandle, FOREGROUND_RED | FOREGROUND_GREEN);
	std::cout << textError << std::endl;
	SetConsoleTextAttribute(myHandle, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
}

// ��������� ������ �������
void Console::ChangeConsoleFont(short width, short height)
{
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = width;
	cfi.dwFontSize.Y = height;
	cfi.FontWeight = FW_REGULAR;
	SetCurrentConsoleFontEx(myHandle, FALSE, &cfi);
}

// ��������� �������� ����� � �������
void Console::SetRusLocale()
{
	setlocale(LC_ALL, "Rus");
}

// ��������� ��������� ������� ����������� ����
void Console::SetTitleConsoleWindow()
{
	SetConsoleTitle(L"������������ ������, ��-20-05, �������� �����");
}
