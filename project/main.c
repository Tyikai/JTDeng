#include "delay.h"
#include "led.h"
#include "key.h"
#include "lcd5110.h"
#include "bigled.h"
#include "digitalled.h"
#include "ui.h"
#include "timer.h"
#include "exti.h"
#include "usart.h"

int main(void)
{
	delay_init();							//��ʼ����ʱģ��
	uart_init(9600);					//��ʼ������
	LED_Init();								//��ʼ��LEDģ��
	KEY_Init();								//��ʼ��KEYģ��																	
	LCD5110_Init();						//��ʼ��LCD5110
	BIGLED_Init();						//��ʼ����LEDģ��
	DigitalLED_Init();				//��ʼ�������ģ��
	TIM3_Init(9999,7199);			//��ʼ����ʱ��
	TIM4_Init(4999,7199);			//��ʼ����ʱ��
	TIM5_Init(9,719);				//��ʼ����ʱ��
	EXIT_Init();
	while(1)
	{
		if(Run_Mode)						//����̬
		{
			Key_Set();
		}else										//����̬
		{
			BIGLED_Run();
		}
	}
}

