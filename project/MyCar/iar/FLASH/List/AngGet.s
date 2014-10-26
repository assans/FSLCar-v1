///////////////////////////////////////////////////////////////////////////////
//
// IAR ANSI C/C++ Compiler V7.30.1.7746/W32 for ARM       26/Oct/2014  17:10:50
// Copyright 1999-2014 IAR Systems AB.
//
//    Cpu mode     =  thumb
//    Endian       =  little
//    Source file  =  H:\Freescale Code\FSLCar v1\project\MyCar\app\AngGet.c
//    Command line =  
//        "H:\Freescale Code\FSLCar v1\project\MyCar\app\AngGet.c" -D LPLD_K60
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
//        H:\Freescale Code\FSLCar v1\project\MyCar\iar\FLASH\List\AngGet.s
//
///////////////////////////////////////////////////////////////////////////////

        #define SHT_PROGBITS 0x1

        EXTERN LPLD_ADC_Get
        EXTERN __aeabi_d2f
        EXTERN __aeabi_dmul
        EXTERN __aeabi_fmul
        EXTERN __aeabi_i2d
        EXTERN __aeabi_i2f
        EXTERN complement_filter
        EXTERN x_f

        PUBLIC AngleCalculate
        PUBLIC AngleGet
        PUBLIC Angle_AD
        PUBLIC Float2Byte
        PUBLIC GravityAngle
        PUBLIC GyroscopeAngleSpeed

// H:\Freescale Code\FSLCar v1\project\MyCar\app\AngGet.c
//    1 #include "AngGet.h"
//    2 #include "common.h"
//    3 #include "Kalman.h"
//    4 #include "complement.h"
//    5 #define GRAVITY_OFFSET     2130
//    6 #define VOLTAGE_GRAVITY   Angle_AD[0]  //加速度x
//    7 #define VOLTAGE_GYRO      Angle_AD[1]  //陀螺仪
//    8 #define CAR_ANGLE_RANGE	   180     //车辆角度范围
//    9 #define GRAVITY_MAX        3370//重力最大值
//   10 #define GRAVITY_MIN        963//重力最小值
//   11 #define GRAVITY_ANGLE_RATIO	((float)CAR_ANGLE_RANGE / (float)((GRAVITY_MAX - GRAVITY_MIN)) )  //这一行需要优化
//   12 #define GYROSCOPE_OFFSET 1606
//   13 #define GYROSCOPE_ANGLE_RATIO   0.004// (3300/4096)/(0.67*5.1)*(3.14/180) =
//   14 
//   15 //extern int GyroZero;
//   16 //extern int GravityZero;
//   17 extern float CarAngle,CarAngSpeed,x_f;
//   18 extern float angle_com,angle_dot_com;

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
//   19 int Angle_AD[2]={0,0};
Angle_AD:
        DS8 8

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
//   20 float GravityAngle,GyroscopeAngleSpeed;
GravityAngle:
        DS8 4

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
GyroscopeAngleSpeed:
        DS8 4
//   21 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   22 void AngleCalculate(void)
//   23 {
AngleCalculate:
        PUSH     {R7,LR}
//   24 	GravityAngle = ((VOLTAGE_GRAVITY - GRAVITY_OFFSET) * GRAVITY_ANGLE_RATIO);
        LDR.N    R0,??DataTable1
        LDR      R0,[R0, #+0]
        SUBW     R0,R0,#+2130
        BL       __aeabi_i2f
        LDR.N    R1,??DataTable1_1  ;; 0x3d99273f
        BL       __aeabi_fmul
        LDR.N    R1,??DataTable1_2
        STR      R0,[R1, #+0]
//   25 	GyroscopeAngleSpeed = ((VOLTAGE_GYRO - GYROSCOPE_OFFSET) * GYROSCOPE_ANGLE_RATIO);
        LDR.N    R0,??DataTable1
        LDR      R0,[R0, #+4]
        SUBW     R0,R0,#+1606
        BL       __aeabi_i2d
        LDR.N    R2,??DataTable1_3  ;; 0xd2f1a9fc
        LDR.N    R3,??DataTable1_4  ;; 0x3f70624d
        BL       __aeabi_dmul
        BL       __aeabi_d2f
        LDR.N    R1,??DataTable1_5
        STR      R0,[R1, #+0]
//   26 
//   27 }
        POP      {R0,PC}          ;; return

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   28 void AngleGet(void)
//   29 {
AngleGet:
        PUSH     {R7,LR}
//   30 	Angle_AD[0]=LPLD_ADC_Get(ADC1,AD10); //采集x轴加速度
        MOVS     R1,#+10
        LDR.N    R0,??DataTable1_6  ;; 0x400bb000
        BL       LPLD_ADC_Get
        LDR.N    R1,??DataTable1
        STR      R0,[R1, #+0]
//   31 	Angle_AD[1]=LPLD_ADC_Get(ADC1,AD14); //采集陀螺仪角速度
        MOVS     R1,#+14
        LDR.N    R0,??DataTable1_6  ;; 0x400bb000
        BL       LPLD_ADC_Get
        LDR.N    R1,??DataTable1
        STR      R0,[R1, #+4]
//   32 	AngleCalculate();
        BL       AngleCalculate
//   33 	//Kalman_Filter(GravityAngle,GyroscopeAngleSpeed);
//   34 
//   35 //	CarAngSpeed=angle_dot;
//   36 //	CarAngle=angle;
//   37 	complement_filter(GravityAngle,GyroscopeAngleSpeed);
        LDR.N    R0,??DataTable1_5
        LDR      R1,[R0, #+0]
        LDR.N    R0,??DataTable1_2
        LDR      R0,[R0, #+0]
        BL       complement_filter
//   38 	x_f=GravityAngle;
        LDR.N    R0,??DataTable1_2
        LDR      R0,[R0, #+0]
        LDR.N    R1,??DataTable1_7
        STR      R0,[R1, #+0]
//   39 
//   40 }
        POP      {R0,PC}          ;; return

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable1:
        DC32     Angle_AD

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable1_1:
        DC32     0x3d99273f

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable1_2:
        DC32     GravityAngle

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable1_3:
        DC32     0xd2f1a9fc

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable1_4:
        DC32     0x3f70624d

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable1_5:
        DC32     GyroscopeAngleSpeed

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable1_6:
        DC32     0x400bb000

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable1_7:
        DC32     x_f
//   41 
//   42 //int GyroScopeGetZero(void)
//   43 //{
//   44 //	int temp;
//   45 //	temp=Angle_AD[1]=LPLD_ADC_Get(ADC1,AD14);
//   46 //	return temp;
//   47 //}
//   48 //int GravityGetZero(void)
//   49 //{
//   50 //	int temp;
//   51 //	temp=Angle_AD[0]=LPLD_ADC_Get(ADC1,AD12);
//   52 //	return temp;
//   53 //}
//   54 
//   55 
//   56 //函数说明：将单精度浮点数据转成4字节数据并存入指定地址
//   57 //附加说明：用户无需直接操作此函数
//   58 //target:目标单精度数据
//   59 //buf:待写入数组
//   60 //beg:指定从数组第几个元素开始写入
//   61 //函数无返回

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   62 void Float2Byte(float *target,unsigned char *buf,unsigned char beg)
//   63 {
Float2Byte:
        PUSH     {R4}
//   64     unsigned char *point;
//   65     point = (unsigned char*)target;	  //得到float的地址
//   66     buf[beg]   = point[0];
        LDRB     R3,[R0, #+0]
        UXTB     R2,R2            ;; ZeroExt  R2,R2,#+24,#+24
        STRB     R3,[R2, R1]
//   67     buf[beg+1] = point[1];
        LDRB     R3,[R0, #+1]
        UXTB     R2,R2            ;; ZeroExt  R2,R2,#+24,#+24
        ADDS     R4,R2,R1
        STRB     R3,[R4, #+1]
//   68     buf[beg+2] = point[2];
        LDRB     R3,[R0, #+2]
        UXTB     R2,R2            ;; ZeroExt  R2,R2,#+24,#+24
        ADDS     R4,R2,R1
        STRB     R3,[R4, #+2]
//   69     buf[beg+3] = point[3];
        LDRB     R0,[R0, #+3]
        UXTB     R2,R2            ;; ZeroExt  R2,R2,#+24,#+24
        ADDS     R1,R2,R1
        STRB     R0,[R1, #+3]
//   70 }
        POP      {R4}
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
//  16 bytes in section .bss
// 174 bytes in section .text
// 
// 174 bytes of CODE memory
//  16 bytes of DATA memory
//
//Errors: none
//Warnings: none
