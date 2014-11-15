#ifndef _DATASTRUCTURE_H
#define _DATASTRUCTURE_H
#include "common.h"

#define NumOfFloat	5
#define DATA_SIZE	NumOfFloat*4
#define FLASH_SECTOR   (60)
#define FLASH_ADDR     (FLASH_SECTOR*2048)
extern uint8 ReadBuffer[DATA_SIZE];
extern uint8 WriteBuffer[DATA_SIZE];
extern float Flash_DataBuffer[NumOfFloat];

typedef struct
{
	float AngSet; //�趨�ĽǶ�
	float AngSpeedSet; //�趨�Ľ��ٶ�
	//float SetPoint;
	float Delta; //���
	float LastError; //E(k-1)
	float PrevError; //E(k-2);

	float Proportion; //��������
	float Integral; //���ֳ���;
	float Derivative; //΢�ֳ���;

//float LastError;
//float PrevError;
} IncPID_InitTypeDef; //����PID�����ݽṹ

typedef struct
{
	int L_Speed;
	int R_Speed;
} CarControl_TypeDef; //�������Ƶ��

typedef struct
{
	unsigned long int MotorRightSpeed; //ͨ��������������
	unsigned long int MotorLeftSpeed; //ͨ��������������
	float CarAngle;
	float CarAngSpeed;
} CarInfo_TypeDef; //�浱ǰ������Ϣ

typedef struct
{
	float AngControl_OutValue;
	float Speed_RightOutValut;
	float Speed_LeftOutValue;
} TempOfMotor_TypeDef;

void Flash_WriteTest(void);
void Flash_DataToBuffer(float data,uint8 num);
void Flash_WriteAllData(void);
void Flash_ReadAllData(void);

#endif
