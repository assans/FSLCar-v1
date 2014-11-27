#include "common.h"
#include "Init.h"
#include "angget.h"
#include "math.h"
#include "complement.h"
#include "DEV_MMA8451.h"
#include "debug.h"
#include "datastructure.h"
#include "Control.h"
#include "CCD.h"
#include "Communicate.h"
//#include "DataScope_DP.h"

CarInfo_TypeDef CarInfo_Now;
CarControl_TypeDef MotorControl; //存储电机控制的值
short acc_x, acc_y, acc_z, gyro_1, gyro_2;
uint8 OUTDATA[16] =
		{ 0x03, 0xfc, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 0xfc, 0x03 }; //示波器
extern float GravityAngle; //重力角
extern char Flag_1Ms, Flag_5Ms, Flag_10Ms; //时间片标志
extern uint8 debugerConnected; //是否连接到调试器
//--控制区
#define Timer
#define	Debuger //是否使用调试器
#define CCDOn //开启或者关闭CCD
#define CCDSendImage_NO //控制要不要发送CCD的图像
#define AngleCale//姿态解算
#define AngDataSend_NO //是否发送姿态解算的数据
//控制区结束
uint8 AngSendCount = 0; //控制角度的发送次数

unsigned char testbyte[4];
void main(void)
{
	Struct_Init(); //初始各种结构体的值
	CarInit();
	LPLD_Flash_Init(); //初始化EEPROM,所有的初始化数据保存在EEPROM的第60个扇区
//	Flash_WriteTest(); 测试flash区

#ifdef Timer
	Debug_Timer_Init();
#endif
	Flash_ReadAllData();
	while (1)
	{
		if (Flag_10Ms == 1)
		{
			Flag_10Ms = 0;
#ifdef Timer
			Debug_Timer_ReSet();
#endif
			LPLD_GPIO_Toggle_b(PTA, 17);
#ifdef AngleCale
			AngleGet();
			AngleControlValueCalc();
			MotorControl_Out(); //输出电机控制的值
#ifdef AngDataSend
			Float2Byte(&CarInfo_Now.CarAngle, OUTDATA, 2);
			Float2Byte(&CarInfo_Now.CarAngSpeed, OUTDATA, 10);
			Float2Byte(&GravityAngle, OUTDATA, 6);
			LPLD_UART_PutCharArr(UART5, OUTDATA, 16);
#endif

#endif
		}
#ifdef	CCDOn
		if (TimerFlag20ms == 1)
		{
			TimerFlag20ms = 0;
			ccd_carry(ccd_array);
			CalculateIntegrationTime();
#ifdef CCDSendImage
			if (++send_data >= 5)
			{
				send_data = 0;
				//ccd_threshold(ccd_array);
				SendImageData(ccd_array);//发送需要接近10Ms的时间,有点久了
			}
#endif
#ifdef Debuger
			if (debugerConnected == 1)
			{
				AngSendCount++;
				if (AngSendCount >= 30)
				{
					AngSendCount = 0;
					Float2Byte(&CarInfo_Now.CarAngle, SendTemp8b, 3);
					SendTemp8b[1] = 0x08;
					SendTemp8b[2] = Data_AngNow;
					LPLD_UART_PutCharArr(UART5, SendTemp8b, SendTemp8b[1]);
				}
			} //发送角度到调试器
#endif
		}
#endif

	}
}

