#include "key.h"
#include "delay.h"
#include "exti.h"
#include "ui.h"
#include "lcd5110.h"
#include "timer.h"
u8 RunCyle	=	3;					//运行周期
u8 temp = 0;
/*-----------------------------------------------------------------------------
名称:		KEY_Init
功能:		初始化所有按键
输入:		void
输出:		void
-----------------------------------------------------------------------------*/
void KEY_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOD
	|RCC_APB2Periph_GPIOE,ENABLE);																		//使能GPIOB、GPIOD、GPIOE时钟
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;													//配置PE8 端口
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;											//配置成上拉输入
	GPIO_Init(GPIOE, &GPIO_InitStructure);														//根据设定值，配置PE8 端口

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;												//配置PB10 端口
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;											//配置成上拉输入
	GPIO_Init(GPIOB, &GPIO_InitStructure);														//根据设定值，配置PB10 端口

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_13;					//配置PD11、PD13 端口
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;											//配置成上拉输入
	GPIO_Init(GPIOD, &GPIO_InitStructure);														//根据设定值，配置PB10 端口	
}
/*-----------------------------------------------------------------------------
名称:		Get_Key
功能:		获取按键的值
输入:		u8 mode		支持的模式 0 不支持连续按  1 支持连按
输出:		按键的值 1->确认 2->返回 3->上 4->下 0-> 无效按键
-----------------------------------------------------------------------------*/
u8 Get_Key(u8 mode)
{
	static u8 key_up = 1;																							//按键松开标识
	if(mode)
	{
		key_up = 1;																											//支持连续按键
	}
	if(key_up&&(K_MakeSure==0||K_Back==0||K_Up==0||K_Down==0))				//如果有按键按下
	{
		delay_ms(50);																										//消除抖动
		key_up = 0;
		if(K_MakeSure==0)																								//确认按键
		{
			return 1;
		}
		if(K_Back==0)																										//返回按键
		{
			return 2;
		}
		if(K_Up==0)																											//上 按键
		{
			return 3;
		}
		if(K_Down==0)																										//下 按键
		{
			return 4;
		}
	}else if(K_MakeSure==1||K_Back==1||K_Up==1||K_Down==1)
	{
		key_up = 1;																											
	}
	return 0;																													//无按键按下
}
/*-----------------------------------------------------------------------------
名称:		KEY_Set
功能:		通过按键设置参数
输入:		void
输出:		void
-----------------------------------------------------------------------------*/
void Key_Set(void)
{
	switch(Get_Key(1))
	{
		case 1:																													//确认退出
		{
			RunCyle = temp;
			times = 0;
			Run_Mode = 0;
			break;
		}
		case 3:																													//上 按键
		{
			temp ++;
			if(temp>99)
			{
				temp = 0;
			}
			break;
		}
		case 4:																													//下 按键
		{
			temp --;
			if(temp <= 0)
			{
				temp = 0;
			}
			break;
		}
	}
	LCD5110_SetBL(1);																									//关闭背光
	UI_Set(temp);																											//显示设置界面
}

