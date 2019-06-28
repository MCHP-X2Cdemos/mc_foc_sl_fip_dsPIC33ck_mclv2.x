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
 * $LastChangedRevision: 1623 $
 */
/* USERCODE-BEGIN:Description                                                                                         */
/*     Description:  Switch between In1 and In3 dependent on Switch signal:   */
/*    			Switch signal rising:  Switch > Threshold up --> Out = In1	  */
/*    			Switch signal falling: Switch < Threshold down --> Out = In3  */
/*																			  */
/* USERCODE-END:Description                                                                                           */
#include "AutoSwitch_Float32.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(AutoSwitch_Float32_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
/* Inputs */
#define IN1 				(*pTAutoSwitch_Float32->In1)
#define SWITCH 				(*pTAutoSwitch_Float32->Switch)
#define IN3 				(*pTAutoSwitch_Float32->In3)

/* Outputs */
#define OUT 				(pTAutoSwitch_Float32->Out)

/* Parameter */
#define THRESH_UP 			(pTAutoSwitch_Float32->Thresh_up)
#define THRESH_DOWN 		(pTAutoSwitch_Float32->Thresh_down)

/* Variables */
#define STATUS 				(pTAutoSwitch_Float32->Status)

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void AutoSwitch_Float32_Update(AUTOSWITCH_FLOAT32 *pTAutoSwitch_Float32)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
    if (SWITCH >= THRESH_UP)
    {
        /* positive crossing of upper threshold level -> change hysteresis state */
        STATUS = &IN1;
    }
    else if (SWITCH < THRESH_DOWN)
    {
        /* negative crossing of lower threshold level -> change hysteresis state */
        STATUS = &IN3;
    }
    /* else: no change in hysteresis state */


    /* set output according to hysteresis status */
    OUT = *STATUS;

/* USERCODE-END:UpdateFnc                                                                                             */

}

/**********************************************************************************************************************/
/** Initialization                                                                                                   **/
/**********************************************************************************************************************/
void AutoSwitch_Float32_Init(AUTOSWITCH_FLOAT32 *pTAutoSwitch_Float32)
{
    pTAutoSwitch_Float32->ID = AUTOSWITCH_FLOAT32_ID;
    pTAutoSwitch_Float32->Out = 0;
/* USERCODE-BEGIN:InitFnc                                                                                             */
    STATUS = &IN3;

/* USERCODE-END:InitFnc                                                                                               */
}

/**********************************************************************************************************************/
/** Load block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 AutoSwitch_Float32_Load(const AUTOSWITCH_FLOAT32 *pTAutoSwitch_Float32, uint8 data[], uint16 *dataLength, uint16 maxSize)
{
    uint8 error = (uint8)0;
    if ((uint16)8 > maxSize)
    {
        error = (uint8)1;
    }
    else
    {
        data[0] = (uint8)((*(uint32*)&(pTAutoSwitch_Float32->Thresh_up)) & 0x000000FF);
        data[1] = (uint8)((*(uint32*)&(pTAutoSwitch_Float32->Thresh_up) >> 8) & 0x000000FF);
        data[2] = (uint8)((*(uint32*)&(pTAutoSwitch_Float32->Thresh_up) >> 16) & 0x000000FF);
        data[3] = (uint8)((*(uint32*)&(pTAutoSwitch_Float32->Thresh_up) >> 24) & 0x000000FF);
        data[4] = (uint8)((*(uint32*)&(pTAutoSwitch_Float32->Thresh_down)) & 0x000000FF);
        data[5] = (uint8)((*(uint32*)&(pTAutoSwitch_Float32->Thresh_down) >> 8) & 0x000000FF);
        data[6] = (uint8)((*(uint32*)&(pTAutoSwitch_Float32->Thresh_down) >> 16) & 0x000000FF);
        data[7] = (uint8)((*(uint32*)&(pTAutoSwitch_Float32->Thresh_down) >> 24) & 0x000000FF);
        *dataLength = (uint16)8;
/* USERCODE-BEGIN:LoadFnc                                                                                             */
/* USERCODE-END:LoadFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Save block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 AutoSwitch_Float32_Save(AUTOSWITCH_FLOAT32 *pTAutoSwitch_Float32, const uint8 data[], uint16 dataLength)
{
    uint8 error;
    uint32 tmp32;

    if (dataLength != (uint16)8)
    {
        error = (uint8)1;
    }
    else
    {
        tmp32 = (uint32)data[0] + \
            ((uint32)data[1] << 8) + ((uint32)data[2] << 16) + \
            ((uint32)data[3] << 24);
        pTAutoSwitch_Float32->Thresh_up = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[4] + \
            ((uint32)data[5] << 8) + ((uint32)data[6] << 16) + \
            ((uint32)data[7] << 24);
        pTAutoSwitch_Float32->Thresh_down = (float32)(*(float32*)&tmp32);
        error = (uint8)0;
/* USERCODE-BEGIN:SaveFnc                                                                                             */
/* USERCODE-END:SaveFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(AUTOSWITCH_FLOAT32_ISLINKED)
void* AutoSwitch_Float32_GetAddress(const AUTOSWITCH_FLOAT32* block, uint16 elementId)
{
    void* addr;
    switch (elementId)
    {
        case 1:
            addr = (void*)block->In1;
            break;
        case 2:
            addr = (void*)block->Switch;
            break;
        case 3:
            addr = (void*)block->In3;
            break;
        case 4:
            addr = (void*)&block->Out;
            break;
        default:
            addr = (void*)0;
            break;
    }
    return (addr);
}
#endif
