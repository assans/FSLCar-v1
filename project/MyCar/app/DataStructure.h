#ifndef  _DATASTRUCTURE_H_
#define  _DATASTRUCTURE_H_
#include "common.h"

typedef struct
{
	int SetPoint;
	long SumError;//�ۻ����

	double Proportion;//��������
	double Integral;//���ֳ���;
	double Derivative;//΢�ֳ���;

	int LastError;
	int PrevError;
}PID_Inc_TypeDef;






#endif
