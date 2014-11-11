#include "common.h"
#include "Init.h"
#include "angget.h"
#include "math.h"
#include "complement.h"
#include "DEV_MMA8451.h"
#include "debug.h"
#include "datastructure.h"
#include "Control.h"
//#include "DataScope_DP.h"

CarInfo_TypeDef CarInfo_Now;
CarControl_TypeDef MotorControl; //存储电机控制的值
short acc_x, acc_y, acc_z, gyro_1, gyro_2;
int gyro_avg = 2360; //角速度AD平均值
uint8 OUTDATA[16] =
		{ 0x03, 0xfc, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 0xfc, 0x03 };
extern float GravityAngle;
extern char Flag_1Ms, Flag_5Ms, Flag_10Ms;
//--控制区
#define Debug

//控制区结束
void main(void)
{
	Struct_Init(); //初始各种结构体的值
	CarInit();
#ifdef Debug
	Debug_Timer_Init();
#endif

	while (1)
	{
		if (Flag_10Ms == 1)
		{
			Flag_10Ms = 0;
#ifdef Debug
			Debug_Timer_ReSet();
#endif
			LPLD_GPIO_Toggle_b(PTA, 17);
			AngleGet();
			AngleControlValueCalc();
			MotorControl_Out(); //输出电机控制的值

//			DataScope_Get_Channel_Data(CarInfo_Now.CarAngle, 1);
//			DataScope_Get_Channel_Data(CarInfo_Now.CarAngSpeed, 2);
//			DataScope_Get_Channel_Data(GravityAngle, 3);
//			i = DataScope_Data_Generate(3);
//			LPLD_UART_PutCharArr(UART5, DataScope_OutPut_Buffer, i);
			Float2Byte(&CarInfo_Now.CarAngle, OUTDATA, 2);
			Float2Byte(&CarInfo_Now.CarAngSpeed, OUTDATA, 10);
			Float2Byte(&GravityAngle, OUTDATA, 6);
			LPLD_UART_PutCharArr(UART5, OUTDATA, 16);

			//LPLD_SYSTICK_DelayMs(10);
			Flag_10Ms = Flag_10Ms;

		}
	}
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
