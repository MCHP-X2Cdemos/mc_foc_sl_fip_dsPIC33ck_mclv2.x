/*
 * Exponential function lookup table.
 * -1..0..1 ~ exp(-1)..exp(1)
 *
 * Caution: input > 0 leads to output = 1!
 *
 * $LastChangedRevision: 632 $
 *
 * Copyright (c) 2013, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
 * All rights reserved.
 */
#ifndef __EXP_DATA__
#define __EXP_DATA__

#include "CommonFcts.h"

extern const int8 Exp_Table8[257];
extern const int16 Exp_Table16[257];
extern const int32 Exp_Table32[257];

#endif
