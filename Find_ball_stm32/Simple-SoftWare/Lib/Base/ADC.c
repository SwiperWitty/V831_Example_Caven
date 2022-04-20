#include "adc.h"
#include "sys_time.h"

void ADCx_Init_Caven(char ADC_x)
{
	GPIO_InitTypeDef   GPIO_InitStruct;
	ADC_InitTypeDef  ADC_InitStructure;
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //����ADC��Ƶ����6 72M/6=12,ADC���ʱ�䲻�ܳ���14M

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);		//����ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);	//GPIOʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);		//ADC ʱ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);			/* �����ж����ȼ�����(������ռ���ȼ��������ȼ��ķ���)���ں�����misc.c */
	
//	ADC_DeInit(ADC1);  //������ ADC1 ��ȫ���Ĵ�������Ϊȱʡֵ
	if(ADC_x == ADC_1)
	{
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;
		GPIO_Init(GPIOA,&GPIO_InitStruct);
	}
	else if(ADC_x == ADC_2)
	{
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;
		GPIO_Init(GPIOA,&GPIO_InitStruct);
	}
	else if(ADC_x == MCU_Temp) ADC_TempSensorVrefintCmd(ENABLE);
	else return;
	
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;		//ģ��ת�������ڵ�ͨ��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;	//ģ��ת�������ڵ���ת��ģʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//ת��������������ⲿ��������
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC�����Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel = 1;					//˳����й���ת����ADCͨ������Ŀ
	ADC_Init(ADC1, &ADC_InitStructure);						//����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���   
	
	ADC_Cmd(ADC1, ENABLE);	//ʹ��ָ����ADC1
	ADC_ResetCalibration(ADC1);	//ʹ�ܸ�λУ׼
	Delay_ms(20);
	while(ADC_GetResetCalibrationStatus(ADC1));	//�ȴ���λУ׼����
	ADC_StartCalibration(ADC1);	 //����ADУ׼
	while(ADC_GetCalibrationStatus(ADC1));	 //�ȴ�У׼����
 
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ָ����ADC1�����ת����������
}

float ADCx_Read_Vol (char ADC_x)
{
	float vol = 0;
	ADC_RegularChannelConfig(ADC1,ADC_x,1,ADC_De_Time);
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);			//ʹ��ָ����ADC1�����ת����������
	Delay_ms(1);
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));	//�ȴ�ת������
	ADC_ClearFlag(ADC1,ADC_FLAG_EOC);
	vol = ADC1->DR;									//��ȡADC1ͨ��
	vol = (vol/4096)*3.3;
	return vol;
}

float Read_MCU_Temp (void)
{
	float temperate;
	temperate = ADCx_Read_Vol (MCU_Temp);	//��ȡͨ��16
	temperate =(1.43 - temperate)/0.43+25;	//ת��Ϊ�¶�ֵ
	if(temperate<0)
	{
		temperate=-temperate;
	}
	return temperate;
}

