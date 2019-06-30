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
 * $LastChangedRevision: 1693 $
 */
/* USERCODE-BEGIN:Description                                                                                         */
/*     Description: Constant value.                                                                                   */
/*                                                                                                                    */
/* USERCODE-END:Description                                                                                           */
#include "uConstant_Int16.h"

/* USERCODE-BEGIN:PreProcessor                                                                                        */
/* Outputs */
#define OUT             (pTuConstant_Int16->Out)

/* Parameter */
#define VALUE           (pTuConstant_Int16->K)

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** No Update function                                                                                               **/
/**********************************************************************************************************************/

/**********************************************************************************************************************/
/** Initialization                                                                                                   **/
/**********************************************************************************************************************/
void uConstant_Int16_Init(UCONSTANT_INT16 *pTuConstant_Int16)
{
    pTuConstant_Int16->ID = UCONSTANT_INT16_ID;
    pTuConstant_Int16->Out = 0;
/* USERCODE-BEGIN:InitFnc                                                                                             */
    OUT = VALUE;
/* USERCODE-END:InitFnc                                                                                               */
}

/**********************************************************************************************************************/
/** Load block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 uConstant_Int16_Load(const UCONSTANT_INT16 *pTuConstant_Int16, uint8 data[], uint16 *dataLength, uint16 maxSize)
{
    uint8 error = (uint8)0;
    if ((uint16)2 > maxSize)
    {
        error = (uint8)1;
    }
    else
    {
        data[0] = (uint8)(pTuConstant_Int16->K & 0x00FF);
        data[1] = (uint8)((pTuConstant_Int16->K >> 8) & 0x00FF);
        *dataLength = (uint16)2;
/* USERCODE-BEGIN:LoadFnc                                                                                             */
/* USERCODE-END:LoadFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Save block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 uConstant_Int16_Save(UCONSTANT_INT16 *pTuConstant_Int16, const uint8 data[], uint16 dataLength)
{
    uint8 error;

    if (dataLength != (uint16)2)
    {
        error = (uint8)1;
    }
    else
    {
        pTuConstant_Int16->K = UINT16_TO_INT16((uint16)data[0] + \
            ((uint16)data[1] << 8));
        error = (uint8)0;
/* USERCODE-BEGIN:SaveFnc                                                                                             */
        OUT = VALUE;
/* USERCODE-END:SaveFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(UCONSTANT_INT16_ISLINKED)
void* uConstant_Int16_GetAddress(const UCONSTANT_INT16* block, uint16 elementId)
{
    void* addr;
    switch (elementId)
    {
        case 1:
            addr = (void*)&block->Out;
            break;
        default:
            addr = (void*)0;
            break;
    }
    return (addr);
}
#endif
