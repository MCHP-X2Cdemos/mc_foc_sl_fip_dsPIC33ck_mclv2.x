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
 * $LastChangedRevision: 1603 $
 */
/* USERCODE-BEGIN:Description                                                                                         */
/* Description: */
/* USERCODE-END:Description                                                                                           */
#ifndef UCONSTANT_BOOL_H
#define UCONSTANT_BOOL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"

#if !defined(UCONSTANT_BOOL_ISLINKED)
#define UCONSTANT_BOOL_ID ((uint16)79)

typedef struct {
    uint16          ID;
    bool            Out;
    bool            K;
} UCONSTANT_BOOL;

#define UCONSTANT_BOOL_FUNCTIONS { \
    UCONSTANT_BOOL_ID, \
    (void (*)(void*))Common_Update, \
    (void (*)(void*))uConstant_Bool_Init, \
    (tLoadImplementationParameter)uConstant_Bool_Load, \
    (tSaveImplementationParameter)uConstant_Bool_Save, \
    (void* (*)(const void*, uint16))uConstant_Bool_GetAddress }

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void uConstant_Bool_Init(UCONSTANT_BOOL *pTuConstant_Bool);
uint8 uConstant_Bool_Load(const UCONSTANT_BOOL *pTuConstant_Bool, uint8 data[], uint16 *dataLength, uint16 maxSize);
uint8 uConstant_Bool_Save(UCONSTANT_BOOL *pTuConstant_Bool, const uint8 data[], uint16 dataLength);
void* uConstant_Bool_GetAddress(const UCONSTANT_BOOL *block, uint16 elementId);

#endif

#ifdef __cplusplus
}
#endif

#endif
