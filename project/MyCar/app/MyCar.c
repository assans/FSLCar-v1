#include "common.h"
#include "Init.h"
#include "angget.h"
#include "math.h"
#include "complement.h"
#include "DEV_MMA8451.h"
#include "DataScope_DP.h"
int8 OutPutData[14] = { 0x03, 0xFC, 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 0xFC, 0x03 };
int8 AngData[20]={0x03, 0xFC,0,0,0,0,1,1,1,1,0,0,0,0,3,3,3,3, 0xFC, 0x03 };
float CarAngle, CarAngSpeed, x_f;
short acc_x, acc_y, acc_z, gyro_1, gyro_2;
int gyro_avg=2360;
extern float GravityAngle;

void main(void)
{
	int i;
	CarInit();
//	for(i=0;i<500;i++)
//	{
//		gyro_avg+=LPLD_ADC_Get(ADC1,AD15);
//		LPLD_SYSTICK_DelayMs(1);
//	}
//	gyro_avg=gyro_avg/500;
	while (1)
	{
		LPLD_GPIO_Toggle_b(PTA, 17);
		LPLD_SYSTICK_DelayMs(10);
		AngleGet();
		CarAngle=angle_com;
		CarAngSpeed=angle_dot_com;
//		Short2Byte(&acc_x,OutPutData,2);
//		Short2Byte(&acc_y,OutPutData,4);
//		Short2Byte(&acc_z,OutPutData,6);
//		Short2Byte(&gyro_1,OutPutData,8);
//		Short2Byte(&gyro_2,OutPutData,10);

//		Float2Byte(&CarAngle,AngData,2);
//		Float2Byte(&CarAngSpeed,AngData,6);
//		Float2Byte(&GravityAngle,AngData,14);


		//LPLD_UART_PutCharArr(UART5, OutPutData, 14);
		//LPLD_UART_PutCharArr(UART5, AngData, 20);

		DataScope_Get_Channel_Data(CarAngle,1);
		DataScope_Get_Channel_Data(CarAngSpeed,2);
		DataScope_Get_Channel_Data(GravityAngle,3);
		i=DataScope_Data_Generate(3);
		LPLD_UART_PutCharArr(UART5,DataScope_OutPut_Buffer,i);
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
