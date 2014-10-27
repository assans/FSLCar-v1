#include "AngGet.h"
#include "common.h"
#include "Kalman.h"
#include "complement.h"
#define GRAVITY_OFFSET     2130
#define VOLTAGE_GRAVITY   Angle_AD[0]  //加速度x
#define VOLTAGE_GYRO      Angle_AD[1]  //陀螺仪
#define CAR_ANGLE_RANGE	   180     //车辆角度范围
#define GRAVITY_MAX        3370//重力最大值
#define GRAVITY_MIN        963//重力最小值
#define GRAVITY_ANGLE_RATIO	((float)CAR_ANGLE_RANGE / (float)((GRAVITY_MAX - GRAVITY_MIN)) )  //这一行需要优化
#define GYROSCOPE_OFFSET 1606
#define GYROSCOPE_ANGLE_RATIO   0.004// (3300/4096)/(0.67*5.1)*(3.14/180) =

//extern int GyroZero;
//extern int GravityZero;
extern float CarAngle,CarAngSpeed,x_f;
extern float angle_com,angle_dot_com;
int Angle_AD[2]={0,0};
float GravityAngle,GyroscopeAngleSpeed;

void AngleCalculate(void)
{
	GravityAngle = (float)((VOLTAGE_GRAVITY - GRAVITY_OFFSET) * GRAVITY_ANGLE_RATIO);
	GyroscopeAngleSpeed = (float)((VOLTAGE_GYRO - GYROSCOPE_OFFSET) * GYROSCOPE_ANGLE_RATIO);

}
void AngleGet(void)
{
	Angle_AD[0]=LPLD_ADC_Get(ADC1,AD10); //采集x轴加速度
	Angle_AD[1]=LPLD_ADC_Get(ADC1,AD14); //采集陀螺仪角速度
	AngleCalculate();
	//Kalman_Filter(GravityAngle,GyroscopeAngleSpeed);

//	CarAngSpeed=angle_dot;
//	CarAngle=angle;
	complement_filter(GravityAngle,GyroscopeAngleSpeed);
	x_f=GravityAngle;

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
