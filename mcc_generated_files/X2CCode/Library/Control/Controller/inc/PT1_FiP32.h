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
/**     Description:    First order proportional element                     **/
/**						Calculation:										 **/
/**	       						 b1.z + b0							   		 **/
/** 						y = ----------- u						   		 **/
/**          					   z + a0									 **/
/**							-> y(k) = u(k).b1 + u(k-1).b0 - y(k-1).a0        **/
/**																			 **/
/**						Note:												 **/
/**							TF1 source code is used!						 **/
/**																			 **/
/* USERCODE-END:Description                                                                                           */
#ifndef PT1_FIP32_H
#define PT1_FIP32_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"

#if !defined(PT1_FIP32_ISLINKED)
#define PT1_FIP32_ID ((uint16)3314)

typedef struct {
    uint16          ID;
    int32           *In;
    int32           Out;
    int32           b0;
    int32           b1;
    int32           a0;
    int8            sfrb;
    int8            sfra;
    int32           in_old;
} PT1_FIP32;

#define PT1_FIP32_FUNCTIONS { \
    PT1_FIP32_ID, \
    (void (*)(void*))PT1_FiP32_Update, \
    (void (*)(void*))PT1_FiP32_Init, \
    (tLoadImplementationParameter)PT1_FiP32_Load, \
    (tSaveImplementationParameter)PT1_FiP32_Save, \
    (void* (*)(const void*, uint16))PT1_FiP32_GetAddress }

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void PT1_FiP32_Update(PT1_FIP32 *pTPT1_FiP32);
void PT1_FiP32_Init(PT1_FIP32 *pTPT1_FiP32);
uint8 PT1_FiP32_Load(const PT1_FIP32 *pTPT1_FiP32, uint8 data[], uint16 *dataLength, uint16 maxSize);
uint8 PT1_FiP32_Save(PT1_FIP32 *pTPT1_FiP32, const uint8 data[], uint16 dataLength);
void* PT1_FiP32_GetAddress(const PT1_FIP32 *block, uint16 elementId);

#endif

#ifdef __cplusplus
}
#endif

#endif
