#ifndef __HW_ADC_H__
#define __HW_ADC_H__

#include "Hw.h"

/** @defgroup ADC_data_align 
  * @{
  */

#define ADC_DataAlign_Right                        ((uint32_t)0x00000000)
#define ADC_DataAlign_Left                         ((uint32_t)0x00000800)

/** @defgroup ADC_external_trigger_sources_for_regular_channels_conversion 
  * @{
  */

#define ADC_ExternalTrigConv_T1_CC1                ((uint32_t)0x00000000) /*!< For ADC1 and ADC2 */
#define ADC_ExternalTrigConv_T1_CC2                ((uint32_t)0x00020000) /*!< For ADC1 and ADC2 */
#define ADC_ExternalTrigConv_T2_CC2                ((uint32_t)0x00060000) /*!< For ADC1 and ADC2 */
#define ADC_ExternalTrigConv_T3_TRGO               ((uint32_t)0x00080000) /*!< For ADC1 and ADC2 */
#define ADC_ExternalTrigConv_T4_CC4                ((uint32_t)0x000A0000) /*!< For ADC1 and ADC2 */
#define ADC_ExternalTrigConv_Ext_IT11_TIM8_TRGO    ((uint32_t)0x000C0000) /*!< For ADC1 and ADC2 */

#define ADC_ExternalTrigConv_T1_CC3                ((uint32_t)0x00040000) /*!< For ADC1, ADC2 and ADC3 */
#define ADC_ExternalTrigConv_None                  ((uint32_t)0x000E0000) /*!< For ADC1, ADC2 and ADC3 */


/** @defgroup ADC_mode 
  * @{
  */

#define ADC_Mode_Independent                       ((uint32_t)0x00000000)
#define ADC_Mode_RegInjecSimult                    ((uint32_t)0x00010000)
#define ADC_Mode_RegSimult_AlterTrig               ((uint32_t)0x00020000)
#define ADC_Mode_InjecSimult_FastInterl            ((uint32_t)0x00030000)
#define ADC_Mode_InjecSimult_SlowInterl            ((uint32_t)0x00040000)
#define ADC_Mode_InjecSimult                       ((uint32_t)0x00050000)
#define ADC_Mode_RegSimult                         ((uint32_t)0x00060000)
#define ADC_Mode_FastInterl                        ((uint32_t)0x00070000)
#define ADC_Mode_SlowInterl                        ((uint32_t)0x00080000)
#define ADC_Mode_AlterTrig                         ((uint32_t)0x00090000)


/** @defgroup ADC_channels 
  * @{
  */

#define ADC_Channel_0                               ((uint8_t)0x00)
#define ADC_Channel_1                               ((uint8_t)0x01)
#define ADC_Channel_2                               ((uint8_t)0x02)
#define ADC_Channel_3                               ((uint8_t)0x03)
#define ADC_Channel_4                               ((uint8_t)0x04)
#define ADC_Channel_5                               ((uint8_t)0x05)
#define ADC_Channel_6                               ((uint8_t)0x06)
#define ADC_Channel_7                               ((uint8_t)0x07)
#define ADC_Channel_8                               ((uint8_t)0x08)
#define ADC_Channel_9                               ((uint8_t)0x09)
#define ADC_Channel_10                              ((uint8_t)0x0A)
#define ADC_Channel_11                              ((uint8_t)0x0B)
#define ADC_Channel_12                              ((uint8_t)0x0C)
#define ADC_Channel_13                              ((uint8_t)0x0D)
#define ADC_Channel_14                              ((uint8_t)0x0E)
#define ADC_Channel_15                              ((uint8_t)0x0F)
#define ADC_Channel_16                              ((uint8_t)0x10)
#define ADC_Channel_17                              ((uint8_t)0x11)

/** @defgroup ADC_sampling_time 
  * @{
  */

#define ADC_SampleTime_1Cycles5                    ((uint8_t)0x00)
#define ADC_SampleTime_7Cycles5                    ((uint8_t)0x01)
#define ADC_SampleTime_13Cycles5                   ((uint8_t)0x02)
#define ADC_SampleTime_28Cycles5                   ((uint8_t)0x03)
#define ADC_SampleTime_41Cycles5                   ((uint8_t)0x04)
#define ADC_SampleTime_55Cycles5                   ((uint8_t)0x05)
#define ADC_SampleTime_71Cycles5                   ((uint8_t)0x06)
#define ADC_SampleTime_239Cycles5                  ((uint8_t)0x07)

/* CR1 register Mask */
#define ADC_CR1_CLEAR_Mask              ((uint32_t)0xFFF0FEFF)
/* CR2 register Mask */
#define ADC_CR2_CLEAR_Mask              ((uint32_t)0xFFF1F7FD)

/* ADC SQx mask */
#define ADC_SQR3_SQ_Set                 ((uint32_t)0x0000001F)
#define ADC_SQR2_SQ_Set                 ((uint32_t)0x0000001F)
#define ADC_SQR1_SQ_Set                 ((uint32_t)0x0000001F)

/* SQR1 register Mask */
#define ADC_SQR1_CLEAR_Mask             ((uint32_t)0xFF0FFFFF)

/* ADC JSQx mask */
#define ADC_JSQR_JSQ_Set                ((uint32_t)0x0000001F)

/* ADC JL mask */
#define ADC_JSQR_JL_Set                 ((uint32_t)0x00300000)
#define ADC_JSQR_JL_Reset               ((uint32_t)0xFFCFFFFF)

/* ADC SMPx mask */
#define ADC_SMPR1_SMP_Set               ((uint32_t)0x00000007)
#define ADC_SMPR2_SMP_Set               ((uint32_t)0x00000007)

/* ADC JDRx registers offset */
#define ADC_JDR_Offset                  ((uint8_t)0x28)

/* ADC1 DR register base address */
#define ADC_DR_ADDRESS                  ((uint32_t)0x4001244C)

/* ADC ADON mask */
#define ADC_CR2_ADON_Set                ((uint32_t)0x00000001)
#define ADC_CR2_ADON_Reset              ((uint32_t)0xFFFFFFFE)

/* ADC DMA mask */
#define ADC_CR2_DMA_Set                 ((uint32_t)0x00000100)
#define ADC_CR2_DMA_Reset               ((uint32_t)0xFFFFFEFF)

/* ADC RSTCAL mask */
#define ADC_CR2_RSTCAL_Set              ((uint32_t)0x00000008)
/* ADC CAL mask */
#define ADC_CR2_CAL_Set                 ((uint32_t)0x00000004)

/* ADC Software start mask */
#define ADC_CR2_EXTTRIG_SWSTART_Set     ((uint32_t)0x00500000)
#define ADC_CR2_EXTTRIG_SWSTART_Reset   ((uint32_t)0xFFAFFFFF)

#ifdef HW_ADC_LOCAL
#define HW_ADC_DEF
#else
#define HW_ADC_DEF                 extern
#endif


HW_ADC_DEF void ADC_Init(ADC_TypeDef* ADCx, ADC_InitTypeDef* ADC_InitStruct);
HW_ADC_DEF void ADC_RegularChannelConfig(ADC_TypeDef* ADCx, uint8_t ADC_Channel, uint8_t Rank, uint8_t ADC_SampleTime);
HW_ADC_DEF void ADC_DMA_Enable_Cmd(ADC_TypeDef* ADCx, FunctionalState NewState);
HW_ADC_DEF void ADC_Enable_Cmd(ADC_TypeDef* ADCx, FunctionalState NewState);
HW_ADC_DEF void ADC_ResetCalibration(ADC_TypeDef* ADCx);
HW_ADC_DEF FlagStatus ADC_GetResetCalibrationStatus(ADC_TypeDef* ADCx);
HW_ADC_DEF void ADC_StartCalibration(ADC_TypeDef* ADCx);
HW_ADC_DEF FlagStatus ADC_GetCalibrationStatus(ADC_TypeDef* ADCx);
HW_ADC_DEF void ADC_SoftwareStartConvCmd(ADC_TypeDef* ADCx, FunctionalState NewState);
HW_ADC_DEF FlagStatus ADC_GetFlagStatus(ADC_TypeDef* ADCx, uint8_t ADC_FLAG);
HW_ADC_DEF uint16_t ADC_GetConversionValue(ADC_TypeDef* ADCx);

#endif