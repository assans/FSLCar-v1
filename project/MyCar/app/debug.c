#include "debug.h"
#include "datastructure.h"

PIT_InitTypeDef Code_Timer_Struct;

extern IncPID_InitTypeDef Ang_PID;//用来调试PID参数
unsigned int Code_Count=0;

void Debug_Timer_Init(void)
{
	Code_Timer_Struct.PIT_Pitx=PIT3;
	Code_Timer_Struct.PIT_PeriodUs=100;
	Code_Timer_Struct.PIT_Isr=PIT3_ISR;
	LPLD_PIT_Init(Code_Timer_Struct);
	LPLD_PIT_EnableIrq(Code_Timer_Struct);
}

void PIT3_ISR(void)
{
	Code_Count++;
}

void Debug_Timer_ReSet(void)
{
	Code_Count=0;
}

void Struct_Init(void) //在这里调试初始参数
{
	Ang_PID.Proportion=0.7; //比例
	Ang_PID.Integral=0; 	//积分
	Ang_PID.Derivative=0.001;//微分
	Ang_PID.AngSet=0;  //调试时调试这一行
	Ang_PID.AngSpeedSet=0;
//	Ang_PID.SetPoint=0;//设定的值
//	Ang_PID.LastError=0;//上一次的误差
//	Ang_PID.PrevError=0;//上上次的误差
}
