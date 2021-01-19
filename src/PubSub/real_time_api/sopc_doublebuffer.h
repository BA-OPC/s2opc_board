/*
 * Licensed to Systerel under one or more contributor license
 * agreements. See the NOTICE file distributed with this work
 * for additional information regarding copyright ownership.
 * Systerel licenses this file to you under the Apache
 * License, Version 2.0 (the "License"); you may not use this
 * file except in compliance with the License. You may obtain
 * a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

/// @file sopc_doublebuffer.h
///
/// @brief Double buffer: allow multiple read concurrently to one writing operation.
///
///        It is used by ::SOPC_InterruptTimer and ::SOPC_MsgBox and implement non blocking algorithm

#ifndef SOPC_DBO_H_
#define SOPC_DBO_H_

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "sopc_enums.h"
#include "sopc_mem_alloc.h"

/// @brief Double buffer object
typedef struct SOPC_DoubleBuffer SOPC_DoubleBuffer;

/// @brief    Creation of double buffer
/// @warning  Not thread safe!
/// @param[in]    TODO nbReaders  +1         Nb of readers will access to DBO object via SOPC_DBO_Read API
/// @param[in]    atomic_elt_size     Size of an atomic element
/// @return   DBO object. Shall be destroyed via SOPC_DoubleBuffer_Destroy.
SOPC_DoubleBuffer* SOPC_DoubleBuffer_Create(size_t nbElements, size_t elementSize);

/// @brief   Destroy a double buffer array
/// @warning Not thread safe!
/// @param [inout]  p  Object to destroy. Pointer is setto NULL.
void SOPC_DoubleBuffer_Destroy(SOPC_DoubleBuffer** pp);

// Following functions (SOPC_DoubleBuffer_XxWriteBufferXx) shall be used from one same thread execution context.
// because not thread safe. SOPC_DoubleBuffer is designed for 1 writer / Multiple readers

/// @brief Reserve a buffer for write operation.
/// @warning Not thread safe for concurrent WRITERS.
/// @param [in] p DBO object
/// @param [out] pIdBuffer Buffer identifier which will be used with write buffer functions.
/// @param [out] pMaxSize Max allowed size
/// @return SOPC_STATUS_NOK in case of failure (returned idBuffer set to UINT32_MAX), else SOPC_STATUS_OK
SOPC_ReturnStatus SOPC_DoubleBuffer_GetWriteBuffer(SOPC_DoubleBuffer* p, size_t* pIdBuffer, size_t* pMaxSize);

/// @brief Write data to a buffer.
/// @warning Not thread safe for concurrent WRITERS!
/// @warning Shall be called between GetWriteBuffer and ReleaseWriteBuffer
/// @param [in] p DBO object
/// @param [in] idBuffer Buffer identifier returned by SOPC_DoubleBuffer_GetWriteBuffer
/// @param [in] offset Offset of writing start. \p offset + \p size must not exceed element size
/// @param [in] data Data to write
/// @param [in] size Size of data to write
/// @param [out] pWrittenSize Pointer to the number of bytes written (including preivous and after).
/// @param [in] ignorePrevious Ignore previous data: don't copy previous last record information before offset
/// @param [in] ignoreAfter Ignore previous data after offset + size
/// @return Returns SOPC_STATUS_OK in case of success.
SOPC_ReturnStatus SOPC_DoubleBuffer_WriteBuffer(SOPC_DoubleBuffer* p,
                                                size_t idBuffer,
                                                size_t offset,
                                                uint8_t* data,
                                                size_t size,
                                                size_t* pWrittenSize,
                                                bool ignorePrevious,
                                                bool ignoreAfter);

/// @brief Expose directly double buffer data field and size field.
/// @warning Not thread safe for concurrent WRITERS!
/// @warning Use it carefully, no check of size and data written !
/// @param [in] p DBO object
/// @param [in] idBuffer Buffer identifier returned by SOPC_DoubleBuffer_GetWriteBuffer
/// @param [out] ppDataField Address where is returned pointer on buffer data field
/// @param [out] ppSizeField Address where is returned pointer on buffer size field
/// @param [in] ignorePrevious If false, the value that was committed in the previous write is copied to the buffer.
/// @return SOPC_STATUS_OK in case of success.
SOPC_ReturnStatus SOPC_DoubleBuffer_WriteBufferGetPtr(SOPC_DoubleBuffer* p,
                                                      size_t idBuffer,
                                                      uint8_t** ppDataField,
                                                      bool ignorePrevious);

/// @brief Set nb of significant bytes to 0 of a double buffer
/// @warning Not thread safe for concurrent WRITERS!
/// @warning Shall be called between GetWriteBuffer and ReleaseWriteBuffer
/// @param [in] p DBO object
/// @param [in] idBuffer Identifier of buffer returned by SOPC_DoubleBuffer_GetWriteBuffer
/// @return SOPC_STATUS_OK in case of success.
SOPC_ReturnStatus SOPC_DoubleBuffer_WriteBufferErase(SOPC_DoubleBuffer* p, size_t idBuffer);

/// @brief Release a reserved buffer after a write operation. Modification by SOPC_DoubleBuffer_WriteXXX are taken into
/// account.
/// @warning If you want cancel write operation, don't call this function!
/// @param [in] p DBO buffer object reference
/// @param [inout] pIdBuffer Id of buffer returned by SOPC_DoubleBuffer_GetWriteBuffer. Set to UINT32_MAX.
/// @return SOPC_STATUS_OK in case of success, else SOPC_STATUS_NOK.
SOPC_ReturnStatus SOPC_DoubleBuffer_ReleaseWriteBuffer(SOPC_DoubleBuffer* p, size_t idBuffer);

/// @brief Get most up to date buffer to read. This buffer is marked as reading status.
/// @warning Shall always be called before ReadBuffer/ReadBufferPtr and ReleaseReadBuffer
/// @param [in] p DBO Object
/// @param [inout] pIdBuffer Address where buffer identifier is returned
/// @return Returns SOPC_STATUS_OK in case of success.
SOPC_ReturnStatus SOPC_DoubleBuffer_GetReadBuffer(SOPC_DoubleBuffer* p, size_t* pIdBuffer);

/// @brief Expose directly pointer on data buffer and return size of significant bytes
/// @warning Shall be called between GetReadBuffer and ReleaseBuffer
/// @param [in] p DBO Object
/// @param [in] idBuffer Buffer identifier returned by SOPC_DoubleBuffer_GetReadBuffer
/// @param [out] pData Address where is returned pointer on data buffer
/// @param [out] pDataToRead Address where is returned data size can be read from offset 0
/// @return Returns SOPC_STATUS_OK in case of success.
SOPC_ReturnStatus SOPC_DoubleBuffer_ReadBufferPtr(SOPC_DoubleBuffer* p, size_t idBuffer, uint8_t** ppData);

/// @brief Read buffer from offset, on sizeRequest
/// @param [in] p DBO object
/// @param [in] idBuffer Buffer identifier returned by SOPC_DoubleBuffer_GetReadBuffer
/// @param [in] offset Absolute offset in the internal buffer where start reading
/// @param [out] data Output buffer where data are returned
/// @param [in] sizeRequest Number of bytes to copy from internal buffer from its offset to output buffer
/// @param [out] pReadData Address where size of data read is returned
/// @return Returns SOPC_STATUS_OK in case of success
SOPC_ReturnStatus SOPC_DoubleBuffer_ReadBuffer(SOPC_DoubleBuffer* p,
                                               size_t idBuffer,
                                               size_t offset,
                                               uint8_t* data,
                                               size_t size,
                                               size_t* pReadSize);

/// @brief Release read buffer to allow writer to write.
/// @param [in] p DBO Object
/// @param [inout] pIdBuffer Address where can be found buffer identifier to release. Set to UINT32_MAX.
/// @return Returns SOPC_STATUS_OK in case of success.
SOPC_ReturnStatus SOPC_DoubleBuffer_ReleaseReadBuffer(SOPC_DoubleBuffer* p, size_t idBuffer);

#endif /* SOPC_DBO_H_ */
