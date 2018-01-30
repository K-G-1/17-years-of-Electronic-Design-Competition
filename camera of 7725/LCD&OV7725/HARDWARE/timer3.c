#include "timer3.h"
#include "oled.h"
#include "image.h"



void tim3_init(u16 arr,u16 psc)
{
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3|RCC_APB1Periph_TIM4,ENABLE);
	
	//timer3中断配置

	TIM_TimeBaseInitStruct.TIM_Period=arr;
	TIM_TimeBaseInitStruct.TIM_Prescaler=psc;
	TIM_TimeBaseInitStruct.TIM_ClockDivision= TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode= TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);
	
	TIM_TimeBaseInitStruct.TIM_Period=10000-1;
	TIM_TimeBaseInitStruct.TIM_Prescaler=8400-1;
	TIM_TimeBaseInitStruct.TIM_ClockDivision= TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode= TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStruct);
	
	//中断优先级配置
	NVIC_InitStruct.NVIC_IRQChannel=TIM3_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE ;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0x00;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=0x04;
	NVIC_Init(&NVIC_InitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel=TIM4_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE ;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0x00;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=0x03;
	NVIC_Init(&NVIC_InitStruct);
	
	//使能timer3中断
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	TIM_Cmd(TIM3, ENABLE);
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);
	TIM_Cmd(TIM4, ENABLE);
}

extern int f_count;
extern unsigned  char deal_buff[4][128];
void TIM3_IRQHandler(void)
{
	if( TIM_GetITStatus(TIM3 ,TIM_IT_Update)==SET)
	{
		
      TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
	  
	}
	
}

void TIM4_IRQHandler(void)
{
	if( TIM_GetITStatus(TIM4 ,TIM_IT_Update)==SET)
	{
		TIM_ClearITPendingBit(TIM4,TIM_IT_Update);

	}
	
}
