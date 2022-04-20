#ifndef _SYS_TIME_H__
#define _SYS_TIME_H__

#include "stm32f10x.h"

typedef struct
{
	char hour;
	char minutes;
	char second;
	u32 sys_time;
	u32 time_unm;
} SYS_Watch;

extern SYS_Watch Timewatch ;

void Sys_Watch (void);

void Delay_10us(int num);
void Delay_ms(int num);
void Delay_S(char num);

#endif
