#ifndef BIGLED_H_
#define BIGLED_H_
#include "sys.h"
#define LED_R1	PBout(0)//��ɫ��LED1
#define LED_Y1	PBout(1)//��ɫ��LED1
#define LED_G1	PBout(2)//��ɫ��LED1
#define LED_R2	PAout(0)//��ɫ��LED2
#define LED_Y2	PAout(1)//��ɫ��LED2
#define LED_G2	PAout(2)//��ɫ��LED2
void BIGLED_Init(void);//��ʼ����LEDģ��
void BIGLED_Run(void);//��LEDģ�����к���
#endif

