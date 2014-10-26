#include "complement.h"


//-------------------------------------------------------
//互补滤波
//-------------------------------------------------------
static float angle_com,angle_dot_com; 		//外部需要引用的变量
extern float CarAngle, CarAngSpeed;
//-------------------------------------------------------
 static float bias_cf;
static const float dt=0.05;
//-------------------------------------------------------
void complement_filter(float angle_m_cf,float gyro_m_cf)
{
	bias_cf*=0.998;			//陀螺仪零飘低通滤波；500次均值；0.998
	bias_cf+=gyro_m_cf*0.009;		   //0.002
	angle_dot_com=gyro_m_cf-bias_cf;
	angle_com=(angle_com+angle_dot_com*dt)*0.95+angle_m_cf*0.05;
	//加速度低通滤波；20次均值；按100次每秒计算，低通5Hz；0.90 0.05
	CarAngSpeed=angle_dot_com;
	CarAngle=angle_com;
}
