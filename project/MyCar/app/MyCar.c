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
//#include "DataScope_DP.h"

CarInfo_TypeDef CarInfo_Now;
CarControl_TypeDef MotorControl; //�洢������Ƶ�ֵ
short acc_x, acc_y, acc_z, gyro_1, gyro_2;
int gyro_avg = 2360; //���ٶ�ADƽ��ֵ
uint8 OUTDATA[16] =
		{ 0x03, 0xfc, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 0xfc, 0x03 };
extern float GravityAngle;
extern char Flag_1Ms, Flag_5Ms, Flag_10Ms;
//--������
#define Debug
#define CCDOn //�������߹ر�CCD
#define CCDSendImage //����Ҫ��Ҫ����CCD��ͼ��
//����������
void main(void)
{
	Struct_Init(); //��ʼ���ֽṹ���ֵ
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
			MotorControl_Out(); //���������Ƶ�ֵ
			Float2Byte(&CarInfo_Now.CarAngle, OUTDATA, 2);
			Float2Byte(&CarInfo_Now.CarAngSpeed, OUTDATA, 10);
			Float2Byte(&GravityAngle, OUTDATA, 6);
			LPLD_UART_PutCharArr(UART5, OUTDATA, 16);
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
				SendImageData(ccd_array);
			}
#endif
		}
#endif

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
