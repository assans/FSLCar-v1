#ifndef  _DATASTRUCTURE_H_
#define  _DATASTRUCTURE_H_
#include "common.h"

typedef struct
{
	int SetPoint;
	long SumError;//累积误差

	double Proportion;//比例常数
	double Integral;//积分常数;
	double Derivative;//微分常数;

	int LastError;
	int PrevError;
}PID_Inc_TypeDef;






#endif
