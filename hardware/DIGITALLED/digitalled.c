#include "digitalled.h"
#include "delay.h"
#include "timer.h"
u8 SEG_CODE[10]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};//共阴数码管显示8421码
u8 Array[2]={0,0};																									//保存个位和十位显示的值
/*-----------------------------------------------------------------------------
名称:	DigitalLED_Init
功能:	初始化两位数码管
输入:	void
输出:	void
-----------------------------------------------------------------------------*/
void DigitalLED_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);							//使能GPIOC时钟
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3
																|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6;	//配置PC0~PC6 端口
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;									//配置为推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;									//配置I/O口的速度为50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);														//根据设定值，配置PC0~PC6 端口
	GPIO_SetBits(GPIOC,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3
																|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6);	//设置默认电平   高电平
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2;							//配置PE1	、PE2	端口
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;									//配置为推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;									//配置I/O口的速度为50MHz
	GPIO_Init(GPIOE, &GPIO_InitStructure);														//根据设定值，配置PE1	、PE2	端口
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4;							//配置PA3	、PA4	端口
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;									//配置为推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;									//配置I/O口的速度为50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);														//根据设定值，配置PA3	、PA4	端口	

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_14|GPIO_Pin_15;
																																		//配置PD9	、PD10、PD14、PD15端口
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;									//配置为推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;									//配置I/O口的速度为50MHz
	GPIO_Init(GPIOD, &GPIO_InitStructure);														//根据设定值，配置PD9	、PD10、PD14、PD15端口	
	
}
/*-----------------------------------------------------------------------------
名称:	DigitalLED_Duan
功能:	输出数码管的段码
输入:	u8 data段码
输出:	void
-----------------------------------------------------------------------------*/
void DigitalLED_Duan(u8 data)
{
	GPIOC->ODR = data&0xFF;
}
/*-----------------------------------------------------------------------------
名称:	DigitalLED_Fen
功能:	分解出各个位数
输入:	u8 num	待分解的数
输出:	void
-----------------------------------------------------------------------------*/
void DigitalLED_Fen(u8 num)
{
	Array[0] = 0;
	while(num>=10)																										//因为只有2位数码管，仅显示0~99
	{
		Array[0]++;																											//十位
		num -= 10;
	}
	Array[1] = num;																										//个位
	
}

