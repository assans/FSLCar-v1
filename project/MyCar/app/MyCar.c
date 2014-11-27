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
CarControl_TypeDef MotorControl; //�洢������Ƶ�ֵ
short acc_x, acc_y, acc_z, gyro_1, gyro_2;
uint8 OUTDATA[16] =
		{ 0x03, 0xfc, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 0xfc, 0x03 }; //ʾ����
extern float GravityAngle; //������
extern char Flag_1Ms, Flag_5Ms, Flag_10Ms; //ʱ��Ƭ��־
extern uint8 debugerConnected; //�Ƿ����ӵ�������
//--������
#define Timer
#define	Debuger //�Ƿ�ʹ�õ�����
#define CCDOn //�������߹ر�CCD
#define CCDSendImage_NO //����Ҫ��Ҫ����CCD��ͼ��
#define AngleCale//��̬����
#define AngDataSend_NO //�Ƿ�����̬���������
//����������
uint8 AngSendCount = 0; //���ƽǶȵķ��ʹ���

unsigned char testbyte[4];
void main(void)
{
	Struct_Init(); //��ʼ���ֽṹ���ֵ
	CarInit();
	LPLD_Flash_Init(); //��ʼ��EEPROM,���еĳ�ʼ�����ݱ�����EEPROM�ĵ�60������
//	Flash_WriteTest(); ����flash��

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
			MotorControl_Out(); //���������Ƶ�ֵ
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
				SendImageData(ccd_array);//������Ҫ�ӽ�10Ms��ʱ��,�е����
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
			} //���ͽǶȵ�������
#endif
		}
#endif

	}
}

