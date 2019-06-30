/**
 * @file
 * @brief Generic block services.
 */
/*
 * $LastChangedRevision: 1280 $
 * $LastChangedDate:: 2017-10-12 22:49:55 +0200#$
 *
 * Copyright (c) 2013, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
 * All rights reserved.
 */
#ifndef BLOCKSERVICES_H
#define BLOCKSERVICES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"

/* public prototypes */
void addBlockServices(tProtocol* protocol);
void addExtendedBlockServices(tProtocol* protocol);
void putBlockData(tProtocol* protocol);
void getBlockData(tProtocol* protocol);
void getRAMBlock(tProtocol* protocol);
void putRAMBlock(tProtocol* protocol);

#ifdef __cplusplus
}
#endif

#endif
