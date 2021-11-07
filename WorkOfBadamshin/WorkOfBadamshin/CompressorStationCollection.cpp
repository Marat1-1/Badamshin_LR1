#include "CompressorStationCollection.h"
#include "Verification_Class.h"
#include <iomanip>



// Добавление компрессорной станции в список
void CompressorStationCollection::AddCS(Console& console)
{
	VerificationClass<size_t> verification;
	CompressorStation compressorStation;
	compressorStation.id = CompressorStation::countCS;
	compressorStation.name = verification.GetStringValue("Введите название КС (длина не больше 30 символов): ",
		"Ошибка!!! Название не может состоять только из пробелов или пустой строки и иметь длину больше чем 30 символов!!!", 30, console);

	compressorStation.countWorkShops = verification.GetNumericValue("Введите количество цехов КС (не больше 20): ",
		"Ошибка!!! Количество цехов это целое число, без посторонних символов, в виде букв, точек и также число должно быть меньше 20.", 0, 20, console);

	compressorStation.countWorkShopsInOperation = verification.GetNumericValue("Введите количество цехов в работе (оно не должно превышать общее количество цехов): ",
		"Ошибка!!! Количество цехов это целое число, без посторонних символов, ввиде букв, точек, а также число не должно превышать общее количество цехов.", 0, compressorStation.countWorkShops, console);

	compressorStation.effectiveness = verification.GetNumericValue("Введите значение эффективности КС (оно измеряется в процентах, поэтому введите число от 0 до 100%): ",
			"Ошибка!!! Вы ввели что-то непонятное.\nЭффективность КС может быть целым числом лежащим в пределах от 0 до 100.\nПовторите ввод!!!", 0, 100, console);
	
	vectorCS.push_back(compressorStation);
}


// Редактирование компрессорной станции
void CompressorStationCollection::ChangeCS(Console& console)
{
	VerificationClass<size_t> verification;
	std::cout << "Всего добавлено компрессорных станций: " << CompressorStation::countCS << std::endl;
	if (CompressorStation::countCS == 0)
	{
		console.PrintErrorText("Вы не добавили ни одной компрессорной станции, редактирование недоступно!");
		verification.GetPressEscape("\n\nЧтобы выйти в меню, нажмите ESC: ", "\nКоманда не распознана, нажмите ESC на клавиатуре, если хотите вернуться в меню!", console);
		return;
	}
	while (true)
	{
		size_t localId = verification.GetNumericValue("\nВведите номер (id) компрессорной станции, которую вы бы хотели редактировать (id не должен превышать общее количество компрессорных станций): ",
			"Вы ввели недопустимое значение, id трубы не должен превышать общее количество компрессорных станций, а также он является натуральным числом!!!",
			1, CompressorStation::countCS, console);
		std::cout << "Количество цехов у данной компрессорной станции: " << vectorCS[localId - 1].countWorkShops << std::endl;
		std::cout << "Количество цехов в работе у данной компрессорной станции: " << vectorCS[localId - 1].countWorkShopsInOperation << std::endl;
		vectorCS[localId - 1].countWorkShopsInOperation = verification.GetNumericValue("Введите новое количество цехов в работе (оно не должно превышать общее количество цехов): ",
			"Ошибка!!! Количество цехов это целое число, без посторонних символов, ввиде букв, точек, а также число не должно превышать общее количество цехов.",
			0, vectorCS[localId - 1].countWorkShops, console);
		bool query = verification.GetBoolValue("\n\nХотите ли вы продолжить редактировать компрессоные станции, если да, то кликните \"y\", если же нет, то нажмите на \"n\": ",
			"\nНеизвестная команда! Повторите ввод по указанным выше правилам, кликните по \"y\", если да, по \"n\", если нет: ", console);
		if (query != true)
			break;
	}
}


// Вывод таблицы компрессорных станций на экран
void CompressorStationCollection::PrintTableCS(Console& console)
{
	int tabulation_20 = 20, tabulation_30 = 30, tableWidth = 172;
	console.PrintChar('-', tableWidth);
	std::cout << "|" << std::setw(tabulation_20) << "ID" << std::setw(tabulation_30 + 1) << "NAME" << std::setw(tabulation_30) << "CountWorkShops" << std::setw(tabulation_30 + 10) << "CountWorkShopsInOperation" << std::setw(tabulation_30) << "EFFECTIVENESS" << std::setw(tabulation_20) << "|" << std::endl;
	console.PrintChar('-', tableWidth);
	for (const auto& cs : vectorCS)
	{
		std::cout << "|" << std::setw(tabulation_20) << cs.id << std::setw(tabulation_30 + 1) << cs.name << std::setw(tabulation_30) << cs.countWorkShops << std::setw(tabulation_30 + 10) << cs.countWorkShopsInOperation << std::setw(tabulation_30) << cs.effectiveness << std::setw(tabulation_20) << "|" << std::endl;
	}
	console.PrintChar('-', tableWidth);
}

// Вывод таблицы компрессорных станций на экран, при этом функция вывод любой вектор КС
void CompressorStationCollection::PrintTableCS(const std::vector<CompressorStation>& vectorCSForPrint, std::string textError, Console& console)
{
	int tabulation_20 = 20, tabulation_30 = 30, tableWidth = 172;
	if (size(vectorCSForPrint) != 0)
	{
		console.PrintTitleText("\n\t\tТаблица КС");
		console.PrintChar('-', tableWidth);
		std::cout << "|" << std::setw(tabulation_20) << "ID" << std::setw(tabulation_30 + 1) << "NAME" << std::setw(tabulation_30) << "CountWorkShops" << std::setw(tabulation_30 + 10) << "CountWorkShopsInOperation" << std::setw(tabulation_30) << "EFFECTIVENESS" << std::setw(tabulation_20) << "|" << std::endl;
		console.PrintChar('-', tableWidth);
		for (const auto& cs : vectorCSForPrint)
		{
			std::cout << "|" << std::setw(tabulation_20) << cs.id << std::setw(tabulation_30 + 1) << cs.name << std::setw(tabulation_30) << cs.countWorkShops << std::setw(tabulation_30 + 10) << cs.countWorkShopsInOperation << std::setw(tabulation_30) << cs.effectiveness << std::setw(tabulation_20) << "|" << std::endl;
		}
		console.PrintChar('-', tableWidth);
	}
	else
	{
		console.PrintErrorText(textError);
	}
}

// Вывод компрессорных станций в файл
void CompressorStationCollection::SaveToFile(std::ofstream& fout, Console& console)
{
	size_t percent = 0;
	if (fout.is_open())
	{
		for (const auto& v : vectorCS)
		{
			fout << v.name << std::endl
				<< v.countWorkShops << std::endl
				<< v.countWorkShopsInOperation << std::endl
				<< v.effectiveness << std::endl;
		}
		while (percent <= 100)
		{
			std::cout << "\t\t" << "Сохранение КС: " << percent++ << "%";
			std::cout << '\r';
			Sleep(20);
		}
		console.PrintTitleText("\n\t\tКС сохранены!");
	}
	else
	{
		console.PrintErrorText("\nОШИБКА!!! Файл по указанному пути не найден, либо он не существует!");
	}
}

// Загрузка КС из файла
void CompressorStationCollection::DownloadFromFile(std::ifstream& fin, Console& console)
{
	size_t percent = 0;
	if (fin.is_open())
	{
		if (fin.peek() != -1)
		{
			while (fin.peek() != ' ' && fin.peek() != -1)
			{
				CompressorStation newCS;
				newCS.id = CompressorStation::countCS;
				getline(fin, newCS.name);
				fin >> newCS.countWorkShops
					>> newCS.countWorkShopsInOperation
					>> newCS.effectiveness;
				vectorCS.push_back(newCS);
				fin.ignore(1000, '\n');
			}
			while (percent <= 100)
			{
				std::cout << "\t\t" << "Загрузка КС: " << percent++ << "%";
				std::cout << '\r';
				Sleep(20);
			}
			console.PrintTitleText("\nКС загружены!");
		}
		else
		{
			console.PrintErrorText("\nНельзя загружать данные из пустого файла, сначала нужно сохранить там данные!!!");
		}
	}
	else
	{
		console.PrintErrorText("\nОШИБКА!!! Файл по указанному пути не найден, либо он не существует!");
	}
}


// Удаление КС
void CompressorStationCollection::DeleteCS(Console& console)
{
	VerificationClass<size_t> verification;
	size_t delId; // id кс, которую нужно удалить
	const size_t& id = delId; // константная ссылка на id, чтобы работать с итератором
	bool query;
	std::vector<CompressorStation>::iterator it = vectorCS.begin();
	if (CompressorStation::countCS == 0)
	{
		console.PrintErrorText("Вы не добавили ни одну КС, удаление недоступно!");
		verification.GetPressEscape("\n\nЧтобы выйти в меню, нажмите ESC: ", "\nКоманда не распознана, нажмите ESC на клавиатуре, если хотите вернуться в меню!", console);
		return;
	}
	while (true)
	{
		std::cout << "\n\nВсего труб: " << CompressorStation::countCS << std::endl;
		delId = verification.GetNumericValue("Введите id КС, которую вы бы хотели удалить (id не должен превышать общее количество КС): ",
			"Вы ввели недопустимое значение, id КС не должен превышать общее количество КС, а также id это натуральное число!!!", 1, CompressorStation::countCS, console);
		it += id - 1;
		CompressorStation::countCS--;
		for (auto iter = vectorCS.erase(it); iter != vectorCS.end(); iter++)
		{
			(*iter).id--;
		}
		console.PrintTitleText("КС была успешно удалена!");
		query = verification.GetBoolValue("\n\nХотите ли вы продолжить удалять КС, если да, то кликните \"y\", если же нет, то нажмите на \"n\": ",
			"\nНеизвестная команда! Повторите ввод по указанным выше правилам, кликните по \"y\", если да, по \"n\", если нет: ", console);
		if (!query)
			break;
	}
}

// Фильтр КС
void CompressorStationCollection::FilterCS(Console& console)
{
	VerificationClass<size_t> verification;
	std::vector<CompressorStation> filterVectorCS;
	char command;
	if (CompressorStation::countCS == 0)
	{
		console.PrintErrorText("Вы не добавили ни одной компрессорной станции, фильтрация недоступна!");
		verification.GetPressEscape("\n\nЧтобы выйти в меню, нажмите ESC: ", "\nКоманда не распознана, нажмите ESC на клавиатуре, если хотите вернуться в меню!", console);
		return;
	}
	std::cout << "Выберите пункт меню:" << std::endl
		<< "1. Отфильтровать по названию" << std::endl
		<< "2. Отфильтровать по проценту незадействованных цехов" << std::endl
		<< "3. Применить оба фильтра" << std::endl
		<< "0. Выйти в меню" << std::endl;
	while (true)
	{
		std::cout << "\nВведите команду: ";
		command = _getch();
		switch (command)
		{
		case '1':
		{
			std::string nameCS;
			nameCS = verification.GetStringValue("\nВведите название КС, по которому вы хотите отфильтровать данные (длина не больше 30 символов): ",
				"Ошибка!!! Название не может состоять только из пробелов или пустой строки и иметь длину больше чем 30 символов!!!", 30, console);
			for (const auto& v : vectorCS)
				if (v.name == nameCS)
					filterVectorCS.push_back(v);
			PrintTableCS(filterVectorCS, "\nПо вашему фильтру не было найдено ни одной КС", console);
			filterVectorCS.clear();
			break;
		}
		case '2':
		{
			size_t lowPercent;
			size_t upPercent;
			size_t percent;
			lowPercent = verification.GetNumericValue("\nВведите нижнюю границу фильтра процента незадейстованных цехов у КС (число целое от 0 до 100): ",
				"Ошибка!!! Вы осуществили неправильный ввод, повторите его по выше указанным правилам.", 0, 100, console);
			upPercent = verification.GetNumericValue("\nВведите верхнюю границу фильтра процента незадейстованных цехов у КС (число целое от нижней границы до 100): ",
				"Ошибка!!! Вы осуществили неправильный ввод, повторите его по выше указанным правилам.", lowPercent, 100, console);
			for (const auto& v : vectorCS)
			{
				percent = static_cast<size_t>(round((static_cast<double>(v.countWorkShops) - v.countWorkShopsInOperation) / v.countWorkShops * 100));
				if (percent >= lowPercent && percent <= upPercent)
					filterVectorCS.push_back(v);
			}
			PrintTableCS(filterVectorCS, "\nПо вашему фильтру не было найдено ни одной КС", console);
			filterVectorCS.clear();
			break;
		}
		case '3':
		{
			std::string nameCS;
			size_t lowPercent;
			size_t upPercent;
			size_t percent;
			nameCS = verification.GetStringValue("\nВведите название КС, по которому вы хотите отфильтровать данные (длина не больше 30 символов): ",
				"Ошибка!!! Название не может состоять только из пробелов или пустой строки и иметь длину больше чем 30 символов!!!", 30, console);
			lowPercent = verification.GetNumericValue("\nВведите нижнюю границу фильтра процента незадейстованных цехов у КС (число целое от 0 до 100): ",
				"Ошибка!!! Вы осуществили неправильный ввод, повторите его по выше указанным правилам.", 0, 100, console);
			upPercent = verification.GetNumericValue("\nВведите верхнюю границу фильтра процента незадейстованных цехов у КС (число целое от нижней границы до 100): ",
				"Ошибка!!! Вы осуществили неправильный ввод, повторите его по выше указанным правилам.", lowPercent, 100, console);
			for (const auto& v : vectorCS)
			{
				percent = static_cast<size_t>(round((static_cast<double>(v.countWorkShops) - v.countWorkShopsInOperation) / v.countWorkShops * 100));
				if (v.name == nameCS && percent >= lowPercent && percent <= upPercent)
					filterVectorCS.push_back(v);
			}
			PrintTableCS(filterVectorCS, "\nПо вашему фильтру не было найдено ни одной КС", console);
			filterVectorCS.clear();
			break;
		}
		case '0':
		{
			return;
		}
		default:
		{
			console.PrintErrorText("\nТакой команды нету в списке, приведённом выше, повторите ввод!!!\n");
			break;
		}
		}
	}
}