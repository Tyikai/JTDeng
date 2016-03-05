#ifndef BIGLED_H_
#define BIGLED_H_
#include "sys.h"
#define LED_R1	PBout(0)//红色大LED1
#define LED_Y1	PBout(1)//黄色大LED1
#define LED_G1	PBout(2)//绿色大LED1
#define LED_R2	PAout(0)//红色大LED2
#define LED_Y2	PAout(1)//黄色大LED2
#define LED_G2	PAout(2)//绿色大LED2
void BIGLED_Init(void);//初始化大LED模块
void BIGLED_Run(void);//大LED模块运行函数
#endif

