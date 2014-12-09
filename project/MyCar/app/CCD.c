#include "CCD.h"
void SamplingDelay(void);
#define TSL1401_SI(x)   LPLD_GPIO_Output_b(PTA, 28, x)
#define TSL1401_CLK(x)  LPLD_GPIO_Output_b(PTA, 29, x)

#define SI_SetVal() LPLD_GPIO_Output_b(PTA, 28, 1)
#define SI_ClrVal() LPLD_GPIO_Output_b(PTA, 28, 0)
#define CLK_SetVal() LPLD_GPIO_Output_b(PTA, 29, 1)
#define CLK_ClrVal() LPLD_GPIO_Output_b(PTA, 29, 0)

//SI--PTA28
//CLK-PTA29
//AD--PTB2

uint8 u32_trans_uint8(uint16 data); //ֻ�б�����

unsigned char TimerCntCCD = 0;
unsigned char TimerFlag20ms = 0;
uint16 send_data = 0;
uint8 IntegrationTime = 10;
unsigned char ccd_array[128] = { 0 };

void ccd_exposure(void)//ͬʱҲ��Ϊʱ��Ƭ��ת��ʱ��
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



void StartIntegration(void) 
{

	unsigned char i;

	SI_SetVal();            /* SI  = 1 */
	SamplingDelay();
	CLK_SetVal();           /* CLK = 1 */
	SamplingDelay();
	SI_ClrVal();            /* SI  = 0 */
	SamplingDelay();
	CLK_ClrVal();           /* CLK = 0 */

	for (i = 0; i < 127; i++) {
		SamplingDelay();
		SamplingDelay();
		CLK_SetVal();       /* CLK = 1 */
		SamplingDelay();
		SamplingDelay();
		CLK_ClrVal();       /* CLK = 0 */
	}
	SamplingDelay();
	SamplingDelay();
	CLK_SetVal();           /* CLK = 1 */
	SamplingDelay();
	SamplingDelay();
	CLK_ClrVal();           /* CLK = 0 */
}


void ImageCapture(unsigned char * ImageData) 
{

	unsigned char i;
	extern uint8 AtemP;

	SI_SetVal();            /* SI  = 1 */
	SamplingDelay();
	CLK_SetVal();           /* CLK = 1 */
	SamplingDelay();
	SI_ClrVal();            /* SI  = 0 */
	SamplingDelay();

	//Delay 10us for sample the first pixel
	/**/
	for (i = 0; i < 250; i++) {                    //����250����CCD��ͼ����ȥ�Ƚ�ƽ����
		SamplingDelay();  //200ns                  //�Ѹ�ֵ�Ĵ���߸�С�ﵽ�Լ�����Ľ����
	}

	//Sampling Pixel 1

	*ImageData = u32_trans_uint8(LPLD_ADC_Get(ADC0, AD12));
	ImageData++;
	CLK_ClrVal();           /* CLK = 0 */

	for (i = 0; i < 127; i++) {
		SamplingDelay();
		SamplingDelay();
		CLK_SetVal();       /* CLK = 1 */
		SamplingDelay();
		SamplingDelay();
		//Sampling Pixel 2~128

		*ImageData = u32_trans_uint8(LPLD_ADC_Get(ADC0, AD12));
		ImageData++;
		CLK_ClrVal();       /* CLK = 0 */
	}
	SamplingDelay();
	SamplingDelay();
	CLK_SetVal();           /* CLK = 1 */
	SamplingDelay();
	SamplingDelay();
	CLK_ClrVal();           /* CLK = 0 */
}



/* �ع�ʱ�䣬��λms */

void CalculateIntegrationTime(void)
{
	//extern uint8 Pixel[128];
	/* 128�����ص��ƽ��ADֵ */
	uint8 PixelAverageValue;
	/* 128�����ص��ƽ����ѹֵ��10�� */
	uint8 PixelAverageVoltage;
	/* �趨Ŀ��ƽ����ѹֵ��ʵ�ʵ�ѹ��10�� */
	uint16 TargetPixelAverageVoltage = 25;
	/* �趨Ŀ��ƽ����ѹֵ��ʵ��ֵ��ƫ�ʵ�ʵ�ѹ��10�� */
	char PixelAverageVoltageError = 0;
	/* �趨Ŀ��ƽ����ѹֵ�����ƫ�ʵ�ʵ�ѹ��10�� */
	uint16 TargetPixelAverageVoltageAllowError = 2;

	/* ����128�����ص��ƽ��ADֵ */
	PixelAverageValue = PixelAverage(128, ccd_array);
	/* ����128�����ص��ƽ����ѹֵ,ʵ��ֵ��10�� */
	PixelAverageVoltage = (unsigned char)((int)PixelAverageValue * 25 / 194);//��0-194ƽ���ֳ���25��

	PixelAverageVoltageError = TargetPixelAverageVoltage - PixelAverageVoltage;
	if (PixelAverageVoltageError < -TargetPixelAverageVoltageAllowError)
	{
		PixelAverageVoltageError = 0 - PixelAverageVoltageError;
		PixelAverageVoltageError /= 2;
		if (PixelAverageVoltageError > 10)
			PixelAverageVoltageError = 10;
		IntegrationTime -= PixelAverageVoltageError;
	}
	if (PixelAverageVoltageError > TargetPixelAverageVoltageAllowError)
	{
		PixelAverageVoltageError /= 2;
		if (PixelAverageVoltageError > 10)
			PixelAverageVoltageError = 10;
		IntegrationTime += PixelAverageVoltageError;
	}


	//  LPLD_UART_PutChar(UART5,0XAA) ;

	//   LPLD_UART_PutChar(UART5,PixelAverageVoltage) ;
	//   LPLD_UART_PutChar(UART5,PixelAverageVoltageError) ;
	//    LPLD_UART_PutChar(UART5,IntegrationTime) ;
	if (IntegrationTime <= 1)
		IntegrationTime = 1;
	if (IntegrationTime >= 100)
		IntegrationTime = 100;
}


uint8 PixelAverage(uint8 len, uint8 *data) {
	unsigned char i;
	unsigned int sum = 0;
	for (i = 0; i < len; i++) {
		sum = sum + *data++;
	}
	return ((unsigned char)(sum / len));
}

void SendHex(unsigned char hex) 
{
	unsigned char temp;
	temp = hex >> 4;
	if (temp < 10) {
		LPLD_UART_PutChar(UART5, temp + '0');
	}
	else {
		LPLD_UART_PutChar(UART5, temp - 10 + 'A');
	}
	temp = hex & 0x0F;
	if (temp < 10) {
		LPLD_UART_PutChar(UART5, temp + '0');
	}
	else {
		LPLD_UART_PutChar(UART5, temp - 10 + 'A');
	}
}

void SendImageData(unsigned char * ImageData) 
{

	unsigned char i;
	unsigned char crc = 0;

	/* Send Data */
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


void SamplingDelay(void)
{
	volatile uint8 i;
	for (i = 0; i < 1; i++) {
		asm("nop");
		asm("nop");
	}

}
uint8 u32_trans_uint8(uint16 data)
{
	return (uint8)((uint32)data * 255 / 4095);
}