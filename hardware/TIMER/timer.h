#ifndef TIMER_H_
#define TIMER_H_
#include "sys.h"
extern u8 Change_Flag;			//�л���ʶ
extern u8 times;
void TIM3_Init(u16 arr,u16 psc);		//��ʼ��TIM3��ʱ��
void TIM3_IRQHandler(void);					//��ʱ��3�жϺ���
void TIM4_Init(u16 arr,u16 psc);		//��ʼ��TIM4��ʱ��
void TIM4_IRQHandler(void);					//��ʱ��4�жϺ���
void TIM5_Init(u16 arr,u16 psc);		//��ʼ��TIM5��ʱ��
void TIM5_IRQHandler(void);					//��ʱ��5�жϺ���
#endif


