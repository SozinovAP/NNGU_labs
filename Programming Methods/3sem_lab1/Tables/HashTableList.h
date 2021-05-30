#ifndef HASH_TABLE_LIST
#define HASH_TABLE_LIST

#include "Table.h"
#include <list>

using namespace std;


class HashTableList : public Table
{
private:
	class RecordHash : public Record
	{
	private:
		HashTableList* ptr;
		int listPos;

	public:
		list<RecordHash>::iterator listIterator;
		RecordHash() : Record()
		{
			ptr = nullptr;
			listPos = -1;
		}

		RecordHash(std::string name, Polynomial polynomial, HashTableList* ptr, int listPos) : Record(name, polynomial)
		{
			this->ptr = ptr;
			this->listPos = listPos;
		}

		Record* GetNext() override
		{
			list<RecordHash>::iterator nextIter = listIterator;
			nextIter++;

			list<RecordHash>* ourList = ptr->mas + listPos;
			if (nextIter == ourList->end())
			{
				int nextpos;
				for (nextpos = listPos + 1; nextpos < ptr->size; ++nextpos)
				{
					if (!(ptr->mas + nextpos)->empty())
					{
						break;
					}
				}
				if (nextpos == ptr->size)
				{
					return nullptr;
					//nextIter = ptr->mas[ptr->size - 1].end();
				}
				else
				{
					nextIter = ptr->mas[nextpos].begin();
				}
			}
			return nextIter.operator->();
		}

		friend class HashtableList;
	};
	list<RecordHash>* mas;
	int size;
	
	int hash(std::string name);	//вычисление хеша

public:
	
	HashTableList(int msize = 25);
	~HashTableList();

	Record* FindRecord(std::string name) override;	//поиск записи

	void Insert(std::string name, Polynomial& polynomial) override;	//вставка
	void Remove(std::string name) override;	//удаление
	void Clear() override;	//очистка таблицы

	//итераторы
	iterator begin() override;
	iterator end() override;

};

#endif HASH_TABLE_LIST
