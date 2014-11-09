#include "complement.h"

//-------------------------------------------------------
//�����˲�
//-------------------------------------------------------
float angle_com, angle_dot_com; //�ⲿ��Ҫ���õı���
extern float CarAngle, CarAngSpeed;
//-------------------------------------------------------
static float bias_cf = 0;
static const float dt = 0.0115;
//-------------------------------------------------------
void complement_filter(float angle_m_cf, float gyro_m_cf)
{
	bias_cf = bias_cf * 0.9; //��������Ʈ��ͨ�˲���500�ξ�ֵ��0.998
	bias_cf = bias_cf + gyro_m_cf * 0.1; //0.002
	angle_dot_com = gyro_m_cf- bias_cf;
	angle_com = (angle_com + angle_dot_com * dt) * 0.8 + angle_m_cf * 0.2;
	//���ٶȵ�ͨ�˲���20�ξ�ֵ����100��ÿ����㣬��ͨ5Hz��0.90 0.05
//	CarAngSpeed=angle_dot_com;
//	CarAngle=angle_com;
}
//ʱ�䳣��   dt=0.011
//		 t		a		b
//		 0.1	0.9		0.1
//		 0.2	0.947	0.053
//		0.15	0.931	0.069
//
//
//aӦ����0.85-0.9֮��ȽϺ���  ������Ŀǰ�ľ�̬������
//
//
