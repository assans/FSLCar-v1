#ifndef _INIT_H_
#define _INIT_H
#include "common.h"

void Init_ADC(void);
void Init_PIT(void);
void CarInit(void);
void Init_I2C(void);
uint8 u32_trans_U8(uint16 data); //��12b��ADC���ת����8b��char //����������



#endif
