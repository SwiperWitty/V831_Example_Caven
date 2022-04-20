#include "dac.h"

void DACx_Init_Caven(int DAC_X)
{
	DAC_InitTypeDef  DAC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);

	DAC_InitStructure.DAC_Trigger = DAC_Trigger_None;
	DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;
	DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bit0;
	DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Disable;
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	if(DAC_X == DAC_1)
	{
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		DAC_Init(DAC_Channel_1, &DAC_InitStructure);
		DAC_Cmd(DAC_Channel_1, ENABLE);
	}
	else if(DAC_X == DAC_2)
	{
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		DAC_Init(DAC_Channel_2, &DAC_InitStructure);
		DAC_Cmd(DAC_Channel_2, ENABLE);
	}

}

//���� ͨ��X �����ѹ
float DACx_Set_Vol(int DAC_X,float vol)
{
	float temp = vol;
	if(temp > 3.3 || temp < 0) vol = 0;
	temp = temp*4096/3.3;
	if(DAC_X == DAC_1)
	{
		DAC_SetChannel1Data(DAC_Align_12b_R,temp);//12λ�Ҷ������ݸ�ʽ����DACֵ
	}
	else if(DAC_X == DAC_2)
	{
		DAC_SetChannel2Data(DAC_Align_12b_R,temp);//12λ�Ҷ������ݸ�ʽ����DACֵ
	}
	else return 0;
	return vol;
}
