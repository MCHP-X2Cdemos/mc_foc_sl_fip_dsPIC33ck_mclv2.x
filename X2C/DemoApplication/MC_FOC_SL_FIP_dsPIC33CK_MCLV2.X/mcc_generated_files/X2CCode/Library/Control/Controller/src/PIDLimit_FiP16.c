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
#include "PIDLimit_FiP16.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(PIDLimit_FiP16_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
/* Inputs */
#define IN 				(*pTPIDLimit_FiP16->In)			/* Q15 */
#define ENABLE 			(*pTPIDLimit_FiP16->Enable)		/* Q0 */
#define INIT 			(*pTPIDLimit_FiP16->Init)		/* Q0 */

#ifndef LIMIT_UP
	#define LIMIT_UP 	(*pTPIDLimit_FiP16->max)		/* Q15 */
	#define LIMIT_DOWN 	(*pTPIDLimit_FiP16->min)		/* Q15 */
#endif

/* Outputs */
#define OUT				(pTPIDLimit_FiP16->Out)			/* Q15 */
 													
/* Parameter */
#define	B0				(pTPIDLimit_FiP16->b0)			/* Qx */
#define	B1				(pTPIDLimit_FiP16->b1)			/* Qy */
#define	B0D				(pTPIDLimit_FiP16->b0d)			/* Qz */
#define	B1D				(pTPIDLimit_FiP16->b1d)			/* Qz */
#define	A0D				(pTPIDLimit_FiP16->a0d)			/* Q15 */

#define SFR0			(pTPIDLimit_FiP16->sfrb0)		/* x */
#define SFR1			(pTPIDLimit_FiP16->sfrb1)		/* y */
#define SFRD			(pTPIDLimit_FiP16->sfrd)		/* z */

/* Variables */
#define I_OLD			(pTPIDLimit_FiP16->i_old)		/* Q30 */
#define IN_OLD			(pTPIDLimit_FiP16->in_old)		/* Q15 */
#define D_OLD			(pTPIDLimit_FiP16->d_old)		/* Q15 */
#define ENABLE_OLD		(pTPIDLimit_FiP16->enable_old)

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void PIDLimit_FiP16_Update(PIDLIMIT_FIP16 *pTPIDLimit_FiP16)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
	int32 y, yp, yd, ypd;

    if (ENABLE) /* Block enabled */
    {
        if (!ENABLE_OLD)    /* rising edge of enable signal occurred */
		{
		 	/* preset old values */
		 	I_OLD = ((int32)INIT) << 15;
			IN_OLD = 0;
			D_OLD  = 0;
		}

		/* Proportional term */
        #ifdef __XC16__
            yp = __builtin_mulss(B1, IN) >> SFR1;	/* Q15 */
        #else
            yp = ((int32)B1 * (int32)IN) >> SFR1;	/* Q15 */
        #endif
		
   		/* Derivative term */	
		yd  =  (int32)B0D * (int32)IN_OLD;				/* Qz */
		yd += ((int32)B1D * (int32)IN);					/* Qz */
		yd  = yd >> SFRD;								/* Qz -> Q15 */
		yd -= (((int32)A0D * (int32)D_OLD) >> 15);		/* Q15 */
		LIMIT(yd, INT16_MAX);

		/* Sum */
		ypd = yp + yd;
		y = ypd + (I_OLD >> 15);
			
		/* Output limitation and anti wind-up */
 		if (y > LIMIT_UP)			/* output is beyond upper limit	*/
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
				I_OLD = (LIMIT_UP - ypd) << 15;
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
				I_OLD = (LIMIT_DOWN - ypd) << 15;
			}
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
		
		/* Save relevant data for next call */
		IN_OLD = IN;
		D_OLD = (int16)yd;

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
void PIDLimit_FiP16_Init(PIDLIMIT_FIP16 *pTPIDLimit_FiP16)
{
    pTPIDLimit_FiP16->ID = PIDLIMIT_FIP16_ID;
    pTPIDLimit_FiP16->Out = 0;
/* USERCODE-BEGIN:InitFnc                                                                                             */
	/* preset old values */
  	I_OLD  = ((int32)INIT) << 15;
	IN_OLD = 0;
	D_OLD  = 0;
 	ENABLE_OLD = false;

/* USERCODE-END:InitFnc                                                                                               */
}

/**********************************************************************************************************************/
/** Load block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 PIDLimit_FiP16_Load(const PIDLIMIT_FIP16 *pTPIDLimit_FiP16, uint8 data[], uint16 *dataLength, uint16 maxSize)
{
    uint8 error = (uint8)0;
    if ((uint16)13 > maxSize)
    {
        error = (uint8)1;
    }
    else
    {
        data[0] = (uint8)(pTPIDLimit_FiP16->b0 & 0x00FF);
        data[1] = (uint8)((pTPIDLimit_FiP16->b0 >> 8) & 0x00FF);
        data[2] = (uint8)(pTPIDLimit_FiP16->b1 & 0x00FF);
        data[3] = (uint8)((pTPIDLimit_FiP16->b1 >> 8) & 0x00FF);
        data[4] = (uint8)(pTPIDLimit_FiP16->b0d & 0x00FF);
        data[5] = (uint8)((pTPIDLimit_FiP16->b0d >> 8) & 0x00FF);
        data[6] = (uint8)(pTPIDLimit_FiP16->b1d & 0x00FF);
        data[7] = (uint8)((pTPIDLimit_FiP16->b1d >> 8) & 0x00FF);
        data[8] = (uint8)(pTPIDLimit_FiP16->a0d & 0x00FF);
        data[9] = (uint8)((pTPIDLimit_FiP16->a0d >> 8) & 0x00FF);
        data[10] = (uint8)pTPIDLimit_FiP16->sfrb0;
        data[11] = (uint8)pTPIDLimit_FiP16->sfrb1;
        data[12] = (uint8)pTPIDLimit_FiP16->sfrd;
        *dataLength = (uint16)13;
/* USERCODE-BEGIN:LoadFnc                                                                                             */
/* USERCODE-END:LoadFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Save block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 PIDLimit_FiP16_Save(PIDLIMIT_FIP16 *pTPIDLimit_FiP16, const uint8 data[], uint16 dataLength)
{
    uint8 error;

    if (dataLength != (uint16)13)
    {
        error = (uint8)1;
    }
    else
    {
        pTPIDLimit_FiP16->b0 = UINT16_TO_INT16((uint16)data[0] + \
            ((uint16)data[1] << 8));
        pTPIDLimit_FiP16->b1 = UINT16_TO_INT16((uint16)data[2] + \
            ((uint16)data[3] << 8));
        pTPIDLimit_FiP16->b0d = UINT16_TO_INT16((uint16)data[4] + \
            ((uint16)data[5] << 8));
        pTPIDLimit_FiP16->b1d = UINT16_TO_INT16((uint16)data[6] + \
            ((uint16)data[7] << 8));
        pTPIDLimit_FiP16->a0d = UINT16_TO_INT16((uint16)data[8] + \
            ((uint16)data[9] << 8));
        pTPIDLimit_FiP16->sfrb0 = UINT8_TO_INT8((uint8)data[10]);
        pTPIDLimit_FiP16->sfrb1 = UINT8_TO_INT8((uint8)data[11]);
        pTPIDLimit_FiP16->sfrd = UINT8_TO_INT8((uint8)data[12]);
        error = (uint8)0;
/* USERCODE-BEGIN:SaveFnc                                                                                             */
/* USERCODE-END:SaveFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(PIDLIMIT_FIP16_ISLINKED)
void* PIDLimit_FiP16_GetAddress(const PIDLIMIT_FIP16* block, uint16 elementId)
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
