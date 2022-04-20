#ifndef _MOTOR_H_
#define _MOTOR_H_
/*
	V1.0				n多年前
	V1.1	(end)		2021.9.18
*/

#include "PWM.h"
#include "stdlib.h"

#define M1_N1 		GPIO_Pin_4
#define M1_N2		GPIO_Pin_5
#define M1_GPIO1	GPIOB
#define M1_GPIO2	GPIOB
#define M1_GPIO_TIM1	RCC_APB2Periph_GPIOB
#define M1_GPIO_TIM2	RCC_APB2Periph_GPIOB

#define M2_N1 		GPIO_Pin_12
#define M2_N2		GPIO_Pin_2
#define M2_GPIO1	GPIOC
#define M2_GPIO2	GPIOD
#define M2_GPIO_TIM1	RCC_APB2Periph_GPIOC
#define M2_GPIO_TIM2	RCC_APB2Periph_GPIOD

#define M3_N1 		GPIO_Pin_0						//Type 版本不用 M3,M4
#define M3_N2		GPIO_Pin_1
#define M3_GPIO1	GPIOC
#define M3_GPIO2	GPIOC
#define M3_GPIO_TIM1	RCC_APB2Periph_GPIOC
#define M3_GPIO_TIM2	RCC_APB2Periph_GPIOC


#define M4_N1 		GPIO_Pin_2
#define M4_N2		GPIO_Pin_3
#define M4_GPIO1	GPIOC
#define M4_GPIO2	GPIOC
#define M4_GPIO_TIM1	RCC_APB2Periph_GPIOC
#define M4_GPIO_TIM2	RCC_APB2Periph_GPIOC

#define Motor1 1
#define Motor2 2
#define Motor3 3
#define Motor4 4

#define	Arr_T8	1000
#define Por_T8	72

//	T = (arr * por) / 72MHz = 1MS

/*

		MotorX_Control(char MotorX, int Speed); 去除此函数方向传参，由Speed的 +/-来判别方向
										
											2021.12.05

*/

void MotorX_Init (char MotorX);
void MotorX_Control(char MotorX, int Speed);

#endif
