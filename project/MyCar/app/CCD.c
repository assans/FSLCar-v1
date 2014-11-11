#include "CCD.h"

#define TSL1401_SI(x)   LPLD_GPIO_Output_b(PTA, 28, x)
#define TSL1401_CLK(x)  LPLD_GPIO_Output_b(PTA, 29, x)

uint8 u32_trans_U8(uint16 data); //只有本地用

unsigned char PixelAverageValue; //128个像素点的平均AD值
unsigned char PixelAverageVoltage; //128个像素点的平均电压值的10倍
int TargetPixelAverageVoltage = 30; //设定目标平均电压值，实际电压的10倍
int PixelAverageVoltageError = 0; //设定目标平均电压值与实际值的偏差，实际电压的10倍
int TargetPixelAverageVoltageAllowError = 2; //设定目标平均电压值允许的偏差，实际电压的10倍
unsigned char IntegrationTime = 10; //曝光时间，单位ms
unsigned char TimerFlag20ms = 0;
unsigned char TimerCntCCD = 0;
unsigned int send_data = 0;
unsigned char threshold = 100;

unsigned char ccd_array[128] = { 0 };

void ccd_exposure(void)
{
	unsigned char integration_piont;
	TimerCntCCD++;
	integration_piont = 20 - IntegrationTime;
	if (integration_piont >= 2)
	{
		if (integration_piont == TimerCntCCD)
			StartIntegration();
	}
	if (TimerCntCCD >= 20)
	{
		TimerCntCCD = 0;
		TimerFlag20ms = 1;
	}
}

void StartIntegration(void) //CCD积分计算
{
	unsigned char i;
	TSL1401_SI(1);
	asm("nop");
	asm("nop");
	TSL1401_CLK(1);
	asm("nop");
	asm("nop");
	TSL1401_SI(0);
	asm("nop");
	asm("nop");
	TSL1401_CLK(0);
	for (i = 0; i < 128; i++)
	{
		asm("nop");
		asm("nop");
		asm("nop");
		asm("nop");
		asm("nop");
		TSL1401_CLK(1);
		asm("nop");
		asm("nop");
		asm("nop");
		asm("nop");
		asm("nop");
		TSL1401_CLK(0);
	}
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	TSL1401_CLK(1);
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	TSL1401_CLK(0);
}

void CalculateIntegrationTime(void)
{
	PixelAverageValue = PixelAverage(128, ccd_array);
	PixelAverageVoltage = (unsigned char) ((int) PixelAverageValue * 25 / 128);
	PixelAverageVoltageError = TargetPixelAverageVoltage - PixelAverageVoltage;
	if (PixelAverageVoltageError < -TargetPixelAverageVoltageAllowError)
		IntegrationTime--;
	if (PixelAverageVoltageError > TargetPixelAverageVoltageAllowError)
		IntegrationTime++;
	if (IntegrationTime <= 1)
		IntegrationTime = 1;
	if (IntegrationTime >= 20)
		IntegrationTime = 20;
}

unsigned char PixelAverage(unsigned char len, unsigned char *data)
{
	unsigned char i;
	unsigned int sum = 0;
	for (i = 0; i < len; i++)
	{
		sum = sum + *data++;
	}
	return ((unsigned char) (sum / len));
}

void ccd_carry(unsigned char *carry) //CCD图像获取
{
	int i;
	TSL1401_SI(1);
	asm("nop");
	asm("nop");
	TSL1401_CLK(1);
	asm("nop");
	asm("nop");
	TSL1401_SI(0);
	asm("nop");
	asm("nop");
	carry[0] = u32_trans_U8(LPLD_ADC_Get(ADC0, AD12));
	TSL1401_CLK(0);
	for (i = 1; i < 128; i++)
	{
		asm("nop");
		asm("nop");
		asm("nop");
		asm("nop");
		asm("nop");
		TSL1401_CLK(1);
		asm("nop");
		asm("nop");
		asm("nop");
		asm("nop");
		asm("nop");
		carry[i] = u32_trans_U8(LPLD_ADC_Get(ADC0, AD12));
		TSL1401_CLK(0);
	}
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	TSL1401_CLK(1);
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	TSL1401_CLK(0);
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
}

void SendImageData(unsigned char *ImageData)
{
	unsigned char i;
	unsigned char crc = 0;
	LPLD_UART_PutChar(UART5, '*');
	LPLD_UART_PutChar(UART5, 'L');
	LPLD_UART_PutChar(UART5, 'D');

	SendHex(0);
	SendHex(0);
	SendHex(0);
	SendHex(0);

	for (i = 0; i < 128; i++)
	{
		SendHex(*ImageData++);
	}

	SendHex(crc);
	LPLD_UART_PutChar(UART5, '#');
}

uint8 u32_trans_U8(uint16 data)
{
	return (uint8) ((uint32) data * 255 / 4095);
}

void SendHex(unsigned char hex)
{
	unsigned char temp;
	temp = hex >> 4;
	if (temp < 10)
	{
		LPLD_UART_PutChar(UART5, temp + '0');
	}
	else
	{
		LPLD_UART_PutChar(UART5, temp - 10 + 'A');
	}
	temp = hex & 0x0F;
	if (temp < 10)
	{
		LPLD_UART_PutChar(UART5, temp + '0');
	}
	else
	{
		LPLD_UART_PutChar(UART5, temp - 10 + 'A');
	}
}
