#ifndef _DATASTRUCTURE_H
#define _DATASTRUCTURE_H
#include "common.h"


typedef struct
{
	float AngSet;//设定的角度
	float AngSpeedSet;//设定的角速度
	//float SetPoint;
	float Delta;//累积误差

	double Proportion;//比例常数
	double Integral;//积分常数;
	double Derivative;//微分常数;

	//float LastError;
	//float PrevError;
}IncPID_InitTypeDef; //增量PID的数据结构

typedef struct
{
	int L_Speed;
	int R_Speed;
}CarControl_TypeDef; //用来控制电机

typedef struct
{
	unsigned long int MotorRightSpeed;  //通过编码器读出来
	unsigned long int MotorLeftSpeed;   //通过编码器读出来
	float CarAngle;
	float CarAngSpeed;
}CarInfo_TypeDef;  //存当前车的信息

typedef struct
{
	float AngControl_OutValue;
	float Speed_RightOutValut;
	float Speed_LeftOutValue;
}TempOfMotor_TypeDef;

#endif
