/*
 * $LastChangedRevision: 1340 $
 * $LastChangedDate:: 2017-12-21 23:05:55 +0100#$
 *
 * Copyright (c) 2013, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
 * All rights reserved.
 */
#include "TableStruct.h"
#include "Services.h"
#include "CRC8CCITT.h"
#include "LNet.h"

#define HW_INTERFACE (protocol->hwInterface)

/* private prototypes */
static void enableSend(tLNet* protocol);
static void enableReceive(tLNet* protocol);
static void communicate(tLNet* protocol);
static void handleOnlineScopeMode(tLNet* protocol);
static void checkFill(tLNet* protocol, uint8 data, tLNetFrameState* stateVar, tLNetFrameState state);
static void updateChecksum(tLNet* protocol, uint8 data);
static void initChecksum(tLNet* protocol);
static void sendProtocolError(tLNet* protocol, uint8 serviceId, uint8 errorId);

static void setupRxTimeout(tLNet* protocol, uint16 timeout);
static void updateRxTimeout(tLNet* protocol, uint16 time);
static void resetRxTimeout(tLNet* protocol);

/* enable send procedure / disable receive procedure */
static void enableSend(tLNet* protocol)
{
	protocol->commState = SEND_ALLOWED;
	protocol->txState = LNET_STATE_SYN;
}

/* enable receive procedure / disable send procedure */
static void enableReceive(tLNet* protocol)
{
	protocol->commState = RECEIVE_ALLOWED;
	protocol->rxState = LNET_STATE_SYN;
}

static void communicate(tLNet* protocol)
{
	/* service table pointer */
	tSERVICEFunction* svTable;
	/* current received message byte */
	uint8 msg;

	/* send procedure */
	while ((protocol->commState == SEND_ALLOWED) && protocol->hwInterface->isSendReady(HW_INTERFACE))
	{
		static uint8 tmp;

		switch (protocol->txState)
		{
			case LNET_STATE_SYN:
				initChecksum(protocol);
				updateChecksum(protocol, LNET_STD_SYN);
				protocol->frameBufferPtr = 0;
				protocol->hwInterface->send(HW_INTERFACE, LNET_STD_SYN);
				protocol->txState = LNET_STATE_NODE;
				break;

			case LNET_STATE_NODE:
				updateChecksum(protocol, protocol->node);
				protocol->hwInterface->send(HW_INTERFACE, protocol->node);
				checkFill(protocol, protocol->node, &protocol->txState, LNET_STATE_SIZE_LSB);
				break;

			case LNET_STATE_SIZE_LSB:
				tmp = (uint8)(protocol->frameSize & 0xFF);
				updateChecksum(protocol, tmp);
				protocol->hwInterface->send(HW_INTERFACE, tmp);
				checkFill(protocol, tmp, &protocol->txState, LNET_STATE_SIZE_MSB);
				break;

			case LNET_STATE_SIZE_MSB:
				tmp = (uint8)(protocol->frameSize >> 8);
				updateChecksum(protocol, tmp);
				protocol->hwInterface->send(HW_INTERFACE, tmp);
				checkFill(protocol, tmp, &protocol->txState, LNET_STATE_DATA);
				break;

			case LNET_STATE_DATA:
				protocol->frameData[protocol->frameBufferPtr] &= 0xFF;
				updateChecksum(protocol, protocol->frameData[protocol->frameBufferPtr]);
				protocol->hwInterface->send(HW_INTERFACE, protocol->frameData[protocol->frameBufferPtr]);

				if ((protocol->frameBufferPtr + 1) >= protocol->frameSize)
				{
					checkFill(protocol, protocol->frameData[protocol->frameBufferPtr], \
						&protocol->txState, LNET_STATE_CRC);
				}
				else
				{
					checkFill(protocol, protocol->frameData[protocol->frameBufferPtr], \
						&protocol->txState, LNET_STATE_DATA);
				}
				protocol->frameBufferPtr++;
				break;

			case LNET_STATE_FILL:
				protocol->hwInterface->send(HW_INTERFACE, LNET_FILL);
				protocol->txState = protocol->nextState;
				break;

			case LNET_STATE_CRC:
				protocol->crc &= 0xFF;
				if ((protocol->crc == LNET_STD_SYN) || (protocol->crc == LNET_OSM_SYN))
				{
					protocol->crc = (~protocol->crc) & 0xFF;
				}
				protocol->hwInterface->send(HW_INTERFACE, protocol->crc);

				/* frame complete -> flush tx buffer */
				protocol->hwInterface->flush(HW_INTERFACE);

				enableReceive(protocol);
				break;

			default:
				enableReceive(protocol);
				break;
		}	/* switch end */
	}		/* tx while end */

	/* receive procedure */
	while ((protocol->commState == RECEIVE_ALLOWED) && protocol->hwInterface->isReceiveDataAvailable(HW_INTERFACE))
	{
		static uint16 tmpSize;

		/* reset timeout */
		resetRxTimeout(protocol);

		/* get 1 byte from rx buffer */
		msg = protocol->hwInterface->receive(HW_INTERFACE);
		
		switch (protocol->rxState)
		{
			case LNET_STATE_SYN:
				if (msg == LNET_STD_SYN)
				{
					initChecksum(protocol);
					updateChecksum(protocol, LNET_STD_SYN);
					protocol->rxState = LNET_STATE_NODE;
				}
				break;

			case LNET_STATE_NODE:
				if ((msg != 0) && (msg == protocol->node))
				{
					updateChecksum(protocol, msg);
					checkFill(protocol, msg, &protocol->rxState, LNET_STATE_SIZE_LSB);
				}
				else
				{
					protocol->rxState = LNET_STATE_SYN;
				}
				break;

			case LNET_STATE_SIZE_LSB:
				tmpSize = (uint16)msg;
				updateChecksum(protocol, msg);
				checkFill(protocol, msg, &protocol->rxState, LNET_STATE_SIZE_MSB);
				break;

			case LNET_STATE_SIZE_MSB:
				tmpSize += ((uint16)msg << 8);
				if (tmpSize > protocol->maxCommSize)
				{
					sendProtocolError(protocol, SV_ID_SVDEVICEINFO, ERRORSizeTooLarge);
				}
				else
				{
					protocol->frameSize = tmpSize;
					updateChecksum(protocol, msg);
					protocol->frameBufferPtr = 0;
					checkFill(protocol, msg, &protocol->rxState, LNET_STATE_DATA);
				}
				break;

			case LNET_STATE_DATA:
				updateChecksum(protocol, msg);
				protocol->frameData[protocol->frameBufferPtr] = msg;
				protocol->frameBufferPtr++;
				
				if (protocol->frameBufferPtr >= protocol->frameSize)
				{
					checkFill(protocol, msg, &protocol->rxState, LNET_STATE_CRC);
				}
				else
				{
					checkFill(protocol, msg, &protocol->rxState, LNET_STATE_DATA);
				}	
				break;

			case LNET_STATE_FILL:
				if (msg == LNET_FILL)
				{
					protocol->rxState = protocol->nextState;
				}
				else
				{
					/*
					 * New frame within current frame detected.
					 * Discard current frame and begin new frame.
					 */
					if ((protocol->lastSyn == LNET_STD_SYN) && (msg == protocol->node))
					{
						initChecksum(protocol);
						updateChecksum(protocol, LNET_STD_SYN);
						updateChecksum(protocol, msg);
						protocol->rxState = LNET_STATE_SIZE_LSB;
					}
					else
					{
						protocol->rxState = LNET_STATE_SYN;
					}
				}	
				break;

			case LNET_STATE_CRC:
				protocol->crc &= 0xFF;
				if ((protocol->crc == LNET_STD_SYN) || (protocol->crc == LNET_OSM_SYN))
				{
					protocol->crc = (~protocol->crc) & 0xFF;
				}
				if (protocol->crc == msg)
				{
					if (protocol->frameData[0] <= MAX_SERVICE_ID)
					{
						/* elements are function pointers */
						svTable = (tSERVICEFunction*)protocol->serviceTable;
						svTable[protocol->frameData[0]]((tProtocol*)protocol);
					}
					else
					{
						sendError((tProtocol*)protocol, ERRORServiceNotAvail);
					}
				}
				else
				{
					sendError((tProtocol*)protocol, ERRORChksum);
				}
				break;

			default:
				protocol->rxState = LNET_STATE_SYN;
				break;
		}	/* switch end */
	}		/* rx while end */

	/* timeout -> reset receive state machine and timeout counter */
	if (protocol->rxTimeoutCnt == 0)
	{
		protocol->rxState = LNET_STATE_SYN;
		resetRxTimeout(protocol);
	}

	handleOnlineScopeMode(protocol);
}


static void checkFill(tLNet* protocol, uint8 data, tLNetFrameState* stateVar, tLNetFrameState state)
{
	if ((data == LNET_STD_SYN) || (data == LNET_OSM_SYN))
	{
		protocol->lastSyn = data;
		protocol->nextState = state;
		*stateVar = LNET_STATE_FILL;
	}
	else
	{
		*stateVar = state;
	}
}


/* online scope mode (osm) */
static void handleOnlineScopeMode(tLNet* protocol)
{
	const uint8 overheadSize = 5;
	static uint32 txBufFull = (uint32)0;
	uint16 i, j;
	uint8 checksum;

	/* if scope pointer is not NULL, scope state is 5 (online running) and */
	/* prescaler counter is 0 -> send osm frame */
	if ((TableStruct->piScope != 0) && (TableStruct->piScope->state == SCOPE_SAMPLE_ONLINE))
	{
		/* call TxFifoFree function (pointer to function located in protocol, */
		/* functions itself is located in the communication interface file */
		/* (e.g. SCI) */
		/* tx fifo must have (frame data + overhead) free bytes */
		if ((protocol->hwInterface->getTxFifoFree(HW_INTERFACE) >= (TableStruct->piScope->txFrameSize + overheadSize)) && \
		    (TableStruct->piScope->stfCnt >= TableStruct->piScope->stf))
		{
            TableStruct->piScope->stfCnt = 0;
			/* send osm frame */
			protocol->hwInterface->send(HW_INTERFACE, LNET_OSM_SYN);
			protocol->hwInterface->send(HW_INTERFACE, protocol->node);
			protocol->hwInterface->send(HW_INTERFACE, TableStruct->piScope->txFrameSize);
			/* size high byte = 0 due to tx fifo free 8-bit limitation */
			protocol->hwInterface->send(HW_INTERFACE, 0);

			protocol->hwInterface->send(HW_INTERFACE, LOW(TableStruct->piScope->timestamp));
			protocol->hwInterface->send(HW_INTERFACE, HIGH(TableStruct->piScope->timestamp));

			checksum = crc8ccitt_init();
			checksum = crc8ccitt_addValue(checksum, LNET_OSM_SYN);
			checksum = crc8ccitt_addValue(checksum, protocol->node);
			checksum = crc8ccitt_addValue(checksum, TableStruct->piScope->txFrameSize);
			/* size high byte */
			checksum = crc8ccitt_addValue(checksum, 0);
			checksum = crc8ccitt_addValue(checksum, LOW(TableStruct->piScope->timestamp));
			checksum = crc8ccitt_addValue(checksum, HIGH(TableStruct->piScope->timestamp));

            i = 0;
            do
            {
                j = 0;
                do
                {
#if defined(__DATA_WIDTH_16BIT__)
                    uint16 tmp;
                    tmp = *((uint16*)TableStruct->piScope->channelAddr[i] + j);
                    protocol->hwInterface->send(HW_INTERFACE, (uint8)tmp);
                    protocol->hwInterface->send(HW_INTERFACE, (uint8)(tmp >> 8));
                    checksum = crc8ccitt_addValue(checksum, (uint8)(tmp & 0xFF));
                    checksum = crc8ccitt_addValue(checksum, tmp >> 8);
#elif defined(__DATA_WIDTH_8BIT__)
                    uint8 tmp;
                    tmp = *((uint8*) TableStruct->piScope->channelAddr[i] + j);
                    protocol->hwInterface->send(HW_INTERFACE, tmp);
                    checksum = crc8ccitt_addValue(checksum, tmp);
#else
#error DATA WIDTH NOT DEFINED
#endif
                    j++;
                }
                while (j < TableStruct->piScope->dataSize[i]);
                i++;
            }
            while(i < TableStruct->piScope->noChannels);

            checksum &= 0xFF;
			if (checksum == LNET_OSM_SYN)
			{
				checksum = ~checksum;
			}
			protocol->hwInterface->send(HW_INTERFACE, checksum);
		}
		else
		{
			/* debug: counter of failed transfers due to full tx fifo */
			txBufFull++;
		}
	}
}


/**
 * Updates checksum in LNet object.
 */
static void updateChecksum(tLNet* protocol, uint8 data)
{
	protocol->crc = crc8ccitt_addValue(protocol->crc, data);
}

/**
 * Initializes checksum in LNet object.
 */
static void initChecksum(tLNet* protocol)
{
	protocol->crc = crc8ccitt_init();
}

static void sendProtocolError(tLNet* protocol, uint8 serviceId, uint8 errorId)
{
	protocol->frameData[0] = serviceId;
	sendError((tProtocol*)protocol, errorId);
}

/*
 * Initializes LNet by using an external buffer.
 * Hence this kind of LNet initialization doesn't use malloc
 * and therefore needs no heap memory.
 */
void initLNet(tLNet* protocol, uint8* dataBuffer, uint16 dataBufferSize, uint8 node)
{
	protocol->frameData = dataBuffer;
	protocol->maxCommSize = dataBufferSize;
	protocol->node = node;

	/* timeout to maximum value */
	protocol->rxTimeout = UINT16_MAX;
	protocol->rxTimeoutCnt = protocol->rxTimeout;

	/* hook functions */
	protocol->communicate = (void (*)(tProtocol*))communicate;
	protocol->enableSend = (void (*)(tProtocol*))enableSend;

	protocol->setupRxTimeout = setupRxTimeout;
	protocol->updateRxTimeout = updateRxTimeout;
	protocol->resetRxTimeout = resetRxTimeout;

	/* set to receive state at begin */
	enableReceive(protocol);
}

static void setupRxTimeout(tLNet* protocol, uint16 timeout)
{
	protocol->rxTimeout = timeout;
}

static void updateRxTimeout(tLNet* protocol, uint16 time)
{
	if ((protocol->commState == RECEIVE_ALLOWED) && (protocol->rxState != LNET_STATE_SYN)) {
		if (time > protocol->rxTimeoutCnt)
		{
			protocol->rxTimeoutCnt = 0;
		}
		else
		{
			protocol->rxTimeoutCnt -= time;
		}
	}
}

static void resetRxTimeout(tLNet* protocol)
{
	protocol->rxTimeoutCnt = protocol->rxTimeout;
}
