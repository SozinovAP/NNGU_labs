#include "TableList.h"

TableList::RecordList::RecordList()
{

}

TableList::RecordList::RecordList(std::string name, Polynomial polynomial, RecordList* prev, RecordList* next) : Record(name, polynomial)
{
	this->prev = prev;
	this->next = next;
	if (prev != nullptr)
		prev->next = this;
	if (next != nullptr)
		next->prev = this;
}

TableList::RecordList* TableList::RecordList::GetPrev()
{
	return prev;
}

TableList::RecordList* TableList::RecordList::GetNext()
{
	return next;
}

void TableList::RecordList::SetPrev(RecordList* prev)
{
	this->prev = prev;
}

void TableList::RecordList::SetNext(RecordList* next)
{
	this->next = next;
}

Record* TableList::FindRecord(std::string name)
{
	RecordList* curRecord = first;

	while ((curRecord != nullptr) && (*curRecord <= name))
	{
		if (name == *curRecord)
		{
			return curRecord;
		}

		curRecord = curRecord->GetNext();
	}

	return nullptr;
}

TableList::TableList()
{
	first = last = nullptr;
}

TableList::~TableList()
{
	Clear();
}

void TableList::Insert(std::string name, Polynomial& rec)
{
	RecordList* curRecord = first;
	RecordList* prevRecord = nullptr;

	while ((curRecord != nullptr) && (name >= *curRecord))
	{
		prevRecord = curRecord;
		curRecord = curRecord->GetNext();
	}

	if ((prevRecord != nullptr) && (name == *prevRecord))
	{
		throw "Item with same name already exists";
	}

	RecordList* newRecord = new RecordList(name, rec, prevRecord, curRecord);
	if (prevRecord == nullptr)
	{
		first = newRecord;
	}
	if (curRecord == nullptr)
	{
		last = newRecord;
	}

	DataCount++;

}

void TableList::Clear()
{
	RecordList* nxt = first;
	while (nxt != nullptr)
	{
		RecordList* del = nxt;
		nxt = nxt->GetNext();
		delete del;
	}
	DataCount = 0;
	first = last = nullptr;

}

void TableList::Remove(std::string name)
{
	RecordList* curRecord = (RecordList*)FindRecord(name);

	if (curRecord == nullptr)
	{
		throw "Item with this name not exists";
	}

	if (curRecord == first)
	{
		RecordList* nextRecord = curRecord->GetNext();
		first = nextRecord;
		if (nextRecord != nullptr)
		{
			nextRecord->SetPrev(nullptr);
		}
	}
	else if (curRecord == last)
	{
		RecordList* prevRecord = curRecord->GetPrev();
		last = prevRecord;
		if (prevRecord != nullptr)
		{
			prevRecord->SetNext(nullptr);
		}
	}
	else
	{
		curRecord->GetPrev()->SetNext(curRecord->GetNext());
		curRecord->GetNext()->SetPrev(curRecord->GetPrev());
	}
	delete curRecord;
	DataCount--;
}

Table::iterator TableList::begin()
{
	iterator tmp(first);
	return tmp;
}

Table::iterator TableList::end()
{
	if (last == nullptr)
	{
		iterator tmp(last);
		return tmp;
	}
	else
	{
		iterator tmp(last->GetNext());
		return tmp;
	}
}

/*
void TableList::Push(int pos, std::string name, Polynomial polynomial)
{
	if (pos < 0 || pos > DataCount)
		throw "wrong_pos";

	if (pos == 0)
	{
		head = new RecordList();
		return;
	}

	RecordList* prev = GetNode(pos - 1);
	prev->next = new Node<T>(value, prev->next);
	length++;
}

TableList::RecordList* TableList::GetRecord(int pos)
{
	if (DataCount == 0)
		throw "list_is_empty";
	if (pos < 0 || pos >= DataCount)
		throw "wrong_pos";

	RecordList res = head;
	for (int i = 1; i <= pos; i++)
		res = res->next;
	return res;
}
*/