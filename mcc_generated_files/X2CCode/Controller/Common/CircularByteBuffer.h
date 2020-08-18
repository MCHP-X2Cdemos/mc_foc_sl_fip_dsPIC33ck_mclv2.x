/**
 * @file
 * @brief Circular (ring) byte buffer implementation.
 */
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
 * $LastChangedDate:: 2020-03-10 16:35:19 +0100#$
 */
#ifndef CIRCULARBYTEBUFFER_H
#define CIRCULARBYTEBUFFER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "Target.h"

typedef struct tCircularByteBuffer tCircularByteBuffer;
struct tCircularByteBuffer {
	uint8* data;
	uint16 size;
	uint32 overflows;
	volatile uint16 start;
	volatile uint16 next;
	volatile uint16 used;
};

/* public prototypes */
/**
 * Initializes buffer.
 *
 * @param buffer Circular buffer object
 * @param data Data buffer
 * @param size Data buffer length
 */
void initBuffer(tCircularByteBuffer* buffer, uint8* data, uint16 size);
/**
 * Writes a byte into the buffer.
 *
 * @param buffer Circular buffer object
 * @param data Data to read from
 *
 * @return Error code (0 = success, !0 = failure)
 */
uint8 writeData(tCircularByteBuffer* buffer, uint8* data);
/**
 * Reads a byte from the buffer.
 *
 * @param buffer Circular buffer object
 * @param data Data to write to
 *
 * return Error code (0 = success, !0 = failure)
 */
uint8 readData(tCircularByteBuffer* buffer, uint8* data);
/**
 * Clears buffer.
 *
 * @param buffer Circular buffer object
 */
void clear(tCircularByteBuffer* buffer);
/**
 * Returns the currently used bytes.
 *
 * @param buffer Circular buffer object
 *
 * @return Used bytes
 */
uint16 getUsedBytes(tCircularByteBuffer* buffer);
/**
 * Returns the currently free bytes.
 *
 * @param buffer Circular buffer object
 *
 * @return Free bytes
 */
uint16 getFreeBytes(tCircularByteBuffer* buffer);

/**
 * Returns amount of linear used bytes.
 *
 * @param buffer Circular buffer object
 *
 * @return Amount of linear used bytes
 */
uint16 getLinearUsedSpace(tCircularByteBuffer* buffer);
/**
 * Returns amount of linear free bytes.
 *
 * @param buffer Circular buffer object
 *
 * @return Amount of linear free bytes
 */
uint16 getLinearFreeSpace(tCircularByteBuffer* buffer);
uint8 moveStart(tCircularByteBuffer* buffer, uint16 n);
uint8 moveNext(tCircularByteBuffer* buffer, uint16 n);
/**
 * Returns address of first entry.
 *
 * @param Circular buffer object
 *
 * @return Address of first entry
 */
uint8* getStartAddress(tCircularByteBuffer* buffer);
/**
 * Reads data from internal buffer and writes it into an user buffer.
 *
 * @param buffer Circular buffer object
 * @param data Buffer to copy data to
 * @param len Amount of bytes to copy
 *
 * @return Amount of successfully transferred bytes
 */
uint16 getData(tCircularByteBuffer* buffer, uint8* data, uint16 len);

/**
 * Reads data from user buffer and writes it into internal buffer.
 *
 * @param buffer Circular buffer object
 * @param data Buffer to copy data from
 * @param len Amount of bytes to copy
 *
 * @return Amount of successfully transferred bytes
 */
uint16 putData(tCircularByteBuffer* buffer, uint8* data, uint16 len);

#ifdef __cplusplus
}
#endif

#endif
