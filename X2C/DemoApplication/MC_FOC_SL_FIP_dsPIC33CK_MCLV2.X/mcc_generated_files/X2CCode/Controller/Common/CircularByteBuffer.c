/*
 * $LastChangedRevision: 873 $
 * $LastChangedDate:: 2016-02-18 12:04:02 +0100#$
 *
 * Copyright (c) 2013, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
 * All rights reserved.
 */
#include <string.h>
#include "CircularByteBuffer.h"

void initBuffer(tCircularByteBuffer* buffer, uint8* data, uint16 size)
{
	buffer->data = data;
	buffer->size = size;

	buffer->start = (uint16)0;
	buffer->next = (uint16)0;
	buffer->used = (uint16)0;

	buffer->overflows = (uint32)0;
}


uint16 getLinearUsedSpace(tCircularByteBuffer* buffer)
{
	uint16 linearByteCount = (uint16)0;

	if (buffer->used > 0)
	{
		if (buffer->next > buffer->start)
		{
			linearByteCount = buffer->used;
		}
		else
		{
			linearByteCount = buffer->size - buffer->start;
		}
	}

	return (linearByteCount);
}


uint16 getLinearFreeSpace(tCircularByteBuffer* buffer)
{
	uint16 linearByteCount;

	if (buffer->used > 0)
	{
		if (buffer->next > buffer->start)
		{
			linearByteCount = buffer->size - buffer->next;
		}
		else
		{
			linearByteCount = buffer->start - buffer->next;
		}
	}
    else
    {
        linearByteCount = buffer->size - buffer->next;
    }
	return (linearByteCount);
}

/**
 * Moves start pointer by <n> bytes.
 * (same effect as reading <n> bytes)
 */
uint8 moveStart(tCircularByteBuffer* buffer, uint16 n)
{
	uint8 error = 0;

	if (n > buffer->used)
	{
		n = buffer->used;
		error = 1;
	}
	buffer->start = (buffer->start + n) % buffer->size;
	buffer->used -= n;

	return (error);
}

/**
 * Moves next pointer by <n> bytes.
 * (same effect as writing <n> bytes)
 */
uint8 moveNext(tCircularByteBuffer* buffer, uint16 n)
{
	uint8 error = 0;
	uint16 freeBytes = getFreeBytes(buffer);

	if (n > freeBytes)
	{
		n = freeBytes;
		error = 1;
	}
	buffer->next = (buffer->next + n) % buffer->size;
	buffer->used += n;

	return (error);
}


uint8* getStartAddress(tCircularByteBuffer* buffer)
{
	return (&buffer->data[buffer->start]);
}


uint8 writeData(tCircularByteBuffer* buffer, uint8* data)
{
	uint8 error;

	if (buffer->used >= buffer->size)
	{
		buffer->overflows++;
		/* buffer is full */
		error = (uint8)1;
	}
	else
	{
		buffer->data[buffer->next] = *data;
		buffer->next = (buffer->next + 1) % buffer->size;
		buffer->used++;
		error = (uint8)0;
	}
	return (error);
}

uint8 readData(tCircularByteBuffer* buffer, uint8* data)
{
	uint8 error;

	if (buffer->used == (uint16)0)
	{
		/* buffer is empty */
		error = (uint8)1;
	}
	else
	{
		*data = buffer->data[buffer->start];
		buffer->used--;
		buffer->start = (buffer->start + 1) % buffer->size;
		error = (uint8)0;
	}
	return (error);
}


uint16 getData(tCircularByteBuffer* buffer, uint8* data, uint16 len)
{
	uint16 remainingBytes;
	uint16 totBytesRead;
    uint16 dataOffset = (uint16)0;

	if (len > buffer->used)
	{
		totBytesRead = buffer->used;
	}
	else
	{
		totBytesRead = len;
	}

	remainingBytes = totBytesRead;
	while (remainingBytes > 0)
	{
		uint16 linBytes = getLinearUsedSpace(buffer);
		uint8* startPtr = getStartAddress(buffer);
		if (linBytes > remainingBytes)
		{
			linBytes = remainingBytes;
		}
        
		memcpy(&data[dataOffset], startPtr, linBytes);
		moveStart(buffer, linBytes);
		remainingBytes -= linBytes;
        dataOffset += linBytes;
	}
	return (totBytesRead);
}


uint16 putData(tCircularByteBuffer* buffer, uint8* data, uint16 len)
{
	uint16 totBytesWritten, remainingBytes;
	uint16 free = getFreeBytes(buffer);
    uint16 dataOffset = (uint16)0;

	if (len > free)
	{
		totBytesWritten = free;
	} else {
		totBytesWritten = len;
	}

	remainingBytes = totBytesWritten;
	while (remainingBytes > 0)
	{
		uint16 linBytes = getLinearFreeSpace(buffer);
		uint8* nextPtr = &buffer->data[buffer->next];
		if (linBytes > remainingBytes)
		{
			linBytes = remainingBytes;
		}
        
		memcpy(nextPtr, &data[dataOffset], linBytes);
		moveNext(buffer, linBytes);
		remainingBytes -= linBytes;
        dataOffset += linBytes;
	}
	return (totBytesWritten);
}



void clear(tCircularByteBuffer* buffer)
{
	buffer->start = (uint16)0;
	buffer->next = (uint16)0;
	buffer->used = (uint16)0;
}

uint16 getUsedBytes(tCircularByteBuffer* buffer)
{
	return (buffer->used);
}

uint16 getFreeBytes(tCircularByteBuffer* buffer)
{
	return (buffer->size - buffer->used);
}
