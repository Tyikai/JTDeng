#ifndef DIGITALLED_H_
#define DIGITALLED_H_
#include "sys.h"
#define Bit1	PEout(1)			//��һλ�����
#define Bit2	PEout(2)			//�ڶ�λ�����
#define Bit3	PAout(3)			//����λ�����
#define Bit4	PAout(4)			//����λ�����
#define Bit5	PDout(9)			//����λ�����
#define Bit6	PDout(10)			//����λ�����
#define Bit7	PDout(14)			//����λ�����
#define Bit8	PDout(15)			//�ڰ�λ�����
void DigitalLED_Duan(u8 data);	//����ܶ���
void DigitalLED_Init(void);			//��ʼ�������
extern u8 SEG_CODE[];						//BCD��
extern u8 Array[];							//��λ��ʮλ��ʾ��ֵ
void DigitalLED_Fen(u8 num);		//�ֽ���λ��
#endif

