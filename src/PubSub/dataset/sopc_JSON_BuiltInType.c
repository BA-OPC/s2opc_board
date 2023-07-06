/*
 * sopc_JSON_BuiltInType.c
 *
 *  Created on: 6 juil. 2023
 *      Author: sebastien
 */

#include "sopc_JSON_BuiltInType.h"

/*
 * Convert OPCUA Types to JSON Types
 */

SOPC_ReturnStatus SOPC_JSON_BuiltInType_Boolean(bool value, char * buffer, size_t sizeBuffer)
{
	int res = 0;
	if (value)
	{
		res = snprintf(buffer,sizeBuffer,"%s","true");
	}
	else
	{
		res = snprintf(buffer,sizeBuffer,"%s","false");
	}
	if ( res <= 0 || (int) sizeBuffer  <= res)
	{
		return SOPC_STATUS_NOK;
	}
	return SOPC_STATUS_OK;
}

SOPC_ReturnStatus SOPC_JSON_BuiltInType_Int16(int value, char * buffer, size_t sizeBuffer)
{
	int res = snprintf(buffer,sizeBuffer,"%d",value);
	if ( res <= 0 || (int) sizeBuffer  <= res)
	{
		return SOPC_STATUS_NOK;
	}
	return SOPC_STATUS_OK;
}

SOPC_ReturnStatus SOPC_JSON_BuiltInType_UInt16(uint16_t value, char * buffer, size_t sizeBuffer)
{
	int res = snprintf(buffer,sizeBuffer,"%" PRIu16,value);
	if ( res <= 0 || (int) sizeBuffer  <= res)
	{
		return SOPC_STATUS_NOK;
	}
	return SOPC_STATUS_OK;
}

SOPC_ReturnStatus SOPC_JSON_BuiltInType_Int32(long value, char * buffer, size_t sizeBuffer)
{
	int res = snprintf(buffer,sizeBuffer,"%li",value);
	if ( res <= 0 || (int) sizeBuffer  <= res)
	{
		return SOPC_STATUS_NOK;
	}
	return SOPC_STATUS_OK;
}

SOPC_ReturnStatus SOPC_JSON_BuiltInType_UInt32(uint32_t value, char * buffer, size_t sizeBuffer)
{
	int res = snprintf(buffer,sizeBuffer,"%" PRIu32,value);
	if ( res <= 0 || (int) sizeBuffer  <= res)
	{
		return SOPC_STATUS_NOK;
	}
	return SOPC_STATUS_OK;
}

SOPC_ReturnStatus SOPC_JSON_BuiltInType_Int64(long long value, char * buffer, size_t sizeBuffer)
{
//TODO
	SOPC_UNUSED_ARG(value);
	SOPC_UNUSED_ARG(buffer);
	SOPC_UNUSED_ARG(sizeBuffer);
	return SOPC_STATUS_NOK;
}
SOPC_ReturnStatus SOPC_JSON_BuiltInType_UInt64(uint64_t value, char * buffer, size_t sizeBuffer)
{
//TODO
	SOPC_UNUSED_ARG(value);
	SOPC_UNUSED_ARG(buffer);
	SOPC_UNUSED_ARG(sizeBuffer);
	return SOPC_STATUS_NOK;
}

SOPC_ReturnStatus SOPC_JSON_BuiltInType_Float(float value, char * buffer, size_t sizeBuffer)
{
	//TODO Special floating-point numbers
	int res = snprintf(buffer,sizeBuffer,"%f",value);
	if ( res <= 0 || (int) sizeBuffer  <= res)
	{
		return SOPC_STATUS_NOK;
	}
	return SOPC_STATUS_OK;
}

SOPC_ReturnStatus SOPC_JSON_BuiltInType_Double(double value, char * buffer, size_t sizeBuffer)
{
	//TODO Special floating-point numbers
	int res = snprintf(buffer,sizeBuffer,"%f",value);
	if ( res <= 0 || (int) sizeBuffer  <= res)
	{
		return SOPC_STATUS_NOK;
	}
	return SOPC_STATUS_OK;
}

SOPC_ReturnStatus SOPC_JSON_BuiltInType_String(char * value, char * buffer, size_t sizeBuffer)
{
	if (value == NULL)
	{
		value = "NULL";
	}
	int res = snprintf(buffer,sizeBuffer,"\"%s\"",value);
	if ( res <= 0 || (int) sizeBuffer  <= res)
	{
		return SOPC_STATUS_NOK;
	}
	return SOPC_STATUS_OK;
}


