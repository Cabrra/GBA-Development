/*********************************************************************************
 * Includes
 ********************************************************************************/
#include "main.h"
#include "ninjagaiden.h"

/*********************************************************************************
 * Prototypes
 ********************************************************************************/

typedef struct _TransformData
{
int nX; // X position
int nY; // Y position
int nSclX; // X scale
int nSclY; // Y scale
int nDeg; // Degrees of rotation
int _Xcenter;
int _Ycenter;
} TransformData;

extern const unsigned short back_Palette[256];
//ninja
//extern const unsigned short ninjagaidenData[];
//extern const unsigned short ninjagaidenPalette[];
//rain
extern const unsigned char rain_Tiles[16320];
extern const unsigned char rain_Map[1024]; //32x32 map
//background
extern const unsigned char ground_Tiles[30912];
extern const unsigned short ground_Map[2048]; //64x32 map


static void WaitVBlank()
{
    while(REG_VCOUNT >= 160);
    while(REG_VCOUNT < 160);
}

static void Draw_PaletteInit()
{
    Memory_DMAFastCopy((void*)pallete, (void*)back_Palette, 128,DF_COPY_32);
    pallete[255] = 0x7FFF;
    Memory_DMAFastCopy((void*)ninjapallete, (void*)ninjagaidenPalette, 128, DF_COPY_32);
}

static void Draw_BGTileInit()
{
    //bg0 = ground
    Memory_DMAFastCopy((void*)BGstorage0, (void*)ground_Tiles, 7728,DF_COPY_32);
    //map0 = ground
    Memory_DMAFastCopy((void*)REG_MAP0, (void*)ground_Map, 1024, DF_COPY_32);
    REG_BG0 = (30<<8) | (1<<14) | (1 << 7) | (1);
    Memory_DMAFastCopy((void*)BGstorage2, (void*)rain_Tiles, 4080, DF_COPY_32);
    //map2 = rain
    Memory_DMAFastCopy((void*)REG_MAP2,(void*)rain_Map, 256, DF_COPY_32);
    REG_BG2 = (28<<8) | (2 << 2) | (1 << 7) | (1<<13) | (1<<14);

   //ninja
    Memory_DMAFastCopy((void*)BGstorage3, (void*)ninjagaidenData, sizeof(ninjagaidenData)/4, DF_COPY_32);
}

static void BGTransformation(M2* Final, int centerX, int centerY)//, int degree)
{

    REG_BG2PA =  Final->nX1;
    REG_BG2PB =  Final->nY1;
    REG_BG2PC =  Final->nX2;
    REG_BG2PD =  Final->nY2;

    REG_BG2X  =  Final->nW1;
    REG_BG2Y  =  Final->nW2;
}

static void OAMMemInit()
{
     memset((void*)oamspr, 0x0000, sizeof(oamspr[0]) *128);
     int i;
     for(i = 1; i <128; i++)
        oamspr[i].attr0 |= (1<<9);

    // 32x32 = 0010
    oamspr[0].attr0 |= (1<<13) | (80);
    oamspr[0].attr1 |= (1<<15) | (1<<12) | (104);
    oamspr[0].attr2 |= (1<<10);
    
}

static void DMAtoOAM()
{

     Memory_DMAFastCopy((void*)OAMVideo, (void*)oamspr, sizeof(oamspr[0])*128/4, DF_COPY_32);
    //(*backdrop) = RGB(0,0,0);
}

/*********************************************************************************
 * Program entry point
 ********************************************************************************/
int main(void)
{
    char left = 0;
    int back0x, back0y, back2x, back2y;
    int index, frame, incre;
    
    index = 0;
    frame = 0;
    incre = 32;

    back0x = 30;
    back0y = 90;
    back2x = 0;
    back2y = 160;

    REG_BG0X = back0x;
    REG_BG0Y = back0y;
    
    TransformData myData;

    myData.nX = back2x;
    myData.nY = back2y;
    myData.nSclX =0;
    myData.nSclY =0;
    myData.nDeg = 1;
    myData._Xcenter = 64;
    myData._Ycenter = 64;

    myData.nSclX = (1<<8);
    myData.nSclY = (1<<8);
    
    SetMode(MODE_1 | BG0_ENABLE | BG2_ENABLE | OAMMEM | IDSprite);
    OAMMemInit();
    Draw_PaletteInit();
    Draw_BGTileInit();
    DMAtoOAM();

    while(1)
    {

        DMAtoOAM();
        WaitVBlank();

        //OAMVideo[64] = oamspr;
            
        if (F_CTRLINPUT_RIGHT_PRESSED)
        {
            back0x += 3;
            REG_BG0X = back0x;
            
            myData.nDeg =60;
            oamspr[0].attr1 &= ~(1<<12);
            left = 0;
            
            frame++;
            if (frame >= 10)
            {
                if (index >= 96)
                     index = 0;
                index+= incre;
                
                frame =0;
            }
            
            oamspr[0].attr2 = 0;
            oamspr[0].attr2 |= (1<<10) | (index);
            
        }
        
        else if (F_CTRLINPUT_LEFT_PRESSED)
        {
            back0x -= 3;
            REG_BG0X = back0x;
            
            myData.nDeg =310;
            oamspr[0].attr1 |= (1<<12);
            left = 1;
            

            if (frame>= 10)
            {
                if (index >= 96)
                    index = 0;
                index+= incre;

                frame =0;
            }
            oamspr[0].attr2 = 0;
            oamspr[0].attr2 |= (1<<10) |(index);
        }
        else
        {
            myData.nDeg =0;
            index = 0;
           oamspr[0].attr2 = (1<<10);
        }

        
        back2y -=5;
        myData._Ycenter -=5;
        myData.nY = back2y;
        
        
        M2 translate;// = 0;
        M2 rotation;// = 0;
        M2 result;// = 0;
        M2 resultFinal;// = 0;
        M2 scale;// = 0;

        M2 end;

        Identity(&end);

        Translation(&end, myData._Xcenter, myData._Ycenter);

        Identity_FP_24_8(&scale);
        Identity_FP_16_16(&rotation);
        Identity(&translate);

        Translation(&translate, myData.nX - myData._Xcenter, myData.nY - myData._Ycenter);
        Scale_FP_24_8(&scale, myData.nSclX, myData.nSclX);
        Rotation_FP_16_16(&rotation, myData.nDeg);

        //Multiply
        //Math_M2Mult(M2* pResult, const M2* pLeft, const M2* pRight);
        Math_M2Mult(&resultFinal, &rotation, &translate);
        Math_M2Mult(&result, &scale, &resultFinal);
        Math_M2Mult(&resultFinal, &end, &result);

        //final
        Math_M2_FP_BitShift(&resultFinal, -16);
        BGTransformation(&resultFinal, myData._Xcenter, myData._Ycenter); //, myData._Ycenter, myData.nDeg);

        frame++;
    }}
