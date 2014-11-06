#include "debug.h"

PIT_InitTypeDef Code_Timer_Struct;
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
