#include "stm32f10x.h"
#include "sys_time.h"
#include "Data_Handle.h"
#include "stdlib.h"
#include "Steering_engine.h"
#include "lcd.h"
#include "string.h"
#include "uart.h"
#include "adc.h"

char Free_Array[30];

float far, temp, vol;

int clo = 0;
int CL, num;
float Space_x = 0 ,Space_y = -45;
extern struct _CV_UART CV_UART;
void Mian_Init(void);
int main(void)
{
	Mian_Init();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	while (1)
	{
		
		if (CV_UART.Read_Flag[2])
		{
			
			if (CV_UART.UART_x_Array[2][0] == '{')
			{
				float deviation = 0;
				
				deviation = Data_Chang_NUM (CV_UART.UART_x_Array[2],'>',sizeof(CV_UART.UART_x_Array[2]));
				int tem = (int)deviation;
				tem = abs(tem);
				if (Data_Judge("{V831:Space_x", CV_UART.UART_x_Array[2],sizeof("{V831:Space_y")))
				{
					
//					sprintf(Free_Array,"%.2f  ",deviation);
//					LCD_ShowString(5,3,Free_Array,CYAN,BLACK,24);//显示字符串
					if(tem > 50)
						Space_x -= (deviation * 0.05);
					else if(tem > 10)
						Space_x -= (deviation * 0.03);
					
//					sprintf(Free_Array,"x:%.2f \n",deviation);
//					UART_Send_String(UART_2, Free_Array);
				}
				else if (Data_Judge("{V831:Space_y", CV_UART.UART_x_Array[2],sizeof("{V831:Space_y")))
				{
//					sprintf(Free_Array,"%.2f  ",deviation);
//					LCD_ShowString(5,4,Free_Array,BLUE,BLACK,24);//显示字符串
					if(tem > 30)
						Space_y -= (deviation * 0.03);
					else if(tem > 10)
						Space_y -= (deviation * 0.01);
				}
			}
			else
				UART_Send_String(UART_2, "{error ! }\r\n");
			Data_Replace("123", CV_UART.UART_x_Array[2], 0, sizeof(CV_UART.UART_x_Array[2]));
			CV_UART.Read_Flag[2] = 0;
		}
		Data_Replace("123", Free_Array, 0, sizeof(Free_Array));
		
		if(Space_y > 5)	Space_y = 5;
		else if(Space_y < -50) Space_y = -50;
		if(Space_x > 90)	Space_x = 90;
		else if(Space_x < -90)	Space_x = -90;
		Steering_Engine_Angle(2,Space_y);
		Steering_Engine_Angle(4,Space_x);
		
		sprintf(Free_Array,"%.2f  ",Space_x);
		LCD_ShowString(9,7,Free_Array,BRED,BLACK,24);//显示字符串
		sprintf(Free_Array,"%.2f  ",Space_y+45);
		LCD_ShowString(9,8,Free_Array,GRED,BLACK,24);//显示字符串
	}
}

void Mian_Init(void)
{
	if (SysTick_Config(SystemCoreClock / 100000))
		while (1);
	LCD_Init();
	ADCx_Init_Caven(MCU_Temp);
	
	UART_Init(UART_2, 115200);
	UART_Send_String(UART_2, "{Caven:Ready !} \r\n");
	Init_Steering_Engine_T4();
	
	Steering_Engine_Angle(1,0);
	Steering_Engine_Angle(2,Space_y);		//y -45 -> 30
	Steering_Engine_Angle(3,0);
	Steering_Engine_Angle(4,Space_x);		//x	-90 -> 90
	
	LCD_ShowString(6,0,"Find ball ",RED,BLACK,24);//显示字符串
	sprintf(Free_Array,"X:        ->0 ");
	LCD_ShowString(2,3,Free_Array,CYAN,BLACK,24);//显示字符串
	sprintf(Free_Array,"Y:        ->0 ");
	LCD_ShowString(2,4,Free_Array,BLUE,BLACK,24);//显示字符串
	
	sprintf(Free_Array,"X-NOW: %.2f  ",Space_x);
	LCD_ShowString(2,7,Free_Array,BRED,BLACK,24);//显示字符串
	sprintf(Free_Array,"Y-NOW: %.2f  ",Space_y+25);
	LCD_ShowString(2,8,Free_Array,GRED,BLACK,24);//显示字符串
	
	Delay_S(1);

}
