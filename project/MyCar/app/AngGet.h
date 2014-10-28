#ifndef _ANGGET_H_
#define _ANGGET_H_

#include "Kalman.h"
#include "common.H"
void AngleGet(void);
//int GyroScopeGetZero(void);
//int GravityGetZero(void);
void Float2Byte(float *target,int8 *buf,int8 beg);

#endif
