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
#define RST	PEout(7)					//PE7		RST		��λ����
#define CE 	PEout(15)					//PE15	CE		Ƭѡ
#define DC	PBout(11)					//PB11	DC		����/ָ��ѡ��
#define BL	PDout(12)					//PD12	BL		�������
void LCD5110_Clear(void);//���LCD��Ļ
void LCD5110_WR_Byte(u8 data, u8 cmd);//��5110ģ��д������
void LCD5110_Init(void);//��ʼ��LCD5110��Ļ
void LCD5110_SetBL(u8 state);//����LCD��Ļ����
void LCD5110_SetXY(u8 x, u8 y);//����LCD��Ļ����
void LCD5110_Putc(u8 x, u8 y, u8 ch);//����Ļ����ʾһ���ַ�
void LCD5110_ShowStringEN(u8 x, u8 y, u8 *str);//����Ļ����ʾһ���ַ�
void LCD5110_ShowNum(u8 x, u8 y, u16 num);//����Ļ����ʾ����
void LCD5110_PutHanzi(u8 X, u8 Y, u8 ch_with, u8 ch_num, u8 line, u8 row);//��ʾ����
#endif

