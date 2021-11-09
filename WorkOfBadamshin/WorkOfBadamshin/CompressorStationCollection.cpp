#include "CompressorStationCollection.h"
#include "Verification.h"
#include <iomanip>

// Добавление компрессорной станции в список
void CompressorStationCollection::AddCS()
{
	CompressorStation compressorStation;
	csCollection.emplace(compressorStation.id, compressorStation);
}


// Редактирование компрессорной станции
void CompressorStationCollection::ChangeCS()
{
	size_t changeId;
	bool query;
	std::cout << "Всего добавлено компрессорных станций: " << size(csCollection) << std::endl
		<< "Id доступные для редактирования: ";
	for (const auto& el : csCollection)
		std::cout << el.first << "  ";
	std::cout << std::endl;
	if (csCollection.empty())
	{
		Console::PrintErrorText("Вы не добавили ни одной компрессорной станции, редактирование недоступно!");
		verification::GetPressEscape("\n\nЧтобы выйти в меню, нажмите ESC: ", "\nКоманда не распознана, нажмите ESC на клавиатуре, если хотите вернуться в меню!");
		return;
	}
	while (true)
	{
		changeId = verification::GetNumericValue<size_t>("\nВведите номер (id) компрессорной станции, которую вы бы хотели редактировать: ",
			"Ошибка! Вы ввели недопустимое значение, возможно вы ввели несуществующий id или же произвели некорректный ввод, помните id это положительное, целое число!!!",
			1, CompressorStation::countCSCreated);
		if (csCollection.find(changeId) != csCollection.end())
		{
			std::cout << "Количество цехов у данной компрессорной станции: " << csCollection[changeId].countWorkShops << std::endl;
			std::cout << "Количество цехов в работе у данной компрессорной станции: " << csCollection[changeId].countWorkShopsInOperation << std::endl;
			csCollection[changeId].ChangeCS();
		}
		query = verification::GetBoolValue("\n\nХотите ли вы продолжить редактировать компрессоные станции, если да, то кликните \"y\", если же нет, то нажмите на \"n\": ",
			"\nНеизвестная команда! Повторите ввод по указанным выше правилам, кликните по \"y\", если да, по \"n\", если нет!!!");
		if (query != true)
			break;
	}
}


// Вывод таблицы компрессорных станций на экран
void CompressorStationCollection::PrintTableCS()
{
	int tabulation_20 = 20, tabulation_30 = 30, tableWidth = 172;
	Console::PrintTitleText("\n\t\t\t\tТаблица КС");
	Console::PrintChar('-', tableWidth);
	std::cout << "|" << std::setw(tabulation_20) << "ID" << std::setw(tabulation_30 + 1) << "NAME" << std::setw(tabulation_30) << "CountWorkShops" << std::setw(tabulation_30 + 10) << "CountWorkShopsInOperation" << std::setw(tabulation_30) << "EFFECTIVENESS" << std::setw(tabulation_20) << "|" << std::endl;
	Console::PrintChar('-', tableWidth);
	for (const auto& cs : csCollection)
	{
		std::cout << "|" << std::setw(tabulation_20) << cs.second.id << std::setw(tabulation_30 + 1) << cs.second.name << std::setw(tabulation_30) << cs.second.countWorkShops << std::setw(tabulation_30 + 10) << cs.second.countWorkShopsInOperation << std::setw(tabulation_30) << cs.second.effectiveness << std::setw(tabulation_20) << "|" << std::endl;
	}
	Console::PrintChar('-', tableWidth);
}

// Вывод таблицы компрессорных станций на экран, при этом функция вывод любой вектор КС
void CompressorStationCollection::PrintFilterTableCS()
{
	int tabulation_20 = 20, tabulation_30 = 30, tableWidth = 172;
	Console::PrintTitleText("\n\t\t\t\tТаблица КС");
	Console::PrintChar('-', tableWidth);
	std::cout << "|" << std::setw(tabulation_20) << "ID" << std::setw(tabulation_30 + 1) << "NAME" << std::setw(tabulation_30) << "CountWorkShops" << std::setw(tabulation_30 + 10) << "CountWorkShopsInOperation" << std::setw(tabulation_30) << "EFFECTIVENESS" << std::setw(tabulation_20) << "|" << std::endl;
	Console::PrintChar('-', tableWidth);
	for (const auto& id : vectorIdForFilter)
	{
		std::cout << "|" << std::setw(tabulation_20) << csCollection[id].id << std::setw(tabulation_30 + 1) << csCollection[id].name << std::setw(tabulation_30) << csCollection[id].countWorkShops << std::setw(tabulation_30 + 10) << csCollection[id].countWorkShopsInOperation << std::setw(tabulation_30) << csCollection[id].effectiveness << std::setw(tabulation_20) << "|" << std::endl;
	}
	Console::PrintChar('-', tableWidth);
}

// Вывод компрессорных станций в файл
void CompressorStationCollection::SaveToFile(std::ofstream& fout)
{
	size_t percent = 0;
	if (csCollection.empty())
	{
		Console::PrintErrorText("Вы не добавили ни одной компрессорной станции!");
		return;
	}
	if (fout.is_open())
	{
		for (auto& el : csCollection)
			el.second.SaveToFile(fout);
		while (percent <= 100)
		{
			std::cout << "\t\t" << "Сохранение КС: " << percent++ << "%";
			std::cout << '\r';
			Sleep(20);
		}
		Console::PrintTitleText("\n\t\tКС сохранены!");
	}
	else
	{
		Console::PrintErrorText("\nОШИБКА!!! Файл по указанному пути не найден, либо он не существует!");
	}
}

// Загрузка КС из файла
void CompressorStationCollection::DownloadFromFile(std::ifstream& fin)
{
	size_t percent = 0;
	if (fin.is_open())
	{
		if (fin.peek() != -1)
		{
			while (fin.peek() != ' ' && fin.peek() != -1)
			{
				CompressorStation compressorStation(fin);
				csCollection.emplace(compressorStation.id, compressorStation);
				fin.ignore(1000, '\n');
			}
			while (percent <= 100)
			{
				std::cout << "\t\t" << "Загрузка КС: " << percent++ << "%";
				std::cout << '\r';
				Sleep(20);
			}
			Console::PrintTitleText("\nКС загружены!");
		}
		else
		{
			Console::PrintErrorText("\nНельзя загружать данные из пустого файла, сначала нужно сохранить там данные!!!");
		}
	}
	else
	{
		Console::PrintErrorText("\nОШИБКА!!! Файл по указанному пути не найден, либо он не существует!");
	}
}

// Фильтр КС
void CompressorStationCollection::FilterCS()
{
	char command;
	std::cout << "\n\nВыберите пункт меню для фильтрации:" << std::endl
		<< "1. Отфильтровать по названию" << std::endl
		<< "2. Отфильтровать по проценту незадействованных цехов" << std::endl
		<< "3. Применить оба фильтра" << std::endl;
	while (true)
	{
		std::cout << "\nВведите команду: ";
		command = _getch();
		switch (command)
		{
		case '1':
		{
			std::string nameCS;
			nameCS = verification::GetStringValue("\nВведите название КС, по которому вы хотите отфильтровать данные (длина не больше 30 символов): ",
				"Ошибка!!! Название не может состоять только из пробелов или пустой строки и иметь длину больше чем 30 символов!!!", 30);
			for (const auto& el : csCollection)
				if (el.second.name == nameCS)
					vectorIdForFilter.push_back(el.first);
			return;
		}
		case '2':
		{
			size_t lowPercent, upPercent, percent;
			lowPercent = verification::GetNumericValue<size_t>("\nВведите нижнюю границу фильтра процента незадейстованных цехов у КС (число целое от 0 до 100): ",
				"Ошибка!!! Вы осуществили неправильный ввод, повторите его по выше указанным правилам.", 0, 100);
			upPercent = verification::GetNumericValue<size_t>("\nВведите верхнюю границу фильтра процента незадейстованных цехов у КС (число целое от нижней границы до 100): ",
				"Ошибка!!! Вы осуществили неправильный ввод, повторите его по выше указанным правилам.", lowPercent, 100);
			for (const auto& el : csCollection)
			{
				percent = static_cast<size_t>(round((static_cast<double>(el.second.countWorkShops) - el.second.countWorkShopsInOperation) / el.second.countWorkShops * 100));
				if (percent >= lowPercent && percent <= upPercent)
					vectorIdForFilter.push_back(el.first);
			}
			return;
		}
		case '3':
		{
			std::string nameCS;
			size_t lowPercent, upPercent, percent;
			nameCS = verification::GetStringValue("\nВведите название КС, по которому вы хотите отфильтровать данные (длина не больше 30 символов): ",
				"Ошибка!!! Название не может состоять только из пробелов или пустой строки и иметь длину больше чем 30 символов!!!", 30);
			lowPercent = verification::GetNumericValue<size_t>("\nВведите нижнюю границу фильтра процента незадейстованных цехов у КС (число целое от 0 до 100): ",
				"Ошибка!!! Вы осуществили неправильный ввод, повторите его по выше указанным правилам.", 0, 100);
			upPercent = verification::GetNumericValue<size_t>("\nВведите верхнюю границу фильтра процента незадейстованных цехов у КС (число целое от нижней границы до 100): ",
				"Ошибка!!! Вы осуществили неправильный ввод, повторите его по выше указанным правилам.", lowPercent, 100);
			for (const auto& el : csCollection)
			{
				percent = static_cast<size_t>(round((static_cast<double>(el.second.countWorkShops) - el.second.countWorkShopsInOperation) / el.second.countWorkShops * 100));
				if (el.second.name == nameCS && percent >= lowPercent && percent <= upPercent)
					vectorIdForFilter.push_back(el.first);
			}
			return;
		}
		default:
		{
			Console::PrintErrorText("\nТакой команды нету в списке, приведённом выше, повторите ввод!!!\n");
			break;
		}
		}
	}
}

// Удаление КС
void CompressorStationCollection::DeleteCS()
{
	size_t delId; // id кс, которую нужно удалить
	bool query;
	if (csCollection.empty())
	{
		Console::PrintErrorText("Вы не добавили ни одну КС, удаление недоступно!");
		verification::GetPressEscape("\n\nЧтобы выйти в меню, нажмите ESC: ", "\nКоманда не распознана, нажмите ESC на клавиатуре, если хотите вернуться в меню!");
		return;
	}
	query = verification::GetBoolValue("\nНажмите на \"y\", если хотите произвести удаление по одной КС, на \"n\", если хотите произвести пакетное удаление по фильтру: ",
		"\nНеизвестная команда! Повторите ввод по указанным правилам!!!");
	if (query)
	{
		while (true)
		{
			std::cout << "\n\nВсего КС: " << size(csCollection) << std::endl
				<< "Id доступные для удаления: ";
			for (const auto& el : csCollection)
				std::cout << el.first << "  ";
			std::cout << std::endl;
			delId = verification::GetNumericValue<size_t>("Введите id КС, которую вы бы хотели удалить: ",
				"Ошибка! Вы ввели недопустимое значение, возможно вы ввели несуществующий id или же произвели некорректный ввод, помните id это положительное, целое число!!!", 1, CompressorStation::countCSCreated);
			if (csCollection.find(delId) != csCollection.end())
			{
				csCollection.erase(delId);
				Console::PrintTitleText("КС была успешно удалена!");
			}
			else
				Console::PrintErrorText("По указанному id не было найдено ни одной КС, возможно КС уже была удалена!!!");
			query = verification::GetBoolValue("\n\nХотите ли вы продолжить удалять КС, если да, то кликните \"y\", если же нет, то нажмите на \"n\": ",
				"\nНеизвестная команда! Повторите ввод по указанным выше правилам, кликните по \"y\", если да, по \"n\", если нет!!!");
			if (!query)
				break;
		}
	}
	else
	{
		FilterCS();
		if (size(vectorIdForFilter) != 0)
		{
			std::cout << "\n\nБудут удалены следующие КС:" << std::endl;
			PrintFilterTableCS();
			for (const auto i : vectorIdForFilter)
				csCollection.erase(i);
			vectorIdForFilter.clear();
			Console::PrintTitleText("\n\nКС Успешно удалены!");
		}
		else
			Console::PrintErrorText("\nПо вашему фильтру не было найдено ни одной КС!");
	}
	std::cout << std::endl;
	system("pause");
}

// Пакетное редактирование КС
void CompressorStationCollection::BatchChangeCS()
{
	bool query;
	if (csCollection.empty())
	{
		Console::PrintErrorText("\nВы не добавили ни одной КС, пакетное редактирование недоступно!");
		verification::GetPressEscape("\n\nЧтобы выйти в меню, нажмите ESC: ", "\nКоманда не распознана, нажмите ESC на клавиатуре, если хотите вернуться в меню!");
		return;
	}
	query = verification::GetBoolValue("\nНажмите на \"y\", если хотите редактировать все КС, на \"n\", если только определённое подмножество: ",
		"\nОшибка!!! Вы нажали на некорректную кнопку, осуществите ввод по указанным вам правилам!!!");
	if (!query)
	{
		FilterCS();
		if (size(vectorIdForFilter) != 0)
		{
			PrintFilterTableCS();
			for (const auto& i : vectorIdForFilter)
			{
				std::cout << "\n\nКомпрессорная станция под id " << csCollection[i].id << " имеет общее количество цехов: " << csCollection[i].countWorkShops << std::endl
					<< "Количество цехов в работе: " << csCollection[i].countWorkShopsInOperation << std::endl;
				csCollection[i].countWorkShopsInOperation = verification::GetNumericValue<size_t>("Введите новое количество цехов в работе для данной КС (оно не должно превышать общее количество цехов): ",
					"Ошибка!!! Количество цехов это целое число, без посторонних символов, ввиде букв, точек, а также число не должно превышать общее количество цехов.", 0, csCollection[i].countWorkShops);
			}
			Console::PrintTitleText("\n\nКС отредактированы!");
		}
		else
			Console::PrintErrorText("\nПо вашему фильтру не было найдено ни одной трубы!");
	}
	else
	{
		PrintTableCS();
		for (auto& el : csCollection)
		{
			std::cout << "\n\nКомпрессорная станция под id " << el.first << " имеет общее количество цехов: " << el.second.countWorkShops << std::endl
				<< "Количество цехов в работе: " << el.second.countWorkShopsInOperation << std::endl;
			el.second.countWorkShopsInOperation = verification::GetNumericValue<size_t>("Введите новое количество цехов в работе для данной КС (оно не должно превышать общее количество цехов): ",
				"Ошибка!!! Количество цехов это целое число, без посторонних символов, ввиде букв, точек, а также число не должно превышать общее количество цехов.", 0, el.second.countWorkShops);
		}
		Console::PrintTitleText("\n\nКС отредактированы!");
	}
	vectorIdForFilter.clear();
	system("pause");
}