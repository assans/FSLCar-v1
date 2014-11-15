#include "datastructure.h"
#include "common.h"
#include "AngGet.h"


uint8 ReadBuffer[DATA_SIZE];
uint8 WriteBuffer[DATA_SIZE];
float Flash_DataBuffer[NumOfFloat];//存放读取出来的数据

void delay();
void Flash_ReadAllData(void)
{
	uint8 *ptr;
	uint8 len = 0;
	ptr = (uint8*) FLASH_ADDR;
	for (len = 0; len <= DATA_SIZE; len++)
	{
		ReadBuffer[len] = *(ptr + len);
		WriteBuffer[len] = ReadBuffer[len]; //将读出来的数据放到写入buffer里面,防止在未对writebuffer初始化的情况下写入
	}
	for(len=0;len<=NumOfFloat;len++)
	{
		Byte2Float(Flash_DataBuffer+len,ReadBuffer,len*4); //需要测试这段代码是否正常
	}
}
void Flash_WriteAllData(void)
{
  uint8 result;
    DisableInterrupts;
    result=LPLD_Flash_SectorErase(FLASH_ADDR);
    EnableInterrupts; //先擦除
    delay();

    DisableInterrupts;
    result=LPLD_Flash_ByteProgram((uint32)FLASH_ADDR, (uint32*)WriteBuffer, DATA_SIZE);
    EnableInterrupts;
    delay();

    if(result==FLASH_OK)
    {
    	//这里写返回给调试器的指令
    }
    else
    {

    }
}
void Flash_DataToBuffer(float data,uint8 num)//num为第n个数据
{
	uint8 temp;
	temp=DATA_SIZE/4;
	if(num<=temp)
	{
	Float2Byte(&data,WriteBuffer,num*4);
	}
}
void Flash_WriteTest(void)
{
	uint8 i;
	for(i=0;i<DATA_SIZE;i++)
	{
		WriteBuffer[i]=i;
	}
	Flash_WriteAllData();
	Flash_ReadAllData();
	LPLD_UART_PutCharArr(UART5,ReadBuffer,DATA_SIZE);
}

void delay()
{
  uint16 i, n;
  for(i=0;i<3000;i++)
  {
    for(n=0;n<200;n++)
    {
      asm("nop");
    }
  }//PLL在100MHz的时候大概延迟5ms
}
