#include "key.h"
#include "delay.h"
#include "exti.h"
#include "ui.h"
#include "lcd5110.h"
#include "timer.h"
u8 RunCyle	=	3;					//��������
u8 temp = 0;
/*-----------------------------------------------------------------------------
����:		KEY_Init
����:		��ʼ�����а���
����:		void
���:		void
-----------------------------------------------------------------------------*/
void KEY_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOD
	|RCC_APB2Periph_GPIOE,ENABLE);																		//ʹ��GPIOB��GPIOD��GPIOEʱ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;													//����PE8 �˿�
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;											//���ó���������
	GPIO_Init(GPIOE, &GPIO_InitStructure);														//�����趨ֵ������PE8 �˿�

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;												//����PB10 �˿�
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;											//���ó���������
	GPIO_Init(GPIOB, &GPIO_InitStructure);														//�����趨ֵ������PB10 �˿�

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_13;					//����PD11��PD13 �˿�
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;											//���ó���������
	GPIO_Init(GPIOD, &GPIO_InitStructure);														//�����趨ֵ������PB10 �˿�	
}
/*-----------------------------------------------------------------------------
����:		Get_Key
����:		��ȡ������ֵ
����:		u8 mode		֧�ֵ�ģʽ 0 ��֧��������  1 ֧������
���:		������ֵ 1->ȷ�� 2->���� 3->�� 4->�� 0-> ��Ч����
-----------------------------------------------------------------------------*/
u8 Get_Key(u8 mode)
{
	static u8 key_up = 1;																							//�����ɿ���ʶ
	if(mode)
	{
		key_up = 1;																											//֧����������
	}
	if(key_up&&(K_MakeSure==0||K_Back==0||K_Up==0||K_Down==0))				//����а�������
	{
		delay_ms(50);																										//��������
		key_up = 0;
		if(K_MakeSure==0)																								//ȷ�ϰ���
		{
			return 1;
		}
		if(K_Back==0)																										//���ذ���
		{
			return 2;
		}
		if(K_Up==0)																											//�� ����
		{
			return 3;
		}
		if(K_Down==0)																										//�� ����
		{
			return 4;
		}
	}else if(K_MakeSure==1||K_Back==1||K_Up==1||K_Down==1)
	{
		key_up = 1;																											
	}
	return 0;																													//�ް�������
}
/*-----------------------------------------------------------------------------
����:		KEY_Set
����:		ͨ���������ò���
����:		void
���:		void
-----------------------------------------------------------------------------*/
void Key_Set(void)
{
	switch(Get_Key(1))
	{
		case 1:																													//ȷ���˳�
		{
			RunCyle = temp;
			times = 0;
			Run_Mode = 0;
			break;
		}
		case 3:																													//�� ����
		{
			temp ++;
			if(temp>99)
			{
				temp = 0;
			}
			break;
		}
		case 4:																													//�� ����
		{
			temp --;
			if(temp <= 0)
			{
				temp = 0;
			}
			break;
		}
	}
	LCD5110_SetBL(1);																									//�رձ���
	UI_Set(temp);																											//��ʾ���ý���
}

