#ifndef JOB_STREAM_H
#define JOB_STREAM_H

#include <iomanip>
#include "TQueue.h"
#include "TClasster.h"



struct Task
{
	int IDTask;					//ID задачи
	short priority;				//приоритет задания
	short time;					//время выполнения
};

struct result
{
	int COunt;					//кол-во задач
	int CountCompleted;			//кол-во выполненных задач
	int CountIgnor;				//кол-во отказов из-за переполнения очереди
	int CountUnCompleted;		//кол-во задач, оставшихся невыполненными на момент окончания имитации
	double Tact;                //процент загруженности класстера
};

class TJobStream
{
private:
	TClasster Classter;
	TQueue<Task> qu;
	double intense;													//интенсивность задач
public:

	TJobStream(double Intense, TClasster classt, int size);
	bool GetNewJob();												//задача поступает?
	result StartStream(int tacts, bool f);							//работа потока
	void SortTaskInQueue();											//сортировка задач по приоритету
	void Info(Task* task);											//выводит информацию по каждому процессору
	void InfoAboutNewTask(Task task);								//Выыводит информацию о новом задании
};

#endif