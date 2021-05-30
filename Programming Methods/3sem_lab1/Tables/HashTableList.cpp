#include "HashTableList.h"


HashTableList::HashTableList(int msize) : Table()
{
	size = msize;
	mas = new list<RecordHash>[size];
}

HashTableList::~HashTableList()
{
	delete[] mas;
}

int HashTableList::hash(std::string name)	//вычисление хеша
{
	int pos = 0;

	for(auto i = 0; i < name.length(); ++i)
	{
		pos += static_cast<int>(name[i]);
	}
	
	return ((name.length() * pos) % size);
}

Record* HashTableList::FindRecord(std::string name)	//поиск записи
{
	int i = hash(name);	//индекс
	list<RecordHash>::iterator it = mas[i].begin();
	while(it != mas[i].end())
	{
		if (*it == name)
			return &(*it);
		++it;
	}
	return nullptr;
}

void HashTableList::Insert(std::string name, Polynomial& polynomial)	//вставка
{	
	if (FindRecord(name) != nullptr)
	{
		throw "Item already exists";
	}
	
	int i = hash(name);
	RecordHash rec(name, polynomial, this, i);
	mas[i].emplace_back(rec);
	list<RecordHash>::iterator it(--mas[i].end());
	(*it).listIterator = it;
	DataCount++;
}

void HashTableList::Remove(std::string name)	//удаление
{
	int i = hash(name);
	if (mas[i].empty())
	{
		throw "No elements";
	}
	if (FindRecord(name) == nullptr)
	{
		throw "Item doesn't exists";
	}

	mas[i].erase(find(mas[i].begin(), mas[i].end(), name));
	DataCount--;
}

void HashTableList::Clear()	//очистка таблицы
{
	delete[] mas;
	DataCount = 0;
	mas = new list<RecordHash>[size];
}

Table::iterator HashTableList::begin()
{
	int i = 0;
	while ((i < size))
	{
		if (!mas[i].empty())
		{
			iterator tmp(mas[i].begin().operator->());
			return tmp;
		}
		++i;
	}
	return end();
}

Table::iterator HashTableList::end()
{
	//iterator tmp(mas[size - 1].end().operator->());
	iterator tmp(nullptr);
	return tmp;
}

