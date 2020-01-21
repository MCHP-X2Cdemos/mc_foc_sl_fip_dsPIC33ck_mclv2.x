/*
 * $LastChangedRevision: 1273 $
 * $LastChangedDate:: 2017-09-28 15:07:29 +0200#$
 *
 * Copyright (c) 2013, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
 * All rights reserved.
 */
#include "TableStruct.h"

/* init tablestruct */
void initTableStruct(void)
{
	uint8 i;

	TableStruct->TParamTable = (tParameterTable*)0;
	TableStruct->TFncTable = (tBlockFunctions*)0;
	TableStruct->TLimitSaveFncTable = (tLimitSaveFunctionTable*)0;

	TableStruct->DSPState = MONITOR_STATE;
	TableStruct->eventType = (uint16)0x0000;
	TableStruct->eventId = (uint32)0x00000000;

	TableStruct->protocolCount = (uint16)0;
	for (i = 0; i < MAX_PROTOCOLS; i++)
	{
		TableStruct->protocols[i] = (tProtocol*)0;
	}

	TableStruct->framePrgVersion = (uint16)0x0000;
	TableStruct->framePrgCompDateTime = (uint8*)0;

	TableStruct->piScope = (SCOPE_MAIN*)0;
	TableStruct->dynamicCodeData = (tDynamicCodeData*)0;

	TableStruct->inportParamTable = (tIoParamIdEntry*)0;
	TableStruct->outportParamTable = (tIoParamIdEntry*)0;
	TableStruct->maskParameterTable = (tMaskParameterEntry*)0;
}


/* add tProtocol to TableStruct */
void addTableStructProtocol(tProtocol* linkProtocol)
{
	if (TableStruct->protocolCount < MAX_PROTOCOLS)
	{
		TableStruct->protocols[TableStruct->protocolCount++] = linkProtocol;
	}
}
