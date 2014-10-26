///////////////////////////////////////////////////////////////////////////////
//
// IAR ANSI C/C++ Compiler V7.30.1.7746/W32 for ARM       26/Oct/2014  16:51:59
// Copyright 1999-2014 IAR Systems AB.
//
//    Cpu mode     =  thumb
//    Endian       =  little
//    Source file  =  H:\Freescale Code\FSLCar v1\project\MyCar\app\Kalman.c
//    Command line =  
//        "H:\Freescale Code\FSLCar v1\project\MyCar\app\Kalman.c" -D LPLD_K60
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
//        H:\Freescale Code\FSLCar v1\project\MyCar\iar\FLASH\List\Kalman.s
//
///////////////////////////////////////////////////////////////////////////////

        #define SHT_PROGBITS 0x1

        EXTERN __aeabi_fadd
        EXTERN __aeabi_fdiv
        EXTERN __aeabi_fmul
        EXTERN __aeabi_fsub
        EXTERN __aeabi_ui2f

        PUBLIC C_0
        PUBLIC E
        PUBLIC K_0
        PUBLIC K_1
        PUBLIC Kalman_Filter
        PUBLIC P
        PUBLIC PCt_0
        PUBLIC PCt_1
        PUBLIC Pdot
        PUBLIC Q_angle
        PUBLIC Q_gyro
        PUBLIC R_angle
        PUBLIC angle
        PUBLIC angle_dot
        PUBLIC angle_err
        PUBLIC dt
        PUBLIC q_bias
        PUBLIC t_0
        PUBLIC t_1

// H:\Freescale Code\FSLCar v1\project\MyCar\app\Kalman.c
//    1 #include "Kalman.h"
//    2 
//    3 //*
//    4 //-------------------------------------------------------
//    5 //Kalman滤波，8MHz的处理时间约1.8ms；
//    6 //-------------------------------------------------------

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
//    7 float angle, angle_dot; 		//外部需要引用的变量
angle:
        DS8 4

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
angle_dot:
        DS8 4
//    8 //-------------------------------------------------------

        SECTION `.data`:DATA:REORDER:NOROOT(2)
//    9 float Q_angle=0.001, Q_gyro=0.07, R_angle=0.001, dt=0.1;
Q_angle:
        DATA
        DC32 3A83126FH

        SECTION `.data`:DATA:REORDER:NOROOT(2)
Q_gyro:
        DATA
        DC32 3D8F5C29H

        SECTION `.data`:DATA:REORDER:NOROOT(2)
R_angle:
        DATA
        DC32 3A83126FH

        SECTION `.data`:DATA:REORDER:NOROOT(2)
dt:
        DATA
        DC32 3DCCCCCDH
//   10 			//注意：dt的取值为kalman滤波器采样时间;

        SECTION `.data`:DATA:REORDER:NOROOT(2)
//   11 float P[2][2] = {{ 1, 0 },{ 0, 1 }};
P:
        DATA
        DC32 3F800000H, 0H, 0H, 3F800000H
//   12 	

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
//   13 float Pdot[4] ={0,0,0,0};
Pdot:
        DS8 16
//   14 

        SECTION `.rodata`:CONST:REORDER:NOROOT(0)
//   15 const char C_0 = 1;
C_0:
        DATA
        DC8 1
//   16 

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
//   17 float q_bias, angle_err, PCt_0, PCt_1, E, K_0, K_1, t_0, t_1;
q_bias:
        DS8 4

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
angle_err:
        DS8 4

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
PCt_0:
        DS8 4

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
PCt_1:
        DS8 4

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
E:
        DS8 4

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
K_0:
        DS8 4

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
K_1:
        DS8 4

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
t_0:
        DS8 4

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
t_1:
        DS8 4
//   18 //-------------------------------------------------------
//   19 

        SECTION `.text`:CODE:NOROOT(2)
        THUMB
//   20 void Kalman_Filter(float angle_m,float gyro_m)			//gyro_m:gyro_measure
//   21 {
Kalman_Filter:
        PUSH     {R3-R5,LR}
        MOVS     R4,R0
        MOVS     R5,R1
//   22 	
//   23 	angle+=(gyro_m-q_bias) * dt;//先验估计
        MOVS     R0,R5
        LDR.N    R1,??Kalman_Filter_0
        LDR      R1,[R1, #+0]
        BL       __aeabi_fsub
        LDR.N    R1,??Kalman_Filter_0+0x4
        LDR      R1,[R1, #+0]
        BL       __aeabi_fmul
        LDR.N    R1,??Kalman_Filter_0+0x8
        LDR      R1,[R1, #+0]
        BL       __aeabi_fadd
        LDR.N    R1,??Kalman_Filter_0+0x8
        STR      R0,[R1, #+0]
//   24 	
//   25 	Pdot[0]=Q_angle - P[0][1] - P[1][0];// Pk-' 先验估计误差协方差的微分
        LDR.N    R0,??Kalman_Filter_0+0xC
        LDR      R0,[R0, #+0]
        LDR.N    R1,??Kalman_Filter_0+0x10
        LDR      R1,[R1, #+4]
        BL       __aeabi_fsub
        LDR.N    R1,??Kalman_Filter_0+0x10
        LDR      R1,[R1, #+8]
        BL       __aeabi_fsub
        LDR.N    R1,??Kalman_Filter_0+0x14
        STR      R0,[R1, #+0]
//   26 	Pdot[1]=- P[1][1];
        LDR.N    R0,??Kalman_Filter_0+0x10
        LDR      R0,[R0, #+12]
        EORS     R0,R0,#0x80000000
        LDR.N    R1,??Kalman_Filter_0+0x14
        STR      R0,[R1, #+4]
//   27 	Pdot[2]=- P[1][1];
        LDR.N    R0,??Kalman_Filter_0+0x10
        LDR      R0,[R0, #+12]
        EORS     R0,R0,#0x80000000
        LDR.N    R1,??Kalman_Filter_0+0x14
        STR      R0,[R1, #+8]
//   28 	Pdot[3]=Q_gyro;
        LDR.N    R0,??Kalman_Filter_0+0x18
        LDR      R0,[R0, #+0]
        LDR.N    R1,??Kalman_Filter_0+0x14
        STR      R0,[R1, #+12]
//   29 	
//   30 	P[0][0] += Pdot[0] * dt;// Pk- 先验估计误差协方差微分的积分 = 先验估计误差协方差
        LDR.N    R0,??Kalman_Filter_0+0x14
        LDR      R1,[R0, #+0]
        LDR.N    R0,??Kalman_Filter_0+0x4
        LDR      R0,[R0, #+0]
        BL       __aeabi_fmul
        LDR.N    R1,??Kalman_Filter_0+0x10
        LDR      R1,[R1, #+0]
        BL       __aeabi_fadd
        LDR.N    R1,??Kalman_Filter_0+0x10
        STR      R0,[R1, #+0]
//   31 	P[0][1] += Pdot[1] * dt;
        LDR.N    R0,??Kalman_Filter_0+0x14
        LDR      R1,[R0, #+4]
        LDR.N    R0,??Kalman_Filter_0+0x4
        LDR      R0,[R0, #+0]
        BL       __aeabi_fmul
        LDR.N    R1,??Kalman_Filter_0+0x10
        LDR      R1,[R1, #+4]
        BL       __aeabi_fadd
        LDR.N    R1,??Kalman_Filter_0+0x10
        STR      R0,[R1, #+4]
//   32 	P[1][0] += Pdot[2] * dt;
        LDR.N    R0,??Kalman_Filter_0+0x14
        LDR      R1,[R0, #+8]
        LDR.N    R0,??Kalman_Filter_0+0x4
        LDR      R0,[R0, #+0]
        BL       __aeabi_fmul
        LDR.N    R1,??Kalman_Filter_0+0x10
        LDR      R1,[R1, #+8]
        BL       __aeabi_fadd
        LDR.N    R1,??Kalman_Filter_0+0x10
        STR      R0,[R1, #+8]
//   33 	P[1][1] += Pdot[3] * dt;
        LDR.N    R0,??Kalman_Filter_0+0x14
        LDR      R1,[R0, #+12]
        LDR.N    R0,??Kalman_Filter_0+0x4
        LDR      R0,[R0, #+0]
        BL       __aeabi_fmul
        LDR.N    R1,??Kalman_Filter_0+0x10
        LDR      R1,[R1, #+12]
        BL       __aeabi_fadd
        LDR.N    R1,??Kalman_Filter_0+0x10
        STR      R0,[R1, #+12]
//   34 	
//   35 	
//   36 	angle_err = angle_m - angle;//zk-先验估计
        MOVS     R0,R4
        LDR.N    R1,??Kalman_Filter_0+0x8
        LDR      R1,[R1, #+0]
        BL       __aeabi_fsub
        LDR.N    R1,??Kalman_Filter_0+0x1C
        STR      R0,[R1, #+0]
//   37 	
//   38 	
//   39 	PCt_0 = C_0 * P[0][0];
        LDR.N    R0,??Kalman_Filter_0+0x20
        LDRB     R0,[R0, #+0]
        BL       __aeabi_ui2f
        LDR.N    R1,??Kalman_Filter_0+0x10
        LDR      R1,[R1, #+0]
        BL       __aeabi_fmul
        LDR.N    R1,??Kalman_Filter_0+0x24
        STR      R0,[R1, #+0]
//   40 	PCt_1 = C_0 * P[1][0];
        LDR.N    R0,??Kalman_Filter_0+0x20
        LDRB     R0,[R0, #+0]
        BL       __aeabi_ui2f
        LDR.N    R1,??Kalman_Filter_0+0x10
        LDR      R1,[R1, #+8]
        BL       __aeabi_fmul
        LDR.N    R1,??Kalman_Filter_0+0x28
        STR      R0,[R1, #+0]
//   41 	
//   42 	E = R_angle + C_0 * PCt_0;
        LDR.N    R0,??Kalman_Filter_0+0x20
        LDRB     R0,[R0, #+0]
        BL       __aeabi_ui2f
        LDR.N    R1,??Kalman_Filter_0+0x24
        LDR      R1,[R1, #+0]
        BL       __aeabi_fmul
        LDR.N    R1,??Kalman_Filter_0+0x2C
        LDR      R1,[R1, #+0]
        BL       __aeabi_fadd
        LDR.N    R1,??Kalman_Filter_0+0x30
        STR      R0,[R1, #+0]
//   43 	
//   44 	K_0 = PCt_0 / E;//Kk
        LDR.N    R0,??Kalman_Filter_0+0x24
        LDR      R0,[R0, #+0]
        LDR.N    R1,??Kalman_Filter_0+0x30
        LDR      R1,[R1, #+0]
        BL       __aeabi_fdiv
        LDR.N    R1,??Kalman_Filter_0+0x34
        STR      R0,[R1, #+0]
//   45 	K_1 = PCt_1 / E;
        LDR.N    R0,??Kalman_Filter_0+0x28
        LDR      R0,[R0, #+0]
        LDR.N    R1,??Kalman_Filter_0+0x30
        LDR      R1,[R1, #+0]
        BL       __aeabi_fdiv
        LDR.N    R1,??Kalman_Filter_0+0x38
        STR      R0,[R1, #+0]
//   46 	
//   47 	t_0 = PCt_0;
        LDR.N    R0,??Kalman_Filter_0+0x24
        LDR      R0,[R0, #+0]
        LDR.N    R1,??Kalman_Filter_0+0x3C
        STR      R0,[R1, #+0]
//   48 	t_1 = C_0 * P[0][1];
        LDR.N    R0,??Kalman_Filter_0+0x20
        LDRB     R0,[R0, #+0]
        BL       __aeabi_ui2f
        LDR.N    R1,??Kalman_Filter_0+0x10
        LDR      R1,[R1, #+4]
        BL       __aeabi_fmul
        LDR.N    R1,??Kalman_Filter_0+0x40
        STR      R0,[R1, #+0]
//   49 
//   50 	P[0][0] -= K_0 * t_0;//后验估计误差协方差
        LDR.N    R0,??Kalman_Filter_0+0x34
        LDR      R1,[R0, #+0]
        LDR.N    R0,??Kalman_Filter_0+0x3C
        LDR      R0,[R0, #+0]
        BL       __aeabi_fmul
        MOVS     R1,R0
        LDR.N    R0,??Kalman_Filter_0+0x10
        LDR      R0,[R0, #+0]
        BL       __aeabi_fsub
        LDR.N    R1,??Kalman_Filter_0+0x10
        STR      R0,[R1, #+0]
//   51 	P[0][1] -= K_0 * t_1;
        LDR.N    R0,??Kalman_Filter_0+0x34
        LDR      R1,[R0, #+0]
        LDR.N    R0,??Kalman_Filter_0+0x40
        LDR      R0,[R0, #+0]
        BL       __aeabi_fmul
        MOVS     R1,R0
        LDR.N    R0,??Kalman_Filter_0+0x10
        LDR      R0,[R0, #+4]
        BL       __aeabi_fsub
        LDR.N    R1,??Kalman_Filter_0+0x10
        STR      R0,[R1, #+4]
//   52 	P[1][0] -= K_1 * t_0;
        LDR.N    R0,??Kalman_Filter_0+0x38
        LDR      R1,[R0, #+0]
        LDR.N    R0,??Kalman_Filter_0+0x3C
        LDR      R0,[R0, #+0]
        BL       __aeabi_fmul
        MOVS     R1,R0
        LDR.N    R0,??Kalman_Filter_0+0x10
        LDR      R0,[R0, #+8]
        BL       __aeabi_fsub
        LDR.N    R1,??Kalman_Filter_0+0x10
        STR      R0,[R1, #+8]
//   53 	P[1][1] -= K_1 * t_1;
        LDR.N    R0,??Kalman_Filter_0+0x38
        LDR      R1,[R0, #+0]
        LDR.N    R0,??Kalman_Filter_0+0x40
        LDR      R0,[R0, #+0]
        BL       __aeabi_fmul
        MOVS     R1,R0
        LDR.N    R0,??Kalman_Filter_0+0x10
        LDR      R0,[R0, #+12]
        BL       __aeabi_fsub
        LDR.N    R1,??Kalman_Filter_0+0x10
        STR      R0,[R1, #+12]
//   54 	
//   55 	
//   56 	angle	+= K_0 * angle_err;//后验估计
        LDR.N    R0,??Kalman_Filter_0+0x34
        LDR      R1,[R0, #+0]
        LDR.N    R0,??Kalman_Filter_0+0x1C
        LDR      R0,[R0, #+0]
        BL       __aeabi_fmul
        LDR.N    R1,??Kalman_Filter_0+0x8
        LDR      R1,[R1, #+0]
        BL       __aeabi_fadd
        LDR.N    R1,??Kalman_Filter_0+0x8
        STR      R0,[R1, #+0]
//   57 	q_bias	+= K_1 * angle_err;//后验估计
        LDR.N    R0,??Kalman_Filter_0+0x38
        LDR      R1,[R0, #+0]
        LDR.N    R0,??Kalman_Filter_0+0x1C
        LDR      R0,[R0, #+0]
        BL       __aeabi_fmul
        LDR.N    R1,??Kalman_Filter_0
        LDR      R1,[R1, #+0]
        BL       __aeabi_fadd
        LDR.N    R1,??Kalman_Filter_0
        STR      R0,[R1, #+0]
//   58 	angle_dot = gyro_m-q_bias;//输出值（后验估计）的微分 = 角速度
        MOVS     R0,R5
        LDR.N    R1,??Kalman_Filter_0
        LDR      R1,[R1, #+0]
        BL       __aeabi_fsub
        LDR.N    R1,??Kalman_Filter_0+0x44
        STR      R0,[R1, #+0]
//   59 
//   60 }
        POP      {R0,R4,R5,PC}    ;; return
        Nop      
        DATA
??Kalman_Filter_0:
        DC32     q_bias
        DC32     dt
        DC32     angle
        DC32     Q_angle
        DC32     P
        DC32     Pdot
        DC32     Q_gyro
        DC32     angle_err
        DC32     C_0
        DC32     PCt_0
        DC32     PCt_1
        DC32     R_angle
        DC32     E
        DC32     K_0
        DC32     K_1
        DC32     t_0
        DC32     t_1
        DC32     angle_dot

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
//  60 bytes in section .bss
//  32 bytes in section .data
//   1 byte  in section .rodata
// 572 bytes in section .text
// 
// 572 bytes of CODE  memory
//   1 byte  of CONST memory
//  92 bytes of DATA  memory
//
//Errors: none
//Warnings: none
