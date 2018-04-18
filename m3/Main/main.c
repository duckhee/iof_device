#include "main.h"


RCC_ClocksTypeDef rcc_clocks;

int main(void)
{
    HW_Init();
    RCC_GetClocksFreq(&rcc_clocks);
    System_Information();
    // Key_Test();
    // Test_LED();
    command_main();

}