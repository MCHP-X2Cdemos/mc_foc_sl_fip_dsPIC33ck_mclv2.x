/**
 * @file
 * @brief LNet protocol
 */
/*
 * $LastChangedRevision: 1273 $
 * $LastChangedDate:: 2017-09-28 15:07:29 +0200#$
 *
 * Copyright (c) 2013, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
 * All rights reserved.
 */
#ifndef LNET_H
#define LNET_H

#include "CommonFcts.h"

#define LNET_STD_SYN ((uint8)0x55)
#define LNET_OSM_SYN ((uint8)0x02)
/* can't be changed -> length dependency */
#define LNET_FILL    ((uint8)0x00)

/* state machine states */
typedef enum {LNET_STATE_SYN, LNET_STATE_NODE, LNET_STATE_SIZE_LSB, LNET_STATE_SIZE_MSB, \
			  LNET_STATE_DATA, LNET_STATE_FILL, LNET_STATE_CRC} tLNetFrameState;

typedef struct tLNet tLNet;
struct tLNet {
	void (*communicate)(tProtocol*);
	void (*enableSend)(tProtocol*);
	
	uint16 frameSize;
	uint16 maxCommSize;
	uint8* frameData;
	
	void* serviceTable;

	tInterface* hwInterface;

	void (*setupRxTimeout)(tLNet*, uint16);
	void (*updateRxTimeout)(tLNet*, uint16);
	void (*resetRxTimeout)(tLNet*);

	/* receive timeout */
	uint16 rxTimeout;
	/* receive timeout counter (from .rcvTimeout towards zero) */
	uint16 rxTimeoutCnt;

	/* slave node id */
	uint8 node;
	
	/* receive- & send state */
	tLNetFrameState rxState;
	tLNetFrameState txState;
	/* communication state (rx or tx) */
	tCommState commState;
	uint8 crc;
	/* framebuffer ptr to actual frame byte */
	uint16 frameBufferPtr;

	/* next state being cached in case of fill byte */
	tLNetFrameState nextState;
	/* last SYN type cached in case of fill byte */
	uint8 lastSyn;
};

/* public prototypes */
void initLNet(tLNet* protocol, uint8* dataBuffer, uint16 dataBufferSize, uint8 node);

#endif
