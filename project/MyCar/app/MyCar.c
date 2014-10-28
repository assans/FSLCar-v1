#include "common.h"
//#include "DataScope_DP.h"
#include "Init.h"
#include "Kalman.h"
#include "angget.h"
#include "MPU6050.h"
#include "math.h"

float Acc_X_MAX=4000;//最大值
uint8 OUTPUT_DATA[] = { 0x03, 0xFC, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 0xFC,
		0x03 };
uint8 AllData[] = { 0x03, 0xFC, 0, 0, 0, 0, 1, 0xFC, 0x03 };
uint8 ang, gyro, x, y, z;
uint8 whoami = 1;
int8 MPUData[16] =
		{ 0x03, 0xFC, 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 0xFC, 0x03 };
int16 mpu_acc_x, mpu_acc_y, mpu_acc_z, mpu_gyro_x, mpu_gyro_y, mpu_gyro_z;
float CarAngle, CarAngSpeed, x_f;
float G_Ang;//重力角

void GetAng(void)
{
	mpu_acc_x = MPU6050_GetResult(ACCEL_XOUT_H);
	mpu_gyro_y = MPU6050_GetResult(GYRO_YOUT_H);
	G_Ang=asinf((float)mpu_acc_x/Acc_X_MAX);
	Kalman_Filter(G_Ang,mpu_gyro_y);
}

void Short2Byte(int16 *target, int8 *buf, int8 beg)
{
	int8 *point;
	point = (int8*) target;
	buf[beg] = point[0];
	buf[beg + 1] = point[1];
}

void main(void)
{
	CarInit();
	whoami = MPU6050_Init();
	while (1)
	{
		LPLD_GPIO_Toggle_b(PTA, 17);
		LPLD_SYSTICK_DelayMs(50);
		mpu_acc_x = MPU6050_GetResult(ACCEL_XOUT_H);
//		mpu_acc_y = MPU6050_GetResult(ACCEL_YOUT_H);
//		mpu_acc_z = MPU6050_GetResult(ACCEL_ZOUT_H);
//		mpu_gyro_x = MPU6050_GetResult(GYRO_XOUT_H);
		mpu_gyro_y = MPU6050_GetResult(GYRO_YOUT_H);
//		mpu_gyro_z = MPU6050_GetResult(GYRO_ZOUT_H);
		Short2Byte(&mpu_acc_x, MPUData, 2);
		Short2Byte(&mpu_acc_y, MPUData, 4);
		Short2Byte(&mpu_acc_z, MPUData, 6);
		Short2Byte(&mpu_gyro_x, MPUData, 8);
		Short2Byte(&mpu_gyro_y, MPUData, 10);
		Short2Byte(&mpu_gyro_z, MPUData, 12);
		LPLD_UART_PutCharArr(UART5, MPUData, 16);
	}
}
void PIT0_ISR(void)
{
	//test
}
