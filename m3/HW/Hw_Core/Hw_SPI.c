#define HW_SPI_LOCAL

#include "Hw_SPI.h"



SPI_DEF void SPI_I2S_SendData(SPI_TypeDef* SPIx, uint16_t Data);
SPI_DEF uint16_t SPI_I2S_ReceiveData(SPI_TypeDef* SPIx);
SPI_DEF FlagStatus SPI_I2S_GetFlagStatus(SPI_TypeDef* SPIx, uint16_t SPI_I2S_FLAG);
SPI_DEF void SPI_I2S_ClearFlag(SPI_TypeDef* SPIx, uint16_t SPI_I2S_FLAG);
SPI_DEF ITStatus SPI_I2S_GetITStatus(SPI_TypeDef* SPIx, uint8_t SPI_I2S_IT);



/**
  * @brief  Transmits a Data through the SPIx/I2Sx peripheral.
  * @param  SPIx: where x can be
  *   - 1, 2 or 3 in SPI mode
  *   - 2 or 3 in I2S mode
  * @param  Data : Data to be transmitted.
  * @retval None
  */
SPI_DEF void SPI_I2S_SendData(SPI_TypeDef* SPIx, uint16_t Data)
{
    SPIx->DR = Data;
}

/**
  * @brief  Returns the most recent received data by the SPIx/I2Sx peripheral.
  * @param  SPIx: where x can be
  *   - 1, 2 or 3 in SPI mode
  *   - 2 or 3 in I2S mode
  * @retval The value of the received data.
  */
SPI_DEF uint16_t SPI_I2S_ReceiveData(SPI_TypeDef* SPIx)
{
    return Spix->DR;
}

/**
  * @brief  Checks whether the specified SPI/I2S flag is set or not.
  * @param  SPIx: where x can be
  *   - 1, 2 or 3 in SPI mode
  *   - 2 or 3 in I2S mode
  * @param  SPI_I2S_FLAG: specifies the SPI/I2S flag to check.
  *   This parameter can be one of the following values:
  *     @arg SPI_I2S_FLAG_TXE: Transmit buffer empty flag.
  *     @arg SPI_I2S_FLAG_RXNE: Receive buffer not empty flag.
  *     @arg SPI_I2S_FLAG_BSY: Busy flag.
  *     @arg SPI_I2S_FLAG_OVR: Overrun flag.
  *     @arg SPI_FLAG_MODF: Mode Fault flag.
  *     @arg SPI_FLAG_CRCERR: CRC Error flag.
  *     @arg I2S_FLAG_UDR: Underrun Error flag.
  *     @arg I2S_FLAG_CHSIDE: Channel Side flag.
  * @retval The new state of SPI_I2S_FLAG (SET or RESET).
  */
SPI_DEF FlagStatus SPI_I2S_GetFlagStatus(SPI_TypeDef* SPIx, uint16_t SPI_I2S_FLAG)
{
    FlagStatus bitStatus = RESET;
    /* Check the status of the specified SPI/I2S flag */
    if((SPIx->SR & SPI_I2S_FLAG) != (uint16_t)RESET)
    {
        bitStatus = SET;
    }
    else{
        bitStatus = RESET;
    }
    return bitStatus;
}

/**
  * @brief  Clears the SPIx CRC Error (CRCERR) flag.
  * @param  SPIx: where x can be
  *   - 1, 2 or 3 in SPI mode
  * @param  SPI_I2S_FLAG: specifies the SPI flag to clear.
  *   This function clears only CRCERR flag.
  * @note
  *   - OVR (OverRun error) flag is cleared by software sequence: a read
  *     operation to SPI_DR register (SPI_I2S_ReceiveData()) followed by a read
  *     operation to SPI_SR register (SPI_I2S_GetFlagStatus()).
  *   - UDR (UnderRun error) flag is cleared by a read operation to
  *     SPI_SR register (SPI_I2S_GetFlagStatus()).
  *   - MODF (Mode Fault) flag is cleared by software sequence: a read/write
  *     operation to SPI_SR register (SPI_I2S_GetFlagStatus()) followed by a
  *     write operation to SPI_CR1 register (SPI_Cmd() to enable the SPI).
  * @retval None
  */
SPI_DEF void SPI_I2S_ClearFlag(SPI_TypeDef* SPIx, uint16_t SPI_I2S_FLAG)
{
    /* Clear the selected SPI CRC Error (CRCERR) flag */
    SPIx->SR = (uint16_t)~SPI_I2S_FLAG;
}

/**
  * @brief  Checks whether the specified SPI/I2S interrupt has occurred or not.
  * @param  SPIx: where x can be
  *   - 1, 2 or 3 in SPI mode
  *   - 2 or 3 in I2S mode
  * @param  SPI_I2S_IT: specifies the SPI/I2S interrupt source to check.
  *   This parameter can be one of the following values:
  *     @arg SPI_I2S_IT_TXE: Transmit buffer empty interrupt.
  *     @arg SPI_I2S_IT_RXNE: Receive buffer not empty interrupt.
  *     @arg SPI_I2S_IT_OVR: Overrun interrupt.
  *     @arg SPI_IT_MODF: Mode Fault interrupt.
  *     @arg SPI_IT_CRCERR: CRC Error interrupt.
  *     @arg I2S_IT_UDR: Underrun Error interrupt.
  * @retval The new state of SPI_I2S_IT (SET or RESET).
  */
SPI_DEF ITStatus SPI_I2S_GetITStatus(SPI_TypeDef* SPIx, uint8_t SPI_I2S_IT)
{
    ITStatus bitStatus = RESET;
    uint16_t itpos = 0, itmask = 0, enableStatus = 0;
    /* Get the SPI/I2S IT index */
    itpos = 0x01 << (SPI_I2S_IT & 0x0F);
    /* Get the SPI/I2S IT mask */
    itmaks = SPI_I2S_IT >> 4;
    /* Set the IT mask */
    itmaks = 0x1 << itmask;
    /* Get the SPI_I2S_IT enable bit status */
    enableStatus = (SPIx->CR2 & itmask);
    /* Check the status of the specified SPI/I2S interrupt */
    if(((SPIx->SR & itpos) != (uint16_t)RESET) && enableStatus)
    {
        /* SPI_I2S_IT is set */
        bitStatus = SET;
    }
    else{
        /* SPI_I2S_IT is reset */
        bitStatus = RESET;
    }
    /* Return the SPI_I2S_IT status */
    return bitStatus;
}