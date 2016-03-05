#include "lcd5110.h"
#include "spi.h"
#include "delay.h"
#include "ascii0608.h"
#include "stringCH.h"
/*-----------------------------------------------------------------------------
名称:	LCD5110_WR_Byte
功能:	向5110模块写入数据
输入:	u8 data 待写入的数据
输出:	u8 cmd 命令和数据标识 0 命令 1 数据
-----------------------------------------------------------------------------*/
void LCD5110_WR_Byte(u8 data, u8 cmd)
{
	CE = 0;											//使能器件
	if(cmd == 0)								//命令
	{
		DC = 0;										//传送命令
	}else
	{
		DC = 1;										//传送数据
	}
	SPI2_ReadWriteByte(data);
	CE = 1;											//禁能器件
}
/*-----------------------------------------------------------------------------
名称:	LCD5110_Init
功能:	初始化LCD5110屏幕
输入:	void
输出:	void
-----------------------------------------------------------------------------*/
void LCD5110_Init(void)
{													
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOD,ENABLE);//使能GPIOB时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;												//配置PB11 端口
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;									//配置为推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;									//配置I/O口的速度为50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);														//根据设定值，配置PB11 端口	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;												//配置PD12 端口
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;									//配置为推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;									//配置I/O口的速度为50MHz
	GPIO_Init(GPIOD, &GPIO_InitStructure);														//根据设定值，配置PD12 端口	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_15;							//配置PE7、PE15 端口
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;									//配置为推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;									//配置I/O口的速度为50MHz
	GPIO_Init(GPIOE, &GPIO_InitStructure);														//根据设定值，配置PE7、PE15 端口		
	RST = 0;																													//产生一个LCD复位的低脉冲信号
	SPI2_Init();																											//初始化SPI2模块		
	delay_us(1);
	RST = 1;
	CE = 0;			
	delay_us(1);
	CE = 1;
	delay_us(1);	
	LCD5110_WR_Byte(0x21,0);																					//使用扩展命令设置LCD模式
	LCD5110_WR_Byte(0xC8,0);																					//设置偏置电压
	LCD5110_WR_Byte(0x06,0);																					//温度校正
	LCD5110_WR_Byte(0x13,0);																					//1：48
	LCD5110_WR_Byte(0x20,0);																					//使用基本命令
	LCD5110_Clear();																									//清屏
	LCD5110_WR_Byte(0x0C,0);																					//设定显示模式，正常模式
	CE = 0;	
}
/*-----------------------------------------------------------------------------
名称:	LCD5110_Clear
功能:	清空LCD屏幕
输入:	void
输出:	void
-----------------------------------------------------------------------------*/
void LCD5110_Clear(void)
{
	u16 i;
	LCD5110_WR_Byte(0x0C,0);
	LCD5110_WR_Byte(0x80,0);
	for(i=0;i<504;i++)
	{
		LCD5110_WR_Byte(0,1);
	}	
}
/*-----------------------------------------------------------------------------
名称:	LCD5110_SetBL
功能:	设置LCD屏幕背光
输入:	u8 state	设定的背光 1 开启 0 关闭
输出:	void
-----------------------------------------------------------------------------*/
void LCD5110_SetBL(u8 state)
{
	BL = state;
}
/*-----------------------------------------------------------------------------
名称:	LCD5110_SetXY
功能:	设置LCD屏幕坐标
输入:	u8 X　x轴坐标
			u8 Y	y轴坐标
输出:	void
-----------------------------------------------------------------------------*/
void LCD5110_SetXY(u8 x, u8 y)
{
	LCD5110_WR_Byte(0x40|y, 0);																				//行号
	LCD5110_WR_Byte(0x80|x, 0);																				//列号
}
/*-----------------------------------------------------------------------------
名称:	LCD5110_Putc
功能:	在屏幕中显示一个字符
输入:	u8 X　x轴坐标
			u8 Y	y轴坐标
			u8 ch	待显示的字符
输出:	void
-----------------------------------------------------------------------------*/
void LCD5110_Putc(u8 x, u8 y, u8 ch)
{
	u8 i=0;
	ch -= 32;
	x *=6;
	LCD5110_SetXY(x,y);
	for(i=0;i<6;i++)
	{
		LCD5110_WR_Byte(ascii_0608[ch][i], 1);													//写入6*8ASCII字符
	}
}
/*-----------------------------------------------------------------------------
名称:	LCD5110_ShowStringEN
功能:	在屏幕中显示一串字符
输入:	u8 X　x轴坐标
			u8 Y	y轴坐标
			u8 *str字符串的首地址
输出:	void
-----------------------------------------------------------------------------*/
void LCD5110_ShowStringEN(u8 x, u8 y, u8 *str)
{
	while(*str)
	{
		LCD5110_Putc(x++, y, *str);
		str ++;
		if(x>14)
		{
			y++;
			x = 0;
		}
	}
}
/*-----------------------------------------------------------------------------
名称:	LCD5110_ShowNum
功能:	在屏幕中显示数字
输入:	u8 X　x轴坐标
			u8 Y	y轴坐标
			u16 num 待显示的数字
输出:	void
-----------------------------------------------------------------------------*/
void LCD5110_ShowNum(u8 x, u8 y, u16 num)
{
	u8 i=0;
	u8 width;
	u8 len=1;
	u8 data[6]={0};
	u16 temp = num;
	while(temp/10)
	{
		temp /= 10;
		len++;
	}
	while(num/10)																											//拆分
	{
		data[i] = num % 10;																							//获取个位上的数值
		num /= 10;
		i++;
	}
	data[i] = num;																										//剩下的一位的数值为最高位
	width = i;
	for(i=0;i<width+1;i++)
	{
		data[i] += 48;																									//转换为ASCII码
	}
	for(i=0;i<len;i++)
	{
		LCD5110_Putc(x+i, y, ' ');
	}
	for(i=0;i<len;i++)
	{
		LCD5110_Putc(x++,y,data[width-i]);
	}
}
/*-----------------------------------------------------------------------------
名称:	LCD5110_PutHanzi
功能:	显示汉字
输入:	u8 X　x轴坐标
			u8 Y	y轴坐标
			u8 ch_with	汉字宽度
			u8 ch_num	汉字个数
			u8 line	在字库数组中的位置
			u8 row	汉字行间距
输出:	void
-----------------------------------------------------------------------------*/
void LCD5110_PutHanzi(u8 X, u8 Y, u8 ch_with, u8 ch_num, u8 line, u8 row)
{
	u8 i,n;
	LCD5110_SetXY(X,Y);																								//设置初始位置
	for(i=0;i<ch_num;)
	{
		for(n=0;n<ch_with*2;n++)
		{
			if(n==ch_with)																								//写汉字的下半部分
			{
				if(i==0)
				{
					LCD5110_SetXY(X,Y+1);																			//如果只有一个汉字
				}else
				{
					LCD5110_SetXY((X+(ch_with+row)*i),Y+1);
				}
			}
			LCD5110_WR_Byte(write_chinese[line+i][n],1);									//从字库中提取显示的数据
		}
		i++;
		LCD5110_SetXY((X+(ch_with+row)*i),Y);														//移动光标的位置
	}
}

