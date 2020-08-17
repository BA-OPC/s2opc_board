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

#ifndef SOPC_Enum_Types_H_
#define SOPC_Enum_Types_H_ 1

#include <stdint.h>

#ifndef OPCUA_EXCLUDE_IdType
/*============================================================================
 * The IdType enumeration.
 *===========================================================================*/
typedef enum _OpcUa_IdType
{
    OpcUa_IdType_Numeric = 0,
    OpcUa_IdType_String = 1,
    OpcUa_IdType_Guid = 2,
    OpcUa_IdType_Opaque = 3,
    OpcUa_IdType_SizeOf = INT32_MAX
} OpcUa_IdType;

#endif

#ifndef OPCUA_EXCLUDE_NodeClass
/*============================================================================
 * The NodeClass enumeration.
 *===========================================================================*/
typedef enum _OpcUa_NodeClass
{
    OpcUa_NodeClass_Unspecified = 0,
    OpcUa_NodeClass_Object = 1,
    OpcUa_NodeClass_Variable = 2,
    OpcUa_NodeClass_Method = 4,
    OpcUa_NodeClass_ObjectType = 8,
    OpcUa_NodeClass_VariableType = 16,
    OpcUa_NodeClass_ReferenceType = 32,
    OpcUa_NodeClass_DataType = 64,
    OpcUa_NodeClass_View = 128,
    OpcUa_NodeClass_SizeOf = INT32_MAX
} OpcUa_NodeClass;

#endif

#ifndef OPCUA_EXCLUDE_ApplicationType
/*============================================================================
 * The ApplicationType enumeration.
 *===========================================================================*/
typedef enum _OpcUa_ApplicationType
{
    OpcUa_ApplicationType_Server = 0,
    OpcUa_ApplicationType_Client = 1,
    OpcUa_ApplicationType_ClientAndServer = 2,
    OpcUa_ApplicationType_DiscoveryServer = 3,
    OpcUa_ApplicationType_SizeOf = INT32_MAX
} OpcUa_ApplicationType;

#endif

#ifndef OPCUA_EXCLUDE_MessageSecurityMode
/*============================================================================
 * The MessageSecurityMode enumeration.
 *===========================================================================*/
typedef enum _OpcUa_MessageSecurityMode
{
    OpcUa_MessageSecurityMode_Invalid = 0,
    OpcUa_MessageSecurityMode_None = 1,
    OpcUa_MessageSecurityMode_Sign = 2,
    OpcUa_MessageSecurityMode_SignAndEncrypt = 3,
    OpcUa_MessageSecurityMode_SizeOf = INT32_MAX
} OpcUa_MessageSecurityMode;

#endif

#ifndef OPCUA_EXCLUDE_UserTokenType
/*============================================================================
 * The UserTokenType enumeration.
 *===========================================================================*/
typedef enum _OpcUa_UserTokenType
{
    OpcUa_UserTokenType_Anonymous = 0,
    OpcUa_UserTokenType_UserName = 1,
    OpcUa_UserTokenType_Certificate = 2,
    OpcUa_UserTokenType_IssuedToken = 3,
    OpcUa_UserTokenType_Kerberos = 4,
    OpcUa_UserTokenType_SizeOf = INT32_MAX
} OpcUa_UserTokenType;

#endif

#ifndef OPCUA_EXCLUDE_SecurityTokenRequestType
/*============================================================================
 * The SecurityTokenRequestType enumeration.
 *===========================================================================*/
typedef enum _OpcUa_SecurityTokenRequestType
{
    OpcUa_SecurityTokenRequestType_Issue = 0,
    OpcUa_SecurityTokenRequestType_Renew = 1,
    OpcUa_SecurityTokenRequestType_SizeOf = INT32_MAX
} OpcUa_SecurityTokenRequestType;

#endif

#ifndef OPCUA_EXCLUDE_NodeAttributesMask
/*============================================================================
 * The NodeAttributesMask enumeration.
 *===========================================================================*/
typedef enum _OpcUa_NodeAttributesMask
{
    OpcUa_NodeAttributesMask_None = 0,
    OpcUa_NodeAttributesMask_AccessLevel = 1,
    OpcUa_NodeAttributesMask_ArrayDimensions = 2,
    OpcUa_NodeAttributesMask_BrowseName = 4,
    OpcUa_NodeAttributesMask_ContainsNoLoops = 8,
    OpcUa_NodeAttributesMask_DataType = 16,
    OpcUa_NodeAttributesMask_Description = 32,
    OpcUa_NodeAttributesMask_DisplayName = 64,
    OpcUa_NodeAttributesMask_EventNotifier = 128,
    OpcUa_NodeAttributesMask_Executable = 256,
    OpcUa_NodeAttributesMask_Historizing = 512,
    OpcUa_NodeAttributesMask_InverseName = 1024,
    OpcUa_NodeAttributesMask_IsAbstract = 2048,
    OpcUa_NodeAttributesMask_MinimumSamplingInterval = 4096,
    OpcUa_NodeAttributesMask_NodeClass = 8192,
    OpcUa_NodeAttributesMask_NodeId = 16384,
    OpcUa_NodeAttributesMask_Symmetric = 32768,
    OpcUa_NodeAttributesMask_UserAccessLevel = 65536,
    OpcUa_NodeAttributesMask_UserExecutable = 131072,
    OpcUa_NodeAttributesMask_UserWriteMask = 262144,
    OpcUa_NodeAttributesMask_ValueRank = 524288,
    OpcUa_NodeAttributesMask_WriteMask = 1048576,
    OpcUa_NodeAttributesMask_Value = 2097152,
    OpcUa_NodeAttributesMask_All = 4194303,
    OpcUa_NodeAttributesMask_BaseNode = 1335396,
    OpcUa_NodeAttributesMask_Object = 1335524,
    OpcUa_NodeAttributesMask_ObjectTypeOrDataType = 1337444,
    OpcUa_NodeAttributesMask_Variable = 4026999,
    OpcUa_NodeAttributesMask_VariableType = 3958902,
    OpcUa_NodeAttributesMask_Method = 1466724,
    OpcUa_NodeAttributesMask_ReferenceType = 1371236,
    OpcUa_NodeAttributesMask_View = 1335532,
    OpcUa_NodeAttributesMask_SizeOf = INT32_MAX
} OpcUa_NodeAttributesMask;

#endif

#ifndef OPCUA_EXCLUDE_AttributeWriteMask
/*============================================================================
 * The AttributeWriteMask enumeration.
 *===========================================================================*/
typedef enum _OpcUa_AttributeWriteMask
{
    OpcUa_AttributeWriteMask_None = 0,
    OpcUa_AttributeWriteMask_AccessLevel = 1,
    OpcUa_AttributeWriteMask_ArrayDimensions = 2,
    OpcUa_AttributeWriteMask_BrowseName = 4,
    OpcUa_AttributeWriteMask_ContainsNoLoops = 8,
    OpcUa_AttributeWriteMask_DataType = 16,
    OpcUa_AttributeWriteMask_Description = 32,
    OpcUa_AttributeWriteMask_DisplayName = 64,
    OpcUa_AttributeWriteMask_EventNotifier = 128,
    OpcUa_AttributeWriteMask_Executable = 256,
    OpcUa_AttributeWriteMask_Historizing = 512,
    OpcUa_AttributeWriteMask_InverseName = 1024,
    OpcUa_AttributeWriteMask_IsAbstract = 2048,
    OpcUa_AttributeWriteMask_MinimumSamplingInterval = 4096,
    OpcUa_AttributeWriteMask_NodeClass = 8192,
    OpcUa_AttributeWriteMask_NodeId = 16384,
    OpcUa_AttributeWriteMask_Symmetric = 32768,
    OpcUa_AttributeWriteMask_UserAccessLevel = 65536,
    OpcUa_AttributeWriteMask_UserExecutable = 131072,
    OpcUa_AttributeWriteMask_UserWriteMask = 262144,
    OpcUa_AttributeWriteMask_ValueRank = 524288,
    OpcUa_AttributeWriteMask_WriteMask = 1048576,
    OpcUa_AttributeWriteMask_ValueForVariableType = 2097152,
    OpcUa_AttributeWriteMask_SizeOf = INT32_MAX
} OpcUa_AttributeWriteMask;

#endif

#ifndef OPCUA_EXCLUDE_BrowseDirection
/*============================================================================
 * The BrowseDirection enumeration.
 *===========================================================================*/
typedef enum _OpcUa_BrowseDirection
{
    OpcUa_BrowseDirection_Forward = 0,
    OpcUa_BrowseDirection_Inverse = 1,
    OpcUa_BrowseDirection_Both = 2,
    OpcUa_BrowseDirection_SizeOf = INT32_MAX
} OpcUa_BrowseDirection;

#endif

#ifndef OPCUA_EXCLUDE_BrowseResultMask
/*============================================================================
 * The BrowseResultMask enumeration.
 *===========================================================================*/
typedef enum _OpcUa_BrowseResultMask
{
    OpcUa_BrowseResultMask_None = 0,
    OpcUa_BrowseResultMask_ReferenceTypeId = 1,
    OpcUa_BrowseResultMask_IsForward = 2,
    OpcUa_BrowseResultMask_NodeClass = 4,
    OpcUa_BrowseResultMask_BrowseName = 8,
    OpcUa_BrowseResultMask_DisplayName = 16,
    OpcUa_BrowseResultMask_TypeDefinition = 32,
    OpcUa_BrowseResultMask_All = 63,
    OpcUa_BrowseResultMask_ReferenceTypeInfo = 3,
    OpcUa_BrowseResultMask_TargetInfo = 60,
    OpcUa_BrowseResultMask_SizeOf = INT32_MAX
} OpcUa_BrowseResultMask;

#endif

#ifndef OPCUA_EXCLUDE_ComplianceLevel
/*============================================================================
 * The ComplianceLevel enumeration.
 *===========================================================================*/
typedef enum _OpcUa_ComplianceLevel
{
    OpcUa_ComplianceLevel_Untested = 0,
    OpcUa_ComplianceLevel_Partial = 1,
    OpcUa_ComplianceLevel_SelfTested = 2,
    OpcUa_ComplianceLevel_Certified = 3,
    OpcUa_ComplianceLevel_SizeOf = INT32_MAX
} OpcUa_ComplianceLevel;

#endif

#ifndef OPCUA_EXCLUDE_FilterOperator
/*============================================================================
 * The FilterOperator enumeration.
 *===========================================================================*/
typedef enum _OpcUa_FilterOperator
{
    OpcUa_FilterOperator_Equals = 0,
    OpcUa_FilterOperator_IsNull = 1,
    OpcUa_FilterOperator_GreaterThan = 2,
    OpcUa_FilterOperator_LessThan = 3,
    OpcUa_FilterOperator_GreaterThanOrEqual = 4,
    OpcUa_FilterOperator_LessThanOrEqual = 5,
    OpcUa_FilterOperator_Like = 6,
    OpcUa_FilterOperator_Not = 7,
    OpcUa_FilterOperator_Between = 8,
    OpcUa_FilterOperator_InList = 9,
    OpcUa_FilterOperator_And = 10,
    OpcUa_FilterOperator_Or = 11,
    OpcUa_FilterOperator_Cast = 12,
    OpcUa_FilterOperator_InView = 13,
    OpcUa_FilterOperator_OfType = 14,
    OpcUa_FilterOperator_RelatedTo = 15,
    OpcUa_FilterOperator_BitwiseAnd = 16,
    OpcUa_FilterOperator_BitwiseOr = 17,
    OpcUa_FilterOperator_SizeOf = INT32_MAX
} OpcUa_FilterOperator;

#endif

#ifndef OPCUA_EXCLUDE_TimestampsToReturn
/*============================================================================
 * The TimestampsToReturn enumeration.
 *===========================================================================*/
typedef enum _OpcUa_TimestampsToReturn
{
    OpcUa_TimestampsToReturn_Source = 0,
    OpcUa_TimestampsToReturn_Server = 1,
    OpcUa_TimestampsToReturn_Both = 2,
    OpcUa_TimestampsToReturn_Neither = 3,
    OpcUa_TimestampsToReturn_SizeOf = INT32_MAX
} OpcUa_TimestampsToReturn;

#endif

#ifndef OPCUA_EXCLUDE_HistoryUpdateType
/*============================================================================
 * The HistoryUpdateType enumeration.
 *===========================================================================*/
typedef enum _OpcUa_HistoryUpdateType
{
    OpcUa_HistoryUpdateType_Insert = 1,
    OpcUa_HistoryUpdateType_Replace = 2,
    OpcUa_HistoryUpdateType_Update = 3,
    OpcUa_HistoryUpdateType_Delete = 4,
    OpcUa_HistoryUpdateType_SizeOf = INT32_MAX
} OpcUa_HistoryUpdateType;

#endif

#ifndef OPCUA_EXCLUDE_PerformUpdateType
/*============================================================================
 * The PerformUpdateType enumeration.
 *===========================================================================*/
typedef enum _OpcUa_PerformUpdateType
{
    OpcUa_PerformUpdateType_Insert = 1,
    OpcUa_PerformUpdateType_Replace = 2,
    OpcUa_PerformUpdateType_Update = 3,
    OpcUa_PerformUpdateType_Remove = 4,
    OpcUa_PerformUpdateType_SizeOf = INT32_MAX
} OpcUa_PerformUpdateType;

#endif

#ifndef OPCUA_EXCLUDE_MonitoringMode
/*============================================================================
 * The MonitoringMode enumeration.
 *===========================================================================*/
typedef enum _OpcUa_MonitoringMode
{
    OpcUa_MonitoringMode_Disabled = 0,
    OpcUa_MonitoringMode_Sampling = 1,
    OpcUa_MonitoringMode_Reporting = 2,
    OpcUa_MonitoringMode_SizeOf = INT32_MAX
} OpcUa_MonitoringMode;

#endif

#ifndef OPCUA_EXCLUDE_DataChangeTrigger
/*============================================================================
 * The DataChangeTrigger enumeration.
 *===========================================================================*/
typedef enum _OpcUa_DataChangeTrigger
{
    OpcUa_DataChangeTrigger_Status = 0,
    OpcUa_DataChangeTrigger_StatusValue = 1,
    OpcUa_DataChangeTrigger_StatusValueTimestamp = 2,
    OpcUa_DataChangeTrigger_SizeOf = INT32_MAX
} OpcUa_DataChangeTrigger;

#endif

#ifndef OPCUA_EXCLUDE_DeadbandType
/*============================================================================
 * The DeadbandType enumeration.
 *===========================================================================*/
typedef enum _OpcUa_DeadbandType
{
    OpcUa_DeadbandType_None = 0,
    OpcUa_DeadbandType_Absolute = 1,
    OpcUa_DeadbandType_Percent = 2,
    OpcUa_DeadbandType_SizeOf = INT32_MAX
} OpcUa_DeadbandType;

#endif

#ifndef OPCUA_EXCLUDE_EnumeratedTestType
/*============================================================================
 * The EnumeratedTestType enumeration.
 *===========================================================================*/
typedef enum _OpcUa_EnumeratedTestType
{
    OpcUa_EnumeratedTestType_Red = 1,
    OpcUa_EnumeratedTestType_Yellow = 4,
    OpcUa_EnumeratedTestType_Green = 5,
    OpcUa_EnumeratedTestType_SizeOf = INT32_MAX
} OpcUa_EnumeratedTestType;

#endif

#ifndef OPCUA_EXCLUDE_RedundancySupport
/*============================================================================
 * The RedundancySupport enumeration.
 *===========================================================================*/
typedef enum _OpcUa_RedundancySupport
{
    OpcUa_RedundancySupport_None = 0,
    OpcUa_RedundancySupport_Cold = 1,
    OpcUa_RedundancySupport_Warm = 2,
    OpcUa_RedundancySupport_Hot = 3,
    OpcUa_RedundancySupport_Transparent = 4,
    OpcUa_RedundancySupport_HotAndMirrored = 5,
    OpcUa_RedundancySupport_SizeOf = INT32_MAX
} OpcUa_RedundancySupport;

#endif

#ifndef OPCUA_EXCLUDE_ServerState
/*============================================================================
 * The ServerState enumeration.
 *===========================================================================*/
typedef enum _OpcUa_ServerState
{
    OpcUa_ServerState_Running = 0,
    OpcUa_ServerState_Failed = 1,
    OpcUa_ServerState_NoConfiguration = 2,
    OpcUa_ServerState_Suspended = 3,
    OpcUa_ServerState_Shutdown = 4,
    OpcUa_ServerState_Test = 5,
    OpcUa_ServerState_CommunicationFault = 6,
    OpcUa_ServerState_Unknown = 7,
    OpcUa_ServerState_SizeOf = INT32_MAX
} OpcUa_ServerState;

#endif

#ifndef OPCUA_EXCLUDE_ModelChangeStructureVerbMask
/*============================================================================
 * The ModelChangeStructureVerbMask enumeration.
 *===========================================================================*/
typedef enum _OpcUa_ModelChangeStructureVerbMask
{
    OpcUa_ModelChangeStructureVerbMask_NodeAdded = 1,
    OpcUa_ModelChangeStructureVerbMask_NodeDeleted = 2,
    OpcUa_ModelChangeStructureVerbMask_ReferenceAdded = 4,
    OpcUa_ModelChangeStructureVerbMask_ReferenceDeleted = 8,
    OpcUa_ModelChangeStructureVerbMask_DataTypeChanged = 16,
    OpcUa_ModelChangeStructureVerbMask_SizeOf = INT32_MAX
} OpcUa_ModelChangeStructureVerbMask;

#endif

#ifndef OPCUA_EXCLUDE_AxisScaleEnumeration
/*============================================================================
 * The AxisScaleEnumeration enumeration.
 *===========================================================================*/
typedef enum _OpcUa_AxisScaleEnumeration
{
    OpcUa_AxisScaleEnumeration_Linear = 0,
    OpcUa_AxisScaleEnumeration_Log = 1,
    OpcUa_AxisScaleEnumeration_Ln = 2,
    OpcUa_AxisScaleEnumeration_SizeOf = INT32_MAX
} OpcUa_AxisScaleEnumeration;

#endif

#ifndef OPCUA_EXCLUDE_ExceptionDeviationFormat
/*============================================================================
 * The ExceptionDeviationFormat enumeration.
 *===========================================================================*/
typedef enum _OpcUa_ExceptionDeviationFormat
{
    OpcUa_ExceptionDeviationFormat_AbsoluteValue = 0,
    OpcUa_ExceptionDeviationFormat_PercentOfValue = 1,
    OpcUa_ExceptionDeviationFormat_PercentOfRange = 2,
    OpcUa_ExceptionDeviationFormat_PercentOfEURange = 3,
    OpcUa_ExceptionDeviationFormat_Unknown = 4,
    OpcUa_ExceptionDeviationFormat_SizeOf = INT32_MAX
} OpcUa_ExceptionDeviationFormat;

#endif

#endif
/* This is the last line of an autogenerated file. */
