#ifndef _ADC_H_
#define _ADC_H_

#include "stm32f10x.h"

/*
			ADC_1        PA4  			ADC1		ADC_Channel_4
			ADC_2        PA5  			ADC1		ADC_Channel_4
			

			Ñ­¼£²»ÒªÆôÓÃ ADC £¡
			Attention £ºUsing Tracing enable ADC
												--2021.12.04
*/

#define ADC_1			ADC_Channel_4
#define ADC_2			ADC_Channel_5
#define MCU_Temp		ADC_Channel_16
#define ADC_De_Time		ADC_SampleTime_239Cycles5

void ADCx_Init_Caven(char ADCx);
float ADCx_Read_Vol (char ADCx);
float Read_MCU_Temp (void);

#endif
