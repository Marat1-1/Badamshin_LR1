#include <string>
#include <fstream>

#ifndef CLASS_PIPE_H
#define CLASS_PIPE_H

// Класс Трубы
class Pipe
{
private:
	size_t id;
	static size_t maxIdPipe; // количество созданных элементов за всё время
public:
	double length;
	double diameter;
	bool repair;
	Pipe(); // в конструкторе идёт работа с пользователем, запрашиваются данные на ввод
	Pipe(std::ifstream&); // Конструктор для считывания из файла
	void GhangePipe();
	void SaveToFile(std::ofstream&);
	friend class PipeCollection;
};

#endif // !CLASS_PIPE_H
