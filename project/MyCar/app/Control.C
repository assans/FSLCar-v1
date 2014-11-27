#include "Control.h"

float AngToMotorRatio=300;//角度转换成电机控制的比例因子..我也不知道取多少合适..以后再调试
#define MOTOR_OUT_MAX       10000
#define MOTOR_OUT_MIN       -10000
#define ANGLE_CONTROL_OUT_MAX			MOTOR_OUT_MAX
#define ANGLE_CONTROL_OUT_MIN			MOTOR_OUT_MIN

extern CarInfo_TypeDef CarInfo_Now; //当前车子的信息
extern CarControl_TypeDef MotorControl; //电机控制的值
extern IncPID_InitTypeDef Ang_PID; //角度控制的PID结构体
extern TempOfMotor_TypeDef TempValue; //临时存储角度和速度控制浮点变量的结构体

void AngleControlValueCalc(void)
{
	float ControlValue;
	Ang_PID.Delta = Ang_PID.AngSet - CarInfo_Now.CarAngle; //当前误差//这里全是角度,值很小
	ControlValue = Ang_PID.Delta * Ang_PID.Proportion +CarInfo_Now.CarAngSpeed* Ang_PID.PrevError; //微分项
//	Ang_PID.PrevError = Ang_PID.LastError;
//	Ang_PID.LastError = Ang_PID.Delta; //PID的三步
	ControlValue *= AngToMotorRatio; //乘上比例因子将角度转换成PWM的占空比
	if (ControlValue > ANGLE_CONTROL_OUT_MAX)
		ControlValue = ANGLE_CONTROL_OUT_MAX;
	if (ControlValue < ANGLE_CONTROL_OUT_MIN)
		ControlValue = ANGLE_CONTROL_OUT_MIN; //限幅
	TempValue.AngControl_OutValue = ControlValue; //更新控制临时变量的值
}

void MotorControl_Out(void)
{
	MotorControl.L_Speed = (int) TempValue.AngControl_OutValue
			+ (int) TempValue.Speed_LeftOutValue; //取整
	MotorControl.R_Speed = (int) TempValue.AngControl_OutValue
			+ (int) TempValue.Speed_RightOutValut; //

	if (MotorControl.L_Speed > MOTOR_OUT_MAX)
	{
		MotorControl.L_Speed = MOTOR_OUT_MAX;
	}
	else if (MotorControl.L_Speed < MOTOR_OUT_MIN)
	{
		MotorControl.L_Speed = MOTOR_OUT_MIN;
	}
	if (MotorControl.R_Speed > MOTOR_OUT_MAX)
	{
		MotorControl.R_Speed = MOTOR_OUT_MAX;
	}
	else if (MotorControl.R_Speed < MOTOR_OUT_MIN)
	{
		MotorControl.R_Speed = MOTOR_OUT_MIN;
	} //限幅不能超过10000

	if (MotorControl.L_Speed >= 0)
	{
		LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch4, MotorControl.L_Speed);
		LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch5, 0);
	}
	else
	{
		MotorControl.L_Speed = -MotorControl.L_Speed; //为负值取反
		LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch4, 0);
		LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch5, MotorControl.L_Speed);
	}
	if (MotorControl.R_Speed >= 0)
	{
		LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch6, MotorControl.R_Speed);
		LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch7, 0);
	}
	else
	{
		MotorControl.R_Speed = -MotorControl.R_Speed;
		LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch6, 0);
		LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch7, MotorControl.R_Speed);
	}
}

//int IncPIDCalc(int NextPoint)
//{
//	int iIncPID;
//	iError=Ang_PID.SetPoint-NextPoint; //需要将角度换算成电机的PWM
//	iIncPID=(int)((Ang_PID.Proportion*iError-Ang_PID.Integral*Ang_PID.LastError+Ang_PID.Derivative*Ang_PID.PrevError));
//	Ang_PID.PrevError=Ang_PID.LastError;
//	Ang_PID.LastError=iError;
//	return(iIncPID);
//}
