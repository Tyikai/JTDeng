#ifndef KEY_H_
#define KEY_H_
#include "sys.h"
#define K_MakeSure	PEin(8)//ȷ��
#define K_Back PBin(10)		 //����
#define K_Up	PDin(11)		 //��
#define K_Down	PDin(13)	//��
extern u8 RunCyle;				//��������
void KEY_Init(void);//��ʼ������
u8 Get_Key(u8 mode);//��ȡ������ֵ
void Key_Set(void);	//ͨ��������������
#endif


