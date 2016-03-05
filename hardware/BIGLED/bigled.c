#include "bigled.h"
#include "timer.h"
#include "delay.h"
#include "key.h"
#include "ui.h"
#include "lcd5110.h"
u8 Flash_Count = 0;					//�Ƶ���˸����
u8 Operation_Type = 3;			//��������
/*-----------------------------------------------------------------------------
����:	BIGLED_Init
����:	��ʼ����LEDģ��
����: void
���: void
-----------------------------------------------------------------------------*/
void BIGLED_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB,ENABLE);//ʹ��GPIOA��GPIOBʱ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2;		//����PB0��PB1��PB2 �˿�
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;									//����Ϊ�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;									//����I/O�ڵ��ٶ�Ϊ50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);														//�����趨ֵ������PB0��PB1��PB2 �˿�
	GPIO_ResetBits(GPIOC,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2);											//����Ĭ�ϵ�ƽ   �ߵ�ƽ

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2;		//����PA0��PA1��PA2 �˿�
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;									//����Ϊ�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;									//����I/O�ڵ��ٶ�Ϊ50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);														//�����趨ֵ������PA0��PA1��PA2 �˿�
	GPIO_ResetBits(GPIOA,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2);							//����Ĭ�ϵ�ƽ   �ߵ�ƽ	
}
/*-----------------------------------------------------------------------------
����:	BIGLED_Run
����:	��LED����ʱ���л�
����: u16 time �л�����
���: void
-----------------------------------------------------------------------------*/
void BIGLED_Run()
{
	switch(Operation_Type)					
	{
		case 1:																													//�������̵����ϱ�������
		{
			LED_R1 = 0;	LED_Y1 = 0;	LED_G1 = 1;
			LED_R2 = 1;	LED_Y2 = 0;	LED_G2 = 0;
			Change_Flag = 0;
			while(!Change_Flag);																					//��ʱ
			Change_Flag = 0;
			Operation_Type = 2;																						//��һ����
			break;
		}
		case 2:																													//������Ƶƿ�ʼ��˸���̵ƹر�
		{
			LED_G1 = 0;
			delay_ms(333);
			LED_Y1 = ~ LED_Y1;
			if(++Flash_Count != 6)
				return;																											//��˸3��
			Flash_Count = 0;
			Operation_Type = 3;																						//��һ����
			break;
		}		
		case 3:																													//�����������ϱ����̵���
		{
			LED_R1 = 1;	LED_Y1 = 0;	LED_G1 = 0;
			LED_R2 = 0;	LED_Y2 = 0;	LED_G2 = 1;
			Change_Flag = 0;
			while(!Change_Flag);																					//��ʱ
			Change_Flag = 0;
			Operation_Type = 4;																						//��һ����
			break;
		}		
		case 4:																													//�ϱ���Ƶƿ�ʼ��˸
		{
			LED_G2 = 0;
			delay_ms(333);
			LED_Y2 = ~ LED_Y2;
			if(++Flash_Count != 6)
				return;																											//��˸3��
			Flash_Count = 0;
			Operation_Type = 1;																						//��һ����
			break;
		}			
	}			
	LCD5110_SetBL(0);																									//�ر���Ļ����
	UI_Run(RunCyle);																									//��ʾ������ʾ����
}

