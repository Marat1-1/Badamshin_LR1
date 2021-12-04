#include <string>
#include <fstream>


#ifndef CLASS_PIPE_H
#define CLASS_PIPE_H

// Класс Трубы
class Pipe
{
private:
	size_t id;
	static size_t maxIdPipe; // максимальный id среди элементов
	size_t inId = 0;
	size_t outId = 0;
	bool used;
public:
	double length;
	double diameter;
	bool repair;
	Pipe(); // в конструкторе идёт работа с пользователем, запрашиваются данные на ввод
	Pipe(std::ifstream&); // Конструктор для считывания из файла
	void GhangePipe();
	void SaveToFile(std::ofstream&);
	void SetUsed(bool);
	bool IsUsed() const;
	void SetInId(size_t);
	void SetOutId(size_t);
	size_t GetInId() const;
	size_t GetOutId() const;
	static size_t GetMaxID();
	friend class PipeCollection;
};

#endif // !CLASS_PIPE_H