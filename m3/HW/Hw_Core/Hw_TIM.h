#ifndef __HW_TIM_H__
#define __HW_TIM_H__

#include "Hw.h"

/* TIM FLAG */
#define TIM_FLAG_Update                    ((uint16_t)0x0001)
/* TIM RELOAD MODE */
#define TIM_PSCReloadMode_Update           ((uint16_t)0x0000)
#define TIM_PSCReloadMode_Immediate        ((uint16_t)0x0001)
/* TIM CLOCK DIVISION */
#define TIM_CKD_DIV1                       ((uint16_t)0x0000)
#define TIM_CKD_DIV2                       ((uint16_t)0x0100)
#define TIM_CKD_DIV4                       ((uint16_t)0x0200)
/* TIM COUNTER MODE */
#define TIM_CounterMode_Up                 ((uint16_t)0x0000)
#define TIM_CounterMode_Down               ((uint16_t)0x0010)
#define TIM_CounterMode_CenterAligned1     ((uint16_t)0x0020)
#define TIM_CounterMode_CenterAligned2     ((uint16_t)0x0040)
#define TIM_CounterMode_CenterAligned3     ((uint16_t)0x0060)

#define TIM_IT_Update                      ((uint16_t)0x0001)
#define TIM_IT_CC1                         ((uint16_t)0x0002)
#define TIM_IT_CC2                         ((uint16_t)0x0004)
#define TIM_IT_CC3                         ((uint16_t)0x0008)
#define TIM_IT_CC4                         ((uint16_t)0x0010)
#define TIM_IT_COM                         ((uint16_t)0x0020)
#define TIM_IT_Trigger                     ((uint16_t)0x0040)
#define TIM_IT_Break                       ((uint16_t)0x0080)
#define TIM_PSCReloadMode_Update           ((uint16_t)0x0000)
#define TIM_PSCReloadMode_Immediate        ((uint16_t)0x0001)
/* TIM register bit mask */
#define TIM_CR1_CEN_Set                    ((uint16_t)0x0001)
#define TIM_CR1_CEN_Reset                  ((uint16_t)0x03FE)
#define TIM_CR1_CKD_Mask                   ((uint16_t)0x00FF)
#define TIM_CR1_CounterMode_Mask           ((uint16_t)0x038F)

#ifdef HW_TIM_LOCAL
#define HW_TIM_DEF
#else
#define HW_TIM_DEF            extern
#endif

HW_TIM_DEF void TIM_ClearITPendingBit(TIM_TypeDef* TIMx, uint16_t TIM_IT);
HW_TIM_DEF void TIM_TimeBaseInit(TIM_TypeDef* TIMx, TIM_TimeBaseInitTypeDef* TIM_TimeBaseInitStruct);
HW_TIM_DEF void TIM_Start_Cmd(TIM_TypeDef* TIMx, FunctionalState NewState);
HW_TIM_DEF void TIM_Configuration(void);
HW_TIM_DEF void TIM_PrescalerConfig(TIM_TypeDef* TIMx, uint16_t prescaler, uint16_t TIM_PscReloadMode);
HW_TIM_DEF void TIM_ClearFlag(TIM_TypeDef* TIMx, uint16_t TIM_FLAG);
HW_TIM_DEF void TIM_ITConfig(TIM_TypeDef* TIMx, uint16_t TIM_IT, FunctionalState NewState);
HW_TIM_DEF void TIM_TimeBaseStructInit(TIM_TimeBaseInitTypeDef* TIM_TimeBaseInitStruct);



#endif