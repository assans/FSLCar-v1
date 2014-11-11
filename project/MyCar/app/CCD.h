#ifndef _CCD_H_
#define _CCD_H_
#include "common.h"

extern unsigned char ccd_array[128]; //外部调用的时候用
extern unsigned char TimerFlag20ms ;
extern unsigned int send_data;

void ccd_carry(unsigned char *carry);
void StartIntegration(void);
void ccd_exposure(void);
void CalculateIntegrationTime(void);
unsigned char PixelAverage(unsigned char len, unsigned char *data);
void SendImageData(unsigned char *ImageData);
void SendHex(unsigned char hex);

#endif
