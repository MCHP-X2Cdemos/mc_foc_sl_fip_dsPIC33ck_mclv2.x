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
 * $LastChangedRevision: 1971 $
 * $LastChangedDate:: 2020-07-20 12:23:30 +0200#$
 */
#include "CommonFcts.h"
#include "X2C.h"
#include "ModelFcts.h"

#define TYPE_FLOAT (1)
#define TYPE_ENUM (2)

uint8 readMaskParamData(uint16 blockParamId, uint8 maskParamId, float64* buffer)
{
    uint8 i;
    uint16 index;
    void* data;

    if (getMaskParamDataTableIndex(maskParamDataTable, blockParamId, maskParamId, &index) != 0)
    {
        return 1;
    }

    data = maskParamDataTable[index].data;
    switch (maskParamDataTable[index].type)
    {
    case TYPE_FLOAT:
        for (i=0 ; i<maskParamDataTable[index].dataSize ; i++) {
            buffer[i] = ((float64*)data)[i];
        }
        break;
    case TYPE_ENUM:
        for (i=0 ; i<maskParamDataTable[index].dataSize ; i++) {
            buffer[i] = (float64)((uint8*)data)[i];
        }
        break;
    default:
        return 2;
    }

    return 0;
}

uint8 writeMaskParamData(uint16 blockParamId, uint8 maskParamId, float64* buffer)
{
    uint8 i;
    uint16 mpIndex, dataIndex;
    void* data;

    /* lookup index of Block in Mask Parameter info table for backup, restore and conversion functions */
    if (getMaskParamIndex(maskParamIdTable, blockParamId, &mpIndex) != 0)
    {
        return 1;
    }

    if (getMaskParamDataTableIndex(maskParamDataTable, blockParamId, maskParamId, &dataIndex) != 0)
    {
        return 1;
    }

    /* Backup current Mask Parameters in case of conversion failure */
    maskParamIdTable[mpIndex].backupMaskParameter(maskParamIdTable[mpIndex].maskParameter);

    data = maskParamDataTable[dataIndex].data;
    switch (maskParamDataTable[dataIndex].type)
    {
    case TYPE_FLOAT:
        for (i=0 ; i<maskParamDataTable[dataIndex].dataSize ; i++) {
            ((float64*)data)[i] = buffer[i];
        }
        break;
    case TYPE_ENUM:
        for (i=0 ; i<maskParamDataTable[dataIndex].dataSize ; i++) {
            ((uint8*)data)[i] = (uint8)buffer[i];
        }
        break;
    default:
        maskParamIdTable[mpIndex].restoreMaskParameter(maskParamIdTable[mpIndex].maskParameter);
        return 2;
    }

    /* Convert Mask Parameters */
    if (maskParamIdTable[mpIndex].convertMaskParameter(maskParamIdTable[mpIndex].block, maskParamIdTable[mpIndex].maskParameter) != 0)
    {
        /* Backup previous Mask Parameters in case of conversion failure and return error */
        maskParamIdTable[mpIndex].restoreMaskParameter(maskParamIdTable[mpIndex].maskParameter);
        return 3;
    }

    return 0;
}
