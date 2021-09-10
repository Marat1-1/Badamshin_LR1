#include <iostream>
#include <string>
using namespace std;

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
		<< "Нажмите на одну из клавиш чисел на клавиатуре: ";
};

// Проверка корректного ввода данных для команды
bool CheckCommand(string command)
{
	if (!isdigit(command[0]) || size(command) > 1)
		return false;
	return true;
}

// Структура Трубы
struct Pipe
{
	string id;
	int length;
	int diameter;
	bool repair;
};

//Структура КС
struct CompressorStation
{
	string id;
	string name;
	int countWorkShops;
	int countWorkShopsInOperation;
	int effectiveness;
};

int main()
{
	setlocale(LC_ALL, "Russian");
	string command;
	while (true)
	{
		system("CLS");
		PrintMenu();
		cin >> command;
		if (CheckCommand(command))
		{
			switch (stoi(command))
			{
			case 1:
			{
				break;
			}
			case 2:
			{
				break;
			}
			case 3:
			{
				break;
			}
			case 4:
			{
				break;
			}
			case 5:
			{
				break;
			}
			case 6:
			{
				break;
			}
			case 7:
			{
				break;
			}
			case 0:
			{
				return 0;
			}
			}
		}
		else
		{
			cout << "Некорректный ввод данных!!!" << endl;
			cin.get();
		}
	}
}