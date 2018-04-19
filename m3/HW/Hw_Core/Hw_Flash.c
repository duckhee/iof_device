#define HW_FLASH_LOCAL

#include "Hw_Flash.h"

HW_FLASH_DEF void FLASH_Unlock(void);
HW_FLASH_DEF void FLASH_Lock(void);
HW_FLASH_DEF FLASH_Status FLASH_ProgramWord(uint32_t Address, uint32_t Data);
HW_FLASH_DEF FLASH_Status FLASH_WaitForLastOperation(uint32_t Timeout);
HW_FLASH_DEF FLASH_Status FLASH_GetBank1Status(void);
HW_FLASH_DEF void FLASH_SetLatency(uint32_t FLASH_Latency);
HW_FLASH_DEF FLASH_Status FLASH_ErasePage(uint32_t Page_Address);
HW_FLASH_DEF FLASH_Status FLASH_EraseAllPage(void);
HW_FLASH_DEF FLASH_Status FLASH_EraseOptionBytes(void);
HW_FLASH_DEF FLASH_Status FLASH_EnableWriteProtection(uint32_t FLASH_Pages);

HW_FLASH_DEF void FLASH_Unlock(void)
{
    /* Authorize the FPEC of Bank1 Access */
    FLASH->KEYR = FLASH_KEY1;
    FLASH->KEYR = FLASH_KEY2;
}

HW_FLASH_DEF void FLASH_Lock(void)
{
    /* Set the Lock Bit to lock the FPEC and the CR of  Bank1 */
    FLASH->CR |= FLASH_CR_LOCK_Set;
}

HW_FLASH_DEF void FLASH_SetLatency(uint32_t FLASH_Latency)
{
    uint32_t tmpreg = 0;
    /* Read the ACR register */
    tmpreg = FLASH->ACR;
    /* Sets the latency vlaue */
    tmpreg &= FLASH_ACR_LATENCY_Mask;
    tmpreg |= FLASH_Latency;
    /* Write the ACR register */
    FLASH->ACR = tmpreg;
}

HW_FLASH_DEF FLASH_Status FLASH_ProgramWord(uint32_t Address, uint32_t Data)
{
    FLASH_Status status = FLASH_COMPLETE;
    __IO uint32_t tmp = 0;
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(ProgramTimeout);

    if(status == FLASH_COMPLETE)
    {
        /* if the previous operation is completed, proceed to program the new second
      half word */
      FLASH->CR |= FLASH_CR_PG_Set;
      *(__IO uint16_t *)Address = (uint16_t)Data;
      /* Wait for last operation to be completed */
      status = FLASH_WaitForLastOperation(ProgramTimeout);

      if(status == FLASH_COMPLETE)
      {
          /* if the previous operation is completed, proceed to program the new second
            half word */
            tmp = Address + 2;
            *(__IO uint16_t *)tmp = Data >> 16;
            /* Wait for last operation to be completed */
            status = FLASH_WaitForLastOperation(ProgramTimeout);
            /* Disable the PG Bit */
            FLASH->CR &= FLASH_CR_PG_Reset;
      }
      else{
          /* Disable the PG Bit */
          FLASH->CR &= FLASH_CR_PG_Reset;
      }
    }
    /* Return the Program Status */
    return status;
}

HW_FLASH_DEF FLASH_Status FLASH_WaitForLastOperation(uint32_t Timeout)
{
    FLASH_Status status = FLASH_COMPLETE;
    /* Check for the Flash Status */
    status = FLASH_GetBank1Status();
    /* Wait for a Flash operation to complete or a TIMEOUT to occur */
    while((status == FLASH_BUSY) && (Timeout != 0x00))
    {
        status = FLASH_GetBank1Status();
        Timeout--;
    }
    if(Timeout == 0x00)
    {
        status = FLASH_TIMEOUT;
    }
    /* Return the operation status */
    return status;
}

HW_FLASH_DEF FLASH_Status FLASH_GetBank1Status(void)
{
    FLASH_Status flashstatus = FLASH_COMPLETE;
    if((FLASH->SR & FLASH_FLAG_BANK1_BSY) == FLASH_FLAG_BSY)
    {
        flashstatus = FLASH_BUSY;
    }
    else{
        if((FLASH->SR & FLASH_FLAG_BANK1_PGERR) != 0)
        {
            flashstatus = FLASH_ERROR_PG;
        }
        else{
            if((FLASH->SR & FLASH_FLAG_BANK1_WRPRTERR) != 0)
            {
                flashstatus = FLASH_ERROR_WRP;
            }
            else{
                flashstatus = FLASH_COMPLETE;
            }
        }
    }
    /* Return the Flash Status */
    return flashstatus;
}

HW_FLASH_DEF FLASH_Status FLASH_ErasePage(uint32_t Page_Address)
{
    FLASH_Status status = FLASH_COMPLETE;
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(EraseTimeout);

    if(status == FLASH_COMPLETE)
    {
        /* if the previous operation is completed, proceed to erase the page */
        FLASH->CR |= FLASH_CR_PER_Set;
        FLASH->AR = Page_Address;
        FLASH->CR |= FLASH_CR_STRT_Set;
        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOperation(EraseTimeout);
        if(status != FLASH_TIMEOUT)
        {
            /* Disable the PER Bit */
            FLASH->CR &= FLASH_CR_PER_Reset;0
        }
    }
    /* Return the Erase Status */
    return status;
}

HW_FLASH_DEF FLASH_Status FLASH_EraseAllPage(void)
{
    FLASH_Status status = FLASH_COMPLETE;
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(EraseTimeout);

    if(status == FLASH_COMPLETE)
    {
        /* if the previous operation is completed, proceed to erase all pages */
        FLASH->CR |= FLASH_CR_MER_Set;
        FLASH->CR |= FLASH_CR_STRT_Set;
        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOperation(EraseTimeout);
        if(status != FLASH_TIMEOUT)
        {
            /* Disable the MER Bit */
            FLASH->CR &= FLASH_CR_MER_Reset;
        }
    }
    /* Return the Erase Status */
    return status;
}

HW_FLASH_DEF FLASH_Status FLASH_EraseOptionBytes(void)
{
    uint16_t rdptmp = RDPRT_KEY;
    FLASH_Status status = FLASH_COMPLETE;
    /* Get the actual read protection Option Byte value */
    if(FLASH_GetReadOutProtectionStatus() != RESET)
    {
        rdptmp = 0x00;
    }
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(EraseTimeout);
    if(status == FLASH_COMPLETE)
    {
        /* Authorize the small information block programming */
        FALSH->OPTKEYR = FLASH_KEY1;
        FLASH->OPTKEYR = FLASH_KEY2;
        /* if the previous operation is completed, proceed to erase the option bytes */
        FLASH->CR |= FLASH_CR_OPTER_Set;
        FLASH->CR |= FLASH_CR_STRT_Set;
        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOperation(EraseTimeout);

        if(status == FLASH_COMPLETE)
        {
            /* if the erase operation is completed, disable the OPTER Bit */
            FLASH->CR &= FLASH_CR_OPTER_Reset;
            /* Enable the Option Bytes Programming operation */
            FLASH->CR |= FLASH_CR_OPTPG_Set;
            /* Restore the last read protection Option Byte value */
            OB->RDP = (uint16_t)rdptmp;
            /* Wait for last operation to be completed */
            status = FLASH_WaitForLastOperation(ProgramTimeout);

            if(status != FLASH_TIMEOUT)
            {
                FLASH->CR &= FLASH_CR_OPTPG_Reset;
            }
        }else{
            if(status != FLASH_TIMEOUT)
            {
                FLASH->CR &= FLASH_CR_OPTPG_Reset;
            }
        }
    }
    /* Return the erase status */
    return status;
}

HW_FLASH_DEF FLASH_Status FLASH_EnableWriteProtection(uint32_t FLASH_Pages)
{
    uint16_t WRP0_Data = 0xFFFF, WRP1_Data = 0xFFFF, WRP2_Data = 0xFFFF, WPR3_Data = 0xFFFF;

    FLASH_Status status = FLASH_COMPLETE;

    FLASH_Pages = (uint32_t)(~FLASH_Pages);
    WRP0_Data = (uint16_t)(FLASH_Pages & FLASH_WRP0_Mask);
    WRP1_Data = (uint16_t)((FLASH_Pages & FLASH_WRP1_Mask) >> 8);
    WRP2_Data = (uint16_t)((FLASH_Pages & FLASH_WRP2_Mask) >> 16);
    WPR3_Data = (uint16_t)((FLASH_Pages & FLASH_WRP3_Mask) >> 24);

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(ProgramTimeout);

    if(status == FLASH_COMPLETE)
    {
        /* Authorizes the small information block programming */
        FLASH->OPTKEYR = FLASH_KEY1;
        FLASH->OPTKEYR = FLASH_KEY2;
        FLAH->CR |= FLASH_CR_OPTPG_Set;
        if(WRP0_Data != 0xFF)
        {
            OB->WRP0 = WRP0_Data;
            /* Wait for last operation to be completed */
            status = FLASH_WaitForLastOperation(ProgramTimeout);
        }
        if((status == FLASH_COMPLETE) && (WRP1_Data != 0xFF))
        {
            OB->WRP1 = WRP1_Data;
            /* Wait for last operation to be completed */
            status = FLASH_WaitForLastOperation(ProgramTimeout);
        }
        if((status == FLASH_COMPLETE) && (WRP2_Data != 0xFF))
        {
            OB->WRP2 = WRP2_Data;
            /* Wait for last operation to be completed */
            status = FLASH_WaitForLastOperation(ProgramTimeout);
        }
        if((status == FLASH_COMPLETE) && (WPR3_Data != 0xFF))
        {
            OB->WRP3 = WPR3_Data;
            /* Wait for last operation to be completed */
            status = FLASH_WaitForLastOperation(ProgramTimeout);
        }
        if(status != FLASH_COMPLETE)
        {
            /* if the program operation is completed, disable the OPTPG Bit */
            FLASH->CR &= FLASH_CR_OPTPG_Reset;
        }
    }
    /* Return the write protection operation Status */
    return status;
}