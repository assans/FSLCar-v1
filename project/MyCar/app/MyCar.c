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
short acc_x,gyro_2;
float tempfloat = 0;//临时变量,没有意义
float dt = 0.019;//全局变量,所有需要周期的都是这个,一个周期20ms
uint8 OUTDATA[20] =
		{ 0x03, 0xfc, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2,3,3,3,3, 0xfc, 0x03 }; //示波器
extern float GravityAngle; //重力角
extern char Flag_1Ms, Flag_5Ms, Flag_10Ms; //时间片标志
extern uint8 debugerConnected; //是否连接到调试器
extern TempOfMotor_TypeDef TempValue; //临时存储角度和速度控制浮点变量的结构体
extern float AngleIntegraed;//对角速度积分的角度值
//--控制区
// #define Timer
// #define	Debuger //是否使用调试器
// #define CCDOn_ //开启或者关闭CCD
// #define CCDSendImage_ //控制要不要发送CCD的图像
// #define AngleCale//姿态解算
// #define AngDataSend //是否发送姿态解算的数据
//uint8 timer = 1;
uint8 debuger = 1;
uint8 ccdon = 0;
uint8 ccdsendimage = 0;
uint8 anglecale = 1;
uint8 angdatasend = 1;
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
	Debug_Timer_Init(); //初始化程序时间计数器
#endif
	Flash_ReadAllData(); //从Flash中读取所有的数据
	Struct_Init();
	while (1)
	{
		if (TimerFlag20ms == 1)
		{
			//一个周期的结束
			TimerFlag20ms = 0; //先执行CCD的数据采集..不然曝光时间不准确
			if (ccdon == 1)
			{
				ImageCapture(ccd_array);//20毫秒周期里面(先开始曝光,曝光时间到了就把20ms的flag置一)
				CalculateIntegrationTime();
			}

			Debug_Timer_ReSet();  //重置程序时间计数器

			LPLD_GPIO_Toggle_b(PTA, 17);
			if (anglecale == 1)
			{
				AngleGet();
				AngleControlValueCalc();
				//SpeedCotorlValueCalc();//速度闭环,先调直立,再调速度闭环
				//DirControlValueCale();//方向控制
				MotorControl_Out(); //输出电机控制的值
			}
			if (angdatasend == 1)
			{
				tempfloat = TempValue.AngControl_OutValue / 10.0;
				Float2Byte(&CarInfo_Now.CarAngle, OUTDATA, 2);
				//Float2Byte(&CarInfo_Now.CarAngSpeed, OUTDATA, 10);
				Float2Byte(&tempfloat, OUTDATA, 10);
				Float2Byte(&GravityAngle, OUTDATA, 6);
				tempfloat = (float)gyro_2;
				Float2Byte(&tempfloat, OUTDATA, 14);
				LPLD_UART_PutCharArr(UART5, OUTDATA, 20);
			}

			if (ccdsendimage == 1)
			{
				if (++send_data >= 2)
				{
					send_data = 0;
					//ccd_threshold(ccd_array);
					SendImageData(ccd_array);//发送需要接近10Ms的时间,有点久了
				}
			}
			if (debuger == 1)
			{
				if (debugerConnected == 1)
				{
					angdatasend = 0;
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
			}

		}


	}
}

