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
	double length;
	double diameter;
	bool repair;
	bool used;
public:
	Pipe(); // � ������������ ��� ������ � �������������, ������������� ������ �� ����
	Pipe(std::ifstream&); // ����������� ��� ���������� �� �����
	void GhangePipe();
	void SaveToFile(std::ofstream&);
	void SetUsed(bool);
	bool IsUsed() const;
	void SetInId(size_t);
	void SetOutId(size_t);
	bool GetRepairStatus() const;
	double GetLength() const;
	double GetProductivity() const;
	size_t GetInId() const;
	size_t GetOutId() const;
	static size_t GetMaxID();
	friend class PipeCollection;
};

#endif // !CLASS_PIPE_H