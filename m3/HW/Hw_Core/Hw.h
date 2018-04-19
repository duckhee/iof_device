#ifndef __HW_H__
#define __HW_H__

//local library add
#include<stdint.h>
//core add
#include "Hw_Reg.h"
#include "Hw_Rcc.h"
#include "Hw_Usart.h"
#include "Hw_ADC.h"
#include "Hw_Flash.h"
#include "Hw_GPIO.h"
#include "Hw_SysTick.h"
#include "Hw_EXTI.h"
#include "Hw_IRQ.h"
#include "Hw_NVIC.h"
#include "Hw_TIM.h"
#include "Hw_ADC.h"
#include "Hw_DMA.h"
#include "Hw_SPI.h"

//driver add
#include "Hw_Led.h"
#include "Hw_Key.h"
//lib add
#include "Ld_printf.h"
#include "Util.h"

#ifdef HW_LOCAL
#define HW_DEF
#else
#define HW_DEF           extern
#endif


HW_DEF void HW_Init(void);

#endif