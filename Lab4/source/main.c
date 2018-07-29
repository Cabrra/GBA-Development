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
    int xPos, yPos, scale, rotation, frame, mosFrame;
    xPos = yPos = frame = rotation = scale = mosFrame= 0;
    scale |= (1<<8);
    int incre = 1;
    int mosaicInc = 1;
    u8 mosaic = 0;
    
    u16 source, target;
    source = 31;
    target =  ~source;
    
    Blending(source, target);

    SetMode(MODE_0 | IDSprite | OAMMEM );
     
    Draw_PaletteInit();
    Draw_DataInit();
    OAMMemInit();
    DMAtoOAM();
    // Loop
    while(TRUE)
    {
        WaitVBlank();
        DMAtoOAM();
        
        //translate
        if (F_CTRLINPUT_RIGHT_PRESSED)
        {
            xPos+= 2;
        }
        if (F_CTRLINPUT_LEFT_PRESSED)
        {
            xPos-= 2;
        }
        if (F_CTRLINPUT_UP_PRESSED)
        {
            yPos-= 2;
        }
        if (F_CTRLINPUT_DOWN_PRESSED)
        {
            yPos+= 2;
        }
         if (F_CTRLINPUT_SELECT_PRESSED) //Scale
        {
            if (F_CTRLINPUT_L_PRESSED)
            {
                scale-= 2;
            }
            if (F_CTRLINPUT_R_PRESSED)
            {
                scale+= 2;
            }
        }
        else  //Rotate
        {
            if (F_CTRLINPUT_L_PRESSED)
            {
                rotation-= 2;
            }
            if (F_CTRLINPUT_R_PRESSED)
            {
                rotation+= 2;
            }
            
            if (rotation < 0)
                rotation += 360;
             if (rotation >= 360)
                rotation -= 360;
        }
        
        if (F_CTRLINPUT_START_PRESSED)
        {
            OAMMemInit();
            xPos = yPos =rotation = scale= 0;
            scale |= (1<<8);
            source = 31;
            incre = 1;
            target = ~source;
            Blending(source, target);
            mosaicInc = 1;
            mosaic = 0;
            UpdateMosaic(0, 0, mosaic, mosaic);
        }
        
        if (F_CTRLINPUT_A_PRESSED)
        {
            //blend
            if (frame == 4)
            {
                source -= incre;
                target = ~source;
                Blending(source, target);
                frame = 0;
                if (source == 0 || source == 31)
                    incre = -incre;
            }
            else
                frame++;
        }
        if (F_CTRLINPUT_B_PRESSED)
        {
            //mosaic
            if (mosFrame == 4)
            {
                mosaic += mosaicInc;
                UpdateMosaic(0, 0, mosaic, mosaic);
                mosFrame = 0;
                if (mosaic == 0 || mosaic == 15)
                    mosaicInc = -mosaicInc;
            }
            else
                mosFrame++;
        }

        OAMTranslate(xPos, yPos);
        OAMRotate(scale, rotation);
    }
}

