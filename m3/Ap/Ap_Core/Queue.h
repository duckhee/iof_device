#ifndef __QUEUE_H__
#define __QUEUE_H__

#include "Ap.h"


#define QUEUE_MAX        100

#ifdef QUEUE_LOCAL
#define QUEUE_DEF
#else
#define QUEUE_DEF            extern
#endif

QUEUE_DEF void Uart3_EnQueue(uint16_t);
QUEUE_DEF void u3_increase_point_value(uint32_t *);
QUEUE_DEF uint16_t Uart3_DeQueue(void);
QUEUE_DEF BitAction Uart3_Is_Empty(void);

#endif