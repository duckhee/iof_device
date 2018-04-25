#ifndef __HW_EXTI_H__
#define __HW_EXTI_H__

#include "Hw.h"

#define EXTI_LINE0       ((uint32_t)0x00001)  /*!< External interrupt line 0 */
#define EXTI_LINE1       ((uint32_t)0x00002)  /*!< External interrupt line 1 */
#define EXTI_LINE2       ((uint32_t)0x00004)  /*!< External interrupt line 2 */
#define EXTI_LINE3       ((uint32_t)0x00008)  /*!< External interrupt line 3 */
#define EXTI_LINE4       ((uint32_t)0x00010)  /*!< External interrupt line 4 */
#define EXTI_LINE5       ((uint32_t)0x00020)  /*!< External interrupt line 5 */
#define EXTI_LINE6       ((uint32_t)0x00040)  /*!< External interrupt line 6 */
#define EXTI_LINE7       ((uint32_t)0x00080)  /*!< External interrupt line 7 */
#define EXTI_LINE8       ((uint32_t)0x00100)  /*!< External interrupt line 8 */
#define EXTI_LINE9       ((uint32_t)0x00200)  /*!< External interrupt line 9 */
#define EXTI_LINE10      ((uint32_t)0x00400)  /*!< External interrupt line 10 */
#define EXTI_LINE11      ((uint32_t)0x00800)  /*!< External interrupt line 11 */
#define EXTI_LINE12      ((uint32_t)0x01000)  /*!< External interrupt line 12 */
#define EXTI_LINE13      ((uint32_t)0x02000)  /*!< External interrupt line 13 */
#define EXTI_LINE14      ((uint32_t)0x04000)  /*!< External interrupt line 14 */
#define EXTI_LINE15      ((uint32_t)0x08000)  /*!< External interrupt line 15 */
#define EXTI_LINE16      ((uint32_t)0x10000)  /*!< External interrupt line 16 Connected to the PVD Output */
#define EXTI_LINE17      ((uint32_t)0x20000)  /*!< External interrupt line 17 Connected to the RTC Alarm event */
#define EXTI_LINE18      ((uint32_t)0x40000)  /*!< External interrupt line 18 Connected to the USB Device/USB OTG FS
                                                   Wakeup from suspend event */
#define EXTI_LINE19      ((uint32_t)0x80000)  /*!< External interrupt line 19 Connected to the Ethernet Wakeup event */ 

#define GPIO_EXTI_Line_KEY1        EXTI_LINE0
#define GPIO_EXTI_Line_KEY2        EXTI_LINE1

#define GPIO_PORTSOURCE_KEY        GPIO_PortSourceGPIOA
#define GPIO_PINSOURCE_KEY1        GPIO_PinSource0
#define GPIO_PINSOURCE_KEY2        GPIO_PinSource1


#ifdef HW_EXTI_LOCAL
#define HW_EXTI_DEF
#else
#define HW_EXTI_DEF                     extern
#endif

HW_EXTI_DEF ITStatus EXTI_GetITStatus(uint32_t EXTI_Line);
HW_EXTI_DEF void EXTI_ClearITPendingBit(uint32_t EXTI_Line);
HW_EXTI_DEF void EXTI_Configuration(void);
HW_EXTI_DEF void EXTI_Init(EXTI_InitTypeDef* EXTI_InitStruct);
HW_EXTI_DEF void GPIO_EXTILineConfig(uint8_t GPIO_PortSource, uint8_t GPIO_PinSource);


#endif