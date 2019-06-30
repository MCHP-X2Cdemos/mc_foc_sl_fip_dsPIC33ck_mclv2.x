/*
 * This file is part of X2C. http://x2c.lcm.at/
 * $LastChangedRevision: 1693 $
 */
/* USERCODE-BEGIN:Description                                                                                         */
/**     Description:	Continuously differentiable output change rate limitation with	sin^2 shape                  **/
/**						Calculation:                               													 **/
/**							du/dt = 0:																				 **/
/**								y = u																				 **/
/**							du/dt <> 0:																				 **/
/**								y = u * sin^2(t)		(simplified)												 **/
/**																													 **/
/**		Caution:	A step in the input signal during a	running limitation process will not abort the running        **/
/**					limitation process!																				 **/
/**																													 **/
/* USERCODE-END:Description                                                                                           */
#ifndef SIN2LIMITER_FLOAT64_H
#define SIN2LIMITER_FLOAT64_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"

#if !defined(SIN2LIMITER_FLOAT64_ISLINKED)
#define SIN2LIMITER_FLOAT64_ID ((uint16)116)

typedef struct {
    uint16          ID;
    float64         *In;
    float64         *Init;
    bool            *Enable;
    float64         Out;
    float64         RateUp;
    float64         RateDown;
    float64         Scaled_RateUp;
    float64         Scaled_RateDown;
    float64         Out_end;
    float64         Level;
    float64         Step_Height;
    int8            State;
    bool            Enable_old;
} SIN2LIMITER_FLOAT64;

#define SIN2LIMITER_FLOAT64_FUNCTIONS { \
    SIN2LIMITER_FLOAT64_ID, \
    (void (*)(void*))Sin2Limiter_Float64_Update, \
    (void (*)(void*))Sin2Limiter_Float64_Init, \
    (tLoadImplementationParameter)Sin2Limiter_Float64_Load, \
    (tSaveImplementationParameter)Sin2Limiter_Float64_Save, \
    (void* (*)(const void*, uint16))Sin2Limiter_Float64_GetAddress }

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void Sin2Limiter_Float64_Update(SIN2LIMITER_FLOAT64 *pTSin2Limiter_Float64);
void Sin2Limiter_Float64_Init(SIN2LIMITER_FLOAT64 *pTSin2Limiter_Float64);
uint8 Sin2Limiter_Float64_Load(const SIN2LIMITER_FLOAT64 *pTSin2Limiter_Float64, uint8 data[], uint16 *dataLength, uint16 maxSize);
uint8 Sin2Limiter_Float64_Save(SIN2LIMITER_FLOAT64 *pTSin2Limiter_Float64, const uint8 data[], uint16 dataLength);
void* Sin2Limiter_Float64_GetAddress(const SIN2LIMITER_FLOAT64 *block, uint16 elementId);

#endif

#ifdef __cplusplus
}
#endif

#endif
