/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include "stdio.h"

static int temperature=99;
static int humidity=99;
static uint8 IState,i;

int DHTread() 
{     
   IState=CyEnterCriticalSection();  
   uint8 bits[5]; 
	uint8 cnt = 7; 
	uint8 idx = 0; 
   int   calc=0; 
   int   timeout=0; 
   for (i=0; i< 5; i++)  
       bits[i] = 0; 
   DHT_Write(0u); 
   CyDelay(19); 
   DHT_Write(1u); 
   while(DHT_Read()==1) 
   { 
       timeout++; 
       if(timeout>500) 
           goto r99;  //DHT error function 
   } 
   while(DHT_Read()==0) 
   {         
       timeout++; 
       if(timeout>500) 
           goto r99; //DHT error function 
   } 
   calc=timeout; 
   timeout=0; 
   while(DHT_Read()==1); 
   for (i=0; i<40; i++) 
	{ 
       timeout=0; 
       while(DHT_Read()==0); 
       while(DHT_Read()==1) 
           timeout++; 
       //Data acquiring point 
       if ((timeout) > (calc/2)) 
           bits[idx] |= (1 << cnt); 
       if (cnt == 0)   // next byte? 
   	{ 
   		cnt = 7;    // restart at MSB 
   		idx++;      // next byte! 
   	} 
   	else cnt--; 
   } 
   humidity    = bits[0];  
   temperature = bits[2];  
   CyExitCriticalSection(IState); 
   CyDelay(1); 
   return 0; 
   r99:    //Goto label for error in DHT reading 
       humidity    = 99;  
       temperature = 99;  
       CyExitCriticalSection(IState); 
       return 99; 
}
int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    char outputstring[40];
    UART_Start();
    
    for(;;)
    {
        DHTread();
        sprintf(outputstring,"Temperature=%i Humidity= %i \r\n",temperature,humidity);
        UART_UartPutString(outputstring);
        CyDelay(5000);  //Delay in milli seconds.        
    }
}

/* [] END OF FILE */
