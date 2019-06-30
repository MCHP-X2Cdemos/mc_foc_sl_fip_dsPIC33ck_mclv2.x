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
#ifndef UADD_FIP32_H
#define UADD_FIP32_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"

#if !defined(UADD_FIP32_ISLINKED)
#define UADD_FIP32_ID ((uint16)4978)

typedef struct {
    uint16          ID;
    int32           *In1;
    int32           *In2;
    int32           Out;
} UADD_FIP32;

#define UADD_FIP32_FUNCTIONS { \
    UADD_FIP32_ID, \
    (void (*)(void*))uAdd_FiP32_Update, \
    (void (*)(void*))uAdd_FiP32_Init, \
    (tLoadImplementationParameter)Common_Load, \
    (tSaveImplementationParameter)Common_Save, \
    (void* (*)(const void*, uint16))uAdd_FiP32_GetAddress }

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void uAdd_FiP32_Update(UADD_FIP32 *pTuAdd_FiP32);
void uAdd_FiP32_Init(UADD_FIP32 *pTuAdd_FiP32);
void* uAdd_FiP32_GetAddress(const UADD_FIP32 *block, uint16 elementId);

#endif

#ifdef __cplusplus
}
#endif

#endif
