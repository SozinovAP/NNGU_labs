#include "TClasster.h"
#include <iostream>
#include <ctime>

using namespace std;


TClasster::TClasster(int Procesors)
{
	try
	{
		if (Procesors < 1)
			throw Procesors;
		CountProc = Procesors;
	}
	catch (int c)
	{
		cout << "Некорректное кол-во процессоров:\t" << c << endl;
		cout << "Значение было изменено на миниамльное возможное: 1" << endl;
		CountProc = 1;
	}
	CountBuzyProc = 0;
	masProc = new bool[CountProc];
	for (int i = 0; i < CountProc; i++)
	{
		masProc[i] = true;
	}
	srand(static_cast<unsigned>(time(0)));
}

short TClasster::SetPriority()					//установить приоритет задачи
{
	return static_cast<short>(rand() % 3 + 1);
}

short TClasster::SetLeadTime()					//установить время выполнения
{
	return static_cast<short>(rand() % 6 + 1);
}

void TClasster::ChangeStatusProc(int i)			//сменить статус процессора
{
	try
	{
		if ((i < 0) || (i > CountProc))
			throw i;
		if (masProc[i])
		{
			masProc[i] = false;
			CountBuzyProc++;
		}
		else
		{
			masProc[i] = true;
			CountBuzyProc--;
		}
	}
	catch(int I)
	{
		cout << "Uncorrect proc:\t" << I << endl;
	}
}

int TClasster::GetCountProc()					//получить количество процессоров
{
	return CountProc;
}

int TClasster::GetCountBuzyProc()				//получить количество занятых процессоров
{
	return CountBuzyProc;
}

int TClasster::BuzyProc()						//получить свободный процессор, если есть
{
	if (CountBuzyProc < CountProc)
	{
		for (int i = 0; i < CountProc; i++)
		{
			if (masProc[i])
			{
				return i;
			}
		}
		return -1;
	}
	else
	{
		return -1;
	}
	
}

bool TClasster::ThisProcIsFree(int Number)	// проверить, свободен ли процессор
{
	return masProc[Number];
}
