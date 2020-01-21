/*
 * Copyright (c) 2017, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
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
 * $LastChangedDate:: 2019-06-03 08:28:37 +0200#$
 */
/* USERCODE-BEGIN:Description                                                                                         */
/* Description: */
/* USERCODE-END:Description                                                                                           */
#ifndef CONSTANT_INT32_H
#define CONSTANT_INT32_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"

#if !defined(CONSTANT_INT32_ISLINKED)
#define CONSTANT_INT32_ID ((uint16)55)

typedef struct {
    uint16          ID;
    int32           Out;
    int32           K;
} CONSTANT_INT32;

#define CONSTANT_INT32_FUNCTIONS { \
    CONSTANT_INT32_ID, \
    (void (*)(void*))Common_Update, \
    (void (*)(void*))Constant_Int32_Init, \
    (tLoadImplementationParameter)Constant_Int32_Load, \
    (tSaveImplementationParameter)Constant_Int32_Save, \
    (void* (*)(const void*, uint16))Constant_Int32_GetAddress }

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void Constant_Int32_Init(CONSTANT_INT32 *pTConstant_Int32);
uint8 Constant_Int32_Load(const CONSTANT_INT32 *pTConstant_Int32, uint8 data[], uint16 *dataLength, uint16 maxSize);
uint8 Constant_Int32_Save(CONSTANT_INT32 *pTConstant_Int32, const uint8 data[], uint16 dataLength);
void* Constant_Int32_GetAddress(const CONSTANT_INT32 *block, uint16 elementId);

#endif

#ifdef __cplusplus
}
#endif

#endif
