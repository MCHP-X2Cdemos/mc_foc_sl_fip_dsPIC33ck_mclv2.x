/**
 * @file
 * @brief Circular (ring) byte buffer implementation.
 */
/*
 * $LastChangedRevision: 873 $
 * $LastChangedDate:: 2016-02-18 12:04:02 +0100#$
 *
 * Copyright (c) 2013, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
 * All rights reserved.
 */
#ifndef __CIRCULARBYTEBUFFER_H__
#define __CIRCULARBYTEBUFFER_H__

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

#endif
