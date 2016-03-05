#include "exti.h"
#include "sys.h"
#include "stm32f10x_exti.h"
#include "ui.h"
#include "key.h"
#include "lcd5110.h"
#include "delay.h"
u8 Run_Mode = 0;						//��ǰ����ģʽ 0 ����		1 ����
/*-----------------------------------------------------------------------------
����:		EXIT_Init
����:		��ʼ���ⲿ�жϣ����ذ���
����:		void
���:		void
-----------------------------------------------------------------------------*/
void EXIT_Init(void)
{
 	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);								//ʹ�ܸ��ù���ʱ��
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource10);				//���ذ���PB10
	EXTI_InitStructure.EXTI_Line=EXTI_Line10;	
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);	 																	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���	
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;							//
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;					//��ռ���ȼ�0�� 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;								//�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;										//ʹ���ⲿ�ж�ͨ��
	NVIC_Init(&NVIC_InitStructure);
}
/********************************************************************
*name:EXTI15_10_IRQHandler
*description:�ⲿ�ж�10_15�������
*param:void
*return:void
********************************************************************/
void EXTI15_10_IRQHandler(void)
{
	Run_Mode = 1;																											//�趨״̬Ϊ����̬
	LCD5110_Clear();																									//��Ƶ
	delay_ms(50);
	LCD5110_Clear();																									//��Ƶ
	EXTI_ClearITPendingBit(EXTI_Line10);															//���LINE10�ϵ��жϱ�־λ
}

