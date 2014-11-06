#ifndef _DEBUG_H_
#define _DEBUG_H_
#include "common.h"

void Debug_Timer_Init(void);  //初始化程序时间计数  每一小格为100us
void PIT3_ISR(void);        //PIT3的中断服务
void Debug_Timer_ReSet(void);  //计数器清零

#endif
