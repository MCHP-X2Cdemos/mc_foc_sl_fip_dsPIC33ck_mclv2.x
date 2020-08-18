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
 * $LastChangedRevision: 1852 $
 * $LastChangedDate:: 2016-02-18 12:04:02 +0100#$
 */
#include "Sin_Data.h"

/*
 * Sine data in 8 bit format.
 * -128..0..127 ~ -Pi..0..Pi/256*255
 */
#ifndef __NO_SIN_TABLE8__
	const int8 Sin_Table8[257]  = {
		   0,    3,    6,    9,   12,   16,   19,   22,
		  25,   28,   31,   34,   37,   40,   43,   46,
		  49,   51,   54,   57,   60,   63,   65,   68,
		  71,   73,   76,   78,   81,   83,   85,   88,
		  90,   92,   94,   96,   98,  100,  102,  104,
		 106,  107,  109,  111,  112,  113,  115,  116,
		 117,  118,  120,  121,  122,  122,  123,  124,
		 125,  125,  126,  126,  126,  127,  127,  127,
		 127,  127,  127,  127,  126,  126,  126,  125,
		 125,  124,  123,  122,  122,  121,  120,  118,
		 117,  116,  115,  113,  112,  111,  109,  107,
		 106,  104,  102,  100,   98,   96,   94,   92,
		  90,   88,   85,   83,   81,   78,   76,   73,
		  71,   68,   65,   63,   60,   57,   54,   51,
		  49,   46,   43,   40,   37,   34,   31,   28,
		  25,   22,   19,   16,   12,    9,    6,    3,
		   0,   -3,   -6,   -9,  -12,  -16,  -19,  -22,
		 -25,  -28,  -31,  -34,  -37,  -40,  -43,  -46,
		 -49,  -51,  -54,  -57,  -60,  -63,  -65,  -68,
		 -71,  -73,  -76,  -78,  -81,  -83,  -85,  -88,
		 -90,  -92,  -94,  -96,  -98, -100, -102, -104,
		-106, -107, -109, -111, -112, -113, -115, -116,
		-117, -118, -120, -121, -122, -122, -123, -124,
		-125, -125, -126, -126, -126, -127, -127, -127,
		-127, -127, -127, -127, -126, -126, -126, -125,
		-125, -124, -123, -122, -122, -121, -120, -118,
		-117, -116, -115, -113, -112, -111, -109, -107,
		-106, -104, -102, -100,  -98,  -96,  -94,  -92,
		 -90,  -88,  -85,  -83,  -81,  -78,  -76,  -73,
		 -71,  -68,  -65,  -63,  -60,  -57,  -54,  -51,
		 -49,  -46,  -43,  -40,  -37,  -34,  -31,  -28,
		 -25,  -22,  -19,  -16,  -12,   -9,   -6,   -3, 0};
#endif

/*
 * Sine data in 16 bit format.
 * -128..0..127 ~ -Pi..0..Pi/256*255
 */
#ifndef __NO_SIN_TABLE16__
	const int16 Sin_Table16[257]  = {
		     0,    804,   1608,   2410,   3212,   4011,   4808,   5602,
		  6393,   7179,   7962,   8739,   9512,  10278,  11039,  11793,
		 12539,  13279,  14010,  14732,  15446,  16151,  16846,  17530,
		 18204,  18868,  19519,  20159,  20787,  21403,  22005,  22594,
		 23170,  23731,  24279,  24811,  25329,  25832,  26319,  26790,
		 27245,  27683,  28105,  28510,  28898,  29268,  29621,  29956,
		 30273,  30571,  30852,  31113,  31356,  31580,  31785,  31971,
		 32137,  32285,  32412,  32521,  32609,  32678,  32728,  32757,
		 32767,  32757,  32728,  32678,  32609,  32521,  32412,  32285,
		 32137,  31971,  31785,  31580,  31356,  31113,  30852,  30571,
		 30273,  29956,  29621,  29268,  28898,  28510,  28105,  27683,
		 27245,  26790,  26319,  25832,  25329,  24811,  24279,  23731,
		 23170,  22594,  22005,  21403,  20787,  20159,  19519,  18868,
		 18204,  17530,  16846,  16151,  15446,  14732,  14010,  13279,
		 12539,  11793,  11039,  10278,   9512,   8739,   7962,   7179,
		  6393,   5602,   4808,  4011,    3212,   2410,   1608,    804,
		     0,   -804,  -1608,  -2410,  -3212,  -4011,  -4808,  -5602,
		 -6393,  -7179,  -7962, -8739,   -9512, -10278, -11039, -11793,
		-12539, -13279, -14010, -14732, -15446, -16151, -16846, -17530,
		-18204, -18868, -19519, -20159, -20787, -21403, -22005, -22594,
		-23170, -23731, -24279, -24811, -25329, -25832, -26319, -26790,
		-27245, -27683, -28105, -28510, -28898, -29268, -29621, -29956,
		-30273, -30571, -30852, -31113, -31356, -31580, -31785, -31971,
		-32137, -32285, -32412, -32521, -32609, -32678, -32728, -32757,
		-32767, -32757, -32728, -32678, -32609, -32521, -32412, -32285,
		-32137, -31971, -31785, -31580, -31356, -31113, -30852, -30571,
		-30273, -29956, -29621, -29268, -28898, -28510, -28105, -27683,
		-27245, -26790, -26319, -25832, -25329, -24811, -24279, -23731,
		-23170, -22594, -22005, -21403, -20787, -20159, -19519, -18868,
		-18204, -17530, -16846, -16151, -15446, -14732, -14010, -13279,
		-12539, -11793, -11039, -10278, -9512,   -8739,  -7962,  -7179,
		 -6393,  -5602,  -4808,  -4011, -3212,   -2410,  -1608,   -804, 0}; 
#endif
	
/*
 * Sine data in 32 bit format.
 * -128..0..127 ~ -Pi..0..Pi/256*255
 */
#ifndef __NO_SIN_TABLE32__
	const int32 Sin_Table32[257]  = {
		          0,    52701887,   105372028,   157978697,   210490206,   262874923,   315101294,   367137860,
		  418953276,   470516330,   521795963,   572761285,   623381597,   673626408,   723465451,   772868706,
		  821806413,   870249095,   918167571,   965532978,  1012316784,  1058490807,  1104027236,  1148898640,
		 1193077990,  1236538675,  1279254515,  1321199780,  1362349204,  1402677999,  1442161874,  1480777044,
		 1518500249,  1555308767,  1591180425,  1626093615,  1660027308,  1692961061,  1724875039,  1755750016,
		 1785567395,  1814309215,  1841958164,  1868497585,  1893911493,  1918184580,  1941302224,  1963250500,
		 1984016188,  2003586778,  2021950483,  2039096240,  2055013722,  2069693341,  2083126253,  2095304369,
		 2106220351,  2115867625,  2124240379,  2131333571,  2137142926,  2141664947,  2144896909,  2146836865,
		 2147483647,  2146836865,  2144896909,  2141664947,  2137142926,  2131333571,  2124240379,  2115867625,
		 2106220351,  2095304369,  2083126253,  2069693341,  2055013722,  2039096240,  2021950483,  2003586778,
		 1984016188,  1963250500,  1941302224,  1918184580,  1893911493,  1868497585,  1841958164,  1814309215,
		 1785567395,  1755750016,  1724875039,  1692961061,  1660027308,  1626093615,  1591180425,  1555308767,
		 1518500249,  1480777044,  1442161874,  1402677999,  1362349204,  1321199780,  1279254515,  1236538675,
		 1193077990,  1148898640,  1104027236,  1058490807,  1012316784,   965532978,   918167571,   870249095,
		  821806413,  772868706,    723465451,   673626408,   623381597,   572761285,   521795963,   470516330,
		  418953276,  367137860,    315101294,   262874923,   210490206,   157978697,   105372028,    52701887,
		          0,   -52701887,  -105372028,  -157978697,  -210490206,  -262874923,  -315101294,  -367137860,
		 -418953276,  -470516330,  -521795963,  -572761285,  -623381597,  -673626408,  -723465451,  -772868706,
		 -821806413,  -870249095,  -918167571,  -965532978, -1012316784, -1058490807, -1104027236, -1148898640,
		-1193077990, -1236538675, -1279254515, -1321199780, -1362349204, -1402677999, -1442161874, -1480777044,
		-1518500249, -1555308767, -1591180425, -1626093615, -1660027308, -1692961061, -1724875039, -1755750016,
		-1785567395, -1814309215, -1841958164, -1868497585, -1893911493, -1918184580, -1941302224, -1963250500,
		-1984016188, -2003586778, -2021950483, -2039096240, -2055013722, -2069693341, -2083126253, -2095304369,
		-2106220351, -2115867625, -2124240379, -2131333571, -2137142926, -2141664947, -2144896909, -2146836865,
		-2147483647, -2146836865, -2144896909, -2141664947, -2137142926, -2131333571, -2124240379, -2115867625,
		-2106220351, -2095304369, -2083126253, -2069693341, -2055013722, -2039096240, -2021950483, -2003586778,
		-1984016188, -1963250500, -1941302224, -1918184580, -1893911493, -1868497585, -1841958164, -1814309215,
		-1785567395, -1755750016, -1724875039, -1692961061, -1660027308, -1626093615, -1591180425, -1555308767,
		-1518500249, -1480777044, -1442161874, -1402677999, -1362349204, -1321199780, -1279254515, -1236538675,
		-1193077990, -1148898640, -1104027236, -1058490807, -1012316784,  -965532978,  -918167571,  -870249095,
		 -821806413,  -772868706,  -723465451,  -673626408,  -623381597,  -572761285,  -521795963,  -470516330,
		 -418953276,  -367137860,  -315101294,  -262874923,  -210490206,  -157978697,  -105372028,   -52701887, 0};
#endif
