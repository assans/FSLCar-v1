#include "AngGet.h"
#include "common.h"
#include "Kalman.h"
#include "complement.h"
#define GRAVITY_OFFSET     2130
#define VOLTAGE_GRAVITY   Angle_AD[0]  //���ٶ�x
#define VOLTAGE_GYRO      Angle_AD[1]  //������
#define CAR_ANGLE_RANGE	   180     //�����Ƕȷ�Χ
#define GRAVITY_MAX        3370//�������ֵ
#define GRAVITY_MIN        963//������Сֵ
#define GRAVITY_ANGLE_RATIO	((float)CAR_ANGLE_RANGE / (float)((GRAVITY_MAX - GRAVITY_MIN)) )  //��һ����Ҫ�Ż�
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
	Angle_AD[0]=LPLD_ADC_Get(ADC1,AD10); //�ɼ�x����ٶ�
	Angle_AD[1]=LPLD_ADC_Get(ADC1,AD14); //�ɼ������ǽ��ٶ�
	AngleCalculate();
	//Kalman_Filter(GravityAngle,GyroscopeAngleSpeed);

//	CarAngSpeed=angle_dot;
//	CarAngle=angle;
	complement_filter(GravityAngle,GyroscopeAngleSpeed);
	x_f=GravityAngle;

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
