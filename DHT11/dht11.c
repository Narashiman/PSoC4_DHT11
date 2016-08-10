/* ========================================
 * Authhor : Narashiman.P
 * HAL not validated yet.
 * Changes done in global variable humidity and temperature.
 * 
 * ========================================
*/
typedef unsigned char uint8;
int humidity=0;
int temperature=0;
char symbol[50];

int DHTread()
{
    uint8 count=0;
    uint8 bits[5];
	uint8 cnt = 7;
	uint8 idx = 0;
    int timeout=0;
    int i=0;
    for (i=0; i< 5; i++) 
        bits[i] = 0;
    
    DHTpin_Write(0u);
    CyDelay(19);
    DHTpin_Write(1u);
    while(DHTpin_Read()==1)
    {
        CyDelayUs(1);
        timeout++;
        if(timeout>60)
        {
            return 99;
            break;
        }
    }
    timeout=0;
    while(DHTpin_Read()==0)
    {
        CyDelayUs(1);
        timeout++;
        if(timeout>80)
        {
            return 80;
        }
    }
    
    timeout=0;
    while(DHTpin_Read()==1)
    {
        CyDelayUs(1);
        timeout++;
        if(timeout>80)
        {
            return 70;
        }
    }    
    timeout=0;
    for (i=0; i<40; i++)
	{
        while(DHTpin_Read()==0)
        {
            CyDelayUs(10);
            timeout++;
            if(timeout>5)
                return 60;
        }
        count++;
        while(DHTpin_Read()==1)
        {
            CyDelay(7);
            count++;
        }
        if ((count) > 6) bits[idx] |= (1 << cnt);
        if (cnt == 0)   // next byte?
		{
			cnt = 7;    // restart at MSB
			idx++;      // next byte!
		}
		else cnt--;
	}
        humidity    = bits[0]; 
	    temperature = bits[2]; 

	    int sum = bits[0] + bits[2];  

        sprintf(symbol,"%d %d %d %d %d ",bits[0],bits[1],bits[2],bits[3],bits[4]);
        printf(symbol);
        
}


/* [] END OF FILE */
