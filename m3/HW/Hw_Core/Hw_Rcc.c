#define HW_RCC_LOCAL

#include "Hw_Rcc.h"

HW_RCC_DEF void HSI_Init(void);
HW_RCC_DEF void HSE_Init(void);
HW_RCC_DEF void APB2Enable(uint32_t RCC_APB2Periph, FunctionalState NewState);
HW_RCC_DEF void APB1Enable(uint32_t RCC_APB1Periph, FunctionalState NewState);
HW_RCC_DEF void APBEnable(uint32_t RCC_APBPeriph, FunctionalState NewState);
HW_RCC_DEF void RCC_GetClocksFreq(RCC_ClocksTypeDef* RCC_Clocks);

__IO uint32_t StartUpCounter = 0;

//sysclock 36MHz
HW_RCC_DEF void HSI_Init(void)
{
    __IO uint32_t HSIStatus = 0;
    RCC->CR |= ((uint32_t)RCC_CR_HSION);
    do
    {
        HSIStatus = RCC->CR & RCC_CR_HSIRDY;
        StartUpCounter++;
    }while((HSIStatus == 0) && (StartUpCounter == 0x500));
    //flash access delay 24Mhz < SYSCLK <= 48Mhz
    FLASH->ACR |= FLASH_ACR_LATENCY_1;
    //PLL setting
    /* HCLK = SYSTICK */
    RCC->CFGR |= (uint32_t)SYSCLK_NOT_DIVIDED;
    /* PCLK2 = HCLK */
    RCC->CFGR |= (uint32_t)APB2_PCLK2_NOT_DIVIDED;
    /* PCLK1 = HCLK */
    RCC->CFGR |= (uint32_t)APB1_PCLK1_DIVIDED2;
    /* ADC = set div 4 */
    RCC->CFGR |= (uint32_t)ADCPRE_PLCK2_DIVIDED4;
    /* PLL ON */
    RCC->CR |= RCC_CR_PLLON;
    /* Wait till PLL is ready */
    while((RCC->CR & RCC_CR_PLLRDY) == 0)
    {
        ;
    }
    /* select PLL as system clock source */
    RCC->CFGR |= (uint32_t)SW_PLL_SYSCLOCK;
    /* Wailt til PLL is used as system clock source */
    while((RCC->CFGR & (uint32_t)RCC_SWS_MASK) != ((uint32_t)0x08))
    {
        ; //조건을 만족하면 여기 pll 준비가 안되어 있다는 것
    }
}


HW_RCC_DEF void HSE_Init(void)
{
    __IO uint32_t HSEStatus = 0;
    RCC->CR |= ((uint32_t)RCC_CR_HSEON);
    do
    {
        HSEStatus = RCC->CR & RCC_CR_HSERDY;
        StartUpCounter++;
    }while((HSEStatus == 0) && (StartUpCounter == 0x500));
    //flash access delay 48MHz < SYSCLOCK <=72MHz
    FLASH->ACR |= FLASH_ACR_LATENCY_2;
     //PLL setting
    /* HCLK = SYSTICK */
    RCC->CFGR |= (uint32_t)SYSCLK_NOT_DIVIDED;
    /* PCLK2 = HCLK */
    RCC->CFGR |= (uint32_t)APB2_PCLK2_NOT_DIVIDED;
    /* PCLK1 = HCLK */
    RCC->CFGR |= (uint32_t)APB1_PCLK1_DIVIDED2;
    /* ADC = set div 6 */
    RCC->CFGR |= (uint32_t)ADCPRE_PLCK2_DIVIDED6;
    /* PLL configuration : PLLCLK = HSE * 6 = 72MHz */
    RCC->CFGR |= (uint32_t)(PLLSRC_HSE | PLL_INPUT_MULT6);
    /* PLL ON */
    RCC->CR |= RCC_CR_PLLON;
    /* Wait till PLL is ready */
    while((RCC->CR & RCC_CR_PLLRDY) == 0)
    {
        ;
    }
    /* select PLL as system clock source */
    RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
    RCC->CFGR |= (uint32_t)SW_PLL_SYSCLOCK;
    /* Wailt til PLL is used as system clock source */
    while((RCC->CFGR & (uint32_t)RCC_SWS_MASK) != ((uint32_t)0x08))
    {
        ; //조건을 만족하면 여기 pll 준비가 안되어 있다는 것
    }
}
HW_RCC_DEF void APB2Enable(uint32_t RCC_APB2Periph, FunctionalState NewState)
{
    if(NewState != DISABLE)
    {
        RCC->APB2ENR |= RCC_APB2Periph;
    }
    else
    {
        RCC->APB2ENR &= ~RCC_APB2Periph;
    }
}

HW_RCC_DEF void APB1Enable(uint32_t RCC_APB1Periph, FunctionalState NewState)
{
    if(NewState != DISABLE)
    {
        RCC->APB1ENR |= RCC_APB1Periph;
    }
    else
    {
        RCC->APB1ENR &= ~RCC_APB1Periph;
    }
}

HW_RCC_DEF void APBEnable(uint32_t RCC_APBPeriph, FunctionalState NewState)
{
    if(NewState != DISABLE)
    {
        RCC->APBENR |= RCC_APBPeriph;
    }
    else
    {
        RCC->APBENR &= ~RCC_APBPeriph;
    }
}


HW_RCC_DEF void RCC_GetClocksFreq(RCC_ClocksTypeDef* RCC_Clocks)
{
    uint32_t tmp = 0, pllmull = 0, pllsource = 0, presc = 0;
    
  /* Get SYSCLK source -------------------------------------------------------*/
  tmp = RCC->CFGR & RCC_SWS_MASK;
  switch (tmp)
  {
    case 0x00:  /* HSI used as system clock */
      RCC_Clocks->SYSCLK_Frequency = RCC_HSI_Value;
      break;

    case 0x04:  /* HSE used as system clock */
      RCC_Clocks->SYSCLK_Frequency = RCC_HSE_Value;
      break;

    case 0x08:  /* PLL used as system clock */
      /* Get PLL clock source and multiplication factor ----------------------*/
      pllmull = RCC->CFGR & RCC_PLLMUL_MASK;
      pllsource = RCC->CFGR & RCC_PLLSRC_MASK;
      pllmull = ( pllmull >> 18) + 2;
      if (pllsource == 0x00)
      {/* HSI oscillator clock divided by 2 selected as PLL clock entry */
        RCC_Clocks->SYSCLK_Frequency = (RCC_HSI_Value >> 1) * pllmull;
        
      }
      else
      {/* HSE selected as PLL clock entry */
        if ((RCC->CFGR & RCC_PLLXTPRE_MASK) != (uint32_t)RESET)
        {/* HSE oscillator clock divided by 2 */
          RCC_Clocks->SYSCLK_Frequency = (RCC_HSE_Value >> 1) * pllmull;
        }
        else
        {
          RCC_Clocks->SYSCLK_Frequency = RCC_HSE_Value * pllmull;
        }
      }
      break;

    default:
      RCC_Clocks->SYSCLK_Frequency = RCC_HSI_Value;
      break;
  }

  /* Compute HCLK, PCLK1, PCLK2 and ADCCLK clocks frequencies ----------------*/
  /* Get HCLK prescaler */
  tmp = RCC->CFGR & RCC_HPRE_SET_MASK;
  tmp = tmp >> 4;
  presc = APBAHBPrescTable[tmp];
  /* HCLK clock frequency */
  RCC_Clocks->HCLK_Frequency = RCC_Clocks->SYSCLK_Frequency >> presc;

  /* Get PCLK1 prescaler */
  tmp = RCC->CFGR & RCC_PPRE1_SET_MASK;
  tmp = tmp >> 8;
  presc = APBAHBPrescTable[tmp];
  /* PCLK1 clock frequency */
  RCC_Clocks->PCLK1_Frequency = RCC_Clocks->HCLK_Frequency >> presc;
  
  /* Get PCLK2 prescaler */
  tmp = RCC->CFGR & RCC_PPRE2_SET_MASK;
  tmp = tmp >> 11;
  presc = APBAHBPrescTable[tmp];
  /* PCLK2 clock frequency */
  RCC_Clocks->PCLK2_Frequency = RCC_Clocks->HCLK_Frequency >> presc;
  
  /* Get ADCCLK prescaler */
  tmp = RCC->CFGR & RCC_ADC_PRE_SET_MASK;
  tmp = tmp >> 14;
  presc = ADCPrescTable[tmp];
  /* ADCCLK clock frequency */
  RCC_Clocks->ADCCLK_Frequency = RCC_Clocks->PCLK2_Frequency / presc;

}