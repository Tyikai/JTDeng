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
	delay_init();							//初始化延时模块
	uart_init(9600);					//初始化串口
	LED_Init();								//初始化LED模块
	KEY_Init();								//初始化KEY模块																	
	LCD5110_Init();						//初始化LCD5110
	BIGLED_Init();						//初始化大LED模块
	DigitalLED_Init();				//初始化数码管模块
	TIM3_Init(9999,7199);			//初始化定时器
	TIM4_Init(4999,7199);			//初始化定时器
	TIM5_Init(9,719);				//初始化定时器
	EXIT_Init();
	while(1)
	{
		if(Run_Mode)						//设置态
		{
			Key_Set();
		}else										//运行态
		{
			BIGLED_Run();
		}
	}
}

