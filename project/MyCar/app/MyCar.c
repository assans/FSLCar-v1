#include "common.h"
#include "Init.h"
#include "angget.h"
#include "math.h"
#include "complement.h"
#include "DEV_MMA8451.h"
#include "DataScope_DP.h"
#include "debug.h"
float CarAngle, CarAngSpeed;
short acc_x, acc_y, acc_z, gyro_1, gyro_2;
int gyro_avg = 2360;
extern float GravityAngle;
//--控制区
#define Debug

//控制区结束
void main(void)
{
	int i;
	CarInit();
#ifdef Debug
	Debug_Timer_Init();
#endif
//	for(i=0;i<500;i++)
//	{
//		gyro_avg+=LPLD_ADC_Get(ADC1,AD15);
//		LPLD_SYSTICK_DelayMs(1);
//	}
//	gyro_avg=gyro_avg/500;
	while (1)
	{
#ifdef Debug
		Debug_Timer_ReSet();
#endif
		LPLD_GPIO_Toggle_b(PTA, 17);
		LPLD_SYSTICK_DelayMs(10);
		AngleGet();
		CarAngle = angle_com;
		CarAngSpeed = angle_dot_com;

		DataScope_Get_Channel_Data(CarAngle, 1);
		DataScope_Get_Channel_Data(CarAngSpeed, 2);
		DataScope_Get_Channel_Data(GravityAngle, 3);
		i = DataScope_Data_Generate(3);
		LPLD_UART_PutCharArr(UART5, DataScope_OutPut_Buffer, i);
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
		//RxBuf[i] = LPLD_UART_GetChar(UART5);
		//LPLD_UART_PutChar(UART5, RxBuf[i]);
	}

}
