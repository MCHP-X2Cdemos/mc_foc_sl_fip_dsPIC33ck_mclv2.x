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
#include "uConstant_Int8.h"

/* USERCODE-BEGIN:PreProcessor                                                                                        */
/* Outputs */
#define OUT             (pTuConstant_Int8->Out)

/* Parameter */
#define VALUE           (pTuConstant_Int8->K)

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** No Update function                                                                                               **/
/**********************************************************************************************************************/

/**********************************************************************************************************************/
/** Initialization                                                                                                   **/
/**********************************************************************************************************************/
void uConstant_Int8_Init(UCONSTANT_INT8 *pTuConstant_Int8)
{
    pTuConstant_Int8->ID = UCONSTANT_INT8_ID;
    pTuConstant_Int8->Out = 0;
/* USERCODE-BEGIN:InitFnc                                                                                             */
    OUT = VALUE;
/* USERCODE-END:InitFnc                                                                                               */
}

/**********************************************************************************************************************/
/** Load block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 uConstant_Int8_Load(const UCONSTANT_INT8 *pTuConstant_Int8, uint8 data[], uint16 *dataLength, uint16 maxSize)
{
    uint8 error = (uint8)0;
    if ((uint16)1 > maxSize)
    {
        error = (uint8)1;
    }
    else
    {
        data[0] = (uint8)pTuConstant_Int8->K;
        *dataLength = (uint16)1;
/* USERCODE-BEGIN:LoadFnc                                                                                             */
/* USERCODE-END:LoadFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Save block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 uConstant_Int8_Save(UCONSTANT_INT8 *pTuConstant_Int8, const uint8 data[], uint16 dataLength)
{
    uint8 error;

    if (dataLength != (uint16)1)
    {
        error = (uint8)1;
    }
    else
    {
        pTuConstant_Int8->K = UINT8_TO_INT8((uint8)data[0]);
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
#if !defined(UCONSTANT_INT8_ISLINKED)
void* uConstant_Int8_GetAddress(const UCONSTANT_INT8* block, uint16 elementId)
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
