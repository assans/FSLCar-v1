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
short acc_x,gyro_2;
float tempfloat = 0;//��ʱ����,û������
float dt = 0.019;//ȫ�ֱ���,������Ҫ���ڵĶ������,һ������20ms
uint8 OUTDATA[20] =
		{ 0x03, 0xfc, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2,3,3,3,3, 0xfc, 0x03 }; //ʾ����
extern float GravityAngle; //������
extern char Flag_1Ms, Flag_5Ms, Flag_10Ms; //ʱ��Ƭ��־
extern uint8 debugerConnected; //�Ƿ����ӵ�������
extern TempOfMotor_TypeDef TempValue; //��ʱ�洢�ǶȺ��ٶȿ��Ƹ�������Ľṹ��
extern float AngleIntegraed;//�Խ��ٶȻ��ֵĽǶ�ֵ
//--������
// #define Timer
// #define	Debuger //�Ƿ�ʹ�õ�����
// #define CCDOn_ //�������߹ر�CCD
// #define CCDSendImage_ //����Ҫ��Ҫ����CCD��ͼ��
// #define AngleCale//��̬����
// #define AngDataSend //�Ƿ�����̬���������
//uint8 timer = 1;
uint8 debuger = 1;
uint8 ccdon = 0;
uint8 ccdsendimage = 0;
uint8 anglecale = 1;
uint8 angdatasend = 1;
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
	Debug_Timer_Init(); //��ʼ������ʱ�������
#endif
	Flash_ReadAllData(); //��Flash�ж�ȡ���е�����
	Struct_Init();
	while (1)
	{
		if (TimerFlag20ms == 1)
		{
			//һ�����ڵĽ���
			TimerFlag20ms = 0; //��ִ��CCD�����ݲɼ�..��Ȼ�ع�ʱ�䲻׼ȷ
			if (ccdon == 1)
			{
				ImageCapture(ccd_array);//20������������(�ȿ�ʼ�ع�,�ع�ʱ�䵽�˾Ͱ�20ms��flag��һ)
				CalculateIntegrationTime();
			}

			Debug_Timer_ReSet();  //���ó���ʱ�������

			LPLD_GPIO_Toggle_b(PTA, 17);
			if (anglecale == 1)
			{
				AngleGet();
				AngleControlValueCalc();
				//SpeedCotorlValueCalc();//�ٶȱջ�,�ȵ�ֱ��,�ٵ��ٶȱջ�
				//DirControlValueCale();//�������
				MotorControl_Out(); //���������Ƶ�ֵ
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
					SendImageData(ccd_array);//������Ҫ�ӽ�10Ms��ʱ��,�е����
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
				} //���ͽǶȵ�������
			}

		}


	}
}

