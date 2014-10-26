#include "common.h"
//#include "DataScope_DP.h"
#include "Init.h"
#include "Kalman.h"
#include "angget.h"
uint8 OUTPUT_DATA[] = { 0x03, 0xFC, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 0xFC,0x03 };
uint8 AllData[] = { 0x03, 0xFC, 0, 0, 0, 0, 1, 0xFC, 0x03 };
uint8 ang, gyro, x, y, z;
int GyroZero = 0; //陀螺仪零点
int GravityZero = 0; //重力Z轴零点
float CarAngle, CarAngSpeed, x_f;
#define mode 1

void ADC_GET(void)
{
	if (mode)
	{
		AngleGet();
		Float2Byte(&CarAngle, OUTPUT_DATA, 2);
		Float2Byte(&CarAngSpeed, OUTPUT_DATA, 6);
		Float2Byte(&x_f, OUTPUT_DATA, 10);
	}
	else
	{
		y = u32_trans_U8(LPLD_ADC_Get(ADC1, AD11));
		x = u32_trans_U8(LPLD_ADC_Get(ADC1, AD10));
		z = u32_trans_U8(LPLD_ADC_Get(ADC1, AD12));
		ang = u32_trans_U8(LPLD_ADC_Get(ADC1, AD13));
		gyro = u32_trans_U8(LPLD_ADC_Get(ADC1, AD14));
		AllData[2] = x;
		AllData[3] = y;
		AllData[4] = z;
		AllData[5] = gyro;
		AllData[6] = ang;
	}
}
void main(void)
{
	CarInit();
	//GyroZero = GyroScopeGetZero();
	//GravityZero=GravityGetZero();
	while (1)
	{
		LPLD_GPIO_Toggle_b(PTA, 17);
		LPLD_SYSTICK_DelayMs(50);
		ADC_GET();
		if (mode)
		{
			LPLD_UART_PutCharArr(UART5, OUTPUT_DATA, 16);
		}
		else
		{
			LPLD_UART_PutCharArr(UART5, AllData, 9);
		}

	}
}

void PIT0_ISR(void)
{
	//test
}
