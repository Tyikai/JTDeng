#ifndef EXTI_H_
#define EXTI_H_
#include "sys.h"
extern u8 Run_Mode;							//�л�ģʽ��ʶ 0 ����  1  ����
void EXIT_Init(void);						//��ʼ���ⲿ�ж�
void EXTI15_10_IRQHandler(void);//�ⲿ�жϺ���
#endif

