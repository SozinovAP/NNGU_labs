#include "Table.h"
#include "../Parser/Parser.h"

using namespace std;

Record::Record(std::string name, Polynomial polynomial)
{
	this->name = name;
	this->polynomial = polynomial;
}

Record* Record::GetNext()
{
	return (this + 1);
}

string Record::GetName() const
{
	return name;
}


Table::Table()
{
	DataCount = 0;
}

int Table::GetCount() const
{
	return DataCount;
}

Polynomial* Table::Find(string name)
{
	Record* result = FindRecord(name);
	return (result == nullptr ? nullptr : &(result->polynomial));
}
void Table::Replace(std::string name, Polynomial& polynomial)
{
	Record* result = FindRecord(name);
	if (result == nullptr)
	{
		throw "Item for replace not found";
	}

	result->polynomial = polynomial;
}


bool Table::IsEmpty() const
{
	return (DataCount == 0);
}

void Table::Read(string pFileName)
{
	ifstream file;
	file.open(pFileName);

	if (!file.fail())
	{
		while (!file.eof())
		{
			string str;
			getline(file, str);
			if(str!="")
				Parser::Parse(str, this);
		}
		file.close();
	}
	else
	{
		throw "File does not exist";
	}
}

void Table::Write(string pFileName)
{
	ofstream file;
	file.open(pFileName);

	for (auto it = begin(); it != end(); it++)
	{
		file << (*it).GetName() << "=" << (*it).polynomial << endl;
	}
		
	file.close();
}

#pragma region Compare operators
bool Record::operator==(const string& other) const
{
	return name == other;
}

bool Record::operator!=(const string& other) const
{
	return !(this->operator==(other));
}

bool Record::operator<(const string& other) const
{
	return (name.length() < other.length() || (name.length() == other.length() && name < other));
}

bool Record::operator<=(const string& other) const
{
	return (this->operator==(other) || this->operator<(other));
}

bool Record::operator>(const string& other) const
{
	return !(this->operator<=(other));
}

bool Record::operator>=(const string& other) const
{
	return !(this->operator<(other));
}

bool Record::operator==(const Record& other) const
{
	return (this->operator==(other.name));
}

bool Record::operator!=(const Record& other) const
{
	return (this->operator!=(other.name));
}

bool Record::operator<(const Record& other) const
{
	return (this->operator<(other.name));
}

bool Record::operator<=(const Record& other) const
{
	return (this->operator<=(other.name));
}

bool Record::operator>(const Record& other) const
{
	return (this->operator>(other.name));
}

bool Record::operator>=(const Record& other) const
{
	return (this->operator>=(other.name));
}

bool operator==(const string& str, const Record& record)
{
	return (record.operator==(str));
}

bool operator!=(const string& str, const Record& record)
{
	return (record.operator!=(str));
}

bool operator<(const string& str, const Record& record)
{
	return (record.operator>(str));
}

bool operator<=(const string& str, const Record& record)
{
	return (record.operator>=(str));
}

bool operator>(const string& str, const Record& record)
{
	return (record.operator<(str));
}

bool operator>=(const string& str, const Record& record)
{
	return (record.operator<=(str));
}

#pragma endregion