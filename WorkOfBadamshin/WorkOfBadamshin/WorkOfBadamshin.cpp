#include <ctime>
#include "ClassElements.h"
#include "Console.h"
#include "Verification_Class.h"
#include "PipeCollection.h"
#include "CompressorStationCollection.h"

// Объявляю счётчики труб и компрессорных станций
size_t Pipe::countPipes = 0;
size_t CompressorStation::countCS = 0;

// Точка входа в программу
int main()
{
	HANDLE myHandle = GetStdHandle(STD_OUTPUT_HANDLE); // для работы с консолью
	Console console(myHandle);
	console.SetRusLocale();
	console.SetTitleConsoleWindow();
	console.ChangeConsoleFont();
	PipeCollection newPipeCollection;
	CompressorStationCollection newCSColletion;
	while (true)
	{
		console.PrintMenu();
		switch (_getch())
		{
		case '1':
		{
			system("CLS");
			console.PrintTitleText("\t\t\t\t\t\tИНИЦИАЛИЗАЦИЯ ТРУБЫ");
			newPipeCollection.AddPipe(console);
			break;
		}
		case '2':
		{
			system("CLS");
			console.PrintTitleText("\t\t\t\t\tИНИЦИАЛИЗАЦИЯ КОМПРЕССОРНОЙ СТАНЦИИ");
			newCSColletion.AddCS(console);
			break;
		}
		case '3':
		{
			VerificationClass<size_t> verification;
			system("ClS");
			console.PrintTitleText("\n\t\t\t\t\t\t\tТАБЛИЦА ТРУБ\n");
			newPipeCollection.PrintTablePipes(console);
			console.PrintTitleText("\n\n\n\n\t\t\t\t\t\t\t\tТАБЛИЦА КОМПРЕССОРНЫХ СТАНЦИЙ\n");
			newCSColletion.PrintTableCS(console);
			verification.GetPressEscape("\n\n\nЧтобы выйти в меню, нажмите ESC: ", "\nКоманда не распознана, нажмите ESC на клавиатуре, если хотите вернуться в меню!", console);
			break;
		}
		case '4':
		{
			system("CLS");
			console.PrintTitleText("\n\t\t\t\t\tРЕДАКТИРОВАНИЕ ТРУБ\n");
			newPipeCollection.ChangePipe(console);
			break;
		}
		case '5':
		{
			system("CLS");
			console.PrintTitleText("\n\t\t\t\t\tРЕДАКТИРОВАНИЕ КОМПРЕССОРНЫХ СТАНЦИЙ\n");
			newCSColletion.ChangeCS(console);
			break;
		}
		case '6':
		{
			system("CLS");
			console.PrintTitleText("\n\t\tСОХРАНЕНИЕ ДАННЫХ В ФАЙЛ\n");
			std::ofstream fout("data.txt");
			newPipeCollection.SaveToFile(fout, console);
			fout << ' ' << std::endl;
			newCSColletion.SaveToFile(fout, console);
			fout.close();
			system("pause");
			break;
		}
		case '7':
		{
			system("CLS");
			console.PrintTitleText("\n\t\tЗАГРУЗКА ДАННЫХ ИЗ ФАЙЛА\n");
			std::ifstream fin("data.txt");
			newPipeCollection.DownloadFromFile(fin, console);
			fin.ignore(10000, '\n');
			newCSColletion.DownloadFromFile(fin, console);
			fin.close();
			system("pause");
			break;
		}
		case '8':
		{
			system("CLS");
			console.PrintTitleText("\n\t\tУДАЛЕНИЕ ТРУБЫ");
			newPipeCollection.DeletePipe(console);
			break;
		}
		case '9':
		{
			system("CLS");
			console.PrintTitleText("\n\t\tУДАЛЕНИЕ КС");
			newCSColletion.DeleteCS(console);
			break;
		}
		case '0':
		{
			system("CLS");
			console.PrintTitleText("\n\tИтак, вы нажали на выход, на этом программа завершила свой сеанс работы.\n\t\t\t\tДо скорой встречи! :)");
			Sleep(5000);
			return 0;
		}
		default:
			console.PrintErrorText("\nНекорректный ввод данных!!! Нажмите на число, которое соотвествует команде из списка!!!\nСообщение пропадёт через 3 секунды");
			Sleep(3000);
			break;
		}
		system("CLS");
	}
};