/**
 * @file
 * @brief CRC-8-CCITT algorithm.
 */
/*
 * $LastChangedRevision: 1603 $
 * $LastChangedDate:: 2019-01-21 19:02:13 +0100#$
 *
 * This file is part of X2C. http://x2c.lcm.at/
 *
 * Copyright (c) 2013, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
 * All rights reserved.
 */
#ifndef CRC8CCITT_H
#define CRC8CCITT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "Target.h"

/* public prototypes */
uint8 crc8ccitt(const uint8* data, uint32 size);
uint8 crc8ccitt_addValue(uint8 crc, uint8 data);
uint8 crc8ccitt_init(void);

#ifdef __cplusplus
}
#endif

#endif
