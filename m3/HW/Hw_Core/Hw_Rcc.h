#ifndef __HW_RCC_H__
#define __HW_RCC_H__

#include "Hw.h"

//oscillator HSI
#define RCC_HSI_Value                        ((uint32_t)8000000) /*!< Value of the Internal oscillator in Hz*/
#define RCC_HSE_Value                        ((uint32_t)12000000)



/********************  Bit definition for RCC_CR register  ********************/
#define  RCC_CR_HSION                        ((uint32_t)0x00000001)        /*!< Internal High Speed clock enable */
#define  RCC_CR_HSIRDY                       ((uint32_t)0x00000002)        /*!< Internal High Speed clock ready flag */
#define  RCC_CR_HSITRIM                      ((uint32_t)0x000000F8)        /*!< Internal High Speed clock trimming */
#define  RCC_CR_HSICAL                       ((uint32_t)0x0000FF00)        /*!< Internal High Speed clock Calibration */
#define  RCC_CR_HSEON                        ((uint32_t)0x00010000)        /*!< External High Speed clock enable */
#define  RCC_CR_HSERDY                       ((uint32_t)0x00020000)        /*!< External High Speed clock ready flag */
#define  RCC_CR_HSEBYP                       ((uint32_t)0x00040000)        /*!< External High Speed clock Bypass */
#define  RCC_CR_CSSON                        ((uint32_t)0x00080000)        /*!< Clock Security System enable */
#define  RCC_CR_PLLON                        ((uint32_t)0x01000000)        /*!< PLL enable */
#define  RCC_CR_PLLRDY                       ((uint32_t)0x02000000)        /*!< PLL clock ready flag */


/*******************  Bit definition for RCC_CFGR register  *******************/
/*!< SW configuration */
#define  RCC_CFGR_SW                         ((uint32_t)0x00000003)        /*!< SW[1:0] bits (System clock Switch) */
#define  RCC_CFGR_SW_0                       ((uint32_t)0x00000001)        /*!< Bit 0 */
#define  RCC_CFGR_SW_1                       ((uint32_t)0x00000002)        /*!< Bit 1 */

//System clock switch
#define SW_HSI_SYSCLOCK                      ((uint32_t)0x00000000)
#define SW_HSE_SYSCLOCK                      ((uint32_t)0x00000001)
#define SW_PLL_SYSCLOCK                      ((uint32_t)0x00000002)
#define SW_NOT_ALLOWED                       ((uint32_t)0x00000003)
//System clock mask
#define RCC_SWS_MASK                         ((uint32_t)0x0000000C)
//PLLMULL mask
#define RCC_PLLMUL_MASK                      ((uint32_t)0x003C0000)
//PLLSRC mask
#define RCC_PLLSRC_MASK                      ((uint32_t)0x00010000)
//PLLXTPRE mask
#define RCC_PLLXTPRE_MASK                    ((uint32_t)0x00020000)
//HPRE_SET mask
#define RCC_HPRE_SET_MASK                    ((uint32_t)0x000000F0)
//PPRE1 SET mask
#define RCC_PPRE1_SET_MASK                   ((uint32_t)0x00000700)
//PPRE2 SET mask
#define RCC_PPRE2_SET_MASK                   ((uint32_t)0x00003800)
//ADC PRE SET mask
#define RCC_ADC_PRE_SET_MASK                 ((uint32_t)0x0000C000)
//ADC PREscaler
#define ADCPRE_PLCK2_DIVIDED2                ((uint32_t)0x00000000)
#define ADCPRE_PLCK2_DIVIDED4                ((uint32_t)0x00004000)
#define ADCPRE_PLCK2_DIVIDED6                ((uint32_t)0x00008000)
#define ADCPRE_PLCK2_DIVIDED8                ((uint32_t)0x0000C000)
//APB2 PREscaler
#define APB2_PCLK2_NOT_DIVIDED               ((uint32_t)0x00000000)
#define APB2_PCLK2_DIVIDED2                  ((uint32_t)0x00002000)
#define APB2_PCLK2_DIVIDED4                  ((uint32_t)0x00002800)
#define APB2_PCLK2_DIVIDED8                  ((uint32_t)0x00003000)
#define APB2_PCLK2_DIVIDED16                 ((uint32_t)0x00003800)
//APB1 PREscaler
#define APB1_PCLK1_NOT_DIVIDED               ((uint32_t)0x00000000)
#define APB1_PCLK1_DIVIDED2                  ((uint32_t)0x00000400)
#define APB1_PCLK1_DIVIDED4                  ((uint32_t)0x00000500)
#define APB1_PCLK1_DIVIDED8                  ((uint32_t)0x00000600)
#define APB1_PCLK1_DIVIDED16                 ((uint32_t)0x00000700)
//AHB PREsacler
#define SYSCLK_NOT_DIVIDED                   ((uint32_t)0x00000000)
#define SYSCLK_DIVIDED2                      ((uint32_t)0x00000080)
#define SYSCLK_DIVIDED4                      ((uint32_t)0x00000090)
#define SYSCLK_DIVIDED8                      ((uint32_t)0x000000A0)
#define SYSCLK_DIVIDED16                     ((uint32_t)0x000000B0)
#define SYSCLK_DIVIDED64                     ((uint32_t)0x000000C0)
#define SYSCLK_DIVIDED128                    ((uint32_t)0x000000D0)
#define SYSCLK_DIVIDED256                    ((uint32_t)0x000000E0)
#define SYSCLK_DIVIDED512                    ((uint32_t)0x000000F0)
//pll use hse or hsi
#define PLLSRC_HSI                           ((uint32_t)0x00000000)
#define PLLSRC_HSE                           ((uint32_t)0x00010000)        /*!< HSE clock selected as PLL entry clock source */
//pll mult
#define PLL_INPUT_MULT2                      ((uint32_t)0x00000000)
#define PLL_INPUT_MULT3                      ((uint32_t)0x00040000)
#define PLL_INPUT_MULT4                      ((uint32_t)0x00080000)
#define PLL_INPUT_MULT5                      ((uint32_t)0x000C0000)
#define PLL_INPUT_MULT6                      ((uint32_t)0x00100000)
#define PLL_INPUT_MULT7                      ((uint32_t)0x00140000)
#define PLL_INPUT_MULT8                      ((uint32_t)0x00180000)
#define PLL_INPUT_MULT9                      ((uint32_t)0x001C0000)
#define PLL_INPUT_MULT10                     ((uint32_t)0x00200000)
#define PLL_INPUT_MULT11                     ((uint32_t)0x00240000)
#define PLL_INPUT_MULT12                     ((uint32_t)0x00280000)
#define PLL_INPUT_MULT13                     ((uint32_t)0x002C0000)
#define PLL_INPUT_MULT14                     ((uint32_t)0x00300000)
#define PLL_INPUT_MULT15                     ((uint32_t)0x00340000)
#define PLL_INPUT_MULT16                     ((uint32_t)0x00380000)
#define PLL_INPUT_MULT2_16                   ((uint32_t)0x003C0000)

//function enable get(APB)
#define DMA1_ENABLE                          ((uint32_t)0x00000001)
#define DMA2_ENABLE                          ((uint32_t)0x00000002)
#define SRAM_ENABLE                          ((uint32_t)0x00000004)
#define FLIT_ENABLE                          ((uint32_t)0x00000010)
#define CRC_ENABLE                           ((uint32_t)0x00000040)
#define OTGFS_ENABLE                         ((uint32_t)0x00001000)
#define ETHMAC_ENABLE                        ((uint32_t)0x00004000)
#define ETHMACTX_ENABLE                      ((uint32_t)0x00008000)
#define ETHMACRX_ENABLE                      ((uint32_t)0x00010000)

//function enable get(APB2)
#define AFIO_ENABLE                          ((uint32_t)0x00000001)
#define IOPORT_A_ENABLE                      ((uint32_t)0x00000004)
#define IOPORT_B_ENABLE                      ((uint32_t)0x00000008)
#define IOPORT_C_ENABLE                      ((uint32_t)0x00000010)
#define IOPORT_D_ENABLE                      ((uint32_t)0x00000020)
#define IOPORT_E_ENABLE                      ((uint32_t)0x00000040)
#define ADC1_ENABLE                          ((uint32_t)0x00000200)
#define ADC2_ENABLE                          ((uint32_t)0x00000400)
#define TIM1_ENABLE                          ((uint32_t)0x00000800)
#define SPI1_ENABLE                          ((uint32_t)0x00001000)
#define USART1_ENABLE                        ((uint32_t)0x00004000)

//function enable get(APB1)
#define TIM2_ENABLE                          ((uint32_t)0x00000001)
#define TIM3_ENABLE                          ((uint32_t)0x00000002)
#define TIM4_ENABLE                          ((uint32_t)0x00000004)
#define TIM5_ENABLE                          ((uint32_t)0x00000008)
#define TIM6_ENABLE                          ((uint32_t)0x00000010)
#define TIM7_ENABLE                          ((uint32_t)0x00000020)
#define WWDG_ENABLE                          ((uint32_t)0x00001000)
#define SPI2_ENABLE                          ((uint32_t)0x00004000)
#define SPI3_ENABLE                          ((uint32_t)0x00008000)
#define USART2_ENABLE                        ((uint32_t)0x00020000)
#define USART3_ENABLE                        ((uint32_t)0x00040000)
#define USART4_ENABLE                        ((uint32_t)0x00080000)
#define USART5_ENABLE                        ((uint32_t)0x00100000)
#define I2C1_ENABLE                          ((uint32_t)0x00200000)
#define I2C2_ENABLE                          ((uint32_t)0x00400000)
#define CAN1_ENABLE                          ((uint32_t)0x02000000)
#define CAN2_ENABLE                          ((uint32_t)0x04000000)
#define BKP_ENABLE                           ((uint32_t)0x08000000)
#define PWR_ENABLE                           ((uint32_t)0x10000000)
#define DAC_ENABLE                           ((uint32_t)0x20000000)



#ifdef HW_RCC_LOCAL
#define HW_RCC_DEF
#else
#define HW_RCC_DEF               extern
#endif

static __I uint8_t APBAHBPrescTable[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};
static __I uint8_t ADCPrescTable[4] = {2, 4, 6, 8};

HW_RCC_DEF void HSI_Init(void);
HW_RCC_DEF void HSE_Init(void);
HW_RCC_DEF void APB2Enable(uint32_t RCC_APB2Periph, FunctionalState NewState);
HW_RCC_DEF void APB1Enable(uint32_t RCC_APB1Periph, FunctionalState NewState);
HW_RCC_DEF void APBEnable(uint32_t RCC_APBPeriph, FunctionalState NewState);
HW_RCC_DEF void RCC_GetClocksFreq(RCC_ClocksTypeDef* RCC_Clocks);


#endif
