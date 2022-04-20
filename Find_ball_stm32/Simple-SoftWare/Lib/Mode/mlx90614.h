#ifndef __MLX90614_H
#define __MLX90614_H

#include "stm32f10x.h"

#define SMBUS_PORT	GPIOB      //PB�˿�(�˿ں������������ſ��Զ���)
#define SMBUS_SCK		GPIO_Pin_10 //PB6��SCL
#define SMBUS_SDA		GPIO_Pin_11 //PB7��SDA2

#define RCC_APB2Periph_SMBUS_PORT		RCC_APB2Periph_GPIOB

void Mlx90614_Init(void);
float Mlx90614_ReadTemp(void); //��ȡ�¶�ֵ

#endif

