#include "ui.h"
#include "lcd5110.h"
#include "sys.h"
#include "delay.h"
/*-----------------------------------------------------------------------------
名称:		UI_Run
功能:		运行时显示UI
输入:		void
输出:		void
-----------------------------------------------------------------------------*/
void UI_Run(u16 t)
{
	LCD5110_PutHanzi(24,0,12,3,0,0);																	//交通灯
	LCD5110_PutHanzi(6,2,12,6,11,0);																	//周期+四空格
	LCD5110_PutHanzi(66,2,12,1,17,0);																	//秒	
	LCD5110_ShowNum(7,2,t);
	LCD5110_PutHanzi(6,4,12,6,3,0);																		//运行中...			
}
/*-----------------------------------------------------------------------------
名称:		UI_Set
功能:		设置时显示UI
输入:		u16 t 设定的时间
输出:		void
-----------------------------------------------------------------------------*/
void UI_Set(u16 t)
{
	LCD5110_PutHanzi(30,0,12,2,9,0);																	//设置
	LCD5110_PutHanzi(6,2,12,6,11,0);																	//周期+四空格
	LCD5110_PutHanzi(66,2,12,1,17,0);																	//秒
	LCD5110_ShowNum(7,2,t);
}

