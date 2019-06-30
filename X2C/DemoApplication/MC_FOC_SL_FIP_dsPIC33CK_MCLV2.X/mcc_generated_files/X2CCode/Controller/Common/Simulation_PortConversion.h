/*
 * Copyright (c) 2014, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
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
 * $LastChangedDate:: 2019-01-21 19:02:13 +0100 #$:
 */
/*
 * In simulation glue code all in/out-ports are handled as double -1..1.
 * This file provides functions to convert from double -1..1 to the internal representation and back.
 */


#ifndef __SIMULATION_PORTCONVERSION__
#define __SIMULATION_PORTCONVERSION__

#include "Target.h"

/* Boolean <=> double */
static bool convert_double_to_bool(double value){
	if (value != 0.0){
		return true;
	}else{
		return false;
	}
}

static double convert_bool_to_double(bool value){
	if (value){
		return 1.0;
	}else{
		return 0.0;
	}
}

/* Q7 <=> double */
static int8 convert_double_to_Q7(double value) {
	value *= 128.0;       /*  2**7      = 128 */
	
	/* prepare for rounding */
	if (value >= 0.0) {
		value += 0.5;
	} else {
		value -= 0.5;
	}
	
	/* range limitation */
	if (value > 127.0) {  /* (2**7) - 1 = 127 */
		value = 127.0;
	} else if (value < -128.0) {
		value = 128.0;
	}

	return (int8)value;
}

static double convert_Q7_to_double(int8 value) {
  return ((double) value) / 128;
}



/* Q15 <=> double */
static int16 convert_double_to_Q15(double value) {
	value *= 32768.0;       /*  2**15      = 32768 */
	
	/* prepare for rounding */
	if (value >= 0.0) {
		value += 0.5;
	} else {
		value -= 0.5;
	}
	
	/* range limitation */
	if (value > 32767.0) {  /* (2**15) - 1 = 32767 */
		value = 32767.0;
	} else if (value < -32768.0) {
		value = -32768.0;
	}

	return (int16)value;	
}

static double convert_Q15_to_double(int16 value) {
  return ((double) value) / 32768.0;
}



/* Q31 <=> double */
static int32 convert_double_to_Q31(double value) {
	value *= 2147483648.0;        /*  2**31      = 2147483648 */
	
	/* prepare for rounding */
	if (value >= 0.0) {
		value += 0.5;
	} else {
		value -= 0.5;
	}
	
	/* range limitation */
	if (value > 2147483647.0) {   /* (2**31) - 1 = 2147483647 */
		value = 2147483647.0;
	} else if (value < -2147483648.0) {
		value = 2147483648.0;
	}

	return (int32)value;	
}

static double convert_Q31_to_double(int32 value) {
  return ((double) value) / 2147483648.0;
}



/* float32 <=> double */
static float32 convert_double_to_float32(double value) {
	/* TODO: implement correct rounding */
	return (float32)value;	
}

static double convert_float32_to_double(float32 value) {
  return ((double) value);
}



/* float64 <=> double */
static float64 convert_double_to_float64(double value) {
	return (float64)value;	
}

static double convert_float64_to_double(float64 value) {
  return ((double) value);
}

#endif
