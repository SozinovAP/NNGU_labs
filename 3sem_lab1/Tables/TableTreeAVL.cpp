#include "TableTreeAVL.h"

TableTreeAVL::RecordTreeAVL::RecordTreeAVL()
{
	leftChild = nullptr;
	rightChild = nullptr;
	parent = nullptr;
	heightDiff = 0;
	isLeftChild = false;
}
TableTreeAVL::RecordTreeAVL::RecordTreeAVL(std::string name, Polynomial polynomial) :Record(name, polynomial)
{
	this->leftChild = nullptr;
	this->rightChild = nullptr;
	this->parent = nullptr;
	this->heightDiff = 0;
	this->isLeftChild = false;
}
Record* TableTreeAVL::RecordTreeAVL::GetNext()
{
	if (rightChild != nullptr)
	{
		RecordTreeAVL* nextByValue = rightChild;
		while (nextByValue->GetChild(true) != nullptr)
		{
			nextByValue = nextByValue->GetChild(true);
		}

		return nextByValue;
	}
	else
	{
		if (isLeftChild)
		{
			return parent;
		}
		else
		{
			RecordTreeAVL* curr = this;
			while (!curr->isLeftChild && curr->parent != nullptr)
			{
				curr = curr->parent;
			}

			RecordTreeAVL* parent = curr->parent;
			if (parent != nullptr)
			{
				return curr = parent;
			}

			return curr;
		}
	}
}
void TableTreeAVL::RecordTreeAVL::SetChild(RecordTreeAVL* child, bool left)
{
	RecordTreeAVL* prevChild = (left ? leftChild : rightChild);
	if (prevChild != nullptr)
	{
		prevChild->parent = nullptr;
	}
	(left ? leftChild : rightChild) = child;
	if (child != nullptr)
	{
		if (child->parent != nullptr)
		{
			child->parent->SetChild(nullptr, child->isLeftChild);
		}

		child->parent = this;
		child->isLeftChild = left;
	}
}
TableTreeAVL::RecordTreeAVL* TableTreeAVL::RecordTreeAVL::GetChild(bool left)
{
	return (left ? leftChild : rightChild);
}
TableTreeAVL::RecordTreeAVL* TableTreeAVL::RecordTreeAVL::GetParent()
{
	return parent;
}

void TableTreeAVL::RecordTreeAVL::Rotate(bool leftChild)
{
	RecordTreeAVL* child = GetChild(leftChild);
	GetParent()->SetChild(child, isLeftChild);
	if (child != nullptr)
	{
		SetChild(child->GetChild(!leftChild), leftChild);
		child->SetChild(this, !leftChild);
	}
}


Record* TableTreeAVL::FindRecord(std::string name)
{
	bool nextLeft = firstRecordLeft;
	RecordTreeAVL* curRecord = head.GetChild(nextLeft);
	

	//go down, looking for parent for newRecord
	while (curRecord != nullptr)
	{
		if (name == *curRecord)
		{
			return curRecord;
		}
		nextLeft = name < *curRecord;

		curRecord = curRecord->GetChild(nextLeft);
	}

	return nullptr;
}
bool TableTreeAVL::Balance(RecordTreeAVL* record)
{
	if (record == nullptr)
	{
		return false;
	}

	int heightDiff = record->heightDiff;
	if (heightDiff ==2 || heightDiff ==-2)
	{
		bool badChildLeft = heightDiff == 2;
		RecordTreeAVL* badChild = record->GetChild(badChildLeft);

		//if big rotation
		if(-heightDiff/2 == badChild->heightDiff)
		{
			RecordTreeAVL* badChildChild = badChild->GetChild(!badChildLeft);
			int k = badChildChild->heightDiff;
			badChild->Rotate(!badChildLeft);
			record->Rotate(badChildLeft);

			badChildChild->heightDiff = 0;	
			record->heightDiff = (k < 0 ? 1 : 0);
			badChild->heightDiff = (k < 0 ? 0 : -k);
		}
		else
		{
			int k = badChild->heightDiff;
			record->Rotate(badChildLeft);
			record->heightDiff = (k == 0 ? -1 : 0);
			badChild->heightDiff = (k == 0 ? 1 : 0);
		}
		return true;
	}
	return false;
}



TableTreeAVL::TableTreeAVL()
{
	height = 0;
	minRecord = &head;
}

TableTreeAVL::~TableTreeAVL()
{
	Clear();
}

void TableTreeAVL::Insert(std::string name, Polynomial& rec)
{
	RecordTreeAVL* curRecord = head.GetChild(firstRecordLeft);
	RecordTreeAVL* parentRecord = &head;
	bool nextLeft = firstRecordLeft;

	//go down, looking for parent for newRecord
	while (curRecord != nullptr)
	{
		if (name == *curRecord)
		{
			throw "Item with same name already exists";
		}
		nextLeft = name < *curRecord;

		parentRecord = curRecord;
		curRecord = curRecord->GetChild(nextLeft);
	}
	RecordTreeAVL* newRecord = new RecordTreeAVL(name, rec);
	parentRecord->SetChild(newRecord, nextLeft);

	//go up, updating heightDiff
	curRecord = parentRecord;
	bool prevRecordLeft = newRecord->isLeftChild;
	bool afterBalance = false;
	while (curRecord != &head)
	{
		if (!afterBalance)
		{
			curRecord->heightDiff += (prevRecordLeft ? 1 : -1);
		}
		afterBalance = Balance(curRecord);

		if (curRecord->heightDiff == 0)
		{
			break;
		}
		else if (curRecord==head.GetChild(firstRecordLeft))
		{
			height++;
		}

		prevRecordLeft = curRecord->isLeftChild;
		curRecord = curRecord->GetParent();
	}
	if (DataCount == 0)
	{
		minRecord = newRecord;
		height++;
	}
	else if(newRecord->isLeftChild && newRecord->GetParent()==minRecord)
	{
		minRecord = newRecord;
	}
	DataCount++;
}

void TableTreeAVL::Remove(RecordTreeAVL* record)
{
	RecordTreeAVL* rightChild = record->GetChild(false);
	if (rightChild == nullptr)
	{
		RecordTreeAVL* leftChild = record->GetChild(true);
		if (leftChild == nullptr)
		{
			RecordTreeAVL* parent = record->GetParent();
			if (record == minRecord)
			{
				minRecord = parent;
			}
			parent->SetChild(nullptr, record->isLeftChild);
			bool prevChildLeft = record->isLeftChild;
			delete record;
			bool afterBalance = false;
			while (parent != &head)
			{
				if (!afterBalance)
				{
					parent->heightDiff -= (prevChildLeft ? 1 : -1);
				}
				afterBalance = Balance(parent);
				

				if (parent->heightDiff != 0)
				{
					break;
				}
				else if (parent == head.GetChild(firstRecordLeft))
				{
					height--;
				}

				prevChildLeft = parent->isLeftChild;
				parent = parent->GetParent();
			}
			if (DataCount == 1)
			{
				height--;
			}

			DataCount--;
		}
		else
		{
			record->Rotate(true);
			record->GetParent()->heightDiff = -record->heightDiff;//-1
			record->heightDiff = 0;
			Remove(record);
		}
	}
	else
	{
		//looking for next by deleterecord value
		RecordTreeAVL* nextByValue = rightChild;
		while (nextByValue->GetChild(true) != nullptr)
		{
			nextByValue = nextByValue->GetChild(true);
		}

		if (nextByValue->GetParent() == record)
		{
			record->Rotate(false);
			record->heightDiff = -record->heightDiff;
			nextByValue->heightDiff = -nextByValue->heightDiff;
		}
		else
		{
			record->SetChild(nextByValue->GetChild(false), false);
			nextByValue->SetChild(record->GetChild(true), true);
			nextByValue->SetChild(rightChild, false);

			RecordTreeAVL* nextByValueParent = nextByValue->GetParent();
			record->GetParent()->SetChild(nextByValue, record->isLeftChild);
			nextByValueParent->SetChild(record, true);
			
		}

		Remove(record);
	}
}

void TableTreeAVL::Clear()
{
	Clear(head.GetChild(firstRecordLeft));
	head.SetChild(nullptr, firstRecordLeft);
	DataCount = 0;
}
void TableTreeAVL::Clear(RecordTreeAVL* start)
{
	if (start == nullptr)
	{
		return;
	}
	Clear(start->GetChild(true));
	Clear(start->GetChild(false));
	delete start;
}

void TableTreeAVL::Remove(std::string name)
{
	RecordTreeAVL* deleteRecord = (RecordTreeAVL*)FindRecord(name);
	if (deleteRecord == nullptr)
	{
		throw "Item with that name doesn't exist";
	}
	Remove(deleteRecord);
}


int TableTreeAVL::GetHeight()
{
	return height;
}

Table::iterator TableTreeAVL::begin()
{
	iterator tmp(minRecord);
	return tmp;
}

Table::iterator TableTreeAVL::end()
{
	iterator tmp(&head);
	return tmp;
}