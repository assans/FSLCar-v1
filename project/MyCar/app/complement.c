#include "complement.h"

//-------------------------------------------------------
//互补滤波
//-------------------------------------------------------
float angle_com, angle_dot_com; //外部需要引用的变量
extern float CarAngle, CarAngSpeed;
//-------------------------------------------------------
static float bias_cf = 0;
static const float dt = 0.0115;
//-------------------------------------------------------
void complement_filter(float angle_m_cf, float gyro_m_cf)
{
	bias_cf = bias_cf * 0.9; //陀螺仪零飘低通滤波；500次均值；0.998
	bias_cf = bias_cf + gyro_m_cf * 0.1; //0.002
	angle_dot_com = gyro_m_cf- bias_cf;
	angle_com = (angle_com + angle_dot_com * dt) * 0.8 + angle_m_cf * 0.2;
	//加速度低通滤波；20次均值；按100次每秒计算，低通5Hz；0.90 0.05
//	CarAngSpeed=angle_dot_com;
//	CarAngle=angle_com;
}
//时间常数   dt=0.011
//		 t		a		b
//		 0.1	0.9		0.1
//		 0.2	0.947	0.053
//		0.15	0.931	0.069
//
//
//a应该在0.85-0.9之间比较合适  陀螺仪目前的静态参数是
//
//
