#ifndef ARRAY_SORT
#define ARRAY_SORT

#include "Table.h"

const int step = 10;

class ArraySortTable : public Table
{
private:
	int CurPos;
	int MaxSize;
	Record* mas;

	Record* FindRecord(std::string name) override; //����� ������ �� ����� ��� �������

	void AddSize();						//��������� ������ �������
public:
	//Record* FindRecord(std::string name) override;	//����� ������
	//Record* FindRecord(std::string name, int left, int right);

	void swap(Record* a, Record* b);	//swap �������
	void Sort(int left, int right);		//����������
	
	bool IsFull();						//�������� �� ������������

	ArraySortTable(int _MaxSize = 10);
	~ArraySortTable();

	std::string GetName(int pos);			//�������� ���

	void Insert(std::string name, Polynomial& polynomial) override;	//�������
	void Remove(std::string name) override;	//��������
	void Clear() override;				//�������� �������

	//���������
	iterator begin() override;
	iterator end() override;
};

#endif ARRAY_SORT
