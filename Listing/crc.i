#line 1 "..\\..\\User\\Alogrisem\\src\\CRC.c"
#line 1 "..\\..\\User\\Alogrisem\\inc\\CRC.h"



int checkCRC(int chCurrByte, int chNextByte);

#line 2 "..\\..\\User\\Alogrisem\\src\\CRC.c"












int checkCRC(int chCurrByte, int chNextByte)
{
	int nMask;

	for(nMask = 0x80; nMask > 0; nMask = nMask>>1)
	{
   		if ((chCurrByte & 0x80) != 0)   
  		{ 
    		chCurrByte <<= 1;     
    		if ( (chNextByte & nMask) != 0) 
    		{
     			chCurrByte |= 1;
    		}	
    		chCurrByte ^= 7;     
   		}
   		else         
   		{  
    		chCurrByte <<= 1;     
    		if ( (chNextByte & nMask) != 0) 
    		{
     			chCurrByte |= 1;
    		}
   		}
	}
	return chCurrByte;
}
