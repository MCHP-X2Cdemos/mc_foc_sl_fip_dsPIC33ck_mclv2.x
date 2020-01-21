/**
 * @file
 * @brief Table structure type definition and -functions.
 */
/*
 * $LastChangedRevision: 1273 $
 * $LastChangedDate:: 2017-09-28 15:07:29 +0200#$
 *
 * Copyright (c) 2013, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
 * All rights reserved.
 */
#ifndef TABLESTRUCT_H
#define TABLESTRUCT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "CommonFcts.h"

#if defined(__COMPILER_CODEWARRIOR_ECLIPSE__)
#pragma push
#pragma section sdata_type ".ptrTableStruct" ".ptrTableStruct"
extern volatile tTableStruct *TableStruct;
#pragma pop
#else
extern volatile tTableStruct* TableStruct;
#endif

/* public prototypes */
void initTableStruct(void);
void addTableStructProtocol(tProtocol* pProtocol);

#ifdef __cplusplus
}
#endif

#endif
