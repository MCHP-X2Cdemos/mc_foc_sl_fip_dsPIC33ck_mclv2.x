/*
 * Copyright (c) {YEAR}, {ORGANIZATION_NAME}, {ORGANIZATION_WEB}
 * All rights reserved.
 */
/*
 * This file is licensed according to the BSD 3-clause license as follows:
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the name of the "{ORGANIZATION_NAME}" nor
 *     the names of its contributors may be used to endorse or promote products
 *     derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL "{ORGANIZATION_NAME}" BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/*
 * This file is part of X2C. http://www.mechatronic-simulation.org/
 * $LastChangedRevision$
 */
/* USERCODE-BEGIN:Description                                                                                         */
/* Description: */
/* USERCODE-END:Description                                                                                           */
#ifndef PARK_CLARKE_INV_SVM_MCHP_FLOAT32_H
#define PARK_CLARKE_INV_SVM_MCHP_FLOAT32_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"

#if !defined(PARK_CLARKE_INV_SVM_MCHP_FLOAT32_ISLINKED)
#define PARK_CLARKE_INV_SVM_MCHP_FLOAT32_ID ((uint16)20978)

typedef struct {
    uint16          ID;
    float32         *d;
    float32         *q;
    float32         *theta;
    bool            *forcedMode;
    float32         *forcedValue;
    float32         A;
    float32         B;
    float32         C;
    float32         Valpha;
    float32         Vbeta;
} PARK_CLARKE_INV_SVM_MCHP_FLOAT32;

#define PARK_CLARKE_INV_SVM_MCHP_FLOAT32_FUNCTIONS { \
    PARK_CLARKE_INV_SVM_MCHP_FLOAT32_ID, \
    (void (*)(void*))Park_Clarke_inv_SVM_MCHP_Float32_Update, \
    (void (*)(void*))Park_Clarke_inv_SVM_MCHP_Float32_Init, \
    (tLoadImplementationParameter)Common_Load, \
    (tSaveImplementationParameter)Common_Save, \
    (void* (*)(const void*, uint16))Park_Clarke_inv_SVM_MCHP_Float32_GetAddress }

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void Park_Clarke_inv_SVM_MCHP_Float32_Update(PARK_CLARKE_INV_SVM_MCHP_FLOAT32 *pTPark_Clarke_inv_SVM_MCHP_Float32);
void Park_Clarke_inv_SVM_MCHP_Float32_Init(PARK_CLARKE_INV_SVM_MCHP_FLOAT32 *pTPark_Clarke_inv_SVM_MCHP_Float32);
void* Park_Clarke_inv_SVM_MCHP_Float32_GetAddress(const PARK_CLARKE_INV_SVM_MCHP_FLOAT32 *block, uint16 elementId);

#endif

#ifdef __cplusplus
}
#endif

#endif
