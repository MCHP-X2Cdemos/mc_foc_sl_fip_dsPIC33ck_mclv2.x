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
/* Description: 															  */
/*		Passing through of input signal selected by the select inport:		  */
/*		  Select = 0 (DSP): Out = In0										  */
/*		  Select = 1 (DSP): Out = In1										  */
/*  	  ...																  */
/*  	  Select = 7 (DSP): Out = In7										  */
/*																			  */
/* USERCODE-END:Description                                                                                           */
#ifndef SELECTOR_FIP16_H
#define SELECTOR_FIP16_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"

#if !defined(SELECTOR_FIP16_ISLINKED)
#define SELECTOR_FIP16_ID ((uint16)401)

typedef struct {
    uint16          ID;
    int16           *In0;
    int16           *In1;
    int16           *In2;
    int16           *In3;
    int16           *In4;
    int16           *In5;
    int16           *In6;
    int16           *In7;
    int8            *Select;
    int16           Out;
} SELECTOR_FIP16;

#define SELECTOR_FIP16_FUNCTIONS { \
    SELECTOR_FIP16_ID, \
    (void (*)(void*))Selector_FiP16_Update, \
    (void (*)(void*))Selector_FiP16_Init, \
    (tLoadImplementationParameter)Common_Load, \
    (tSaveImplementationParameter)Common_Save, \
    (void* (*)(const void*, uint16))Selector_FiP16_GetAddress }

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void Selector_FiP16_Update(SELECTOR_FIP16 *pTSelector_FiP16);
void Selector_FiP16_Init(SELECTOR_FIP16 *pTSelector_FiP16);
void* Selector_FiP16_GetAddress(const SELECTOR_FIP16 *block, uint16 elementId);

#endif

#ifdef __cplusplus
}
#endif

#endif
