#ifndef __HW_SPI_H__
#define __HW_SPI_H__


#include "Hw.h"




#ifdef HW_SPI_LOCAL
#define SPI_DEF
#else
#define SPI_DEF               extern
#endif

SPI_DEF void SPI_I2S_SendData(SPI_TypeDef* SPIx, uint16_t Data);
SPI_DEF uint16_t SPI_I2S_ReceiveData(SPI_TypeDef* SPIx);
SPI_DEF FlagStatus SPI_I2S_GetFlagStatus(SPI_TypeDef* SPIx, uint16_t SPI_I2S_FLAG);
SPI_DEF void SPI_I2S_ClearFlag(SPI_TypeDef* SPIx, uint16_t SPI_I2S_FLAG);
SPI_DEF ITStatus SPI_I2S_GetITStatus(SPI_TypeDef* SPIx, uint8_t SPI_I2S_IT);


#endif