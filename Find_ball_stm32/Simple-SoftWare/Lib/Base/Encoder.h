#ifndef _ENCODER_H_
#define _ENCODER_H_

#define	TIM_1	1
#define	TIM_2	2

#define ENCODER_TIM_PERIOD (u16)(65535)   //���ɴ���65535 ��ΪF103�Ķ�ʱ����16λ�ġ�

void Encoder_Init(char TIM_X);

int Read_Encoder(char TIM_X);
	
#endif
