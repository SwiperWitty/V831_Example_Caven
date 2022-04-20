#ifndef _DAC_H_
#define _DAC_H_

#include "stm32f10x.h"

#define DAC_1			DAC_Channel_1
#define DAC_2			DAC_Channel_2



void DACx_Init_Caven(int DAC_X);
float DACx_Set_Vol(int DAC_X,float vol);


#endif
