#ifndef DIGITALLED_H_
#define DIGITALLED_H_
#include "sys.h"
#define Bit1	PEout(1)			//第一位数码管
#define Bit2	PEout(2)			//第二位数码管
#define Bit3	PAout(3)			//第三位数码管
#define Bit4	PAout(4)			//第四位数码管
#define Bit5	PDout(9)			//第五位数码管
#define Bit6	PDout(10)			//第六位数码管
#define Bit7	PDout(14)			//第七位数码管
#define Bit8	PDout(15)			//第八位数码管
void DigitalLED_Duan(u8 data);	//数码管段码
void DigitalLED_Init(void);			//初始化数码管
extern u8 SEG_CODE[];						//BCD码
extern u8 Array[];							//个位和十位显示的值
void DigitalLED_Fen(u8 num);		//分解两位数
#endif

