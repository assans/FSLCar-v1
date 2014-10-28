#include "MPU6050.h"
#define	SMPLRT_DIV		0x19	//陀螺仪采样率，典型值：0x07(125Hz)
#define	CONFIG			0x1A	//低通滤波频率，典型值：0x06(5Hz)
#define	GYRO_CONFIG		0x1B	//陀螺仪自检及测量范围，典型值：0x18(不自检，2000deg/s)
#define	ACCEL_CONFIG	0x1C	//加速计自检、测量范围及高通滤波频率，典型值：0x01(不自检，2G，5Hz)
#define	ACCEL_XOUT_H	0x3B
#define	ACCEL_XOUT_L	0x3C
#define	ACCEL_YOUT_H	0x3D
#define	ACCEL_YOUT_L	0x3E
#define	ACCEL_ZOUT_H	0x3F
#define	ACCEL_ZOUT_L	0x40
#define	TEMP_OUT_H		0x41
#define	TEMP_OUT_L		0x42
#define	GYRO_XOUT_H		0x43
#define	GYRO_XOUT_L		0x44
#define	GYRO_YOUT_H		0x45
#define	GYRO_YOUT_L		0x46
#define	GYRO_ZOUT_H		0x47
#define	GYRO_ZOUT_L		0x48
#define	PWR_MGMT_1		0x6B	//电源管理，典型值：0x00(正常启用)
#define	WHO_AM_I			0x75	//IIC地址寄存器(默认数值0x68，只读)
#define	SlaveAddress	0xD0	//IIC写入时的地址字节数据，+1为读取
static void MMA8451_Delay(void);

/*
 *   MPU6050_Init
 *   初始化MMA8451，包括初始化8451所需的I2C接口以及8451的寄存器
 *
 *   参数：
 *    无
 *
 *   返回值
 *      设备ID
 */
uint8 MPU6050_Init(void)
{
//  I2C_InitTypeDef i2c_init_param;
	uint8 device_id;
//
//  //初始化I2C0
//  i2c_init_param.I2C_I2Cx = I2C0;       //在DEV_MMA8451.h中修改该值
//  i2c_init_param.I2C_IntEnable = FALSE;
//  i2c_init_param.I2C_ICR = MMA8451_SCL_200KHZ;  //可根据实际电路更改SCL频率
//  i2c_init_param.I2C_SclPin = MMA8451_SCLPIN;   //在DEV_MMA8451.h中修改该值
//  i2c_init_param.I2C_SdaPin = MMA8451_SDAPIN;   //在DEV_MMA8451.h中修改该值
//  i2c_init_param.I2C_Isr = NULL;
//
//  LPLD_I2C_Init(i2c_init_param);

//读取设备ID
	device_id = MPU6050_ReadReg(WHO_AM_I);
	MPU6050_WriteReg(PWR_MGMT_1, 0x00); //解除休眠状态
	MPU6050_WriteReg(SMPLRT_DIV, 0x07);
	MPU6050_WriteReg(CONFIG, 0x06);
	MPU6050_WriteReg(GYRO_CONFIG, 0x18);
	MPU6050_WriteReg(ACCEL_CONFIG, 0x01);

	return device_id;
}

/*
 *   MPU6050_WriteReg
 *   该函数用于配置MMA8451的寄存器
 *
 *   参数：
 *   RegisterAddress
 *    |__ MMA8451寄存器地址
 *   Data
 *    |__ 具体写入的字节型数据
 */
void MPU6050_WriteReg(uint8 RegisterAddress, uint8 Data)
{
	//发送从机地址
	// LPLD_I2C_StartTrans(I2C0, MMA8451_DEV_ADDR, I2C_MWSR);
	LPLD_I2C_Start(I2C0);
	LPLD_I2C_WriteByte(I2C0, SlaveAddress);
	LPLD_I2C_WaitAck(I2C0, I2C_ACK_ON);

	//写MMA8451寄存器地址
	LPLD_I2C_WriteByte(I2C0, RegisterAddress);
	LPLD_I2C_WaitAck(I2C0, I2C_ACK_ON);

	//向寄存器中写具体数据
	LPLD_I2C_WriteByte(I2C0, Data);
	LPLD_I2C_WaitAck(I2C0, I2C_ACK_ON);

	LPLD_I2C_Stop(I2C0);

	//MMA8451_Delay();
}

/*
 *   MPU6050_WriteReg
 *   该函数用于读取MMA8451的数据
 *
 *   参数：
 *     RegisterAddress
 *        |__ MMA8451寄存器地址
 *   返回值
 *      加速传感器的测量值
 */
uint8 MPU6050_ReadReg(uint8 RegisterAddress)
{
	uint8 result;

	//发送从机地址
	LPLD_I2C_Start(I2C0);
	LPLD_I2C_WriteByte(I2C0, SlaveAddress);
	LPLD_I2C_WaitAck(I2C0, I2C_ACK_ON);

	//写MMA8451寄存器地址
	LPLD_I2C_WriteByte(I2C0, RegisterAddress);
	LPLD_I2C_WaitAck(I2C0, I2C_ACK_ON);

	//再次产生开始信号
	LPLD_I2C_ReStart(I2C0);

	//发送从机地址和读取位
	LPLD_I2C_WriteByte(I2C0, SlaveAddress + 1);
	LPLD_I2C_WaitAck(I2C0, I2C_ACK_ON);

	//转换主机模式为读
	LPLD_I2C_SetMasterWR(I2C0, I2C_MRSW);

	//关闭应答ACK
	LPLD_I2C_WaitAck(I2C0, I2C_ACK_OFF); //关闭ACK

	//读IIC数据
	result = LPLD_I2C_ReadByte(I2C0);
	LPLD_I2C_WaitAck(I2C0, I2C_ACK_ON);

	//发送停止信号
	LPLD_I2C_Stop(I2C0);

	//读IIC数据
	result = LPLD_I2C_ReadByte(I2C0);

	MMA8451_Delay();

	return result;
}

/*
 * 函数功能：读MAA8451加速度输出
 * 参数
 *       Regs_Addr - 数据寄存器地址
 * 函数返回值：加速度值（int16）
 */
int16 MPU6050_GetResult(uint8 Regs_Addr)
{

	int16 result, temp;
	result = MPU6050_ReadReg(Regs_Addr);
	temp = MPU6050_ReadReg(Regs_Addr + 1);
	result = result << 8;
	result = result | temp;

	return result >> 2;
}

/*
 * 延时函数
 */
static void MMA8451_Delay(void)
{
	int n;
	for (n = 1; n < 200; n++)
	{
		asm("nop");
	}
}
