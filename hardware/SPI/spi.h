#ifndef SPI_H_
#define SPI_H_
#include "sys.h"
void SPI2_Init(void);//��ʼ��STM32 SPI2ģ��
u8 SPI2_ReadWriteByte(u8 TxData);//ͨ��SPI���ͻ��������
void SPI2_SetSpeed(u8 SPI_BaudRatePrescaler);//SPI2�ٶ�����
#endif

