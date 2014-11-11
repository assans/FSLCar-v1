现在已经使用的模块	FTM0-控制电机
					PIT3-用来计算程序执行时间
					PIT0-作为程序时间片控制
					ADC1-采集陀螺仪的数据 
					IIC0-MMA8451

占用的端口:	USART5 	PTE8-PTE9;
			FTM0   	PTD4,PTD5,PTD6,PTD7;
			LED		PTA17;
			ADC1	PTB10,PTB11
			IIC0	PTD8,PTD9;
			
			
需要调试的参数:	Debug.c:		Ang_PID.Proportion	//比例
								Ang_PID.Integral 	//积分
								Ang_PID.Derivative	//微分
								Ang_PID.AngSet		//调试时调试这一行
								Ang_PID.AngSpeedSet	//角速度的设定值
				AngGet.c		#define AngToMotorRatio 300  //角度转换成电机控制的比例因子..我也不知道取多少合适..以后再调试



使用I2C的DMA来传送数据..因为I2C消耗的时间大概在1.2ms

2014年11月3日 21:40:59  更新了流程控制和IIC的速度以后..IIC读取加速度值大概在0.5Ms左右.总共计算加上滤波 0.8Ms,加上发送数据到串口需要1.7Ms

2014年11月5日 21:38:03  写一个头文件定义所有的数据结构和Extern..暂时定为DataStructure.h

2014年11月6日 21:50:07  因为发送数据的时间太长(三个轴的数据发送需要1ms),暂时决定使用DMA来发送串口数据

2014年11月9日 15:15:11  DMA配置不成功,发送时间需要1MS,直接发送,

2014年11月11日 13:05:16	改用了卡尔曼滤波,角速度收敛有点慢
					   