#include <iostream>
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
		<< "0. Выход" << endl;
};

// Структуры Трубы и КС
struct Pipe
{
	string id;
	int length;
	int diameter;
	bool repair;
};

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
	setlocale(LC_ALL, "Rus");
	PrintMenu();
}