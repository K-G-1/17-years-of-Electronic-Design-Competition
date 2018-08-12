#ifndef _TIME_H_
#define _TIME_H_

#include "stm32f10x.h"

void TIM_INIT(void);
void sys_time(void);

u16 Get_Time(u8,u16,u16);

u32 Get_Cycle_T(u8 );

void Cycle_Time_Init(void);

extern volatile uint32_t sysTickUptime;
extern int time_1h,time_1m,time_1s,time_1ms;

void Delay_us(uint32_t);
void Delay_ms(uint32_t);
void SysTick_Configuration(void);
uint32_t GetSysTime_us(void);

#define EnTIM5()  TIM_Cmd(TIM5,ENABLE)
#define unTIM5()  TIM_Cmd(TIM5,DISABLE)
#define EnTIM7()  TIM_Cmd(TIM7,ENABLE)
#define unTIM7()  TIM_Cmd(TIM7,DISABLE)
#define EnTIM2()  TIM_Cmd(TIM2,ENABLE)
#define EnTIM3()  TIM_Cmd(TIM3,ENABLE)
#define unTIM3()  TIM_Cmd(TIM3,DISABLE)
void Nvic_Init(void);
void TIM5_Init(u16 period_num);
void TIM7_init(void);
void TIM6_Int_Init(u16 arr,u16 psc);
void TIM6_Init(u16 period_num);
void Timerx_Init(u16 arr,u16 psc);
void Cycle_Time_Init(void);
u32 Get_Cycle_T(u8 );

void SysTick_Configuration(void);
uint32_t GetSysTime_us(void);
extern u16 x;
extern volatile uint32_t sysTickUptime;


#endif
