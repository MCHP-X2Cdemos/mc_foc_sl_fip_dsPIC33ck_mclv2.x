/**
 * @file
 * @brief Scope.
 */
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
 * $LastChangedRevision: 1894 $
 * $LastChangedDate:: 2020-04-28 23:26:04 +0200#$
 */
#ifndef SCOPE_MAIN_H
#define SCOPE_MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"

#define SCOPE_MAIN_ID ((uint16)65535)

#if defined(SCOPE_SIZE)
/* Scope array size maximum size = 2^31-1 due to int32 variable types */
#if SCOPE_SIZE > 2147483647
#error SCOPE ARRAY SIZE MUST NOT EXCEED 2147483647 (2^31-1)
#endif

#else

#if defined(__TMS320F28XX__) || defined(__TMS320F2833X__) || \
		defined(__TMS320F2803X__) || defined(__TMS320F280X__) || \
		defined(__TMS320F2806X__) || defined(__TMS320F281X__) || defined(__SERIES_TM4C__)
#define SCOPE_SIZE ((uint16)4900)

#elif defined(__TMS320F2802X__)
#define SCOPE_SIZE ((uint16)512)

#elif defined(__STM32F10X__) || defined(__STM32F10XXX__) || defined(__SERIES_STM32F1__)
#define SCOPE_SIZE ((uint16)490)

#elif defined(__SERIES_STM32F4__) || defined(__SERIES_MPC5__)
#define SCOPE_SIZE ((uint16)4900)

#elif defined(__SERIES_DSPIC33F__) || defined(__SERIES_DSPIC33E__)
#define SCOPE_SIZE ((uint16)4900)

#elif defined(__SERIES_PIC32MZ__)
#define SCOPE_SIZE ((uint16)8192)

#elif defined(__RX6XX__)
#define SCOPE_SIZE ((uint16)4900)
#else
#error SCOPE ARRAY SIZE NOT DEFINED FOR CURRENT PROCESSOR
#endif

#endif

#if defined(__DATA_WIDTH_8BIT__)
#define ALIGNTYPE int8
#define ALIGNCASTPTR (int8*)
#elif defined(__DATA_WIDTH_16BIT__)
#define ALIGNTYPE int16
#define ALIGNCASTPTR (int16*)
#else
#error DATA WIDTH NOT DEFINED
#endif

#define SCOPE_MAIN_FUNCTIONS { \
	SCOPE_MAIN_ID, \
    (void (*)(void*))Scope_Main_Update, \
    (void (*)(void*))Scope_Main_Init, \
    (uint8 (*)(const void*, uint8[], uint16*, uint16))Scope_Main_Load, \
    (uint8 (*)(void*, const uint8[], uint16))Scope_Main_Save, \
    (void* (*)(const void*, uint16))Scope_Main_GetAddress }

/* public prototypes */
void Scope_Main_Update(SCOPE_MAIN *pTGain_FiP16);
void Scope_Main_Init(SCOPE_MAIN *pTGain_FiP16);
uint8 Scope_Main_Load(const SCOPE_MAIN *pTGain_FiP16, uint8 data[], uint16 *dataLength, uint16 maxSize);
uint8 Scope_Main_Save(SCOPE_MAIN *pTGain_FiP16, const uint8 data[], uint16 dataLength);
void* Scope_Main_GetAddress(const SCOPE_MAIN *block, uint16 elementId);

#ifdef __cplusplus
}
#endif

#endif
