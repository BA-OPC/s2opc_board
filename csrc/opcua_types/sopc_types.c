/* ========================================================================
 * Copyright (c) 2005-2016 The OPC Foundation, Inc. All rights reserved.
 *
 * OPC Foundation MIT License 1.00
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * The complete license agreement can be found here:
 * http://opcfoundation.org/License/MIT/1.00/
 *
 * Modifications: adaptation for S2OPC project
 * ======================================================================*/

/* standard */
#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

/* self */
#include "sopc_types.h"

/* stack */
#include "sopc_encoder.h"

/* types */
#include "opcua_identifiers.h"

#ifndef OPCUA_EXCLUDE_Node
/*============================================================================
 * OpcUa_Node_Initialize
 *===========================================================================*/
void OpcUa_Node_Initialize(void* pValue)
{
    OpcUa_Node* a_pValue = (OpcUa_Node*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_Node_EncodeableType;
        SOPC_NodeId_Initialize(&a_pValue->NodeId);
        SOPC_Initialize_EnumeratedType((int32_t*) &a_pValue->NodeClass);
        SOPC_QualifiedName_Initialize(&a_pValue->BrowseName);
        SOPC_LocalizedText_Initialize(&a_pValue->DisplayName);
        SOPC_LocalizedText_Initialize(&a_pValue->Description);
        SOPC_UInt32_Initialize(&a_pValue->WriteMask);
        SOPC_UInt32_Initialize(&a_pValue->UserWriteMask);
        SOPC_Initialize_Array(&a_pValue->NoOfReferences, (void**) &a_pValue->References, sizeof(OpcUa_ReferenceNode),
                              (SOPC_EncodeableObject_PfnInitialize*) OpcUa_ReferenceNode_Initialize);
    }
}

/*============================================================================
 * OpcUa_Node_Clear
 *===========================================================================*/
void OpcUa_Node_Clear(void* pValue)
{
    OpcUa_Node* a_pValue = (OpcUa_Node*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_NodeId_Clear(&a_pValue->NodeId);
        SOPC_Clear_EnumeratedType((int32_t*) &a_pValue->NodeClass);
        SOPC_QualifiedName_Clear(&a_pValue->BrowseName);
        SOPC_LocalizedText_Clear(&a_pValue->DisplayName);
        SOPC_LocalizedText_Clear(&a_pValue->Description);
        SOPC_UInt32_Clear(&a_pValue->WriteMask);
        SOPC_UInt32_Clear(&a_pValue->UserWriteMask);
        SOPC_Clear_Array(&a_pValue->NoOfReferences, (void**) &a_pValue->References, sizeof(OpcUa_ReferenceNode),
                         (SOPC_EncodeableObject_PfnClear*) OpcUa_ReferenceNode_Clear);
    }
}

/*============================================================================
 * OpcUa_Node_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_Node_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_Node* a_pValue = (const OpcUa_Node*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Write(&a_pValue->NodeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Write_EnumeratedType(buf, (const int32_t*) &a_pValue->NodeClass);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_QualifiedName_Write(&a_pValue->BrowseName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Write(&a_pValue->DisplayName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Write(&a_pValue->Description, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->WriteMask, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->UserWriteMask, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->References;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfReferences, &arr, sizeof(OpcUa_ReferenceNode),
                                  (SOPC_EncodeableObject_PfnEncode*) OpcUa_ReferenceNode_Encode);
    }

    return status;
}

/*============================================================================
 * OpcUa_Node_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_Node_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_Node* a_pValue = (OpcUa_Node*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_Node_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Read(&a_pValue->NodeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_EnumeratedType(buf, (int32_t*) &a_pValue->NodeClass);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_QualifiedName_Read(&a_pValue->BrowseName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Read(&a_pValue->DisplayName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Read(&a_pValue->Description, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->WriteMask, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->UserWriteMask, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status =
            SOPC_Read_Array(buf, &a_pValue->NoOfReferences, (void**) &a_pValue->References, sizeof(OpcUa_ReferenceNode),
                            (SOPC_EncodeableObject_PfnDecode*) OpcUa_ReferenceNode_Decode,
                            (SOPC_EncodeableObject_PfnInitialize*) OpcUa_ReferenceNode_Initialize,
                            (SOPC_EncodeableObject_PfnClear*) OpcUa_ReferenceNode_Clear);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_Node_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_InstanceNode
/*============================================================================
 * OpcUa_InstanceNode_Initialize
 *===========================================================================*/
void OpcUa_InstanceNode_Initialize(void* pValue)
{
    OpcUa_InstanceNode* a_pValue = (OpcUa_InstanceNode*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_InstanceNode_EncodeableType;
        SOPC_NodeId_Initialize(&a_pValue->NodeId);
        SOPC_Initialize_EnumeratedType((int32_t*) &a_pValue->NodeClass);
        SOPC_QualifiedName_Initialize(&a_pValue->BrowseName);
        SOPC_LocalizedText_Initialize(&a_pValue->DisplayName);
        SOPC_LocalizedText_Initialize(&a_pValue->Description);
        SOPC_UInt32_Initialize(&a_pValue->WriteMask);
        SOPC_UInt32_Initialize(&a_pValue->UserWriteMask);
        SOPC_Initialize_Array(&a_pValue->NoOfReferences, (void**) &a_pValue->References, sizeof(OpcUa_ReferenceNode),
                              (SOPC_EncodeableObject_PfnInitialize*) OpcUa_ReferenceNode_Initialize);
    }
}

/*============================================================================
 * OpcUa_InstanceNode_Clear
 *===========================================================================*/
void OpcUa_InstanceNode_Clear(void* pValue)
{
    OpcUa_InstanceNode* a_pValue = (OpcUa_InstanceNode*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_NodeId_Clear(&a_pValue->NodeId);
        SOPC_Clear_EnumeratedType((int32_t*) &a_pValue->NodeClass);
        SOPC_QualifiedName_Clear(&a_pValue->BrowseName);
        SOPC_LocalizedText_Clear(&a_pValue->DisplayName);
        SOPC_LocalizedText_Clear(&a_pValue->Description);
        SOPC_UInt32_Clear(&a_pValue->WriteMask);
        SOPC_UInt32_Clear(&a_pValue->UserWriteMask);
        SOPC_Clear_Array(&a_pValue->NoOfReferences, (void**) &a_pValue->References, sizeof(OpcUa_ReferenceNode),
                         (SOPC_EncodeableObject_PfnClear*) OpcUa_ReferenceNode_Clear);
    }
}

/*============================================================================
 * OpcUa_InstanceNode_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_InstanceNode_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_InstanceNode* a_pValue = (const OpcUa_InstanceNode*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Write(&a_pValue->NodeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Write_EnumeratedType(buf, (const int32_t*) &a_pValue->NodeClass);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_QualifiedName_Write(&a_pValue->BrowseName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Write(&a_pValue->DisplayName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Write(&a_pValue->Description, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->WriteMask, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->UserWriteMask, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->References;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfReferences, &arr, sizeof(OpcUa_ReferenceNode),
                                  (SOPC_EncodeableObject_PfnEncode*) OpcUa_ReferenceNode_Encode);
    }

    return status;
}

/*============================================================================
 * OpcUa_InstanceNode_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_InstanceNode_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_InstanceNode* a_pValue = (OpcUa_InstanceNode*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_InstanceNode_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Read(&a_pValue->NodeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_EnumeratedType(buf, (int32_t*) &a_pValue->NodeClass);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_QualifiedName_Read(&a_pValue->BrowseName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Read(&a_pValue->DisplayName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Read(&a_pValue->Description, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->WriteMask, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->UserWriteMask, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status =
            SOPC_Read_Array(buf, &a_pValue->NoOfReferences, (void**) &a_pValue->References, sizeof(OpcUa_ReferenceNode),
                            (SOPC_EncodeableObject_PfnDecode*) OpcUa_ReferenceNode_Decode,
                            (SOPC_EncodeableObject_PfnInitialize*) OpcUa_ReferenceNode_Initialize,
                            (SOPC_EncodeableObject_PfnClear*) OpcUa_ReferenceNode_Clear);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_InstanceNode_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_TypeNode
/*============================================================================
 * OpcUa_TypeNode_Initialize
 *===========================================================================*/
void OpcUa_TypeNode_Initialize(void* pValue)
{
    OpcUa_TypeNode* a_pValue = (OpcUa_TypeNode*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_TypeNode_EncodeableType;
        SOPC_NodeId_Initialize(&a_pValue->NodeId);
        SOPC_Initialize_EnumeratedType((int32_t*) &a_pValue->NodeClass);
        SOPC_QualifiedName_Initialize(&a_pValue->BrowseName);
        SOPC_LocalizedText_Initialize(&a_pValue->DisplayName);
        SOPC_LocalizedText_Initialize(&a_pValue->Description);
        SOPC_UInt32_Initialize(&a_pValue->WriteMask);
        SOPC_UInt32_Initialize(&a_pValue->UserWriteMask);
        SOPC_Initialize_Array(&a_pValue->NoOfReferences, (void**) &a_pValue->References, sizeof(OpcUa_ReferenceNode),
                              (SOPC_EncodeableObject_PfnInitialize*) OpcUa_ReferenceNode_Initialize);
    }
}

/*============================================================================
 * OpcUa_TypeNode_Clear
 *===========================================================================*/
void OpcUa_TypeNode_Clear(void* pValue)
{
    OpcUa_TypeNode* a_pValue = (OpcUa_TypeNode*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_NodeId_Clear(&a_pValue->NodeId);
        SOPC_Clear_EnumeratedType((int32_t*) &a_pValue->NodeClass);
        SOPC_QualifiedName_Clear(&a_pValue->BrowseName);
        SOPC_LocalizedText_Clear(&a_pValue->DisplayName);
        SOPC_LocalizedText_Clear(&a_pValue->Description);
        SOPC_UInt32_Clear(&a_pValue->WriteMask);
        SOPC_UInt32_Clear(&a_pValue->UserWriteMask);
        SOPC_Clear_Array(&a_pValue->NoOfReferences, (void**) &a_pValue->References, sizeof(OpcUa_ReferenceNode),
                         (SOPC_EncodeableObject_PfnClear*) OpcUa_ReferenceNode_Clear);
    }
}

/*============================================================================
 * OpcUa_TypeNode_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_TypeNode_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_TypeNode* a_pValue = (const OpcUa_TypeNode*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Write(&a_pValue->NodeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Write_EnumeratedType(buf, (const int32_t*) &a_pValue->NodeClass);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_QualifiedName_Write(&a_pValue->BrowseName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Write(&a_pValue->DisplayName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Write(&a_pValue->Description, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->WriteMask, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->UserWriteMask, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->References;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfReferences, &arr, sizeof(OpcUa_ReferenceNode),
                                  (SOPC_EncodeableObject_PfnEncode*) OpcUa_ReferenceNode_Encode);
    }

    return status;
}

/*============================================================================
 * OpcUa_TypeNode_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_TypeNode_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_TypeNode* a_pValue = (OpcUa_TypeNode*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_TypeNode_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Read(&a_pValue->NodeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_EnumeratedType(buf, (int32_t*) &a_pValue->NodeClass);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_QualifiedName_Read(&a_pValue->BrowseName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Read(&a_pValue->DisplayName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Read(&a_pValue->Description, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->WriteMask, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->UserWriteMask, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status =
            SOPC_Read_Array(buf, &a_pValue->NoOfReferences, (void**) &a_pValue->References, sizeof(OpcUa_ReferenceNode),
                            (SOPC_EncodeableObject_PfnDecode*) OpcUa_ReferenceNode_Decode,
                            (SOPC_EncodeableObject_PfnInitialize*) OpcUa_ReferenceNode_Initialize,
                            (SOPC_EncodeableObject_PfnClear*) OpcUa_ReferenceNode_Clear);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_TypeNode_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_ObjectNode
/*============================================================================
 * OpcUa_ObjectNode_Initialize
 *===========================================================================*/
void OpcUa_ObjectNode_Initialize(void* pValue)
{
    OpcUa_ObjectNode* a_pValue = (OpcUa_ObjectNode*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_ObjectNode_EncodeableType;
        SOPC_NodeId_Initialize(&a_pValue->NodeId);
        SOPC_Initialize_EnumeratedType((int32_t*) &a_pValue->NodeClass);
        SOPC_QualifiedName_Initialize(&a_pValue->BrowseName);
        SOPC_LocalizedText_Initialize(&a_pValue->DisplayName);
        SOPC_LocalizedText_Initialize(&a_pValue->Description);
        SOPC_UInt32_Initialize(&a_pValue->WriteMask);
        SOPC_UInt32_Initialize(&a_pValue->UserWriteMask);
        SOPC_Initialize_Array(&a_pValue->NoOfReferences, (void**) &a_pValue->References, sizeof(OpcUa_ReferenceNode),
                              (SOPC_EncodeableObject_PfnInitialize*) OpcUa_ReferenceNode_Initialize);
        SOPC_Byte_Initialize(&a_pValue->EventNotifier);
    }
}

/*============================================================================
 * OpcUa_ObjectNode_Clear
 *===========================================================================*/
void OpcUa_ObjectNode_Clear(void* pValue)
{
    OpcUa_ObjectNode* a_pValue = (OpcUa_ObjectNode*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_NodeId_Clear(&a_pValue->NodeId);
        SOPC_Clear_EnumeratedType((int32_t*) &a_pValue->NodeClass);
        SOPC_QualifiedName_Clear(&a_pValue->BrowseName);
        SOPC_LocalizedText_Clear(&a_pValue->DisplayName);
        SOPC_LocalizedText_Clear(&a_pValue->Description);
        SOPC_UInt32_Clear(&a_pValue->WriteMask);
        SOPC_UInt32_Clear(&a_pValue->UserWriteMask);
        SOPC_Clear_Array(&a_pValue->NoOfReferences, (void**) &a_pValue->References, sizeof(OpcUa_ReferenceNode),
                         (SOPC_EncodeableObject_PfnClear*) OpcUa_ReferenceNode_Clear);
        SOPC_Byte_Clear(&a_pValue->EventNotifier);
    }
}

/*============================================================================
 * OpcUa_ObjectNode_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_ObjectNode_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_ObjectNode* a_pValue = (const OpcUa_ObjectNode*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Write(&a_pValue->NodeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Write_EnumeratedType(buf, (const int32_t*) &a_pValue->NodeClass);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_QualifiedName_Write(&a_pValue->BrowseName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Write(&a_pValue->DisplayName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Write(&a_pValue->Description, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->WriteMask, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->UserWriteMask, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->References;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfReferences, &arr, sizeof(OpcUa_ReferenceNode),
                                  (SOPC_EncodeableObject_PfnEncode*) OpcUa_ReferenceNode_Encode);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Byte_Write(&a_pValue->EventNotifier, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_ObjectNode_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_ObjectNode_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_ObjectNode* a_pValue = (OpcUa_ObjectNode*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_ObjectNode_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Read(&a_pValue->NodeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_EnumeratedType(buf, (int32_t*) &a_pValue->NodeClass);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_QualifiedName_Read(&a_pValue->BrowseName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Read(&a_pValue->DisplayName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Read(&a_pValue->Description, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->WriteMask, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->UserWriteMask, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status =
            SOPC_Read_Array(buf, &a_pValue->NoOfReferences, (void**) &a_pValue->References, sizeof(OpcUa_ReferenceNode),
                            (SOPC_EncodeableObject_PfnDecode*) OpcUa_ReferenceNode_Decode,
                            (SOPC_EncodeableObject_PfnInitialize*) OpcUa_ReferenceNode_Initialize,
                            (SOPC_EncodeableObject_PfnClear*) OpcUa_ReferenceNode_Clear);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Byte_Read(&a_pValue->EventNotifier, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_ObjectNode_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_ObjectTypeNode
/*============================================================================
 * OpcUa_ObjectTypeNode_Initialize
 *===========================================================================*/
void OpcUa_ObjectTypeNode_Initialize(void* pValue)
{
    OpcUa_ObjectTypeNode* a_pValue = (OpcUa_ObjectTypeNode*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_ObjectTypeNode_EncodeableType;
        SOPC_NodeId_Initialize(&a_pValue->NodeId);
        SOPC_Initialize_EnumeratedType((int32_t*) &a_pValue->NodeClass);
        SOPC_QualifiedName_Initialize(&a_pValue->BrowseName);
        SOPC_LocalizedText_Initialize(&a_pValue->DisplayName);
        SOPC_LocalizedText_Initialize(&a_pValue->Description);
        SOPC_UInt32_Initialize(&a_pValue->WriteMask);
        SOPC_UInt32_Initialize(&a_pValue->UserWriteMask);
        SOPC_Initialize_Array(&a_pValue->NoOfReferences, (void**) &a_pValue->References, sizeof(OpcUa_ReferenceNode),
                              (SOPC_EncodeableObject_PfnInitialize*) OpcUa_ReferenceNode_Initialize);
        SOPC_Boolean_Initialize(&a_pValue->IsAbstract);
    }
}

/*============================================================================
 * OpcUa_ObjectTypeNode_Clear
 *===========================================================================*/
void OpcUa_ObjectTypeNode_Clear(void* pValue)
{
    OpcUa_ObjectTypeNode* a_pValue = (OpcUa_ObjectTypeNode*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_NodeId_Clear(&a_pValue->NodeId);
        SOPC_Clear_EnumeratedType((int32_t*) &a_pValue->NodeClass);
        SOPC_QualifiedName_Clear(&a_pValue->BrowseName);
        SOPC_LocalizedText_Clear(&a_pValue->DisplayName);
        SOPC_LocalizedText_Clear(&a_pValue->Description);
        SOPC_UInt32_Clear(&a_pValue->WriteMask);
        SOPC_UInt32_Clear(&a_pValue->UserWriteMask);
        SOPC_Clear_Array(&a_pValue->NoOfReferences, (void**) &a_pValue->References, sizeof(OpcUa_ReferenceNode),
                         (SOPC_EncodeableObject_PfnClear*) OpcUa_ReferenceNode_Clear);
        SOPC_Boolean_Clear(&a_pValue->IsAbstract);
    }
}

/*============================================================================
 * OpcUa_ObjectTypeNode_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_ObjectTypeNode_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_ObjectTypeNode* a_pValue = (const OpcUa_ObjectTypeNode*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Write(&a_pValue->NodeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Write_EnumeratedType(buf, (const int32_t*) &a_pValue->NodeClass);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_QualifiedName_Write(&a_pValue->BrowseName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Write(&a_pValue->DisplayName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Write(&a_pValue->Description, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->WriteMask, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->UserWriteMask, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->References;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfReferences, &arr, sizeof(OpcUa_ReferenceNode),
                                  (SOPC_EncodeableObject_PfnEncode*) OpcUa_ReferenceNode_Encode);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Write(&a_pValue->IsAbstract, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_ObjectTypeNode_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_ObjectTypeNode_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_ObjectTypeNode* a_pValue = (OpcUa_ObjectTypeNode*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_ObjectTypeNode_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Read(&a_pValue->NodeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_EnumeratedType(buf, (int32_t*) &a_pValue->NodeClass);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_QualifiedName_Read(&a_pValue->BrowseName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Read(&a_pValue->DisplayName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Read(&a_pValue->Description, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->WriteMask, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->UserWriteMask, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status =
            SOPC_Read_Array(buf, &a_pValue->NoOfReferences, (void**) &a_pValue->References, sizeof(OpcUa_ReferenceNode),
                            (SOPC_EncodeableObject_PfnDecode*) OpcUa_ReferenceNode_Decode,
                            (SOPC_EncodeableObject_PfnInitialize*) OpcUa_ReferenceNode_Initialize,
                            (SOPC_EncodeableObject_PfnClear*) OpcUa_ReferenceNode_Clear);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Read(&a_pValue->IsAbstract, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_ObjectTypeNode_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_VariableNode
/*============================================================================
 * OpcUa_VariableNode_Initialize
 *===========================================================================*/
void OpcUa_VariableNode_Initialize(void* pValue)
{
    OpcUa_VariableNode* a_pValue = (OpcUa_VariableNode*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_VariableNode_EncodeableType;
        SOPC_NodeId_Initialize(&a_pValue->NodeId);
        SOPC_Initialize_EnumeratedType((int32_t*) &a_pValue->NodeClass);
        SOPC_QualifiedName_Initialize(&a_pValue->BrowseName);
        SOPC_LocalizedText_Initialize(&a_pValue->DisplayName);
        SOPC_LocalizedText_Initialize(&a_pValue->Description);
        SOPC_UInt32_Initialize(&a_pValue->WriteMask);
        SOPC_UInt32_Initialize(&a_pValue->UserWriteMask);
        SOPC_Initialize_Array(&a_pValue->NoOfReferences, (void**) &a_pValue->References, sizeof(OpcUa_ReferenceNode),
                              (SOPC_EncodeableObject_PfnInitialize*) OpcUa_ReferenceNode_Initialize);
        SOPC_Variant_Initialize(&a_pValue->Value);
        SOPC_NodeId_Initialize(&a_pValue->DataType);
        SOPC_Int32_Initialize(&a_pValue->ValueRank);
        SOPC_Initialize_Array(&a_pValue->NoOfArrayDimensions, (void**) &a_pValue->ArrayDimensions, sizeof(uint32_t),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_UInt32_InitializeAux);
        SOPC_Byte_Initialize(&a_pValue->AccessLevel);
        SOPC_Byte_Initialize(&a_pValue->UserAccessLevel);
        SOPC_Double_Initialize(&a_pValue->MinimumSamplingInterval);
        SOPC_Boolean_Initialize(&a_pValue->Historizing);
    }
}

/*============================================================================
 * OpcUa_VariableNode_Clear
 *===========================================================================*/
void OpcUa_VariableNode_Clear(void* pValue)
{
    OpcUa_VariableNode* a_pValue = (OpcUa_VariableNode*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_NodeId_Clear(&a_pValue->NodeId);
        SOPC_Clear_EnumeratedType((int32_t*) &a_pValue->NodeClass);
        SOPC_QualifiedName_Clear(&a_pValue->BrowseName);
        SOPC_LocalizedText_Clear(&a_pValue->DisplayName);
        SOPC_LocalizedText_Clear(&a_pValue->Description);
        SOPC_UInt32_Clear(&a_pValue->WriteMask);
        SOPC_UInt32_Clear(&a_pValue->UserWriteMask);
        SOPC_Clear_Array(&a_pValue->NoOfReferences, (void**) &a_pValue->References, sizeof(OpcUa_ReferenceNode),
                         (SOPC_EncodeableObject_PfnClear*) OpcUa_ReferenceNode_Clear);
        SOPC_Variant_Clear(&a_pValue->Value);
        SOPC_NodeId_Clear(&a_pValue->DataType);
        SOPC_Int32_Clear(&a_pValue->ValueRank);
        SOPC_Clear_Array(&a_pValue->NoOfArrayDimensions, (void**) &a_pValue->ArrayDimensions, sizeof(uint32_t),
                         (SOPC_EncodeableObject_PfnClear*) SOPC_UInt32_ClearAux);
        SOPC_Byte_Clear(&a_pValue->AccessLevel);
        SOPC_Byte_Clear(&a_pValue->UserAccessLevel);
        SOPC_Double_Clear(&a_pValue->MinimumSamplingInterval);
        SOPC_Boolean_Clear(&a_pValue->Historizing);
    }
}

/*============================================================================
 * OpcUa_VariableNode_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_VariableNode_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_VariableNode* a_pValue = (const OpcUa_VariableNode*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Write(&a_pValue->NodeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Write_EnumeratedType(buf, (const int32_t*) &a_pValue->NodeClass);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_QualifiedName_Write(&a_pValue->BrowseName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Write(&a_pValue->DisplayName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Write(&a_pValue->Description, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->WriteMask, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->UserWriteMask, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->References;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfReferences, &arr, sizeof(OpcUa_ReferenceNode),
                                  (SOPC_EncodeableObject_PfnEncode*) OpcUa_ReferenceNode_Encode);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Variant_Write(&a_pValue->Value, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Write(&a_pValue->DataType, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Int32_Write(&a_pValue->ValueRank, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->ArrayDimensions;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfArrayDimensions, &arr, sizeof(uint32_t),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_UInt32_WriteAux);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Byte_Write(&a_pValue->AccessLevel, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Byte_Write(&a_pValue->UserAccessLevel, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Double_Write(&a_pValue->MinimumSamplingInterval, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Write(&a_pValue->Historizing, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_VariableNode_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_VariableNode_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_VariableNode* a_pValue = (OpcUa_VariableNode*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_VariableNode_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Read(&a_pValue->NodeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_EnumeratedType(buf, (int32_t*) &a_pValue->NodeClass);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_QualifiedName_Read(&a_pValue->BrowseName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Read(&a_pValue->DisplayName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Read(&a_pValue->Description, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->WriteMask, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->UserWriteMask, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status =
            SOPC_Read_Array(buf, &a_pValue->NoOfReferences, (void**) &a_pValue->References, sizeof(OpcUa_ReferenceNode),
                            (SOPC_EncodeableObject_PfnDecode*) OpcUa_ReferenceNode_Decode,
                            (SOPC_EncodeableObject_PfnInitialize*) OpcUa_ReferenceNode_Initialize,
                            (SOPC_EncodeableObject_PfnClear*) OpcUa_ReferenceNode_Clear);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Variant_Read(&a_pValue->Value, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Read(&a_pValue->DataType, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Int32_Read(&a_pValue->ValueRank, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfArrayDimensions, (void**) &a_pValue->ArrayDimensions,
                                 sizeof(uint32_t), (SOPC_EncodeableObject_PfnDecode*) SOPC_UInt32_ReadAux,
                                 (SOPC_EncodeableObject_PfnInitialize*) SOPC_UInt32_InitializeAux,
                                 (SOPC_EncodeableObject_PfnClear*) SOPC_UInt32_ClearAux);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Byte_Read(&a_pValue->AccessLevel, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Byte_Read(&a_pValue->UserAccessLevel, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Double_Read(&a_pValue->MinimumSamplingInterval, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Read(&a_pValue->Historizing, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_VariableNode_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_VariableTypeNode
/*============================================================================
 * OpcUa_VariableTypeNode_Initialize
 *===========================================================================*/
void OpcUa_VariableTypeNode_Initialize(void* pValue)
{
    OpcUa_VariableTypeNode* a_pValue = (OpcUa_VariableTypeNode*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_VariableTypeNode_EncodeableType;
        SOPC_NodeId_Initialize(&a_pValue->NodeId);
        SOPC_Initialize_EnumeratedType((int32_t*) &a_pValue->NodeClass);
        SOPC_QualifiedName_Initialize(&a_pValue->BrowseName);
        SOPC_LocalizedText_Initialize(&a_pValue->DisplayName);
        SOPC_LocalizedText_Initialize(&a_pValue->Description);
        SOPC_UInt32_Initialize(&a_pValue->WriteMask);
        SOPC_UInt32_Initialize(&a_pValue->UserWriteMask);
        SOPC_Initialize_Array(&a_pValue->NoOfReferences, (void**) &a_pValue->References, sizeof(OpcUa_ReferenceNode),
                              (SOPC_EncodeableObject_PfnInitialize*) OpcUa_ReferenceNode_Initialize);
        SOPC_Variant_Initialize(&a_pValue->Value);
        SOPC_NodeId_Initialize(&a_pValue->DataType);
        SOPC_Int32_Initialize(&a_pValue->ValueRank);
        SOPC_Initialize_Array(&a_pValue->NoOfArrayDimensions, (void**) &a_pValue->ArrayDimensions, sizeof(uint32_t),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_UInt32_InitializeAux);
        SOPC_Boolean_Initialize(&a_pValue->IsAbstract);
    }
}

/*============================================================================
 * OpcUa_VariableTypeNode_Clear
 *===========================================================================*/
void OpcUa_VariableTypeNode_Clear(void* pValue)
{
    OpcUa_VariableTypeNode* a_pValue = (OpcUa_VariableTypeNode*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_NodeId_Clear(&a_pValue->NodeId);
        SOPC_Clear_EnumeratedType((int32_t*) &a_pValue->NodeClass);
        SOPC_QualifiedName_Clear(&a_pValue->BrowseName);
        SOPC_LocalizedText_Clear(&a_pValue->DisplayName);
        SOPC_LocalizedText_Clear(&a_pValue->Description);
        SOPC_UInt32_Clear(&a_pValue->WriteMask);
        SOPC_UInt32_Clear(&a_pValue->UserWriteMask);
        SOPC_Clear_Array(&a_pValue->NoOfReferences, (void**) &a_pValue->References, sizeof(OpcUa_ReferenceNode),
                         (SOPC_EncodeableObject_PfnClear*) OpcUa_ReferenceNode_Clear);
        SOPC_Variant_Clear(&a_pValue->Value);
        SOPC_NodeId_Clear(&a_pValue->DataType);
        SOPC_Int32_Clear(&a_pValue->ValueRank);
        SOPC_Clear_Array(&a_pValue->NoOfArrayDimensions, (void**) &a_pValue->ArrayDimensions, sizeof(uint32_t),
                         (SOPC_EncodeableObject_PfnClear*) SOPC_UInt32_ClearAux);
        SOPC_Boolean_Clear(&a_pValue->IsAbstract);
    }
}

/*============================================================================
 * OpcUa_VariableTypeNode_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_VariableTypeNode_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_VariableTypeNode* a_pValue = (const OpcUa_VariableTypeNode*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Write(&a_pValue->NodeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Write_EnumeratedType(buf, (const int32_t*) &a_pValue->NodeClass);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_QualifiedName_Write(&a_pValue->BrowseName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Write(&a_pValue->DisplayName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Write(&a_pValue->Description, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->WriteMask, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->UserWriteMask, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->References;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfReferences, &arr, sizeof(OpcUa_ReferenceNode),
                                  (SOPC_EncodeableObject_PfnEncode*) OpcUa_ReferenceNode_Encode);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Variant_Write(&a_pValue->Value, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Write(&a_pValue->DataType, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Int32_Write(&a_pValue->ValueRank, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->ArrayDimensions;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfArrayDimensions, &arr, sizeof(uint32_t),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_UInt32_WriteAux);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Write(&a_pValue->IsAbstract, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_VariableTypeNode_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_VariableTypeNode_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_VariableTypeNode* a_pValue = (OpcUa_VariableTypeNode*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_VariableTypeNode_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Read(&a_pValue->NodeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_EnumeratedType(buf, (int32_t*) &a_pValue->NodeClass);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_QualifiedName_Read(&a_pValue->BrowseName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Read(&a_pValue->DisplayName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Read(&a_pValue->Description, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->WriteMask, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->UserWriteMask, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status =
            SOPC_Read_Array(buf, &a_pValue->NoOfReferences, (void**) &a_pValue->References, sizeof(OpcUa_ReferenceNode),
                            (SOPC_EncodeableObject_PfnDecode*) OpcUa_ReferenceNode_Decode,
                            (SOPC_EncodeableObject_PfnInitialize*) OpcUa_ReferenceNode_Initialize,
                            (SOPC_EncodeableObject_PfnClear*) OpcUa_ReferenceNode_Clear);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Variant_Read(&a_pValue->Value, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Read(&a_pValue->DataType, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Int32_Read(&a_pValue->ValueRank, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfArrayDimensions, (void**) &a_pValue->ArrayDimensions,
                                 sizeof(uint32_t), (SOPC_EncodeableObject_PfnDecode*) SOPC_UInt32_ReadAux,
                                 (SOPC_EncodeableObject_PfnInitialize*) SOPC_UInt32_InitializeAux,
                                 (SOPC_EncodeableObject_PfnClear*) SOPC_UInt32_ClearAux);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Read(&a_pValue->IsAbstract, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_VariableTypeNode_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_ReferenceTypeNode
/*============================================================================
 * OpcUa_ReferenceTypeNode_Initialize
 *===========================================================================*/
void OpcUa_ReferenceTypeNode_Initialize(void* pValue)
{
    OpcUa_ReferenceTypeNode* a_pValue = (OpcUa_ReferenceTypeNode*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_ReferenceTypeNode_EncodeableType;
        SOPC_NodeId_Initialize(&a_pValue->NodeId);
        SOPC_Initialize_EnumeratedType((int32_t*) &a_pValue->NodeClass);
        SOPC_QualifiedName_Initialize(&a_pValue->BrowseName);
        SOPC_LocalizedText_Initialize(&a_pValue->DisplayName);
        SOPC_LocalizedText_Initialize(&a_pValue->Description);
        SOPC_UInt32_Initialize(&a_pValue->WriteMask);
        SOPC_UInt32_Initialize(&a_pValue->UserWriteMask);
        SOPC_Initialize_Array(&a_pValue->NoOfReferences, (void**) &a_pValue->References, sizeof(OpcUa_ReferenceNode),
                              (SOPC_EncodeableObject_PfnInitialize*) OpcUa_ReferenceNode_Initialize);
        SOPC_Boolean_Initialize(&a_pValue->IsAbstract);
        SOPC_Boolean_Initialize(&a_pValue->Symmetric);
        SOPC_LocalizedText_Initialize(&a_pValue->InverseName);
    }
}

/*============================================================================
 * OpcUa_ReferenceTypeNode_Clear
 *===========================================================================*/
void OpcUa_ReferenceTypeNode_Clear(void* pValue)
{
    OpcUa_ReferenceTypeNode* a_pValue = (OpcUa_ReferenceTypeNode*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_NodeId_Clear(&a_pValue->NodeId);
        SOPC_Clear_EnumeratedType((int32_t*) &a_pValue->NodeClass);
        SOPC_QualifiedName_Clear(&a_pValue->BrowseName);
        SOPC_LocalizedText_Clear(&a_pValue->DisplayName);
        SOPC_LocalizedText_Clear(&a_pValue->Description);
        SOPC_UInt32_Clear(&a_pValue->WriteMask);
        SOPC_UInt32_Clear(&a_pValue->UserWriteMask);
        SOPC_Clear_Array(&a_pValue->NoOfReferences, (void**) &a_pValue->References, sizeof(OpcUa_ReferenceNode),
                         (SOPC_EncodeableObject_PfnClear*) OpcUa_ReferenceNode_Clear);
        SOPC_Boolean_Clear(&a_pValue->IsAbstract);
        SOPC_Boolean_Clear(&a_pValue->Symmetric);
        SOPC_LocalizedText_Clear(&a_pValue->InverseName);
    }
}

/*============================================================================
 * OpcUa_ReferenceTypeNode_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_ReferenceTypeNode_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_ReferenceTypeNode* a_pValue = (const OpcUa_ReferenceTypeNode*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Write(&a_pValue->NodeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Write_EnumeratedType(buf, (const int32_t*) &a_pValue->NodeClass);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_QualifiedName_Write(&a_pValue->BrowseName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Write(&a_pValue->DisplayName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Write(&a_pValue->Description, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->WriteMask, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->UserWriteMask, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->References;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfReferences, &arr, sizeof(OpcUa_ReferenceNode),
                                  (SOPC_EncodeableObject_PfnEncode*) OpcUa_ReferenceNode_Encode);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Write(&a_pValue->IsAbstract, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Write(&a_pValue->Symmetric, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Write(&a_pValue->InverseName, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_ReferenceTypeNode_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_ReferenceTypeNode_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_ReferenceTypeNode* a_pValue = (OpcUa_ReferenceTypeNode*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_ReferenceTypeNode_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Read(&a_pValue->NodeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_EnumeratedType(buf, (int32_t*) &a_pValue->NodeClass);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_QualifiedName_Read(&a_pValue->BrowseName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Read(&a_pValue->DisplayName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Read(&a_pValue->Description, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->WriteMask, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->UserWriteMask, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status =
            SOPC_Read_Array(buf, &a_pValue->NoOfReferences, (void**) &a_pValue->References, sizeof(OpcUa_ReferenceNode),
                            (SOPC_EncodeableObject_PfnDecode*) OpcUa_ReferenceNode_Decode,
                            (SOPC_EncodeableObject_PfnInitialize*) OpcUa_ReferenceNode_Initialize,
                            (SOPC_EncodeableObject_PfnClear*) OpcUa_ReferenceNode_Clear);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Read(&a_pValue->IsAbstract, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Read(&a_pValue->Symmetric, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Read(&a_pValue->InverseName, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_ReferenceTypeNode_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_MethodNode
/*============================================================================
 * OpcUa_MethodNode_Initialize
 *===========================================================================*/
void OpcUa_MethodNode_Initialize(void* pValue)
{
    OpcUa_MethodNode* a_pValue = (OpcUa_MethodNode*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_MethodNode_EncodeableType;
        SOPC_NodeId_Initialize(&a_pValue->NodeId);
        SOPC_Initialize_EnumeratedType((int32_t*) &a_pValue->NodeClass);
        SOPC_QualifiedName_Initialize(&a_pValue->BrowseName);
        SOPC_LocalizedText_Initialize(&a_pValue->DisplayName);
        SOPC_LocalizedText_Initialize(&a_pValue->Description);
        SOPC_UInt32_Initialize(&a_pValue->WriteMask);
        SOPC_UInt32_Initialize(&a_pValue->UserWriteMask);
        SOPC_Initialize_Array(&a_pValue->NoOfReferences, (void**) &a_pValue->References, sizeof(OpcUa_ReferenceNode),
                              (SOPC_EncodeableObject_PfnInitialize*) OpcUa_ReferenceNode_Initialize);
        SOPC_Boolean_Initialize(&a_pValue->Executable);
        SOPC_Boolean_Initialize(&a_pValue->UserExecutable);
    }
}

/*============================================================================
 * OpcUa_MethodNode_Clear
 *===========================================================================*/
void OpcUa_MethodNode_Clear(void* pValue)
{
    OpcUa_MethodNode* a_pValue = (OpcUa_MethodNode*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_NodeId_Clear(&a_pValue->NodeId);
        SOPC_Clear_EnumeratedType((int32_t*) &a_pValue->NodeClass);
        SOPC_QualifiedName_Clear(&a_pValue->BrowseName);
        SOPC_LocalizedText_Clear(&a_pValue->DisplayName);
        SOPC_LocalizedText_Clear(&a_pValue->Description);
        SOPC_UInt32_Clear(&a_pValue->WriteMask);
        SOPC_UInt32_Clear(&a_pValue->UserWriteMask);
        SOPC_Clear_Array(&a_pValue->NoOfReferences, (void**) &a_pValue->References, sizeof(OpcUa_ReferenceNode),
                         (SOPC_EncodeableObject_PfnClear*) OpcUa_ReferenceNode_Clear);
        SOPC_Boolean_Clear(&a_pValue->Executable);
        SOPC_Boolean_Clear(&a_pValue->UserExecutable);
    }
}

/*============================================================================
 * OpcUa_MethodNode_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_MethodNode_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_MethodNode* a_pValue = (const OpcUa_MethodNode*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Write(&a_pValue->NodeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Write_EnumeratedType(buf, (const int32_t*) &a_pValue->NodeClass);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_QualifiedName_Write(&a_pValue->BrowseName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Write(&a_pValue->DisplayName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Write(&a_pValue->Description, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->WriteMask, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->UserWriteMask, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->References;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfReferences, &arr, sizeof(OpcUa_ReferenceNode),
                                  (SOPC_EncodeableObject_PfnEncode*) OpcUa_ReferenceNode_Encode);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Write(&a_pValue->Executable, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Write(&a_pValue->UserExecutable, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_MethodNode_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_MethodNode_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_MethodNode* a_pValue = (OpcUa_MethodNode*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_MethodNode_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Read(&a_pValue->NodeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_EnumeratedType(buf, (int32_t*) &a_pValue->NodeClass);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_QualifiedName_Read(&a_pValue->BrowseName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Read(&a_pValue->DisplayName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Read(&a_pValue->Description, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->WriteMask, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->UserWriteMask, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status =
            SOPC_Read_Array(buf, &a_pValue->NoOfReferences, (void**) &a_pValue->References, sizeof(OpcUa_ReferenceNode),
                            (SOPC_EncodeableObject_PfnDecode*) OpcUa_ReferenceNode_Decode,
                            (SOPC_EncodeableObject_PfnInitialize*) OpcUa_ReferenceNode_Initialize,
                            (SOPC_EncodeableObject_PfnClear*) OpcUa_ReferenceNode_Clear);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Read(&a_pValue->Executable, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Read(&a_pValue->UserExecutable, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_MethodNode_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_ViewNode
/*============================================================================
 * OpcUa_ViewNode_Initialize
 *===========================================================================*/
void OpcUa_ViewNode_Initialize(void* pValue)
{
    OpcUa_ViewNode* a_pValue = (OpcUa_ViewNode*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_ViewNode_EncodeableType;
        SOPC_NodeId_Initialize(&a_pValue->NodeId);
        SOPC_Initialize_EnumeratedType((int32_t*) &a_pValue->NodeClass);
        SOPC_QualifiedName_Initialize(&a_pValue->BrowseName);
        SOPC_LocalizedText_Initialize(&a_pValue->DisplayName);
        SOPC_LocalizedText_Initialize(&a_pValue->Description);
        SOPC_UInt32_Initialize(&a_pValue->WriteMask);
        SOPC_UInt32_Initialize(&a_pValue->UserWriteMask);
        SOPC_Initialize_Array(&a_pValue->NoOfReferences, (void**) &a_pValue->References, sizeof(OpcUa_ReferenceNode),
                              (SOPC_EncodeableObject_PfnInitialize*) OpcUa_ReferenceNode_Initialize);
        SOPC_Boolean_Initialize(&a_pValue->ContainsNoLoops);
        SOPC_Byte_Initialize(&a_pValue->EventNotifier);
    }
}

/*============================================================================
 * OpcUa_ViewNode_Clear
 *===========================================================================*/
void OpcUa_ViewNode_Clear(void* pValue)
{
    OpcUa_ViewNode* a_pValue = (OpcUa_ViewNode*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_NodeId_Clear(&a_pValue->NodeId);
        SOPC_Clear_EnumeratedType((int32_t*) &a_pValue->NodeClass);
        SOPC_QualifiedName_Clear(&a_pValue->BrowseName);
        SOPC_LocalizedText_Clear(&a_pValue->DisplayName);
        SOPC_LocalizedText_Clear(&a_pValue->Description);
        SOPC_UInt32_Clear(&a_pValue->WriteMask);
        SOPC_UInt32_Clear(&a_pValue->UserWriteMask);
        SOPC_Clear_Array(&a_pValue->NoOfReferences, (void**) &a_pValue->References, sizeof(OpcUa_ReferenceNode),
                         (SOPC_EncodeableObject_PfnClear*) OpcUa_ReferenceNode_Clear);
        SOPC_Boolean_Clear(&a_pValue->ContainsNoLoops);
        SOPC_Byte_Clear(&a_pValue->EventNotifier);
    }
}

/*============================================================================
 * OpcUa_ViewNode_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_ViewNode_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_ViewNode* a_pValue = (const OpcUa_ViewNode*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Write(&a_pValue->NodeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Write_EnumeratedType(buf, (const int32_t*) &a_pValue->NodeClass);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_QualifiedName_Write(&a_pValue->BrowseName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Write(&a_pValue->DisplayName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Write(&a_pValue->Description, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->WriteMask, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->UserWriteMask, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->References;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfReferences, &arr, sizeof(OpcUa_ReferenceNode),
                                  (SOPC_EncodeableObject_PfnEncode*) OpcUa_ReferenceNode_Encode);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Write(&a_pValue->ContainsNoLoops, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Byte_Write(&a_pValue->EventNotifier, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_ViewNode_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_ViewNode_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_ViewNode* a_pValue = (OpcUa_ViewNode*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_ViewNode_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Read(&a_pValue->NodeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_EnumeratedType(buf, (int32_t*) &a_pValue->NodeClass);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_QualifiedName_Read(&a_pValue->BrowseName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Read(&a_pValue->DisplayName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Read(&a_pValue->Description, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->WriteMask, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->UserWriteMask, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status =
            SOPC_Read_Array(buf, &a_pValue->NoOfReferences, (void**) &a_pValue->References, sizeof(OpcUa_ReferenceNode),
                            (SOPC_EncodeableObject_PfnDecode*) OpcUa_ReferenceNode_Decode,
                            (SOPC_EncodeableObject_PfnInitialize*) OpcUa_ReferenceNode_Initialize,
                            (SOPC_EncodeableObject_PfnClear*) OpcUa_ReferenceNode_Clear);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Read(&a_pValue->ContainsNoLoops, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Byte_Read(&a_pValue->EventNotifier, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_ViewNode_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_DataTypeNode
/*============================================================================
 * OpcUa_DataTypeNode_Initialize
 *===========================================================================*/
void OpcUa_DataTypeNode_Initialize(void* pValue)
{
    OpcUa_DataTypeNode* a_pValue = (OpcUa_DataTypeNode*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_DataTypeNode_EncodeableType;
        SOPC_NodeId_Initialize(&a_pValue->NodeId);
        SOPC_Initialize_EnumeratedType((int32_t*) &a_pValue->NodeClass);
        SOPC_QualifiedName_Initialize(&a_pValue->BrowseName);
        SOPC_LocalizedText_Initialize(&a_pValue->DisplayName);
        SOPC_LocalizedText_Initialize(&a_pValue->Description);
        SOPC_UInt32_Initialize(&a_pValue->WriteMask);
        SOPC_UInt32_Initialize(&a_pValue->UserWriteMask);
        SOPC_Initialize_Array(&a_pValue->NoOfReferences, (void**) &a_pValue->References, sizeof(OpcUa_ReferenceNode),
                              (SOPC_EncodeableObject_PfnInitialize*) OpcUa_ReferenceNode_Initialize);
        SOPC_Boolean_Initialize(&a_pValue->IsAbstract);
    }
}

/*============================================================================
 * OpcUa_DataTypeNode_Clear
 *===========================================================================*/
void OpcUa_DataTypeNode_Clear(void* pValue)
{
    OpcUa_DataTypeNode* a_pValue = (OpcUa_DataTypeNode*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_NodeId_Clear(&a_pValue->NodeId);
        SOPC_Clear_EnumeratedType((int32_t*) &a_pValue->NodeClass);
        SOPC_QualifiedName_Clear(&a_pValue->BrowseName);
        SOPC_LocalizedText_Clear(&a_pValue->DisplayName);
        SOPC_LocalizedText_Clear(&a_pValue->Description);
        SOPC_UInt32_Clear(&a_pValue->WriteMask);
        SOPC_UInt32_Clear(&a_pValue->UserWriteMask);
        SOPC_Clear_Array(&a_pValue->NoOfReferences, (void**) &a_pValue->References, sizeof(OpcUa_ReferenceNode),
                         (SOPC_EncodeableObject_PfnClear*) OpcUa_ReferenceNode_Clear);
        SOPC_Boolean_Clear(&a_pValue->IsAbstract);
    }
}

/*============================================================================
 * OpcUa_DataTypeNode_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_DataTypeNode_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_DataTypeNode* a_pValue = (const OpcUa_DataTypeNode*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Write(&a_pValue->NodeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Write_EnumeratedType(buf, (const int32_t*) &a_pValue->NodeClass);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_QualifiedName_Write(&a_pValue->BrowseName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Write(&a_pValue->DisplayName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Write(&a_pValue->Description, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->WriteMask, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->UserWriteMask, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->References;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfReferences, &arr, sizeof(OpcUa_ReferenceNode),
                                  (SOPC_EncodeableObject_PfnEncode*) OpcUa_ReferenceNode_Encode);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Write(&a_pValue->IsAbstract, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_DataTypeNode_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_DataTypeNode_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_DataTypeNode* a_pValue = (OpcUa_DataTypeNode*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_DataTypeNode_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Read(&a_pValue->NodeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_EnumeratedType(buf, (int32_t*) &a_pValue->NodeClass);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_QualifiedName_Read(&a_pValue->BrowseName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Read(&a_pValue->DisplayName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Read(&a_pValue->Description, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->WriteMask, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->UserWriteMask, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status =
            SOPC_Read_Array(buf, &a_pValue->NoOfReferences, (void**) &a_pValue->References, sizeof(OpcUa_ReferenceNode),
                            (SOPC_EncodeableObject_PfnDecode*) OpcUa_ReferenceNode_Decode,
                            (SOPC_EncodeableObject_PfnInitialize*) OpcUa_ReferenceNode_Initialize,
                            (SOPC_EncodeableObject_PfnClear*) OpcUa_ReferenceNode_Clear);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Read(&a_pValue->IsAbstract, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_DataTypeNode_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_ReferenceNode
/*============================================================================
 * OpcUa_ReferenceNode_Initialize
 *===========================================================================*/
void OpcUa_ReferenceNode_Initialize(void* pValue)
{
    OpcUa_ReferenceNode* a_pValue = (OpcUa_ReferenceNode*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_ReferenceNode_EncodeableType;
        SOPC_NodeId_Initialize(&a_pValue->ReferenceTypeId);
        SOPC_Boolean_Initialize(&a_pValue->IsInverse);
        SOPC_ExpandedNodeId_Initialize(&a_pValue->TargetId);
    }
}

/*============================================================================
 * OpcUa_ReferenceNode_Clear
 *===========================================================================*/
void OpcUa_ReferenceNode_Clear(void* pValue)
{
    OpcUa_ReferenceNode* a_pValue = (OpcUa_ReferenceNode*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_NodeId_Clear(&a_pValue->ReferenceTypeId);
        SOPC_Boolean_Clear(&a_pValue->IsInverse);
        SOPC_ExpandedNodeId_Clear(&a_pValue->TargetId);
    }
}

/*============================================================================
 * OpcUa_ReferenceNode_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_ReferenceNode_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_ReferenceNode* a_pValue = (const OpcUa_ReferenceNode*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Write(&a_pValue->ReferenceTypeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Write(&a_pValue->IsInverse, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ExpandedNodeId_Write(&a_pValue->TargetId, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_ReferenceNode_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_ReferenceNode_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_ReferenceNode* a_pValue = (OpcUa_ReferenceNode*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_ReferenceNode_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Read(&a_pValue->ReferenceTypeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Read(&a_pValue->IsInverse, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ExpandedNodeId_Read(&a_pValue->TargetId, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_ReferenceNode_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_Argument
/*============================================================================
 * OpcUa_Argument_Initialize
 *===========================================================================*/
void OpcUa_Argument_Initialize(void* pValue)
{
    OpcUa_Argument* a_pValue = (OpcUa_Argument*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_Argument_EncodeableType;
        SOPC_String_Initialize(&a_pValue->Name);
        SOPC_NodeId_Initialize(&a_pValue->DataType);
        SOPC_Int32_Initialize(&a_pValue->ValueRank);
        SOPC_Initialize_Array(&a_pValue->NoOfArrayDimensions, (void**) &a_pValue->ArrayDimensions, sizeof(uint32_t),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_UInt32_InitializeAux);
        SOPC_LocalizedText_Initialize(&a_pValue->Description);
    }
}

/*============================================================================
 * OpcUa_Argument_Clear
 *===========================================================================*/
void OpcUa_Argument_Clear(void* pValue)
{
    OpcUa_Argument* a_pValue = (OpcUa_Argument*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_String_Clear(&a_pValue->Name);
        SOPC_NodeId_Clear(&a_pValue->DataType);
        SOPC_Int32_Clear(&a_pValue->ValueRank);
        SOPC_Clear_Array(&a_pValue->NoOfArrayDimensions, (void**) &a_pValue->ArrayDimensions, sizeof(uint32_t),
                         (SOPC_EncodeableObject_PfnClear*) SOPC_UInt32_ClearAux);
        SOPC_LocalizedText_Clear(&a_pValue->Description);
    }
}

/*============================================================================
 * OpcUa_Argument_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_Argument_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_Argument* a_pValue = (const OpcUa_Argument*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Write(&a_pValue->Name, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Write(&a_pValue->DataType, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Int32_Write(&a_pValue->ValueRank, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->ArrayDimensions;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfArrayDimensions, &arr, sizeof(uint32_t),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_UInt32_WriteAux);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Write(&a_pValue->Description, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_Argument_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_Argument_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_Argument* a_pValue = (OpcUa_Argument*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_Argument_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Read(&a_pValue->Name, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Read(&a_pValue->DataType, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Int32_Read(&a_pValue->ValueRank, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfArrayDimensions, (void**) &a_pValue->ArrayDimensions,
                                 sizeof(uint32_t), (SOPC_EncodeableObject_PfnDecode*) SOPC_UInt32_ReadAux,
                                 (SOPC_EncodeableObject_PfnInitialize*) SOPC_UInt32_InitializeAux,
                                 (SOPC_EncodeableObject_PfnClear*) SOPC_UInt32_ClearAux);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Read(&a_pValue->Description, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_Argument_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_EnumValueType
/*============================================================================
 * OpcUa_EnumValueType_Initialize
 *===========================================================================*/
void OpcUa_EnumValueType_Initialize(void* pValue)
{
    OpcUa_EnumValueType* a_pValue = (OpcUa_EnumValueType*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_EnumValueType_EncodeableType;
        SOPC_Int64_Initialize(&a_pValue->Value);
        SOPC_LocalizedText_Initialize(&a_pValue->DisplayName);
        SOPC_LocalizedText_Initialize(&a_pValue->Description);
    }
}

/*============================================================================
 * OpcUa_EnumValueType_Clear
 *===========================================================================*/
void OpcUa_EnumValueType_Clear(void* pValue)
{
    OpcUa_EnumValueType* a_pValue = (OpcUa_EnumValueType*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_Int64_Clear(&a_pValue->Value);
        SOPC_LocalizedText_Clear(&a_pValue->DisplayName);
        SOPC_LocalizedText_Clear(&a_pValue->Description);
    }
}

/*============================================================================
 * OpcUa_EnumValueType_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_EnumValueType_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_EnumValueType* a_pValue = (const OpcUa_EnumValueType*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Int64_Write(&a_pValue->Value, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Write(&a_pValue->DisplayName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Write(&a_pValue->Description, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_EnumValueType_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_EnumValueType_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_EnumValueType* a_pValue = (OpcUa_EnumValueType*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_EnumValueType_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Int64_Read(&a_pValue->Value, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Read(&a_pValue->DisplayName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Read(&a_pValue->Description, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_EnumValueType_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_EnumField
/*============================================================================
 * OpcUa_EnumField_Initialize
 *===========================================================================*/
void OpcUa_EnumField_Initialize(void* pValue)
{
    OpcUa_EnumField* a_pValue = (OpcUa_EnumField*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_EnumField_EncodeableType;
        SOPC_Int64_Initialize(&a_pValue->Value);
        SOPC_LocalizedText_Initialize(&a_pValue->DisplayName);
        SOPC_LocalizedText_Initialize(&a_pValue->Description);
        SOPC_String_Initialize(&a_pValue->Name);
    }
}

/*============================================================================
 * OpcUa_EnumField_Clear
 *===========================================================================*/
void OpcUa_EnumField_Clear(void* pValue)
{
    OpcUa_EnumField* a_pValue = (OpcUa_EnumField*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_Int64_Clear(&a_pValue->Value);
        SOPC_LocalizedText_Clear(&a_pValue->DisplayName);
        SOPC_LocalizedText_Clear(&a_pValue->Description);
        SOPC_String_Clear(&a_pValue->Name);
    }
}

/*============================================================================
 * OpcUa_EnumField_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_EnumField_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_EnumField* a_pValue = (const OpcUa_EnumField*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Int64_Write(&a_pValue->Value, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Write(&a_pValue->DisplayName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Write(&a_pValue->Description, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Write(&a_pValue->Name, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_EnumField_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_EnumField_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_EnumField* a_pValue = (OpcUa_EnumField*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_EnumField_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Int64_Read(&a_pValue->Value, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Read(&a_pValue->DisplayName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Read(&a_pValue->Description, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Read(&a_pValue->Name, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_EnumField_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_OptionSet
/*============================================================================
 * OpcUa_OptionSet_Initialize
 *===========================================================================*/
void OpcUa_OptionSet_Initialize(void* pValue)
{
    OpcUa_OptionSet* a_pValue = (OpcUa_OptionSet*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_OptionSet_EncodeableType;
        SOPC_ByteString_Initialize(&a_pValue->Value);
        SOPC_ByteString_Initialize(&a_pValue->ValidBits);
    }
}

/*============================================================================
 * OpcUa_OptionSet_Clear
 *===========================================================================*/
void OpcUa_OptionSet_Clear(void* pValue)
{
    OpcUa_OptionSet* a_pValue = (OpcUa_OptionSet*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_ByteString_Clear(&a_pValue->Value);
        SOPC_ByteString_Clear(&a_pValue->ValidBits);
    }
}

/*============================================================================
 * OpcUa_OptionSet_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_OptionSet_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_OptionSet* a_pValue = (const OpcUa_OptionSet*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ByteString_Write(&a_pValue->Value, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ByteString_Write(&a_pValue->ValidBits, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_OptionSet_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_OptionSet_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_OptionSet* a_pValue = (OpcUa_OptionSet*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_OptionSet_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ByteString_Read(&a_pValue->Value, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ByteString_Read(&a_pValue->ValidBits, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_OptionSet_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_TimeZoneDataType
/*============================================================================
 * OpcUa_TimeZoneDataType_Initialize
 *===========================================================================*/
void OpcUa_TimeZoneDataType_Initialize(void* pValue)
{
    OpcUa_TimeZoneDataType* a_pValue = (OpcUa_TimeZoneDataType*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_TimeZoneDataType_EncodeableType;
        SOPC_Int16_Initialize(&a_pValue->Offset);
        SOPC_Boolean_Initialize(&a_pValue->DaylightSavingInOffset);
    }
}

/*============================================================================
 * OpcUa_TimeZoneDataType_Clear
 *===========================================================================*/
void OpcUa_TimeZoneDataType_Clear(void* pValue)
{
    OpcUa_TimeZoneDataType* a_pValue = (OpcUa_TimeZoneDataType*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_Int16_Clear(&a_pValue->Offset);
        SOPC_Boolean_Clear(&a_pValue->DaylightSavingInOffset);
    }
}

/*============================================================================
 * OpcUa_TimeZoneDataType_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_TimeZoneDataType_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_TimeZoneDataType* a_pValue = (const OpcUa_TimeZoneDataType*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Int16_Write(&a_pValue->Offset, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Write(&a_pValue->DaylightSavingInOffset, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_TimeZoneDataType_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_TimeZoneDataType_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_TimeZoneDataType* a_pValue = (OpcUa_TimeZoneDataType*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_TimeZoneDataType_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Int16_Read(&a_pValue->Offset, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Read(&a_pValue->DaylightSavingInOffset, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_TimeZoneDataType_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_ApplicationDescription
/*============================================================================
 * OpcUa_ApplicationDescription_Initialize
 *===========================================================================*/
void OpcUa_ApplicationDescription_Initialize(void* pValue)
{
    OpcUa_ApplicationDescription* a_pValue = (OpcUa_ApplicationDescription*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_ApplicationDescription_EncodeableType;
        SOPC_String_Initialize(&a_pValue->ApplicationUri);
        SOPC_String_Initialize(&a_pValue->ProductUri);
        SOPC_LocalizedText_Initialize(&a_pValue->ApplicationName);
        SOPC_Initialize_EnumeratedType((int32_t*) &a_pValue->ApplicationType);
        SOPC_String_Initialize(&a_pValue->GatewayServerUri);
        SOPC_String_Initialize(&a_pValue->DiscoveryProfileUri);
        SOPC_Initialize_Array(&a_pValue->NoOfDiscoveryUrls, (void**) &a_pValue->DiscoveryUrls, sizeof(SOPC_String),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_String_InitializeAux);
    }
}

/*============================================================================
 * OpcUa_ApplicationDescription_Clear
 *===========================================================================*/
void OpcUa_ApplicationDescription_Clear(void* pValue)
{
    OpcUa_ApplicationDescription* a_pValue = (OpcUa_ApplicationDescription*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_String_Clear(&a_pValue->ApplicationUri);
        SOPC_String_Clear(&a_pValue->ProductUri);
        SOPC_LocalizedText_Clear(&a_pValue->ApplicationName);
        SOPC_Clear_EnumeratedType((int32_t*) &a_pValue->ApplicationType);
        SOPC_String_Clear(&a_pValue->GatewayServerUri);
        SOPC_String_Clear(&a_pValue->DiscoveryProfileUri);
        SOPC_Clear_Array(&a_pValue->NoOfDiscoveryUrls, (void**) &a_pValue->DiscoveryUrls, sizeof(SOPC_String),
                         (SOPC_EncodeableObject_PfnClear*) SOPC_String_ClearAux);
    }
}

/*============================================================================
 * OpcUa_ApplicationDescription_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_ApplicationDescription_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_ApplicationDescription* a_pValue = (const OpcUa_ApplicationDescription*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Write(&a_pValue->ApplicationUri, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Write(&a_pValue->ProductUri, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Write(&a_pValue->ApplicationName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Write_EnumeratedType(buf, (const int32_t*) &a_pValue->ApplicationType);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Write(&a_pValue->GatewayServerUri, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Write(&a_pValue->DiscoveryProfileUri, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->DiscoveryUrls;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfDiscoveryUrls, &arr, sizeof(SOPC_String),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_String_WriteAux);
    }

    return status;
}

/*============================================================================
 * OpcUa_ApplicationDescription_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_ApplicationDescription_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_ApplicationDescription* a_pValue = (OpcUa_ApplicationDescription*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_ApplicationDescription_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Read(&a_pValue->ApplicationUri, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Read(&a_pValue->ProductUri, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Read(&a_pValue->ApplicationName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_EnumeratedType(buf, (int32_t*) &a_pValue->ApplicationType);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Read(&a_pValue->GatewayServerUri, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Read(&a_pValue->DiscoveryProfileUri, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfDiscoveryUrls, (void**) &a_pValue->DiscoveryUrls,
                                 sizeof(SOPC_String), (SOPC_EncodeableObject_PfnDecode*) SOPC_String_ReadAux,
                                 (SOPC_EncodeableObject_PfnInitialize*) SOPC_String_InitializeAux,
                                 (SOPC_EncodeableObject_PfnClear*) SOPC_String_ClearAux);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_ApplicationDescription_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_RequestHeader
/*============================================================================
 * OpcUa_RequestHeader_Initialize
 *===========================================================================*/
void OpcUa_RequestHeader_Initialize(void* pValue)
{
    OpcUa_RequestHeader* a_pValue = (OpcUa_RequestHeader*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_RequestHeader_EncodeableType;
        SOPC_NodeId_Initialize(&a_pValue->AuthenticationToken);
        SOPC_DateTime_Initialize(&a_pValue->Timestamp);
        SOPC_UInt32_Initialize(&a_pValue->RequestHandle);
        SOPC_UInt32_Initialize(&a_pValue->ReturnDiagnostics);
        SOPC_String_Initialize(&a_pValue->AuditEntryId);
        SOPC_UInt32_Initialize(&a_pValue->TimeoutHint);
        SOPC_ExtensionObject_Initialize(&a_pValue->AdditionalHeader);
    }
}

/*============================================================================
 * OpcUa_RequestHeader_Clear
 *===========================================================================*/
void OpcUa_RequestHeader_Clear(void* pValue)
{
    OpcUa_RequestHeader* a_pValue = (OpcUa_RequestHeader*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_NodeId_Clear(&a_pValue->AuthenticationToken);
        SOPC_DateTime_Clear(&a_pValue->Timestamp);
        SOPC_UInt32_Clear(&a_pValue->RequestHandle);
        SOPC_UInt32_Clear(&a_pValue->ReturnDiagnostics);
        SOPC_String_Clear(&a_pValue->AuditEntryId);
        SOPC_UInt32_Clear(&a_pValue->TimeoutHint);
        SOPC_ExtensionObject_Clear(&a_pValue->AdditionalHeader);
    }
}

/*============================================================================
 * OpcUa_RequestHeader_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_RequestHeader_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_RequestHeader* a_pValue = (const OpcUa_RequestHeader*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Write(&a_pValue->AuthenticationToken, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_DateTime_Write(&a_pValue->Timestamp, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->RequestHandle, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->ReturnDiagnostics, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Write(&a_pValue->AuditEntryId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->TimeoutHint, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ExtensionObject_Write(&a_pValue->AdditionalHeader, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_RequestHeader_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_RequestHeader_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_RequestHeader* a_pValue = (OpcUa_RequestHeader*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_RequestHeader_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Read(&a_pValue->AuthenticationToken, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_DateTime_Read(&a_pValue->Timestamp, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->RequestHandle, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->ReturnDiagnostics, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Read(&a_pValue->AuditEntryId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->TimeoutHint, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ExtensionObject_Read(&a_pValue->AdditionalHeader, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_RequestHeader_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_ResponseHeader
/*============================================================================
 * OpcUa_ResponseHeader_Initialize
 *===========================================================================*/
void OpcUa_ResponseHeader_Initialize(void* pValue)
{
    OpcUa_ResponseHeader* a_pValue = (OpcUa_ResponseHeader*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_ResponseHeader_EncodeableType;
        SOPC_DateTime_Initialize(&a_pValue->Timestamp);
        SOPC_UInt32_Initialize(&a_pValue->RequestHandle);
        SOPC_StatusCode_Initialize(&a_pValue->ServiceResult);
        SOPC_DiagnosticInfo_Initialize(&a_pValue->ServiceDiagnostics);
        SOPC_Initialize_Array(&a_pValue->NoOfStringTable, (void**) &a_pValue->StringTable, sizeof(SOPC_String),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_String_InitializeAux);
        SOPC_ExtensionObject_Initialize(&a_pValue->AdditionalHeader);
    }
}

/*============================================================================
 * OpcUa_ResponseHeader_Clear
 *===========================================================================*/
void OpcUa_ResponseHeader_Clear(void* pValue)
{
    OpcUa_ResponseHeader* a_pValue = (OpcUa_ResponseHeader*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_DateTime_Clear(&a_pValue->Timestamp);
        SOPC_UInt32_Clear(&a_pValue->RequestHandle);
        SOPC_StatusCode_Clear(&a_pValue->ServiceResult);
        SOPC_DiagnosticInfo_Clear(&a_pValue->ServiceDiagnostics);
        SOPC_Clear_Array(&a_pValue->NoOfStringTable, (void**) &a_pValue->StringTable, sizeof(SOPC_String),
                         (SOPC_EncodeableObject_PfnClear*) SOPC_String_ClearAux);
        SOPC_ExtensionObject_Clear(&a_pValue->AdditionalHeader);
    }
}

/*============================================================================
 * OpcUa_ResponseHeader_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_ResponseHeader_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_ResponseHeader* a_pValue = (const OpcUa_ResponseHeader*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_DateTime_Write(&a_pValue->Timestamp, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->RequestHandle, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_StatusCode_Write(&a_pValue->ServiceResult, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_DiagnosticInfo_Write(&a_pValue->ServiceDiagnostics, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->StringTable;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfStringTable, &arr, sizeof(SOPC_String),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_String_WriteAux);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ExtensionObject_Write(&a_pValue->AdditionalHeader, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_ResponseHeader_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_ResponseHeader_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_ResponseHeader* a_pValue = (OpcUa_ResponseHeader*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_ResponseHeader_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_DateTime_Read(&a_pValue->Timestamp, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->RequestHandle, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_StatusCode_Read(&a_pValue->ServiceResult, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_DiagnosticInfo_Read(&a_pValue->ServiceDiagnostics, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfStringTable, (void**) &a_pValue->StringTable, sizeof(SOPC_String),
                                 (SOPC_EncodeableObject_PfnDecode*) SOPC_String_ReadAux,
                                 (SOPC_EncodeableObject_PfnInitialize*) SOPC_String_InitializeAux,
                                 (SOPC_EncodeableObject_PfnClear*) SOPC_String_ClearAux);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ExtensionObject_Read(&a_pValue->AdditionalHeader, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_ResponseHeader_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_ServiceFault
/*============================================================================
 * OpcUa_ServiceFault_Initialize
 *===========================================================================*/
void OpcUa_ServiceFault_Initialize(void* pValue)
{
    OpcUa_ServiceFault* a_pValue = (OpcUa_ServiceFault*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_ServiceFault_EncodeableType;
        OpcUa_ResponseHeader_Initialize(&a_pValue->ResponseHeader);
    }
}

/*============================================================================
 * OpcUa_ServiceFault_Clear
 *===========================================================================*/
void OpcUa_ServiceFault_Clear(void* pValue)
{
    OpcUa_ServiceFault* a_pValue = (OpcUa_ServiceFault*) pValue;
    if (a_pValue != NULL)
    {
        OpcUa_ResponseHeader_Clear(&a_pValue->ResponseHeader);
    }
}

/*============================================================================
 * OpcUa_ServiceFault_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_ServiceFault_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_ServiceFault* a_pValue = (const OpcUa_ServiceFault*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    return status;
}

/*============================================================================
 * OpcUa_ServiceFault_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_ServiceFault_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_ServiceFault* a_pValue = (OpcUa_ServiceFault*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_ServiceFault_Initialize(a_pValue);

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_ServiceFault_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_FindServers
#ifndef OPCUA_EXCLUDE_FindServersRequest
/*============================================================================
 * OpcUa_FindServersRequest_Initialize
 *===========================================================================*/
void OpcUa_FindServersRequest_Initialize(void* pValue)
{
    OpcUa_FindServersRequest* a_pValue = (OpcUa_FindServersRequest*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_FindServersRequest_EncodeableType;
        SOPC_String_Initialize(&a_pValue->EndpointUrl);
        SOPC_Initialize_Array(&a_pValue->NoOfLocaleIds, (void**) &a_pValue->LocaleIds, sizeof(SOPC_String),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_String_InitializeAux);
        SOPC_Initialize_Array(&a_pValue->NoOfServerUris, (void**) &a_pValue->ServerUris, sizeof(SOPC_String),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_String_InitializeAux);
    }
}

/*============================================================================
 * OpcUa_FindServersRequest_Clear
 *===========================================================================*/
void OpcUa_FindServersRequest_Clear(void* pValue)
{
    OpcUa_FindServersRequest* a_pValue = (OpcUa_FindServersRequest*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_String_Clear(&a_pValue->EndpointUrl);
        SOPC_Clear_Array(&a_pValue->NoOfLocaleIds, (void**) &a_pValue->LocaleIds, sizeof(SOPC_String),
                         (SOPC_EncodeableObject_PfnClear*) SOPC_String_ClearAux);
        SOPC_Clear_Array(&a_pValue->NoOfServerUris, (void**) &a_pValue->ServerUris, sizeof(SOPC_String),
                         (SOPC_EncodeableObject_PfnClear*) SOPC_String_ClearAux);
    }
}

/*============================================================================
 * OpcUa_FindServersRequest_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_FindServersRequest_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_FindServersRequest* a_pValue = (const OpcUa_FindServersRequest*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Write(&a_pValue->EndpointUrl, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->LocaleIds;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfLocaleIds, &arr, sizeof(SOPC_String),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_String_WriteAux);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->ServerUris;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfServerUris, &arr, sizeof(SOPC_String),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_String_WriteAux);
    }

    return status;
}

/*============================================================================
 * OpcUa_FindServersRequest_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_FindServersRequest_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_FindServersRequest* a_pValue = (OpcUa_FindServersRequest*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_FindServersRequest_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Read(&a_pValue->EndpointUrl, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfLocaleIds, (void**) &a_pValue->LocaleIds, sizeof(SOPC_String),
                                 (SOPC_EncodeableObject_PfnDecode*) SOPC_String_ReadAux,
                                 (SOPC_EncodeableObject_PfnInitialize*) SOPC_String_InitializeAux,
                                 (SOPC_EncodeableObject_PfnClear*) SOPC_String_ClearAux);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfServerUris, (void**) &a_pValue->ServerUris, sizeof(SOPC_String),
                                 (SOPC_EncodeableObject_PfnDecode*) SOPC_String_ReadAux,
                                 (SOPC_EncodeableObject_PfnInitialize*) SOPC_String_InitializeAux,
                                 (SOPC_EncodeableObject_PfnClear*) SOPC_String_ClearAux);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_FindServersRequest_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_FindServersResponse
/*============================================================================
 * OpcUa_FindServersResponse_Initialize
 *===========================================================================*/
void OpcUa_FindServersResponse_Initialize(void* pValue)
{
    OpcUa_FindServersResponse* a_pValue = (OpcUa_FindServersResponse*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_FindServersResponse_EncodeableType;
        OpcUa_ResponseHeader_Initialize(&a_pValue->ResponseHeader);
        SOPC_Initialize_Array(&a_pValue->NoOfServers, (void**) &a_pValue->Servers, sizeof(OpcUa_ApplicationDescription),
                              (SOPC_EncodeableObject_PfnInitialize*) OpcUa_ApplicationDescription_Initialize);
    }
}

/*============================================================================
 * OpcUa_FindServersResponse_Clear
 *===========================================================================*/
void OpcUa_FindServersResponse_Clear(void* pValue)
{
    OpcUa_FindServersResponse* a_pValue = (OpcUa_FindServersResponse*) pValue;
    if (a_pValue != NULL)
    {
        OpcUa_ResponseHeader_Clear(&a_pValue->ResponseHeader);
        SOPC_Clear_Array(&a_pValue->NoOfServers, (void**) &a_pValue->Servers, sizeof(OpcUa_ApplicationDescription),
                         (SOPC_EncodeableObject_PfnClear*) OpcUa_ApplicationDescription_Clear);
    }
}

/*============================================================================
 * OpcUa_FindServersResponse_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_FindServersResponse_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_FindServersResponse* a_pValue = (const OpcUa_FindServersResponse*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->Servers;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfServers, &arr, sizeof(OpcUa_ApplicationDescription),
                                  (SOPC_EncodeableObject_PfnEncode*) OpcUa_ApplicationDescription_Encode);
    }

    return status;
}

/*============================================================================
 * OpcUa_FindServersResponse_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_FindServersResponse_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_FindServersResponse* a_pValue = (OpcUa_FindServersResponse*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_FindServersResponse_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfServers, (void**) &a_pValue->Servers,
                                 sizeof(OpcUa_ApplicationDescription),
                                 (SOPC_EncodeableObject_PfnDecode*) OpcUa_ApplicationDescription_Decode,
                                 (SOPC_EncodeableObject_PfnInitialize*) OpcUa_ApplicationDescription_Initialize,
                                 (SOPC_EncodeableObject_PfnClear*) OpcUa_ApplicationDescription_Clear);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_FindServersResponse_Clear(a_pValue);
    }

    return status;
}
#endif
#endif

#ifndef OPCUA_EXCLUDE_ServerOnNetwork
/*============================================================================
 * OpcUa_ServerOnNetwork_Initialize
 *===========================================================================*/
void OpcUa_ServerOnNetwork_Initialize(void* pValue)
{
    OpcUa_ServerOnNetwork* a_pValue = (OpcUa_ServerOnNetwork*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_ServerOnNetwork_EncodeableType;
        SOPC_UInt32_Initialize(&a_pValue->RecordId);
        SOPC_String_Initialize(&a_pValue->ServerName);
        SOPC_String_Initialize(&a_pValue->DiscoveryUrl);
        SOPC_Initialize_Array(&a_pValue->NoOfServerCapabilities, (void**) &a_pValue->ServerCapabilities,
                              sizeof(SOPC_String), (SOPC_EncodeableObject_PfnInitialize*) SOPC_String_InitializeAux);
    }
}

/*============================================================================
 * OpcUa_ServerOnNetwork_Clear
 *===========================================================================*/
void OpcUa_ServerOnNetwork_Clear(void* pValue)
{
    OpcUa_ServerOnNetwork* a_pValue = (OpcUa_ServerOnNetwork*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_UInt32_Clear(&a_pValue->RecordId);
        SOPC_String_Clear(&a_pValue->ServerName);
        SOPC_String_Clear(&a_pValue->DiscoveryUrl);
        SOPC_Clear_Array(&a_pValue->NoOfServerCapabilities, (void**) &a_pValue->ServerCapabilities, sizeof(SOPC_String),
                         (SOPC_EncodeableObject_PfnClear*) SOPC_String_ClearAux);
    }
}

/*============================================================================
 * OpcUa_ServerOnNetwork_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_ServerOnNetwork_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_ServerOnNetwork* a_pValue = (const OpcUa_ServerOnNetwork*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->RecordId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Write(&a_pValue->ServerName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Write(&a_pValue->DiscoveryUrl, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->ServerCapabilities;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfServerCapabilities, &arr, sizeof(SOPC_String),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_String_WriteAux);
    }

    return status;
}

/*============================================================================
 * OpcUa_ServerOnNetwork_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_ServerOnNetwork_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_ServerOnNetwork* a_pValue = (OpcUa_ServerOnNetwork*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_ServerOnNetwork_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->RecordId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Read(&a_pValue->ServerName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Read(&a_pValue->DiscoveryUrl, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfServerCapabilities, (void**) &a_pValue->ServerCapabilities,
                                 sizeof(SOPC_String), (SOPC_EncodeableObject_PfnDecode*) SOPC_String_ReadAux,
                                 (SOPC_EncodeableObject_PfnInitialize*) SOPC_String_InitializeAux,
                                 (SOPC_EncodeableObject_PfnClear*) SOPC_String_ClearAux);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_ServerOnNetwork_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_FindServersOnNetwork
#ifndef OPCUA_EXCLUDE_FindServersOnNetworkRequest
/*============================================================================
 * OpcUa_FindServersOnNetworkRequest_Initialize
 *===========================================================================*/
void OpcUa_FindServersOnNetworkRequest_Initialize(void* pValue)
{
    OpcUa_FindServersOnNetworkRequest* a_pValue = (OpcUa_FindServersOnNetworkRequest*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_FindServersOnNetworkRequest_EncodeableType;
        SOPC_UInt32_Initialize(&a_pValue->StartingRecordId);
        SOPC_UInt32_Initialize(&a_pValue->MaxRecordsToReturn);
        SOPC_Initialize_Array(&a_pValue->NoOfServerCapabilityFilter, (void**) &a_pValue->ServerCapabilityFilter,
                              sizeof(SOPC_String), (SOPC_EncodeableObject_PfnInitialize*) SOPC_String_InitializeAux);
    }
}

/*============================================================================
 * OpcUa_FindServersOnNetworkRequest_Clear
 *===========================================================================*/
void OpcUa_FindServersOnNetworkRequest_Clear(void* pValue)
{
    OpcUa_FindServersOnNetworkRequest* a_pValue = (OpcUa_FindServersOnNetworkRequest*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_UInt32_Clear(&a_pValue->StartingRecordId);
        SOPC_UInt32_Clear(&a_pValue->MaxRecordsToReturn);
        SOPC_Clear_Array(&a_pValue->NoOfServerCapabilityFilter, (void**) &a_pValue->ServerCapabilityFilter,
                         sizeof(SOPC_String), (SOPC_EncodeableObject_PfnClear*) SOPC_String_ClearAux);
    }
}

/*============================================================================
 * OpcUa_FindServersOnNetworkRequest_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_FindServersOnNetworkRequest_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_FindServersOnNetworkRequest* a_pValue = (const OpcUa_FindServersOnNetworkRequest*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->StartingRecordId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->MaxRecordsToReturn, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->ServerCapabilityFilter;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfServerCapabilityFilter, &arr, sizeof(SOPC_String),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_String_WriteAux);
    }

    return status;
}

/*============================================================================
 * OpcUa_FindServersOnNetworkRequest_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_FindServersOnNetworkRequest_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_FindServersOnNetworkRequest* a_pValue = (OpcUa_FindServersOnNetworkRequest*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_FindServersOnNetworkRequest_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->StartingRecordId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->MaxRecordsToReturn, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfServerCapabilityFilter, (void**) &a_pValue->ServerCapabilityFilter,
                                 sizeof(SOPC_String), (SOPC_EncodeableObject_PfnDecode*) SOPC_String_ReadAux,
                                 (SOPC_EncodeableObject_PfnInitialize*) SOPC_String_InitializeAux,
                                 (SOPC_EncodeableObject_PfnClear*) SOPC_String_ClearAux);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_FindServersOnNetworkRequest_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_FindServersOnNetworkResponse
/*============================================================================
 * OpcUa_FindServersOnNetworkResponse_Initialize
 *===========================================================================*/
void OpcUa_FindServersOnNetworkResponse_Initialize(void* pValue)
{
    OpcUa_FindServersOnNetworkResponse* a_pValue = (OpcUa_FindServersOnNetworkResponse*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_FindServersOnNetworkResponse_EncodeableType;
        OpcUa_ResponseHeader_Initialize(&a_pValue->ResponseHeader);
        SOPC_DateTime_Initialize(&a_pValue->LastCounterResetTime);
        SOPC_Initialize_Array(&a_pValue->NoOfServers, (void**) &a_pValue->Servers, sizeof(OpcUa_ServerOnNetwork),
                              (SOPC_EncodeableObject_PfnInitialize*) OpcUa_ServerOnNetwork_Initialize);
    }
}

/*============================================================================
 * OpcUa_FindServersOnNetworkResponse_Clear
 *===========================================================================*/
void OpcUa_FindServersOnNetworkResponse_Clear(void* pValue)
{
    OpcUa_FindServersOnNetworkResponse* a_pValue = (OpcUa_FindServersOnNetworkResponse*) pValue;
    if (a_pValue != NULL)
    {
        OpcUa_ResponseHeader_Clear(&a_pValue->ResponseHeader);
        SOPC_DateTime_Clear(&a_pValue->LastCounterResetTime);
        SOPC_Clear_Array(&a_pValue->NoOfServers, (void**) &a_pValue->Servers, sizeof(OpcUa_ServerOnNetwork),
                         (SOPC_EncodeableObject_PfnClear*) OpcUa_ServerOnNetwork_Clear);
    }
}

/*============================================================================
 * OpcUa_FindServersOnNetworkResponse_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_FindServersOnNetworkResponse_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_FindServersOnNetworkResponse* a_pValue = (const OpcUa_FindServersOnNetworkResponse*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_DateTime_Write(&a_pValue->LastCounterResetTime, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->Servers;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfServers, &arr, sizeof(OpcUa_ServerOnNetwork),
                                  (SOPC_EncodeableObject_PfnEncode*) OpcUa_ServerOnNetwork_Encode);
    }

    return status;
}

/*============================================================================
 * OpcUa_FindServersOnNetworkResponse_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_FindServersOnNetworkResponse_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_FindServersOnNetworkResponse* a_pValue = (OpcUa_FindServersOnNetworkResponse*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_FindServersOnNetworkResponse_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_DateTime_Read(&a_pValue->LastCounterResetTime, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status =
            SOPC_Read_Array(buf, &a_pValue->NoOfServers, (void**) &a_pValue->Servers, sizeof(OpcUa_ServerOnNetwork),
                            (SOPC_EncodeableObject_PfnDecode*) OpcUa_ServerOnNetwork_Decode,
                            (SOPC_EncodeableObject_PfnInitialize*) OpcUa_ServerOnNetwork_Initialize,
                            (SOPC_EncodeableObject_PfnClear*) OpcUa_ServerOnNetwork_Clear);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_FindServersOnNetworkResponse_Clear(a_pValue);
    }

    return status;
}
#endif
#endif

#ifndef OPCUA_EXCLUDE_UserTokenPolicy
/*============================================================================
 * OpcUa_UserTokenPolicy_Initialize
 *===========================================================================*/
void OpcUa_UserTokenPolicy_Initialize(void* pValue)
{
    OpcUa_UserTokenPolicy* a_pValue = (OpcUa_UserTokenPolicy*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_UserTokenPolicy_EncodeableType;
        SOPC_String_Initialize(&a_pValue->PolicyId);
        SOPC_Initialize_EnumeratedType((int32_t*) &a_pValue->TokenType);
        SOPC_String_Initialize(&a_pValue->IssuedTokenType);
        SOPC_String_Initialize(&a_pValue->IssuerEndpointUrl);
        SOPC_String_Initialize(&a_pValue->SecurityPolicyUri);
    }
}

/*============================================================================
 * OpcUa_UserTokenPolicy_Clear
 *===========================================================================*/
void OpcUa_UserTokenPolicy_Clear(void* pValue)
{
    OpcUa_UserTokenPolicy* a_pValue = (OpcUa_UserTokenPolicy*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_String_Clear(&a_pValue->PolicyId);
        SOPC_Clear_EnumeratedType((int32_t*) &a_pValue->TokenType);
        SOPC_String_Clear(&a_pValue->IssuedTokenType);
        SOPC_String_Clear(&a_pValue->IssuerEndpointUrl);
        SOPC_String_Clear(&a_pValue->SecurityPolicyUri);
    }
}

/*============================================================================
 * OpcUa_UserTokenPolicy_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_UserTokenPolicy_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_UserTokenPolicy* a_pValue = (const OpcUa_UserTokenPolicy*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Write(&a_pValue->PolicyId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Write_EnumeratedType(buf, (const int32_t*) &a_pValue->TokenType);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Write(&a_pValue->IssuedTokenType, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Write(&a_pValue->IssuerEndpointUrl, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Write(&a_pValue->SecurityPolicyUri, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_UserTokenPolicy_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_UserTokenPolicy_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_UserTokenPolicy* a_pValue = (OpcUa_UserTokenPolicy*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_UserTokenPolicy_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Read(&a_pValue->PolicyId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_EnumeratedType(buf, (int32_t*) &a_pValue->TokenType);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Read(&a_pValue->IssuedTokenType, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Read(&a_pValue->IssuerEndpointUrl, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Read(&a_pValue->SecurityPolicyUri, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_UserTokenPolicy_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_EndpointDescription
/*============================================================================
 * OpcUa_EndpointDescription_Initialize
 *===========================================================================*/
void OpcUa_EndpointDescription_Initialize(void* pValue)
{
    OpcUa_EndpointDescription* a_pValue = (OpcUa_EndpointDescription*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_EndpointDescription_EncodeableType;
        SOPC_String_Initialize(&a_pValue->EndpointUrl);
        OpcUa_ApplicationDescription_Initialize(&a_pValue->Server);
        SOPC_ByteString_Initialize(&a_pValue->ServerCertificate);
        SOPC_Initialize_EnumeratedType((int32_t*) &a_pValue->SecurityMode);
        SOPC_String_Initialize(&a_pValue->SecurityPolicyUri);
        SOPC_Initialize_Array(&a_pValue->NoOfUserIdentityTokens, (void**) &a_pValue->UserIdentityTokens,
                              sizeof(OpcUa_UserTokenPolicy),
                              (SOPC_EncodeableObject_PfnInitialize*) OpcUa_UserTokenPolicy_Initialize);
        SOPC_String_Initialize(&a_pValue->TransportProfileUri);
        SOPC_Byte_Initialize(&a_pValue->SecurityLevel);
    }
}

/*============================================================================
 * OpcUa_EndpointDescription_Clear
 *===========================================================================*/
void OpcUa_EndpointDescription_Clear(void* pValue)
{
    OpcUa_EndpointDescription* a_pValue = (OpcUa_EndpointDescription*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_String_Clear(&a_pValue->EndpointUrl);
        OpcUa_ApplicationDescription_Clear(&a_pValue->Server);
        SOPC_ByteString_Clear(&a_pValue->ServerCertificate);
        SOPC_Clear_EnumeratedType((int32_t*) &a_pValue->SecurityMode);
        SOPC_String_Clear(&a_pValue->SecurityPolicyUri);
        SOPC_Clear_Array(&a_pValue->NoOfUserIdentityTokens, (void**) &a_pValue->UserIdentityTokens,
                         sizeof(OpcUa_UserTokenPolicy), (SOPC_EncodeableObject_PfnClear*) OpcUa_UserTokenPolicy_Clear);
        SOPC_String_Clear(&a_pValue->TransportProfileUri);
        SOPC_Byte_Clear(&a_pValue->SecurityLevel);
    }
}

/*============================================================================
 * OpcUa_EndpointDescription_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_EndpointDescription_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_EndpointDescription* a_pValue = (const OpcUa_EndpointDescription*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Write(&a_pValue->EndpointUrl, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_ApplicationDescription_Encode(&a_pValue->Server, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ByteString_Write(&a_pValue->ServerCertificate, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Write_EnumeratedType(buf, (const int32_t*) &a_pValue->SecurityMode);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Write(&a_pValue->SecurityPolicyUri, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->UserIdentityTokens;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfUserIdentityTokens, &arr, sizeof(OpcUa_UserTokenPolicy),
                                  (SOPC_EncodeableObject_PfnEncode*) OpcUa_UserTokenPolicy_Encode);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Write(&a_pValue->TransportProfileUri, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Byte_Write(&a_pValue->SecurityLevel, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_EndpointDescription_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_EndpointDescription_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_EndpointDescription* a_pValue = (OpcUa_EndpointDescription*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_EndpointDescription_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Read(&a_pValue->EndpointUrl, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_ApplicationDescription_Decode(&a_pValue->Server, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ByteString_Read(&a_pValue->ServerCertificate, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_EnumeratedType(buf, (int32_t*) &a_pValue->SecurityMode);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Read(&a_pValue->SecurityPolicyUri, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfUserIdentityTokens, (void**) &a_pValue->UserIdentityTokens,
                                 sizeof(OpcUa_UserTokenPolicy),
                                 (SOPC_EncodeableObject_PfnDecode*) OpcUa_UserTokenPolicy_Decode,
                                 (SOPC_EncodeableObject_PfnInitialize*) OpcUa_UserTokenPolicy_Initialize,
                                 (SOPC_EncodeableObject_PfnClear*) OpcUa_UserTokenPolicy_Clear);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Read(&a_pValue->TransportProfileUri, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Byte_Read(&a_pValue->SecurityLevel, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_EndpointDescription_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_GetEndpoints
#ifndef OPCUA_EXCLUDE_GetEndpointsRequest
/*============================================================================
 * OpcUa_GetEndpointsRequest_Initialize
 *===========================================================================*/
void OpcUa_GetEndpointsRequest_Initialize(void* pValue)
{
    OpcUa_GetEndpointsRequest* a_pValue = (OpcUa_GetEndpointsRequest*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_GetEndpointsRequest_EncodeableType;
        SOPC_String_Initialize(&a_pValue->EndpointUrl);
        SOPC_Initialize_Array(&a_pValue->NoOfLocaleIds, (void**) &a_pValue->LocaleIds, sizeof(SOPC_String),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_String_InitializeAux);
        SOPC_Initialize_Array(&a_pValue->NoOfProfileUris, (void**) &a_pValue->ProfileUris, sizeof(SOPC_String),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_String_InitializeAux);
    }
}

/*============================================================================
 * OpcUa_GetEndpointsRequest_Clear
 *===========================================================================*/
void OpcUa_GetEndpointsRequest_Clear(void* pValue)
{
    OpcUa_GetEndpointsRequest* a_pValue = (OpcUa_GetEndpointsRequest*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_String_Clear(&a_pValue->EndpointUrl);
        SOPC_Clear_Array(&a_pValue->NoOfLocaleIds, (void**) &a_pValue->LocaleIds, sizeof(SOPC_String),
                         (SOPC_EncodeableObject_PfnClear*) SOPC_String_ClearAux);
        SOPC_Clear_Array(&a_pValue->NoOfProfileUris, (void**) &a_pValue->ProfileUris, sizeof(SOPC_String),
                         (SOPC_EncodeableObject_PfnClear*) SOPC_String_ClearAux);
    }
}

/*============================================================================
 * OpcUa_GetEndpointsRequest_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_GetEndpointsRequest_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_GetEndpointsRequest* a_pValue = (const OpcUa_GetEndpointsRequest*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Write(&a_pValue->EndpointUrl, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->LocaleIds;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfLocaleIds, &arr, sizeof(SOPC_String),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_String_WriteAux);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->ProfileUris;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfProfileUris, &arr, sizeof(SOPC_String),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_String_WriteAux);
    }

    return status;
}

/*============================================================================
 * OpcUa_GetEndpointsRequest_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_GetEndpointsRequest_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_GetEndpointsRequest* a_pValue = (OpcUa_GetEndpointsRequest*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_GetEndpointsRequest_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Read(&a_pValue->EndpointUrl, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfLocaleIds, (void**) &a_pValue->LocaleIds, sizeof(SOPC_String),
                                 (SOPC_EncodeableObject_PfnDecode*) SOPC_String_ReadAux,
                                 (SOPC_EncodeableObject_PfnInitialize*) SOPC_String_InitializeAux,
                                 (SOPC_EncodeableObject_PfnClear*) SOPC_String_ClearAux);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfProfileUris, (void**) &a_pValue->ProfileUris, sizeof(SOPC_String),
                                 (SOPC_EncodeableObject_PfnDecode*) SOPC_String_ReadAux,
                                 (SOPC_EncodeableObject_PfnInitialize*) SOPC_String_InitializeAux,
                                 (SOPC_EncodeableObject_PfnClear*) SOPC_String_ClearAux);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_GetEndpointsRequest_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_GetEndpointsResponse
/*============================================================================
 * OpcUa_GetEndpointsResponse_Initialize
 *===========================================================================*/
void OpcUa_GetEndpointsResponse_Initialize(void* pValue)
{
    OpcUa_GetEndpointsResponse* a_pValue = (OpcUa_GetEndpointsResponse*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_GetEndpointsResponse_EncodeableType;
        OpcUa_ResponseHeader_Initialize(&a_pValue->ResponseHeader);
        SOPC_Initialize_Array(&a_pValue->NoOfEndpoints, (void**) &a_pValue->Endpoints,
                              sizeof(OpcUa_EndpointDescription),
                              (SOPC_EncodeableObject_PfnInitialize*) OpcUa_EndpointDescription_Initialize);
    }
}

/*============================================================================
 * OpcUa_GetEndpointsResponse_Clear
 *===========================================================================*/
void OpcUa_GetEndpointsResponse_Clear(void* pValue)
{
    OpcUa_GetEndpointsResponse* a_pValue = (OpcUa_GetEndpointsResponse*) pValue;
    if (a_pValue != NULL)
    {
        OpcUa_ResponseHeader_Clear(&a_pValue->ResponseHeader);
        SOPC_Clear_Array(&a_pValue->NoOfEndpoints, (void**) &a_pValue->Endpoints, sizeof(OpcUa_EndpointDescription),
                         (SOPC_EncodeableObject_PfnClear*) OpcUa_EndpointDescription_Clear);
    }
}

/*============================================================================
 * OpcUa_GetEndpointsResponse_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_GetEndpointsResponse_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_GetEndpointsResponse* a_pValue = (const OpcUa_GetEndpointsResponse*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->Endpoints;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfEndpoints, &arr, sizeof(OpcUa_EndpointDescription),
                                  (SOPC_EncodeableObject_PfnEncode*) OpcUa_EndpointDescription_Encode);
    }

    return status;
}

/*============================================================================
 * OpcUa_GetEndpointsResponse_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_GetEndpointsResponse_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_GetEndpointsResponse* a_pValue = (OpcUa_GetEndpointsResponse*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_GetEndpointsResponse_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfEndpoints, (void**) &a_pValue->Endpoints,
                                 sizeof(OpcUa_EndpointDescription),
                                 (SOPC_EncodeableObject_PfnDecode*) OpcUa_EndpointDescription_Decode,
                                 (SOPC_EncodeableObject_PfnInitialize*) OpcUa_EndpointDescription_Initialize,
                                 (SOPC_EncodeableObject_PfnClear*) OpcUa_EndpointDescription_Clear);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_GetEndpointsResponse_Clear(a_pValue);
    }

    return status;
}
#endif
#endif

#ifndef OPCUA_EXCLUDE_RegisteredServer
/*============================================================================
 * OpcUa_RegisteredServer_Initialize
 *===========================================================================*/
void OpcUa_RegisteredServer_Initialize(void* pValue)
{
    OpcUa_RegisteredServer* a_pValue = (OpcUa_RegisteredServer*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_RegisteredServer_EncodeableType;
        SOPC_String_Initialize(&a_pValue->ServerUri);
        SOPC_String_Initialize(&a_pValue->ProductUri);
        SOPC_Initialize_Array(&a_pValue->NoOfServerNames, (void**) &a_pValue->ServerNames, sizeof(SOPC_LocalizedText),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_LocalizedText_InitializeAux);
        SOPC_Initialize_EnumeratedType((int32_t*) &a_pValue->ServerType);
        SOPC_String_Initialize(&a_pValue->GatewayServerUri);
        SOPC_Initialize_Array(&a_pValue->NoOfDiscoveryUrls, (void**) &a_pValue->DiscoveryUrls, sizeof(SOPC_String),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_String_InitializeAux);
        SOPC_String_Initialize(&a_pValue->SemaphoreFilePath);
        SOPC_Boolean_Initialize(&a_pValue->IsOnline);
    }
}

/*============================================================================
 * OpcUa_RegisteredServer_Clear
 *===========================================================================*/
void OpcUa_RegisteredServer_Clear(void* pValue)
{
    OpcUa_RegisteredServer* a_pValue = (OpcUa_RegisteredServer*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_String_Clear(&a_pValue->ServerUri);
        SOPC_String_Clear(&a_pValue->ProductUri);
        SOPC_Clear_Array(&a_pValue->NoOfServerNames, (void**) &a_pValue->ServerNames, sizeof(SOPC_LocalizedText),
                         (SOPC_EncodeableObject_PfnClear*) SOPC_LocalizedText_ClearAux);
        SOPC_Clear_EnumeratedType((int32_t*) &a_pValue->ServerType);
        SOPC_String_Clear(&a_pValue->GatewayServerUri);
        SOPC_Clear_Array(&a_pValue->NoOfDiscoveryUrls, (void**) &a_pValue->DiscoveryUrls, sizeof(SOPC_String),
                         (SOPC_EncodeableObject_PfnClear*) SOPC_String_ClearAux);
        SOPC_String_Clear(&a_pValue->SemaphoreFilePath);
        SOPC_Boolean_Clear(&a_pValue->IsOnline);
    }
}

/*============================================================================
 * OpcUa_RegisteredServer_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_RegisteredServer_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_RegisteredServer* a_pValue = (const OpcUa_RegisteredServer*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Write(&a_pValue->ServerUri, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Write(&a_pValue->ProductUri, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->ServerNames;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfServerNames, &arr, sizeof(SOPC_LocalizedText),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_LocalizedText_WriteAux);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Write_EnumeratedType(buf, (const int32_t*) &a_pValue->ServerType);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Write(&a_pValue->GatewayServerUri, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->DiscoveryUrls;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfDiscoveryUrls, &arr, sizeof(SOPC_String),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_String_WriteAux);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Write(&a_pValue->SemaphoreFilePath, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Write(&a_pValue->IsOnline, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_RegisteredServer_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_RegisteredServer_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_RegisteredServer* a_pValue = (OpcUa_RegisteredServer*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_RegisteredServer_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Read(&a_pValue->ServerUri, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Read(&a_pValue->ProductUri, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status =
            SOPC_Read_Array(buf, &a_pValue->NoOfServerNames, (void**) &a_pValue->ServerNames,
                            sizeof(SOPC_LocalizedText), (SOPC_EncodeableObject_PfnDecode*) SOPC_LocalizedText_ReadAux,
                            (SOPC_EncodeableObject_PfnInitialize*) SOPC_LocalizedText_InitializeAux,
                            (SOPC_EncodeableObject_PfnClear*) SOPC_LocalizedText_ClearAux);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_EnumeratedType(buf, (int32_t*) &a_pValue->ServerType);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Read(&a_pValue->GatewayServerUri, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfDiscoveryUrls, (void**) &a_pValue->DiscoveryUrls,
                                 sizeof(SOPC_String), (SOPC_EncodeableObject_PfnDecode*) SOPC_String_ReadAux,
                                 (SOPC_EncodeableObject_PfnInitialize*) SOPC_String_InitializeAux,
                                 (SOPC_EncodeableObject_PfnClear*) SOPC_String_ClearAux);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Read(&a_pValue->SemaphoreFilePath, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Read(&a_pValue->IsOnline, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_RegisteredServer_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_RegisterServer
#ifndef OPCUA_EXCLUDE_RegisterServerRequest
/*============================================================================
 * OpcUa_RegisterServerRequest_Initialize
 *===========================================================================*/
void OpcUa_RegisterServerRequest_Initialize(void* pValue)
{
    OpcUa_RegisterServerRequest* a_pValue = (OpcUa_RegisterServerRequest*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_RegisterServerRequest_EncodeableType;
        OpcUa_RegisteredServer_Initialize(&a_pValue->Server);
    }
}

/*============================================================================
 * OpcUa_RegisterServerRequest_Clear
 *===========================================================================*/
void OpcUa_RegisterServerRequest_Clear(void* pValue)
{
    OpcUa_RegisterServerRequest* a_pValue = (OpcUa_RegisterServerRequest*) pValue;
    if (a_pValue != NULL)
    {
        OpcUa_RegisteredServer_Clear(&a_pValue->Server);
    }
}

/*============================================================================
 * OpcUa_RegisterServerRequest_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_RegisterServerRequest_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_RegisterServerRequest* a_pValue = (const OpcUa_RegisterServerRequest*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_RegisteredServer_Encode(&a_pValue->Server, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_RegisterServerRequest_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_RegisterServerRequest_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_RegisterServerRequest* a_pValue = (OpcUa_RegisterServerRequest*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_RegisterServerRequest_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_RegisteredServer_Decode(&a_pValue->Server, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_RegisterServerRequest_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_RegisterServerResponse
/*============================================================================
 * OpcUa_RegisterServerResponse_Initialize
 *===========================================================================*/
void OpcUa_RegisterServerResponse_Initialize(void* pValue)
{
    OpcUa_RegisterServerResponse* a_pValue = (OpcUa_RegisterServerResponse*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_RegisterServerResponse_EncodeableType;
        OpcUa_ResponseHeader_Initialize(&a_pValue->ResponseHeader);
    }
}

/*============================================================================
 * OpcUa_RegisterServerResponse_Clear
 *===========================================================================*/
void OpcUa_RegisterServerResponse_Clear(void* pValue)
{
    OpcUa_RegisterServerResponse* a_pValue = (OpcUa_RegisterServerResponse*) pValue;
    if (a_pValue != NULL)
    {
        OpcUa_ResponseHeader_Clear(&a_pValue->ResponseHeader);
    }
}

/*============================================================================
 * OpcUa_RegisterServerResponse_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_RegisterServerResponse_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_RegisterServerResponse* a_pValue = (const OpcUa_RegisterServerResponse*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    return status;
}

/*============================================================================
 * OpcUa_RegisterServerResponse_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_RegisterServerResponse_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_RegisterServerResponse* a_pValue = (OpcUa_RegisterServerResponse*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_RegisterServerResponse_Initialize(a_pValue);

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_RegisterServerResponse_Clear(a_pValue);
    }

    return status;
}
#endif
#endif

#ifndef OPCUA_EXCLUDE_MdnsDiscoveryConfiguration
/*============================================================================
 * OpcUa_MdnsDiscoveryConfiguration_Initialize
 *===========================================================================*/
void OpcUa_MdnsDiscoveryConfiguration_Initialize(void* pValue)
{
    OpcUa_MdnsDiscoveryConfiguration* a_pValue = (OpcUa_MdnsDiscoveryConfiguration*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_MdnsDiscoveryConfiguration_EncodeableType;
        SOPC_String_Initialize(&a_pValue->MdnsServerName);
        SOPC_Initialize_Array(&a_pValue->NoOfServerCapabilities, (void**) &a_pValue->ServerCapabilities,
                              sizeof(SOPC_String), (SOPC_EncodeableObject_PfnInitialize*) SOPC_String_InitializeAux);
    }
}

/*============================================================================
 * OpcUa_MdnsDiscoveryConfiguration_Clear
 *===========================================================================*/
void OpcUa_MdnsDiscoveryConfiguration_Clear(void* pValue)
{
    OpcUa_MdnsDiscoveryConfiguration* a_pValue = (OpcUa_MdnsDiscoveryConfiguration*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_String_Clear(&a_pValue->MdnsServerName);
        SOPC_Clear_Array(&a_pValue->NoOfServerCapabilities, (void**) &a_pValue->ServerCapabilities, sizeof(SOPC_String),
                         (SOPC_EncodeableObject_PfnClear*) SOPC_String_ClearAux);
    }
}

/*============================================================================
 * OpcUa_MdnsDiscoveryConfiguration_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_MdnsDiscoveryConfiguration_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_MdnsDiscoveryConfiguration* a_pValue = (const OpcUa_MdnsDiscoveryConfiguration*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Write(&a_pValue->MdnsServerName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->ServerCapabilities;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfServerCapabilities, &arr, sizeof(SOPC_String),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_String_WriteAux);
    }

    return status;
}

/*============================================================================
 * OpcUa_MdnsDiscoveryConfiguration_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_MdnsDiscoveryConfiguration_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_MdnsDiscoveryConfiguration* a_pValue = (OpcUa_MdnsDiscoveryConfiguration*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_MdnsDiscoveryConfiguration_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Read(&a_pValue->MdnsServerName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfServerCapabilities, (void**) &a_pValue->ServerCapabilities,
                                 sizeof(SOPC_String), (SOPC_EncodeableObject_PfnDecode*) SOPC_String_ReadAux,
                                 (SOPC_EncodeableObject_PfnInitialize*) SOPC_String_InitializeAux,
                                 (SOPC_EncodeableObject_PfnClear*) SOPC_String_ClearAux);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_MdnsDiscoveryConfiguration_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_RegisterServer2
#ifndef OPCUA_EXCLUDE_RegisterServer2Request
/*============================================================================
 * OpcUa_RegisterServer2Request_Initialize
 *===========================================================================*/
void OpcUa_RegisterServer2Request_Initialize(void* pValue)
{
    OpcUa_RegisterServer2Request* a_pValue = (OpcUa_RegisterServer2Request*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_RegisterServer2Request_EncodeableType;
        OpcUa_RegisteredServer_Initialize(&a_pValue->Server);
        SOPC_Initialize_Array(&a_pValue->NoOfDiscoveryConfiguration, (void**) &a_pValue->DiscoveryConfiguration,
                              sizeof(SOPC_ExtensionObject),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_ExtensionObject_InitializeAux);
    }
}

/*============================================================================
 * OpcUa_RegisterServer2Request_Clear
 *===========================================================================*/
void OpcUa_RegisterServer2Request_Clear(void* pValue)
{
    OpcUa_RegisterServer2Request* a_pValue = (OpcUa_RegisterServer2Request*) pValue;
    if (a_pValue != NULL)
    {
        OpcUa_RegisteredServer_Clear(&a_pValue->Server);
        SOPC_Clear_Array(&a_pValue->NoOfDiscoveryConfiguration, (void**) &a_pValue->DiscoveryConfiguration,
                         sizeof(SOPC_ExtensionObject), (SOPC_EncodeableObject_PfnClear*) SOPC_ExtensionObject_ClearAux);
    }
}

/*============================================================================
 * OpcUa_RegisterServer2Request_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_RegisterServer2Request_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_RegisterServer2Request* a_pValue = (const OpcUa_RegisterServer2Request*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_RegisteredServer_Encode(&a_pValue->Server, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->DiscoveryConfiguration;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfDiscoveryConfiguration, &arr, sizeof(SOPC_ExtensionObject),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_ExtensionObject_WriteAux);
    }

    return status;
}

/*============================================================================
 * OpcUa_RegisterServer2Request_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_RegisterServer2Request_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_RegisterServer2Request* a_pValue = (OpcUa_RegisterServer2Request*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_RegisterServer2Request_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_RegisteredServer_Decode(&a_pValue->Server, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfDiscoveryConfiguration, (void**) &a_pValue->DiscoveryConfiguration,
                                 sizeof(SOPC_ExtensionObject),
                                 (SOPC_EncodeableObject_PfnDecode*) SOPC_ExtensionObject_ReadAux,
                                 (SOPC_EncodeableObject_PfnInitialize*) SOPC_ExtensionObject_InitializeAux,
                                 (SOPC_EncodeableObject_PfnClear*) SOPC_ExtensionObject_ClearAux);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_RegisterServer2Request_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_RegisterServer2Response
/*============================================================================
 * OpcUa_RegisterServer2Response_Initialize
 *===========================================================================*/
void OpcUa_RegisterServer2Response_Initialize(void* pValue)
{
    OpcUa_RegisterServer2Response* a_pValue = (OpcUa_RegisterServer2Response*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_RegisterServer2Response_EncodeableType;
        OpcUa_ResponseHeader_Initialize(&a_pValue->ResponseHeader);
        SOPC_Initialize_Array(&a_pValue->NoOfConfigurationResults, (void**) &a_pValue->ConfigurationResults,
                              sizeof(SOPC_StatusCode),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_StatusCode_InitializeAux);
        SOPC_Initialize_Array(&a_pValue->NoOfDiagnosticInfos, (void**) &a_pValue->DiagnosticInfos,
                              sizeof(SOPC_DiagnosticInfo),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_DiagnosticInfo_InitializeAux);
    }
}

/*============================================================================
 * OpcUa_RegisterServer2Response_Clear
 *===========================================================================*/
void OpcUa_RegisterServer2Response_Clear(void* pValue)
{
    OpcUa_RegisterServer2Response* a_pValue = (OpcUa_RegisterServer2Response*) pValue;
    if (a_pValue != NULL)
    {
        OpcUa_ResponseHeader_Clear(&a_pValue->ResponseHeader);
        SOPC_Clear_Array(&a_pValue->NoOfConfigurationResults, (void**) &a_pValue->ConfigurationResults,
                         sizeof(SOPC_StatusCode), (SOPC_EncodeableObject_PfnClear*) SOPC_StatusCode_ClearAux);
        SOPC_Clear_Array(&a_pValue->NoOfDiagnosticInfos, (void**) &a_pValue->DiagnosticInfos,
                         sizeof(SOPC_DiagnosticInfo), (SOPC_EncodeableObject_PfnClear*) SOPC_DiagnosticInfo_ClearAux);
    }
}

/*============================================================================
 * OpcUa_RegisterServer2Response_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_RegisterServer2Response_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_RegisterServer2Response* a_pValue = (const OpcUa_RegisterServer2Response*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->ConfigurationResults;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfConfigurationResults, &arr, sizeof(SOPC_StatusCode),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_StatusCode_WriteAux);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->DiagnosticInfos;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfDiagnosticInfos, &arr, sizeof(SOPC_DiagnosticInfo),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_DiagnosticInfo_WriteAux);
    }

    return status;
}

/*============================================================================
 * OpcUa_RegisterServer2Response_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_RegisterServer2Response_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_RegisterServer2Response* a_pValue = (OpcUa_RegisterServer2Response*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_RegisterServer2Response_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfConfigurationResults, (void**) &a_pValue->ConfigurationResults,
                                 sizeof(SOPC_StatusCode), (SOPC_EncodeableObject_PfnDecode*) SOPC_StatusCode_ReadAux,
                                 (SOPC_EncodeableObject_PfnInitialize*) SOPC_StatusCode_InitializeAux,
                                 (SOPC_EncodeableObject_PfnClear*) SOPC_StatusCode_ClearAux);
    }
    if (SOPC_STATUS_OK == status)
    {
        status =
            SOPC_Read_Array(buf, &a_pValue->NoOfDiagnosticInfos, (void**) &a_pValue->DiagnosticInfos,
                            sizeof(SOPC_DiagnosticInfo), (SOPC_EncodeableObject_PfnDecode*) SOPC_DiagnosticInfo_ReadAux,
                            (SOPC_EncodeableObject_PfnInitialize*) SOPC_DiagnosticInfo_InitializeAux,
                            (SOPC_EncodeableObject_PfnClear*) SOPC_DiagnosticInfo_ClearAux);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_RegisterServer2Response_Clear(a_pValue);
    }

    return status;
}
#endif
#endif

#ifndef OPCUA_EXCLUDE_ChannelSecurityToken
/*============================================================================
 * OpcUa_ChannelSecurityToken_Initialize
 *===========================================================================*/
void OpcUa_ChannelSecurityToken_Initialize(void* pValue)
{
    OpcUa_ChannelSecurityToken* a_pValue = (OpcUa_ChannelSecurityToken*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_ChannelSecurityToken_EncodeableType;
        SOPC_UInt32_Initialize(&a_pValue->ChannelId);
        SOPC_UInt32_Initialize(&a_pValue->TokenId);
        SOPC_DateTime_Initialize(&a_pValue->CreatedAt);
        SOPC_UInt32_Initialize(&a_pValue->RevisedLifetime);
    }
}

/*============================================================================
 * OpcUa_ChannelSecurityToken_Clear
 *===========================================================================*/
void OpcUa_ChannelSecurityToken_Clear(void* pValue)
{
    OpcUa_ChannelSecurityToken* a_pValue = (OpcUa_ChannelSecurityToken*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_UInt32_Clear(&a_pValue->ChannelId);
        SOPC_UInt32_Clear(&a_pValue->TokenId);
        SOPC_DateTime_Clear(&a_pValue->CreatedAt);
        SOPC_UInt32_Clear(&a_pValue->RevisedLifetime);
    }
}

/*============================================================================
 * OpcUa_ChannelSecurityToken_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_ChannelSecurityToken_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_ChannelSecurityToken* a_pValue = (const OpcUa_ChannelSecurityToken*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->ChannelId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->TokenId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_DateTime_Write(&a_pValue->CreatedAt, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->RevisedLifetime, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_ChannelSecurityToken_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_ChannelSecurityToken_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_ChannelSecurityToken* a_pValue = (OpcUa_ChannelSecurityToken*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_ChannelSecurityToken_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->ChannelId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->TokenId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_DateTime_Read(&a_pValue->CreatedAt, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->RevisedLifetime, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_ChannelSecurityToken_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_OpenSecureChannel
#ifndef OPCUA_EXCLUDE_OpenSecureChannelRequest
/*============================================================================
 * OpcUa_OpenSecureChannelRequest_Initialize
 *===========================================================================*/
void OpcUa_OpenSecureChannelRequest_Initialize(void* pValue)
{
    OpcUa_OpenSecureChannelRequest* a_pValue = (OpcUa_OpenSecureChannelRequest*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_OpenSecureChannelRequest_EncodeableType;
        SOPC_UInt32_Initialize(&a_pValue->ClientProtocolVersion);
        SOPC_Initialize_EnumeratedType((int32_t*) &a_pValue->RequestType);
        SOPC_Initialize_EnumeratedType((int32_t*) &a_pValue->SecurityMode);
        SOPC_ByteString_Initialize(&a_pValue->ClientNonce);
        SOPC_UInt32_Initialize(&a_pValue->RequestedLifetime);
    }
}

/*============================================================================
 * OpcUa_OpenSecureChannelRequest_Clear
 *===========================================================================*/
void OpcUa_OpenSecureChannelRequest_Clear(void* pValue)
{
    OpcUa_OpenSecureChannelRequest* a_pValue = (OpcUa_OpenSecureChannelRequest*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_UInt32_Clear(&a_pValue->ClientProtocolVersion);
        SOPC_Clear_EnumeratedType((int32_t*) &a_pValue->RequestType);
        SOPC_Clear_EnumeratedType((int32_t*) &a_pValue->SecurityMode);
        SOPC_ByteString_Clear(&a_pValue->ClientNonce);
        SOPC_UInt32_Clear(&a_pValue->RequestedLifetime);
    }
}

/*============================================================================
 * OpcUa_OpenSecureChannelRequest_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_OpenSecureChannelRequest_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_OpenSecureChannelRequest* a_pValue = (const OpcUa_OpenSecureChannelRequest*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->ClientProtocolVersion, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Write_EnumeratedType(buf, (const int32_t*) &a_pValue->RequestType);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Write_EnumeratedType(buf, (const int32_t*) &a_pValue->SecurityMode);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ByteString_Write(&a_pValue->ClientNonce, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->RequestedLifetime, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_OpenSecureChannelRequest_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_OpenSecureChannelRequest_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_OpenSecureChannelRequest* a_pValue = (OpcUa_OpenSecureChannelRequest*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_OpenSecureChannelRequest_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->ClientProtocolVersion, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_EnumeratedType(buf, (int32_t*) &a_pValue->RequestType);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_EnumeratedType(buf, (int32_t*) &a_pValue->SecurityMode);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ByteString_Read(&a_pValue->ClientNonce, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->RequestedLifetime, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_OpenSecureChannelRequest_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_OpenSecureChannelResponse
/*============================================================================
 * OpcUa_OpenSecureChannelResponse_Initialize
 *===========================================================================*/
void OpcUa_OpenSecureChannelResponse_Initialize(void* pValue)
{
    OpcUa_OpenSecureChannelResponse* a_pValue = (OpcUa_OpenSecureChannelResponse*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_OpenSecureChannelResponse_EncodeableType;
        OpcUa_ResponseHeader_Initialize(&a_pValue->ResponseHeader);
        SOPC_UInt32_Initialize(&a_pValue->ServerProtocolVersion);
        OpcUa_ChannelSecurityToken_Initialize(&a_pValue->SecurityToken);
        SOPC_ByteString_Initialize(&a_pValue->ServerNonce);
    }
}

/*============================================================================
 * OpcUa_OpenSecureChannelResponse_Clear
 *===========================================================================*/
void OpcUa_OpenSecureChannelResponse_Clear(void* pValue)
{
    OpcUa_OpenSecureChannelResponse* a_pValue = (OpcUa_OpenSecureChannelResponse*) pValue;
    if (a_pValue != NULL)
    {
        OpcUa_ResponseHeader_Clear(&a_pValue->ResponseHeader);
        SOPC_UInt32_Clear(&a_pValue->ServerProtocolVersion);
        OpcUa_ChannelSecurityToken_Clear(&a_pValue->SecurityToken);
        SOPC_ByteString_Clear(&a_pValue->ServerNonce);
    }
}

/*============================================================================
 * OpcUa_OpenSecureChannelResponse_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_OpenSecureChannelResponse_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_OpenSecureChannelResponse* a_pValue = (const OpcUa_OpenSecureChannelResponse*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->ServerProtocolVersion, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_ChannelSecurityToken_Encode(&a_pValue->SecurityToken, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ByteString_Write(&a_pValue->ServerNonce, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_OpenSecureChannelResponse_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_OpenSecureChannelResponse_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_OpenSecureChannelResponse* a_pValue = (OpcUa_OpenSecureChannelResponse*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_OpenSecureChannelResponse_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->ServerProtocolVersion, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_ChannelSecurityToken_Decode(&a_pValue->SecurityToken, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ByteString_Read(&a_pValue->ServerNonce, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_OpenSecureChannelResponse_Clear(a_pValue);
    }

    return status;
}
#endif
#endif

#ifndef OPCUA_EXCLUDE_CloseSecureChannel
#ifndef OPCUA_EXCLUDE_CloseSecureChannelRequest
/*============================================================================
 * OpcUa_CloseSecureChannelRequest_Initialize
 *===========================================================================*/
void OpcUa_CloseSecureChannelRequest_Initialize(void* pValue)
{
    OpcUa_CloseSecureChannelRequest* a_pValue = (OpcUa_CloseSecureChannelRequest*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_CloseSecureChannelRequest_EncodeableType;
    }
}

/*============================================================================
 * OpcUa_CloseSecureChannelRequest_Clear
 *===========================================================================*/
void OpcUa_CloseSecureChannelRequest_Clear(void* pValue)
{
    OpcUa_CloseSecureChannelRequest* a_pValue = (OpcUa_CloseSecureChannelRequest*) pValue;
    if (a_pValue != NULL)
    {
    }
}

/*============================================================================
 * OpcUa_CloseSecureChannelRequest_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_CloseSecureChannelRequest_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_CloseSecureChannelRequest* a_pValue = (const OpcUa_CloseSecureChannelRequest*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    return status;
}

/*============================================================================
 * OpcUa_CloseSecureChannelRequest_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_CloseSecureChannelRequest_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_CloseSecureChannelRequest* a_pValue = (OpcUa_CloseSecureChannelRequest*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_CloseSecureChannelRequest_Initialize(a_pValue);

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_CloseSecureChannelRequest_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_CloseSecureChannelResponse
/*============================================================================
 * OpcUa_CloseSecureChannelResponse_Initialize
 *===========================================================================*/
void OpcUa_CloseSecureChannelResponse_Initialize(void* pValue)
{
    OpcUa_CloseSecureChannelResponse* a_pValue = (OpcUa_CloseSecureChannelResponse*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_CloseSecureChannelResponse_EncodeableType;
        OpcUa_ResponseHeader_Initialize(&a_pValue->ResponseHeader);
    }
}

/*============================================================================
 * OpcUa_CloseSecureChannelResponse_Clear
 *===========================================================================*/
void OpcUa_CloseSecureChannelResponse_Clear(void* pValue)
{
    OpcUa_CloseSecureChannelResponse* a_pValue = (OpcUa_CloseSecureChannelResponse*) pValue;
    if (a_pValue != NULL)
    {
        OpcUa_ResponseHeader_Clear(&a_pValue->ResponseHeader);
    }
}

/*============================================================================
 * OpcUa_CloseSecureChannelResponse_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_CloseSecureChannelResponse_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_CloseSecureChannelResponse* a_pValue = (const OpcUa_CloseSecureChannelResponse*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    return status;
}

/*============================================================================
 * OpcUa_CloseSecureChannelResponse_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_CloseSecureChannelResponse_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_CloseSecureChannelResponse* a_pValue = (OpcUa_CloseSecureChannelResponse*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_CloseSecureChannelResponse_Initialize(a_pValue);

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_CloseSecureChannelResponse_Clear(a_pValue);
    }

    return status;
}
#endif
#endif

#ifndef OPCUA_EXCLUDE_SignedSoftwareCertificate
/*============================================================================
 * OpcUa_SignedSoftwareCertificate_Initialize
 *===========================================================================*/
void OpcUa_SignedSoftwareCertificate_Initialize(void* pValue)
{
    OpcUa_SignedSoftwareCertificate* a_pValue = (OpcUa_SignedSoftwareCertificate*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_SignedSoftwareCertificate_EncodeableType;
        SOPC_ByteString_Initialize(&a_pValue->CertificateData);
        SOPC_ByteString_Initialize(&a_pValue->Signature);
    }
}

/*============================================================================
 * OpcUa_SignedSoftwareCertificate_Clear
 *===========================================================================*/
void OpcUa_SignedSoftwareCertificate_Clear(void* pValue)
{
    OpcUa_SignedSoftwareCertificate* a_pValue = (OpcUa_SignedSoftwareCertificate*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_ByteString_Clear(&a_pValue->CertificateData);
        SOPC_ByteString_Clear(&a_pValue->Signature);
    }
}

/*============================================================================
 * OpcUa_SignedSoftwareCertificate_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_SignedSoftwareCertificate_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_SignedSoftwareCertificate* a_pValue = (const OpcUa_SignedSoftwareCertificate*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ByteString_Write(&a_pValue->CertificateData, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ByteString_Write(&a_pValue->Signature, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_SignedSoftwareCertificate_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_SignedSoftwareCertificate_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_SignedSoftwareCertificate* a_pValue = (OpcUa_SignedSoftwareCertificate*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_SignedSoftwareCertificate_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ByteString_Read(&a_pValue->CertificateData, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ByteString_Read(&a_pValue->Signature, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_SignedSoftwareCertificate_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_SignatureData
/*============================================================================
 * OpcUa_SignatureData_Initialize
 *===========================================================================*/
void OpcUa_SignatureData_Initialize(void* pValue)
{
    OpcUa_SignatureData* a_pValue = (OpcUa_SignatureData*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_SignatureData_EncodeableType;
        SOPC_String_Initialize(&a_pValue->Algorithm);
        SOPC_ByteString_Initialize(&a_pValue->Signature);
    }
}

/*============================================================================
 * OpcUa_SignatureData_Clear
 *===========================================================================*/
void OpcUa_SignatureData_Clear(void* pValue)
{
    OpcUa_SignatureData* a_pValue = (OpcUa_SignatureData*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_String_Clear(&a_pValue->Algorithm);
        SOPC_ByteString_Clear(&a_pValue->Signature);
    }
}

/*============================================================================
 * OpcUa_SignatureData_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_SignatureData_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_SignatureData* a_pValue = (const OpcUa_SignatureData*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Write(&a_pValue->Algorithm, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ByteString_Write(&a_pValue->Signature, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_SignatureData_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_SignatureData_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_SignatureData* a_pValue = (OpcUa_SignatureData*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_SignatureData_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Read(&a_pValue->Algorithm, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ByteString_Read(&a_pValue->Signature, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_SignatureData_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_CreateSession
#ifndef OPCUA_EXCLUDE_CreateSessionRequest
/*============================================================================
 * OpcUa_CreateSessionRequest_Initialize
 *===========================================================================*/
void OpcUa_CreateSessionRequest_Initialize(void* pValue)
{
    OpcUa_CreateSessionRequest* a_pValue = (OpcUa_CreateSessionRequest*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_CreateSessionRequest_EncodeableType;
        OpcUa_ApplicationDescription_Initialize(&a_pValue->ClientDescription);
        SOPC_String_Initialize(&a_pValue->ServerUri);
        SOPC_String_Initialize(&a_pValue->EndpointUrl);
        SOPC_String_Initialize(&a_pValue->SessionName);
        SOPC_ByteString_Initialize(&a_pValue->ClientNonce);
        SOPC_ByteString_Initialize(&a_pValue->ClientCertificate);
        SOPC_Double_Initialize(&a_pValue->RequestedSessionTimeout);
        SOPC_UInt32_Initialize(&a_pValue->MaxResponseMessageSize);
    }
}

/*============================================================================
 * OpcUa_CreateSessionRequest_Clear
 *===========================================================================*/
void OpcUa_CreateSessionRequest_Clear(void* pValue)
{
    OpcUa_CreateSessionRequest* a_pValue = (OpcUa_CreateSessionRequest*) pValue;
    if (a_pValue != NULL)
    {
        OpcUa_ApplicationDescription_Clear(&a_pValue->ClientDescription);
        SOPC_String_Clear(&a_pValue->ServerUri);
        SOPC_String_Clear(&a_pValue->EndpointUrl);
        SOPC_String_Clear(&a_pValue->SessionName);
        SOPC_ByteString_Clear(&a_pValue->ClientNonce);
        SOPC_ByteString_Clear(&a_pValue->ClientCertificate);
        SOPC_Double_Clear(&a_pValue->RequestedSessionTimeout);
        SOPC_UInt32_Clear(&a_pValue->MaxResponseMessageSize);
    }
}

/*============================================================================
 * OpcUa_CreateSessionRequest_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_CreateSessionRequest_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_CreateSessionRequest* a_pValue = (const OpcUa_CreateSessionRequest*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_ApplicationDescription_Encode(&a_pValue->ClientDescription, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Write(&a_pValue->ServerUri, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Write(&a_pValue->EndpointUrl, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Write(&a_pValue->SessionName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ByteString_Write(&a_pValue->ClientNonce, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ByteString_Write(&a_pValue->ClientCertificate, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Double_Write(&a_pValue->RequestedSessionTimeout, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->MaxResponseMessageSize, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_CreateSessionRequest_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_CreateSessionRequest_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_CreateSessionRequest* a_pValue = (OpcUa_CreateSessionRequest*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_CreateSessionRequest_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_ApplicationDescription_Decode(&a_pValue->ClientDescription, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Read(&a_pValue->ServerUri, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Read(&a_pValue->EndpointUrl, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Read(&a_pValue->SessionName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ByteString_Read(&a_pValue->ClientNonce, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ByteString_Read(&a_pValue->ClientCertificate, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Double_Read(&a_pValue->RequestedSessionTimeout, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->MaxResponseMessageSize, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_CreateSessionRequest_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_CreateSessionResponse
/*============================================================================
 * OpcUa_CreateSessionResponse_Initialize
 *===========================================================================*/
void OpcUa_CreateSessionResponse_Initialize(void* pValue)
{
    OpcUa_CreateSessionResponse* a_pValue = (OpcUa_CreateSessionResponse*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_CreateSessionResponse_EncodeableType;
        OpcUa_ResponseHeader_Initialize(&a_pValue->ResponseHeader);
        SOPC_NodeId_Initialize(&a_pValue->SessionId);
        SOPC_NodeId_Initialize(&a_pValue->AuthenticationToken);
        SOPC_Double_Initialize(&a_pValue->RevisedSessionTimeout);
        SOPC_ByteString_Initialize(&a_pValue->ServerNonce);
        SOPC_ByteString_Initialize(&a_pValue->ServerCertificate);
        SOPC_Initialize_Array(&a_pValue->NoOfServerEndpoints, (void**) &a_pValue->ServerEndpoints,
                              sizeof(OpcUa_EndpointDescription),
                              (SOPC_EncodeableObject_PfnInitialize*) OpcUa_EndpointDescription_Initialize);
        SOPC_Initialize_Array(&a_pValue->NoOfServerSoftwareCertificates, (void**) &a_pValue->ServerSoftwareCertificates,
                              sizeof(OpcUa_SignedSoftwareCertificate),
                              (SOPC_EncodeableObject_PfnInitialize*) OpcUa_SignedSoftwareCertificate_Initialize);
        OpcUa_SignatureData_Initialize(&a_pValue->ServerSignature);
        SOPC_UInt32_Initialize(&a_pValue->MaxRequestMessageSize);
    }
}

/*============================================================================
 * OpcUa_CreateSessionResponse_Clear
 *===========================================================================*/
void OpcUa_CreateSessionResponse_Clear(void* pValue)
{
    OpcUa_CreateSessionResponse* a_pValue = (OpcUa_CreateSessionResponse*) pValue;
    if (a_pValue != NULL)
    {
        OpcUa_ResponseHeader_Clear(&a_pValue->ResponseHeader);
        SOPC_NodeId_Clear(&a_pValue->SessionId);
        SOPC_NodeId_Clear(&a_pValue->AuthenticationToken);
        SOPC_Double_Clear(&a_pValue->RevisedSessionTimeout);
        SOPC_ByteString_Clear(&a_pValue->ServerNonce);
        SOPC_ByteString_Clear(&a_pValue->ServerCertificate);
        SOPC_Clear_Array(&a_pValue->NoOfServerEndpoints, (void**) &a_pValue->ServerEndpoints,
                         sizeof(OpcUa_EndpointDescription),
                         (SOPC_EncodeableObject_PfnClear*) OpcUa_EndpointDescription_Clear);
        SOPC_Clear_Array(&a_pValue->NoOfServerSoftwareCertificates, (void**) &a_pValue->ServerSoftwareCertificates,
                         sizeof(OpcUa_SignedSoftwareCertificate),
                         (SOPC_EncodeableObject_PfnClear*) OpcUa_SignedSoftwareCertificate_Clear);
        OpcUa_SignatureData_Clear(&a_pValue->ServerSignature);
        SOPC_UInt32_Clear(&a_pValue->MaxRequestMessageSize);
    }
}

/*============================================================================
 * OpcUa_CreateSessionResponse_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_CreateSessionResponse_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_CreateSessionResponse* a_pValue = (const OpcUa_CreateSessionResponse*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Write(&a_pValue->SessionId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Write(&a_pValue->AuthenticationToken, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Double_Write(&a_pValue->RevisedSessionTimeout, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ByteString_Write(&a_pValue->ServerNonce, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ByteString_Write(&a_pValue->ServerCertificate, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->ServerEndpoints;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfServerEndpoints, &arr, sizeof(OpcUa_EndpointDescription),
                                  (SOPC_EncodeableObject_PfnEncode*) OpcUa_EndpointDescription_Encode);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->ServerSoftwareCertificates;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfServerSoftwareCertificates, &arr,
                                  sizeof(OpcUa_SignedSoftwareCertificate),
                                  (SOPC_EncodeableObject_PfnEncode*) OpcUa_SignedSoftwareCertificate_Encode);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_SignatureData_Encode(&a_pValue->ServerSignature, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->MaxRequestMessageSize, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_CreateSessionResponse_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_CreateSessionResponse_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_CreateSessionResponse* a_pValue = (OpcUa_CreateSessionResponse*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_CreateSessionResponse_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Read(&a_pValue->SessionId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Read(&a_pValue->AuthenticationToken, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Double_Read(&a_pValue->RevisedSessionTimeout, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ByteString_Read(&a_pValue->ServerNonce, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ByteString_Read(&a_pValue->ServerCertificate, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfServerEndpoints, (void**) &a_pValue->ServerEndpoints,
                                 sizeof(OpcUa_EndpointDescription),
                                 (SOPC_EncodeableObject_PfnDecode*) OpcUa_EndpointDescription_Decode,
                                 (SOPC_EncodeableObject_PfnInitialize*) OpcUa_EndpointDescription_Initialize,
                                 (SOPC_EncodeableObject_PfnClear*) OpcUa_EndpointDescription_Clear);
    }
    if (SOPC_STATUS_OK == status)
    {
        status =
            SOPC_Read_Array(buf, &a_pValue->NoOfServerSoftwareCertificates,
                            (void**) &a_pValue->ServerSoftwareCertificates, sizeof(OpcUa_SignedSoftwareCertificate),
                            (SOPC_EncodeableObject_PfnDecode*) OpcUa_SignedSoftwareCertificate_Decode,
                            (SOPC_EncodeableObject_PfnInitialize*) OpcUa_SignedSoftwareCertificate_Initialize,
                            (SOPC_EncodeableObject_PfnClear*) OpcUa_SignedSoftwareCertificate_Clear);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_SignatureData_Decode(&a_pValue->ServerSignature, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->MaxRequestMessageSize, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_CreateSessionResponse_Clear(a_pValue);
    }

    return status;
}
#endif
#endif

#ifndef OPCUA_EXCLUDE_UserIdentityToken
/*============================================================================
 * OpcUa_UserIdentityToken_Initialize
 *===========================================================================*/
void OpcUa_UserIdentityToken_Initialize(void* pValue)
{
    OpcUa_UserIdentityToken* a_pValue = (OpcUa_UserIdentityToken*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_UserIdentityToken_EncodeableType;
        SOPC_String_Initialize(&a_pValue->PolicyId);
    }
}

/*============================================================================
 * OpcUa_UserIdentityToken_Clear
 *===========================================================================*/
void OpcUa_UserIdentityToken_Clear(void* pValue)
{
    OpcUa_UserIdentityToken* a_pValue = (OpcUa_UserIdentityToken*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_String_Clear(&a_pValue->PolicyId);
    }
}

/*============================================================================
 * OpcUa_UserIdentityToken_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_UserIdentityToken_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_UserIdentityToken* a_pValue = (const OpcUa_UserIdentityToken*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Write(&a_pValue->PolicyId, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_UserIdentityToken_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_UserIdentityToken_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_UserIdentityToken* a_pValue = (OpcUa_UserIdentityToken*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_UserIdentityToken_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Read(&a_pValue->PolicyId, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_UserIdentityToken_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_AnonymousIdentityToken
/*============================================================================
 * OpcUa_AnonymousIdentityToken_Initialize
 *===========================================================================*/
void OpcUa_AnonymousIdentityToken_Initialize(void* pValue)
{
    OpcUa_AnonymousIdentityToken* a_pValue = (OpcUa_AnonymousIdentityToken*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_AnonymousIdentityToken_EncodeableType;
        SOPC_String_Initialize(&a_pValue->PolicyId);
    }
}

/*============================================================================
 * OpcUa_AnonymousIdentityToken_Clear
 *===========================================================================*/
void OpcUa_AnonymousIdentityToken_Clear(void* pValue)
{
    OpcUa_AnonymousIdentityToken* a_pValue = (OpcUa_AnonymousIdentityToken*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_String_Clear(&a_pValue->PolicyId);
    }
}

/*============================================================================
 * OpcUa_AnonymousIdentityToken_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_AnonymousIdentityToken_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_AnonymousIdentityToken* a_pValue = (const OpcUa_AnonymousIdentityToken*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Write(&a_pValue->PolicyId, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_AnonymousIdentityToken_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_AnonymousIdentityToken_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_AnonymousIdentityToken* a_pValue = (OpcUa_AnonymousIdentityToken*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_AnonymousIdentityToken_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Read(&a_pValue->PolicyId, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_AnonymousIdentityToken_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_UserNameIdentityToken
/*============================================================================
 * OpcUa_UserNameIdentityToken_Initialize
 *===========================================================================*/
void OpcUa_UserNameIdentityToken_Initialize(void* pValue)
{
    OpcUa_UserNameIdentityToken* a_pValue = (OpcUa_UserNameIdentityToken*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_UserNameIdentityToken_EncodeableType;
        SOPC_String_Initialize(&a_pValue->PolicyId);
        SOPC_String_Initialize(&a_pValue->UserName);
        SOPC_ByteString_Initialize(&a_pValue->Password);
        SOPC_String_Initialize(&a_pValue->EncryptionAlgorithm);
    }
}

/*============================================================================
 * OpcUa_UserNameIdentityToken_Clear
 *===========================================================================*/
void OpcUa_UserNameIdentityToken_Clear(void* pValue)
{
    OpcUa_UserNameIdentityToken* a_pValue = (OpcUa_UserNameIdentityToken*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_String_Clear(&a_pValue->PolicyId);
        SOPC_String_Clear(&a_pValue->UserName);
        SOPC_ByteString_Clear(&a_pValue->Password);
        SOPC_String_Clear(&a_pValue->EncryptionAlgorithm);
    }
}

/*============================================================================
 * OpcUa_UserNameIdentityToken_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_UserNameIdentityToken_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_UserNameIdentityToken* a_pValue = (const OpcUa_UserNameIdentityToken*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Write(&a_pValue->PolicyId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Write(&a_pValue->UserName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ByteString_Write(&a_pValue->Password, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Write(&a_pValue->EncryptionAlgorithm, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_UserNameIdentityToken_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_UserNameIdentityToken_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_UserNameIdentityToken* a_pValue = (OpcUa_UserNameIdentityToken*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_UserNameIdentityToken_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Read(&a_pValue->PolicyId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Read(&a_pValue->UserName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ByteString_Read(&a_pValue->Password, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Read(&a_pValue->EncryptionAlgorithm, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_UserNameIdentityToken_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_X509IdentityToken
/*============================================================================
 * OpcUa_X509IdentityToken_Initialize
 *===========================================================================*/
void OpcUa_X509IdentityToken_Initialize(void* pValue)
{
    OpcUa_X509IdentityToken* a_pValue = (OpcUa_X509IdentityToken*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_X509IdentityToken_EncodeableType;
        SOPC_String_Initialize(&a_pValue->PolicyId);
        SOPC_ByteString_Initialize(&a_pValue->CertificateData);
    }
}

/*============================================================================
 * OpcUa_X509IdentityToken_Clear
 *===========================================================================*/
void OpcUa_X509IdentityToken_Clear(void* pValue)
{
    OpcUa_X509IdentityToken* a_pValue = (OpcUa_X509IdentityToken*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_String_Clear(&a_pValue->PolicyId);
        SOPC_ByteString_Clear(&a_pValue->CertificateData);
    }
}

/*============================================================================
 * OpcUa_X509IdentityToken_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_X509IdentityToken_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_X509IdentityToken* a_pValue = (const OpcUa_X509IdentityToken*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Write(&a_pValue->PolicyId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ByteString_Write(&a_pValue->CertificateData, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_X509IdentityToken_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_X509IdentityToken_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_X509IdentityToken* a_pValue = (OpcUa_X509IdentityToken*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_X509IdentityToken_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Read(&a_pValue->PolicyId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ByteString_Read(&a_pValue->CertificateData, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_X509IdentityToken_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_KerberosIdentityToken
/*============================================================================
 * OpcUa_KerberosIdentityToken_Initialize
 *===========================================================================*/
void OpcUa_KerberosIdentityToken_Initialize(void* pValue)
{
    OpcUa_KerberosIdentityToken* a_pValue = (OpcUa_KerberosIdentityToken*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_KerberosIdentityToken_EncodeableType;
        SOPC_String_Initialize(&a_pValue->PolicyId);
        SOPC_ByteString_Initialize(&a_pValue->TicketData);
    }
}

/*============================================================================
 * OpcUa_KerberosIdentityToken_Clear
 *===========================================================================*/
void OpcUa_KerberosIdentityToken_Clear(void* pValue)
{
    OpcUa_KerberosIdentityToken* a_pValue = (OpcUa_KerberosIdentityToken*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_String_Clear(&a_pValue->PolicyId);
        SOPC_ByteString_Clear(&a_pValue->TicketData);
    }
}

/*============================================================================
 * OpcUa_KerberosIdentityToken_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_KerberosIdentityToken_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_KerberosIdentityToken* a_pValue = (const OpcUa_KerberosIdentityToken*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Write(&a_pValue->PolicyId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ByteString_Write(&a_pValue->TicketData, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_KerberosIdentityToken_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_KerberosIdentityToken_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_KerberosIdentityToken* a_pValue = (OpcUa_KerberosIdentityToken*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_KerberosIdentityToken_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Read(&a_pValue->PolicyId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ByteString_Read(&a_pValue->TicketData, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_KerberosIdentityToken_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_IssuedIdentityToken
/*============================================================================
 * OpcUa_IssuedIdentityToken_Initialize
 *===========================================================================*/
void OpcUa_IssuedIdentityToken_Initialize(void* pValue)
{
    OpcUa_IssuedIdentityToken* a_pValue = (OpcUa_IssuedIdentityToken*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_IssuedIdentityToken_EncodeableType;
        SOPC_String_Initialize(&a_pValue->PolicyId);
        SOPC_ByteString_Initialize(&a_pValue->TokenData);
        SOPC_String_Initialize(&a_pValue->EncryptionAlgorithm);
    }
}

/*============================================================================
 * OpcUa_IssuedIdentityToken_Clear
 *===========================================================================*/
void OpcUa_IssuedIdentityToken_Clear(void* pValue)
{
    OpcUa_IssuedIdentityToken* a_pValue = (OpcUa_IssuedIdentityToken*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_String_Clear(&a_pValue->PolicyId);
        SOPC_ByteString_Clear(&a_pValue->TokenData);
        SOPC_String_Clear(&a_pValue->EncryptionAlgorithm);
    }
}

/*============================================================================
 * OpcUa_IssuedIdentityToken_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_IssuedIdentityToken_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_IssuedIdentityToken* a_pValue = (const OpcUa_IssuedIdentityToken*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Write(&a_pValue->PolicyId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ByteString_Write(&a_pValue->TokenData, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Write(&a_pValue->EncryptionAlgorithm, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_IssuedIdentityToken_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_IssuedIdentityToken_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_IssuedIdentityToken* a_pValue = (OpcUa_IssuedIdentityToken*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_IssuedIdentityToken_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Read(&a_pValue->PolicyId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ByteString_Read(&a_pValue->TokenData, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Read(&a_pValue->EncryptionAlgorithm, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_IssuedIdentityToken_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_ActivateSession
#ifndef OPCUA_EXCLUDE_ActivateSessionRequest
/*============================================================================
 * OpcUa_ActivateSessionRequest_Initialize
 *===========================================================================*/
void OpcUa_ActivateSessionRequest_Initialize(void* pValue)
{
    OpcUa_ActivateSessionRequest* a_pValue = (OpcUa_ActivateSessionRequest*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_ActivateSessionRequest_EncodeableType;
        OpcUa_SignatureData_Initialize(&a_pValue->ClientSignature);
        SOPC_Initialize_Array(&a_pValue->NoOfClientSoftwareCertificates, (void**) &a_pValue->ClientSoftwareCertificates,
                              sizeof(OpcUa_SignedSoftwareCertificate),
                              (SOPC_EncodeableObject_PfnInitialize*) OpcUa_SignedSoftwareCertificate_Initialize);
        SOPC_Initialize_Array(&a_pValue->NoOfLocaleIds, (void**) &a_pValue->LocaleIds, sizeof(SOPC_String),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_String_InitializeAux);
        SOPC_ExtensionObject_Initialize(&a_pValue->UserIdentityToken);
        OpcUa_SignatureData_Initialize(&a_pValue->UserTokenSignature);
    }
}

/*============================================================================
 * OpcUa_ActivateSessionRequest_Clear
 *===========================================================================*/
void OpcUa_ActivateSessionRequest_Clear(void* pValue)
{
    OpcUa_ActivateSessionRequest* a_pValue = (OpcUa_ActivateSessionRequest*) pValue;
    if (a_pValue != NULL)
    {
        OpcUa_SignatureData_Clear(&a_pValue->ClientSignature);
        SOPC_Clear_Array(&a_pValue->NoOfClientSoftwareCertificates, (void**) &a_pValue->ClientSoftwareCertificates,
                         sizeof(OpcUa_SignedSoftwareCertificate),
                         (SOPC_EncodeableObject_PfnClear*) OpcUa_SignedSoftwareCertificate_Clear);
        SOPC_Clear_Array(&a_pValue->NoOfLocaleIds, (void**) &a_pValue->LocaleIds, sizeof(SOPC_String),
                         (SOPC_EncodeableObject_PfnClear*) SOPC_String_ClearAux);
        SOPC_ExtensionObject_Clear(&a_pValue->UserIdentityToken);
        OpcUa_SignatureData_Clear(&a_pValue->UserTokenSignature);
    }
}

/*============================================================================
 * OpcUa_ActivateSessionRequest_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_ActivateSessionRequest_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_ActivateSessionRequest* a_pValue = (const OpcUa_ActivateSessionRequest*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_SignatureData_Encode(&a_pValue->ClientSignature, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->ClientSoftwareCertificates;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfClientSoftwareCertificates, &arr,
                                  sizeof(OpcUa_SignedSoftwareCertificate),
                                  (SOPC_EncodeableObject_PfnEncode*) OpcUa_SignedSoftwareCertificate_Encode);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->LocaleIds;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfLocaleIds, &arr, sizeof(SOPC_String),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_String_WriteAux);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ExtensionObject_Write(&a_pValue->UserIdentityToken, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_SignatureData_Encode(&a_pValue->UserTokenSignature, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_ActivateSessionRequest_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_ActivateSessionRequest_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_ActivateSessionRequest* a_pValue = (OpcUa_ActivateSessionRequest*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_ActivateSessionRequest_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_SignatureData_Decode(&a_pValue->ClientSignature, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status =
            SOPC_Read_Array(buf, &a_pValue->NoOfClientSoftwareCertificates,
                            (void**) &a_pValue->ClientSoftwareCertificates, sizeof(OpcUa_SignedSoftwareCertificate),
                            (SOPC_EncodeableObject_PfnDecode*) OpcUa_SignedSoftwareCertificate_Decode,
                            (SOPC_EncodeableObject_PfnInitialize*) OpcUa_SignedSoftwareCertificate_Initialize,
                            (SOPC_EncodeableObject_PfnClear*) OpcUa_SignedSoftwareCertificate_Clear);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfLocaleIds, (void**) &a_pValue->LocaleIds, sizeof(SOPC_String),
                                 (SOPC_EncodeableObject_PfnDecode*) SOPC_String_ReadAux,
                                 (SOPC_EncodeableObject_PfnInitialize*) SOPC_String_InitializeAux,
                                 (SOPC_EncodeableObject_PfnClear*) SOPC_String_ClearAux);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ExtensionObject_Read(&a_pValue->UserIdentityToken, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_SignatureData_Decode(&a_pValue->UserTokenSignature, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_ActivateSessionRequest_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_ActivateSessionResponse
/*============================================================================
 * OpcUa_ActivateSessionResponse_Initialize
 *===========================================================================*/
void OpcUa_ActivateSessionResponse_Initialize(void* pValue)
{
    OpcUa_ActivateSessionResponse* a_pValue = (OpcUa_ActivateSessionResponse*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_ActivateSessionResponse_EncodeableType;
        OpcUa_ResponseHeader_Initialize(&a_pValue->ResponseHeader);
        SOPC_ByteString_Initialize(&a_pValue->ServerNonce);
        SOPC_Initialize_Array(&a_pValue->NoOfResults, (void**) &a_pValue->Results, sizeof(SOPC_StatusCode),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_StatusCode_InitializeAux);
        SOPC_Initialize_Array(&a_pValue->NoOfDiagnosticInfos, (void**) &a_pValue->DiagnosticInfos,
                              sizeof(SOPC_DiagnosticInfo),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_DiagnosticInfo_InitializeAux);
    }
}

/*============================================================================
 * OpcUa_ActivateSessionResponse_Clear
 *===========================================================================*/
void OpcUa_ActivateSessionResponse_Clear(void* pValue)
{
    OpcUa_ActivateSessionResponse* a_pValue = (OpcUa_ActivateSessionResponse*) pValue;
    if (a_pValue != NULL)
    {
        OpcUa_ResponseHeader_Clear(&a_pValue->ResponseHeader);
        SOPC_ByteString_Clear(&a_pValue->ServerNonce);
        SOPC_Clear_Array(&a_pValue->NoOfResults, (void**) &a_pValue->Results, sizeof(SOPC_StatusCode),
                         (SOPC_EncodeableObject_PfnClear*) SOPC_StatusCode_ClearAux);
        SOPC_Clear_Array(&a_pValue->NoOfDiagnosticInfos, (void**) &a_pValue->DiagnosticInfos,
                         sizeof(SOPC_DiagnosticInfo), (SOPC_EncodeableObject_PfnClear*) SOPC_DiagnosticInfo_ClearAux);
    }
}

/*============================================================================
 * OpcUa_ActivateSessionResponse_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_ActivateSessionResponse_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_ActivateSessionResponse* a_pValue = (const OpcUa_ActivateSessionResponse*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ByteString_Write(&a_pValue->ServerNonce, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->Results;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfResults, &arr, sizeof(SOPC_StatusCode),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_StatusCode_WriteAux);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->DiagnosticInfos;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfDiagnosticInfos, &arr, sizeof(SOPC_DiagnosticInfo),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_DiagnosticInfo_WriteAux);
    }

    return status;
}

/*============================================================================
 * OpcUa_ActivateSessionResponse_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_ActivateSessionResponse_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_ActivateSessionResponse* a_pValue = (OpcUa_ActivateSessionResponse*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_ActivateSessionResponse_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ByteString_Read(&a_pValue->ServerNonce, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfResults, (void**) &a_pValue->Results, sizeof(SOPC_StatusCode),
                                 (SOPC_EncodeableObject_PfnDecode*) SOPC_StatusCode_ReadAux,
                                 (SOPC_EncodeableObject_PfnInitialize*) SOPC_StatusCode_InitializeAux,
                                 (SOPC_EncodeableObject_PfnClear*) SOPC_StatusCode_ClearAux);
    }
    if (SOPC_STATUS_OK == status)
    {
        status =
            SOPC_Read_Array(buf, &a_pValue->NoOfDiagnosticInfos, (void**) &a_pValue->DiagnosticInfos,
                            sizeof(SOPC_DiagnosticInfo), (SOPC_EncodeableObject_PfnDecode*) SOPC_DiagnosticInfo_ReadAux,
                            (SOPC_EncodeableObject_PfnInitialize*) SOPC_DiagnosticInfo_InitializeAux,
                            (SOPC_EncodeableObject_PfnClear*) SOPC_DiagnosticInfo_ClearAux);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_ActivateSessionResponse_Clear(a_pValue);
    }

    return status;
}
#endif
#endif

#ifndef OPCUA_EXCLUDE_CloseSession
#ifndef OPCUA_EXCLUDE_CloseSessionRequest
/*============================================================================
 * OpcUa_CloseSessionRequest_Initialize
 *===========================================================================*/
void OpcUa_CloseSessionRequest_Initialize(void* pValue)
{
    OpcUa_CloseSessionRequest* a_pValue = (OpcUa_CloseSessionRequest*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_CloseSessionRequest_EncodeableType;
        SOPC_Boolean_Initialize(&a_pValue->DeleteSubscriptions);
    }
}

/*============================================================================
 * OpcUa_CloseSessionRequest_Clear
 *===========================================================================*/
void OpcUa_CloseSessionRequest_Clear(void* pValue)
{
    OpcUa_CloseSessionRequest* a_pValue = (OpcUa_CloseSessionRequest*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_Boolean_Clear(&a_pValue->DeleteSubscriptions);
    }
}

/*============================================================================
 * OpcUa_CloseSessionRequest_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_CloseSessionRequest_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_CloseSessionRequest* a_pValue = (const OpcUa_CloseSessionRequest*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Write(&a_pValue->DeleteSubscriptions, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_CloseSessionRequest_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_CloseSessionRequest_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_CloseSessionRequest* a_pValue = (OpcUa_CloseSessionRequest*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_CloseSessionRequest_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Read(&a_pValue->DeleteSubscriptions, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_CloseSessionRequest_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_CloseSessionResponse
/*============================================================================
 * OpcUa_CloseSessionResponse_Initialize
 *===========================================================================*/
void OpcUa_CloseSessionResponse_Initialize(void* pValue)
{
    OpcUa_CloseSessionResponse* a_pValue = (OpcUa_CloseSessionResponse*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_CloseSessionResponse_EncodeableType;
        OpcUa_ResponseHeader_Initialize(&a_pValue->ResponseHeader);
    }
}

/*============================================================================
 * OpcUa_CloseSessionResponse_Clear
 *===========================================================================*/
void OpcUa_CloseSessionResponse_Clear(void* pValue)
{
    OpcUa_CloseSessionResponse* a_pValue = (OpcUa_CloseSessionResponse*) pValue;
    if (a_pValue != NULL)
    {
        OpcUa_ResponseHeader_Clear(&a_pValue->ResponseHeader);
    }
}

/*============================================================================
 * OpcUa_CloseSessionResponse_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_CloseSessionResponse_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_CloseSessionResponse* a_pValue = (const OpcUa_CloseSessionResponse*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    return status;
}

/*============================================================================
 * OpcUa_CloseSessionResponse_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_CloseSessionResponse_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_CloseSessionResponse* a_pValue = (OpcUa_CloseSessionResponse*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_CloseSessionResponse_Initialize(a_pValue);

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_CloseSessionResponse_Clear(a_pValue);
    }

    return status;
}
#endif
#endif

#ifndef OPCUA_EXCLUDE_Cancel
#ifndef OPCUA_EXCLUDE_CancelRequest
/*============================================================================
 * OpcUa_CancelRequest_Initialize
 *===========================================================================*/
void OpcUa_CancelRequest_Initialize(void* pValue)
{
    OpcUa_CancelRequest* a_pValue = (OpcUa_CancelRequest*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_CancelRequest_EncodeableType;
        SOPC_UInt32_Initialize(&a_pValue->RequestHandle);
    }
}

/*============================================================================
 * OpcUa_CancelRequest_Clear
 *===========================================================================*/
void OpcUa_CancelRequest_Clear(void* pValue)
{
    OpcUa_CancelRequest* a_pValue = (OpcUa_CancelRequest*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_UInt32_Clear(&a_pValue->RequestHandle);
    }
}

/*============================================================================
 * OpcUa_CancelRequest_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_CancelRequest_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_CancelRequest* a_pValue = (const OpcUa_CancelRequest*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->RequestHandle, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_CancelRequest_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_CancelRequest_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_CancelRequest* a_pValue = (OpcUa_CancelRequest*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_CancelRequest_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->RequestHandle, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_CancelRequest_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_CancelResponse
/*============================================================================
 * OpcUa_CancelResponse_Initialize
 *===========================================================================*/
void OpcUa_CancelResponse_Initialize(void* pValue)
{
    OpcUa_CancelResponse* a_pValue = (OpcUa_CancelResponse*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_CancelResponse_EncodeableType;
        OpcUa_ResponseHeader_Initialize(&a_pValue->ResponseHeader);
        SOPC_UInt32_Initialize(&a_pValue->CancelCount);
    }
}

/*============================================================================
 * OpcUa_CancelResponse_Clear
 *===========================================================================*/
void OpcUa_CancelResponse_Clear(void* pValue)
{
    OpcUa_CancelResponse* a_pValue = (OpcUa_CancelResponse*) pValue;
    if (a_pValue != NULL)
    {
        OpcUa_ResponseHeader_Clear(&a_pValue->ResponseHeader);
        SOPC_UInt32_Clear(&a_pValue->CancelCount);
    }
}

/*============================================================================
 * OpcUa_CancelResponse_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_CancelResponse_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_CancelResponse* a_pValue = (const OpcUa_CancelResponse*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->CancelCount, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_CancelResponse_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_CancelResponse_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_CancelResponse* a_pValue = (OpcUa_CancelResponse*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_CancelResponse_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->CancelCount, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_CancelResponse_Clear(a_pValue);
    }

    return status;
}
#endif
#endif

#ifndef OPCUA_EXCLUDE_NodeAttributes
/*============================================================================
 * OpcUa_NodeAttributes_Initialize
 *===========================================================================*/
void OpcUa_NodeAttributes_Initialize(void* pValue)
{
    OpcUa_NodeAttributes* a_pValue = (OpcUa_NodeAttributes*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_NodeAttributes_EncodeableType;
        SOPC_UInt32_Initialize(&a_pValue->SpecifiedAttributes);
        SOPC_LocalizedText_Initialize(&a_pValue->DisplayName);
        SOPC_LocalizedText_Initialize(&a_pValue->Description);
        SOPC_UInt32_Initialize(&a_pValue->WriteMask);
        SOPC_UInt32_Initialize(&a_pValue->UserWriteMask);
    }
}

/*============================================================================
 * OpcUa_NodeAttributes_Clear
 *===========================================================================*/
void OpcUa_NodeAttributes_Clear(void* pValue)
{
    OpcUa_NodeAttributes* a_pValue = (OpcUa_NodeAttributes*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_UInt32_Clear(&a_pValue->SpecifiedAttributes);
        SOPC_LocalizedText_Clear(&a_pValue->DisplayName);
        SOPC_LocalizedText_Clear(&a_pValue->Description);
        SOPC_UInt32_Clear(&a_pValue->WriteMask);
        SOPC_UInt32_Clear(&a_pValue->UserWriteMask);
    }
}

/*============================================================================
 * OpcUa_NodeAttributes_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_NodeAttributes_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_NodeAttributes* a_pValue = (const OpcUa_NodeAttributes*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->SpecifiedAttributes, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Write(&a_pValue->DisplayName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Write(&a_pValue->Description, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->WriteMask, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->UserWriteMask, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_NodeAttributes_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_NodeAttributes_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_NodeAttributes* a_pValue = (OpcUa_NodeAttributes*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_NodeAttributes_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->SpecifiedAttributes, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Read(&a_pValue->DisplayName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Read(&a_pValue->Description, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->WriteMask, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->UserWriteMask, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_NodeAttributes_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_ObjectAttributes
/*============================================================================
 * OpcUa_ObjectAttributes_Initialize
 *===========================================================================*/
void OpcUa_ObjectAttributes_Initialize(void* pValue)
{
    OpcUa_ObjectAttributes* a_pValue = (OpcUa_ObjectAttributes*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_ObjectAttributes_EncodeableType;
        SOPC_UInt32_Initialize(&a_pValue->SpecifiedAttributes);
        SOPC_LocalizedText_Initialize(&a_pValue->DisplayName);
        SOPC_LocalizedText_Initialize(&a_pValue->Description);
        SOPC_UInt32_Initialize(&a_pValue->WriteMask);
        SOPC_UInt32_Initialize(&a_pValue->UserWriteMask);
        SOPC_Byte_Initialize(&a_pValue->EventNotifier);
    }
}

/*============================================================================
 * OpcUa_ObjectAttributes_Clear
 *===========================================================================*/
void OpcUa_ObjectAttributes_Clear(void* pValue)
{
    OpcUa_ObjectAttributes* a_pValue = (OpcUa_ObjectAttributes*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_UInt32_Clear(&a_pValue->SpecifiedAttributes);
        SOPC_LocalizedText_Clear(&a_pValue->DisplayName);
        SOPC_LocalizedText_Clear(&a_pValue->Description);
        SOPC_UInt32_Clear(&a_pValue->WriteMask);
        SOPC_UInt32_Clear(&a_pValue->UserWriteMask);
        SOPC_Byte_Clear(&a_pValue->EventNotifier);
    }
}

/*============================================================================
 * OpcUa_ObjectAttributes_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_ObjectAttributes_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_ObjectAttributes* a_pValue = (const OpcUa_ObjectAttributes*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->SpecifiedAttributes, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Write(&a_pValue->DisplayName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Write(&a_pValue->Description, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->WriteMask, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->UserWriteMask, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Byte_Write(&a_pValue->EventNotifier, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_ObjectAttributes_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_ObjectAttributes_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_ObjectAttributes* a_pValue = (OpcUa_ObjectAttributes*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_ObjectAttributes_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->SpecifiedAttributes, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Read(&a_pValue->DisplayName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Read(&a_pValue->Description, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->WriteMask, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->UserWriteMask, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Byte_Read(&a_pValue->EventNotifier, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_ObjectAttributes_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_VariableAttributes
/*============================================================================
 * OpcUa_VariableAttributes_Initialize
 *===========================================================================*/
void OpcUa_VariableAttributes_Initialize(void* pValue)
{
    OpcUa_VariableAttributes* a_pValue = (OpcUa_VariableAttributes*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_VariableAttributes_EncodeableType;
        SOPC_UInt32_Initialize(&a_pValue->SpecifiedAttributes);
        SOPC_LocalizedText_Initialize(&a_pValue->DisplayName);
        SOPC_LocalizedText_Initialize(&a_pValue->Description);
        SOPC_UInt32_Initialize(&a_pValue->WriteMask);
        SOPC_UInt32_Initialize(&a_pValue->UserWriteMask);
        SOPC_Variant_Initialize(&a_pValue->Value);
        SOPC_NodeId_Initialize(&a_pValue->DataType);
        SOPC_Int32_Initialize(&a_pValue->ValueRank);
        SOPC_Initialize_Array(&a_pValue->NoOfArrayDimensions, (void**) &a_pValue->ArrayDimensions, sizeof(uint32_t),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_UInt32_InitializeAux);
        SOPC_Byte_Initialize(&a_pValue->AccessLevel);
        SOPC_Byte_Initialize(&a_pValue->UserAccessLevel);
        SOPC_Double_Initialize(&a_pValue->MinimumSamplingInterval);
        SOPC_Boolean_Initialize(&a_pValue->Historizing);
    }
}

/*============================================================================
 * OpcUa_VariableAttributes_Clear
 *===========================================================================*/
void OpcUa_VariableAttributes_Clear(void* pValue)
{
    OpcUa_VariableAttributes* a_pValue = (OpcUa_VariableAttributes*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_UInt32_Clear(&a_pValue->SpecifiedAttributes);
        SOPC_LocalizedText_Clear(&a_pValue->DisplayName);
        SOPC_LocalizedText_Clear(&a_pValue->Description);
        SOPC_UInt32_Clear(&a_pValue->WriteMask);
        SOPC_UInt32_Clear(&a_pValue->UserWriteMask);
        SOPC_Variant_Clear(&a_pValue->Value);
        SOPC_NodeId_Clear(&a_pValue->DataType);
        SOPC_Int32_Clear(&a_pValue->ValueRank);
        SOPC_Clear_Array(&a_pValue->NoOfArrayDimensions, (void**) &a_pValue->ArrayDimensions, sizeof(uint32_t),
                         (SOPC_EncodeableObject_PfnClear*) SOPC_UInt32_ClearAux);
        SOPC_Byte_Clear(&a_pValue->AccessLevel);
        SOPC_Byte_Clear(&a_pValue->UserAccessLevel);
        SOPC_Double_Clear(&a_pValue->MinimumSamplingInterval);
        SOPC_Boolean_Clear(&a_pValue->Historizing);
    }
}

/*============================================================================
 * OpcUa_VariableAttributes_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_VariableAttributes_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_VariableAttributes* a_pValue = (const OpcUa_VariableAttributes*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->SpecifiedAttributes, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Write(&a_pValue->DisplayName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Write(&a_pValue->Description, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->WriteMask, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->UserWriteMask, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Variant_Write(&a_pValue->Value, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Write(&a_pValue->DataType, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Int32_Write(&a_pValue->ValueRank, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->ArrayDimensions;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfArrayDimensions, &arr, sizeof(uint32_t),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_UInt32_WriteAux);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Byte_Write(&a_pValue->AccessLevel, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Byte_Write(&a_pValue->UserAccessLevel, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Double_Write(&a_pValue->MinimumSamplingInterval, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Write(&a_pValue->Historizing, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_VariableAttributes_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_VariableAttributes_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_VariableAttributes* a_pValue = (OpcUa_VariableAttributes*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_VariableAttributes_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->SpecifiedAttributes, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Read(&a_pValue->DisplayName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Read(&a_pValue->Description, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->WriteMask, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->UserWriteMask, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Variant_Read(&a_pValue->Value, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Read(&a_pValue->DataType, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Int32_Read(&a_pValue->ValueRank, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfArrayDimensions, (void**) &a_pValue->ArrayDimensions,
                                 sizeof(uint32_t), (SOPC_EncodeableObject_PfnDecode*) SOPC_UInt32_ReadAux,
                                 (SOPC_EncodeableObject_PfnInitialize*) SOPC_UInt32_InitializeAux,
                                 (SOPC_EncodeableObject_PfnClear*) SOPC_UInt32_ClearAux);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Byte_Read(&a_pValue->AccessLevel, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Byte_Read(&a_pValue->UserAccessLevel, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Double_Read(&a_pValue->MinimumSamplingInterval, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Read(&a_pValue->Historizing, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_VariableAttributes_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_MethodAttributes
/*============================================================================
 * OpcUa_MethodAttributes_Initialize
 *===========================================================================*/
void OpcUa_MethodAttributes_Initialize(void* pValue)
{
    OpcUa_MethodAttributes* a_pValue = (OpcUa_MethodAttributes*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_MethodAttributes_EncodeableType;
        SOPC_UInt32_Initialize(&a_pValue->SpecifiedAttributes);
        SOPC_LocalizedText_Initialize(&a_pValue->DisplayName);
        SOPC_LocalizedText_Initialize(&a_pValue->Description);
        SOPC_UInt32_Initialize(&a_pValue->WriteMask);
        SOPC_UInt32_Initialize(&a_pValue->UserWriteMask);
        SOPC_Boolean_Initialize(&a_pValue->Executable);
        SOPC_Boolean_Initialize(&a_pValue->UserExecutable);
    }
}

/*============================================================================
 * OpcUa_MethodAttributes_Clear
 *===========================================================================*/
void OpcUa_MethodAttributes_Clear(void* pValue)
{
    OpcUa_MethodAttributes* a_pValue = (OpcUa_MethodAttributes*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_UInt32_Clear(&a_pValue->SpecifiedAttributes);
        SOPC_LocalizedText_Clear(&a_pValue->DisplayName);
        SOPC_LocalizedText_Clear(&a_pValue->Description);
        SOPC_UInt32_Clear(&a_pValue->WriteMask);
        SOPC_UInt32_Clear(&a_pValue->UserWriteMask);
        SOPC_Boolean_Clear(&a_pValue->Executable);
        SOPC_Boolean_Clear(&a_pValue->UserExecutable);
    }
}

/*============================================================================
 * OpcUa_MethodAttributes_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_MethodAttributes_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_MethodAttributes* a_pValue = (const OpcUa_MethodAttributes*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->SpecifiedAttributes, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Write(&a_pValue->DisplayName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Write(&a_pValue->Description, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->WriteMask, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->UserWriteMask, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Write(&a_pValue->Executable, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Write(&a_pValue->UserExecutable, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_MethodAttributes_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_MethodAttributes_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_MethodAttributes* a_pValue = (OpcUa_MethodAttributes*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_MethodAttributes_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->SpecifiedAttributes, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Read(&a_pValue->DisplayName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Read(&a_pValue->Description, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->WriteMask, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->UserWriteMask, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Read(&a_pValue->Executable, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Read(&a_pValue->UserExecutable, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_MethodAttributes_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_ObjectTypeAttributes
/*============================================================================
 * OpcUa_ObjectTypeAttributes_Initialize
 *===========================================================================*/
void OpcUa_ObjectTypeAttributes_Initialize(void* pValue)
{
    OpcUa_ObjectTypeAttributes* a_pValue = (OpcUa_ObjectTypeAttributes*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_ObjectTypeAttributes_EncodeableType;
        SOPC_UInt32_Initialize(&a_pValue->SpecifiedAttributes);
        SOPC_LocalizedText_Initialize(&a_pValue->DisplayName);
        SOPC_LocalizedText_Initialize(&a_pValue->Description);
        SOPC_UInt32_Initialize(&a_pValue->WriteMask);
        SOPC_UInt32_Initialize(&a_pValue->UserWriteMask);
        SOPC_Boolean_Initialize(&a_pValue->IsAbstract);
    }
}

/*============================================================================
 * OpcUa_ObjectTypeAttributes_Clear
 *===========================================================================*/
void OpcUa_ObjectTypeAttributes_Clear(void* pValue)
{
    OpcUa_ObjectTypeAttributes* a_pValue = (OpcUa_ObjectTypeAttributes*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_UInt32_Clear(&a_pValue->SpecifiedAttributes);
        SOPC_LocalizedText_Clear(&a_pValue->DisplayName);
        SOPC_LocalizedText_Clear(&a_pValue->Description);
        SOPC_UInt32_Clear(&a_pValue->WriteMask);
        SOPC_UInt32_Clear(&a_pValue->UserWriteMask);
        SOPC_Boolean_Clear(&a_pValue->IsAbstract);
    }
}

/*============================================================================
 * OpcUa_ObjectTypeAttributes_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_ObjectTypeAttributes_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_ObjectTypeAttributes* a_pValue = (const OpcUa_ObjectTypeAttributes*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->SpecifiedAttributes, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Write(&a_pValue->DisplayName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Write(&a_pValue->Description, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->WriteMask, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->UserWriteMask, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Write(&a_pValue->IsAbstract, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_ObjectTypeAttributes_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_ObjectTypeAttributes_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_ObjectTypeAttributes* a_pValue = (OpcUa_ObjectTypeAttributes*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_ObjectTypeAttributes_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->SpecifiedAttributes, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Read(&a_pValue->DisplayName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Read(&a_pValue->Description, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->WriteMask, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->UserWriteMask, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Read(&a_pValue->IsAbstract, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_ObjectTypeAttributes_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_VariableTypeAttributes
/*============================================================================
 * OpcUa_VariableTypeAttributes_Initialize
 *===========================================================================*/
void OpcUa_VariableTypeAttributes_Initialize(void* pValue)
{
    OpcUa_VariableTypeAttributes* a_pValue = (OpcUa_VariableTypeAttributes*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_VariableTypeAttributes_EncodeableType;
        SOPC_UInt32_Initialize(&a_pValue->SpecifiedAttributes);
        SOPC_LocalizedText_Initialize(&a_pValue->DisplayName);
        SOPC_LocalizedText_Initialize(&a_pValue->Description);
        SOPC_UInt32_Initialize(&a_pValue->WriteMask);
        SOPC_UInt32_Initialize(&a_pValue->UserWriteMask);
        SOPC_Variant_Initialize(&a_pValue->Value);
        SOPC_NodeId_Initialize(&a_pValue->DataType);
        SOPC_Int32_Initialize(&a_pValue->ValueRank);
        SOPC_Initialize_Array(&a_pValue->NoOfArrayDimensions, (void**) &a_pValue->ArrayDimensions, sizeof(uint32_t),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_UInt32_InitializeAux);
        SOPC_Boolean_Initialize(&a_pValue->IsAbstract);
    }
}

/*============================================================================
 * OpcUa_VariableTypeAttributes_Clear
 *===========================================================================*/
void OpcUa_VariableTypeAttributes_Clear(void* pValue)
{
    OpcUa_VariableTypeAttributes* a_pValue = (OpcUa_VariableTypeAttributes*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_UInt32_Clear(&a_pValue->SpecifiedAttributes);
        SOPC_LocalizedText_Clear(&a_pValue->DisplayName);
        SOPC_LocalizedText_Clear(&a_pValue->Description);
        SOPC_UInt32_Clear(&a_pValue->WriteMask);
        SOPC_UInt32_Clear(&a_pValue->UserWriteMask);
        SOPC_Variant_Clear(&a_pValue->Value);
        SOPC_NodeId_Clear(&a_pValue->DataType);
        SOPC_Int32_Clear(&a_pValue->ValueRank);
        SOPC_Clear_Array(&a_pValue->NoOfArrayDimensions, (void**) &a_pValue->ArrayDimensions, sizeof(uint32_t),
                         (SOPC_EncodeableObject_PfnClear*) SOPC_UInt32_ClearAux);
        SOPC_Boolean_Clear(&a_pValue->IsAbstract);
    }
}

/*============================================================================
 * OpcUa_VariableTypeAttributes_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_VariableTypeAttributes_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_VariableTypeAttributes* a_pValue = (const OpcUa_VariableTypeAttributes*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->SpecifiedAttributes, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Write(&a_pValue->DisplayName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Write(&a_pValue->Description, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->WriteMask, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->UserWriteMask, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Variant_Write(&a_pValue->Value, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Write(&a_pValue->DataType, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Int32_Write(&a_pValue->ValueRank, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->ArrayDimensions;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfArrayDimensions, &arr, sizeof(uint32_t),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_UInt32_WriteAux);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Write(&a_pValue->IsAbstract, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_VariableTypeAttributes_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_VariableTypeAttributes_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_VariableTypeAttributes* a_pValue = (OpcUa_VariableTypeAttributes*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_VariableTypeAttributes_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->SpecifiedAttributes, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Read(&a_pValue->DisplayName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Read(&a_pValue->Description, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->WriteMask, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->UserWriteMask, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Variant_Read(&a_pValue->Value, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Read(&a_pValue->DataType, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Int32_Read(&a_pValue->ValueRank, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfArrayDimensions, (void**) &a_pValue->ArrayDimensions,
                                 sizeof(uint32_t), (SOPC_EncodeableObject_PfnDecode*) SOPC_UInt32_ReadAux,
                                 (SOPC_EncodeableObject_PfnInitialize*) SOPC_UInt32_InitializeAux,
                                 (SOPC_EncodeableObject_PfnClear*) SOPC_UInt32_ClearAux);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Read(&a_pValue->IsAbstract, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_VariableTypeAttributes_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_ReferenceTypeAttributes
/*============================================================================
 * OpcUa_ReferenceTypeAttributes_Initialize
 *===========================================================================*/
void OpcUa_ReferenceTypeAttributes_Initialize(void* pValue)
{
    OpcUa_ReferenceTypeAttributes* a_pValue = (OpcUa_ReferenceTypeAttributes*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_ReferenceTypeAttributes_EncodeableType;
        SOPC_UInt32_Initialize(&a_pValue->SpecifiedAttributes);
        SOPC_LocalizedText_Initialize(&a_pValue->DisplayName);
        SOPC_LocalizedText_Initialize(&a_pValue->Description);
        SOPC_UInt32_Initialize(&a_pValue->WriteMask);
        SOPC_UInt32_Initialize(&a_pValue->UserWriteMask);
        SOPC_Boolean_Initialize(&a_pValue->IsAbstract);
        SOPC_Boolean_Initialize(&a_pValue->Symmetric);
        SOPC_LocalizedText_Initialize(&a_pValue->InverseName);
    }
}

/*============================================================================
 * OpcUa_ReferenceTypeAttributes_Clear
 *===========================================================================*/
void OpcUa_ReferenceTypeAttributes_Clear(void* pValue)
{
    OpcUa_ReferenceTypeAttributes* a_pValue = (OpcUa_ReferenceTypeAttributes*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_UInt32_Clear(&a_pValue->SpecifiedAttributes);
        SOPC_LocalizedText_Clear(&a_pValue->DisplayName);
        SOPC_LocalizedText_Clear(&a_pValue->Description);
        SOPC_UInt32_Clear(&a_pValue->WriteMask);
        SOPC_UInt32_Clear(&a_pValue->UserWriteMask);
        SOPC_Boolean_Clear(&a_pValue->IsAbstract);
        SOPC_Boolean_Clear(&a_pValue->Symmetric);
        SOPC_LocalizedText_Clear(&a_pValue->InverseName);
    }
}

/*============================================================================
 * OpcUa_ReferenceTypeAttributes_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_ReferenceTypeAttributes_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_ReferenceTypeAttributes* a_pValue = (const OpcUa_ReferenceTypeAttributes*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->SpecifiedAttributes, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Write(&a_pValue->DisplayName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Write(&a_pValue->Description, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->WriteMask, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->UserWriteMask, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Write(&a_pValue->IsAbstract, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Write(&a_pValue->Symmetric, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Write(&a_pValue->InverseName, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_ReferenceTypeAttributes_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_ReferenceTypeAttributes_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_ReferenceTypeAttributes* a_pValue = (OpcUa_ReferenceTypeAttributes*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_ReferenceTypeAttributes_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->SpecifiedAttributes, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Read(&a_pValue->DisplayName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Read(&a_pValue->Description, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->WriteMask, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->UserWriteMask, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Read(&a_pValue->IsAbstract, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Read(&a_pValue->Symmetric, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Read(&a_pValue->InverseName, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_ReferenceTypeAttributes_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_DataTypeAttributes
/*============================================================================
 * OpcUa_DataTypeAttributes_Initialize
 *===========================================================================*/
void OpcUa_DataTypeAttributes_Initialize(void* pValue)
{
    OpcUa_DataTypeAttributes* a_pValue = (OpcUa_DataTypeAttributes*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_DataTypeAttributes_EncodeableType;
        SOPC_UInt32_Initialize(&a_pValue->SpecifiedAttributes);
        SOPC_LocalizedText_Initialize(&a_pValue->DisplayName);
        SOPC_LocalizedText_Initialize(&a_pValue->Description);
        SOPC_UInt32_Initialize(&a_pValue->WriteMask);
        SOPC_UInt32_Initialize(&a_pValue->UserWriteMask);
        SOPC_Boolean_Initialize(&a_pValue->IsAbstract);
    }
}

/*============================================================================
 * OpcUa_DataTypeAttributes_Clear
 *===========================================================================*/
void OpcUa_DataTypeAttributes_Clear(void* pValue)
{
    OpcUa_DataTypeAttributes* a_pValue = (OpcUa_DataTypeAttributes*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_UInt32_Clear(&a_pValue->SpecifiedAttributes);
        SOPC_LocalizedText_Clear(&a_pValue->DisplayName);
        SOPC_LocalizedText_Clear(&a_pValue->Description);
        SOPC_UInt32_Clear(&a_pValue->WriteMask);
        SOPC_UInt32_Clear(&a_pValue->UserWriteMask);
        SOPC_Boolean_Clear(&a_pValue->IsAbstract);
    }
}

/*============================================================================
 * OpcUa_DataTypeAttributes_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_DataTypeAttributes_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_DataTypeAttributes* a_pValue = (const OpcUa_DataTypeAttributes*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->SpecifiedAttributes, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Write(&a_pValue->DisplayName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Write(&a_pValue->Description, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->WriteMask, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->UserWriteMask, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Write(&a_pValue->IsAbstract, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_DataTypeAttributes_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_DataTypeAttributes_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_DataTypeAttributes* a_pValue = (OpcUa_DataTypeAttributes*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_DataTypeAttributes_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->SpecifiedAttributes, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Read(&a_pValue->DisplayName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Read(&a_pValue->Description, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->WriteMask, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->UserWriteMask, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Read(&a_pValue->IsAbstract, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_DataTypeAttributes_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_ViewAttributes
/*============================================================================
 * OpcUa_ViewAttributes_Initialize
 *===========================================================================*/
void OpcUa_ViewAttributes_Initialize(void* pValue)
{
    OpcUa_ViewAttributes* a_pValue = (OpcUa_ViewAttributes*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_ViewAttributes_EncodeableType;
        SOPC_UInt32_Initialize(&a_pValue->SpecifiedAttributes);
        SOPC_LocalizedText_Initialize(&a_pValue->DisplayName);
        SOPC_LocalizedText_Initialize(&a_pValue->Description);
        SOPC_UInt32_Initialize(&a_pValue->WriteMask);
        SOPC_UInt32_Initialize(&a_pValue->UserWriteMask);
        SOPC_Boolean_Initialize(&a_pValue->ContainsNoLoops);
        SOPC_Byte_Initialize(&a_pValue->EventNotifier);
    }
}

/*============================================================================
 * OpcUa_ViewAttributes_Clear
 *===========================================================================*/
void OpcUa_ViewAttributes_Clear(void* pValue)
{
    OpcUa_ViewAttributes* a_pValue = (OpcUa_ViewAttributes*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_UInt32_Clear(&a_pValue->SpecifiedAttributes);
        SOPC_LocalizedText_Clear(&a_pValue->DisplayName);
        SOPC_LocalizedText_Clear(&a_pValue->Description);
        SOPC_UInt32_Clear(&a_pValue->WriteMask);
        SOPC_UInt32_Clear(&a_pValue->UserWriteMask);
        SOPC_Boolean_Clear(&a_pValue->ContainsNoLoops);
        SOPC_Byte_Clear(&a_pValue->EventNotifier);
    }
}

/*============================================================================
 * OpcUa_ViewAttributes_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_ViewAttributes_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_ViewAttributes* a_pValue = (const OpcUa_ViewAttributes*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->SpecifiedAttributes, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Write(&a_pValue->DisplayName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Write(&a_pValue->Description, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->WriteMask, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->UserWriteMask, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Write(&a_pValue->ContainsNoLoops, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Byte_Write(&a_pValue->EventNotifier, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_ViewAttributes_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_ViewAttributes_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_ViewAttributes* a_pValue = (OpcUa_ViewAttributes*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_ViewAttributes_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->SpecifiedAttributes, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Read(&a_pValue->DisplayName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Read(&a_pValue->Description, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->WriteMask, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->UserWriteMask, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Read(&a_pValue->ContainsNoLoops, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Byte_Read(&a_pValue->EventNotifier, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_ViewAttributes_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_AddNodesItem
/*============================================================================
 * OpcUa_AddNodesItem_Initialize
 *===========================================================================*/
void OpcUa_AddNodesItem_Initialize(void* pValue)
{
    OpcUa_AddNodesItem* a_pValue = (OpcUa_AddNodesItem*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_AddNodesItem_EncodeableType;
        SOPC_ExpandedNodeId_Initialize(&a_pValue->ParentNodeId);
        SOPC_NodeId_Initialize(&a_pValue->ReferenceTypeId);
        SOPC_ExpandedNodeId_Initialize(&a_pValue->RequestedNewNodeId);
        SOPC_QualifiedName_Initialize(&a_pValue->BrowseName);
        SOPC_Initialize_EnumeratedType((int32_t*) &a_pValue->NodeClass);
        SOPC_ExtensionObject_Initialize(&a_pValue->NodeAttributes);
        SOPC_ExpandedNodeId_Initialize(&a_pValue->TypeDefinition);
    }
}

/*============================================================================
 * OpcUa_AddNodesItem_Clear
 *===========================================================================*/
void OpcUa_AddNodesItem_Clear(void* pValue)
{
    OpcUa_AddNodesItem* a_pValue = (OpcUa_AddNodesItem*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_ExpandedNodeId_Clear(&a_pValue->ParentNodeId);
        SOPC_NodeId_Clear(&a_pValue->ReferenceTypeId);
        SOPC_ExpandedNodeId_Clear(&a_pValue->RequestedNewNodeId);
        SOPC_QualifiedName_Clear(&a_pValue->BrowseName);
        SOPC_Clear_EnumeratedType((int32_t*) &a_pValue->NodeClass);
        SOPC_ExtensionObject_Clear(&a_pValue->NodeAttributes);
        SOPC_ExpandedNodeId_Clear(&a_pValue->TypeDefinition);
    }
}

/*============================================================================
 * OpcUa_AddNodesItem_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_AddNodesItem_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_AddNodesItem* a_pValue = (const OpcUa_AddNodesItem*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ExpandedNodeId_Write(&a_pValue->ParentNodeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Write(&a_pValue->ReferenceTypeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ExpandedNodeId_Write(&a_pValue->RequestedNewNodeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_QualifiedName_Write(&a_pValue->BrowseName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Write_EnumeratedType(buf, (const int32_t*) &a_pValue->NodeClass);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ExtensionObject_Write(&a_pValue->NodeAttributes, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ExpandedNodeId_Write(&a_pValue->TypeDefinition, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_AddNodesItem_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_AddNodesItem_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_AddNodesItem* a_pValue = (OpcUa_AddNodesItem*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_AddNodesItem_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ExpandedNodeId_Read(&a_pValue->ParentNodeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Read(&a_pValue->ReferenceTypeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ExpandedNodeId_Read(&a_pValue->RequestedNewNodeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_QualifiedName_Read(&a_pValue->BrowseName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_EnumeratedType(buf, (int32_t*) &a_pValue->NodeClass);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ExtensionObject_Read(&a_pValue->NodeAttributes, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ExpandedNodeId_Read(&a_pValue->TypeDefinition, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_AddNodesItem_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_AddNodesResult
/*============================================================================
 * OpcUa_AddNodesResult_Initialize
 *===========================================================================*/
void OpcUa_AddNodesResult_Initialize(void* pValue)
{
    OpcUa_AddNodesResult* a_pValue = (OpcUa_AddNodesResult*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_AddNodesResult_EncodeableType;
        SOPC_StatusCode_Initialize(&a_pValue->StatusCode);
        SOPC_NodeId_Initialize(&a_pValue->AddedNodeId);
    }
}

/*============================================================================
 * OpcUa_AddNodesResult_Clear
 *===========================================================================*/
void OpcUa_AddNodesResult_Clear(void* pValue)
{
    OpcUa_AddNodesResult* a_pValue = (OpcUa_AddNodesResult*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_StatusCode_Clear(&a_pValue->StatusCode);
        SOPC_NodeId_Clear(&a_pValue->AddedNodeId);
    }
}

/*============================================================================
 * OpcUa_AddNodesResult_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_AddNodesResult_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_AddNodesResult* a_pValue = (const OpcUa_AddNodesResult*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_StatusCode_Write(&a_pValue->StatusCode, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Write(&a_pValue->AddedNodeId, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_AddNodesResult_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_AddNodesResult_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_AddNodesResult* a_pValue = (OpcUa_AddNodesResult*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_AddNodesResult_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_StatusCode_Read(&a_pValue->StatusCode, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Read(&a_pValue->AddedNodeId, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_AddNodesResult_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_AddNodes
#ifndef OPCUA_EXCLUDE_AddNodesRequest
/*============================================================================
 * OpcUa_AddNodesRequest_Initialize
 *===========================================================================*/
void OpcUa_AddNodesRequest_Initialize(void* pValue)
{
    OpcUa_AddNodesRequest* a_pValue = (OpcUa_AddNodesRequest*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_AddNodesRequest_EncodeableType;
        SOPC_Initialize_Array(&a_pValue->NoOfNodesToAdd, (void**) &a_pValue->NodesToAdd, sizeof(OpcUa_AddNodesItem),
                              (SOPC_EncodeableObject_PfnInitialize*) OpcUa_AddNodesItem_Initialize);
    }
}

/*============================================================================
 * OpcUa_AddNodesRequest_Clear
 *===========================================================================*/
void OpcUa_AddNodesRequest_Clear(void* pValue)
{
    OpcUa_AddNodesRequest* a_pValue = (OpcUa_AddNodesRequest*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_Clear_Array(&a_pValue->NoOfNodesToAdd, (void**) &a_pValue->NodesToAdd, sizeof(OpcUa_AddNodesItem),
                         (SOPC_EncodeableObject_PfnClear*) OpcUa_AddNodesItem_Clear);
    }
}

/*============================================================================
 * OpcUa_AddNodesRequest_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_AddNodesRequest_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_AddNodesRequest* a_pValue = (const OpcUa_AddNodesRequest*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->NodesToAdd;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfNodesToAdd, &arr, sizeof(OpcUa_AddNodesItem),
                                  (SOPC_EncodeableObject_PfnEncode*) OpcUa_AddNodesItem_Encode);
    }

    return status;
}

/*============================================================================
 * OpcUa_AddNodesRequest_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_AddNodesRequest_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_AddNodesRequest* a_pValue = (OpcUa_AddNodesRequest*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_AddNodesRequest_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status =
            SOPC_Read_Array(buf, &a_pValue->NoOfNodesToAdd, (void**) &a_pValue->NodesToAdd, sizeof(OpcUa_AddNodesItem),
                            (SOPC_EncodeableObject_PfnDecode*) OpcUa_AddNodesItem_Decode,
                            (SOPC_EncodeableObject_PfnInitialize*) OpcUa_AddNodesItem_Initialize,
                            (SOPC_EncodeableObject_PfnClear*) OpcUa_AddNodesItem_Clear);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_AddNodesRequest_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_AddNodesResponse
/*============================================================================
 * OpcUa_AddNodesResponse_Initialize
 *===========================================================================*/
void OpcUa_AddNodesResponse_Initialize(void* pValue)
{
    OpcUa_AddNodesResponse* a_pValue = (OpcUa_AddNodesResponse*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_AddNodesResponse_EncodeableType;
        OpcUa_ResponseHeader_Initialize(&a_pValue->ResponseHeader);
        SOPC_Initialize_Array(&a_pValue->NoOfResults, (void**) &a_pValue->Results, sizeof(OpcUa_AddNodesResult),
                              (SOPC_EncodeableObject_PfnInitialize*) OpcUa_AddNodesResult_Initialize);
        SOPC_Initialize_Array(&a_pValue->NoOfDiagnosticInfos, (void**) &a_pValue->DiagnosticInfos,
                              sizeof(SOPC_DiagnosticInfo),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_DiagnosticInfo_InitializeAux);
    }
}

/*============================================================================
 * OpcUa_AddNodesResponse_Clear
 *===========================================================================*/
void OpcUa_AddNodesResponse_Clear(void* pValue)
{
    OpcUa_AddNodesResponse* a_pValue = (OpcUa_AddNodesResponse*) pValue;
    if (a_pValue != NULL)
    {
        OpcUa_ResponseHeader_Clear(&a_pValue->ResponseHeader);
        SOPC_Clear_Array(&a_pValue->NoOfResults, (void**) &a_pValue->Results, sizeof(OpcUa_AddNodesResult),
                         (SOPC_EncodeableObject_PfnClear*) OpcUa_AddNodesResult_Clear);
        SOPC_Clear_Array(&a_pValue->NoOfDiagnosticInfos, (void**) &a_pValue->DiagnosticInfos,
                         sizeof(SOPC_DiagnosticInfo), (SOPC_EncodeableObject_PfnClear*) SOPC_DiagnosticInfo_ClearAux);
    }
}

/*============================================================================
 * OpcUa_AddNodesResponse_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_AddNodesResponse_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_AddNodesResponse* a_pValue = (const OpcUa_AddNodesResponse*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->Results;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfResults, &arr, sizeof(OpcUa_AddNodesResult),
                                  (SOPC_EncodeableObject_PfnEncode*) OpcUa_AddNodesResult_Encode);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->DiagnosticInfos;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfDiagnosticInfos, &arr, sizeof(SOPC_DiagnosticInfo),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_DiagnosticInfo_WriteAux);
    }

    return status;
}

/*============================================================================
 * OpcUa_AddNodesResponse_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_AddNodesResponse_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_AddNodesResponse* a_pValue = (OpcUa_AddNodesResponse*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_AddNodesResponse_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfResults, (void**) &a_pValue->Results, sizeof(OpcUa_AddNodesResult),
                                 (SOPC_EncodeableObject_PfnDecode*) OpcUa_AddNodesResult_Decode,
                                 (SOPC_EncodeableObject_PfnInitialize*) OpcUa_AddNodesResult_Initialize,
                                 (SOPC_EncodeableObject_PfnClear*) OpcUa_AddNodesResult_Clear);
    }
    if (SOPC_STATUS_OK == status)
    {
        status =
            SOPC_Read_Array(buf, &a_pValue->NoOfDiagnosticInfos, (void**) &a_pValue->DiagnosticInfos,
                            sizeof(SOPC_DiagnosticInfo), (SOPC_EncodeableObject_PfnDecode*) SOPC_DiagnosticInfo_ReadAux,
                            (SOPC_EncodeableObject_PfnInitialize*) SOPC_DiagnosticInfo_InitializeAux,
                            (SOPC_EncodeableObject_PfnClear*) SOPC_DiagnosticInfo_ClearAux);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_AddNodesResponse_Clear(a_pValue);
    }

    return status;
}
#endif
#endif

#ifndef OPCUA_EXCLUDE_AddReferencesItem
/*============================================================================
 * OpcUa_AddReferencesItem_Initialize
 *===========================================================================*/
void OpcUa_AddReferencesItem_Initialize(void* pValue)
{
    OpcUa_AddReferencesItem* a_pValue = (OpcUa_AddReferencesItem*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_AddReferencesItem_EncodeableType;
        SOPC_NodeId_Initialize(&a_pValue->SourceNodeId);
        SOPC_NodeId_Initialize(&a_pValue->ReferenceTypeId);
        SOPC_Boolean_Initialize(&a_pValue->IsForward);
        SOPC_String_Initialize(&a_pValue->TargetServerUri);
        SOPC_ExpandedNodeId_Initialize(&a_pValue->TargetNodeId);
        SOPC_Initialize_EnumeratedType((int32_t*) &a_pValue->TargetNodeClass);
    }
}

/*============================================================================
 * OpcUa_AddReferencesItem_Clear
 *===========================================================================*/
void OpcUa_AddReferencesItem_Clear(void* pValue)
{
    OpcUa_AddReferencesItem* a_pValue = (OpcUa_AddReferencesItem*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_NodeId_Clear(&a_pValue->SourceNodeId);
        SOPC_NodeId_Clear(&a_pValue->ReferenceTypeId);
        SOPC_Boolean_Clear(&a_pValue->IsForward);
        SOPC_String_Clear(&a_pValue->TargetServerUri);
        SOPC_ExpandedNodeId_Clear(&a_pValue->TargetNodeId);
        SOPC_Clear_EnumeratedType((int32_t*) &a_pValue->TargetNodeClass);
    }
}

/*============================================================================
 * OpcUa_AddReferencesItem_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_AddReferencesItem_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_AddReferencesItem* a_pValue = (const OpcUa_AddReferencesItem*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Write(&a_pValue->SourceNodeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Write(&a_pValue->ReferenceTypeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Write(&a_pValue->IsForward, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Write(&a_pValue->TargetServerUri, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ExpandedNodeId_Write(&a_pValue->TargetNodeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Write_EnumeratedType(buf, (const int32_t*) &a_pValue->TargetNodeClass);
    }

    return status;
}

/*============================================================================
 * OpcUa_AddReferencesItem_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_AddReferencesItem_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_AddReferencesItem* a_pValue = (OpcUa_AddReferencesItem*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_AddReferencesItem_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Read(&a_pValue->SourceNodeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Read(&a_pValue->ReferenceTypeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Read(&a_pValue->IsForward, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Read(&a_pValue->TargetServerUri, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ExpandedNodeId_Read(&a_pValue->TargetNodeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_EnumeratedType(buf, (int32_t*) &a_pValue->TargetNodeClass);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_AddReferencesItem_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_AddReferences
#ifndef OPCUA_EXCLUDE_AddReferencesRequest
/*============================================================================
 * OpcUa_AddReferencesRequest_Initialize
 *===========================================================================*/
void OpcUa_AddReferencesRequest_Initialize(void* pValue)
{
    OpcUa_AddReferencesRequest* a_pValue = (OpcUa_AddReferencesRequest*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_AddReferencesRequest_EncodeableType;
        SOPC_Initialize_Array(&a_pValue->NoOfReferencesToAdd, (void**) &a_pValue->ReferencesToAdd,
                              sizeof(OpcUa_AddReferencesItem),
                              (SOPC_EncodeableObject_PfnInitialize*) OpcUa_AddReferencesItem_Initialize);
    }
}

/*============================================================================
 * OpcUa_AddReferencesRequest_Clear
 *===========================================================================*/
void OpcUa_AddReferencesRequest_Clear(void* pValue)
{
    OpcUa_AddReferencesRequest* a_pValue = (OpcUa_AddReferencesRequest*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_Clear_Array(&a_pValue->NoOfReferencesToAdd, (void**) &a_pValue->ReferencesToAdd,
                         sizeof(OpcUa_AddReferencesItem),
                         (SOPC_EncodeableObject_PfnClear*) OpcUa_AddReferencesItem_Clear);
    }
}

/*============================================================================
 * OpcUa_AddReferencesRequest_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_AddReferencesRequest_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_AddReferencesRequest* a_pValue = (const OpcUa_AddReferencesRequest*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->ReferencesToAdd;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfReferencesToAdd, &arr, sizeof(OpcUa_AddReferencesItem),
                                  (SOPC_EncodeableObject_PfnEncode*) OpcUa_AddReferencesItem_Encode);
    }

    return status;
}

/*============================================================================
 * OpcUa_AddReferencesRequest_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_AddReferencesRequest_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_AddReferencesRequest* a_pValue = (OpcUa_AddReferencesRequest*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_AddReferencesRequest_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfReferencesToAdd, (void**) &a_pValue->ReferencesToAdd,
                                 sizeof(OpcUa_AddReferencesItem),
                                 (SOPC_EncodeableObject_PfnDecode*) OpcUa_AddReferencesItem_Decode,
                                 (SOPC_EncodeableObject_PfnInitialize*) OpcUa_AddReferencesItem_Initialize,
                                 (SOPC_EncodeableObject_PfnClear*) OpcUa_AddReferencesItem_Clear);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_AddReferencesRequest_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_AddReferencesResponse
/*============================================================================
 * OpcUa_AddReferencesResponse_Initialize
 *===========================================================================*/
void OpcUa_AddReferencesResponse_Initialize(void* pValue)
{
    OpcUa_AddReferencesResponse* a_pValue = (OpcUa_AddReferencesResponse*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_AddReferencesResponse_EncodeableType;
        OpcUa_ResponseHeader_Initialize(&a_pValue->ResponseHeader);
        SOPC_Initialize_Array(&a_pValue->NoOfResults, (void**) &a_pValue->Results, sizeof(SOPC_StatusCode),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_StatusCode_InitializeAux);
        SOPC_Initialize_Array(&a_pValue->NoOfDiagnosticInfos, (void**) &a_pValue->DiagnosticInfos,
                              sizeof(SOPC_DiagnosticInfo),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_DiagnosticInfo_InitializeAux);
    }
}

/*============================================================================
 * OpcUa_AddReferencesResponse_Clear
 *===========================================================================*/
void OpcUa_AddReferencesResponse_Clear(void* pValue)
{
    OpcUa_AddReferencesResponse* a_pValue = (OpcUa_AddReferencesResponse*) pValue;
    if (a_pValue != NULL)
    {
        OpcUa_ResponseHeader_Clear(&a_pValue->ResponseHeader);
        SOPC_Clear_Array(&a_pValue->NoOfResults, (void**) &a_pValue->Results, sizeof(SOPC_StatusCode),
                         (SOPC_EncodeableObject_PfnClear*) SOPC_StatusCode_ClearAux);
        SOPC_Clear_Array(&a_pValue->NoOfDiagnosticInfos, (void**) &a_pValue->DiagnosticInfos,
                         sizeof(SOPC_DiagnosticInfo), (SOPC_EncodeableObject_PfnClear*) SOPC_DiagnosticInfo_ClearAux);
    }
}

/*============================================================================
 * OpcUa_AddReferencesResponse_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_AddReferencesResponse_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_AddReferencesResponse* a_pValue = (const OpcUa_AddReferencesResponse*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->Results;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfResults, &arr, sizeof(SOPC_StatusCode),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_StatusCode_WriteAux);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->DiagnosticInfos;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfDiagnosticInfos, &arr, sizeof(SOPC_DiagnosticInfo),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_DiagnosticInfo_WriteAux);
    }

    return status;
}

/*============================================================================
 * OpcUa_AddReferencesResponse_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_AddReferencesResponse_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_AddReferencesResponse* a_pValue = (OpcUa_AddReferencesResponse*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_AddReferencesResponse_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfResults, (void**) &a_pValue->Results, sizeof(SOPC_StatusCode),
                                 (SOPC_EncodeableObject_PfnDecode*) SOPC_StatusCode_ReadAux,
                                 (SOPC_EncodeableObject_PfnInitialize*) SOPC_StatusCode_InitializeAux,
                                 (SOPC_EncodeableObject_PfnClear*) SOPC_StatusCode_ClearAux);
    }
    if (SOPC_STATUS_OK == status)
    {
        status =
            SOPC_Read_Array(buf, &a_pValue->NoOfDiagnosticInfos, (void**) &a_pValue->DiagnosticInfos,
                            sizeof(SOPC_DiagnosticInfo), (SOPC_EncodeableObject_PfnDecode*) SOPC_DiagnosticInfo_ReadAux,
                            (SOPC_EncodeableObject_PfnInitialize*) SOPC_DiagnosticInfo_InitializeAux,
                            (SOPC_EncodeableObject_PfnClear*) SOPC_DiagnosticInfo_ClearAux);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_AddReferencesResponse_Clear(a_pValue);
    }

    return status;
}
#endif
#endif

#ifndef OPCUA_EXCLUDE_DeleteNodesItem
/*============================================================================
 * OpcUa_DeleteNodesItem_Initialize
 *===========================================================================*/
void OpcUa_DeleteNodesItem_Initialize(void* pValue)
{
    OpcUa_DeleteNodesItem* a_pValue = (OpcUa_DeleteNodesItem*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_DeleteNodesItem_EncodeableType;
        SOPC_NodeId_Initialize(&a_pValue->NodeId);
        SOPC_Boolean_Initialize(&a_pValue->DeleteTargetReferences);
    }
}

/*============================================================================
 * OpcUa_DeleteNodesItem_Clear
 *===========================================================================*/
void OpcUa_DeleteNodesItem_Clear(void* pValue)
{
    OpcUa_DeleteNodesItem* a_pValue = (OpcUa_DeleteNodesItem*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_NodeId_Clear(&a_pValue->NodeId);
        SOPC_Boolean_Clear(&a_pValue->DeleteTargetReferences);
    }
}

/*============================================================================
 * OpcUa_DeleteNodesItem_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_DeleteNodesItem_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_DeleteNodesItem* a_pValue = (const OpcUa_DeleteNodesItem*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Write(&a_pValue->NodeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Write(&a_pValue->DeleteTargetReferences, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_DeleteNodesItem_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_DeleteNodesItem_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_DeleteNodesItem* a_pValue = (OpcUa_DeleteNodesItem*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_DeleteNodesItem_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Read(&a_pValue->NodeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Read(&a_pValue->DeleteTargetReferences, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_DeleteNodesItem_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_DeleteNodes
#ifndef OPCUA_EXCLUDE_DeleteNodesRequest
/*============================================================================
 * OpcUa_DeleteNodesRequest_Initialize
 *===========================================================================*/
void OpcUa_DeleteNodesRequest_Initialize(void* pValue)
{
    OpcUa_DeleteNodesRequest* a_pValue = (OpcUa_DeleteNodesRequest*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_DeleteNodesRequest_EncodeableType;
        SOPC_Initialize_Array(&a_pValue->NoOfNodesToDelete, (void**) &a_pValue->NodesToDelete,
                              sizeof(OpcUa_DeleteNodesItem),
                              (SOPC_EncodeableObject_PfnInitialize*) OpcUa_DeleteNodesItem_Initialize);
    }
}

/*============================================================================
 * OpcUa_DeleteNodesRequest_Clear
 *===========================================================================*/
void OpcUa_DeleteNodesRequest_Clear(void* pValue)
{
    OpcUa_DeleteNodesRequest* a_pValue = (OpcUa_DeleteNodesRequest*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_Clear_Array(&a_pValue->NoOfNodesToDelete, (void**) &a_pValue->NodesToDelete, sizeof(OpcUa_DeleteNodesItem),
                         (SOPC_EncodeableObject_PfnClear*) OpcUa_DeleteNodesItem_Clear);
    }
}

/*============================================================================
 * OpcUa_DeleteNodesRequest_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_DeleteNodesRequest_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_DeleteNodesRequest* a_pValue = (const OpcUa_DeleteNodesRequest*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->NodesToDelete;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfNodesToDelete, &arr, sizeof(OpcUa_DeleteNodesItem),
                                  (SOPC_EncodeableObject_PfnEncode*) OpcUa_DeleteNodesItem_Encode);
    }

    return status;
}

/*============================================================================
 * OpcUa_DeleteNodesRequest_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_DeleteNodesRequest_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_DeleteNodesRequest* a_pValue = (OpcUa_DeleteNodesRequest*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_DeleteNodesRequest_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfNodesToDelete, (void**) &a_pValue->NodesToDelete,
                                 sizeof(OpcUa_DeleteNodesItem),
                                 (SOPC_EncodeableObject_PfnDecode*) OpcUa_DeleteNodesItem_Decode,
                                 (SOPC_EncodeableObject_PfnInitialize*) OpcUa_DeleteNodesItem_Initialize,
                                 (SOPC_EncodeableObject_PfnClear*) OpcUa_DeleteNodesItem_Clear);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_DeleteNodesRequest_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_DeleteNodesResponse
/*============================================================================
 * OpcUa_DeleteNodesResponse_Initialize
 *===========================================================================*/
void OpcUa_DeleteNodesResponse_Initialize(void* pValue)
{
    OpcUa_DeleteNodesResponse* a_pValue = (OpcUa_DeleteNodesResponse*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_DeleteNodesResponse_EncodeableType;
        OpcUa_ResponseHeader_Initialize(&a_pValue->ResponseHeader);
        SOPC_Initialize_Array(&a_pValue->NoOfResults, (void**) &a_pValue->Results, sizeof(SOPC_StatusCode),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_StatusCode_InitializeAux);
        SOPC_Initialize_Array(&a_pValue->NoOfDiagnosticInfos, (void**) &a_pValue->DiagnosticInfos,
                              sizeof(SOPC_DiagnosticInfo),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_DiagnosticInfo_InitializeAux);
    }
}

/*============================================================================
 * OpcUa_DeleteNodesResponse_Clear
 *===========================================================================*/
void OpcUa_DeleteNodesResponse_Clear(void* pValue)
{
    OpcUa_DeleteNodesResponse* a_pValue = (OpcUa_DeleteNodesResponse*) pValue;
    if (a_pValue != NULL)
    {
        OpcUa_ResponseHeader_Clear(&a_pValue->ResponseHeader);
        SOPC_Clear_Array(&a_pValue->NoOfResults, (void**) &a_pValue->Results, sizeof(SOPC_StatusCode),
                         (SOPC_EncodeableObject_PfnClear*) SOPC_StatusCode_ClearAux);
        SOPC_Clear_Array(&a_pValue->NoOfDiagnosticInfos, (void**) &a_pValue->DiagnosticInfos,
                         sizeof(SOPC_DiagnosticInfo), (SOPC_EncodeableObject_PfnClear*) SOPC_DiagnosticInfo_ClearAux);
    }
}

/*============================================================================
 * OpcUa_DeleteNodesResponse_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_DeleteNodesResponse_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_DeleteNodesResponse* a_pValue = (const OpcUa_DeleteNodesResponse*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->Results;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfResults, &arr, sizeof(SOPC_StatusCode),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_StatusCode_WriteAux);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->DiagnosticInfos;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfDiagnosticInfos, &arr, sizeof(SOPC_DiagnosticInfo),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_DiagnosticInfo_WriteAux);
    }

    return status;
}

/*============================================================================
 * OpcUa_DeleteNodesResponse_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_DeleteNodesResponse_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_DeleteNodesResponse* a_pValue = (OpcUa_DeleteNodesResponse*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_DeleteNodesResponse_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfResults, (void**) &a_pValue->Results, sizeof(SOPC_StatusCode),
                                 (SOPC_EncodeableObject_PfnDecode*) SOPC_StatusCode_ReadAux,
                                 (SOPC_EncodeableObject_PfnInitialize*) SOPC_StatusCode_InitializeAux,
                                 (SOPC_EncodeableObject_PfnClear*) SOPC_StatusCode_ClearAux);
    }
    if (SOPC_STATUS_OK == status)
    {
        status =
            SOPC_Read_Array(buf, &a_pValue->NoOfDiagnosticInfos, (void**) &a_pValue->DiagnosticInfos,
                            sizeof(SOPC_DiagnosticInfo), (SOPC_EncodeableObject_PfnDecode*) SOPC_DiagnosticInfo_ReadAux,
                            (SOPC_EncodeableObject_PfnInitialize*) SOPC_DiagnosticInfo_InitializeAux,
                            (SOPC_EncodeableObject_PfnClear*) SOPC_DiagnosticInfo_ClearAux);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_DeleteNodesResponse_Clear(a_pValue);
    }

    return status;
}
#endif
#endif

#ifndef OPCUA_EXCLUDE_DeleteReferencesItem
/*============================================================================
 * OpcUa_DeleteReferencesItem_Initialize
 *===========================================================================*/
void OpcUa_DeleteReferencesItem_Initialize(void* pValue)
{
    OpcUa_DeleteReferencesItem* a_pValue = (OpcUa_DeleteReferencesItem*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_DeleteReferencesItem_EncodeableType;
        SOPC_NodeId_Initialize(&a_pValue->SourceNodeId);
        SOPC_NodeId_Initialize(&a_pValue->ReferenceTypeId);
        SOPC_Boolean_Initialize(&a_pValue->IsForward);
        SOPC_ExpandedNodeId_Initialize(&a_pValue->TargetNodeId);
        SOPC_Boolean_Initialize(&a_pValue->DeleteBidirectional);
    }
}

/*============================================================================
 * OpcUa_DeleteReferencesItem_Clear
 *===========================================================================*/
void OpcUa_DeleteReferencesItem_Clear(void* pValue)
{
    OpcUa_DeleteReferencesItem* a_pValue = (OpcUa_DeleteReferencesItem*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_NodeId_Clear(&a_pValue->SourceNodeId);
        SOPC_NodeId_Clear(&a_pValue->ReferenceTypeId);
        SOPC_Boolean_Clear(&a_pValue->IsForward);
        SOPC_ExpandedNodeId_Clear(&a_pValue->TargetNodeId);
        SOPC_Boolean_Clear(&a_pValue->DeleteBidirectional);
    }
}

/*============================================================================
 * OpcUa_DeleteReferencesItem_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_DeleteReferencesItem_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_DeleteReferencesItem* a_pValue = (const OpcUa_DeleteReferencesItem*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Write(&a_pValue->SourceNodeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Write(&a_pValue->ReferenceTypeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Write(&a_pValue->IsForward, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ExpandedNodeId_Write(&a_pValue->TargetNodeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Write(&a_pValue->DeleteBidirectional, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_DeleteReferencesItem_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_DeleteReferencesItem_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_DeleteReferencesItem* a_pValue = (OpcUa_DeleteReferencesItem*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_DeleteReferencesItem_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Read(&a_pValue->SourceNodeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Read(&a_pValue->ReferenceTypeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Read(&a_pValue->IsForward, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ExpandedNodeId_Read(&a_pValue->TargetNodeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Read(&a_pValue->DeleteBidirectional, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_DeleteReferencesItem_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_DeleteReferences
#ifndef OPCUA_EXCLUDE_DeleteReferencesRequest
/*============================================================================
 * OpcUa_DeleteReferencesRequest_Initialize
 *===========================================================================*/
void OpcUa_DeleteReferencesRequest_Initialize(void* pValue)
{
    OpcUa_DeleteReferencesRequest* a_pValue = (OpcUa_DeleteReferencesRequest*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_DeleteReferencesRequest_EncodeableType;
        SOPC_Initialize_Array(&a_pValue->NoOfReferencesToDelete, (void**) &a_pValue->ReferencesToDelete,
                              sizeof(OpcUa_DeleteReferencesItem),
                              (SOPC_EncodeableObject_PfnInitialize*) OpcUa_DeleteReferencesItem_Initialize);
    }
}

/*============================================================================
 * OpcUa_DeleteReferencesRequest_Clear
 *===========================================================================*/
void OpcUa_DeleteReferencesRequest_Clear(void* pValue)
{
    OpcUa_DeleteReferencesRequest* a_pValue = (OpcUa_DeleteReferencesRequest*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_Clear_Array(&a_pValue->NoOfReferencesToDelete, (void**) &a_pValue->ReferencesToDelete,
                         sizeof(OpcUa_DeleteReferencesItem),
                         (SOPC_EncodeableObject_PfnClear*) OpcUa_DeleteReferencesItem_Clear);
    }
}

/*============================================================================
 * OpcUa_DeleteReferencesRequest_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_DeleteReferencesRequest_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_DeleteReferencesRequest* a_pValue = (const OpcUa_DeleteReferencesRequest*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->ReferencesToDelete;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfReferencesToDelete, &arr, sizeof(OpcUa_DeleteReferencesItem),
                                  (SOPC_EncodeableObject_PfnEncode*) OpcUa_DeleteReferencesItem_Encode);
    }

    return status;
}

/*============================================================================
 * OpcUa_DeleteReferencesRequest_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_DeleteReferencesRequest_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_DeleteReferencesRequest* a_pValue = (OpcUa_DeleteReferencesRequest*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_DeleteReferencesRequest_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfReferencesToDelete, (void**) &a_pValue->ReferencesToDelete,
                                 sizeof(OpcUa_DeleteReferencesItem),
                                 (SOPC_EncodeableObject_PfnDecode*) OpcUa_DeleteReferencesItem_Decode,
                                 (SOPC_EncodeableObject_PfnInitialize*) OpcUa_DeleteReferencesItem_Initialize,
                                 (SOPC_EncodeableObject_PfnClear*) OpcUa_DeleteReferencesItem_Clear);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_DeleteReferencesRequest_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_DeleteReferencesResponse
/*============================================================================
 * OpcUa_DeleteReferencesResponse_Initialize
 *===========================================================================*/
void OpcUa_DeleteReferencesResponse_Initialize(void* pValue)
{
    OpcUa_DeleteReferencesResponse* a_pValue = (OpcUa_DeleteReferencesResponse*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_DeleteReferencesResponse_EncodeableType;
        OpcUa_ResponseHeader_Initialize(&a_pValue->ResponseHeader);
        SOPC_Initialize_Array(&a_pValue->NoOfResults, (void**) &a_pValue->Results, sizeof(SOPC_StatusCode),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_StatusCode_InitializeAux);
        SOPC_Initialize_Array(&a_pValue->NoOfDiagnosticInfos, (void**) &a_pValue->DiagnosticInfos,
                              sizeof(SOPC_DiagnosticInfo),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_DiagnosticInfo_InitializeAux);
    }
}

/*============================================================================
 * OpcUa_DeleteReferencesResponse_Clear
 *===========================================================================*/
void OpcUa_DeleteReferencesResponse_Clear(void* pValue)
{
    OpcUa_DeleteReferencesResponse* a_pValue = (OpcUa_DeleteReferencesResponse*) pValue;
    if (a_pValue != NULL)
    {
        OpcUa_ResponseHeader_Clear(&a_pValue->ResponseHeader);
        SOPC_Clear_Array(&a_pValue->NoOfResults, (void**) &a_pValue->Results, sizeof(SOPC_StatusCode),
                         (SOPC_EncodeableObject_PfnClear*) SOPC_StatusCode_ClearAux);
        SOPC_Clear_Array(&a_pValue->NoOfDiagnosticInfos, (void**) &a_pValue->DiagnosticInfos,
                         sizeof(SOPC_DiagnosticInfo), (SOPC_EncodeableObject_PfnClear*) SOPC_DiagnosticInfo_ClearAux);
    }
}

/*============================================================================
 * OpcUa_DeleteReferencesResponse_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_DeleteReferencesResponse_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_DeleteReferencesResponse* a_pValue = (const OpcUa_DeleteReferencesResponse*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->Results;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfResults, &arr, sizeof(SOPC_StatusCode),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_StatusCode_WriteAux);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->DiagnosticInfos;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfDiagnosticInfos, &arr, sizeof(SOPC_DiagnosticInfo),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_DiagnosticInfo_WriteAux);
    }

    return status;
}

/*============================================================================
 * OpcUa_DeleteReferencesResponse_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_DeleteReferencesResponse_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_DeleteReferencesResponse* a_pValue = (OpcUa_DeleteReferencesResponse*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_DeleteReferencesResponse_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfResults, (void**) &a_pValue->Results, sizeof(SOPC_StatusCode),
                                 (SOPC_EncodeableObject_PfnDecode*) SOPC_StatusCode_ReadAux,
                                 (SOPC_EncodeableObject_PfnInitialize*) SOPC_StatusCode_InitializeAux,
                                 (SOPC_EncodeableObject_PfnClear*) SOPC_StatusCode_ClearAux);
    }
    if (SOPC_STATUS_OK == status)
    {
        status =
            SOPC_Read_Array(buf, &a_pValue->NoOfDiagnosticInfos, (void**) &a_pValue->DiagnosticInfos,
                            sizeof(SOPC_DiagnosticInfo), (SOPC_EncodeableObject_PfnDecode*) SOPC_DiagnosticInfo_ReadAux,
                            (SOPC_EncodeableObject_PfnInitialize*) SOPC_DiagnosticInfo_InitializeAux,
                            (SOPC_EncodeableObject_PfnClear*) SOPC_DiagnosticInfo_ClearAux);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_DeleteReferencesResponse_Clear(a_pValue);
    }

    return status;
}
#endif
#endif

#ifndef OPCUA_EXCLUDE_ViewDescription
/*============================================================================
 * OpcUa_ViewDescription_Initialize
 *===========================================================================*/
void OpcUa_ViewDescription_Initialize(void* pValue)
{
    OpcUa_ViewDescription* a_pValue = (OpcUa_ViewDescription*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_ViewDescription_EncodeableType;
        SOPC_NodeId_Initialize(&a_pValue->ViewId);
        SOPC_DateTime_Initialize(&a_pValue->Timestamp);
        SOPC_UInt32_Initialize(&a_pValue->ViewVersion);
    }
}

/*============================================================================
 * OpcUa_ViewDescription_Clear
 *===========================================================================*/
void OpcUa_ViewDescription_Clear(void* pValue)
{
    OpcUa_ViewDescription* a_pValue = (OpcUa_ViewDescription*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_NodeId_Clear(&a_pValue->ViewId);
        SOPC_DateTime_Clear(&a_pValue->Timestamp);
        SOPC_UInt32_Clear(&a_pValue->ViewVersion);
    }
}

/*============================================================================
 * OpcUa_ViewDescription_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_ViewDescription_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_ViewDescription* a_pValue = (const OpcUa_ViewDescription*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Write(&a_pValue->ViewId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_DateTime_Write(&a_pValue->Timestamp, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->ViewVersion, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_ViewDescription_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_ViewDescription_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_ViewDescription* a_pValue = (OpcUa_ViewDescription*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_ViewDescription_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Read(&a_pValue->ViewId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_DateTime_Read(&a_pValue->Timestamp, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->ViewVersion, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_ViewDescription_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_BrowseDescription
/*============================================================================
 * OpcUa_BrowseDescription_Initialize
 *===========================================================================*/
void OpcUa_BrowseDescription_Initialize(void* pValue)
{
    OpcUa_BrowseDescription* a_pValue = (OpcUa_BrowseDescription*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_BrowseDescription_EncodeableType;
        SOPC_NodeId_Initialize(&a_pValue->NodeId);
        SOPC_Initialize_EnumeratedType((int32_t*) &a_pValue->BrowseDirection);
        SOPC_NodeId_Initialize(&a_pValue->ReferenceTypeId);
        SOPC_Boolean_Initialize(&a_pValue->IncludeSubtypes);
        SOPC_UInt32_Initialize(&a_pValue->NodeClassMask);
        SOPC_UInt32_Initialize(&a_pValue->ResultMask);
    }
}

/*============================================================================
 * OpcUa_BrowseDescription_Clear
 *===========================================================================*/
void OpcUa_BrowseDescription_Clear(void* pValue)
{
    OpcUa_BrowseDescription* a_pValue = (OpcUa_BrowseDescription*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_NodeId_Clear(&a_pValue->NodeId);
        SOPC_Clear_EnumeratedType((int32_t*) &a_pValue->BrowseDirection);
        SOPC_NodeId_Clear(&a_pValue->ReferenceTypeId);
        SOPC_Boolean_Clear(&a_pValue->IncludeSubtypes);
        SOPC_UInt32_Clear(&a_pValue->NodeClassMask);
        SOPC_UInt32_Clear(&a_pValue->ResultMask);
    }
}

/*============================================================================
 * OpcUa_BrowseDescription_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_BrowseDescription_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_BrowseDescription* a_pValue = (const OpcUa_BrowseDescription*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Write(&a_pValue->NodeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Write_EnumeratedType(buf, (const int32_t*) &a_pValue->BrowseDirection);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Write(&a_pValue->ReferenceTypeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Write(&a_pValue->IncludeSubtypes, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->NodeClassMask, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->ResultMask, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_BrowseDescription_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_BrowseDescription_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_BrowseDescription* a_pValue = (OpcUa_BrowseDescription*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_BrowseDescription_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Read(&a_pValue->NodeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_EnumeratedType(buf, (int32_t*) &a_pValue->BrowseDirection);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Read(&a_pValue->ReferenceTypeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Read(&a_pValue->IncludeSubtypes, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->NodeClassMask, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->ResultMask, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_BrowseDescription_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_ReferenceDescription
/*============================================================================
 * OpcUa_ReferenceDescription_Initialize
 *===========================================================================*/
void OpcUa_ReferenceDescription_Initialize(void* pValue)
{
    OpcUa_ReferenceDescription* a_pValue = (OpcUa_ReferenceDescription*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_ReferenceDescription_EncodeableType;
        SOPC_NodeId_Initialize(&a_pValue->ReferenceTypeId);
        SOPC_Boolean_Initialize(&a_pValue->IsForward);
        SOPC_ExpandedNodeId_Initialize(&a_pValue->NodeId);
        SOPC_QualifiedName_Initialize(&a_pValue->BrowseName);
        SOPC_LocalizedText_Initialize(&a_pValue->DisplayName);
        SOPC_Initialize_EnumeratedType((int32_t*) &a_pValue->NodeClass);
        SOPC_ExpandedNodeId_Initialize(&a_pValue->TypeDefinition);
    }
}

/*============================================================================
 * OpcUa_ReferenceDescription_Clear
 *===========================================================================*/
void OpcUa_ReferenceDescription_Clear(void* pValue)
{
    OpcUa_ReferenceDescription* a_pValue = (OpcUa_ReferenceDescription*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_NodeId_Clear(&a_pValue->ReferenceTypeId);
        SOPC_Boolean_Clear(&a_pValue->IsForward);
        SOPC_ExpandedNodeId_Clear(&a_pValue->NodeId);
        SOPC_QualifiedName_Clear(&a_pValue->BrowseName);
        SOPC_LocalizedText_Clear(&a_pValue->DisplayName);
        SOPC_Clear_EnumeratedType((int32_t*) &a_pValue->NodeClass);
        SOPC_ExpandedNodeId_Clear(&a_pValue->TypeDefinition);
    }
}

/*============================================================================
 * OpcUa_ReferenceDescription_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_ReferenceDescription_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_ReferenceDescription* a_pValue = (const OpcUa_ReferenceDescription*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Write(&a_pValue->ReferenceTypeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Write(&a_pValue->IsForward, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ExpandedNodeId_Write(&a_pValue->NodeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_QualifiedName_Write(&a_pValue->BrowseName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Write(&a_pValue->DisplayName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Write_EnumeratedType(buf, (const int32_t*) &a_pValue->NodeClass);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ExpandedNodeId_Write(&a_pValue->TypeDefinition, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_ReferenceDescription_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_ReferenceDescription_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_ReferenceDescription* a_pValue = (OpcUa_ReferenceDescription*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_ReferenceDescription_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Read(&a_pValue->ReferenceTypeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Read(&a_pValue->IsForward, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ExpandedNodeId_Read(&a_pValue->NodeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_QualifiedName_Read(&a_pValue->BrowseName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Read(&a_pValue->DisplayName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_EnumeratedType(buf, (int32_t*) &a_pValue->NodeClass);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ExpandedNodeId_Read(&a_pValue->TypeDefinition, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_ReferenceDescription_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_BrowseResult
/*============================================================================
 * OpcUa_BrowseResult_Initialize
 *===========================================================================*/
void OpcUa_BrowseResult_Initialize(void* pValue)
{
    OpcUa_BrowseResult* a_pValue = (OpcUa_BrowseResult*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_BrowseResult_EncodeableType;
        SOPC_StatusCode_Initialize(&a_pValue->StatusCode);
        SOPC_ByteString_Initialize(&a_pValue->ContinuationPoint);
        SOPC_Initialize_Array(&a_pValue->NoOfReferences, (void**) &a_pValue->References,
                              sizeof(OpcUa_ReferenceDescription),
                              (SOPC_EncodeableObject_PfnInitialize*) OpcUa_ReferenceDescription_Initialize);
    }
}

/*============================================================================
 * OpcUa_BrowseResult_Clear
 *===========================================================================*/
void OpcUa_BrowseResult_Clear(void* pValue)
{
    OpcUa_BrowseResult* a_pValue = (OpcUa_BrowseResult*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_StatusCode_Clear(&a_pValue->StatusCode);
        SOPC_ByteString_Clear(&a_pValue->ContinuationPoint);
        SOPC_Clear_Array(&a_pValue->NoOfReferences, (void**) &a_pValue->References, sizeof(OpcUa_ReferenceDescription),
                         (SOPC_EncodeableObject_PfnClear*) OpcUa_ReferenceDescription_Clear);
    }
}

/*============================================================================
 * OpcUa_BrowseResult_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_BrowseResult_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_BrowseResult* a_pValue = (const OpcUa_BrowseResult*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_StatusCode_Write(&a_pValue->StatusCode, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ByteString_Write(&a_pValue->ContinuationPoint, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->References;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfReferences, &arr, sizeof(OpcUa_ReferenceDescription),
                                  (SOPC_EncodeableObject_PfnEncode*) OpcUa_ReferenceDescription_Encode);
    }

    return status;
}

/*============================================================================
 * OpcUa_BrowseResult_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_BrowseResult_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_BrowseResult* a_pValue = (OpcUa_BrowseResult*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_BrowseResult_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_StatusCode_Read(&a_pValue->StatusCode, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ByteString_Read(&a_pValue->ContinuationPoint, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfReferences, (void**) &a_pValue->References,
                                 sizeof(OpcUa_ReferenceDescription),
                                 (SOPC_EncodeableObject_PfnDecode*) OpcUa_ReferenceDescription_Decode,
                                 (SOPC_EncodeableObject_PfnInitialize*) OpcUa_ReferenceDescription_Initialize,
                                 (SOPC_EncodeableObject_PfnClear*) OpcUa_ReferenceDescription_Clear);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_BrowseResult_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_Browse
#ifndef OPCUA_EXCLUDE_BrowseRequest
/*============================================================================
 * OpcUa_BrowseRequest_Initialize
 *===========================================================================*/
void OpcUa_BrowseRequest_Initialize(void* pValue)
{
    OpcUa_BrowseRequest* a_pValue = (OpcUa_BrowseRequest*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_BrowseRequest_EncodeableType;
        OpcUa_ViewDescription_Initialize(&a_pValue->View);
        SOPC_UInt32_Initialize(&a_pValue->RequestedMaxReferencesPerNode);
        SOPC_Initialize_Array(&a_pValue->NoOfNodesToBrowse, (void**) &a_pValue->NodesToBrowse,
                              sizeof(OpcUa_BrowseDescription),
                              (SOPC_EncodeableObject_PfnInitialize*) OpcUa_BrowseDescription_Initialize);
    }
}

/*============================================================================
 * OpcUa_BrowseRequest_Clear
 *===========================================================================*/
void OpcUa_BrowseRequest_Clear(void* pValue)
{
    OpcUa_BrowseRequest* a_pValue = (OpcUa_BrowseRequest*) pValue;
    if (a_pValue != NULL)
    {
        OpcUa_ViewDescription_Clear(&a_pValue->View);
        SOPC_UInt32_Clear(&a_pValue->RequestedMaxReferencesPerNode);
        SOPC_Clear_Array(&a_pValue->NoOfNodesToBrowse, (void**) &a_pValue->NodesToBrowse,
                         sizeof(OpcUa_BrowseDescription),
                         (SOPC_EncodeableObject_PfnClear*) OpcUa_BrowseDescription_Clear);
    }
}

/*============================================================================
 * OpcUa_BrowseRequest_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_BrowseRequest_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_BrowseRequest* a_pValue = (const OpcUa_BrowseRequest*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_ViewDescription_Encode(&a_pValue->View, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->RequestedMaxReferencesPerNode, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->NodesToBrowse;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfNodesToBrowse, &arr, sizeof(OpcUa_BrowseDescription),
                                  (SOPC_EncodeableObject_PfnEncode*) OpcUa_BrowseDescription_Encode);
    }

    return status;
}

/*============================================================================
 * OpcUa_BrowseRequest_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_BrowseRequest_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_BrowseRequest* a_pValue = (OpcUa_BrowseRequest*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_BrowseRequest_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_ViewDescription_Decode(&a_pValue->View, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->RequestedMaxReferencesPerNode, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfNodesToBrowse, (void**) &a_pValue->NodesToBrowse,
                                 sizeof(OpcUa_BrowseDescription),
                                 (SOPC_EncodeableObject_PfnDecode*) OpcUa_BrowseDescription_Decode,
                                 (SOPC_EncodeableObject_PfnInitialize*) OpcUa_BrowseDescription_Initialize,
                                 (SOPC_EncodeableObject_PfnClear*) OpcUa_BrowseDescription_Clear);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_BrowseRequest_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_BrowseResponse
/*============================================================================
 * OpcUa_BrowseResponse_Initialize
 *===========================================================================*/
void OpcUa_BrowseResponse_Initialize(void* pValue)
{
    OpcUa_BrowseResponse* a_pValue = (OpcUa_BrowseResponse*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_BrowseResponse_EncodeableType;
        OpcUa_ResponseHeader_Initialize(&a_pValue->ResponseHeader);
        SOPC_Initialize_Array(&a_pValue->NoOfResults, (void**) &a_pValue->Results, sizeof(OpcUa_BrowseResult),
                              (SOPC_EncodeableObject_PfnInitialize*) OpcUa_BrowseResult_Initialize);
        SOPC_Initialize_Array(&a_pValue->NoOfDiagnosticInfos, (void**) &a_pValue->DiagnosticInfos,
                              sizeof(SOPC_DiagnosticInfo),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_DiagnosticInfo_InitializeAux);
    }
}

/*============================================================================
 * OpcUa_BrowseResponse_Clear
 *===========================================================================*/
void OpcUa_BrowseResponse_Clear(void* pValue)
{
    OpcUa_BrowseResponse* a_pValue = (OpcUa_BrowseResponse*) pValue;
    if (a_pValue != NULL)
    {
        OpcUa_ResponseHeader_Clear(&a_pValue->ResponseHeader);
        SOPC_Clear_Array(&a_pValue->NoOfResults, (void**) &a_pValue->Results, sizeof(OpcUa_BrowseResult),
                         (SOPC_EncodeableObject_PfnClear*) OpcUa_BrowseResult_Clear);
        SOPC_Clear_Array(&a_pValue->NoOfDiagnosticInfos, (void**) &a_pValue->DiagnosticInfos,
                         sizeof(SOPC_DiagnosticInfo), (SOPC_EncodeableObject_PfnClear*) SOPC_DiagnosticInfo_ClearAux);
    }
}

/*============================================================================
 * OpcUa_BrowseResponse_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_BrowseResponse_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_BrowseResponse* a_pValue = (const OpcUa_BrowseResponse*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->Results;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfResults, &arr, sizeof(OpcUa_BrowseResult),
                                  (SOPC_EncodeableObject_PfnEncode*) OpcUa_BrowseResult_Encode);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->DiagnosticInfos;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfDiagnosticInfos, &arr, sizeof(SOPC_DiagnosticInfo),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_DiagnosticInfo_WriteAux);
    }

    return status;
}

/*============================================================================
 * OpcUa_BrowseResponse_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_BrowseResponse_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_BrowseResponse* a_pValue = (OpcUa_BrowseResponse*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_BrowseResponse_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfResults, (void**) &a_pValue->Results, sizeof(OpcUa_BrowseResult),
                                 (SOPC_EncodeableObject_PfnDecode*) OpcUa_BrowseResult_Decode,
                                 (SOPC_EncodeableObject_PfnInitialize*) OpcUa_BrowseResult_Initialize,
                                 (SOPC_EncodeableObject_PfnClear*) OpcUa_BrowseResult_Clear);
    }
    if (SOPC_STATUS_OK == status)
    {
        status =
            SOPC_Read_Array(buf, &a_pValue->NoOfDiagnosticInfos, (void**) &a_pValue->DiagnosticInfos,
                            sizeof(SOPC_DiagnosticInfo), (SOPC_EncodeableObject_PfnDecode*) SOPC_DiagnosticInfo_ReadAux,
                            (SOPC_EncodeableObject_PfnInitialize*) SOPC_DiagnosticInfo_InitializeAux,
                            (SOPC_EncodeableObject_PfnClear*) SOPC_DiagnosticInfo_ClearAux);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_BrowseResponse_Clear(a_pValue);
    }

    return status;
}
#endif
#endif

#ifndef OPCUA_EXCLUDE_BrowseNext
#ifndef OPCUA_EXCLUDE_BrowseNextRequest
/*============================================================================
 * OpcUa_BrowseNextRequest_Initialize
 *===========================================================================*/
void OpcUa_BrowseNextRequest_Initialize(void* pValue)
{
    OpcUa_BrowseNextRequest* a_pValue = (OpcUa_BrowseNextRequest*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_BrowseNextRequest_EncodeableType;
        SOPC_Boolean_Initialize(&a_pValue->ReleaseContinuationPoints);
        SOPC_Initialize_Array(&a_pValue->NoOfContinuationPoints, (void**) &a_pValue->ContinuationPoints,
                              sizeof(SOPC_ByteString),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_ByteString_InitializeAux);
    }
}

/*============================================================================
 * OpcUa_BrowseNextRequest_Clear
 *===========================================================================*/
void OpcUa_BrowseNextRequest_Clear(void* pValue)
{
    OpcUa_BrowseNextRequest* a_pValue = (OpcUa_BrowseNextRequest*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_Boolean_Clear(&a_pValue->ReleaseContinuationPoints);
        SOPC_Clear_Array(&a_pValue->NoOfContinuationPoints, (void**) &a_pValue->ContinuationPoints,
                         sizeof(SOPC_ByteString), (SOPC_EncodeableObject_PfnClear*) SOPC_ByteString_ClearAux);
    }
}

/*============================================================================
 * OpcUa_BrowseNextRequest_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_BrowseNextRequest_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_BrowseNextRequest* a_pValue = (const OpcUa_BrowseNextRequest*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Write(&a_pValue->ReleaseContinuationPoints, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->ContinuationPoints;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfContinuationPoints, &arr, sizeof(SOPC_ByteString),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_ByteString_WriteAux);
    }

    return status;
}

/*============================================================================
 * OpcUa_BrowseNextRequest_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_BrowseNextRequest_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_BrowseNextRequest* a_pValue = (OpcUa_BrowseNextRequest*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_BrowseNextRequest_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Read(&a_pValue->ReleaseContinuationPoints, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfContinuationPoints, (void**) &a_pValue->ContinuationPoints,
                                 sizeof(SOPC_ByteString), (SOPC_EncodeableObject_PfnDecode*) SOPC_ByteString_ReadAux,
                                 (SOPC_EncodeableObject_PfnInitialize*) SOPC_ByteString_InitializeAux,
                                 (SOPC_EncodeableObject_PfnClear*) SOPC_ByteString_ClearAux);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_BrowseNextRequest_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_BrowseNextResponse
/*============================================================================
 * OpcUa_BrowseNextResponse_Initialize
 *===========================================================================*/
void OpcUa_BrowseNextResponse_Initialize(void* pValue)
{
    OpcUa_BrowseNextResponse* a_pValue = (OpcUa_BrowseNextResponse*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_BrowseNextResponse_EncodeableType;
        OpcUa_ResponseHeader_Initialize(&a_pValue->ResponseHeader);
        SOPC_Initialize_Array(&a_pValue->NoOfResults, (void**) &a_pValue->Results, sizeof(OpcUa_BrowseResult),
                              (SOPC_EncodeableObject_PfnInitialize*) OpcUa_BrowseResult_Initialize);
        SOPC_Initialize_Array(&a_pValue->NoOfDiagnosticInfos, (void**) &a_pValue->DiagnosticInfos,
                              sizeof(SOPC_DiagnosticInfo),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_DiagnosticInfo_InitializeAux);
    }
}

/*============================================================================
 * OpcUa_BrowseNextResponse_Clear
 *===========================================================================*/
void OpcUa_BrowseNextResponse_Clear(void* pValue)
{
    OpcUa_BrowseNextResponse* a_pValue = (OpcUa_BrowseNextResponse*) pValue;
    if (a_pValue != NULL)
    {
        OpcUa_ResponseHeader_Clear(&a_pValue->ResponseHeader);
        SOPC_Clear_Array(&a_pValue->NoOfResults, (void**) &a_pValue->Results, sizeof(OpcUa_BrowseResult),
                         (SOPC_EncodeableObject_PfnClear*) OpcUa_BrowseResult_Clear);
        SOPC_Clear_Array(&a_pValue->NoOfDiagnosticInfos, (void**) &a_pValue->DiagnosticInfos,
                         sizeof(SOPC_DiagnosticInfo), (SOPC_EncodeableObject_PfnClear*) SOPC_DiagnosticInfo_ClearAux);
    }
}

/*============================================================================
 * OpcUa_BrowseNextResponse_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_BrowseNextResponse_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_BrowseNextResponse* a_pValue = (const OpcUa_BrowseNextResponse*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->Results;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfResults, &arr, sizeof(OpcUa_BrowseResult),
                                  (SOPC_EncodeableObject_PfnEncode*) OpcUa_BrowseResult_Encode);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->DiagnosticInfos;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfDiagnosticInfos, &arr, sizeof(SOPC_DiagnosticInfo),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_DiagnosticInfo_WriteAux);
    }

    return status;
}

/*============================================================================
 * OpcUa_BrowseNextResponse_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_BrowseNextResponse_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_BrowseNextResponse* a_pValue = (OpcUa_BrowseNextResponse*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_BrowseNextResponse_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfResults, (void**) &a_pValue->Results, sizeof(OpcUa_BrowseResult),
                                 (SOPC_EncodeableObject_PfnDecode*) OpcUa_BrowseResult_Decode,
                                 (SOPC_EncodeableObject_PfnInitialize*) OpcUa_BrowseResult_Initialize,
                                 (SOPC_EncodeableObject_PfnClear*) OpcUa_BrowseResult_Clear);
    }
    if (SOPC_STATUS_OK == status)
    {
        status =
            SOPC_Read_Array(buf, &a_pValue->NoOfDiagnosticInfos, (void**) &a_pValue->DiagnosticInfos,
                            sizeof(SOPC_DiagnosticInfo), (SOPC_EncodeableObject_PfnDecode*) SOPC_DiagnosticInfo_ReadAux,
                            (SOPC_EncodeableObject_PfnInitialize*) SOPC_DiagnosticInfo_InitializeAux,
                            (SOPC_EncodeableObject_PfnClear*) SOPC_DiagnosticInfo_ClearAux);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_BrowseNextResponse_Clear(a_pValue);
    }

    return status;
}
#endif
#endif

#ifndef OPCUA_EXCLUDE_RelativePathElement
/*============================================================================
 * OpcUa_RelativePathElement_Initialize
 *===========================================================================*/
void OpcUa_RelativePathElement_Initialize(void* pValue)
{
    OpcUa_RelativePathElement* a_pValue = (OpcUa_RelativePathElement*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_RelativePathElement_EncodeableType;
        SOPC_NodeId_Initialize(&a_pValue->ReferenceTypeId);
        SOPC_Boolean_Initialize(&a_pValue->IsInverse);
        SOPC_Boolean_Initialize(&a_pValue->IncludeSubtypes);
        SOPC_QualifiedName_Initialize(&a_pValue->TargetName);
    }
}

/*============================================================================
 * OpcUa_RelativePathElement_Clear
 *===========================================================================*/
void OpcUa_RelativePathElement_Clear(void* pValue)
{
    OpcUa_RelativePathElement* a_pValue = (OpcUa_RelativePathElement*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_NodeId_Clear(&a_pValue->ReferenceTypeId);
        SOPC_Boolean_Clear(&a_pValue->IsInverse);
        SOPC_Boolean_Clear(&a_pValue->IncludeSubtypes);
        SOPC_QualifiedName_Clear(&a_pValue->TargetName);
    }
}

/*============================================================================
 * OpcUa_RelativePathElement_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_RelativePathElement_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_RelativePathElement* a_pValue = (const OpcUa_RelativePathElement*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Write(&a_pValue->ReferenceTypeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Write(&a_pValue->IsInverse, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Write(&a_pValue->IncludeSubtypes, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_QualifiedName_Write(&a_pValue->TargetName, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_RelativePathElement_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_RelativePathElement_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_RelativePathElement* a_pValue = (OpcUa_RelativePathElement*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_RelativePathElement_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Read(&a_pValue->ReferenceTypeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Read(&a_pValue->IsInverse, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Read(&a_pValue->IncludeSubtypes, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_QualifiedName_Read(&a_pValue->TargetName, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_RelativePathElement_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_RelativePath
/*============================================================================
 * OpcUa_RelativePath_Initialize
 *===========================================================================*/
void OpcUa_RelativePath_Initialize(void* pValue)
{
    OpcUa_RelativePath* a_pValue = (OpcUa_RelativePath*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_RelativePath_EncodeableType;
        SOPC_Initialize_Array(&a_pValue->NoOfElements, (void**) &a_pValue->Elements, sizeof(OpcUa_RelativePathElement),
                              (SOPC_EncodeableObject_PfnInitialize*) OpcUa_RelativePathElement_Initialize);
    }
}

/*============================================================================
 * OpcUa_RelativePath_Clear
 *===========================================================================*/
void OpcUa_RelativePath_Clear(void* pValue)
{
    OpcUa_RelativePath* a_pValue = (OpcUa_RelativePath*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_Clear_Array(&a_pValue->NoOfElements, (void**) &a_pValue->Elements, sizeof(OpcUa_RelativePathElement),
                         (SOPC_EncodeableObject_PfnClear*) OpcUa_RelativePathElement_Clear);
    }
}

/*============================================================================
 * OpcUa_RelativePath_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_RelativePath_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_RelativePath* a_pValue = (const OpcUa_RelativePath*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->Elements;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfElements, &arr, sizeof(OpcUa_RelativePathElement),
                                  (SOPC_EncodeableObject_PfnEncode*) OpcUa_RelativePathElement_Encode);
    }

    return status;
}

/*============================================================================
 * OpcUa_RelativePath_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_RelativePath_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_RelativePath* a_pValue = (OpcUa_RelativePath*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_RelativePath_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfElements, (void**) &a_pValue->Elements,
                                 sizeof(OpcUa_RelativePathElement),
                                 (SOPC_EncodeableObject_PfnDecode*) OpcUa_RelativePathElement_Decode,
                                 (SOPC_EncodeableObject_PfnInitialize*) OpcUa_RelativePathElement_Initialize,
                                 (SOPC_EncodeableObject_PfnClear*) OpcUa_RelativePathElement_Clear);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_RelativePath_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_BrowsePath
/*============================================================================
 * OpcUa_BrowsePath_Initialize
 *===========================================================================*/
void OpcUa_BrowsePath_Initialize(void* pValue)
{
    OpcUa_BrowsePath* a_pValue = (OpcUa_BrowsePath*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_BrowsePath_EncodeableType;
        SOPC_NodeId_Initialize(&a_pValue->StartingNode);
        OpcUa_RelativePath_Initialize(&a_pValue->RelativePath);
    }
}

/*============================================================================
 * OpcUa_BrowsePath_Clear
 *===========================================================================*/
void OpcUa_BrowsePath_Clear(void* pValue)
{
    OpcUa_BrowsePath* a_pValue = (OpcUa_BrowsePath*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_NodeId_Clear(&a_pValue->StartingNode);
        OpcUa_RelativePath_Clear(&a_pValue->RelativePath);
    }
}

/*============================================================================
 * OpcUa_BrowsePath_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_BrowsePath_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_BrowsePath* a_pValue = (const OpcUa_BrowsePath*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Write(&a_pValue->StartingNode, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_RelativePath_Encode(&a_pValue->RelativePath, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_BrowsePath_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_BrowsePath_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_BrowsePath* a_pValue = (OpcUa_BrowsePath*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_BrowsePath_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Read(&a_pValue->StartingNode, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_RelativePath_Decode(&a_pValue->RelativePath, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_BrowsePath_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_BrowsePathTarget
/*============================================================================
 * OpcUa_BrowsePathTarget_Initialize
 *===========================================================================*/
void OpcUa_BrowsePathTarget_Initialize(void* pValue)
{
    OpcUa_BrowsePathTarget* a_pValue = (OpcUa_BrowsePathTarget*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_BrowsePathTarget_EncodeableType;
        SOPC_ExpandedNodeId_Initialize(&a_pValue->TargetId);
        SOPC_UInt32_Initialize(&a_pValue->RemainingPathIndex);
    }
}

/*============================================================================
 * OpcUa_BrowsePathTarget_Clear
 *===========================================================================*/
void OpcUa_BrowsePathTarget_Clear(void* pValue)
{
    OpcUa_BrowsePathTarget* a_pValue = (OpcUa_BrowsePathTarget*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_ExpandedNodeId_Clear(&a_pValue->TargetId);
        SOPC_UInt32_Clear(&a_pValue->RemainingPathIndex);
    }
}

/*============================================================================
 * OpcUa_BrowsePathTarget_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_BrowsePathTarget_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_BrowsePathTarget* a_pValue = (const OpcUa_BrowsePathTarget*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ExpandedNodeId_Write(&a_pValue->TargetId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->RemainingPathIndex, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_BrowsePathTarget_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_BrowsePathTarget_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_BrowsePathTarget* a_pValue = (OpcUa_BrowsePathTarget*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_BrowsePathTarget_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ExpandedNodeId_Read(&a_pValue->TargetId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->RemainingPathIndex, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_BrowsePathTarget_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_BrowsePathResult
/*============================================================================
 * OpcUa_BrowsePathResult_Initialize
 *===========================================================================*/
void OpcUa_BrowsePathResult_Initialize(void* pValue)
{
    OpcUa_BrowsePathResult* a_pValue = (OpcUa_BrowsePathResult*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_BrowsePathResult_EncodeableType;
        SOPC_StatusCode_Initialize(&a_pValue->StatusCode);
        SOPC_Initialize_Array(&a_pValue->NoOfTargets, (void**) &a_pValue->Targets, sizeof(OpcUa_BrowsePathTarget),
                              (SOPC_EncodeableObject_PfnInitialize*) OpcUa_BrowsePathTarget_Initialize);
    }
}

/*============================================================================
 * OpcUa_BrowsePathResult_Clear
 *===========================================================================*/
void OpcUa_BrowsePathResult_Clear(void* pValue)
{
    OpcUa_BrowsePathResult* a_pValue = (OpcUa_BrowsePathResult*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_StatusCode_Clear(&a_pValue->StatusCode);
        SOPC_Clear_Array(&a_pValue->NoOfTargets, (void**) &a_pValue->Targets, sizeof(OpcUa_BrowsePathTarget),
                         (SOPC_EncodeableObject_PfnClear*) OpcUa_BrowsePathTarget_Clear);
    }
}

/*============================================================================
 * OpcUa_BrowsePathResult_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_BrowsePathResult_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_BrowsePathResult* a_pValue = (const OpcUa_BrowsePathResult*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_StatusCode_Write(&a_pValue->StatusCode, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->Targets;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfTargets, &arr, sizeof(OpcUa_BrowsePathTarget),
                                  (SOPC_EncodeableObject_PfnEncode*) OpcUa_BrowsePathTarget_Encode);
    }

    return status;
}

/*============================================================================
 * OpcUa_BrowsePathResult_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_BrowsePathResult_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_BrowsePathResult* a_pValue = (OpcUa_BrowsePathResult*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_BrowsePathResult_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_StatusCode_Read(&a_pValue->StatusCode, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status =
            SOPC_Read_Array(buf, &a_pValue->NoOfTargets, (void**) &a_pValue->Targets, sizeof(OpcUa_BrowsePathTarget),
                            (SOPC_EncodeableObject_PfnDecode*) OpcUa_BrowsePathTarget_Decode,
                            (SOPC_EncodeableObject_PfnInitialize*) OpcUa_BrowsePathTarget_Initialize,
                            (SOPC_EncodeableObject_PfnClear*) OpcUa_BrowsePathTarget_Clear);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_BrowsePathResult_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_TranslateBrowsePathsToNodeIds
#ifndef OPCUA_EXCLUDE_TranslateBrowsePathsToNodeIdsRequest
/*============================================================================
 * OpcUa_TranslateBrowsePathsToNodeIdsRequest_Initialize
 *===========================================================================*/
void OpcUa_TranslateBrowsePathsToNodeIdsRequest_Initialize(void* pValue)
{
    OpcUa_TranslateBrowsePathsToNodeIdsRequest* a_pValue = (OpcUa_TranslateBrowsePathsToNodeIdsRequest*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_TranslateBrowsePathsToNodeIdsRequest_EncodeableType;
        SOPC_Initialize_Array(&a_pValue->NoOfBrowsePaths, (void**) &a_pValue->BrowsePaths, sizeof(OpcUa_BrowsePath),
                              (SOPC_EncodeableObject_PfnInitialize*) OpcUa_BrowsePath_Initialize);
    }
}

/*============================================================================
 * OpcUa_TranslateBrowsePathsToNodeIdsRequest_Clear
 *===========================================================================*/
void OpcUa_TranslateBrowsePathsToNodeIdsRequest_Clear(void* pValue)
{
    OpcUa_TranslateBrowsePathsToNodeIdsRequest* a_pValue = (OpcUa_TranslateBrowsePathsToNodeIdsRequest*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_Clear_Array(&a_pValue->NoOfBrowsePaths, (void**) &a_pValue->BrowsePaths, sizeof(OpcUa_BrowsePath),
                         (SOPC_EncodeableObject_PfnClear*) OpcUa_BrowsePath_Clear);
    }
}

/*============================================================================
 * OpcUa_TranslateBrowsePathsToNodeIdsRequest_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_TranslateBrowsePathsToNodeIdsRequest_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_TranslateBrowsePathsToNodeIdsRequest* a_pValue =
        (const OpcUa_TranslateBrowsePathsToNodeIdsRequest*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->BrowsePaths;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfBrowsePaths, &arr, sizeof(OpcUa_BrowsePath),
                                  (SOPC_EncodeableObject_PfnEncode*) OpcUa_BrowsePath_Encode);
    }

    return status;
}

/*============================================================================
 * OpcUa_TranslateBrowsePathsToNodeIdsRequest_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_TranslateBrowsePathsToNodeIdsRequest_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_TranslateBrowsePathsToNodeIdsRequest* a_pValue = (OpcUa_TranslateBrowsePathsToNodeIdsRequest*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_TranslateBrowsePathsToNodeIdsRequest_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfBrowsePaths, (void**) &a_pValue->BrowsePaths,
                                 sizeof(OpcUa_BrowsePath), (SOPC_EncodeableObject_PfnDecode*) OpcUa_BrowsePath_Decode,
                                 (SOPC_EncodeableObject_PfnInitialize*) OpcUa_BrowsePath_Initialize,
                                 (SOPC_EncodeableObject_PfnClear*) OpcUa_BrowsePath_Clear);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_TranslateBrowsePathsToNodeIdsRequest_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_TranslateBrowsePathsToNodeIdsResponse
/*============================================================================
 * OpcUa_TranslateBrowsePathsToNodeIdsResponse_Initialize
 *===========================================================================*/
void OpcUa_TranslateBrowsePathsToNodeIdsResponse_Initialize(void* pValue)
{
    OpcUa_TranslateBrowsePathsToNodeIdsResponse* a_pValue = (OpcUa_TranslateBrowsePathsToNodeIdsResponse*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_TranslateBrowsePathsToNodeIdsResponse_EncodeableType;
        OpcUa_ResponseHeader_Initialize(&a_pValue->ResponseHeader);
        SOPC_Initialize_Array(&a_pValue->NoOfResults, (void**) &a_pValue->Results, sizeof(OpcUa_BrowsePathResult),
                              (SOPC_EncodeableObject_PfnInitialize*) OpcUa_BrowsePathResult_Initialize);
        SOPC_Initialize_Array(&a_pValue->NoOfDiagnosticInfos, (void**) &a_pValue->DiagnosticInfos,
                              sizeof(SOPC_DiagnosticInfo),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_DiagnosticInfo_InitializeAux);
    }
}

/*============================================================================
 * OpcUa_TranslateBrowsePathsToNodeIdsResponse_Clear
 *===========================================================================*/
void OpcUa_TranslateBrowsePathsToNodeIdsResponse_Clear(void* pValue)
{
    OpcUa_TranslateBrowsePathsToNodeIdsResponse* a_pValue = (OpcUa_TranslateBrowsePathsToNodeIdsResponse*) pValue;
    if (a_pValue != NULL)
    {
        OpcUa_ResponseHeader_Clear(&a_pValue->ResponseHeader);
        SOPC_Clear_Array(&a_pValue->NoOfResults, (void**) &a_pValue->Results, sizeof(OpcUa_BrowsePathResult),
                         (SOPC_EncodeableObject_PfnClear*) OpcUa_BrowsePathResult_Clear);
        SOPC_Clear_Array(&a_pValue->NoOfDiagnosticInfos, (void**) &a_pValue->DiagnosticInfos,
                         sizeof(SOPC_DiagnosticInfo), (SOPC_EncodeableObject_PfnClear*) SOPC_DiagnosticInfo_ClearAux);
    }
}

/*============================================================================
 * OpcUa_TranslateBrowsePathsToNodeIdsResponse_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_TranslateBrowsePathsToNodeIdsResponse_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_TranslateBrowsePathsToNodeIdsResponse* a_pValue =
        (const OpcUa_TranslateBrowsePathsToNodeIdsResponse*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->Results;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfResults, &arr, sizeof(OpcUa_BrowsePathResult),
                                  (SOPC_EncodeableObject_PfnEncode*) OpcUa_BrowsePathResult_Encode);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->DiagnosticInfos;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfDiagnosticInfos, &arr, sizeof(SOPC_DiagnosticInfo),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_DiagnosticInfo_WriteAux);
    }

    return status;
}

/*============================================================================
 * OpcUa_TranslateBrowsePathsToNodeIdsResponse_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_TranslateBrowsePathsToNodeIdsResponse_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_TranslateBrowsePathsToNodeIdsResponse* a_pValue = (OpcUa_TranslateBrowsePathsToNodeIdsResponse*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_TranslateBrowsePathsToNodeIdsResponse_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status =
            SOPC_Read_Array(buf, &a_pValue->NoOfResults, (void**) &a_pValue->Results, sizeof(OpcUa_BrowsePathResult),
                            (SOPC_EncodeableObject_PfnDecode*) OpcUa_BrowsePathResult_Decode,
                            (SOPC_EncodeableObject_PfnInitialize*) OpcUa_BrowsePathResult_Initialize,
                            (SOPC_EncodeableObject_PfnClear*) OpcUa_BrowsePathResult_Clear);
    }
    if (SOPC_STATUS_OK == status)
    {
        status =
            SOPC_Read_Array(buf, &a_pValue->NoOfDiagnosticInfos, (void**) &a_pValue->DiagnosticInfos,
                            sizeof(SOPC_DiagnosticInfo), (SOPC_EncodeableObject_PfnDecode*) SOPC_DiagnosticInfo_ReadAux,
                            (SOPC_EncodeableObject_PfnInitialize*) SOPC_DiagnosticInfo_InitializeAux,
                            (SOPC_EncodeableObject_PfnClear*) SOPC_DiagnosticInfo_ClearAux);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_TranslateBrowsePathsToNodeIdsResponse_Clear(a_pValue);
    }

    return status;
}
#endif
#endif

#ifndef OPCUA_EXCLUDE_RegisterNodes
#ifndef OPCUA_EXCLUDE_RegisterNodesRequest
/*============================================================================
 * OpcUa_RegisterNodesRequest_Initialize
 *===========================================================================*/
void OpcUa_RegisterNodesRequest_Initialize(void* pValue)
{
    OpcUa_RegisterNodesRequest* a_pValue = (OpcUa_RegisterNodesRequest*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_RegisterNodesRequest_EncodeableType;
        SOPC_Initialize_Array(&a_pValue->NoOfNodesToRegister, (void**) &a_pValue->NodesToRegister, sizeof(SOPC_NodeId),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_NodeId_InitializeAux);
    }
}

/*============================================================================
 * OpcUa_RegisterNodesRequest_Clear
 *===========================================================================*/
void OpcUa_RegisterNodesRequest_Clear(void* pValue)
{
    OpcUa_RegisterNodesRequest* a_pValue = (OpcUa_RegisterNodesRequest*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_Clear_Array(&a_pValue->NoOfNodesToRegister, (void**) &a_pValue->NodesToRegister, sizeof(SOPC_NodeId),
                         (SOPC_EncodeableObject_PfnClear*) SOPC_NodeId_ClearAux);
    }
}

/*============================================================================
 * OpcUa_RegisterNodesRequest_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_RegisterNodesRequest_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_RegisterNodesRequest* a_pValue = (const OpcUa_RegisterNodesRequest*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->NodesToRegister;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfNodesToRegister, &arr, sizeof(SOPC_NodeId),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_NodeId_WriteAux);
    }

    return status;
}

/*============================================================================
 * OpcUa_RegisterNodesRequest_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_RegisterNodesRequest_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_RegisterNodesRequest* a_pValue = (OpcUa_RegisterNodesRequest*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_RegisterNodesRequest_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfNodesToRegister, (void**) &a_pValue->NodesToRegister,
                                 sizeof(SOPC_NodeId), (SOPC_EncodeableObject_PfnDecode*) SOPC_NodeId_ReadAux,
                                 (SOPC_EncodeableObject_PfnInitialize*) SOPC_NodeId_InitializeAux,
                                 (SOPC_EncodeableObject_PfnClear*) SOPC_NodeId_ClearAux);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_RegisterNodesRequest_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_RegisterNodesResponse
/*============================================================================
 * OpcUa_RegisterNodesResponse_Initialize
 *===========================================================================*/
void OpcUa_RegisterNodesResponse_Initialize(void* pValue)
{
    OpcUa_RegisterNodesResponse* a_pValue = (OpcUa_RegisterNodesResponse*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_RegisterNodesResponse_EncodeableType;
        OpcUa_ResponseHeader_Initialize(&a_pValue->ResponseHeader);
        SOPC_Initialize_Array(&a_pValue->NoOfRegisteredNodeIds, (void**) &a_pValue->RegisteredNodeIds,
                              sizeof(SOPC_NodeId), (SOPC_EncodeableObject_PfnInitialize*) SOPC_NodeId_InitializeAux);
    }
}

/*============================================================================
 * OpcUa_RegisterNodesResponse_Clear
 *===========================================================================*/
void OpcUa_RegisterNodesResponse_Clear(void* pValue)
{
    OpcUa_RegisterNodesResponse* a_pValue = (OpcUa_RegisterNodesResponse*) pValue;
    if (a_pValue != NULL)
    {
        OpcUa_ResponseHeader_Clear(&a_pValue->ResponseHeader);
        SOPC_Clear_Array(&a_pValue->NoOfRegisteredNodeIds, (void**) &a_pValue->RegisteredNodeIds, sizeof(SOPC_NodeId),
                         (SOPC_EncodeableObject_PfnClear*) SOPC_NodeId_ClearAux);
    }
}

/*============================================================================
 * OpcUa_RegisterNodesResponse_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_RegisterNodesResponse_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_RegisterNodesResponse* a_pValue = (const OpcUa_RegisterNodesResponse*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->RegisteredNodeIds;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfRegisteredNodeIds, &arr, sizeof(SOPC_NodeId),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_NodeId_WriteAux);
    }

    return status;
}

/*============================================================================
 * OpcUa_RegisterNodesResponse_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_RegisterNodesResponse_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_RegisterNodesResponse* a_pValue = (OpcUa_RegisterNodesResponse*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_RegisterNodesResponse_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfRegisteredNodeIds, (void**) &a_pValue->RegisteredNodeIds,
                                 sizeof(SOPC_NodeId), (SOPC_EncodeableObject_PfnDecode*) SOPC_NodeId_ReadAux,
                                 (SOPC_EncodeableObject_PfnInitialize*) SOPC_NodeId_InitializeAux,
                                 (SOPC_EncodeableObject_PfnClear*) SOPC_NodeId_ClearAux);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_RegisterNodesResponse_Clear(a_pValue);
    }

    return status;
}
#endif
#endif

#ifndef OPCUA_EXCLUDE_UnregisterNodes
#ifndef OPCUA_EXCLUDE_UnregisterNodesRequest
/*============================================================================
 * OpcUa_UnregisterNodesRequest_Initialize
 *===========================================================================*/
void OpcUa_UnregisterNodesRequest_Initialize(void* pValue)
{
    OpcUa_UnregisterNodesRequest* a_pValue = (OpcUa_UnregisterNodesRequest*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_UnregisterNodesRequest_EncodeableType;
        SOPC_Initialize_Array(&a_pValue->NoOfNodesToUnregister, (void**) &a_pValue->NodesToUnregister,
                              sizeof(SOPC_NodeId), (SOPC_EncodeableObject_PfnInitialize*) SOPC_NodeId_InitializeAux);
    }
}

/*============================================================================
 * OpcUa_UnregisterNodesRequest_Clear
 *===========================================================================*/
void OpcUa_UnregisterNodesRequest_Clear(void* pValue)
{
    OpcUa_UnregisterNodesRequest* a_pValue = (OpcUa_UnregisterNodesRequest*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_Clear_Array(&a_pValue->NoOfNodesToUnregister, (void**) &a_pValue->NodesToUnregister, sizeof(SOPC_NodeId),
                         (SOPC_EncodeableObject_PfnClear*) SOPC_NodeId_ClearAux);
    }
}

/*============================================================================
 * OpcUa_UnregisterNodesRequest_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_UnregisterNodesRequest_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_UnregisterNodesRequest* a_pValue = (const OpcUa_UnregisterNodesRequest*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->NodesToUnregister;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfNodesToUnregister, &arr, sizeof(SOPC_NodeId),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_NodeId_WriteAux);
    }

    return status;
}

/*============================================================================
 * OpcUa_UnregisterNodesRequest_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_UnregisterNodesRequest_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_UnregisterNodesRequest* a_pValue = (OpcUa_UnregisterNodesRequest*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_UnregisterNodesRequest_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfNodesToUnregister, (void**) &a_pValue->NodesToUnregister,
                                 sizeof(SOPC_NodeId), (SOPC_EncodeableObject_PfnDecode*) SOPC_NodeId_ReadAux,
                                 (SOPC_EncodeableObject_PfnInitialize*) SOPC_NodeId_InitializeAux,
                                 (SOPC_EncodeableObject_PfnClear*) SOPC_NodeId_ClearAux);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_UnregisterNodesRequest_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_UnregisterNodesResponse
/*============================================================================
 * OpcUa_UnregisterNodesResponse_Initialize
 *===========================================================================*/
void OpcUa_UnregisterNodesResponse_Initialize(void* pValue)
{
    OpcUa_UnregisterNodesResponse* a_pValue = (OpcUa_UnregisterNodesResponse*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_UnregisterNodesResponse_EncodeableType;
        OpcUa_ResponseHeader_Initialize(&a_pValue->ResponseHeader);
    }
}

/*============================================================================
 * OpcUa_UnregisterNodesResponse_Clear
 *===========================================================================*/
void OpcUa_UnregisterNodesResponse_Clear(void* pValue)
{
    OpcUa_UnregisterNodesResponse* a_pValue = (OpcUa_UnregisterNodesResponse*) pValue;
    if (a_pValue != NULL)
    {
        OpcUa_ResponseHeader_Clear(&a_pValue->ResponseHeader);
    }
}

/*============================================================================
 * OpcUa_UnregisterNodesResponse_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_UnregisterNodesResponse_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_UnregisterNodesResponse* a_pValue = (const OpcUa_UnregisterNodesResponse*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    return status;
}

/*============================================================================
 * OpcUa_UnregisterNodesResponse_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_UnregisterNodesResponse_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_UnregisterNodesResponse* a_pValue = (OpcUa_UnregisterNodesResponse*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_UnregisterNodesResponse_Initialize(a_pValue);

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_UnregisterNodesResponse_Clear(a_pValue);
    }

    return status;
}
#endif
#endif

#ifndef OPCUA_EXCLUDE_EndpointConfiguration
/*============================================================================
 * OpcUa_EndpointConfiguration_Initialize
 *===========================================================================*/
void OpcUa_EndpointConfiguration_Initialize(void* pValue)
{
    OpcUa_EndpointConfiguration* a_pValue = (OpcUa_EndpointConfiguration*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_EndpointConfiguration_EncodeableType;
        SOPC_Int32_Initialize(&a_pValue->OperationTimeout);
        SOPC_Boolean_Initialize(&a_pValue->UseBinaryEncoding);
        SOPC_Int32_Initialize(&a_pValue->MaxStringLength);
        SOPC_Int32_Initialize(&a_pValue->MaxByteStringLength);
        SOPC_Int32_Initialize(&a_pValue->MaxArrayLength);
        SOPC_Int32_Initialize(&a_pValue->MaxMessageSize);
        SOPC_Int32_Initialize(&a_pValue->MaxBufferSize);
        SOPC_Int32_Initialize(&a_pValue->ChannelLifetime);
        SOPC_Int32_Initialize(&a_pValue->SecurityTokenLifetime);
    }
}

/*============================================================================
 * OpcUa_EndpointConfiguration_Clear
 *===========================================================================*/
void OpcUa_EndpointConfiguration_Clear(void* pValue)
{
    OpcUa_EndpointConfiguration* a_pValue = (OpcUa_EndpointConfiguration*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_Int32_Clear(&a_pValue->OperationTimeout);
        SOPC_Boolean_Clear(&a_pValue->UseBinaryEncoding);
        SOPC_Int32_Clear(&a_pValue->MaxStringLength);
        SOPC_Int32_Clear(&a_pValue->MaxByteStringLength);
        SOPC_Int32_Clear(&a_pValue->MaxArrayLength);
        SOPC_Int32_Clear(&a_pValue->MaxMessageSize);
        SOPC_Int32_Clear(&a_pValue->MaxBufferSize);
        SOPC_Int32_Clear(&a_pValue->ChannelLifetime);
        SOPC_Int32_Clear(&a_pValue->SecurityTokenLifetime);
    }
}

/*============================================================================
 * OpcUa_EndpointConfiguration_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_EndpointConfiguration_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_EndpointConfiguration* a_pValue = (const OpcUa_EndpointConfiguration*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Int32_Write(&a_pValue->OperationTimeout, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Write(&a_pValue->UseBinaryEncoding, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Int32_Write(&a_pValue->MaxStringLength, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Int32_Write(&a_pValue->MaxByteStringLength, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Int32_Write(&a_pValue->MaxArrayLength, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Int32_Write(&a_pValue->MaxMessageSize, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Int32_Write(&a_pValue->MaxBufferSize, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Int32_Write(&a_pValue->ChannelLifetime, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Int32_Write(&a_pValue->SecurityTokenLifetime, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_EndpointConfiguration_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_EndpointConfiguration_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_EndpointConfiguration* a_pValue = (OpcUa_EndpointConfiguration*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_EndpointConfiguration_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Int32_Read(&a_pValue->OperationTimeout, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Read(&a_pValue->UseBinaryEncoding, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Int32_Read(&a_pValue->MaxStringLength, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Int32_Read(&a_pValue->MaxByteStringLength, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Int32_Read(&a_pValue->MaxArrayLength, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Int32_Read(&a_pValue->MaxMessageSize, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Int32_Read(&a_pValue->MaxBufferSize, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Int32_Read(&a_pValue->ChannelLifetime, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Int32_Read(&a_pValue->SecurityTokenLifetime, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_EndpointConfiguration_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_SupportedProfile
/*============================================================================
 * OpcUa_SupportedProfile_Initialize
 *===========================================================================*/
void OpcUa_SupportedProfile_Initialize(void* pValue)
{
    OpcUa_SupportedProfile* a_pValue = (OpcUa_SupportedProfile*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_SupportedProfile_EncodeableType;
        SOPC_String_Initialize(&a_pValue->OrganizationUri);
        SOPC_String_Initialize(&a_pValue->ProfileId);
        SOPC_String_Initialize(&a_pValue->ComplianceTool);
        SOPC_DateTime_Initialize(&a_pValue->ComplianceDate);
        SOPC_Initialize_EnumeratedType((int32_t*) &a_pValue->ComplianceLevel);
        SOPC_Initialize_Array(&a_pValue->NoOfUnsupportedUnitIds, (void**) &a_pValue->UnsupportedUnitIds,
                              sizeof(SOPC_String), (SOPC_EncodeableObject_PfnInitialize*) SOPC_String_InitializeAux);
    }
}

/*============================================================================
 * OpcUa_SupportedProfile_Clear
 *===========================================================================*/
void OpcUa_SupportedProfile_Clear(void* pValue)
{
    OpcUa_SupportedProfile* a_pValue = (OpcUa_SupportedProfile*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_String_Clear(&a_pValue->OrganizationUri);
        SOPC_String_Clear(&a_pValue->ProfileId);
        SOPC_String_Clear(&a_pValue->ComplianceTool);
        SOPC_DateTime_Clear(&a_pValue->ComplianceDate);
        SOPC_Clear_EnumeratedType((int32_t*) &a_pValue->ComplianceLevel);
        SOPC_Clear_Array(&a_pValue->NoOfUnsupportedUnitIds, (void**) &a_pValue->UnsupportedUnitIds, sizeof(SOPC_String),
                         (SOPC_EncodeableObject_PfnClear*) SOPC_String_ClearAux);
    }
}

/*============================================================================
 * OpcUa_SupportedProfile_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_SupportedProfile_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_SupportedProfile* a_pValue = (const OpcUa_SupportedProfile*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Write(&a_pValue->OrganizationUri, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Write(&a_pValue->ProfileId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Write(&a_pValue->ComplianceTool, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_DateTime_Write(&a_pValue->ComplianceDate, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Write_EnumeratedType(buf, (const int32_t*) &a_pValue->ComplianceLevel);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->UnsupportedUnitIds;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfUnsupportedUnitIds, &arr, sizeof(SOPC_String),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_String_WriteAux);
    }

    return status;
}

/*============================================================================
 * OpcUa_SupportedProfile_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_SupportedProfile_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_SupportedProfile* a_pValue = (OpcUa_SupportedProfile*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_SupportedProfile_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Read(&a_pValue->OrganizationUri, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Read(&a_pValue->ProfileId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Read(&a_pValue->ComplianceTool, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_DateTime_Read(&a_pValue->ComplianceDate, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_EnumeratedType(buf, (int32_t*) &a_pValue->ComplianceLevel);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfUnsupportedUnitIds, (void**) &a_pValue->UnsupportedUnitIds,
                                 sizeof(SOPC_String), (SOPC_EncodeableObject_PfnDecode*) SOPC_String_ReadAux,
                                 (SOPC_EncodeableObject_PfnInitialize*) SOPC_String_InitializeAux,
                                 (SOPC_EncodeableObject_PfnClear*) SOPC_String_ClearAux);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_SupportedProfile_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_SoftwareCertificate
/*============================================================================
 * OpcUa_SoftwareCertificate_Initialize
 *===========================================================================*/
void OpcUa_SoftwareCertificate_Initialize(void* pValue)
{
    OpcUa_SoftwareCertificate* a_pValue = (OpcUa_SoftwareCertificate*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_SoftwareCertificate_EncodeableType;
        SOPC_String_Initialize(&a_pValue->ProductName);
        SOPC_String_Initialize(&a_pValue->ProductUri);
        SOPC_String_Initialize(&a_pValue->VendorName);
        SOPC_ByteString_Initialize(&a_pValue->VendorProductCertificate);
        SOPC_String_Initialize(&a_pValue->SoftwareVersion);
        SOPC_String_Initialize(&a_pValue->BuildNumber);
        SOPC_DateTime_Initialize(&a_pValue->BuildDate);
        SOPC_String_Initialize(&a_pValue->IssuedBy);
        SOPC_DateTime_Initialize(&a_pValue->IssueDate);
        SOPC_Initialize_Array(&a_pValue->NoOfSupportedProfiles, (void**) &a_pValue->SupportedProfiles,
                              sizeof(OpcUa_SupportedProfile),
                              (SOPC_EncodeableObject_PfnInitialize*) OpcUa_SupportedProfile_Initialize);
    }
}

/*============================================================================
 * OpcUa_SoftwareCertificate_Clear
 *===========================================================================*/
void OpcUa_SoftwareCertificate_Clear(void* pValue)
{
    OpcUa_SoftwareCertificate* a_pValue = (OpcUa_SoftwareCertificate*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_String_Clear(&a_pValue->ProductName);
        SOPC_String_Clear(&a_pValue->ProductUri);
        SOPC_String_Clear(&a_pValue->VendorName);
        SOPC_ByteString_Clear(&a_pValue->VendorProductCertificate);
        SOPC_String_Clear(&a_pValue->SoftwareVersion);
        SOPC_String_Clear(&a_pValue->BuildNumber);
        SOPC_DateTime_Clear(&a_pValue->BuildDate);
        SOPC_String_Clear(&a_pValue->IssuedBy);
        SOPC_DateTime_Clear(&a_pValue->IssueDate);
        SOPC_Clear_Array(&a_pValue->NoOfSupportedProfiles, (void**) &a_pValue->SupportedProfiles,
                         sizeof(OpcUa_SupportedProfile),
                         (SOPC_EncodeableObject_PfnClear*) OpcUa_SupportedProfile_Clear);
    }
}

/*============================================================================
 * OpcUa_SoftwareCertificate_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_SoftwareCertificate_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_SoftwareCertificate* a_pValue = (const OpcUa_SoftwareCertificate*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Write(&a_pValue->ProductName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Write(&a_pValue->ProductUri, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Write(&a_pValue->VendorName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ByteString_Write(&a_pValue->VendorProductCertificate, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Write(&a_pValue->SoftwareVersion, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Write(&a_pValue->BuildNumber, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_DateTime_Write(&a_pValue->BuildDate, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Write(&a_pValue->IssuedBy, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_DateTime_Write(&a_pValue->IssueDate, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->SupportedProfiles;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfSupportedProfiles, &arr, sizeof(OpcUa_SupportedProfile),
                                  (SOPC_EncodeableObject_PfnEncode*) OpcUa_SupportedProfile_Encode);
    }

    return status;
}

/*============================================================================
 * OpcUa_SoftwareCertificate_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_SoftwareCertificate_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_SoftwareCertificate* a_pValue = (OpcUa_SoftwareCertificate*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_SoftwareCertificate_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Read(&a_pValue->ProductName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Read(&a_pValue->ProductUri, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Read(&a_pValue->VendorName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ByteString_Read(&a_pValue->VendorProductCertificate, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Read(&a_pValue->SoftwareVersion, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Read(&a_pValue->BuildNumber, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_DateTime_Read(&a_pValue->BuildDate, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Read(&a_pValue->IssuedBy, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_DateTime_Read(&a_pValue->IssueDate, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfSupportedProfiles, (void**) &a_pValue->SupportedProfiles,
                                 sizeof(OpcUa_SupportedProfile),
                                 (SOPC_EncodeableObject_PfnDecode*) OpcUa_SupportedProfile_Decode,
                                 (SOPC_EncodeableObject_PfnInitialize*) OpcUa_SupportedProfile_Initialize,
                                 (SOPC_EncodeableObject_PfnClear*) OpcUa_SupportedProfile_Clear);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_SoftwareCertificate_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_QueryDataDescription
/*============================================================================
 * OpcUa_QueryDataDescription_Initialize
 *===========================================================================*/
void OpcUa_QueryDataDescription_Initialize(void* pValue)
{
    OpcUa_QueryDataDescription* a_pValue = (OpcUa_QueryDataDescription*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_QueryDataDescription_EncodeableType;
        OpcUa_RelativePath_Initialize(&a_pValue->RelativePath);
        SOPC_UInt32_Initialize(&a_pValue->AttributeId);
        SOPC_String_Initialize(&a_pValue->IndexRange);
    }
}

/*============================================================================
 * OpcUa_QueryDataDescription_Clear
 *===========================================================================*/
void OpcUa_QueryDataDescription_Clear(void* pValue)
{
    OpcUa_QueryDataDescription* a_pValue = (OpcUa_QueryDataDescription*) pValue;
    if (a_pValue != NULL)
    {
        OpcUa_RelativePath_Clear(&a_pValue->RelativePath);
        SOPC_UInt32_Clear(&a_pValue->AttributeId);
        SOPC_String_Clear(&a_pValue->IndexRange);
    }
}

/*============================================================================
 * OpcUa_QueryDataDescription_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_QueryDataDescription_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_QueryDataDescription* a_pValue = (const OpcUa_QueryDataDescription*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_RelativePath_Encode(&a_pValue->RelativePath, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->AttributeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Write(&a_pValue->IndexRange, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_QueryDataDescription_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_QueryDataDescription_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_QueryDataDescription* a_pValue = (OpcUa_QueryDataDescription*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_QueryDataDescription_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_RelativePath_Decode(&a_pValue->RelativePath, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->AttributeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Read(&a_pValue->IndexRange, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_QueryDataDescription_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_NodeTypeDescription
/*============================================================================
 * OpcUa_NodeTypeDescription_Initialize
 *===========================================================================*/
void OpcUa_NodeTypeDescription_Initialize(void* pValue)
{
    OpcUa_NodeTypeDescription* a_pValue = (OpcUa_NodeTypeDescription*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_NodeTypeDescription_EncodeableType;
        SOPC_ExpandedNodeId_Initialize(&a_pValue->TypeDefinitionNode);
        SOPC_Boolean_Initialize(&a_pValue->IncludeSubTypes);
        SOPC_Initialize_Array(&a_pValue->NoOfDataToReturn, (void**) &a_pValue->DataToReturn,
                              sizeof(OpcUa_QueryDataDescription),
                              (SOPC_EncodeableObject_PfnInitialize*) OpcUa_QueryDataDescription_Initialize);
    }
}

/*============================================================================
 * OpcUa_NodeTypeDescription_Clear
 *===========================================================================*/
void OpcUa_NodeTypeDescription_Clear(void* pValue)
{
    OpcUa_NodeTypeDescription* a_pValue = (OpcUa_NodeTypeDescription*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_ExpandedNodeId_Clear(&a_pValue->TypeDefinitionNode);
        SOPC_Boolean_Clear(&a_pValue->IncludeSubTypes);
        SOPC_Clear_Array(&a_pValue->NoOfDataToReturn, (void**) &a_pValue->DataToReturn,
                         sizeof(OpcUa_QueryDataDescription),
                         (SOPC_EncodeableObject_PfnClear*) OpcUa_QueryDataDescription_Clear);
    }
}

/*============================================================================
 * OpcUa_NodeTypeDescription_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_NodeTypeDescription_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_NodeTypeDescription* a_pValue = (const OpcUa_NodeTypeDescription*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ExpandedNodeId_Write(&a_pValue->TypeDefinitionNode, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Write(&a_pValue->IncludeSubTypes, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->DataToReturn;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfDataToReturn, &arr, sizeof(OpcUa_QueryDataDescription),
                                  (SOPC_EncodeableObject_PfnEncode*) OpcUa_QueryDataDescription_Encode);
    }

    return status;
}

/*============================================================================
 * OpcUa_NodeTypeDescription_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_NodeTypeDescription_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_NodeTypeDescription* a_pValue = (OpcUa_NodeTypeDescription*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_NodeTypeDescription_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ExpandedNodeId_Read(&a_pValue->TypeDefinitionNode, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Read(&a_pValue->IncludeSubTypes, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfDataToReturn, (void**) &a_pValue->DataToReturn,
                                 sizeof(OpcUa_QueryDataDescription),
                                 (SOPC_EncodeableObject_PfnDecode*) OpcUa_QueryDataDescription_Decode,
                                 (SOPC_EncodeableObject_PfnInitialize*) OpcUa_QueryDataDescription_Initialize,
                                 (SOPC_EncodeableObject_PfnClear*) OpcUa_QueryDataDescription_Clear);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_NodeTypeDescription_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_QueryDataSet
/*============================================================================
 * OpcUa_QueryDataSet_Initialize
 *===========================================================================*/
void OpcUa_QueryDataSet_Initialize(void* pValue)
{
    OpcUa_QueryDataSet* a_pValue = (OpcUa_QueryDataSet*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_QueryDataSet_EncodeableType;
        SOPC_ExpandedNodeId_Initialize(&a_pValue->NodeId);
        SOPC_ExpandedNodeId_Initialize(&a_pValue->TypeDefinitionNode);
        SOPC_Initialize_Array(&a_pValue->NoOfValues, (void**) &a_pValue->Values, sizeof(SOPC_Variant),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_Variant_InitializeAux);
    }
}

/*============================================================================
 * OpcUa_QueryDataSet_Clear
 *===========================================================================*/
void OpcUa_QueryDataSet_Clear(void* pValue)
{
    OpcUa_QueryDataSet* a_pValue = (OpcUa_QueryDataSet*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_ExpandedNodeId_Clear(&a_pValue->NodeId);
        SOPC_ExpandedNodeId_Clear(&a_pValue->TypeDefinitionNode);
        SOPC_Clear_Array(&a_pValue->NoOfValues, (void**) &a_pValue->Values, sizeof(SOPC_Variant),
                         (SOPC_EncodeableObject_PfnClear*) SOPC_Variant_ClearAux);
    }
}

/*============================================================================
 * OpcUa_QueryDataSet_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_QueryDataSet_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_QueryDataSet* a_pValue = (const OpcUa_QueryDataSet*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ExpandedNodeId_Write(&a_pValue->NodeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ExpandedNodeId_Write(&a_pValue->TypeDefinitionNode, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->Values;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfValues, &arr, sizeof(SOPC_Variant),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_Variant_WriteAux);
    }

    return status;
}

/*============================================================================
 * OpcUa_QueryDataSet_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_QueryDataSet_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_QueryDataSet* a_pValue = (OpcUa_QueryDataSet*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_QueryDataSet_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ExpandedNodeId_Read(&a_pValue->NodeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ExpandedNodeId_Read(&a_pValue->TypeDefinitionNode, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfValues, (void**) &a_pValue->Values, sizeof(SOPC_Variant),
                                 (SOPC_EncodeableObject_PfnDecode*) SOPC_Variant_ReadAux,
                                 (SOPC_EncodeableObject_PfnInitialize*) SOPC_Variant_InitializeAux,
                                 (SOPC_EncodeableObject_PfnClear*) SOPC_Variant_ClearAux);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_QueryDataSet_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_NodeReference
/*============================================================================
 * OpcUa_NodeReference_Initialize
 *===========================================================================*/
void OpcUa_NodeReference_Initialize(void* pValue)
{
    OpcUa_NodeReference* a_pValue = (OpcUa_NodeReference*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_NodeReference_EncodeableType;
        SOPC_NodeId_Initialize(&a_pValue->NodeId);
        SOPC_NodeId_Initialize(&a_pValue->ReferenceTypeId);
        SOPC_Boolean_Initialize(&a_pValue->IsForward);
        SOPC_Initialize_Array(&a_pValue->NoOfReferencedNodeIds, (void**) &a_pValue->ReferencedNodeIds,
                              sizeof(SOPC_NodeId), (SOPC_EncodeableObject_PfnInitialize*) SOPC_NodeId_InitializeAux);
    }
}

/*============================================================================
 * OpcUa_NodeReference_Clear
 *===========================================================================*/
void OpcUa_NodeReference_Clear(void* pValue)
{
    OpcUa_NodeReference* a_pValue = (OpcUa_NodeReference*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_NodeId_Clear(&a_pValue->NodeId);
        SOPC_NodeId_Clear(&a_pValue->ReferenceTypeId);
        SOPC_Boolean_Clear(&a_pValue->IsForward);
        SOPC_Clear_Array(&a_pValue->NoOfReferencedNodeIds, (void**) &a_pValue->ReferencedNodeIds, sizeof(SOPC_NodeId),
                         (SOPC_EncodeableObject_PfnClear*) SOPC_NodeId_ClearAux);
    }
}

/*============================================================================
 * OpcUa_NodeReference_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_NodeReference_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_NodeReference* a_pValue = (const OpcUa_NodeReference*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Write(&a_pValue->NodeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Write(&a_pValue->ReferenceTypeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Write(&a_pValue->IsForward, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->ReferencedNodeIds;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfReferencedNodeIds, &arr, sizeof(SOPC_NodeId),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_NodeId_WriteAux);
    }

    return status;
}

/*============================================================================
 * OpcUa_NodeReference_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_NodeReference_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_NodeReference* a_pValue = (OpcUa_NodeReference*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_NodeReference_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Read(&a_pValue->NodeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Read(&a_pValue->ReferenceTypeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Read(&a_pValue->IsForward, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfReferencedNodeIds, (void**) &a_pValue->ReferencedNodeIds,
                                 sizeof(SOPC_NodeId), (SOPC_EncodeableObject_PfnDecode*) SOPC_NodeId_ReadAux,
                                 (SOPC_EncodeableObject_PfnInitialize*) SOPC_NodeId_InitializeAux,
                                 (SOPC_EncodeableObject_PfnClear*) SOPC_NodeId_ClearAux);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_NodeReference_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_ContentFilterElement
/*============================================================================
 * OpcUa_ContentFilterElement_Initialize
 *===========================================================================*/
void OpcUa_ContentFilterElement_Initialize(void* pValue)
{
    OpcUa_ContentFilterElement* a_pValue = (OpcUa_ContentFilterElement*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_ContentFilterElement_EncodeableType;
        SOPC_Initialize_EnumeratedType((int32_t*) &a_pValue->FilterOperator);
        SOPC_Initialize_Array(&a_pValue->NoOfFilterOperands, (void**) &a_pValue->FilterOperands,
                              sizeof(SOPC_ExtensionObject),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_ExtensionObject_InitializeAux);
    }
}

/*============================================================================
 * OpcUa_ContentFilterElement_Clear
 *===========================================================================*/
void OpcUa_ContentFilterElement_Clear(void* pValue)
{
    OpcUa_ContentFilterElement* a_pValue = (OpcUa_ContentFilterElement*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_Clear_EnumeratedType((int32_t*) &a_pValue->FilterOperator);
        SOPC_Clear_Array(&a_pValue->NoOfFilterOperands, (void**) &a_pValue->FilterOperands,
                         sizeof(SOPC_ExtensionObject), (SOPC_EncodeableObject_PfnClear*) SOPC_ExtensionObject_ClearAux);
    }
}

/*============================================================================
 * OpcUa_ContentFilterElement_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_ContentFilterElement_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_ContentFilterElement* a_pValue = (const OpcUa_ContentFilterElement*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Write_EnumeratedType(buf, (const int32_t*) &a_pValue->FilterOperator);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->FilterOperands;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfFilterOperands, &arr, sizeof(SOPC_ExtensionObject),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_ExtensionObject_WriteAux);
    }

    return status;
}

/*============================================================================
 * OpcUa_ContentFilterElement_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_ContentFilterElement_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_ContentFilterElement* a_pValue = (OpcUa_ContentFilterElement*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_ContentFilterElement_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_EnumeratedType(buf, (int32_t*) &a_pValue->FilterOperator);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfFilterOperands, (void**) &a_pValue->FilterOperands,
                                 sizeof(SOPC_ExtensionObject),
                                 (SOPC_EncodeableObject_PfnDecode*) SOPC_ExtensionObject_ReadAux,
                                 (SOPC_EncodeableObject_PfnInitialize*) SOPC_ExtensionObject_InitializeAux,
                                 (SOPC_EncodeableObject_PfnClear*) SOPC_ExtensionObject_ClearAux);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_ContentFilterElement_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_ContentFilter
/*============================================================================
 * OpcUa_ContentFilter_Initialize
 *===========================================================================*/
void OpcUa_ContentFilter_Initialize(void* pValue)
{
    OpcUa_ContentFilter* a_pValue = (OpcUa_ContentFilter*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_ContentFilter_EncodeableType;
        SOPC_Initialize_Array(&a_pValue->NoOfElements, (void**) &a_pValue->Elements, sizeof(OpcUa_ContentFilterElement),
                              (SOPC_EncodeableObject_PfnInitialize*) OpcUa_ContentFilterElement_Initialize);
    }
}

/*============================================================================
 * OpcUa_ContentFilter_Clear
 *===========================================================================*/
void OpcUa_ContentFilter_Clear(void* pValue)
{
    OpcUa_ContentFilter* a_pValue = (OpcUa_ContentFilter*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_Clear_Array(&a_pValue->NoOfElements, (void**) &a_pValue->Elements, sizeof(OpcUa_ContentFilterElement),
                         (SOPC_EncodeableObject_PfnClear*) OpcUa_ContentFilterElement_Clear);
    }
}

/*============================================================================
 * OpcUa_ContentFilter_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_ContentFilter_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_ContentFilter* a_pValue = (const OpcUa_ContentFilter*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->Elements;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfElements, &arr, sizeof(OpcUa_ContentFilterElement),
                                  (SOPC_EncodeableObject_PfnEncode*) OpcUa_ContentFilterElement_Encode);
    }

    return status;
}

/*============================================================================
 * OpcUa_ContentFilter_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_ContentFilter_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_ContentFilter* a_pValue = (OpcUa_ContentFilter*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_ContentFilter_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfElements, (void**) &a_pValue->Elements,
                                 sizeof(OpcUa_ContentFilterElement),
                                 (SOPC_EncodeableObject_PfnDecode*) OpcUa_ContentFilterElement_Decode,
                                 (SOPC_EncodeableObject_PfnInitialize*) OpcUa_ContentFilterElement_Initialize,
                                 (SOPC_EncodeableObject_PfnClear*) OpcUa_ContentFilterElement_Clear);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_ContentFilter_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_ElementOperand
/*============================================================================
 * OpcUa_ElementOperand_Initialize
 *===========================================================================*/
void OpcUa_ElementOperand_Initialize(void* pValue)
{
    OpcUa_ElementOperand* a_pValue = (OpcUa_ElementOperand*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_ElementOperand_EncodeableType;
        SOPC_UInt32_Initialize(&a_pValue->Index);
    }
}

/*============================================================================
 * OpcUa_ElementOperand_Clear
 *===========================================================================*/
void OpcUa_ElementOperand_Clear(void* pValue)
{
    OpcUa_ElementOperand* a_pValue = (OpcUa_ElementOperand*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_UInt32_Clear(&a_pValue->Index);
    }
}

/*============================================================================
 * OpcUa_ElementOperand_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_ElementOperand_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_ElementOperand* a_pValue = (const OpcUa_ElementOperand*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->Index, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_ElementOperand_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_ElementOperand_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_ElementOperand* a_pValue = (OpcUa_ElementOperand*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_ElementOperand_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->Index, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_ElementOperand_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_LiteralOperand
/*============================================================================
 * OpcUa_LiteralOperand_Initialize
 *===========================================================================*/
void OpcUa_LiteralOperand_Initialize(void* pValue)
{
    OpcUa_LiteralOperand* a_pValue = (OpcUa_LiteralOperand*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_LiteralOperand_EncodeableType;
        SOPC_Variant_Initialize(&a_pValue->Value);
    }
}

/*============================================================================
 * OpcUa_LiteralOperand_Clear
 *===========================================================================*/
void OpcUa_LiteralOperand_Clear(void* pValue)
{
    OpcUa_LiteralOperand* a_pValue = (OpcUa_LiteralOperand*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_Variant_Clear(&a_pValue->Value);
    }
}

/*============================================================================
 * OpcUa_LiteralOperand_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_LiteralOperand_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_LiteralOperand* a_pValue = (const OpcUa_LiteralOperand*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Variant_Write(&a_pValue->Value, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_LiteralOperand_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_LiteralOperand_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_LiteralOperand* a_pValue = (OpcUa_LiteralOperand*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_LiteralOperand_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Variant_Read(&a_pValue->Value, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_LiteralOperand_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_AttributeOperand
/*============================================================================
 * OpcUa_AttributeOperand_Initialize
 *===========================================================================*/
void OpcUa_AttributeOperand_Initialize(void* pValue)
{
    OpcUa_AttributeOperand* a_pValue = (OpcUa_AttributeOperand*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_AttributeOperand_EncodeableType;
        SOPC_NodeId_Initialize(&a_pValue->NodeId);
        SOPC_String_Initialize(&a_pValue->Alias);
        OpcUa_RelativePath_Initialize(&a_pValue->BrowsePath);
        SOPC_UInt32_Initialize(&a_pValue->AttributeId);
        SOPC_String_Initialize(&a_pValue->IndexRange);
    }
}

/*============================================================================
 * OpcUa_AttributeOperand_Clear
 *===========================================================================*/
void OpcUa_AttributeOperand_Clear(void* pValue)
{
    OpcUa_AttributeOperand* a_pValue = (OpcUa_AttributeOperand*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_NodeId_Clear(&a_pValue->NodeId);
        SOPC_String_Clear(&a_pValue->Alias);
        OpcUa_RelativePath_Clear(&a_pValue->BrowsePath);
        SOPC_UInt32_Clear(&a_pValue->AttributeId);
        SOPC_String_Clear(&a_pValue->IndexRange);
    }
}

/*============================================================================
 * OpcUa_AttributeOperand_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_AttributeOperand_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_AttributeOperand* a_pValue = (const OpcUa_AttributeOperand*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Write(&a_pValue->NodeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Write(&a_pValue->Alias, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_RelativePath_Encode(&a_pValue->BrowsePath, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->AttributeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Write(&a_pValue->IndexRange, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_AttributeOperand_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_AttributeOperand_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_AttributeOperand* a_pValue = (OpcUa_AttributeOperand*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_AttributeOperand_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Read(&a_pValue->NodeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Read(&a_pValue->Alias, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_RelativePath_Decode(&a_pValue->BrowsePath, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->AttributeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Read(&a_pValue->IndexRange, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_AttributeOperand_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_SimpleAttributeOperand
/*============================================================================
 * OpcUa_SimpleAttributeOperand_Initialize
 *===========================================================================*/
void OpcUa_SimpleAttributeOperand_Initialize(void* pValue)
{
    OpcUa_SimpleAttributeOperand* a_pValue = (OpcUa_SimpleAttributeOperand*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_SimpleAttributeOperand_EncodeableType;
        SOPC_NodeId_Initialize(&a_pValue->TypeDefinitionId);
        SOPC_Initialize_Array(&a_pValue->NoOfBrowsePath, (void**) &a_pValue->BrowsePath, sizeof(SOPC_QualifiedName),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_QualifiedName_InitializeAux);
        SOPC_UInt32_Initialize(&a_pValue->AttributeId);
        SOPC_String_Initialize(&a_pValue->IndexRange);
    }
}

/*============================================================================
 * OpcUa_SimpleAttributeOperand_Clear
 *===========================================================================*/
void OpcUa_SimpleAttributeOperand_Clear(void* pValue)
{
    OpcUa_SimpleAttributeOperand* a_pValue = (OpcUa_SimpleAttributeOperand*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_NodeId_Clear(&a_pValue->TypeDefinitionId);
        SOPC_Clear_Array(&a_pValue->NoOfBrowsePath, (void**) &a_pValue->BrowsePath, sizeof(SOPC_QualifiedName),
                         (SOPC_EncodeableObject_PfnClear*) SOPC_QualifiedName_ClearAux);
        SOPC_UInt32_Clear(&a_pValue->AttributeId);
        SOPC_String_Clear(&a_pValue->IndexRange);
    }
}

/*============================================================================
 * OpcUa_SimpleAttributeOperand_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_SimpleAttributeOperand_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_SimpleAttributeOperand* a_pValue = (const OpcUa_SimpleAttributeOperand*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Write(&a_pValue->TypeDefinitionId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->BrowsePath;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfBrowsePath, &arr, sizeof(SOPC_QualifiedName),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_QualifiedName_WriteAux);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->AttributeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Write(&a_pValue->IndexRange, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_SimpleAttributeOperand_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_SimpleAttributeOperand_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_SimpleAttributeOperand* a_pValue = (OpcUa_SimpleAttributeOperand*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_SimpleAttributeOperand_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Read(&a_pValue->TypeDefinitionId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status =
            SOPC_Read_Array(buf, &a_pValue->NoOfBrowsePath, (void**) &a_pValue->BrowsePath, sizeof(SOPC_QualifiedName),
                            (SOPC_EncodeableObject_PfnDecode*) SOPC_QualifiedName_ReadAux,
                            (SOPC_EncodeableObject_PfnInitialize*) SOPC_QualifiedName_InitializeAux,
                            (SOPC_EncodeableObject_PfnClear*) SOPC_QualifiedName_ClearAux);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->AttributeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Read(&a_pValue->IndexRange, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_SimpleAttributeOperand_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_ContentFilterElementResult
/*============================================================================
 * OpcUa_ContentFilterElementResult_Initialize
 *===========================================================================*/
void OpcUa_ContentFilterElementResult_Initialize(void* pValue)
{
    OpcUa_ContentFilterElementResult* a_pValue = (OpcUa_ContentFilterElementResult*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_ContentFilterElementResult_EncodeableType;
        SOPC_StatusCode_Initialize(&a_pValue->StatusCode);
        SOPC_Initialize_Array(&a_pValue->NoOfOperandStatusCodes, (void**) &a_pValue->OperandStatusCodes,
                              sizeof(SOPC_StatusCode),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_StatusCode_InitializeAux);
        SOPC_Initialize_Array(&a_pValue->NoOfOperandDiagnosticInfos, (void**) &a_pValue->OperandDiagnosticInfos,
                              sizeof(SOPC_DiagnosticInfo),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_DiagnosticInfo_InitializeAux);
    }
}

/*============================================================================
 * OpcUa_ContentFilterElementResult_Clear
 *===========================================================================*/
void OpcUa_ContentFilterElementResult_Clear(void* pValue)
{
    OpcUa_ContentFilterElementResult* a_pValue = (OpcUa_ContentFilterElementResult*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_StatusCode_Clear(&a_pValue->StatusCode);
        SOPC_Clear_Array(&a_pValue->NoOfOperandStatusCodes, (void**) &a_pValue->OperandStatusCodes,
                         sizeof(SOPC_StatusCode), (SOPC_EncodeableObject_PfnClear*) SOPC_StatusCode_ClearAux);
        SOPC_Clear_Array(&a_pValue->NoOfOperandDiagnosticInfos, (void**) &a_pValue->OperandDiagnosticInfos,
                         sizeof(SOPC_DiagnosticInfo), (SOPC_EncodeableObject_PfnClear*) SOPC_DiagnosticInfo_ClearAux);
    }
}

/*============================================================================
 * OpcUa_ContentFilterElementResult_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_ContentFilterElementResult_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_ContentFilterElementResult* a_pValue = (const OpcUa_ContentFilterElementResult*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_StatusCode_Write(&a_pValue->StatusCode, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->OperandStatusCodes;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfOperandStatusCodes, &arr, sizeof(SOPC_StatusCode),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_StatusCode_WriteAux);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->OperandDiagnosticInfos;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfOperandDiagnosticInfos, &arr, sizeof(SOPC_DiagnosticInfo),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_DiagnosticInfo_WriteAux);
    }

    return status;
}

/*============================================================================
 * OpcUa_ContentFilterElementResult_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_ContentFilterElementResult_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_ContentFilterElementResult* a_pValue = (OpcUa_ContentFilterElementResult*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_ContentFilterElementResult_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_StatusCode_Read(&a_pValue->StatusCode, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfOperandStatusCodes, (void**) &a_pValue->OperandStatusCodes,
                                 sizeof(SOPC_StatusCode), (SOPC_EncodeableObject_PfnDecode*) SOPC_StatusCode_ReadAux,
                                 (SOPC_EncodeableObject_PfnInitialize*) SOPC_StatusCode_InitializeAux,
                                 (SOPC_EncodeableObject_PfnClear*) SOPC_StatusCode_ClearAux);
    }
    if (SOPC_STATUS_OK == status)
    {
        status =
            SOPC_Read_Array(buf, &a_pValue->NoOfOperandDiagnosticInfos, (void**) &a_pValue->OperandDiagnosticInfos,
                            sizeof(SOPC_DiagnosticInfo), (SOPC_EncodeableObject_PfnDecode*) SOPC_DiagnosticInfo_ReadAux,
                            (SOPC_EncodeableObject_PfnInitialize*) SOPC_DiagnosticInfo_InitializeAux,
                            (SOPC_EncodeableObject_PfnClear*) SOPC_DiagnosticInfo_ClearAux);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_ContentFilterElementResult_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_ContentFilterResult
/*============================================================================
 * OpcUa_ContentFilterResult_Initialize
 *===========================================================================*/
void OpcUa_ContentFilterResult_Initialize(void* pValue)
{
    OpcUa_ContentFilterResult* a_pValue = (OpcUa_ContentFilterResult*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_ContentFilterResult_EncodeableType;
        SOPC_Initialize_Array(&a_pValue->NoOfElementResults, (void**) &a_pValue->ElementResults,
                              sizeof(OpcUa_ContentFilterElementResult),
                              (SOPC_EncodeableObject_PfnInitialize*) OpcUa_ContentFilterElementResult_Initialize);
        SOPC_Initialize_Array(&a_pValue->NoOfElementDiagnosticInfos, (void**) &a_pValue->ElementDiagnosticInfos,
                              sizeof(SOPC_DiagnosticInfo),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_DiagnosticInfo_InitializeAux);
    }
}

/*============================================================================
 * OpcUa_ContentFilterResult_Clear
 *===========================================================================*/
void OpcUa_ContentFilterResult_Clear(void* pValue)
{
    OpcUa_ContentFilterResult* a_pValue = (OpcUa_ContentFilterResult*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_Clear_Array(&a_pValue->NoOfElementResults, (void**) &a_pValue->ElementResults,
                         sizeof(OpcUa_ContentFilterElementResult),
                         (SOPC_EncodeableObject_PfnClear*) OpcUa_ContentFilterElementResult_Clear);
        SOPC_Clear_Array(&a_pValue->NoOfElementDiagnosticInfos, (void**) &a_pValue->ElementDiagnosticInfos,
                         sizeof(SOPC_DiagnosticInfo), (SOPC_EncodeableObject_PfnClear*) SOPC_DiagnosticInfo_ClearAux);
    }
}

/*============================================================================
 * OpcUa_ContentFilterResult_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_ContentFilterResult_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_ContentFilterResult* a_pValue = (const OpcUa_ContentFilterResult*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->ElementResults;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfElementResults, &arr, sizeof(OpcUa_ContentFilterElementResult),
                                  (SOPC_EncodeableObject_PfnEncode*) OpcUa_ContentFilterElementResult_Encode);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->ElementDiagnosticInfos;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfElementDiagnosticInfos, &arr, sizeof(SOPC_DiagnosticInfo),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_DiagnosticInfo_WriteAux);
    }

    return status;
}

/*============================================================================
 * OpcUa_ContentFilterResult_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_ContentFilterResult_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_ContentFilterResult* a_pValue = (OpcUa_ContentFilterResult*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_ContentFilterResult_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfElementResults, (void**) &a_pValue->ElementResults,
                                 sizeof(OpcUa_ContentFilterElementResult),
                                 (SOPC_EncodeableObject_PfnDecode*) OpcUa_ContentFilterElementResult_Decode,
                                 (SOPC_EncodeableObject_PfnInitialize*) OpcUa_ContentFilterElementResult_Initialize,
                                 (SOPC_EncodeableObject_PfnClear*) OpcUa_ContentFilterElementResult_Clear);
    }
    if (SOPC_STATUS_OK == status)
    {
        status =
            SOPC_Read_Array(buf, &a_pValue->NoOfElementDiagnosticInfos, (void**) &a_pValue->ElementDiagnosticInfos,
                            sizeof(SOPC_DiagnosticInfo), (SOPC_EncodeableObject_PfnDecode*) SOPC_DiagnosticInfo_ReadAux,
                            (SOPC_EncodeableObject_PfnInitialize*) SOPC_DiagnosticInfo_InitializeAux,
                            (SOPC_EncodeableObject_PfnClear*) SOPC_DiagnosticInfo_ClearAux);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_ContentFilterResult_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_ParsingResult
/*============================================================================
 * OpcUa_ParsingResult_Initialize
 *===========================================================================*/
void OpcUa_ParsingResult_Initialize(void* pValue)
{
    OpcUa_ParsingResult* a_pValue = (OpcUa_ParsingResult*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_ParsingResult_EncodeableType;
        SOPC_StatusCode_Initialize(&a_pValue->StatusCode);
        SOPC_Initialize_Array(&a_pValue->NoOfDataStatusCodes, (void**) &a_pValue->DataStatusCodes,
                              sizeof(SOPC_StatusCode),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_StatusCode_InitializeAux);
        SOPC_Initialize_Array(&a_pValue->NoOfDataDiagnosticInfos, (void**) &a_pValue->DataDiagnosticInfos,
                              sizeof(SOPC_DiagnosticInfo),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_DiagnosticInfo_InitializeAux);
    }
}

/*============================================================================
 * OpcUa_ParsingResult_Clear
 *===========================================================================*/
void OpcUa_ParsingResult_Clear(void* pValue)
{
    OpcUa_ParsingResult* a_pValue = (OpcUa_ParsingResult*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_StatusCode_Clear(&a_pValue->StatusCode);
        SOPC_Clear_Array(&a_pValue->NoOfDataStatusCodes, (void**) &a_pValue->DataStatusCodes, sizeof(SOPC_StatusCode),
                         (SOPC_EncodeableObject_PfnClear*) SOPC_StatusCode_ClearAux);
        SOPC_Clear_Array(&a_pValue->NoOfDataDiagnosticInfos, (void**) &a_pValue->DataDiagnosticInfos,
                         sizeof(SOPC_DiagnosticInfo), (SOPC_EncodeableObject_PfnClear*) SOPC_DiagnosticInfo_ClearAux);
    }
}

/*============================================================================
 * OpcUa_ParsingResult_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_ParsingResult_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_ParsingResult* a_pValue = (const OpcUa_ParsingResult*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_StatusCode_Write(&a_pValue->StatusCode, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->DataStatusCodes;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfDataStatusCodes, &arr, sizeof(SOPC_StatusCode),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_StatusCode_WriteAux);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->DataDiagnosticInfos;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfDataDiagnosticInfos, &arr, sizeof(SOPC_DiagnosticInfo),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_DiagnosticInfo_WriteAux);
    }

    return status;
}

/*============================================================================
 * OpcUa_ParsingResult_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_ParsingResult_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_ParsingResult* a_pValue = (OpcUa_ParsingResult*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_ParsingResult_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_StatusCode_Read(&a_pValue->StatusCode, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfDataStatusCodes, (void**) &a_pValue->DataStatusCodes,
                                 sizeof(SOPC_StatusCode), (SOPC_EncodeableObject_PfnDecode*) SOPC_StatusCode_ReadAux,
                                 (SOPC_EncodeableObject_PfnInitialize*) SOPC_StatusCode_InitializeAux,
                                 (SOPC_EncodeableObject_PfnClear*) SOPC_StatusCode_ClearAux);
    }
    if (SOPC_STATUS_OK == status)
    {
        status =
            SOPC_Read_Array(buf, &a_pValue->NoOfDataDiagnosticInfos, (void**) &a_pValue->DataDiagnosticInfos,
                            sizeof(SOPC_DiagnosticInfo), (SOPC_EncodeableObject_PfnDecode*) SOPC_DiagnosticInfo_ReadAux,
                            (SOPC_EncodeableObject_PfnInitialize*) SOPC_DiagnosticInfo_InitializeAux,
                            (SOPC_EncodeableObject_PfnClear*) SOPC_DiagnosticInfo_ClearAux);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_ParsingResult_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_QueryFirst
#ifndef OPCUA_EXCLUDE_QueryFirstRequest
/*============================================================================
 * OpcUa_QueryFirstRequest_Initialize
 *===========================================================================*/
void OpcUa_QueryFirstRequest_Initialize(void* pValue)
{
    OpcUa_QueryFirstRequest* a_pValue = (OpcUa_QueryFirstRequest*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_QueryFirstRequest_EncodeableType;
        OpcUa_ViewDescription_Initialize(&a_pValue->View);
        SOPC_Initialize_Array(&a_pValue->NoOfNodeTypes, (void**) &a_pValue->NodeTypes,
                              sizeof(OpcUa_NodeTypeDescription),
                              (SOPC_EncodeableObject_PfnInitialize*) OpcUa_NodeTypeDescription_Initialize);
        OpcUa_ContentFilter_Initialize(&a_pValue->Filter);
        SOPC_UInt32_Initialize(&a_pValue->MaxDataSetsToReturn);
        SOPC_UInt32_Initialize(&a_pValue->MaxReferencesToReturn);
    }
}

/*============================================================================
 * OpcUa_QueryFirstRequest_Clear
 *===========================================================================*/
void OpcUa_QueryFirstRequest_Clear(void* pValue)
{
    OpcUa_QueryFirstRequest* a_pValue = (OpcUa_QueryFirstRequest*) pValue;
    if (a_pValue != NULL)
    {
        OpcUa_ViewDescription_Clear(&a_pValue->View);
        SOPC_Clear_Array(&a_pValue->NoOfNodeTypes, (void**) &a_pValue->NodeTypes, sizeof(OpcUa_NodeTypeDescription),
                         (SOPC_EncodeableObject_PfnClear*) OpcUa_NodeTypeDescription_Clear);
        OpcUa_ContentFilter_Clear(&a_pValue->Filter);
        SOPC_UInt32_Clear(&a_pValue->MaxDataSetsToReturn);
        SOPC_UInt32_Clear(&a_pValue->MaxReferencesToReturn);
    }
}

/*============================================================================
 * OpcUa_QueryFirstRequest_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_QueryFirstRequest_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_QueryFirstRequest* a_pValue = (const OpcUa_QueryFirstRequest*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_ViewDescription_Encode(&a_pValue->View, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->NodeTypes;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfNodeTypes, &arr, sizeof(OpcUa_NodeTypeDescription),
                                  (SOPC_EncodeableObject_PfnEncode*) OpcUa_NodeTypeDescription_Encode);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_ContentFilter_Encode(&a_pValue->Filter, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->MaxDataSetsToReturn, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->MaxReferencesToReturn, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_QueryFirstRequest_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_QueryFirstRequest_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_QueryFirstRequest* a_pValue = (OpcUa_QueryFirstRequest*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_QueryFirstRequest_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_ViewDescription_Decode(&a_pValue->View, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfNodeTypes, (void**) &a_pValue->NodeTypes,
                                 sizeof(OpcUa_NodeTypeDescription),
                                 (SOPC_EncodeableObject_PfnDecode*) OpcUa_NodeTypeDescription_Decode,
                                 (SOPC_EncodeableObject_PfnInitialize*) OpcUa_NodeTypeDescription_Initialize,
                                 (SOPC_EncodeableObject_PfnClear*) OpcUa_NodeTypeDescription_Clear);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_ContentFilter_Decode(&a_pValue->Filter, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->MaxDataSetsToReturn, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->MaxReferencesToReturn, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_QueryFirstRequest_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_QueryFirstResponse
/*============================================================================
 * OpcUa_QueryFirstResponse_Initialize
 *===========================================================================*/
void OpcUa_QueryFirstResponse_Initialize(void* pValue)
{
    OpcUa_QueryFirstResponse* a_pValue = (OpcUa_QueryFirstResponse*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_QueryFirstResponse_EncodeableType;
        OpcUa_ResponseHeader_Initialize(&a_pValue->ResponseHeader);
        SOPC_Initialize_Array(&a_pValue->NoOfQueryDataSets, (void**) &a_pValue->QueryDataSets,
                              sizeof(OpcUa_QueryDataSet),
                              (SOPC_EncodeableObject_PfnInitialize*) OpcUa_QueryDataSet_Initialize);
        SOPC_ByteString_Initialize(&a_pValue->ContinuationPoint);
        SOPC_Initialize_Array(&a_pValue->NoOfParsingResults, (void**) &a_pValue->ParsingResults,
                              sizeof(OpcUa_ParsingResult),
                              (SOPC_EncodeableObject_PfnInitialize*) OpcUa_ParsingResult_Initialize);
        SOPC_Initialize_Array(&a_pValue->NoOfDiagnosticInfos, (void**) &a_pValue->DiagnosticInfos,
                              sizeof(SOPC_DiagnosticInfo),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_DiagnosticInfo_InitializeAux);
        OpcUa_ContentFilterResult_Initialize(&a_pValue->FilterResult);
    }
}

/*============================================================================
 * OpcUa_QueryFirstResponse_Clear
 *===========================================================================*/
void OpcUa_QueryFirstResponse_Clear(void* pValue)
{
    OpcUa_QueryFirstResponse* a_pValue = (OpcUa_QueryFirstResponse*) pValue;
    if (a_pValue != NULL)
    {
        OpcUa_ResponseHeader_Clear(&a_pValue->ResponseHeader);
        SOPC_Clear_Array(&a_pValue->NoOfQueryDataSets, (void**) &a_pValue->QueryDataSets, sizeof(OpcUa_QueryDataSet),
                         (SOPC_EncodeableObject_PfnClear*) OpcUa_QueryDataSet_Clear);
        SOPC_ByteString_Clear(&a_pValue->ContinuationPoint);
        SOPC_Clear_Array(&a_pValue->NoOfParsingResults, (void**) &a_pValue->ParsingResults, sizeof(OpcUa_ParsingResult),
                         (SOPC_EncodeableObject_PfnClear*) OpcUa_ParsingResult_Clear);
        SOPC_Clear_Array(&a_pValue->NoOfDiagnosticInfos, (void**) &a_pValue->DiagnosticInfos,
                         sizeof(SOPC_DiagnosticInfo), (SOPC_EncodeableObject_PfnClear*) SOPC_DiagnosticInfo_ClearAux);
        OpcUa_ContentFilterResult_Clear(&a_pValue->FilterResult);
    }
}

/*============================================================================
 * OpcUa_QueryFirstResponse_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_QueryFirstResponse_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_QueryFirstResponse* a_pValue = (const OpcUa_QueryFirstResponse*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->QueryDataSets;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfQueryDataSets, &arr, sizeof(OpcUa_QueryDataSet),
                                  (SOPC_EncodeableObject_PfnEncode*) OpcUa_QueryDataSet_Encode);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ByteString_Write(&a_pValue->ContinuationPoint, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->ParsingResults;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfParsingResults, &arr, sizeof(OpcUa_ParsingResult),
                                  (SOPC_EncodeableObject_PfnEncode*) OpcUa_ParsingResult_Encode);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->DiagnosticInfos;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfDiagnosticInfos, &arr, sizeof(SOPC_DiagnosticInfo),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_DiagnosticInfo_WriteAux);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_ContentFilterResult_Encode(&a_pValue->FilterResult, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_QueryFirstResponse_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_QueryFirstResponse_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_QueryFirstResponse* a_pValue = (OpcUa_QueryFirstResponse*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_QueryFirstResponse_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status =
            SOPC_Read_Array(buf, &a_pValue->NoOfQueryDataSets, (void**) &a_pValue->QueryDataSets,
                            sizeof(OpcUa_QueryDataSet), (SOPC_EncodeableObject_PfnDecode*) OpcUa_QueryDataSet_Decode,
                            (SOPC_EncodeableObject_PfnInitialize*) OpcUa_QueryDataSet_Initialize,
                            (SOPC_EncodeableObject_PfnClear*) OpcUa_QueryDataSet_Clear);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ByteString_Read(&a_pValue->ContinuationPoint, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status =
            SOPC_Read_Array(buf, &a_pValue->NoOfParsingResults, (void**) &a_pValue->ParsingResults,
                            sizeof(OpcUa_ParsingResult), (SOPC_EncodeableObject_PfnDecode*) OpcUa_ParsingResult_Decode,
                            (SOPC_EncodeableObject_PfnInitialize*) OpcUa_ParsingResult_Initialize,
                            (SOPC_EncodeableObject_PfnClear*) OpcUa_ParsingResult_Clear);
    }
    if (SOPC_STATUS_OK == status)
    {
        status =
            SOPC_Read_Array(buf, &a_pValue->NoOfDiagnosticInfos, (void**) &a_pValue->DiagnosticInfos,
                            sizeof(SOPC_DiagnosticInfo), (SOPC_EncodeableObject_PfnDecode*) SOPC_DiagnosticInfo_ReadAux,
                            (SOPC_EncodeableObject_PfnInitialize*) SOPC_DiagnosticInfo_InitializeAux,
                            (SOPC_EncodeableObject_PfnClear*) SOPC_DiagnosticInfo_ClearAux);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_ContentFilterResult_Decode(&a_pValue->FilterResult, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_QueryFirstResponse_Clear(a_pValue);
    }

    return status;
}
#endif
#endif

#ifndef OPCUA_EXCLUDE_QueryNext
#ifndef OPCUA_EXCLUDE_QueryNextRequest
/*============================================================================
 * OpcUa_QueryNextRequest_Initialize
 *===========================================================================*/
void OpcUa_QueryNextRequest_Initialize(void* pValue)
{
    OpcUa_QueryNextRequest* a_pValue = (OpcUa_QueryNextRequest*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_QueryNextRequest_EncodeableType;
        SOPC_Boolean_Initialize(&a_pValue->ReleaseContinuationPoint);
        SOPC_ByteString_Initialize(&a_pValue->ContinuationPoint);
    }
}

/*============================================================================
 * OpcUa_QueryNextRequest_Clear
 *===========================================================================*/
void OpcUa_QueryNextRequest_Clear(void* pValue)
{
    OpcUa_QueryNextRequest* a_pValue = (OpcUa_QueryNextRequest*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_Boolean_Clear(&a_pValue->ReleaseContinuationPoint);
        SOPC_ByteString_Clear(&a_pValue->ContinuationPoint);
    }
}

/*============================================================================
 * OpcUa_QueryNextRequest_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_QueryNextRequest_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_QueryNextRequest* a_pValue = (const OpcUa_QueryNextRequest*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Write(&a_pValue->ReleaseContinuationPoint, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ByteString_Write(&a_pValue->ContinuationPoint, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_QueryNextRequest_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_QueryNextRequest_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_QueryNextRequest* a_pValue = (OpcUa_QueryNextRequest*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_QueryNextRequest_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Read(&a_pValue->ReleaseContinuationPoint, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ByteString_Read(&a_pValue->ContinuationPoint, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_QueryNextRequest_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_QueryNextResponse
/*============================================================================
 * OpcUa_QueryNextResponse_Initialize
 *===========================================================================*/
void OpcUa_QueryNextResponse_Initialize(void* pValue)
{
    OpcUa_QueryNextResponse* a_pValue = (OpcUa_QueryNextResponse*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_QueryNextResponse_EncodeableType;
        OpcUa_ResponseHeader_Initialize(&a_pValue->ResponseHeader);
        SOPC_Initialize_Array(&a_pValue->NoOfQueryDataSets, (void**) &a_pValue->QueryDataSets,
                              sizeof(OpcUa_QueryDataSet),
                              (SOPC_EncodeableObject_PfnInitialize*) OpcUa_QueryDataSet_Initialize);
        SOPC_ByteString_Initialize(&a_pValue->RevisedContinuationPoint);
    }
}

/*============================================================================
 * OpcUa_QueryNextResponse_Clear
 *===========================================================================*/
void OpcUa_QueryNextResponse_Clear(void* pValue)
{
    OpcUa_QueryNextResponse* a_pValue = (OpcUa_QueryNextResponse*) pValue;
    if (a_pValue != NULL)
    {
        OpcUa_ResponseHeader_Clear(&a_pValue->ResponseHeader);
        SOPC_Clear_Array(&a_pValue->NoOfQueryDataSets, (void**) &a_pValue->QueryDataSets, sizeof(OpcUa_QueryDataSet),
                         (SOPC_EncodeableObject_PfnClear*) OpcUa_QueryDataSet_Clear);
        SOPC_ByteString_Clear(&a_pValue->RevisedContinuationPoint);
    }
}

/*============================================================================
 * OpcUa_QueryNextResponse_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_QueryNextResponse_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_QueryNextResponse* a_pValue = (const OpcUa_QueryNextResponse*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->QueryDataSets;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfQueryDataSets, &arr, sizeof(OpcUa_QueryDataSet),
                                  (SOPC_EncodeableObject_PfnEncode*) OpcUa_QueryDataSet_Encode);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ByteString_Write(&a_pValue->RevisedContinuationPoint, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_QueryNextResponse_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_QueryNextResponse_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_QueryNextResponse* a_pValue = (OpcUa_QueryNextResponse*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_QueryNextResponse_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status =
            SOPC_Read_Array(buf, &a_pValue->NoOfQueryDataSets, (void**) &a_pValue->QueryDataSets,
                            sizeof(OpcUa_QueryDataSet), (SOPC_EncodeableObject_PfnDecode*) OpcUa_QueryDataSet_Decode,
                            (SOPC_EncodeableObject_PfnInitialize*) OpcUa_QueryDataSet_Initialize,
                            (SOPC_EncodeableObject_PfnClear*) OpcUa_QueryDataSet_Clear);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ByteString_Read(&a_pValue->RevisedContinuationPoint, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_QueryNextResponse_Clear(a_pValue);
    }

    return status;
}
#endif
#endif

#ifndef OPCUA_EXCLUDE_ReadValueId
/*============================================================================
 * OpcUa_ReadValueId_Initialize
 *===========================================================================*/
void OpcUa_ReadValueId_Initialize(void* pValue)
{
    OpcUa_ReadValueId* a_pValue = (OpcUa_ReadValueId*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_ReadValueId_EncodeableType;
        SOPC_NodeId_Initialize(&a_pValue->NodeId);
        SOPC_UInt32_Initialize(&a_pValue->AttributeId);
        SOPC_String_Initialize(&a_pValue->IndexRange);
        SOPC_QualifiedName_Initialize(&a_pValue->DataEncoding);
    }
}

/*============================================================================
 * OpcUa_ReadValueId_Clear
 *===========================================================================*/
void OpcUa_ReadValueId_Clear(void* pValue)
{
    OpcUa_ReadValueId* a_pValue = (OpcUa_ReadValueId*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_NodeId_Clear(&a_pValue->NodeId);
        SOPC_UInt32_Clear(&a_pValue->AttributeId);
        SOPC_String_Clear(&a_pValue->IndexRange);
        SOPC_QualifiedName_Clear(&a_pValue->DataEncoding);
    }
}

/*============================================================================
 * OpcUa_ReadValueId_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_ReadValueId_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_ReadValueId* a_pValue = (const OpcUa_ReadValueId*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Write(&a_pValue->NodeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->AttributeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Write(&a_pValue->IndexRange, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_QualifiedName_Write(&a_pValue->DataEncoding, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_ReadValueId_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_ReadValueId_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_ReadValueId* a_pValue = (OpcUa_ReadValueId*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_ReadValueId_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Read(&a_pValue->NodeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->AttributeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Read(&a_pValue->IndexRange, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_QualifiedName_Read(&a_pValue->DataEncoding, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_ReadValueId_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_Read
#ifndef OPCUA_EXCLUDE_ReadRequest
/*============================================================================
 * OpcUa_ReadRequest_Initialize
 *===========================================================================*/
void OpcUa_ReadRequest_Initialize(void* pValue)
{
    OpcUa_ReadRequest* a_pValue = (OpcUa_ReadRequest*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_ReadRequest_EncodeableType;
        SOPC_Double_Initialize(&a_pValue->MaxAge);
        SOPC_Initialize_EnumeratedType((int32_t*) &a_pValue->TimestampsToReturn);
        SOPC_Initialize_Array(&a_pValue->NoOfNodesToRead, (void**) &a_pValue->NodesToRead, sizeof(OpcUa_ReadValueId),
                              (SOPC_EncodeableObject_PfnInitialize*) OpcUa_ReadValueId_Initialize);
    }
}

/*============================================================================
 * OpcUa_ReadRequest_Clear
 *===========================================================================*/
void OpcUa_ReadRequest_Clear(void* pValue)
{
    OpcUa_ReadRequest* a_pValue = (OpcUa_ReadRequest*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_Double_Clear(&a_pValue->MaxAge);
        SOPC_Clear_EnumeratedType((int32_t*) &a_pValue->TimestampsToReturn);
        SOPC_Clear_Array(&a_pValue->NoOfNodesToRead, (void**) &a_pValue->NodesToRead, sizeof(OpcUa_ReadValueId),
                         (SOPC_EncodeableObject_PfnClear*) OpcUa_ReadValueId_Clear);
    }
}

/*============================================================================
 * OpcUa_ReadRequest_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_ReadRequest_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_ReadRequest* a_pValue = (const OpcUa_ReadRequest*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Double_Write(&a_pValue->MaxAge, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Write_EnumeratedType(buf, (const int32_t*) &a_pValue->TimestampsToReturn);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->NodesToRead;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfNodesToRead, &arr, sizeof(OpcUa_ReadValueId),
                                  (SOPC_EncodeableObject_PfnEncode*) OpcUa_ReadValueId_Encode);
    }

    return status;
}

/*============================================================================
 * OpcUa_ReadRequest_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_ReadRequest_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_ReadRequest* a_pValue = (OpcUa_ReadRequest*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_ReadRequest_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Double_Read(&a_pValue->MaxAge, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_EnumeratedType(buf, (int32_t*) &a_pValue->TimestampsToReturn);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfNodesToRead, (void**) &a_pValue->NodesToRead,
                                 sizeof(OpcUa_ReadValueId), (SOPC_EncodeableObject_PfnDecode*) OpcUa_ReadValueId_Decode,
                                 (SOPC_EncodeableObject_PfnInitialize*) OpcUa_ReadValueId_Initialize,
                                 (SOPC_EncodeableObject_PfnClear*) OpcUa_ReadValueId_Clear);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_ReadRequest_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_ReadResponse
/*============================================================================
 * OpcUa_ReadResponse_Initialize
 *===========================================================================*/
void OpcUa_ReadResponse_Initialize(void* pValue)
{
    OpcUa_ReadResponse* a_pValue = (OpcUa_ReadResponse*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_ReadResponse_EncodeableType;
        OpcUa_ResponseHeader_Initialize(&a_pValue->ResponseHeader);
        SOPC_Initialize_Array(&a_pValue->NoOfResults, (void**) &a_pValue->Results, sizeof(SOPC_DataValue),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_DataValue_InitializeAux);
        SOPC_Initialize_Array(&a_pValue->NoOfDiagnosticInfos, (void**) &a_pValue->DiagnosticInfos,
                              sizeof(SOPC_DiagnosticInfo),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_DiagnosticInfo_InitializeAux);
    }
}

/*============================================================================
 * OpcUa_ReadResponse_Clear
 *===========================================================================*/
void OpcUa_ReadResponse_Clear(void* pValue)
{
    OpcUa_ReadResponse* a_pValue = (OpcUa_ReadResponse*) pValue;
    if (a_pValue != NULL)
    {
        OpcUa_ResponseHeader_Clear(&a_pValue->ResponseHeader);
        SOPC_Clear_Array(&a_pValue->NoOfResults, (void**) &a_pValue->Results, sizeof(SOPC_DataValue),
                         (SOPC_EncodeableObject_PfnClear*) SOPC_DataValue_ClearAux);
        SOPC_Clear_Array(&a_pValue->NoOfDiagnosticInfos, (void**) &a_pValue->DiagnosticInfos,
                         sizeof(SOPC_DiagnosticInfo), (SOPC_EncodeableObject_PfnClear*) SOPC_DiagnosticInfo_ClearAux);
    }
}

/*============================================================================
 * OpcUa_ReadResponse_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_ReadResponse_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_ReadResponse* a_pValue = (const OpcUa_ReadResponse*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->Results;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfResults, &arr, sizeof(SOPC_DataValue),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_DataValue_WriteAux);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->DiagnosticInfos;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfDiagnosticInfos, &arr, sizeof(SOPC_DiagnosticInfo),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_DiagnosticInfo_WriteAux);
    }

    return status;
}

/*============================================================================
 * OpcUa_ReadResponse_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_ReadResponse_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_ReadResponse* a_pValue = (OpcUa_ReadResponse*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_ReadResponse_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfResults, (void**) &a_pValue->Results, sizeof(SOPC_DataValue),
                                 (SOPC_EncodeableObject_PfnDecode*) SOPC_DataValue_ReadAux,
                                 (SOPC_EncodeableObject_PfnInitialize*) SOPC_DataValue_InitializeAux,
                                 (SOPC_EncodeableObject_PfnClear*) SOPC_DataValue_ClearAux);
    }
    if (SOPC_STATUS_OK == status)
    {
        status =
            SOPC_Read_Array(buf, &a_pValue->NoOfDiagnosticInfos, (void**) &a_pValue->DiagnosticInfos,
                            sizeof(SOPC_DiagnosticInfo), (SOPC_EncodeableObject_PfnDecode*) SOPC_DiagnosticInfo_ReadAux,
                            (SOPC_EncodeableObject_PfnInitialize*) SOPC_DiagnosticInfo_InitializeAux,
                            (SOPC_EncodeableObject_PfnClear*) SOPC_DiagnosticInfo_ClearAux);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_ReadResponse_Clear(a_pValue);
    }

    return status;
}
#endif
#endif

#ifndef OPCUA_EXCLUDE_HistoryReadValueId
/*============================================================================
 * OpcUa_HistoryReadValueId_Initialize
 *===========================================================================*/
void OpcUa_HistoryReadValueId_Initialize(void* pValue)
{
    OpcUa_HistoryReadValueId* a_pValue = (OpcUa_HistoryReadValueId*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_HistoryReadValueId_EncodeableType;
        SOPC_NodeId_Initialize(&a_pValue->NodeId);
        SOPC_String_Initialize(&a_pValue->IndexRange);
        SOPC_QualifiedName_Initialize(&a_pValue->DataEncoding);
        SOPC_ByteString_Initialize(&a_pValue->ContinuationPoint);
    }
}

/*============================================================================
 * OpcUa_HistoryReadValueId_Clear
 *===========================================================================*/
void OpcUa_HistoryReadValueId_Clear(void* pValue)
{
    OpcUa_HistoryReadValueId* a_pValue = (OpcUa_HistoryReadValueId*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_NodeId_Clear(&a_pValue->NodeId);
        SOPC_String_Clear(&a_pValue->IndexRange);
        SOPC_QualifiedName_Clear(&a_pValue->DataEncoding);
        SOPC_ByteString_Clear(&a_pValue->ContinuationPoint);
    }
}

/*============================================================================
 * OpcUa_HistoryReadValueId_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_HistoryReadValueId_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_HistoryReadValueId* a_pValue = (const OpcUa_HistoryReadValueId*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Write(&a_pValue->NodeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Write(&a_pValue->IndexRange, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_QualifiedName_Write(&a_pValue->DataEncoding, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ByteString_Write(&a_pValue->ContinuationPoint, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_HistoryReadValueId_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_HistoryReadValueId_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_HistoryReadValueId* a_pValue = (OpcUa_HistoryReadValueId*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_HistoryReadValueId_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Read(&a_pValue->NodeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Read(&a_pValue->IndexRange, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_QualifiedName_Read(&a_pValue->DataEncoding, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ByteString_Read(&a_pValue->ContinuationPoint, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_HistoryReadValueId_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_HistoryReadResult
/*============================================================================
 * OpcUa_HistoryReadResult_Initialize
 *===========================================================================*/
void OpcUa_HistoryReadResult_Initialize(void* pValue)
{
    OpcUa_HistoryReadResult* a_pValue = (OpcUa_HistoryReadResult*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_HistoryReadResult_EncodeableType;
        SOPC_StatusCode_Initialize(&a_pValue->StatusCode);
        SOPC_ByteString_Initialize(&a_pValue->ContinuationPoint);
        SOPC_ExtensionObject_Initialize(&a_pValue->HistoryData);
    }
}

/*============================================================================
 * OpcUa_HistoryReadResult_Clear
 *===========================================================================*/
void OpcUa_HistoryReadResult_Clear(void* pValue)
{
    OpcUa_HistoryReadResult* a_pValue = (OpcUa_HistoryReadResult*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_StatusCode_Clear(&a_pValue->StatusCode);
        SOPC_ByteString_Clear(&a_pValue->ContinuationPoint);
        SOPC_ExtensionObject_Clear(&a_pValue->HistoryData);
    }
}

/*============================================================================
 * OpcUa_HistoryReadResult_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_HistoryReadResult_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_HistoryReadResult* a_pValue = (const OpcUa_HistoryReadResult*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_StatusCode_Write(&a_pValue->StatusCode, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ByteString_Write(&a_pValue->ContinuationPoint, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ExtensionObject_Write(&a_pValue->HistoryData, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_HistoryReadResult_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_HistoryReadResult_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_HistoryReadResult* a_pValue = (OpcUa_HistoryReadResult*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_HistoryReadResult_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_StatusCode_Read(&a_pValue->StatusCode, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ByteString_Read(&a_pValue->ContinuationPoint, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ExtensionObject_Read(&a_pValue->HistoryData, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_HistoryReadResult_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_ReadEventDetails
/*============================================================================
 * OpcUa_ReadEventDetails_Initialize
 *===========================================================================*/
void OpcUa_ReadEventDetails_Initialize(void* pValue)
{
    OpcUa_ReadEventDetails* a_pValue = (OpcUa_ReadEventDetails*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_ReadEventDetails_EncodeableType;
        SOPC_UInt32_Initialize(&a_pValue->NumValuesPerNode);
        SOPC_DateTime_Initialize(&a_pValue->StartTime);
        SOPC_DateTime_Initialize(&a_pValue->EndTime);
        OpcUa_EventFilter_Initialize(&a_pValue->Filter);
    }
}

/*============================================================================
 * OpcUa_ReadEventDetails_Clear
 *===========================================================================*/
void OpcUa_ReadEventDetails_Clear(void* pValue)
{
    OpcUa_ReadEventDetails* a_pValue = (OpcUa_ReadEventDetails*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_UInt32_Clear(&a_pValue->NumValuesPerNode);
        SOPC_DateTime_Clear(&a_pValue->StartTime);
        SOPC_DateTime_Clear(&a_pValue->EndTime);
        OpcUa_EventFilter_Clear(&a_pValue->Filter);
    }
}

/*============================================================================
 * OpcUa_ReadEventDetails_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_ReadEventDetails_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_ReadEventDetails* a_pValue = (const OpcUa_ReadEventDetails*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->NumValuesPerNode, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_DateTime_Write(&a_pValue->StartTime, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_DateTime_Write(&a_pValue->EndTime, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_EventFilter_Encode(&a_pValue->Filter, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_ReadEventDetails_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_ReadEventDetails_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_ReadEventDetails* a_pValue = (OpcUa_ReadEventDetails*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_ReadEventDetails_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->NumValuesPerNode, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_DateTime_Read(&a_pValue->StartTime, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_DateTime_Read(&a_pValue->EndTime, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_EventFilter_Decode(&a_pValue->Filter, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_ReadEventDetails_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_ReadRawModifiedDetails
/*============================================================================
 * OpcUa_ReadRawModifiedDetails_Initialize
 *===========================================================================*/
void OpcUa_ReadRawModifiedDetails_Initialize(void* pValue)
{
    OpcUa_ReadRawModifiedDetails* a_pValue = (OpcUa_ReadRawModifiedDetails*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_ReadRawModifiedDetails_EncodeableType;
        SOPC_Boolean_Initialize(&a_pValue->IsReadModified);
        SOPC_DateTime_Initialize(&a_pValue->StartTime);
        SOPC_DateTime_Initialize(&a_pValue->EndTime);
        SOPC_UInt32_Initialize(&a_pValue->NumValuesPerNode);
        SOPC_Boolean_Initialize(&a_pValue->ReturnBounds);
    }
}

/*============================================================================
 * OpcUa_ReadRawModifiedDetails_Clear
 *===========================================================================*/
void OpcUa_ReadRawModifiedDetails_Clear(void* pValue)
{
    OpcUa_ReadRawModifiedDetails* a_pValue = (OpcUa_ReadRawModifiedDetails*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_Boolean_Clear(&a_pValue->IsReadModified);
        SOPC_DateTime_Clear(&a_pValue->StartTime);
        SOPC_DateTime_Clear(&a_pValue->EndTime);
        SOPC_UInt32_Clear(&a_pValue->NumValuesPerNode);
        SOPC_Boolean_Clear(&a_pValue->ReturnBounds);
    }
}

/*============================================================================
 * OpcUa_ReadRawModifiedDetails_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_ReadRawModifiedDetails_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_ReadRawModifiedDetails* a_pValue = (const OpcUa_ReadRawModifiedDetails*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Write(&a_pValue->IsReadModified, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_DateTime_Write(&a_pValue->StartTime, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_DateTime_Write(&a_pValue->EndTime, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->NumValuesPerNode, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Write(&a_pValue->ReturnBounds, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_ReadRawModifiedDetails_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_ReadRawModifiedDetails_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_ReadRawModifiedDetails* a_pValue = (OpcUa_ReadRawModifiedDetails*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_ReadRawModifiedDetails_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Read(&a_pValue->IsReadModified, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_DateTime_Read(&a_pValue->StartTime, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_DateTime_Read(&a_pValue->EndTime, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->NumValuesPerNode, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Read(&a_pValue->ReturnBounds, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_ReadRawModifiedDetails_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_ReadProcessedDetails
/*============================================================================
 * OpcUa_ReadProcessedDetails_Initialize
 *===========================================================================*/
void OpcUa_ReadProcessedDetails_Initialize(void* pValue)
{
    OpcUa_ReadProcessedDetails* a_pValue = (OpcUa_ReadProcessedDetails*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_ReadProcessedDetails_EncodeableType;
        SOPC_DateTime_Initialize(&a_pValue->StartTime);
        SOPC_DateTime_Initialize(&a_pValue->EndTime);
        SOPC_Double_Initialize(&a_pValue->ProcessingInterval);
        SOPC_Initialize_Array(&a_pValue->NoOfAggregateType, (void**) &a_pValue->AggregateType, sizeof(SOPC_NodeId),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_NodeId_InitializeAux);
        OpcUa_AggregateConfiguration_Initialize(&a_pValue->AggregateConfiguration);
    }
}

/*============================================================================
 * OpcUa_ReadProcessedDetails_Clear
 *===========================================================================*/
void OpcUa_ReadProcessedDetails_Clear(void* pValue)
{
    OpcUa_ReadProcessedDetails* a_pValue = (OpcUa_ReadProcessedDetails*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_DateTime_Clear(&a_pValue->StartTime);
        SOPC_DateTime_Clear(&a_pValue->EndTime);
        SOPC_Double_Clear(&a_pValue->ProcessingInterval);
        SOPC_Clear_Array(&a_pValue->NoOfAggregateType, (void**) &a_pValue->AggregateType, sizeof(SOPC_NodeId),
                         (SOPC_EncodeableObject_PfnClear*) SOPC_NodeId_ClearAux);
        OpcUa_AggregateConfiguration_Clear(&a_pValue->AggregateConfiguration);
    }
}

/*============================================================================
 * OpcUa_ReadProcessedDetails_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_ReadProcessedDetails_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_ReadProcessedDetails* a_pValue = (const OpcUa_ReadProcessedDetails*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_DateTime_Write(&a_pValue->StartTime, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_DateTime_Write(&a_pValue->EndTime, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Double_Write(&a_pValue->ProcessingInterval, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->AggregateType;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfAggregateType, &arr, sizeof(SOPC_NodeId),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_NodeId_WriteAux);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_AggregateConfiguration_Encode(&a_pValue->AggregateConfiguration, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_ReadProcessedDetails_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_ReadProcessedDetails_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_ReadProcessedDetails* a_pValue = (OpcUa_ReadProcessedDetails*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_ReadProcessedDetails_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_DateTime_Read(&a_pValue->StartTime, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_DateTime_Read(&a_pValue->EndTime, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Double_Read(&a_pValue->ProcessingInterval, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfAggregateType, (void**) &a_pValue->AggregateType,
                                 sizeof(SOPC_NodeId), (SOPC_EncodeableObject_PfnDecode*) SOPC_NodeId_ReadAux,
                                 (SOPC_EncodeableObject_PfnInitialize*) SOPC_NodeId_InitializeAux,
                                 (SOPC_EncodeableObject_PfnClear*) SOPC_NodeId_ClearAux);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_AggregateConfiguration_Decode(&a_pValue->AggregateConfiguration, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_ReadProcessedDetails_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_ReadAtTimeDetails
/*============================================================================
 * OpcUa_ReadAtTimeDetails_Initialize
 *===========================================================================*/
void OpcUa_ReadAtTimeDetails_Initialize(void* pValue)
{
    OpcUa_ReadAtTimeDetails* a_pValue = (OpcUa_ReadAtTimeDetails*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_ReadAtTimeDetails_EncodeableType;
        SOPC_Initialize_Array(&a_pValue->NoOfReqTimes, (void**) &a_pValue->ReqTimes, sizeof(SOPC_DateTime),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_DateTime_InitializeAux);
        SOPC_Boolean_Initialize(&a_pValue->UseSimpleBounds);
    }
}

/*============================================================================
 * OpcUa_ReadAtTimeDetails_Clear
 *===========================================================================*/
void OpcUa_ReadAtTimeDetails_Clear(void* pValue)
{
    OpcUa_ReadAtTimeDetails* a_pValue = (OpcUa_ReadAtTimeDetails*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_Clear_Array(&a_pValue->NoOfReqTimes, (void**) &a_pValue->ReqTimes, sizeof(SOPC_DateTime),
                         (SOPC_EncodeableObject_PfnClear*) SOPC_DateTime_ClearAux);
        SOPC_Boolean_Clear(&a_pValue->UseSimpleBounds);
    }
}

/*============================================================================
 * OpcUa_ReadAtTimeDetails_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_ReadAtTimeDetails_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_ReadAtTimeDetails* a_pValue = (const OpcUa_ReadAtTimeDetails*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->ReqTimes;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfReqTimes, &arr, sizeof(SOPC_DateTime),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_DateTime_WriteAux);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Write(&a_pValue->UseSimpleBounds, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_ReadAtTimeDetails_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_ReadAtTimeDetails_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_ReadAtTimeDetails* a_pValue = (OpcUa_ReadAtTimeDetails*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_ReadAtTimeDetails_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfReqTimes, (void**) &a_pValue->ReqTimes, sizeof(SOPC_DateTime),
                                 (SOPC_EncodeableObject_PfnDecode*) SOPC_DateTime_ReadAux,
                                 (SOPC_EncodeableObject_PfnInitialize*) SOPC_DateTime_InitializeAux,
                                 (SOPC_EncodeableObject_PfnClear*) SOPC_DateTime_ClearAux);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Read(&a_pValue->UseSimpleBounds, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_ReadAtTimeDetails_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_HistoryData
/*============================================================================
 * OpcUa_HistoryData_Initialize
 *===========================================================================*/
void OpcUa_HistoryData_Initialize(void* pValue)
{
    OpcUa_HistoryData* a_pValue = (OpcUa_HistoryData*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_HistoryData_EncodeableType;
        SOPC_Initialize_Array(&a_pValue->NoOfDataValues, (void**) &a_pValue->DataValues, sizeof(SOPC_DataValue),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_DataValue_InitializeAux);
    }
}

/*============================================================================
 * OpcUa_HistoryData_Clear
 *===========================================================================*/
void OpcUa_HistoryData_Clear(void* pValue)
{
    OpcUa_HistoryData* a_pValue = (OpcUa_HistoryData*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_Clear_Array(&a_pValue->NoOfDataValues, (void**) &a_pValue->DataValues, sizeof(SOPC_DataValue),
                         (SOPC_EncodeableObject_PfnClear*) SOPC_DataValue_ClearAux);
    }
}

/*============================================================================
 * OpcUa_HistoryData_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_HistoryData_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_HistoryData* a_pValue = (const OpcUa_HistoryData*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->DataValues;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfDataValues, &arr, sizeof(SOPC_DataValue),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_DataValue_WriteAux);
    }

    return status;
}

/*============================================================================
 * OpcUa_HistoryData_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_HistoryData_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_HistoryData* a_pValue = (OpcUa_HistoryData*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_HistoryData_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfDataValues, (void**) &a_pValue->DataValues, sizeof(SOPC_DataValue),
                                 (SOPC_EncodeableObject_PfnDecode*) SOPC_DataValue_ReadAux,
                                 (SOPC_EncodeableObject_PfnInitialize*) SOPC_DataValue_InitializeAux,
                                 (SOPC_EncodeableObject_PfnClear*) SOPC_DataValue_ClearAux);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_HistoryData_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_ModificationInfo
/*============================================================================
 * OpcUa_ModificationInfo_Initialize
 *===========================================================================*/
void OpcUa_ModificationInfo_Initialize(void* pValue)
{
    OpcUa_ModificationInfo* a_pValue = (OpcUa_ModificationInfo*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_ModificationInfo_EncodeableType;
        SOPC_DateTime_Initialize(&a_pValue->ModificationTime);
        SOPC_Initialize_EnumeratedType((int32_t*) &a_pValue->UpdateType);
        SOPC_String_Initialize(&a_pValue->UserName);
    }
}

/*============================================================================
 * OpcUa_ModificationInfo_Clear
 *===========================================================================*/
void OpcUa_ModificationInfo_Clear(void* pValue)
{
    OpcUa_ModificationInfo* a_pValue = (OpcUa_ModificationInfo*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_DateTime_Clear(&a_pValue->ModificationTime);
        SOPC_Clear_EnumeratedType((int32_t*) &a_pValue->UpdateType);
        SOPC_String_Clear(&a_pValue->UserName);
    }
}

/*============================================================================
 * OpcUa_ModificationInfo_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_ModificationInfo_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_ModificationInfo* a_pValue = (const OpcUa_ModificationInfo*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_DateTime_Write(&a_pValue->ModificationTime, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Write_EnumeratedType(buf, (const int32_t*) &a_pValue->UpdateType);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Write(&a_pValue->UserName, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_ModificationInfo_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_ModificationInfo_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_ModificationInfo* a_pValue = (OpcUa_ModificationInfo*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_ModificationInfo_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_DateTime_Read(&a_pValue->ModificationTime, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_EnumeratedType(buf, (int32_t*) &a_pValue->UpdateType);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Read(&a_pValue->UserName, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_ModificationInfo_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_HistoryModifiedData
/*============================================================================
 * OpcUa_HistoryModifiedData_Initialize
 *===========================================================================*/
void OpcUa_HistoryModifiedData_Initialize(void* pValue)
{
    OpcUa_HistoryModifiedData* a_pValue = (OpcUa_HistoryModifiedData*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_HistoryModifiedData_EncodeableType;
        SOPC_Initialize_Array(&a_pValue->NoOfDataValues, (void**) &a_pValue->DataValues, sizeof(SOPC_DataValue),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_DataValue_InitializeAux);
        SOPC_Initialize_Array(&a_pValue->NoOfModificationInfos, (void**) &a_pValue->ModificationInfos,
                              sizeof(OpcUa_ModificationInfo),
                              (SOPC_EncodeableObject_PfnInitialize*) OpcUa_ModificationInfo_Initialize);
    }
}

/*============================================================================
 * OpcUa_HistoryModifiedData_Clear
 *===========================================================================*/
void OpcUa_HistoryModifiedData_Clear(void* pValue)
{
    OpcUa_HistoryModifiedData* a_pValue = (OpcUa_HistoryModifiedData*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_Clear_Array(&a_pValue->NoOfDataValues, (void**) &a_pValue->DataValues, sizeof(SOPC_DataValue),
                         (SOPC_EncodeableObject_PfnClear*) SOPC_DataValue_ClearAux);
        SOPC_Clear_Array(&a_pValue->NoOfModificationInfos, (void**) &a_pValue->ModificationInfos,
                         sizeof(OpcUa_ModificationInfo),
                         (SOPC_EncodeableObject_PfnClear*) OpcUa_ModificationInfo_Clear);
    }
}

/*============================================================================
 * OpcUa_HistoryModifiedData_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_HistoryModifiedData_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_HistoryModifiedData* a_pValue = (const OpcUa_HistoryModifiedData*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->DataValues;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfDataValues, &arr, sizeof(SOPC_DataValue),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_DataValue_WriteAux);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->ModificationInfos;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfModificationInfos, &arr, sizeof(OpcUa_ModificationInfo),
                                  (SOPC_EncodeableObject_PfnEncode*) OpcUa_ModificationInfo_Encode);
    }

    return status;
}

/*============================================================================
 * OpcUa_HistoryModifiedData_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_HistoryModifiedData_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_HistoryModifiedData* a_pValue = (OpcUa_HistoryModifiedData*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_HistoryModifiedData_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfDataValues, (void**) &a_pValue->DataValues, sizeof(SOPC_DataValue),
                                 (SOPC_EncodeableObject_PfnDecode*) SOPC_DataValue_ReadAux,
                                 (SOPC_EncodeableObject_PfnInitialize*) SOPC_DataValue_InitializeAux,
                                 (SOPC_EncodeableObject_PfnClear*) SOPC_DataValue_ClearAux);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfModificationInfos, (void**) &a_pValue->ModificationInfos,
                                 sizeof(OpcUa_ModificationInfo),
                                 (SOPC_EncodeableObject_PfnDecode*) OpcUa_ModificationInfo_Decode,
                                 (SOPC_EncodeableObject_PfnInitialize*) OpcUa_ModificationInfo_Initialize,
                                 (SOPC_EncodeableObject_PfnClear*) OpcUa_ModificationInfo_Clear);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_HistoryModifiedData_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_HistoryEvent
/*============================================================================
 * OpcUa_HistoryEvent_Initialize
 *===========================================================================*/
void OpcUa_HistoryEvent_Initialize(void* pValue)
{
    OpcUa_HistoryEvent* a_pValue = (OpcUa_HistoryEvent*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_HistoryEvent_EncodeableType;
        SOPC_Initialize_Array(&a_pValue->NoOfEvents, (void**) &a_pValue->Events, sizeof(OpcUa_HistoryEventFieldList),
                              (SOPC_EncodeableObject_PfnInitialize*) OpcUa_HistoryEventFieldList_Initialize);
    }
}

/*============================================================================
 * OpcUa_HistoryEvent_Clear
 *===========================================================================*/
void OpcUa_HistoryEvent_Clear(void* pValue)
{
    OpcUa_HistoryEvent* a_pValue = (OpcUa_HistoryEvent*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_Clear_Array(&a_pValue->NoOfEvents, (void**) &a_pValue->Events, sizeof(OpcUa_HistoryEventFieldList),
                         (SOPC_EncodeableObject_PfnClear*) OpcUa_HistoryEventFieldList_Clear);
    }
}

/*============================================================================
 * OpcUa_HistoryEvent_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_HistoryEvent_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_HistoryEvent* a_pValue = (const OpcUa_HistoryEvent*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->Events;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfEvents, &arr, sizeof(OpcUa_HistoryEventFieldList),
                                  (SOPC_EncodeableObject_PfnEncode*) OpcUa_HistoryEventFieldList_Encode);
    }

    return status;
}

/*============================================================================
 * OpcUa_HistoryEvent_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_HistoryEvent_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_HistoryEvent* a_pValue = (OpcUa_HistoryEvent*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_HistoryEvent_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status =
            SOPC_Read_Array(buf, &a_pValue->NoOfEvents, (void**) &a_pValue->Events, sizeof(OpcUa_HistoryEventFieldList),
                            (SOPC_EncodeableObject_PfnDecode*) OpcUa_HistoryEventFieldList_Decode,
                            (SOPC_EncodeableObject_PfnInitialize*) OpcUa_HistoryEventFieldList_Initialize,
                            (SOPC_EncodeableObject_PfnClear*) OpcUa_HistoryEventFieldList_Clear);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_HistoryEvent_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_HistoryRead
#ifndef OPCUA_EXCLUDE_HistoryReadRequest
/*============================================================================
 * OpcUa_HistoryReadRequest_Initialize
 *===========================================================================*/
void OpcUa_HistoryReadRequest_Initialize(void* pValue)
{
    OpcUa_HistoryReadRequest* a_pValue = (OpcUa_HistoryReadRequest*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_HistoryReadRequest_EncodeableType;
        SOPC_ExtensionObject_Initialize(&a_pValue->HistoryReadDetails);
        SOPC_Initialize_EnumeratedType((int32_t*) &a_pValue->TimestampsToReturn);
        SOPC_Boolean_Initialize(&a_pValue->ReleaseContinuationPoints);
        SOPC_Initialize_Array(&a_pValue->NoOfNodesToRead, (void**) &a_pValue->NodesToRead,
                              sizeof(OpcUa_HistoryReadValueId),
                              (SOPC_EncodeableObject_PfnInitialize*) OpcUa_HistoryReadValueId_Initialize);
    }
}

/*============================================================================
 * OpcUa_HistoryReadRequest_Clear
 *===========================================================================*/
void OpcUa_HistoryReadRequest_Clear(void* pValue)
{
    OpcUa_HistoryReadRequest* a_pValue = (OpcUa_HistoryReadRequest*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_ExtensionObject_Clear(&a_pValue->HistoryReadDetails);
        SOPC_Clear_EnumeratedType((int32_t*) &a_pValue->TimestampsToReturn);
        SOPC_Boolean_Clear(&a_pValue->ReleaseContinuationPoints);
        SOPC_Clear_Array(&a_pValue->NoOfNodesToRead, (void**) &a_pValue->NodesToRead, sizeof(OpcUa_HistoryReadValueId),
                         (SOPC_EncodeableObject_PfnClear*) OpcUa_HistoryReadValueId_Clear);
    }
}

/*============================================================================
 * OpcUa_HistoryReadRequest_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_HistoryReadRequest_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_HistoryReadRequest* a_pValue = (const OpcUa_HistoryReadRequest*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ExtensionObject_Write(&a_pValue->HistoryReadDetails, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Write_EnumeratedType(buf, (const int32_t*) &a_pValue->TimestampsToReturn);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Write(&a_pValue->ReleaseContinuationPoints, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->NodesToRead;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfNodesToRead, &arr, sizeof(OpcUa_HistoryReadValueId),
                                  (SOPC_EncodeableObject_PfnEncode*) OpcUa_HistoryReadValueId_Encode);
    }

    return status;
}

/*============================================================================
 * OpcUa_HistoryReadRequest_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_HistoryReadRequest_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_HistoryReadRequest* a_pValue = (OpcUa_HistoryReadRequest*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_HistoryReadRequest_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ExtensionObject_Read(&a_pValue->HistoryReadDetails, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_EnumeratedType(buf, (int32_t*) &a_pValue->TimestampsToReturn);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Read(&a_pValue->ReleaseContinuationPoints, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfNodesToRead, (void**) &a_pValue->NodesToRead,
                                 sizeof(OpcUa_HistoryReadValueId),
                                 (SOPC_EncodeableObject_PfnDecode*) OpcUa_HistoryReadValueId_Decode,
                                 (SOPC_EncodeableObject_PfnInitialize*) OpcUa_HistoryReadValueId_Initialize,
                                 (SOPC_EncodeableObject_PfnClear*) OpcUa_HistoryReadValueId_Clear);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_HistoryReadRequest_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_HistoryReadResponse
/*============================================================================
 * OpcUa_HistoryReadResponse_Initialize
 *===========================================================================*/
void OpcUa_HistoryReadResponse_Initialize(void* pValue)
{
    OpcUa_HistoryReadResponse* a_pValue = (OpcUa_HistoryReadResponse*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_HistoryReadResponse_EncodeableType;
        OpcUa_ResponseHeader_Initialize(&a_pValue->ResponseHeader);
        SOPC_Initialize_Array(&a_pValue->NoOfResults, (void**) &a_pValue->Results, sizeof(OpcUa_HistoryReadResult),
                              (SOPC_EncodeableObject_PfnInitialize*) OpcUa_HistoryReadResult_Initialize);
        SOPC_Initialize_Array(&a_pValue->NoOfDiagnosticInfos, (void**) &a_pValue->DiagnosticInfos,
                              sizeof(SOPC_DiagnosticInfo),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_DiagnosticInfo_InitializeAux);
    }
}

/*============================================================================
 * OpcUa_HistoryReadResponse_Clear
 *===========================================================================*/
void OpcUa_HistoryReadResponse_Clear(void* pValue)
{
    OpcUa_HistoryReadResponse* a_pValue = (OpcUa_HistoryReadResponse*) pValue;
    if (a_pValue != NULL)
    {
        OpcUa_ResponseHeader_Clear(&a_pValue->ResponseHeader);
        SOPC_Clear_Array(&a_pValue->NoOfResults, (void**) &a_pValue->Results, sizeof(OpcUa_HistoryReadResult),
                         (SOPC_EncodeableObject_PfnClear*) OpcUa_HistoryReadResult_Clear);
        SOPC_Clear_Array(&a_pValue->NoOfDiagnosticInfos, (void**) &a_pValue->DiagnosticInfos,
                         sizeof(SOPC_DiagnosticInfo), (SOPC_EncodeableObject_PfnClear*) SOPC_DiagnosticInfo_ClearAux);
    }
}

/*============================================================================
 * OpcUa_HistoryReadResponse_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_HistoryReadResponse_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_HistoryReadResponse* a_pValue = (const OpcUa_HistoryReadResponse*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->Results;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfResults, &arr, sizeof(OpcUa_HistoryReadResult),
                                  (SOPC_EncodeableObject_PfnEncode*) OpcUa_HistoryReadResult_Encode);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->DiagnosticInfos;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfDiagnosticInfos, &arr, sizeof(SOPC_DiagnosticInfo),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_DiagnosticInfo_WriteAux);
    }

    return status;
}

/*============================================================================
 * OpcUa_HistoryReadResponse_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_HistoryReadResponse_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_HistoryReadResponse* a_pValue = (OpcUa_HistoryReadResponse*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_HistoryReadResponse_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status =
            SOPC_Read_Array(buf, &a_pValue->NoOfResults, (void**) &a_pValue->Results, sizeof(OpcUa_HistoryReadResult),
                            (SOPC_EncodeableObject_PfnDecode*) OpcUa_HistoryReadResult_Decode,
                            (SOPC_EncodeableObject_PfnInitialize*) OpcUa_HistoryReadResult_Initialize,
                            (SOPC_EncodeableObject_PfnClear*) OpcUa_HistoryReadResult_Clear);
    }
    if (SOPC_STATUS_OK == status)
    {
        status =
            SOPC_Read_Array(buf, &a_pValue->NoOfDiagnosticInfos, (void**) &a_pValue->DiagnosticInfos,
                            sizeof(SOPC_DiagnosticInfo), (SOPC_EncodeableObject_PfnDecode*) SOPC_DiagnosticInfo_ReadAux,
                            (SOPC_EncodeableObject_PfnInitialize*) SOPC_DiagnosticInfo_InitializeAux,
                            (SOPC_EncodeableObject_PfnClear*) SOPC_DiagnosticInfo_ClearAux);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_HistoryReadResponse_Clear(a_pValue);
    }

    return status;
}
#endif
#endif

#ifndef OPCUA_EXCLUDE_WriteValue
/*============================================================================
 * OpcUa_WriteValue_Initialize
 *===========================================================================*/
void OpcUa_WriteValue_Initialize(void* pValue)
{
    OpcUa_WriteValue* a_pValue = (OpcUa_WriteValue*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_WriteValue_EncodeableType;
        SOPC_NodeId_Initialize(&a_pValue->NodeId);
        SOPC_UInt32_Initialize(&a_pValue->AttributeId);
        SOPC_String_Initialize(&a_pValue->IndexRange);
        SOPC_DataValue_Initialize(&a_pValue->Value);
    }
}

/*============================================================================
 * OpcUa_WriteValue_Clear
 *===========================================================================*/
void OpcUa_WriteValue_Clear(void* pValue)
{
    OpcUa_WriteValue* a_pValue = (OpcUa_WriteValue*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_NodeId_Clear(&a_pValue->NodeId);
        SOPC_UInt32_Clear(&a_pValue->AttributeId);
        SOPC_String_Clear(&a_pValue->IndexRange);
        SOPC_DataValue_Clear(&a_pValue->Value);
    }
}

/*============================================================================
 * OpcUa_WriteValue_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_WriteValue_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_WriteValue* a_pValue = (const OpcUa_WriteValue*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Write(&a_pValue->NodeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->AttributeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Write(&a_pValue->IndexRange, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_DataValue_Write(&a_pValue->Value, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_WriteValue_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_WriteValue_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_WriteValue* a_pValue = (OpcUa_WriteValue*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_WriteValue_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Read(&a_pValue->NodeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->AttributeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Read(&a_pValue->IndexRange, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_DataValue_Read(&a_pValue->Value, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_WriteValue_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_Write
#ifndef OPCUA_EXCLUDE_WriteRequest
/*============================================================================
 * OpcUa_WriteRequest_Initialize
 *===========================================================================*/
void OpcUa_WriteRequest_Initialize(void* pValue)
{
    OpcUa_WriteRequest* a_pValue = (OpcUa_WriteRequest*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_WriteRequest_EncodeableType;
        SOPC_Initialize_Array(&a_pValue->NoOfNodesToWrite, (void**) &a_pValue->NodesToWrite, sizeof(OpcUa_WriteValue),
                              (SOPC_EncodeableObject_PfnInitialize*) OpcUa_WriteValue_Initialize);
    }
}

/*============================================================================
 * OpcUa_WriteRequest_Clear
 *===========================================================================*/
void OpcUa_WriteRequest_Clear(void* pValue)
{
    OpcUa_WriteRequest* a_pValue = (OpcUa_WriteRequest*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_Clear_Array(&a_pValue->NoOfNodesToWrite, (void**) &a_pValue->NodesToWrite, sizeof(OpcUa_WriteValue),
                         (SOPC_EncodeableObject_PfnClear*) OpcUa_WriteValue_Clear);
    }
}

/*============================================================================
 * OpcUa_WriteRequest_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_WriteRequest_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_WriteRequest* a_pValue = (const OpcUa_WriteRequest*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->NodesToWrite;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfNodesToWrite, &arr, sizeof(OpcUa_WriteValue),
                                  (SOPC_EncodeableObject_PfnEncode*) OpcUa_WriteValue_Encode);
    }

    return status;
}

/*============================================================================
 * OpcUa_WriteRequest_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_WriteRequest_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_WriteRequest* a_pValue = (OpcUa_WriteRequest*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_WriteRequest_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfNodesToWrite, (void**) &a_pValue->NodesToWrite,
                                 sizeof(OpcUa_WriteValue), (SOPC_EncodeableObject_PfnDecode*) OpcUa_WriteValue_Decode,
                                 (SOPC_EncodeableObject_PfnInitialize*) OpcUa_WriteValue_Initialize,
                                 (SOPC_EncodeableObject_PfnClear*) OpcUa_WriteValue_Clear);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_WriteRequest_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_WriteResponse
/*============================================================================
 * OpcUa_WriteResponse_Initialize
 *===========================================================================*/
void OpcUa_WriteResponse_Initialize(void* pValue)
{
    OpcUa_WriteResponse* a_pValue = (OpcUa_WriteResponse*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_WriteResponse_EncodeableType;
        OpcUa_ResponseHeader_Initialize(&a_pValue->ResponseHeader);
        SOPC_Initialize_Array(&a_pValue->NoOfResults, (void**) &a_pValue->Results, sizeof(SOPC_StatusCode),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_StatusCode_InitializeAux);
        SOPC_Initialize_Array(&a_pValue->NoOfDiagnosticInfos, (void**) &a_pValue->DiagnosticInfos,
                              sizeof(SOPC_DiagnosticInfo),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_DiagnosticInfo_InitializeAux);
    }
}

/*============================================================================
 * OpcUa_WriteResponse_Clear
 *===========================================================================*/
void OpcUa_WriteResponse_Clear(void* pValue)
{
    OpcUa_WriteResponse* a_pValue = (OpcUa_WriteResponse*) pValue;
    if (a_pValue != NULL)
    {
        OpcUa_ResponseHeader_Clear(&a_pValue->ResponseHeader);
        SOPC_Clear_Array(&a_pValue->NoOfResults, (void**) &a_pValue->Results, sizeof(SOPC_StatusCode),
                         (SOPC_EncodeableObject_PfnClear*) SOPC_StatusCode_ClearAux);
        SOPC_Clear_Array(&a_pValue->NoOfDiagnosticInfos, (void**) &a_pValue->DiagnosticInfos,
                         sizeof(SOPC_DiagnosticInfo), (SOPC_EncodeableObject_PfnClear*) SOPC_DiagnosticInfo_ClearAux);
    }
}

/*============================================================================
 * OpcUa_WriteResponse_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_WriteResponse_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_WriteResponse* a_pValue = (const OpcUa_WriteResponse*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->Results;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfResults, &arr, sizeof(SOPC_StatusCode),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_StatusCode_WriteAux);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->DiagnosticInfos;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfDiagnosticInfos, &arr, sizeof(SOPC_DiagnosticInfo),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_DiagnosticInfo_WriteAux);
    }

    return status;
}

/*============================================================================
 * OpcUa_WriteResponse_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_WriteResponse_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_WriteResponse* a_pValue = (OpcUa_WriteResponse*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_WriteResponse_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfResults, (void**) &a_pValue->Results, sizeof(SOPC_StatusCode),
                                 (SOPC_EncodeableObject_PfnDecode*) SOPC_StatusCode_ReadAux,
                                 (SOPC_EncodeableObject_PfnInitialize*) SOPC_StatusCode_InitializeAux,
                                 (SOPC_EncodeableObject_PfnClear*) SOPC_StatusCode_ClearAux);
    }
    if (SOPC_STATUS_OK == status)
    {
        status =
            SOPC_Read_Array(buf, &a_pValue->NoOfDiagnosticInfos, (void**) &a_pValue->DiagnosticInfos,
                            sizeof(SOPC_DiagnosticInfo), (SOPC_EncodeableObject_PfnDecode*) SOPC_DiagnosticInfo_ReadAux,
                            (SOPC_EncodeableObject_PfnInitialize*) SOPC_DiagnosticInfo_InitializeAux,
                            (SOPC_EncodeableObject_PfnClear*) SOPC_DiagnosticInfo_ClearAux);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_WriteResponse_Clear(a_pValue);
    }

    return status;
}
#endif
#endif

#ifndef OPCUA_EXCLUDE_HistoryUpdateDetails
/*============================================================================
 * OpcUa_HistoryUpdateDetails_Initialize
 *===========================================================================*/
void OpcUa_HistoryUpdateDetails_Initialize(void* pValue)
{
    OpcUa_HistoryUpdateDetails* a_pValue = (OpcUa_HistoryUpdateDetails*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_HistoryUpdateDetails_EncodeableType;
        SOPC_NodeId_Initialize(&a_pValue->NodeId);
    }
}

/*============================================================================
 * OpcUa_HistoryUpdateDetails_Clear
 *===========================================================================*/
void OpcUa_HistoryUpdateDetails_Clear(void* pValue)
{
    OpcUa_HistoryUpdateDetails* a_pValue = (OpcUa_HistoryUpdateDetails*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_NodeId_Clear(&a_pValue->NodeId);
    }
}

/*============================================================================
 * OpcUa_HistoryUpdateDetails_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_HistoryUpdateDetails_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_HistoryUpdateDetails* a_pValue = (const OpcUa_HistoryUpdateDetails*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Write(&a_pValue->NodeId, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_HistoryUpdateDetails_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_HistoryUpdateDetails_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_HistoryUpdateDetails* a_pValue = (OpcUa_HistoryUpdateDetails*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_HistoryUpdateDetails_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Read(&a_pValue->NodeId, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_HistoryUpdateDetails_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_UpdateDataDetails
/*============================================================================
 * OpcUa_UpdateDataDetails_Initialize
 *===========================================================================*/
void OpcUa_UpdateDataDetails_Initialize(void* pValue)
{
    OpcUa_UpdateDataDetails* a_pValue = (OpcUa_UpdateDataDetails*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_UpdateDataDetails_EncodeableType;
        SOPC_NodeId_Initialize(&a_pValue->NodeId);
        SOPC_Initialize_EnumeratedType((int32_t*) &a_pValue->PerformInsertReplace);
        SOPC_Initialize_Array(&a_pValue->NoOfUpdateValues, (void**) &a_pValue->UpdateValues, sizeof(SOPC_DataValue),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_DataValue_InitializeAux);
    }
}

/*============================================================================
 * OpcUa_UpdateDataDetails_Clear
 *===========================================================================*/
void OpcUa_UpdateDataDetails_Clear(void* pValue)
{
    OpcUa_UpdateDataDetails* a_pValue = (OpcUa_UpdateDataDetails*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_NodeId_Clear(&a_pValue->NodeId);
        SOPC_Clear_EnumeratedType((int32_t*) &a_pValue->PerformInsertReplace);
        SOPC_Clear_Array(&a_pValue->NoOfUpdateValues, (void**) &a_pValue->UpdateValues, sizeof(SOPC_DataValue),
                         (SOPC_EncodeableObject_PfnClear*) SOPC_DataValue_ClearAux);
    }
}

/*============================================================================
 * OpcUa_UpdateDataDetails_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_UpdateDataDetails_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_UpdateDataDetails* a_pValue = (const OpcUa_UpdateDataDetails*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Write(&a_pValue->NodeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Write_EnumeratedType(buf, (const int32_t*) &a_pValue->PerformInsertReplace);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->UpdateValues;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfUpdateValues, &arr, sizeof(SOPC_DataValue),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_DataValue_WriteAux);
    }

    return status;
}

/*============================================================================
 * OpcUa_UpdateDataDetails_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_UpdateDataDetails_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_UpdateDataDetails* a_pValue = (OpcUa_UpdateDataDetails*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_UpdateDataDetails_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Read(&a_pValue->NodeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_EnumeratedType(buf, (int32_t*) &a_pValue->PerformInsertReplace);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfUpdateValues, (void**) &a_pValue->UpdateValues,
                                 sizeof(SOPC_DataValue), (SOPC_EncodeableObject_PfnDecode*) SOPC_DataValue_ReadAux,
                                 (SOPC_EncodeableObject_PfnInitialize*) SOPC_DataValue_InitializeAux,
                                 (SOPC_EncodeableObject_PfnClear*) SOPC_DataValue_ClearAux);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_UpdateDataDetails_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_UpdateStructureDataDetails
/*============================================================================
 * OpcUa_UpdateStructureDataDetails_Initialize
 *===========================================================================*/
void OpcUa_UpdateStructureDataDetails_Initialize(void* pValue)
{
    OpcUa_UpdateStructureDataDetails* a_pValue = (OpcUa_UpdateStructureDataDetails*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_UpdateStructureDataDetails_EncodeableType;
        SOPC_NodeId_Initialize(&a_pValue->NodeId);
        SOPC_Initialize_EnumeratedType((int32_t*) &a_pValue->PerformInsertReplace);
        SOPC_Initialize_Array(&a_pValue->NoOfUpdateValues, (void**) &a_pValue->UpdateValues, sizeof(SOPC_DataValue),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_DataValue_InitializeAux);
    }
}

/*============================================================================
 * OpcUa_UpdateStructureDataDetails_Clear
 *===========================================================================*/
void OpcUa_UpdateStructureDataDetails_Clear(void* pValue)
{
    OpcUa_UpdateStructureDataDetails* a_pValue = (OpcUa_UpdateStructureDataDetails*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_NodeId_Clear(&a_pValue->NodeId);
        SOPC_Clear_EnumeratedType((int32_t*) &a_pValue->PerformInsertReplace);
        SOPC_Clear_Array(&a_pValue->NoOfUpdateValues, (void**) &a_pValue->UpdateValues, sizeof(SOPC_DataValue),
                         (SOPC_EncodeableObject_PfnClear*) SOPC_DataValue_ClearAux);
    }
}

/*============================================================================
 * OpcUa_UpdateStructureDataDetails_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_UpdateStructureDataDetails_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_UpdateStructureDataDetails* a_pValue = (const OpcUa_UpdateStructureDataDetails*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Write(&a_pValue->NodeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Write_EnumeratedType(buf, (const int32_t*) &a_pValue->PerformInsertReplace);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->UpdateValues;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfUpdateValues, &arr, sizeof(SOPC_DataValue),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_DataValue_WriteAux);
    }

    return status;
}

/*============================================================================
 * OpcUa_UpdateStructureDataDetails_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_UpdateStructureDataDetails_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_UpdateStructureDataDetails* a_pValue = (OpcUa_UpdateStructureDataDetails*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_UpdateStructureDataDetails_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Read(&a_pValue->NodeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_EnumeratedType(buf, (int32_t*) &a_pValue->PerformInsertReplace);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfUpdateValues, (void**) &a_pValue->UpdateValues,
                                 sizeof(SOPC_DataValue), (SOPC_EncodeableObject_PfnDecode*) SOPC_DataValue_ReadAux,
                                 (SOPC_EncodeableObject_PfnInitialize*) SOPC_DataValue_InitializeAux,
                                 (SOPC_EncodeableObject_PfnClear*) SOPC_DataValue_ClearAux);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_UpdateStructureDataDetails_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_UpdateEventDetails
/*============================================================================
 * OpcUa_UpdateEventDetails_Initialize
 *===========================================================================*/
void OpcUa_UpdateEventDetails_Initialize(void* pValue)
{
    OpcUa_UpdateEventDetails* a_pValue = (OpcUa_UpdateEventDetails*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_UpdateEventDetails_EncodeableType;
        SOPC_NodeId_Initialize(&a_pValue->NodeId);
        SOPC_Initialize_EnumeratedType((int32_t*) &a_pValue->PerformInsertReplace);
        OpcUa_EventFilter_Initialize(&a_pValue->Filter);
        SOPC_Initialize_Array(&a_pValue->NoOfEventData, (void**) &a_pValue->EventData,
                              sizeof(OpcUa_HistoryEventFieldList),
                              (SOPC_EncodeableObject_PfnInitialize*) OpcUa_HistoryEventFieldList_Initialize);
    }
}

/*============================================================================
 * OpcUa_UpdateEventDetails_Clear
 *===========================================================================*/
void OpcUa_UpdateEventDetails_Clear(void* pValue)
{
    OpcUa_UpdateEventDetails* a_pValue = (OpcUa_UpdateEventDetails*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_NodeId_Clear(&a_pValue->NodeId);
        SOPC_Clear_EnumeratedType((int32_t*) &a_pValue->PerformInsertReplace);
        OpcUa_EventFilter_Clear(&a_pValue->Filter);
        SOPC_Clear_Array(&a_pValue->NoOfEventData, (void**) &a_pValue->EventData, sizeof(OpcUa_HistoryEventFieldList),
                         (SOPC_EncodeableObject_PfnClear*) OpcUa_HistoryEventFieldList_Clear);
    }
}

/*============================================================================
 * OpcUa_UpdateEventDetails_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_UpdateEventDetails_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_UpdateEventDetails* a_pValue = (const OpcUa_UpdateEventDetails*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Write(&a_pValue->NodeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Write_EnumeratedType(buf, (const int32_t*) &a_pValue->PerformInsertReplace);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_EventFilter_Encode(&a_pValue->Filter, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->EventData;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfEventData, &arr, sizeof(OpcUa_HistoryEventFieldList),
                                  (SOPC_EncodeableObject_PfnEncode*) OpcUa_HistoryEventFieldList_Encode);
    }

    return status;
}

/*============================================================================
 * OpcUa_UpdateEventDetails_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_UpdateEventDetails_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_UpdateEventDetails* a_pValue = (OpcUa_UpdateEventDetails*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_UpdateEventDetails_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Read(&a_pValue->NodeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_EnumeratedType(buf, (int32_t*) &a_pValue->PerformInsertReplace);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_EventFilter_Decode(&a_pValue->Filter, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfEventData, (void**) &a_pValue->EventData,
                                 sizeof(OpcUa_HistoryEventFieldList),
                                 (SOPC_EncodeableObject_PfnDecode*) OpcUa_HistoryEventFieldList_Decode,
                                 (SOPC_EncodeableObject_PfnInitialize*) OpcUa_HistoryEventFieldList_Initialize,
                                 (SOPC_EncodeableObject_PfnClear*) OpcUa_HistoryEventFieldList_Clear);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_UpdateEventDetails_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_DeleteRawModifiedDetails
/*============================================================================
 * OpcUa_DeleteRawModifiedDetails_Initialize
 *===========================================================================*/
void OpcUa_DeleteRawModifiedDetails_Initialize(void* pValue)
{
    OpcUa_DeleteRawModifiedDetails* a_pValue = (OpcUa_DeleteRawModifiedDetails*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_DeleteRawModifiedDetails_EncodeableType;
        SOPC_NodeId_Initialize(&a_pValue->NodeId);
        SOPC_Boolean_Initialize(&a_pValue->IsDeleteModified);
        SOPC_DateTime_Initialize(&a_pValue->StartTime);
        SOPC_DateTime_Initialize(&a_pValue->EndTime);
    }
}

/*============================================================================
 * OpcUa_DeleteRawModifiedDetails_Clear
 *===========================================================================*/
void OpcUa_DeleteRawModifiedDetails_Clear(void* pValue)
{
    OpcUa_DeleteRawModifiedDetails* a_pValue = (OpcUa_DeleteRawModifiedDetails*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_NodeId_Clear(&a_pValue->NodeId);
        SOPC_Boolean_Clear(&a_pValue->IsDeleteModified);
        SOPC_DateTime_Clear(&a_pValue->StartTime);
        SOPC_DateTime_Clear(&a_pValue->EndTime);
    }
}

/*============================================================================
 * OpcUa_DeleteRawModifiedDetails_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_DeleteRawModifiedDetails_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_DeleteRawModifiedDetails* a_pValue = (const OpcUa_DeleteRawModifiedDetails*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Write(&a_pValue->NodeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Write(&a_pValue->IsDeleteModified, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_DateTime_Write(&a_pValue->StartTime, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_DateTime_Write(&a_pValue->EndTime, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_DeleteRawModifiedDetails_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_DeleteRawModifiedDetails_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_DeleteRawModifiedDetails* a_pValue = (OpcUa_DeleteRawModifiedDetails*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_DeleteRawModifiedDetails_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Read(&a_pValue->NodeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Read(&a_pValue->IsDeleteModified, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_DateTime_Read(&a_pValue->StartTime, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_DateTime_Read(&a_pValue->EndTime, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_DeleteRawModifiedDetails_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_DeleteAtTimeDetails
/*============================================================================
 * OpcUa_DeleteAtTimeDetails_Initialize
 *===========================================================================*/
void OpcUa_DeleteAtTimeDetails_Initialize(void* pValue)
{
    OpcUa_DeleteAtTimeDetails* a_pValue = (OpcUa_DeleteAtTimeDetails*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_DeleteAtTimeDetails_EncodeableType;
        SOPC_NodeId_Initialize(&a_pValue->NodeId);
        SOPC_Initialize_Array(&a_pValue->NoOfReqTimes, (void**) &a_pValue->ReqTimes, sizeof(SOPC_DateTime),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_DateTime_InitializeAux);
    }
}

/*============================================================================
 * OpcUa_DeleteAtTimeDetails_Clear
 *===========================================================================*/
void OpcUa_DeleteAtTimeDetails_Clear(void* pValue)
{
    OpcUa_DeleteAtTimeDetails* a_pValue = (OpcUa_DeleteAtTimeDetails*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_NodeId_Clear(&a_pValue->NodeId);
        SOPC_Clear_Array(&a_pValue->NoOfReqTimes, (void**) &a_pValue->ReqTimes, sizeof(SOPC_DateTime),
                         (SOPC_EncodeableObject_PfnClear*) SOPC_DateTime_ClearAux);
    }
}

/*============================================================================
 * OpcUa_DeleteAtTimeDetails_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_DeleteAtTimeDetails_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_DeleteAtTimeDetails* a_pValue = (const OpcUa_DeleteAtTimeDetails*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Write(&a_pValue->NodeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->ReqTimes;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfReqTimes, &arr, sizeof(SOPC_DateTime),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_DateTime_WriteAux);
    }

    return status;
}

/*============================================================================
 * OpcUa_DeleteAtTimeDetails_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_DeleteAtTimeDetails_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_DeleteAtTimeDetails* a_pValue = (OpcUa_DeleteAtTimeDetails*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_DeleteAtTimeDetails_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Read(&a_pValue->NodeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfReqTimes, (void**) &a_pValue->ReqTimes, sizeof(SOPC_DateTime),
                                 (SOPC_EncodeableObject_PfnDecode*) SOPC_DateTime_ReadAux,
                                 (SOPC_EncodeableObject_PfnInitialize*) SOPC_DateTime_InitializeAux,
                                 (SOPC_EncodeableObject_PfnClear*) SOPC_DateTime_ClearAux);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_DeleteAtTimeDetails_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_DeleteEventDetails
/*============================================================================
 * OpcUa_DeleteEventDetails_Initialize
 *===========================================================================*/
void OpcUa_DeleteEventDetails_Initialize(void* pValue)
{
    OpcUa_DeleteEventDetails* a_pValue = (OpcUa_DeleteEventDetails*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_DeleteEventDetails_EncodeableType;
        SOPC_NodeId_Initialize(&a_pValue->NodeId);
        SOPC_Initialize_Array(&a_pValue->NoOfEventIds, (void**) &a_pValue->EventIds, sizeof(SOPC_ByteString),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_ByteString_InitializeAux);
    }
}

/*============================================================================
 * OpcUa_DeleteEventDetails_Clear
 *===========================================================================*/
void OpcUa_DeleteEventDetails_Clear(void* pValue)
{
    OpcUa_DeleteEventDetails* a_pValue = (OpcUa_DeleteEventDetails*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_NodeId_Clear(&a_pValue->NodeId);
        SOPC_Clear_Array(&a_pValue->NoOfEventIds, (void**) &a_pValue->EventIds, sizeof(SOPC_ByteString),
                         (SOPC_EncodeableObject_PfnClear*) SOPC_ByteString_ClearAux);
    }
}

/*============================================================================
 * OpcUa_DeleteEventDetails_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_DeleteEventDetails_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_DeleteEventDetails* a_pValue = (const OpcUa_DeleteEventDetails*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Write(&a_pValue->NodeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->EventIds;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfEventIds, &arr, sizeof(SOPC_ByteString),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_ByteString_WriteAux);
    }

    return status;
}

/*============================================================================
 * OpcUa_DeleteEventDetails_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_DeleteEventDetails_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_DeleteEventDetails* a_pValue = (OpcUa_DeleteEventDetails*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_DeleteEventDetails_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Read(&a_pValue->NodeId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfEventIds, (void**) &a_pValue->EventIds, sizeof(SOPC_ByteString),
                                 (SOPC_EncodeableObject_PfnDecode*) SOPC_ByteString_ReadAux,
                                 (SOPC_EncodeableObject_PfnInitialize*) SOPC_ByteString_InitializeAux,
                                 (SOPC_EncodeableObject_PfnClear*) SOPC_ByteString_ClearAux);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_DeleteEventDetails_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_HistoryUpdateResult
/*============================================================================
 * OpcUa_HistoryUpdateResult_Initialize
 *===========================================================================*/
void OpcUa_HistoryUpdateResult_Initialize(void* pValue)
{
    OpcUa_HistoryUpdateResult* a_pValue = (OpcUa_HistoryUpdateResult*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_HistoryUpdateResult_EncodeableType;
        SOPC_StatusCode_Initialize(&a_pValue->StatusCode);
        SOPC_Initialize_Array(&a_pValue->NoOfOperationResults, (void**) &a_pValue->OperationResults,
                              sizeof(SOPC_StatusCode),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_StatusCode_InitializeAux);
        SOPC_Initialize_Array(&a_pValue->NoOfDiagnosticInfos, (void**) &a_pValue->DiagnosticInfos,
                              sizeof(SOPC_DiagnosticInfo),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_DiagnosticInfo_InitializeAux);
    }
}

/*============================================================================
 * OpcUa_HistoryUpdateResult_Clear
 *===========================================================================*/
void OpcUa_HistoryUpdateResult_Clear(void* pValue)
{
    OpcUa_HistoryUpdateResult* a_pValue = (OpcUa_HistoryUpdateResult*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_StatusCode_Clear(&a_pValue->StatusCode);
        SOPC_Clear_Array(&a_pValue->NoOfOperationResults, (void**) &a_pValue->OperationResults, sizeof(SOPC_StatusCode),
                         (SOPC_EncodeableObject_PfnClear*) SOPC_StatusCode_ClearAux);
        SOPC_Clear_Array(&a_pValue->NoOfDiagnosticInfos, (void**) &a_pValue->DiagnosticInfos,
                         sizeof(SOPC_DiagnosticInfo), (SOPC_EncodeableObject_PfnClear*) SOPC_DiagnosticInfo_ClearAux);
    }
}

/*============================================================================
 * OpcUa_HistoryUpdateResult_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_HistoryUpdateResult_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_HistoryUpdateResult* a_pValue = (const OpcUa_HistoryUpdateResult*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_StatusCode_Write(&a_pValue->StatusCode, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->OperationResults;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfOperationResults, &arr, sizeof(SOPC_StatusCode),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_StatusCode_WriteAux);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->DiagnosticInfos;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfDiagnosticInfos, &arr, sizeof(SOPC_DiagnosticInfo),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_DiagnosticInfo_WriteAux);
    }

    return status;
}

/*============================================================================
 * OpcUa_HistoryUpdateResult_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_HistoryUpdateResult_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_HistoryUpdateResult* a_pValue = (OpcUa_HistoryUpdateResult*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_HistoryUpdateResult_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_StatusCode_Read(&a_pValue->StatusCode, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfOperationResults, (void**) &a_pValue->OperationResults,
                                 sizeof(SOPC_StatusCode), (SOPC_EncodeableObject_PfnDecode*) SOPC_StatusCode_ReadAux,
                                 (SOPC_EncodeableObject_PfnInitialize*) SOPC_StatusCode_InitializeAux,
                                 (SOPC_EncodeableObject_PfnClear*) SOPC_StatusCode_ClearAux);
    }
    if (SOPC_STATUS_OK == status)
    {
        status =
            SOPC_Read_Array(buf, &a_pValue->NoOfDiagnosticInfos, (void**) &a_pValue->DiagnosticInfos,
                            sizeof(SOPC_DiagnosticInfo), (SOPC_EncodeableObject_PfnDecode*) SOPC_DiagnosticInfo_ReadAux,
                            (SOPC_EncodeableObject_PfnInitialize*) SOPC_DiagnosticInfo_InitializeAux,
                            (SOPC_EncodeableObject_PfnClear*) SOPC_DiagnosticInfo_ClearAux);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_HistoryUpdateResult_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_HistoryUpdate
#ifndef OPCUA_EXCLUDE_HistoryUpdateRequest
/*============================================================================
 * OpcUa_HistoryUpdateRequest_Initialize
 *===========================================================================*/
void OpcUa_HistoryUpdateRequest_Initialize(void* pValue)
{
    OpcUa_HistoryUpdateRequest* a_pValue = (OpcUa_HistoryUpdateRequest*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_HistoryUpdateRequest_EncodeableType;
        SOPC_Initialize_Array(&a_pValue->NoOfHistoryUpdateDetails, (void**) &a_pValue->HistoryUpdateDetails,
                              sizeof(SOPC_ExtensionObject),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_ExtensionObject_InitializeAux);
    }
}

/*============================================================================
 * OpcUa_HistoryUpdateRequest_Clear
 *===========================================================================*/
void OpcUa_HistoryUpdateRequest_Clear(void* pValue)
{
    OpcUa_HistoryUpdateRequest* a_pValue = (OpcUa_HistoryUpdateRequest*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_Clear_Array(&a_pValue->NoOfHistoryUpdateDetails, (void**) &a_pValue->HistoryUpdateDetails,
                         sizeof(SOPC_ExtensionObject), (SOPC_EncodeableObject_PfnClear*) SOPC_ExtensionObject_ClearAux);
    }
}

/*============================================================================
 * OpcUa_HistoryUpdateRequest_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_HistoryUpdateRequest_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_HistoryUpdateRequest* a_pValue = (const OpcUa_HistoryUpdateRequest*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->HistoryUpdateDetails;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfHistoryUpdateDetails, &arr, sizeof(SOPC_ExtensionObject),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_ExtensionObject_WriteAux);
    }

    return status;
}

/*============================================================================
 * OpcUa_HistoryUpdateRequest_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_HistoryUpdateRequest_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_HistoryUpdateRequest* a_pValue = (OpcUa_HistoryUpdateRequest*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_HistoryUpdateRequest_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfHistoryUpdateDetails, (void**) &a_pValue->HistoryUpdateDetails,
                                 sizeof(SOPC_ExtensionObject),
                                 (SOPC_EncodeableObject_PfnDecode*) SOPC_ExtensionObject_ReadAux,
                                 (SOPC_EncodeableObject_PfnInitialize*) SOPC_ExtensionObject_InitializeAux,
                                 (SOPC_EncodeableObject_PfnClear*) SOPC_ExtensionObject_ClearAux);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_HistoryUpdateRequest_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_HistoryUpdateResponse
/*============================================================================
 * OpcUa_HistoryUpdateResponse_Initialize
 *===========================================================================*/
void OpcUa_HistoryUpdateResponse_Initialize(void* pValue)
{
    OpcUa_HistoryUpdateResponse* a_pValue = (OpcUa_HistoryUpdateResponse*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_HistoryUpdateResponse_EncodeableType;
        OpcUa_ResponseHeader_Initialize(&a_pValue->ResponseHeader);
        SOPC_Initialize_Array(&a_pValue->NoOfResults, (void**) &a_pValue->Results, sizeof(OpcUa_HistoryUpdateResult),
                              (SOPC_EncodeableObject_PfnInitialize*) OpcUa_HistoryUpdateResult_Initialize);
        SOPC_Initialize_Array(&a_pValue->NoOfDiagnosticInfos, (void**) &a_pValue->DiagnosticInfos,
                              sizeof(SOPC_DiagnosticInfo),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_DiagnosticInfo_InitializeAux);
    }
}

/*============================================================================
 * OpcUa_HistoryUpdateResponse_Clear
 *===========================================================================*/
void OpcUa_HistoryUpdateResponse_Clear(void* pValue)
{
    OpcUa_HistoryUpdateResponse* a_pValue = (OpcUa_HistoryUpdateResponse*) pValue;
    if (a_pValue != NULL)
    {
        OpcUa_ResponseHeader_Clear(&a_pValue->ResponseHeader);
        SOPC_Clear_Array(&a_pValue->NoOfResults, (void**) &a_pValue->Results, sizeof(OpcUa_HistoryUpdateResult),
                         (SOPC_EncodeableObject_PfnClear*) OpcUa_HistoryUpdateResult_Clear);
        SOPC_Clear_Array(&a_pValue->NoOfDiagnosticInfos, (void**) &a_pValue->DiagnosticInfos,
                         sizeof(SOPC_DiagnosticInfo), (SOPC_EncodeableObject_PfnClear*) SOPC_DiagnosticInfo_ClearAux);
    }
}

/*============================================================================
 * OpcUa_HistoryUpdateResponse_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_HistoryUpdateResponse_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_HistoryUpdateResponse* a_pValue = (const OpcUa_HistoryUpdateResponse*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->Results;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfResults, &arr, sizeof(OpcUa_HistoryUpdateResult),
                                  (SOPC_EncodeableObject_PfnEncode*) OpcUa_HistoryUpdateResult_Encode);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->DiagnosticInfos;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfDiagnosticInfos, &arr, sizeof(SOPC_DiagnosticInfo),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_DiagnosticInfo_WriteAux);
    }

    return status;
}

/*============================================================================
 * OpcUa_HistoryUpdateResponse_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_HistoryUpdateResponse_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_HistoryUpdateResponse* a_pValue = (OpcUa_HistoryUpdateResponse*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_HistoryUpdateResponse_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status =
            SOPC_Read_Array(buf, &a_pValue->NoOfResults, (void**) &a_pValue->Results, sizeof(OpcUa_HistoryUpdateResult),
                            (SOPC_EncodeableObject_PfnDecode*) OpcUa_HistoryUpdateResult_Decode,
                            (SOPC_EncodeableObject_PfnInitialize*) OpcUa_HistoryUpdateResult_Initialize,
                            (SOPC_EncodeableObject_PfnClear*) OpcUa_HistoryUpdateResult_Clear);
    }
    if (SOPC_STATUS_OK == status)
    {
        status =
            SOPC_Read_Array(buf, &a_pValue->NoOfDiagnosticInfos, (void**) &a_pValue->DiagnosticInfos,
                            sizeof(SOPC_DiagnosticInfo), (SOPC_EncodeableObject_PfnDecode*) SOPC_DiagnosticInfo_ReadAux,
                            (SOPC_EncodeableObject_PfnInitialize*) SOPC_DiagnosticInfo_InitializeAux,
                            (SOPC_EncodeableObject_PfnClear*) SOPC_DiagnosticInfo_ClearAux);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_HistoryUpdateResponse_Clear(a_pValue);
    }

    return status;
}
#endif
#endif

#ifndef OPCUA_EXCLUDE_CallMethodRequest
/*============================================================================
 * OpcUa_CallMethodRequest_Initialize
 *===========================================================================*/
void OpcUa_CallMethodRequest_Initialize(void* pValue)
{
    OpcUa_CallMethodRequest* a_pValue = (OpcUa_CallMethodRequest*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_CallMethodRequest_EncodeableType;
        SOPC_NodeId_Initialize(&a_pValue->ObjectId);
        SOPC_NodeId_Initialize(&a_pValue->MethodId);
        SOPC_Initialize_Array(&a_pValue->NoOfInputArguments, (void**) &a_pValue->InputArguments, sizeof(SOPC_Variant),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_Variant_InitializeAux);
    }
}

/*============================================================================
 * OpcUa_CallMethodRequest_Clear
 *===========================================================================*/
void OpcUa_CallMethodRequest_Clear(void* pValue)
{
    OpcUa_CallMethodRequest* a_pValue = (OpcUa_CallMethodRequest*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_NodeId_Clear(&a_pValue->ObjectId);
        SOPC_NodeId_Clear(&a_pValue->MethodId);
        SOPC_Clear_Array(&a_pValue->NoOfInputArguments, (void**) &a_pValue->InputArguments, sizeof(SOPC_Variant),
                         (SOPC_EncodeableObject_PfnClear*) SOPC_Variant_ClearAux);
    }
}

/*============================================================================
 * OpcUa_CallMethodRequest_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_CallMethodRequest_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_CallMethodRequest* a_pValue = (const OpcUa_CallMethodRequest*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Write(&a_pValue->ObjectId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Write(&a_pValue->MethodId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->InputArguments;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfInputArguments, &arr, sizeof(SOPC_Variant),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_Variant_WriteAux);
    }

    return status;
}

/*============================================================================
 * OpcUa_CallMethodRequest_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_CallMethodRequest_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_CallMethodRequest* a_pValue = (OpcUa_CallMethodRequest*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_CallMethodRequest_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Read(&a_pValue->ObjectId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Read(&a_pValue->MethodId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfInputArguments, (void**) &a_pValue->InputArguments,
                                 sizeof(SOPC_Variant), (SOPC_EncodeableObject_PfnDecode*) SOPC_Variant_ReadAux,
                                 (SOPC_EncodeableObject_PfnInitialize*) SOPC_Variant_InitializeAux,
                                 (SOPC_EncodeableObject_PfnClear*) SOPC_Variant_ClearAux);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_CallMethodRequest_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_CallMethodResult
/*============================================================================
 * OpcUa_CallMethodResult_Initialize
 *===========================================================================*/
void OpcUa_CallMethodResult_Initialize(void* pValue)
{
    OpcUa_CallMethodResult* a_pValue = (OpcUa_CallMethodResult*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_CallMethodResult_EncodeableType;
        SOPC_StatusCode_Initialize(&a_pValue->StatusCode);
        SOPC_Initialize_Array(&a_pValue->NoOfInputArgumentResults, (void**) &a_pValue->InputArgumentResults,
                              sizeof(SOPC_StatusCode),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_StatusCode_InitializeAux);
        SOPC_Initialize_Array(&a_pValue->NoOfInputArgumentDiagnosticInfos,
                              (void**) &a_pValue->InputArgumentDiagnosticInfos, sizeof(SOPC_DiagnosticInfo),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_DiagnosticInfo_InitializeAux);
        SOPC_Initialize_Array(&a_pValue->NoOfOutputArguments, (void**) &a_pValue->OutputArguments, sizeof(SOPC_Variant),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_Variant_InitializeAux);
    }
}

/*============================================================================
 * OpcUa_CallMethodResult_Clear
 *===========================================================================*/
void OpcUa_CallMethodResult_Clear(void* pValue)
{
    OpcUa_CallMethodResult* a_pValue = (OpcUa_CallMethodResult*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_StatusCode_Clear(&a_pValue->StatusCode);
        SOPC_Clear_Array(&a_pValue->NoOfInputArgumentResults, (void**) &a_pValue->InputArgumentResults,
                         sizeof(SOPC_StatusCode), (SOPC_EncodeableObject_PfnClear*) SOPC_StatusCode_ClearAux);
        SOPC_Clear_Array(&a_pValue->NoOfInputArgumentDiagnosticInfos, (void**) &a_pValue->InputArgumentDiagnosticInfos,
                         sizeof(SOPC_DiagnosticInfo), (SOPC_EncodeableObject_PfnClear*) SOPC_DiagnosticInfo_ClearAux);
        SOPC_Clear_Array(&a_pValue->NoOfOutputArguments, (void**) &a_pValue->OutputArguments, sizeof(SOPC_Variant),
                         (SOPC_EncodeableObject_PfnClear*) SOPC_Variant_ClearAux);
    }
}

/*============================================================================
 * OpcUa_CallMethodResult_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_CallMethodResult_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_CallMethodResult* a_pValue = (const OpcUa_CallMethodResult*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_StatusCode_Write(&a_pValue->StatusCode, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->InputArgumentResults;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfInputArgumentResults, &arr, sizeof(SOPC_StatusCode),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_StatusCode_WriteAux);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->InputArgumentDiagnosticInfos;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfInputArgumentDiagnosticInfos, &arr, sizeof(SOPC_DiagnosticInfo),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_DiagnosticInfo_WriteAux);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->OutputArguments;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfOutputArguments, &arr, sizeof(SOPC_Variant),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_Variant_WriteAux);
    }

    return status;
}

/*============================================================================
 * OpcUa_CallMethodResult_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_CallMethodResult_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_CallMethodResult* a_pValue = (OpcUa_CallMethodResult*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_CallMethodResult_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_StatusCode_Read(&a_pValue->StatusCode, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfInputArgumentResults, (void**) &a_pValue->InputArgumentResults,
                                 sizeof(SOPC_StatusCode), (SOPC_EncodeableObject_PfnDecode*) SOPC_StatusCode_ReadAux,
                                 (SOPC_EncodeableObject_PfnInitialize*) SOPC_StatusCode_InitializeAux,
                                 (SOPC_EncodeableObject_PfnClear*) SOPC_StatusCode_ClearAux);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfInputArgumentDiagnosticInfos,
                                 (void**) &a_pValue->InputArgumentDiagnosticInfos, sizeof(SOPC_DiagnosticInfo),
                                 (SOPC_EncodeableObject_PfnDecode*) SOPC_DiagnosticInfo_ReadAux,
                                 (SOPC_EncodeableObject_PfnInitialize*) SOPC_DiagnosticInfo_InitializeAux,
                                 (SOPC_EncodeableObject_PfnClear*) SOPC_DiagnosticInfo_ClearAux);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfOutputArguments, (void**) &a_pValue->OutputArguments,
                                 sizeof(SOPC_Variant), (SOPC_EncodeableObject_PfnDecode*) SOPC_Variant_ReadAux,
                                 (SOPC_EncodeableObject_PfnInitialize*) SOPC_Variant_InitializeAux,
                                 (SOPC_EncodeableObject_PfnClear*) SOPC_Variant_ClearAux);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_CallMethodResult_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_Call
#ifndef OPCUA_EXCLUDE_CallRequest
/*============================================================================
 * OpcUa_CallRequest_Initialize
 *===========================================================================*/
void OpcUa_CallRequest_Initialize(void* pValue)
{
    OpcUa_CallRequest* a_pValue = (OpcUa_CallRequest*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_CallRequest_EncodeableType;
        SOPC_Initialize_Array(&a_pValue->NoOfMethodsToCall, (void**) &a_pValue->MethodsToCall,
                              sizeof(OpcUa_CallMethodRequest),
                              (SOPC_EncodeableObject_PfnInitialize*) OpcUa_CallMethodRequest_Initialize);
    }
}

/*============================================================================
 * OpcUa_CallRequest_Clear
 *===========================================================================*/
void OpcUa_CallRequest_Clear(void* pValue)
{
    OpcUa_CallRequest* a_pValue = (OpcUa_CallRequest*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_Clear_Array(&a_pValue->NoOfMethodsToCall, (void**) &a_pValue->MethodsToCall,
                         sizeof(OpcUa_CallMethodRequest),
                         (SOPC_EncodeableObject_PfnClear*) OpcUa_CallMethodRequest_Clear);
    }
}

/*============================================================================
 * OpcUa_CallRequest_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_CallRequest_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_CallRequest* a_pValue = (const OpcUa_CallRequest*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->MethodsToCall;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfMethodsToCall, &arr, sizeof(OpcUa_CallMethodRequest),
                                  (SOPC_EncodeableObject_PfnEncode*) OpcUa_CallMethodRequest_Encode);
    }

    return status;
}

/*============================================================================
 * OpcUa_CallRequest_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_CallRequest_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_CallRequest* a_pValue = (OpcUa_CallRequest*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_CallRequest_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfMethodsToCall, (void**) &a_pValue->MethodsToCall,
                                 sizeof(OpcUa_CallMethodRequest),
                                 (SOPC_EncodeableObject_PfnDecode*) OpcUa_CallMethodRequest_Decode,
                                 (SOPC_EncodeableObject_PfnInitialize*) OpcUa_CallMethodRequest_Initialize,
                                 (SOPC_EncodeableObject_PfnClear*) OpcUa_CallMethodRequest_Clear);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_CallRequest_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_CallResponse
/*============================================================================
 * OpcUa_CallResponse_Initialize
 *===========================================================================*/
void OpcUa_CallResponse_Initialize(void* pValue)
{
    OpcUa_CallResponse* a_pValue = (OpcUa_CallResponse*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_CallResponse_EncodeableType;
        OpcUa_ResponseHeader_Initialize(&a_pValue->ResponseHeader);
        SOPC_Initialize_Array(&a_pValue->NoOfResults, (void**) &a_pValue->Results, sizeof(OpcUa_CallMethodResult),
                              (SOPC_EncodeableObject_PfnInitialize*) OpcUa_CallMethodResult_Initialize);
        SOPC_Initialize_Array(&a_pValue->NoOfDiagnosticInfos, (void**) &a_pValue->DiagnosticInfos,
                              sizeof(SOPC_DiagnosticInfo),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_DiagnosticInfo_InitializeAux);
    }
}

/*============================================================================
 * OpcUa_CallResponse_Clear
 *===========================================================================*/
void OpcUa_CallResponse_Clear(void* pValue)
{
    OpcUa_CallResponse* a_pValue = (OpcUa_CallResponse*) pValue;
    if (a_pValue != NULL)
    {
        OpcUa_ResponseHeader_Clear(&a_pValue->ResponseHeader);
        SOPC_Clear_Array(&a_pValue->NoOfResults, (void**) &a_pValue->Results, sizeof(OpcUa_CallMethodResult),
                         (SOPC_EncodeableObject_PfnClear*) OpcUa_CallMethodResult_Clear);
        SOPC_Clear_Array(&a_pValue->NoOfDiagnosticInfos, (void**) &a_pValue->DiagnosticInfos,
                         sizeof(SOPC_DiagnosticInfo), (SOPC_EncodeableObject_PfnClear*) SOPC_DiagnosticInfo_ClearAux);
    }
}

/*============================================================================
 * OpcUa_CallResponse_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_CallResponse_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_CallResponse* a_pValue = (const OpcUa_CallResponse*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->Results;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfResults, &arr, sizeof(OpcUa_CallMethodResult),
                                  (SOPC_EncodeableObject_PfnEncode*) OpcUa_CallMethodResult_Encode);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->DiagnosticInfos;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfDiagnosticInfos, &arr, sizeof(SOPC_DiagnosticInfo),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_DiagnosticInfo_WriteAux);
    }

    return status;
}

/*============================================================================
 * OpcUa_CallResponse_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_CallResponse_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_CallResponse* a_pValue = (OpcUa_CallResponse*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_CallResponse_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status =
            SOPC_Read_Array(buf, &a_pValue->NoOfResults, (void**) &a_pValue->Results, sizeof(OpcUa_CallMethodResult),
                            (SOPC_EncodeableObject_PfnDecode*) OpcUa_CallMethodResult_Decode,
                            (SOPC_EncodeableObject_PfnInitialize*) OpcUa_CallMethodResult_Initialize,
                            (SOPC_EncodeableObject_PfnClear*) OpcUa_CallMethodResult_Clear);
    }
    if (SOPC_STATUS_OK == status)
    {
        status =
            SOPC_Read_Array(buf, &a_pValue->NoOfDiagnosticInfos, (void**) &a_pValue->DiagnosticInfos,
                            sizeof(SOPC_DiagnosticInfo), (SOPC_EncodeableObject_PfnDecode*) SOPC_DiagnosticInfo_ReadAux,
                            (SOPC_EncodeableObject_PfnInitialize*) SOPC_DiagnosticInfo_InitializeAux,
                            (SOPC_EncodeableObject_PfnClear*) SOPC_DiagnosticInfo_ClearAux);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_CallResponse_Clear(a_pValue);
    }

    return status;
}
#endif
#endif

#ifndef OPCUA_EXCLUDE_DataChangeFilter
/*============================================================================
 * OpcUa_DataChangeFilter_Initialize
 *===========================================================================*/
void OpcUa_DataChangeFilter_Initialize(void* pValue)
{
    OpcUa_DataChangeFilter* a_pValue = (OpcUa_DataChangeFilter*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_DataChangeFilter_EncodeableType;
        SOPC_Initialize_EnumeratedType((int32_t*) &a_pValue->Trigger);
        SOPC_UInt32_Initialize(&a_pValue->DeadbandType);
        SOPC_Double_Initialize(&a_pValue->DeadbandValue);
    }
}

/*============================================================================
 * OpcUa_DataChangeFilter_Clear
 *===========================================================================*/
void OpcUa_DataChangeFilter_Clear(void* pValue)
{
    OpcUa_DataChangeFilter* a_pValue = (OpcUa_DataChangeFilter*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_Clear_EnumeratedType((int32_t*) &a_pValue->Trigger);
        SOPC_UInt32_Clear(&a_pValue->DeadbandType);
        SOPC_Double_Clear(&a_pValue->DeadbandValue);
    }
}

/*============================================================================
 * OpcUa_DataChangeFilter_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_DataChangeFilter_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_DataChangeFilter* a_pValue = (const OpcUa_DataChangeFilter*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Write_EnumeratedType(buf, (const int32_t*) &a_pValue->Trigger);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->DeadbandType, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Double_Write(&a_pValue->DeadbandValue, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_DataChangeFilter_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_DataChangeFilter_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_DataChangeFilter* a_pValue = (OpcUa_DataChangeFilter*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_DataChangeFilter_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_EnumeratedType(buf, (int32_t*) &a_pValue->Trigger);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->DeadbandType, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Double_Read(&a_pValue->DeadbandValue, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_DataChangeFilter_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_EventFilter
/*============================================================================
 * OpcUa_EventFilter_Initialize
 *===========================================================================*/
void OpcUa_EventFilter_Initialize(void* pValue)
{
    OpcUa_EventFilter* a_pValue = (OpcUa_EventFilter*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_EventFilter_EncodeableType;
        SOPC_Initialize_Array(&a_pValue->NoOfSelectClauses, (void**) &a_pValue->SelectClauses,
                              sizeof(OpcUa_SimpleAttributeOperand),
                              (SOPC_EncodeableObject_PfnInitialize*) OpcUa_SimpleAttributeOperand_Initialize);
        OpcUa_ContentFilter_Initialize(&a_pValue->WhereClause);
    }
}

/*============================================================================
 * OpcUa_EventFilter_Clear
 *===========================================================================*/
void OpcUa_EventFilter_Clear(void* pValue)
{
    OpcUa_EventFilter* a_pValue = (OpcUa_EventFilter*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_Clear_Array(&a_pValue->NoOfSelectClauses, (void**) &a_pValue->SelectClauses,
                         sizeof(OpcUa_SimpleAttributeOperand),
                         (SOPC_EncodeableObject_PfnClear*) OpcUa_SimpleAttributeOperand_Clear);
        OpcUa_ContentFilter_Clear(&a_pValue->WhereClause);
    }
}

/*============================================================================
 * OpcUa_EventFilter_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_EventFilter_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_EventFilter* a_pValue = (const OpcUa_EventFilter*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->SelectClauses;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfSelectClauses, &arr, sizeof(OpcUa_SimpleAttributeOperand),
                                  (SOPC_EncodeableObject_PfnEncode*) OpcUa_SimpleAttributeOperand_Encode);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_ContentFilter_Encode(&a_pValue->WhereClause, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_EventFilter_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_EventFilter_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_EventFilter* a_pValue = (OpcUa_EventFilter*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_EventFilter_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfSelectClauses, (void**) &a_pValue->SelectClauses,
                                 sizeof(OpcUa_SimpleAttributeOperand),
                                 (SOPC_EncodeableObject_PfnDecode*) OpcUa_SimpleAttributeOperand_Decode,
                                 (SOPC_EncodeableObject_PfnInitialize*) OpcUa_SimpleAttributeOperand_Initialize,
                                 (SOPC_EncodeableObject_PfnClear*) OpcUa_SimpleAttributeOperand_Clear);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_ContentFilter_Decode(&a_pValue->WhereClause, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_EventFilter_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_AggregateConfiguration
/*============================================================================
 * OpcUa_AggregateConfiguration_Initialize
 *===========================================================================*/
void OpcUa_AggregateConfiguration_Initialize(void* pValue)
{
    OpcUa_AggregateConfiguration* a_pValue = (OpcUa_AggregateConfiguration*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_AggregateConfiguration_EncodeableType;
        SOPC_Boolean_Initialize(&a_pValue->UseServerCapabilitiesDefaults);
        SOPC_Boolean_Initialize(&a_pValue->TreatUncertainAsBad);
        SOPC_Byte_Initialize(&a_pValue->PercentDataBad);
        SOPC_Byte_Initialize(&a_pValue->PercentDataGood);
        SOPC_Boolean_Initialize(&a_pValue->UseSlopedExtrapolation);
    }
}

/*============================================================================
 * OpcUa_AggregateConfiguration_Clear
 *===========================================================================*/
void OpcUa_AggregateConfiguration_Clear(void* pValue)
{
    OpcUa_AggregateConfiguration* a_pValue = (OpcUa_AggregateConfiguration*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_Boolean_Clear(&a_pValue->UseServerCapabilitiesDefaults);
        SOPC_Boolean_Clear(&a_pValue->TreatUncertainAsBad);
        SOPC_Byte_Clear(&a_pValue->PercentDataBad);
        SOPC_Byte_Clear(&a_pValue->PercentDataGood);
        SOPC_Boolean_Clear(&a_pValue->UseSlopedExtrapolation);
    }
}

/*============================================================================
 * OpcUa_AggregateConfiguration_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_AggregateConfiguration_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_AggregateConfiguration* a_pValue = (const OpcUa_AggregateConfiguration*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Write(&a_pValue->UseServerCapabilitiesDefaults, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Write(&a_pValue->TreatUncertainAsBad, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Byte_Write(&a_pValue->PercentDataBad, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Byte_Write(&a_pValue->PercentDataGood, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Write(&a_pValue->UseSlopedExtrapolation, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_AggregateConfiguration_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_AggregateConfiguration_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_AggregateConfiguration* a_pValue = (OpcUa_AggregateConfiguration*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_AggregateConfiguration_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Read(&a_pValue->UseServerCapabilitiesDefaults, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Read(&a_pValue->TreatUncertainAsBad, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Byte_Read(&a_pValue->PercentDataBad, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Byte_Read(&a_pValue->PercentDataGood, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Read(&a_pValue->UseSlopedExtrapolation, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_AggregateConfiguration_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_AggregateFilter
/*============================================================================
 * OpcUa_AggregateFilter_Initialize
 *===========================================================================*/
void OpcUa_AggregateFilter_Initialize(void* pValue)
{
    OpcUa_AggregateFilter* a_pValue = (OpcUa_AggregateFilter*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_AggregateFilter_EncodeableType;
        SOPC_DateTime_Initialize(&a_pValue->StartTime);
        SOPC_NodeId_Initialize(&a_pValue->AggregateType);
        SOPC_Double_Initialize(&a_pValue->ProcessingInterval);
        OpcUa_AggregateConfiguration_Initialize(&a_pValue->AggregateConfiguration);
    }
}

/*============================================================================
 * OpcUa_AggregateFilter_Clear
 *===========================================================================*/
void OpcUa_AggregateFilter_Clear(void* pValue)
{
    OpcUa_AggregateFilter* a_pValue = (OpcUa_AggregateFilter*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_DateTime_Clear(&a_pValue->StartTime);
        SOPC_NodeId_Clear(&a_pValue->AggregateType);
        SOPC_Double_Clear(&a_pValue->ProcessingInterval);
        OpcUa_AggregateConfiguration_Clear(&a_pValue->AggregateConfiguration);
    }
}

/*============================================================================
 * OpcUa_AggregateFilter_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_AggregateFilter_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_AggregateFilter* a_pValue = (const OpcUa_AggregateFilter*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_DateTime_Write(&a_pValue->StartTime, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Write(&a_pValue->AggregateType, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Double_Write(&a_pValue->ProcessingInterval, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_AggregateConfiguration_Encode(&a_pValue->AggregateConfiguration, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_AggregateFilter_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_AggregateFilter_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_AggregateFilter* a_pValue = (OpcUa_AggregateFilter*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_AggregateFilter_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_DateTime_Read(&a_pValue->StartTime, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Read(&a_pValue->AggregateType, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Double_Read(&a_pValue->ProcessingInterval, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_AggregateConfiguration_Decode(&a_pValue->AggregateConfiguration, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_AggregateFilter_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_EventFilterResult
/*============================================================================
 * OpcUa_EventFilterResult_Initialize
 *===========================================================================*/
void OpcUa_EventFilterResult_Initialize(void* pValue)
{
    OpcUa_EventFilterResult* a_pValue = (OpcUa_EventFilterResult*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_EventFilterResult_EncodeableType;
        SOPC_Initialize_Array(&a_pValue->NoOfSelectClauseResults, (void**) &a_pValue->SelectClauseResults,
                              sizeof(SOPC_StatusCode),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_StatusCode_InitializeAux);
        SOPC_Initialize_Array(&a_pValue->NoOfSelectClauseDiagnosticInfos,
                              (void**) &a_pValue->SelectClauseDiagnosticInfos, sizeof(SOPC_DiagnosticInfo),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_DiagnosticInfo_InitializeAux);
        OpcUa_ContentFilterResult_Initialize(&a_pValue->WhereClauseResult);
    }
}

/*============================================================================
 * OpcUa_EventFilterResult_Clear
 *===========================================================================*/
void OpcUa_EventFilterResult_Clear(void* pValue)
{
    OpcUa_EventFilterResult* a_pValue = (OpcUa_EventFilterResult*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_Clear_Array(&a_pValue->NoOfSelectClauseResults, (void**) &a_pValue->SelectClauseResults,
                         sizeof(SOPC_StatusCode), (SOPC_EncodeableObject_PfnClear*) SOPC_StatusCode_ClearAux);
        SOPC_Clear_Array(&a_pValue->NoOfSelectClauseDiagnosticInfos, (void**) &a_pValue->SelectClauseDiagnosticInfos,
                         sizeof(SOPC_DiagnosticInfo), (SOPC_EncodeableObject_PfnClear*) SOPC_DiagnosticInfo_ClearAux);
        OpcUa_ContentFilterResult_Clear(&a_pValue->WhereClauseResult);
    }
}

/*============================================================================
 * OpcUa_EventFilterResult_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_EventFilterResult_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_EventFilterResult* a_pValue = (const OpcUa_EventFilterResult*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->SelectClauseResults;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfSelectClauseResults, &arr, sizeof(SOPC_StatusCode),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_StatusCode_WriteAux);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->SelectClauseDiagnosticInfos;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfSelectClauseDiagnosticInfos, &arr, sizeof(SOPC_DiagnosticInfo),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_DiagnosticInfo_WriteAux);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_ContentFilterResult_Encode(&a_pValue->WhereClauseResult, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_EventFilterResult_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_EventFilterResult_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_EventFilterResult* a_pValue = (OpcUa_EventFilterResult*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_EventFilterResult_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfSelectClauseResults, (void**) &a_pValue->SelectClauseResults,
                                 sizeof(SOPC_StatusCode), (SOPC_EncodeableObject_PfnDecode*) SOPC_StatusCode_ReadAux,
                                 (SOPC_EncodeableObject_PfnInitialize*) SOPC_StatusCode_InitializeAux,
                                 (SOPC_EncodeableObject_PfnClear*) SOPC_StatusCode_ClearAux);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfSelectClauseDiagnosticInfos,
                                 (void**) &a_pValue->SelectClauseDiagnosticInfos, sizeof(SOPC_DiagnosticInfo),
                                 (SOPC_EncodeableObject_PfnDecode*) SOPC_DiagnosticInfo_ReadAux,
                                 (SOPC_EncodeableObject_PfnInitialize*) SOPC_DiagnosticInfo_InitializeAux,
                                 (SOPC_EncodeableObject_PfnClear*) SOPC_DiagnosticInfo_ClearAux);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_ContentFilterResult_Decode(&a_pValue->WhereClauseResult, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_EventFilterResult_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_AggregateFilterResult
/*============================================================================
 * OpcUa_AggregateFilterResult_Initialize
 *===========================================================================*/
void OpcUa_AggregateFilterResult_Initialize(void* pValue)
{
    OpcUa_AggregateFilterResult* a_pValue = (OpcUa_AggregateFilterResult*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_AggregateFilterResult_EncodeableType;
        SOPC_DateTime_Initialize(&a_pValue->RevisedStartTime);
        SOPC_Double_Initialize(&a_pValue->RevisedProcessingInterval);
        OpcUa_AggregateConfiguration_Initialize(&a_pValue->RevisedAggregateConfiguration);
    }
}

/*============================================================================
 * OpcUa_AggregateFilterResult_Clear
 *===========================================================================*/
void OpcUa_AggregateFilterResult_Clear(void* pValue)
{
    OpcUa_AggregateFilterResult* a_pValue = (OpcUa_AggregateFilterResult*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_DateTime_Clear(&a_pValue->RevisedStartTime);
        SOPC_Double_Clear(&a_pValue->RevisedProcessingInterval);
        OpcUa_AggregateConfiguration_Clear(&a_pValue->RevisedAggregateConfiguration);
    }
}

/*============================================================================
 * OpcUa_AggregateFilterResult_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_AggregateFilterResult_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_AggregateFilterResult* a_pValue = (const OpcUa_AggregateFilterResult*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_DateTime_Write(&a_pValue->RevisedStartTime, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Double_Write(&a_pValue->RevisedProcessingInterval, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_AggregateConfiguration_Encode(&a_pValue->RevisedAggregateConfiguration, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_AggregateFilterResult_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_AggregateFilterResult_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_AggregateFilterResult* a_pValue = (OpcUa_AggregateFilterResult*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_AggregateFilterResult_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_DateTime_Read(&a_pValue->RevisedStartTime, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Double_Read(&a_pValue->RevisedProcessingInterval, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_AggregateConfiguration_Decode(&a_pValue->RevisedAggregateConfiguration, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_AggregateFilterResult_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_MonitoringParameters
/*============================================================================
 * OpcUa_MonitoringParameters_Initialize
 *===========================================================================*/
void OpcUa_MonitoringParameters_Initialize(void* pValue)
{
    OpcUa_MonitoringParameters* a_pValue = (OpcUa_MonitoringParameters*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_MonitoringParameters_EncodeableType;
        SOPC_UInt32_Initialize(&a_pValue->ClientHandle);
        SOPC_Double_Initialize(&a_pValue->SamplingInterval);
        SOPC_ExtensionObject_Initialize(&a_pValue->Filter);
        SOPC_UInt32_Initialize(&a_pValue->QueueSize);
        SOPC_Boolean_Initialize(&a_pValue->DiscardOldest);
    }
}

/*============================================================================
 * OpcUa_MonitoringParameters_Clear
 *===========================================================================*/
void OpcUa_MonitoringParameters_Clear(void* pValue)
{
    OpcUa_MonitoringParameters* a_pValue = (OpcUa_MonitoringParameters*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_UInt32_Clear(&a_pValue->ClientHandle);
        SOPC_Double_Clear(&a_pValue->SamplingInterval);
        SOPC_ExtensionObject_Clear(&a_pValue->Filter);
        SOPC_UInt32_Clear(&a_pValue->QueueSize);
        SOPC_Boolean_Clear(&a_pValue->DiscardOldest);
    }
}

/*============================================================================
 * OpcUa_MonitoringParameters_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_MonitoringParameters_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_MonitoringParameters* a_pValue = (const OpcUa_MonitoringParameters*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->ClientHandle, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Double_Write(&a_pValue->SamplingInterval, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ExtensionObject_Write(&a_pValue->Filter, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->QueueSize, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Write(&a_pValue->DiscardOldest, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_MonitoringParameters_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_MonitoringParameters_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_MonitoringParameters* a_pValue = (OpcUa_MonitoringParameters*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_MonitoringParameters_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->ClientHandle, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Double_Read(&a_pValue->SamplingInterval, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ExtensionObject_Read(&a_pValue->Filter, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->QueueSize, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Read(&a_pValue->DiscardOldest, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_MonitoringParameters_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_MonitoredItemCreateRequest
/*============================================================================
 * OpcUa_MonitoredItemCreateRequest_Initialize
 *===========================================================================*/
void OpcUa_MonitoredItemCreateRequest_Initialize(void* pValue)
{
    OpcUa_MonitoredItemCreateRequest* a_pValue = (OpcUa_MonitoredItemCreateRequest*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_MonitoredItemCreateRequest_EncodeableType;
        OpcUa_ReadValueId_Initialize(&a_pValue->ItemToMonitor);
        SOPC_Initialize_EnumeratedType((int32_t*) &a_pValue->MonitoringMode);
        OpcUa_MonitoringParameters_Initialize(&a_pValue->RequestedParameters);
    }
}

/*============================================================================
 * OpcUa_MonitoredItemCreateRequest_Clear
 *===========================================================================*/
void OpcUa_MonitoredItemCreateRequest_Clear(void* pValue)
{
    OpcUa_MonitoredItemCreateRequest* a_pValue = (OpcUa_MonitoredItemCreateRequest*) pValue;
    if (a_pValue != NULL)
    {
        OpcUa_ReadValueId_Clear(&a_pValue->ItemToMonitor);
        SOPC_Clear_EnumeratedType((int32_t*) &a_pValue->MonitoringMode);
        OpcUa_MonitoringParameters_Clear(&a_pValue->RequestedParameters);
    }
}

/*============================================================================
 * OpcUa_MonitoredItemCreateRequest_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_MonitoredItemCreateRequest_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_MonitoredItemCreateRequest* a_pValue = (const OpcUa_MonitoredItemCreateRequest*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_ReadValueId_Encode(&a_pValue->ItemToMonitor, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Write_EnumeratedType(buf, (const int32_t*) &a_pValue->MonitoringMode);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_MonitoringParameters_Encode(&a_pValue->RequestedParameters, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_MonitoredItemCreateRequest_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_MonitoredItemCreateRequest_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_MonitoredItemCreateRequest* a_pValue = (OpcUa_MonitoredItemCreateRequest*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_MonitoredItemCreateRequest_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_ReadValueId_Decode(&a_pValue->ItemToMonitor, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_EnumeratedType(buf, (int32_t*) &a_pValue->MonitoringMode);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_MonitoringParameters_Decode(&a_pValue->RequestedParameters, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_MonitoredItemCreateRequest_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_MonitoredItemCreateResult
/*============================================================================
 * OpcUa_MonitoredItemCreateResult_Initialize
 *===========================================================================*/
void OpcUa_MonitoredItemCreateResult_Initialize(void* pValue)
{
    OpcUa_MonitoredItemCreateResult* a_pValue = (OpcUa_MonitoredItemCreateResult*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_MonitoredItemCreateResult_EncodeableType;
        SOPC_StatusCode_Initialize(&a_pValue->StatusCode);
        SOPC_UInt32_Initialize(&a_pValue->MonitoredItemId);
        SOPC_Double_Initialize(&a_pValue->RevisedSamplingInterval);
        SOPC_UInt32_Initialize(&a_pValue->RevisedQueueSize);
        SOPC_ExtensionObject_Initialize(&a_pValue->FilterResult);
    }
}

/*============================================================================
 * OpcUa_MonitoredItemCreateResult_Clear
 *===========================================================================*/
void OpcUa_MonitoredItemCreateResult_Clear(void* pValue)
{
    OpcUa_MonitoredItemCreateResult* a_pValue = (OpcUa_MonitoredItemCreateResult*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_StatusCode_Clear(&a_pValue->StatusCode);
        SOPC_UInt32_Clear(&a_pValue->MonitoredItemId);
        SOPC_Double_Clear(&a_pValue->RevisedSamplingInterval);
        SOPC_UInt32_Clear(&a_pValue->RevisedQueueSize);
        SOPC_ExtensionObject_Clear(&a_pValue->FilterResult);
    }
}

/*============================================================================
 * OpcUa_MonitoredItemCreateResult_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_MonitoredItemCreateResult_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_MonitoredItemCreateResult* a_pValue = (const OpcUa_MonitoredItemCreateResult*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_StatusCode_Write(&a_pValue->StatusCode, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->MonitoredItemId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Double_Write(&a_pValue->RevisedSamplingInterval, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->RevisedQueueSize, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ExtensionObject_Write(&a_pValue->FilterResult, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_MonitoredItemCreateResult_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_MonitoredItemCreateResult_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_MonitoredItemCreateResult* a_pValue = (OpcUa_MonitoredItemCreateResult*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_MonitoredItemCreateResult_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_StatusCode_Read(&a_pValue->StatusCode, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->MonitoredItemId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Double_Read(&a_pValue->RevisedSamplingInterval, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->RevisedQueueSize, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ExtensionObject_Read(&a_pValue->FilterResult, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_MonitoredItemCreateResult_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_CreateMonitoredItems
#ifndef OPCUA_EXCLUDE_CreateMonitoredItemsRequest
/*============================================================================
 * OpcUa_CreateMonitoredItemsRequest_Initialize
 *===========================================================================*/
void OpcUa_CreateMonitoredItemsRequest_Initialize(void* pValue)
{
    OpcUa_CreateMonitoredItemsRequest* a_pValue = (OpcUa_CreateMonitoredItemsRequest*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_CreateMonitoredItemsRequest_EncodeableType;
        SOPC_UInt32_Initialize(&a_pValue->SubscriptionId);
        SOPC_Initialize_EnumeratedType((int32_t*) &a_pValue->TimestampsToReturn);
        SOPC_Initialize_Array(&a_pValue->NoOfItemsToCreate, (void**) &a_pValue->ItemsToCreate,
                              sizeof(OpcUa_MonitoredItemCreateRequest),
                              (SOPC_EncodeableObject_PfnInitialize*) OpcUa_MonitoredItemCreateRequest_Initialize);
    }
}

/*============================================================================
 * OpcUa_CreateMonitoredItemsRequest_Clear
 *===========================================================================*/
void OpcUa_CreateMonitoredItemsRequest_Clear(void* pValue)
{
    OpcUa_CreateMonitoredItemsRequest* a_pValue = (OpcUa_CreateMonitoredItemsRequest*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_UInt32_Clear(&a_pValue->SubscriptionId);
        SOPC_Clear_EnumeratedType((int32_t*) &a_pValue->TimestampsToReturn);
        SOPC_Clear_Array(&a_pValue->NoOfItemsToCreate, (void**) &a_pValue->ItemsToCreate,
                         sizeof(OpcUa_MonitoredItemCreateRequest),
                         (SOPC_EncodeableObject_PfnClear*) OpcUa_MonitoredItemCreateRequest_Clear);
    }
}

/*============================================================================
 * OpcUa_CreateMonitoredItemsRequest_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_CreateMonitoredItemsRequest_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_CreateMonitoredItemsRequest* a_pValue = (const OpcUa_CreateMonitoredItemsRequest*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->SubscriptionId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Write_EnumeratedType(buf, (const int32_t*) &a_pValue->TimestampsToReturn);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->ItemsToCreate;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfItemsToCreate, &arr, sizeof(OpcUa_MonitoredItemCreateRequest),
                                  (SOPC_EncodeableObject_PfnEncode*) OpcUa_MonitoredItemCreateRequest_Encode);
    }

    return status;
}

/*============================================================================
 * OpcUa_CreateMonitoredItemsRequest_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_CreateMonitoredItemsRequest_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_CreateMonitoredItemsRequest* a_pValue = (OpcUa_CreateMonitoredItemsRequest*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_CreateMonitoredItemsRequest_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->SubscriptionId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_EnumeratedType(buf, (int32_t*) &a_pValue->TimestampsToReturn);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfItemsToCreate, (void**) &a_pValue->ItemsToCreate,
                                 sizeof(OpcUa_MonitoredItemCreateRequest),
                                 (SOPC_EncodeableObject_PfnDecode*) OpcUa_MonitoredItemCreateRequest_Decode,
                                 (SOPC_EncodeableObject_PfnInitialize*) OpcUa_MonitoredItemCreateRequest_Initialize,
                                 (SOPC_EncodeableObject_PfnClear*) OpcUa_MonitoredItemCreateRequest_Clear);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_CreateMonitoredItemsRequest_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_CreateMonitoredItemsResponse
/*============================================================================
 * OpcUa_CreateMonitoredItemsResponse_Initialize
 *===========================================================================*/
void OpcUa_CreateMonitoredItemsResponse_Initialize(void* pValue)
{
    OpcUa_CreateMonitoredItemsResponse* a_pValue = (OpcUa_CreateMonitoredItemsResponse*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_CreateMonitoredItemsResponse_EncodeableType;
        OpcUa_ResponseHeader_Initialize(&a_pValue->ResponseHeader);
        SOPC_Initialize_Array(&a_pValue->NoOfResults, (void**) &a_pValue->Results,
                              sizeof(OpcUa_MonitoredItemCreateResult),
                              (SOPC_EncodeableObject_PfnInitialize*) OpcUa_MonitoredItemCreateResult_Initialize);
        SOPC_Initialize_Array(&a_pValue->NoOfDiagnosticInfos, (void**) &a_pValue->DiagnosticInfos,
                              sizeof(SOPC_DiagnosticInfo),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_DiagnosticInfo_InitializeAux);
    }
}

/*============================================================================
 * OpcUa_CreateMonitoredItemsResponse_Clear
 *===========================================================================*/
void OpcUa_CreateMonitoredItemsResponse_Clear(void* pValue)
{
    OpcUa_CreateMonitoredItemsResponse* a_pValue = (OpcUa_CreateMonitoredItemsResponse*) pValue;
    if (a_pValue != NULL)
    {
        OpcUa_ResponseHeader_Clear(&a_pValue->ResponseHeader);
        SOPC_Clear_Array(&a_pValue->NoOfResults, (void**) &a_pValue->Results, sizeof(OpcUa_MonitoredItemCreateResult),
                         (SOPC_EncodeableObject_PfnClear*) OpcUa_MonitoredItemCreateResult_Clear);
        SOPC_Clear_Array(&a_pValue->NoOfDiagnosticInfos, (void**) &a_pValue->DiagnosticInfos,
                         sizeof(SOPC_DiagnosticInfo), (SOPC_EncodeableObject_PfnClear*) SOPC_DiagnosticInfo_ClearAux);
    }
}

/*============================================================================
 * OpcUa_CreateMonitoredItemsResponse_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_CreateMonitoredItemsResponse_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_CreateMonitoredItemsResponse* a_pValue = (const OpcUa_CreateMonitoredItemsResponse*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->Results;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfResults, &arr, sizeof(OpcUa_MonitoredItemCreateResult),
                                  (SOPC_EncodeableObject_PfnEncode*) OpcUa_MonitoredItemCreateResult_Encode);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->DiagnosticInfos;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfDiagnosticInfos, &arr, sizeof(SOPC_DiagnosticInfo),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_DiagnosticInfo_WriteAux);
    }

    return status;
}

/*============================================================================
 * OpcUa_CreateMonitoredItemsResponse_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_CreateMonitoredItemsResponse_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_CreateMonitoredItemsResponse* a_pValue = (OpcUa_CreateMonitoredItemsResponse*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_CreateMonitoredItemsResponse_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfResults, (void**) &a_pValue->Results,
                                 sizeof(OpcUa_MonitoredItemCreateResult),
                                 (SOPC_EncodeableObject_PfnDecode*) OpcUa_MonitoredItemCreateResult_Decode,
                                 (SOPC_EncodeableObject_PfnInitialize*) OpcUa_MonitoredItemCreateResult_Initialize,
                                 (SOPC_EncodeableObject_PfnClear*) OpcUa_MonitoredItemCreateResult_Clear);
    }
    if (SOPC_STATUS_OK == status)
    {
        status =
            SOPC_Read_Array(buf, &a_pValue->NoOfDiagnosticInfos, (void**) &a_pValue->DiagnosticInfos,
                            sizeof(SOPC_DiagnosticInfo), (SOPC_EncodeableObject_PfnDecode*) SOPC_DiagnosticInfo_ReadAux,
                            (SOPC_EncodeableObject_PfnInitialize*) SOPC_DiagnosticInfo_InitializeAux,
                            (SOPC_EncodeableObject_PfnClear*) SOPC_DiagnosticInfo_ClearAux);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_CreateMonitoredItemsResponse_Clear(a_pValue);
    }

    return status;
}
#endif
#endif

#ifndef OPCUA_EXCLUDE_MonitoredItemModifyRequest
/*============================================================================
 * OpcUa_MonitoredItemModifyRequest_Initialize
 *===========================================================================*/
void OpcUa_MonitoredItemModifyRequest_Initialize(void* pValue)
{
    OpcUa_MonitoredItemModifyRequest* a_pValue = (OpcUa_MonitoredItemModifyRequest*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_MonitoredItemModifyRequest_EncodeableType;
        SOPC_UInt32_Initialize(&a_pValue->MonitoredItemId);
        OpcUa_MonitoringParameters_Initialize(&a_pValue->RequestedParameters);
    }
}

/*============================================================================
 * OpcUa_MonitoredItemModifyRequest_Clear
 *===========================================================================*/
void OpcUa_MonitoredItemModifyRequest_Clear(void* pValue)
{
    OpcUa_MonitoredItemModifyRequest* a_pValue = (OpcUa_MonitoredItemModifyRequest*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_UInt32_Clear(&a_pValue->MonitoredItemId);
        OpcUa_MonitoringParameters_Clear(&a_pValue->RequestedParameters);
    }
}

/*============================================================================
 * OpcUa_MonitoredItemModifyRequest_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_MonitoredItemModifyRequest_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_MonitoredItemModifyRequest* a_pValue = (const OpcUa_MonitoredItemModifyRequest*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->MonitoredItemId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_MonitoringParameters_Encode(&a_pValue->RequestedParameters, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_MonitoredItemModifyRequest_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_MonitoredItemModifyRequest_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_MonitoredItemModifyRequest* a_pValue = (OpcUa_MonitoredItemModifyRequest*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_MonitoredItemModifyRequest_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->MonitoredItemId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_MonitoringParameters_Decode(&a_pValue->RequestedParameters, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_MonitoredItemModifyRequest_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_MonitoredItemModifyResult
/*============================================================================
 * OpcUa_MonitoredItemModifyResult_Initialize
 *===========================================================================*/
void OpcUa_MonitoredItemModifyResult_Initialize(void* pValue)
{
    OpcUa_MonitoredItemModifyResult* a_pValue = (OpcUa_MonitoredItemModifyResult*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_MonitoredItemModifyResult_EncodeableType;
        SOPC_StatusCode_Initialize(&a_pValue->StatusCode);
        SOPC_Double_Initialize(&a_pValue->RevisedSamplingInterval);
        SOPC_UInt32_Initialize(&a_pValue->RevisedQueueSize);
        SOPC_ExtensionObject_Initialize(&a_pValue->FilterResult);
    }
}

/*============================================================================
 * OpcUa_MonitoredItemModifyResult_Clear
 *===========================================================================*/
void OpcUa_MonitoredItemModifyResult_Clear(void* pValue)
{
    OpcUa_MonitoredItemModifyResult* a_pValue = (OpcUa_MonitoredItemModifyResult*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_StatusCode_Clear(&a_pValue->StatusCode);
        SOPC_Double_Clear(&a_pValue->RevisedSamplingInterval);
        SOPC_UInt32_Clear(&a_pValue->RevisedQueueSize);
        SOPC_ExtensionObject_Clear(&a_pValue->FilterResult);
    }
}

/*============================================================================
 * OpcUa_MonitoredItemModifyResult_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_MonitoredItemModifyResult_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_MonitoredItemModifyResult* a_pValue = (const OpcUa_MonitoredItemModifyResult*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_StatusCode_Write(&a_pValue->StatusCode, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Double_Write(&a_pValue->RevisedSamplingInterval, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->RevisedQueueSize, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ExtensionObject_Write(&a_pValue->FilterResult, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_MonitoredItemModifyResult_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_MonitoredItemModifyResult_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_MonitoredItemModifyResult* a_pValue = (OpcUa_MonitoredItemModifyResult*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_MonitoredItemModifyResult_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_StatusCode_Read(&a_pValue->StatusCode, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Double_Read(&a_pValue->RevisedSamplingInterval, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->RevisedQueueSize, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ExtensionObject_Read(&a_pValue->FilterResult, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_MonitoredItemModifyResult_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_ModifyMonitoredItems
#ifndef OPCUA_EXCLUDE_ModifyMonitoredItemsRequest
/*============================================================================
 * OpcUa_ModifyMonitoredItemsRequest_Initialize
 *===========================================================================*/
void OpcUa_ModifyMonitoredItemsRequest_Initialize(void* pValue)
{
    OpcUa_ModifyMonitoredItemsRequest* a_pValue = (OpcUa_ModifyMonitoredItemsRequest*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_ModifyMonitoredItemsRequest_EncodeableType;
        SOPC_UInt32_Initialize(&a_pValue->SubscriptionId);
        SOPC_Initialize_EnumeratedType((int32_t*) &a_pValue->TimestampsToReturn);
        SOPC_Initialize_Array(&a_pValue->NoOfItemsToModify, (void**) &a_pValue->ItemsToModify,
                              sizeof(OpcUa_MonitoredItemModifyRequest),
                              (SOPC_EncodeableObject_PfnInitialize*) OpcUa_MonitoredItemModifyRequest_Initialize);
    }
}

/*============================================================================
 * OpcUa_ModifyMonitoredItemsRequest_Clear
 *===========================================================================*/
void OpcUa_ModifyMonitoredItemsRequest_Clear(void* pValue)
{
    OpcUa_ModifyMonitoredItemsRequest* a_pValue = (OpcUa_ModifyMonitoredItemsRequest*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_UInt32_Clear(&a_pValue->SubscriptionId);
        SOPC_Clear_EnumeratedType((int32_t*) &a_pValue->TimestampsToReturn);
        SOPC_Clear_Array(&a_pValue->NoOfItemsToModify, (void**) &a_pValue->ItemsToModify,
                         sizeof(OpcUa_MonitoredItemModifyRequest),
                         (SOPC_EncodeableObject_PfnClear*) OpcUa_MonitoredItemModifyRequest_Clear);
    }
}

/*============================================================================
 * OpcUa_ModifyMonitoredItemsRequest_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_ModifyMonitoredItemsRequest_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_ModifyMonitoredItemsRequest* a_pValue = (const OpcUa_ModifyMonitoredItemsRequest*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->SubscriptionId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Write_EnumeratedType(buf, (const int32_t*) &a_pValue->TimestampsToReturn);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->ItemsToModify;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfItemsToModify, &arr, sizeof(OpcUa_MonitoredItemModifyRequest),
                                  (SOPC_EncodeableObject_PfnEncode*) OpcUa_MonitoredItemModifyRequest_Encode);
    }

    return status;
}

/*============================================================================
 * OpcUa_ModifyMonitoredItemsRequest_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_ModifyMonitoredItemsRequest_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_ModifyMonitoredItemsRequest* a_pValue = (OpcUa_ModifyMonitoredItemsRequest*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_ModifyMonitoredItemsRequest_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->SubscriptionId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_EnumeratedType(buf, (int32_t*) &a_pValue->TimestampsToReturn);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfItemsToModify, (void**) &a_pValue->ItemsToModify,
                                 sizeof(OpcUa_MonitoredItemModifyRequest),
                                 (SOPC_EncodeableObject_PfnDecode*) OpcUa_MonitoredItemModifyRequest_Decode,
                                 (SOPC_EncodeableObject_PfnInitialize*) OpcUa_MonitoredItemModifyRequest_Initialize,
                                 (SOPC_EncodeableObject_PfnClear*) OpcUa_MonitoredItemModifyRequest_Clear);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_ModifyMonitoredItemsRequest_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_ModifyMonitoredItemsResponse
/*============================================================================
 * OpcUa_ModifyMonitoredItemsResponse_Initialize
 *===========================================================================*/
void OpcUa_ModifyMonitoredItemsResponse_Initialize(void* pValue)
{
    OpcUa_ModifyMonitoredItemsResponse* a_pValue = (OpcUa_ModifyMonitoredItemsResponse*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_ModifyMonitoredItemsResponse_EncodeableType;
        OpcUa_ResponseHeader_Initialize(&a_pValue->ResponseHeader);
        SOPC_Initialize_Array(&a_pValue->NoOfResults, (void**) &a_pValue->Results,
                              sizeof(OpcUa_MonitoredItemModifyResult),
                              (SOPC_EncodeableObject_PfnInitialize*) OpcUa_MonitoredItemModifyResult_Initialize);
        SOPC_Initialize_Array(&a_pValue->NoOfDiagnosticInfos, (void**) &a_pValue->DiagnosticInfos,
                              sizeof(SOPC_DiagnosticInfo),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_DiagnosticInfo_InitializeAux);
    }
}

/*============================================================================
 * OpcUa_ModifyMonitoredItemsResponse_Clear
 *===========================================================================*/
void OpcUa_ModifyMonitoredItemsResponse_Clear(void* pValue)
{
    OpcUa_ModifyMonitoredItemsResponse* a_pValue = (OpcUa_ModifyMonitoredItemsResponse*) pValue;
    if (a_pValue != NULL)
    {
        OpcUa_ResponseHeader_Clear(&a_pValue->ResponseHeader);
        SOPC_Clear_Array(&a_pValue->NoOfResults, (void**) &a_pValue->Results, sizeof(OpcUa_MonitoredItemModifyResult),
                         (SOPC_EncodeableObject_PfnClear*) OpcUa_MonitoredItemModifyResult_Clear);
        SOPC_Clear_Array(&a_pValue->NoOfDiagnosticInfos, (void**) &a_pValue->DiagnosticInfos,
                         sizeof(SOPC_DiagnosticInfo), (SOPC_EncodeableObject_PfnClear*) SOPC_DiagnosticInfo_ClearAux);
    }
}

/*============================================================================
 * OpcUa_ModifyMonitoredItemsResponse_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_ModifyMonitoredItemsResponse_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_ModifyMonitoredItemsResponse* a_pValue = (const OpcUa_ModifyMonitoredItemsResponse*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->Results;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfResults, &arr, sizeof(OpcUa_MonitoredItemModifyResult),
                                  (SOPC_EncodeableObject_PfnEncode*) OpcUa_MonitoredItemModifyResult_Encode);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->DiagnosticInfos;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfDiagnosticInfos, &arr, sizeof(SOPC_DiagnosticInfo),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_DiagnosticInfo_WriteAux);
    }

    return status;
}

/*============================================================================
 * OpcUa_ModifyMonitoredItemsResponse_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_ModifyMonitoredItemsResponse_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_ModifyMonitoredItemsResponse* a_pValue = (OpcUa_ModifyMonitoredItemsResponse*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_ModifyMonitoredItemsResponse_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfResults, (void**) &a_pValue->Results,
                                 sizeof(OpcUa_MonitoredItemModifyResult),
                                 (SOPC_EncodeableObject_PfnDecode*) OpcUa_MonitoredItemModifyResult_Decode,
                                 (SOPC_EncodeableObject_PfnInitialize*) OpcUa_MonitoredItemModifyResult_Initialize,
                                 (SOPC_EncodeableObject_PfnClear*) OpcUa_MonitoredItemModifyResult_Clear);
    }
    if (SOPC_STATUS_OK == status)
    {
        status =
            SOPC_Read_Array(buf, &a_pValue->NoOfDiagnosticInfos, (void**) &a_pValue->DiagnosticInfos,
                            sizeof(SOPC_DiagnosticInfo), (SOPC_EncodeableObject_PfnDecode*) SOPC_DiagnosticInfo_ReadAux,
                            (SOPC_EncodeableObject_PfnInitialize*) SOPC_DiagnosticInfo_InitializeAux,
                            (SOPC_EncodeableObject_PfnClear*) SOPC_DiagnosticInfo_ClearAux);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_ModifyMonitoredItemsResponse_Clear(a_pValue);
    }

    return status;
}
#endif
#endif

#ifndef OPCUA_EXCLUDE_SetMonitoringMode
#ifndef OPCUA_EXCLUDE_SetMonitoringModeRequest
/*============================================================================
 * OpcUa_SetMonitoringModeRequest_Initialize
 *===========================================================================*/
void OpcUa_SetMonitoringModeRequest_Initialize(void* pValue)
{
    OpcUa_SetMonitoringModeRequest* a_pValue = (OpcUa_SetMonitoringModeRequest*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_SetMonitoringModeRequest_EncodeableType;
        SOPC_UInt32_Initialize(&a_pValue->SubscriptionId);
        SOPC_Initialize_EnumeratedType((int32_t*) &a_pValue->MonitoringMode);
        SOPC_Initialize_Array(&a_pValue->NoOfMonitoredItemIds, (void**) &a_pValue->MonitoredItemIds, sizeof(uint32_t),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_UInt32_InitializeAux);
    }
}

/*============================================================================
 * OpcUa_SetMonitoringModeRequest_Clear
 *===========================================================================*/
void OpcUa_SetMonitoringModeRequest_Clear(void* pValue)
{
    OpcUa_SetMonitoringModeRequest* a_pValue = (OpcUa_SetMonitoringModeRequest*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_UInt32_Clear(&a_pValue->SubscriptionId);
        SOPC_Clear_EnumeratedType((int32_t*) &a_pValue->MonitoringMode);
        SOPC_Clear_Array(&a_pValue->NoOfMonitoredItemIds, (void**) &a_pValue->MonitoredItemIds, sizeof(uint32_t),
                         (SOPC_EncodeableObject_PfnClear*) SOPC_UInt32_ClearAux);
    }
}

/*============================================================================
 * OpcUa_SetMonitoringModeRequest_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_SetMonitoringModeRequest_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_SetMonitoringModeRequest* a_pValue = (const OpcUa_SetMonitoringModeRequest*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->SubscriptionId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Write_EnumeratedType(buf, (const int32_t*) &a_pValue->MonitoringMode);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->MonitoredItemIds;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfMonitoredItemIds, &arr, sizeof(uint32_t),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_UInt32_WriteAux);
    }

    return status;
}

/*============================================================================
 * OpcUa_SetMonitoringModeRequest_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_SetMonitoringModeRequest_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_SetMonitoringModeRequest* a_pValue = (OpcUa_SetMonitoringModeRequest*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_SetMonitoringModeRequest_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->SubscriptionId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_EnumeratedType(buf, (int32_t*) &a_pValue->MonitoringMode);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfMonitoredItemIds, (void**) &a_pValue->MonitoredItemIds,
                                 sizeof(uint32_t), (SOPC_EncodeableObject_PfnDecode*) SOPC_UInt32_ReadAux,
                                 (SOPC_EncodeableObject_PfnInitialize*) SOPC_UInt32_InitializeAux,
                                 (SOPC_EncodeableObject_PfnClear*) SOPC_UInt32_ClearAux);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_SetMonitoringModeRequest_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_SetMonitoringModeResponse
/*============================================================================
 * OpcUa_SetMonitoringModeResponse_Initialize
 *===========================================================================*/
void OpcUa_SetMonitoringModeResponse_Initialize(void* pValue)
{
    OpcUa_SetMonitoringModeResponse* a_pValue = (OpcUa_SetMonitoringModeResponse*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_SetMonitoringModeResponse_EncodeableType;
        OpcUa_ResponseHeader_Initialize(&a_pValue->ResponseHeader);
        SOPC_Initialize_Array(&a_pValue->NoOfResults, (void**) &a_pValue->Results, sizeof(SOPC_StatusCode),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_StatusCode_InitializeAux);
        SOPC_Initialize_Array(&a_pValue->NoOfDiagnosticInfos, (void**) &a_pValue->DiagnosticInfos,
                              sizeof(SOPC_DiagnosticInfo),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_DiagnosticInfo_InitializeAux);
    }
}

/*============================================================================
 * OpcUa_SetMonitoringModeResponse_Clear
 *===========================================================================*/
void OpcUa_SetMonitoringModeResponse_Clear(void* pValue)
{
    OpcUa_SetMonitoringModeResponse* a_pValue = (OpcUa_SetMonitoringModeResponse*) pValue;
    if (a_pValue != NULL)
    {
        OpcUa_ResponseHeader_Clear(&a_pValue->ResponseHeader);
        SOPC_Clear_Array(&a_pValue->NoOfResults, (void**) &a_pValue->Results, sizeof(SOPC_StatusCode),
                         (SOPC_EncodeableObject_PfnClear*) SOPC_StatusCode_ClearAux);
        SOPC_Clear_Array(&a_pValue->NoOfDiagnosticInfos, (void**) &a_pValue->DiagnosticInfos,
                         sizeof(SOPC_DiagnosticInfo), (SOPC_EncodeableObject_PfnClear*) SOPC_DiagnosticInfo_ClearAux);
    }
}

/*============================================================================
 * OpcUa_SetMonitoringModeResponse_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_SetMonitoringModeResponse_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_SetMonitoringModeResponse* a_pValue = (const OpcUa_SetMonitoringModeResponse*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->Results;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfResults, &arr, sizeof(SOPC_StatusCode),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_StatusCode_WriteAux);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->DiagnosticInfos;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfDiagnosticInfos, &arr, sizeof(SOPC_DiagnosticInfo),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_DiagnosticInfo_WriteAux);
    }

    return status;
}

/*============================================================================
 * OpcUa_SetMonitoringModeResponse_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_SetMonitoringModeResponse_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_SetMonitoringModeResponse* a_pValue = (OpcUa_SetMonitoringModeResponse*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_SetMonitoringModeResponse_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfResults, (void**) &a_pValue->Results, sizeof(SOPC_StatusCode),
                                 (SOPC_EncodeableObject_PfnDecode*) SOPC_StatusCode_ReadAux,
                                 (SOPC_EncodeableObject_PfnInitialize*) SOPC_StatusCode_InitializeAux,
                                 (SOPC_EncodeableObject_PfnClear*) SOPC_StatusCode_ClearAux);
    }
    if (SOPC_STATUS_OK == status)
    {
        status =
            SOPC_Read_Array(buf, &a_pValue->NoOfDiagnosticInfos, (void**) &a_pValue->DiagnosticInfos,
                            sizeof(SOPC_DiagnosticInfo), (SOPC_EncodeableObject_PfnDecode*) SOPC_DiagnosticInfo_ReadAux,
                            (SOPC_EncodeableObject_PfnInitialize*) SOPC_DiagnosticInfo_InitializeAux,
                            (SOPC_EncodeableObject_PfnClear*) SOPC_DiagnosticInfo_ClearAux);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_SetMonitoringModeResponse_Clear(a_pValue);
    }

    return status;
}
#endif
#endif

#ifndef OPCUA_EXCLUDE_SetTriggering
#ifndef OPCUA_EXCLUDE_SetTriggeringRequest
/*============================================================================
 * OpcUa_SetTriggeringRequest_Initialize
 *===========================================================================*/
void OpcUa_SetTriggeringRequest_Initialize(void* pValue)
{
    OpcUa_SetTriggeringRequest* a_pValue = (OpcUa_SetTriggeringRequest*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_SetTriggeringRequest_EncodeableType;
        SOPC_UInt32_Initialize(&a_pValue->SubscriptionId);
        SOPC_UInt32_Initialize(&a_pValue->TriggeringItemId);
        SOPC_Initialize_Array(&a_pValue->NoOfLinksToAdd, (void**) &a_pValue->LinksToAdd, sizeof(uint32_t),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_UInt32_InitializeAux);
        SOPC_Initialize_Array(&a_pValue->NoOfLinksToRemove, (void**) &a_pValue->LinksToRemove, sizeof(uint32_t),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_UInt32_InitializeAux);
    }
}

/*============================================================================
 * OpcUa_SetTriggeringRequest_Clear
 *===========================================================================*/
void OpcUa_SetTriggeringRequest_Clear(void* pValue)
{
    OpcUa_SetTriggeringRequest* a_pValue = (OpcUa_SetTriggeringRequest*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_UInt32_Clear(&a_pValue->SubscriptionId);
        SOPC_UInt32_Clear(&a_pValue->TriggeringItemId);
        SOPC_Clear_Array(&a_pValue->NoOfLinksToAdd, (void**) &a_pValue->LinksToAdd, sizeof(uint32_t),
                         (SOPC_EncodeableObject_PfnClear*) SOPC_UInt32_ClearAux);
        SOPC_Clear_Array(&a_pValue->NoOfLinksToRemove, (void**) &a_pValue->LinksToRemove, sizeof(uint32_t),
                         (SOPC_EncodeableObject_PfnClear*) SOPC_UInt32_ClearAux);
    }
}

/*============================================================================
 * OpcUa_SetTriggeringRequest_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_SetTriggeringRequest_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_SetTriggeringRequest* a_pValue = (const OpcUa_SetTriggeringRequest*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->SubscriptionId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->TriggeringItemId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->LinksToAdd;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfLinksToAdd, &arr, sizeof(uint32_t),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_UInt32_WriteAux);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->LinksToRemove;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfLinksToRemove, &arr, sizeof(uint32_t),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_UInt32_WriteAux);
    }

    return status;
}

/*============================================================================
 * OpcUa_SetTriggeringRequest_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_SetTriggeringRequest_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_SetTriggeringRequest* a_pValue = (OpcUa_SetTriggeringRequest*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_SetTriggeringRequest_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->SubscriptionId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->TriggeringItemId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfLinksToAdd, (void**) &a_pValue->LinksToAdd, sizeof(uint32_t),
                                 (SOPC_EncodeableObject_PfnDecode*) SOPC_UInt32_ReadAux,
                                 (SOPC_EncodeableObject_PfnInitialize*) SOPC_UInt32_InitializeAux,
                                 (SOPC_EncodeableObject_PfnClear*) SOPC_UInt32_ClearAux);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfLinksToRemove, (void**) &a_pValue->LinksToRemove, sizeof(uint32_t),
                                 (SOPC_EncodeableObject_PfnDecode*) SOPC_UInt32_ReadAux,
                                 (SOPC_EncodeableObject_PfnInitialize*) SOPC_UInt32_InitializeAux,
                                 (SOPC_EncodeableObject_PfnClear*) SOPC_UInt32_ClearAux);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_SetTriggeringRequest_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_SetTriggeringResponse
/*============================================================================
 * OpcUa_SetTriggeringResponse_Initialize
 *===========================================================================*/
void OpcUa_SetTriggeringResponse_Initialize(void* pValue)
{
    OpcUa_SetTriggeringResponse* a_pValue = (OpcUa_SetTriggeringResponse*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_SetTriggeringResponse_EncodeableType;
        OpcUa_ResponseHeader_Initialize(&a_pValue->ResponseHeader);
        SOPC_Initialize_Array(&a_pValue->NoOfAddResults, (void**) &a_pValue->AddResults, sizeof(SOPC_StatusCode),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_StatusCode_InitializeAux);
        SOPC_Initialize_Array(&a_pValue->NoOfAddDiagnosticInfos, (void**) &a_pValue->AddDiagnosticInfos,
                              sizeof(SOPC_DiagnosticInfo),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_DiagnosticInfo_InitializeAux);
        SOPC_Initialize_Array(&a_pValue->NoOfRemoveResults, (void**) &a_pValue->RemoveResults, sizeof(SOPC_StatusCode),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_StatusCode_InitializeAux);
        SOPC_Initialize_Array(&a_pValue->NoOfRemoveDiagnosticInfos, (void**) &a_pValue->RemoveDiagnosticInfos,
                              sizeof(SOPC_DiagnosticInfo),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_DiagnosticInfo_InitializeAux);
    }
}

/*============================================================================
 * OpcUa_SetTriggeringResponse_Clear
 *===========================================================================*/
void OpcUa_SetTriggeringResponse_Clear(void* pValue)
{
    OpcUa_SetTriggeringResponse* a_pValue = (OpcUa_SetTriggeringResponse*) pValue;
    if (a_pValue != NULL)
    {
        OpcUa_ResponseHeader_Clear(&a_pValue->ResponseHeader);
        SOPC_Clear_Array(&a_pValue->NoOfAddResults, (void**) &a_pValue->AddResults, sizeof(SOPC_StatusCode),
                         (SOPC_EncodeableObject_PfnClear*) SOPC_StatusCode_ClearAux);
        SOPC_Clear_Array(&a_pValue->NoOfAddDiagnosticInfos, (void**) &a_pValue->AddDiagnosticInfos,
                         sizeof(SOPC_DiagnosticInfo), (SOPC_EncodeableObject_PfnClear*) SOPC_DiagnosticInfo_ClearAux);
        SOPC_Clear_Array(&a_pValue->NoOfRemoveResults, (void**) &a_pValue->RemoveResults, sizeof(SOPC_StatusCode),
                         (SOPC_EncodeableObject_PfnClear*) SOPC_StatusCode_ClearAux);
        SOPC_Clear_Array(&a_pValue->NoOfRemoveDiagnosticInfos, (void**) &a_pValue->RemoveDiagnosticInfos,
                         sizeof(SOPC_DiagnosticInfo), (SOPC_EncodeableObject_PfnClear*) SOPC_DiagnosticInfo_ClearAux);
    }
}

/*============================================================================
 * OpcUa_SetTriggeringResponse_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_SetTriggeringResponse_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_SetTriggeringResponse* a_pValue = (const OpcUa_SetTriggeringResponse*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->AddResults;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfAddResults, &arr, sizeof(SOPC_StatusCode),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_StatusCode_WriteAux);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->AddDiagnosticInfos;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfAddDiagnosticInfos, &arr, sizeof(SOPC_DiagnosticInfo),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_DiagnosticInfo_WriteAux);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->RemoveResults;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfRemoveResults, &arr, sizeof(SOPC_StatusCode),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_StatusCode_WriteAux);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->RemoveDiagnosticInfos;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfRemoveDiagnosticInfos, &arr, sizeof(SOPC_DiagnosticInfo),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_DiagnosticInfo_WriteAux);
    }

    return status;
}

/*============================================================================
 * OpcUa_SetTriggeringResponse_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_SetTriggeringResponse_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_SetTriggeringResponse* a_pValue = (OpcUa_SetTriggeringResponse*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_SetTriggeringResponse_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfAddResults, (void**) &a_pValue->AddResults,
                                 sizeof(SOPC_StatusCode), (SOPC_EncodeableObject_PfnDecode*) SOPC_StatusCode_ReadAux,
                                 (SOPC_EncodeableObject_PfnInitialize*) SOPC_StatusCode_InitializeAux,
                                 (SOPC_EncodeableObject_PfnClear*) SOPC_StatusCode_ClearAux);
    }
    if (SOPC_STATUS_OK == status)
    {
        status =
            SOPC_Read_Array(buf, &a_pValue->NoOfAddDiagnosticInfos, (void**) &a_pValue->AddDiagnosticInfos,
                            sizeof(SOPC_DiagnosticInfo), (SOPC_EncodeableObject_PfnDecode*) SOPC_DiagnosticInfo_ReadAux,
                            (SOPC_EncodeableObject_PfnInitialize*) SOPC_DiagnosticInfo_InitializeAux,
                            (SOPC_EncodeableObject_PfnClear*) SOPC_DiagnosticInfo_ClearAux);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfRemoveResults, (void**) &a_pValue->RemoveResults,
                                 sizeof(SOPC_StatusCode), (SOPC_EncodeableObject_PfnDecode*) SOPC_StatusCode_ReadAux,
                                 (SOPC_EncodeableObject_PfnInitialize*) SOPC_StatusCode_InitializeAux,
                                 (SOPC_EncodeableObject_PfnClear*) SOPC_StatusCode_ClearAux);
    }
    if (SOPC_STATUS_OK == status)
    {
        status =
            SOPC_Read_Array(buf, &a_pValue->NoOfRemoveDiagnosticInfos, (void**) &a_pValue->RemoveDiagnosticInfos,
                            sizeof(SOPC_DiagnosticInfo), (SOPC_EncodeableObject_PfnDecode*) SOPC_DiagnosticInfo_ReadAux,
                            (SOPC_EncodeableObject_PfnInitialize*) SOPC_DiagnosticInfo_InitializeAux,
                            (SOPC_EncodeableObject_PfnClear*) SOPC_DiagnosticInfo_ClearAux);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_SetTriggeringResponse_Clear(a_pValue);
    }

    return status;
}
#endif
#endif

#ifndef OPCUA_EXCLUDE_DeleteMonitoredItems
#ifndef OPCUA_EXCLUDE_DeleteMonitoredItemsRequest
/*============================================================================
 * OpcUa_DeleteMonitoredItemsRequest_Initialize
 *===========================================================================*/
void OpcUa_DeleteMonitoredItemsRequest_Initialize(void* pValue)
{
    OpcUa_DeleteMonitoredItemsRequest* a_pValue = (OpcUa_DeleteMonitoredItemsRequest*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_DeleteMonitoredItemsRequest_EncodeableType;
        SOPC_UInt32_Initialize(&a_pValue->SubscriptionId);
        SOPC_Initialize_Array(&a_pValue->NoOfMonitoredItemIds, (void**) &a_pValue->MonitoredItemIds, sizeof(uint32_t),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_UInt32_InitializeAux);
    }
}

/*============================================================================
 * OpcUa_DeleteMonitoredItemsRequest_Clear
 *===========================================================================*/
void OpcUa_DeleteMonitoredItemsRequest_Clear(void* pValue)
{
    OpcUa_DeleteMonitoredItemsRequest* a_pValue = (OpcUa_DeleteMonitoredItemsRequest*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_UInt32_Clear(&a_pValue->SubscriptionId);
        SOPC_Clear_Array(&a_pValue->NoOfMonitoredItemIds, (void**) &a_pValue->MonitoredItemIds, sizeof(uint32_t),
                         (SOPC_EncodeableObject_PfnClear*) SOPC_UInt32_ClearAux);
    }
}

/*============================================================================
 * OpcUa_DeleteMonitoredItemsRequest_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_DeleteMonitoredItemsRequest_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_DeleteMonitoredItemsRequest* a_pValue = (const OpcUa_DeleteMonitoredItemsRequest*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->SubscriptionId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->MonitoredItemIds;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfMonitoredItemIds, &arr, sizeof(uint32_t),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_UInt32_WriteAux);
    }

    return status;
}

/*============================================================================
 * OpcUa_DeleteMonitoredItemsRequest_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_DeleteMonitoredItemsRequest_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_DeleteMonitoredItemsRequest* a_pValue = (OpcUa_DeleteMonitoredItemsRequest*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_DeleteMonitoredItemsRequest_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->SubscriptionId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfMonitoredItemIds, (void**) &a_pValue->MonitoredItemIds,
                                 sizeof(uint32_t), (SOPC_EncodeableObject_PfnDecode*) SOPC_UInt32_ReadAux,
                                 (SOPC_EncodeableObject_PfnInitialize*) SOPC_UInt32_InitializeAux,
                                 (SOPC_EncodeableObject_PfnClear*) SOPC_UInt32_ClearAux);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_DeleteMonitoredItemsRequest_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_DeleteMonitoredItemsResponse
/*============================================================================
 * OpcUa_DeleteMonitoredItemsResponse_Initialize
 *===========================================================================*/
void OpcUa_DeleteMonitoredItemsResponse_Initialize(void* pValue)
{
    OpcUa_DeleteMonitoredItemsResponse* a_pValue = (OpcUa_DeleteMonitoredItemsResponse*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_DeleteMonitoredItemsResponse_EncodeableType;
        OpcUa_ResponseHeader_Initialize(&a_pValue->ResponseHeader);
        SOPC_Initialize_Array(&a_pValue->NoOfResults, (void**) &a_pValue->Results, sizeof(SOPC_StatusCode),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_StatusCode_InitializeAux);
        SOPC_Initialize_Array(&a_pValue->NoOfDiagnosticInfos, (void**) &a_pValue->DiagnosticInfos,
                              sizeof(SOPC_DiagnosticInfo),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_DiagnosticInfo_InitializeAux);
    }
}

/*============================================================================
 * OpcUa_DeleteMonitoredItemsResponse_Clear
 *===========================================================================*/
void OpcUa_DeleteMonitoredItemsResponse_Clear(void* pValue)
{
    OpcUa_DeleteMonitoredItemsResponse* a_pValue = (OpcUa_DeleteMonitoredItemsResponse*) pValue;
    if (a_pValue != NULL)
    {
        OpcUa_ResponseHeader_Clear(&a_pValue->ResponseHeader);
        SOPC_Clear_Array(&a_pValue->NoOfResults, (void**) &a_pValue->Results, sizeof(SOPC_StatusCode),
                         (SOPC_EncodeableObject_PfnClear*) SOPC_StatusCode_ClearAux);
        SOPC_Clear_Array(&a_pValue->NoOfDiagnosticInfos, (void**) &a_pValue->DiagnosticInfos,
                         sizeof(SOPC_DiagnosticInfo), (SOPC_EncodeableObject_PfnClear*) SOPC_DiagnosticInfo_ClearAux);
    }
}

/*============================================================================
 * OpcUa_DeleteMonitoredItemsResponse_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_DeleteMonitoredItemsResponse_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_DeleteMonitoredItemsResponse* a_pValue = (const OpcUa_DeleteMonitoredItemsResponse*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->Results;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfResults, &arr, sizeof(SOPC_StatusCode),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_StatusCode_WriteAux);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->DiagnosticInfos;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfDiagnosticInfos, &arr, sizeof(SOPC_DiagnosticInfo),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_DiagnosticInfo_WriteAux);
    }

    return status;
}

/*============================================================================
 * OpcUa_DeleteMonitoredItemsResponse_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_DeleteMonitoredItemsResponse_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_DeleteMonitoredItemsResponse* a_pValue = (OpcUa_DeleteMonitoredItemsResponse*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_DeleteMonitoredItemsResponse_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfResults, (void**) &a_pValue->Results, sizeof(SOPC_StatusCode),
                                 (SOPC_EncodeableObject_PfnDecode*) SOPC_StatusCode_ReadAux,
                                 (SOPC_EncodeableObject_PfnInitialize*) SOPC_StatusCode_InitializeAux,
                                 (SOPC_EncodeableObject_PfnClear*) SOPC_StatusCode_ClearAux);
    }
    if (SOPC_STATUS_OK == status)
    {
        status =
            SOPC_Read_Array(buf, &a_pValue->NoOfDiagnosticInfos, (void**) &a_pValue->DiagnosticInfos,
                            sizeof(SOPC_DiagnosticInfo), (SOPC_EncodeableObject_PfnDecode*) SOPC_DiagnosticInfo_ReadAux,
                            (SOPC_EncodeableObject_PfnInitialize*) SOPC_DiagnosticInfo_InitializeAux,
                            (SOPC_EncodeableObject_PfnClear*) SOPC_DiagnosticInfo_ClearAux);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_DeleteMonitoredItemsResponse_Clear(a_pValue);
    }

    return status;
}
#endif
#endif

#ifndef OPCUA_EXCLUDE_CreateSubscription
#ifndef OPCUA_EXCLUDE_CreateSubscriptionRequest
/*============================================================================
 * OpcUa_CreateSubscriptionRequest_Initialize
 *===========================================================================*/
void OpcUa_CreateSubscriptionRequest_Initialize(void* pValue)
{
    OpcUa_CreateSubscriptionRequest* a_pValue = (OpcUa_CreateSubscriptionRequest*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_CreateSubscriptionRequest_EncodeableType;
        SOPC_Double_Initialize(&a_pValue->RequestedPublishingInterval);
        SOPC_UInt32_Initialize(&a_pValue->RequestedLifetimeCount);
        SOPC_UInt32_Initialize(&a_pValue->RequestedMaxKeepAliveCount);
        SOPC_UInt32_Initialize(&a_pValue->MaxNotificationsPerPublish);
        SOPC_Boolean_Initialize(&a_pValue->PublishingEnabled);
        SOPC_Byte_Initialize(&a_pValue->Priority);
    }
}

/*============================================================================
 * OpcUa_CreateSubscriptionRequest_Clear
 *===========================================================================*/
void OpcUa_CreateSubscriptionRequest_Clear(void* pValue)
{
    OpcUa_CreateSubscriptionRequest* a_pValue = (OpcUa_CreateSubscriptionRequest*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_Double_Clear(&a_pValue->RequestedPublishingInterval);
        SOPC_UInt32_Clear(&a_pValue->RequestedLifetimeCount);
        SOPC_UInt32_Clear(&a_pValue->RequestedMaxKeepAliveCount);
        SOPC_UInt32_Clear(&a_pValue->MaxNotificationsPerPublish);
        SOPC_Boolean_Clear(&a_pValue->PublishingEnabled);
        SOPC_Byte_Clear(&a_pValue->Priority);
    }
}

/*============================================================================
 * OpcUa_CreateSubscriptionRequest_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_CreateSubscriptionRequest_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_CreateSubscriptionRequest* a_pValue = (const OpcUa_CreateSubscriptionRequest*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Double_Write(&a_pValue->RequestedPublishingInterval, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->RequestedLifetimeCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->RequestedMaxKeepAliveCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->MaxNotificationsPerPublish, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Write(&a_pValue->PublishingEnabled, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Byte_Write(&a_pValue->Priority, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_CreateSubscriptionRequest_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_CreateSubscriptionRequest_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_CreateSubscriptionRequest* a_pValue = (OpcUa_CreateSubscriptionRequest*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_CreateSubscriptionRequest_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Double_Read(&a_pValue->RequestedPublishingInterval, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->RequestedLifetimeCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->RequestedMaxKeepAliveCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->MaxNotificationsPerPublish, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Read(&a_pValue->PublishingEnabled, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Byte_Read(&a_pValue->Priority, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_CreateSubscriptionRequest_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_CreateSubscriptionResponse
/*============================================================================
 * OpcUa_CreateSubscriptionResponse_Initialize
 *===========================================================================*/
void OpcUa_CreateSubscriptionResponse_Initialize(void* pValue)
{
    OpcUa_CreateSubscriptionResponse* a_pValue = (OpcUa_CreateSubscriptionResponse*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_CreateSubscriptionResponse_EncodeableType;
        OpcUa_ResponseHeader_Initialize(&a_pValue->ResponseHeader);
        SOPC_UInt32_Initialize(&a_pValue->SubscriptionId);
        SOPC_Double_Initialize(&a_pValue->RevisedPublishingInterval);
        SOPC_UInt32_Initialize(&a_pValue->RevisedLifetimeCount);
        SOPC_UInt32_Initialize(&a_pValue->RevisedMaxKeepAliveCount);
    }
}

/*============================================================================
 * OpcUa_CreateSubscriptionResponse_Clear
 *===========================================================================*/
void OpcUa_CreateSubscriptionResponse_Clear(void* pValue)
{
    OpcUa_CreateSubscriptionResponse* a_pValue = (OpcUa_CreateSubscriptionResponse*) pValue;
    if (a_pValue != NULL)
    {
        OpcUa_ResponseHeader_Clear(&a_pValue->ResponseHeader);
        SOPC_UInt32_Clear(&a_pValue->SubscriptionId);
        SOPC_Double_Clear(&a_pValue->RevisedPublishingInterval);
        SOPC_UInt32_Clear(&a_pValue->RevisedLifetimeCount);
        SOPC_UInt32_Clear(&a_pValue->RevisedMaxKeepAliveCount);
    }
}

/*============================================================================
 * OpcUa_CreateSubscriptionResponse_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_CreateSubscriptionResponse_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_CreateSubscriptionResponse* a_pValue = (const OpcUa_CreateSubscriptionResponse*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->SubscriptionId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Double_Write(&a_pValue->RevisedPublishingInterval, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->RevisedLifetimeCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->RevisedMaxKeepAliveCount, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_CreateSubscriptionResponse_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_CreateSubscriptionResponse_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_CreateSubscriptionResponse* a_pValue = (OpcUa_CreateSubscriptionResponse*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_CreateSubscriptionResponse_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->SubscriptionId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Double_Read(&a_pValue->RevisedPublishingInterval, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->RevisedLifetimeCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->RevisedMaxKeepAliveCount, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_CreateSubscriptionResponse_Clear(a_pValue);
    }

    return status;
}
#endif
#endif

#ifndef OPCUA_EXCLUDE_ModifySubscription
#ifndef OPCUA_EXCLUDE_ModifySubscriptionRequest
/*============================================================================
 * OpcUa_ModifySubscriptionRequest_Initialize
 *===========================================================================*/
void OpcUa_ModifySubscriptionRequest_Initialize(void* pValue)
{
    OpcUa_ModifySubscriptionRequest* a_pValue = (OpcUa_ModifySubscriptionRequest*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_ModifySubscriptionRequest_EncodeableType;
        SOPC_UInt32_Initialize(&a_pValue->SubscriptionId);
        SOPC_Double_Initialize(&a_pValue->RequestedPublishingInterval);
        SOPC_UInt32_Initialize(&a_pValue->RequestedLifetimeCount);
        SOPC_UInt32_Initialize(&a_pValue->RequestedMaxKeepAliveCount);
        SOPC_UInt32_Initialize(&a_pValue->MaxNotificationsPerPublish);
        SOPC_Byte_Initialize(&a_pValue->Priority);
    }
}

/*============================================================================
 * OpcUa_ModifySubscriptionRequest_Clear
 *===========================================================================*/
void OpcUa_ModifySubscriptionRequest_Clear(void* pValue)
{
    OpcUa_ModifySubscriptionRequest* a_pValue = (OpcUa_ModifySubscriptionRequest*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_UInt32_Clear(&a_pValue->SubscriptionId);
        SOPC_Double_Clear(&a_pValue->RequestedPublishingInterval);
        SOPC_UInt32_Clear(&a_pValue->RequestedLifetimeCount);
        SOPC_UInt32_Clear(&a_pValue->RequestedMaxKeepAliveCount);
        SOPC_UInt32_Clear(&a_pValue->MaxNotificationsPerPublish);
        SOPC_Byte_Clear(&a_pValue->Priority);
    }
}

/*============================================================================
 * OpcUa_ModifySubscriptionRequest_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_ModifySubscriptionRequest_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_ModifySubscriptionRequest* a_pValue = (const OpcUa_ModifySubscriptionRequest*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->SubscriptionId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Double_Write(&a_pValue->RequestedPublishingInterval, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->RequestedLifetimeCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->RequestedMaxKeepAliveCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->MaxNotificationsPerPublish, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Byte_Write(&a_pValue->Priority, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_ModifySubscriptionRequest_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_ModifySubscriptionRequest_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_ModifySubscriptionRequest* a_pValue = (OpcUa_ModifySubscriptionRequest*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_ModifySubscriptionRequest_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->SubscriptionId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Double_Read(&a_pValue->RequestedPublishingInterval, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->RequestedLifetimeCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->RequestedMaxKeepAliveCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->MaxNotificationsPerPublish, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Byte_Read(&a_pValue->Priority, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_ModifySubscriptionRequest_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_ModifySubscriptionResponse
/*============================================================================
 * OpcUa_ModifySubscriptionResponse_Initialize
 *===========================================================================*/
void OpcUa_ModifySubscriptionResponse_Initialize(void* pValue)
{
    OpcUa_ModifySubscriptionResponse* a_pValue = (OpcUa_ModifySubscriptionResponse*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_ModifySubscriptionResponse_EncodeableType;
        OpcUa_ResponseHeader_Initialize(&a_pValue->ResponseHeader);
        SOPC_Double_Initialize(&a_pValue->RevisedPublishingInterval);
        SOPC_UInt32_Initialize(&a_pValue->RevisedLifetimeCount);
        SOPC_UInt32_Initialize(&a_pValue->RevisedMaxKeepAliveCount);
    }
}

/*============================================================================
 * OpcUa_ModifySubscriptionResponse_Clear
 *===========================================================================*/
void OpcUa_ModifySubscriptionResponse_Clear(void* pValue)
{
    OpcUa_ModifySubscriptionResponse* a_pValue = (OpcUa_ModifySubscriptionResponse*) pValue;
    if (a_pValue != NULL)
    {
        OpcUa_ResponseHeader_Clear(&a_pValue->ResponseHeader);
        SOPC_Double_Clear(&a_pValue->RevisedPublishingInterval);
        SOPC_UInt32_Clear(&a_pValue->RevisedLifetimeCount);
        SOPC_UInt32_Clear(&a_pValue->RevisedMaxKeepAliveCount);
    }
}

/*============================================================================
 * OpcUa_ModifySubscriptionResponse_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_ModifySubscriptionResponse_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_ModifySubscriptionResponse* a_pValue = (const OpcUa_ModifySubscriptionResponse*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Double_Write(&a_pValue->RevisedPublishingInterval, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->RevisedLifetimeCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->RevisedMaxKeepAliveCount, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_ModifySubscriptionResponse_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_ModifySubscriptionResponse_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_ModifySubscriptionResponse* a_pValue = (OpcUa_ModifySubscriptionResponse*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_ModifySubscriptionResponse_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Double_Read(&a_pValue->RevisedPublishingInterval, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->RevisedLifetimeCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->RevisedMaxKeepAliveCount, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_ModifySubscriptionResponse_Clear(a_pValue);
    }

    return status;
}
#endif
#endif

#ifndef OPCUA_EXCLUDE_SetPublishingMode
#ifndef OPCUA_EXCLUDE_SetPublishingModeRequest
/*============================================================================
 * OpcUa_SetPublishingModeRequest_Initialize
 *===========================================================================*/
void OpcUa_SetPublishingModeRequest_Initialize(void* pValue)
{
    OpcUa_SetPublishingModeRequest* a_pValue = (OpcUa_SetPublishingModeRequest*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_SetPublishingModeRequest_EncodeableType;
        SOPC_Boolean_Initialize(&a_pValue->PublishingEnabled);
        SOPC_Initialize_Array(&a_pValue->NoOfSubscriptionIds, (void**) &a_pValue->SubscriptionIds, sizeof(uint32_t),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_UInt32_InitializeAux);
    }
}

/*============================================================================
 * OpcUa_SetPublishingModeRequest_Clear
 *===========================================================================*/
void OpcUa_SetPublishingModeRequest_Clear(void* pValue)
{
    OpcUa_SetPublishingModeRequest* a_pValue = (OpcUa_SetPublishingModeRequest*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_Boolean_Clear(&a_pValue->PublishingEnabled);
        SOPC_Clear_Array(&a_pValue->NoOfSubscriptionIds, (void**) &a_pValue->SubscriptionIds, sizeof(uint32_t),
                         (SOPC_EncodeableObject_PfnClear*) SOPC_UInt32_ClearAux);
    }
}

/*============================================================================
 * OpcUa_SetPublishingModeRequest_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_SetPublishingModeRequest_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_SetPublishingModeRequest* a_pValue = (const OpcUa_SetPublishingModeRequest*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Write(&a_pValue->PublishingEnabled, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->SubscriptionIds;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfSubscriptionIds, &arr, sizeof(uint32_t),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_UInt32_WriteAux);
    }

    return status;
}

/*============================================================================
 * OpcUa_SetPublishingModeRequest_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_SetPublishingModeRequest_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_SetPublishingModeRequest* a_pValue = (OpcUa_SetPublishingModeRequest*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_SetPublishingModeRequest_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Read(&a_pValue->PublishingEnabled, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfSubscriptionIds, (void**) &a_pValue->SubscriptionIds,
                                 sizeof(uint32_t), (SOPC_EncodeableObject_PfnDecode*) SOPC_UInt32_ReadAux,
                                 (SOPC_EncodeableObject_PfnInitialize*) SOPC_UInt32_InitializeAux,
                                 (SOPC_EncodeableObject_PfnClear*) SOPC_UInt32_ClearAux);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_SetPublishingModeRequest_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_SetPublishingModeResponse
/*============================================================================
 * OpcUa_SetPublishingModeResponse_Initialize
 *===========================================================================*/
void OpcUa_SetPublishingModeResponse_Initialize(void* pValue)
{
    OpcUa_SetPublishingModeResponse* a_pValue = (OpcUa_SetPublishingModeResponse*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_SetPublishingModeResponse_EncodeableType;
        OpcUa_ResponseHeader_Initialize(&a_pValue->ResponseHeader);
        SOPC_Initialize_Array(&a_pValue->NoOfResults, (void**) &a_pValue->Results, sizeof(SOPC_StatusCode),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_StatusCode_InitializeAux);
        SOPC_Initialize_Array(&a_pValue->NoOfDiagnosticInfos, (void**) &a_pValue->DiagnosticInfos,
                              sizeof(SOPC_DiagnosticInfo),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_DiagnosticInfo_InitializeAux);
    }
}

/*============================================================================
 * OpcUa_SetPublishingModeResponse_Clear
 *===========================================================================*/
void OpcUa_SetPublishingModeResponse_Clear(void* pValue)
{
    OpcUa_SetPublishingModeResponse* a_pValue = (OpcUa_SetPublishingModeResponse*) pValue;
    if (a_pValue != NULL)
    {
        OpcUa_ResponseHeader_Clear(&a_pValue->ResponseHeader);
        SOPC_Clear_Array(&a_pValue->NoOfResults, (void**) &a_pValue->Results, sizeof(SOPC_StatusCode),
                         (SOPC_EncodeableObject_PfnClear*) SOPC_StatusCode_ClearAux);
        SOPC_Clear_Array(&a_pValue->NoOfDiagnosticInfos, (void**) &a_pValue->DiagnosticInfos,
                         sizeof(SOPC_DiagnosticInfo), (SOPC_EncodeableObject_PfnClear*) SOPC_DiagnosticInfo_ClearAux);
    }
}

/*============================================================================
 * OpcUa_SetPublishingModeResponse_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_SetPublishingModeResponse_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_SetPublishingModeResponse* a_pValue = (const OpcUa_SetPublishingModeResponse*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->Results;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfResults, &arr, sizeof(SOPC_StatusCode),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_StatusCode_WriteAux);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->DiagnosticInfos;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfDiagnosticInfos, &arr, sizeof(SOPC_DiagnosticInfo),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_DiagnosticInfo_WriteAux);
    }

    return status;
}

/*============================================================================
 * OpcUa_SetPublishingModeResponse_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_SetPublishingModeResponse_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_SetPublishingModeResponse* a_pValue = (OpcUa_SetPublishingModeResponse*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_SetPublishingModeResponse_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfResults, (void**) &a_pValue->Results, sizeof(SOPC_StatusCode),
                                 (SOPC_EncodeableObject_PfnDecode*) SOPC_StatusCode_ReadAux,
                                 (SOPC_EncodeableObject_PfnInitialize*) SOPC_StatusCode_InitializeAux,
                                 (SOPC_EncodeableObject_PfnClear*) SOPC_StatusCode_ClearAux);
    }
    if (SOPC_STATUS_OK == status)
    {
        status =
            SOPC_Read_Array(buf, &a_pValue->NoOfDiagnosticInfos, (void**) &a_pValue->DiagnosticInfos,
                            sizeof(SOPC_DiagnosticInfo), (SOPC_EncodeableObject_PfnDecode*) SOPC_DiagnosticInfo_ReadAux,
                            (SOPC_EncodeableObject_PfnInitialize*) SOPC_DiagnosticInfo_InitializeAux,
                            (SOPC_EncodeableObject_PfnClear*) SOPC_DiagnosticInfo_ClearAux);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_SetPublishingModeResponse_Clear(a_pValue);
    }

    return status;
}
#endif
#endif

#ifndef OPCUA_EXCLUDE_NotificationMessage
/*============================================================================
 * OpcUa_NotificationMessage_Initialize
 *===========================================================================*/
void OpcUa_NotificationMessage_Initialize(void* pValue)
{
    OpcUa_NotificationMessage* a_pValue = (OpcUa_NotificationMessage*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_NotificationMessage_EncodeableType;
        SOPC_UInt32_Initialize(&a_pValue->SequenceNumber);
        SOPC_DateTime_Initialize(&a_pValue->PublishTime);
        SOPC_Initialize_Array(&a_pValue->NoOfNotificationData, (void**) &a_pValue->NotificationData,
                              sizeof(SOPC_ExtensionObject),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_ExtensionObject_InitializeAux);
    }
}

/*============================================================================
 * OpcUa_NotificationMessage_Clear
 *===========================================================================*/
void OpcUa_NotificationMessage_Clear(void* pValue)
{
    OpcUa_NotificationMessage* a_pValue = (OpcUa_NotificationMessage*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_UInt32_Clear(&a_pValue->SequenceNumber);
        SOPC_DateTime_Clear(&a_pValue->PublishTime);
        SOPC_Clear_Array(&a_pValue->NoOfNotificationData, (void**) &a_pValue->NotificationData,
                         sizeof(SOPC_ExtensionObject), (SOPC_EncodeableObject_PfnClear*) SOPC_ExtensionObject_ClearAux);
    }
}

/*============================================================================
 * OpcUa_NotificationMessage_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_NotificationMessage_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_NotificationMessage* a_pValue = (const OpcUa_NotificationMessage*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->SequenceNumber, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_DateTime_Write(&a_pValue->PublishTime, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->NotificationData;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfNotificationData, &arr, sizeof(SOPC_ExtensionObject),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_ExtensionObject_WriteAux);
    }

    return status;
}

/*============================================================================
 * OpcUa_NotificationMessage_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_NotificationMessage_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_NotificationMessage* a_pValue = (OpcUa_NotificationMessage*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_NotificationMessage_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->SequenceNumber, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_DateTime_Read(&a_pValue->PublishTime, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfNotificationData, (void**) &a_pValue->NotificationData,
                                 sizeof(SOPC_ExtensionObject),
                                 (SOPC_EncodeableObject_PfnDecode*) SOPC_ExtensionObject_ReadAux,
                                 (SOPC_EncodeableObject_PfnInitialize*) SOPC_ExtensionObject_InitializeAux,
                                 (SOPC_EncodeableObject_PfnClear*) SOPC_ExtensionObject_ClearAux);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_NotificationMessage_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_DataChangeNotification
/*============================================================================
 * OpcUa_DataChangeNotification_Initialize
 *===========================================================================*/
void OpcUa_DataChangeNotification_Initialize(void* pValue)
{
    OpcUa_DataChangeNotification* a_pValue = (OpcUa_DataChangeNotification*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_DataChangeNotification_EncodeableType;
        SOPC_Initialize_Array(&a_pValue->NoOfMonitoredItems, (void**) &a_pValue->MonitoredItems,
                              sizeof(OpcUa_MonitoredItemNotification),
                              (SOPC_EncodeableObject_PfnInitialize*) OpcUa_MonitoredItemNotification_Initialize);
        SOPC_Initialize_Array(&a_pValue->NoOfDiagnosticInfos, (void**) &a_pValue->DiagnosticInfos,
                              sizeof(SOPC_DiagnosticInfo),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_DiagnosticInfo_InitializeAux);
    }
}

/*============================================================================
 * OpcUa_DataChangeNotification_Clear
 *===========================================================================*/
void OpcUa_DataChangeNotification_Clear(void* pValue)
{
    OpcUa_DataChangeNotification* a_pValue = (OpcUa_DataChangeNotification*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_Clear_Array(&a_pValue->NoOfMonitoredItems, (void**) &a_pValue->MonitoredItems,
                         sizeof(OpcUa_MonitoredItemNotification),
                         (SOPC_EncodeableObject_PfnClear*) OpcUa_MonitoredItemNotification_Clear);
        SOPC_Clear_Array(&a_pValue->NoOfDiagnosticInfos, (void**) &a_pValue->DiagnosticInfos,
                         sizeof(SOPC_DiagnosticInfo), (SOPC_EncodeableObject_PfnClear*) SOPC_DiagnosticInfo_ClearAux);
    }
}

/*============================================================================
 * OpcUa_DataChangeNotification_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_DataChangeNotification_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_DataChangeNotification* a_pValue = (const OpcUa_DataChangeNotification*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->MonitoredItems;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfMonitoredItems, &arr, sizeof(OpcUa_MonitoredItemNotification),
                                  (SOPC_EncodeableObject_PfnEncode*) OpcUa_MonitoredItemNotification_Encode);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->DiagnosticInfos;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfDiagnosticInfos, &arr, sizeof(SOPC_DiagnosticInfo),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_DiagnosticInfo_WriteAux);
    }

    return status;
}

/*============================================================================
 * OpcUa_DataChangeNotification_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_DataChangeNotification_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_DataChangeNotification* a_pValue = (OpcUa_DataChangeNotification*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_DataChangeNotification_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfMonitoredItems, (void**) &a_pValue->MonitoredItems,
                                 sizeof(OpcUa_MonitoredItemNotification),
                                 (SOPC_EncodeableObject_PfnDecode*) OpcUa_MonitoredItemNotification_Decode,
                                 (SOPC_EncodeableObject_PfnInitialize*) OpcUa_MonitoredItemNotification_Initialize,
                                 (SOPC_EncodeableObject_PfnClear*) OpcUa_MonitoredItemNotification_Clear);
    }
    if (SOPC_STATUS_OK == status)
    {
        status =
            SOPC_Read_Array(buf, &a_pValue->NoOfDiagnosticInfos, (void**) &a_pValue->DiagnosticInfos,
                            sizeof(SOPC_DiagnosticInfo), (SOPC_EncodeableObject_PfnDecode*) SOPC_DiagnosticInfo_ReadAux,
                            (SOPC_EncodeableObject_PfnInitialize*) SOPC_DiagnosticInfo_InitializeAux,
                            (SOPC_EncodeableObject_PfnClear*) SOPC_DiagnosticInfo_ClearAux);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_DataChangeNotification_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_MonitoredItemNotification
/*============================================================================
 * OpcUa_MonitoredItemNotification_Initialize
 *===========================================================================*/
void OpcUa_MonitoredItemNotification_Initialize(void* pValue)
{
    OpcUa_MonitoredItemNotification* a_pValue = (OpcUa_MonitoredItemNotification*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_MonitoredItemNotification_EncodeableType;
        SOPC_UInt32_Initialize(&a_pValue->ClientHandle);
        SOPC_DataValue_Initialize(&a_pValue->Value);
    }
}

/*============================================================================
 * OpcUa_MonitoredItemNotification_Clear
 *===========================================================================*/
void OpcUa_MonitoredItemNotification_Clear(void* pValue)
{
    OpcUa_MonitoredItemNotification* a_pValue = (OpcUa_MonitoredItemNotification*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_UInt32_Clear(&a_pValue->ClientHandle);
        SOPC_DataValue_Clear(&a_pValue->Value);
    }
}

/*============================================================================
 * OpcUa_MonitoredItemNotification_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_MonitoredItemNotification_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_MonitoredItemNotification* a_pValue = (const OpcUa_MonitoredItemNotification*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->ClientHandle, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_DataValue_Write(&a_pValue->Value, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_MonitoredItemNotification_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_MonitoredItemNotification_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_MonitoredItemNotification* a_pValue = (OpcUa_MonitoredItemNotification*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_MonitoredItemNotification_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->ClientHandle, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_DataValue_Read(&a_pValue->Value, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_MonitoredItemNotification_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_EventNotificationList
/*============================================================================
 * OpcUa_EventNotificationList_Initialize
 *===========================================================================*/
void OpcUa_EventNotificationList_Initialize(void* pValue)
{
    OpcUa_EventNotificationList* a_pValue = (OpcUa_EventNotificationList*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_EventNotificationList_EncodeableType;
        SOPC_Initialize_Array(&a_pValue->NoOfEvents, (void**) &a_pValue->Events, sizeof(OpcUa_EventFieldList),
                              (SOPC_EncodeableObject_PfnInitialize*) OpcUa_EventFieldList_Initialize);
    }
}

/*============================================================================
 * OpcUa_EventNotificationList_Clear
 *===========================================================================*/
void OpcUa_EventNotificationList_Clear(void* pValue)
{
    OpcUa_EventNotificationList* a_pValue = (OpcUa_EventNotificationList*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_Clear_Array(&a_pValue->NoOfEvents, (void**) &a_pValue->Events, sizeof(OpcUa_EventFieldList),
                         (SOPC_EncodeableObject_PfnClear*) OpcUa_EventFieldList_Clear);
    }
}

/*============================================================================
 * OpcUa_EventNotificationList_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_EventNotificationList_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_EventNotificationList* a_pValue = (const OpcUa_EventNotificationList*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->Events;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfEvents, &arr, sizeof(OpcUa_EventFieldList),
                                  (SOPC_EncodeableObject_PfnEncode*) OpcUa_EventFieldList_Encode);
    }

    return status;
}

/*============================================================================
 * OpcUa_EventNotificationList_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_EventNotificationList_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_EventNotificationList* a_pValue = (OpcUa_EventNotificationList*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_EventNotificationList_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfEvents, (void**) &a_pValue->Events, sizeof(OpcUa_EventFieldList),
                                 (SOPC_EncodeableObject_PfnDecode*) OpcUa_EventFieldList_Decode,
                                 (SOPC_EncodeableObject_PfnInitialize*) OpcUa_EventFieldList_Initialize,
                                 (SOPC_EncodeableObject_PfnClear*) OpcUa_EventFieldList_Clear);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_EventNotificationList_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_EventFieldList
/*============================================================================
 * OpcUa_EventFieldList_Initialize
 *===========================================================================*/
void OpcUa_EventFieldList_Initialize(void* pValue)
{
    OpcUa_EventFieldList* a_pValue = (OpcUa_EventFieldList*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_EventFieldList_EncodeableType;
        SOPC_UInt32_Initialize(&a_pValue->ClientHandle);
        SOPC_Initialize_Array(&a_pValue->NoOfEventFields, (void**) &a_pValue->EventFields, sizeof(SOPC_Variant),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_Variant_InitializeAux);
    }
}

/*============================================================================
 * OpcUa_EventFieldList_Clear
 *===========================================================================*/
void OpcUa_EventFieldList_Clear(void* pValue)
{
    OpcUa_EventFieldList* a_pValue = (OpcUa_EventFieldList*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_UInt32_Clear(&a_pValue->ClientHandle);
        SOPC_Clear_Array(&a_pValue->NoOfEventFields, (void**) &a_pValue->EventFields, sizeof(SOPC_Variant),
                         (SOPC_EncodeableObject_PfnClear*) SOPC_Variant_ClearAux);
    }
}

/*============================================================================
 * OpcUa_EventFieldList_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_EventFieldList_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_EventFieldList* a_pValue = (const OpcUa_EventFieldList*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->ClientHandle, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->EventFields;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfEventFields, &arr, sizeof(SOPC_Variant),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_Variant_WriteAux);
    }

    return status;
}

/*============================================================================
 * OpcUa_EventFieldList_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_EventFieldList_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_EventFieldList* a_pValue = (OpcUa_EventFieldList*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_EventFieldList_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->ClientHandle, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfEventFields, (void**) &a_pValue->EventFields, sizeof(SOPC_Variant),
                                 (SOPC_EncodeableObject_PfnDecode*) SOPC_Variant_ReadAux,
                                 (SOPC_EncodeableObject_PfnInitialize*) SOPC_Variant_InitializeAux,
                                 (SOPC_EncodeableObject_PfnClear*) SOPC_Variant_ClearAux);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_EventFieldList_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_HistoryEventFieldList
/*============================================================================
 * OpcUa_HistoryEventFieldList_Initialize
 *===========================================================================*/
void OpcUa_HistoryEventFieldList_Initialize(void* pValue)
{
    OpcUa_HistoryEventFieldList* a_pValue = (OpcUa_HistoryEventFieldList*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_HistoryEventFieldList_EncodeableType;
        SOPC_Initialize_Array(&a_pValue->NoOfEventFields, (void**) &a_pValue->EventFields, sizeof(SOPC_Variant),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_Variant_InitializeAux);
    }
}

/*============================================================================
 * OpcUa_HistoryEventFieldList_Clear
 *===========================================================================*/
void OpcUa_HistoryEventFieldList_Clear(void* pValue)
{
    OpcUa_HistoryEventFieldList* a_pValue = (OpcUa_HistoryEventFieldList*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_Clear_Array(&a_pValue->NoOfEventFields, (void**) &a_pValue->EventFields, sizeof(SOPC_Variant),
                         (SOPC_EncodeableObject_PfnClear*) SOPC_Variant_ClearAux);
    }
}

/*============================================================================
 * OpcUa_HistoryEventFieldList_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_HistoryEventFieldList_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_HistoryEventFieldList* a_pValue = (const OpcUa_HistoryEventFieldList*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->EventFields;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfEventFields, &arr, sizeof(SOPC_Variant),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_Variant_WriteAux);
    }

    return status;
}

/*============================================================================
 * OpcUa_HistoryEventFieldList_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_HistoryEventFieldList_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_HistoryEventFieldList* a_pValue = (OpcUa_HistoryEventFieldList*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_HistoryEventFieldList_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfEventFields, (void**) &a_pValue->EventFields, sizeof(SOPC_Variant),
                                 (SOPC_EncodeableObject_PfnDecode*) SOPC_Variant_ReadAux,
                                 (SOPC_EncodeableObject_PfnInitialize*) SOPC_Variant_InitializeAux,
                                 (SOPC_EncodeableObject_PfnClear*) SOPC_Variant_ClearAux);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_HistoryEventFieldList_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_StatusChangeNotification
/*============================================================================
 * OpcUa_StatusChangeNotification_Initialize
 *===========================================================================*/
void OpcUa_StatusChangeNotification_Initialize(void* pValue)
{
    OpcUa_StatusChangeNotification* a_pValue = (OpcUa_StatusChangeNotification*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_StatusChangeNotification_EncodeableType;
        SOPC_StatusCode_Initialize(&a_pValue->Status);
        SOPC_DiagnosticInfo_Initialize(&a_pValue->DiagnosticInfo);
    }
}

/*============================================================================
 * OpcUa_StatusChangeNotification_Clear
 *===========================================================================*/
void OpcUa_StatusChangeNotification_Clear(void* pValue)
{
    OpcUa_StatusChangeNotification* a_pValue = (OpcUa_StatusChangeNotification*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_StatusCode_Clear(&a_pValue->Status);
        SOPC_DiagnosticInfo_Clear(&a_pValue->DiagnosticInfo);
    }
}

/*============================================================================
 * OpcUa_StatusChangeNotification_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_StatusChangeNotification_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_StatusChangeNotification* a_pValue = (const OpcUa_StatusChangeNotification*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_StatusCode_Write(&a_pValue->Status, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_DiagnosticInfo_Write(&a_pValue->DiagnosticInfo, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_StatusChangeNotification_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_StatusChangeNotification_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_StatusChangeNotification* a_pValue = (OpcUa_StatusChangeNotification*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_StatusChangeNotification_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_StatusCode_Read(&a_pValue->Status, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_DiagnosticInfo_Read(&a_pValue->DiagnosticInfo, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_StatusChangeNotification_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_SubscriptionAcknowledgement
/*============================================================================
 * OpcUa_SubscriptionAcknowledgement_Initialize
 *===========================================================================*/
void OpcUa_SubscriptionAcknowledgement_Initialize(void* pValue)
{
    OpcUa_SubscriptionAcknowledgement* a_pValue = (OpcUa_SubscriptionAcknowledgement*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_SubscriptionAcknowledgement_EncodeableType;
        SOPC_UInt32_Initialize(&a_pValue->SubscriptionId);
        SOPC_UInt32_Initialize(&a_pValue->SequenceNumber);
    }
}

/*============================================================================
 * OpcUa_SubscriptionAcknowledgement_Clear
 *===========================================================================*/
void OpcUa_SubscriptionAcknowledgement_Clear(void* pValue)
{
    OpcUa_SubscriptionAcknowledgement* a_pValue = (OpcUa_SubscriptionAcknowledgement*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_UInt32_Clear(&a_pValue->SubscriptionId);
        SOPC_UInt32_Clear(&a_pValue->SequenceNumber);
    }
}

/*============================================================================
 * OpcUa_SubscriptionAcknowledgement_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_SubscriptionAcknowledgement_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_SubscriptionAcknowledgement* a_pValue = (const OpcUa_SubscriptionAcknowledgement*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->SubscriptionId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->SequenceNumber, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_SubscriptionAcknowledgement_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_SubscriptionAcknowledgement_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_SubscriptionAcknowledgement* a_pValue = (OpcUa_SubscriptionAcknowledgement*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_SubscriptionAcknowledgement_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->SubscriptionId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->SequenceNumber, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_SubscriptionAcknowledgement_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_Publish
#ifndef OPCUA_EXCLUDE_PublishRequest
/*============================================================================
 * OpcUa_PublishRequest_Initialize
 *===========================================================================*/
void OpcUa_PublishRequest_Initialize(void* pValue)
{
    OpcUa_PublishRequest* a_pValue = (OpcUa_PublishRequest*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_PublishRequest_EncodeableType;
        SOPC_Initialize_Array(&a_pValue->NoOfSubscriptionAcknowledgements,
                              (void**) &a_pValue->SubscriptionAcknowledgements,
                              sizeof(OpcUa_SubscriptionAcknowledgement),
                              (SOPC_EncodeableObject_PfnInitialize*) OpcUa_SubscriptionAcknowledgement_Initialize);
    }
}

/*============================================================================
 * OpcUa_PublishRequest_Clear
 *===========================================================================*/
void OpcUa_PublishRequest_Clear(void* pValue)
{
    OpcUa_PublishRequest* a_pValue = (OpcUa_PublishRequest*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_Clear_Array(&a_pValue->NoOfSubscriptionAcknowledgements, (void**) &a_pValue->SubscriptionAcknowledgements,
                         sizeof(OpcUa_SubscriptionAcknowledgement),
                         (SOPC_EncodeableObject_PfnClear*) OpcUa_SubscriptionAcknowledgement_Clear);
    }
}

/*============================================================================
 * OpcUa_PublishRequest_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_PublishRequest_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_PublishRequest* a_pValue = (const OpcUa_PublishRequest*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->SubscriptionAcknowledgements;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfSubscriptionAcknowledgements, &arr,
                                  sizeof(OpcUa_SubscriptionAcknowledgement),
                                  (SOPC_EncodeableObject_PfnEncode*) OpcUa_SubscriptionAcknowledgement_Encode);
    }

    return status;
}

/*============================================================================
 * OpcUa_PublishRequest_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_PublishRequest_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_PublishRequest* a_pValue = (OpcUa_PublishRequest*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_PublishRequest_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status =
            SOPC_Read_Array(buf, &a_pValue->NoOfSubscriptionAcknowledgements,
                            (void**) &a_pValue->SubscriptionAcknowledgements, sizeof(OpcUa_SubscriptionAcknowledgement),
                            (SOPC_EncodeableObject_PfnDecode*) OpcUa_SubscriptionAcknowledgement_Decode,
                            (SOPC_EncodeableObject_PfnInitialize*) OpcUa_SubscriptionAcknowledgement_Initialize,
                            (SOPC_EncodeableObject_PfnClear*) OpcUa_SubscriptionAcknowledgement_Clear);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_PublishRequest_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_PublishResponse
/*============================================================================
 * OpcUa_PublishResponse_Initialize
 *===========================================================================*/
void OpcUa_PublishResponse_Initialize(void* pValue)
{
    OpcUa_PublishResponse* a_pValue = (OpcUa_PublishResponse*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_PublishResponse_EncodeableType;
        OpcUa_ResponseHeader_Initialize(&a_pValue->ResponseHeader);
        SOPC_UInt32_Initialize(&a_pValue->SubscriptionId);
        SOPC_Initialize_Array(&a_pValue->NoOfAvailableSequenceNumbers, (void**) &a_pValue->AvailableSequenceNumbers,
                              sizeof(uint32_t), (SOPC_EncodeableObject_PfnInitialize*) SOPC_UInt32_InitializeAux);
        SOPC_Boolean_Initialize(&a_pValue->MoreNotifications);
        OpcUa_NotificationMessage_Initialize(&a_pValue->NotificationMessage);
        SOPC_Initialize_Array(&a_pValue->NoOfResults, (void**) &a_pValue->Results, sizeof(SOPC_StatusCode),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_StatusCode_InitializeAux);
        SOPC_Initialize_Array(&a_pValue->NoOfDiagnosticInfos, (void**) &a_pValue->DiagnosticInfos,
                              sizeof(SOPC_DiagnosticInfo),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_DiagnosticInfo_InitializeAux);
    }
}

/*============================================================================
 * OpcUa_PublishResponse_Clear
 *===========================================================================*/
void OpcUa_PublishResponse_Clear(void* pValue)
{
    OpcUa_PublishResponse* a_pValue = (OpcUa_PublishResponse*) pValue;
    if (a_pValue != NULL)
    {
        OpcUa_ResponseHeader_Clear(&a_pValue->ResponseHeader);
        SOPC_UInt32_Clear(&a_pValue->SubscriptionId);
        SOPC_Clear_Array(&a_pValue->NoOfAvailableSequenceNumbers, (void**) &a_pValue->AvailableSequenceNumbers,
                         sizeof(uint32_t), (SOPC_EncodeableObject_PfnClear*) SOPC_UInt32_ClearAux);
        SOPC_Boolean_Clear(&a_pValue->MoreNotifications);
        OpcUa_NotificationMessage_Clear(&a_pValue->NotificationMessage);
        SOPC_Clear_Array(&a_pValue->NoOfResults, (void**) &a_pValue->Results, sizeof(SOPC_StatusCode),
                         (SOPC_EncodeableObject_PfnClear*) SOPC_StatusCode_ClearAux);
        SOPC_Clear_Array(&a_pValue->NoOfDiagnosticInfos, (void**) &a_pValue->DiagnosticInfos,
                         sizeof(SOPC_DiagnosticInfo), (SOPC_EncodeableObject_PfnClear*) SOPC_DiagnosticInfo_ClearAux);
    }
}

/*============================================================================
 * OpcUa_PublishResponse_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_PublishResponse_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_PublishResponse* a_pValue = (const OpcUa_PublishResponse*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->SubscriptionId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->AvailableSequenceNumbers;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfAvailableSequenceNumbers, &arr, sizeof(uint32_t),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_UInt32_WriteAux);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Write(&a_pValue->MoreNotifications, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_NotificationMessage_Encode(&a_pValue->NotificationMessage, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->Results;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfResults, &arr, sizeof(SOPC_StatusCode),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_StatusCode_WriteAux);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->DiagnosticInfos;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfDiagnosticInfos, &arr, sizeof(SOPC_DiagnosticInfo),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_DiagnosticInfo_WriteAux);
    }

    return status;
}

/*============================================================================
 * OpcUa_PublishResponse_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_PublishResponse_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_PublishResponse* a_pValue = (OpcUa_PublishResponse*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_PublishResponse_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->SubscriptionId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status =
            SOPC_Read_Array(buf, &a_pValue->NoOfAvailableSequenceNumbers, (void**) &a_pValue->AvailableSequenceNumbers,
                            sizeof(uint32_t), (SOPC_EncodeableObject_PfnDecode*) SOPC_UInt32_ReadAux,
                            (SOPC_EncodeableObject_PfnInitialize*) SOPC_UInt32_InitializeAux,
                            (SOPC_EncodeableObject_PfnClear*) SOPC_UInt32_ClearAux);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Read(&a_pValue->MoreNotifications, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_NotificationMessage_Decode(&a_pValue->NotificationMessage, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfResults, (void**) &a_pValue->Results, sizeof(SOPC_StatusCode),
                                 (SOPC_EncodeableObject_PfnDecode*) SOPC_StatusCode_ReadAux,
                                 (SOPC_EncodeableObject_PfnInitialize*) SOPC_StatusCode_InitializeAux,
                                 (SOPC_EncodeableObject_PfnClear*) SOPC_StatusCode_ClearAux);
    }
    if (SOPC_STATUS_OK == status)
    {
        status =
            SOPC_Read_Array(buf, &a_pValue->NoOfDiagnosticInfos, (void**) &a_pValue->DiagnosticInfos,
                            sizeof(SOPC_DiagnosticInfo), (SOPC_EncodeableObject_PfnDecode*) SOPC_DiagnosticInfo_ReadAux,
                            (SOPC_EncodeableObject_PfnInitialize*) SOPC_DiagnosticInfo_InitializeAux,
                            (SOPC_EncodeableObject_PfnClear*) SOPC_DiagnosticInfo_ClearAux);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_PublishResponse_Clear(a_pValue);
    }

    return status;
}
#endif
#endif

#ifndef OPCUA_EXCLUDE_Republish
#ifndef OPCUA_EXCLUDE_RepublishRequest
/*============================================================================
 * OpcUa_RepublishRequest_Initialize
 *===========================================================================*/
void OpcUa_RepublishRequest_Initialize(void* pValue)
{
    OpcUa_RepublishRequest* a_pValue = (OpcUa_RepublishRequest*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_RepublishRequest_EncodeableType;
        SOPC_UInt32_Initialize(&a_pValue->SubscriptionId);
        SOPC_UInt32_Initialize(&a_pValue->RetransmitSequenceNumber);
    }
}

/*============================================================================
 * OpcUa_RepublishRequest_Clear
 *===========================================================================*/
void OpcUa_RepublishRequest_Clear(void* pValue)
{
    OpcUa_RepublishRequest* a_pValue = (OpcUa_RepublishRequest*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_UInt32_Clear(&a_pValue->SubscriptionId);
        SOPC_UInt32_Clear(&a_pValue->RetransmitSequenceNumber);
    }
}

/*============================================================================
 * OpcUa_RepublishRequest_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_RepublishRequest_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_RepublishRequest* a_pValue = (const OpcUa_RepublishRequest*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->SubscriptionId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->RetransmitSequenceNumber, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_RepublishRequest_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_RepublishRequest_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_RepublishRequest* a_pValue = (OpcUa_RepublishRequest*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_RepublishRequest_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->SubscriptionId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->RetransmitSequenceNumber, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_RepublishRequest_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_RepublishResponse
/*============================================================================
 * OpcUa_RepublishResponse_Initialize
 *===========================================================================*/
void OpcUa_RepublishResponse_Initialize(void* pValue)
{
    OpcUa_RepublishResponse* a_pValue = (OpcUa_RepublishResponse*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_RepublishResponse_EncodeableType;
        OpcUa_ResponseHeader_Initialize(&a_pValue->ResponseHeader);
        OpcUa_NotificationMessage_Initialize(&a_pValue->NotificationMessage);
    }
}

/*============================================================================
 * OpcUa_RepublishResponse_Clear
 *===========================================================================*/
void OpcUa_RepublishResponse_Clear(void* pValue)
{
    OpcUa_RepublishResponse* a_pValue = (OpcUa_RepublishResponse*) pValue;
    if (a_pValue != NULL)
    {
        OpcUa_ResponseHeader_Clear(&a_pValue->ResponseHeader);
        OpcUa_NotificationMessage_Clear(&a_pValue->NotificationMessage);
    }
}

/*============================================================================
 * OpcUa_RepublishResponse_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_RepublishResponse_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_RepublishResponse* a_pValue = (const OpcUa_RepublishResponse*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_NotificationMessage_Encode(&a_pValue->NotificationMessage, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_RepublishResponse_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_RepublishResponse_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_RepublishResponse* a_pValue = (OpcUa_RepublishResponse*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_RepublishResponse_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_NotificationMessage_Decode(&a_pValue->NotificationMessage, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_RepublishResponse_Clear(a_pValue);
    }

    return status;
}
#endif
#endif

#ifndef OPCUA_EXCLUDE_TransferResult
/*============================================================================
 * OpcUa_TransferResult_Initialize
 *===========================================================================*/
void OpcUa_TransferResult_Initialize(void* pValue)
{
    OpcUa_TransferResult* a_pValue = (OpcUa_TransferResult*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_TransferResult_EncodeableType;
        SOPC_StatusCode_Initialize(&a_pValue->StatusCode);
        SOPC_Initialize_Array(&a_pValue->NoOfAvailableSequenceNumbers, (void**) &a_pValue->AvailableSequenceNumbers,
                              sizeof(uint32_t), (SOPC_EncodeableObject_PfnInitialize*) SOPC_UInt32_InitializeAux);
    }
}

/*============================================================================
 * OpcUa_TransferResult_Clear
 *===========================================================================*/
void OpcUa_TransferResult_Clear(void* pValue)
{
    OpcUa_TransferResult* a_pValue = (OpcUa_TransferResult*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_StatusCode_Clear(&a_pValue->StatusCode);
        SOPC_Clear_Array(&a_pValue->NoOfAvailableSequenceNumbers, (void**) &a_pValue->AvailableSequenceNumbers,
                         sizeof(uint32_t), (SOPC_EncodeableObject_PfnClear*) SOPC_UInt32_ClearAux);
    }
}

/*============================================================================
 * OpcUa_TransferResult_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_TransferResult_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_TransferResult* a_pValue = (const OpcUa_TransferResult*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_StatusCode_Write(&a_pValue->StatusCode, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->AvailableSequenceNumbers;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfAvailableSequenceNumbers, &arr, sizeof(uint32_t),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_UInt32_WriteAux);
    }

    return status;
}

/*============================================================================
 * OpcUa_TransferResult_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_TransferResult_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_TransferResult* a_pValue = (OpcUa_TransferResult*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_TransferResult_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_StatusCode_Read(&a_pValue->StatusCode, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status =
            SOPC_Read_Array(buf, &a_pValue->NoOfAvailableSequenceNumbers, (void**) &a_pValue->AvailableSequenceNumbers,
                            sizeof(uint32_t), (SOPC_EncodeableObject_PfnDecode*) SOPC_UInt32_ReadAux,
                            (SOPC_EncodeableObject_PfnInitialize*) SOPC_UInt32_InitializeAux,
                            (SOPC_EncodeableObject_PfnClear*) SOPC_UInt32_ClearAux);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_TransferResult_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_TransferSubscriptions
#ifndef OPCUA_EXCLUDE_TransferSubscriptionsRequest
/*============================================================================
 * OpcUa_TransferSubscriptionsRequest_Initialize
 *===========================================================================*/
void OpcUa_TransferSubscriptionsRequest_Initialize(void* pValue)
{
    OpcUa_TransferSubscriptionsRequest* a_pValue = (OpcUa_TransferSubscriptionsRequest*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_TransferSubscriptionsRequest_EncodeableType;
        SOPC_Initialize_Array(&a_pValue->NoOfSubscriptionIds, (void**) &a_pValue->SubscriptionIds, sizeof(uint32_t),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_UInt32_InitializeAux);
        SOPC_Boolean_Initialize(&a_pValue->SendInitialValues);
    }
}

/*============================================================================
 * OpcUa_TransferSubscriptionsRequest_Clear
 *===========================================================================*/
void OpcUa_TransferSubscriptionsRequest_Clear(void* pValue)
{
    OpcUa_TransferSubscriptionsRequest* a_pValue = (OpcUa_TransferSubscriptionsRequest*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_Clear_Array(&a_pValue->NoOfSubscriptionIds, (void**) &a_pValue->SubscriptionIds, sizeof(uint32_t),
                         (SOPC_EncodeableObject_PfnClear*) SOPC_UInt32_ClearAux);
        SOPC_Boolean_Clear(&a_pValue->SendInitialValues);
    }
}

/*============================================================================
 * OpcUa_TransferSubscriptionsRequest_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_TransferSubscriptionsRequest_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_TransferSubscriptionsRequest* a_pValue = (const OpcUa_TransferSubscriptionsRequest*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->SubscriptionIds;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfSubscriptionIds, &arr, sizeof(uint32_t),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_UInt32_WriteAux);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Write(&a_pValue->SendInitialValues, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_TransferSubscriptionsRequest_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_TransferSubscriptionsRequest_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_TransferSubscriptionsRequest* a_pValue = (OpcUa_TransferSubscriptionsRequest*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_TransferSubscriptionsRequest_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfSubscriptionIds, (void**) &a_pValue->SubscriptionIds,
                                 sizeof(uint32_t), (SOPC_EncodeableObject_PfnDecode*) SOPC_UInt32_ReadAux,
                                 (SOPC_EncodeableObject_PfnInitialize*) SOPC_UInt32_InitializeAux,
                                 (SOPC_EncodeableObject_PfnClear*) SOPC_UInt32_ClearAux);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Read(&a_pValue->SendInitialValues, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_TransferSubscriptionsRequest_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_TransferSubscriptionsResponse
/*============================================================================
 * OpcUa_TransferSubscriptionsResponse_Initialize
 *===========================================================================*/
void OpcUa_TransferSubscriptionsResponse_Initialize(void* pValue)
{
    OpcUa_TransferSubscriptionsResponse* a_pValue = (OpcUa_TransferSubscriptionsResponse*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_TransferSubscriptionsResponse_EncodeableType;
        OpcUa_ResponseHeader_Initialize(&a_pValue->ResponseHeader);
        SOPC_Initialize_Array(&a_pValue->NoOfResults, (void**) &a_pValue->Results, sizeof(OpcUa_TransferResult),
                              (SOPC_EncodeableObject_PfnInitialize*) OpcUa_TransferResult_Initialize);
        SOPC_Initialize_Array(&a_pValue->NoOfDiagnosticInfos, (void**) &a_pValue->DiagnosticInfos,
                              sizeof(SOPC_DiagnosticInfo),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_DiagnosticInfo_InitializeAux);
    }
}

/*============================================================================
 * OpcUa_TransferSubscriptionsResponse_Clear
 *===========================================================================*/
void OpcUa_TransferSubscriptionsResponse_Clear(void* pValue)
{
    OpcUa_TransferSubscriptionsResponse* a_pValue = (OpcUa_TransferSubscriptionsResponse*) pValue;
    if (a_pValue != NULL)
    {
        OpcUa_ResponseHeader_Clear(&a_pValue->ResponseHeader);
        SOPC_Clear_Array(&a_pValue->NoOfResults, (void**) &a_pValue->Results, sizeof(OpcUa_TransferResult),
                         (SOPC_EncodeableObject_PfnClear*) OpcUa_TransferResult_Clear);
        SOPC_Clear_Array(&a_pValue->NoOfDiagnosticInfos, (void**) &a_pValue->DiagnosticInfos,
                         sizeof(SOPC_DiagnosticInfo), (SOPC_EncodeableObject_PfnClear*) SOPC_DiagnosticInfo_ClearAux);
    }
}

/*============================================================================
 * OpcUa_TransferSubscriptionsResponse_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_TransferSubscriptionsResponse_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_TransferSubscriptionsResponse* a_pValue = (const OpcUa_TransferSubscriptionsResponse*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->Results;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfResults, &arr, sizeof(OpcUa_TransferResult),
                                  (SOPC_EncodeableObject_PfnEncode*) OpcUa_TransferResult_Encode);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->DiagnosticInfos;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfDiagnosticInfos, &arr, sizeof(SOPC_DiagnosticInfo),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_DiagnosticInfo_WriteAux);
    }

    return status;
}

/*============================================================================
 * OpcUa_TransferSubscriptionsResponse_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_TransferSubscriptionsResponse_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_TransferSubscriptionsResponse* a_pValue = (OpcUa_TransferSubscriptionsResponse*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_TransferSubscriptionsResponse_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfResults, (void**) &a_pValue->Results, sizeof(OpcUa_TransferResult),
                                 (SOPC_EncodeableObject_PfnDecode*) OpcUa_TransferResult_Decode,
                                 (SOPC_EncodeableObject_PfnInitialize*) OpcUa_TransferResult_Initialize,
                                 (SOPC_EncodeableObject_PfnClear*) OpcUa_TransferResult_Clear);
    }
    if (SOPC_STATUS_OK == status)
    {
        status =
            SOPC_Read_Array(buf, &a_pValue->NoOfDiagnosticInfos, (void**) &a_pValue->DiagnosticInfos,
                            sizeof(SOPC_DiagnosticInfo), (SOPC_EncodeableObject_PfnDecode*) SOPC_DiagnosticInfo_ReadAux,
                            (SOPC_EncodeableObject_PfnInitialize*) SOPC_DiagnosticInfo_InitializeAux,
                            (SOPC_EncodeableObject_PfnClear*) SOPC_DiagnosticInfo_ClearAux);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_TransferSubscriptionsResponse_Clear(a_pValue);
    }

    return status;
}
#endif
#endif

#ifndef OPCUA_EXCLUDE_DeleteSubscriptions
#ifndef OPCUA_EXCLUDE_DeleteSubscriptionsRequest
/*============================================================================
 * OpcUa_DeleteSubscriptionsRequest_Initialize
 *===========================================================================*/
void OpcUa_DeleteSubscriptionsRequest_Initialize(void* pValue)
{
    OpcUa_DeleteSubscriptionsRequest* a_pValue = (OpcUa_DeleteSubscriptionsRequest*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_DeleteSubscriptionsRequest_EncodeableType;
        SOPC_Initialize_Array(&a_pValue->NoOfSubscriptionIds, (void**) &a_pValue->SubscriptionIds, sizeof(uint32_t),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_UInt32_InitializeAux);
    }
}

/*============================================================================
 * OpcUa_DeleteSubscriptionsRequest_Clear
 *===========================================================================*/
void OpcUa_DeleteSubscriptionsRequest_Clear(void* pValue)
{
    OpcUa_DeleteSubscriptionsRequest* a_pValue = (OpcUa_DeleteSubscriptionsRequest*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_Clear_Array(&a_pValue->NoOfSubscriptionIds, (void**) &a_pValue->SubscriptionIds, sizeof(uint32_t),
                         (SOPC_EncodeableObject_PfnClear*) SOPC_UInt32_ClearAux);
    }
}

/*============================================================================
 * OpcUa_DeleteSubscriptionsRequest_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_DeleteSubscriptionsRequest_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_DeleteSubscriptionsRequest* a_pValue = (const OpcUa_DeleteSubscriptionsRequest*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->SubscriptionIds;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfSubscriptionIds, &arr, sizeof(uint32_t),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_UInt32_WriteAux);
    }

    return status;
}

/*============================================================================
 * OpcUa_DeleteSubscriptionsRequest_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_DeleteSubscriptionsRequest_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_DeleteSubscriptionsRequest* a_pValue = (OpcUa_DeleteSubscriptionsRequest*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_DeleteSubscriptionsRequest_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfSubscriptionIds, (void**) &a_pValue->SubscriptionIds,
                                 sizeof(uint32_t), (SOPC_EncodeableObject_PfnDecode*) SOPC_UInt32_ReadAux,
                                 (SOPC_EncodeableObject_PfnInitialize*) SOPC_UInt32_InitializeAux,
                                 (SOPC_EncodeableObject_PfnClear*) SOPC_UInt32_ClearAux);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_DeleteSubscriptionsRequest_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_DeleteSubscriptionsResponse
/*============================================================================
 * OpcUa_DeleteSubscriptionsResponse_Initialize
 *===========================================================================*/
void OpcUa_DeleteSubscriptionsResponse_Initialize(void* pValue)
{
    OpcUa_DeleteSubscriptionsResponse* a_pValue = (OpcUa_DeleteSubscriptionsResponse*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_DeleteSubscriptionsResponse_EncodeableType;
        OpcUa_ResponseHeader_Initialize(&a_pValue->ResponseHeader);
        SOPC_Initialize_Array(&a_pValue->NoOfResults, (void**) &a_pValue->Results, sizeof(SOPC_StatusCode),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_StatusCode_InitializeAux);
        SOPC_Initialize_Array(&a_pValue->NoOfDiagnosticInfos, (void**) &a_pValue->DiagnosticInfos,
                              sizeof(SOPC_DiagnosticInfo),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_DiagnosticInfo_InitializeAux);
    }
}

/*============================================================================
 * OpcUa_DeleteSubscriptionsResponse_Clear
 *===========================================================================*/
void OpcUa_DeleteSubscriptionsResponse_Clear(void* pValue)
{
    OpcUa_DeleteSubscriptionsResponse* a_pValue = (OpcUa_DeleteSubscriptionsResponse*) pValue;
    if (a_pValue != NULL)
    {
        OpcUa_ResponseHeader_Clear(&a_pValue->ResponseHeader);
        SOPC_Clear_Array(&a_pValue->NoOfResults, (void**) &a_pValue->Results, sizeof(SOPC_StatusCode),
                         (SOPC_EncodeableObject_PfnClear*) SOPC_StatusCode_ClearAux);
        SOPC_Clear_Array(&a_pValue->NoOfDiagnosticInfos, (void**) &a_pValue->DiagnosticInfos,
                         sizeof(SOPC_DiagnosticInfo), (SOPC_EncodeableObject_PfnClear*) SOPC_DiagnosticInfo_ClearAux);
    }
}

/*============================================================================
 * OpcUa_DeleteSubscriptionsResponse_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_DeleteSubscriptionsResponse_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_DeleteSubscriptionsResponse* a_pValue = (const OpcUa_DeleteSubscriptionsResponse*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->Results;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfResults, &arr, sizeof(SOPC_StatusCode),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_StatusCode_WriteAux);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->DiagnosticInfos;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfDiagnosticInfos, &arr, sizeof(SOPC_DiagnosticInfo),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_DiagnosticInfo_WriteAux);
    }

    return status;
}

/*============================================================================
 * OpcUa_DeleteSubscriptionsResponse_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_DeleteSubscriptionsResponse_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_DeleteSubscriptionsResponse* a_pValue = (OpcUa_DeleteSubscriptionsResponse*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_DeleteSubscriptionsResponse_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfResults, (void**) &a_pValue->Results, sizeof(SOPC_StatusCode),
                                 (SOPC_EncodeableObject_PfnDecode*) SOPC_StatusCode_ReadAux,
                                 (SOPC_EncodeableObject_PfnInitialize*) SOPC_StatusCode_InitializeAux,
                                 (SOPC_EncodeableObject_PfnClear*) SOPC_StatusCode_ClearAux);
    }
    if (SOPC_STATUS_OK == status)
    {
        status =
            SOPC_Read_Array(buf, &a_pValue->NoOfDiagnosticInfos, (void**) &a_pValue->DiagnosticInfos,
                            sizeof(SOPC_DiagnosticInfo), (SOPC_EncodeableObject_PfnDecode*) SOPC_DiagnosticInfo_ReadAux,
                            (SOPC_EncodeableObject_PfnInitialize*) SOPC_DiagnosticInfo_InitializeAux,
                            (SOPC_EncodeableObject_PfnClear*) SOPC_DiagnosticInfo_ClearAux);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_DeleteSubscriptionsResponse_Clear(a_pValue);
    }

    return status;
}
#endif
#endif

#ifndef OPCUA_EXCLUDE_BuildInfo
/*============================================================================
 * OpcUa_BuildInfo_Initialize
 *===========================================================================*/
void OpcUa_BuildInfo_Initialize(void* pValue)
{
    OpcUa_BuildInfo* a_pValue = (OpcUa_BuildInfo*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_BuildInfo_EncodeableType;
        SOPC_String_Initialize(&a_pValue->ProductUri);
        SOPC_String_Initialize(&a_pValue->ManufacturerName);
        SOPC_String_Initialize(&a_pValue->ProductName);
        SOPC_String_Initialize(&a_pValue->SoftwareVersion);
        SOPC_String_Initialize(&a_pValue->BuildNumber);
        SOPC_DateTime_Initialize(&a_pValue->BuildDate);
    }
}

/*============================================================================
 * OpcUa_BuildInfo_Clear
 *===========================================================================*/
void OpcUa_BuildInfo_Clear(void* pValue)
{
    OpcUa_BuildInfo* a_pValue = (OpcUa_BuildInfo*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_String_Clear(&a_pValue->ProductUri);
        SOPC_String_Clear(&a_pValue->ManufacturerName);
        SOPC_String_Clear(&a_pValue->ProductName);
        SOPC_String_Clear(&a_pValue->SoftwareVersion);
        SOPC_String_Clear(&a_pValue->BuildNumber);
        SOPC_DateTime_Clear(&a_pValue->BuildDate);
    }
}

/*============================================================================
 * OpcUa_BuildInfo_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_BuildInfo_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_BuildInfo* a_pValue = (const OpcUa_BuildInfo*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Write(&a_pValue->ProductUri, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Write(&a_pValue->ManufacturerName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Write(&a_pValue->ProductName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Write(&a_pValue->SoftwareVersion, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Write(&a_pValue->BuildNumber, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_DateTime_Write(&a_pValue->BuildDate, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_BuildInfo_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_BuildInfo_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_BuildInfo* a_pValue = (OpcUa_BuildInfo*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_BuildInfo_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Read(&a_pValue->ProductUri, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Read(&a_pValue->ManufacturerName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Read(&a_pValue->ProductName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Read(&a_pValue->SoftwareVersion, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Read(&a_pValue->BuildNumber, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_DateTime_Read(&a_pValue->BuildDate, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_BuildInfo_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_RedundantServerDataType
/*============================================================================
 * OpcUa_RedundantServerDataType_Initialize
 *===========================================================================*/
void OpcUa_RedundantServerDataType_Initialize(void* pValue)
{
    OpcUa_RedundantServerDataType* a_pValue = (OpcUa_RedundantServerDataType*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_RedundantServerDataType_EncodeableType;
        SOPC_String_Initialize(&a_pValue->ServerId);
        SOPC_Byte_Initialize(&a_pValue->ServiceLevel);
        SOPC_Initialize_EnumeratedType((int32_t*) &a_pValue->ServerState);
    }
}

/*============================================================================
 * OpcUa_RedundantServerDataType_Clear
 *===========================================================================*/
void OpcUa_RedundantServerDataType_Clear(void* pValue)
{
    OpcUa_RedundantServerDataType* a_pValue = (OpcUa_RedundantServerDataType*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_String_Clear(&a_pValue->ServerId);
        SOPC_Byte_Clear(&a_pValue->ServiceLevel);
        SOPC_Clear_EnumeratedType((int32_t*) &a_pValue->ServerState);
    }
}

/*============================================================================
 * OpcUa_RedundantServerDataType_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_RedundantServerDataType_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_RedundantServerDataType* a_pValue = (const OpcUa_RedundantServerDataType*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Write(&a_pValue->ServerId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Byte_Write(&a_pValue->ServiceLevel, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Write_EnumeratedType(buf, (const int32_t*) &a_pValue->ServerState);
    }

    return status;
}

/*============================================================================
 * OpcUa_RedundantServerDataType_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_RedundantServerDataType_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_RedundantServerDataType* a_pValue = (OpcUa_RedundantServerDataType*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_RedundantServerDataType_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Read(&a_pValue->ServerId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Byte_Read(&a_pValue->ServiceLevel, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_EnumeratedType(buf, (int32_t*) &a_pValue->ServerState);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_RedundantServerDataType_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_EndpointUrlListDataType
/*============================================================================
 * OpcUa_EndpointUrlListDataType_Initialize
 *===========================================================================*/
void OpcUa_EndpointUrlListDataType_Initialize(void* pValue)
{
    OpcUa_EndpointUrlListDataType* a_pValue = (OpcUa_EndpointUrlListDataType*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_EndpointUrlListDataType_EncodeableType;
        SOPC_Initialize_Array(&a_pValue->NoOfEndpointUrlList, (void**) &a_pValue->EndpointUrlList, sizeof(SOPC_String),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_String_InitializeAux);
    }
}

/*============================================================================
 * OpcUa_EndpointUrlListDataType_Clear
 *===========================================================================*/
void OpcUa_EndpointUrlListDataType_Clear(void* pValue)
{
    OpcUa_EndpointUrlListDataType* a_pValue = (OpcUa_EndpointUrlListDataType*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_Clear_Array(&a_pValue->NoOfEndpointUrlList, (void**) &a_pValue->EndpointUrlList, sizeof(SOPC_String),
                         (SOPC_EncodeableObject_PfnClear*) SOPC_String_ClearAux);
    }
}

/*============================================================================
 * OpcUa_EndpointUrlListDataType_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_EndpointUrlListDataType_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_EndpointUrlListDataType* a_pValue = (const OpcUa_EndpointUrlListDataType*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->EndpointUrlList;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfEndpointUrlList, &arr, sizeof(SOPC_String),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_String_WriteAux);
    }

    return status;
}

/*============================================================================
 * OpcUa_EndpointUrlListDataType_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_EndpointUrlListDataType_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_EndpointUrlListDataType* a_pValue = (OpcUa_EndpointUrlListDataType*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_EndpointUrlListDataType_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfEndpointUrlList, (void**) &a_pValue->EndpointUrlList,
                                 sizeof(SOPC_String), (SOPC_EncodeableObject_PfnDecode*) SOPC_String_ReadAux,
                                 (SOPC_EncodeableObject_PfnInitialize*) SOPC_String_InitializeAux,
                                 (SOPC_EncodeableObject_PfnClear*) SOPC_String_ClearAux);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_EndpointUrlListDataType_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_NetworkGroupDataType
/*============================================================================
 * OpcUa_NetworkGroupDataType_Initialize
 *===========================================================================*/
void OpcUa_NetworkGroupDataType_Initialize(void* pValue)
{
    OpcUa_NetworkGroupDataType* a_pValue = (OpcUa_NetworkGroupDataType*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_NetworkGroupDataType_EncodeableType;
        SOPC_String_Initialize(&a_pValue->ServerUri);
        SOPC_Initialize_Array(&a_pValue->NoOfNetworkPaths, (void**) &a_pValue->NetworkPaths,
                              sizeof(OpcUa_EndpointUrlListDataType),
                              (SOPC_EncodeableObject_PfnInitialize*) OpcUa_EndpointUrlListDataType_Initialize);
    }
}

/*============================================================================
 * OpcUa_NetworkGroupDataType_Clear
 *===========================================================================*/
void OpcUa_NetworkGroupDataType_Clear(void* pValue)
{
    OpcUa_NetworkGroupDataType* a_pValue = (OpcUa_NetworkGroupDataType*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_String_Clear(&a_pValue->ServerUri);
        SOPC_Clear_Array(&a_pValue->NoOfNetworkPaths, (void**) &a_pValue->NetworkPaths,
                         sizeof(OpcUa_EndpointUrlListDataType),
                         (SOPC_EncodeableObject_PfnClear*) OpcUa_EndpointUrlListDataType_Clear);
    }
}

/*============================================================================
 * OpcUa_NetworkGroupDataType_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_NetworkGroupDataType_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_NetworkGroupDataType* a_pValue = (const OpcUa_NetworkGroupDataType*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Write(&a_pValue->ServerUri, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->NetworkPaths;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfNetworkPaths, &arr, sizeof(OpcUa_EndpointUrlListDataType),
                                  (SOPC_EncodeableObject_PfnEncode*) OpcUa_EndpointUrlListDataType_Encode);
    }

    return status;
}

/*============================================================================
 * OpcUa_NetworkGroupDataType_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_NetworkGroupDataType_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_NetworkGroupDataType* a_pValue = (OpcUa_NetworkGroupDataType*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_NetworkGroupDataType_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Read(&a_pValue->ServerUri, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfNetworkPaths, (void**) &a_pValue->NetworkPaths,
                                 sizeof(OpcUa_EndpointUrlListDataType),
                                 (SOPC_EncodeableObject_PfnDecode*) OpcUa_EndpointUrlListDataType_Decode,
                                 (SOPC_EncodeableObject_PfnInitialize*) OpcUa_EndpointUrlListDataType_Initialize,
                                 (SOPC_EncodeableObject_PfnClear*) OpcUa_EndpointUrlListDataType_Clear);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_NetworkGroupDataType_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_SamplingIntervalDiagnosticsDataType
/*============================================================================
 * OpcUa_SamplingIntervalDiagnosticsDataType_Initialize
 *===========================================================================*/
void OpcUa_SamplingIntervalDiagnosticsDataType_Initialize(void* pValue)
{
    OpcUa_SamplingIntervalDiagnosticsDataType* a_pValue = (OpcUa_SamplingIntervalDiagnosticsDataType*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_SamplingIntervalDiagnosticsDataType_EncodeableType;
        SOPC_Double_Initialize(&a_pValue->SamplingInterval);
        SOPC_UInt32_Initialize(&a_pValue->MonitoredItemCount);
        SOPC_UInt32_Initialize(&a_pValue->MaxMonitoredItemCount);
        SOPC_UInt32_Initialize(&a_pValue->DisabledMonitoredItemCount);
    }
}

/*============================================================================
 * OpcUa_SamplingIntervalDiagnosticsDataType_Clear
 *===========================================================================*/
void OpcUa_SamplingIntervalDiagnosticsDataType_Clear(void* pValue)
{
    OpcUa_SamplingIntervalDiagnosticsDataType* a_pValue = (OpcUa_SamplingIntervalDiagnosticsDataType*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_Double_Clear(&a_pValue->SamplingInterval);
        SOPC_UInt32_Clear(&a_pValue->MonitoredItemCount);
        SOPC_UInt32_Clear(&a_pValue->MaxMonitoredItemCount);
        SOPC_UInt32_Clear(&a_pValue->DisabledMonitoredItemCount);
    }
}

/*============================================================================
 * OpcUa_SamplingIntervalDiagnosticsDataType_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_SamplingIntervalDiagnosticsDataType_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_SamplingIntervalDiagnosticsDataType* a_pValue =
        (const OpcUa_SamplingIntervalDiagnosticsDataType*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Double_Write(&a_pValue->SamplingInterval, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->MonitoredItemCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->MaxMonitoredItemCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->DisabledMonitoredItemCount, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_SamplingIntervalDiagnosticsDataType_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_SamplingIntervalDiagnosticsDataType_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_SamplingIntervalDiagnosticsDataType* a_pValue = (OpcUa_SamplingIntervalDiagnosticsDataType*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_SamplingIntervalDiagnosticsDataType_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Double_Read(&a_pValue->SamplingInterval, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->MonitoredItemCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->MaxMonitoredItemCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->DisabledMonitoredItemCount, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_SamplingIntervalDiagnosticsDataType_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_ServerDiagnosticsSummaryDataType
/*============================================================================
 * OpcUa_ServerDiagnosticsSummaryDataType_Initialize
 *===========================================================================*/
void OpcUa_ServerDiagnosticsSummaryDataType_Initialize(void* pValue)
{
    OpcUa_ServerDiagnosticsSummaryDataType* a_pValue = (OpcUa_ServerDiagnosticsSummaryDataType*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_ServerDiagnosticsSummaryDataType_EncodeableType;
        SOPC_UInt32_Initialize(&a_pValue->ServerViewCount);
        SOPC_UInt32_Initialize(&a_pValue->CurrentSessionCount);
        SOPC_UInt32_Initialize(&a_pValue->CumulatedSessionCount);
        SOPC_UInt32_Initialize(&a_pValue->SecurityRejectedSessionCount);
        SOPC_UInt32_Initialize(&a_pValue->RejectedSessionCount);
        SOPC_UInt32_Initialize(&a_pValue->SessionTimeoutCount);
        SOPC_UInt32_Initialize(&a_pValue->SessionAbortCount);
        SOPC_UInt32_Initialize(&a_pValue->CurrentSubscriptionCount);
        SOPC_UInt32_Initialize(&a_pValue->CumulatedSubscriptionCount);
        SOPC_UInt32_Initialize(&a_pValue->PublishingIntervalCount);
        SOPC_UInt32_Initialize(&a_pValue->SecurityRejectedRequestsCount);
        SOPC_UInt32_Initialize(&a_pValue->RejectedRequestsCount);
    }
}

/*============================================================================
 * OpcUa_ServerDiagnosticsSummaryDataType_Clear
 *===========================================================================*/
void OpcUa_ServerDiagnosticsSummaryDataType_Clear(void* pValue)
{
    OpcUa_ServerDiagnosticsSummaryDataType* a_pValue = (OpcUa_ServerDiagnosticsSummaryDataType*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_UInt32_Clear(&a_pValue->ServerViewCount);
        SOPC_UInt32_Clear(&a_pValue->CurrentSessionCount);
        SOPC_UInt32_Clear(&a_pValue->CumulatedSessionCount);
        SOPC_UInt32_Clear(&a_pValue->SecurityRejectedSessionCount);
        SOPC_UInt32_Clear(&a_pValue->RejectedSessionCount);
        SOPC_UInt32_Clear(&a_pValue->SessionTimeoutCount);
        SOPC_UInt32_Clear(&a_pValue->SessionAbortCount);
        SOPC_UInt32_Clear(&a_pValue->CurrentSubscriptionCount);
        SOPC_UInt32_Clear(&a_pValue->CumulatedSubscriptionCount);
        SOPC_UInt32_Clear(&a_pValue->PublishingIntervalCount);
        SOPC_UInt32_Clear(&a_pValue->SecurityRejectedRequestsCount);
        SOPC_UInt32_Clear(&a_pValue->RejectedRequestsCount);
    }
}

/*============================================================================
 * OpcUa_ServerDiagnosticsSummaryDataType_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_ServerDiagnosticsSummaryDataType_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_ServerDiagnosticsSummaryDataType* a_pValue = (const OpcUa_ServerDiagnosticsSummaryDataType*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->ServerViewCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->CurrentSessionCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->CumulatedSessionCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->SecurityRejectedSessionCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->RejectedSessionCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->SessionTimeoutCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->SessionAbortCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->CurrentSubscriptionCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->CumulatedSubscriptionCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->PublishingIntervalCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->SecurityRejectedRequestsCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->RejectedRequestsCount, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_ServerDiagnosticsSummaryDataType_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_ServerDiagnosticsSummaryDataType_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_ServerDiagnosticsSummaryDataType* a_pValue = (OpcUa_ServerDiagnosticsSummaryDataType*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_ServerDiagnosticsSummaryDataType_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->ServerViewCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->CurrentSessionCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->CumulatedSessionCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->SecurityRejectedSessionCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->RejectedSessionCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->SessionTimeoutCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->SessionAbortCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->CurrentSubscriptionCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->CumulatedSubscriptionCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->PublishingIntervalCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->SecurityRejectedRequestsCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->RejectedRequestsCount, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_ServerDiagnosticsSummaryDataType_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_ServerStatusDataType
/*============================================================================
 * OpcUa_ServerStatusDataType_Initialize
 *===========================================================================*/
void OpcUa_ServerStatusDataType_Initialize(void* pValue)
{
    OpcUa_ServerStatusDataType* a_pValue = (OpcUa_ServerStatusDataType*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_ServerStatusDataType_EncodeableType;
        SOPC_DateTime_Initialize(&a_pValue->StartTime);
        SOPC_DateTime_Initialize(&a_pValue->CurrentTime);
        SOPC_Initialize_EnumeratedType((int32_t*) &a_pValue->State);
        OpcUa_BuildInfo_Initialize(&a_pValue->BuildInfo);
        SOPC_UInt32_Initialize(&a_pValue->SecondsTillShutdown);
        SOPC_LocalizedText_Initialize(&a_pValue->ShutdownReason);
    }
}

/*============================================================================
 * OpcUa_ServerStatusDataType_Clear
 *===========================================================================*/
void OpcUa_ServerStatusDataType_Clear(void* pValue)
{
    OpcUa_ServerStatusDataType* a_pValue = (OpcUa_ServerStatusDataType*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_DateTime_Clear(&a_pValue->StartTime);
        SOPC_DateTime_Clear(&a_pValue->CurrentTime);
        SOPC_Clear_EnumeratedType((int32_t*) &a_pValue->State);
        OpcUa_BuildInfo_Clear(&a_pValue->BuildInfo);
        SOPC_UInt32_Clear(&a_pValue->SecondsTillShutdown);
        SOPC_LocalizedText_Clear(&a_pValue->ShutdownReason);
    }
}

/*============================================================================
 * OpcUa_ServerStatusDataType_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_ServerStatusDataType_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_ServerStatusDataType* a_pValue = (const OpcUa_ServerStatusDataType*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_DateTime_Write(&a_pValue->StartTime, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_DateTime_Write(&a_pValue->CurrentTime, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Write_EnumeratedType(buf, (const int32_t*) &a_pValue->State);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_BuildInfo_Encode(&a_pValue->BuildInfo, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->SecondsTillShutdown, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Write(&a_pValue->ShutdownReason, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_ServerStatusDataType_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_ServerStatusDataType_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_ServerStatusDataType* a_pValue = (OpcUa_ServerStatusDataType*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_ServerStatusDataType_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_DateTime_Read(&a_pValue->StartTime, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_DateTime_Read(&a_pValue->CurrentTime, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_EnumeratedType(buf, (int32_t*) &a_pValue->State);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_BuildInfo_Decode(&a_pValue->BuildInfo, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->SecondsTillShutdown, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Read(&a_pValue->ShutdownReason, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_ServerStatusDataType_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_SessionDiagnosticsDataType
/*============================================================================
 * OpcUa_SessionDiagnosticsDataType_Initialize
 *===========================================================================*/
void OpcUa_SessionDiagnosticsDataType_Initialize(void* pValue)
{
    OpcUa_SessionDiagnosticsDataType* a_pValue = (OpcUa_SessionDiagnosticsDataType*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_SessionDiagnosticsDataType_EncodeableType;
        SOPC_NodeId_Initialize(&a_pValue->SessionId);
        SOPC_String_Initialize(&a_pValue->SessionName);
        OpcUa_ApplicationDescription_Initialize(&a_pValue->ClientDescription);
        SOPC_String_Initialize(&a_pValue->ServerUri);
        SOPC_String_Initialize(&a_pValue->EndpointUrl);
        SOPC_Initialize_Array(&a_pValue->NoOfLocaleIds, (void**) &a_pValue->LocaleIds, sizeof(SOPC_String),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_String_InitializeAux);
        SOPC_Double_Initialize(&a_pValue->ActualSessionTimeout);
        SOPC_UInt32_Initialize(&a_pValue->MaxResponseMessageSize);
        SOPC_DateTime_Initialize(&a_pValue->ClientConnectionTime);
        SOPC_DateTime_Initialize(&a_pValue->ClientLastContactTime);
        SOPC_UInt32_Initialize(&a_pValue->CurrentSubscriptionsCount);
        SOPC_UInt32_Initialize(&a_pValue->CurrentMonitoredItemsCount);
        SOPC_UInt32_Initialize(&a_pValue->CurrentPublishRequestsInQueue);
        OpcUa_ServiceCounterDataType_Initialize(&a_pValue->TotalRequestCount);
        SOPC_UInt32_Initialize(&a_pValue->UnauthorizedRequestCount);
        OpcUa_ServiceCounterDataType_Initialize(&a_pValue->ReadCount);
        OpcUa_ServiceCounterDataType_Initialize(&a_pValue->HistoryReadCount);
        OpcUa_ServiceCounterDataType_Initialize(&a_pValue->WriteCount);
        OpcUa_ServiceCounterDataType_Initialize(&a_pValue->HistoryUpdateCount);
        OpcUa_ServiceCounterDataType_Initialize(&a_pValue->CallCount);
        OpcUa_ServiceCounterDataType_Initialize(&a_pValue->CreateMonitoredItemsCount);
        OpcUa_ServiceCounterDataType_Initialize(&a_pValue->ModifyMonitoredItemsCount);
        OpcUa_ServiceCounterDataType_Initialize(&a_pValue->SetMonitoringModeCount);
        OpcUa_ServiceCounterDataType_Initialize(&a_pValue->SetTriggeringCount);
        OpcUa_ServiceCounterDataType_Initialize(&a_pValue->DeleteMonitoredItemsCount);
        OpcUa_ServiceCounterDataType_Initialize(&a_pValue->CreateSubscriptionCount);
        OpcUa_ServiceCounterDataType_Initialize(&a_pValue->ModifySubscriptionCount);
        OpcUa_ServiceCounterDataType_Initialize(&a_pValue->SetPublishingModeCount);
        OpcUa_ServiceCounterDataType_Initialize(&a_pValue->PublishCount);
        OpcUa_ServiceCounterDataType_Initialize(&a_pValue->RepublishCount);
        OpcUa_ServiceCounterDataType_Initialize(&a_pValue->TransferSubscriptionsCount);
        OpcUa_ServiceCounterDataType_Initialize(&a_pValue->DeleteSubscriptionsCount);
        OpcUa_ServiceCounterDataType_Initialize(&a_pValue->AddNodesCount);
        OpcUa_ServiceCounterDataType_Initialize(&a_pValue->AddReferencesCount);
        OpcUa_ServiceCounterDataType_Initialize(&a_pValue->DeleteNodesCount);
        OpcUa_ServiceCounterDataType_Initialize(&a_pValue->DeleteReferencesCount);
        OpcUa_ServiceCounterDataType_Initialize(&a_pValue->BrowseCount);
        OpcUa_ServiceCounterDataType_Initialize(&a_pValue->BrowseNextCount);
        OpcUa_ServiceCounterDataType_Initialize(&a_pValue->TranslateBrowsePathsToNodeIdsCount);
        OpcUa_ServiceCounterDataType_Initialize(&a_pValue->QueryFirstCount);
        OpcUa_ServiceCounterDataType_Initialize(&a_pValue->QueryNextCount);
        OpcUa_ServiceCounterDataType_Initialize(&a_pValue->RegisterNodesCount);
        OpcUa_ServiceCounterDataType_Initialize(&a_pValue->UnregisterNodesCount);
    }
}

/*============================================================================
 * OpcUa_SessionDiagnosticsDataType_Clear
 *===========================================================================*/
void OpcUa_SessionDiagnosticsDataType_Clear(void* pValue)
{
    OpcUa_SessionDiagnosticsDataType* a_pValue = (OpcUa_SessionDiagnosticsDataType*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_NodeId_Clear(&a_pValue->SessionId);
        SOPC_String_Clear(&a_pValue->SessionName);
        OpcUa_ApplicationDescription_Clear(&a_pValue->ClientDescription);
        SOPC_String_Clear(&a_pValue->ServerUri);
        SOPC_String_Clear(&a_pValue->EndpointUrl);
        SOPC_Clear_Array(&a_pValue->NoOfLocaleIds, (void**) &a_pValue->LocaleIds, sizeof(SOPC_String),
                         (SOPC_EncodeableObject_PfnClear*) SOPC_String_ClearAux);
        SOPC_Double_Clear(&a_pValue->ActualSessionTimeout);
        SOPC_UInt32_Clear(&a_pValue->MaxResponseMessageSize);
        SOPC_DateTime_Clear(&a_pValue->ClientConnectionTime);
        SOPC_DateTime_Clear(&a_pValue->ClientLastContactTime);
        SOPC_UInt32_Clear(&a_pValue->CurrentSubscriptionsCount);
        SOPC_UInt32_Clear(&a_pValue->CurrentMonitoredItemsCount);
        SOPC_UInt32_Clear(&a_pValue->CurrentPublishRequestsInQueue);
        OpcUa_ServiceCounterDataType_Clear(&a_pValue->TotalRequestCount);
        SOPC_UInt32_Clear(&a_pValue->UnauthorizedRequestCount);
        OpcUa_ServiceCounterDataType_Clear(&a_pValue->ReadCount);
        OpcUa_ServiceCounterDataType_Clear(&a_pValue->HistoryReadCount);
        OpcUa_ServiceCounterDataType_Clear(&a_pValue->WriteCount);
        OpcUa_ServiceCounterDataType_Clear(&a_pValue->HistoryUpdateCount);
        OpcUa_ServiceCounterDataType_Clear(&a_pValue->CallCount);
        OpcUa_ServiceCounterDataType_Clear(&a_pValue->CreateMonitoredItemsCount);
        OpcUa_ServiceCounterDataType_Clear(&a_pValue->ModifyMonitoredItemsCount);
        OpcUa_ServiceCounterDataType_Clear(&a_pValue->SetMonitoringModeCount);
        OpcUa_ServiceCounterDataType_Clear(&a_pValue->SetTriggeringCount);
        OpcUa_ServiceCounterDataType_Clear(&a_pValue->DeleteMonitoredItemsCount);
        OpcUa_ServiceCounterDataType_Clear(&a_pValue->CreateSubscriptionCount);
        OpcUa_ServiceCounterDataType_Clear(&a_pValue->ModifySubscriptionCount);
        OpcUa_ServiceCounterDataType_Clear(&a_pValue->SetPublishingModeCount);
        OpcUa_ServiceCounterDataType_Clear(&a_pValue->PublishCount);
        OpcUa_ServiceCounterDataType_Clear(&a_pValue->RepublishCount);
        OpcUa_ServiceCounterDataType_Clear(&a_pValue->TransferSubscriptionsCount);
        OpcUa_ServiceCounterDataType_Clear(&a_pValue->DeleteSubscriptionsCount);
        OpcUa_ServiceCounterDataType_Clear(&a_pValue->AddNodesCount);
        OpcUa_ServiceCounterDataType_Clear(&a_pValue->AddReferencesCount);
        OpcUa_ServiceCounterDataType_Clear(&a_pValue->DeleteNodesCount);
        OpcUa_ServiceCounterDataType_Clear(&a_pValue->DeleteReferencesCount);
        OpcUa_ServiceCounterDataType_Clear(&a_pValue->BrowseCount);
        OpcUa_ServiceCounterDataType_Clear(&a_pValue->BrowseNextCount);
        OpcUa_ServiceCounterDataType_Clear(&a_pValue->TranslateBrowsePathsToNodeIdsCount);
        OpcUa_ServiceCounterDataType_Clear(&a_pValue->QueryFirstCount);
        OpcUa_ServiceCounterDataType_Clear(&a_pValue->QueryNextCount);
        OpcUa_ServiceCounterDataType_Clear(&a_pValue->RegisterNodesCount);
        OpcUa_ServiceCounterDataType_Clear(&a_pValue->UnregisterNodesCount);
    }
}

/*============================================================================
 * OpcUa_SessionDiagnosticsDataType_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_SessionDiagnosticsDataType_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_SessionDiagnosticsDataType* a_pValue = (const OpcUa_SessionDiagnosticsDataType*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Write(&a_pValue->SessionId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Write(&a_pValue->SessionName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_ApplicationDescription_Encode(&a_pValue->ClientDescription, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Write(&a_pValue->ServerUri, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Write(&a_pValue->EndpointUrl, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->LocaleIds;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfLocaleIds, &arr, sizeof(SOPC_String),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_String_WriteAux);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Double_Write(&a_pValue->ActualSessionTimeout, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->MaxResponseMessageSize, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_DateTime_Write(&a_pValue->ClientConnectionTime, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_DateTime_Write(&a_pValue->ClientLastContactTime, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->CurrentSubscriptionsCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->CurrentMonitoredItemsCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->CurrentPublishRequestsInQueue, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_ServiceCounterDataType_Encode(&a_pValue->TotalRequestCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->UnauthorizedRequestCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_ServiceCounterDataType_Encode(&a_pValue->ReadCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_ServiceCounterDataType_Encode(&a_pValue->HistoryReadCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_ServiceCounterDataType_Encode(&a_pValue->WriteCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_ServiceCounterDataType_Encode(&a_pValue->HistoryUpdateCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_ServiceCounterDataType_Encode(&a_pValue->CallCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_ServiceCounterDataType_Encode(&a_pValue->CreateMonitoredItemsCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_ServiceCounterDataType_Encode(&a_pValue->ModifyMonitoredItemsCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_ServiceCounterDataType_Encode(&a_pValue->SetMonitoringModeCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_ServiceCounterDataType_Encode(&a_pValue->SetTriggeringCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_ServiceCounterDataType_Encode(&a_pValue->DeleteMonitoredItemsCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_ServiceCounterDataType_Encode(&a_pValue->CreateSubscriptionCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_ServiceCounterDataType_Encode(&a_pValue->ModifySubscriptionCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_ServiceCounterDataType_Encode(&a_pValue->SetPublishingModeCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_ServiceCounterDataType_Encode(&a_pValue->PublishCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_ServiceCounterDataType_Encode(&a_pValue->RepublishCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_ServiceCounterDataType_Encode(&a_pValue->TransferSubscriptionsCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_ServiceCounterDataType_Encode(&a_pValue->DeleteSubscriptionsCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_ServiceCounterDataType_Encode(&a_pValue->AddNodesCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_ServiceCounterDataType_Encode(&a_pValue->AddReferencesCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_ServiceCounterDataType_Encode(&a_pValue->DeleteNodesCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_ServiceCounterDataType_Encode(&a_pValue->DeleteReferencesCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_ServiceCounterDataType_Encode(&a_pValue->BrowseCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_ServiceCounterDataType_Encode(&a_pValue->BrowseNextCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_ServiceCounterDataType_Encode(&a_pValue->TranslateBrowsePathsToNodeIdsCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_ServiceCounterDataType_Encode(&a_pValue->QueryFirstCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_ServiceCounterDataType_Encode(&a_pValue->QueryNextCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_ServiceCounterDataType_Encode(&a_pValue->RegisterNodesCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_ServiceCounterDataType_Encode(&a_pValue->UnregisterNodesCount, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_SessionDiagnosticsDataType_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_SessionDiagnosticsDataType_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_SessionDiagnosticsDataType* a_pValue = (OpcUa_SessionDiagnosticsDataType*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_SessionDiagnosticsDataType_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Read(&a_pValue->SessionId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Read(&a_pValue->SessionName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_ApplicationDescription_Decode(&a_pValue->ClientDescription, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Read(&a_pValue->ServerUri, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Read(&a_pValue->EndpointUrl, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfLocaleIds, (void**) &a_pValue->LocaleIds, sizeof(SOPC_String),
                                 (SOPC_EncodeableObject_PfnDecode*) SOPC_String_ReadAux,
                                 (SOPC_EncodeableObject_PfnInitialize*) SOPC_String_InitializeAux,
                                 (SOPC_EncodeableObject_PfnClear*) SOPC_String_ClearAux);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Double_Read(&a_pValue->ActualSessionTimeout, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->MaxResponseMessageSize, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_DateTime_Read(&a_pValue->ClientConnectionTime, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_DateTime_Read(&a_pValue->ClientLastContactTime, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->CurrentSubscriptionsCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->CurrentMonitoredItemsCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->CurrentPublishRequestsInQueue, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_ServiceCounterDataType_Decode(&a_pValue->TotalRequestCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->UnauthorizedRequestCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_ServiceCounterDataType_Decode(&a_pValue->ReadCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_ServiceCounterDataType_Decode(&a_pValue->HistoryReadCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_ServiceCounterDataType_Decode(&a_pValue->WriteCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_ServiceCounterDataType_Decode(&a_pValue->HistoryUpdateCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_ServiceCounterDataType_Decode(&a_pValue->CallCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_ServiceCounterDataType_Decode(&a_pValue->CreateMonitoredItemsCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_ServiceCounterDataType_Decode(&a_pValue->ModifyMonitoredItemsCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_ServiceCounterDataType_Decode(&a_pValue->SetMonitoringModeCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_ServiceCounterDataType_Decode(&a_pValue->SetTriggeringCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_ServiceCounterDataType_Decode(&a_pValue->DeleteMonitoredItemsCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_ServiceCounterDataType_Decode(&a_pValue->CreateSubscriptionCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_ServiceCounterDataType_Decode(&a_pValue->ModifySubscriptionCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_ServiceCounterDataType_Decode(&a_pValue->SetPublishingModeCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_ServiceCounterDataType_Decode(&a_pValue->PublishCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_ServiceCounterDataType_Decode(&a_pValue->RepublishCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_ServiceCounterDataType_Decode(&a_pValue->TransferSubscriptionsCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_ServiceCounterDataType_Decode(&a_pValue->DeleteSubscriptionsCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_ServiceCounterDataType_Decode(&a_pValue->AddNodesCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_ServiceCounterDataType_Decode(&a_pValue->AddReferencesCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_ServiceCounterDataType_Decode(&a_pValue->DeleteNodesCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_ServiceCounterDataType_Decode(&a_pValue->DeleteReferencesCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_ServiceCounterDataType_Decode(&a_pValue->BrowseCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_ServiceCounterDataType_Decode(&a_pValue->BrowseNextCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_ServiceCounterDataType_Decode(&a_pValue->TranslateBrowsePathsToNodeIdsCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_ServiceCounterDataType_Decode(&a_pValue->QueryFirstCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_ServiceCounterDataType_Decode(&a_pValue->QueryNextCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_ServiceCounterDataType_Decode(&a_pValue->RegisterNodesCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_ServiceCounterDataType_Decode(&a_pValue->UnregisterNodesCount, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_SessionDiagnosticsDataType_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_SessionSecurityDiagnosticsDataType
/*============================================================================
 * OpcUa_SessionSecurityDiagnosticsDataType_Initialize
 *===========================================================================*/
void OpcUa_SessionSecurityDiagnosticsDataType_Initialize(void* pValue)
{
    OpcUa_SessionSecurityDiagnosticsDataType* a_pValue = (OpcUa_SessionSecurityDiagnosticsDataType*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_SessionSecurityDiagnosticsDataType_EncodeableType;
        SOPC_NodeId_Initialize(&a_pValue->SessionId);
        SOPC_String_Initialize(&a_pValue->ClientUserIdOfSession);
        SOPC_Initialize_Array(&a_pValue->NoOfClientUserIdHistory, (void**) &a_pValue->ClientUserIdHistory,
                              sizeof(SOPC_String), (SOPC_EncodeableObject_PfnInitialize*) SOPC_String_InitializeAux);
        SOPC_String_Initialize(&a_pValue->AuthenticationMechanism);
        SOPC_String_Initialize(&a_pValue->Encoding);
        SOPC_String_Initialize(&a_pValue->TransportProtocol);
        SOPC_Initialize_EnumeratedType((int32_t*) &a_pValue->SecurityMode);
        SOPC_String_Initialize(&a_pValue->SecurityPolicyUri);
        SOPC_ByteString_Initialize(&a_pValue->ClientCertificate);
    }
}

/*============================================================================
 * OpcUa_SessionSecurityDiagnosticsDataType_Clear
 *===========================================================================*/
void OpcUa_SessionSecurityDiagnosticsDataType_Clear(void* pValue)
{
    OpcUa_SessionSecurityDiagnosticsDataType* a_pValue = (OpcUa_SessionSecurityDiagnosticsDataType*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_NodeId_Clear(&a_pValue->SessionId);
        SOPC_String_Clear(&a_pValue->ClientUserIdOfSession);
        SOPC_Clear_Array(&a_pValue->NoOfClientUserIdHistory, (void**) &a_pValue->ClientUserIdHistory,
                         sizeof(SOPC_String), (SOPC_EncodeableObject_PfnClear*) SOPC_String_ClearAux);
        SOPC_String_Clear(&a_pValue->AuthenticationMechanism);
        SOPC_String_Clear(&a_pValue->Encoding);
        SOPC_String_Clear(&a_pValue->TransportProtocol);
        SOPC_Clear_EnumeratedType((int32_t*) &a_pValue->SecurityMode);
        SOPC_String_Clear(&a_pValue->SecurityPolicyUri);
        SOPC_ByteString_Clear(&a_pValue->ClientCertificate);
    }
}

/*============================================================================
 * OpcUa_SessionSecurityDiagnosticsDataType_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_SessionSecurityDiagnosticsDataType_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_SessionSecurityDiagnosticsDataType* a_pValue = (const OpcUa_SessionSecurityDiagnosticsDataType*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Write(&a_pValue->SessionId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Write(&a_pValue->ClientUserIdOfSession, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->ClientUserIdHistory;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfClientUserIdHistory, &arr, sizeof(SOPC_String),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_String_WriteAux);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Write(&a_pValue->AuthenticationMechanism, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Write(&a_pValue->Encoding, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Write(&a_pValue->TransportProtocol, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Write_EnumeratedType(buf, (const int32_t*) &a_pValue->SecurityMode);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Write(&a_pValue->SecurityPolicyUri, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ByteString_Write(&a_pValue->ClientCertificate, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_SessionSecurityDiagnosticsDataType_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_SessionSecurityDiagnosticsDataType_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_SessionSecurityDiagnosticsDataType* a_pValue = (OpcUa_SessionSecurityDiagnosticsDataType*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_SessionSecurityDiagnosticsDataType_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Read(&a_pValue->SessionId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Read(&a_pValue->ClientUserIdOfSession, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfClientUserIdHistory, (void**) &a_pValue->ClientUserIdHistory,
                                 sizeof(SOPC_String), (SOPC_EncodeableObject_PfnDecode*) SOPC_String_ReadAux,
                                 (SOPC_EncodeableObject_PfnInitialize*) SOPC_String_InitializeAux,
                                 (SOPC_EncodeableObject_PfnClear*) SOPC_String_ClearAux);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Read(&a_pValue->AuthenticationMechanism, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Read(&a_pValue->Encoding, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Read(&a_pValue->TransportProtocol, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_EnumeratedType(buf, (int32_t*) &a_pValue->SecurityMode);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Read(&a_pValue->SecurityPolicyUri, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_ByteString_Read(&a_pValue->ClientCertificate, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_SessionSecurityDiagnosticsDataType_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_ServiceCounterDataType
/*============================================================================
 * OpcUa_ServiceCounterDataType_Initialize
 *===========================================================================*/
void OpcUa_ServiceCounterDataType_Initialize(void* pValue)
{
    OpcUa_ServiceCounterDataType* a_pValue = (OpcUa_ServiceCounterDataType*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_ServiceCounterDataType_EncodeableType;
        SOPC_UInt32_Initialize(&a_pValue->TotalCount);
        SOPC_UInt32_Initialize(&a_pValue->ErrorCount);
    }
}

/*============================================================================
 * OpcUa_ServiceCounterDataType_Clear
 *===========================================================================*/
void OpcUa_ServiceCounterDataType_Clear(void* pValue)
{
    OpcUa_ServiceCounterDataType* a_pValue = (OpcUa_ServiceCounterDataType*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_UInt32_Clear(&a_pValue->TotalCount);
        SOPC_UInt32_Clear(&a_pValue->ErrorCount);
    }
}

/*============================================================================
 * OpcUa_ServiceCounterDataType_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_ServiceCounterDataType_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_ServiceCounterDataType* a_pValue = (const OpcUa_ServiceCounterDataType*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->TotalCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->ErrorCount, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_ServiceCounterDataType_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_ServiceCounterDataType_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_ServiceCounterDataType* a_pValue = (OpcUa_ServiceCounterDataType*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_ServiceCounterDataType_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->TotalCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->ErrorCount, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_ServiceCounterDataType_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_StatusResult
/*============================================================================
 * OpcUa_StatusResult_Initialize
 *===========================================================================*/
void OpcUa_StatusResult_Initialize(void* pValue)
{
    OpcUa_StatusResult* a_pValue = (OpcUa_StatusResult*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_StatusResult_EncodeableType;
        SOPC_StatusCode_Initialize(&a_pValue->StatusCode);
        SOPC_DiagnosticInfo_Initialize(&a_pValue->DiagnosticInfo);
    }
}

/*============================================================================
 * OpcUa_StatusResult_Clear
 *===========================================================================*/
void OpcUa_StatusResult_Clear(void* pValue)
{
    OpcUa_StatusResult* a_pValue = (OpcUa_StatusResult*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_StatusCode_Clear(&a_pValue->StatusCode);
        SOPC_DiagnosticInfo_Clear(&a_pValue->DiagnosticInfo);
    }
}

/*============================================================================
 * OpcUa_StatusResult_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_StatusResult_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_StatusResult* a_pValue = (const OpcUa_StatusResult*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_StatusCode_Write(&a_pValue->StatusCode, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_DiagnosticInfo_Write(&a_pValue->DiagnosticInfo, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_StatusResult_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_StatusResult_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_StatusResult* a_pValue = (OpcUa_StatusResult*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_StatusResult_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_StatusCode_Read(&a_pValue->StatusCode, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_DiagnosticInfo_Read(&a_pValue->DiagnosticInfo, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_StatusResult_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_SubscriptionDiagnosticsDataType
/*============================================================================
 * OpcUa_SubscriptionDiagnosticsDataType_Initialize
 *===========================================================================*/
void OpcUa_SubscriptionDiagnosticsDataType_Initialize(void* pValue)
{
    OpcUa_SubscriptionDiagnosticsDataType* a_pValue = (OpcUa_SubscriptionDiagnosticsDataType*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_SubscriptionDiagnosticsDataType_EncodeableType;
        SOPC_NodeId_Initialize(&a_pValue->SessionId);
        SOPC_UInt32_Initialize(&a_pValue->SubscriptionId);
        SOPC_Byte_Initialize(&a_pValue->Priority);
        SOPC_Double_Initialize(&a_pValue->PublishingInterval);
        SOPC_UInt32_Initialize(&a_pValue->MaxKeepAliveCount);
        SOPC_UInt32_Initialize(&a_pValue->MaxLifetimeCount);
        SOPC_UInt32_Initialize(&a_pValue->MaxNotificationsPerPublish);
        SOPC_Boolean_Initialize(&a_pValue->PublishingEnabled);
        SOPC_UInt32_Initialize(&a_pValue->ModifyCount);
        SOPC_UInt32_Initialize(&a_pValue->EnableCount);
        SOPC_UInt32_Initialize(&a_pValue->DisableCount);
        SOPC_UInt32_Initialize(&a_pValue->RepublishRequestCount);
        SOPC_UInt32_Initialize(&a_pValue->RepublishMessageRequestCount);
        SOPC_UInt32_Initialize(&a_pValue->RepublishMessageCount);
        SOPC_UInt32_Initialize(&a_pValue->TransferRequestCount);
        SOPC_UInt32_Initialize(&a_pValue->TransferredToAltClientCount);
        SOPC_UInt32_Initialize(&a_pValue->TransferredToSameClientCount);
        SOPC_UInt32_Initialize(&a_pValue->PublishRequestCount);
        SOPC_UInt32_Initialize(&a_pValue->DataChangeNotificationsCount);
        SOPC_UInt32_Initialize(&a_pValue->EventNotificationsCount);
        SOPC_UInt32_Initialize(&a_pValue->NotificationsCount);
        SOPC_UInt32_Initialize(&a_pValue->LatePublishRequestCount);
        SOPC_UInt32_Initialize(&a_pValue->CurrentKeepAliveCount);
        SOPC_UInt32_Initialize(&a_pValue->CurrentLifetimeCount);
        SOPC_UInt32_Initialize(&a_pValue->UnacknowledgedMessageCount);
        SOPC_UInt32_Initialize(&a_pValue->DiscardedMessageCount);
        SOPC_UInt32_Initialize(&a_pValue->MonitoredItemCount);
        SOPC_UInt32_Initialize(&a_pValue->DisabledMonitoredItemCount);
        SOPC_UInt32_Initialize(&a_pValue->MonitoringQueueOverflowCount);
        SOPC_UInt32_Initialize(&a_pValue->NextSequenceNumber);
        SOPC_UInt32_Initialize(&a_pValue->EventQueueOverFlowCount);
    }
}

/*============================================================================
 * OpcUa_SubscriptionDiagnosticsDataType_Clear
 *===========================================================================*/
void OpcUa_SubscriptionDiagnosticsDataType_Clear(void* pValue)
{
    OpcUa_SubscriptionDiagnosticsDataType* a_pValue = (OpcUa_SubscriptionDiagnosticsDataType*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_NodeId_Clear(&a_pValue->SessionId);
        SOPC_UInt32_Clear(&a_pValue->SubscriptionId);
        SOPC_Byte_Clear(&a_pValue->Priority);
        SOPC_Double_Clear(&a_pValue->PublishingInterval);
        SOPC_UInt32_Clear(&a_pValue->MaxKeepAliveCount);
        SOPC_UInt32_Clear(&a_pValue->MaxLifetimeCount);
        SOPC_UInt32_Clear(&a_pValue->MaxNotificationsPerPublish);
        SOPC_Boolean_Clear(&a_pValue->PublishingEnabled);
        SOPC_UInt32_Clear(&a_pValue->ModifyCount);
        SOPC_UInt32_Clear(&a_pValue->EnableCount);
        SOPC_UInt32_Clear(&a_pValue->DisableCount);
        SOPC_UInt32_Clear(&a_pValue->RepublishRequestCount);
        SOPC_UInt32_Clear(&a_pValue->RepublishMessageRequestCount);
        SOPC_UInt32_Clear(&a_pValue->RepublishMessageCount);
        SOPC_UInt32_Clear(&a_pValue->TransferRequestCount);
        SOPC_UInt32_Clear(&a_pValue->TransferredToAltClientCount);
        SOPC_UInt32_Clear(&a_pValue->TransferredToSameClientCount);
        SOPC_UInt32_Clear(&a_pValue->PublishRequestCount);
        SOPC_UInt32_Clear(&a_pValue->DataChangeNotificationsCount);
        SOPC_UInt32_Clear(&a_pValue->EventNotificationsCount);
        SOPC_UInt32_Clear(&a_pValue->NotificationsCount);
        SOPC_UInt32_Clear(&a_pValue->LatePublishRequestCount);
        SOPC_UInt32_Clear(&a_pValue->CurrentKeepAliveCount);
        SOPC_UInt32_Clear(&a_pValue->CurrentLifetimeCount);
        SOPC_UInt32_Clear(&a_pValue->UnacknowledgedMessageCount);
        SOPC_UInt32_Clear(&a_pValue->DiscardedMessageCount);
        SOPC_UInt32_Clear(&a_pValue->MonitoredItemCount);
        SOPC_UInt32_Clear(&a_pValue->DisabledMonitoredItemCount);
        SOPC_UInt32_Clear(&a_pValue->MonitoringQueueOverflowCount);
        SOPC_UInt32_Clear(&a_pValue->NextSequenceNumber);
        SOPC_UInt32_Clear(&a_pValue->EventQueueOverFlowCount);
    }
}

/*============================================================================
 * OpcUa_SubscriptionDiagnosticsDataType_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_SubscriptionDiagnosticsDataType_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_SubscriptionDiagnosticsDataType* a_pValue = (const OpcUa_SubscriptionDiagnosticsDataType*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Write(&a_pValue->SessionId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->SubscriptionId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Byte_Write(&a_pValue->Priority, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Double_Write(&a_pValue->PublishingInterval, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->MaxKeepAliveCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->MaxLifetimeCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->MaxNotificationsPerPublish, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Write(&a_pValue->PublishingEnabled, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->ModifyCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->EnableCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->DisableCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->RepublishRequestCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->RepublishMessageRequestCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->RepublishMessageCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->TransferRequestCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->TransferredToAltClientCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->TransferredToSameClientCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->PublishRequestCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->DataChangeNotificationsCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->EventNotificationsCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->NotificationsCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->LatePublishRequestCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->CurrentKeepAliveCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->CurrentLifetimeCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->UnacknowledgedMessageCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->DiscardedMessageCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->MonitoredItemCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->DisabledMonitoredItemCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->MonitoringQueueOverflowCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->NextSequenceNumber, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Write(&a_pValue->EventQueueOverFlowCount, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_SubscriptionDiagnosticsDataType_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_SubscriptionDiagnosticsDataType_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_SubscriptionDiagnosticsDataType* a_pValue = (OpcUa_SubscriptionDiagnosticsDataType*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_SubscriptionDiagnosticsDataType_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Read(&a_pValue->SessionId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->SubscriptionId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Byte_Read(&a_pValue->Priority, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Double_Read(&a_pValue->PublishingInterval, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->MaxKeepAliveCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->MaxLifetimeCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->MaxNotificationsPerPublish, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Boolean_Read(&a_pValue->PublishingEnabled, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->ModifyCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->EnableCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->DisableCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->RepublishRequestCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->RepublishMessageRequestCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->RepublishMessageCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->TransferRequestCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->TransferredToAltClientCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->TransferredToSameClientCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->PublishRequestCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->DataChangeNotificationsCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->EventNotificationsCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->NotificationsCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->LatePublishRequestCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->CurrentKeepAliveCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->CurrentLifetimeCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->UnacknowledgedMessageCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->DiscardedMessageCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->MonitoredItemCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->DisabledMonitoredItemCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->MonitoringQueueOverflowCount, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->NextSequenceNumber, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_UInt32_Read(&a_pValue->EventQueueOverFlowCount, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_SubscriptionDiagnosticsDataType_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_ModelChangeStructureDataType
/*============================================================================
 * OpcUa_ModelChangeStructureDataType_Initialize
 *===========================================================================*/
void OpcUa_ModelChangeStructureDataType_Initialize(void* pValue)
{
    OpcUa_ModelChangeStructureDataType* a_pValue = (OpcUa_ModelChangeStructureDataType*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_ModelChangeStructureDataType_EncodeableType;
        SOPC_NodeId_Initialize(&a_pValue->Affected);
        SOPC_NodeId_Initialize(&a_pValue->AffectedType);
        SOPC_Byte_Initialize(&a_pValue->Verb);
    }
}

/*============================================================================
 * OpcUa_ModelChangeStructureDataType_Clear
 *===========================================================================*/
void OpcUa_ModelChangeStructureDataType_Clear(void* pValue)
{
    OpcUa_ModelChangeStructureDataType* a_pValue = (OpcUa_ModelChangeStructureDataType*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_NodeId_Clear(&a_pValue->Affected);
        SOPC_NodeId_Clear(&a_pValue->AffectedType);
        SOPC_Byte_Clear(&a_pValue->Verb);
    }
}

/*============================================================================
 * OpcUa_ModelChangeStructureDataType_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_ModelChangeStructureDataType_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_ModelChangeStructureDataType* a_pValue = (const OpcUa_ModelChangeStructureDataType*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Write(&a_pValue->Affected, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Write(&a_pValue->AffectedType, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Byte_Write(&a_pValue->Verb, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_ModelChangeStructureDataType_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_ModelChangeStructureDataType_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_ModelChangeStructureDataType* a_pValue = (OpcUa_ModelChangeStructureDataType*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_ModelChangeStructureDataType_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Read(&a_pValue->Affected, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Read(&a_pValue->AffectedType, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Byte_Read(&a_pValue->Verb, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_ModelChangeStructureDataType_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_SemanticChangeStructureDataType
/*============================================================================
 * OpcUa_SemanticChangeStructureDataType_Initialize
 *===========================================================================*/
void OpcUa_SemanticChangeStructureDataType_Initialize(void* pValue)
{
    OpcUa_SemanticChangeStructureDataType* a_pValue = (OpcUa_SemanticChangeStructureDataType*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_SemanticChangeStructureDataType_EncodeableType;
        SOPC_NodeId_Initialize(&a_pValue->Affected);
        SOPC_NodeId_Initialize(&a_pValue->AffectedType);
    }
}

/*============================================================================
 * OpcUa_SemanticChangeStructureDataType_Clear
 *===========================================================================*/
void OpcUa_SemanticChangeStructureDataType_Clear(void* pValue)
{
    OpcUa_SemanticChangeStructureDataType* a_pValue = (OpcUa_SemanticChangeStructureDataType*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_NodeId_Clear(&a_pValue->Affected);
        SOPC_NodeId_Clear(&a_pValue->AffectedType);
    }
}

/*============================================================================
 * OpcUa_SemanticChangeStructureDataType_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_SemanticChangeStructureDataType_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_SemanticChangeStructureDataType* a_pValue = (const OpcUa_SemanticChangeStructureDataType*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Write(&a_pValue->Affected, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Write(&a_pValue->AffectedType, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_SemanticChangeStructureDataType_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_SemanticChangeStructureDataType_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_SemanticChangeStructureDataType* a_pValue = (OpcUa_SemanticChangeStructureDataType*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_SemanticChangeStructureDataType_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Read(&a_pValue->Affected, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Read(&a_pValue->AffectedType, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_SemanticChangeStructureDataType_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_Range
/*============================================================================
 * OpcUa_Range_Initialize
 *===========================================================================*/
void OpcUa_Range_Initialize(void* pValue)
{
    OpcUa_Range* a_pValue = (OpcUa_Range*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_Range_EncodeableType;
        SOPC_Double_Initialize(&a_pValue->Low);
        SOPC_Double_Initialize(&a_pValue->High);
    }
}

/*============================================================================
 * OpcUa_Range_Clear
 *===========================================================================*/
void OpcUa_Range_Clear(void* pValue)
{
    OpcUa_Range* a_pValue = (OpcUa_Range*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_Double_Clear(&a_pValue->Low);
        SOPC_Double_Clear(&a_pValue->High);
    }
}

/*============================================================================
 * OpcUa_Range_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_Range_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_Range* a_pValue = (const OpcUa_Range*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Double_Write(&a_pValue->Low, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Double_Write(&a_pValue->High, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_Range_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_Range_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_Range* a_pValue = (OpcUa_Range*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_Range_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Double_Read(&a_pValue->Low, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Double_Read(&a_pValue->High, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_Range_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_EUInformation
/*============================================================================
 * OpcUa_EUInformation_Initialize
 *===========================================================================*/
void OpcUa_EUInformation_Initialize(void* pValue)
{
    OpcUa_EUInformation* a_pValue = (OpcUa_EUInformation*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_EUInformation_EncodeableType;
        SOPC_String_Initialize(&a_pValue->NamespaceUri);
        SOPC_Int32_Initialize(&a_pValue->UnitId);
        SOPC_LocalizedText_Initialize(&a_pValue->DisplayName);
        SOPC_LocalizedText_Initialize(&a_pValue->Description);
    }
}

/*============================================================================
 * OpcUa_EUInformation_Clear
 *===========================================================================*/
void OpcUa_EUInformation_Clear(void* pValue)
{
    OpcUa_EUInformation* a_pValue = (OpcUa_EUInformation*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_String_Clear(&a_pValue->NamespaceUri);
        SOPC_Int32_Clear(&a_pValue->UnitId);
        SOPC_LocalizedText_Clear(&a_pValue->DisplayName);
        SOPC_LocalizedText_Clear(&a_pValue->Description);
    }
}

/*============================================================================
 * OpcUa_EUInformation_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_EUInformation_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_EUInformation* a_pValue = (const OpcUa_EUInformation*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Write(&a_pValue->NamespaceUri, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Int32_Write(&a_pValue->UnitId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Write(&a_pValue->DisplayName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Write(&a_pValue->Description, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_EUInformation_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_EUInformation_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_EUInformation* a_pValue = (OpcUa_EUInformation*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_EUInformation_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Read(&a_pValue->NamespaceUri, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Int32_Read(&a_pValue->UnitId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Read(&a_pValue->DisplayName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Read(&a_pValue->Description, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_EUInformation_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_ComplexNumberType
/*============================================================================
 * OpcUa_ComplexNumberType_Initialize
 *===========================================================================*/
void OpcUa_ComplexNumberType_Initialize(void* pValue)
{
    OpcUa_ComplexNumberType* a_pValue = (OpcUa_ComplexNumberType*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_ComplexNumberType_EncodeableType;
        SOPC_Float_Initialize(&a_pValue->Real);
        SOPC_Float_Initialize(&a_pValue->Imaginary);
    }
}

/*============================================================================
 * OpcUa_ComplexNumberType_Clear
 *===========================================================================*/
void OpcUa_ComplexNumberType_Clear(void* pValue)
{
    OpcUa_ComplexNumberType* a_pValue = (OpcUa_ComplexNumberType*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_Float_Clear(&a_pValue->Real);
        SOPC_Float_Clear(&a_pValue->Imaginary);
    }
}

/*============================================================================
 * OpcUa_ComplexNumberType_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_ComplexNumberType_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_ComplexNumberType* a_pValue = (const OpcUa_ComplexNumberType*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Float_Write(&a_pValue->Real, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Float_Write(&a_pValue->Imaginary, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_ComplexNumberType_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_ComplexNumberType_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_ComplexNumberType* a_pValue = (OpcUa_ComplexNumberType*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_ComplexNumberType_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Float_Read(&a_pValue->Real, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Float_Read(&a_pValue->Imaginary, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_ComplexNumberType_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_DoubleComplexNumberType
/*============================================================================
 * OpcUa_DoubleComplexNumberType_Initialize
 *===========================================================================*/
void OpcUa_DoubleComplexNumberType_Initialize(void* pValue)
{
    OpcUa_DoubleComplexNumberType* a_pValue = (OpcUa_DoubleComplexNumberType*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_DoubleComplexNumberType_EncodeableType;
        SOPC_Double_Initialize(&a_pValue->Real);
        SOPC_Double_Initialize(&a_pValue->Imaginary);
    }
}

/*============================================================================
 * OpcUa_DoubleComplexNumberType_Clear
 *===========================================================================*/
void OpcUa_DoubleComplexNumberType_Clear(void* pValue)
{
    OpcUa_DoubleComplexNumberType* a_pValue = (OpcUa_DoubleComplexNumberType*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_Double_Clear(&a_pValue->Real);
        SOPC_Double_Clear(&a_pValue->Imaginary);
    }
}

/*============================================================================
 * OpcUa_DoubleComplexNumberType_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_DoubleComplexNumberType_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_DoubleComplexNumberType* a_pValue = (const OpcUa_DoubleComplexNumberType*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Double_Write(&a_pValue->Real, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Double_Write(&a_pValue->Imaginary, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_DoubleComplexNumberType_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_DoubleComplexNumberType_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_DoubleComplexNumberType* a_pValue = (OpcUa_DoubleComplexNumberType*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_DoubleComplexNumberType_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Double_Read(&a_pValue->Real, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Double_Read(&a_pValue->Imaginary, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_DoubleComplexNumberType_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_AxisInformation
/*============================================================================
 * OpcUa_AxisInformation_Initialize
 *===========================================================================*/
void OpcUa_AxisInformation_Initialize(void* pValue)
{
    OpcUa_AxisInformation* a_pValue = (OpcUa_AxisInformation*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_AxisInformation_EncodeableType;
        OpcUa_EUInformation_Initialize(&a_pValue->EngineeringUnits);
        OpcUa_Range_Initialize(&a_pValue->EURange);
        SOPC_LocalizedText_Initialize(&a_pValue->Title);
        SOPC_Initialize_EnumeratedType((int32_t*) &a_pValue->AxisScaleType);
        SOPC_Initialize_Array(&a_pValue->NoOfAxisSteps, (void**) &a_pValue->AxisSteps, sizeof(double),
                              (SOPC_EncodeableObject_PfnInitialize*) SOPC_Double_InitializeAux);
    }
}

/*============================================================================
 * OpcUa_AxisInformation_Clear
 *===========================================================================*/
void OpcUa_AxisInformation_Clear(void* pValue)
{
    OpcUa_AxisInformation* a_pValue = (OpcUa_AxisInformation*) pValue;
    if (a_pValue != NULL)
    {
        OpcUa_EUInformation_Clear(&a_pValue->EngineeringUnits);
        OpcUa_Range_Clear(&a_pValue->EURange);
        SOPC_LocalizedText_Clear(&a_pValue->Title);
        SOPC_Clear_EnumeratedType((int32_t*) &a_pValue->AxisScaleType);
        SOPC_Clear_Array(&a_pValue->NoOfAxisSteps, (void**) &a_pValue->AxisSteps, sizeof(double),
                         (SOPC_EncodeableObject_PfnClear*) SOPC_Double_ClearAux);
    }
}

/*============================================================================
 * OpcUa_AxisInformation_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_AxisInformation_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_AxisInformation* a_pValue = (const OpcUa_AxisInformation*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_EUInformation_Encode(&a_pValue->EngineeringUnits, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_Range_Encode(&a_pValue->EURange, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Write(&a_pValue->Title, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Write_EnumeratedType(buf, (const int32_t*) &a_pValue->AxisScaleType);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->AxisSteps;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfAxisSteps, &arr, sizeof(double),
                                  (SOPC_EncodeableObject_PfnEncode*) SOPC_Double_WriteAux);
    }

    return status;
}

/*============================================================================
 * OpcUa_AxisInformation_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_AxisInformation_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_AxisInformation* a_pValue = (OpcUa_AxisInformation*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_AxisInformation_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_EUInformation_Decode(&a_pValue->EngineeringUnits, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_Range_Decode(&a_pValue->EURange, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_LocalizedText_Read(&a_pValue->Title, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_EnumeratedType(buf, (int32_t*) &a_pValue->AxisScaleType);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfAxisSteps, (void**) &a_pValue->AxisSteps, sizeof(double),
                                 (SOPC_EncodeableObject_PfnDecode*) SOPC_Double_ReadAux,
                                 (SOPC_EncodeableObject_PfnInitialize*) SOPC_Double_InitializeAux,
                                 (SOPC_EncodeableObject_PfnClear*) SOPC_Double_ClearAux);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_AxisInformation_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_XVType
/*============================================================================
 * OpcUa_XVType_Initialize
 *===========================================================================*/
void OpcUa_XVType_Initialize(void* pValue)
{
    OpcUa_XVType* a_pValue = (OpcUa_XVType*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_XVType_EncodeableType;
        SOPC_Double_Initialize(&a_pValue->X);
        SOPC_Float_Initialize(&a_pValue->Value);
    }
}

/*============================================================================
 * OpcUa_XVType_Clear
 *===========================================================================*/
void OpcUa_XVType_Clear(void* pValue)
{
    OpcUa_XVType* a_pValue = (OpcUa_XVType*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_Double_Clear(&a_pValue->X);
        SOPC_Float_Clear(&a_pValue->Value);
    }
}

/*============================================================================
 * OpcUa_XVType_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_XVType_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_XVType* a_pValue = (const OpcUa_XVType*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Double_Write(&a_pValue->X, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Float_Write(&a_pValue->Value, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_XVType_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_XVType_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_XVType* a_pValue = (OpcUa_XVType*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_XVType_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Double_Read(&a_pValue->X, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Float_Read(&a_pValue->Value, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_XVType_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_ProgramDiagnosticDataType
/*============================================================================
 * OpcUa_ProgramDiagnosticDataType_Initialize
 *===========================================================================*/
void OpcUa_ProgramDiagnosticDataType_Initialize(void* pValue)
{
    OpcUa_ProgramDiagnosticDataType* a_pValue = (OpcUa_ProgramDiagnosticDataType*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_ProgramDiagnosticDataType_EncodeableType;
        SOPC_NodeId_Initialize(&a_pValue->CreateSessionId);
        SOPC_String_Initialize(&a_pValue->CreateClientName);
        SOPC_DateTime_Initialize(&a_pValue->InvocationCreationTime);
        SOPC_DateTime_Initialize(&a_pValue->LastTransitionTime);
        SOPC_String_Initialize(&a_pValue->LastMethodCall);
        SOPC_NodeId_Initialize(&a_pValue->LastMethodSessionId);
        SOPC_Initialize_Array(&a_pValue->NoOfLastMethodInputArguments, (void**) &a_pValue->LastMethodInputArguments,
                              sizeof(OpcUa_Argument), (SOPC_EncodeableObject_PfnInitialize*) OpcUa_Argument_Initialize);
        SOPC_Initialize_Array(&a_pValue->NoOfLastMethodOutputArguments, (void**) &a_pValue->LastMethodOutputArguments,
                              sizeof(OpcUa_Argument), (SOPC_EncodeableObject_PfnInitialize*) OpcUa_Argument_Initialize);
        SOPC_DateTime_Initialize(&a_pValue->LastMethodCallTime);
        OpcUa_StatusResult_Initialize(&a_pValue->LastMethodReturnStatus);
    }
}

/*============================================================================
 * OpcUa_ProgramDiagnosticDataType_Clear
 *===========================================================================*/
void OpcUa_ProgramDiagnosticDataType_Clear(void* pValue)
{
    OpcUa_ProgramDiagnosticDataType* a_pValue = (OpcUa_ProgramDiagnosticDataType*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_NodeId_Clear(&a_pValue->CreateSessionId);
        SOPC_String_Clear(&a_pValue->CreateClientName);
        SOPC_DateTime_Clear(&a_pValue->InvocationCreationTime);
        SOPC_DateTime_Clear(&a_pValue->LastTransitionTime);
        SOPC_String_Clear(&a_pValue->LastMethodCall);
        SOPC_NodeId_Clear(&a_pValue->LastMethodSessionId);
        SOPC_Clear_Array(&a_pValue->NoOfLastMethodInputArguments, (void**) &a_pValue->LastMethodInputArguments,
                         sizeof(OpcUa_Argument), (SOPC_EncodeableObject_PfnClear*) OpcUa_Argument_Clear);
        SOPC_Clear_Array(&a_pValue->NoOfLastMethodOutputArguments, (void**) &a_pValue->LastMethodOutputArguments,
                         sizeof(OpcUa_Argument), (SOPC_EncodeableObject_PfnClear*) OpcUa_Argument_Clear);
        SOPC_DateTime_Clear(&a_pValue->LastMethodCallTime);
        OpcUa_StatusResult_Clear(&a_pValue->LastMethodReturnStatus);
    }
}

/*============================================================================
 * OpcUa_ProgramDiagnosticDataType_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_ProgramDiagnosticDataType_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_ProgramDiagnosticDataType* a_pValue = (const OpcUa_ProgramDiagnosticDataType*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Write(&a_pValue->CreateSessionId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Write(&a_pValue->CreateClientName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_DateTime_Write(&a_pValue->InvocationCreationTime, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_DateTime_Write(&a_pValue->LastTransitionTime, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Write(&a_pValue->LastMethodCall, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Write(&a_pValue->LastMethodSessionId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->LastMethodInputArguments;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfLastMethodInputArguments, &arr, sizeof(OpcUa_Argument),
                                  (SOPC_EncodeableObject_PfnEncode*) OpcUa_Argument_Encode);
    }
    if (SOPC_STATUS_OK == status)
    {
        const void* arr = a_pValue->LastMethodOutputArguments;
        status = SOPC_Write_Array(buf, &a_pValue->NoOfLastMethodOutputArguments, &arr, sizeof(OpcUa_Argument),
                                  (SOPC_EncodeableObject_PfnEncode*) OpcUa_Argument_Encode);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_DateTime_Write(&a_pValue->LastMethodCallTime, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_StatusResult_Encode(&a_pValue->LastMethodReturnStatus, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_ProgramDiagnosticDataType_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_ProgramDiagnosticDataType_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_ProgramDiagnosticDataType* a_pValue = (OpcUa_ProgramDiagnosticDataType*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_ProgramDiagnosticDataType_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Read(&a_pValue->CreateSessionId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Read(&a_pValue->CreateClientName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_DateTime_Read(&a_pValue->InvocationCreationTime, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_DateTime_Read(&a_pValue->LastTransitionTime, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Read(&a_pValue->LastMethodCall, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_NodeId_Read(&a_pValue->LastMethodSessionId, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status =
            SOPC_Read_Array(buf, &a_pValue->NoOfLastMethodInputArguments, (void**) &a_pValue->LastMethodInputArguments,
                            sizeof(OpcUa_Argument), (SOPC_EncodeableObject_PfnDecode*) OpcUa_Argument_Decode,
                            (SOPC_EncodeableObject_PfnInitialize*) OpcUa_Argument_Initialize,
                            (SOPC_EncodeableObject_PfnClear*) OpcUa_Argument_Clear);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_Read_Array(buf, &a_pValue->NoOfLastMethodOutputArguments,
                                 (void**) &a_pValue->LastMethodOutputArguments, sizeof(OpcUa_Argument),
                                 (SOPC_EncodeableObject_PfnDecode*) OpcUa_Argument_Decode,
                                 (SOPC_EncodeableObject_PfnInitialize*) OpcUa_Argument_Initialize,
                                 (SOPC_EncodeableObject_PfnClear*) OpcUa_Argument_Clear);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_DateTime_Read(&a_pValue->LastMethodCallTime, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = OpcUa_StatusResult_Decode(&a_pValue->LastMethodReturnStatus, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_ProgramDiagnosticDataType_Clear(a_pValue);
    }

    return status;
}
#endif

#ifndef OPCUA_EXCLUDE_Annotation
/*============================================================================
 * OpcUa_Annotation_Initialize
 *===========================================================================*/
void OpcUa_Annotation_Initialize(void* pValue)
{
    OpcUa_Annotation* a_pValue = (OpcUa_Annotation*) pValue;
    if (a_pValue != NULL)
    {
        a_pValue->encodeableType = &OpcUa_Annotation_EncodeableType;
        SOPC_String_Initialize(&a_pValue->Message);
        SOPC_String_Initialize(&a_pValue->UserName);
        SOPC_DateTime_Initialize(&a_pValue->AnnotationTime);
    }
}

/*============================================================================
 * OpcUa_Annotation_Clear
 *===========================================================================*/
void OpcUa_Annotation_Clear(void* pValue)
{
    OpcUa_Annotation* a_pValue = (OpcUa_Annotation*) pValue;
    if (a_pValue != NULL)
    {
        SOPC_String_Clear(&a_pValue->Message);
        SOPC_String_Clear(&a_pValue->UserName);
        SOPC_DateTime_Clear(&a_pValue->AnnotationTime);
    }
}

/*============================================================================
 * OpcUa_Annotation_Encode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_Annotation_Encode(const void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    const OpcUa_Annotation* a_pValue = (const OpcUa_Annotation*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Write(&a_pValue->Message, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Write(&a_pValue->UserName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_DateTime_Write(&a_pValue->AnnotationTime, buf);
    }

    return status;
}

/*============================================================================
 * OpcUa_Annotation_Decode
 *===========================================================================*/
SOPC_ReturnStatus OpcUa_Annotation_Decode(void* pValue, SOPC_Buffer* buf)
{
    SOPC_ReturnStatus status = SOPC_STATUS_INVALID_PARAMETERS;
    OpcUa_Annotation* a_pValue = (OpcUa_Annotation*) pValue;

    if (a_pValue != NULL && buf != NULL)
    {
        status = SOPC_STATUS_OK;
    }

    OpcUa_Annotation_Initialize(a_pValue);

    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Read(&a_pValue->Message, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_String_Read(&a_pValue->UserName, buf);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = SOPC_DateTime_Read(&a_pValue->AnnotationTime, buf);
    }

    if (status != SOPC_STATUS_OK && a_pValue != NULL)
    {
        OpcUa_Annotation_Clear(a_pValue);
    }

    return status;
}
#endif

void SOPC_Initialize_EnumeratedType(int32_t* enumerationValue)
{
    *enumerationValue = 0;
}

void SOPC_Clear_EnumeratedType(int32_t* enumerationValue)
{
    *enumerationValue = 0;
}

SOPC_ReturnStatus SOPC_Read_EnumeratedType(SOPC_Buffer* buffer, int32_t* enumerationValue)
{
    return SOPC_Int32_Read(enumerationValue, buffer);
}

SOPC_ReturnStatus SOPC_Write_EnumeratedType(SOPC_Buffer* buffer, const int32_t* enumerationValue)
{
    return SOPC_Int32_Write(enumerationValue, buffer);
}

/* This is the last line of an autogenerated file. */

#include "sopc_types.c.suppl"
