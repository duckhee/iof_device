#ifndef __HW_USART_H__
#define __HW_USART_H__

#include "Hw.h"



#define GPIO_USART1            GPIOA
#define GPIO_USART1_Rx_Pin     GPIO_Pin_10
#define GPIO_USART1_Tx_Pin     GPIO_Pin_9


//usart enable
#define USART_ENABLE                         ((uint16_t)0x2000)
//word length
#define USART_WordLength_8b                  ((uint16_t)0x0000)
#define USART_WordLength_9b                  ((uint16_t)0x1000)
//wakeUp method
#define USART_WAKE                           ((uint16_t)0x0800)
//parity
#define USART_Parity_No                      ((uint16_t)0x0000)
#define USART_Parity_Even                    ((uint16_t)0x0400)
#define USART_Parity_Odd                     ((uint16_t)0x0600)

//stopbit
#define USART_StopBits_1                     ((uint16_t)0x0000)
#define USART_StopBits_0_5                   ((uint16_t)0x1000)
#define USART_StopBits_2                     ((uint16_t)0x2000)
#define USART_StopBits_1_5                   ((uint16_t)0x3000)
//usart mode
#define USART_Mode_Rx                        ((uint16_t)0x0004)
#define USART_Mode_Tx                        ((uint16_t)0x0008)
//hardwoar folow control
#define USART_HardwareFlowControl_None       ((uint16_t)0x0000)
#define USART_HardwareFlowControl_RTS        ((uint16_t)0x0100)
#define USART_HardwareFlowControl_CTS        ((uint16_t)0x0200)
#define USART_HardwareFlowControl_RTS_CTS    ((uint16_t)0x0300)

//stop clear mask
#define USART_STOP_BIT_CLEAR_MASK            ((uint16_t)0xCFFF)
//usart CR1 clear mask
#define USART_CR1_CLEAR_MASK                 ((uint16_t)0xE9F3)
//usart CR3 clear mask
#define USART_CR3_CLEAR_MASK                 ((uint16_t)0xFCFF)
/* USART OverSampling-8 Mask */
#define USART_OVER8_Set                      ((uint16_t)0x8000)  /* USART OVER8 mode Enable Mask */
#define USART_OVER8_Reset                    ((uint16_t)0x7FFF)  /* USART OVER8 mode Disable Mask */

#define USART_CR1_SET                        ((uint16_t)0x2000)
#define USART_CR1_RESET                      ((uint16_t)0xDFFF)

/**
  * @}
  */

/** @defgroup USART_Interrupt_definition
  * @{
  */

#define USART_IT_PE                          ((uint16_t)0x0028)
#define USART_IT_TXE                         ((uint16_t)0x0727)
#define USART_IT_TC                          ((uint16_t)0x0626)
#define USART_IT_RXNE                        ((uint16_t)0x0525)
#define USART_IT_IDLE                        ((uint16_t)0x0424)
#define USART_IT_LBD                         ((uint16_t)0x0846)
#define USART_IT_CTS                         ((uint16_t)0x096A)
#define USART_IT_ERR                         ((uint16_t)0x0060)
#define USART_IT_ORE                         ((uint16_t)0x0360)
#define USART_IT_NE                          ((uint16_t)0x0260)
#define USART_IT_FE                          ((uint16_t)0x0160)

#define IS_USART_CONFIG_IT(IT) (((IT) == USART_IT_PE) || ((IT) == USART_IT_TXE) || \
                               ((IT) == USART_IT_TC) || ((IT) == USART_IT_RXNE) || \
                               ((IT) == USART_IT_IDLE) || ((IT) == USART_IT_LBD) || \
                               ((IT) == USART_IT_CTS) || ((IT) == USART_IT_ERR))
#define IS_USART_GET_IT(IT) (((IT) == USART_IT_PE) || ((IT) == USART_IT_TXE) || \
                            ((IT) == USART_IT_TC) || ((IT) == USART_IT_RXNE) || \
                            ((IT) == USART_IT_IDLE) || ((IT) == USART_IT_LBD) || \
                            ((IT) == USART_IT_CTS) || ((IT) == USART_IT_ORE) || \
                            ((IT) == USART_IT_NE) || ((IT) == USART_IT_FE))
#define IS_USART_CLEAR_IT(IT) (((IT) == USART_IT_TC) || ((IT) == USART_IT_RXNE) || \
                               ((IT) == USART_IT_LBD) || ((IT) == USART_IT_CTS))

#ifdef HW_USART_LOCAL
#define HW_USART_DEF
#else
#define HW_USART_DEF                     extern
#endif

HW_USART_DEF void USART1_Init(void);
HW_USART_DEF void USART_Init(USART_TypeDef* USARTx, USART_InitTypeDef* USART_InitStruct);
HW_USART_DEF uint16_t USART_ReceiveData(USART_TypeDef* USARTx);
HW_USART_DEF void USART_SendData(USART_TypeDef* USARTx, uint16_t Data);
HW_USART_DEF FlagStatus USART_GetFlagStatus(USART_TypeDef* USARTx, uint16_t USART_FLAG);
HW_USART_DEF void USART_Start_Cmd(USART_TypeDef* USARTx, FunctionalState NewStatue);
HW_USART_DEF void USART_ClearITPendingBit(USART_TypeDef* USARTx, uint16_t USART_IT);

#endif