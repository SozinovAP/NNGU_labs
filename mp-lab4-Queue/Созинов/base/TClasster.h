#ifndef PROC_H
#define PROC_H

#include <string>


using namespace std;

class TClasster
{
	
private:
	int CountProc;						//���������� �����������
	int CountBuzyProc;					//���������� ������� �����������
	bool* masProc;						//������ �����������
	
public:
	TClasster(int Procesors = 1);
	short SetPriority();				//���������� ��������� ������
	short SetLeadTime();				//���������� ����� ����������
	void ChangeStatusProc(int i);		//������� ������ ����������
	int GetCountProc();					//�������� ���������� �����������
	int GetCountBuzyProc();				//�������� ���������� ������� �����������
	int BuzyProc();						//�������� ��������� ���������, ���� ����
	bool ThisProcIsFree(int Number);	//���������, �������� �� ���������
};
#endif

