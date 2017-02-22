/*******************************************************************************
* File Name: DHT.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_DHT_ALIASES_H) /* Pins DHT_ALIASES_H */
#define CY_PINS_DHT_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define DHT_0			(DHT__0__PC)
#define DHT_0_PS		(DHT__0__PS)
#define DHT_0_PC		(DHT__0__PC)
#define DHT_0_DR		(DHT__0__DR)
#define DHT_0_SHIFT	(DHT__0__SHIFT)
#define DHT_0_INTR	((uint16)((uint16)0x0003u << (DHT__0__SHIFT*2u)))

#define DHT_INTR_ALL	 ((uint16)(DHT_0_INTR))


#endif /* End Pins DHT_ALIASES_H */


/* [] END OF FILE */
