#ifndef _UART_H_
#define _UART_H_

#include "stm32f10x_rcc.h"

#define UART_1 1
#define UART_2 2
#define UART_3 3

struct _CV_UART
{
	char UART_x_Array[6][24]; //å„ä¸²å£çš„æ•°æ®
	char Read_Flag[6];		 //å„ä¸²å£çš„è¯»å–ç»“æŸä½
	char Rxd_Num[6];		 //å„ä¸²å£æ¥æ”¶æ•°é‡
};


void UART_Init (char Channel,uint32_t Baud);
void UART_Send_String(char Channel,char *String);				//²»ĞèÒªÖªµÀ³¤¶È
void UART_Send_Data(char Channel,char *Data,u8 Length);			//ĞèÒªÖªµÀ³¤¶È

#endif
