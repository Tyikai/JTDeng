#ifndef LCD5110_H_
#define LCD5110_H_
#include "sys.h"
/*-----------------------------------------------------------------------------
				RST			PE7
				CE			PE15
				DC			PB11
				BL			PD12
						SPI
				DIN			PB15
				CLK			PB13
-----------------------------------------------------------------------------*/
#define RST	PEout(7)					//PE7		RST		复位引脚
#define CE 	PEout(15)					//PE15	CE		片选
#define DC	PBout(11)					//PB11	DC		数据/指令选择
#define BL	PDout(12)					//PD12	BL		背光控制
void LCD5110_Clear(void);//清空LCD屏幕
void LCD5110_WR_Byte(u8 data, u8 cmd);//向5110模块写入数据
void LCD5110_Init(void);//初始化LCD5110屏幕
void LCD5110_SetBL(u8 state);//设置LCD屏幕背光
void LCD5110_SetXY(u8 x, u8 y);//设置LCD屏幕坐标
void LCD5110_Putc(u8 x, u8 y, u8 ch);//在屏幕中显示一个字符
void LCD5110_ShowStringEN(u8 x, u8 y, u8 *str);//在屏幕中显示一串字符
void LCD5110_ShowNum(u8 x, u8 y, u16 num);//在屏幕中显示数字
void LCD5110_PutHanzi(u8 X, u8 Y, u8 ch_with, u8 ch_num, u8 line, u8 row);//显示汉字
#endif

