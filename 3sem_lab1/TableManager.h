#pragma once
#include "Tables/Table.h"
#include "List.h"

class TableManager: public Table
{
private:
	TList<Table*> tables;

	Record* FindRecord(std::string name) override;
public:

	void Insert(std::string name, Polynomial& rec) override;
	void Remove(std::string name) override;
	void Clear() override;

	int GetCount() const override;
	Polynomial* Find(std::string name) override;
	void Replace(std::string name, Polynomial& polynomial) override;
	bool IsEmpty() const override;

	iterator begin() override;
	iterator end() override;

	void Read(std::string pFileName) override;
	void Write(std::string pFileName) override;

	std::string FindNameByPart(std::string str, int num);
	void AddTable(Table* table);
	Table* GetTable(int num);
	int GetTablesCount();
};

