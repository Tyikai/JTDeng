#include "lcd5110.h"
#include "spi.h"
#include "delay.h"
#include "ascii0608.h"
#include "stringCH.h"
/*-----------------------------------------------------------------------------
����:	LCD5110_WR_Byte
����:	��5110ģ��д������
����:	u8 data ��д�������
���:	u8 cmd ��������ݱ�ʶ 0 ���� 1 ����
-----------------------------------------------------------------------------*/
void LCD5110_WR_Byte(u8 data, u8 cmd)
{
	CE = 0;											//ʹ������
	if(cmd == 0)								//����
	{
		DC = 0;										//��������
	}else
	{
		DC = 1;										//��������
	}
	SPI2_ReadWriteByte(data);
	CE = 1;											//��������
}
/*-----------------------------------------------------------------------------
����:	LCD5110_Init
����:	��ʼ��LCD5110��Ļ
����:	void
���:	void
-----------------------------------------------------------------------------*/
void LCD5110_Init(void)
{													
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOD,ENABLE);//ʹ��GPIOBʱ��
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;												//����PB11 �˿�
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;									//����Ϊ�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;									//����I/O�ڵ��ٶ�Ϊ50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);														//�����趨ֵ������PB11 �˿�	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;												//����PD12 �˿�
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;									//����Ϊ�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;									//����I/O�ڵ��ٶ�Ϊ50MHz
	GPIO_Init(GPIOD, &GPIO_InitStructure);														//�����趨ֵ������PD12 �˿�	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_15;							//����PE7��PE15 �˿�
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;									//����Ϊ�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;									//����I/O�ڵ��ٶ�Ϊ50MHz
	GPIO_Init(GPIOE, &GPIO_InitStructure);														//�����趨ֵ������PE7��PE15 �˿�		
	RST = 0;																													//����һ��LCD��λ�ĵ������ź�
	SPI2_Init();																											//��ʼ��SPI2ģ��		
	delay_us(1);
	RST = 1;
	CE = 0;			
	delay_us(1);
	CE = 1;
	delay_us(1);	
	LCD5110_WR_Byte(0x21,0);																					//ʹ����չ��������LCDģʽ
	LCD5110_WR_Byte(0xC8,0);																					//����ƫ�õ�ѹ
	LCD5110_WR_Byte(0x06,0);																					//�¶�У��
	LCD5110_WR_Byte(0x13,0);																					//1��48
	LCD5110_WR_Byte(0x20,0);																					//ʹ�û�������
	LCD5110_Clear();																									//����
	LCD5110_WR_Byte(0x0C,0);																					//�趨��ʾģʽ������ģʽ
	CE = 0;	
}
/*-----------------------------------------------------------------------------
����:	LCD5110_Clear
����:	���LCD��Ļ
����:	void
���:	void
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
����:	LCD5110_SetBL
����:	����LCD��Ļ����
����:	u8 state	�趨�ı��� 1 ���� 0 �ر�
���:	void
-----------------------------------------------------------------------------*/
void LCD5110_SetBL(u8 state)
{
	BL = state;
}
/*-----------------------------------------------------------------------------
����:	LCD5110_SetXY
����:	����LCD��Ļ����
����:	u8 X��x������
			u8 Y	y������
���:	void
-----------------------------------------------------------------------------*/
void LCD5110_SetXY(u8 x, u8 y)
{
	LCD5110_WR_Byte(0x40|y, 0);																				//�к�
	LCD5110_WR_Byte(0x80|x, 0);																				//�к�
}
/*-----------------------------------------------------------------------------
����:	LCD5110_Putc
����:	����Ļ����ʾһ���ַ�
����:	u8 X��x������
			u8 Y	y������
			u8 ch	����ʾ���ַ�
���:	void
-----------------------------------------------------------------------------*/
void LCD5110_Putc(u8 x, u8 y, u8 ch)
{
	u8 i=0;
	ch -= 32;
	x *=6;
	LCD5110_SetXY(x,y);
	for(i=0;i<6;i++)
	{
		LCD5110_WR_Byte(ascii_0608[ch][i], 1);													//д��6*8ASCII�ַ�
	}
}
/*-----------------------------------------------------------------------------
����:	LCD5110_ShowStringEN
����:	����Ļ����ʾһ���ַ�
����:	u8 X��x������
			u8 Y	y������
			u8 *str�ַ������׵�ַ
���:	void
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
����:	LCD5110_ShowNum
����:	����Ļ����ʾ����
����:	u8 X��x������
			u8 Y	y������
			u16 num ����ʾ������
���:	void
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
	while(num/10)																											//���
	{
		data[i] = num % 10;																							//��ȡ��λ�ϵ���ֵ
		num /= 10;
		i++;
	}
	data[i] = num;																										//ʣ�µ�һλ����ֵΪ���λ
	width = i;
	for(i=0;i<width+1;i++)
	{
		data[i] += 48;																									//ת��ΪASCII��
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
����:	LCD5110_PutHanzi
����:	��ʾ����
����:	u8 X��x������
			u8 Y	y������
			u8 ch_with	���ֿ��
			u8 ch_num	���ָ���
			u8 line	���ֿ������е�λ��
			u8 row	�����м��
���:	void
-----------------------------------------------------------------------------*/
void LCD5110_PutHanzi(u8 X, u8 Y, u8 ch_with, u8 ch_num, u8 line, u8 row)
{
	u8 i,n;
	LCD5110_SetXY(X,Y);																								//���ó�ʼλ��
	for(i=0;i<ch_num;)
	{
		for(n=0;n<ch_with*2;n++)
		{
			if(n==ch_with)																								//д���ֵ��°벿��
			{
				if(i==0)
				{
					LCD5110_SetXY(X,Y+1);																			//���ֻ��һ������
				}else
				{
					LCD5110_SetXY((X+(ch_with+row)*i),Y+1);
				}
			}
			LCD5110_WR_Byte(write_chinese[line+i][n],1);									//���ֿ�����ȡ��ʾ������
		}
		i++;
		LCD5110_SetXY((X+(ch_with+row)*i),Y);														//�ƶ�����λ��
	}
}

