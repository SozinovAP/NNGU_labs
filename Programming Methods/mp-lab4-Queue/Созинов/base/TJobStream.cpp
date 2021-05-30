#include "TJobStream.h"
#include "TClasster.h"
#include <iostream>

TJobStream::TJobStream(double Intense, TClasster classt, int size) : Classter(classt), qu(size)
{
	try
	{
		if ((Intense <= 0) || (Intense > 1))
			throw Intense;
		intense = Intense;
	}
	catch (double c)
	{
		cout << "Некорректное значение интенсивности: " << c << endl;
		if (Intense <= 0)
		{
			intense = 0;
			cout << "Задачи появляться не будут" << endl;
		}
		else if(Intense > 1)
		{
			intense = 1;
			cout << "Установлена максимальная интенсивность: 1" << endl;
		}
	}
}

bool TJobStream::GetNewJob()											//задача поступает?
{
	return  ((static_cast<double>((rand()) / RAND_MAX)) < intense) ? true : false;
}

result TJobStream::StartStream(int tacts, bool f)						//работа потока
{
	int CountTacts = 1;
	try
	{
		if (tacts < 1)
			throw tacts;
		CountTacts = tacts;
	}
	catch (int c)
	{
		cout << "Некорректное число тактов: " << c << endl;
		cout << "Установлено миннимальное возможное количество тактов: 1" << endl;
	}
	const bool NeedInfo = f;
	result ResJob = { 0, 0, 0, 0, 0.0 };
	int ID = 0;
	Task* MasTask = new Task[Classter.GetCountProc()];
	for (int i = 0; i < Classter.GetCountProc(); i++)
		MasTask[i] = { 0, 0, -1 };

	
	for (int i = 1; i < CountTacts + 1; i++)
	{
		cout << "\n\tТакт № " << i << endl;
		
		if(GetNewJob())												//попытка добавления задачи
		{
			Task task = { ++ID, Classter.SetPriority(), Classter.SetLeadTime()};
			ResJob.COunt++;											//увеличить счётчик полученных задач
			cout << "\nПоступление задачи № " << task.IDTask << endl;
			
			if (NeedInfo)											//выводится, если нужны характеристики задачи
			{
				InfoAboutNewTask(task);
			}
		
			if (Classter.BuzyProc() == -1)							//получить свободный процессор, если такой имеется
			{
				if (!qu.IsFull())
				{
					qu.Push(task);									//добавить задачу в очередь
					SortTaskInQueue();
					cout << "Задача отправлена в очередь" << endl;
				}
				else
				{
					ResJob.CountIgnor++;							//увеличить счётчик проигнорированных задач
					cout << "Задача проигнорирована из-за переполнения очереди" << endl;
				}
			}
			else
			{
				MasTask[Classter.BuzyProc()] = task;				//отправить задачу на выполнение
				Classter.ChangeStatusProc(Classter.BuzyProc());	//сменить статус процессора
			}
		}

		if (Classter.GetCountBuzyProc() != 0)						//проверить есть ли занятый процессор
		{
			ResJob.Tact += (static_cast<double>(Classter.GetCountBuzyProc()) / static_cast<double>(Classter.GetCountProc()));
			for (int j = 0; j < Classter.GetCountProc(); j++)
			{
				if (!Classter.ThisProcIsFree(j))
				{
					if (MasTask[j].time > 0)
						MasTask[j].time--;
					if (MasTask[j].time == 0)
					{
						ResJob.CountCompleted++;
						cout << "выполнена задача " << MasTask[j].IDTask << endl;
						MasTask[j] = { 0, 0, -1};
						Classter.ChangeStatusProc(j);
					}
				}	
			}
		}
		
		while ((Classter.BuzyProc() > -1) && (!qu.IsEmpty()))
		{
			Task task = qu.Pop();
			MasTask[Classter.BuzyProc()] = task;
			Classter.ChangeStatusProc(Classter.BuzyProc());
			cout << "задача взята из очереди" << endl;
		}
		
		if (NeedInfo)
		{
			Info(MasTask);
		}
	}

	ResJob.Tact = ResJob.Tact / CountTacts * 100;
	ResJob.CountUnCompleted = Classter.GetCountBuzyProc() + qu.GetCountElem();
	
	return ResJob;
}

void TJobStream::SortTaskInQueue()										//сортировка задач в очереди
{
		int j = qu.GetTopIndex();
		qu.GetPrevIndex(&j);
		int i = qu.GetTopIndex();
		int Count = qu.GetCountElem() - 1;
		bool F = true;
		while ((Count != 0) && (F))
		{
			int D = 5 * (qu.GetElemByIndex(i).priority - qu.GetElemByIndex(j).priority); 
			if ((qu.GetElemByIndex(i).priority > qu.GetElemByIndex(j).priority) && (qu.GetElemByIndex(i).IDTask <= qu.GetElemByIndex(j).IDTask + D))
			//второе условие необходимо для того, чтобы избежать ситуации, когда задача из-за менее высокого приоритета, чем поступающие, все время уходит вглубь очереди
			//если разность в номерах задач больше (5 * на разность приоритетов между сравниваемыми задачами), то не будет происходить смены положения в очереди  
			{
				qu.swap(i, j);
				qu.GetPrevIndex(&i);
			}
			else
			{
				F = false;
			}
			qu.GetPrevIndex(&j);
			Count--;
		}
}

void TJobStream::Info(Task* task)										//выводит информацию по каждому процессору
{
	cout << "Информация по каждому процессору" << endl;
	cout << setiosflags(ios::left);
	cout << setw(3) << "№" << setw(6) << "ID" << setw(2) << "time" << endl;
	for (int j = 0; j < Classter.GetCountProc(); j++)
	{
		cout << setw(3) << j << setw(6);
		if (Classter.ThisProcIsFree(j))
		{
			cout << "\tэтот процессор простаивает" << endl;
		}
		else
		{
			cout << task[j].IDTask << setw(2) << task[j].time << endl;
		}
	}

}

void TJobStream::InfoAboutNewTask(Task task)							//Выводит информацию о новом задании
{
	cout << setiosflags(ios::left);
	cout << setw(6) << "ID" << setw(10) << "priority" << setw(6) << "time" << endl;
	cout << setw(9) << task.IDTask << setw(8) << task.priority << setw(6) << task.time << endl << endl;
}