/*
 * $LastChangedRevision: 1603 $
 * $LastChangedDate:: 2019-01-21 19:02:13 +0100#$
 *
 * This file is part of X2C. http://x2c.lcm.at/
 *
 * Copyright (c) 2013, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
 * All rights reserved.
 */
#include "CommonFcts.h"

/** Pseudo Initialization */
void Common_Init(void* common)
{
	;
}

/** Pseudo Update */
void Common_Update(void* common)
{
	;
}

/** Pseudo Load block data */
uint8 Common_Load(const void* common, uint8 data[], uint16* dataLength, uint16 maxSize)
{
	*dataLength = (uint16)0;
    return ((uint8)0);
}

/** Pseudo Save block data */
uint8 Common_Save(void* common, const uint8 data[], uint16 dataLength)
{
	uint8 retVal;
    if (dataLength > 0)
    {
    	retVal = 1;
    }
    else
    {
    	retVal = 0;
    }
    return (retVal);
}

/** Pseudo Get Address */
void* Common_GetAddress(const void* common, uint16 elementId)
{
	return ((void*)0);
}

/** Pseudo Init Mask Parameter */
uint8 Common_InitMP(void *block, const void *maskParam)
{
	return ((uint8)0);
}

/** Pseudo Save Mask Parameter */
uint8 Common_SaveMP(void* block, void* maskParam, const uint8 data[], uint16 dataLength)
{
	return ((uint8)0);
}

/** Pseudo Load Mask Parameter */
uint8 Common_LoadMP(const void* block, uint8 data[], uint16* dataLength, uint16 maxSize)
{
	*dataLength = (uint16)0;
	return ((uint8)0);
}

/* abs(x) functions */

/** @brief Calculation of 8-bit absolute value.
 *
 * out = |in|
 * 
 * @param x 8-bit fixed point input value.
 * @return Absolute value of input.
 */
int8 getAbsValI8(int8 x){
	if (x == ((int8)0x80)){
		x = (int8)0x7F;
	}else if (x < 0){
		x = -(x);
	}
	return (x);
}

/** @brief Calculation of 16-bit absolute value.
 *
 * out = |in|
 * 
 * @param x 16-bit fixed point input value.
 * @return Absolute value of input.
 */
int16 getAbsValI16(int16 x){
	if (x == ((int16)0x8000)){
		x = (int16)0x7FFF;
	}else if (x < 0){
		x = -(x);
	}
	return (x);
}

/** @brief Calculation of 32-bit absolute value.
 *
 * out = |in|
 * 
 * @param x 32-bit fixed point input value.
 * @return Absolute value of input.
 */
int32 getAbsValI32(int32 x){
	if (x == ((int32)0x80000000)){
		x = (int32)0x7FFFFFFF;
	}else if (x < 0){
		x = -(x);
	}
	return (x);
}

/** @brief Calculation of 64-bit absolute value.
 *
 * out = |in|
 * 
 * @param x 64-bit fixed point input value.
 * @return Absolute value of input.
 */
int64 getAbsValI64(int64 x){
	if (x == ((int64)0x8000000000000000)){
		x = (int64)0x7FFFFFFFFFFFFFFF;
	}else if (x < 0){
		x = -(x);
	}
	return (x);
}

/** @brief Calculation of single precision absolute value.
 *
 * out = |in|
 * 
 * @param x 32-bit floating point input value.
 * @return Absolute value of input.
 */
float32 getAbsValR32(float32 x){
	if (x < 0){
		x = -(x);
	}
	return (x);
}

/** @brief Calculation of double precision absolute value.
 *
 * out = |in|
 * 
 * @param x 64-bit floating point input value.
 * @return Absolute value of input.
 */
float64 getAbsValR64(float64 x){
	if (x < 0){
		x = -(x);
	}
	return (x);
}

/**
 * @brief Returns IO-Block-Parameter identifier table index for a given Parameter identifier.
 *
 * @param[in] ioParamTbl IO-Block-Parameter identifier table
 * @param[in] paramId Parameter identifier
 * @param[out] index Index
 *
 * @return Error code
 */
uint8 getIoParamIndex(const tIoParamIdEntry ioParamTbl[], uint16 paramId, uint16* index)
{
	uint16 i;
	uint8 error;

	if (ioParamTbl == 0)
	{
		*index = 0;
		error = ERROR_TABLE_NOT_INIT;
	}
	else
	{
		i = 0;
		while ((paramId != ioParamTbl[i].id) && (ioParamTbl[i].id != 0))
		{
			i++;
		}
		if (ioParamTbl[i].id == 0)
		{
			*index = 0;
			error = ERROR_INVALID_ID;
		}
		else
		{
			*index = i;
			error = ERROR_SUCCESS;
		}
	}
	return (error);
}

/**
 * @brief Returns Block-Parameter identifier table index for a given Parameter identifier.
 *
 * @param[in] paramTable Block-Parameter identifier table
 * @param[in] paramId Parameter Identifier
 * @param[out] index Index
 *
 * @return Error code
 */
uint8 getBlockParamIndex(const tParameterTable* paramTable, uint16 paramId, uint16* index)
{
	uint16 i;
	uint8 error;

	/* send parameter ID error if no parameter table has been initialized */
	if (paramTable == 0)
	{
		*index = 0;
		error = ERROR_TABLE_NOT_INIT;
	}
	else
	{
		i = 0;
		while((paramId != paramTable[i].uiParID) && (paramTable[i].uiParID != 0))
		{
			i++;
		}
		/* check if parameter is located in parameter table */
		if (paramTable[i].uiParID == 0)
		{
			*index = 0;
			error = ERROR_INVALID_ID;
		}
		else
		{
			*index = i;
			error = ERROR_SUCCESS;
		}
	}
	return (error);
}

/**
 * @brief Returns Mask Parameter identifier table index for a given Parameter identifier.
 *
 * @param[in] mpTable Mask Parameter identifier table
 * @param[in] paramId Parameter Identifier
 * @param[out] index Index
 *
 * @return Error code
 */
uint8 getMaskParamIndex(const tMaskParameterEntry* mpTable, uint16 paramId, uint16* index)
{
	uint16 i;
	uint8 error;

	/* send parameter ID error if no parameter table has been initialized */
	if (mpTable == 0)
	{
		*index = 0;
		error = ERROR_TABLE_NOT_INIT;
	}
	else
	{
		i = 0;
		while((paramId != mpTable[i].id) && (mpTable[i].id != 0))
		{
			i++;
		}
		/* check if parameter is located in parameter table */
		if (mpTable[i].id == 0)
		{
			*index = 0;
			error = ERROR_INVALID_ID;
		}
		else
		{
			*index = i;
			error = ERROR_SUCCESS;
		}
	}
	return (error);
}

/**
 * @brief Returns Block function table index for a given Block identifier.
 *
 * @param[in] fncTable Block function table
 * @param[in] blockId Block identifier
 * @param[out] index Index
 *
 * @return Error code
 */
uint8 getBlockFunctionIndex(const tBlockFunctions* fncTable, uint16 blockId, uint16* index)
{
	uint16 i;
	uint8 error;

	if (fncTable == 0)
	{
		*index = 0;
		error = ERROR_TABLE_NOT_INIT;
	}
	else
	{
		i = 0;
		while ((blockId != fncTable[i].iBlockID) && (fncTable[i].iBlockID != 0))
		{
			i++;
		}

		if (fncTable[i].iBlockID == 0)
		{
			*index = 0;
			error = ERROR_INVALID_ID;
		}
		else
		{
			*index = i;
			error = ERROR_SUCCESS;
		}
	}
	return (error);
}


/**
 * @brief Returns Q-format for given decimal value.
 *
 * @param   decValue Decimal value (-2147483647 ... +2147483647)
 * @param   maxBits Maximum bit width (8 ... 32)
 *
 * @return  Q-Format (0 ... 31)
 */
uint8 getQFormat(float_CoT decValue, uint8 maxBits)
{
    uint8 qFormat;
    uint32 maxValue;
    float_CoT realValue;

    /* check and limit input arguments if necessary */
    if (maxBits > 32)
    {
        maxBits = 32;
    }
    else if (maxBits < 8)
    {
        maxBits = 8;
    }
    LIMIT(decValue, (float_CoT)INT32_MAX);

    /* take absolute value of decValue to simplify calculation */
    if (decValue < 0)
    {
        decValue = -decValue;
    }

    /* calculate qFormat */
    qFormat = maxBits;
    maxValue = (((uint32)1) << (maxBits-1)) - 1;
    do {
        qFormat--;

        realValue = decValue * (float_CoT)(((uint32)1) << qFormat);

    } while ((qFormat > 0) && (realValue > (float_CoT)maxValue));

    return (qFormat);
}


/**
 * @brief Returns integer value in Qx.8-format for given decimal value.
 *
 * @param   decValue Decimal value (-1.0 ... +1.0)
 * @param   qFormat Q-format (0 ... 7)
 *
 * @return  Q-format integer value (-127 ... +127)
 */
int8 getQx8Value(float_CoT decValue, uint8 qFormat)
{
    int16 intValue;

    intValue = decValue * (float_CoT)(((uint8)1) << qFormat);
    LIMIT(intValue, INT8_MAX);

    return (int8)intValue;
}

/**
 * @brief Returns integer value in Qx.16-format for given decimal value.
 *
 * @param   decValue Decimal value (-1.0 ... +1.0)
 * @param   qFormat Q-format (0 ... 15)
 *
 * @return  Q-format integer value (-32767 ... +32767)
 */
int16 getQx16Value(float_CoT decValue, uint8 qFormat)
{
    int32 intValue;

    intValue = decValue * (float_CoT)(((uint16)1) << qFormat);
    LIMIT(intValue, INT16_MAX);

    return (int16)intValue;
}

/**
 * @brief Returns integer value in Qx.32-format for given decimal value.
 *
 * @param   decValue Decimal value (-1.0 ... +1.0)
 * @param   qFormat Q-format (0 ... 31)
 *
 * @return  Q-format integer value (-2147483647 ... +2147483647)
 */
int32 getQx32Value(float_CoT decValue, uint8 qFormat)
{
    int64 intValue;

    intValue = decValue * (float_CoT)(((uint32)1) << qFormat);
    LIMIT(intValue, INT32_MAX);

    return (int32)intValue;
}

/**
 * @brief Returns asymmetric integer value (for angular signals) in Qx.8-format for given decimal value.
 *
 * @param   decValue Decimal value (-1.0 ... +1.0)
 * @param   qFormat Q-format (0 ... 7)
 *
 * @return  Q-format integer value (-128 ... +127)
 */
int8 getAQx8Value(float_CoT decValue, uint8 qFormat)
{
    int16 intValue;

    intValue = decValue * (float_CoT)(((uint8)1) << qFormat);
    if (intValue > INT8_MAX)
    {
        intValue = INT8_MAX;
    }
    else if (intValue < INT8_MIN)
    {
        intValue = INT8_MIN;
    }

    return (int8)intValue;
}

/**
 * @brief Returns asymmetric integer value (for angular signals) in Qx.16-format for given decimal value.
 *
 * @param   decValue Decimal value (-1.0 ... +1.0)
 * @param   qFormat Q-format (0 ... 15)
 *
 * @return  Q-format integer value (-32768 ... +32767)
 */
int16 getAQx16Value(float_CoT decValue, uint8 qFormat)
{
    int32 intValue;

    intValue = decValue * (float_CoT)(((uint16)1) << qFormat);
    if (intValue > INT16_MAX)
    {
        intValue = INT16_MAX;
    }
    else if (intValue < INT16_MIN)
    {
        intValue = INT16_MIN;
    }

    return (int16)intValue;
}

/**
 * @brief Returns asymmetric integer value (for angular signals) in Qx.32-format for given decimal value.
 *
 * @param   decValue Decimal value (-1.0 ... +1.0)
 * @param   qFormat Q-format (0 ... 31)
 *
 * @return  Q-format integer value (-2147483648 ... +2147483647)
 */
int32 getAQx32Value(float_CoT decValue, uint8 qFormat)
{
    int64 intValue;

    intValue = decValue * (float_CoT)(((uint32)1) << qFormat);
    if (intValue > INT32_MAX)
    {
        intValue = INT32_MAX;
    }
    else if (intValue < INT32_MIN)
    {
        intValue = INT32_MIN;
    }

    return (int32)intValue;
}
