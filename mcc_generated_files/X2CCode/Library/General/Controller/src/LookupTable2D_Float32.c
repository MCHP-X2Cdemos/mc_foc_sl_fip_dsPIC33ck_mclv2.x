/*
 * Copyright (c) 2013, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
 * All rights reserved.
 */
/*
 * This file is licensed according to the BSD 3-clause license as follows:
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the "Linz Center of Mechatronics GmbH" and "LCM" nor
 *       the names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL "Linz Center of Mechatronics GmbH" BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/*
 * This file is part of X2C. http://x2c.lcm.at/
 * $LastChangedRevision: 1658 $
 */
/* USERCODE-BEGIN:Description                                                                                         */
/* Description: Two dimensional look-up table with selectable number of entries */
/* USERCODE-END:Description                                                                                           */
#include "LookupTable2D_Float32.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(LookupTable2D_Float32_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
/* Inputs */
#define IN_X        (*pTLookupTable2D_Float32->x)
#define IN_Y        (*pTLookupTable2D_Float32->y)

/* Outputs */
#define OUT         (pTLookupTable2D_Float32->Out)

/* Parameters */
#define TABLE_DATA   (pTLookupTable2D_Float32->Table)
#define DIM_X        (pTLookupTable2D_Float32->dimX)
#define DIM_Y        (pTLookupTable2D_Float32->dimY)

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void LookupTable2D_Float32_Update(LOOKUPTABLE2D_FLOAT32 *pTLookupTable2D_Float32)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
    float32 tmp;
    uint16 idxx, idxy, idx;
    float32 fact, factx, facty, factxy, deltax, deltay, deltaxy;

    idxx   = (uint16)IN_X;    /*  x  */
    idxy   = (uint16)IN_Y;    /*  y  */

    deltax  = IN_X - idxx;                                /* dx  */
    deltay  = IN_Y - idxy;                                /* dy  */
    if (IN_X < 0)
    {
        /* index below lower boundary -> cutoff */
        idxx = 0;
        deltax = 0; /* cut-off mode*/
    }
    else if ((uint16)IN_X >= DIM_X)
    {
        /* index above higher boundary -> cutoff */
        idxx = DIM_X;
        deltax = 0;
    }
    if (IN_Y < 0)
    {
        /* index below lower boundary -> cutoff */
        idxy = 0;
        deltay = 0; /* cut-off mode*/
    }
    else if ((uint16)IN_Y >= DIM_Y)
    {
        /* index above higher boundary -> cutoff */
        idxy = DIM_Y;
        deltay = 0;
    }
    idx     = idxx + (idxy*(DIM_X+1));
    deltaxy = deltax * deltay;   /* dxy */

    fact   = TABLE_DATA[idx];                           /* f(x  ,y)   */
    factx  = TABLE_DATA[idx + 1];                       /* f(x+1,y)   */
    facty  = TABLE_DATA[idx + DIM_X+1];                 /* f(x  ,y+1) */
    factxy = TABLE_DATA[idx + DIM_X+2];                 /* f(x+1,y+1) */

    tmp  = fact;                                        /* f(x,y) */
    tmp += ((factx - fact) * deltax);                   /* f(x,y) + dx*(f(x+1,y) - f(x,y)) */
    tmp += ((facty - fact) * deltay);                   /* f(x,y) + dx*(f(x+1,y) - f(x,y)) + dy*(f(x,y+1) - f(x,y)) */
    tmp += ((fact + factxy - factx - facty) * deltaxy); /* f(x,y) + dx*(f(x+1,y) - f(x,y)) + dy*(f(x,y+1) - f(x,y))  + dxy*(f(x,y) + f(x+1,y+1) - f(x+1,y) - f(x,y+1)) */

    OUT = tmp;

/* USERCODE-END:UpdateFnc                                                                                             */

}

/**********************************************************************************************************************/
/** Initialization                                                                                                   **/
/**********************************************************************************************************************/
void LookupTable2D_Float32_Init(LOOKUPTABLE2D_FLOAT32 *pTLookupTable2D_Float32)
{
    pTLookupTable2D_Float32->ID = LOOKUPTABLE2D_FLOAT32_ID;
    pTLookupTable2D_Float32->Out = 0;
/* USERCODE-BEGIN:InitFnc                                                                                             */
/* USERCODE-END:InitFnc                                                                                               */
}

/**********************************************************************************************************************/
/** Load block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 LookupTable2D_Float32_Load(const LOOKUPTABLE2D_FLOAT32 *pTLookupTable2D_Float32, uint8 data[], uint16 *dataLength, uint16 maxSize)
{
    uint8 error = (uint8)0;
    if ((uint16)4 > maxSize)
    {
        error = (uint8)1;
    }
    else
    {
        data[0] = (uint8)(pTLookupTable2D_Float32->dimX & 0x00FF);
        data[1] = (uint8)((pTLookupTable2D_Float32->dimX >> 8) & 0x00FF);
        data[2] = (uint8)(pTLookupTable2D_Float32->dimY & 0x00FF);
        data[3] = (uint8)((pTLookupTable2D_Float32->dimY >> 8) & 0x00FF);
        *dataLength = (uint16)4;
/* USERCODE-BEGIN:LoadFnc                                                                                             */
/* USERCODE-END:LoadFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Save block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 LookupTable2D_Float32_Save(LOOKUPTABLE2D_FLOAT32 *pTLookupTable2D_Float32, const uint8 data[], uint16 dataLength)
{
    uint8 error;

    if (dataLength != (uint16)4)
    {
        error = (uint8)1;
    }
    else
    {
        pTLookupTable2D_Float32->dimX = ((uint16)data[0] + \
            ((uint16)data[1] << 8));
        pTLookupTable2D_Float32->dimY = ((uint16)data[2] + \
            ((uint16)data[3] << 8));
        error = (uint8)0;
/* USERCODE-BEGIN:SaveFnc                                                                                             */
/* USERCODE-END:SaveFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(LOOKUPTABLE2D_FLOAT32_ISLINKED)
void* LookupTable2D_Float32_GetAddress(const LOOKUPTABLE2D_FLOAT32* block, uint16 elementId)
{
    void* addr;
    switch (elementId)
    {
        case 1:
            addr = (void*)block->x;
            break;
        case 2:
            addr = (void*)block->y;
            break;
        case 3:
            addr = (void*)&block->Out;
            break;
        default:
            addr = (void*)0;
            break;
    }
    return (addr);
}
#endif
