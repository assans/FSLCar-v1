#include "AngGet.h"
#include "common.h"
#include "complement.h"
#include "DEV_MMA8451.h"

#define GYROSCOPE_OFFSET 1606
#define GYROSCOPE_ANGLE_RATIO   0.2// (3300/4096)/(0.67*6) //�����ǵ�ǰ�ľ�̬Ϊ2360
extern float CarAngle, CarAngSpeed, x_f;
extern float angle_com, angle_dot_com;
extern short acc_x, acc_y, acc_z, gyro_1, gyro_2;

extern int gyro_avg;
float GravityAngle, GyroscopeAngleSpeed;
float temp_x;

void AngleGet(void)
{

	acc_x = LPLD_MMA8451_GetResult(MMA8451_STATUS_X_READY,
			MMA8451_REG_OUTX_MSB);
	temp_x=(float)acc_x/4096.0;
	if(temp_x>1)
		temp_x=1;
	else if(temp_x<-1)
		temp_x=-1;
//		acc_y = LPLD_MMA8451_GetResult(MMA8451_STATUS_Y_READY,
//				MMA8451_REG_OUTY_MSB);
//	acc_z = LPLD_MMA8451_GetResult(MMA8451_STATUS_X_READY,
//			MMA8451_REG_OUTZ_MSB);
	//gyro_1 = LPLD_ADC_Get(ADC1, AD14);n
	gyro_2 = (LPLD_ADC_Get(ADC1, AD15)-gyro_avg);
	GyroscopeAngleSpeed=(float)gyro_2*GYROSCOPE_ANGLE_RATIO;
	GravityAngle=asinf(temp_x)*57.3;

	complement_filter(GravityAngle,-GyroscopeAngleSpeed);

//	mpu_acc_x = MPU6050_GetResult(ACCEL_XOUT_H);
//	mpu_gyro_y = MPU6050_GetResult(GYRO_YOUT_H);
//	temp_gyro = (float) mpu_gyro_y / 4.096;
//	temp_gyro = -temp_gyro;
//	temp_acc = (float) mpu_acc_x / 4096.0;
//	if (temp_acc > 1)
//		temp_acc = 1;
//	else if (temp_acc < -1)
//		temp_acc = -1;
//	G_Ang = asinf(temp_acc) * 57;
//	Kalman_Filter(G_Ang, temp_gyro);
//	//my_com(G_Ang,temp_gyro);

}

//����˵�����������ȸ�������ת��4�ֽ����ݲ�����ָ����ַ //gittest
//����˵�����û�����ֱ�Ӳ����˺���
//target:Ŀ�굥��������
//buf:��д������
//beg:ָ��������ڼ���Ԫ�ؿ�ʼд��
//�����޷���
void Float2Byte(float *target, int8 *buf, int8 beg)
{
	int8 *point;
	point = (int8*) target; //�õ�float�ĵ�ַ
	buf[beg] = point[0];
	buf[beg + 1] = point[1];
	buf[beg + 2] = point[2];
	buf[beg + 3] = point[3];
}

void Short2Byte(int16 *target, int8 *buf, int8 beg)
{
	int8 *point;
	point = (int8*) target;
	buf[beg] = point[0];
	buf[beg + 1] = point[1];
}
