#ifndef _SCHEDULER_H_
#define _SCHEDULER_H_
#include "stm32f10x.h"

typedef struct
{
	u8 check_flag;
	u8 err_flag;
	s16 cnt_1ms;
	s16 cnt_2ms;
	s16 cnt_5ms;
	s16 cnt_10ms;
	s16 cnt_20ms;
	s16 cnt_50ms;
	s16 cnt_100ms;
	u16 time;
}loop_t;

extern float test[5];

void Loop_check(void);

void Duty_Loop(void);

void Inner_Loop(float);

void Outer_Loop(float);


#endif

