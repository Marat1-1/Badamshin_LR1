#include "PipeCollection.h"
#include "Verification_Class.h"
#include <iomanip>

// Добавление трубы в список
void PipeCollection::AddPipe(Console& console)
{
	VerificationClass<double> verification;
	Pipe pipe;
	pipe.id = Pipe::countPipes;

	pipe.length = verification.GetNumericValue("Введите длину трубы, размерность - километры, диапазон от 10 до 100 км (необязательно целое число, чтобы отделить дробную часть используйте \".\"): ",
		"Ошибка!!! Вы ввели что-то непонятное.\nДлина трубы может быть либо целым числом, либо числом с плавающей точкой, лежащим в диапазоне от 10 до 100 км, повторите ввод!!!", 10.0, 100.0, console);

	pipe.diameter = verification.GetNumericValue("Введите диаметр трубы, размерность миллиметры, диапазон от 500 до 1420 мм (необязательно целое число, чтобы отделить дробную часть используйте \".\"): ",
		"Ошибка!!! Вы ввели что-то непонятное.\nДиаметр трубы может быть либо целым числом, либо числом с плавающей точкой, лежащим в диапазоне от 500 до 1420 мм, повторите ввод!!!", 500.0, 1420.0, console);

	pipe.repair = verification.GetBoolValue("Укажите находится ли труба в ремонте, если да, то нажмите \"y\" на клавиатуре, если же нет, кликните по \"n\": ",
		"\nНеизвестная команда! Повторите ввод по указанным выше правилам, кликните по \"y\", если да, по \"n\", если нет: ", console);
	vectorPipes.push_back(pipe);
}

// Редактирование трубы
void PipeCollection::ChangePipe(Console& console)
{
	VerificationClass<size_t> verification;
	size_t localId;
	bool query;
	std::cout << "Всего добавлено труб: " << Pipe::countPipes << std::endl;
	if (Pipe::countPipes == 0)
	{
		console.PrintErrorText("Вы не добавили ни одной трубы, редактирование недоступно!");
		verification.GetPressEscape("\n\nЧтобы выйти в меню, нажмите ESC: ", "\nКоманда не распознана, нажмите ESC на клавиатуре, если хотите вернуться в меню!", console);
		return;
	}
	while (true)
	{
		localId = verification.GetNumericValue("\nВведите номер (id) трубы, которую вы бы хотели редактировать (id не должен превышать общее количество труб): ",
			"Вы ввели недопустимое значение, id трубы не должен превышать общее количество труб, а также он является натуральным числом!!!", 1, Pipe::countPipes, console);
		std::cout << "Изначальное состояние трубы: "
			<< (vectorPipes[localId - 1].repair ? "в ремонте" : "не в ремонте")
			<< std::endl;

		vectorPipes[localId - 1].repair = verification.GetBoolValue("Укажите новое состояние для трубы, если она в ремонте, то нажмите \"y\" на клавиатуре, если же нет, кликните по \"n\": ",
			"\nНеизвестная команда! Повторите ввод по указанным выше правилам, кликните по \"y\", если да, по \"n\", если нет: ", console);
		query = verification.GetBoolValue("\n\nХотите ли вы продолжить редактировать трубы, если да, то кликните \"y\", если же нет, то нажмите на \"n\": ",
			"\nНеизвестная команда! Повторите ввод по указанным выше правилам, кликните по \"y\", если да, по \"n\", если нет: ", console);
		if (!query)
			break;
	}
}

// Вывод таблицы труб на экран
void PipeCollection::PrintTablePipes(Console& console)
{
	int tabulation_20 = 20, tabulation_30 = 30, tableWidth = 131;
	console.PrintChar('-', tableWidth);
	std::cout << "|" << std::setw(tabulation_20) << "ID" << std::setw(tabulation_30) << "LENGTH" << std::setw(tabulation_30) << "DIAMETER" << std::setw(tabulation_30) << "REPAIR" << std::setw(tabulation_20) << "|" << std::endl;
	console.PrintChar('-', tableWidth);
	for (const auto& p : vectorPipes)
	{
		std::cout << "|" << std::setw(tabulation_20) << p.id << std::setw(tabulation_30) << p.length << std::setw(tabulation_30) << p.diameter << std::setw(tabulation_30) << (p.repair == true ? "true" : "false") << std::setw(tabulation_20) << "|" << std::endl;
	}
	console.PrintChar('-', tableWidth);
}

// Вывод труб в файл
void PipeCollection::SaveToFile(std::ofstream& fout, Console& console)
{
	size_t percent = 0;
	if (fout.is_open())
	{
		for (const auto& v : vectorPipes)
		{
			fout << v.length << std::endl
				<< v.diameter << std::endl
				<< v.repair << std::endl;
		}
		while (percent <= 100)
		{
			std::cout << "\t\t" << "Сохранение труб: " << percent++ << "%";
			std::cout << '\r';
			Sleep(20);
		}
		console.PrintTitleText("\n\t\tТрубы сохранены!");
	}
	else
	{
		console.PrintErrorText("\nОШИБКА!!! Файл по указанному пути не найден, либо он не существует!");
		Sleep(3000);
	}
}

// Загрузка труб из файла
void PipeCollection::DownloadFromFile(std::ifstream& fin, Console& console)
{
	size_t percent = 0;
	if (fin.is_open())
	{
		if (fin.peek() != -1)
		{
			while (fin.peek() != ' ' && fin.peek() != -1)
			{
				Pipe newPipe;
				newPipe.id = Pipe::countPipes;
				fin >> newPipe.length
					>> newPipe.diameter
					>> newPipe.repair;
				vectorPipes.push_back(newPipe);
				fin.ignore(1000, '\n');
			}
			while (percent <= 100)
			{
				std::cout << "\t\t" << "Загрузка труб: " << percent++ << "%";
				std::cout << '\r';
				Sleep(20);
			}
			console.PrintTitleText("\nТрубы загружены!");
		}
		else
		{
			console.PrintErrorText("\nНельзя загружать данные из пустого файла, сначала нужно сохранить там данные!!!");
			Sleep(3000);
		}
	}
	else
	{
		console.PrintErrorText("\nОШИБКА!!! Файл по указанному пути не найден, либо он не существует!");
		Sleep(3000);
	}
}


// Удаление трубы
void PipeCollection::DeletePipe(Console& console)
{
	VerificationClass<size_t> verification;
	size_t delId; // id труюбы, которую нужно удалить
	const size_t& id = delId; // константная ссылка на id, чтобы работать с итератором
	bool query;
	std::vector<Pipe>::iterator it = vectorPipes.begin();
	if (Pipe::countPipes == 0)
	{
		console.PrintErrorText("Вы не добавили ни одной трубы, удаление недоступно!");
		verification.GetPressEscape("\n\nЧтобы выйти в меню, нажмите ESC: ", "\nКоманда не распознана, нажмите ESC на клавиатуре, если хотите вернуться в меню!", console);
		return;
	}
	while (true)
	{
		std::cout << "\n\nВсего труб: " << Pipe::countPipes << std::endl;
		delId = verification.GetNumericValue("Введите id трубы, которую вы бы хотели удалить (id не должен превышать общее количество труб): ",
			"Вы ввели недопустимое значение, id трубы не должен превышать общее количество труб, а также id это натуральное число!!!", 1, Pipe::countPipes, console);
		it += id - 1;
		Pipe::countPipes--;
		for (auto iter = vectorPipes.erase(it); iter != vectorPipes.end(); iter++)
		{
			(*iter).id--;
		}
		console.PrintTitleText("Труба была успешно удалена!");
		query = verification.GetBoolValue("\n\nХотите ли вы продолжить удалять трубы, если да, то кликните \"y\", если же нет, то нажмите на \"n\": ",
			"\nНеизвестная команда! Повторите ввод по указанным выше правилам, кликните по \"y\", если да, по \"n\", если нет: ", console);
		if (!query)
			break;
	}
}