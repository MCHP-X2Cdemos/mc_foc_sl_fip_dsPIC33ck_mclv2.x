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
/**     Description:	PI Controller with                                   **/
/**							- Enable Input									 **/
/**							- Anti Wind-up									 **/
/**							- Initial Condition Input	 					 **/
/**							- Output Limitation								 **/
/**						Calculation ZOH:									 **/
/**	       						                1          			 		 **/
/** 						y = ( Kp + Ki*Ts* -----  ) * u					 **/
/**          					              z - 1	   						 **/
/**																			 **/
/**						-> y(k) = b1.u(k) + b0.u(k-1) + y(k-1)				 **/
/**																			 **/
/* USERCODE-END:Description                                                                                           */
#include "PILimit_FiP16.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(PILimit_FiP16_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
/* Inputs */
#define IN 				(*pTPILimit_FiP16->In)			/* Q15 */
#define ENABLE 			(*pTPILimit_FiP16->Enable)		/* Q0 */
#define INIT 			(*pTPILimit_FiP16->Init)		/* Q15 */

#ifndef LIMIT_UP
	#define LIMIT_UP 	(*pTPILimit_FiP16->max)			/* Q15 */
	#define LIMIT_DOWN 	(*pTPILimit_FiP16->min)			/* Q15 */
#endif

/* Outputs */
#define OUT	 			(pTPILimit_FiP16->Out)			/* Q15 */
													
/* Parameter */
#define	B0				(pTPILimit_FiP16->b0)			/* Qx */
#define	B1				(pTPILimit_FiP16->b1)			/* Qy */
#define SFR0			(pTPILimit_FiP16->sfrb0)		/* x */
#define SFR1			(pTPILimit_FiP16->sfrb1)		/* y */

/* Variables */ 
#define I_OLD			(pTPILimit_FiP16->i_old)		/* Q30 */
#define ENABLE_OLD		(pTPILimit_FiP16->enable_old)

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void PILimit_FiP16_Update(PILIMIT_FIP16 *pTPILimit_FiP16)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
	int32 y, yp;

	if (ENABLE)	/* Block enabled */
	{
		if (!ENABLE_OLD)	/* rising edge of enable signal occurred */
		{
		 	/* preset old value */
		 	I_OLD = ((int32)INIT) << 15;
		}

		/* Proportional term */
        #ifdef __XC16__
            yp = __builtin_mulss(B1, IN) >> SFR1;	/* Q15 */
        #else
            yp = ((int32)B1 * (int32)IN) >> SFR1;	/* Q15 */
        #endif

		/* Sum of proportional and integral term */
		y = yp + (I_OLD>>15);						/* Q15 */

		/* Output limitation and anti wind-up */
		if (y > LIMIT_UP)			/* output is beyond upper limit */
		{
			/* output limitation to upper boundary */
			y = LIMIT_UP;

			/* limitation of integral part */
			if (yp > LIMIT_UP)
			{
				yp = LIMIT_UP;
			}
			I_OLD = (LIMIT_UP - yp) << 15;			/* Q30 */

		}
		else if (y < LIMIT_DOWN)	/* output is beyond lower limit */
		{
			/* output limitation to lower boundary */
			y = LIMIT_DOWN;

			/* limitation of integral part */
			if (yp < LIMIT_DOWN)
			{
				yp = LIMIT_DOWN;
			}
			I_OLD = (LIMIT_DOWN - yp) << 15;		/* Q30 */
		}
		else
		{
			/* No output limitation -> no limitation of integral term */
            #ifdef __XC16__
                I_OLD += (__builtin_mulss(B0, IN) << (15-SFR0));	/* Q30 */
            #else
                I_OLD += (((int32)B0 * (int32)IN) << (15-SFR0));	/* Q30 */
            #endif
		}

		/* Assign output */
		OUT = (int16)y;

	}
	else				/* Block disabled */
	{
		OUT = 0;	/* reset output */
	}
	ENABLE_OLD = ENABLE;

/* USERCODE-END:UpdateFnc                                                                                             */

}

/**********************************************************************************************************************/
/** Initialization                                                                                                   **/
/**********************************************************************************************************************/
void PILimit_FiP16_Init(PILIMIT_FIP16 *pTPILimit_FiP16)
{
    pTPILimit_FiP16->ID = PILIMIT_FIP16_ID;
    pTPILimit_FiP16->Out = 0;
/* USERCODE-BEGIN:InitFnc                                                                                             */
    /* preset old values */
  	I_OLD = ((int32)INIT) << 15;
 	ENABLE_OLD = false;

/* USERCODE-END:InitFnc                                                                                               */
}

/**********************************************************************************************************************/
/** Load block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 PILimit_FiP16_Load(const PILIMIT_FIP16 *pTPILimit_FiP16, uint8 data[], uint16 *dataLength, uint16 maxSize)
{
    uint8 error = (uint8)0;
    if ((uint16)6 > maxSize)
    {
        error = (uint8)1;
    }
    else
    {
        data[0] = (uint8)(pTPILimit_FiP16->b0 & 0x00FF);
        data[1] = (uint8)((pTPILimit_FiP16->b0 >> 8) & 0x00FF);
        data[2] = (uint8)(pTPILimit_FiP16->b1 & 0x00FF);
        data[3] = (uint8)((pTPILimit_FiP16->b1 >> 8) & 0x00FF);
        data[4] = (uint8)pTPILimit_FiP16->sfrb0;
        data[5] = (uint8)pTPILimit_FiP16->sfrb1;
        *dataLength = (uint16)6;
/* USERCODE-BEGIN:LoadFnc                                                                                             */
/* USERCODE-END:LoadFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Save block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 PILimit_FiP16_Save(PILIMIT_FIP16 *pTPILimit_FiP16, const uint8 data[], uint16 dataLength)
{
    uint8 error;

    if (dataLength != (uint16)6)
    {
        error = (uint8)1;
    }
    else
    {
        pTPILimit_FiP16->b0 = UINT16_TO_INT16((uint16)data[0] + \
            ((uint16)data[1] << 8));
        pTPILimit_FiP16->b1 = UINT16_TO_INT16((uint16)data[2] + \
            ((uint16)data[3] << 8));
        pTPILimit_FiP16->sfrb0 = UINT8_TO_INT8((uint8)data[4]);
        pTPILimit_FiP16->sfrb1 = UINT8_TO_INT8((uint8)data[5]);
        error = (uint8)0;
/* USERCODE-BEGIN:SaveFnc                                                                                             */
/* USERCODE-END:SaveFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(PILIMIT_FIP16_ISLINKED)
void* PILimit_FiP16_GetAddress(const PILIMIT_FIP16* block, uint16 elementId)
{
    void* addr;
    switch (elementId)
    {
        case 1:
            addr = (void*)block->In;
            break;
        case 2:
            addr = (void*)block->Init;
            break;
        case 3:
            addr = (void*)block->max;
            break;
        case 4:
            addr = (void*)block->min;
            break;
        case 5:
            addr = (void*)block->Enable;
            break;
        case 6:
            addr = (void*)&block->Out;
            break;
        default:
            addr = (void*)0;
            break;
    }
    return (addr);
}
#endif
