/*
 * Square root and inverse square root lookup table.
 *
 * $$LastChangedRevision: 387 $$
 * $$LastChangedDate: 2014-03-26 10:55:38 +0100 (Wed, 26 Mar 2014) $$
 * $$LastChangedBy: EAL\sfragner $$
 *
 * Copyright (c) 2013 Linz Center of Mechatronics GmbH
 * All rights reserved.
 */
#ifndef __SQRT_DATA__
	#define __SQRT_DATA__

	#include "CommonFcts.h"

	extern const int8  Sqrt_Table8[257];
	extern const int16 Sqrt_Table16[257];
	extern const int32 Sqrt_Table32[257];
	extern const int8  InvSqrt_Table8[257];
	extern const int16 InvSqrt_Table16[257];
	extern const int32 InvSqrt_Table32[257];

#endif
