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

	Record* FindRecord(std::string name) override; //поиск записи по имени для вставки

	void AddSize();						//увеличить размер массива
public:
	//Record* FindRecord(std::string name) override;	//поиск записи
	//Record* FindRecord(std::string name, int left, int right);

	void swap(Record* a, Record* b);	//swap записей
	void Sort(int left, int right);		//сортировка
	
	bool IsFull();						//проверка на переполнение

	ArraySortTable(int _MaxSize = 10);
	~ArraySortTable();

	std::string GetName(int pos);			//получить имя

	void Insert(std::string name, Polynomial& polynomial) override;	//вставка
	void Remove(std::string name) override;	//удаление
	void Clear() override;				//очистить таблицу

	//итераторы
	iterator begin() override;
	iterator end() override;
};

#endif ARRAY_SORT
