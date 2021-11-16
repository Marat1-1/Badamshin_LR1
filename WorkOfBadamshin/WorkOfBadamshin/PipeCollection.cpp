#include "PipeCollection.h"
#include "Verification.h"
#include <iomanip>

// Добавление трубы в список
void PipeCollection::AddPipe()
{
	Pipe pipe;
	pipeCollection.emplace(pipe.id, pipe);
}

// Редактирование трубы
void PipeCollection::ChangePipe()
{
	size_t changeId;
	bool query;
	std::cout << "Всего добавлено труб: " << size(pipeCollection) << std::endl
		<< "Id доступные для редактирования: ";
	for (const auto& el : pipeCollection)
		std::cout << el.first << "  ";
	std::cout << std::endl;
	if (pipeCollection.empty())
	{
		Console::PrintErrorText("Вы не добавили ни одной трубы, редактирование недоступно!");
		verification::GetPressEscape("\n\nЧтобы выйти в меню, нажмите ESC: ", "\nКоманда не распознана, нажмите ESC на клавиатуре, если хотите вернуться в меню!");
		return;
	}
	while (true)
	{
		changeId = verification::GetNumericValue<size_t>("\nВведите номер id трубы, которую вы бы хотели редактировать: ",
			"Ошибка! Вы ввели недопустимое значение, возможно вы ввели несуществующий id или же произвели некорректный ввод, помните id это положительное, целое число!!!", 1, Pipe::maxIdPipe);
		if (pipeCollection.find(changeId) != pipeCollection.end())
		{
			std::cout << "Изначальное состояние трубы: "
				<< (pipeCollection[changeId].repair ? "в ремонте" : "не в ремонте")
				<< std::endl;
			pipeCollection[changeId].GhangePipe();
		}
		else
			Console::PrintErrorText("По указанному id не найдено ни одной трубы!!!");
		query = verification::GetBoolValue("\n\nХотите ли вы продолжить редактировать трубы, если да, то кликните \"y\", если же нет, то нажмите на \"n\": ",
			"\nНеизвестная команда! Повторите ввод по указанным выше правилам, кликните по \"y\", если да, по \"n\", если нет!!!");
		if (!query)
			break;
	}
}

// Вывод таблицы труб на экран (вектор самого класса)
void PipeCollection::PrintTablePipes()
{
	int tabulation_20 = 20, tabulation_30 = 30, tableWidth = 131;
	Console::PrintTitleText("\n\t\t\t\tТаблица труб");
	Console::PrintChar('-', tableWidth);
	std::cout << "|" << std::setw(tabulation_20) << "ID" << std::setw(tabulation_30) << "LENGTH" << std::setw(tabulation_30) << "DIAMETER" << std::setw(tabulation_30) << "REPAIR" << std::setw(tabulation_20) << "|" << std::endl;
	Console::PrintChar('-', tableWidth);
	for (const auto& p : pipeCollection)
	{
		std::cout << "|" << std::setw(tabulation_20) << p.second.id << std::setw(tabulation_30) << p.second.length << std::setw(tabulation_30) << p.second.diameter << std::setw(tabulation_30) << (p.second.repair == true ? "true" : "false") << std::setw(tabulation_20) << "|" << std::endl;
	}
	Console::PrintChar('-', tableWidth);
}

// Вывод таблицы труб на экран, при этом функция выводит любой вектор труб
void PipeCollection::PrintFilterTablePipes()
{
	int tabulation_20 = 20, tabulation_30 = 30, tableWidth = 131;
	Console::PrintTitleText("\n\n\t\tТаблица труб");
	Console::PrintChar('-', tableWidth);
	std::cout << "|" << std::setw(tabulation_20) << "ID" << std::setw(tabulation_30) << "LENGTH" << std::setw(tabulation_30) << "DIAMETER" << std::setw(tabulation_30) << "REPAIR" << std::setw(tabulation_20) << "|" << std::endl;
	Console::PrintChar('-', tableWidth);
	for (const auto& id : vectorIdForFilter)
	{
		std::cout << "|" << std::setw(tabulation_20) << pipeCollection[id].id << std::setw(tabulation_30) << pipeCollection[id].length << std::setw(tabulation_30) << pipeCollection[id].diameter << std::setw(tabulation_30) << (pipeCollection[id].repair == true ? "true" : "false") << std::setw(tabulation_20) << "|" << std::endl;
	}
	Console::PrintChar('-', tableWidth);
}

// Вывод труб в файл
void PipeCollection::SaveToFile(std::ofstream& fout)
{
	size_t percent = 0;
	if (pipeCollection.empty())
	{
		Console::PrintErrorText("Вы не добавили ни одной трубы!");
		return;
	}
	fout << Pipe::maxIdPipe << std::endl;
	for (auto& el : pipeCollection)
		el.second.SaveToFile(fout);
	while (percent <= 100)
	{
		std::cout << "\t\t" << "Сохранение КС: " << percent++ << "%";
		std::cout << '\r';
		Sleep(20);
	}
	Console::PrintTitleText("\n\t\tТрубы сохранены!");
}

// Загрузка труб из файла
void PipeCollection::DownloadFromFile(std::ifstream& fin)
{
	size_t percent = 0;
	if (fin.peek() != -1)
	{
		fin >> Pipe::maxIdPipe;
		while (fin.peek() != ' ' && fin.peek() != -1)
		{
			Pipe pipe(fin);
			pipeCollection.emplace(pipe.id, pipe);
			fin.ignore(1000, '\n');
		}
		while (percent <= 100)
		{
			std::cout << "\t\t" << "Загрузка труб: " << percent++ << "%";
			std::cout << '\r';
			Sleep(20);
		}
		Console::PrintTitleText("\nТрубы загружены!");
	}
	else
	{
		Console::PrintErrorText("\nНельзя загружать данные из пустого файла, сначала нужно сохранить там данные!!!");
	}
}

// Фильтр труб
void PipeCollection::FilterPipe()
{
	bool query;
	query = verification::GetBoolValue("\nЕсли вам нужны трубы, состояние которых: \"В ремонте\", то кликните по \"y\", если же нужны исправные трубы, то кликните по \"n\"",
		"\nНеизвестная команда! Повторите ввод по указанным выше правилам, кликните по \"y\" или же по \"n\"!!!");
	for (const auto& el : pipeCollection)
		if (el.second.repair == query)
			vectorIdForFilter.push_back(el.first);
}

// Удаление труб
void PipeCollection::DeletePipe()
{
	size_t delId; // id трубы, которую нужно удалить
	bool query;
	if (pipeCollection.empty())
	{
		Console::PrintErrorText("Вы не добавили ни одной трубы, удаление недоступно!");
		verification::GetPressEscape("\n\nЧтобы выйти в меню, нажмите ESC: ", "\nКоманда не распознана, нажмите ESC на клавиатуре, если хотите вернуться в меню!");
		return;
	}
	query = verification::GetBoolValue("Нажмите на \"y\", если хотите произвести удаление по одной трубе, на \"n\", если хотите произвести пакетное удаление по фильтру: ",
		"\nНеизвестная команда! Повторите ввод по указанным правилам!!!");
	if (query)
	{
		while (true)
		{
			std::cout << "\n\nВсего труб: " << size(pipeCollection) << std::endl
				<< "Id доступные для удаления: ";
			for (const auto& el : pipeCollection)
				std::cout << el.first << "  ";
			std::cout << std::endl;
			delId = verification::GetNumericValue<size_t>("Введите id трубы, которую вы бы хотели удалить: ",
				"Ошибка! Вы ввели недопустимое значение, возможно вы ввели несуществующий id или же произвели некорректный ввод, помните id это положительное, целое число!!!", 1, Pipe::maxIdPipe);
			if (pipeCollection.find(delId) != pipeCollection.end())
			{
				pipeCollection.erase(delId);
				Console::PrintTitleText("Труба была успешно удалена!");
			}
			else
				Console::PrintErrorText("По указанному id не было найдено ни одной трубы, возможно труба уже была удалена!!!");
			query = verification::GetBoolValue("\n\nХотите ли вы продолжить удалять трубы, если да, то кликните \"y\", если же нет, то нажмите на \"n\": ",
				"\nНеизвестная команда! Повторите ввод по указанным выше правилам, кликните по \"y\", если да, по \"n\", если нет!!!");
			if (!query)
				break;
		}
	}
	else
	{
		FilterPipe();
		if (size(vectorIdForFilter) != 0)
		{
			std::cout << "\n\nБудут удалены следующие трубы:" << std::endl;
			PrintFilterTablePipes();
			for (const auto& i : vectorIdForFilter)
				pipeCollection.erase(i);
			vectorIdForFilter.clear();
			Console::PrintTitleText("\n\nТрубы успешно удалены!");
		}
		else
			Console::PrintErrorText("\nПо вашему фильтру не было найдено ни одной трубы!");
	}
	std::cout << std::endl;
	system("pause");
}

// Пакетное редактирование труб
void PipeCollection::BatchChangePipe()
{
	bool query;
	bool repairStatus;
	if (pipeCollection.empty())
	{
		Console::PrintErrorText("\nВы не добавили ни одной трубы, пакетное редактирование недоступно!");
		verification::GetPressEscape("\n\nЧтобы выйти в меню, нажмите ESC: ", "\nКоманда не распознана, нажмите ESC на клавиатуре, если хотите вернуться в меню!");
		return;
	}
	query = verification::GetBoolValue("\nНажмите на \"y\", если хотите редактировать все трубы, на \"n\", если только определённое подмножество: ",
		"\nОшибка!!! Вы нажали на некорректную кнопку, осуществите ввод по указанным вам правилам!!!");
	if (!query)
	{
		FilterPipe();
		if (size(vectorIdForFilter) != 0)
		{
			PrintFilterTablePipes();
			repairStatus = verification::GetBoolValue("\n\nУкажите новое состояние для выбранных труб, если в ремонте, то нажмите \"y\" на клавиатуре, если же нет, кликните по \"n\": ",
				"\nНеизвестная команда! Повторите ввод по указанным выше правилам, кликните по \"y\", если да, по \"n\", если нет!!!");
			for (const auto& i : vectorIdForFilter)
				pipeCollection[i].repair = repairStatus;
			Console::PrintTitleText("\nТрубы отредактированы!");
		}
		else
			Console::PrintErrorText("\nПо вашему фильтру не было найдено ни одной трубы!");
		vectorIdForFilter.clear();
	}
	else
	{
		PrintTablePipes();
		repairStatus = verification::GetBoolValue("\n\nУкажите новое состояние для выбранных труб, если в ремонте, то нажмите \"y\" на клавиатуре, если же нет, кликните по \"n\": ",
			"\nНеизвестная команда! Повторите ввод по указанным выше правилам, кликните по \"y\", если да, по \"n\", если нет!!!");
		for (auto& el : pipeCollection)
			el.second.repair = repairStatus;
		Console::PrintTitleText("\nТрубы отредактированы!");
	}
	system("pause");
}