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
#include "LookupTable2D_FiP16.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(LookupTable2D_FiP16_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
/* Inputs */
#define IN_X            (*pTLookupTable2D_FiP16->x)
#define IN_Y            (*pTLookupTable2D_FiP16->y)

/* Outputs */
#define OUT             (pTLookupTable2D_FiP16->Out)

/* Parameters */
#define TABLE_DATA      (pTLookupTable2D_FiP16->Table)
#define SFR_X           (pTLookupTable2D_FiP16->sfrX)
#define MASK_X          (pTLookupTable2D_FiP16->maskX)
#define IDX_OFFSET_X    (pTLookupTable2D_FiP16->idxOffsetX)
#define SIZE_X          (pTLookupTable2D_FiP16->sizeX)
#define SFR_Y           (pTLookupTable2D_FiP16->sfrY)
#define MASK_Y          (pTLookupTable2D_FiP16->maskY)
#define IDX_OFFSET_Y    (pTLookupTable2D_FiP16->idxOffsetY)

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void LookupTable2D_FiP16_Update(LOOKUPTABLE2D_FIP16 *pTLookupTable2D_FiP16)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
    int32 tmp;
    uint16 idxx, idxy, idx;
    int16 fact, factx, facty, factxy, deltax, deltay, deltaxy;

    idxx   = (IN_X >> SFR_X) + IDX_OFFSET_X;    /*  x  */
    idxy   = (IN_Y >> SFR_Y) + IDX_OFFSET_Y;    /*  y  */
    idx    = idxx + (idxy*SIZE_X);

    deltax  = IN_X & MASK_X;                                    /* dx  */
    deltay  = IN_Y & MASK_Y;                                    /* dy  */
    deltaxy = ((int32)(deltax)*(int32)(deltay)) >> SFR_Y;       /* dxy */

    fact   = TABLE_DATA[idx];                                   /* f(x  ,y)   */
    factx  = TABLE_DATA[idx + 1];                               /* f(x+1,y)   */
    facty  = TABLE_DATA[idx + SIZE_X];                          /* f(x  ,y+1) */
    factxy = TABLE_DATA[idx + SIZE_X+1];                        /* f(x+1,y+1) */

    tmp  = fact;                                                /* f(x,y) */
    tmp += (((int32)(factx - fact) * (int32)deltax) >> SFR_X);  /* f(x,y) + dx*(f(x+1,y) - f(x,y)) */
    tmp += (((int32)(facty - fact) * (int32)deltay) >> SFR_Y);  /* f(x,y) + dx*(f(x+1,y) - f(x,y)) + dy*(f(x,y+1) - f(x,y))*/
    tmp += ((((int32)fact + (int32)factxy - (int32)factx - (int32)facty) * (int32)deltaxy) >> SFR_X);   /* f(x,y) + dx*(f(x+1,y) - f(x,y)) + dy*(f(x,y+1) - f(x,y))  + dxy*(f(x,y) + f(x+1,y+1) - f(x+1,y) - f(x,y+1)) */

    OUT = (int16)tmp;
/* USERCODE-END:UpdateFnc                                                                                             */

}

/**********************************************************************************************************************/
/** Initialization                                                                                                   **/
/**********************************************************************************************************************/
void LookupTable2D_FiP16_Init(LOOKUPTABLE2D_FIP16 *pTLookupTable2D_FiP16)
{
    pTLookupTable2D_FiP16->ID = LOOKUPTABLE2D_FIP16_ID;
    pTLookupTable2D_FiP16->Out = 0;
/* USERCODE-BEGIN:InitFnc                                                                                             */
/* USERCODE-END:InitFnc                                                                                               */
}

/**********************************************************************************************************************/
/** Load block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 LookupTable2D_FiP16_Load(const LOOKUPTABLE2D_FIP16 *pTLookupTable2D_FiP16, uint8 data[], uint16 *dataLength, uint16 maxSize)
{
    uint8 error = (uint8)0;
    if ((uint16)12 > maxSize)
    {
        error = (uint8)1;
    }
    else
    {
        data[0] = (uint8)pTLookupTable2D_FiP16->sfrX;
        data[1] = (uint8)pTLookupTable2D_FiP16->sfrY;
        data[2] = (uint8)(pTLookupTable2D_FiP16->maskX & 0x00FF);
        data[3] = (uint8)((pTLookupTable2D_FiP16->maskX >> 8) & 0x00FF);
        data[4] = (uint8)(pTLookupTable2D_FiP16->maskY & 0x00FF);
        data[5] = (uint8)((pTLookupTable2D_FiP16->maskY >> 8) & 0x00FF);
        data[6] = (uint8)(pTLookupTable2D_FiP16->idxOffsetX & 0x00FF);
        data[7] = (uint8)((pTLookupTable2D_FiP16->idxOffsetX >> 8) & 0x00FF);
        data[8] = (uint8)(pTLookupTable2D_FiP16->idxOffsetY & 0x00FF);
        data[9] = (uint8)((pTLookupTable2D_FiP16->idxOffsetY >> 8) & 0x00FF);
        data[10] = (uint8)(pTLookupTable2D_FiP16->sizeX & 0x00FF);
        data[11] = (uint8)((pTLookupTable2D_FiP16->sizeX >> 8) & 0x00FF);
        *dataLength = (uint16)12;
/* USERCODE-BEGIN:LoadFnc                                                                                             */
/* USERCODE-END:LoadFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Save block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 LookupTable2D_FiP16_Save(LOOKUPTABLE2D_FIP16 *pTLookupTable2D_FiP16, const uint8 data[], uint16 dataLength)
{
    uint8 error;

    if (dataLength != (uint16)12)
    {
        error = (uint8)1;
    }
    else
    {
        pTLookupTable2D_FiP16->sfrX = UINT8_TO_INT8((uint8)data[0]);
        pTLookupTable2D_FiP16->sfrY = UINT8_TO_INT8((uint8)data[1]);
        pTLookupTable2D_FiP16->maskX = ((uint16)data[2] + \
            ((uint16)data[3] << 8));
        pTLookupTable2D_FiP16->maskY = ((uint16)data[4] + \
            ((uint16)data[5] << 8));
        pTLookupTable2D_FiP16->idxOffsetX = ((uint16)data[6] + \
            ((uint16)data[7] << 8));
        pTLookupTable2D_FiP16->idxOffsetY = ((uint16)data[8] + \
            ((uint16)data[9] << 8));
        pTLookupTable2D_FiP16->sizeX = ((uint16)data[10] + \
            ((uint16)data[11] << 8));
        error = (uint8)0;
/* USERCODE-BEGIN:SaveFnc                                                                                             */
/* USERCODE-END:SaveFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(LOOKUPTABLE2D_FIP16_ISLINKED)
void* LookupTable2D_FiP16_GetAddress(const LOOKUPTABLE2D_FIP16* block, uint16 elementId)
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
