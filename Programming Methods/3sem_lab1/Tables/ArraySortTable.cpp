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

Record* ArraySortTable::FindRecord(std::string name) //поиск записи по имени для вставки
{
	Record tmp;
	int left = 0;
	int right = DataCount - 1;
	int middle = 0;

	if(IsEmpty())		//если пустой массив
	{
		CurPos = 0;
		return nullptr;
	}
	
	while (left <= right)
	{
		if (mas[0].GetName() > name) //если искомый элемент меньше первого в массиве
		{
			CurPos = 0;
			return nullptr;
		}

		if (mas[right].GetName() < name)	//если искомы элемент больше последнего в массиве
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

void ArraySortTable::swap(Record* a, Record* b) //swap записей
{
	Record tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

void ArraySortTable::Sort(int left, int right)	//сортировка
{
	Record p;
	int l = left;
	int r = right;
	p = mas[(l + r) / 2]; //опорный элемент

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
	} while (l <= r); //пока не сойдутся границы

	if (left < r)
		Sort(left, r);
	if (l < right)
		Sort(l, right);
}

void ArraySortTable::AddSize()	//увеличить размер массива
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

/*Record* ArraySortTable::FindRecord(std::string name, int left, int right)	//поиск записи
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

/*Record* ArraySortTable::FindRecord(std::string name)	//поиск записи
{
	return FindRecord(name, 0, DataCount - 1);
}*/

std::string ArraySortTable::GetName(int pos)	//получить имя
{
	if ((pos < 0) || (pos > DataCount - 1))
		throw "uncorrect position";
	else
		return mas[pos].GetName();
}

inline bool ArraySortTable::IsFull() //проверка на переполнение
{
	return (MaxSize == DataCount);
}

void ArraySortTable::Insert(std::string name, Polynomial& polynomial)	//вставка
{
	if (!IsEmpty())
		if (FindRecord(name) != nullptr)
		{
			throw "Item already exists";
		}
	
	if (IsFull())	//если массив заполнен, расширить
	{
		AddSize();
	}
	//сдвиг элементов на 1 вправо для вставки
	for (int i = DataCount; i > CurPos; --i)	
	{
		mas[i] = mas[i - 1];
	}
	Record rec(name, polynomial);
	mas[CurPos] = rec;
	
	DataCount++;
}

void ArraySortTable::Remove(std::string name)	//удаление
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

void ArraySortTable::Clear()	//очистить таблицу
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

