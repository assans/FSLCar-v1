#include "AngGet.h"
#include "common.h"
#include "complement.h"
#include "DEV_MMA8451.h"
#include "datastructure.h"
#define GYROSCOPE_ANGLE_RATIO   0.1336// (3300/4096)/(0.67*6) //�����ǵ�ǰ�ľ�̬Ϊ2360  //����ǷŴ�9��
/*��������޷�*/
#define AngToMotorRatio 300  //�Ƕ�ת���ɵ�����Ƶı�������..��Ҳ��֪��ȡ���ٺ���..�Ժ��ٵ���
#define MOTOR_OUT_MAX       10000
#define MOTOR_OUT_MIN       -10000
#define ANGLE_CONTROL_OUT_MAX			MOTOR_OUT_MAX
#define ANGLE_CONTROL_OUT_MIN			MOTOR_OUT_MIN

extern CarInfo_TypeDef CarInfo_Now; //��ǰ���ӵ���Ϣ
extern CarControl_TypeDef MotorControl; //������Ƶ�ֵ
extern float angle_com, angle_dot_com;
extern short acc_x, acc_y, acc_z, gyro_1, gyro_2;
extern int gyro_avg;

IncPID_InitTypeDef Ang_PID; //�Ƕȿ��Ƶ�PID�ṹ��
TempOfMotor_TypeDef TempValue; //��ʱ�洢�ǶȺ��ٶȿ��Ƹ�������Ľṹ��
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
	Ang_PID.Delta = Ang_PID.AngSet - CarInfo_Now.CarAngle; //��ǰ���//����ȫ�ǽǶ�,ֵ��С
	ControlValue = Ang_PID.Delta * Ang_PID.Proportion
			+ (Ang_PID.AngSpeedSet - CarInfo_Now.CarAngSpeed) //������ٶȵ����
			* Ang_PID.Derivative; //PD����//������ǽǶ�
	ControlValue *= AngToMotorRatio; //���ϱ������ӽ��Ƕ�ת����PWM��ռ�ձ�
	if (ControlValue > ANGLE_CONTROL_OUT_MAX)
		ControlValue = ANGLE_CONTROL_OUT_MAX;
	if (ControlValue < ANGLE_CONTROL_OUT_MIN)
		ControlValue = ANGLE_CONTROL_OUT_MIN; //�޷�
	TempValue.AngControl_OutValue = ControlValue;
}
void MotorControl_Out(void)
{
	MotorControl.L_Speed = (int) TempValue.AngControl_OutValue + (int)TempValue.Speed_LeftOutValue; //ȡ��
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
	} //�޷����ܳ���10000

	if(MotorControl.L_Speed>=0)
	{
		LPLD_FTM_PWM_ChangeDuty(FTM0,FTM_Ch4,MotorControl.L_Speed);
		LPLD_FTM_PWM_ChangeDuty(FTM0,FTM_Ch5,0);
	}
	else
	{
		MotorControl.L_Speed=-MotorControl.L_Speed;//Ϊ��ֵȡ��
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
//	iError=Ang_PID.SetPoint-NextPoint; //��Ҫ���ǶȻ���ɵ����PWM
//	iIncPID=(int)((Ang_PID.Proportion*iError-Ang_PID.Integral*Ang_PID.LastError+Ang_PID.Derivative*Ang_PID.PrevError));
//	Ang_PID.PrevError=Ang_PID.LastError;
//	Ang_PID.LastError=iError;
//	return(iIncPID);
}

//����˵�����������ȸ�������ת��4�ֽ����ݲ�����ָ����ַ //gittest
//����˵�����û�����ֱ�Ӳ����˺���
//target:Ŀ�굥��������
//buf:��д������
//beg:ָ��������ڼ���Ԫ�ؿ�ʼд��
//�����޷���
void Float2Byte(float *target,unsigned char *buf,unsigned char beg)
{
    unsigned char *point;
    point = (unsigned char*)target;	  //�õ�float�ĵ�ַ
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
