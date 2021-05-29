#pragma once
#include "Table.h"


class TableList :public Table
{
protected:
	class RecordList : public Record
	{
	private:
		RecordList* next;
		RecordList* prev;

	public:

		RecordList();
		RecordList(std::string name, Polynomial polynomial, RecordList* next = nullptr, RecordList* prev = nullptr);

		RecordList* GetPrev();
		RecordList* GetNext();
		void SetPrev(RecordList* prev);
		void SetNext(RecordList* next);
	};

	RecordList* first;
	RecordList* last;

	Record* FindRecord(std::string name) override;
	//void Remove(RecordList* record);
	//void Clear(RecordList* start);

	//void Push(int pos, std::string name, Polynomial polynomial);
	//RecordList* GetRecord(int pos);
private:
public:
	TableList();
	~TableList();

	void Insert(std::string name, Polynomial& rec) override;
	void Remove(std::string name) override;
	void Clear() override;

	//итераторы
	iterator begin() override;
	iterator end() override;
};

