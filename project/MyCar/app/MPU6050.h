#ifndef _MPU6050_H_
#define _MPU6050_H_
#include "common.h"
uint8 MPU6050_Init(void);
void MPU6050_WriteReg(uint8 RegisterAddress, uint8 Data);
uint8 MPU6050_ReadReg(uint8 RegisterAddress);
int16 MPU6050_GetResult(uint8 Regs_Addr);









#endif
