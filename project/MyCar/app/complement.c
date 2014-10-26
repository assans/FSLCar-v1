#include "complement.h"


//-------------------------------------------------------
//�����˲�
//-------------------------------------------------------
static float angle_com,angle_dot_com; 		//�ⲿ��Ҫ���õı���
extern float CarAngle, CarAngSpeed;
//-------------------------------------------------------
 static float bias_cf;
static const float dt=0.05;
//-------------------------------------------------------
void complement_filter(float angle_m_cf,float gyro_m_cf)
{
	bias_cf*=0.998;			//��������Ʈ��ͨ�˲���500�ξ�ֵ��0.998
	bias_cf+=gyro_m_cf*0.009;		   //0.002
	angle_dot_com=gyro_m_cf-bias_cf;
	angle_com=(angle_com+angle_dot_com*dt)*0.95+angle_m_cf*0.05;
	//���ٶȵ�ͨ�˲���20�ξ�ֵ����100��ÿ����㣬��ͨ5Hz��0.90 0.05
	CarAngSpeed=angle_dot_com;
	CarAngle=angle_com;
}
