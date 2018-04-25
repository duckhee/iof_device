#ifndef __GS1_H__
#define __GS1_H__

#include "Ap.h"

#ifdef GS1_LOCAL
#define GS1_DEF
#else
#define GS1_DEF                  extern
#endif

/* struct data buffer */
#define USART_QUEUE_BUF_SIZE 100//(2*2)
#define USART_QUEUE_BUF_MASK 99//(USART_QUEUE_BUF_SIZE-1)

typedef struct
{
    uint16_t uBuf[USART_QUEUE_BUF_SIZE];
    uint16_t uHeadIndex;
    uint16_t uTailIndex;
} getUartQueue;


GS1_DEF void GS1_Init(void);
//get usrat queue data
HW_USART_DEF void USART_GetData(void);
HW_USART_DEF void USART_PutData(uint16_t uData);
HW_USART_DEF void USART_InitQueue(void);
HW_USART_DEF void USART_AddQueue(uint16_t uData);
HW_USART_DEF void USART_ProcessQueue(void);




#endif