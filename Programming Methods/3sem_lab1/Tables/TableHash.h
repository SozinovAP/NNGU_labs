#pragma once
#include "Table.h"





class TableHash : public Table
{

protected:
	class RecordHash : public Record
	{
	public:
		bool busy;
		RecordHash* last;
	
		RecordHash();
		RecordHash(std::string name, Polynomial polynomial, bool busy, RecordHash* last) : Record(name, polynomial)
		{
			this->busy = busy;
			this->last = last;
		}
		
		Record* GetNext() override;
	};

	Record* FindRecord(std::string name) override;
private:
	RecordHash* records;
	int length;
	int Hash(std::string name, int length);
	int RelativePrime(int n);
public:
	TableHash(int startLength = 1);
	~TableHash();

	iterator begin() override;
	iterator end() override;

	void Insert(std::string name, Polynomial& rec) override;
	void Remove(std::string name) override;
	void Clear() override;
};

