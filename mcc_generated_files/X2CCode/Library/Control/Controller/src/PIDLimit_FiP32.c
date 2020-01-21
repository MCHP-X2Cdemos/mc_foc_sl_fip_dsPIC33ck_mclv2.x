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
/*     Description:	 PID Controller with
 *							- Enable Input
 *							- Anti Windup
 *							- Initial Condition Input
 *							- Output Limitation
 *						Calculation ZOH:
 *	       						          1       	        z - 1
 * 						y = (Kp + Ki*Ts ----- + Kd*wc --------------- )*u
 *          					        z - 1	 	  z - exp(-wc*Ts)
 *
 *						-> y(k) = b1.u(k) + b0.u(k-1) + y(k-1) + b1d.u(k) + b0d.u(k-1) - a0d.yd(k-1)
 *
 *						Note:
 *							PIDLimit source code is used!
 */
/* USERCODE-END:Description                                                                                           */
#include "PIDLimit_FiP32.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(PIDLimit_FiP32_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
/* Inputs */
#define IN 				(*pTPIDLimit_FiP32->In)			/* Q31 */
#define ENABLE 			(*pTPIDLimit_FiP32->Enable)		/* Q0 */
#define INIT 			(*pTPIDLimit_FiP32->Init)		/* Q0 */

#ifndef LIMIT_UP
	#define LIMIT_UP 	(*pTPIDLimit_FiP32->max)		/* Q62 */
	#define LIMIT_DOWN 	(*pTPIDLimit_FiP32->min)		/* Q62 */
#endif

/* Outputs */
#define OUT	 			(pTPIDLimit_FiP32->Out)			/* Q31 */
 													
/* Parameter */
#define	B0				(pTPIDLimit_FiP32->b0)			/* Qx */
#define	B1				(pTPIDLimit_FiP32->b1)			/* Qy */
#define	B0D				(pTPIDLimit_FiP32->b0d)			/* Qz */
#define	B1D				(pTPIDLimit_FiP32->b1d)			/* Qz */
#define	A0D				(pTPIDLimit_FiP32->a0d)			/* Q31 */

#define SFR0			(pTPIDLimit_FiP32->sfrb0)		/* x */
#define SFR1			(pTPIDLimit_FiP32->sfrb1)		/* y */
#define SFRD			(pTPIDLimit_FiP32->sfrd)		/* z */

/* Variables */ 
#define I_OLD			(pTPIDLimit_FiP32->i_old)		/* Q62 */
#define IN_OLD			(pTPIDLimit_FiP32->in_old)		/* Q31 */
#define D_OLD			(pTPIDLimit_FiP32->d_old)		/* Q31 */
#define ENABLE_OLD		(pTPIDLimit_FiP32->enable_old)

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void PIDLimit_FiP32_Update(PIDLIMIT_FIP32 *pTPIDLimit_FiP32)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
	int64 y, yp, yd, ypd;

    if (ENABLE) /* Block enabled */
    {
        if (!ENABLE_OLD)    /* rising edge of enable signal occurred */
		{
			/* preset old values */
			I_OLD = ((int64)INIT) << 31;
			IN_OLD  = 0;
			D_OLD   = 0;
		}

		/* Proportional term */
		yp  = ((int64)B1 * (int64)IN) >> SFR1;			/* Q31 */

		/* Derivative term */
		yd  =  ((int64)B0D * (int64)IN_OLD);			/* Qz */
		yd += (((int64)B1D * (int64)IN));				/* Qz */
		yd  = yd >> SFRD;								/* Qz -> Q62 */
		yd -= (((int64)A0D * (int64)D_OLD) >> 31);		/* Q62 */
		LIMIT(yd, INT32_MAX);

		/* Sum */
		ypd = yp + yd;
		y = ypd + (I_OLD >> 31);

		/* Output limitation and anti wind-up */
		if (y > LIMIT_UP)			/* output is beyond upper limit */
		{
			/* limitation of output to upper boundary */
			y = LIMIT_UP;

			/* limitation of integral part */
			if (B0 != 0)	/* check for integral coefficient */
			{
				if (ypd > LIMIT_UP)
				{
					ypd = LIMIT_UP;
				}
				I_OLD = (LIMIT_UP - ypd) << 31;
			}
		}
		else if (y < LIMIT_DOWN)	/* output is beyond lower limit */
		{
			/* limitation of output to lower boundary */
			y = LIMIT_DOWN;

			/* limitation of integral part */
			if (B0 != 0)	/* check for integral coefficient */
			{
				if (ypd < LIMIT_DOWN)
				{
					ypd = LIMIT_DOWN;
				}
				I_OLD = (LIMIT_DOWN - ypd) << 31;
			}
		}
		else
		{
			/* No output limitation -> no limitation of integral term */
			I_OLD += (((int64)B0 * (int64)IN) << (31-SFR0));	/* Q62 */
		}

		/* Assign output */
		OUT = (int32)y;

		/* Save relevant data for next call */
		IN_OLD = IN;
		D_OLD  = (int32)yd;

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
void PIDLimit_FiP32_Init(PIDLIMIT_FIP32 *pTPIDLimit_FiP32)
{
    pTPIDLimit_FiP32->ID = PIDLIMIT_FIP32_ID;
    pTPIDLimit_FiP32->Out = 0;
/* USERCODE-BEGIN:InitFnc                                                                                             */
 	/* preset old values */
	I_OLD = ((int64)INIT) << 31;
	IN_OLD  = 0;
	D_OLD   = 0;
 	ENABLE_OLD = false;

/* USERCODE-END:InitFnc                                                                                               */
}

/**********************************************************************************************************************/
/** Load block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 PIDLimit_FiP32_Load(const PIDLIMIT_FIP32 *pTPIDLimit_FiP32, uint8 data[], uint16 *dataLength, uint16 maxSize)
{
    uint8 error = (uint8)0;
    if ((uint16)23 > maxSize)
    {
        error = (uint8)1;
    }
    else
    {
        data[0] = (uint8)(pTPIDLimit_FiP32->b0 & 0x000000FF);
        data[1] = (uint8)((pTPIDLimit_FiP32->b0 >> 8) & 0x000000FF);
        data[2] = (uint8)((pTPIDLimit_FiP32->b0 >> 16) & 0x000000FF);
        data[3] = (uint8)((pTPIDLimit_FiP32->b0 >> 24) & 0x000000FF);
        data[4] = (uint8)(pTPIDLimit_FiP32->b1 & 0x000000FF);
        data[5] = (uint8)((pTPIDLimit_FiP32->b1 >> 8) & 0x000000FF);
        data[6] = (uint8)((pTPIDLimit_FiP32->b1 >> 16) & 0x000000FF);
        data[7] = (uint8)((pTPIDLimit_FiP32->b1 >> 24) & 0x000000FF);
        data[8] = (uint8)(pTPIDLimit_FiP32->b0d & 0x000000FF);
        data[9] = (uint8)((pTPIDLimit_FiP32->b0d >> 8) & 0x000000FF);
        data[10] = (uint8)((pTPIDLimit_FiP32->b0d >> 16) & 0x000000FF);
        data[11] = (uint8)((pTPIDLimit_FiP32->b0d >> 24) & 0x000000FF);
        data[12] = (uint8)(pTPIDLimit_FiP32->b1d & 0x000000FF);
        data[13] = (uint8)((pTPIDLimit_FiP32->b1d >> 8) & 0x000000FF);
        data[14] = (uint8)((pTPIDLimit_FiP32->b1d >> 16) & 0x000000FF);
        data[15] = (uint8)((pTPIDLimit_FiP32->b1d >> 24) & 0x000000FF);
        data[16] = (uint8)(pTPIDLimit_FiP32->a0d & 0x000000FF);
        data[17] = (uint8)((pTPIDLimit_FiP32->a0d >> 8) & 0x000000FF);
        data[18] = (uint8)((pTPIDLimit_FiP32->a0d >> 16) & 0x000000FF);
        data[19] = (uint8)((pTPIDLimit_FiP32->a0d >> 24) & 0x000000FF);
        data[20] = (uint8)pTPIDLimit_FiP32->sfrb0;
        data[21] = (uint8)pTPIDLimit_FiP32->sfrb1;
        data[22] = (uint8)pTPIDLimit_FiP32->sfrd;
        *dataLength = (uint16)23;
/* USERCODE-BEGIN:LoadFnc                                                                                             */
/* USERCODE-END:LoadFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Save block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 PIDLimit_FiP32_Save(PIDLIMIT_FIP32 *pTPIDLimit_FiP32, const uint8 data[], uint16 dataLength)
{
    uint8 error;

    if (dataLength != (uint16)23)
    {
        error = (uint8)1;
    }
    else
    {
        pTPIDLimit_FiP32->b0 = UINT32_TO_INT32((uint32)data[0] + \
            ((uint32)data[1] << 8) + ((uint32)data[2] << 16) + \
            ((uint32)data[3] << 24));
        pTPIDLimit_FiP32->b1 = UINT32_TO_INT32((uint32)data[4] + \
            ((uint32)data[5] << 8) + ((uint32)data[6] << 16) + \
            ((uint32)data[7] << 24));
        pTPIDLimit_FiP32->b0d = UINT32_TO_INT32((uint32)data[8] + \
            ((uint32)data[9] << 8) + ((uint32)data[10] << 16) + \
            ((uint32)data[11] << 24));
        pTPIDLimit_FiP32->b1d = UINT32_TO_INT32((uint32)data[12] + \
            ((uint32)data[13] << 8) + ((uint32)data[14] << 16) + \
            ((uint32)data[15] << 24));
        pTPIDLimit_FiP32->a0d = UINT32_TO_INT32((uint32)data[16] + \
            ((uint32)data[17] << 8) + ((uint32)data[18] << 16) + \
            ((uint32)data[19] << 24));
        pTPIDLimit_FiP32->sfrb0 = UINT8_TO_INT8((uint8)data[20]);
        pTPIDLimit_FiP32->sfrb1 = UINT8_TO_INT8((uint8)data[21]);
        pTPIDLimit_FiP32->sfrd = UINT8_TO_INT8((uint8)data[22]);
        error = (uint8)0;
/* USERCODE-BEGIN:SaveFnc                                                                                             */
/* USERCODE-END:SaveFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(PIDLIMIT_FIP32_ISLINKED)
void* PIDLimit_FiP32_GetAddress(const PIDLIMIT_FIP32* block, uint16 elementId)
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
