/*
 * Copyright (c) 2013, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
 * All rights reserved.
 */
/*
 * This file is part of X2C. http://x2c.lcm.at/
 * $LastChangedRevision: 1603 $
 */
/* USERCODE-BEGIN:Description                                                                                         */
/*      Description:	Addition of Input 1 and Input 2 with output wrapping. */
/*						Calculation:										  */
/* 							Out = In1 + In2									  */
/* 																			  */
/* USERCODE-END:Description                                                                                           */
#ifndef UADD_FIP16_H
#define UADD_FIP16_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"

#if !defined(UADD_FIP16_ISLINKED)
#define UADD_FIP16_ID ((uint16)4977)

typedef struct {
    uint16          ID;
    int16           *In1;
    int16           *In2;
    int16           Out;
} UADD_FIP16;

#define UADD_FIP16_FUNCTIONS { \
    UADD_FIP16_ID, \
    (void (*)(void*))uAdd_FiP16_Update, \
    (void (*)(void*))uAdd_FiP16_Init, \
    (tLoadImplementationParameter)Common_Load, \
    (tSaveImplementationParameter)Common_Save, \
    (void* (*)(const void*, uint16))uAdd_FiP16_GetAddress }

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void uAdd_FiP16_Update(UADD_FIP16 *pTuAdd_FiP16);
void uAdd_FiP16_Init(UADD_FIP16 *pTuAdd_FiP16);
void* uAdd_FiP16_GetAddress(const UADD_FIP16 *block, uint16 elementId);

#endif

#ifdef __cplusplus
}
#endif

#endif
