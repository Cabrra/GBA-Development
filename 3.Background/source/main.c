/*********************************************************************************
 * Includes
 ********************************************************************************/
#include "main.h"

/*********************************************************************************
 * Prototypes
 ********************************************************************************/
#define TRUE 1

/*********************************************************************************
 * Program entry point
 ********************************************************************************/
int main(void)
{

    int back0x, back0y, back1x, back1y, back2x, back2y, back3x, back3y;
    int index, frame, incre;
    index = 0;
    frame = 0;
    incre = 1;
    
    back0x = 30;
    back0y = 90;
    back1x = 20;
    back1y = 105;
    back2x = 100;
    back2y = 121;
    back3x = 200;
    back3y = 260;
    
    REG_BG0X = back0x;
    REG_BG0Y = back0y;
    REG_BG1X = back1x;
    REG_BG1Y = back1y;
    REG_BG2X = back2x;
    REG_BG2Y = back2y;
    REG_BG3X = back3x;
    REG_BG3Y = back3y;
    
    SetMode(MODE_0 | BG0_ENABLE | BG1_ENABLE | BG2_ENABLE | BG3_ENABLE );
    Draw_PaletteInit();
    Draw_BGTileInit();
    // Loop
    while(TRUE)
    {
        if (frame == 20)
        {
            index+= incre;
            if (index ==2 || index == 0)
                incre= - incre;
                
            frame = 0;
        }
        
        REG_MAP2[65] = index;
        WaitVBlank();
        
        if (F_CTRLINPUT_RIGHT_PRESSED)
        {
            back0x += 6;
            back1x += 3;
            back2x += 1;

            REG_BG0X = back0x;
            REG_BG1X = back1x;
            REG_BG2X = back2x;
        }

         if (F_CTRLINPUT_LEFT_PRESSED)
        {
            back0x -= 6;
            back1x -= 3;
            back2x -= 1;

            REG_BG0X = back0x;
            REG_BG1X = back1x;
            REG_BG2X = back2x;
        }
        frame++;
    }
}

