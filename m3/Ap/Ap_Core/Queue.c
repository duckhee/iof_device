#define QUEUE_LOCAL

#include "Queue.h"


uint16_t u3_rx_buffer[QUEUE_MAX];
uint32_t u3_rx_point_head = 0;
uint32_t u3_rx_point_tail = 0;

QUEUE_DEF void Uart3_EnQueue(uint16_t);
QUEUE_DEF void u3_increase_point_value(uint32_t *);
QUEUE_DEF uint16_t Uart3_DeQueue(void);
QUEUE_DEF BitAction Uart3_Is_Empty(void);

//save data queue
QUEUE_DEF void Uart3_EnQueue(uint16_t data)
{
    u3_rx_buffer[u3_rx_point_head] = data;
    u3_increase_point_value(&u3_rx_point_head);
}

//incrate pointer
QUEUE_DEF void u3_increase_point_value(uint32_t *data_p)
{
    (*data_p) ++;
    if(QUEUE_MAX == (*data_p))
    {
        (*data_p) = 0;
    }
}

//get data queue
QUEUE_DEF uint16_t Uart3_DeQueue(void)
{
    uint16_t retVal = u3_rx_buffer[u3_rx_point_tail];
    u3_increase_point_value(&u3_rx_point_tail);
    return retVal;
}

//flag check empty
QUEUE_DEF BitAction Uart3_Is_Empty(void)
{
    if(u3_rx_point_head == u3_rx_point_tail)
    {
        return SET;
    }
    return RESET;
}
