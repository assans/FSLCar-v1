#ifndef _ANGGET_H_
#define _ANGGET_H_

//#include "Kalman.h"
#include "common.H"


void AngleGet(void);
//int GyroScopeGetZero(void);
//int GravityGetZero(void);
void Float2Byte(float *target,uint8 *buf,uint8 beg);
void Short2Byte(int16 *target, int8 *buf, int8 beg);
void AngleControlValueCalc(void);
void MotorControl_Out(void);

#endif
