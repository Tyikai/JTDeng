#include "led.h"
/*-----------------------------------------------------------------------------
名称:		LED_Init
功能:		初始化LED
输入:		void
输出:		void
-----------------------------------------------------------------------------*/
void LED_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOD,ENABLE);							//使能GPIOB时钟
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;													//配置PB5 端口
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;									//配置为推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;									//配置I/O口的速度为50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);														//根据设定值，配置PB5 端口
}

