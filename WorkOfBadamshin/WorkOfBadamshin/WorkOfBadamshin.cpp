#include <ctime>
#include <conio.h>
#include "Console.h"
#include "GasTransmissionNetwork.h"
#include "Verification.h"

// Точка входа в программу
int main()
{
	Console::SetRusLocale();
	Console::SetTitleConsoleWindow();
	Console::ChangeConsoleFont(0, 20);
	GasTransmissionNetwork newNetwork;
	while (true)
	{
		Console::PrintMenu();
		switch (_getch())
		{
		case '1':
		{
			system("CLS");
			Console::PrintTitleText("\t\t\t\t\t\tИНИЦИАЛИЗАЦИЯ ТРУБЫ");
			newNetwork.AddPipe();
			break;
		}
		case '2':
		{
			system("CLS");
			Console::PrintTitleText("\t\t\t\t\tИНИЦИАЛИЗАЦИЯ КОМПРЕССОРНОЙ СТАНЦИИ");
			newNetwork.AddCS();
			break;
		}
		case '3':
		{
			system("ClS");
			Console::PrintTitleText("\n\t\t\t\t\t\t\tПРОСМОТР ВСЕХ ТРУБ\n");
			newNetwork.PrintTablePipes();
			Console::PrintTitleText("\n\n\n\n\t\t\t\t\t\t\tПРОСМОТР ВСЕХ КОМПРЕССОРНЫХ СТАНЦИЙ\n");
			newNetwork.PrintTableCS();
			verification::GetPressEscape("\n\n\nЧтобы выйти в меню, нажмите ESC: ", "\nКоманда не распознана, нажмите ESC на клавиатуре, если хотите вернуться в меню!");
			break;
		}
		case '4':
		{
			system("CLS");
			Console::PrintTitleText("\n\t\t\t\t\tРЕДАКТИРОВАНИЕ ТРУБ\n");
			newNetwork.ChangePipe();
			break;
		}
		case '5':
		{
			system("CLS");
			Console::PrintTitleText("\n\t\t\t\t\tРЕДАКТИРОВАНИЕ КОМПРЕССОРНЫХ СТАНЦИЙ\n");
			newNetwork.ChangeCS();
			break;
		}
		case '6':
		{
			system("CLS");
			Console::PrintTitleText("\n\t\tСОХРАНЕНИЕ ДАННЫХ В ФАЙЛ\n");
			std::string fileName = verification::GetStringValue("Введите имя файла, в который вы хотели бы сохранить данные (.txt, максимум 30 символов): ",
				"Ошибка!!! Название файла не может состоять только из пробелов или пустой строки и иметь длину больше чем 30 символов!!!", 30);
			std::ofstream fout(fileName);
			if (fout.is_open())
			{
				newNetwork.SaveToFilePipeCollection(fout);
				fout << ' ' << std::endl;
				newNetwork.SaveToFileCSCollection(fout);
			}
			else
				Console::PrintErrorText("\nОШИБКА!!! Файл по указанному пути не найден, либо он не существует!");
			fout.close();
			verification::GetPressEscape("\n\nЧтобы выйти в меню, нажмите ESC: ", "\nКоманда не распознана, нажмите ESC на клавиатуре, если хотите вернуться в меню!");
			break;
		}
		case '7':
		{
			system("CLS");
			Console::PrintTitleText("\n\t\tЗАГРУЗКА ДАННЫХ ИЗ ФАЙЛА\n");
			std::string fileName = verification::GetStringValue("Введите имя файла, в который вы хотели бы сохранить данные (.txt, максимум 30 символов): ",
				"Ошибка!!! Название файла не может состоять только из пробелов или пустой строки и иметь длину больше чем 30 символов!!!", 30);
			std::ifstream fin(fileName);
			if (fin.is_open())
			{
				if (fin.peek() != -1)
				{
					newNetwork.DownloadFromFilePipeCollection(fin);
					fin.ignore(10000, '\n');
					newNetwork.DownloadFromFileCSCollection(fin);
				}
				else
				{
					Console::PrintErrorText("\nНельзя загружать данные из пустого файла, сначала нужно сохранить там данные!!!");
				}
			}
			else
				Console::PrintErrorText("\nОШИБКА!!! Файл по указанному пути не найден, либо он не существует!");
			fin.close();
			system("pause");
			break;
		}
		case '8':
		{
			system("CLS");
			Console::PrintTitleText("\n\t\tУДАЛЕНИЕ ТРУБЫ");
			newNetwork.DeletePipe();
			break;
		}
		case '9':
		{
			system("CLS");
			Console::PrintTitleText("\n\t\tУДАЛЕНИЕ КС");
			newNetwork.DeleteCS();
			break;
		}
		case 'a':
		{
			system("CLS");
			Console::PrintTitleText("\n\t\t\tПАКЕТНОЕ РЕДАКТИРОВАНИЕ ТРУБ");
			newNetwork.BatchChangePipeCollection();
			break;
		}
		case 'b':
		{
			system("CLS");
			Console::PrintTitleText("\n\t\t\t\tПАКЕТНОЕ РЕДАКТИРОВАНИЕ КС");
			newNetwork.BatchChangeCSCollection();
			break;
		}
		case 'c':
		{
			system("CLS");
			newNetwork.manageNetwork();
			break;
		}
		case '0':
		{
			system("CLS");
			Console::PrintTitleText("\n\tИтак, вы нажали на выход, на этом программа завершила свой сеанс работы.\n\t\t\t\tДо скорой встречи! :)");
			Sleep(5000);
			return 0;
		}
		default:
		{
			Console::PrintErrorText("\nНекорректный ввод данных!!! Нажмите на число, которое соотвествует команде из списка!!!\nСообщение пропадёт через 3 секунды");
			Sleep(3000);
			break;
		}
		}
		system("CLS");
	}
};