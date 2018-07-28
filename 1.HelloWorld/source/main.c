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
    //REG_DISPCNT is the address
    //Map_Begin
    SetMode(0x3 | 0x400);
    
    char* word = (char*)"HELLO WORLD";
    unsigned short check = 0xFFFF;
    // Loop
    while(TRUE)
    {
         key_poll();
            //H
            if (key_hit(KEY_A))
                check ^= (1<<0);
            if (key_hit(KEY_B))
                check ^= (1<<1);
            if (key_hit(KEY_SELECT))
                check ^= (1<<2);
            if (key_hit(KEY_START))
               check ^= (1<<3);
            if (key_hit(KEY_RIGHT))
                check ^= (1<<4);
            if (key_hit(KEY_LEFT))
                check ^= (1<<5);
            if (key_hit(KEY_UP))
               check ^= (1<<6);
            if (key_hit(KEY_DOWN))
                check ^= (1<<7);
            if (key_hit(KEY_R))
                check ^= (1<<8);
            if (key_hit(KEY_L))
                check ^= (1<<9);
                

            if ((check & (1 << 0)) == 0)
                DrawLetter(25, 25, word[0], 0);
            else
                DrawLetter(25, 25, word[0], 0x7FFF);
            //E
            if ((check & (1 << 1)) == 0)
                DrawLetter(33, 25, word[1], 0);
            else
                DrawLetter(33, 25, word[1], 0x7FFF);
            //L
           if ((check & (1 << 2)) == 0)
                DrawLetter(41, 25, word[2], 0);
            else
                DrawLetter(41, 25, word[2], 0x7FFF);
            //L
             if ((check & (1 << 3)) == 0)
                DrawLetter(49, 25, word[3], 0);
            else
                DrawLetter(49, 25, word[3], 0x7FFF);
            //O
            if ((check & (1 << 4)) == 0)
                DrawLetter(57, 25, word[4], 0);
            else
                DrawLetter(57, 25, word[4], 0x7FFF);
            //W
           if ((check & (1 << 5)) == 0)
                DrawLetter(73, 25, word[6], 0);
            else
                DrawLetter(73, 25, word[6], 0x7FFF);
            //O
           if ((check & (1 << 6)) == 0)
                DrawLetter(81, 25, word[7], 0);
            else
                DrawLetter(81, 25, word[7], 0x7FFF);
            //R
            if ((check & (1 << 7)) == 0)
                DrawLetter(89, 25, word[8], 0);
            else
                DrawLetter(89, 25, word[8], 0x7FFF);
            //R
            if ((check & (1 << 8)) == 0)
                DrawLetter(97, 25, word[9], 0);
            else
                DrawLetter(97, 25, word[9], 0x7FFF);
            //L
           if ((check & (1 << 9)) == 0)
                DrawLetter(105, 25, word[10], 0);
            else
                DrawLetter(105, 25, word[10], 0x7FFF);


    }
}

