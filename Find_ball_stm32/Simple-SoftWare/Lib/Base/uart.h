#ifndef _UART_H_
#define _UART_H_

#include "stm32f10x_rcc.h"

#define UART_1 1
#define UART_2 2
#define UART_3 3

struct _CV_UART
{
	char UART_x_Array[6][24]; //各串口的数据
	char Read_Flag[6];		 //各串口的读取结束位
	char Rxd_Num[6];		 //各串口接收数量
};


void UART_Init (char Channel,uint32_t Baud);
void UART_Send_String(char Channel,char *String);				//����Ҫ֪������
void UART_Send_Data(char Channel,char *Data,u8 Length);			//��Ҫ֪������

#endif
