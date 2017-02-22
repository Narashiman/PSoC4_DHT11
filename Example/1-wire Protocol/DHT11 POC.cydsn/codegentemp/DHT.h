/*******************************************************************************
* File Name: DHT.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_DHT_H) /* Pins DHT_H */
#define CY_PINS_DHT_H

#include "cytypes.h"
#include "cyfitter.h"
#include "DHT_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} DHT_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   DHT_Read(void);
void    DHT_Write(uint8 value);
uint8   DHT_ReadDataReg(void);
#if defined(DHT__PC) || (CY_PSOC4_4200L) 
    void    DHT_SetDriveMode(uint8 mode);
#endif
void    DHT_SetInterruptMode(uint16 position, uint16 mode);
uint8   DHT_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void DHT_Sleep(void); 
void DHT_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(DHT__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define DHT_DRIVE_MODE_BITS        (3)
    #define DHT_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - DHT_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the DHT_SetDriveMode() function.
         *  @{
         */
        #define DHT_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define DHT_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define DHT_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define DHT_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define DHT_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define DHT_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define DHT_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define DHT_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define DHT_MASK               DHT__MASK
#define DHT_SHIFT              DHT__SHIFT
#define DHT_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in DHT_SetInterruptMode() function.
     *  @{
     */
        #define DHT_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define DHT_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define DHT_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define DHT_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(DHT__SIO)
    #define DHT_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(DHT__PC) && (CY_PSOC4_4200L)
    #define DHT_USBIO_ENABLE               ((uint32)0x80000000u)
    #define DHT_USBIO_DISABLE              ((uint32)(~DHT_USBIO_ENABLE))
    #define DHT_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define DHT_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define DHT_USBIO_ENTER_SLEEP          ((uint32)((1u << DHT_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << DHT_USBIO_SUSPEND_DEL_SHIFT)))
    #define DHT_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << DHT_USBIO_SUSPEND_SHIFT)))
    #define DHT_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << DHT_USBIO_SUSPEND_DEL_SHIFT)))
    #define DHT_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(DHT__PC)
    /* Port Configuration */
    #define DHT_PC                 (* (reg32 *) DHT__PC)
#endif
/* Pin State */
#define DHT_PS                     (* (reg32 *) DHT__PS)
/* Data Register */
#define DHT_DR                     (* (reg32 *) DHT__DR)
/* Input Buffer Disable Override */
#define DHT_INP_DIS                (* (reg32 *) DHT__PC2)

/* Interrupt configuration Registers */
#define DHT_INTCFG                 (* (reg32 *) DHT__INTCFG)
#define DHT_INTSTAT                (* (reg32 *) DHT__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define DHT_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(DHT__SIO)
    #define DHT_SIO_REG            (* (reg32 *) DHT__SIO)
#endif /* (DHT__SIO_CFG) */

/* USBIO registers */
#if !defined(DHT__PC) && (CY_PSOC4_4200L)
    #define DHT_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define DHT_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define DHT_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define DHT_DRIVE_MODE_SHIFT       (0x00u)
#define DHT_DRIVE_MODE_MASK        (0x07u << DHT_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins DHT_H */


/* [] END OF FILE */
