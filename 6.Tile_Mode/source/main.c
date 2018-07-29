/*********************************************************************************
 * Includes
 ********************************************************************************/
#include "main.h"
#include "math.h"

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

#define TRUE 1



extern const unsigned char super_Tiles[9664];
extern const unsigned char super_Map[256];
extern const unsigned short super_Palette[256];
extern const int g_nCos_FP_16_16[360];
extern const int g_nSin_FP_16_16[360];

static void Math_M2Identity(M2* pResult)
{
    //memset((int*)pResult->nX1, 0, 36);
    pResult->nX1 = 0;
    pResult->nY1 = 0;
    pResult->nW1 = 0;
    pResult->nX2 = 0;
    pResult->nY2 = 0;
    pResult->nW2 = 0;
    pResult->nX3 = 0;
    pResult->nY3 = 0;
    pResult->nW3 = 0;
    
    pResult->nX1 = 1;
    pResult->nY2 = 1;
    pResult->nW3 = 1;
}

static void Math_M2Identity_FP_24_8(M2* pResult)
{
    Math_M2Identity(pResult);
    Math_M2_FP_BitShift(pResult, 8);
}

static void Math_M2Identity_FP_16_16 (M2* pResult)
{
    Math_M2Identity(pResult);
    Math_M2_FP_BitShift(pResult, 16);
}

static void Math_M2TranslationSet(M2* pResult, int x, int y)
{
    pResult->nW1 = x;
    pResult->nW2 = y;
}

static void Math_M2RotationSet_FP_16_16(M2* pResult, int x)
{
    pResult->nX1 = g_nCos_FP_16_16[x];
    pResult->nX2 = g_nSin_FP_16_16[x];
    pResult->nY1 = -g_nSin_FP_16_16[x];
    pResult->nY2 = g_nCos_FP_16_16[x];
}

static void Math_M2ScaleSet_FP_24_8 (M2* pResult, int x, int y)
{
    pResult->nX1 = x;
    pResult->nY2 = y;
}

static void PaletteInit()
{
    Memory_DMAFastCopy((void*)pallete, (void*)super_Palette, 128,DF_COPY_32);
}

static void BGTileInit()
{
    //bg0
    Memory_DMAFastCopy((void*)BGstorage , (void*)super_Tiles, 4832,DF_COPY_32);
    //map0
    Memory_DMAFastCopy((void*)REG_MAP , (void*)super_Map, 128, DF_COPY_32);
    REG_BG = (30<<8) | (1<<13);
}

static void BGTransformation(M2* Final, int centerX) //, int centerY, int degree)
{

    REG_BG2PA =  Final->nX1;
    REG_BG2PB =  Final->nY1;
    REG_BG2PC =  Final->nX2;
    REG_BG2PD =  Final->nY2;
    
    REG_BG2X  =  Final->nW1;
    REG_BG2Y  =  Final->nW2;

    //step2 vector from center to origin (0,0)
    //(-120,-80)
//    //originX, originY;
//    int posX, posY;
//
//    posX = centerX - 120;
//    posY = centerY -80;
//
//    M2 helpRot;
//    Math_M2Identity_FP_16_16(&helpRot);
//    Math_M2RotationSet_FP_16_16(&helpRot, degree);
//
//    M2 helpVector;
//    Math_M2Identity(&helpVector);
//    Math_M2TranslationSet(&helpVector, posX, posY);
//
//    M2 result;
//    Math_M2Mult(&result, &helpVector, &helpRot);
//    //step3
//
//     Math_M2_FP_BitShift(&result, -16);
//
//    REG_BG2X  =  result.nX1 + centerX;
//    REG_BG2Y  =  result.nY2 + centerY;
//
        
}

static void WaitVBlank()
{
    while(REG_VCOUNT >= 160);
    while(REG_VCOUNT < 160);
}

/*********************************************************************************
 * Program entry point
 ********************************************************************************/
int main(void)
{
    SetMode(MODE_2 | BG2_ENABLE);
    
    PaletteInit();
    BGTileInit();
    
    TransformData myData;
    
    myData.nX = 0;
    myData.nY = 0;
    myData.nSclX =0;
    myData.nSclY =0;
    myData.nDeg =0;
    myData._Xcenter = 64;
    myData._Ycenter = 64;
    
    myData.nSclX = (1<<8);
    myData.nSclY = (1<<8);
    
    

    // Loop
    while(TRUE)
    {
        WaitVBlank();
        if (F_CTRLINPUT_RIGHT_PRESSED)
        {
             myData.nX-= 2;
             myData._Xcenter-= 2;
        }
        if (F_CTRLINPUT_LEFT_PRESSED)
        {
             myData.nX+= 2;
             myData._Xcenter+= 2;
        }
        if (F_CTRLINPUT_UP_PRESSED)
        {
            myData.nY+= 2;
            myData._Ycenter+= 2;
        }
        if (F_CTRLINPUT_DOWN_PRESSED)
        {
            myData.nY-= 2;
            myData._Ycenter-= 2;
        }
        //scale
        if (F_CTRLINPUT_A_PRESSED)
        {
            myData.nSclX +=2;
            myData.nSclY +=2;
        }
        if (F_CTRLINPUT_B_PRESSED)
        {
            myData.nSclX -=2;
            myData.nSclY -=2;
        }
        //rotate
        if (F_CTRLINPUT_L_PRESSED)
        {
               myData.nDeg -= 2;
               if (myData.nDeg < 0)
                myData.nDeg = 359;
        }
        if (F_CTRLINPUT_R_PRESSED)
        {
            myData.nDeg += 2;
            if (myData.nDeg > 359)
                myData.nDeg = 0;
        }

        if (F_CTRLINPUT_START_PRESSED)
        {
            myData.nX = 0;
            myData.nY = 0;
            myData.nSclX = 0;
            myData.nSclY = 0;
            myData.nDeg = 0;
            myData._Xcenter = 64;
            myData._Ycenter = 64;

            myData.nSclX = (1<<8);
            myData.nSclY = (1<<8);
        }
        
        M2 translate;// = 0;
        M2 rotation;// = 0;
        M2 scale;// = 0;
        M2 result;// = 0;
        M2 resultFinal;// = 0;
        
        M2 end;
        
        Math_M2Identity(&end);
        
        Math_M2TranslationSet(&end, 64, 64);
        
        Math_M2Identity_FP_24_8(&scale);
        Math_M2Identity_FP_16_16(&rotation);
        Math_M2Identity(&translate);
        
        Math_M2TranslationSet(&translate, myData.nX - 64, myData.nY - 64);
        Math_M2ScaleSet_FP_24_8(&scale, myData.nSclX, myData.nSclX);
        Math_M2RotationSet_FP_16_16(&rotation, myData.nDeg);

        //Multiply
        //Math_M2Mult(M2* pResult, const M2* pLeft, const M2* pRight);
        Math_M2Mult(&resultFinal, &rotation, &translate);
        Math_M2Mult(&result, &scale, &resultFinal);
        Math_M2Mult(&resultFinal, &end, &result);

        //final
        Math_M2_FP_BitShift(&resultFinal, -16);
        BGTransformation(&resultFinal, myData._Xcenter); //, myData._Ycenter, myData.nDeg);


    }
}

