#pragma once
#include "Table.h"

#define TableArray_NoSpaceIncreaseCount 5

class TableArray : public Table
{

protected:
	Record* FindRecord(std::string name) override;
private:
	Record* records;
	int length;
public:

	TableArray(int startLength=0);
	~TableArray();

	void Insert(std::string name, Polynomial& rec) override;
	void Remove(std::string name) override;
	void Clear() override;


	//итераторы
	iterator begin() override;
	iterator end() override;
};

