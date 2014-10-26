///////////////////////////////////////////////////////////////////////////////
//
// IAR ANSI C/C++ Compiler V7.30.1.7746/W32 for ARM       23/Oct/2014  18:15:47
// Copyright 1999-2014 IAR Systems AB.
//
//    Cpu mode     =  thumb
//    Endian       =  little
//    Source file  =  H:\Freescale Code\FSLCar v1\project\MyCar\app\MyCar.c
//    Command line =  
//        "H:\Freescale Code\FSLCar v1\project\MyCar\app\MyCar.c" -D LPLD_K60
//        -lCN "H:\Freescale Code\FSLCar v1\project\MyCar\iar\RAM\List\" -lB
//        "H:\Freescale Code\FSLCar v1\project\MyCar\iar\RAM\List\" -o
//        "H:\Freescale Code\FSLCar v1\project\MyCar\iar\RAM\Obj\" --no_cse
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
//        H:\Freescale Code\FSLCar v1\project\MyCar\iar\RAM\List\MyCar.s
//
///////////////////////////////////////////////////////////////////////////////

        #define SHT_PROGBITS 0x1

        PUBLIC main

// H:\Freescale Code\FSLCar v1\project\MyCar\app\MyCar.c
//    1 /**
//    2  * --------------����"��������K60�ײ��V3"�Ĺ��̣�MyCar��-----------------
//    3  * @file MyCar.c
//    4  * @version 0.0
//    5  * @date 2013-9-29
//    6  * @brief ���ڸù��̵�����
//    7  *
//    8  * ��Ȩ����:�����������µ��Ӽ������޹�˾
//    9  * http://www.lpld.cn
//   10  * mail:support@lpld.cn
//   11  * Ӳ��ƽ̨:  LPLD K60 Card / LPLD K60 Nano
//   12  *
//   13  * �����̻���"��������K60�ײ��V3"������
//   14  * ���п�Դ�������"lib"�ļ����£��û����ظ��ĸ�Ŀ¼�´��룬
//   15  * �����û������豣����"project"�ļ����£��Թ����������ļ�������
//   16  * �ײ��ʹ�÷���������ĵ��� 
//   17  *
//   18  */
//   19 #include "common.h"
//   20 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   21 void main (void)
//   22 {
//   23 
//   24   while(1)
main:
??main_0:
        B.N      ??main_0
//   25   {
//   26 
//   27   } 
//   28 }

        SECTION `.iar_vfe_header`:DATA:NOALLOC:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
        DC32 0

        SECTION __DLIB_PERTHREAD:DATA:REORDER:NOROOT(0)
        SECTION_TYPE SHT_PROGBITS, 0

        SECTION __DLIB_PERTHREAD_init:DATA:REORDER:NOROOT(0)
        SECTION_TYPE SHT_PROGBITS, 0

        END
//   29 
// 
// 2 bytes in section .text
// 
// 2 bytes of CODE memory
//
//Errors: none
//Warnings: none
