#include <iostream>
#include <Windows.h>
#include "Console.h"

// Вывод символа определённое количество раз
void Console::PrintChar(char ch, size_t count)
{
	std::cout << std::string(count, ch) << std::endl;
};


// Вывод меню на консоль
void Console::PrintMenu()
{
	std::cout << "Перед вами меню программы, выберите одну из операций!" << std::endl
		<< "1. Добавить трубу" << std::endl
		<< "2. Добавить КС" << std::endl
		<< "3. Просмотр всех объектов" << std::endl
		<< "4. Редактировать трубу" << std::endl
		<< "5. Редактировать КС" << std::endl
		<< "6. Сохранить" << std::endl
		<< "7. Загрузить" << std::endl
		<< "8. Удалить трубу" << std::endl
		<< "9. Удалить КС" << std::endl
		<< "a. Пакетное редактирование труб" << std::endl
		<< "b. Пакетное редактирование КС" << std::endl
		<< "0. Выход" << std::endl
		<< "Итак, нажмите на нужную клавишу на клавиатуре ";
}


// Вывод заголовков с установкой зелёного цвета
void Console::PrintTitleText(std::string textTitle)
{
	SetConsoleTextAttribute(myHandle, FOREGROUND_GREEN);
	std::cout << textTitle << std::endl;
	SetConsoleTextAttribute(myHandle, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
}


// Вывод ошибки с установкой жёлтого цвета текста
void Console::PrintErrorText(std::string textError)
{
	SetConsoleTextAttribute(myHandle, FOREGROUND_RED | FOREGROUND_GREEN);
	std::cout << textError << std::endl;
	SetConsoleTextAttribute(myHandle, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
}

// Изменение шрифта консоли
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

// Установка русского языка в консоли
void Console::SetRusLocale()
{
	setlocale(LC_ALL, "Rus");
}

// Установка титульной надписи консольного окна
void Console::SetTitleConsoleWindow()
{
	SetConsoleTitle(L"Лабораторная работа, АА-20-05, Бадамшин Марат");
}
