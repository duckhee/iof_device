#define HW_USART_LOCAL

#include "Hw_Usart.h"

HW_USART_DEF void USART1_Init(void);
HW_USART_DEF void USART_Init(USART_TypeDef* USARTx, USART_InitTypeDef* USART_InitStruct);
HW_USART_DEF uint16_t USART_ReceiveData(USART_TypeDef* USARTx);
HW_USART_DEF void USART_SendData(USART_TypeDef* USARTx, uint16_t Data);
HW_USART_DEF FlagStatus USART_GetFlagStatus(USART_TypeDef* USARTx, uint16_t USART_FLAG);
HW_USART_DEF void USART_Start_Cmd(USART_TypeDef* USARTx, FunctionalState NewStatue);
HW_USART_DEF void USART_ClearITPendingBit(USART_TypeDef* USARTx, uint16_t USART_IT);

HW_USART_DEF void USART1_Init(void)
{
    //APB2Enable(AFIO_ENABLE, ENABLE);
    //APB2Enable(IOPORT_A_ENABLE, ENABLE);
    //APB2Enable(USART1_ENABLE, ENABLE);
    
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_USART1_Tx_Pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIO_USART1, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_USART1_Rx_Pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIO_USART1, &GPIO_InitStructure);


    USART_InitTypeDef USART_InitStructure;
    /* USARTx configuration */
    /* USARTx configured as follow : 
    - BaudRate = 115200 baud
    - Word Length = 8bits
    - One Stop Bit
    - No parity
    - Hardware flow control disabled (RTS and CTS signals)
    - Receive and transmit enabled
    */
    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    USART_Init(USART1, &USART_InitStructure);

    USART1->CR1 |= USART_ENABLE;
}

HW_USART_DEF void USART_Init(USART_TypeDef* USARTx, USART_InitTypeDef* USART_InitStruct)
{
    uint32_t tmpreg = 0x00, apbclock = 0x00;
    uint32_t integerdivider = 0x00;
    uint32_t fractionaldivider = 0x00;
    uint32_t usartxbase = 0;
    //RCC Clock을 얻기 위해서 구조체 선언
    RCC_ClocksTypeDef RCC_ClocksStatus;
 /* The hardware flow control is available only for USART1, USART2 and USART3 */
  if (USART_InitStruct->USART_HardwareFlowControl != USART_HardwareFlowControl_None)
  {
    //assert param debug code here
  }

  usartxbase = (uint32_t)USARTx;

/*---------------------------- USART CR2 Configuration -----------------------*/
  tmpreg = USARTx->CR2;
  /* Clear STOP[13:12] bits */
  tmpreg &= USART_STOP_BIT_CLEAR_MASK;
  /* Configure the USART Stop Bits, Clock, CPOL, CPHA and LastBit ------------*/
  /* Set STOP[13:12] bits according to USART_StopBits value */
  tmpreg |= (uint32_t)USART_InitStruct->USART_StopBits;

  /* Write to USART CR2 */
  USARTx->CR2 = (uint16_t)tmpreg;

/*---------------------------- USART CR1 Configuration -----------------------*/
  tmpreg = USARTx->CR1;
  /* Clear M, PCE, PS, TE and RE bits */
  tmpreg &= USART_CR1_CLEAR_MASK;
  /* Configure the USART Word Length, Parity and mode ----------------------- */
  /* Set the M bits according to USART_WordLength value */
  /* Set PCE and PS bits according to USART_Parity value */
  /* Set TE and RE bits according to USART_Mode value */
  tmpreg |= (uint32_t)USART_InitStruct->USART_WordLength | USART_InitStruct->USART_Parity |
            USART_InitStruct->USART_Mode;
  /* Write to USART CR1 */
  USARTx->CR1 = (uint16_t)tmpreg;

/*---------------------------- USART CR3 Configuration -----------------------*/
  tmpreg = USARTx->CR3;
  /* Clear CTSE and RTSE bits */
  tmpreg &= USART_CR3_CLEAR_MASK;
  /* Configure the USART HFC -------------------------------------------------*/
  /* Set CTSE and RTSE bits according to USART_HardwareFlowControl value */
  tmpreg |= USART_InitStruct->USART_HardwareFlowControl;
  /* Write to USART CR3 */
  USARTx->CR3 = (uint16_t)tmpreg;

/*---------------------------- USART BRR Configuration -----------------------*/
  /* Configure the USART Baud Rate -------------------------------------------*/
  RCC_GetClocksFreq(&RCC_ClocksStatus);
  if (usartxbase == USART1_BASE)
  {
    apbclock = RCC_ClocksStatus.PCLK2_Frequency;
  }
  else
  {
    apbclock = RCC_ClocksStatus.PCLK1_Frequency;
  }

  /* Determine the integer part */
  if ((USARTx->CR1 & USART_OVER8_Set) != 0)
  {
    /* Integer part computing in case Oversampling mode is 8 Samples */
    integerdivider = ((25 * apbclock) / (2 * (USART_InitStruct->USART_BaudRate)));
  }
  else /* if ((USARTx->CR1 & CR1_OVER8_Set) == 0) */
  {
    /* Integer part computing in case Oversampling mode is 16 Samples */
    integerdivider = ((25 * apbclock) / (4 * (USART_InitStruct->USART_BaudRate)));
  }
  tmpreg = (integerdivider / 100) << 4;

  /* Determine the fractional part */
  fractionaldivider = integerdivider - (100 * (tmpreg >> 4));

  /* Implement the fractional part in the register */
  if ((USARTx->CR1 & USART_OVER8_Set) != 0)
  {
    tmpreg |= ((((fractionaldivider * 8) + 50) / 100)) & ((uint8_t)0x07);
  }
  else /* if ((USARTx->CR1 & CR1_OVER8_Set) == 0) */
  {
    tmpreg |= ((((fractionaldivider * 16) + 50) / 100)) & ((uint8_t)0x0F);
  }

  /* Write to USART BRR */
  USARTx->BRR = (uint16_t)tmpreg;
}


HW_USART_DEF void USART_SendData(USART_TypeDef* USARTx, uint16_t Data)
{
  /* Transmit Data */
  USARTx->DR = (Data & (uint16_t)0x01FF);
}

HW_USART_DEF uint16_t USART_ReceiveData(USART_TypeDef* USARTx)
{
  /* Receive Data */
  return (uint16_t)(USARTx->DR & (uint16_t)0x01FF);
}

HW_USART_DEF FlagStatus USART_GetFlagStatus(USART_TypeDef* USARTx, uint16_t USART_FLAG)
{
  FlagStatus bitstatus = RESET;
  
  if ((USARTx->SR & USART_FLAG) != (uint16_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  return bitstatus;
}

HW_USART_DEF void USART_Start_Cmd(USART_TypeDef* USARTx, FunctionalState NewStatue)
{
  if(NewStatue != DISABLE)
  {
    USARTx->CR1 |= USART_CR1_SET;
  }
  else
  {
    USARTx->CR1 &= USART_CR1_RESET;
  }
}

/**
  * @brief  Clears the USARTx's interrupt pending bits.
  * @param  USARTx: Select the USART or the UART peripheral.
  *   This parameter can be one of the following values:
  *   USART1, USART2, USART3, UART4 or UART5.
  * @param  USART_IT: specifies the interrupt pending bit to clear.
  *   This parameter can be one of the following values:
  *     @arg USART_IT_CTS:  CTS change interrupt (not available for UART4 and UART5)
  *     @arg USART_IT_LBD:  LIN Break detection interrupt
  *     @arg USART_IT_TC:   Transmission complete interrupt.
  *     @arg USART_IT_RXNE: Receive Data register not empty interrupt.
  *
  * @note
  *   - PE (Parity error), FE (Framing error), NE (Noise error), ORE (OverRun
  *     error) and IDLE (Idle line detected) pending bits are cleared by
  *     software sequence: a read operation to USART_SR register
  *     (USART_GetITStatus()) followed by a read operation to USART_DR register
  *     (USART_ReceiveData()).
  *   - RXNE pending bit can be also cleared by a read to the USART_DR register
  *     (USART_ReceiveData()).
  *   - TC pending bit can be also cleared by software sequence: a read
  *     operation to USART_SR register (USART_GetITStatus()) followed by a write
  *     operation to USART_DR register (USART_SendData()).
  *   - TXE pending bit is cleared only by a write to the USART_DR register
  *     (USART_SendData()).
  * @retval None
  */
 HW_USART_DEF void USART_ClearITPendingBit(USART_TypeDef* USARTx, uint16_t USART_IT)
{
  uint16_t bitpos = 0x00, itmask = 0x00;
  /* The CTS interrupt is not available for UART4 and UART5 */
  if (USART_IT == USART_IT_CTS)
  {
    assert_param(IS_USART_123_PERIPH(USARTx));
  }

  bitpos = USART_IT >> 0x08;
  itmask = ((uint16_t)0x01 << (uint16_t)bitpos);
  USARTx->SR = (uint16_t)~itmask;
}