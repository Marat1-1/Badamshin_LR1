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
void GasTransmissionNetwork::fillMapCSInUSe()
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
void GasTransmissionNetwork::findCSZeroDegreeOfOutcome(std::unordered_map<size_t, CompressorStation>& mapCS, std::unordered_map<size_t, Pipe>& mapPipe)
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

// Вывод отсортированного графа
void GasTransmissionNetwork::printSortGraph()
{
	for (auto id : sortIdCS)
	{
		std::cout << id << "  ";
	}
}

// Сортировка графа
void GasTransmissionNetwork::sortGraph()
{
	sortIdCS.clear();
	fillMapCSInUSe();
	fillMapPipeInUse();
	try
	{
		findCSZeroDegreeOfOutcome(mapCSInUse, mapPipeInUse);
		printSortGraph();
	}
	catch (int)
	{
		Console::PrintErrorText("\nТопологическая сортировка невозможна, поскольку граф является цикличным!!!");
	}
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