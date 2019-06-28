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
/**     Description:	Output change rate limitation                        **/
/**						Calculation:										 **/
/**							u > y:											 **/
/**								y(k)     = y(k-1) + RateUp					 **/
/**								RateUp   = 1/Tr * Ts						 **/
/**							u < y:											 **/
/**								y(k)     = y(k-1) - RateDown				 **/
/**								RateDown = 1/Tf * Ts						 **/
/**                                                                          **/ 
/* USERCODE-END:Description                                                                                           */
#ifndef RATELIMITER_FIP16_H
#define RATELIMITER_FIP16_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"

#if !defined(RATELIMITER_FIP16_ISLINKED)
#define RATELIMITER_FIP16_ID ((uint16)97)

typedef struct {
    uint16          ID;
    int16           *In;
    int16           *Init;
    bool            *Enable;
    int16           Out;
    int32           RateUp;
    int32           RateDown;
    int32           out_old;
    bool            enable_old;
} RATELIMITER_FIP16;

#define RATELIMITER_FIP16_FUNCTIONS { \
    RATELIMITER_FIP16_ID, \
    (void (*)(void*))RateLimiter_FiP16_Update, \
    (void (*)(void*))RateLimiter_FiP16_Init, \
    (tLoadImplementationParameter)RateLimiter_FiP16_Load, \
    (tSaveImplementationParameter)RateLimiter_FiP16_Save, \
    (void* (*)(const void*, uint16))RateLimiter_FiP16_GetAddress }

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void RateLimiter_FiP16_Update(RATELIMITER_FIP16 *pTRateLimiter_FiP16);
void RateLimiter_FiP16_Init(RATELIMITER_FIP16 *pTRateLimiter_FiP16);
uint8 RateLimiter_FiP16_Load(const RATELIMITER_FIP16 *pTRateLimiter_FiP16, uint8 data[], uint16 *dataLength, uint16 maxSize);
uint8 RateLimiter_FiP16_Save(RATELIMITER_FIP16 *pTRateLimiter_FiP16, const uint8 data[], uint16 dataLength);
void* RateLimiter_FiP16_GetAddress(const RATELIMITER_FIP16 *block, uint16 elementId);

#endif

#ifdef __cplusplus
}
#endif

#endif
