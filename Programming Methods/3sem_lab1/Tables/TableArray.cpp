#include "TableArray.h"

Record* TableArray::FindRecord(std::string name)
{
	for (size_t i = 0; i < DataCount; i++)
	{
		if (records[i] == name)
		{
			return (records+i);
		}
	}

	return nullptr;
}

TableArray::TableArray(int startLength)
{
	length = startLength;
	records = new Record[length];
}

TableArray::~TableArray()
{
	delete[] records;
}

void TableArray::Insert(std::string name, Polynomial& polynomial)
{
	Record* foundRecord = FindRecord(name);

	if (foundRecord != nullptr)
	{
		throw "Item already exists";
	}

	
	if (DataCount < length)
	{
		Record tmp(name, polynomial);
		records[DataCount] = tmp;
		DataCount++;
	}
	else
	{
		// if DataCount==length update records
		length += TableArray_NoSpaceIncreaseCount;
		Record* newRecords = new Record[length];
		for (int i=0; i < DataCount; i++)
		{
			newRecords[i] = records[i];
		}
		Record tmp(name, polynomial);
		newRecords[DataCount] = tmp;
		DataCount++;
		delete[] records;
		records = newRecords;
	}
}

void TableArray::Remove(std::string name)
{
	Record* foundRecord = FindRecord(name);
	if (foundRecord == nullptr)
	{
		throw "Item doesn't exist";
	}

	int stId = foundRecord - records;
	DataCount--;
	for (int i = stId; i < DataCount; i++)
	{
		records[i] = records[i + 1];
	}
	
}

void TableArray::Clear()
{
	delete[] records;
	DataCount = 0;
	length = 0;
	records = new Record[length];
	
}

Table::iterator TableArray::begin()
{
	iterator tmp(records);
	return tmp;
}

Table::iterator TableArray::end()
{
	iterator tmp(records + DataCount);
	return tmp;
}
