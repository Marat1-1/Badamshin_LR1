#include <string>
#include <fstream>


#ifndef CLASS_PIPE_H
#define CLASS_PIPE_H

// ����� �����
class Pipe
{
private:
	size_t id;
	static size_t maxIdPipe; // ���������� ��������� ��������� �� �� �����
public:
	double length;
	double diameter;
	bool repair;
	size_t inId = 0;
	size_t outId = 0;
	bool used;
	Pipe(); // � ������������ ��� ������ � �������������, ������������� ������ �� ����
	Pipe(std::ifstream&); // ����������� ��� ���������� �� �����
	void GhangePipe();
	void SaveToFile(std::ofstream&);
	friend class PipeCollection;
};

#endif // !CLASS_PIPE_H
