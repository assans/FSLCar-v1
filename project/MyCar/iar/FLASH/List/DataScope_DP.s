///////////////////////////////////////////////////////////////////////////////
//
// IAR ANSI C/C++ Compiler V7.30.1.7746/W32 for ARM       25/Oct/2014  14:33:15
// Copyright 1999-2014 IAR Systems AB.
//
//    Cpu mode     =  thumb
//    Endian       =  little
//    Source file  =  
//        H:\Freescale Code\FSLCar v1\project\MyCar\app\DataScope_DP.C
//    Command line =  
//        "H:\Freescale Code\FSLCar v1\project\MyCar\app\DataScope_DP.C" -D
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
//        H:\Freescale Code\FSLCar
//        v1\project\MyCar\iar\FLASH\List\DataScope_DP.s
//
///////////////////////////////////////////////////////////////////////////////

        #define SHT_PROGBITS 0x1

        PUBLIC DataScope_Data_Generate
        PUBLIC DataScope_Get_Channel_Data
        PUBLIC DataScope_OutPut_Buffer
        PUBLIC Float2Byte

// H:\Freescale Code\FSLCar v1\project\MyCar\app\DataScope_DP.C
//    1  
//    2 #include "DataScope_DP.h"
//    3  

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
//    4 unsigned char DataScope_OutPut_Buffer[42] = {0};	   //串口发送缓冲区
DataScope_OutPut_Buffer:
        DS8 44
//    5 
//    6 
//    7 //函数说明：将单精度浮点数据转成4字节数据并存入指定地址 
//    8 //附加说明：用户无需直接操作此函数 
//    9 //target:目标单精度数据
//   10 //buf:待写入数组
//   11 //beg:指定从数组第几个元素开始写入
//   12 //函数无返回 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   13 void Float2Byte(float *target,unsigned char *buf,unsigned char beg)
//   14 {
Float2Byte:
        PUSH     {R4}
//   15     unsigned char *point;
//   16     point = (unsigned char*)target;	  //得到float的地址
//   17     buf[beg]   = point[0];
        LDRB     R3,[R0, #+0]
        UXTB     R2,R2            ;; ZeroExt  R2,R2,#+24,#+24
        STRB     R3,[R2, R1]
//   18     buf[beg+1] = point[1];
        LDRB     R3,[R0, #+1]
        UXTB     R2,R2            ;; ZeroExt  R2,R2,#+24,#+24
        ADDS     R4,R2,R1
        STRB     R3,[R4, #+1]
//   19     buf[beg+2] = point[2];
        LDRB     R3,[R0, #+2]
        UXTB     R2,R2            ;; ZeroExt  R2,R2,#+24,#+24
        ADDS     R4,R2,R1
        STRB     R3,[R4, #+2]
//   20     buf[beg+3] = point[3];
        LDRB     R0,[R0, #+3]
        UXTB     R2,R2            ;; ZeroExt  R2,R2,#+24,#+24
        ADDS     R1,R2,R1
        STRB     R0,[R1, #+3]
//   21 }
        POP      {R4}
        BX       LR               ;; return
//   22  
//   23  
//   24 //函数说明：将待发送通道的单精度浮点数据写入发送缓冲区
//   25 //Data：通道数据
//   26 //Channel：选择通道（1-10）
//   27 //函数无返回 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   28 void DataScope_Get_Channel_Data(float Data,unsigned char Channel)
//   29 {
DataScope_Get_Channel_Data:
        PUSH     {R0,LR}
//   30 	if ( (Channel > 10) || (Channel == 0) ) return;  //通道个数大于10或等于0，直接跳出，不执行函数
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        CMP      R1,#+11
        BGE.N    ??DataScope_Get_Channel_Data_0
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        CMP      R1,#+0
        BNE.N    ??DataScope_Get_Channel_Data_1
??DataScope_Get_Channel_Data_0:
        B.N      ??DataScope_Get_Channel_Data_2
//   31   else
//   32   {
//   33      switch (Channel)
??DataScope_Get_Channel_Data_1:
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        CMP      R1,#+1
        BEQ.N    ??DataScope_Get_Channel_Data_3
        BCC.N    ??DataScope_Get_Channel_Data_4
        CMP      R1,#+3
        BEQ.N    ??DataScope_Get_Channel_Data_5
        BCC.N    ??DataScope_Get_Channel_Data_6
        CMP      R1,#+5
        BEQ.N    ??DataScope_Get_Channel_Data_7
        BCC.N    ??DataScope_Get_Channel_Data_8
        CMP      R1,#+7
        BEQ.N    ??DataScope_Get_Channel_Data_9
        BCC.N    ??DataScope_Get_Channel_Data_10
        CMP      R1,#+9
        BEQ.N    ??DataScope_Get_Channel_Data_11
        BCC.N    ??DataScope_Get_Channel_Data_12
        CMP      R1,#+10
        BEQ.N    ??DataScope_Get_Channel_Data_13
        B.N      ??DataScope_Get_Channel_Data_4
//   34 		{
//   35       case 1:  Float2Byte(&Data,DataScope_OutPut_Buffer,1); break;
??DataScope_Get_Channel_Data_3:
        MOVS     R2,#+1
        LDR.N    R1,??DataTable1
        ADD      R0,SP,#+0
        BL       Float2Byte
        B.N      ??DataScope_Get_Channel_Data_4
//   36       case 2:  Float2Byte(&Data,DataScope_OutPut_Buffer,5); break;
??DataScope_Get_Channel_Data_6:
        MOVS     R2,#+5
        LDR.N    R1,??DataTable1
        ADD      R0,SP,#+0
        BL       Float2Byte
        B.N      ??DataScope_Get_Channel_Data_4
//   37 		  case 3:  Float2Byte(&Data,DataScope_OutPut_Buffer,9); break;
??DataScope_Get_Channel_Data_5:
        MOVS     R2,#+9
        LDR.N    R1,??DataTable1
        ADD      R0,SP,#+0
        BL       Float2Byte
        B.N      ??DataScope_Get_Channel_Data_4
//   38 		  case 4:  Float2Byte(&Data,DataScope_OutPut_Buffer,13); break;
??DataScope_Get_Channel_Data_8:
        MOVS     R2,#+13
        LDR.N    R1,??DataTable1
        ADD      R0,SP,#+0
        BL       Float2Byte
        B.N      ??DataScope_Get_Channel_Data_4
//   39 		  case 5:  Float2Byte(&Data,DataScope_OutPut_Buffer,17); break;
??DataScope_Get_Channel_Data_7:
        MOVS     R2,#+17
        LDR.N    R1,??DataTable1
        ADD      R0,SP,#+0
        BL       Float2Byte
        B.N      ??DataScope_Get_Channel_Data_4
//   40 		  case 6:  Float2Byte(&Data,DataScope_OutPut_Buffer,21); break;
??DataScope_Get_Channel_Data_10:
        MOVS     R2,#+21
        LDR.N    R1,??DataTable1
        ADD      R0,SP,#+0
        BL       Float2Byte
        B.N      ??DataScope_Get_Channel_Data_4
//   41 		  case 7:  Float2Byte(&Data,DataScope_OutPut_Buffer,25); break;
??DataScope_Get_Channel_Data_9:
        MOVS     R2,#+25
        LDR.N    R1,??DataTable1
        ADD      R0,SP,#+0
        BL       Float2Byte
        B.N      ??DataScope_Get_Channel_Data_4
//   42 		  case 8:  Float2Byte(&Data,DataScope_OutPut_Buffer,29); break;
??DataScope_Get_Channel_Data_12:
        MOVS     R2,#+29
        LDR.N    R1,??DataTable1
        ADD      R0,SP,#+0
        BL       Float2Byte
        B.N      ??DataScope_Get_Channel_Data_4
//   43 		  case 9:  Float2Byte(&Data,DataScope_OutPut_Buffer,33); break;
??DataScope_Get_Channel_Data_11:
        MOVS     R2,#+33
        LDR.N    R1,??DataTable1
        ADD      R0,SP,#+0
        BL       Float2Byte
        B.N      ??DataScope_Get_Channel_Data_4
//   44 		  case 10: Float2Byte(&Data,DataScope_OutPut_Buffer,37); break;
??DataScope_Get_Channel_Data_13:
        MOVS     R2,#+37
        LDR.N    R1,??DataTable1
        ADD      R0,SP,#+0
        BL       Float2Byte
//   45 		}
//   46   }	 
//   47 }
??DataScope_Get_Channel_Data_4:
??DataScope_Get_Channel_Data_2:
        POP      {R0,PC}          ;; return
//   48 
//   49 
//   50 //函数说明：生成 DataScopeV1.0 能正确识别的帧格式
//   51 //Channel_Number，需要发送的通道个数
//   52 //返回发送缓冲区数据个数
//   53 //返回0表示帧格式生成失败 

        SECTION `.text`:CODE:NOROOT(1)
        THUMB
//   54 unsigned char DataScope_Data_Generate(unsigned char Channel_Number)
//   55 {
//   56 	if ( (Channel_Number > 10) || (Channel_Number == 0) ) { return 0; }  //通道个数大于10或等于0，直接跳出，不执行函数
DataScope_Data_Generate:
        UXTB     R0,R0            ;; ZeroExt  R0,R0,#+24,#+24
        CMP      R0,#+11
        BGE.N    ??DataScope_Data_Generate_0
        UXTB     R0,R0            ;; ZeroExt  R0,R0,#+24,#+24
        CMP      R0,#+0
        BNE.N    ??DataScope_Data_Generate_1
??DataScope_Data_Generate_0:
        MOVS     R0,#+0
        B.N      ??DataScope_Data_Generate_2
//   57   else
//   58   {	
//   59 	 DataScope_OutPut_Buffer[0] = '$';  //帧头
??DataScope_Data_Generate_1:
        MOVS     R1,#+36
        LDR.N    R2,??DataTable1
        STRB     R1,[R2, #+0]
//   60 		
//   61 	 switch(Channel_Number)   
        UXTB     R0,R0            ;; ZeroExt  R0,R0,#+24,#+24
        CMP      R0,#+1
        BEQ.N    ??DataScope_Data_Generate_3
        BCC.N    ??DataScope_Data_Generate_4
        CMP      R0,#+3
        BEQ.N    ??DataScope_Data_Generate_5
        BCC.N    ??DataScope_Data_Generate_6
        CMP      R0,#+5
        BEQ.N    ??DataScope_Data_Generate_7
        BCC.N    ??DataScope_Data_Generate_8
        CMP      R0,#+7
        BEQ.N    ??DataScope_Data_Generate_9
        BCC.N    ??DataScope_Data_Generate_10
        CMP      R0,#+9
        BEQ.N    ??DataScope_Data_Generate_11
        BCC.N    ??DataScope_Data_Generate_12
        CMP      R0,#+10
        BEQ.N    ??DataScope_Data_Generate_13
        B.N      ??DataScope_Data_Generate_4
//   62    { 
//   63 		 case 1:   DataScope_OutPut_Buffer[5]  =  5; return  6; break;   
??DataScope_Data_Generate_3:
        MOVS     R0,#+5
        LDR.N    R1,??DataTable1
        STRB     R0,[R1, #+5]
        MOVS     R0,#+6
        B.N      ??DataScope_Data_Generate_2
//   64 		 case 2:   DataScope_OutPut_Buffer[9]  =  9; return 10; break;
??DataScope_Data_Generate_6:
        MOVS     R0,#+9
        LDR.N    R1,??DataTable1
        STRB     R0,[R1, #+9]
        MOVS     R0,#+10
        B.N      ??DataScope_Data_Generate_2
//   65 		 case 3:   DataScope_OutPut_Buffer[13] = 13; return 14; break;
??DataScope_Data_Generate_5:
        MOVS     R0,#+13
        LDR.N    R1,??DataTable1
        STRB     R0,[R1, #+13]
        MOVS     R0,#+14
        B.N      ??DataScope_Data_Generate_2
//   66 		 case 4:   DataScope_OutPut_Buffer[17] = 17; return 18; break;
??DataScope_Data_Generate_8:
        MOVS     R0,#+17
        LDR.N    R1,??DataTable1
        STRB     R0,[R1, #+17]
        MOVS     R0,#+18
        B.N      ??DataScope_Data_Generate_2
//   67 		 case 5:   DataScope_OutPut_Buffer[21] = 21; return 22; break; 
??DataScope_Data_Generate_7:
        MOVS     R0,#+21
        LDR.N    R1,??DataTable1
        STRB     R0,[R1, #+21]
        MOVS     R0,#+22
        B.N      ??DataScope_Data_Generate_2
//   68 		 case 6:   DataScope_OutPut_Buffer[25] = 25; return 26; break;
??DataScope_Data_Generate_10:
        MOVS     R0,#+25
        LDR.N    R1,??DataTable1
        STRB     R0,[R1, #+25]
        MOVS     R0,#+26
        B.N      ??DataScope_Data_Generate_2
//   69 		 case 7:   DataScope_OutPut_Buffer[29] = 29; return 30; break;
??DataScope_Data_Generate_9:
        MOVS     R0,#+29
        LDR.N    R1,??DataTable1
        STRB     R0,[R1, #+29]
        MOVS     R0,#+30
        B.N      ??DataScope_Data_Generate_2
//   70 		 case 8:   DataScope_OutPut_Buffer[33] = 33; return 34; break;
??DataScope_Data_Generate_12:
        MOVS     R0,#+33
        LDR.N    R1,??DataTable1
        STRB     R0,[R1, #+33]
        MOVS     R0,#+34
        B.N      ??DataScope_Data_Generate_2
//   71 		 case 9:   DataScope_OutPut_Buffer[37] = 37; return 38; break;
??DataScope_Data_Generate_11:
        MOVS     R0,#+37
        LDR.N    R1,??DataTable1
        STRB     R0,[R1, #+37]
        MOVS     R0,#+38
        B.N      ??DataScope_Data_Generate_2
//   72      case 10:  DataScope_OutPut_Buffer[41] = 41; return 42; break;
??DataScope_Data_Generate_13:
        MOVS     R0,#+41
        LDR.N    R1,??DataTable1
        STRB     R0,[R1, #+41]
        MOVS     R0,#+42
        B.N      ??DataScope_Data_Generate_2
//   73    }	 
//   74   }
//   75 	return 0;
??DataScope_Data_Generate_4:
        MOVS     R0,#+0
??DataScope_Data_Generate_2:
        BX       LR               ;; return
//   76 }

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable1:
        DC32     DataScope_OutPut_Buffer

        SECTION `.iar_vfe_header`:DATA:NOALLOC:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
        DC32 0

        END
//   77 
//   78 
//   79 
//   80 
//   81 
//   82 
//   83 
//   84 
//   85 
//   86 
//   87 
// 
//  44 bytes in section .bss
// 384 bytes in section .text
// 
// 384 bytes of CODE memory
//  44 bytes of DATA memory
//
//Errors: none
//Warnings: none
