//#pragma once
#ifndef LIST_H
#define LIST_H

#include <string>
#include <algorithm>

template <typename T>
struct Node
{
	T value;
	Node* next;

	Node(T value, Node* next = nullptr)
	{
		this->value = value;
		this->next = next;
	}
};

template <typename T>
class TList
{
private:
	Node<T>* head;
	int length;
public:
	TList()
	{
		head = nullptr;
		length = 0;
	}
	~TList() { Clear(); }

	TList(const TList& list)
	{
		if (list.length == 0)
		{
			head = nullptr;
			length = 0;
			return;
		}

		Node<T>* last = head = new Node<T>(list.head->value);
		length = 1;

		if (list.length < 2) return;

		Node<T>* next = list.head->next;

		while (next != nullptr)
		{
			last->next = new Node<T>(next->value);
			last = last->next;
			length++;
			next = next->next;
		}
	}

	TList& operator= (const TList &list)
	{
		if (this == &list) return *this;

		Clear();
		length = 0;

		if (list.length < 1) return *this;

		Node<T>* last = head = new Node<T>(list.head->value);
		length = 1;

		if (list.length < 2) return *this;

		Node<T>* next = list.head->next;

		while (next != nullptr)
		{
			last->next = new Node<T>(next->value);
			last = last->next;
			length++;
			next = next->next;
		}

		return *this;
	}

	T &operator[] (int i) { return Get(i); }
	T &operator[] (int i) const { return Get(i); }

	Node<T>* GetNode(int pos) const
	{
		if (length == 0)
			throw "list_is_empty";
		if (pos < 0 || pos >= length)
			throw "wrong_pos";

		Node<T>* res = head;
		for (int i = 1; i <= pos; i++)
			res = res->next;
		return res;
	}


	bool IsEmpty() { return length == 0; }
	int GetLength() const { return length; }
	void Clear()
	{
		Node<T>* now = head;
		while (now != nullptr)
		{
			Node<T>* del = now;
			now = now->next;
			delete del;
		}

		head = nullptr;
		length = 0;
	}
	void Sort(bool increase = true)
	{
		if (length < 2)
			return;

		for (int i = 0; i < length-1; i++)
		{
			Node<T> *cur = head;
			Node<T> *prev = nullptr;
			for (int j = 0; j < length-1 - i; j++)
			{
				if (increase)
				{
					if (cur->next->value < cur->value)
					{
						Node<T> * prevNext = cur->next;
						cur->next = prevNext->next;
						prevNext->next = cur;
						if (j > 0) prev->next = prevNext;
						else head = prevNext;
					}
				}
				else if (cur->value < cur->next->value)
				{
					Node<T> * prevNext = cur->next;
					cur->next = prevNext->next;
					prevNext->next = cur;
					if (j > 0) prev->next = prevNext;
					else head = prevNext;
				}
				if (j > 0) prev = prev->next;
				else prev = head;

				cur = prev->next;
			}
		}
	}

	T& Front() { return GetNode(0)->value; }
	T& Back() { return GetNode(length - 1)->value; }
	T& Get(int pos) { return GetNode(pos)->value; }
	T& Get(int pos) const { return GetNode(pos)->value; }

	T Pop_Front()
	{
		if (length == 0)
			throw "list_is_empty";

		Node<T> *del = head;
		head = head->next;
		length--;

		T value = del->value;
		delete del;

		return value;
	}
	T Pop_Back() { return Pop(length - 1); }
	T Pop(int pos)
	{
		if (pos == 0)
		{
			return Pop_Front();
		}
		
		if (length == 0)
			throw "list_is_empty";
		if (pos < 0 || pos >= length)
			throw "wrong_pos";

		Node<T> *prev = GetNode(pos - 1);
		Node<T> *del = prev->next;
		prev->next = del->next;
		length--;

		T value = del->value;
		delete del;

		return value;
	}

	void Push_Front(T value)
	{
		head = new Node<T>(value, head);
		length++;
	}
	void Push_Back(T value) { Push(length, value); }
	void Push(int pos, T value)
	{
		if (pos < 0 || pos > length)
			throw "wrong_pos";

		if (pos == 0)
		{
			Push_Front(value);
			return;
		}

		Node<T> *prev = GetNode(pos - 1);
		prev->next = new Node<T>(value, prev->next);
		length++;
	}

};

#endif LIST_H

