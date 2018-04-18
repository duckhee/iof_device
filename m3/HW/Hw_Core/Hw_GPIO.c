#define HW_GPIO_LOCAL


#include "Hw_GPIO.h"

HW_GPIO_DEF uint8_t GPIO_ReadInputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
HW_GPIO_DEF void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct);
HW_GPIO_DEF void GPIO_Configuratioin(void);
HW_GPIO_DEF void GPIO_WriteBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, BitAction BitVal);
HW_GPIO_DEF uint8_t GPIO_ReadOutputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
HW_GPIO_DEF void GPIO_SetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);


/**
  * @brief  Initializes the GPIOx peripheral according to the specified
  *         parameters in the GPIO_InitStruct.
  * @param  GPIOx: where x can be (A..G) to select the GPIO peripheral.
  * @param  GPIO_InitStruct: pointer to a GPIO_InitTypeDef structure that
  *         contains the configuration information for the specified GPIO peripheral.
  * @retval None
  */
HW_GPIO_DEF void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct)
{
    uint32_t currentmode = 0x00, currentpin = 0x00, pinpos = 0x00, pos = 0x00;
    uint32_t tmpreg = 0x00, pinmask = 0x00;
    /*--------------- GPIO Mode Configuration -----------------*/
    currentmode = ((uint32_t)GPIO_InitStruct->GPIO_Mode) & (uint32_t)0x0F;
    if((((uint32_t)GPIO_InitStruct->GPIO_Mode) & (uint32_t)0x10) != 0x00)
    {
        currentmode |= GPIO_InitStruct->GPIO_Speed;
    }
    /*--------------- GPIO CRL Configuration -----------------*/
    //max pin_7 = uint16_t 0x0080 pin_8 = uint16)t 0x0100
    if(((uint32_t)GPIO_InitStruct->GPIO_Pin & ((uint32_t)0x00FF)) != 0x00)
    {
        tmpreg = GPIOx->CRL;
        for(pinpos = 0x00; pinpos < 0x08; pinpos++)
        {
            pos = ((uint32_t)0x01) << pinpos;
            /* Get the port pins position */
            currentpin = (GPIO_InitStruct->GPIO_Pin) & pos;
            if(currentpin == pos)
            {
                pos = pinpos << 2;
                /* Clear the corresponding low control register bits */
                pinmask = ((uint32_t)0x0F) << pos;
                tmpreg &= ~pinmask;
                /* Write the mode configuration in the corresponding bits */
                tmpreg |= (currentmode << pos);
                /* Reset the corresponding ODR bit */
                if(GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPD)
                {
                    GPIOx->BRR = (((uint32_t)0x01) >> pinpos);
                }
                else
                {
                    /* Set the corresponding ODR bit */
                    if(GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPU)
                    {
                        GPIOx->BSRR = (((uint32_t)0x01) << pinpos);
                    }
                }
            }
        }
        GPIOx->CRL = tmpreg;
    }
    /*---------------------------- GPIO CRH Configuration ------------------------*/
  /* Configure the eight high port pins */
  //0x00ff = 1111 1111, pin_8 = 1 0000 0000
  if(GPIO_InitStruct->GPIO_Pin > 0x00FF)
  {
      tmpreg = GPIOx->CRH;
      for(pinpos = 0x00; pinpos < 0x08; pinpos++)
      {
          pos = (((uint32_t)0x01) << (pinpos + 0x08));
          /* Get the port pins position */
          currentpin = ((GPIO_InitStruct->GPIO_Pin) & pos);
          if(currentpin == pos)
          {
              pos = pinpos << 2;
              /* Clear the corresponding high control register bits */
              pinmask = ((uint32_t)0x0F) << pos;
              tmpreg &= ~pinmask;
              /* Write the mode configuration in the corresponding bits */
              tmpreg |= (currentmode << pos);
              /* Reset the corresponding ODR bit */
              if(GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPD)
              {
                  GPIOx->BRR = (((uint32_t)0x01) << (pinpos + 0x08));
              }
              /* Set the corresponding ODR bit */
              if(GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPU)
              {
                  GPIOx->BSRR = (((uint32_t)0x01) << (pinpos + 0x08));
              }
          }
      }
      GPIOx->CRH = tmpreg;
  }
}

/**
  * @brief  Reads the specified GPIO input data port.
  * @param  GPIOx: where x can be (A..G) to select the GPIO peripheral.
  * @retval GPIO input data port value.
  */
HW_GPIO_DEF uint8_t GPIO_ReadInputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    uint8_t bitStatus = 0x00;
    if((GPIOx->IDR & GPIO_Pin) != (uint32_t)Bit_RESET)
    {
        bitStatus = (uint8_t)Bit_SET;
    }
    else
    {
        bitStatus = (uint8_t)Bit_RESET;
    }
    return bitStatus;
}
/**
  * @brief  Reads the specified output data port bit.
  * @param  GPIOx: where x can be (A..G) to select the GPIO peripheral.
  * @param  GPIO_Pin:  specifies the port bit to read.
  *   This parameter can be GPIO_Pin_x where x can be (0..15).
  * @retval The output port pin value.
  */
HW_GPIO_DEF uint8_t GPIO_ReadOutputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    uint8_t bitstatus = 0x00;

    if((GPIOx->ODR & GPIO_Pin) != (uint32_t)Bit_RESET)
    {
        bitstatus = (uint8_t)Bit_SET;
    }
    else
    {
        bitstatus = (uint8_t)Bit_RESET;
    }
    return bitstatus;
}

/**
  * @brief  Writes data to the specified GPIO data port.
  * @param  GPIOx: where x can be (A..G) to select the GPIO peripheral.
  * @param  PortVal: specifies the value to be written to the port output data register.
  * @retval None
  */
HW_GPIO_DEF void GPIO_Write(GPIO_TypeDef* GPIOx, uint16_t PortVal)
{
    GPIOx->ODR = PortVal;
}
/**
  * @brief  Sets or clears the selected data port bit.
  * @param  GPIOx: where x can be (A..G) to select the GPIO peripheral.
  * @param  GPIO_Pin: specifies the port bit to be written.
  *   This parameter can be one of GPIO_Pin_x where x can be (0..15).
  * @param  BitVal: specifies the value to be written to the selected bit.
  *   This parameter can be one of the BitAction enum values:
  *     @arg Bit_RESET: to clear the port pin
  *     @arg Bit_SET: to set the port pin
  * @retval None
  */
HW_GPIO_DEF void GPIO_WriteBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, BitAction BitVal)
{
    if(BitVal != Bit_RESET)
    {
        GPIOx->BSRR = GPIO_Pin;
    }
    else
    {
        GPIOx->BRR = GPIO_Pin;
    }
}

/**
  * @brief  Sets the selected data port bits.
  * @param  GPIOx: where x can be (A..G) to select the GPIO peripheral.
  * @param  GPIO_Pin: specifies the port bits to be written.
  *   This parameter can be any combination of GPIO_Pin_x where x can be (0..15).
  * @retval None
  */
HW_GPIO_DEF void GPIO_SetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    GPIOx->BSRR = GPIO_Pin;
}

/**
  * @brief  Clears the selected data port bits.
  * @param  GPIOx: where x can be (A..G) to select the GPIO peripheral.
  * @param  GPIO_Pin: specifies the port bits to be written.
  *   This parameter can be any combination of GPIO_Pin_x where x can be (0..15).
  * @retval None
  */
HW_GPIO_DEF void GPIO_ResetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    GPIOx->BRR = GPIO_Pin;
}





HW_GPIO_DEF void GPIO_Configuratioin(void)
{
    /*
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_USART1_Tx_Pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIO_USART1, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_USART1_Rx_Pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIO_USART1, &GPIO_InitStructure);
    */
    /*
    GPIO_InitStructure.GPIO_Pin = GPIO_KEY1_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIO_KEY, &GPIO_InitStructure);
    */
    /* Configure gpio as input : Button Right-USER */
    /*
    GPIO_InitStructure.GPIO_Pin = GPIO_KEY2_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIO_KEY, &GPIO_InitStructure);
    */
    /* Configure gpio as output : LED1, LED2, LED3 */
    /*
    GPIO_InitStructure.GPIO_Pin = GPIO_LED1_PIN | GPIO_LED2_PIN | GPIO_LED3_PIN ;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIO_LED, &GPIO_InitStructure);
    */
    
    /*
    GPIO_InitStructure.GPIO_Pin = GPIO_7_SEG_POWER_PIN | GPIO_7_SEG_A_PIN | GPIO_7_SEG_B_PIN | GPIO_7_SEG_C_PIN | GPIO_7_SEG_D_PIN | GPIO_7_SEG_E_PIN | GPIO_7_SEG_F_PIN | GPIO_7_SEG_G_PIN | GPIO_7_SEG_DP_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIO_7_SEG, &GPIO_InitStructure);
    POWER_SEG_On();
    SEG_AllPin_Off();
    */
    /* Configure PC.04 (ADC Channel14) as analog input -------------------------*/
    /*
    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    */
}