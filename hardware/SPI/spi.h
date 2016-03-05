#ifndef SPI_H_
#define SPI_H_
#include "sys.h"
void SPI2_Init(void);//初始化STM32 SPI2模块
u8 SPI2_ReadWriteByte(u8 TxData);//通过SPI发送或接受数据
void SPI2_SetSpeed(u8 SPI_BaudRatePrescaler);//SPI2速度设置
#endif

