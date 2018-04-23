<<<<<<< HEAD
#define GS1_LOCAl

#include "gs1.h"
=======
#define GS1_LOCAL

#include "gs1.h"

GS1_DEF void GS1_Init(void);
//get usrat queue data
HW_USART_DEF void USART_GetData(void);
HW_USART_DEF void USART_PutData(uint16_t uData);
HW_USART_DEF void USART_InitQueue(void);
HW_USART_DEF void USART_AddQueue(uint16_t uData);
HW_USART_DEF void USART_ProcessQueue(void);



GS1_DEF void GS1_Init(void)
{
    
}



//get usrat queue data
HW_USART_DEF void USART_GetData(void)
{
  uint16_t uData;
  while(!USART_GetFlagStatus(USART2, USART_FLAG_RXNE));
  uData = USART_ReceiveData(USART2);
  return uData;
}

HW_USART_DEF void USART_PutData(uint16_t uData)
{
  while(!USART_GetFlagStatus(USART2, USART_FLAG_TXE));
  USART_SendData(USART2, uData);
}
HW_USART_DEF void USART_InitQueue(void)
{
  getUartQueue.uHeadIndex = 0;
  getUartQueue.uTailIndex = 0;
}

HW_USART_DEF void USART_AddQueue(uint16_t uData)
{
  getUartQueue.uHeadIndex = (getUartQueue.uHeadIndex + 1) & USART_QUEUE_BUF_MASK;
  getUartQueue.uBuf[getUartQueue.uHeadIndex] = uData;
}

HW_USART_DEF void USART_ProcessQueue(void)
{
  while(getUartQueue.uHeadIndex != getUartQueue.uTailIndex){
    getUartQueue.uTailIndex = (getUartQueue.uTailIndex + 1) & USART_QUEUE_BUF_MASK;
    USART_PutData(getUartQueue.uBuf[getUartQueue.uTailIndex]);
  }  
}

>>>>>>> merge_branch
