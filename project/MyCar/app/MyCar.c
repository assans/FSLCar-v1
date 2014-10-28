#include "common.h"
//#include "DataScope_DP.h"
#include "Init.h"
#include "Kalman.h"
#include "angget.h"
#include "MPU6050.h"
#include "math.h"
//#include "complement.h"

uint8 whoami = 1;
int8 MPUData[20] = { 0x03, 0xFC, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 4, 4, 4, 4,
		0xFC, 0x03 };
int16 mpu_acc_x, mpu_acc_y, mpu_acc_z, mpu_gyro_x, mpu_gyro_y, mpu_gyro_z;
float CarAngle, CarAngSpeed, x_f;
float G_Ang; //重力角
float tempf_acc_x, tempf_gyro_y;
extern float angle, angle_dot; //卡尔曼滤波的东西

//互补滤波的东西
float angle_com, angle_dot_com; //外部需要引用的变量
//extern float CarAngle, CarAngSpeed;
//-------------------------------------------------------
float bias_cf;
const float cdt = 0.08;
//------------------------------------
float temp_acc, temp_gyro;
extern float Q_angle, Q_gyro, R_angle;
int8 RxBuf[3] = { 0, 0, 0 };

void my_com(float angle_m_cf, float gyro_m_cf)
{
	/*bias_cf*=0.002;			//陀螺仪零飘低通滤波；500次均值；0.998
	 bias_cf+=gyro_m_cf*0.009;		   //0.002
	 angle_dot_com=gyro_m_cf-bias_cf;*/
	angle_com = (angle_com + gyro_m_cf * cdt) * 0.95 + angle_m_cf * 0.05;
	//加速度低通滤波；20次均值；按100次每秒计算，低通5Hz；0.90 0.05
}

void GetAng(void)
{

	mpu_acc_x = MPU6050_GetResult(ACCEL_XOUT_H);
	mpu_gyro_y = MPU6050_GetResult(GYRO_YOUT_H);
	temp_gyro = (float) mpu_gyro_y / 4.096;
	temp_gyro = -temp_gyro;
	temp_acc = (float) mpu_acc_x / 4096.0;
	if (temp_acc > 1)
		temp_acc = 1;
	else if (temp_acc < -1)
		temp_acc = -1;
	G_Ang = asinf(temp_acc) * 57;
	Kalman_Filter(G_Ang, temp_gyro);
	//my_com(G_Ang,temp_gyro);

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
//		mpu_acc_x = MPU6050_GetResult(ACCEL_XOUT_H);
//		mpu_acc_y = MPU6050_GetResult(ACCEL_YOUT_H);
//		mpu_acc_z = MPU6050_GetResult(ACCEL_ZOUT_H);
//		mpu_gyro_x = MPU6050_GetResult(GYRO_XOUT_H);
//		mpu_gyro_y = MPU6050_GetResult(GYRO_YOUT_H);
//		mpu_gyro_z = MPU6050_GetResult(GYRO_ZOUT_H);
		GetAng();
		tempf_acc_x = (float) mpu_acc_x;
		tempf_gyro_y = (float) mpu_gyro_y;
//		Short2Byte(&mpu_acc_x, MPUData, 2);
//		Short2Byte(&mpu_acc_y, MPUData, 4);
//		Short2Byte(&mpu_acc_z, MPUData, 6);
//		Short2Byte(&mpu_gyro_x, MPUData, 8);
//		Short2Byte(&mpu_gyro_y, MPUData, 10);
//		Short2Byte(&mpu_gyro_z, MPUData, 12);
//		Short2Byte(&mpu_gyro_y, MPUData, 4);
		Float2Byte(&G_Ang, MPUData, 2);
		Float2Byte(&temp_gyro, MPUData, 6);
		Float2Byte(&angle, MPUData, 14);
		Float2Byte(&angle_dot, MPUData, 10);
//		Float2Byte(&angle_com,MPUData,14);
//		Float2Byte(&angle_dot_com,MPUData,10);
		LPLD_UART_PutCharArr(UART5, MPUData, 20);
	}
}
void PIT0_ISR(void)
{
	//test
}

void UART5_RxIsr(void)
{
	uint8 i;
	for (i = 0; i < 3; i++)
	{
		RxBuf[i]=LPLD_UART_GetChar(UART5);
		LPLD_UART_PutChar(UART5,RxBuf[i]);
	}

}
