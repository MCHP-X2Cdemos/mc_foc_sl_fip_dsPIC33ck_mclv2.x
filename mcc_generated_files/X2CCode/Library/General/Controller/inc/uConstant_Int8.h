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
/* Description: */
/* USERCODE-END:Description                                                                                           */
#ifndef UCONSTANT_INT8_H
#define UCONSTANT_INT8_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"

#if !defined(UCONSTANT_INT8_ISLINKED)
#define UCONSTANT_INT8_ID ((uint16)69)

typedef struct {
    uint16          ID;
    int8            Out;
    int8            K;
} UCONSTANT_INT8;

#define UCONSTANT_INT8_FUNCTIONS { \
    UCONSTANT_INT8_ID, \
    (void (*)(void*))Common_Update, \
    (void (*)(void*))uConstant_Int8_Init, \
    (tLoadImplementationParameter)uConstant_Int8_Load, \
    (tSaveImplementationParameter)uConstant_Int8_Save, \
    (void* (*)(const void*, uint16))uConstant_Int8_GetAddress }

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void uConstant_Int8_Init(UCONSTANT_INT8 *pTuConstant_Int8);
uint8 uConstant_Int8_Load(const UCONSTANT_INT8 *pTuConstant_Int8, uint8 data[], uint16 *dataLength, uint16 maxSize);
uint8 uConstant_Int8_Save(UCONSTANT_INT8 *pTuConstant_Int8, const uint8 data[], uint16 dataLength);
void* uConstant_Int8_GetAddress(const UCONSTANT_INT8 *block, uint16 elementId);

#endif

#ifdef __cplusplus
}
#endif

#endif
