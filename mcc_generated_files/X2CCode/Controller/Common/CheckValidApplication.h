/**
 * @file
 * @brief Checks reset state
 */
/*
 * $LastChangedRevision: 1273 $
 * $LastChangedDate:: 2017-09-28 15:07:29 +0200#$
 *
 * Copyright (c) 2013, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
 * All rights reserved.
 */
#ifndef CHECKVALIDAPPLICATION_H
#define CHECKVALIDAPPLICATION_H

#ifdef __cplusplus
extern "C" {
#endif

#include "Target.h"
#include "TableStruct.h"

/* maximum watchdogs reset after propgram stays in monitor */
#define MAX_WATCHDOG_RESTS ((int16)10)

/* public prototypes */
void boot(void);
uint8 checkValidApplication(void);

#ifdef __cplusplus
}
#endif

#endif
