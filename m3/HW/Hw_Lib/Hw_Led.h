#ifndef __HW_LED_H__
#define __HW_LED_H__

#include "Hw.h"

#define GPIO_LED             GPIOB

#define GPIO_LED1_PIN        GPIO_Pin_9 /* RED */
#define GPIO_LED2_PIN        GPIO_Pin_5 /* YELLOW */ 
#define GPIO_LED3_PIN        GPIO_Pin_8 /* BLUE */

#ifdef LED_DRIVER_LOCAL
#define LED_DRIVER_DEF
#else
#define LED_DRIVER_DEF            extern
#endif

LED_DRIVER_DEF void Led_Init(void);
LED_DRIVER_DEF void Led_AllOn(void);
LED_DRIVER_DEF void Led_AllOff(void);
LED_DRIVER_DEF void Red_On(void);
LED_DRIVER_DEF void Red_Off(void);
LED_DRIVER_DEF void Yellow_On(void);
LED_DRIVER_DEF void Yellow_Off(void);
LED_DRIVER_DEF void Blue_On(void);
LED_DRIVER_DEF void Blue_Off(void);
LED_DRIVER_DEF void Test_LED(void);
LED_DRIVER_DEF void Test_Check(void);
LED_DRIVER_DEF void LED_MULT(uint32_t count);

#endif