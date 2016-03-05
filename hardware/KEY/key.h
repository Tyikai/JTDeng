#ifndef KEY_H_
#define KEY_H_
#include "sys.h"
#define K_MakeSure	PEin(8)//确认
#define K_Back PBin(10)		 //返回
#define K_Up	PDin(11)		 //上
#define K_Down	PDin(13)	//下
extern u8 RunCyle;				//运行周期
void KEY_Init(void);//初始化按键
u8 Get_Key(u8 mode);//获取按键的值
void Key_Set(void);	//通过按键进行设置
#endif


