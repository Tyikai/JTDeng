#ifndef EXTI_H_
#define EXTI_H_
#include "sys.h"
extern u8 Run_Mode;							//切换模式标识 0 运行  1  设置
void EXIT_Init(void);						//初始化外部中断
void EXTI15_10_IRQHandler(void);//外部中断函数
#endif

