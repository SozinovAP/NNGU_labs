#include "ArraySortTable.h"



ArraySortTable::ArraySortTable(int _MaxSize) : Table()
{
	CurPos = 0;
	MaxSize = _MaxSize;
	mas = new Record[MaxSize];
}

ArraySortTable::~ArraySortTable()
{
	delete[] mas;
}

Record* ArraySortTable::FindRecord(std::string name) //����� ������ �� ����� ��� �������
{
	Record tmp;
	int left = 0;
	int right = DataCount - 1;
	int middle = 0;

	if(IsEmpty())		//���� ������ ������
	{
		CurPos = 0;
		return nullptr;
	}
	
	while (left <= right)
	{
		if (mas[0].GetName() > name) //���� ������� ������� ������ ������� � �������
		{
			CurPos = 0;
			return nullptr;
		}

		if (mas[right].GetName() < name)	//���� ������ ������� ������ ���������� � �������
		{
			CurPos = right + 1;
			return nullptr;
		}
		
		middle = (left + right) / 2;
		if (mas[middle].GetName() < name)
		{
			left = middle + 1;
		}
		else if (mas[middle].GetName() > name)
		{
			right = middle - 1;
		}
		else
		{
			CurPos = middle;
			return &mas[middle];
		}
		CurPos = middle;

	}

	return nullptr;
}

void ArraySortTable::swap(Record* a, Record* b) //swap �������
{
	Record tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

void ArraySortTable::Sort(int left, int right)	//����������
{
	Record p;
	int l = left;
	int r = right;
	p = mas[(l + r) / 2]; //������� �������

	do
	{
		while (mas[l] < p)
			l++;
		while (mas[r] > p)
			r--;

		if (l <= r)
		{
			swap(&mas[l], &mas[r]);
			l++;
			r--;
		}
	} while (l <= r); //���� �� �������� �������

	if (left < r)
		Sort(left, r);
	if (l < right)
		Sort(l, right);
}

void ArraySortTable::AddSize()	//��������� ������ �������
{
	MaxSize += step;
	Record* tmp = new Record[MaxSize];
	for (auto i = 0; i < DataCount; ++i)
	{
		tmp[i] = mas[i];
	}
	delete[] mas;

	mas = tmp;
}

/*Record* ArraySortTable::FindRecord(std::string name, int left, int right)	//����� ������
{
	Record tmp;
	int middle = (left + right) / 2;

	if (left == middle)
	{
		if (mas[middle].GetName() == name)
		{
			return &mas[middle];
		}
		return nullptr;
	}
	if (mas[middle].GetName() < name)
	{
		return FindRecord(name, middle + 1, right);
	}
	else if (mas[middle].GetName() > name)
	{
		return FindRecord(name, left, middle - 1);
	}
	else
	{
		return &mas[middle];
	}
}*/

/*Record* ArraySortTable::FindRecord(std::string name)	//����� ������
{
	return FindRecord(name, 0, DataCount - 1);
}*/

std::string ArraySortTable::GetName(int pos)	//�������� ���
{
	if ((pos < 0) || (pos > DataCount - 1))
		throw "uncorrect position";
	else
		return mas[pos].GetName();
}

inline bool ArraySortTable::IsFull() //�������� �� ������������
{
	return (MaxSize == DataCount);
}

void ArraySortTable::Insert(std::string name, Polynomial& polynomial)	//�������
{
	if (!IsEmpty())
		if (FindRecord(name) != nullptr)
		{
			throw "Item already exists";
		}
	
	if (IsFull())	//���� ������ ��������, ���������
	{
		AddSize();
	}
	//����� ��������� �� 1 ������ ��� �������
	for (int i = DataCount; i > CurPos; --i)	
	{
		mas[i] = mas[i - 1];
	}
	Record rec(name, polynomial);
	mas[CurPos] = rec;
	
	DataCount++;
}

void ArraySortTable::Remove(std::string name)	//��������
{
	if (IsEmpty())
	{
		throw "Table is empty";
	}
	if (FindRecord(name) == nullptr)
	{
		throw "Item doesn't exists";
	}

	for (auto i =  CurPos; i < DataCount - 1; ++i)
	{
		mas[i] = mas[i + 1];
	}
	DataCount--;
}

void ArraySortTable::Clear()	//�������� �������
{
	delete[] mas;
	DataCount = 0;
	mas = new Record[MaxSize];
}

Table::iterator ArraySortTable::begin()
{
	iterator it(mas);
	return it;
}

Table::iterator ArraySortTable::end()
{
	iterator it(mas + DataCount);
	return it;
}

