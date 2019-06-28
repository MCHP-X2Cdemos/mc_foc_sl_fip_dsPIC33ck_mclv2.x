/**
 * @file
 * @brief Common services.
 */
/*
 * $LastChangedRevision: 1603 $
 * $LastChangedDate:: 2019-01-21 19:02:13 +0100#$
 *
 * This file is part of X2C. http://x2c.lcm.at/
 *
 * Copyright (c) 2013, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
 * All rights reserved.
 */
#ifndef SERVICES_H
#define SERVICES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"

#define	MAX_SERVICE_ID ((uint8)26)

/* service identifiers */
#define SV_ID_SVDEVICEINFO    ((uint8)0x00)
#define SV_ID_GETTARGETSTATE  ((uint8)0x01)
#define SV_ID_SETTARGETSTATE  ((uint8)0x02)
#define SV_ID_SVERASEFLASH    ((uint8)0x04)
#define SV_ID_GETBLOCKDATA   ((uint8)0x07)
#define SV_ID_PUTBLOCKDATA   ((uint8)0x08)
#define SV_ID_SVGETRAMBLOCK   ((uint8)0x09)
#define SV_ID_SVPUTRAMBLOCK   ((uint8)0x0A)
#define SV_ID_SVGETFLASHBLOCK ((uint8)0x0B)
#define SV_ID_SVPUTFLASHBLOCK ((uint8)0x0C)
#define SV_ID_SVLOADEE        ((uint8)0x0F)
#define SV_ID_SVSAVEEE        ((uint8)0x10)
#define SV_ID_SVLOADPARAM     ((uint8)0x11)
#define SV_ID_SVSAVEPARAM     ((uint8)0x12)
#define SV_ID_LOAD_IO_PARAM   ((uint8)0x13)
#define SV_ID_SAVEMASKPARAM   ((uint8)0x14)
#define SV_ID_LOADMASKPARAM   ((uint8)0x15)
#define SV_ID_SVREBOOT        ((uint8)0x19)
#define SV_ID_SVOSMCONTROL    ((uint8)0x1A)

/* data type bitwidths */
#define DATATYPE_8BIT  ((uint8)1)
#define DATATYPE_16BIT ((uint8)2)
#define DATATYPE_32BIT ((uint8)4)
#define DATATYPE_64BIT ((uint8)8)

typedef void (*tSERVICEFunction)(tProtocol* protocol);
typedef tSERVICEFunction tSERVICE_Table[MAX_SERVICE_ID+1];

/* error identifiers */
#define ERRORSuccess             		((uint8)0x00)
#define ERRORChksum              		((uint8)0x13)
#define ERRORFormat              		((uint8)0x14)
#define ERRORSizeTooLarge        		((uint8)0x15)
#define ERRORServiceNotAvail     		((uint8)0x21)
#define SvErrorInvalidDspState   		((uint8)0x22)
#define SvErrorInvalidDataType			((uint8)0x23)
#define ERRORFlashWrite          		((uint8)0x30)
#define ERRORFlashWriteProtect   		((uint8)0x31)
#define ERRORFlashErase          		((uint8)0x32)
#define ERRORFlashAddressAlign   		((uint8)0x33)
#define ERRORFlashData           		((uint8)0x34)
#define SvErrorInvalidParamId    		((uint8)0x40)
#define ERRORBlkID               		((uint8)0x41)
#define ERRORParLimit            		((uint8)0x42)
#define SvErrorParamTableNotInit 		((uint8)0x43)
#define SvErrorFncTableNotInit   		((uint8)0x44)
#define SvErrorInportParamTableNotInit	((uint8)0x45)
#define SvErrorOutportParamTableNotInit	((uint8)0x46)
#define SvErrorMaskParamTableNotInit    ((uint8)0x47)
#define SvErrorSaveMaskParam			((uint8)0x48)
#define SvErrorLoadMaskParam            ((uint8)0x49)
#define ERRORPowerIsOn           		((uint8)0x50)
#define SvErrorUnknown					((uint8)0xFF)

/* public prototypes */
void sendSvNotAvailable(tProtocol* protocol);
void sendError(tProtocol* protocol, uint8 ucErrorNr);
void initServiceTable(tProtocol* protocol);
void addCoreServices(tProtocol* protocol);

#ifdef __cplusplus
}
#endif

#endif
