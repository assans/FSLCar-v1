#ifndef _DEBUG_H_
#define _DEBUG_H_
#include "common.h"

void Debug_Timer_Init(void);  //��ʼ������ʱ�����  ÿһС��Ϊ100us
void PIT3_ISR(void);        //PIT3���жϷ���
void Debug_Timer_ReSet(void);  //����������

#endif
