#define HW_TIM_LOCAL

#include "Hw_TIM.h"

HW_TIM_DEF void TIM_ClearITPendingBit(TIM_TypeDef* TIMx, uint16_t TIM_IT);
HW_TIM_DEF void TIM_TimeBaseInit(TIM_TypeDef* TIMx, TIM_TimeBaseInitTypeDef* TIM_TimeBaseInitStruct);
HW_TIM_DEF void TIM_Start_Cmd(TIM_TypeDef* TIMx, FunctionalState NewState);
HW_TIM_DEF void TIM_Configuration(void);
HW_TIM_DEF void TIM_PrescalerConfig(TIM_TypeDef* TIMx, uint16_t prescaler, uint16_t TIM_PscReloadMode);
HW_TIM_DEF void TIM_ClearFlag(TIM_TypeDef* TIMx, uint16_t TIM_FLAG);
HW_TIM_DEF void TIM_ITConfig(TIM_TypeDef* TIMx, uint16_t TIM_IT, FunctionalState NewState);


HW_TIM_DEF void TIM_Configuration(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

    /* TIM2 configuration */
    TIM_TimeBaseStructure.TIM_Period = 0x4AF;          
    TIM_TimeBaseStructure.TIM_Prescaler = 0xEA5F;       
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;    
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x0000;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
    /* TIM3 configuration */
    TIM_TimeBaseStructure.TIM_Period = 0x95F;
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
    /* TIM4 configuration */
    TIM_TimeBaseStructure.TIM_Period = 0xE0F;
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
    /* TIM2 enable counter */
    TIM_Start_Cmd(TIM2, ENABLE);
    /* TIM3 enable counter */
    TIM_Start_Cmd(TIM3, ENABLE);
    /* TIM4 enable counter */
    TIM_Start_Cmd(TIM4, ENABLE);
    /* Immediate load of TIM2 Precaler value */
    TIM_PrescalerConfig(TIM2, 0xEA5F, TIM_PSCReloadMode_Immediate);
    /* Immediate load of TIM3 Precaler value */
    TIM_PrescalerConfig(TIM3, 0xEA5F, TIM_PSCReloadMode_Immediate);
    /* Immediate load of TIM4 Precaler value */
    TIM_PrescalerConfig(TIM4, 0xEA5F, TIM_PSCReloadMode_Immediate);
    /* Clear TIM2 update pending flag */
    TIM_ClearFlag(TIM2, TIM_FLAG_Update);
    /* Clear TIM3 update pending flag */
    TIM_ClearFlag(TIM3, TIM_FLAG_Update);
    /* Clear TIM4 update pending flag */
    TIM_ClearFlag(TIM4, TIM_FLAG_Update);
    /* Enable TIM2 Update interrupt */
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
    /* Enable TIM3 Update interrupt */
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
    /* Enable TIM4 Update interrupt */
    TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
    
}

/**
  * @brief  Clears the TIMx's interrupt pending bits.
  * @param  TIMx: where x can be 1 to 17 to select the TIM peripheral.
  * @param  TIM_IT: specifies the pending bit to clear.
  *   This parameter can be any combination of the following values:
  *     @arg TIM_IT_Update: TIM1 update Interrupt source
  *     @arg TIM_IT_CC1: TIM Capture Compare 1 Interrupt source
  *     @arg TIM_IT_CC2: TIM Capture Compare 2 Interrupt source
  *     @arg TIM_IT_CC3: TIM Capture Compare 3 Interrupt source
  *     @arg TIM_IT_CC4: TIM Capture Compare 4 Interrupt source
  *     @arg TIM_IT_COM: TIM Commutation Interrupt source
  *     @arg TIM_IT_Trigger: TIM Trigger Interrupt source
  *     @arg TIM_IT_Break: TIM Break Interrupt source
  * @note
  *   - TIM6 and TIM7 can generate only an update interrupt.
  *   - TIM9, TIM12 and TIM15 can have only TIM_IT_Update, TIM_IT_CC1,
  *      TIM_IT_CC2 or TIM_IT_Trigger.
  *   - TIM10, TIM11, TIM13, TIM14, TIM16 and TIM17 can have TIM_IT_Update or TIM_IT_CC1.
  *   - TIM_IT_Break is used only with TIM1, TIM8 and TIM15.
  *   - TIM_IT_COM is used only with TIM1, TIM8, TIM15, TIM16 and TIM17.
  * @retval None
  */
HW_TIM_DEF void TIM_ClearITPendingBit(TIM_TypeDef* TIMx, uint16_t TIM_IT)
{
    /* Clear the IT pending Bit */
    TIMx->SR = (uint16_t)~TIM_IT;
}

/**
  * @brief  Initializes the TIMx Time Base Unit peripheral according to
  *         the specified parameters in the TIM_TimeBaseInitStruct.
  * @param  TIMx: where x can be 1 to 17 to select the TIM peripheral.
  * @param  TIM_TimeBaseInitStruct: pointer to a TIM_TimeBaseInitTypeDef
  *         structure that contains the configuration information for the
  *         specified TIM peripheral.
  * @retval None
  */
HW_TIM_DEF void TIM_TimeBaseInit(TIM_TypeDef* TIMx, TIM_TimeBaseInitTypeDef* TIM_TimeBaseInitStruct)
{
    TIMx->CR1 &= TIM_CR1_CKD_Mask & TIM_CR1_CounterMode_Mask;
    TIMx->CR1 |= (uint32_t)TIM_TimeBaseInitStruct->TIM_ClockDivision | TIM_TimeBaseInitStruct->TIM_CounterMode;
    /* Set the Autoreload value */
    TIMx->ARR = TIM_TimeBaseInitStruct->TIM_Period;
    /* Set the Prescaler value */
    TIMx->PSC = TIM_TimeBaseInitStruct->TIM_Prescaler;
    if ((((uint32_t) TIMx) == TIM1_BASE) || (((uint32_t) TIMx) == TIM8_BASE))
    {
        /* Set the Repetition Counter value */
        TIMx->RCR = TIM_TimeBaseInitStruct->TIM_RepetitionCounter;
    }
    /* Generate an update event to reload the Prescaler value immediatly */
    TIMx->EGR = TIM_PSCReloadMode_Immediate;          

}

/**
  * @brief  Fills each TIM_TimeBaseInitStruct member with its default value.
  * @param  TIM_TimeBaseInitStruct : pointer to a TIM_TimeBaseInitTypeDef
  *         structure which will be initialized.
  * @retval None
  */
HW_TIM_DEF void TIM_TimeBaseStructInit(TIM_TimeBaseInitTypeDef* TIM_TimeBaseInitStruct)
{
  /* Set the default configuration */
  TIM_TimeBaseInitStruct->TIM_Period = 0xFFFF;
  TIM_TimeBaseInitStruct->TIM_Prescaler = 0x0000;
  TIM_TimeBaseInitStruct->TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseInitStruct->TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInitStruct->TIM_RepetitionCounter = 0x0000;
}


HW_TIM_DEF void TIM_Start_Cmd(TIM_TypeDef* TIMx, FunctionalState NewState)
{
    if (NewState != DISABLE)
    {
        /* Enable the TIM Counter */
        TIMx->CR1 |= TIM_CR1_CEN_Set;
    }
    else
    {
        /* Disable the TIM Counter */
        TIMx->CR1 &= (uint16_t)(~((uint16_t)TIM_CR1_CEN_Set));
    }
}

HW_TIM_DEF void TIM_PrescalerConfig(TIM_TypeDef* TIMx, uint16_t prescaler, uint16_t TIM_PscReloadMode)
{
    /* Set the Prescaler value */
    TIMx->PSC = prescaler;
    /* Set or reset the UG Bit */
    TIMx->EGR = TIM_PscReloadMode;
}

HW_TIM_DEF void TIM_ClearFlag(TIM_TypeDef* TIMx, uint16_t TIM_FLAG)
{
    /* Clear the flags */
    TIMx->SR = (uint16_t)~TIM_FLAG;
}

HW_TIM_DEF void TIM_ITConfig(TIM_TypeDef* TIMx, uint16_t TIM_IT, FunctionalState NewState)
{
    if(NewState != DISABLE)
    {
        /* Enable the Interrupt sources */
        TIMx->DIER |= TIM_IT;
    }
    else
    {
        /* Disable the Interrupt sources */
        TIMx->DIER &= (uint16_t)~TIM_IT;
    }
}