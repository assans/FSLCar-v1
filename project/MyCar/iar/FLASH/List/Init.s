///////////////////////////////////////////////////////////////////////////////
//
// IAR ANSI C/C++ Compiler V7.30.1.7746/W32 for ARM       25/Oct/2014  20:29:47
// Copyright 1999-2014 IAR Systems AB.
//
//    Cpu mode     =  thumb
//    Endian       =  little
//    Source file  =  H:\Freescale Code\FSLCar v1\project\MyCar\app\Init.c
//    Command line =  
//        "H:\Freescale Code\FSLCar v1\project\MyCar\app\Init.c" -D LPLD_K60
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
//        H:\Freescale Code\FSLCar v1\project\MyCar\iar\FLASH\List\Init.s
//
///////////////////////////////////////////////////////////////////////////////

        #define SHT_PROGBITS 0x1

        EXTERN LPLD_ADC_Chn_Enable
        EXTERN LPLD_ADC_Init
        EXTERN LPLD_GPIO_Init
        EXTERN LPLD_PIT_EnableIrq
        EXTERN LPLD_PIT_Init
        EXTERN PIT0_ISR
        EXTERN __aeabi_memcpy4

        PUBLIC CarInit
        PUBLIC Init_ADC
        PUBLIC Init_ADC_Struct
        PUBLIC Init_FTM_Struct
        PUBLIC Init_GPIO
        PUBLIC Init_GPIO_Struct
        PUBLIC Init_PIT
        PUBLIC Init_PIT_Struct
        PUBLIC Init_UART_Struct
        PUBLIC u32_trans_U8

// H:\Freescale Code\FSLCar v1\project\MyCar\app\Init.c
//    1 #include "init.h"
//    2 #include "hw_ftm.h"
//    3 #include "hw_gpio.h"
//    4 #include "hw_adc.h"
//    5 #include "hw_uart.h"
//    6 extern void PIT0_ISR(void);

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
//    7 ADC_InitTypeDef Init_ADC_Struct;
Init_ADC_Struct:
        DS8 20

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
//    8 GPIO_InitTypeDef Init_GPIO_Struct;
Init_GPIO_Struct:
        DS8 20

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
//    9 FTM_InitTypeDef Init_FTM_Struct;
Init_FTM_Struct:
        DS8 28

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
//   10 PIT_InitTypeDef Init_PIT_Struct;
Init_PIT_Struct:
        DS8 20

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
//   11 UART_InitTypeDef Init_UART_Struct;
Init_UART_Struct:
        DS8 20
//   12 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   13 void Init_PIT(void)
//   14 {
Init_PIT:
        PUSH     {R7,LR}
//   15 	Init_PIT_Struct.PIT_Pitx=PIT0;
        MOVS     R0,#+0
        LDR.N    R1,??DataTable2
        STRB     R0,[R1, #+0]
//   16 	Init_PIT_Struct.PIT_PeriodMs=1;
        MOVS     R0,#+1
        LDR.N    R1,??DataTable2
        STR      R0,[R1, #+8]
//   17 	Init_PIT_Struct.PIT_Isr= PIT0_ISR;
        LDR.N    R0,??DataTable2_1
        LDR.N    R1,??DataTable2
        STR      R0,[R1, #+16]
//   18 	LPLD_PIT_Init(Init_PIT_Struct);  //用PIT0来做1MS的中断
        LDR.N    R1,??DataTable2
        SUB      SP,SP,#+16
        MOV      R0,SP
        MOVS     R2,#+20
        BL       __aeabi_memcpy4
        POP      {R0-R3}
        BL       LPLD_PIT_Init
//   19 	LPLD_PIT_EnableIrq(Init_PIT_Struct); //开启PIT0的中断
        LDR.N    R1,??DataTable2
        SUB      SP,SP,#+16
        MOV      R0,SP
        MOVS     R2,#+20
        BL       __aeabi_memcpy4
        POP      {R0-R3}
        BL       LPLD_PIT_EnableIrq
//   20 }
        POP      {R0,PC}          ;; return

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   21 void Init_ADC(void)
//   22 {
Init_ADC:
        PUSH     {R7,LR}
//   23 	Init_ADC_Struct.ADC_Adcx=ADC1;
        LDR.N    R0,??DataTable2_2  ;; 0x400bb000
        LDR.N    R1,??DataTable2_3
        STR      R0,[R1, #+0]
//   24 	Init_ADC_Struct.ADC_BitMode=SE_12BIT;
        MOVS     R0,#+1
        LDR.N    R1,??DataTable2_3
        STRB     R0,[R1, #+5]
//   25 	Init_ADC_Struct.ADC_SampleTimeCfg=SAMTIME_SHORT;
        MOVS     R0,#+0
        LDR.N    R1,??DataTable2_3
        STRB     R0,[R1, #+6]
//   26 	Init_ADC_Struct.ADC_HwAvgSel=HW_4AVG;
        MOVS     R0,#+4
        LDR.N    R1,??DataTable2_3
        STRB     R0,[R1, #+8]
//   27 	Init_ADC_Struct.ADC_CalEnable=TRUE;
        MOVS     R0,#+1
        LDR.N    R1,??DataTable2_3
        STRB     R0,[R1, #+11]
//   28 	LPLD_ADC_Init(Init_ADC_Struct);
        LDR.N    R1,??DataTable2_3
        SUB      SP,SP,#+16
        MOV      R0,SP
        MOVS     R2,#+20
        BL       __aeabi_memcpy4
        POP      {R0-R3}
        BL       LPLD_ADC_Init
//   29 	LPLD_ADC_Chn_Enable(ADC1,AD10);
        MOVS     R1,#+10
        LDR.N    R0,??DataTable2_2  ;; 0x400bb000
        BL       LPLD_ADC_Chn_Enable
//   30 	LPLD_ADC_Chn_Enable(ADC1,AD11);
        MOVS     R1,#+11
        LDR.N    R0,??DataTable2_2  ;; 0x400bb000
        BL       LPLD_ADC_Chn_Enable
//   31 	LPLD_ADC_Chn_Enable(ADC1,AD12);
        MOVS     R1,#+12
        LDR.N    R0,??DataTable2_2  ;; 0x400bb000
        BL       LPLD_ADC_Chn_Enable
//   32 
//   33 	LPLD_ADC_Chn_Enable(ADC1,AD14);
        MOVS     R1,#+14
        LDR.N    R0,??DataTable2_2  ;; 0x400bb000
        BL       LPLD_ADC_Chn_Enable
//   34 	LPLD_ADC_Chn_Enable(ADC1,AD13);
        MOVS     R1,#+13
        LDR.N    R0,??DataTable2_2  ;; 0x400bb000
        BL       LPLD_ADC_Chn_Enable
//   35 	//开启四个通道的ADC,
//   36 	 //*      |__AD10          --单端(ADC1_SE10--PTB4)  //ACC_X
//   37 	 //*      |__AD11          --单端(ADC1_SE11--PTB5)  //ACC_Y
//   38 	 //*      |__AD12          --单端(ADC1_SE12--PTB6)  //ACC_Z
//   39 
//   40 	 //*      |__AD14          --单端(ADC1_SE14--PTB10) //Gyro
//   41 	 //*      |__AD13          --单端(ADC1_SE15--PTB7) //ANG
//   42 }
        POP      {R0,PC}          ;; return

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   43 void Init_GPIO(void)
//   44 {
Init_GPIO:
        PUSH     {R7,LR}
//   45 	Init_GPIO_Struct.GPIO_PTx=PTA;
        LDR.N    R0,??DataTable2_4  ;; 0x400ff000
        LDR.N    R1,??DataTable2_5
        STR      R0,[R1, #+0]
//   46 	Init_GPIO_Struct.GPIO_Dir=DIR_OUTPUT;
        MOVS     R0,#+1
        LDR.N    R1,??DataTable2_5
        STRB     R0,[R1, #+12]
//   47 	Init_GPIO_Struct.GPIO_Output=OUTPUT_H;
        MOVS     R0,#+1
        LDR.N    R1,??DataTable2_5
        STRB     R0,[R1, #+13]
//   48 	Init_GPIO_Struct.GPIO_Pins=GPIO_Pin17;
        MOVS     R0,#+131072
        LDR.N    R1,??DataTable2_5
        STR      R0,[R1, #+4]
//   49 	LPLD_GPIO_Init(Init_GPIO_Struct);  //初始化LED灯;
        LDR.N    R1,??DataTable2_5
        SUB      SP,SP,#+16
        MOV      R0,SP
        MOVS     R2,#+20
        BL       __aeabi_memcpy4
        POP      {R0-R3}
        BL       LPLD_GPIO_Init
//   50 }
        POP      {R0,PC}          ;; return

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable2:
        DC32     Init_PIT_Struct

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable2_1:
        DC32     PIT0_ISR

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable2_2:
        DC32     0x400bb000

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable2_3:
        DC32     Init_ADC_Struct

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable2_4:
        DC32     0x400ff000

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable2_5:
        DC32     Init_GPIO_Struct
//   51 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   52 void CarInit(void)
//   53 {
CarInit:
        PUSH     {R7,LR}
//   54 	Init_ADC();
        BL       Init_ADC
//   55 	Init_PIT();
        BL       Init_PIT
//   56 	Init_GPIO();
        BL       Init_GPIO
//   57 }
        POP      {R0,PC}          ;; return
//   58 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   59 uint8 u32_trans_U8(uint16 data)
//   60 {
//   61   return (uint8)((((uint32)data<<8)-(uint32)data)>>12);
u32_trans_U8:
        UXTH     R0,R0            ;; ZeroExt  R0,R0,#+16,#+16
        MOVS     R1,R0
        UXTH     R1,R1            ;; ZeroExt  R1,R1,#+16,#+16
        RSBS     R0,R1,R0, LSL #+8
        LSRS     R0,R0,#+12
        UXTB     R0,R0            ;; ZeroExt  R0,R0,#+24,#+24
        BX       LR               ;; return
//   62 }

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
// 108 bytes in section .bss
// 254 bytes in section .text
// 
// 254 bytes of CODE memory
// 108 bytes of DATA memory
//
//Errors: none
//Warnings: none
