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
#ifndef BEMF_CALC_FIP32_H
#define BEMF_CALC_FIP32_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"

#if !defined(BEMF_CALC_FIP32_ISLINKED)
#define BEMF_CALC_FIP32_ID ((uint16)20993)

typedef struct {
    uint16          ID;
    int32           *Ialpha;
    int32           *Ibeta;
    int32           *Valpha;
    int32           *Vbeta;
    int32           BEMFalpha;
    int32           BEMFbeta;
    int32           Ls;
    int32           Rs;
    int8            sfrLs;
    int8            sfrRs;
    int32           Ia_old;
    int32           Ib_old;
    uint8           CurrentSampleFactor;
    int32           V_Ls_alpha;
    int32           V_Ls_beta;
    uint8           FactCounter;
} BEMF_CALC_FIP32;

#define BEMF_CALC_FIP32_FUNCTIONS { \
    BEMF_CALC_FIP32_ID, \
    (void (*)(void*))BEMF_calc_FiP32_Update, \
    (void (*)(void*))BEMF_calc_FiP32_Init, \
    (tLoadImplementationParameter)BEMF_calc_FiP32_Load, \
    (tSaveImplementationParameter)BEMF_calc_FiP32_Save, \
    (void* (*)(const void*, uint16))BEMF_calc_FiP32_GetAddress }

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void BEMF_calc_FiP32_Update(BEMF_CALC_FIP32 *pTBEMF_calc_FiP32);
void BEMF_calc_FiP32_Init(BEMF_CALC_FIP32 *pTBEMF_calc_FiP32);
uint8 BEMF_calc_FiP32_Load(const BEMF_CALC_FIP32 *pTBEMF_calc_FiP32, uint8 data[], uint16 *dataLength, uint16 maxSize);
uint8 BEMF_calc_FiP32_Save(BEMF_CALC_FIP32 *pTBEMF_calc_FiP32, const uint8 data[], uint16 dataLength);
void* BEMF_calc_FiP32_GetAddress(const BEMF_CALC_FIP32 *block, uint16 elementId);

#endif

#ifdef __cplusplus
}
#endif

#endif
