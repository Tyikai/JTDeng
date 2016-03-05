#include "exti.h"
#include "sys.h"
#include "stm32f10x_exti.h"
#include "ui.h"
#include "key.h"
#include "lcd5110.h"
#include "delay.h"
u8 Run_Mode = 0;						//当前运行模式 0 运行		1 设置
/*-----------------------------------------------------------------------------
名称:		EXIT_Init
功能:		初始化外部中断，返回按键
输入:		void
输出:		void
-----------------------------------------------------------------------------*/
void EXIT_Init(void)
{
 	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);								//使能复用功能时钟
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource10);				//返回按键PB10
	EXTI_InitStructure.EXTI_Line=EXTI_Line10;	
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);	 																	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器	
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;							//
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;					//先占优先级0级 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;								//从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;										//使能外部中断通道
	NVIC_Init(&NVIC_InitStructure);
}
/********************************************************************
*name:EXTI15_10_IRQHandler
*description:外部中断10_15服务程序
*param:void
*return:void
********************************************************************/
void EXTI15_10_IRQHandler(void)
{
	Run_Mode = 1;																											//设定状态为设置态
	LCD5110_Clear();																									//清频
	delay_ms(50);
	LCD5110_Clear();																									//清频
	EXTI_ClearITPendingBit(EXTI_Line10);															//清除LINE10上的中断标志位
}

