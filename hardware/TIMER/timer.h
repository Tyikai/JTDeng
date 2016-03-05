#ifndef TIMER_H_
#define TIMER_H_
#include "sys.h"
extern u8 Change_Flag;			//切换标识
extern u8 times;
void TIM3_Init(u16 arr,u16 psc);		//初始化TIM3定时器
void TIM3_IRQHandler(void);					//定时器3中断函数
void TIM4_Init(u16 arr,u16 psc);		//初始化TIM4定时器
void TIM4_IRQHandler(void);					//定时器4中断函数
void TIM5_Init(u16 arr,u16 psc);		//初始化TIM5定时器
void TIM5_IRQHandler(void);					//定时器5中断函数
#endif


