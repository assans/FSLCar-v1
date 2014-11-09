#ifndef _DATASTRUCTURE_H
#define _DATASTRUCTURE_H
#include "common.h"


typedef struct
{
	float AngSet;//�趨�ĽǶ�
	float AngSpeedSet;//�趨�Ľ��ٶ�
	//float SetPoint;
	float Delta;//�ۻ����

	double Proportion;//��������
	double Integral;//���ֳ���;
	double Derivative;//΢�ֳ���;

	//float LastError;
	//float PrevError;
}IncPID_InitTypeDef; //����PID�����ݽṹ

typedef struct
{
	int L_Speed;
	int R_Speed;
}CarControl_TypeDef; //�������Ƶ��

typedef struct
{
	unsigned long int MotorRightSpeed;  //ͨ��������������
	unsigned long int MotorLeftSpeed;   //ͨ��������������
	float CarAngle;
	float CarAngSpeed;
}CarInfo_TypeDef;  //�浱ǰ������Ϣ

typedef struct
{
	float AngControl_OutValue;
	float Speed_RightOutValut;
	float Speed_LeftOutValue;
}TempOfMotor_TypeDef;

#endif
