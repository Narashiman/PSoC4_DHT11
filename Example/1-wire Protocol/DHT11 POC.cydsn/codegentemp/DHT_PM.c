/*******************************************************************************
* File Name: DHT.c  
* Version 2.20
*
* Description:
*  This file contains APIs to set up the Pins component for low power modes.
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "DHT.h"

static DHT_BACKUP_STRUCT  DHT_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: DHT_Sleep
****************************************************************************//**
*
* \brief Stores the pin configuration and prepares the pin for entering chip 
*  deep-sleep/hibernate modes. This function must be called for SIO and USBIO
*  pins. It is not essential if using GPIO or GPIO_OVT pins.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None 
*  
* \sideeffect
*  For SIO pins, this function configures the pin input threshold to CMOS and
*  drive level to Vddio. This is needed for SIO pins when in device 
*  deep-sleep/hibernate modes.
*
* \funcusage
*  \snippet DHT_SUT.c usage_DHT_Sleep_Wakeup
*******************************************************************************/
void DHT_Sleep(void)
{
    #if defined(DHT__PC)
        DHT_backup.pcState = DHT_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            DHT_backup.usbState = DHT_CR1_REG;
            DHT_USB_POWER_REG |= DHT_USBIO_ENTER_SLEEP;
            DHT_CR1_REG &= DHT_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(DHT__SIO)
        DHT_backup.sioState = DHT_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        DHT_SIO_REG &= (uint32)(~DHT_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: DHT_Wakeup
****************************************************************************//**
*
* \brief Restores the pin configuration that was saved during Pin_Sleep().
*
* For USBIO pins, the wakeup is only triggered for falling edge interrupts.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None
*  
* \funcusage
*  Refer to DHT_Sleep() for an example usage.
*******************************************************************************/
void DHT_Wakeup(void)
{
    #if defined(DHT__PC)
        DHT_PC = DHT_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            DHT_USB_POWER_REG &= DHT_USBIO_EXIT_SLEEP_PH1;
            DHT_CR1_REG = DHT_backup.usbState;
            DHT_USB_POWER_REG &= DHT_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(DHT__SIO)
        DHT_SIO_REG = DHT_backup.sioState;
    #endif
}


/* [] END OF FILE */
