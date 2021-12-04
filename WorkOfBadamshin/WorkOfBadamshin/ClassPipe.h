#include <string>
#include <fstream>


#ifndef CLASS_PIPE_H
#define CLASS_PIPE_H

// ����� �����
class Pipe
{
private:
	size_t id;
	static size_t maxIdPipe; // ������������ id ����� ���������
	size_t inId = 0;
	size_t outId = 0;
	bool used;
public:
	double length;
	double diameter;
	bool repair;
	Pipe(); // � ������������ ��� ������ � �������������, ������������� ������ �� ����
	Pipe(std::ifstream&); // ����������� ��� ���������� �� �����
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