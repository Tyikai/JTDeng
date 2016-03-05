#include "digitalled.h"
#include "delay.h"
#include "timer.h"
u8 SEG_CODE[10]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};//�����������ʾ8421��
u8 Array[2]={0,0};																									//�����λ��ʮλ��ʾ��ֵ
/*-----------------------------------------------------------------------------
����:	DigitalLED_Init
����:	��ʼ����λ�����
����:	void
���:	void
-----------------------------------------------------------------------------*/
void DigitalLED_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);							//ʹ��GPIOCʱ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3
																|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6;	//����PC0~PC6 �˿�
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;									//����Ϊ�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;									//����I/O�ڵ��ٶ�Ϊ50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);														//�����趨ֵ������PC0~PC6 �˿�
	GPIO_SetBits(GPIOC,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3
																|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6);	//����Ĭ�ϵ�ƽ   �ߵ�ƽ
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2;							//����PE1	��PE2	�˿�
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;									//����Ϊ�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;									//����I/O�ڵ��ٶ�Ϊ50MHz
	GPIO_Init(GPIOE, &GPIO_InitStructure);														//�����趨ֵ������PE1	��PE2	�˿�
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4;							//����PA3	��PA4	�˿�
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;									//����Ϊ�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;									//����I/O�ڵ��ٶ�Ϊ50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);														//�����趨ֵ������PA3	��PA4	�˿�	

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_14|GPIO_Pin_15;
																																		//����PD9	��PD10��PD14��PD15�˿�
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;									//����Ϊ�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;									//����I/O�ڵ��ٶ�Ϊ50MHz
	GPIO_Init(GPIOD, &GPIO_InitStructure);														//�����趨ֵ������PD9	��PD10��PD14��PD15�˿�	
	
}
/*-----------------------------------------------------------------------------
����:	DigitalLED_Duan
����:	�������ܵĶ���
����:	u8 data����
���:	void
-----------------------------------------------------------------------------*/
void DigitalLED_Duan(u8 data)
{
	GPIOC->ODR = data&0xFF;
}
/*-----------------------------------------------------------------------------
����:	DigitalLED_Fen
����:	�ֽ������λ��
����:	u8 num	���ֽ����
���:	void
-----------------------------------------------------------------------------*/
void DigitalLED_Fen(u8 num)
{
	Array[0] = 0;
	while(num>=10)																										//��Ϊֻ��2λ����ܣ�����ʾ0~99
	{
		Array[0]++;																											//ʮλ
		num -= 10;
	}
	Array[1] = num;																										//��λ
	
}

