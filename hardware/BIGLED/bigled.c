#include "bigled.h"
#include "timer.h"
#include "delay.h"
#include "key.h"
#include "ui.h"
#include "lcd5110.h"
u8 Flash_Count = 0;					//黄灯闪烁次数
u8 Operation_Type = 3;			//操作类型
/*-----------------------------------------------------------------------------
名称:	BIGLED_Init
功能:	初始化大LED模块
输入: void
输出: void
-----------------------------------------------------------------------------*/
void BIGLED_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB,ENABLE);//使能GPIOA、GPIOB时钟
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2;		//配置PB0、PB1、PB2 端口
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;									//配置为推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;									//配置I/O口的速度为50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);														//根据设定值，配置PB0、PB1、PB2 端口
	GPIO_ResetBits(GPIOC,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2);											//设置默认电平   高电平

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2;		//配置PA0、PA1、PA2 端口
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;									//配置为推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;									//配置I/O口的速度为50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);														//根据设定值，配置PA0、PA1、PA2 端口
	GPIO_ResetBits(GPIOA,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2);							//设置默认电平   高电平	
}
/*-----------------------------------------------------------------------------
名称:	BIGLED_Run
功能:	大LED运行时的切换
输入: u16 time 切换周期
输出: void
-----------------------------------------------------------------------------*/
void BIGLED_Run()
{
	switch(Operation_Type)					
	{
		case 1:																													//东西向绿灯与南北向红灯亮
		{
			LED_R1 = 0;	LED_Y1 = 0;	LED_G1 = 1;
			LED_R2 = 1;	LED_Y2 = 0;	LED_G2 = 0;
			Change_Flag = 0;
			while(!Change_Flag);																					//延时
			Change_Flag = 0;
			Operation_Type = 2;																						//下一操作
			break;
		}
		case 2:																													//东西向黄灯开始闪烁，绿灯关闭
		{
			LED_G1 = 0;
			delay_ms(333);
			LED_Y1 = ~ LED_Y1;
			if(++Flash_Count != 6)
				return;																											//闪烁3次
			Flash_Count = 0;
			Operation_Type = 3;																						//下一操作
			break;
		}		
		case 3:																													//东西向红灯与南北向绿灯亮
		{
			LED_R1 = 1;	LED_Y1 = 0;	LED_G1 = 0;
			LED_R2 = 0;	LED_Y2 = 0;	LED_G2 = 1;
			Change_Flag = 0;
			while(!Change_Flag);																					//延时
			Change_Flag = 0;
			Operation_Type = 4;																						//下一操作
			break;
		}		
		case 4:																													//南北向黄灯开始闪烁
		{
			LED_G2 = 0;
			delay_ms(333);
			LED_Y2 = ~ LED_Y2;
			if(++Flash_Count != 6)
				return;																											//闪烁3次
			Flash_Count = 0;
			Operation_Type = 1;																						//下一操作
			break;
		}			
	}			
	LCD5110_SetBL(0);																									//关闭屏幕背光
	UI_Run(RunCyle);																									//显示正常显示界面
}

