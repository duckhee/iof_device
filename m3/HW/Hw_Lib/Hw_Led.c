#define LED_DRIVER_LOCAL

#include "Hw_Led.h"


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


LED_DRIVER_DEF void Led_Init(void)
{
    //APB2Enable(IOPORT_B_ENABLE, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_LED1_PIN | GPIO_LED2_PIN | GPIO_LED3_PIN ;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIO_LED, &GPIO_InitStructure);

    Led_AllOff();
    
}
LED_DRIVER_DEF void Led_AllOn(void)
{
    Red_On();
    Yellow_On();
    Blue_On();
}

LED_DRIVER_DEF void Led_AllOff(void)
{
    Red_Off();
    Yellow_Off();
    Blue_Off();
}

LED_DRIVER_DEF void Red_On(void)
{
    GPIO_LED->BRR |= GPIO_LED1_PIN;
}

LED_DRIVER_DEF void Red_Off(void)
{
    GPIO_LED->BSRR |= GPIO_LED1_PIN;
}

LED_DRIVER_DEF void Yellow_On(void)
{
    GPIO_LED->BRR |= GPIO_LED2_PIN;
}

LED_DRIVER_DEF void Yellow_Off(void)
{
    GPIO_LED->BSRR |= GPIO_LED2_PIN;
}

LED_DRIVER_DEF void Blue_On(void)
{
    GPIO_LED->BRR |= GPIO_LED3_PIN;
}

LED_DRIVER_DEF void Blue_Off(void)
{
    GPIO_LED->BSRR |= GPIO_LED3_PIN;
}

LED_DRIVER_DEF void LED_MULT(uint32_t count)
{
    for(; count > 0; count --)
    {
        Red_Off();
        Yellow_On();
        Blue_On();
        Hw_1_second();

        Red_On();
        Yellow_Off();
        Blue_On();
        Hw_1_second();

        Red_On();
        Yellow_On();
        Blue_Off();
        Hw_1_second();
    }
    
}

LED_DRIVER_DEF void Test_LED(void)
{
        #if 0
        Led_AllOn();
        Hw_1_second();
        Led_AllOff();
        Hw_1_second();
        Led_AllOn();

    #else
        LED_MULT(30);
        Led_AllOff();
    #endif

}

LED_DRIVER_DEF void Test_Check(void)
{

}