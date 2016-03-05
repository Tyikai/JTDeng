#include "timer.h"
#include "sys.h"
#include "key.h"
#include "led.h"
#include "ui.h"
#include "exti.h"
#include "digitalled.h"
#include "delay.h"
u8 Change_Flag = 0;					//�л���ʶ
u8 times = 0; 							//��ʱ��ʱ�ñ�ʶ
u8 n = 0;										//�����λ����ʶ
u8 m = 0;										//��ʱ����
u8 t = 0;										//��ʱ����
/*-----------------------------------------------------------------------------
����:		TIM3_Init
����:		��ʱ��3�жϳ�ʼ��
����:		arr �Զ���װֵ
				psc ʱ��Ԥ��Ƶ��
���:		void
-----------------------------------------------------------------------------*/
void TIM3_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); 							//ʱ��ʹ��
																																		//��ʱ��TIM3��ʼ��
	TIM_TimeBaseStructure.TIM_Period = arr; 													//��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 												//����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 					//����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  			//TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); 									//����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); 												//ʹ��ָ����TIM3�ж�,��������ж�	
																																		//�ж����ȼ�NVIC����
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  									//TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  				//��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  							//�����ȼ�1��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 									//IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  																	//��ʼ��NVIC�Ĵ���	
	TIM_Cmd(TIM3, ENABLE);  																					//ʹ��TIMx
	times = RunCyle;
}
/*-----------------------------------------------------------------------------
����:		TIM3_IRQHandler
����:		��ʱ��3�жϺ���
����:		void
���:		void
-----------------------------------------------------------------------------*/
void TIM3_IRQHandler(void)   
{																										//��ʱ����ʱ����
	if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  								//���TIM3�����жϷ������
	{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  									//���TIMx�����жϱ�־ 
		/**************************************************************************/
																		//���Ĵ���
		/**************************************************************************/
		times --;																												//��ʱ
		if(times==0)																										//��ʱ��ﵽ�趨������ʱ
		{
			Change_Flag = 1;																							//LED�����л�
			times = RunCyle;																							//�����趨����
		}else if(times>RunCyle)																					//�ݴ����
		{
			times = RunCyle;
		}
		
		if(times==RunCyle)																							//�����ڵ�ͳ��
		{
			m ++;
		}
		if(m==2)																												//�������2�����ڣ���Ƶ���˸,��˸ʱ��2s
		{
			times = 2;
			t = 1;
			m = 0;
		}else if(times==1&&t==1)																				//�Ƶ���˸ʱ���������ʾ0
		{
			DigitalLED_Fen(0);
			t = 0;
		}else 																													//����ʱ��������ʾ����ʱ
		{
			DigitalLED_Fen(times);
		}
	}
}
/*-----------------------------------------------------------------------------
����:		TIM4_Init
����:		��ʱ��4�жϳ�ʼ��
����:		arr �Զ���װֵ
				psc ʱ��Ԥ��Ƶ��
���:		void
-----------------------------------------------------------------------------*/
void TIM4_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); 							//ʱ��ʹ��
																																		//��ʱ��TIM4��ʼ��
	TIM_TimeBaseStructure.TIM_Period = arr; 													//��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 												//����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 					//����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  			//TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); 									//����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE ); 												//ʹ��ָ����TIM4�ж�,��������ж�	
																																		//�ж����ȼ�NVIC����
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  									//TIM4�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  				//��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;  							//�����ȼ�2��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 									//IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  																	//��ʼ��NVIC�Ĵ���	
	TIM_Cmd(TIM4, ENABLE);  																					//ʹ��TIMx
}
/*-----------------------------------------------------------------------------
����:		TIM4_IRQHandler
����:		��ʱ��4�жϺ���
����:		void
���:		void
-----------------------------------------------------------------------------*/
void TIM4_IRQHandler(void)   
{																																		//��ʱ����ʱ����
	if(TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)  								//���TIM4�����жϷ������
	{
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);  										//���TIMx�����жϱ�־ 
		LED = !LED;																											//LED״̬����ָʾ��
	}
}
/*-----------------------------------------------------------------------------
����:		TIM5_Init
����:		��ʱ��4�жϳ�ʼ��
����:		arr �Զ���װֵ
				psc ʱ��Ԥ��Ƶ��
���:		void
-----------------------------------------------------------------------------*/
void TIM5_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE); 							//ʱ��ʹ��
																																		//��ʱ��TIM5��ʼ��
	TIM_TimeBaseStructure.TIM_Period = arr; 													//��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 												//����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 					//����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  			//TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); 									//����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE ); 												//ʹ��ָ����TIM5�ж�,��������ж�	
																																		//�ж����ȼ�NVIC����
	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;  									//TIM5�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  				//��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  							//�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 									//IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  																	//��ʼ��NVIC�Ĵ���	
	TIM_Cmd(TIM5, ENABLE);  																					//ʹ��TIMx
}
/*-----------------------------------------------------------------------------
����:		TIM5_IRQHandler
����:		��ʱ��4�жϺ���
����:		void
���:		void
-----------------------------------------------------------------------------*/
void TIM5_IRQHandler(void)   
{		
	if(TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)  								//���TIM4�����жϷ������
	{
		switch(n)																												//��̬��ʾ��Ŀ��
		{
			case 0:
			{
				DigitalLED_Duan(SEG_CODE[Array[0]]);
				Bit1 = 1;
				Bit2 = 0;
				Bit3 = 0;
				Bit4 = 0;
				Bit5 = 0;
				Bit6 = 0;
				Bit7 = 0;
				Bit8 = 0;
				n ++;
				break;
			}
			case 1:
			{
				DigitalLED_Duan(SEG_CODE[Array[1]]);
				Bit1 = 0;
				Bit2 = 1;
				Bit3 = 0;
				Bit4 = 0;
				Bit5 = 0;
				Bit6 = 0;
				Bit7 = 0;
				Bit8 = 0;
				n ++;
				break;			
			}
			case 2:
			{
				DigitalLED_Duan(SEG_CODE[Array[0]]);
				Bit1 = 0;
				Bit2 = 0;
				Bit3 = 1;
				Bit4 = 0;
				Bit5 = 0;
				Bit6 = 0;
				Bit7 = 0;
				Bit8 = 0;
				n ++;
				break;			
			}
			case 3:
			{
				DigitalLED_Duan(SEG_CODE[Array[1]]);
				Bit1 = 0;
				Bit2 = 0;
				Bit3 = 0;
				Bit4 = 1;
				Bit5 = 0;
				Bit6 = 0;
				Bit7 = 0;
				Bit8 = 0;
				n ++;
				break;			
			}
			case 4:
			{
				DigitalLED_Duan(SEG_CODE[Array[0]]);
				Bit1 = 0;
				Bit2 = 0;
				Bit3 = 0;
				Bit4 = 0;
				Bit5 = 1;
				Bit6 = 0;
				Bit7 = 0;
				Bit8 = 0;
				n ++;
				break;			
			}
			case 5:
			{
				DigitalLED_Duan(SEG_CODE[Array[1]]);
				Bit1 = 0;
				Bit2 = 0;
				Bit3 = 0;
				Bit4 = 0;
				Bit5 = 0;
				Bit6 = 1;
				Bit7 = 0;
				Bit8 = 0;
				n ++;
				break;				
			}
			case 6:
			{
				DigitalLED_Duan(SEG_CODE[Array[0]]);
				Bit1 = 0;
				Bit2 = 0;
				Bit3 = 0;
				Bit4 = 0;
				Bit5 = 0;
				Bit6 = 0;
				Bit7 = 1;
				Bit8 = 0;
				n ++;
				break;				
			}
			case 7:
			{
				DigitalLED_Duan(SEG_CODE[Array[1]]);
				Bit1 = 0;
				Bit2 = 0;
				Bit3 = 0;
				Bit4 = 0;
				Bit5 = 0;
				Bit6 = 0;
				Bit7 = 0;
				Bit8 = 1;
				n = 0;
				break;				
			}
		}
		TIM_ClearITPendingBit(TIM5, TIM_IT_Update);  										//���TIMx�����жϱ�־ 
	}
}
