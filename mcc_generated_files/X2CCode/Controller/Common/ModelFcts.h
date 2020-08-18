/**
 * @file
 * @brief Model API functions.
 */
/*
 * Copyright (c) 2020, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
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
 * $LastChangedRevision: 1970 $
 * $LastChangedDate:: 2020-07-17 22:44:50 +0200#$
 */
#ifndef MODELFCTS_H
#define MODELFCTS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "Target.h"

/* public prototypes */
/**
 * @brief Reads Mask Parameter data into buffer.
 *
 * This function searches for the Mask Parameter in the current X2C Model.
 * If the Mask Parameter record was found, the function copies the Mask Parameter data into the given buffer.
 *
 * @param[in] blockParamId Block Parameter ID
 * @param[in] maskParamId Mask Parameter ID
 * @param[out] buffer Buffer
 *
 * @return 0 if successful
 * @return 1 if Mask Parameter record was not found in Model
 * @return 2 if invalid Mask Parameter data type
 */
uint8 readMaskParamData(uint16 blockParamId, uint8 maskParamId, float64* buffer);
/**
 * @brief Writes Mask Parameter data from buffer.
 *
 * This function searches for the Mask Parameter in the current X2C Model.
 * If the Mask Parameter record was found, the function copies the data in the buffer into the Mask Parameter data.
 *
 * @param[in] blockParamId Block Parameter ID
 * @param[in] maskParamId Mask Parameter ID
 * @param[in] buffer Buffer
 *
 * @return 0 if successful
 * @return 1 if Mask Parameter record was not found in Model
 * @return 2 if invalid Mask Parameter data type
 * @return 3 if Mask Parameter conversion failed
 */
uint8 writeMaskParamData(uint16 blockParamId, uint8 maskParamId, float64* buffer);

#ifdef __cplusplus
}
#endif

#endif
