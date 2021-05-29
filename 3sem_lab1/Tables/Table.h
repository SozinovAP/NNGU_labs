#pragma once
#include <string>
#include <fstream>
#include "../Polynomial.h"

//�������� �������� ������
class Record
{
protected:
	std::string name;
public:
	Polynomial polynomial;

	Record() {}
	Record(std::string name, Polynomial polynomial);
	virtual Record* GetNext();
	std::string GetName() const;

	bool operator==(const std::string& other) const;
	bool operator!=(const std::string& other) const;
	bool operator<(const std::string& other) const;
	bool operator<=(const std::string& other) const;
	bool operator>(const std::string& other) const;
	bool operator>=(const std::string& other) const;

	bool operator==(const Record& other) const;
	bool operator!=(const Record& other) const;
	bool operator<(const Record& other) const;
	bool operator<=(const Record& other) const;
	bool operator>(const Record& other) const;
	bool operator>=(const Record& other) const;

	friend bool operator==(const std::string& str, const Record& record);
	friend bool operator!=(const std::string& str, const Record& record);
	friend bool operator<(const std::string& str, const Record& record);
	friend bool operator<=(const std::string& str, const Record& record);
	friend bool operator>(const std::string& str, const Record& record);
	friend bool operator>=(const std::string& str, const Record& record);
};



class Table
{
protected:

	int DataCount;//���������� �������
	virtual Record* FindRecord(std::string name) = 0;
public:

	

	class iterator
	{
	private:
		Record* ptr_;
	public:
		iterator(Record* ptr) : ptr_(ptr) {}
		iterator(const iterator& other) : ptr_(other.ptr_) {}
		iterator operator++() { ptr_ = ptr_->GetNext(); return *this; }
		iterator operator++(int junk) { iterator i = *this; ptr_ = ptr_->GetNext(); return i; }
		const Record& operator*() { return *ptr_; }
		const Record* operator->() { return ptr_; }
		bool operator==(const iterator& rhs) { return ptr_ == rhs.ptr_; }
		bool operator!=(const iterator& rhs) { return !(this->operator==(rhs)); }
	};

	Table();

	virtual int GetCount() const;												//�������� ���������� �������

	virtual void Insert(std::string name, Polynomial& polynomial) = 0;	//������� ������
	virtual void Remove(std::string name) = 0;							//�������� ������
	virtual void Clear() = 0;											//�������
	virtual Polynomial* Find(std::string name);									//����� ������, nullptr ���� �� �������
	virtual void Replace(std::string name, Polynomial& polynomial);				//������ ������

	//��������
	virtual bool IsEmpty() const;							//�������� �� �������

	//���������
	virtual iterator begin() = 0;
	virtual iterator end() = 0;

	//�����
	virtual void Read(std::string pFileName);						//������ �� �����
	virtual void Write(std::string pFileName);						//������ � �����

};