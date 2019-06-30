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
#ifndef SELECTOR_FIP8_H
#define SELECTOR_FIP8_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"

#if !defined(SELECTOR_FIP8_ISLINKED)
#define SELECTOR_FIP8_ID ((uint16)400)

typedef struct {
    uint16          ID;
    int8            *In0;
    int8            *In1;
    int8            *In2;
    int8            *In3;
    int8            *In4;
    int8            *In5;
    int8            *In6;
    int8            *In7;
    int8            *Select;
    int8            Out;
} SELECTOR_FIP8;

#define SELECTOR_FIP8_FUNCTIONS { \
    SELECTOR_FIP8_ID, \
    (void (*)(void*))Selector_FiP8_Update, \
    (void (*)(void*))Selector_FiP8_Init, \
    (tLoadImplementationParameter)Common_Load, \
    (tSaveImplementationParameter)Common_Save, \
    (void* (*)(const void*, uint16))Selector_FiP8_GetAddress }

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void Selector_FiP8_Update(SELECTOR_FIP8 *pTSelector_FiP8);
void Selector_FiP8_Init(SELECTOR_FIP8 *pTSelector_FiP8);
void* Selector_FiP8_GetAddress(const SELECTOR_FIP8 *block, uint16 elementId);

#endif

#ifdef __cplusplus
}
#endif

#endif
