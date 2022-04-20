#ifndef _PWM_H_
#define _PWM_H_

#include "stm32f10x.h"

/*
	TIM4
	TIM8(高级)
	
	Period = (ARR + 1)*(PSC + 1)/CLK
	ARR   PSC 
	
							舵机 
	20ms pwm	1.5ms(0)	0.5ms(-90)	2.5ms(+90)	
	arr = 1999	psc = 719	CLK = 72MHz	Period = 0.02s
	
							电机
	1ms	arr = 1000	psc = 7	CLK = 72MHz	Period = 1ms
	
	GD和ST在模式上好像有差异，特别是PWM
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	这样才通用											--2021.11.21
*/

void TIM4_PWM_Init (u16 arr,u16 psc);
void TIM8_PWM_Init (u16 arr,u16 psc);

#endif
