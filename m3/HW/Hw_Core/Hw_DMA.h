#ifndef __HW_DMA_H__
#define __HW_DMA_H__

#include "Hw.h"


/** @defgroup DMA_data_transfer_direction 
  * @{
  */

#define DMA_DIR_PeripheralDST              ((uint32_t)0x00000010)
#define DMA_DIR_PeripheralSRC              ((uint32_t)0x00000000)

/** @defgroup DMA_memory_data_size 
  * @{
  */

#define DMA_MemoryDataSize_Byte            ((uint32_t)0x00000000)
#define DMA_MemoryDataSize_HalfWord        ((uint32_t)0x00000400)
#define DMA_MemoryDataSize_Word            ((uint32_t)0x00000800)


/** @defgroup DMA_peripheral_incremented_mode 
  * @{
  */

#define DMA_PeripheralInc_Enable           ((uint32_t)0x00000040)
#define DMA_PeripheralInc_Disable          ((uint32_t)0x00000000)


/** @defgroup DMA_peripheral_data_size 
  * @{
  */

#define DMA_PeripheralDataSize_Byte        ((uint32_t)0x00000000)
#define DMA_PeripheralDataSize_HalfWord    ((uint32_t)0x00000100)
#define DMA_PeripheralDataSize_Word        ((uint32_t)0x00000200)

/** @defgroup DMA_priority_level 
  * @{
  */

#define DMA_Priority_VeryHigh              ((uint32_t)0x00003000)
#define DMA_Priority_High                  ((uint32_t)0x00002000)
#define DMA_Priority_Medium                ((uint32_t)0x00001000)
#define DMA_Priority_Low                   ((uint32_t)0x00000000)


/** @defgroup DMA_circular_normal_mode 
  * @{
  */

#define DMA_Mode_Circular                  ((uint32_t)0x00000020)
#define DMA_Mode_Normal                    ((uint32_t)0x00000000)


/** @defgroup DMA_memory_incremented_mode 
  * @{
  */

#define DMA_MemoryInc_Enable               ((uint32_t)0x00000080)
#define DMA_MemoryInc_Disable              ((uint32_t)0x00000000)

/** @defgroup DMA_memory_to_memory 
  * @{
  */
#define DMA_M2M_Enable                     ((uint32_t)0x00004000)
#define DMA_M2M_Disable                    ((uint32_t)0x00000000)

/* DMA1 Channelx interrupt pending bit masks */
#define DMA1_Channel1_IT_Mask              ((uint32_t)0x0000000F)
#define DMA1_Channel2_IT_Mask              ((uint32_t)0x000000F0)
#define DMA1_Channel3_IT_Mask              ((uint32_t)0x00000F00)
#define DMA1_Channel4_IT_Mask              ((uint32_t)0x0000F000)
#define DMA1_Channel5_IT_Mask              ((uint32_t)0x000F0000)
#define DMA1_Channel6_IT_Mask              ((uint32_t)0x00F00000)
#define DMA1_Channel7_IT_Mask              ((uint32_t)0x0F000000)

/* DMA2 Channelx interrupt pending bit masks */
#define DMA2_Channel1_IT_Mask             ((uint32_t)0x0000000F)
#define DMA2_Channel2_IT_Mask             ((uint32_t)0x000000F0)
#define DMA2_Channel3_IT_Mask             ((uint32_t)0x00000F00)
#define DMA2_Channel4_IT_Mask             ((uint32_t)0x0000F000)
#define DMA2_Channel5_IT_Mask             ((uint32_t)0x000F0000)
/* DMA ENABLE mask */
#define DMA_CCR_ENABLE_Set                ((uint32_t)0x00000001)
#define DMA_CCR_ENABLE_Reset              ((uint32_t)0xFFFFFFFE)
/*******************  Bit definition for DMA_CCR1 register  *******************/
#define  DMA_CCR1_EN                         ((uint16_t)0x0001)            /*!< Channel enable*/
#define  DMA_CCR1_TCIE                       ((uint16_t)0x0002)            /*!< Transfer complete interrupt enable */
#define  DMA_CCR1_HTIE                       ((uint16_t)0x0004)            /*!< Half Transfer interrupt enable */
#define  DMA_CCR1_TEIE                       ((uint16_t)0x0008)            /*!< Transfer error interrupt enable */
#define  DMA_CCR1_DIR                        ((uint16_t)0x0010)            /*!< Data transfer direction */
#define  DMA_CCR1_CIRC                       ((uint16_t)0x0020)            /*!< Circular mode */
#define  DMA_CCR1_PINC                       ((uint16_t)0x0040)            /*!< Peripheral increment mode */
#define  DMA_CCR1_MINC                       ((uint16_t)0x0080)            /*!< Memory increment mode */

/* DMA ENABLE mask */
#define DMA_CCR_ENABLE_Set               ((uint32_t)0x00000001)
#define DMA_CCR_ENABLE_Reset             ((uint32_t)0xFFFFFFFE)


/* DMA2 FLAG mask */
#define DMA_FLAG_Mask                    ((uint32_t)0x10000000)

/* DMA registers Masks */
#define DMA_CCR_CLEAR_Mask               ((uint32_t)0xFFFF800F)


#ifdef HW_DMA_LOCAL
#define HW_DMA_DEF
#else
#define HW_DMA_DEF                     extern
#endif

#define ADC1_DR_Address                  ((uint32_t)0x4001244C)


HW_DMA_DEF void DMA_Start_Cmd(DMA_Channel_TypeDef* DMAy_Channelx, FunctionalState NewState);
HW_DMA_DEF void DMA_Init(DMA_Channel_TypeDef* DMAy_Channelx, DMA_InitTypeDef* DMA_InitStruct);
HW_DMA_DEF void DMA_DeInit(DMA_Channel_TypeDef* DMAy_Channelx);

#endif