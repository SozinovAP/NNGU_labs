#ifndef QUEUE_H
#define QUEUE_H


using namespace std;


const int MaxMemSize = 1000;

template <class T>
class TQueue
{
private:
	T* pMem;
	int size;					//размер выделенной памяти
	int low;					//индекс первого элемента
	int top;					//индекс последнего элемента	
	int count;					//к-во заполненных в очереди элементов	

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
			cout << "Некорректное значение размера очереди " << c << endl;
			cout << "Некорректное значение размера очереди " << c << endl;
			if (size < 1)
			{
				size = 1;
			}
			else if (size > MaxMemSize)
			{
				size = MaxMemSize;
			}
			cout << "Размер очереди изменен на " << size << endl;
		}
		pMem = new T[size];
	}

	~TQueue()
	{
		delete[] pMem;
	}

	bool IsEmpty();						//проверка на пустоту
	bool IsFull();						//проверка на полноту
	void Push(const T Pval);			//добавить в стек
	void swap(int indexi, int indexj);	//поменять элементы местами
	T Pop();							//получить начальный элемент с его удалением из очереди
	T GetLowElem();						//получить начальный элемент
	T GetTopElem();						//получить конечный элемент
	T GetElemByIndex(int index);		//получить элемент по индексу
	int GetSize();						//получить размер очереди
	int GetCountElem();					//получить количество элементов
	int GetLowIndex();					//получить индекс начального элемента
	int GetTopIndex();					//получить индекс конечного элемента
	void GetNextIndex(int* index);		//получить следующий индекс
	void GetPrevIndex(int* index);		//получить предыдущий индекс
};

template <class T>
bool TQueue<T>::IsEmpty()							//проверка на пустоту
{
	return (count == 0);
}

template <class T>
bool TQueue<T>::IsFull()							//проверка на полноту
{
	return (count == size);
}

template <class T>
void TQueue<T>::Push(const T Pval)					//добавить в стек
{
		if (IsFull())
			throw "Queue is Full";;
		GetNextIndex(&top);
		pMem[top] = Pval;
		count++;
}

template<class T>
void TQueue<T>::swap(int indexi, int indexj)				//поменять элементы местами
{
	T tmp = pMem[indexi];
	pMem[indexi] = pMem[indexj];
	pMem[indexj] = tmp;
}

template<class T>
T TQueue<T>::Pop()									//получить начальный элемент с его удалением из очереди
{
	if (IsEmpty())
		throw "Queue is Empty";;
	T tmp = pMem[low];
	count--;
	GetNextIndex(&low);
	return tmp;
}

template <class T>
T TQueue<T>::GetLowElem()							//получить начальный элемент
{
		if (this->IsEmpty())
			throw "Queue is Empty";
		return pMem[low];
}

template <class T>
T TQueue<T>::GetTopElem()							//получить конечный элемент
{
	if (this->IsEmpty())
		throw  "Queue is Empty";
	return pMem[top];
}

template<class T>
T TQueue<T>::GetElemByIndex(int index)		//получить элемент по индексу
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
int TQueue<T>::GetSize()					//получить размер очереди
{
	return size;
}

template<class T>
inline int TQueue<T>::GetCountElem()			//получить количество элементов
{
	return count;
}

template<class T>
int TQueue<T>::GetLowIndex()					//получить индекс начального элемента
{
	return low;
}

template<class T>
int TQueue<T>::GetTopIndex()					//получить индекс конечного элемента
{
	return top;
}

template <class T>
void TQueue<T>::GetNextIndex(int* index)				//получить следующий индекс
{
	*index = (++*index % size);
}

template<class T>
void TQueue<T>::GetPrevIndex(int* index)		//получить предыдущий индекс
{
	*index = (--*index + size) % size;
}

	
#endif