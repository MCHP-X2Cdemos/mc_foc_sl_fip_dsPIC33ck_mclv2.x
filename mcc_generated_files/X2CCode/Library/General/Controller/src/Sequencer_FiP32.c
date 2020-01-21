/*
 * Copyright (c) 2014, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
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
/* Description: Generation of time delayed (enable) sequence.                 */
/* USERCODE-END:Description                                                                                           */
#include "Sequencer_FiP32.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(Sequencer_FiP32_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
/* Inputs */
#define START 		(*pTSequencer_FiP32->Start)

/* Outputs */
#define OUT1 		(pTSequencer_FiP32->Out1)
#define OUT2 		(pTSequencer_FiP32->Out2)
#define OUT3 		(pTSequencer_FiP32->Out3)
#define OUT4 		(pTSequencer_FiP32->Out4)

/* Parameters */
#define DELAY1		(pTSequencer_FiP32->delay1)
#define DELAY2		(pTSequencer_FiP32->delay2)
#define DELAY3		(pTSequencer_FiP32->delay3)
#define DELAY4		(pTSequencer_FiP32->delay4)

/* Variables */
#define	CNT			(pTSequencer_FiP32->cnt)
#define START_OLD	(pTSequencer_FiP32->start_old)

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void Sequencer_FiP32_Update(SEQUENCER_FIP32 *pTSequencer_FiP32)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
	int32 out1 = 0;
	int32 out2 = 0;
	int32 out3 = 0;
	int32 out4 = 0;

	if (START != 0)	/* start signal */
	{
		/* check for rising flank */
		if (START_OLD == 0)	/* rising edge of start signal occurred */
		{
		 	/* reset timer value */
			CNT  = 0;
		}

		/* compare delay values with timer value */
		if (CNT >= DELAY1)
		{
			out1 = INT32_MAX;
		}
		if (CNT >= DELAY2)
		{
			out2 = INT32_MAX;
		}
		if (CNT >= DELAY3)
		{
			out3 = INT32_MAX;
		}
		if (CNT >= DELAY4)
		{
			out4 = INT32_MAX;
		}

		/* check for timer overflow */
		if (CNT < UINT16_MAX)
		{
			CNT++;
		}
		else
		{
			CNT = UINT16_MAX;
		}
	}

	/* assign outputs */
	OUT1 = out1;
	OUT2 = out2;
	OUT3 = out3;
	OUT4 = out4;

	/* save start signal for next cycle */
	START_OLD = START;

/* USERCODE-END:UpdateFnc                                                                                             */

}

/**********************************************************************************************************************/
/** Initialization                                                                                                   **/
/**********************************************************************************************************************/
void Sequencer_FiP32_Init(SEQUENCER_FIP32 *pTSequencer_FiP32)
{
    pTSequencer_FiP32->ID = SEQUENCER_FIP32_ID;
    pTSequencer_FiP32->Out1 = 0;
    pTSequencer_FiP32->Out2 = 0;
    pTSequencer_FiP32->Out3 = 0;
    pTSequencer_FiP32->Out4 = 0;
/* USERCODE-BEGIN:InitFnc                                                                                             */
     CNT = 0;
     START_OLD = 0;

/* USERCODE-END:InitFnc                                                                                               */
}

/**********************************************************************************************************************/
/** Load block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 Sequencer_FiP32_Load(const SEQUENCER_FIP32 *pTSequencer_FiP32, uint8 data[], uint16 *dataLength, uint16 maxSize)
{
    uint8 error = (uint8)0;
    if ((uint16)8 > maxSize)
    {
        error = (uint8)1;
    }
    else
    {
        data[0] = (uint8)(pTSequencer_FiP32->delay1 & 0x00FF);
        data[1] = (uint8)((pTSequencer_FiP32->delay1 >> 8) & 0x00FF);
        data[2] = (uint8)(pTSequencer_FiP32->delay2 & 0x00FF);
        data[3] = (uint8)((pTSequencer_FiP32->delay2 >> 8) & 0x00FF);
        data[4] = (uint8)(pTSequencer_FiP32->delay3 & 0x00FF);
        data[5] = (uint8)((pTSequencer_FiP32->delay3 >> 8) & 0x00FF);
        data[6] = (uint8)(pTSequencer_FiP32->delay4 & 0x00FF);
        data[7] = (uint8)((pTSequencer_FiP32->delay4 >> 8) & 0x00FF);
        *dataLength = (uint16)8;
/* USERCODE-BEGIN:LoadFnc                                                                                             */
/* USERCODE-END:LoadFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Save block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 Sequencer_FiP32_Save(SEQUENCER_FIP32 *pTSequencer_FiP32, const uint8 data[], uint16 dataLength)
{
    uint8 error;

    if (dataLength != (uint16)8)
    {
        error = (uint8)1;
    }
    else
    {
        pTSequencer_FiP32->delay1 = ((uint16)data[0] + \
            ((uint16)data[1] << 8));
        pTSequencer_FiP32->delay2 = ((uint16)data[2] + \
            ((uint16)data[3] << 8));
        pTSequencer_FiP32->delay3 = ((uint16)data[4] + \
            ((uint16)data[5] << 8));
        pTSequencer_FiP32->delay4 = ((uint16)data[6] + \
            ((uint16)data[7] << 8));
        error = (uint8)0;
/* USERCODE-BEGIN:SaveFnc                                                                                             */
/* USERCODE-END:SaveFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(SEQUENCER_FIP32_ISLINKED)
void* Sequencer_FiP32_GetAddress(const SEQUENCER_FIP32* block, uint16 elementId)
{
    void* addr;
    switch (elementId)
    {
        case 1:
            addr = (void*)block->Start;
            break;
        case 2:
            addr = (void*)&block->Out1;
            break;
        case 3:
            addr = (void*)&block->Out2;
            break;
        case 4:
            addr = (void*)&block->Out3;
            break;
        case 5:
            addr = (void*)&block->Out4;
            break;
        default:
            addr = (void*)0;
            break;
    }
    return (addr);
}
#endif
