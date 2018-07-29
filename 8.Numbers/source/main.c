/*********************************************************************************
 * Includes
 ********************************************************************************/
#include "main.h"

/*********************************************************************************
 * Prototypes
 ********************************************************************************/
 
 u32 key_curr = 0;
u32 key_prev = 0;

extern const char g_ucFont[];

static void WaitForBlank()
{
    while(REG_VCOUNT >= 160);
    while(REG_VCOUNT < 160);
}

static inline void key_poll()
{
    key_prev= key_curr;
    key_curr= ~R_CTRLINPUT & Key_MASK;
}

static inline u32 key_hit(u32 key)
{   return ( key_curr &~ key_prev) & key;  }


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

static void ParseStringSigned(int left, int top, char* string)
{
    int help = 0;
    u16 cul = rand()%32766;
    cul++;
    while (string[help])
    {
        DrawLetter(left + (8* help), top, string[help], cul);
        help++;
    }
}

static void ParseStringOnes(int left, int top, char* string)
{
    int help = 0;

    while (string[help])
    {
        u16 cul = rand()%32766;
        cul++;
        DrawLetter(left + (8* help), top, string[help], cul);
        help++;
    }
}

static void DrawLetterTwos(int left, int top, char letter)
{
    int x, y;
    int draw;

    for(y = 0; y < 8; y++)
    {
        for (x = 0; x < 8; x++)
        {
            u16 cul = rand()%32766;
            cul++;
            draw = g_ucFont[(letter-32) * 64 + y * 8 + x];

            if (draw)
                DrawPixel3(left + x, top + y, cul);
            else
                DrawPixel3(left + x, top + y, 0x0000);
        }
    }
}

static void ParseStringTwos(int left, int top, char* string)
{
    int help = 0;

    while (string[help])
    {
        DrawLetterTwos(left + (8* help), top, string[help]);
        help++;
    }
}

static void DecToBin(char* result, int integir)
{
    int help = 0;
    for( ; help < 8; help++)
    {
        if ((integir & (1 << help)))
            result[7 - help] = '1';
        else
            result[7 -help] = '0';
    }
    result[8] = '\0';
}


/*********************************************************************************
 * Program entry point
 ********************************************************************************/
int main(void)
{

    char valChar[5];
    char signChar[9];
    
    SetMode(0x3 | 0x400);
    ParseString(0, 10, "SIGNED MAGNITUDE:", 0x7FFF);
    ParseString(0, 28, "ONE'S COMPLIMENT:", 0x7FFF);
    ParseString(0, 46, "TWO'S COMPLIMENT:", 0x7FFF);
    ParseString(0, 64, "INTEGER VALUE:", 0x7FFF);
    
    int value = 0;
    int checkVal;
    char update =0;
    

    snprintf(valChar, sizeof(valChar), "%-5d", value);
    ParseString(170, 64, valChar, 0x7FFF);
    DecToBin(signChar, value);
    ParseString(150, 10, signChar, 0x7FFF);
    ParseString(150, 28, signChar, 0x7FFF);
    ParseString(150, 46, signChar, 0x7FFF);
           
    // Loop
    while(1)
    {
        key_poll();
        

        
        if(key_hit(Key_RIGHT))
        {
            value+=1;
            update = 1;
        }
        if(key_hit(Key_LEFT))
        {
            value-=1;
            update = 1;
        }

        if(key_hit(Key_UP))
        {
            value+=10;
            update = 1;
        }
        if(key_hit(Key_DOWN))
        {
            value-=10;
            update = 1;
        }
            
        if( value > 127)
            value = 127;
        if ( value < -128)
            value = -128;
            
        int aux = value;
        
        WaitForBlank();
        
        if (update ==1)
        {

            snprintf(valChar, sizeof(valChar), "%-5d", value);
            ParseString(170, 64, valChar, 0x7FFF);


            if (value>=0) //show in binary
            {

                DecToBin(signChar, aux);

                ParseStringSigned(150, 10, signChar);
                ParseStringOnes(150, 28, signChar);
                ParseStringTwos(150, 46, signChar);
            }
            else
            {
                if (value == -128)
                {
                    ParseString(150, 10, "0000000000", 0x0000);
                    ParseString(150, 28, "0000000000", 0x0000);
                }
                else
                {
                    //signed
                    checkVal = -value;
                    checkVal |= (1<<7);
                    DecToBin(signChar, checkVal);
                    ParseStringSigned(150, 10, signChar);

                    //ONES
                    checkVal = -value;
                    checkVal = ~checkVal;
                    DecToBin(signChar, checkVal);
                    ParseStringOnes(150, 28, signChar);
                }

                //TWOS
                checkVal = -(value+1);
                checkVal = ~checkVal;

                DecToBin(signChar, checkVal);
                ParseStringTwos(150, 46, signChar);
            }
            update =0;
        }
    }
}

