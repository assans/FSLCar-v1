#include "common.h"
//#include "DataScope_DP.h"
#include "Init.h"
#include "Kalman.h"
#include "angget.h"
uint8 OUTPUT_DATA[] = { 0x03, 0xFC, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 0xFC,0x03 };
uint8 AllData[] = { 0x03, 0xFC, 0, 0, 0, 0, 1, 0xFC, 0x03 };
uint8 ang, gyro, x, y, z;

float CarAngle, CarAngSpeed, x_f;

void main(void)
{
	CarInit();

	while (1)
	{
		LPLD_GPIO_Toggle_b(PTA, 17);
		LPLD_SYSTICK_DelayMs(50);

	}
}

void PIT0_ISR(void)
{
	//test
}
