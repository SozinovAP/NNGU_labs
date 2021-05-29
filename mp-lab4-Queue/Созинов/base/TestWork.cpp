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
	cout << "����� �� �������� ���������� �� ������� ���������� � ����� ������� ����� � �������������� ���������� ������? \n 1 - �� \n 2 - ��� \n";
	cin >> check;
	switch (check)
	{
	case 1:
		NeedInfo = true;
		break;
	case 2:
		break;
	default:
		cout << "������� �������� ��������, ����� ���������� ������ �������� ����������" << endl;
		break;
	}
	cout << "������� ������ �������" << endl;
	cin >> qusize;
	cout << "������� ���������� �����������" << endl;
	cin >> Processors;
	cout << "������� ���������� ������" << endl;
	cin >> tacts;
	cout << "������� ������������� ��������� �����" << endl;
	cin >> Intense;
	TClasster Classter(Processors);
	TJobStream Job(Intense, Classter, qusize);
	result resJob;
	resJob = Job.StartStream(tacts,/* qusize, */NeedInfo);

	cout << "\n������������� �����: " << resJob.COunt << endl;
	cout << "��������� �����: " << resJob.CountCompleted << endl;
	cout << "�����, ���������� �������������� �� ������ ��������� ��������: " << resJob.COunt - resJob.CountCompleted - resJob.CountIgnor << endl;
	cout << "�� ��������� ����� ��-�� ������������ �������: " << resJob.CountIgnor << endl;
	cout << "������������� ���������� � %: " << resJob.Tact << endl;
	return 0;
}