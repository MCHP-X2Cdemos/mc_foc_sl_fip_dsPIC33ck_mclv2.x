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
#include "PID_Float32.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
    #pragma CODE_SECTION(PID_Float32_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
/* Inputs */
#define IN 				(*pTPID_Float32->In)
#define ENABLE 			(*pTPID_Float32->Enable)
#define INIT 			(*pTPID_Float32->Init)

/* Outputs */
#define OUT				(pTPID_Float32->Out)

/* Parameter */
#define	B0				(pTPID_Float32->b0)
#define	B1				(pTPID_Float32->b1)
#define	B0D				(pTPID_Float32->b0d)
#define	B1D				(pTPID_Float32->b1d)
#define	A0D				(pTPID_Float32->a0d)

/* Variables */
#define I_OLD			(pTPID_Float32->i_old)
#define IN_OLD			(pTPID_Float32->in_old)
#define D_OLD			(pTPID_Float32->d_old)
#define ENABLE_OLD		(pTPID_Float32->enable_old)

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void PID_Float32_Update(PID_FLOAT32 *pTPID_Float32)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
	float32 yp, yd;

    if (ENABLE) /* Block enabled */
    {
        if (!ENABLE_OLD)    /* rising edge of enable signal occurred */
		{
		 	/* preset old values */
		 	I_OLD  = INIT;
			IN_OLD = 0;
			D_OLD  = 0;
		}

		/* Proportional term */
		yp  = B1 * IN;

   		/* Derivative term */
		yd  =  B0D * IN_OLD;
		yd += (B1D * IN);
		yd -= (A0D * D_OLD);

		/* Sum */
		OUT = yp + yd + I_OLD;

		/* Integral term */
		I_OLD += (B0 * IN);


		/* Save relevant data for next call */
		IN_OLD = IN;
		D_OLD  = yd;

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
void PID_Float32_Init(PID_FLOAT32 *pTPID_Float32)
{
    pTPID_Float32->ID = PID_FLOAT32_ID;
    pTPID_Float32->Out = 0;
/* USERCODE-BEGIN:InitFnc                                                                                             */
  	/* preset old values */
    I_OLD  = INIT;
  	IN_OLD = 0;
  	D_OLD  = 0;
   	ENABLE_OLD = false;

/* USERCODE-END:InitFnc                                                                                               */
}

/**********************************************************************************************************************/
/** Load block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 PID_Float32_Load(const PID_FLOAT32 *pTPID_Float32, uint8 data[], uint16 *dataLength, uint16 maxSize)
{
    uint8 error = (uint8)0;
    if ((uint16)20 > maxSize)
    {
        error = (uint8)1;
    }
    else
    {
        data[0] = (uint8)((*(uint32*)&(pTPID_Float32->b0)) & 0x000000FF);
        data[1] = (uint8)((*(uint32*)&(pTPID_Float32->b0) >> 8) & 0x000000FF);
        data[2] = (uint8)((*(uint32*)&(pTPID_Float32->b0) >> 16) & 0x000000FF);
        data[3] = (uint8)((*(uint32*)&(pTPID_Float32->b0) >> 24) & 0x000000FF);
        data[4] = (uint8)((*(uint32*)&(pTPID_Float32->b1)) & 0x000000FF);
        data[5] = (uint8)((*(uint32*)&(pTPID_Float32->b1) >> 8) & 0x000000FF);
        data[6] = (uint8)((*(uint32*)&(pTPID_Float32->b1) >> 16) & 0x000000FF);
        data[7] = (uint8)((*(uint32*)&(pTPID_Float32->b1) >> 24) & 0x000000FF);
        data[8] = (uint8)((*(uint32*)&(pTPID_Float32->b0d)) & 0x000000FF);
        data[9] = (uint8)((*(uint32*)&(pTPID_Float32->b0d) >> 8) & 0x000000FF);
        data[10] = (uint8)((*(uint32*)&(pTPID_Float32->b0d) >> 16) & 0x000000FF);
        data[11] = (uint8)((*(uint32*)&(pTPID_Float32->b0d) >> 24) & 0x000000FF);
        data[12] = (uint8)((*(uint32*)&(pTPID_Float32->b1d)) & 0x000000FF);
        data[13] = (uint8)((*(uint32*)&(pTPID_Float32->b1d) >> 8) & 0x000000FF);
        data[14] = (uint8)((*(uint32*)&(pTPID_Float32->b1d) >> 16) & 0x000000FF);
        data[15] = (uint8)((*(uint32*)&(pTPID_Float32->b1d) >> 24) & 0x000000FF);
        data[16] = (uint8)((*(uint32*)&(pTPID_Float32->a0d)) & 0x000000FF);
        data[17] = (uint8)((*(uint32*)&(pTPID_Float32->a0d) >> 8) & 0x000000FF);
        data[18] = (uint8)((*(uint32*)&(pTPID_Float32->a0d) >> 16) & 0x000000FF);
        data[19] = (uint8)((*(uint32*)&(pTPID_Float32->a0d) >> 24) & 0x000000FF);
        *dataLength = (uint16)20;
/* USERCODE-BEGIN:LoadFnc                                                                                             */
/* USERCODE-END:LoadFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Save block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 PID_Float32_Save(PID_FLOAT32 *pTPID_Float32, const uint8 data[], uint16 dataLength)
{
    uint8 error;
    uint32 tmp32;

    if (dataLength != (uint16)20)
    {
        error = (uint8)1;
    }
    else
    {
        tmp32 = (uint32)data[0] + \
            ((uint32)data[1] << 8) + ((uint32)data[2] << 16) + \
            ((uint32)data[3] << 24);
        pTPID_Float32->b0 = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[4] + \
            ((uint32)data[5] << 8) + ((uint32)data[6] << 16) + \
            ((uint32)data[7] << 24);
        pTPID_Float32->b1 = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[8] + \
            ((uint32)data[9] << 8) + ((uint32)data[10] << 16) + \
            ((uint32)data[11] << 24);
        pTPID_Float32->b0d = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[12] + \
            ((uint32)data[13] << 8) + ((uint32)data[14] << 16) + \
            ((uint32)data[15] << 24);
        pTPID_Float32->b1d = (float32)(*(float32*)&tmp32);
        tmp32 = (uint32)data[16] + \
            ((uint32)data[17] << 8) + ((uint32)data[18] << 16) + \
            ((uint32)data[19] << 24);
        pTPID_Float32->a0d = (float32)(*(float32*)&tmp32);
        error = (uint8)0;
/* USERCODE-BEGIN:SaveFnc                                                                                             */
/* USERCODE-END:SaveFnc                                                                                               */
    }
    return (error);
}

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(PID_FLOAT32_ISLINKED)
void* PID_Float32_GetAddress(const PID_FLOAT32* block, uint16 elementId)
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
            addr = (void*)block->Enable;
            break;
        case 4:
            addr = (void*)&block->Out;
            break;
        default:
            addr = (void*)0;
            break;
    }
    return (addr);
}
#endif
