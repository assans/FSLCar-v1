///////////////////////////////////////////////////////////////////////////////
//
// IAR ANSI C/C++ Compiler V7.30.1.7746/W32 for ARM       26/Oct/2014  17:12:37
// Copyright 1999-2014 IAR Systems AB.
//
//    Cpu mode     =  thumb
//    Endian       =  little
//    Source file  =  
//        H:\Freescale Code\FSLCar v1\project\MyCar\app\complement.c
//    Command line =  
//        "H:\Freescale Code\FSLCar v1\project\MyCar\app\complement.c" -D
//        LPLD_K60 -lCN "H:\Freescale Code\FSLCar
//        v1\project\MyCar\iar\FLASH\List\" -lB "H:\Freescale Code\FSLCar
//        v1\project\MyCar\iar\FLASH\List\" -o "H:\Freescale Code\FSLCar
//        v1\project\MyCar\iar\FLASH\Obj\" --no_cse --no_unroll --no_inline
//        --no_code_motion --no_tbaa --no_clustering --no_scheduling --debug
//        --endian=little --cpu=Cortex-M4 -e --fpu=None --dlib_config
//        "H:\Embedded Workbench 7.0\arm\INC\c\DLib_Config_Normal.h" -I
//        "H:\Freescale Code\FSLCar v1\project\MyCar\iar\..\app\" -I
//        "H:\Freescale Code\FSLCar v1\project\MyCar\iar\..\..\..\lib\CPU\" -I
//        "H:\Freescale Code\FSLCar v1\project\MyCar\iar\..\..\..\lib\common\"
//        -I "H:\Freescale Code\FSLCar v1\project\MyCar\iar\..\..\..\lib\LPLD\"
//        -I "H:\Freescale Code\FSLCar
//        v1\project\MyCar\iar\..\..\..\lib\LPLD\HW\" -I "H:\Freescale
//        Code\FSLCar v1\project\MyCar\iar\..\..\..\lib\LPLD\DEV\" -I
//        "H:\Freescale Code\FSLCar
//        v1\project\MyCar\iar\..\..\..\lib\uCOS-II\Ports\" -I "H:\Freescale
//        Code\FSLCar v1\project\MyCar\iar\..\..\..\lib\uCOS-II\Source\" -I
//        "H:\Freescale Code\FSLCar v1\project\MyCar\iar\..\..\..\lib\FatFs\"
//        -I "H:\Freescale Code\FSLCar
//        v1\project\MyCar\iar\..\..\..\lib\FatFs\option\" -I "H:\Freescale
//        Code\FSLCar v1\project\MyCar\iar\..\..\..\lib\USB\common\" -I
//        "H:\Freescale Code\FSLCar
//        v1\project\MyCar\iar\..\..\..\lib\USB\driver\" -I "H:\Freescale
//        Code\FSLCar v1\project\MyCar\iar\..\..\..\lib\USB\descriptor\" -I
//        "H:\Freescale Code\FSLCar
//        v1\project\MyCar\iar\..\..\..\lib\USB\class\" -Ol -I "H:\Embedded
//        Workbench 7.0\arm\CMSIS\Include\" -D ARM_MATH_CM4
//    List file    =  
//        H:\Freescale Code\FSLCar v1\project\MyCar\iar\FLASH\List\complement.s
//
///////////////////////////////////////////////////////////////////////////////

        #define SHT_PROGBITS 0x1

        EXTERN CarAngSpeed
        EXTERN CarAngle
        EXTERN __aeabi_d2f
        EXTERN __aeabi_dadd
        EXTERN __aeabi_dmul
        EXTERN __aeabi_f2d
        EXTERN __aeabi_fadd
        EXTERN __aeabi_fmul
        EXTERN __aeabi_fsub

        PUBLIC complement_filter

// H:\Freescale Code\FSLCar v1\project\MyCar\app\complement.c
//    1 #include "complement.h"
//    2 
//    3 
//    4 //-------------------------------------------------------
//    5 //互补滤波
//    6 //-------------------------------------------------------

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
//    7 static float angle_com,angle_dot_com; 		//外部需要引用的变量
angle_com:
        DS8 4

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
angle_dot_com:
        DS8 4
//    8 extern float CarAngle, CarAngSpeed;
//    9 //-------------------------------------------------------

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
//   10  static float bias_cf;
bias_cf:
        DS8 4

        SECTION `.rodata`:CONST:REORDER:NOROOT(2)
//   11 static const float dt=0.05;
dt:
        DATA
        DC32 3D4CCCCDH
//   12 //-------------------------------------------------------

        SECTION `.text`:CODE:NOROOT(2)
        THUMB
//   13 void complement_filter(float angle_m_cf,float gyro_m_cf)
//   14 {
complement_filter:
        PUSH     {R3-R7,LR}
        MOVS     R6,R0
        MOVS     R7,R1
//   15 	bias_cf*=0.998;			//陀螺仪零飘低通滤波；500次均值；0.998
        LDR.N    R0,??complement_filter_0
        LDR      R0,[R0, #+0]
        BL       __aeabi_f2d
        LDR.N    R2,??complement_filter_0+0x4  ;; 0xb22d0e56
        LDR.N    R3,??complement_filter_0+0x8  ;; 0x3fefef9d
        BL       __aeabi_dmul
        BL       __aeabi_d2f
        LDR.N    R1,??complement_filter_0
        STR      R0,[R1, #+0]
//   16 	bias_cf+=gyro_m_cf*0.009;		   //0.002
        LDR.N    R0,??complement_filter_0
        LDR      R0,[R0, #+0]
        BL       __aeabi_f2d
        MOVS     R4,R0
        MOVS     R5,R1
        MOVS     R0,R7
        BL       __aeabi_f2d
        LDR.N    R2,??complement_filter_0+0xC  ;; 0x8d4fdf3b
        LDR.N    R3,??complement_filter_0+0x10  ;; 0x3f826e97
        BL       __aeabi_dmul
        MOVS     R2,R4
        MOVS     R3,R5
        BL       __aeabi_dadd
        BL       __aeabi_d2f
        LDR.N    R1,??complement_filter_0
        STR      R0,[R1, #+0]
//   17 	angle_dot_com=gyro_m_cf-bias_cf;
        MOVS     R0,R7
        LDR.N    R1,??complement_filter_0
        LDR      R1,[R1, #+0]
        BL       __aeabi_fsub
        LDR.N    R1,??complement_filter_0+0x14
        STR      R0,[R1, #+0]
//   18 	angle_com=(angle_com+angle_dot_com*dt)*0.95+angle_m_cf*0.05;
        LDR.N    R0,??complement_filter_0+0x14
        LDR      R1,[R0, #+0]
        LDR.N    R0,??complement_filter_0+0x18
        LDR      R0,[R0, #+0]
        BL       __aeabi_fmul
        LDR.N    R1,??complement_filter_0+0x1C
        LDR      R1,[R1, #+0]
        BL       __aeabi_fadd
        BL       __aeabi_f2d
        MOVS     R2,#+1717986918
        LDR.N    R3,??complement_filter_0+0x20  ;; 0x3fee6666
        BL       __aeabi_dmul
        MOVS     R4,R0
        MOVS     R5,R1
        MOVS     R0,R6
        BL       __aeabi_f2d
        LDR.N    R2,??complement_filter_0+0x24  ;; 0x9999999a
        LDR.N    R3,??complement_filter_0+0x28  ;; 0x3fa99999
        BL       __aeabi_dmul
        MOVS     R2,R4
        MOVS     R3,R5
        BL       __aeabi_dadd
        BL       __aeabi_d2f
        LDR.N    R1,??complement_filter_0+0x1C
        STR      R0,[R1, #+0]
//   19 	//加速度低通滤波；20次均值；按100次每秒计算，低通5Hz；0.90 0.05
//   20 	CarAngSpeed=angle_dot_com;
        LDR.N    R0,??complement_filter_0+0x14
        LDR      R0,[R0, #+0]
        LDR.N    R1,??complement_filter_0+0x2C
        STR      R0,[R1, #+0]
//   21 	CarAngle=angle_com;
        LDR.N    R0,??complement_filter_0+0x1C
        LDR      R0,[R0, #+0]
        LDR.N    R1,??complement_filter_0+0x30
        STR      R0,[R1, #+0]
//   22 }
        POP      {R0,R4-R7,PC}    ;; return
        DATA
??complement_filter_0:
        DC32     bias_cf
        DC32     0xb22d0e56
        DC32     0x3fefef9d
        DC32     0x8d4fdf3b
        DC32     0x3f826e97
        DC32     angle_dot_com
        DC32     dt
        DC32     angle_com
        DC32     0x3fee6666
        DC32     0x9999999a
        DC32     0x3fa99999
        DC32     CarAngSpeed
        DC32     CarAngle

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
//  12 bytes in section .bss
//   4 bytes in section .rodata
// 224 bytes in section .text
// 
// 224 bytes of CODE  memory
//   4 bytes of CONST memory
//  12 bytes of DATA  memory
//
//Errors: none
//Warnings: none
