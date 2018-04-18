#ifndef __HW_KEY_H__
#define __HW_KEY_H__

#include "Hw.h"

#define GPIO_KEY             GPIOA

#define GPIO_KEY1_PIN        GPIO_Pin_0 /* LEFT_WKUP */
#define GPIO_KEY2_PIN        GPIO_Pin_1 /* RIGHT_USER */

#ifdef HW_KEY_LOCAL
#define HW_KEY_DEF
#else
#define HW_KEY_DEF         extern
#endif

HW_KEY_DEF void Key_Init(void);
HW_KEY_DEF void Key_Test(void);

#endif