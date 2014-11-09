#include "AngGet.h"
#include "common.h"
#include "complement.h"
#include "DEV_MMA8451.h"
#include "datastructure.h"
#define GYROSCOPE_ANGLE_RATIO   0.1336// (3300/4096)/(0.67*6) //陀螺仪当前的静态为2360  //这个是放大9倍
/*各项输出限幅*/
#define AngToMotorRatio 300  //角度转换成电机控制的比例因子..我也不知道取多少合适..以后再调试
#define MOTOR_OUT_MAX       10000
#define MOTOR_OUT_MIN       -10000
#define ANGLE_CONTROL_OUT_MAX			MOTOR_OUT_MAX
#define ANGLE_CONTROL_OUT_MIN			MOTOR_OUT_MIN

extern CarInfo_TypeDef CarInfo_Now; //当前车子的信息
extern CarControl_TypeDef MotorControl; //电机控制的值
extern float angle_com, angle_dot_com;
extern short acc_x, acc_y, acc_z, gyro_1, gyro_2;
extern int gyro_avg;

IncPID_InitTypeDef Ang_PID; //角度控制的PID结构体
TempOfMotor_TypeDef TempValue; //临时存储角度和速度控制浮点变量的结构体
float GravityAngle, GyroscopeAngleSpeed;
float temp_x;

void AngleGet(void)
{
	acc_x = LPLD_MMA8451_GetResult(MMA8451_STATUS_X_READY,
			MMA8451_REG_OUTX_MSB);
	temp_x = (float) acc_x / 4096.0;
	if (temp_x > 1)
		temp_x = 1;
	else if (temp_x < -1)
		temp_x = -1;
//		acc_y = LPLD_MMA8451_GetResult(MMA8451_STATUS_Y_READY,
//				MMA8451_REG_OUTY_MSB);
//	acc_z = LPLD_MMA8451_GetResult(MMA8451_STATUS_X_READY,
//			MMA8451_REG_OUTZ_MSB);
	//gyro_1 = LPLD_ADC_Get(ADC1, AD14);n
	gyro_2 = (LPLD_ADC_Get(ADC1, AD15) - gyro_avg);
	GyroscopeAngleSpeed = (float) gyro_2 * GYROSCOPE_ANGLE_RATIO;
	GravityAngle = asinf(temp_x) * 57.3;

	complement_filter(GravityAngle, -GyroscopeAngleSpeed);

	CarInfo_Now.CarAngle = angle_com;
	CarInfo_Now.CarAngSpeed = angle_dot_com;

}

void AngleControlValueCalc(void)
{
	float ControlValue;
	Ang_PID.Delta = Ang_PID.AngSet - CarInfo_Now.CarAngle; //当前误差//这里全是角度,值很小
	ControlValue = Ang_PID.Delta * Ang_PID.Proportion
			+ (Ang_PID.AngSpeedSet - CarInfo_Now.CarAngSpeed) //计算角速度的误差
			* Ang_PID.Derivative; //PD控制//输出的是角度
	ControlValue *= AngToMotorRatio; //乘上比例因子将角度转换成PWM的占空比
	if (ControlValue > ANGLE_CONTROL_OUT_MAX)
		ControlValue = ANGLE_CONTROL_OUT_MAX;
	if (ControlValue < ANGLE_CONTROL_OUT_MIN)
		ControlValue = ANGLE_CONTROL_OUT_MIN; //限幅
	TempValue.AngControl_OutValue = ControlValue;
}
void MotorControl_Out(void)
{
	MotorControl.L_Speed = (int) TempValue.AngControl_OutValue + (int)TempValue.Speed_LeftOutValue; //取整
	MotorControl.R_Speed=(int)TempValue.AngControl_OutValue+(int)TempValue.Speed_RightOutValut;//

	if(MotorControl.L_Speed>MOTOR_OUT_MAX)
	{
		MotorControl.L_Speed=MOTOR_OUT_MAX;
	}
	else if(MotorControl.L_Speed<MOTOR_OUT_MIN)
	{
		MotorControl.L_Speed=MOTOR_OUT_MIN;
	}
	if(MotorControl.R_Speed>MOTOR_OUT_MAX)
	{
		MotorControl.R_Speed=MOTOR_OUT_MAX;
	}
	else if(MotorControl.R_Speed<MOTOR_OUT_MIN)
	{
		MotorControl.R_Speed=MOTOR_OUT_MIN;
	} //限幅不能超过10000

	if(MotorControl.L_Speed>=0)
	{
		LPLD_FTM_PWM_ChangeDuty(FTM0,FTM_Ch4,MotorControl.L_Speed);
		LPLD_FTM_PWM_ChangeDuty(FTM0,FTM_Ch5,0);
	}
	else
	{
		MotorControl.L_Speed=-MotorControl.L_Speed;//为负值取反
		LPLD_FTM_PWM_ChangeDuty(FTM0,FTM_Ch4,0);
		LPLD_FTM_PWM_ChangeDuty(FTM0,FTM_Ch5,MotorControl.L_Speed);
	}
	if(MotorControl.R_Speed>=0)
	{
		LPLD_FTM_PWM_ChangeDuty(FTM0,FTM_Ch6,MotorControl.R_Speed);
		LPLD_FTM_PWM_ChangeDuty(FTM0,FTM_Ch7,0);
	}
	else
	{
		MotorControl.R_Speed=-MotorControl.R_Speed;
		LPLD_FTM_PWM_ChangeDuty(FTM0,FTM_Ch6,0);
		LPLD_FTM_PWM_ChangeDuty(FTM0,FTM_Ch7,MotorControl.R_Speed);
	}
}

int IncPIDCalc(int NextPoint)
{
//	int iIncPID;
//	iError=Ang_PID.SetPoint-NextPoint; //需要将角度换算成电机的PWM
//	iIncPID=(int)((Ang_PID.Proportion*iError-Ang_PID.Integral*Ang_PID.LastError+Ang_PID.Derivative*Ang_PID.PrevError));
//	Ang_PID.PrevError=Ang_PID.LastError;
//	Ang_PID.LastError=iError;
//	return(iIncPID);
}

//函数说明：将单精度浮点数据转成4字节数据并存入指定地址 //gittest
//附加说明：用户无需直接操作此函数
//target:目标单精度数据
//buf:待写入数组
//beg:指定从数组第几个元素开始写入
//函数无返回
void Float2Byte(float *target,unsigned char *buf,unsigned char beg)
{
    unsigned char *point;
    point = (unsigned char*)target;	  //得到float的地址
    buf[beg]   = point[0];
    buf[beg+1] = point[1];
    buf[beg+2] = point[2];
    buf[beg+3] = point[3];
}

void Short2Byte(int16 *target, int8 *buf, int8 beg)
{
	int8 *point;
	point = (int8*) target;
	buf[beg] = point[0];
	buf[beg + 1] = point[1];
}
