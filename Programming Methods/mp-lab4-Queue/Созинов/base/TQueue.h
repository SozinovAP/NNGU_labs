#ifndef QUEUE_H
#define QUEUE_H


using namespace std;


const int MaxMemSize = 1000;

template <class T>
class TQueue
{
private:
	T* pMem;
	int size;					//������ ���������� ������
	int low;					//������ ������� ��������
	int top;					//������ ���������� ��������	
	int count;					//�-�� ����������� � ������� ���������	

public:
	TQueue(int _size = 1)
	{
		size = _size;
		low = 0;
		top = -1;
		count = 0;
		try
		{
			if ((size < 1) || (size > MaxMemSize))
				throw size;
		}
		catch (int c)
		{
			cout << "������������ �������� ������� ������� " << c << endl;
			cout << "������������ �������� ������� ������� " << c << endl;
			if (size < 1)
			{
				size = 1;
			}
			else if (size > MaxMemSize)
			{
				size = MaxMemSize;
			}
			cout << "������ ������� ������� �� " << size << endl;
		}
		pMem = new T[size];
	}

	~TQueue()
	{
		delete[] pMem;
	}

	bool IsEmpty();						//�������� �� �������
	bool IsFull();						//�������� �� �������
	void Push(const T Pval);			//�������� � ����
	void swap(int indexi, int indexj);	//�������� �������� �������
	T Pop();							//�������� ��������� ������� � ��� ��������� �� �������
	T GetLowElem();						//�������� ��������� �������
	T GetTopElem();						//�������� �������� �������
	T GetElemByIndex(int index);		//�������� ������� �� �������
	int GetSize();						//�������� ������ �������
	int GetCountElem();					//�������� ���������� ���������
	int GetLowIndex();					//�������� ������ ���������� ��������
	int GetTopIndex();					//�������� ������ ��������� ��������
	void GetNextIndex(int* index);		//�������� ��������� ������
	void GetPrevIndex(int* index);		//�������� ���������� ������
};

template <class T>
bool TQueue<T>::IsEmpty()							//�������� �� �������
{
	return (count == 0);
}

template <class T>
bool TQueue<T>::IsFull()							//�������� �� �������
{
	return (count == size);
}

template <class T>
void TQueue<T>::Push(const T Pval)					//�������� � ����
{
		if (IsFull())
			throw "Queue is Full";;
		GetNextIndex(&top);
		pMem[top] = Pval;
		count++;
}

template<class T>
void TQueue<T>::swap(int indexi, int indexj)				//�������� �������� �������
{
	T tmp = pMem[indexi];
	pMem[indexi] = pMem[indexj];
	pMem[indexj] = tmp;
}

template<class T>
T TQueue<T>::Pop()									//�������� ��������� ������� � ��� ��������� �� �������
{
	if (IsEmpty())
		throw "Queue is Empty";;
	T tmp = pMem[low];
	count--;
	GetNextIndex(&low);
	return tmp;
}

template <class T>
T TQueue<T>::GetLowElem()							//�������� ��������� �������
{
		if (this->IsEmpty())
			throw "Queue is Empty";
		return pMem[low];
}

template <class T>
T TQueue<T>::GetTopElem()							//�������� �������� �������
{
	if (this->IsEmpty())
		throw  "Queue is Empty";
	return pMem[top];
}

template<class T>
T TQueue<T>::GetElemByIndex(int index)		//�������� ������� �� �������
{
	try
	{
		if ((index < 0) || (index > (size - 1)))
			throw index;
		return pMem[index];
	}
	catch (int i)
	{
		cout << "Uncorrect index " << i << endl;
	}
}

template<class T>
int TQueue<T>::GetSize()					//�������� ������ �������
{
	return size;
}

template<class T>
inline int TQueue<T>::GetCountElem()			//�������� ���������� ���������
{
	return count;
}

template<class T>
int TQueue<T>::GetLowIndex()					//�������� ������ ���������� ��������
{
	return low;
}

template<class T>
int TQueue<T>::GetTopIndex()					//�������� ������ ��������� ��������
{
	return top;
}

template <class T>
void TQueue<T>::GetNextIndex(int* index)				//�������� ��������� ������
{
	*index = (++*index % size);
}

template<class T>
void TQueue<T>::GetPrevIndex(int* index)		//�������� ���������� ������
{
	*index = (--*index + size) % size;
}

	
#endif