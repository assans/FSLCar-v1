///////////////////////////////////////////////////////////////////////////////
//
// IAR ANSI C/C++ Compiler V7.30.1.7746/W32 for ARM       26/Oct/2014  17:07:01
// Copyright 1999-2014 IAR Systems AB.
//
//    Cpu mode     =  thumb
//    Endian       =  little
//    Source file  =  H:\Freescale Code\FSLCar v1\project\MyCar\app\MyCar.c
//    Command line =  
//        "H:\Freescale Code\FSLCar v1\project\MyCar\app\MyCar.c" -D LPLD_K60
//        -lCN "H:\Freescale Code\FSLCar v1\project\MyCar\iar\FLASH\List\" -lB
//        "H:\Freescale Code\FSLCar v1\project\MyCar\iar\FLASH\List\" -o
//        "H:\Freescale Code\FSLCar v1\project\MyCar\iar\FLASH\Obj\" --no_cse
//        --no_unroll --no_inline --no_code_motion --no_tbaa --no_clustering
//        --no_scheduling --debug --endian=little --cpu=Cortex-M4 -e --fpu=None
//        --dlib_config "H:\Embedded Workbench
//        7.0\arm\INC\c\DLib_Config_Normal.h" -I "H:\Freescale Code\FSLCar
//        v1\project\MyCar\iar\..\app\" -I "H:\Freescale Code\FSLCar
//        v1\project\MyCar\iar\..\..\..\lib\CPU\" -I "H:\Freescale Code\FSLCar
//        v1\project\MyCar\iar\..\..\..\lib\common\" -I "H:\Freescale
//        Code\FSLCar v1\project\MyCar\iar\..\..\..\lib\LPLD\" -I "H:\Freescale
//        Code\FSLCar v1\project\MyCar\iar\..\..\..\lib\LPLD\HW\" -I
//        "H:\Freescale Code\FSLCar
//        v1\project\MyCar\iar\..\..\..\lib\LPLD\DEV\" -I "H:\Freescale
//        Code\FSLCar v1\project\MyCar\iar\..\..\..\lib\uCOS-II\Ports\" -I
//        "H:\Freescale Code\FSLCar
//        v1\project\MyCar\iar\..\..\..\lib\uCOS-II\Source\" -I "H:\Freescale
//        Code\FSLCar v1\project\MyCar\iar\..\..\..\lib\FatFs\" -I
//        "H:\Freescale Code\FSLCar
//        v1\project\MyCar\iar\..\..\..\lib\FatFs\option\" -I "H:\Freescale
//        Code\FSLCar v1\project\MyCar\iar\..\..\..\lib\USB\common\" -I
//        "H:\Freescale Code\FSLCar
//        v1\project\MyCar\iar\..\..\..\lib\USB\driver\" -I "H:\Freescale
//        Code\FSLCar v1\project\MyCar\iar\..\..\..\lib\USB\descriptor\" -I
//        "H:\Freescale Code\FSLCar
//        v1\project\MyCar\iar\..\..\..\lib\USB\class\" -Ol -I "H:\Embedded
//        Workbench 7.0\arm\CMSIS\Include\" -D ARM_MATH_CM4
//    List file    =  
//        H:\Freescale Code\FSLCar v1\project\MyCar\iar\FLASH\List\MyCar.s
//
///////////////////////////////////////////////////////////////////////////////

        #define SHT_PROGBITS 0x1

        EXTERN AngleGet
        EXTERN CarInit
        EXTERN Float2Byte
        EXTERN LPLD_GPIO_Toggle_b
        EXTERN LPLD_SYSTICK_DelayMs
        EXTERN LPLD_UART_PutCharArr

        PUBLIC ADC_GET
        PUBLIC AllData
        PUBLIC CarAngSpeed
        PUBLIC CarAngle
        PUBLIC GravityZero
        PUBLIC GyroZero
        PUBLIC OUTPUT_DATA
        PUBLIC PIT0_ISR
        PUBLIC ang
        PUBLIC gyro
        PUBLIC main
        PUBLIC x
        PUBLIC x_f
        PUBLIC y
        PUBLIC z

// H:\Freescale Code\FSLCar v1\project\MyCar\app\MyCar.c
//    1 #include "common.h"
//    2 //#include "DataScope_DP.h"
//    3 #include "Init.h"
//    4 #include "Kalman.h"
//    5 #include "angget.h"

        SECTION `.data`:DATA:REORDER:NOROOT(2)
//    6 uint8 OUTPUT_DATA[] = { 0x03, 0xFC, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 0xFC,0x03 };
OUTPUT_DATA:
        DATA
        DC8 3, 252, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 252, 3

        SECTION `.data`:DATA:REORDER:NOROOT(2)
//    7 uint8 AllData[] = { 0x03, 0xFC, 0, 0, 0, 0, 1, 0xFC, 0x03 };
AllData:
        DATA
        DC8 3, 252, 0, 0, 0, 0, 1, 252, 3, 0, 0, 0

        SECTION `.bss`:DATA:REORDER:NOROOT(0)
//    8 uint8 ang, gyro, x, y, z;
ang:
        DS8 1

        SECTION `.bss`:DATA:REORDER:NOROOT(0)
gyro:
        DS8 1

        SECTION `.bss`:DATA:REORDER:NOROOT(0)
x:
        DS8 1

        SECTION `.bss`:DATA:REORDER:NOROOT(0)
y:
        DS8 1

        SECTION `.bss`:DATA:REORDER:NOROOT(0)
z:
        DS8 1

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
//    9 int GyroZero = 0; //陀螺仪零点
GyroZero:
        DS8 4

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
//   10 int GravityZero = 0; //重力Z轴零点
GravityZero:
        DS8 4

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
//   11 float CarAngle, CarAngSpeed, x_f;
CarAngle:
        DS8 4

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
CarAngSpeed:
        DS8 4

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
x_f:
        DS8 4
//   12 #define mode 1
//   13 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   14 void ADC_GET(void)
//   15 {
ADC_GET:
        PUSH     {R7,LR}
//   16 	if (mode)
//   17 	{
//   18 		AngleGet();
        BL       AngleGet
//   19 		Float2Byte(&CarAngle, OUTPUT_DATA, 2);
        MOVS     R2,#+2
        LDR.N    R1,??DataTable1
        LDR.N    R0,??DataTable1_1
        BL       Float2Byte
//   20 		Float2Byte(&CarAngSpeed, OUTPUT_DATA, 6);
        MOVS     R2,#+6
        LDR.N    R1,??DataTable1
        LDR.N    R0,??DataTable1_2
        BL       Float2Byte
//   21 		Float2Byte(&x_f, OUTPUT_DATA, 10);
        MOVS     R2,#+10
        LDR.N    R1,??DataTable1
        LDR.N    R0,??DataTable1_3
        BL       Float2Byte
//   22 	}
//   23 	else
//   24 	{
//   25 		y = u32_trans_U8(LPLD_ADC_Get(ADC1, AD11));
//   26 		x = u32_trans_U8(LPLD_ADC_Get(ADC1, AD10));
//   27 		z = u32_trans_U8(LPLD_ADC_Get(ADC1, AD12));
//   28 		ang = u32_trans_U8(LPLD_ADC_Get(ADC1, AD13));
//   29 		gyro = u32_trans_U8(LPLD_ADC_Get(ADC1, AD14));
//   30 		AllData[2] = x;
//   31 		AllData[3] = y;
//   32 		AllData[4] = z;
//   33 		AllData[5] = gyro;
//   34 		AllData[6] = ang;
//   35 	}
//   36 }
        POP      {R0,PC}          ;; return

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   37 void main(void)
//   38 {
main:
        PUSH     {R7,LR}
//   39 	CarInit();
        BL       CarInit
//   40 	//GyroZero = GyroScopeGetZero();
//   41 	//GravityZero=GravityGetZero();
//   42 	while (1)
//   43 	{
//   44 		LPLD_GPIO_Toggle_b(PTA, 17);
??main_0:
        MOVS     R1,#+17
        LDR.N    R0,??DataTable1_4  ;; 0x400ff000
        BL       LPLD_GPIO_Toggle_b
//   45 		LPLD_SYSTICK_DelayMs(50);
        MOVS     R0,#+50
        BL       LPLD_SYSTICK_DelayMs
//   46 		ADC_GET();
        BL       ADC_GET
//   47 		if (mode)
//   48 		{
//   49 			LPLD_UART_PutCharArr(UART5, OUTPUT_DATA, 16);
        MOVS     R2,#+16
        LDR.N    R1,??DataTable1
        LDR.N    R0,??DataTable1_5  ;; 0x400eb000
        BL       LPLD_UART_PutCharArr
        B.N      ??main_0
//   50 		}
//   51 		else
//   52 		{
//   53 			LPLD_UART_PutCharArr(UART5, AllData, 9);
//   54 		}
//   55 
//   56 	}
//   57 }

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable1:
        DC32     OUTPUT_DATA

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable1_1:
        DC32     CarAngle

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable1_2:
        DC32     CarAngSpeed

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable1_3:
        DC32     x_f

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable1_4:
        DC32     0x400ff000

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable1_5:
        DC32     0x400eb000
//   58 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   59 void PIT0_ISR(void)
//   60 {
//   61 
//   62 }
PIT0_ISR:
        BX       LR               ;; return

        SECTION `.iar_vfe_header`:DATA:NOALLOC:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
        DC32 0

        SECTION __DLIB_PERTHREAD:DATA:REORDER:NOROOT(0)
        SECTION_TYPE SHT_PROGBITS, 0

        SECTION __DLIB_PERTHREAD_init:DATA:REORDER:NOROOT(0)
        SECTION_TYPE SHT_PROGBITS, 0

        END
// 
//  25 bytes in section .bss
//  28 bytes in section .data
// 100 bytes in section .text
// 
// 100 bytes of CODE memory
//  53 bytes of DATA memory
//
//Errors: none
//Warnings: 2
