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
	float AngSet; //设定的角度
	float AngSpeedSet; //设定的角速度
	//float SetPoint;
	float Delta; //误差
	float LastError; //E(k-1)
	float PrevError; //E(k-2);

	float Proportion; //比例常数
	float Integral; //积分常数;
	float Derivative; //微分常数;

//float LastError;
//float PrevError;
} IncPID_InitTypeDef; //增量PID的数据结构

typedef struct
{
	int L_Speed;
	int R_Speed;
} CarControl_TypeDef; //用来控制电机

typedef struct
{
	unsigned long int MotorRightSpeed; //通过编码器读出来
	unsigned long int MotorLeftSpeed; //通过编码器读出来
	float CarAngle;
	float CarAngSpeed;
} CarInfo_TypeDef; //存当前车的信息

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
