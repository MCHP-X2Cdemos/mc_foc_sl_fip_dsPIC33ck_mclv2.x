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
/**     Description:	Second order transfer function                      										 **/
/**						Calculation:																				 **/
/**	       						 b2.z^2 + b1.z + b0					   												 **/
/** 						y = ------------------ u				   												 **/
/**          					  z^2 + a1.z + a0																	 **/
/**							-> y(k) = u(k).b2 + u(k-1).b1 + u(k-2).b0												 **/
/**									- y(k-1).a1 - y(k-2).a0															 **/
/**																													 **/
/* USERCODE-END:Description                                                                                           */
#ifndef TF2_FIP8_H
#define TF2_FIP8_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"

#if !defined(TF2_FIP8_ISLINKED)
#define TF2_FIP8_ID ((uint16)3296)

typedef struct {
    uint16          ID;
    int8            *In;
    int8            Out;
    int8            b0;
    int8            b1;
    int8            b2;
    int8            a0;
    int8            a1;
    int8            sfrb;
    int8            sfra;
    int8            in_old;
    int8            in_veryold;
    int8            out_old;
    int8            out_veryold;
} TF2_FIP8;

#define TF2_FIP8_FUNCTIONS { \
    TF2_FIP8_ID, \
    (void (*)(void*))TF2_FiP8_Update, \
    (void (*)(void*))TF2_FiP8_Init, \
    (tLoadImplementationParameter)TF2_FiP8_Load, \
    (tSaveImplementationParameter)TF2_FiP8_Save, \
    (void* (*)(const void*, uint16))TF2_FiP8_GetAddress }

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void TF2_FiP8_Update(TF2_FIP8 *pTTF2_FiP8);
void TF2_FiP8_Init(TF2_FIP8 *pTTF2_FiP8);
uint8 TF2_FiP8_Load(const TF2_FIP8 *pTTF2_FiP8, uint8 data[], uint16 *dataLength, uint16 maxSize);
uint8 TF2_FiP8_Save(TF2_FIP8 *pTTF2_FiP8, const uint8 data[], uint16 dataLength);
void* TF2_FiP8_GetAddress(const TF2_FIP8 *block, uint16 elementId);

#endif

#ifdef __cplusplus
}
#endif

#endif
