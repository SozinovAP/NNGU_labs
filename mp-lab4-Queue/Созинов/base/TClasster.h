#ifndef PROC_H
#define PROC_H

#include <string>


using namespace std;

class TClasster
{
	
private:
	int CountProc;						//количество процессоров
	int CountBuzyProc;					//количество занятых процессоров
	bool* masProc;						//массив процессоров
	
public:
	TClasster(int Procesors = 1);
	short SetPriority();				//установить приоритет задачи
	short SetLeadTime();				//установить время выполнения
	void ChangeStatusProc(int i);		//сменить статус процессора
	int GetCountProc();					//получить количество процессоров
	int GetCountBuzyProc();				//получить количество занятых процессоров
	int BuzyProc();						//получить свободный процессор, если есть
	bool ThisProcIsFree(int Number);	//проверить, свободен ли процессор
};
#endif

