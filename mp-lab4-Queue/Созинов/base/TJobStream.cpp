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
		cout << "������������ �������� �������������: " << c << endl;
		if (Intense <= 0)
		{
			intense = 0;
			cout << "������ ���������� �� �����" << endl;
		}
		else if(Intense > 1)
		{
			intense = 1;
			cout << "����������� ������������ �������������: 1" << endl;
		}
	}
}

bool TJobStream::GetNewJob()											//������ ���������?
{
	return  ((static_cast<double>((rand()) / RAND_MAX)) < intense) ? true : false;
}

result TJobStream::StartStream(int tacts, bool f)						//������ ������
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
		cout << "������������ ����� ������: " << c << endl;
		cout << "����������� ������������ ��������� ���������� ������: 1" << endl;
	}
	const bool NeedInfo = f;
	result ResJob = { 0, 0, 0, 0, 0.0 };
	int ID = 0;
	Task* MasTask = new Task[Classter.GetCountProc()];
	for (int i = 0; i < Classter.GetCountProc(); i++)
		MasTask[i] = { 0, 0, -1 };

	
	for (int i = 1; i < CountTacts + 1; i++)
	{
		cout << "\n\t���� � " << i << endl;
		
		if(GetNewJob())												//������� ���������� ������
		{
			Task task = { ++ID, Classter.SetPriority(), Classter.SetLeadTime()};
			ResJob.COunt++;											//��������� ������� ���������� �����
			cout << "\n����������� ������ � " << task.IDTask << endl;
			
			if (NeedInfo)											//���������, ���� ����� �������������� ������
			{
				InfoAboutNewTask(task);
			}
		
			if (Classter.BuzyProc() == -1)							//�������� ��������� ���������, ���� ����� �������
			{
				if (!qu.IsFull())
				{
					qu.Push(task);									//�������� ������ � �������
					SortTaskInQueue();
					cout << "������ ���������� � �������" << endl;
				}
				else
				{
					ResJob.CountIgnor++;							//��������� ������� ����������������� �����
					cout << "������ ��������������� ��-�� ������������ �������" << endl;
				}
			}
			else
			{
				MasTask[Classter.BuzyProc()] = task;				//��������� ������ �� ����������
				Classter.ChangeStatusProc(Classter.BuzyProc());	//������� ������ ����������
			}
		}

		if (Classter.GetCountBuzyProc() != 0)						//��������� ���� �� ������� ���������
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
						cout << "��������� ������ " << MasTask[j].IDTask << endl;
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
			cout << "������ ����� �� �������" << endl;
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

void TJobStream::SortTaskInQueue()										//���������� ����� � �������
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
			//������ ������� ���������� ��� ����, ����� �������� ��������, ����� ������ ��-�� ����� �������� ����������, ��� �����������, ��� ����� ������ ������ �������
			//���� �������� � ������� ����� ������ (5 * �� �������� ����������� ����� ������������� ��������), �� �� ����� ����������� ����� ��������� � �������  
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

void TJobStream::Info(Task* task)										//������� ���������� �� ������� ����������
{
	cout << "���������� �� ������� ����������" << endl;
	cout << setiosflags(ios::left);
	cout << setw(3) << "�" << setw(6) << "ID" << setw(2) << "time" << endl;
	for (int j = 0; j < Classter.GetCountProc(); j++)
	{
		cout << setw(3) << j << setw(6);
		if (Classter.ThisProcIsFree(j))
		{
			cout << "\t���� ��������� �����������" << endl;
		}
		else
		{
			cout << task[j].IDTask << setw(2) << task[j].time << endl;
		}
	}

}

void TJobStream::InfoAboutNewTask(Task task)							//������� ���������� � ����� �������
{
	cout << setiosflags(ios::left);
	cout << setw(6) << "ID" << setw(10) << "priority" << setw(6) << "time" << endl;
	cout << setw(9) << task.IDTask << setw(8) << task.priority << setw(6) << task.time << endl << endl;
}