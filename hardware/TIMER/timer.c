#include "timer.h"
#include "sys.h"
#include "key.h"
#include "led.h"
#include "ui.h"
#include "exti.h"
#include "digitalled.h"
#include "delay.h"
u8 Change_Flag = 0;					//切换标识
u8 times = 0; 							//临时延时用标识
u8 n = 0;										//数码管位数标识
u8 m = 0;										//临时变量
u8 t = 0;										//临时变量
/*-----------------------------------------------------------------------------
名称:		TIM3_Init
功能:		定时器3中断初始化
输入:		arr 自动重装值
				psc 时钟预分频数
输出:		void
-----------------------------------------------------------------------------*/
void TIM3_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); 							//时钟使能
																																		//定时器TIM3初始化
	TIM_TimeBaseStructure.TIM_Period = arr; 													//设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 												//设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 					//设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  			//TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); 									//根据指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); 												//使能指定的TIM3中断,允许更新中断	
																																		//中断优先级NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  									//TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  				//先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  							//从优先级1级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 									//IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  																	//初始化NVIC寄存器	
	TIM_Cmd(TIM3, ENABLE);  																					//使能TIMx
	times = RunCyle;
}
/*-----------------------------------------------------------------------------
名称:		TIM3_IRQHandler
功能:		定时器3中断函数
输入:		void
输出:		void
-----------------------------------------------------------------------------*/
void TIM3_IRQHandler(void)   
{																										//延时用临时变量
	if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  								//检查TIM3更新中断发生与否
	{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  									//清除TIMx更新中断标志 
		/**************************************************************************/
																		//核心代码
		/**************************************************************************/
		times --;																												//延时
		if(times==0)																										//当时间达到设定的周期时
		{
			Change_Flag = 1;																							//LED进行切换
			times = RunCyle;																							//重新设定周期
		}else if(times>RunCyle)																					//容错设计
		{
			times = RunCyle;
		}
		
		if(times==RunCyle)																							//对周期的统计
		{
			m ++;
		}
		if(m==2)																												//如果运行2个周期，则黄灯闪烁,闪烁时间2s
		{
			times = 2;
			t = 1;
			m = 0;
		}else if(times==1&&t==1)																				//黄灯闪烁时，数码管显示0
		{
			DigitalLED_Fen(0);
			t = 0;
		}else 																													//其他时间正常显示倒计时
		{
			DigitalLED_Fen(times);
		}
	}
}
/*-----------------------------------------------------------------------------
名称:		TIM4_Init
功能:		定时器4中断初始化
输入:		arr 自动重装值
				psc 时钟预分频数
输出:		void
-----------------------------------------------------------------------------*/
void TIM4_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); 							//时钟使能
																																		//定时器TIM4初始化
	TIM_TimeBaseStructure.TIM_Period = arr; 													//设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 												//设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 					//设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  			//TIM向上计数模式
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); 									//根据指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE ); 												//使能指定的TIM4中断,允许更新中断	
																																		//中断优先级NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  									//TIM4中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  				//先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;  							//从优先级2级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 									//IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  																	//初始化NVIC寄存器	
	TIM_Cmd(TIM4, ENABLE);  																					//使能TIMx
}
/*-----------------------------------------------------------------------------
名称:		TIM4_IRQHandler
功能:		定时器4中断函数
输入:		void
输出:		void
-----------------------------------------------------------------------------*/
void TIM4_IRQHandler(void)   
{																																		//延时用临时变量
	if(TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)  								//检查TIM4更新中断发生与否
	{
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);  										//清除TIMx更新中断标志 
		LED = !LED;																											//LED状态运行指示灯
	}
}
/*-----------------------------------------------------------------------------
名称:		TIM5_Init
功能:		定时器4中断初始化
输入:		arr 自动重装值
				psc 时钟预分频数
输出:		void
-----------------------------------------------------------------------------*/
void TIM5_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE); 							//时钟使能
																																		//定时器TIM5初始化
	TIM_TimeBaseStructure.TIM_Period = arr; 													//设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 												//设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 					//设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  			//TIM向上计数模式
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); 									//根据指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE ); 												//使能指定的TIM5中断,允许更新中断	
																																		//中断优先级NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;  									//TIM5中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  				//先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  							//从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 									//IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  																	//初始化NVIC寄存器	
	TIM_Cmd(TIM5, ENABLE);  																					//使能TIMx
}
/*-----------------------------------------------------------------------------
名称:		TIM5_IRQHandler
功能:		定时器4中断函数
输入:		void
输出:		void
-----------------------------------------------------------------------------*/
void TIM5_IRQHandler(void)   
{		
	if(TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)  								//检查TIM4更新中断发生与否
	{
		switch(n)																												//动态显示数目管
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
		TIM_ClearITPendingBit(TIM5, TIM_IT_Update);  										//清除TIMx更新中断标志 
	}
}
