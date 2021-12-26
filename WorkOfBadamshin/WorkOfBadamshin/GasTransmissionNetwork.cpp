#include "GasTransmissionNetwork.h"
#include "Verification.h"
#include "Console.h"
#include <conio.h>
#include <iomanip>

// Меню для работы с пользователем
void GasTransmissionNetwork::printMenu()
{
	Console::PrintTitleText("\n\t\t\t\tУправление Газотранспортной сетью\n");
	std::cout << "\nВыберите один из пунктов меню: " << std::endl
		<< "1. Добавить связи" << std::endl
		<< "2. Удалить связи" << std::endl
		<< "3. Отсортировать граф" << std::endl
		<< "4. Вывести таблицу связей" << std::endl
		<< "5. Найти кратчайший путь от одной вершины к другой" << std::endl
		<< "0. Выйти в общее меню" << std::endl
		<< "Ввод: ";
}

// Вывод свободных труб и КС
void GasTransmissionNetwork::printFreePipes()
{
	std::vector<size_t> vectorForOutput;
	for (const auto& el : newPipeCollection.pipeCollection)
		if (!el.second.IsUsed())
			vectorForOutput.push_back(el.first);
	newPipeCollection.PrintFilterTable(vectorForOutput);
}

void GasTransmissionNetwork::printFreeCS()
{
	std::vector<size_t> vectorForOutput;
	for (const auto& el : newCSCollection.csCollection)
		if (!el.second.IsFullyField())
			vectorForOutput.push_back(el.first);
	newCSCollection.PrintFilterTable(vectorForOutput);
}

// Проверка на наличие свободных труб и КС
bool GasTransmissionNetwork::checkFreePipes()
{
	for (const auto& el : newPipeCollection.pipeCollection)
		if (!el.second.IsUsed())
			return true;
	return false;
}

bool GasTransmissionNetwork::checkFreeCS()
{
	for (const auto& el : newCSCollection.csCollection)
		if (!el.second.IsFullyField())
			return true;
	return false;
}

// Проверка на наличие связей
bool GasTransmissionNetwork::checkingConnections()
{
	for (const auto& el : newPipeCollection.pipeCollection)
		if (el.second.IsUsed())
			return true;
	return false;
}

// Вывод таблицы связей
void GasTransmissionNetwork::printTableConnections()
{
	size_t tabulation_20 = 20, tabulation_30 = 30, tableWidth = 101;
	Console::PrintTitleText("\n\t\t\t\tТаблица Связей");
	Console::PrintChar('-', tableWidth);
	std::cout << "|" << std::setw(tabulation_20) << "ID PIPE" << std::setw(tabulation_30) << "ID Output CS" << std::setw(tabulation_30) << "ID Input CS" << std::setw(tabulation_20) << "|" << std::endl;
	Console::PrintChar('-', tableWidth);
	for (const auto& el : newPipeCollection.pipeCollection)
		if (el.second.IsUsed())
			std::cout << "|" << std::setw(tabulation_20) << el.first << std::setw(tabulation_30) << el.second.GetOutId() << std::setw(tabulation_30) << el.second.GetInId() << std::setw(tabulation_20) << "|" << std::endl;
	Console::PrintChar('-', tableWidth);
}

// Заполнение мапов труб и КС для графа
void GasTransmissionNetwork::fillMapCSInUse()
{
	mapCSInUse.clear();
	for (const auto& el : newCSCollection.csCollection)
		if (el.second.IsUsed())
			mapCSInUse.emplace(el.first, el.second);
}

void GasTransmissionNetwork::fillMapPipeInUse()
{
	mapPipeInUse.clear();
	for (const auto& el : newPipeCollection.pipeCollection)
		if (el.second.IsUsed())
			mapPipeInUse.emplace(el.first, el.second);
}

// Рекурсивный метод поиска элемента с нулевой степенью захода и заполнения вектора отсортированных id
void GasTransmissionNetwork::findCSZeroDegreeOfOutcome(std::unordered_map<size_t, CompressorStation> mapCS, std::unordered_map<size_t, Pipe> mapPipe)
{
	size_t counter = 0;
	std::vector<size_t> idDelCS;
	std::vector<size_t> idDelPipe;
	for (const auto& elCS : mapCS)
		if (elCS.second.GetDegreeOfEntry() == 0)
		{
			++counter;
			idDelCS.push_back(elCS.first);
			sortIdCS.push_back(elCS.first);
			for (const auto& elPipe : mapPipe)
				if (elPipe.second.GetOutId() == elCS.first)
				{
					idDelPipe.push_back(elPipe.first);
				}
		}
	for (const auto& id : idDelCS)
		mapCS.erase(id);
	for (const auto& id : idDelPipe)
	{
		(*mapCS.find((*mapPipe.find(id)).second.GetInId())).second.DecDegreeOfEntry();
		mapPipe.erase(id);
	}
	idDelCS.clear();
	idDelPipe.clear();
	if (counter == 0)
		throw - 1;
	if (mapCS.empty() && mapPipe.empty())
		return;
	findCSZeroDegreeOfOutcome(mapCS, mapPipe);
}

// Вывод неотсортированного графа
void GasTransmissionNetwork::printGraph()
{
	Console::PrintTitleText("\n\nНеотсортированный граф:");
	Console::PrintChar('-', mapCSInUse.size() * 20 + 1);
	std::cout << "|";
	for (const auto& el : mapCSInUse)
		std::cout << std::setw(10) << el.first << std::setw(10) << "|";
	std::cout << std::endl;
	Console::PrintChar('-', mapCSInUse.size() * 20 + 1);
}

// Вывод отсортированного графа
void GasTransmissionNetwork::printSortGraph()
{
	Console::PrintTitleText("\n\nОтсортированный граф:");
	Console::PrintChar('-', mapCSInUse.size() * 20 + 1);
	std::cout << "|";
	for (const auto& id : sortIdCS)
		std::cout << std::setw(10) << id << std::setw(10) << "|";
	std::cout << std::endl;
	Console::PrintChar('-', mapCSInUse.size() * 20 + 1);
}

// Сортировка графа
void GasTransmissionNetwork::sortGraph()
{
	sortIdCS.clear();
	fillMapCSInUse();
	fillMapPipeInUse();
	try
	{
		findCSZeroDegreeOfOutcome(mapCSInUse, mapPipeInUse);
		printGraph();
		printSortGraph();
	}
	catch (int)
	{
		Console::PrintErrorText("\nТопологическая сортировка невозможна, поскольку граф является цикличным!!!");
	}
}

// Поиск кратчайшего пути https://prog-cpp.ru/deikstra/
std::vector<size_t> GasTransmissionNetwork::findPath(size_t outID, size_t inID)
{
	const size_t SIZE = mapCSInUse.size();
	std::vector<size_t> resultPath;
	std::vector<std::vector<double>> a; a.resize(SIZE); // матрица связей
	std::vector<double> d; d.resize(SIZE); // минимальное расстояние
	std::vector<size_t> v; v.resize(SIZE); // посещенные вершины
	std::unordered_map<size_t, size_t> mapIdIndex; // связи между id-никами и индексами в мапе
	double temp, min;
	size_t minindex;
	size_t counter = 0;
	for (const auto& cs : mapCSInUse)
		mapIdIndex.emplace(cs.first, counter++);

	// Инициализация матрицы связей
	for (size_t i = 0; i < SIZE; i++)
		a[i].resize(SIZE);

	for (const auto& pipe : mapPipeInUse)
		a[mapIdIndex[pipe.second.GetOutId()]][mapIdIndex[pipe.second.GetInId()]] = pipe.second.length;

	//Инициализация вершин и расстояний
	for (size_t i = 0; i < SIZE; i++)
	{
		d[i] = 10000;
		v[i] = 1;
	}
	size_t begin_index = mapIdIndex[outID];
	d[begin_index] = 0;
	// Шаг алгоритма
	do {
		minindex = 10000;
		min = 10000;
		for (size_t i = 0; i < SIZE; i++)
		{ // Если вершину ещё не обошли и вес меньше min
			if ((v[i] == 1) && (d[i] < min))
			{ // Переприсваиваем значения
				min = d[i];
				minindex = i;
			}
		}
		// Добавляем найденный минимальный вес
		// к текущему весу вершины
		// и сравниваем с текущим минимальным весом вершины
		if (minindex != 10000)
		{
			for (size_t i = 0; i < SIZE; i++)
			{
				if (a[minindex][i] > 0)
				{
					temp = min + a[minindex][i];
					if (temp < d[i])
					{
						d[i] = temp;
					}
				}
			}
			v[minindex] = 0;
		}
	} while (minindex < 10000);
	
	// Проверка был ли найден путь, если нет, то выбрасываю исключение
	if (d[mapIdIndex[inID]] == 10000)
		throw - 1;

	// Восстановление пути
	std::vector<size_t> ver; // вектор посещенных вершин
	size_t end = mapIdIndex[inID]; // индекс конечной вершины
	ver.push_back(end); // начальный элемент - конечная вершина
	size_t weight = d[end]; // вес конечной вершины
	while (end != begin_index) // пока не дошли до начальной вершины
	{
		for (size_t i = 0; i < SIZE; i++) // просматриваем все вершины
			if (a[i][end] != 0)   // если связь есть
			{
				size_t temp = weight - a[i][end]; // определяем вес пути из предыдущей вершины
				if (temp == d[i]) // если вес совпал с рассчитанным
				{                 // значит из этой вершины и был переход
					weight = temp; // сохраняем новый вес
					end = i;       // сохраняем предыдущую вершину
					ver.push_back(i); // и записываем ее в массив
				}
			}
	}
	// Переход от индексов к ID
	for (size_t i = 0; i < ver.size(); i++)
	{
		for(const auto& el : mapIdIndex)
			if (el.second == ver[i])
				resultPath.push_back(el.first);
	}
	std::reverse(resultPath.begin(), resultPath.end());
	return resultPath;
}

// Вывод отсортированного пути
void GasTransmissionNetwork::printPath(const std::vector<size_t>& vectorPath)
{
	Console::PrintTitleText("\n\nКратчайший путь:");
	Console::PrintChar('-', vectorPath.size() * 20 + 1);
	std::cout << "|";
	for (const auto& id : vectorPath)
		std::cout << std::setw(10) << id << std::setw(10) << "|";
	std::cout << std::endl;
	Console::PrintChar('-', vectorPath.size() * 20 + 1);
}


// Функция управления Газотранспортной сетью
void GasTransmissionNetwork::manageNetwork()
{
	while (true)
	{
		printMenu();
		switch (_getch())
		{
		case '1':
		{
			if (!checkFreePipes() || !checkFreeCS())
			{
				Console::PrintErrorText("\nНет свободных труб или КС! Либо добавьте новые трубы, либо удалите связи у старых и используйте их.");
				system("pause");
				system("CLS");
				break;
			}
			size_t idPipe;
			size_t inId;
			size_t outId;
			bool query;
			std::cout << "\nСвободные трубы, которые можно использовать для построения сети: " << std::endl;
			printFreePipes();
			std::cout << "\nСвободные кс, которые можно использовать для построения сети: " << std::endl;
			printFreeCS();
			while (true)
			{
				idPipe = verification::GetNumericValue<size_t>("\nВведите id трубы, для которой хотели бы добавить связь: ",
					"\nНекорректный ввод! Id целое положительное число, при этом труба с таким id должна быть создана, повторите ввод!", 1, Pipe::GetMaxID());
				if (newPipeCollection.pipeCollection.find(idPipe) != newPipeCollection.pipeCollection.end() && !(*newPipeCollection.pipeCollection.find(idPipe)).second.IsUsed())
				{
					while (true)
					{
						outId = verification::GetNumericValue<size_t>("\nВведите id КС из которой будет исходить указанная труба: ",
							"\nНекорректный ввод! Id целое положительное число, при этом КС с таким id должна быть создана, повторите ввод!", 1, CompressorStation::GetMaxID());
						if (newCSCollection.csCollection.find(outId) != newCSCollection.csCollection.end() && !(*newCSCollection.csCollection.find(outId)).second.IsFullyField())
						{
							while (true)
							{
								inId = verification::GetNumericValue<size_t>("\nВведите id КС в которую будет входить указанная труба: ",
									"\nНекорректный ввод! Id целое положительное число, при этом КС с таким id должна быть создана, повторите ввод!", 1, CompressorStation::GetMaxID());
								if (inId != outId && newCSCollection.csCollection.find(inId) != newCSCollection.csCollection.end() && !(*newCSCollection.csCollection.find(inId)).second.IsFullyField())
								{
									newPipeCollection.pipeCollection[idPipe].SetInId(inId);
									newPipeCollection.pipeCollection[idPipe].SetOutId(outId);
									newPipeCollection.pipeCollection[idPipe].SetUsed(true);
									newCSCollection.csCollection[inId].IncDegreeOfEntry();
									newCSCollection.csCollection[outId].IncDegreeOfOutcome();
									Console::PrintTitleText("Связь была создана!");
									break;
								}
								else
									Console::PrintErrorText("Ошибка! По указанному id не найдено свободных КС или же id выхода совпало с id входом у трубы! Повторите ввод.");
							}
							break;
						}
						else
						{
							Console::PrintErrorText("По указанному id не найдено свободных КС! Повторите ввод.");
						}
					}
				}
				else
				{
					Console::PrintErrorText("По указанному id не найдено свободной трубы! Повторите ввод.");
					continue;
				}
				if (!checkFreePipes() || !checkFreeCS())
				{
					Console::PrintErrorText("Извините, но у вас не осталось элементов, чтобы добавить их в сеть!");
					break;
				}
				query = verification::GetBoolValue("Хотите ли продолжить создавать связи, нажмите \"y\", если да, \"n\", если нет: ",
					"Некорректное нажатие, повторите ввод по указанным правилам.");
				if (!query)
					break;
			}
			std::cout << std::endl;
			system("pause");
			system("CLS");
			break;
		}
		case '2':
		{
			if (!checkingConnections())
			{
				Console::PrintErrorText("\nСвязи отсуствуют, сначала создайте связь, только потом вы сможете удалить её.");
				system("pause");
				system("CLS");
				break;
			}
			size_t idPipe;
			bool query;
			std::cout << "\nТаблица доступных связей:" << std::endl;
			printTableConnections();
			while (true)
			{
				idPipe = verification::GetNumericValue<size_t>("\nВведите id трубы из таблицы, которую вы бы хотели убрать из связи: ",
					"\nНекорректный ввод! Id целое положительное число, при этом труба с таким id должна быть создана, повторите ввод!", 1, Pipe::GetMaxID());
				if (newPipeCollection.pipeCollection.find(idPipe) != newPipeCollection.pipeCollection.end() && (*newPipeCollection.pipeCollection.find(idPipe)).second.IsUsed())
				{
					(*newCSCollection.csCollection.find((*newPipeCollection.pipeCollection.find(idPipe)).second.GetOutId())).second.DecDegreeOfOutcome();
					(*newCSCollection.csCollection.find((*newPipeCollection.pipeCollection.find(idPipe)).second.GetInId())).second.DecDegreeOfEntry();
					(*newPipeCollection.pipeCollection.find(idPipe)).second.SetInId(0);
					(*newPipeCollection.pipeCollection.find(idPipe)).second.SetOutId(0);
					(*newPipeCollection.pipeCollection.find(idPipe)).second.SetUsed(false);
					Console::PrintTitleText("Связь успешно удалена!");
				}
				else
				{
					Console::PrintErrorText("По указанному id не найдено связи, возможно вы уже удалили эту связь или же не добавляли её!");
					continue;
				}
				if (!checkingConnections())
				{
					Console::PrintErrorText("Вы удалили все связи!!!");
					break;
				}
				query = verification::GetBoolValue("Хотите ли вы продолжить удалять связи, нажмите \"y\", если да, \"n\", если нет: ",
					"Некорректное нажатие, повторите ввод по указанным правилам.");
				if (!query)
					break;
			}
			std::cout << std::endl;
			system("pause");
			system("CLS");
			break;
		}
		case '3':
		{
			sortGraph();
			system("pause");
			system("CLS");
			break;
		}
		case '4':
		{
			printTableConnections();
			system("pause");
			system("CLS");
			break;
		}
		case '5':
		{
			if (!checkingConnections())
			{
				Console::PrintErrorText("\nСвязи отсуствуют, сначала создайте связь, только потом вы сможете найти кратчайшие пути.");
				system("pause");
				system("CLS");
				break;
			}
			fillMapCSInUse();
			fillMapPipeInUse();
			size_t idCSOut;
			size_t idCSIn;
			std::cout << "\nТаблица связей:" << std::endl;
			printTableConnections();
			while (true)
			{
				idCSOut = verification::GetNumericValue<size_t>("\nВведите id КС из графа, которая будет являться началом пути: ",
					"Id КС положительное целое число, при этом КС с таким id должна была создаться ранее!!!", 1, CompressorStation::GetMaxID());
				if (mapCSInUse.find(idCSOut) == mapCSInUse.end())
				{
					Console::PrintErrorText("КС с данным ID отсутствует в графе, просмотрите таблицу связей более внимательно и повторите ввод!");
					continue;
				}
				else
					break;
			}
			while (true)
			{
				idCSIn = verification::GetNumericValue<size_t>("\nВведите id КС из графа, которая будет являться концом пути: ",
					"Id КС положительное целое число, при этом КС с таким id должна была создаться ранее!!!", 1, CompressorStation::GetMaxID());
				if (mapCSInUse.find(idCSIn) == mapCSInUse.end())
				{
					Console::PrintErrorText("КС с данным ID отсутствует в графе, просмотрите таблицу связей более внимательно и повторите ввод!");
					continue;
				}
				else
					break;
			}
			try
			{
				std::vector<size_t> vectorPath = findPath(idCSOut, idCSIn);
				printPath(vectorPath);
			}
			catch (int)
			{
				Console::PrintErrorText("Извините, но пути из вершины " + std::to_string(idCSOut) + " в вершину " + std::to_string(idCSIn) + " не существует!");
			}
			system("pause");
			system("CLS");
			break;
		}
		case '0':
		{
			return;
		}
		default:
		{
			Console::PrintErrorText("\nВы осуществили неправильный ввод, попробуйте выбрать команду заново!");
			Sleep(2000);
			system("CLS");
			break;
		}
		}
	}
}


// Добавление труб и КС
void GasTransmissionNetwork::AddPipe()
{
	newPipeCollection.Add();
}

void GasTransmissionNetwork::AddCS()
{
	newCSCollection.Add();
}

// Редактирование по одной трубе и КС
void GasTransmissionNetwork::ChangePipe()
{
	newPipeCollection.Change();
}

void GasTransmissionNetwork::ChangeCS()
{
	newCSCollection.Change();
}

// Вывод таблиц Труб и КС
void GasTransmissionNetwork::PrintTablePipes()
{
	newPipeCollection.PrintTable();
}

void GasTransmissionNetwork::PrintTableCS()
{
	newCSCollection.PrintTable();
}

// Сохранение труб и КС в файл
void GasTransmissionNetwork::SaveToFilePipeCollection(std::ofstream& fout)
{
	newPipeCollection.SaveToFile(fout);
}

void GasTransmissionNetwork::SaveToFileCSCollection(std::ofstream& fout)
{
	newCSCollection.SaveToFile(fout);
}

// Загрузка труб и КС из файла
void GasTransmissionNetwork::DownloadFromFilePipeCollection(std::ifstream& fin)
{
	newPipeCollection.DownloadFromFile(fin);
}

void GasTransmissionNetwork::DownloadFromFileCSCollection(std::ifstream& fin)
{
	newCSCollection.DownloadFromFile(fin);
}

// Удаление труб и КС
void GasTransmissionNetwork::DeletePipe()
{
	newPipeCollection.Delete();
}

void GasTransmissionNetwork::DeleteCS()
{
	newCSCollection.Delete();
}

// Пакетное редактирование труб и КС
void GasTransmissionNetwork::BatchChangePipeCollection()
{
	newPipeCollection.BatchChange();
}

void GasTransmissionNetwork::BatchChangeCSCollection()
{
	newCSCollection.BatchChange();
}