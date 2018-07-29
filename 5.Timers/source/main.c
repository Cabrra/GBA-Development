/*********************************************************************************
 * Includes
 ********************************************************************************/
#include "main.h"
#include "memory.h"
/*********************************************************************************
 * Prototypes
 ********************************************************************************/

extern void MyHandler (void);
extern volatile unsigned int myCount;
extern volatile unsigned int mySec;

volatile unsigned int myPrintflag = 0;
volatile unsigned int secFlag = 0;

extern const char g_ucFont[];

#pragma GCC push_options

//#define RUN_FAST
//#ifdef RUN_FAST
//    #pragma GCC optimize ("O2")
//#else
//    #pragma GCC optimize ("O0")
//#endif

/*********************************************************************************
 * Program entry point
 ********************************************************************************/
 
IWRAM_CODE static void WaitVBlank()
{
    while(REG_VCOUNT >= 160) {};
    while(REG_VCOUNT < 160){};
}

static void PaletteInit()
{
    pallete[0] = 0x0000;
    pallete[1] = 0x7FFF;
}

static void BGTileInit()
{
    Memory_DMAFastCopy((void*)BG0Storage , (void*)g_ucFont, 992, DF_COPY_32);
    REG_BG0 = (30<<8) | (1<<14) | (1 << 7);
}

IWRAM_CODE static void ParseChar(int x, int y, char* string)
{
    int help = 0;
    //int aux[16];
    
    while (string[help])
    {
        REG_MAP0[y * 32 +x + help] = (string[help]) - 32;
        help++;
    }
}

IWRAM_CODE int main(void)
{
    SetMode(0x0 | 0x100);
    PaletteInit();
    BGTileInit();
    
    int fram, fpsCount;
    fram = fpsCount = 0;
    
    REG_WSCNT |= (1<<3) | (1<<4) | (1<<14);
    
    //interrupt stuff
     REG_IME = 0x00;
    //point interrupt handler to custom function
    REG_INTERRUPT = (u32)&MyHandler;
    //enable hblank interrupt (bit 4)
    REG_IE = 0x0001;
    //enable vblank status (bit 3)
    REG_DISPSTAT |= 0x18;
    //enable interrupts
    REG_IME = 0x01;
    
    char bliank[10];
    char siucond[10];
    char friamis[10];
    char fipis[10];

    ParseChar(0, 0, "VBLANKS:");
    ParseChar(0, 2, "SECONDS:");
    ParseChar(0, 4, "FRAMES:");
    ParseChar(0, 6, "FPS:");
    
    // Loop
    while(1)
    {
        //sec = mySec;

        fram++;
        fpsCount++;

        if (secFlag)
        {
            secFlag =0;

            sprintf(siucond, " %u", mySec);
            ParseChar(13, 2, siucond);
            sprintf(fipis, " %-8u", fpsCount);
            ParseChar(13, 6, fipis);

            fpsCount = 0;
        }

        if (myPrintflag)
        {
            myPrintflag = 0;
            
            if (!(~R_CTRLINPUT & 0x0001)) WaitVBlank();
            if (~R_CTRLINPUT & 0x0080) WaitVBlank();

            sprintf(bliank, " %u", myCount);
            ParseChar(13, 0, bliank);
            sprintf(friamis, " %u", fram);
            ParseChar(13, 4, friamis);

        }
    }
}

