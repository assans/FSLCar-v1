#include "init.h"
#include "DEV_MMA8451.h"
extern void PIT0_ISR(void);
ADC_InitTypeDef Init_ADC_Struct;
GPIO_InitTypeDef Init_GPIO_Struct;
FTM_InitTypeDef Init_FTM_Struct;
PIT_InitTypeDef Init_PIT_Struct;
UART_InitTypeDef Init_UART_Struct;
//I2C_InitTypeDef Init_I2C_Struct;

void Init_PIT(void)
{
	Init_PIT_Struct.PIT_Pitx = PIT0;
	Init_PIT_Struct.PIT_PeriodMs = 1;
	Init_PIT_Struct.PIT_Isr = PIT0_ISR;
	LPLD_PIT_Init(Init_PIT_Struct); //用PIT0来做1MS的中断
	LPLD_PIT_EnableIrq(Init_PIT_Struct); //开启PIT0的中断
}

//void Init_I2C(void)
//{
//	Init_I2C_Struct.I2C_I2Cx=I2C0;
//	Init_I2C_Struct.I2C_ICR=0x2b;
//	Init_I2C_Struct.I2C_IntEnable=FALSE;
//	Init_I2C_Struct.I2C_OpenDrainEnable=TRUE;
////	Init_I2C_Struct.I2C_SclPin=PTB0;
////	Init_I2C_Struct.I2C_SdaPin=PTB1;
//	LPLD_I2C_Init(Init_I2C_Struct);
//}

void Init_ADC(void)
{
	Init_ADC_Struct.ADC_Adcx = ADC1;
	Init_ADC_Struct.ADC_BitMode = SE_12BIT;
	Init_ADC_Struct.ADC_SampleTimeCfg = SAMTIME_SHORT;
	Init_ADC_Struct.ADC_HwAvgSel = HW_4AVG;
	Init_ADC_Struct.ADC_CalEnable = TRUE;
	LPLD_ADC_Init(Init_ADC_Struct);
	LPLD_ADC_Chn_Enable(ADC1, AD14);
	LPLD_ADC_Chn_Enable(ADC1, AD15);
	//开启四个通道的ADC,

//	 *      |__AD14          --单端(ADC1_SE14--PTB10)  //Gyro_1
//	 *      |__AD15          --单端(ADC1_SE15--PTB11) //Gyro_2
}
void Init_GPIO(void)
{
	Init_GPIO_Struct.GPIO_PTx = PTA;
	Init_GPIO_Struct.GPIO_Dir = DIR_OUTPUT;
	Init_GPIO_Struct.GPIO_Output = OUTPUT_H;
	Init_GPIO_Struct.GPIO_Pins = GPIO_Pin17;
	LPLD_GPIO_Init(Init_GPIO_Struct); //初始化LED灯;
}

void CarInit(void)
{
	char whoami = 1; //用來判斷寄存器正常不正常
	Init_ADC();
	Init_PIT();
	Init_GPIO();
	whoami = LPLD_MMA8451_Init();
	//Init_I2C();
}

uint8 u32_trans_U8(uint16 data)
{
	return (uint8) ((((uint32) data << 8) - (uint32) data) >> 12);
}
