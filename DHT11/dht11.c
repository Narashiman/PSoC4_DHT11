/* ========================================
 * Authhor : Narashiman.P
 * Tested using CY8CKIT 49 Prototyping Kit PSoC 42xx for testing.
 * Changes done in global variable humidity and temperature.
 * 
 * ========================================
*/
int DHTread()
{    
    uint8 bits[5];
    uint8 cnt = 7;
    uint8 idx = 0;
    int   calc=0;
    int   timeout=0;
    for (i=0; i< 5; i++) 
        bits[i] = 0;
    DHTpin_Write(0u);
    CyDelay(19);
    DHTpin_Write(1u);
    while(DHTpin_Read()==1)
    {
        timeout++;
        if(timeout>500)
            return 99;  //Write overflow return function
    }
    while(DHTpin_Read()==0)
    {        
        timeout++;
        if(timeout>500)
            return 99;  //Write overflow return function
    }
    calc=timeout;
    timeout=0;
    while(DHTpin_Read()==1);
    for (i=0; i<40; i++)
    {
        timeout=0;
        while(DHTpin_Read()==0);
        while(DHTpin_Read()==1)
            timeout++;
        //Data acquiring area point
        if ((timeout) > (calc/2))
        //  UART_UartPutChar(49);
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
    sprintf(symbol,"Temperature:%c\tHumidity%c\r\n"temperature,humidity);
    UART_UartPutString(symbol);
    return 0;
}
/* [] END OF FILE */
