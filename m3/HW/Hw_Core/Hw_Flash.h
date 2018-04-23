#ifndef __HW_FLASH_H__
#define __HW_FLASH_H__

#include "Hw.h"



/* FLASH Mask */
#define FLASH_RDPRT_Mask               ((uint32_t)0x00000002)
#define FLASH_WRP0_Mask                ((uint32_t)0x000000FF)
#define FLASH_WRP1_Mask                ((uint32_t)0x0000FF00)
#define FLASH_WRP2_Mask                ((uint32_t)0x00FF0000)
#define FLASH_WRP3_Mask                ((uint32_t)0xFF000000)
#define FLASH_OB_USER_BFB2             ((uint16_t)0x0008)

/* FLASH Keys */
#define RDPRT_KEY                  ((uint16_t)0x00A5)
#define FLASH_KEY1               ((uint32_t)0x45670123)
#define FLASH_KEY2               ((uint32_t)0xCDEF89AB)

#define FLASH_FLAG_BANK1_BSY                 FLASH_FLAG_BSY       /*!< FLASH BANK1 Busy flag*/
#define FLASH_FLAG_BANK1_EOP                 FLASH_FLAG_EOP       /*!< FLASH BANK1 End of Operation flag */
#define FLASH_FLAG_BANK1_PGERR               FLASH_FLAG_PGERR     /*!< FLASH BANK1 Program error flag */
#define FLASH_FLAG_BANK1_WRPRTERR            FLASH_FLAG_WRPRTERR  /*!< FLASH BANK1 Write protected error flag */
/* Flash Control Register bits */
#define FLASH_CR_PG_Set                ((uint32_t)0x00000001)
#define FLASH_CR_PG_Reset              ((uint32_t)0x00001FFE)
#define FLASH_CR_PER_Set               ((uint32_t)0x00000002)
#define FLASH_CR_PER_Reset             ((uint32_t)0x00001FFD)
#define FLASH_CR_MER_Set               ((uint32_t)0x00000004)
#define FLASH_CR_MER_Reset             ((uint32_t)0x00001FFB)
#define FLASH_CR_OPTPG_Set             ((uint32_t)0x00000010)
#define FLASH_CR_OPTPG_Reset           ((uint32_t)0x00001FEF)
#define FLASH_CR_OPTER_Set             ((uint32_t)0x00000020)
#define FLASH_CR_OPTER_Reset           ((uint32_t)0x00001FDF)
#define FLASH_CR_STRT_Set              ((uint32_t)0x00000040)
#define FLASH_CR_LOCK_Set              ((uint32_t)0x00000080)
/*******************  Bit definition for FLASH_ACR register  ******************/
#define  FLASH_ACR_LATENCY                   ((uint8_t)0x03)               /*!< LATENCY[2:0] bits (Latency) */
#define  FLASH_ACR_LATENCY_0                 ((uint8_t)0x00)               /*!< Bit 0 0 < SYSCLK <= 24MHz */
#define  FLASH_ACR_LATENCY_1                 ((uint8_t)0x01)               /*!< Bit 0 24 < SYSCLK <= 48MHz */
#define  FLASH_ACR_LATENCY_2                 ((uint8_t)0x02)               /*!< Bit 1 48 < SYSCLK <= 72MHz */
/* Flash Access Control Register bits */
#define FLASH_ACR_LATENCY_Mask         ((uint32_t)0x00000038)
#define FLASH_ACR_HLFCYA_Mask          ((uint32_t)0xFFFFFFF7)
#define FLASH_ACR_PRFTBE_Mask          ((uint32_t)0xFFFFFFEF)

/** @defgroup Prefetch_Buffer_Enable_Disable
  * @{
  */

#define FLASH_PrefetchBuffer_Enable    ((uint32_t)0x00000010)  /*!< FLASH Prefetch Buffer Enable */
#define FLASH_PrefetchBuffer_Disable   ((uint32_t)0x00000000)  /*!< FLASH Prefetch Buffer Disable */
#define FLASH_FLAG_BSY                 ((uint32_t)0x00000001)  /*!< FLASH Busy flag */
#define FLASH_FLAG_EOP                 ((uint32_t)0x00000020)  /*!< FLASH End of Operation flag */
#define FLASH_FLAG_PGERR               ((uint32_t)0x00000004)  /*!< FLASH Program error flag */
#define FLASH_FLAG_WRPRTERR            ((uint32_t)0x00000010)  /*!< FLASH Write protected error flag */
#define FLASH_FLAG_OPTERR              ((uint32_t)0x00000001)  /*!< FLASH Option Byte error flag */
/** @defgroup Option_Bytes_Write_Protection
  * @{
  */

/* Values to be used with STM32 Low and Medium density devices */
#define FLASH_WRProt_Pages0to3         ((uint32_t)0x00000001) /*!< STM32 Low and Medium density devices: Write protection of page 0 to 3 */
#define FLASH_WRProt_Pages4to7         ((uint32_t)0x00000002) /*!< STM32 Low and Medium density devices: Write protection of page 4 to 7 */
#define FLASH_WRProt_Pages8to11        ((uint32_t)0x00000004) /*!< STM32 Low and Medium density devices: Write protection of page 8 to 11 */
#define FLASH_WRProt_Pages12to15       ((uint32_t)0x00000008) /*!< STM32 Low and Medium density devices: Write protection of page 12 to 15 */
#define FLASH_WRProt_Pages16to19       ((uint32_t)0x00000010) /*!< STM32 Low and Medium density devices: Write protection of page 16 to 19 */
#define FLASH_WRProt_Pages20to23       ((uint32_t)0x00000020) /*!< STM32 Low and Medium density devices: Write protection of page 20 to 23 */
#define FLASH_WRProt_Pages24to27       ((uint32_t)0x00000040) /*!< STM32 Low and Medium density devices: Write protection of page 24 to 27 */
#define FLASH_WRProt_Pages28to31       ((uint32_t)0x00000080) /*!< STM32 Low and Medium density devices: Write protection of page 28 to 31 */

/* Values to be used with STM32 Medium-density devices */
#define FLASH_WRProt_Pages32to35       ((uint32_t)0x00000100) /*!< STM32 Medium-density devices: Write protection of page 32 to 35 */
#define FLASH_WRProt_Pages36to39       ((uint32_t)0x00000200) /*!< STM32 Medium-density devices: Write protection of page 36 to 39 */
#define FLASH_WRProt_Pages40to43       ((uint32_t)0x00000400) /*!< STM32 Medium-density devices: Write protection of page 40 to 43 */
#define FLASH_WRProt_Pages44to47       ((uint32_t)0x00000800) /*!< STM32 Medium-density devices: Write protection of page 44 to 47 */
#define FLASH_WRProt_Pages48to51       ((uint32_t)0x00001000) /*!< STM32 Medium-density devices: Write protection of page 48 to 51 */
#define FLASH_WRProt_Pages52to55       ((uint32_t)0x00002000) /*!< STM32 Medium-density devices: Write protection of page 52 to 55 */
#define FLASH_WRProt_Pages56to59       ((uint32_t)0x00004000) /*!< STM32 Medium-density devices: Write protection of page 56 to 59 */
#define FLASH_WRProt_Pages60to63       ((uint32_t)0x00008000) /*!< STM32 Medium-density devices: Write protection of page 60 to 63 */
#define FLASH_WRProt_Pages64to67       ((uint32_t)0x00010000) /*!< STM32 Medium-density devices: Write protection of page 64 to 67 */
#define FLASH_WRProt_Pages68to71       ((uint32_t)0x00020000) /*!< STM32 Medium-density devices: Write protection of page 68 to 71 */
#define FLASH_WRProt_Pages72to75       ((uint32_t)0x00040000) /*!< STM32 Medium-density devices: Write protection of page 72 to 75 */
#define FLASH_WRProt_Pages76to79       ((uint32_t)0x00080000) /*!< STM32 Medium-density devices: Write protection of page 76 to 79 */
#define FLASH_WRProt_Pages80to83       ((uint32_t)0x00100000) /*!< STM32 Medium-density devices: Write protection of page 80 to 83 */
#define FLASH_WRProt_Pages84to87       ((uint32_t)0x00200000) /*!< STM32 Medium-density devices: Write protection of page 84 to 87 */
#define FLASH_WRProt_Pages88to91       ((uint32_t)0x00400000) /*!< STM32 Medium-density devices: Write protection of page 88 to 91 */
#define FLASH_WRProt_Pages92to95       ((uint32_t)0x00800000) /*!< STM32 Medium-density devices: Write protection of page 92 to 95 */
#define FLASH_WRProt_Pages96to99       ((uint32_t)0x01000000) /*!< STM32 Medium-density devices: Write protection of page 96 to 99 */
#define FLASH_WRProt_Pages100to103     ((uint32_t)0x02000000) /*!< STM32 Medium-density devices: Write protection of page 100 to 103 */
#define FLASH_WRProt_Pages104to107     ((uint32_t)0x04000000) /*!< STM32 Medium-density devices: Write protection of page 104 to 107 */
#define FLASH_WRProt_Pages108to111     ((uint32_t)0x08000000) /*!< STM32 Medium-density devices: Write protection of page 108 to 111 */
#define FLASH_WRProt_Pages112to115     ((uint32_t)0x10000000) /*!< STM32 Medium-density devices: Write protection of page 112 to 115 */
#define FLASH_WRProt_Pages116to119     ((uint32_t)0x20000000) /*!< STM32 Medium-density devices: Write protection of page 115 to 119 */
#define FLASH_WRProt_Pages120to123     ((uint32_t)0x40000000) /*!< STM32 Medium-density devices: Write protection of page 120 to 123 */
#define FLASH_WRProt_Pages124to127     ((uint32_t)0x80000000) /*!< STM32 Medium-density devices: Write protection of page 124 to 127 */

/* Values to be used with STM32 High-density and STM32F10X Connectivity line devices */
#define FLASH_WRProt_Pages0to1         ((uint32_t)0x00000001) /*!< STM32 High-density, XL-density and Connectivity line devices:
                                                                   Write protection of page 0 to 1 */
#define FLASH_WRProt_Pages2to3         ((uint32_t)0x00000002) /*!< STM32 High-density, XL-density and Connectivity line devices:
                                                                   Write protection of page 2 to 3 */
#define FLASH_WRProt_Pages4to5         ((uint32_t)0x00000004) /*!< STM32 High-density, XL-density and Connectivity line devices:
                                                                   Write protection of page 4 to 5 */
#define FLASH_WRProt_Pages6to7         ((uint32_t)0x00000008) /*!< STM32 High-density, XL-density and Connectivity line devices:
                                                                   Write protection of page 6 to 7 */
#define FLASH_WRProt_Pages8to9         ((uint32_t)0x00000010) /*!< STM32 High-density, XL-density and Connectivity line devices:
                                                                   Write protection of page 8 to 9 */
#define FLASH_WRProt_Pages10to11       ((uint32_t)0x00000020) /*!< STM32 High-density, XL-density and Connectivity line devices:
                                                                   Write protection of page 10 to 11 */
#define FLASH_WRProt_Pages12to13       ((uint32_t)0x00000040) /*!< STM32 High-density, XL-density and Connectivity line devices:
                                                                   Write protection of page 12 to 13 */
#define FLASH_WRProt_Pages14to15       ((uint32_t)0x00000080) /*!< STM32 High-density, XL-density and Connectivity line devices:
                                                                   Write protection of page 14 to 15 */
#define FLASH_WRProt_Pages16to17       ((uint32_t)0x00000100) /*!< STM32 High-density, XL-density and Connectivity line devices:
                                                                   Write protection of page 16 to 17 */
#define FLASH_WRProt_Pages18to19       ((uint32_t)0x00000200) /*!< STM32 High-density, XL-density and Connectivity line devices:
                                                                   Write protection of page 18 to 19 */
#define FLASH_WRProt_Pages20to21       ((uint32_t)0x00000400) /*!< STM32 High-density, XL-density and Connectivity line devices:
                                                                   Write protection of page 20 to 21 */
#define FLASH_WRProt_Pages22to23       ((uint32_t)0x00000800) /*!< STM32 High-density, XL-density and Connectivity line devices:
                                                                   Write protection of page 22 to 23 */
#define FLASH_WRProt_Pages24to25       ((uint32_t)0x00001000) /*!< STM32 High-density, XL-density and Connectivity line devices:
                                                                   Write protection of page 24 to 25 */
#define FLASH_WRProt_Pages26to27       ((uint32_t)0x00002000) /*!< STM32 High-density, XL-density and Connectivity line devices:
                                                                   Write protection of page 26 to 27 */
#define FLASH_WRProt_Pages28to29       ((uint32_t)0x00004000) /*!< STM32 High-density, XL-density and Connectivity line devices:
                                                                   Write protection of page 28 to 29 */
#define FLASH_WRProt_Pages30to31       ((uint32_t)0x00008000) /*!< STM32 High-density, XL-density and Connectivity line devices:
                                                                   Write protection of page 30 to 31 */
#define FLASH_WRProt_Pages32to33       ((uint32_t)0x00010000) /*!< STM32 High-density, XL-density and Connectivity line devices:
                                                                   Write protection of page 32 to 33 */
#define FLASH_WRProt_Pages34to35       ((uint32_t)0x00020000) /*!< STM32 High-density, XL-density and Connectivity line devices:
                                                                   Write protection of page 34 to 35 */
#define FLASH_WRProt_Pages36to37       ((uint32_t)0x00040000) /*!< STM32 High-density, XL-density and Connectivity line devices:
                                                                   Write protection of page 36 to 37 */
#define FLASH_WRProt_Pages38to39       ((uint32_t)0x00080000) /*!< STM32 High-density, XL-density and Connectivity line devices:
                                                                   Write protection of page 38 to 39 */
#define FLASH_WRProt_Pages40to41       ((uint32_t)0x00100000) /*!< STM32 High-density, XL-density and Connectivity line devices:
                                                                   Write protection of page 40 to 41 */
#define FLASH_WRProt_Pages42to43       ((uint32_t)0x00200000) /*!< STM32 High-density, XL-density and Connectivity line devices:
                                                                   Write protection of page 42 to 43 */
#define FLASH_WRProt_Pages44to45       ((uint32_t)0x00400000) /*!< STM32 High-density, XL-density and Connectivity line devices:
                                                                   Write protection of page 44 to 45 */
#define FLASH_WRProt_Pages46to47       ((uint32_t)0x00800000) /*!< STM32 High-density, XL-density and Connectivity line devices:
                                                                   Write protection of page 46 to 47 */
#define FLASH_WRProt_Pages48to49       ((uint32_t)0x01000000) /*!< STM32 High-density, XL-density and Connectivity line devices:
                                                                   Write protection of page 48 to 49 */
#define FLASH_WRProt_Pages50to51       ((uint32_t)0x02000000) /*!< STM32 High-density, XL-density and Connectivity line devices:
                                                                   Write protection of page 50 to 51 */
#define FLASH_WRProt_Pages52to53       ((uint32_t)0x04000000) /*!< STM32 High-density, XL-density and Connectivity line devices:
                                                                   Write protection of page 52 to 53 */
#define FLASH_WRProt_Pages54to55       ((uint32_t)0x08000000) /*!< STM32 High-density, XL-density and Connectivity line devices:
                                                                   Write protection of page 54 to 55 */
#define FLASH_WRProt_Pages56to57       ((uint32_t)0x10000000) /*!< STM32 High-density, XL-density and Connectivity line devices:
                                                                   Write protection of page 56 to 57 */
#define FLASH_WRProt_Pages58to59       ((uint32_t)0x20000000) /*!< STM32 High-density, XL-density and Connectivity line devices:
                                                                   Write protection of page 58 to 59 */
#define FLASH_WRProt_Pages60to61       ((uint32_t)0x40000000) /*!< STM32 High-density, XL-density and Connectivity line devices:
                                                                   Write protection of page 60 to 61 */
#define FLASH_WRProt_Pages62to127      ((uint32_t)0x80000000) /*!< STM32 Connectivity line devices: Write protection of page 62 to 127 */
#define FLASH_WRProt_Pages62to255      ((uint32_t)0x80000000) /*!< STM32 Medium-density devices: Write protection of page 62 to 255 */
#define FLASH_WRProt_Pages62to511      ((uint32_t)0x80000000) /*!< STM32 XL-density devices: Write protection of page 62 to 511 */
/* Delay definition */
#define EraseTimeout          ((uint32_t)0x000B0000)
#define ProgramTimeout        ((uint32_t)0x00002000)


#ifdef HW_FLASH_LOCAL
#define HW_FLASH_DEF
#else
#define HW_FLASH_DEF                    extern
#endif

HW_FLASH_DEF FLASH_Status FLASH_ProgramWord(uint32_t Address, uint32_t Data);
HW_FLASH_DEF FLASH_Status FLASH_WaitForLastOperation(uint32_t Timeout);
HW_FLASH_DEF FLASH_Status FLASH_GetBank1Status(void);
HW_FLASH_DEF void FLASH_Unlock(void);
HW_FLASH_DEF void FLASH_Lock(void);
HW_FLASH_DEF void FLASH_SetLatency(uint32_t FLASH_Latency);
HW_FLASH_DEF FLASH_Status FLASH_ErasePage(uint32_t Page_Address);
HW_FLASH_DEF FLASH_Status FLASH_EraseAllPage(void);
HW_FLASH_DEF FLASH_Status FLASH_EraseOptionBytes(void);
HW_FLASH_DEF FLASH_Status FLASH_EnableWriteProtection(uint32_t FLASH_Pages);



#endif