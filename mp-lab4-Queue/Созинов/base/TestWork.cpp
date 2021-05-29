#include "TClasster.h"
#include "TJobStream.h"
#include <iostream>
#include <string>
#include <locale>

using namespace std;

int main()
{
	setlocale(LC_ALL, "RUS");
	
	int qusize;
	int Processors;
	int  tacts;
	double  Intense;
	int check;
	bool NeedInfo = false;
	cout << "Нужно ли выводить информацию по каждому процессору в конце каждого такта и характеристики полученной задачи? \n 1 - да \n 2 - нет \n";
	cin >> check;
	switch (check)
	{
	case 1:
		NeedInfo = true;
		break;
	case 2:
		break;
	default:
		cout << "Указано неверное значение, будет выводиться только основная информация" << endl;
		break;
	}
	cout << "Введите размер очереди" << endl;
	cin >> qusize;
	cout << "Введите количество процессоров" << endl;
	cin >> Processors;
	cout << "Введите количество тактов" << endl;
	cin >> tacts;
	cout << "Введите интенсивность появления задач" << endl;
	cin >> Intense;
	TClasster Classter(Processors);
	TJobStream Job(Intense, Classter, qusize);
	result resJob;
	resJob = Job.StartStream(tacts,/* qusize, */NeedInfo);

	cout << "\nСгенерировано задач: " << resJob.COunt << endl;
	cout << "Выполнено задач: " << resJob.CountCompleted << endl;
	cout << "Задач, оставшиеся невыполненными на момент окончания имитации: " << resJob.COunt - resJob.CountCompleted - resJob.CountIgnor << endl;
	cout << "Не выполнено задач из-за переполнения очереди: " << resJob.CountIgnor << endl;
	cout << "Загруженность процессора в %: " << resJob.Tact << endl;
	return 0;
}