#include "uart.h"

static int n;
struct _CV_UART CV_UART;


void UART_Init(char Channel, uint32_t Baud)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure; //
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 		//设置中断组，4位抢占优先级，4位响应优先级
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);	//AFIO复用功能模块时钟
	if (Channel == 1)
	{
		/*	Clock	*/
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  // GPIOB 服用 PB6 PB7
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); // USART1  (APB2)
		GPIO_PinRemapConfig(GPIO_Remap_USART1, ENABLE);
		USART_DeInit(USART1);

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; //TXD
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //
		GPIO_Init(GPIOB, &GPIO_InitStructure);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;	  //RXD
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //
		GPIO_Init(GPIOB, &GPIO_InitStructure);

		USART_InitStructure.USART_BaudRate = Baud;
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //
		USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;					//
		USART_InitStructure.USART_Parity = USART_Parity_No;								//
		USART_InitStructure.USART_StopBits = USART_StopBits_1;							//
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;						//
		USART_Init(USART1, &USART_InitStructure);
		USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); //
		USART_Cmd(USART1, ENABLE);					   //

		NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; //抢占优先级
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		  //响应优先级
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
	}
	else if (Channel == 2)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE );
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE );

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //USART2 TX；
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //复用推挽输出；
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure); //端口A；
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3; //USART2 RX；
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //浮空输入；
		GPIO_Init(GPIOA, &GPIO_InitStructure); //端口A；

		USART_InitStructure.USART_BaudRate = Baud; //波特率；
		USART_InitStructure.USART_WordLength = USART_WordLength_8b; //数据位8位；
		USART_InitStructure.USART_StopBits = USART_StopBits_1; //停止位1位；
		USART_InitStructure.USART_Parity = USART_Parity_No ; //无校验位；
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
		USART_Init(USART2, &USART_InitStructure);//配置串口参数；
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置中断组，4位抢占优先级，4位响应优先级；

		NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn; //中断号；
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //抢占优先级；
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; //响应优先级
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);

		USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
		USART_Cmd(USART2, ENABLE); //使能串口
		CV_UART.Read_Flag[2] = 0;
	}
	
	else if(Channel == 3)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
		GPIO_PinRemapConfig(GPIO_PartialRemap_USART3, ENABLE);		//串口3重映射，与串口4 IO一致（STM32F103RB版本只有串口3没有4）
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //USART3 TX；
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //复用推
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOC, &GPIO_InitStructure);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11; //USART3 RX；
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //浮空输入
		GPIO_Init(GPIOC, &GPIO_InitStructure);
		
		USART_InitStructure.USART_BaudRate = Baud; //波特率；
		USART_InitStructure.USART_WordLength = USART_WordLength_8b; //数据位8位；
		USART_InitStructure.USART_StopBits = USART_StopBits_1; //停止位1位；
		USART_InitStructure.USART_Parity = USART_Parity_No ; //无校验位；
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

		USART_Init(USART3, &USART_InitStructure);//配置串口参数
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置中断组，4位抢占优先级，4位响应优先级；
		NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn; //中断号；
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; //抢占优先级；
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2; //响应优先级；
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);

		USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
		USART_Cmd(USART3, ENABLE);
	}
}

void UART_Send_Data(char Channel,char *Data,u8 Length)
{
	n = 0;
	while(Length--)
	{
		switch (Channel)
		{
		case 1:
			while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
				;
			USART_SendData(USART1, *(Data + n));
			break;
		case 2:
			while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET)
				;
			USART_SendData(USART2, *(Data + n));
			break;
		case 3:
			while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET)
				;
			USART_SendData(USART3, *(Data + n));
			break;
		default:
			break;
		}
		n++;
	}
}

void UART_Send_String(char Channel,char *String)
{
	n = 0;
	while (30 - n)
	{
		switch (Channel)
		{
		case 1:
			while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
				;
			USART_SendData(USART1, *(String + n));
			break;
		case 2:
			while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET)
				;
			USART_SendData(USART2, *(String + n));
			break;
		case 3:
			while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET)
				;
			USART_SendData(USART3, *(String + n));
			break;
		default:
			break;
		}
		if (*(String + n) == '\0' || *(String + n) == 0)
			return;
		n++;
	}
}

void USART1_IRQHandler (void) //中断处理函数；
{
	char res;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
	{
		USART_ClearFlag(USART1, USART_IT_RXNE);
		if (CV_UART.Read_Flag[UART_1] == 0)
		{
			res = USART_ReceiveData(USART1); //接收数据
			CV_UART.UART_x_Array[UART_1][CV_UART.Rxd_Num[UART_1] ++] = res;
			if (res == '\n' || res == '}')
			{
				CV_UART.Read_Flag[1] = 1;
				CV_UART.Rxd_Num[1] = 0;
			}
		}
	}
}

void USART2_IRQHandler(void) //中断处理函数；
{
	char res;
	if(USART_GetITStatus(USART2, USART_IT_RXNE)) //判断是否发生中断；
	{
		USART_ClearFlag(USART2, USART_IT_RXNE); //清除标志位
		if(CV_UART.Read_Flag[2] == 0)
		{
			res = USART_ReceiveData(USART2); //接收数据
			CV_UART.UART_x_Array[2][CV_UART.Rxd_Num[2] ++] = res;
			if (res == '\0' || res == '}' || res == '\n')
			{
				CV_UART.Read_Flag[2] = 1;
				CV_UART.Rxd_Num[2] = 0;
			}
		}
	}
}

void USART3_IRQHandler(void) //中断处理函数
{
	u8 res;
	if(USART_GetITStatus(USART3, USART_IT_RXNE) == SET) //判断是否发生中断
	{
		USART_ClearFlag(USART3, USART_IT_RXNE); //清除标志位
		if(CV_UART.Read_Flag[3] == 0)
		{
			res = USART_ReceiveData(USART3); //接收数据
			CV_UART.UART_x_Array[3][CV_UART.Rxd_Num[3]++] = res;
			if (res == '\0' || res == '\n')
			{
				CV_UART.Read_Flag[3] = 1;
				CV_UART.Rxd_Num[UART_3] = 0;
			}
		}
	}
}
