#include <stdlib.h>
#include "main.h"

volatile unsigned int myCount = 0;
volatile unsigned int mySec = 0;

extern volatile unsigned char myPrintflag;
extern volatile unsigned int secFlag;

IWRAM_CODE void MyHandler (void)
{
    myCount++;
    myPrintflag |= 1;

    if (myCount % 60 == 0)
    {
        mySec++;
        secFlag |=1;
    }
    
  REG_IF = 0x01;

}

