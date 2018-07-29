/****
Direct Sound
****/

#include "main.h"

extern const unsigned int mysize;
extern const signed char mystuffa[];
extern const signed char mario[];
extern const unsigned int marioSize;
extern const char g_ucFont[];


u32 key_curr = 0;
u32 key_prev = 0;

char HELP[] = {"PRESS KEY L/R TO START/STOP"};

// stops playing audio track
void stopSound(void) {
  REG_TM0CNT = 0;
  REG_DMA1CNT = 0;
  REG_SOUNDCNT_X = 0;
  REG_SOUNDCNT_H = 0;
  numberOfSamples = 0;
}

static void WaitForBlank()
{
    while(REG_VCOUNT >= 160);
    while(REG_VCOUNT < 160);
}

// start or restarts playing audio track
void startSound(void *pBuffer, int position, int length) {

  // stop playing
  stopSound();

  // total number of audio samples to play
  numberOfSamples = length;

  // starting position of audio samples to play
  samplePosition = position;

  // calculate how many clocks per sample
  clocksPerSample = CLKOSC/samplesPerSecond;

  //output to both left & right audio channels and reset the FIFO
  REG_SOUNDCNT_H = SOUNDCNT_H_A_RIGHT_CHANNEL|SOUNDCNT_H_A_LEFT_CHANNEL|SOUNDCNT_H_A_FIFO_RESET;

  //enable all sound
  REG_SOUNDCNT_X = SOUNDCNT_X_MASTER_ENABLE;

  // dma synchronizes to fifo transfers (replace with your own function)
  //xferDma1((void *)&REG_FIFOA, pBuffer+position, length-position, (DMAXCNT_DSTCONST|DMAXCNT_COPY32|DMAXCNT_REPEAT|DMAXCNT_FIFO|DMAXCNT_ENABLE));
    Memory_DMAFastCopy((void *)&REG_FIFOA, pBuffer+position, length-position, (DMAXCNT_DSTCONST|DMAXCNT_COPY32|DMAXCNT_REPEAT|DMAXCNT_FIFO|DMAXCNT_ENABLE));

  // start timer0 to interrupt once per sample period
  REG_TM0D = 65536 - clocksPerSample;
  REG_TM0CNT = TMXCNT_INTERRUPT|TMXCNT_ENABLE;
}



static void DrawPixel3(int x, int y, unsigned short c)
{
     Map_Begin[y * 240 + x] = c;
}

static void DrawLetter(int left, int top, char letter, u16 color)
{
    int x, y;
    int draw;
    
    for(y = 0; y < 8; y++)
    {
        for (x = 0; x < 8; x++)
        {
            draw = g_ucFont[(letter-32) * 64 + y * 8 + x];

            if (draw)
                DrawPixel3(left + x, top + y, color);
            else
                DrawPixel3(left + x, top + y, 0x0000);
        }
    }
}

static void ParseString(int left, int top, char* string, u16 color)
{
    int help = 0;
    while (string[help])
    {
        DrawLetter(left + (8* help), top, string[help], color);
        help++;
    }
}

static inline void key_poll()
{
    key_prev= key_curr;
    key_curr= ~R_CTRLINPUT & Key_MASK;
}

static inline u32 key_het(u32 key)
{   return ( key_curr &~ key_prev) & key;  }

static inline u32 key_held(u32 key)
{   return ( key_curr &  key_prev) & key;  }

int main(void) {

  char cstr[24];
  int homework = TRUE;
  samplesPerSecond = 8000;
  numberOfSamples = samplePosition = clocksPerSample = 0;

  // video mode 3 using background #2
  REG_DISPCNT = DISPCNT_VM3|DISPCNT_BG2;
  //REG_DISPCNT |= (0x3 | 0x400);


  // setup interrupt
  REG_IME = IME_DISABLE;
  IRQ_VECTOR = (unsigned long)MyHandler;
  REG_IE = IE_TIMER0;
  REG_IME = IME_ENABLE;

  // print title and help menu (replace with your own functions)
//  cprint64(2, 4, "THE HITCHHIKERS GUIDE", WHITE);
//  cprint64(4, 8, "TO THE GALAXY", WHITE);
//  cprint64(15, 1, HELP, WHITE);
  
  ParseString(30, 1, "KNOW YOUR MEME:", WHITE);
  ParseString(40, 20, "VIDEOGAME MODE", WHITE);
  ParseString(7, 150, HELP, WHITE);

  while(FOREVER) {

    // reads key states (replace with your own function)
	//processKeys(KEY_MASK);
	key_poll();

    // if KEY_R toggled, stops playing (replace with your own function)
   // if (keysToggled(KEY_R)) stopSound();
   if (key_het(Key_R))stopSound();

    // if KEY_L toggled, starts or restarts playing (replace with your own function)
    //if (keysToggled(KEY_L)) startSound((void*)BUTTON, 0, sizeof_BUTTON());
    //if (key_het(Key_L))startSound((void*)mystuffa, 0, mysize);
     if (key_het(Key_L))startSound((void*)mario, 0, marioSize);


    if (homework)
    {	
        int inver = 0;
		// implement the homework audio track speed changes here 
		if (key_het(Key_START))
		{
            samplesPerSecond = 8000;
            inver = 1;
        }
        if (key_het(Key_UP))
        {
            samplesPerSecond+=1000;
             if (samplesPerSecond> 40000)
                samplesPerSecond=40000;
            inver = 1;
        }
        if (key_het(Key_DOWN))
        {
            samplesPerSecond-=1000;
            if (samplesPerSecond< 100)
                samplesPerSecond=100;
            inver = 1;
        }
        if (key_held(Key_RIGHT))
        {
            samplesPerSecond+=100;
            if (samplesPerSecond> 40000)
                samplesPerSecond=40000;
            inver = 1;
        }
        if (key_held(Key_LEFT))
        {
            samplesPerSecond-=100;
            if (samplesPerSecond< 100)
                samplesPerSecond=100;
            inver = 1;
        }
        
        if ( inver ==1)
            //startSound((void*)mystuffa, samplePosition, mysize);
            startSound((void*)mario, samplePosition, marioSize);

    }

    // wait for vertical blank period (replace with your own function)
    //waitVBlank();
    WaitForBlank();

    if (homework)
    {
		// display the samplesPerSecond here
	snprintf(cstr, sizeof(cstr), "SAMPLE RATE %05d", samplesPerSecond); //ParseString(7, 12, cstr, WHITE);
	ParseString(50, 100 , cstr, WHITE);
    }

    // replace with your own function
	snprintf(cstr, sizeof(cstr), "%05d", samplePosition); //ParseString(7, 12, cstr, WHITE);
	ParseString(100, 70 , cstr, WHITE);
  }

  return 0;
}
  
