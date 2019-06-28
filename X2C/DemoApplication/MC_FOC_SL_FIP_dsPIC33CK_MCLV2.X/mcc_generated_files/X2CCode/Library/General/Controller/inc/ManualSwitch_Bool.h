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
 * $LastChangedRevision: 1603 $
 * $LastChangedDate:: 2019-01-21 19:02:13 +0100#$
 */
/* USERCODE-BEGIN:Description                                                                                         */
/**
 * @file
 * @brief Toggling between the two inputs.
 */
/* USERCODE-END:Description                                                                                           */
#ifndef MANUALSWITCH_BOOL_H
#define MANUALSWITCH_BOOL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"

#if !defined(MANUALSWITCH_BOOL_ISLINKED)
#define MANUALSWITCH_BOOL_ID ((uint16)159)

typedef struct {
    uint16          ID;
    bool            *In1;
    bool            *In2;
    bool            Out;
    uint8           Toggle;
} MANUALSWITCH_BOOL;

#define MANUALSWITCH_BOOL_FUNCTIONS { \
    MANUALSWITCH_BOOL_ID, \
    (void (*)(void*))ManualSwitch_Bool_Update, \
    (void (*)(void*))ManualSwitch_Bool_Init, \
    (tLoadImplementationParameter)ManualSwitch_Bool_Load, \
    (tSaveImplementationParameter)ManualSwitch_Bool_Save, \
    (void* (*)(const void*, uint16))ManualSwitch_Bool_GetAddress }

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void ManualSwitch_Bool_Update(MANUALSWITCH_BOOL *pTManualSwitch_Bool);
void ManualSwitch_Bool_Init(MANUALSWITCH_BOOL *pTManualSwitch_Bool);
uint8 ManualSwitch_Bool_Load(const MANUALSWITCH_BOOL *pTManualSwitch_Bool, uint8 data[], uint16 *dataLength, uint16 maxSize);
uint8 ManualSwitch_Bool_Save(MANUALSWITCH_BOOL *pTManualSwitch_Bool, const uint8 data[], uint16 dataLength);
void* ManualSwitch_Bool_GetAddress(const MANUALSWITCH_BOOL *block, uint16 elementId);

#endif

#ifdef __cplusplus
}
#endif

#endif
