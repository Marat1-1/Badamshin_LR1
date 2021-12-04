#include "GasTransmissionNetwork.h"
#include "Verification.h"
#include "Console.h"
#include <conio.h>

// Меню для работы с пользователем
void GasTransmissionNetwork::printMenu()
{
	Console::PrintTitleText("\n\t\t\t\tУправление Газотранспортной сетью\n");
	std::cout << "\nВыберите один из пунктов меню: " << std::endl
		<< "1. Добавить связь" << std::endl
		<< "2. Удалить связь" << std::endl
		<< "0. Выйти в общее меню" << std::endl
		<< "Ввод: ";
}

// Заполнение Сета id-никами свободных труб
void GasTransmissionNetwork::fillSetFreePipes()
{
	for (const auto& el : newPipeCollection.pipeCollection)
		if (!el.second.IsUsed())
			freePipes.insert(el.first);
}

// Заполнение Сета id-никами свободных КС
void GasTransmissionNetwork::fillSetFreeCS()
{
	for (const auto& el : newCSCollection.csCollection)
		if (!el.second.IsUsed())
			freeCS.insert(el.first);
}

// Вывод свободных труб и КС
void GasTransmissionNetwork::printFreePipes()
{
	std::vector<size_t> vectorForOutput;
	for (auto id : freePipes)
		if (!newPipeCollection.pipeCollection[id].IsUsed())
			vectorForOutput.push_back(id);
	newPipeCollection.PrintFilterTable(vectorForOutput);
}

void GasTransmissionNetwork::printFreeCS()
{
	std::vector<size_t> vectorForOutput;
	for (auto id : freeCS)
		if (!newCSCollection.csCollection[id].IsUsed())
			vectorForOutput.push_back(id);
	newCSCollection.PrintFilterTable(vectorForOutput);
}

// Функция управления Газотранспортной сетью
void GasTransmissionNetwork::manageNetwork()
{
	fillSetFreePipes();
	fillSetFreeCS();
	while (true)
	{
		printMenu();
		switch (_getch())
		{
		case '1':
		{
			if (freePipes.empty() || freeCS.empty())
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
				if (freePipes.find(idPipe) != freePipes.end())
				{
					while (true)
					{
						outId = verification::GetNumericValue<size_t>("\nВведите id КС из которой будет исходить указанная труба: ",
							"\nНекорректный ввод! Id целое положительное число, при этом КС с таким id должна быть создана, повторите ввод!", 1, CompressorStation::GetMaxID());
						if (freeCS.find(outId) != freeCS.end())
						{
							while (true)
							{
								inId = verification::GetNumericValue<size_t>("\nВведите id КС в которую будет входить указанная труба: ",
									"\nНекорректный ввод! Id целое положительное число, при этом КС с таким id должна быть создана, повторите ввод!", 1, CompressorStation::GetMaxID());
								if (inId != outId && freeCS.find(inId) != freeCS.end())
								{
									newPipeCollection.pipeCollection[idPipe].SetInId(inId);
									newPipeCollection.pipeCollection[idPipe].SetOutId(outId);
									newPipeCollection.pipeCollection[idPipe].SetUsed(true);
									freePipes.erase(idPipe);
									newCSCollection.csCollection[inId].IncCountUse();
									newCSCollection.csCollection[outId].IncCountUse();
									if (newCSCollection.csCollection[inId].IsUsed())
										freeCS.erase(inId);
									if (newCSCollection.csCollection[outId].IsUsed())
										freeCS.erase(outId);
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