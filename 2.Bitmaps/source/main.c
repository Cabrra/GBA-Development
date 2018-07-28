/*********************************************************************************
 * Includes
 ********************************************************************************/
#include "main.h"

/*********************************************************************************
 * Prototy0pes
 ********************************************************************************/
#define TRUE 1
volatile u16 *myPointer = BackBuffer1;
int mode = 3;

static void Page_Flip();


/*********************************************************************************
 * Program entry point
 ********************************************************************************/
0int main(void)
{
    Draw_Init();
    u16 color = 0;
     int x,y;
     x = y = 0;
     int incrementX, incrementY;
     incrementX = incrementY = 2;
     
    // Loop
    while(TRUE)
    {
        key_poll();
        
        
        if (F_CTRLINPUT_DOWN_PRESSED)
            Draw_Clear_DMA(color);
        else
            Draw_Clear(color); //, mode);
        

        DrawBitmap(x, y); //, mode);
        Draw_WaitVBlank();
        
        if (mode ==3)
        {
            if (F_CTRLINPUT_A_PRESSED)
                Draw_Present_DMA();
            else
                Draw_Present();
       }
       else
          Page_Flip();
          
        REG_DISPCNT |= BG2_ENABLE;
            
        color += 8;
        x+=incrementX;
        y+=incrementY;
        
        if (mode ==3)
        {
            if (x >= 176 || x <= 0)
                incrementX = -incrementX;
            if (y >= 96 || y <= 0)
                incrementY = -incrementY;
        }
        else
        {

            if (x >= 95 || x <= 0)
                incrementX = -incrementX;
            if (y >= 63 || y <= 0)
                incrementY = -incrementY;
        }
        if (key_hit(KEY_START))
        {
            if (mode ==3)
            {
                mode = 5;
                SetMode(0x5);

                if (x >= 95)
                    x = 94;
                if (y >= 63)
                    y = 62;
                    
                (*backdrop) = 0x7F00;
            }
            else
            {
                mode = 3;
                SetMode(0x3);
                
                u16 new_dispcnt = REG_DISPCNT | BACKBUFFER;
	            REG_DISPCNT = new_dispcnt;
	            myPointer = BackBuffer2;
            }
        }
    }
}

static void Page_Flip()
{
//	if(REG_DISPCNT & BACKBUFFER)
//        myPointer = (u16*)((u32) BackBuffer1);
//    else
//        myPointer = (u16*)((u32)BackBuffer2);
//
//    REG_DISPCNT ^= BACKBUFFER;

{
	u16 new_dispcnt = REG_DISPCNT ^ BACKBUFFER;
	REG_DISPCNT = new_dispcnt;

	if (new_dispcnt & BACKBUFFER)
		myPointer = BackBuffer1;
	else
	{
		// Vice versa
		myPointer = BackBuffer2;
	}
}
}
