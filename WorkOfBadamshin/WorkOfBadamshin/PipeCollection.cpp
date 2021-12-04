#include "PipeCollection.h"
#include "Verification.h"
#include <iomanip>


// Счётчик id
size_t Pipe::maxIdPipe = 0;

// Добавление трубы в список
void PipeCollection::Add()
{
	Pipe pipe;
	pipeCollection.emplace(pipe.id, pipe);
}

// Редактирование трубы
void PipeCollection::Change()
{
	size_t changeId;
	bool query;
	std::cout << "Всего добавлено труб: " << pipeCollection.size() << std::endl
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
void PipeCollection::PrintTable()
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
void PipeCollection::PrintFilterTable(std::vector<size_t>& vectorId)
{
	int tabulation_20 = 20, tabulation_30 = 30, tableWidth = 131;
	Console::PrintTitleText("\n\n\t\tТаблица труб");
	Console::PrintChar('-', tableWidth);
	std::cout << "|" << std::setw(tabulation_20) << "ID" << std::setw(tabulation_30) << "LENGTH" << std::setw(tabulation_30) << "DIAMETER" << std::setw(tabulation_30) << "REPAIR" << std::setw(tabulation_20) << "|" << std::endl;
	Console::PrintChar('-', tableWidth);
	for (const auto& id : vectorId)
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
	size_t maxId;
	fin >> maxId;
	if (maxId > Pipe::maxIdPipe)
		Pipe::maxIdPipe = maxId;
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

// Фильтр труб
void PipeCollection::Filter()
{
	bool query;
	query = verification::GetBoolValue("\nЕсли вам нужны трубы, состояние которых: \"В ремонте\", то кликните по \"y\", если же нужны исправные трубы, то кликните по \"n\"",
		"\nНеизвестная команда! Повторите ввод по указанным выше правилам, кликните по \"y\" или же по \"n\"!!!");
	for (const auto& el : pipeCollection)
		if (el.second.repair == query)
			vectorIdForFilter.push_back(el.first);
}

// Удаление труб
void PipeCollection::Delete()
{
	if (pipeCollection.empty())
	{
		Console::PrintErrorText("Вы не добавили ни одной трубы, удаление недоступно!");
		verification::GetPressEscape("\n\nЧтобы выйти в меню, нажмите ESC: ", "\nКоманда не распознана, нажмите ESC на клавиатуре, если хотите вернуться в меню!");
		return;
	}
	bool query;
	query = verification::GetBoolValue("\nНажмите на \"y\", если хотите произвести удаление по одной трубе, на \"n\", если хотите произвести пакетное удаление по фильтру: ",
		"\nНеизвестная команда! Повторите ввод по указанным правилам!!!");
	if (query) // Удаление по одной трубе
	{
		std::cout << "\n\nВсего Труб: " << pipeCollection.size() << std::endl
			<< "Id доступные для удаления: ";
		for (const auto& el : pipeCollection)
			std::cout << el.first << "  ";
		std::set<size_t> setIdForDelete = verification::GetMultipleNumericValues<size_t>(
			"\nВведите через пробел id труб, которые хотели бы удалить: ",
			"\nОшибка, вы ввели недопустимый формат, повторите ввод заново!");
		for (const auto id : setIdForDelete)
		{
			if (pipeCollection.find(id) != pipeCollection.end())
			{
				pipeCollection.erase(id);
				Console::PrintTitleText("Труба с id = " + std::to_string(id) + " была удалена!\n");
			}
			else
				Console::PrintErrorText("Труба с id = " + std::to_string(id) + " не была найдена в списке всех труб!\n");
		}
	}
	else // Пакетное удаление
	{
		Filter();
		if (!vectorIdForFilter.empty())
		{
			std::cout << "\n\nТрубы, полученные после фильтрации:" << std::endl;
			PrintFilterTable(vectorIdForFilter);
			query = verification::GetBoolValue("\nЕсли хотите удалить все отфильтрованные трубы, нажмите \"y\", если часть из них, то нажмите \"n\": ",
				"\nНеизвестная команда! Повторите ввод по указанным выше правилам!!!");
			if (query) // Удалить все отфильтрованные трубы
			{
				for (const auto& i : vectorIdForFilter)
					pipeCollection.erase(i);
				Console::PrintTitleText("\nТрубы были успешно удалены!");
			}
			else // Удалить часть отфильтрованных труб
			{
				std::set<size_t> setIdForDelete = verification::GetMultipleNumericValues<size_t>(
					"\nВведите через пробел id труб, которые хотели бы удалить: ",
					"\nОшибка, вы ввели недопустимый формат, повторите ввод заново!");
				for (auto id : setIdForDelete)
				{
					auto it = std::find(vectorIdForFilter.begin(), vectorIdForFilter.end(), id);
					if (it != vectorIdForFilter.end())
					{
						pipeCollection.erase(id);
						Console::PrintTitleText("Труба с id = " + std::to_string(id) + " была удалена!\n");
					}
					else
						Console::PrintErrorText("Труба с id = " + std::to_string(id) + " не была найдена в списке отфильтрованных труб!\n");
				}
			}
			vectorIdForFilter.clear();
		}
		else
			Console::PrintErrorText("\nПо вашему фильтру не было найдено ни одной трубы!");
	}
	std::cout << std::endl;
	system("pause");
}

// Пакетное редактирование труб
void PipeCollection::BatchChange()
{
	if (pipeCollection.empty())
	{
		Console::PrintErrorText("\nВы не добавили ни одной трубы, пакетное редактирование недоступно!");
		verification::GetPressEscape("\n\nЧтобы выйти в меню, нажмите ESC: ", "\nКоманда не распознана, нажмите ESC на клавиатуре, если хотите вернуться в меню!");
		return;
	}
	bool query;
	bool repairStatus;
	query = verification::GetBoolValue("\nНажмите на \"y\", если хотите редактировать все трубы, на \"n\", если только определённое подмножество: ",
		"\nОшибка!!! Вы нажали на некорректную кнопку, осуществите ввод по указанным вам правилам!!!");
	if (!query) // Пакетное редактирование
	{
		Filter();
		if (!vectorIdForFilter.empty())
		{
			PrintFilterTable(vectorIdForFilter);
			query = verification::GetBoolValue("\nНажмите на \"y\", если хотите редактировать все отфильтрованные трубы, на \"n\", если только определённое подмножество: ",
				"\nОшибка!!! Вы нажали на некорректную кнопку, осуществите ввод по указанным вам правилам!!!");
			if (!query) // Редактировать все отфильтрованные трубы
			{
				std::set<size_t> setIdForChange = verification::GetMultipleNumericValues<size_t>(
					"\nВведите через пробел id труб, которые хотели бы отредактировать: ",
					"\nОшибка, вы ввели недопустимый формат, повторите ввод заново!");
				repairStatus = verification::GetBoolValue("\n\nУкажите новое состояние для выбранных труб, если в ремонте, то нажмите \"y\" на клавиатуре, если же нет, кликните по \"n\": ",
					"\nНеизвестная команда! Повторите ввод по указанным выше правилам, кликните по \"y\", если да, по \"n\", если нет!!!");
				for (const auto id : setIdForChange)
				{
					auto it = std::find(vectorIdForFilter.begin(), vectorIdForFilter.end(), id);
					if (it != vectorIdForFilter.end())
					{
						pipeCollection[id].repair = repairStatus;
						Console::PrintTitleText("Труба с id - " + std::to_string(id) + " была отредактирована");
					}
					else
						Console::PrintErrorText("Труба с id - " + std::to_string(id) + " не была найдена в списке отфильтрованных труб\n");
				}
			}
			else // Отредактировать часть отфильтрованных труб
			{
				repairStatus = verification::GetBoolValue("\n\nУкажите новое состояние для выбранных труб, если в ремонте, то нажмите \"y\" на клавиатуре, если же нет, кликните по \"n\": ",
					"\nНеизвестная команда! Повторите ввод по указанным выше правилам, кликните по \"y\", если да, по \"n\", если нет!!!");
				for (const auto& i : vectorIdForFilter)
					pipeCollection[i].repair = repairStatus;
				Console::PrintTitleText("\nТрубы отредактированы!");
			}
		}
		else
			Console::PrintErrorText("\nПо вашему фильтру не было найдено ни одной трубы!");
		vectorIdForFilter.clear();
	}
	else // Редактирование всех труб
	{
		PrintTable();
		repairStatus = verification::GetBoolValue("\n\nУкажите новое состояние для выбранных труб, если в ремонте, то нажмите \"y\" на клавиатуре, если же нет, кликните по \"n\": ",
			"\nНеизвестная команда! Повторите ввод по указанным выше правилам, кликните по \"y\", если да, по \"n\", если нет!!!");
		for (auto& el : pipeCollection)
			el.second.repair = repairStatus;
		Console::PrintTitleText("\nТрубы отредактированы!");
	}
	system("pause");
}