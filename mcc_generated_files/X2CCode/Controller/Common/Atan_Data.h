/*
 * Arc tangent function lookup table.
 * -1..0..1 ~ atan(-1..1)/atan(1) ~ -pi..pi
 *
 * $LastChangedRevision: 632 $
 *
 * Copyright (c) 2013, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
 * All rights reserved.
 */
#ifndef __ATAN_DATA__
#define __ATAN_DATA__

#include "CommonFcts.h"

extern const int8 Atan_Table8[257];
extern const int16 Atan_Table16[257];
extern const int32 Atan_Table32[257];

#endif
