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

#include "sopc_address_space.h"

#include <stdio.h>
#include <stdbool.h>

#include "opcua_statuscodes.h"

#include "sopc_builtintypes.h"
#include "sopc_enums.h"
#include "sopc_types.h"
#include "sopc_macros.h"

const bool sopc_embedded_is_const_addspace = true;

SOPC_GCC_DIAGNOSTIC_IGNORE_DISCARD_QUALIFIER
const SOPC_AddressSpace_Node SOPC_Embedded_AddressSpace_Nodes[] = {
    {
        OpcUa_NodeClass_DataType,
        OpcUa_UncertainInitialValue,
        {0, 0},
        {.data_type={
            .encodeableType = &OpcUa_DataTypeNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 24},
            .NodeClass = OpcUa_NodeClass_DataType,
            .BrowseName = {0, {sizeof("BaseDataType")-1, 1, (SOPC_Byte*) "BaseDataType"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("BaseDataType")-1, 1, (SOPC_Byte*) "BaseDataType"}},
            .Description = {{0, 0, NULL}, {sizeof("Describes a value that can have any valid DataType.")-1, 1, (SOPC_Byte*) "Describes a value that can have any valid DataType."}},
            .NoOfReferences = 1,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 35},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 86}, {0, 0, NULL}, 0},
                }
            },
        }}
    },
    {
        OpcUa_NodeClass_DataType,
        OpcUa_UncertainInitialValue,
        {0, 0},
        {.data_type={
            .encodeableType = &OpcUa_DataTypeNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 26},
            .NodeClass = OpcUa_NodeClass_DataType,
            .BrowseName = {0, {sizeof("Number")-1, 1, (SOPC_Byte*) "Number"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("Number")-1, 1, (SOPC_Byte*) "Number"}},
            .Description = {{0, 0, NULL}, {sizeof("Describes a value that can have any numeric DataType.")-1, 1, (SOPC_Byte*) "Describes a value that can have any numeric DataType."}},
            .NoOfReferences = 1,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 45},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 24}, {0, 0, NULL}, 0},
                }
            },
        }}
    },
    {
        OpcUa_NodeClass_DataType,
        OpcUa_UncertainInitialValue,
        {0, 0},
        {.data_type={
            .encodeableType = &OpcUa_DataTypeNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 27},
            .NodeClass = OpcUa_NodeClass_DataType,
            .BrowseName = {0, {sizeof("Integer")-1, 1, (SOPC_Byte*) "Integer"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("Integer")-1, 1, (SOPC_Byte*) "Integer"}},
            .Description = {{0, 0, NULL}, {sizeof("Describes a value that can have any integer DataType.")-1, 1, (SOPC_Byte*) "Describes a value that can have any integer DataType."}},
            .NoOfReferences = 1,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 45},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 26}, {0, 0, NULL}, 0},
                }
            },
        }}
    },
    {
        OpcUa_NodeClass_DataType,
        OpcUa_UncertainInitialValue,
        {0, 0},
        {.data_type={
            .encodeableType = &OpcUa_DataTypeNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 28},
            .NodeClass = OpcUa_NodeClass_DataType,
            .BrowseName = {0, {sizeof("UInteger")-1, 1, (SOPC_Byte*) "UInteger"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("UInteger")-1, 1, (SOPC_Byte*) "UInteger"}},
            .Description = {{0, 0, NULL}, {sizeof("Describes a value that can have any unsigned integer DataType.")-1, 1, (SOPC_Byte*) "Describes a value that can have any unsigned integer DataType."}},
            .NoOfReferences = 1,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 45},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 26}, {0, 0, NULL}, 0},
                }
            },
        }}
    },
    {
        OpcUa_NodeClass_DataType,
        OpcUa_UncertainInitialValue,
        {0, 0},
        {.data_type={
            .encodeableType = &OpcUa_DataTypeNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 29},
            .NodeClass = OpcUa_NodeClass_DataType,
            .BrowseName = {0, {sizeof("Enumeration")-1, 1, (SOPC_Byte*) "Enumeration"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("Enumeration")-1, 1, (SOPC_Byte*) "Enumeration"}},
            .Description = {{0, 0, NULL}, {sizeof("Describes a value that is an enumerated DataType.")-1, 1, (SOPC_Byte*) "Describes a value that is an enumerated DataType."}},
            .NoOfReferences = 1,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 45},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 24}, {0, 0, NULL}, 0},
                }
            },
        }}
    },
    {
        OpcUa_NodeClass_DataType,
        OpcUa_UncertainInitialValue,
        {0, 0},
        {.data_type={
            .encodeableType = &OpcUa_DataTypeNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 1},
            .NodeClass = OpcUa_NodeClass_DataType,
            .BrowseName = {0, {sizeof("Boolean")-1, 1, (SOPC_Byte*) "Boolean"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("Boolean")-1, 1, (SOPC_Byte*) "Boolean"}},
            .Description = {{0, 0, NULL}, {sizeof("Describes a value that is either TRUE or FALSE.")-1, 1, (SOPC_Byte*) "Describes a value that is either TRUE or FALSE."}},
            .NoOfReferences = 1,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 45},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 24}, {0, 0, NULL}, 0},
                }
            },
        }}
    },
    {
        OpcUa_NodeClass_DataType,
        OpcUa_UncertainInitialValue,
        {0, 0},
        {.data_type={
            .encodeableType = &OpcUa_DataTypeNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 2},
            .NodeClass = OpcUa_NodeClass_DataType,
            .BrowseName = {0, {sizeof("SByte")-1, 1, (SOPC_Byte*) "SByte"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("SByte")-1, 1, (SOPC_Byte*) "SByte"}},
            .Description = {{0, 0, NULL}, {sizeof("Describes a value that is an integer between -128 and 127.")-1, 1, (SOPC_Byte*) "Describes a value that is an integer between -128 and 127."}},
            .NoOfReferences = 1,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 45},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 27}, {0, 0, NULL}, 0},
                }
            },
        }}
    },
    {
        OpcUa_NodeClass_DataType,
        OpcUa_UncertainInitialValue,
        {0, 0},
        {.data_type={
            .encodeableType = &OpcUa_DataTypeNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 3},
            .NodeClass = OpcUa_NodeClass_DataType,
            .BrowseName = {0, {sizeof("Byte")-1, 1, (SOPC_Byte*) "Byte"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("Byte")-1, 1, (SOPC_Byte*) "Byte"}},
            .Description = {{0, 0, NULL}, {sizeof("Describes a value that is an integer between 0 and 255.")-1, 1, (SOPC_Byte*) "Describes a value that is an integer between 0 and 255."}},
            .NoOfReferences = 1,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 45},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 28}, {0, 0, NULL}, 0},
                }
            },
        }}
    },
    {
        OpcUa_NodeClass_DataType,
        OpcUa_UncertainInitialValue,
        {0, 0},
        {.data_type={
            .encodeableType = &OpcUa_DataTypeNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 4},
            .NodeClass = OpcUa_NodeClass_DataType,
            .BrowseName = {0, {sizeof("Int16")-1, 1, (SOPC_Byte*) "Int16"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("Int16")-1, 1, (SOPC_Byte*) "Int16"}},
            .Description = {{0, 0, NULL}, {sizeof("Describes a value that is an integer between −32,768 and 32,767.")-1, 1, (SOPC_Byte*) "Describes a value that is an integer between −32,768 and 32,767."}},
            .NoOfReferences = 1,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 45},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 27}, {0, 0, NULL}, 0},
                }
            },
        }}
    },
    {
        OpcUa_NodeClass_DataType,
        OpcUa_UncertainInitialValue,
        {0, 0},
        {.data_type={
            .encodeableType = &OpcUa_DataTypeNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 5},
            .NodeClass = OpcUa_NodeClass_DataType,
            .BrowseName = {0, {sizeof("UInt16")-1, 1, (SOPC_Byte*) "UInt16"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("UInt16")-1, 1, (SOPC_Byte*) "UInt16"}},
            .Description = {{0, 0, NULL}, {sizeof("Describes a value that is an integer between 0 and 65535.")-1, 1, (SOPC_Byte*) "Describes a value that is an integer between 0 and 65535."}},
            .NoOfReferences = 1,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 45},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 28}, {0, 0, NULL}, 0},
                }
            },
        }}
    },
    {
        OpcUa_NodeClass_DataType,
        OpcUa_UncertainInitialValue,
        {0, 0},
        {.data_type={
            .encodeableType = &OpcUa_DataTypeNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 6},
            .NodeClass = OpcUa_NodeClass_DataType,
            .BrowseName = {0, {sizeof("Int32")-1, 1, (SOPC_Byte*) "Int32"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("Int32")-1, 1, (SOPC_Byte*) "Int32"}},
            .Description = {{0, 0, NULL}, {sizeof("Describes a value that is an integer between −2,147,483,648  and 2,147,483,647.")-1, 1, (SOPC_Byte*) "Describes a value that is an integer between −2,147,483,648  and 2,147,483,647."}},
            .NoOfReferences = 1,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 45},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 27}, {0, 0, NULL}, 0},
                }
            },
        }}
    },
    {
        OpcUa_NodeClass_DataType,
        OpcUa_UncertainInitialValue,
        {0, 0},
        {.data_type={
            .encodeableType = &OpcUa_DataTypeNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 7},
            .NodeClass = OpcUa_NodeClass_DataType,
            .BrowseName = {0, {sizeof("UInt32")-1, 1, (SOPC_Byte*) "UInt32"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("UInt32")-1, 1, (SOPC_Byte*) "UInt32"}},
            .Description = {{0, 0, NULL}, {sizeof("Describes a value that is an integer between 0 and 4,294,967,295.")-1, 1, (SOPC_Byte*) "Describes a value that is an integer between 0 and 4,294,967,295."}},
            .NoOfReferences = 1,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 45},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 28}, {0, 0, NULL}, 0},
                }
            },
        }}
    },
    {
        OpcUa_NodeClass_DataType,
        OpcUa_UncertainInitialValue,
        {0, 0},
        {.data_type={
            .encodeableType = &OpcUa_DataTypeNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 8},
            .NodeClass = OpcUa_NodeClass_DataType,
            .BrowseName = {0, {sizeof("Int64")-1, 1, (SOPC_Byte*) "Int64"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("Int64")-1, 1, (SOPC_Byte*) "Int64"}},
            .Description = {{0, 0, NULL}, {sizeof("Describes a value that is an integer between −9,223,372,036,854,775,808 and 9,223,372,036,854,775,807.")-1, 1, (SOPC_Byte*) "Describes a value that is an integer between −9,223,372,036,854,775,808 and 9,223,372,036,854,775,807."}},
            .NoOfReferences = 1,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 45},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 27}, {0, 0, NULL}, 0},
                }
            },
        }}
    },
    {
        OpcUa_NodeClass_DataType,
        OpcUa_UncertainInitialValue,
        {0, 0},
        {.data_type={
            .encodeableType = &OpcUa_DataTypeNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 9},
            .NodeClass = OpcUa_NodeClass_DataType,
            .BrowseName = {0, {sizeof("UInt64")-1, 1, (SOPC_Byte*) "UInt64"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("UInt64")-1, 1, (SOPC_Byte*) "UInt64"}},
            .Description = {{0, 0, NULL}, {sizeof("Describes a value that is an integer between 0 and 18,446,744,073,709,551,615.")-1, 1, (SOPC_Byte*) "Describes a value that is an integer between 0 and 18,446,744,073,709,551,615."}},
            .NoOfReferences = 1,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 45},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 28}, {0, 0, NULL}, 0},
                }
            },
        }}
    },
    {
        OpcUa_NodeClass_DataType,
        OpcUa_UncertainInitialValue,
        {0, 0},
        {.data_type={
            .encodeableType = &OpcUa_DataTypeNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 10},
            .NodeClass = OpcUa_NodeClass_DataType,
            .BrowseName = {0, {sizeof("Float")-1, 1, (SOPC_Byte*) "Float"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("Float")-1, 1, (SOPC_Byte*) "Float"}},
            .Description = {{0, 0, NULL}, {sizeof("Describes a value that is an IEEE 754-1985 single precision floating point number.")-1, 1, (SOPC_Byte*) "Describes a value that is an IEEE 754-1985 single precision floating point number."}},
            .NoOfReferences = 1,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 45},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 26}, {0, 0, NULL}, 0},
                }
            },
        }}
    },
    {
        OpcUa_NodeClass_DataType,
        OpcUa_UncertainInitialValue,
        {0, 0},
        {.data_type={
            .encodeableType = &OpcUa_DataTypeNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 11},
            .NodeClass = OpcUa_NodeClass_DataType,
            .BrowseName = {0, {sizeof("Double")-1, 1, (SOPC_Byte*) "Double"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("Double")-1, 1, (SOPC_Byte*) "Double"}},
            .Description = {{0, 0, NULL}, {sizeof("Describes a value that is an IEEE 754-1985 double precision floating point number.")-1, 1, (SOPC_Byte*) "Describes a value that is an IEEE 754-1985 double precision floating point number."}},
            .NoOfReferences = 1,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 45},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 26}, {0, 0, NULL}, 0},
                }
            },
        }}
    },
    {
        OpcUa_NodeClass_DataType,
        OpcUa_UncertainInitialValue,
        {0, 0},
        {.data_type={
            .encodeableType = &OpcUa_DataTypeNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 12},
            .NodeClass = OpcUa_NodeClass_DataType,
            .BrowseName = {0, {sizeof("String")-1, 1, (SOPC_Byte*) "String"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("String")-1, 1, (SOPC_Byte*) "String"}},
            .Description = {{0, 0, NULL}, {sizeof("Describes a value that is a sequence of printable Unicode characters.")-1, 1, (SOPC_Byte*) "Describes a value that is a sequence of printable Unicode characters."}},
            .NoOfReferences = 1,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 45},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 24}, {0, 0, NULL}, 0},
                }
            },
        }}
    },
    {
        OpcUa_NodeClass_DataType,
        OpcUa_UncertainInitialValue,
        {0, 0},
        {.data_type={
            .encodeableType = &OpcUa_DataTypeNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 13},
            .NodeClass = OpcUa_NodeClass_DataType,
            .BrowseName = {0, {sizeof("DateTime")-1, 1, (SOPC_Byte*) "DateTime"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("DateTime")-1, 1, (SOPC_Byte*) "DateTime"}},
            .Description = {{0, 0, NULL}, {sizeof("Describes a value that is a Gregorian calender date and time.")-1, 1, (SOPC_Byte*) "Describes a value that is a Gregorian calender date and time."}},
            .NoOfReferences = 1,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 45},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 24}, {0, 0, NULL}, 0},
                }
            },
        }}
    },
    {
        OpcUa_NodeClass_DataType,
        OpcUa_UncertainInitialValue,
        {0, 0},
        {.data_type={
            .encodeableType = &OpcUa_DataTypeNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 14},
            .NodeClass = OpcUa_NodeClass_DataType,
            .BrowseName = {0, {sizeof("Guid")-1, 1, (SOPC_Byte*) "Guid"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("Guid")-1, 1, (SOPC_Byte*) "Guid"}},
            .Description = {{0, 0, NULL}, {sizeof("Describes a value that is a 128-bit globally unique identifier.")-1, 1, (SOPC_Byte*) "Describes a value that is a 128-bit globally unique identifier."}},
            .NoOfReferences = 1,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 45},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 24}, {0, 0, NULL}, 0},
                }
            },
        }}
    },
    {
        OpcUa_NodeClass_DataType,
        OpcUa_UncertainInitialValue,
        {0, 0},
        {.data_type={
            .encodeableType = &OpcUa_DataTypeNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 15},
            .NodeClass = OpcUa_NodeClass_DataType,
            .BrowseName = {0, {sizeof("ByteString")-1, 1, (SOPC_Byte*) "ByteString"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("ByteString")-1, 1, (SOPC_Byte*) "ByteString"}},
            .Description = {{0, 0, NULL}, {sizeof("Describes a value that is a sequence of bytes.")-1, 1, (SOPC_Byte*) "Describes a value that is a sequence of bytes."}},
            .NoOfReferences = 1,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 45},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 24}, {0, 0, NULL}, 0},
                }
            },
        }}
    },
    {
        OpcUa_NodeClass_DataType,
        OpcUa_UncertainInitialValue,
        {0, 0},
        {.data_type={
            .encodeableType = &OpcUa_DataTypeNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 16},
            .NodeClass = OpcUa_NodeClass_DataType,
            .BrowseName = {0, {sizeof("XmlElement")-1, 1, (SOPC_Byte*) "XmlElement"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("XmlElement")-1, 1, (SOPC_Byte*) "XmlElement"}},
            .Description = {{0, 0, NULL}, {sizeof("Describes a value that is an XML element.")-1, 1, (SOPC_Byte*) "Describes a value that is an XML element."}},
            .NoOfReferences = 1,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 45},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 24}, {0, 0, NULL}, 0},
                }
            },
        }}
    },
    {
        OpcUa_NodeClass_DataType,
        OpcUa_UncertainInitialValue,
        {0, 0},
        {.data_type={
            .encodeableType = &OpcUa_DataTypeNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 17},
            .NodeClass = OpcUa_NodeClass_DataType,
            .BrowseName = {0, {sizeof("NodeId")-1, 1, (SOPC_Byte*) "NodeId"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("NodeId")-1, 1, (SOPC_Byte*) "NodeId"}},
            .Description = {{0, 0, NULL}, {sizeof("Describes a value that is an identifier for a node within a Server address space.")-1, 1, (SOPC_Byte*) "Describes a value that is an identifier for a node within a Server address space."}},
            .NoOfReferences = 1,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 45},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 24}, {0, 0, NULL}, 0},
                }
            },
        }}
    },
    {
        OpcUa_NodeClass_DataType,
        OpcUa_UncertainInitialValue,
        {0, 0},
        {.data_type={
            .encodeableType = &OpcUa_DataTypeNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 18},
            .NodeClass = OpcUa_NodeClass_DataType,
            .BrowseName = {0, {sizeof("ExpandedNodeId")-1, 1, (SOPC_Byte*) "ExpandedNodeId"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("ExpandedNodeId")-1, 1, (SOPC_Byte*) "ExpandedNodeId"}},
            .Description = {{0, 0, NULL}, {sizeof("Describes a value that is an absolute identifier for a node.")-1, 1, (SOPC_Byte*) "Describes a value that is an absolute identifier for a node."}},
            .NoOfReferences = 1,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 45},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 24}, {0, 0, NULL}, 0},
                }
            },
        }}
    },
    {
        OpcUa_NodeClass_DataType,
        OpcUa_UncertainInitialValue,
        {0, 0},
        {.data_type={
            .encodeableType = &OpcUa_DataTypeNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 19},
            .NodeClass = OpcUa_NodeClass_DataType,
            .BrowseName = {0, {sizeof("StatusCode")-1, 1, (SOPC_Byte*) "StatusCode"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("StatusCode")-1, 1, (SOPC_Byte*) "StatusCode"}},
            .Description = {{0, 0, NULL}, {sizeof("Describes a value that is a code representing the outcome of an operation by a Server.")-1, 1, (SOPC_Byte*) "Describes a value that is a code representing the outcome of an operation by a Server."}},
            .NoOfReferences = 1,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 45},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 24}, {0, 0, NULL}, 0},
                }
            },
        }}
    },
    {
        OpcUa_NodeClass_DataType,
        OpcUa_UncertainInitialValue,
        {0, 0},
        {.data_type={
            .encodeableType = &OpcUa_DataTypeNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 20},
            .NodeClass = OpcUa_NodeClass_DataType,
            .BrowseName = {0, {sizeof("QualifiedName")-1, 1, (SOPC_Byte*) "QualifiedName"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("QualifiedName")-1, 1, (SOPC_Byte*) "QualifiedName"}},
            .Description = {{0, 0, NULL}, {sizeof("Describes a value that is a name qualified by a namespace.")-1, 1, (SOPC_Byte*) "Describes a value that is a name qualified by a namespace."}},
            .NoOfReferences = 1,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 45},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 24}, {0, 0, NULL}, 0},
                }
            },
        }}
    },
    {
        OpcUa_NodeClass_DataType,
        OpcUa_UncertainInitialValue,
        {0, 0},
        {.data_type={
            .encodeableType = &OpcUa_DataTypeNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 21},
            .NodeClass = OpcUa_NodeClass_DataType,
            .BrowseName = {0, {sizeof("LocalizedText")-1, 1, (SOPC_Byte*) "LocalizedText"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("LocalizedText")-1, 1, (SOPC_Byte*) "LocalizedText"}},
            .Description = {{0, 0, NULL}, {sizeof("Describes a value that is human readable Unicode text with a locale identifier.")-1, 1, (SOPC_Byte*) "Describes a value that is human readable Unicode text with a locale identifier."}},
            .NoOfReferences = 1,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 45},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 24}, {0, 0, NULL}, 0},
                }
            },
        }}
    },
    {
        OpcUa_NodeClass_DataType,
        OpcUa_UncertainInitialValue,
        {0, 0},
        {.data_type={
            .encodeableType = &OpcUa_DataTypeNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 22},
            .NodeClass = OpcUa_NodeClass_DataType,
            .BrowseName = {0, {sizeof("Structure")-1, 1, (SOPC_Byte*) "Structure"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("Structure")-1, 1, (SOPC_Byte*) "Structure"}},
            .Description = {{0, 0, NULL}, {sizeof("Describes a value that is any type of structure that can be described with a data encoding.")-1, 1, (SOPC_Byte*) "Describes a value that is any type of structure that can be described with a data encoding."}},
            .NoOfReferences = 1,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 45},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 24}, {0, 0, NULL}, 0},
                }
            },
        }}
    },
    {
        OpcUa_NodeClass_DataType,
        OpcUa_UncertainInitialValue,
        {0, 0},
        {.data_type={
            .encodeableType = &OpcUa_DataTypeNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 23},
            .NodeClass = OpcUa_NodeClass_DataType,
            .BrowseName = {0, {sizeof("DataValue")-1, 1, (SOPC_Byte*) "DataValue"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("DataValue")-1, 1, (SOPC_Byte*) "DataValue"}},
            .Description = {{0, 0, NULL}, {sizeof("Describes a value that is a structure containing a value, a status code and timestamps.")-1, 1, (SOPC_Byte*) "Describes a value that is a structure containing a value, a status code and timestamps."}},
            .NoOfReferences = 1,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 45},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 24}, {0, 0, NULL}, 0},
                }
            },
        }}
    },
    {
        OpcUa_NodeClass_DataType,
        OpcUa_UncertainInitialValue,
        {0, 0},
        {.data_type={
            .encodeableType = &OpcUa_DataTypeNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 25},
            .NodeClass = OpcUa_NodeClass_DataType,
            .BrowseName = {0, {sizeof("DiagnosticInfo")-1, 1, (SOPC_Byte*) "DiagnosticInfo"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("DiagnosticInfo")-1, 1, (SOPC_Byte*) "DiagnosticInfo"}},
            .Description = {{0, 0, NULL}, {sizeof("Describes a value that is a structure containing diagnostics associated with a StatusCode.")-1, 1, (SOPC_Byte*) "Describes a value that is a structure containing diagnostics associated with a StatusCode."}},
            .NoOfReferences = 1,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 45},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 24}, {0, 0, NULL}, 0},
                }
            },
        }}
    },
    {
        OpcUa_NodeClass_ReferenceType,
        OpcUa_UncertainInitialValue,
        {0, 0},
        {.reference_type={
            .encodeableType = &OpcUa_ReferenceTypeNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 31},
            .NodeClass = OpcUa_NodeClass_ReferenceType,
            .BrowseName = {0, {sizeof("References")-1, 1, (SOPC_Byte*) "References"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("References")-1, 1, (SOPC_Byte*) "References"}},
            .Description = {{0, 0, NULL}, {sizeof("The abstract base type for all references.")-1, 1, (SOPC_Byte*) "The abstract base type for all references."}},
            .NoOfReferences = 0,
            .References = NULL,
        }}
    },
    {
        OpcUa_NodeClass_ReferenceType,
        OpcUa_UncertainInitialValue,
        {0, 0},
        {.reference_type={
            .encodeableType = &OpcUa_ReferenceTypeNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 32},
            .NodeClass = OpcUa_NodeClass_ReferenceType,
            .BrowseName = {0, {sizeof("NonHierarchicalReferences")-1, 1, (SOPC_Byte*) "NonHierarchicalReferences"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("NonHierarchicalReferences")-1, 1, (SOPC_Byte*) "NonHierarchicalReferences"}},
            .Description = {{0, 0, NULL}, {sizeof("The abstract base type for all non-hierarchical references.")-1, 1, (SOPC_Byte*) "The abstract base type for all non-hierarchical references."}},
            .NoOfReferences = 1,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 45},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 31}, {0, 0, NULL}, 0},
                }
            },
        }}
    },
    {
        OpcUa_NodeClass_ReferenceType,
        OpcUa_UncertainInitialValue,
        {0, 0},
        {.reference_type={
            .encodeableType = &OpcUa_ReferenceTypeNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 33},
            .NodeClass = OpcUa_NodeClass_ReferenceType,
            .BrowseName = {0, {sizeof("HierarchicalReferences")-1, 1, (SOPC_Byte*) "HierarchicalReferences"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("HierarchicalReferences")-1, 1, (SOPC_Byte*) "HierarchicalReferences"}},
            .Description = {{0, 0, NULL}, {0, 0, NULL}},
            .NoOfReferences = 1,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 45},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 31}, {0, 0, NULL}, 0},
                }
            },
        }}
    },
    {
        OpcUa_NodeClass_ReferenceType,
        OpcUa_UncertainInitialValue,
        {0, 0},
        {.reference_type={
            .encodeableType = &OpcUa_ReferenceTypeNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 34},
            .NodeClass = OpcUa_NodeClass_ReferenceType,
            .BrowseName = {0, {sizeof("HasChild")-1, 1, (SOPC_Byte*) "HasChild"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("HasChild")-1, 1, (SOPC_Byte*) "HasChild"}},
            .Description = {{0, 0, NULL}, {0, 0, NULL}},
            .NoOfReferences = 1,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 45},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 33}, {0, 0, NULL}, 0},
                }
            },
        }}
    },
    {
        OpcUa_NodeClass_ReferenceType,
        OpcUa_UncertainInitialValue,
        {0, 0},
        {.reference_type={
            .encodeableType = &OpcUa_ReferenceTypeNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 35},
            .NodeClass = OpcUa_NodeClass_ReferenceType,
            .BrowseName = {0, {sizeof("Organizes")-1, 1, (SOPC_Byte*) "Organizes"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("Organizes")-1, 1, (SOPC_Byte*) "Organizes"}},
            .Description = {{0, 0, NULL}, {0, 0, NULL}},
            .NoOfReferences = 1,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 45},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 33}, {0, 0, NULL}, 0},
                }
            },
        }}
    },
    {
        OpcUa_NodeClass_ReferenceType,
        OpcUa_UncertainInitialValue,
        {0, 0},
        {.reference_type={
            .encodeableType = &OpcUa_ReferenceTypeNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 39},
            .NodeClass = OpcUa_NodeClass_ReferenceType,
            .BrowseName = {0, {sizeof("HasDescription")-1, 1, (SOPC_Byte*) "HasDescription"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("HasDescription")-1, 1, (SOPC_Byte*) "HasDescription"}},
            .Description = {{0, 0, NULL}, {sizeof("The type for references from data type encoding nodes to data type description nodes.")-1, 1, (SOPC_Byte*) "The type for references from data type encoding nodes to data type description nodes."}},
            .NoOfReferences = 1,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 45},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 32}, {0, 0, NULL}, 0},
                }
            },
        }}
    },
    {
        OpcUa_NodeClass_ReferenceType,
        OpcUa_UncertainInitialValue,
        {0, 0},
        {.reference_type={
            .encodeableType = &OpcUa_ReferenceTypeNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 40},
            .NodeClass = OpcUa_NodeClass_ReferenceType,
            .BrowseName = {0, {sizeof("HasTypeDefinition")-1, 1, (SOPC_Byte*) "HasTypeDefinition"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("HasTypeDefinition")-1, 1, (SOPC_Byte*) "HasTypeDefinition"}},
            .Description = {{0, 0, NULL}, {sizeof("The type for references from a instance node its type definition node.")-1, 1, (SOPC_Byte*) "The type for references from a instance node its type definition node."}},
            .NoOfReferences = 1,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 45},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 32}, {0, 0, NULL}, 0},
                }
            },
        }}
    },
    {
        OpcUa_NodeClass_ReferenceType,
        OpcUa_UncertainInitialValue,
        {0, 0},
        {.reference_type={
            .encodeableType = &OpcUa_ReferenceTypeNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 44},
            .NodeClass = OpcUa_NodeClass_ReferenceType,
            .BrowseName = {0, {sizeof("Aggregates")-1, 1, (SOPC_Byte*) "Aggregates"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("Aggregates")-1, 1, (SOPC_Byte*) "Aggregates"}},
            .Description = {{0, 0, NULL}, {0, 0, NULL}},
            .NoOfReferences = 1,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 45},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 34}, {0, 0, NULL}, 0},
                }
            },
        }}
    },
    {
        OpcUa_NodeClass_ReferenceType,
        OpcUa_UncertainInitialValue,
        {0, 0},
        {.reference_type={
            .encodeableType = &OpcUa_ReferenceTypeNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 46},
            .NodeClass = OpcUa_NodeClass_ReferenceType,
            .BrowseName = {0, {sizeof("HasProperty")-1, 1, (SOPC_Byte*) "HasProperty"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("HasProperty")-1, 1, (SOPC_Byte*) "HasProperty"}},
            .Description = {{0, 0, NULL}, {0, 0, NULL}},
            .NoOfReferences = 1,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 45},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 44}, {0, 0, NULL}, 0},
                }
            },
        }}
    },
    {
        OpcUa_NodeClass_ReferenceType,
        OpcUa_UncertainInitialValue,
        {0, 0},
        {.reference_type={
            .encodeableType = &OpcUa_ReferenceTypeNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 47},
            .NodeClass = OpcUa_NodeClass_ReferenceType,
            .BrowseName = {0, {sizeof("HasComponent")-1, 1, (SOPC_Byte*) "HasComponent"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("HasComponent")-1, 1, (SOPC_Byte*) "HasComponent"}},
            .Description = {{0, 0, NULL}, {0, 0, NULL}},
            .NoOfReferences = 1,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 45},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 44}, {0, 0, NULL}, 0},
                }
            },
        }}
    },
    {
        OpcUa_NodeClass_VariableType,
        0x00,
        {0, 0},
        {.variable_type={
            .encodeableType = &OpcUa_VariableTypeNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 68},
            .NodeClass = OpcUa_NodeClass_VariableType,
            .BrowseName = {0, {sizeof("PropertyType")-1, 1, (SOPC_Byte*) "PropertyType"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("PropertyType")-1, 1, (SOPC_Byte*) "PropertyType"}},
            .Description = {{0, 0, NULL}, {sizeof("The type for variable that represents a property of another node.")-1, 1, (SOPC_Byte*) "The type for variable that represents a property of another node."}},
            .NoOfReferences = 1,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 45},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 62}, {0, 0, NULL}, 0},
                }
            },
            .Value = {true, SOPC_Null_Id, SOPC_VariantArrayType_SingleValue, {0}},
            .DataType = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 0},
            .ValueRank = (-2),
        }}
    },
    {
        OpcUa_NodeClass_ObjectType,
        OpcUa_UncertainInitialValue,
        {0, 0},
        {.object_type={
            .encodeableType = &OpcUa_ObjectTypeNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 77},
            .NodeClass = OpcUa_NodeClass_ObjectType,
            .BrowseName = {0, {sizeof("ModellingRuleType")-1, 1, (SOPC_Byte*) "ModellingRuleType"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("ModellingRuleType")-1, 1, (SOPC_Byte*) "ModellingRuleType"}},
            .Description = {{0, 0, NULL}, {0, 0, NULL}},
            .NoOfReferences = 1,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 45},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 58}, {0, 0, NULL}, 0},
                }
            },
        }}
    },
    {
        OpcUa_NodeClass_Object,
        OpcUa_UncertainInitialValue,
        {0, 0},
        {.object={
            .encodeableType = &OpcUa_ObjectNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 78},
            .NodeClass = OpcUa_NodeClass_Object,
            .BrowseName = {0, {sizeof("Mandatory")-1, 1, (SOPC_Byte*) "Mandatory"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("Mandatory")-1, 1, (SOPC_Byte*) "Mandatory"}},
            .Description = {{0, 0, NULL}, {0, 0, NULL}},
            .NoOfReferences = 1,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 40},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 77}, {0, 0, NULL}, 0},
                }
            },
        }}
    },
    {
        OpcUa_NodeClass_Object,
        OpcUa_UncertainInitialValue,
        {0, 0},
        {.object={
            .encodeableType = &OpcUa_ObjectNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 80},
            .NodeClass = OpcUa_NodeClass_Object,
            .BrowseName = {0, {sizeof("Optional")-1, 1, (SOPC_Byte*) "Optional"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("Optional")-1, 1, (SOPC_Byte*) "Optional"}},
            .Description = {{0, 0, NULL}, {0, 0, NULL}},
            .NoOfReferences = 1,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 40},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 77}, {0, 0, NULL}, 0},
                }
            },
        }}
    },
    {
        OpcUa_NodeClass_DataType,
        OpcUa_UncertainInitialValue,
        {0, 0},
        {.data_type={
            .encodeableType = &OpcUa_DataTypeNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 295},
            .NodeClass = OpcUa_NodeClass_DataType,
            .BrowseName = {0, {sizeof("LocaleId")-1, 1, (SOPC_Byte*) "LocaleId"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("LocaleId")-1, 1, (SOPC_Byte*) "LocaleId"}},
            .Description = {{0, 0, NULL}, {sizeof("An identifier for a user locale.")-1, 1, (SOPC_Byte*) "An identifier for a user locale."}},
            .NoOfReferences = 1,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 45},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 12}, {0, 0, NULL}, 0},
                }
            },
        }}
    },
    {
        OpcUa_NodeClass_DataType,
        OpcUa_UncertainInitialValue,
        {0, 0},
        {.data_type={
            .encodeableType = &OpcUa_DataTypeNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 121},
            .NodeClass = OpcUa_NodeClass_DataType,
            .BrowseName = {0, {sizeof("Decimal128")-1, 1, (SOPC_Byte*) "Decimal128"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("Decimal128")-1, 1, (SOPC_Byte*) "Decimal128"}},
            .Description = {{0, 0, NULL}, {sizeof("Describes a 128-bit decimal value.")-1, 1, (SOPC_Byte*) "Describes a 128-bit decimal value."}},
            .NoOfReferences = 1,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 45},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 26}, {0, 0, NULL}, 0},
                }
            },
        }}
    },
    {
        OpcUa_NodeClass_VariableType,
        0x00,
        {0, 0},
        {.variable_type={
            .encodeableType = &OpcUa_VariableTypeNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 2365},
            .NodeClass = OpcUa_NodeClass_VariableType,
            .BrowseName = {0, {sizeof("DataItemType")-1, 1, (SOPC_Byte*) "DataItemType"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("DataItemType")-1, 1, (SOPC_Byte*) "DataItemType"}},
            .Description = {{0, 0, NULL}, {0, 0, NULL}},
            .NoOfReferences = 3,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 46},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 2366}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 46},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 2367}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 45},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 63}, {0, 0, NULL}, 0},
                }
            },
            .Value = {true, SOPC_Null_Id, SOPC_VariantArrayType_SingleValue, {0}},
            .DataType = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 0},
            .ValueRank = (-2),
        }}
    },
    {
        OpcUa_NodeClass_Variable,
        0x00,
        {0, 0},
        {.variable={
            .encodeableType = &OpcUa_VariableNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 2366},
            .NodeClass = OpcUa_NodeClass_Variable,
            .BrowseName = {0, {sizeof("Definition")-1, 1, (SOPC_Byte*) "Definition"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("Definition")-1, 1, (SOPC_Byte*) "Definition"}},
            .Description = {{0, 0, NULL}, {0, 0, NULL}},
            .NoOfReferences = 3,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 40},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 68}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 37},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 80}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 46},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 2365}, {0, 0, NULL}, 0},
                }
            },
            .Value = 
                  {true,
                   SOPC_UInt32_Id,
                   SOPC_VariantArrayType_SingleValue,
                   {.Uint32 = 0}},
            .DataType = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 12},
            .ValueRank = (-1),
            .AccessLevel = 1,
        }}
    },
    {
        OpcUa_NodeClass_Variable,
        0x00,
        {0, 0},
        {.variable={
            .encodeableType = &OpcUa_VariableNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 2367},
            .NodeClass = OpcUa_NodeClass_Variable,
            .BrowseName = {0, {sizeof("ValuePrecision")-1, 1, (SOPC_Byte*) "ValuePrecision"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("ValuePrecision")-1, 1, (SOPC_Byte*) "ValuePrecision"}},
            .Description = {{0, 0, NULL}, {0, 0, NULL}},
            .NoOfReferences = 3,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 40},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 68}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 37},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 80}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 46},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 2365}, {0, 0, NULL}, 0},
                }
            },
            .Value = 
                  {true,
                   SOPC_UInt32_Id,
                   SOPC_VariantArrayType_SingleValue,
                   {.Uint32 = 1}},
            .DataType = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 11},
            .ValueRank = (-1),
            .AccessLevel = 1,
        }}
    },
    {
        OpcUa_NodeClass_VariableType,
        0x00,
        {0, 0},
        {.variable_type={
            .encodeableType = &OpcUa_VariableTypeNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 2368},
            .NodeClass = OpcUa_NodeClass_VariableType,
            .BrowseName = {0, {sizeof("AnalogItemType")-1, 1, (SOPC_Byte*) "AnalogItemType"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("AnalogItemType")-1, 1, (SOPC_Byte*) "AnalogItemType"}},
            .Description = {{0, 0, NULL}, {0, 0, NULL}},
            .NoOfReferences = 4,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 46},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 2370}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 46},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 2369}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 46},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 2371}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 45},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 2365}, {0, 0, NULL}, 0},
                }
            },
            .Value = {true, SOPC_Null_Id, SOPC_VariantArrayType_SingleValue, {0}},
            .DataType = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 26},
            .ValueRank = (-2),
        }}
    },
    {
        OpcUa_NodeClass_Variable,
        0x00,
        {0, 0},
        {.variable={
            .encodeableType = &OpcUa_VariableNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 2370},
            .NodeClass = OpcUa_NodeClass_Variable,
            .BrowseName = {0, {sizeof("InstrumentRange")-1, 1, (SOPC_Byte*) "InstrumentRange"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("InstrumentRange")-1, 1, (SOPC_Byte*) "InstrumentRange"}},
            .Description = {{0, 0, NULL}, {0, 0, NULL}},
            .NoOfReferences = 3,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 40},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 68}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 37},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 80}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 46},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 2368}, {0, 0, NULL}, 0},
                }
            },
            .Value = 
                  {true,
                   SOPC_UInt32_Id,
                   SOPC_VariantArrayType_SingleValue,
                   {.Uint32 = 2}},
            .DataType = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 884},
            .ValueRank = (-1),
            .AccessLevel = 1,
        }}
    },
    {
        OpcUa_NodeClass_Variable,
        0x00,
        {0, 0},
        {.variable={
            .encodeableType = &OpcUa_VariableNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 2369},
            .NodeClass = OpcUa_NodeClass_Variable,
            .BrowseName = {0, {sizeof("EURange")-1, 1, (SOPC_Byte*) "EURange"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("EURange")-1, 1, (SOPC_Byte*) "EURange"}},
            .Description = {{0, 0, NULL}, {0, 0, NULL}},
            .NoOfReferences = 3,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 40},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 68}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 37},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 78}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 46},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 2368}, {0, 0, NULL}, 0},
                }
            },
            .Value = 
                  {true,
                   SOPC_UInt32_Id,
                   SOPC_VariantArrayType_SingleValue,
                   {.Uint32 = 3}},
            .DataType = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 884},
            .ValueRank = (-1),
            .AccessLevel = 1,
        }}
    },
    {
        OpcUa_NodeClass_Variable,
        0x00,
        {0, 0},
        {.variable={
            .encodeableType = &OpcUa_VariableNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 2371},
            .NodeClass = OpcUa_NodeClass_Variable,
            .BrowseName = {0, {sizeof("EngineeringUnits")-1, 1, (SOPC_Byte*) "EngineeringUnits"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("EngineeringUnits")-1, 1, (SOPC_Byte*) "EngineeringUnits"}},
            .Description = {{0, 0, NULL}, {0, 0, NULL}},
            .NoOfReferences = 3,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 40},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 68}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 37},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 80}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 46},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 2368}, {0, 0, NULL}, 0},
                }
            },
            .Value = 
                  {true,
                   SOPC_UInt32_Id,
                   SOPC_VariantArrayType_SingleValue,
                   {.Uint32 = 4}},
            .DataType = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 887},
            .ValueRank = (-1),
            .AccessLevel = 1,
        }}
    },
    {
        OpcUa_NodeClass_ObjectType,
        OpcUa_UncertainInitialValue,
        {0, 0},
        {.object_type={
            .encodeableType = &OpcUa_ObjectTypeNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 58},
            .NodeClass = OpcUa_NodeClass_ObjectType,
            .BrowseName = {0, {sizeof("BaseObjectType")-1, 1, (SOPC_Byte*) "BaseObjectType"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("BaseObjectType")-1, 1, (SOPC_Byte*) "BaseObjectType"}},
            .Description = {{0, 0, NULL}, {sizeof("The base type for all object nodes.")-1, 1, (SOPC_Byte*) "The base type for all object nodes."}},
            .NoOfReferences = 0,
            .References = NULL,
        }}
    },
    {
        OpcUa_NodeClass_ObjectType,
        OpcUa_UncertainInitialValue,
        {0, 0},
        {.object_type={
            .encodeableType = &OpcUa_ObjectTypeNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 61},
            .NodeClass = OpcUa_NodeClass_ObjectType,
            .BrowseName = {0, {sizeof("FolderType")-1, 1, (SOPC_Byte*) "FolderType"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("FolderType")-1, 1, (SOPC_Byte*) "FolderType"}},
            .Description = {{0, 0, NULL}, {sizeof("The type for objects that organize other nodes.")-1, 1, (SOPC_Byte*) "The type for objects that organize other nodes."}},
            .NoOfReferences = 1,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 45},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 58}, {0, 0, NULL}, 0},
                }
            },
        }}
    },
    {
        OpcUa_NodeClass_VariableType,
        0x00,
        {0, 0},
        {.variable_type={
            .encodeableType = &OpcUa_VariableTypeNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 62},
            .NodeClass = OpcUa_NodeClass_VariableType,
            .BrowseName = {0, {sizeof("BaseVariableType")-1, 1, (SOPC_Byte*) "BaseVariableType"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("BaseVariableType")-1, 1, (SOPC_Byte*) "BaseVariableType"}},
            .Description = {{0, 0, NULL}, {sizeof("The abstract base type for all variable nodes.")-1, 1, (SOPC_Byte*) "The abstract base type for all variable nodes."}},
            .NoOfReferences = 2,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 45},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 63}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 45},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 68}, {0, 0, NULL}, 0},
                }
            },
            .Value = {true, SOPC_Null_Id, SOPC_VariantArrayType_SingleValue, {0}},
            .DataType = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 0},
            .ValueRank = (-2),
        }}
    },
    {
        OpcUa_NodeClass_VariableType,
        0x00,
        {0, 0},
        {.variable_type={
            .encodeableType = &OpcUa_VariableTypeNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 63},
            .NodeClass = OpcUa_NodeClass_VariableType,
            .BrowseName = {0, {sizeof("BaseDataVariableType")-1, 1, (SOPC_Byte*) "BaseDataVariableType"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("BaseDataVariableType")-1, 1, (SOPC_Byte*) "BaseDataVariableType"}},
            .Description = {{0, 0, NULL}, {sizeof("The type for variable that represents a process value.")-1, 1, (SOPC_Byte*) "The type for variable that represents a process value."}},
            .NoOfReferences = 2,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 45},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 62}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 45},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 3051}, {0, 0, NULL}, 0},
                }
            },
            .Value = {true, SOPC_Null_Id, SOPC_VariantArrayType_SingleValue, {0}},
            .DataType = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 0},
            .ValueRank = (-2),
        }}
    },
    {
        OpcUa_NodeClass_DataType,
        OpcUa_UncertainInitialValue,
        {0, 0},
        {.data_type={
            .encodeableType = &OpcUa_DataTypeNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 884},
            .NodeClass = OpcUa_NodeClass_DataType,
            .BrowseName = {0, {sizeof("Range")-1, 1, (SOPC_Byte*) "Range"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("Range")-1, 1, (SOPC_Byte*) "Range"}},
            .Description = {{0, 0, NULL}, {0, 0, NULL}},
            .NoOfReferences = 1,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 45},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 22}, {0, 0, NULL}, 0},
                }
            },
        }}
    },
    {
        OpcUa_NodeClass_Object,
        OpcUa_UncertainInitialValue,
        {0, 0},
        {.object={
            .encodeableType = &OpcUa_ObjectNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 84},
            .NodeClass = OpcUa_NodeClass_Object,
            .BrowseName = {0, {sizeof("Root")-1, 1, (SOPC_Byte*) "Root"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("Root")-1, 1, (SOPC_Byte*) "Root"}},
            .Description = {{0, 0, NULL}, {sizeof("The root of the server address space.")-1, 1, (SOPC_Byte*) "The root of the server address space."}},
            .NoOfReferences = 4,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 35},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 85}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 35},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 86}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 35},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 87}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 40},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 61}, {0, 0, NULL}, 0},
                }
            },
        }}
    },
    {
        OpcUa_NodeClass_Object,
        OpcUa_UncertainInitialValue,
        {0, 0},
        {.object={
            .encodeableType = &OpcUa_ObjectNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 85},
            .NodeClass = OpcUa_NodeClass_Object,
            .BrowseName = {0, {sizeof("Objects")-1, 1, (SOPC_Byte*) "Objects"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("Objects")-1, 1, (SOPC_Byte*) "Objects"}},
            .Description = {{0, 0, NULL}, {sizeof("The browse entry point when looking for objects in the server address space.")-1, 1, (SOPC_Byte*) "The browse entry point when looking for objects in the server address space."}},
            .NoOfReferences = 7,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 35},
                    false,
                    {{SOPC_IdentifierType_String, 1, .Data.String = {sizeof("InESObjects")-1, 1, (SOPC_Byte*) "InESObjects"}}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 35},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 2253}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 47},
                    false,
                    {{SOPC_IdentifierType_String, 1, .Data.String = {sizeof("PubSubStatus")-1, 1, (SOPC_Byte*) "PubSubStatus"}}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 47},
                    false,
                    {{SOPC_IdentifierType_String, 1, .Data.String = {sizeof("PubSubConfiguration")-1, 1, (SOPC_Byte*) "PubSubConfiguration"}}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 47},
                    false,
                    {{SOPC_IdentifierType_String, 1, .Data.String = {sizeof("PubSubStartStop")-1, 1, (SOPC_Byte*) "PubSubStartStop"}}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 35},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 84}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 40},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 61}, {0, 0, NULL}, 0},
                }
            },
        }}
    },
    {
        OpcUa_NodeClass_Object,
        OpcUa_UncertainInitialValue,
        {0, 0},
        {.object={
            .encodeableType = &OpcUa_ObjectNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 86},
            .NodeClass = OpcUa_NodeClass_Object,
            .BrowseName = {0, {sizeof("Types")-1, 1, (SOPC_Byte*) "Types"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("Types")-1, 1, (SOPC_Byte*) "Types"}},
            .Description = {{0, 0, NULL}, {sizeof("The browse entry point when looking for types in the server address space.")-1, 1, (SOPC_Byte*) "The browse entry point when looking for types in the server address space."}},
            .NoOfReferences = 6,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 35},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 84}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 35},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 88}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 35},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 89}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 35},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 90}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 35},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 91}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 40},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 61}, {0, 0, NULL}, 0},
                }
            },
        }}
    },
    {
        OpcUa_NodeClass_Object,
        OpcUa_UncertainInitialValue,
        {0, 0},
        {.object={
            .encodeableType = &OpcUa_ObjectNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 87},
            .NodeClass = OpcUa_NodeClass_Object,
            .BrowseName = {0, {sizeof("Views")-1, 1, (SOPC_Byte*) "Views"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("Views")-1, 1, (SOPC_Byte*) "Views"}},
            .Description = {{0, 0, NULL}, {sizeof("The browse entry point when looking for views in the server address space.")-1, 1, (SOPC_Byte*) "The browse entry point when looking for views in the server address space."}},
            .NoOfReferences = 2,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 35},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 84}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 40},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 61}, {0, 0, NULL}, 0},
                }
            },
        }}
    },
    {
        OpcUa_NodeClass_Object,
        OpcUa_UncertainInitialValue,
        {0, 0},
        {.object={
            .encodeableType = &OpcUa_ObjectNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 88},
            .NodeClass = OpcUa_NodeClass_Object,
            .BrowseName = {0, {sizeof("ObjectTypes")-1, 1, (SOPC_Byte*) "ObjectTypes"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("ObjectTypes")-1, 1, (SOPC_Byte*) "ObjectTypes"}},
            .Description = {{0, 0, NULL}, {sizeof("The browse entry point when looking for object types in the server address space.")-1, 1, (SOPC_Byte*) "The browse entry point when looking for object types in the server address space."}},
            .NoOfReferences = 3,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 35},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 86}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 35},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 58}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 40},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 61}, {0, 0, NULL}, 0},
                }
            },
        }}
    },
    {
        OpcUa_NodeClass_Object,
        OpcUa_UncertainInitialValue,
        {0, 0},
        {.object={
            .encodeableType = &OpcUa_ObjectNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 89},
            .NodeClass = OpcUa_NodeClass_Object,
            .BrowseName = {0, {sizeof("VariableTypes")-1, 1, (SOPC_Byte*) "VariableTypes"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("VariableTypes")-1, 1, (SOPC_Byte*) "VariableTypes"}},
            .Description = {{0, 0, NULL}, {sizeof("The browse entry point when looking for variable types in the server address space.")-1, 1, (SOPC_Byte*) "The browse entry point when looking for variable types in the server address space."}},
            .NoOfReferences = 3,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 35},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 86}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 35},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 62}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 40},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 61}, {0, 0, NULL}, 0},
                }
            },
        }}
    },
    {
        OpcUa_NodeClass_Object,
        OpcUa_UncertainInitialValue,
        {0, 0},
        {.object={
            .encodeableType = &OpcUa_ObjectNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 90},
            .NodeClass = OpcUa_NodeClass_Object,
            .BrowseName = {0, {sizeof("DataTypes")-1, 1, (SOPC_Byte*) "DataTypes"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("DataTypes")-1, 1, (SOPC_Byte*) "DataTypes"}},
            .Description = {{0, 0, NULL}, {sizeof("The browse entry point when looking for data types in the server address space.")-1, 1, (SOPC_Byte*) "The browse entry point when looking for data types in the server address space."}},
            .NoOfReferences = 30,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 35},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 86}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 35},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 24}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 35},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 26}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 35},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 27}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 35},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 28}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 35},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 29}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 35},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 1}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 35},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 2}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 35},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 3}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 35},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 4}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 35},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 5}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 35},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 6}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 35},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 7}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 35},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 8}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 35},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 9}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 35},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 10}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 35},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 11}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 35},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 12}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 35},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 13}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 35},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 14}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 35},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 15}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 35},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 16}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 35},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 17}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 35},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 18}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 35},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 19}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 35},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 20}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 35},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 21}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 35},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 22}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 35},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 23}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 40},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 61}, {0, 0, NULL}, 0},
                }
            },
        }}
    },
    {
        OpcUa_NodeClass_Object,
        OpcUa_UncertainInitialValue,
        {0, 0},
        {.object={
            .encodeableType = &OpcUa_ObjectNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 91},
            .NodeClass = OpcUa_NodeClass_Object,
            .BrowseName = {0, {sizeof("ReferenceTypes")-1, 1, (SOPC_Byte*) "ReferenceTypes"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("ReferenceTypes")-1, 1, (SOPC_Byte*) "ReferenceTypes"}},
            .Description = {{0, 0, NULL}, {sizeof("The browse entry point when looking for reference types in the server address space.")-1, 1, (SOPC_Byte*) "The browse entry point when looking for reference types in the server address space."}},
            .NoOfReferences = 3,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 35},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 86}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 35},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 31}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 40},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 61}, {0, 0, NULL}, 0},
                }
            },
        }}
    },
    {
        OpcUa_NodeClass_ObjectType,
        OpcUa_UncertainInitialValue,
        {0, 0},
        {.object_type={
            .encodeableType = &OpcUa_ObjectTypeNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 2013},
            .NodeClass = OpcUa_NodeClass_ObjectType,
            .BrowseName = {0, {sizeof("ServerCapabilitiesType")-1, 1, (SOPC_Byte*) "ServerCapabilitiesType"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("ServerCapabilitiesType")-1, 1, (SOPC_Byte*) "ServerCapabilitiesType"}},
            .Description = {{0, 0, NULL}, {sizeof("Describes the capabilities supported by the server.")-1, 1, (SOPC_Byte*) "Describes the capabilities supported by the server."}},
            .NoOfReferences = 1,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 45},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 58}, {0, 0, NULL}, 0},
                }
            },
        }}
    },
    {
        OpcUa_NodeClass_Object,
        OpcUa_UncertainInitialValue,
        {0, 0},
        {.object={
            .encodeableType = &OpcUa_ObjectNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 2268},
            .NodeClass = OpcUa_NodeClass_Object,
            .BrowseName = {0, {sizeof("ServerCapabilities")-1, 1, (SOPC_Byte*) "ServerCapabilities"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("ServerCapabilities")-1, 1, (SOPC_Byte*) "ServerCapabilities"}},
            .Description = {{0, 0, NULL}, {sizeof("Describes capabilities supported by the server.")-1, 1, (SOPC_Byte*) "Describes capabilities supported by the server."}},
            .NoOfReferences = 3,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 46},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 2271}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 40},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 2013}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 47},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 2253}, {0, 0, NULL}, 0},
                }
            },
        }}
    },
    {
        OpcUa_NodeClass_Variable,
        0x00,
        {0, 0},
        {.variable={
            .encodeableType = &OpcUa_VariableNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 2271},
            .NodeClass = OpcUa_NodeClass_Variable,
            .BrowseName = {0, {sizeof("LocaleIdArray")-1, 1, (SOPC_Byte*) "LocaleIdArray"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("LocaleIdArray")-1, 1, (SOPC_Byte*) "LocaleIdArray"}},
            .Description = {{0, 0, NULL}, {sizeof("A list of locales supported by the server.")-1, 1, (SOPC_Byte*) "A list of locales supported by the server."}},
            .NoOfReferences = 2,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 40},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 68}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 46},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 2268}, {0, 0, NULL}, 0},
                }
            },
            .Value = 
                  {true,
                   SOPC_UInt32_Id,
                   SOPC_VariantArrayType_SingleValue,
                   {.Uint32 = 5}},
            .DataType = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 295},
            .ValueRank = (1),
            .AccessLevel = 1,
        }}
    },
    {
        OpcUa_NodeClass_Object,
        OpcUa_UncertainInitialValue,
        {0, 0},
        {.object={
            .encodeableType = &OpcUa_ObjectNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 2253},
            .NodeClass = OpcUa_NodeClass_Object,
            .BrowseName = {0, {sizeof("Server")-1, 1, (SOPC_Byte*) "Server"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("Server")-1, 1, (SOPC_Byte*) "Server"}},
            .Description = {{0, 0, NULL}, {sizeof("Describes this OPC-UA Server")-1, 1, (SOPC_Byte*) "Describes this OPC-UA Server"}},
            .NoOfReferences = 10,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 46},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 2254}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 46},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 2255}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 47},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 2256}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 46},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 2267}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 47},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 2268}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 47},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 2274}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 46},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 2994}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 35},
                    false,
                    {{SOPC_IdentifierType_String, 1, .Data.String = {sizeof("InESObjects")-1, 1, (SOPC_Byte*) "InESObjects"}}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 35},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 85}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 40},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 61}, {0, 0, NULL}, 0},
                }
            },
        }}
    },
    {
        OpcUa_NodeClass_Variable,
        0x00,
        {0, 0},
        {.variable={
            .encodeableType = &OpcUa_VariableNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 2254},
            .NodeClass = OpcUa_NodeClass_Variable,
            .BrowseName = {0, {sizeof("ServerArray")-1, 1, (SOPC_Byte*) "ServerArray"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("ServerArray")-1, 1, (SOPC_Byte*) "ServerArray"}},
            .Description = {{0, 0, NULL}, {sizeof("List of servers accessible from this server.")-1, 1, (SOPC_Byte*) "List of servers accessible from this server."}},
            .NoOfReferences = 2,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 40},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 68}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 46},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 2253}, {0, 0, NULL}, 0},
                }
            },
            .Value = 
                  {true,
                   SOPC_UInt32_Id,
                   SOPC_VariantArrayType_SingleValue,
                   {.Uint32 = 6}},
            .DataType = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 12},
            .ValueRank = (1),
            .AccessLevel = 1,
        }}
    },
    {
        OpcUa_NodeClass_Variable,
        0x00,
        {0, 0},
        {.variable={
            .encodeableType = &OpcUa_VariableNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 2255},
            .NodeClass = OpcUa_NodeClass_Variable,
            .BrowseName = {0, {sizeof("NamespaceArray")-1, 1, (SOPC_Byte*) "NamespaceArray"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("NamespaceArray")-1, 1, (SOPC_Byte*) "NamespaceArray"}},
            .Description = {{0, 0, NULL}, {sizeof("List of namespace on this server.")-1, 1, (SOPC_Byte*) "List of namespace on this server."}},
            .NoOfReferences = 2,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 40},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 68}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 46},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 2253}, {0, 0, NULL}, 0},
                }
            },
            .Value = 
                  {true,
                   SOPC_UInt32_Id,
                   SOPC_VariantArrayType_SingleValue,
                   {.Uint32 = 7}},
            .DataType = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 12},
            .ValueRank = (1),
            .AccessLevel = 1,
        }}
    },
    {
        OpcUa_NodeClass_Variable,
        0x00,
        {0, 0},
        {.variable={
            .encodeableType = &OpcUa_VariableNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 2256},
            .NodeClass = OpcUa_NodeClass_Variable,
            .BrowseName = {0, {sizeof("ServerStatus")-1, 1, (SOPC_Byte*) "ServerStatus"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("ServerStatus")-1, 1, (SOPC_Byte*) "ServerStatus"}},
            .Description = {{0, 0, NULL}, {sizeof("Describes the status of this server")-1, 1, (SOPC_Byte*) "Describes the status of this server"}},
            .NoOfReferences = 6,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 47},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 2257}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 47},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 2258}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 47},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 2259}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 47},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 2260}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 47},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 2253}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 40},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 63}, {0, 0, NULL}, 0},
                }
            },
            .Value = 
                  {true,
                   SOPC_UInt32_Id,
                   SOPC_VariantArrayType_SingleValue,
                   {.Uint32 = 8}},
            .DataType = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 862},
            .ValueRank = (-1),
            .AccessLevel = 1,
        }}
    },
    {
        OpcUa_NodeClass_Variable,
        0x00,
        {0, 0},
        {.variable={
            .encodeableType = &OpcUa_VariableNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 2257},
            .NodeClass = OpcUa_NodeClass_Variable,
            .BrowseName = {0, {sizeof("StartTime")-1, 1, (SOPC_Byte*) "StartTime"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("StartTime")-1, 1, (SOPC_Byte*) "StartTime"}},
            .Description = {{0, 0, NULL}, {0, 0, NULL}},
            .NoOfReferences = 2,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 47},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 2256}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 40},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 63}, {0, 0, NULL}, 0},
                }
            },
            .Value = 
                  {true,
                   SOPC_UInt32_Id,
                   SOPC_VariantArrayType_SingleValue,
                   {.Uint32 = 9}},
            .DataType = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 13},
            .ValueRank = (-1),
            .AccessLevel = 1,
        }}
    },
    {
        OpcUa_NodeClass_Variable,
        0x00,
        {0, 0},
        {.variable={
            .encodeableType = &OpcUa_VariableNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 2258},
            .NodeClass = OpcUa_NodeClass_Variable,
            .BrowseName = {0, {sizeof("CurrentTime")-1, 1, (SOPC_Byte*) "CurrentTime"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("CurrentTime")-1, 1, (SOPC_Byte*) "CurrentTime"}},
            .Description = {{0, 0, NULL}, {0, 0, NULL}},
            .NoOfReferences = 2,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 47},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 2256}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 40},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 63}, {0, 0, NULL}, 0},
                }
            },
            .Value = 
                  {true,
                   SOPC_UInt32_Id,
                   SOPC_VariantArrayType_SingleValue,
                   {.Uint32 = 10}},
            .DataType = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 13},
            .ValueRank = (-1),
            .AccessLevel = 1,
        }}
    },
    {
        OpcUa_NodeClass_Variable,
        0x00,
        {0, 0},
        {.variable={
            .encodeableType = &OpcUa_VariableNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 2259},
            .NodeClass = OpcUa_NodeClass_Variable,
            .BrowseName = {0, {sizeof("State")-1, 1, (SOPC_Byte*) "State"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("State")-1, 1, (SOPC_Byte*) "State"}},
            .Description = {{0, 0, NULL}, {0, 0, NULL}},
            .NoOfReferences = 2,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 47},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 2256}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 40},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 63}, {0, 0, NULL}, 0},
                }
            },
            .Value = 
                  {true,
                   SOPC_UInt32_Id,
                   SOPC_VariantArrayType_SingleValue,
                   {.Uint32 = 11}},
            .DataType = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 6},
            .ValueRank = (-1),
            .AccessLevel = 1,
        }}
    },
    {
        OpcUa_NodeClass_Variable,
        0x00,
        {0, 0},
        {.variable={
            .encodeableType = &OpcUa_VariableNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 2260},
            .NodeClass = OpcUa_NodeClass_Variable,
            .BrowseName = {0, {sizeof("BuildInfo")-1, 1, (SOPC_Byte*) "BuildInfo"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("BuildInfo")-1, 1, (SOPC_Byte*) "BuildInfo"}},
            .Description = {{0, 0, NULL}, {0, 0, NULL}},
            .NoOfReferences = 8,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 47},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 2261}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 47},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 2262}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 47},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 2263}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 47},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 2264}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 47},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 2265}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 47},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 2266}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 47},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 2256}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 40},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 3051}, {0, 0, NULL}, 0},
                }
            },
            .Value = 
                  {true,
                   SOPC_UInt32_Id,
                   SOPC_VariantArrayType_SingleValue,
                   {.Uint32 = 12}},
            .DataType = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 338},
            .ValueRank = (-1),
            .AccessLevel = 1,
        }}
    },
    {
        OpcUa_NodeClass_Variable,
        0x00,
        {0, 0},
        {.variable={
            .encodeableType = &OpcUa_VariableNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 2261},
            .NodeClass = OpcUa_NodeClass_Variable,
            .BrowseName = {0, {sizeof("ProductName")-1, 1, (SOPC_Byte*) "ProductName"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("ProductName")-1, 1, (SOPC_Byte*) "ProductName"}},
            .Description = {{0, 0, NULL}, {0, 0, NULL}},
            .NoOfReferences = 2,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 47},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 2260}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 40},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 63}, {0, 0, NULL}, 0},
                }
            },
            .Value = 
                  {true,
                   SOPC_UInt32_Id,
                   SOPC_VariantArrayType_SingleValue,
                   {.Uint32 = 13}},
            .DataType = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 12},
            .ValueRank = (-1),
            .AccessLevel = 1,
        }}
    },
    {
        OpcUa_NodeClass_Variable,
        0x00,
        {0, 0},
        {.variable={
            .encodeableType = &OpcUa_VariableNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 2262},
            .NodeClass = OpcUa_NodeClass_Variable,
            .BrowseName = {0, {sizeof("ProductUri")-1, 1, (SOPC_Byte*) "ProductUri"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("ProductUri")-1, 1, (SOPC_Byte*) "ProductUri"}},
            .Description = {{0, 0, NULL}, {0, 0, NULL}},
            .NoOfReferences = 2,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 47},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 2260}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 40},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 63}, {0, 0, NULL}, 0},
                }
            },
            .Value = 
                  {true,
                   SOPC_UInt32_Id,
                   SOPC_VariantArrayType_SingleValue,
                   {.Uint32 = 14}},
            .DataType = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 12},
            .ValueRank = (-1),
            .AccessLevel = 1,
        }}
    },
    {
        OpcUa_NodeClass_Variable,
        0x00,
        {0, 0},
        {.variable={
            .encodeableType = &OpcUa_VariableNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 2263},
            .NodeClass = OpcUa_NodeClass_Variable,
            .BrowseName = {0, {sizeof("ManufacturerName")-1, 1, (SOPC_Byte*) "ManufacturerName"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("ManufacturerName")-1, 1, (SOPC_Byte*) "ManufacturerName"}},
            .Description = {{0, 0, NULL}, {0, 0, NULL}},
            .NoOfReferences = 2,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 47},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 2260}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 40},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 63}, {0, 0, NULL}, 0},
                }
            },
            .Value = 
                  {true,
                   SOPC_UInt32_Id,
                   SOPC_VariantArrayType_SingleValue,
                   {.Uint32 = 15}},
            .DataType = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 12},
            .ValueRank = (-1),
            .AccessLevel = 1,
        }}
    },
    {
        OpcUa_NodeClass_Variable,
        0x00,
        {0, 0},
        {.variable={
            .encodeableType = &OpcUa_VariableNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 2264},
            .NodeClass = OpcUa_NodeClass_Variable,
            .BrowseName = {0, {sizeof("SoftwareVersion")-1, 1, (SOPC_Byte*) "SoftwareVersion"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("SoftwareVersion")-1, 1, (SOPC_Byte*) "SoftwareVersion"}},
            .Description = {{0, 0, NULL}, {0, 0, NULL}},
            .NoOfReferences = 2,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 47},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 2260}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 40},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 63}, {0, 0, NULL}, 0},
                }
            },
            .Value = 
                  {true,
                   SOPC_UInt32_Id,
                   SOPC_VariantArrayType_SingleValue,
                   {.Uint32 = 16}},
            .DataType = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 12},
            .ValueRank = (-1),
            .AccessLevel = 1,
        }}
    },
    {
        OpcUa_NodeClass_Variable,
        0x00,
        {0, 0},
        {.variable={
            .encodeableType = &OpcUa_VariableNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 2265},
            .NodeClass = OpcUa_NodeClass_Variable,
            .BrowseName = {0, {sizeof("BuildNumber")-1, 1, (SOPC_Byte*) "BuildNumber"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("BuildNumber")-1, 1, (SOPC_Byte*) "BuildNumber"}},
            .Description = {{0, 0, NULL}, {0, 0, NULL}},
            .NoOfReferences = 2,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 47},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 2260}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 40},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 63}, {0, 0, NULL}, 0},
                }
            },
            .Value = 
                  {true,
                   SOPC_UInt32_Id,
                   SOPC_VariantArrayType_SingleValue,
                   {.Uint32 = 17}},
            .DataType = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 12},
            .ValueRank = (-1),
            .AccessLevel = 1,
        }}
    },
    {
        OpcUa_NodeClass_Variable,
        0x00,
        {0, 0},
        {.variable={
            .encodeableType = &OpcUa_VariableNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 2266},
            .NodeClass = OpcUa_NodeClass_Variable,
            .BrowseName = {0, {sizeof("BuildDate")-1, 1, (SOPC_Byte*) "BuildDate"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("BuildDate")-1, 1, (SOPC_Byte*) "BuildDate"}},
            .Description = {{0, 0, NULL}, {0, 0, NULL}},
            .NoOfReferences = 2,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 47},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 2260}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 40},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 63}, {0, 0, NULL}, 0},
                }
            },
            .Value = 
                  {true,
                   SOPC_UInt32_Id,
                   SOPC_VariantArrayType_SingleValue,
                   {.Uint32 = 18}},
            .DataType = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 13},
            .ValueRank = (-1),
            .AccessLevel = 1,
        }}
    },
    {
        OpcUa_NodeClass_Variable,
        0x00,
        {0, 0},
        {.variable={
            .encodeableType = &OpcUa_VariableNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 2267},
            .NodeClass = OpcUa_NodeClass_Variable,
            .BrowseName = {0, {sizeof("ServiceLevel")-1, 1, (SOPC_Byte*) "ServiceLevel"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("ServiceLevel")-1, 1, (SOPC_Byte*) "ServiceLevel"}},
            .Description = {{0, 0, NULL}, {0, 0, NULL}},
            .NoOfReferences = 2,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 46},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 2253}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 40},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 63}, {0, 0, NULL}, 0},
                }
            },
            .Value = 
                  {true,
                   SOPC_UInt32_Id,
                   SOPC_VariantArrayType_SingleValue,
                   {.Uint32 = 19}},
            .DataType = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 3},
            .ValueRank = (-1),
            .AccessLevel = 1,
        }}
    },
    {
        OpcUa_NodeClass_Object,
        OpcUa_UncertainInitialValue,
        {0, 0},
        {.object={
            .encodeableType = &OpcUa_ObjectNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 2274},
            .NodeClass = OpcUa_NodeClass_Object,
            .BrowseName = {0, {sizeof("ServerDiagnostics")-1, 1, (SOPC_Byte*) "ServerDiagnostics"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("ServerDiagnostics")-1, 1, (SOPC_Byte*) "ServerDiagnostics"}},
            .Description = {{0, 0, NULL}, {sizeof("Diagnostic summary of this server")-1, 1, (SOPC_Byte*) "Diagnostic summary of this server"}},
            .NoOfReferences = 2,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 46},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 2294}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 47},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 2253}, {0, 0, NULL}, 0},
                }
            },
        }}
    },
    {
        OpcUa_NodeClass_Variable,
        0x00,
        {0, 0},
        {.variable={
            .encodeableType = &OpcUa_VariableNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 2294},
            .NodeClass = OpcUa_NodeClass_Variable,
            .BrowseName = {0, {sizeof("Enabled")-1, 1, (SOPC_Byte*) "Enabled"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("Enabled")-1, 1, (SOPC_Byte*) "Enabled"}},
            .Description = {{0, 0, NULL}, {0, 0, NULL}},
            .NoOfReferences = 2,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 46},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 2274}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 40},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 63}, {0, 0, NULL}, 0},
                }
            },
            .Value = 
                  {true,
                   SOPC_UInt32_Id,
                   SOPC_VariantArrayType_SingleValue,
                   {.Uint32 = 20}},
            .DataType = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 1},
            .ValueRank = (-1),
            .AccessLevel = 1,
        }}
    },
    {
        OpcUa_NodeClass_Variable,
        0x00,
        {0, 0},
        {.variable={
            .encodeableType = &OpcUa_VariableNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 2994},
            .NodeClass = OpcUa_NodeClass_Variable,
            .BrowseName = {0, {sizeof("Auditing")-1, 1, (SOPC_Byte*) "Auditing"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("Auditing")-1, 1, (SOPC_Byte*) "Auditing"}},
            .Description = {{0, 0, NULL}, {0, 0, NULL}},
            .NoOfReferences = 2,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 46},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 2253}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 40},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 63}, {0, 0, NULL}, 0},
                }
            },
            .Value = 
                  {true,
                   SOPC_UInt32_Id,
                   SOPC_VariantArrayType_SingleValue,
                   {.Uint32 = 21}},
            .DataType = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 1},
            .ValueRank = (-1),
            .AccessLevel = 1,
        }}
    },
    {
        OpcUa_NodeClass_VariableType,
        0x00,
        {0, 0},
        {.variable_type={
            .encodeableType = &OpcUa_VariableTypeNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 3051},
            .NodeClass = OpcUa_NodeClass_VariableType,
            .BrowseName = {0, {sizeof("BuildInfoType")-1, 1, (SOPC_Byte*) "BuildInfoType"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("BuildInfoType")-1, 1, (SOPC_Byte*) "BuildInfoType"}},
            .Description = {{0, 0, NULL}, {0, 0, NULL}},
            .NoOfReferences = 7,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 47},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 3052}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 47},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 3053}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 47},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 3054}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 47},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 3055}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 47},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 3056}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 47},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 3057}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 45},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 63}, {0, 0, NULL}, 0},
                }
            },
            .Value = {true, SOPC_Null_Id, SOPC_VariantArrayType_SingleValue, {0}},
            .DataType = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 338},
            .ValueRank = (-1),
        }}
    },
    {
        OpcUa_NodeClass_Variable,
        0x00,
        {0, 0},
        {.variable={
            .encodeableType = &OpcUa_VariableNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 3052},
            .NodeClass = OpcUa_NodeClass_Variable,
            .BrowseName = {0, {sizeof("ProductUri")-1, 1, (SOPC_Byte*) "ProductUri"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("ProductUri")-1, 1, (SOPC_Byte*) "ProductUri"}},
            .Description = {{0, 0, NULL}, {0, 0, NULL}},
            .NoOfReferences = 2,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 40},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 63}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 47},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 3051}, {0, 0, NULL}, 0},
                }
            },
            .Value = 
                  {true,
                   SOPC_UInt32_Id,
                   SOPC_VariantArrayType_SingleValue,
                   {.Uint32 = 22}},
            .DataType = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 12},
            .ValueRank = (-1),
            .AccessLevel = 1,
        }}
    },
    {
        OpcUa_NodeClass_Variable,
        0x00,
        {0, 0},
        {.variable={
            .encodeableType = &OpcUa_VariableNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 3053},
            .NodeClass = OpcUa_NodeClass_Variable,
            .BrowseName = {0, {sizeof("ManufacturerName")-1, 1, (SOPC_Byte*) "ManufacturerName"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("ManufacturerName")-1, 1, (SOPC_Byte*) "ManufacturerName"}},
            .Description = {{0, 0, NULL}, {0, 0, NULL}},
            .NoOfReferences = 2,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 40},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 63}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 47},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 3051}, {0, 0, NULL}, 0},
                }
            },
            .Value = 
                  {true,
                   SOPC_UInt32_Id,
                   SOPC_VariantArrayType_SingleValue,
                   {.Uint32 = 23}},
            .DataType = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 12},
            .ValueRank = (-1),
            .AccessLevel = 1,
        }}
    },
    {
        OpcUa_NodeClass_Variable,
        0x00,
        {0, 0},
        {.variable={
            .encodeableType = &OpcUa_VariableNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 3054},
            .NodeClass = OpcUa_NodeClass_Variable,
            .BrowseName = {0, {sizeof("ProductName")-1, 1, (SOPC_Byte*) "ProductName"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("ProductName")-1, 1, (SOPC_Byte*) "ProductName"}},
            .Description = {{0, 0, NULL}, {0, 0, NULL}},
            .NoOfReferences = 2,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 40},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 63}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 47},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 3051}, {0, 0, NULL}, 0},
                }
            },
            .Value = 
                  {true,
                   SOPC_UInt32_Id,
                   SOPC_VariantArrayType_SingleValue,
                   {.Uint32 = 24}},
            .DataType = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 12},
            .ValueRank = (-1),
            .AccessLevel = 1,
        }}
    },
    {
        OpcUa_NodeClass_Variable,
        0x00,
        {0, 0},
        {.variable={
            .encodeableType = &OpcUa_VariableNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 3055},
            .NodeClass = OpcUa_NodeClass_Variable,
            .BrowseName = {0, {sizeof("SoftwareVersion")-1, 1, (SOPC_Byte*) "SoftwareVersion"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("SoftwareVersion")-1, 1, (SOPC_Byte*) "SoftwareVersion"}},
            .Description = {{0, 0, NULL}, {0, 0, NULL}},
            .NoOfReferences = 2,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 40},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 63}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 47},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 3051}, {0, 0, NULL}, 0},
                }
            },
            .Value = 
                  {true,
                   SOPC_UInt32_Id,
                   SOPC_VariantArrayType_SingleValue,
                   {.Uint32 = 25}},
            .DataType = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 12},
            .ValueRank = (-1),
            .AccessLevel = 1,
        }}
    },
    {
        OpcUa_NodeClass_Variable,
        0x00,
        {0, 0},
        {.variable={
            .encodeableType = &OpcUa_VariableNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 3056},
            .NodeClass = OpcUa_NodeClass_Variable,
            .BrowseName = {0, {sizeof("BuildNumber")-1, 1, (SOPC_Byte*) "BuildNumber"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("BuildNumber")-1, 1, (SOPC_Byte*) "BuildNumber"}},
            .Description = {{0, 0, NULL}, {0, 0, NULL}},
            .NoOfReferences = 2,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 40},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 63}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 47},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 3051}, {0, 0, NULL}, 0},
                }
            },
            .Value = 
                  {true,
                   SOPC_UInt32_Id,
                   SOPC_VariantArrayType_SingleValue,
                   {.Uint32 = 26}},
            .DataType = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 12},
            .ValueRank = (-1),
            .AccessLevel = 1,
        }}
    },
    {
        OpcUa_NodeClass_Variable,
        0x00,
        {0, 0},
        {.variable={
            .encodeableType = &OpcUa_VariableNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 3057},
            .NodeClass = OpcUa_NodeClass_Variable,
            .BrowseName = {0, {sizeof("BuildDate")-1, 1, (SOPC_Byte*) "BuildDate"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("BuildDate")-1, 1, (SOPC_Byte*) "BuildDate"}},
            .Description = {{0, 0, NULL}, {0, 0, NULL}},
            .NoOfReferences = 2,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 40},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 63}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 47},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 3051}, {0, 0, NULL}, 0},
                }
            },
            .Value = 
                  {true,
                   SOPC_UInt32_Id,
                   SOPC_VariantArrayType_SingleValue,
                   {.Uint32 = 27}},
            .DataType = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 294},
            .ValueRank = (-1),
            .AccessLevel = 1,
        }}
    },
    {
        OpcUa_NodeClass_Object,
        OpcUa_UncertainInitialValue,
        {0, 0},
        {.object={
            .encodeableType = &OpcUa_ObjectNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 10001},
            .NodeClass = OpcUa_NodeClass_Object,
            .BrowseName = {0, {sizeof("SessionPlaceHolder1")-1, 1, (SOPC_Byte*) "SessionPlaceHolder1"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("SessionPlaceHolder 1")-1, 1, (SOPC_Byte*) "SessionPlaceHolder 1"}},
            .Description = {{0, 0, NULL}, {0, 0, NULL}},
            .NoOfReferences = 0,
            .References = NULL,
        }}
    },
    {
        OpcUa_NodeClass_Object,
        OpcUa_UncertainInitialValue,
        {0, 0},
        {.object={
            .encodeableType = &OpcUa_ObjectNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 10002},
            .NodeClass = OpcUa_NodeClass_Object,
            .BrowseName = {0, {sizeof("SessionPlaceHolder2")-1, 1, (SOPC_Byte*) "SessionPlaceHolder2"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("SessionPlaceHolder 2")-1, 1, (SOPC_Byte*) "SessionPlaceHolder 2"}},
            .Description = {{0, 0, NULL}, {0, 0, NULL}},
            .NoOfReferences = 0,
            .References = NULL,
        }}
    },
    {
        OpcUa_NodeClass_Object,
        OpcUa_UncertainInitialValue,
        {0, 0},
        {.object={
            .encodeableType = &OpcUa_ObjectNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 10003},
            .NodeClass = OpcUa_NodeClass_Object,
            .BrowseName = {0, {sizeof("SessionPlaceHolder3")-1, 1, (SOPC_Byte*) "SessionPlaceHolder3"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("SessionPlaceHolder 3")-1, 1, (SOPC_Byte*) "SessionPlaceHolder 3"}},
            .Description = {{0, 0, NULL}, {0, 0, NULL}},
            .NoOfReferences = 0,
            .References = NULL,
        }}
    },
    {
        OpcUa_NodeClass_Object,
        OpcUa_UncertainInitialValue,
        {0, 0},
        {.object={
            .encodeableType = &OpcUa_ObjectNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 10004},
            .NodeClass = OpcUa_NodeClass_Object,
            .BrowseName = {0, {sizeof("SessionPlaceHolder4")-1, 1, (SOPC_Byte*) "SessionPlaceHolder4"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("SessionPlaceHolder 4")-1, 1, (SOPC_Byte*) "SessionPlaceHolder 4"}},
            .Description = {{0, 0, NULL}, {0, 0, NULL}},
            .NoOfReferences = 0,
            .References = NULL,
        }}
    },
    {
        OpcUa_NodeClass_Object,
        OpcUa_UncertainInitialValue,
        {0, 0},
        {.object={
            .encodeableType = &OpcUa_ObjectNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 10005},
            .NodeClass = OpcUa_NodeClass_Object,
            .BrowseName = {0, {sizeof("SessionPlaceHolder5")-1, 1, (SOPC_Byte*) "SessionPlaceHolder5"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("SessionPlaceHolder 5")-1, 1, (SOPC_Byte*) "SessionPlaceHolder 5"}},
            .Description = {{0, 0, NULL}, {0, 0, NULL}},
            .NoOfReferences = 0,
            .References = NULL,
        }}
    },
    {
        OpcUa_NodeClass_Object,
        OpcUa_UncertainInitialValue,
        {0, 0},
        {.object={
            .encodeableType = &OpcUa_ObjectNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 10006},
            .NodeClass = OpcUa_NodeClass_Object,
            .BrowseName = {0, {sizeof("SessionPlaceHolder6")-1, 1, (SOPC_Byte*) "SessionPlaceHolder6"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("SessionPlaceHolder 6")-1, 1, (SOPC_Byte*) "SessionPlaceHolder 6"}},
            .Description = {{0, 0, NULL}, {0, 0, NULL}},
            .NoOfReferences = 0,
            .References = NULL,
        }}
    },
    {
        OpcUa_NodeClass_Object,
        OpcUa_UncertainInitialValue,
        {0, 0},
        {.object={
            .encodeableType = &OpcUa_ObjectNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 10007},
            .NodeClass = OpcUa_NodeClass_Object,
            .BrowseName = {0, {sizeof("SessionPlaceHolder7")-1, 1, (SOPC_Byte*) "SessionPlaceHolder7"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("SessionPlaceHolder 7")-1, 1, (SOPC_Byte*) "SessionPlaceHolder 7"}},
            .Description = {{0, 0, NULL}, {0, 0, NULL}},
            .NoOfReferences = 0,
            .References = NULL,
        }}
    },
    {
        OpcUa_NodeClass_Object,
        OpcUa_UncertainInitialValue,
        {0, 0},
        {.object={
            .encodeableType = &OpcUa_ObjectNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 10008},
            .NodeClass = OpcUa_NodeClass_Object,
            .BrowseName = {0, {sizeof("SessionPlaceHolder8")-1, 1, (SOPC_Byte*) "SessionPlaceHolder8"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("SessionPlaceHolder 8")-1, 1, (SOPC_Byte*) "SessionPlaceHolder 8"}},
            .Description = {{0, 0, NULL}, {0, 0, NULL}},
            .NoOfReferences = 0,
            .References = NULL,
        }}
    },
    {
        OpcUa_NodeClass_Object,
        OpcUa_UncertainInitialValue,
        {0, 0},
        {.object={
            .encodeableType = &OpcUa_ObjectNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 10009},
            .NodeClass = OpcUa_NodeClass_Object,
            .BrowseName = {0, {sizeof("SessionPlaceHolder9")-1, 1, (SOPC_Byte*) "SessionPlaceHolder9"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("SessionPlaceHolder 9")-1, 1, (SOPC_Byte*) "SessionPlaceHolder 9"}},
            .Description = {{0, 0, NULL}, {0, 0, NULL}},
            .NoOfReferences = 0,
            .References = NULL,
        }}
    },
    {
        OpcUa_NodeClass_Object,
        OpcUa_UncertainInitialValue,
        {0, 0},
        {.object={
            .encodeableType = &OpcUa_ObjectNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 10010},
            .NodeClass = OpcUa_NodeClass_Object,
            .BrowseName = {0, {sizeof("SessionPlaceHolder10")-1, 1, (SOPC_Byte*) "SessionPlaceHolder10"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("SessionPlaceHolder 10")-1, 1, (SOPC_Byte*) "SessionPlaceHolder 10"}},
            .Description = {{0, 0, NULL}, {0, 0, NULL}},
            .NoOfReferences = 0,
            .References = NULL,
        }}
    },
    {
        OpcUa_NodeClass_Object,
        OpcUa_UncertainInitialValue,
        {0, 0},
        {.object={
            .encodeableType = &OpcUa_ObjectNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 10011},
            .NodeClass = OpcUa_NodeClass_Object,
            .BrowseName = {0, {sizeof("SessionPlaceHolder11")-1, 1, (SOPC_Byte*) "SessionPlaceHolder11"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("SessionPlaceHolder 11")-1, 1, (SOPC_Byte*) "SessionPlaceHolder 11"}},
            .Description = {{0, 0, NULL}, {0, 0, NULL}},
            .NoOfReferences = 0,
            .References = NULL,
        }}
    },
    {
        OpcUa_NodeClass_Object,
        OpcUa_UncertainInitialValue,
        {0, 0},
        {.object={
            .encodeableType = &OpcUa_ObjectNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 10012},
            .NodeClass = OpcUa_NodeClass_Object,
            .BrowseName = {0, {sizeof("SessionPlaceHolder12")-1, 1, (SOPC_Byte*) "SessionPlaceHolder12"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("SessionPlaceHolder 12")-1, 1, (SOPC_Byte*) "SessionPlaceHolder 12"}},
            .Description = {{0, 0, NULL}, {0, 0, NULL}},
            .NoOfReferences = 0,
            .References = NULL,
        }}
    },
    {
        OpcUa_NodeClass_Object,
        OpcUa_UncertainInitialValue,
        {0, 0},
        {.object={
            .encodeableType = &OpcUa_ObjectNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 10013},
            .NodeClass = OpcUa_NodeClass_Object,
            .BrowseName = {0, {sizeof("SessionPlaceHolder13")-1, 1, (SOPC_Byte*) "SessionPlaceHolder13"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("SessionPlaceHolder 13")-1, 1, (SOPC_Byte*) "SessionPlaceHolder 13"}},
            .Description = {{0, 0, NULL}, {0, 0, NULL}},
            .NoOfReferences = 0,
            .References = NULL,
        }}
    },
    {
        OpcUa_NodeClass_Object,
        OpcUa_UncertainInitialValue,
        {0, 0},
        {.object={
            .encodeableType = &OpcUa_ObjectNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 10014},
            .NodeClass = OpcUa_NodeClass_Object,
            .BrowseName = {0, {sizeof("SessionPlaceHolder14")-1, 1, (SOPC_Byte*) "SessionPlaceHolder14"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("SessionPlaceHolder 14")-1, 1, (SOPC_Byte*) "SessionPlaceHolder 14"}},
            .Description = {{0, 0, NULL}, {0, 0, NULL}},
            .NoOfReferences = 0,
            .References = NULL,
        }}
    },
    {
        OpcUa_NodeClass_Object,
        OpcUa_UncertainInitialValue,
        {0, 0},
        {.object={
            .encodeableType = &OpcUa_ObjectNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 10015},
            .NodeClass = OpcUa_NodeClass_Object,
            .BrowseName = {0, {sizeof("SessionPlaceHolder15")-1, 1, (SOPC_Byte*) "SessionPlaceHolder15"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("SessionPlaceHolder 15")-1, 1, (SOPC_Byte*) "SessionPlaceHolder 15"}},
            .Description = {{0, 0, NULL}, {0, 0, NULL}},
            .NoOfReferences = 0,
            .References = NULL,
        }}
    },
    {
        OpcUa_NodeClass_Object,
        OpcUa_UncertainInitialValue,
        {0, 0},
        {.object={
            .encodeableType = &OpcUa_ObjectNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 10016},
            .NodeClass = OpcUa_NodeClass_Object,
            .BrowseName = {0, {sizeof("SessionPlaceHolder16")-1, 1, (SOPC_Byte*) "SessionPlaceHolder16"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("SessionPlaceHolder 16")-1, 1, (SOPC_Byte*) "SessionPlaceHolder 16"}},
            .Description = {{0, 0, NULL}, {0, 0, NULL}},
            .NoOfReferences = 0,
            .References = NULL,
        }}
    },
    {
        OpcUa_NodeClass_Object,
        OpcUa_UncertainInitialValue,
        {0, 0},
        {.object={
            .encodeableType = &OpcUa_ObjectNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 10017},
            .NodeClass = OpcUa_NodeClass_Object,
            .BrowseName = {0, {sizeof("SessionPlaceHolder17")-1, 1, (SOPC_Byte*) "SessionPlaceHolder17"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("SessionPlaceHolder 17")-1, 1, (SOPC_Byte*) "SessionPlaceHolder 17"}},
            .Description = {{0, 0, NULL}, {0, 0, NULL}},
            .NoOfReferences = 0,
            .References = NULL,
        }}
    },
    {
        OpcUa_NodeClass_Object,
        OpcUa_UncertainInitialValue,
        {0, 0},
        {.object={
            .encodeableType = &OpcUa_ObjectNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 10018},
            .NodeClass = OpcUa_NodeClass_Object,
            .BrowseName = {0, {sizeof("SessionPlaceHolder18")-1, 1, (SOPC_Byte*) "SessionPlaceHolder18"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("SessionPlaceHolder 18")-1, 1, (SOPC_Byte*) "SessionPlaceHolder 18"}},
            .Description = {{0, 0, NULL}, {0, 0, NULL}},
            .NoOfReferences = 0,
            .References = NULL,
        }}
    },
    {
        OpcUa_NodeClass_Object,
        OpcUa_UncertainInitialValue,
        {0, 0},
        {.object={
            .encodeableType = &OpcUa_ObjectNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 10019},
            .NodeClass = OpcUa_NodeClass_Object,
            .BrowseName = {0, {sizeof("SessionPlaceHolder19")-1, 1, (SOPC_Byte*) "SessionPlaceHolder19"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("SessionPlaceHolder 19")-1, 1, (SOPC_Byte*) "SessionPlaceHolder 19"}},
            .Description = {{0, 0, NULL}, {0, 0, NULL}},
            .NoOfReferences = 0,
            .References = NULL,
        }}
    },
    {
        OpcUa_NodeClass_Object,
        OpcUa_UncertainInitialValue,
        {0, 0},
        {.object={
            .encodeableType = &OpcUa_ObjectNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 10020},
            .NodeClass = OpcUa_NodeClass_Object,
            .BrowseName = {0, {sizeof("SessionPlaceHolder20")-1, 1, (SOPC_Byte*) "SessionPlaceHolder20"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("SessionPlaceHolder 20")-1, 1, (SOPC_Byte*) "SessionPlaceHolder 20"}},
            .Description = {{0, 0, NULL}, {0, 0, NULL}},
            .NoOfReferences = 0,
            .References = NULL,
        }}
    },
    {
        OpcUa_NodeClass_Variable,
        0x00,
        {0, 0},
        {.variable={
            .encodeableType = &OpcUa_VariableNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_String, 1, .Data.String = {sizeof("PubSubStatus")-1, 1, (SOPC_Byte*) "PubSubStatus"}},
            .NodeClass = OpcUa_NodeClass_Variable,
            .BrowseName = {0, {sizeof("PubSub Status")-1, 1, (SOPC_Byte*) "PubSub Status"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("PubSub Status")-1, 1, (SOPC_Byte*) "PubSub Status"}},
            .Description = {{0, 0, NULL}, {sizeof("The status of the PubSub module")-1, 1, (SOPC_Byte*) "The status of the PubSub module"}},
            .NoOfReferences = 2,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 35},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 85}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 40},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 63}, {0, 0, NULL}, 0},
                }
            },
            .Value = 
                  {true,
                   SOPC_UInt32_Id,
                   SOPC_VariantArrayType_SingleValue,
                   {.Uint32 = 28}},
            .DataType = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 3},
            .ValueRank = (-1),
            .AccessLevel = 3,
        }}
    },
    {
        OpcUa_NodeClass_Variable,
        0x00,
        {0, 0},
        {.variable={
            .encodeableType = &OpcUa_VariableNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_String, 1, .Data.String = {sizeof("PubSubConfiguration")-1, 1, (SOPC_Byte*) "PubSubConfiguration"}},
            .NodeClass = OpcUa_NodeClass_Variable,
            .BrowseName = {0, {sizeof("PubSub Configuration")-1, 1, (SOPC_Byte*) "PubSub Configuration"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("PubSub Configuration")-1, 1, (SOPC_Byte*) "PubSub Configuration"}},
            .Description = {{0, 0, NULL}, {sizeof("Path(s) to the configuration files used when PubSub is started")-1, 1, (SOPC_Byte*) "Path(s) to the configuration files used when PubSub is started"}},
            .NoOfReferences = 2,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 35},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 85}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 40},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 63}, {0, 0, NULL}, 0},
                }
            },
            .Value = 
                  {true,
                   SOPC_UInt32_Id,
                   SOPC_VariantArrayType_SingleValue,
                   {.Uint32 = 29}},
            .DataType = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 12},
            .ValueRank = (-1),
            .AccessLevel = 3,
        }}
    },
    {
        OpcUa_NodeClass_Variable,
        0x00,
        {0, 0},
        {.variable={
            .encodeableType = &OpcUa_VariableNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_String, 1, .Data.String = {sizeof("PubSubStartStop")-1, 1, (SOPC_Byte*) "PubSubStartStop"}},
            .NodeClass = OpcUa_NodeClass_Variable,
            .BrowseName = {0, {sizeof("PubSub Start/Stop Command")-1, 1, (SOPC_Byte*) "PubSub Start/Stop Command"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("PubSub Start/Stop Command")-1, 1, (SOPC_Byte*) "PubSub Start/Stop Command"}},
            .Description = {{0, 0, NULL}, {sizeof("Write 1 to start (or restart) the PubSub Module, write 0 to stop the module")-1, 1, (SOPC_Byte*) "Write 1 to start (or restart) the PubSub Module, write 0 to stop the module"}},
            .NoOfReferences = 2,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 35},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 85}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 40},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 63}, {0, 0, NULL}, 0},
                }
            },
            .Value = 
                  {true,
                   SOPC_UInt32_Id,
                   SOPC_VariantArrayType_SingleValue,
                   {.Uint32 = 30}},
            .DataType = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 3},
            .ValueRank = (-1),
            .AccessLevel = 3,
        }}
    },
    {
        OpcUa_NodeClass_Object,
        OpcUa_UncertainInitialValue,
        {0, 0},
        {.object={
            .encodeableType = &OpcUa_ObjectNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_String, 1, .Data.String = {sizeof("InESObjects")-1, 1, (SOPC_Byte*) "InESObjects"}},
            .NodeClass = OpcUa_NodeClass_Object,
            .BrowseName = {1, {sizeof("InESObjects")-1, 1, (SOPC_Byte*) "InESObjects"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("InESObjects")-1, 1, (SOPC_Byte*) "InESObjects"}},
            .Description = {{0, 0, NULL}, {0, 0, NULL}},
            .NoOfReferences = 4,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 40},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 61}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 35},
                    false,
                    {{SOPC_IdentifierType_String, 1, .Data.String = {sizeof("FluidTank")-1, 1, (SOPC_Byte*) "FluidTank"}}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 35},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 85}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 35},
                    true,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 2253}, {0, 0, NULL}, 0},
                }
            },
        }}
    },
    {
        OpcUa_NodeClass_Object,
        OpcUa_UncertainInitialValue,
        {0, 0},
        {.object={
            .encodeableType = &OpcUa_ObjectNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_String, 1, .Data.String = {sizeof("FluidTank")-1, 1, (SOPC_Byte*) "FluidTank"}},
            .NodeClass = OpcUa_NodeClass_Object,
            .BrowseName = {1, {sizeof("FluidTank")-1, 1, (SOPC_Byte*) "FluidTank"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("FluidTank")-1, 1, (SOPC_Byte*) "FluidTank"}},
            .Description = {{0, 0, NULL}, {sizeof("The depot for beer or soft drinks")-1, 1, (SOPC_Byte*) "The depot for beer or soft drinks"}},
            .NoOfReferences = 6,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 40},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 58}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 35},
                    true,
                    {{SOPC_IdentifierType_String, 1, .Data.String = {sizeof("InESObjects")-1, 1, (SOPC_Byte*) "InESObjects"}}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 47},
                    false,
                    {{SOPC_IdentifierType_String, 1, .Data.String = {sizeof("BASET1L_IF")-1, 1, (SOPC_Byte*) "BASET1L_IF"}}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 47},
                    false,
                    {{SOPC_IdentifierType_String, 1, .Data.String = {sizeof("ForceSensor")-1, 1, (SOPC_Byte*) "ForceSensor"}}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 47},
                    false,
                    {{SOPC_IdentifierType_String, 1, .Data.String = {sizeof("TankLevel")-1, 1, (SOPC_Byte*) "TankLevel"}}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 47},
                    false,
                    {{SOPC_IdentifierType_String, 1, .Data.String = {sizeof("TankWeight")-1, 1, (SOPC_Byte*) "TankWeight"}}, {0, 0, NULL}, 0},
                }
            },
        }}
    },
    {
        OpcUa_NodeClass_Object,
        OpcUa_UncertainInitialValue,
        {0, 0},
        {.object={
            .encodeableType = &OpcUa_ObjectNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_String, 1, .Data.String = {sizeof("BASET1L_IF")-1, 1, (SOPC_Byte*) "BASET1L_IF"}},
            .NodeClass = OpcUa_NodeClass_Object,
            .BrowseName = {1, {sizeof("BASET1L_IF")-1, 1, (SOPC_Byte*) "BASET1L_IF"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("BASET1L_IF")-1, 1, (SOPC_Byte*) "BASET1L_IF"}},
            .Description = {{0, 0, NULL}, {sizeof("The 10BASE-T1L interface of the Fluid Tank")-1, 1, (SOPC_Byte*) "The 10BASE-T1L interface of the Fluid Tank"}},
            .NoOfReferences = 5,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 40},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 58}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 47},
                    true,
                    {{SOPC_IdentifierType_String, 1, .Data.String = {sizeof("FluidTank")-1, 1, (SOPC_Byte*) "FluidTank"}}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 35},
                    false,
                    {{SOPC_IdentifierType_String, 1, .Data.String = {sizeof("IFAdminStatus")-1, 1, (SOPC_Byte*) "IFAdminStatus"}}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 35},
                    false,
                    {{SOPC_IdentifierType_String, 1, .Data.String = {sizeof("IFOperStatus")-1, 1, (SOPC_Byte*) "IFOperStatus"}}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 35},
                    false,
                    {{SOPC_IdentifierType_String, 1, .Data.String = {sizeof("IFSpeed")-1, 1, (SOPC_Byte*) "IFSpeed"}}, {0, 0, NULL}, 0},
                }
            },
        }}
    },
    {
        OpcUa_NodeClass_Variable,
        0x00,
        {0, 0},
        {.variable={
            .encodeableType = &OpcUa_VariableNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_String, 1, .Data.String = {sizeof("IFAdminStatus")-1, 1, (SOPC_Byte*) "IFAdminStatus"}},
            .NodeClass = OpcUa_NodeClass_Variable,
            .BrowseName = {1, {sizeof("IFAdminStatus")-1, 1, (SOPC_Byte*) "IFAdminStatus"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("AdminStatus")-1, 1, (SOPC_Byte*) "AdminStatus"}},
            .Description = {{0, 0, NULL}, {sizeof("Administrative Status of the Interface")-1, 1, (SOPC_Byte*) "Administrative Status of the Interface"}},
            .NoOfReferences = 2,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 40},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 63}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 35},
                    true,
                    {{SOPC_IdentifierType_String, 1, .Data.String = {sizeof("BASET1L_IF")-1, 1, (SOPC_Byte*) "BASET1L_IF"}}, {0, 0, NULL}, 0},
                }
            },
            .Value = 
                  {true,
                   SOPC_UInt32_Id,
                   SOPC_VariantArrayType_SingleValue,
                   {.Uint32 = 31}},
            .DataType = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 24212},
            .ValueRank = (-1),
            .AccessLevel = 1,
        }}
    },
    {
        OpcUa_NodeClass_Variable,
        0x00,
        {0, 0},
        {.variable={
            .encodeableType = &OpcUa_VariableNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_String, 1, .Data.String = {sizeof("IFOperStatus")-1, 1, (SOPC_Byte*) "IFOperStatus"}},
            .NodeClass = OpcUa_NodeClass_Variable,
            .BrowseName = {1, {sizeof("IFOperStatus")-1, 1, (SOPC_Byte*) "IFOperStatus"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("OperStatus")-1, 1, (SOPC_Byte*) "OperStatus"}},
            .Description = {{0, 0, NULL}, {sizeof("Operational Status of the Interface")-1, 1, (SOPC_Byte*) "Operational Status of the Interface"}},
            .NoOfReferences = 2,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 40},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 63}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 35},
                    true,
                    {{SOPC_IdentifierType_String, 1, .Data.String = {sizeof("BASET1L_IF")-1, 1, (SOPC_Byte*) "BASET1L_IF"}}, {0, 0, NULL}, 0},
                }
            },
            .Value = 
                  {true,
                   SOPC_UInt32_Id,
                   SOPC_VariantArrayType_SingleValue,
                   {.Uint32 = 32}},
            .DataType = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 24214},
            .ValueRank = (-1),
            .AccessLevel = 1,
        }}
    },
    {
        OpcUa_NodeClass_Variable,
        0x00,
        {0, 0},
        {.variable={
            .encodeableType = &OpcUa_VariableNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_String, 1, .Data.String = {sizeof("IFSpeed")-1, 1, (SOPC_Byte*) "IFSpeed"}},
            .NodeClass = OpcUa_NodeClass_Variable,
            .BrowseName = {1, {sizeof("IFSpeed")-1, 1, (SOPC_Byte*) "IFSpeed"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("Speed")-1, 1, (SOPC_Byte*) "Speed"}},
            .Description = {{0, 0, NULL}, {sizeof("Speed of the sensor interface")-1, 1, (SOPC_Byte*) "Speed of the sensor interface"}},
            .NoOfReferences = 3,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 40},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 63}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 46},
                    false,
                    {{SOPC_IdentifierType_String, 1, .Data.String = {sizeof("EUInterface_T1L")-1, 1, (SOPC_Byte*) "EUInterface_T1L"}}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 35},
                    true,
                    {{SOPC_IdentifierType_String, 1, .Data.String = {sizeof("BASET1L_IF")-1, 1, (SOPC_Byte*) "BASET1L_IF"}}, {0, 0, NULL}, 0},
                }
            },
            .Value = 
                  {true,
                   SOPC_UInt32_Id,
                   SOPC_VariantArrayType_SingleValue,
                   {.Uint32 = 33}},
            .DataType = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 9},
            .ValueRank = (-1),
            .AccessLevel = 1,
        }}
    },
    {
        OpcUa_NodeClass_Variable,
        0x00,
        {0, 0},
        {.variable={
            .encodeableType = &OpcUa_VariableNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_String, 1, .Data.String = {sizeof("EUInterface_T1L")-1, 1, (SOPC_Byte*) "EUInterface_T1L"}},
            .NodeClass = OpcUa_NodeClass_Variable,
            .BrowseName = {1, {sizeof("EUInterface_T1L")-1, 1, (SOPC_Byte*) "EUInterface_T1L"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("EngineeringUnits")-1, 1, (SOPC_Byte*) "EngineeringUnits"}},
            .Description = {{0, 0, NULL}, {sizeof("Units for the I/F Speed")-1, 1, (SOPC_Byte*) "Units for the I/F Speed"}},
            .NoOfReferences = 2,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 40},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 68}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 46},
                    true,
                    {{SOPC_IdentifierType_String, 1, .Data.String = {sizeof("IFSpeed")-1, 1, (SOPC_Byte*) "IFSpeed"}}, {0, 0, NULL}, 0},
                }
            },
            .Value = 
                  {true,
                   SOPC_UInt32_Id,
                   SOPC_VariantArrayType_SingleValue,
                   {.Uint32 = 34}},
            .DataType = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 887},
            .ValueRank = (-1),
            .AccessLevel = 1,
        }}
    },
    {
        OpcUa_NodeClass_Object,
        OpcUa_UncertainInitialValue,
        {0, 0},
        {.object={
            .encodeableType = &OpcUa_ObjectNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_String, 1, .Data.String = {sizeof("ForceSensor")-1, 1, (SOPC_Byte*) "ForceSensor"}},
            .NodeClass = OpcUa_NodeClass_Object,
            .BrowseName = {1, {sizeof("ForceSensor")-1, 1, (SOPC_Byte*) "ForceSensor"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("ForceSensor")-1, 1, (SOPC_Byte*) "ForceSensor"}},
            .Description = {{0, 0, NULL}, {sizeof("The Kistler Charge Amplifier representing the Piezo sensor")-1, 1, (SOPC_Byte*) "The Kistler Charge Amplifier representing the Piezo sensor"}},
            .NoOfReferences = 8,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 40},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 58}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 47},
                    true,
                    {{SOPC_IdentifierType_String, 1, .Data.String = {sizeof("FluidTank")-1, 1, (SOPC_Byte*) "FluidTank"}}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 46},
                    false,
                    {{SOPC_IdentifierType_String, 1, .Data.String = {sizeof("ForceSensorManufacturer")-1, 1, (SOPC_Byte*) "ForceSensorManufacturer"}}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 46},
                    false,
                    {{SOPC_IdentifierType_String, 1, .Data.String = {sizeof("ForceSensorModelName")-1, 1, (SOPC_Byte*) "ForceSensorModelName"}}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 46},
                    false,
                    {{SOPC_IdentifierType_String, 1, .Data.String = {sizeof("ForceSensorSerialNumber")-1, 1, (SOPC_Byte*) "ForceSensorSerialNumber"}}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 47},
                    false,
                    {{SOPC_IdentifierType_String, 1, .Data.String = {sizeof("Force")-1, 1, (SOPC_Byte*) "Force"}}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 47},
                    false,
                    {{SOPC_IdentifierType_String, 1, .Data.String = {sizeof("RawVoltage")-1, 1, (SOPC_Byte*) "RawVoltage"}}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 46},
                    false,
                    {{SOPC_IdentifierType_String, 1, .Data.String = {sizeof("Slope")-1, 1, (SOPC_Byte*) "Slope"}}, {0, 0, NULL}, 0},
                }
            },
        }}
    },
    {
        OpcUa_NodeClass_Variable,
        0x00,
        {0, 0},
        {.variable={
            .encodeableType = &OpcUa_VariableNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_String, 1, .Data.String = {sizeof("RawVoltage")-1, 1, (SOPC_Byte*) "RawVoltage"}},
            .NodeClass = OpcUa_NodeClass_Variable,
            .BrowseName = {1, {sizeof("RawVoltage")-1, 1, (SOPC_Byte*) "RawVoltage"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("RawVoltage")-1, 1, (SOPC_Byte*) "RawVoltage"}},
            .Description = {{0, 0, NULL}, {sizeof("Measured Voltage of the sensor")-1, 1, (SOPC_Byte*) "Measured Voltage of the sensor"}},
            .NoOfReferences = 4,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 40},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 2368}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 46},
                    false,
                    {{SOPC_IdentifierType_String, 1, .Data.String = {sizeof("EURawVoltage")-1, 1, (SOPC_Byte*) "EURawVoltage"}}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 46},
                    false,
                    {{SOPC_IdentifierType_String, 1, .Data.String = {sizeof("EURangeRawVoltage")-1, 1, (SOPC_Byte*) "EURangeRawVoltage"}}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 47},
                    true,
                    {{SOPC_IdentifierType_String, 1, .Data.String = {sizeof("ForceSensor")-1, 1, (SOPC_Byte*) "ForceSensor"}}, {0, 0, NULL}, 0},
                }
            },
            .Value = 
                  {true,
                   SOPC_UInt32_Id,
                   SOPC_VariantArrayType_SingleValue,
                   {.Uint32 = 35}},
            .DataType = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 11},
            .ValueRank = (-1),
            .AccessLevel = 1,
        }}
    },
    {
        OpcUa_NodeClass_Variable,
        0x00,
        {0, 0},
        {.variable={
            .encodeableType = &OpcUa_VariableNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_String, 1, .Data.String = {sizeof("EURawVoltage")-1, 1, (SOPC_Byte*) "EURawVoltage"}},
            .NodeClass = OpcUa_NodeClass_Variable,
            .BrowseName = {1, {sizeof("EURawVoltage")-1, 1, (SOPC_Byte*) "EURawVoltage"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("EngineeringUnits")-1, 1, (SOPC_Byte*) "EngineeringUnits"}},
            .Description = {{0, 0, NULL}, {sizeof("Units for the voltage")-1, 1, (SOPC_Byte*) "Units for the voltage"}},
            .NoOfReferences = 2,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 40},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 68}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 46},
                    true,
                    {{SOPC_IdentifierType_String, 1, .Data.String = {sizeof("RawVoltage")-1, 1, (SOPC_Byte*) "RawVoltage"}}, {0, 0, NULL}, 0},
                }
            },
            .Value = 
                  {true,
                   SOPC_UInt32_Id,
                   SOPC_VariantArrayType_SingleValue,
                   {.Uint32 = 36}},
            .DataType = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 887},
            .ValueRank = (-1),
            .AccessLevel = 1,
        }}
    },
    {
        OpcUa_NodeClass_Variable,
        0x00,
        {0, 0},
        {.variable={
            .encodeableType = &OpcUa_VariableNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_String, 1, .Data.String = {sizeof("EURangeRawVoltage")-1, 1, (SOPC_Byte*) "EURangeRawVoltage"}},
            .NodeClass = OpcUa_NodeClass_Variable,
            .BrowseName = {1, {sizeof("EURangeRawVoltage")-1, 1, (SOPC_Byte*) "EURangeRawVoltage"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("EURange")-1, 1, (SOPC_Byte*) "EURange"}},
            .Description = {{0, 0, NULL}, {sizeof("Value range for the voltage")-1, 1, (SOPC_Byte*) "Value range for the voltage"}},
            .NoOfReferences = 2,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 40},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 68}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 46},
                    true,
                    {{SOPC_IdentifierType_String, 1, .Data.String = {sizeof("RawVoltage")-1, 1, (SOPC_Byte*) "RawVoltage"}}, {0, 0, NULL}, 0},
                }
            },
            .Value = 
                  {true,
                   SOPC_UInt32_Id,
                   SOPC_VariantArrayType_SingleValue,
                   {.Uint32 = 37}},
            .DataType = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 884},
            .ValueRank = (-1),
            .AccessLevel = 1,
        }}
    },
    {
        OpcUa_NodeClass_Variable,
        0x00,
        {0, 0},
        {.variable={
            .encodeableType = &OpcUa_VariableNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_String, 1, .Data.String = {sizeof("Slope")-1, 1, (SOPC_Byte*) "Slope"}},
            .NodeClass = OpcUa_NodeClass_Variable,
            .BrowseName = {1, {sizeof("Slope")-1, 1, (SOPC_Byte*) "Slope"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("Slope [N per V]")-1, 1, (SOPC_Byte*) "Slope [N per V]"}},
            .Description = {{0, 0, NULL}, {0, 0, NULL}},
            .NoOfReferences = 2,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 40},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 68}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 46},
                    true,
                    {{SOPC_IdentifierType_String, 1, .Data.String = {sizeof("ForceSensor")-1, 1, (SOPC_Byte*) "ForceSensor"}}, {0, 0, NULL}, 0},
                }
            },
            .Value = 
                  {true,
                   SOPC_UInt32_Id,
                   SOPC_VariantArrayType_SingleValue,
                   {.Uint32 = 38}},
            .DataType = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 11},
            .ValueRank = (-1),
            .AccessLevel = 3,
        }}
    },
    {
        OpcUa_NodeClass_Variable,
        0x00,
        {0, 0},
        {.variable={
            .encodeableType = &OpcUa_VariableNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_String, 1, .Data.String = {sizeof("Force")-1, 1, (SOPC_Byte*) "Force"}},
            .NodeClass = OpcUa_NodeClass_Variable,
            .BrowseName = {1, {sizeof("Force")-1, 1, (SOPC_Byte*) "Force"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("Force")-1, 1, (SOPC_Byte*) "Force"}},
            .Description = {{0, 0, NULL}, {sizeof("Force based on sensor reading")-1, 1, (SOPC_Byte*) "Force based on sensor reading"}},
            .NoOfReferences = 5,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 40},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 2368}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 46},
                    false,
                    {{SOPC_IdentifierType_String, 1, .Data.String = {sizeof("EUForce")-1, 1, (SOPC_Byte*) "EUForce"}}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 46},
                    false,
                    {{SOPC_IdentifierType_String, 1, .Data.String = {sizeof("EURangeForce")-1, 1, (SOPC_Byte*) "EURangeForce"}}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 35},
                    true,
                    {{SOPC_IdentifierType_String, 1, .Data.String = {sizeof("TankWeight")-1, 1, (SOPC_Byte*) "TankWeight"}}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 47},
                    true,
                    {{SOPC_IdentifierType_String, 1, .Data.String = {sizeof("ForceSensor")-1, 1, (SOPC_Byte*) "ForceSensor"}}, {0, 0, NULL}, 0},
                }
            },
            .Value = 
                  {true,
                   SOPC_UInt32_Id,
                   SOPC_VariantArrayType_SingleValue,
                   {.Uint32 = 39}},
            .DataType = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 11},
            .ValueRank = (-1),
            .AccessLevel = 1,
        }}
    },
    {
        OpcUa_NodeClass_Variable,
        0x00,
        {0, 0},
        {.variable={
            .encodeableType = &OpcUa_VariableNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_String, 1, .Data.String = {sizeof("EUForce")-1, 1, (SOPC_Byte*) "EUForce"}},
            .NodeClass = OpcUa_NodeClass_Variable,
            .BrowseName = {1, {sizeof("EUForce")-1, 1, (SOPC_Byte*) "EUForce"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("EngineeringUnits")-1, 1, (SOPC_Byte*) "EngineeringUnits"}},
            .Description = {{0, 0, NULL}, {sizeof("Units for the force")-1, 1, (SOPC_Byte*) "Units for the force"}},
            .NoOfReferences = 2,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 40},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 68}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 46},
                    true,
                    {{SOPC_IdentifierType_String, 1, .Data.String = {sizeof("Force")-1, 1, (SOPC_Byte*) "Force"}}, {0, 0, NULL}, 0},
                }
            },
            .Value = 
                  {true,
                   SOPC_UInt32_Id,
                   SOPC_VariantArrayType_SingleValue,
                   {.Uint32 = 40}},
            .DataType = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 887},
            .ValueRank = (-1),
            .AccessLevel = 1,
        }}
    },
    {
        OpcUa_NodeClass_Variable,
        0x00,
        {0, 0},
        {.variable={
            .encodeableType = &OpcUa_VariableNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_String, 1, .Data.String = {sizeof("EURangeForce")-1, 1, (SOPC_Byte*) "EURangeForce"}},
            .NodeClass = OpcUa_NodeClass_Variable,
            .BrowseName = {1, {sizeof("EURangeForce")-1, 1, (SOPC_Byte*) "EURangeForce"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("EURange")-1, 1, (SOPC_Byte*) "EURange"}},
            .Description = {{0, 0, NULL}, {sizeof("Value range for the force")-1, 1, (SOPC_Byte*) "Value range for the force"}},
            .NoOfReferences = 2,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 40},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 68}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 46},
                    true,
                    {{SOPC_IdentifierType_String, 1, .Data.String = {sizeof("Force")-1, 1, (SOPC_Byte*) "Force"}}, {0, 0, NULL}, 0},
                }
            },
            .Value = 
                  {true,
                   SOPC_UInt32_Id,
                   SOPC_VariantArrayType_SingleValue,
                   {.Uint32 = 41}},
            .DataType = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 884},
            .ValueRank = (-1),
            .AccessLevel = 1,
        }}
    },
    {
        OpcUa_NodeClass_Variable,
        0x00,
        {0, 0},
        {.variable={
            .encodeableType = &OpcUa_VariableNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_String, 1, .Data.String = {sizeof("ForceSensorManufacturer")-1, 1, (SOPC_Byte*) "ForceSensorManufacturer"}},
            .NodeClass = OpcUa_NodeClass_Variable,
            .BrowseName = {1, {sizeof("ForceSensorManufacturer")-1, 1, (SOPC_Byte*) "ForceSensorManufacturer"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("Manufacturer")-1, 1, (SOPC_Byte*) "Manufacturer"}},
            .Description = {{0, 0, NULL}, {sizeof("Manufacturer of the Force Sensor")-1, 1, (SOPC_Byte*) "Manufacturer of the Force Sensor"}},
            .NoOfReferences = 2,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 40},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 68}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 46},
                    true,
                    {{SOPC_IdentifierType_String, 1, .Data.String = {sizeof("ForceSensor")-1, 1, (SOPC_Byte*) "ForceSensor"}}, {0, 0, NULL}, 0},
                }
            },
            .Value = 
                  {true,
                   SOPC_UInt32_Id,
                   SOPC_VariantArrayType_SingleValue,
                   {.Uint32 = 42}},
            .DataType = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 12},
            .ValueRank = (-1),
            .AccessLevel = 1,
        }}
    },
    {
        OpcUa_NodeClass_Variable,
        0x00,
        {0, 0},
        {.variable={
            .encodeableType = &OpcUa_VariableNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_String, 1, .Data.String = {sizeof("ForceSensorModelName")-1, 1, (SOPC_Byte*) "ForceSensorModelName"}},
            .NodeClass = OpcUa_NodeClass_Variable,
            .BrowseName = {1, {sizeof("ForceSensorModelName")-1, 1, (SOPC_Byte*) "ForceSensorModelName"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("Model")-1, 1, (SOPC_Byte*) "Model"}},
            .Description = {{0, 0, NULL}, {sizeof("Model of the Force Sensor")-1, 1, (SOPC_Byte*) "Model of the Force Sensor"}},
            .NoOfReferences = 2,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 40},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 68}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 46},
                    true,
                    {{SOPC_IdentifierType_String, 1, .Data.String = {sizeof("ForceSensor")-1, 1, (SOPC_Byte*) "ForceSensor"}}, {0, 0, NULL}, 0},
                }
            },
            .Value = 
                  {true,
                   SOPC_UInt32_Id,
                   SOPC_VariantArrayType_SingleValue,
                   {.Uint32 = 43}},
            .DataType = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 12},
            .ValueRank = (-1),
            .AccessLevel = 1,
        }}
    },
    {
        OpcUa_NodeClass_Variable,
        0x00,
        {0, 0},
        {.variable={
            .encodeableType = &OpcUa_VariableNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_String, 1, .Data.String = {sizeof("ForceSensorSerialNumber")-1, 1, (SOPC_Byte*) "ForceSensorSerialNumber"}},
            .NodeClass = OpcUa_NodeClass_Variable,
            .BrowseName = {1, {sizeof("ForceSensorSerialNumber")-1, 1, (SOPC_Byte*) "ForceSensorSerialNumber"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("Serial Number")-1, 1, (SOPC_Byte*) "Serial Number"}},
            .Description = {{0, 0, NULL}, {sizeof("Serial Number of  Force Sensor")-1, 1, (SOPC_Byte*) "Serial Number of  Force Sensor"}},
            .NoOfReferences = 2,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 40},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 68}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 46},
                    true,
                    {{SOPC_IdentifierType_String, 1, .Data.String = {sizeof("ForceSensor")-1, 1, (SOPC_Byte*) "ForceSensor"}}, {0, 0, NULL}, 0},
                }
            },
            .Value = 
                  {true,
                   SOPC_UInt32_Id,
                   SOPC_VariantArrayType_SingleValue,
                   {.Uint32 = 44}},
            .DataType = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 12},
            .ValueRank = (-1),
            .AccessLevel = 1,
        }}
    },
    {
        OpcUa_NodeClass_Variable,
        0x00,
        {0, 0},
        {.variable={
            .encodeableType = &OpcUa_VariableNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_String, 1, .Data.String = {sizeof("TankLevel")-1, 1, (SOPC_Byte*) "TankLevel"}},
            .NodeClass = OpcUa_NodeClass_Variable,
            .BrowseName = {1, {sizeof("TankLevel")-1, 1, (SOPC_Byte*) "TankLevel"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("TankLevel")-1, 1, (SOPC_Byte*) "TankLevel"}},
            .Description = {{0, 0, NULL}, {sizeof("CurrentDrinkreservoir (beer od soft drink)")-1, 1, (SOPC_Byte*) "CurrentDrinkreservoir (beer od soft drink)"}},
            .NoOfReferences = 8,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 40},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 2368}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 46},
                    false,
                    {{SOPC_IdentifierType_String, 1, .Data.String = {sizeof("EUTankLevel")-1, 1, (SOPC_Byte*) "EUTankLevel"}}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 46},
                    false,
                    {{SOPC_IdentifierType_String, 1, .Data.String = {sizeof("EURangeTankLevel")-1, 1, (SOPC_Byte*) "EURangeTankLevel"}}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 46},
                    false,
                    {{SOPC_IdentifierType_String, 1, .Data.String = {sizeof("HiLimitTankLevel")-1, 1, (SOPC_Byte*) "HiLimitTankLevel"}}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 46},
                    false,
                    {{SOPC_IdentifierType_String, 1, .Data.String = {sizeof("LoLimitTankLevel")-1, 1, (SOPC_Byte*) "LoLimitTankLevel"}}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 35},
                    false,
                    {{SOPC_IdentifierType_String, 1, .Data.String = {sizeof("LevelAboveHigh")-1, 1, (SOPC_Byte*) "LevelAboveHigh"}}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 35},
                    false,
                    {{SOPC_IdentifierType_String, 1, .Data.String = {sizeof("LevelUnderLow")-1, 1, (SOPC_Byte*) "LevelUnderLow"}}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 47},
                    true,
                    {{SOPC_IdentifierType_String, 1, .Data.String = {sizeof("FluidTank")-1, 1, (SOPC_Byte*) "FluidTank"}}, {0, 0, NULL}, 0},
                }
            },
            .Value = 
                  {true,
                   SOPC_UInt32_Id,
                   SOPC_VariantArrayType_SingleValue,
                   {.Uint32 = 45}},
            .DataType = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 11},
            .ValueRank = (-1),
            .AccessLevel = 1,
        }}
    },
    {
        OpcUa_NodeClass_Variable,
        0x00,
        {0, 0},
        {.variable={
            .encodeableType = &OpcUa_VariableNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_String, 1, .Data.String = {sizeof("EUTankLevel")-1, 1, (SOPC_Byte*) "EUTankLevel"}},
            .NodeClass = OpcUa_NodeClass_Variable,
            .BrowseName = {1, {sizeof("EUTankLevel")-1, 1, (SOPC_Byte*) "EUTankLevel"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("EngineeringUnits")-1, 1, (SOPC_Byte*) "EngineeringUnits"}},
            .Description = {{0, 0, NULL}, {sizeof("Units for the fill level")-1, 1, (SOPC_Byte*) "Units for the fill level"}},
            .NoOfReferences = 2,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 40},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 68}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 46},
                    true,
                    {{SOPC_IdentifierType_String, 1, .Data.String = {sizeof("TankLevel")-1, 1, (SOPC_Byte*) "TankLevel"}}, {0, 0, NULL}, 0},
                }
            },
            .Value = 
                  {true,
                   SOPC_UInt32_Id,
                   SOPC_VariantArrayType_SingleValue,
                   {.Uint32 = 46}},
            .DataType = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 887},
            .ValueRank = (-1),
            .AccessLevel = 1,
        }}
    },
    {
        OpcUa_NodeClass_Variable,
        0x00,
        {0, 0},
        {.variable={
            .encodeableType = &OpcUa_VariableNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_String, 1, .Data.String = {sizeof("EURangeTankLevel")-1, 1, (SOPC_Byte*) "EURangeTankLevel"}},
            .NodeClass = OpcUa_NodeClass_Variable,
            .BrowseName = {1, {sizeof("EURangeTankLevel")-1, 1, (SOPC_Byte*) "EURangeTankLevel"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("EURange")-1, 1, (SOPC_Byte*) "EURange"}},
            .Description = {{0, 0, NULL}, {sizeof("Value range for the fluid tank")-1, 1, (SOPC_Byte*) "Value range for the fluid tank"}},
            .NoOfReferences = 2,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 40},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 68}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 46},
                    true,
                    {{SOPC_IdentifierType_String, 1, .Data.String = {sizeof("TankLevel")-1, 1, (SOPC_Byte*) "TankLevel"}}, {0, 0, NULL}, 0},
                }
            },
            .Value = 
                  {true,
                   SOPC_UInt32_Id,
                   SOPC_VariantArrayType_SingleValue,
                   {.Uint32 = 47}},
            .DataType = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 884},
            .ValueRank = (-1),
            .AccessLevel = 1,
        }}
    },
    {
        OpcUa_NodeClass_Variable,
        0x00,
        {0, 0},
        {.variable={
            .encodeableType = &OpcUa_VariableNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_String, 1, .Data.String = {sizeof("HiLimitTankLevel")-1, 1, (SOPC_Byte*) "HiLimitTankLevel"}},
            .NodeClass = OpcUa_NodeClass_Variable,
            .BrowseName = {1, {sizeof("HiLimit")-1, 1, (SOPC_Byte*) "HiLimit"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("HiLimit")-1, 1, (SOPC_Byte*) "HiLimit"}},
            .Description = {{0, 0, NULL}, {0, 0, NULL}},
            .NoOfReferences = 2,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 40},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 68}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 47},
                    true,
                    {{SOPC_IdentifierType_String, 1, .Data.String = {sizeof("TankLevel")-1, 1, (SOPC_Byte*) "TankLevel"}}, {0, 0, NULL}, 0},
                }
            },
            .Value = 
                  {true,
                   SOPC_UInt32_Id,
                   SOPC_VariantArrayType_SingleValue,
                   {.Uint32 = 48}},
            .DataType = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 11},
            .ValueRank = (-1),
            .AccessLevel = 3,
        }}
    },
    {
        OpcUa_NodeClass_Variable,
        0x00,
        {0, 0},
        {.variable={
            .encodeableType = &OpcUa_VariableNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_String, 1, .Data.String = {sizeof("LoLimitTankLevel")-1, 1, (SOPC_Byte*) "LoLimitTankLevel"}},
            .NodeClass = OpcUa_NodeClass_Variable,
            .BrowseName = {1, {sizeof("LoLimit")-1, 1, (SOPC_Byte*) "LoLimit"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("LoLimit")-1, 1, (SOPC_Byte*) "LoLimit"}},
            .Description = {{0, 0, NULL}, {0, 0, NULL}},
            .NoOfReferences = 2,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 40},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 68}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 47},
                    true,
                    {{SOPC_IdentifierType_String, 1, .Data.String = {sizeof("TankLevel")-1, 1, (SOPC_Byte*) "TankLevel"}}, {0, 0, NULL}, 0},
                }
            },
            .Value = 
                  {true,
                   SOPC_UInt32_Id,
                   SOPC_VariantArrayType_SingleValue,
                   {.Uint32 = 49}},
            .DataType = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 11},
            .ValueRank = (-1),
            .AccessLevel = 3,
        }}
    },
    {
        OpcUa_NodeClass_Variable,
        0x00,
        {0, 0},
        {.variable={
            .encodeableType = &OpcUa_VariableNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_String, 1, .Data.String = {sizeof("LevelAboveHigh")-1, 1, (SOPC_Byte*) "LevelAboveHigh"}},
            .NodeClass = OpcUa_NodeClass_Variable,
            .BrowseName = {1, {sizeof("LevelAboveHigh")-1, 1, (SOPC_Byte*) "LevelAboveHigh"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("Overflow Warning")-1, 1, (SOPC_Byte*) "Overflow Warning"}},
            .Description = {{0, 0, NULL}, {0, 0, NULL}},
            .NoOfReferences = 2,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 40},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 63}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 47},
                    true,
                    {{SOPC_IdentifierType_String, 1, .Data.String = {sizeof("TankLevel")-1, 1, (SOPC_Byte*) "TankLevel"}}, {0, 0, NULL}, 0},
                }
            },
            .Value = 
                  {true,
                   SOPC_UInt32_Id,
                   SOPC_VariantArrayType_SingleValue,
                   {.Uint32 = 50}},
            .DataType = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 1},
            .ValueRank = (-1),
            .AccessLevel = 1,
        }}
    },
    {
        OpcUa_NodeClass_Variable,
        0x00,
        {0, 0},
        {.variable={
            .encodeableType = &OpcUa_VariableNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_String, 1, .Data.String = {sizeof("LevelUnderLow")-1, 1, (SOPC_Byte*) "LevelUnderLow"}},
            .NodeClass = OpcUa_NodeClass_Variable,
            .BrowseName = {1, {sizeof("LevelUnderLow")-1, 1, (SOPC_Byte*) "LevelUnderLow"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("Underflow Warning")-1, 1, (SOPC_Byte*) "Underflow Warning"}},
            .Description = {{0, 0, NULL}, {0, 0, NULL}},
            .NoOfReferences = 2,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 40},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 63}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 35},
                    true,
                    {{SOPC_IdentifierType_String, 1, .Data.String = {sizeof("TankLevel")-1, 1, (SOPC_Byte*) "TankLevel"}}, {0, 0, NULL}, 0},
                }
            },
            .Value = 
                  {true,
                   SOPC_UInt32_Id,
                   SOPC_VariantArrayType_SingleValue,
                   {.Uint32 = 51}},
            .DataType = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 1},
            .ValueRank = (-1),
            .AccessLevel = 1,
        }}
    },
    {
        OpcUa_NodeClass_Variable,
        0x00,
        {0, 0},
        {.variable={
            .encodeableType = &OpcUa_VariableNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_String, 1, .Data.String = {sizeof("TankWeight")-1, 1, (SOPC_Byte*) "TankWeight"}},
            .NodeClass = OpcUa_NodeClass_Variable,
            .BrowseName = {1, {sizeof("TankWeight")-1, 1, (SOPC_Byte*) "TankWeight"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("TankWeight")-1, 1, (SOPC_Byte*) "TankWeight"}},
            .Description = {{0, 0, NULL}, {sizeof("CurrentGross Weight of the Reservoir")-1, 1, (SOPC_Byte*) "CurrentGross Weight of the Reservoir"}},
            .NoOfReferences = 6,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 40},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 2368}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 46},
                    false,
                    {{SOPC_IdentifierType_String, 1, .Data.String = {sizeof("EUTankWeight")-1, 1, (SOPC_Byte*) "EUTankWeight"}}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 46},
                    false,
                    {{SOPC_IdentifierType_String, 1, .Data.String = {sizeof("EURangeTankWeight")-1, 1, (SOPC_Byte*) "EURangeTankWeight"}}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 35},
                    false,
                    {{SOPC_IdentifierType_String, 1, .Data.String = {sizeof("Force")-1, 1, (SOPC_Byte*) "Force"}}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 47},
                    false,
                    {{SOPC_IdentifierType_String, 1, .Data.String = {sizeof("Tara")-1, 1, (SOPC_Byte*) "Tara"}}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 47},
                    true,
                    {{SOPC_IdentifierType_String, 1, .Data.String = {sizeof("FluidTank")-1, 1, (SOPC_Byte*) "FluidTank"}}, {0, 0, NULL}, 0},
                }
            },
            .Value = 
                  {true,
                   SOPC_UInt32_Id,
                   SOPC_VariantArrayType_SingleValue,
                   {.Uint32 = 52}},
            .DataType = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 11},
            .ValueRank = (-1),
            .AccessLevel = 1,
        }}
    },
    {
        OpcUa_NodeClass_Variable,
        0x00,
        {0, 0},
        {.variable={
            .encodeableType = &OpcUa_VariableNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_String, 1, .Data.String = {sizeof("EUTankWeight")-1, 1, (SOPC_Byte*) "EUTankWeight"}},
            .NodeClass = OpcUa_NodeClass_Variable,
            .BrowseName = {1, {sizeof("EUTankWeight")-1, 1, (SOPC_Byte*) "EUTankWeight"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("EngineeringUnits")-1, 1, (SOPC_Byte*) "EngineeringUnits"}},
            .Description = {{0, 0, NULL}, {sizeof("Units for the tank weight")-1, 1, (SOPC_Byte*) "Units for the tank weight"}},
            .NoOfReferences = 2,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 40},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 68}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 46},
                    true,
                    {{SOPC_IdentifierType_String, 1, .Data.String = {sizeof("TankWeight")-1, 1, (SOPC_Byte*) "TankWeight"}}, {0, 0, NULL}, 0},
                }
            },
            .Value = 
                  {true,
                   SOPC_UInt32_Id,
                   SOPC_VariantArrayType_SingleValue,
                   {.Uint32 = 53}},
            .DataType = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 887},
            .ValueRank = (-1),
            .AccessLevel = 1,
        }}
    },
    {
        OpcUa_NodeClass_Variable,
        0x00,
        {0, 0},
        {.variable={
            .encodeableType = &OpcUa_VariableNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_String, 1, .Data.String = {sizeof("EURangeTankWeight")-1, 1, (SOPC_Byte*) "EURangeTankWeight"}},
            .NodeClass = OpcUa_NodeClass_Variable,
            .BrowseName = {1, {sizeof("EURangeTankWeight")-1, 1, (SOPC_Byte*) "EURangeTankWeight"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("EURange")-1, 1, (SOPC_Byte*) "EURange"}},
            .Description = {{0, 0, NULL}, {sizeof("Value range for the fluid tank")-1, 1, (SOPC_Byte*) "Value range for the fluid tank"}},
            .NoOfReferences = 2,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 40},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 68}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 46},
                    true,
                    {{SOPC_IdentifierType_String, 1, .Data.String = {sizeof("TankWeight")-1, 1, (SOPC_Byte*) "TankWeight"}}, {0, 0, NULL}, 0},
                }
            },
            .Value = 
                  {true,
                   SOPC_UInt32_Id,
                   SOPC_VariantArrayType_SingleValue,
                   {.Uint32 = 54}},
            .DataType = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 884},
            .ValueRank = (-1),
            .AccessLevel = 1,
        }}
    },
    {
        OpcUa_NodeClass_Variable,
        0x00,
        {0, 0},
        {.variable={
            .encodeableType = &OpcUa_VariableNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_String, 1, .Data.String = {sizeof("Tara")-1, 1, (SOPC_Byte*) "Tara"}},
            .NodeClass = OpcUa_NodeClass_Variable,
            .BrowseName = {1, {sizeof("Tara")-1, 1, (SOPC_Byte*) "Tara"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("Tara")-1, 1, (SOPC_Byte*) "Tara"}},
            .Description = {{0, 0, NULL}, {sizeof("Current Tara of the Reservoir (R/W)")-1, 1, (SOPC_Byte*) "Current Tara of the Reservoir (R/W)"}},
            .NoOfReferences = 4,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 40},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 2368}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 46},
                    false,
                    {{SOPC_IdentifierType_String, 1, .Data.String = {sizeof("EUTara")-1, 1, (SOPC_Byte*) "EUTara"}}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 46},
                    false,
                    {{SOPC_IdentifierType_String, 1, .Data.String = {sizeof("EURangeTara")-1, 1, (SOPC_Byte*) "EURangeTara"}}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 47},
                    true,
                    {{SOPC_IdentifierType_String, 1, .Data.String = {sizeof("TankWeight")-1, 1, (SOPC_Byte*) "TankWeight"}}, {0, 0, NULL}, 0},
                }
            },
            .Value = 
                  {true,
                   SOPC_UInt32_Id,
                   SOPC_VariantArrayType_SingleValue,
                   {.Uint32 = 55}},
            .DataType = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 11},
            .ValueRank = (-1),
            .AccessLevel = 3,
        }}
    },
    {
        OpcUa_NodeClass_Variable,
        0x00,
        {0, 0},
        {.variable={
            .encodeableType = &OpcUa_VariableNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_String, 1, .Data.String = {sizeof("EUTara")-1, 1, (SOPC_Byte*) "EUTara"}},
            .NodeClass = OpcUa_NodeClass_Variable,
            .BrowseName = {1, {sizeof("EUTara")-1, 1, (SOPC_Byte*) "EUTara"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("EngineeringUnits")-1, 1, (SOPC_Byte*) "EngineeringUnits"}},
            .Description = {{0, 0, NULL}, {sizeof("Units for the tank tara")-1, 1, (SOPC_Byte*) "Units for the tank tara"}},
            .NoOfReferences = 2,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 40},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 68}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 46},
                    true,
                    {{SOPC_IdentifierType_String, 1, .Data.String = {sizeof("Tara")-1, 1, (SOPC_Byte*) "Tara"}}, {0, 0, NULL}, 0},
                }
            },
            .Value = 
                  {true,
                   SOPC_UInt32_Id,
                   SOPC_VariantArrayType_SingleValue,
                   {.Uint32 = 56}},
            .DataType = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 887},
            .ValueRank = (-1),
            .AccessLevel = 1,
        }}
    },
    {
        OpcUa_NodeClass_Variable,
        0x00,
        {0, 0},
        {.variable={
            .encodeableType = &OpcUa_VariableNode_EncodeableType,
            .NodeId = {SOPC_IdentifierType_String, 1, .Data.String = {sizeof("EURangeTara")-1, 1, (SOPC_Byte*) "EURangeTara"}},
            .NodeClass = OpcUa_NodeClass_Variable,
            .BrowseName = {1, {sizeof("EURangeTara")-1, 1, (SOPC_Byte*) "EURangeTara"}},
            .DisplayName = {{0, 0, NULL}, {sizeof("EURange")-1, 1, (SOPC_Byte*) "EURange"}},
            .Description = {{0, 0, NULL}, {sizeof("Value range for the tara of the fluid tank")-1, 1, (SOPC_Byte*) "Value range for the tara of the fluid tank"}},
            .NoOfReferences = 2,
            .References = (const OpcUa_ReferenceNode[]) {
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 40},
                    false,
                    {{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 68}, {0, 0, NULL}, 0},
                },
                {
                    &OpcUa_ReferenceNode_EncodeableType,
                    {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 46},
                    true,
                    {{SOPC_IdentifierType_String, 1, .Data.String = {sizeof("Tara")-1, 1, (SOPC_Byte*) "Tara"}}, {0, 0, NULL}, 0},
                }
            },
            .Value = 
                  {true,
                   SOPC_UInt32_Id,
                   SOPC_VariantArrayType_SingleValue,
                   {.Uint32 = 57}},
            .DataType = {SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 884},
            .ValueRank = (-1),
            .AccessLevel = 1,
        }}
    },
};
SOPC_GCC_DIAGNOSTIC_RESTORE
const uint32_t SOPC_Embedded_AddressSpace_nNodes = 147;

// Index is provided by the corresponding Variable UInt32 Variant in SOPC_Embedded_AddressSpace_Nodes
SOPC_Variant SOPC_Embedded_VariableVariant[58] = {
{true, SOPC_Null_Id, SOPC_VariantArrayType_SingleValue, {0}},
{true, SOPC_Null_Id, SOPC_VariantArrayType_SingleValue, {0}},
{true, SOPC_Null_Id, SOPC_VariantArrayType_SingleValue, {0}},
{true, SOPC_Null_Id, SOPC_VariantArrayType_SingleValue, {0}},
{true, SOPC_Null_Id, SOPC_VariantArrayType_SingleValue, {0}},
{true, SOPC_Null_Id, SOPC_VariantArrayType_SingleValue, {0}},
{true, SOPC_Null_Id, SOPC_VariantArrayType_SingleValue, {0}},
{true, SOPC_Null_Id, SOPC_VariantArrayType_SingleValue, {0}},
{true, SOPC_Null_Id, SOPC_VariantArrayType_SingleValue, {0}},
{true, SOPC_Null_Id, SOPC_VariantArrayType_SingleValue, {0}},
{true, SOPC_Null_Id, SOPC_VariantArrayType_SingleValue, {0}},

                  {true,
                   SOPC_Int32_Id,
                   SOPC_VariantArrayType_SingleValue,
                   {.Int32 = 0}},
{true, SOPC_Null_Id, SOPC_VariantArrayType_SingleValue, {0}},

                  {true,
                   SOPC_String_Id,
                   SOPC_VariantArrayType_SingleValue,
                   {.String = {sizeof("InES Embedded PubSub Server")-1, 1, (SOPC_Byte*) "InES Embedded PubSub Server"}}},
{true, SOPC_Null_Id, SOPC_VariantArrayType_SingleValue, {0}},

                  {true,
                   SOPC_String_Id,
                   SOPC_VariantArrayType_SingleValue,
                   {.String = {sizeof("Institute of Embedded Systems - Communication Network Engineering")-1, 1, (SOPC_Byte*) "Institute of Embedded Systems - Communication Network Engineering"}}},

                  {true,
                   SOPC_String_Id,
                   SOPC_VariantArrayType_SingleValue,
                   {.String = {sizeof("0.1.1")-1, 1, (SOPC_Byte*) "0.1.1"}}},

                  {true,
                   SOPC_String_Id,
                   SOPC_VariantArrayType_SingleValue,
                   {.String = {sizeof("Experimental")-1, 1, (SOPC_Byte*) "Experimental"}}},
{true, SOPC_Null_Id, SOPC_VariantArrayType_SingleValue, {0}},
{true, SOPC_Null_Id, SOPC_VariantArrayType_SingleValue, {0}},
{true, SOPC_Null_Id, SOPC_VariantArrayType_SingleValue, {0}},
{true, SOPC_Null_Id, SOPC_VariantArrayType_SingleValue, {0}},
{true, SOPC_Null_Id, SOPC_VariantArrayType_SingleValue, {0}},
{true, SOPC_Null_Id, SOPC_VariantArrayType_SingleValue, {0}},
{true, SOPC_Null_Id, SOPC_VariantArrayType_SingleValue, {0}},
{true, SOPC_Null_Id, SOPC_VariantArrayType_SingleValue, {0}},
{true, SOPC_Null_Id, SOPC_VariantArrayType_SingleValue, {0}},
{true, SOPC_Null_Id, SOPC_VariantArrayType_SingleValue, {0}},

                  {true,
                   SOPC_Byte_Id,
                   SOPC_VariantArrayType_SingleValue,
                   {.Byte = 3}},

                  {true,
                   SOPC_String_Id,
                   SOPC_VariantArrayType_SingleValue,
                   {.String = {sizeof("PLACEHOLDER")-1, 1, (SOPC_Byte*) "PLACEHOLDER"}}},

                  {true,
                   SOPC_Byte_Id,
                   SOPC_VariantArrayType_SingleValue,
                   {.Byte = 2}},

                  {true,
                   SOPC_Int32_Id,
                   SOPC_VariantArrayType_SingleValue,
                   {.Int32 = 0}},

                  {true,
                   SOPC_Int32_Id,
                   SOPC_VariantArrayType_SingleValue,
                   {.Int32 = 0}},

                  {true,
                   SOPC_UInt64_Id,
                   SOPC_VariantArrayType_SingleValue,
                   {.Uint64 = 10000000UL}},

                  {true,
                   SOPC_ExtensionObject_Id,
                   SOPC_VariantArrayType_SingleValue,
                   {.ExtObject = 
                  (SOPC_ExtensionObject[])
                  {{{{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 889}, {0, 0, NULL}, 0},SOPC_ExtObjBodyEncoding_Object,.Body.Object = {
               (OpcUa_EUInformation[])
               {{&OpcUa_EUInformation_EncodeableType,
                 {sizeof("http://www.opcfoundation.org/UA/units/un/cefact")-1, 1, (SOPC_Byte*) "http://www.opcfoundation.org/UA/units/un/cefact"},
                 4337968,
                 {{0, 0, NULL}, {sizeof("bit/s")-1, 1, (SOPC_Byte*) "bit/s"}},                 
                 {{0, 0, NULL}, {sizeof("bit per second")-1, 1, (SOPC_Byte*) "bit per second"}}}}
            , &OpcUa_EUInformation_EncodeableType}}}
               }},
{true, SOPC_Null_Id, SOPC_VariantArrayType_SingleValue, {0}},

                  {true,
                   SOPC_ExtensionObject_Id,
                   SOPC_VariantArrayType_SingleValue,
                   {.ExtObject = 
                  (SOPC_ExtensionObject[])
                  {{{{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 889}, {0, 0, NULL}, 0},SOPC_ExtObjBodyEncoding_Object,.Body.Object = {
               (OpcUa_EUInformation[])
               {{&OpcUa_EUInformation_EncodeableType,
                 {sizeof("http://www.opcfoundation.org/UA/units/un/cefact")-1, 1, (SOPC_Byte*) "http://www.opcfoundation.org/UA/units/un/cefact"},
                 5655636,
                 {{0, 0, NULL}, {sizeof("V")-1, 1, (SOPC_Byte*) "V"}},                 
                 {{0, 0, NULL}, {sizeof("volt")-1, 1, (SOPC_Byte*) "volt"}}}}
            , &OpcUa_EUInformation_EncodeableType}}}
               }},

                  {true,
                   SOPC_ExtensionObject_Id,
                   SOPC_VariantArrayType_SingleValue,
                   {.ExtObject = 
                  (SOPC_ExtensionObject[])
                  {{{{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 886}, {0, 0, NULL}, 0},SOPC_ExtObjBodyEncoding_Object,.Body.Object = {
               (OpcUa_Range[])
               {{&OpcUa_Range_EncodeableType,
                 0.0,
                 3.3}}
            , &OpcUa_Range_EncodeableType}}}
               }},

                  {true,
                   SOPC_Double_Id,
                   SOPC_VariantArrayType_SingleValue,
                   {.Doublev = 6.25}},
{true, SOPC_Null_Id, SOPC_VariantArrayType_SingleValue, {0}},

                  {true,
                   SOPC_ExtensionObject_Id,
                   SOPC_VariantArrayType_SingleValue,
                   {.ExtObject = 
                  (SOPC_ExtensionObject[])
                  {{{{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 889}, {0, 0, NULL}, 0},SOPC_ExtObjBodyEncoding_Object,.Body.Object = {
               (OpcUa_EUInformation[])
               {{&OpcUa_EUInformation_EncodeableType,
                 {sizeof("http://www.opcfoundation.org/UA/units/un/cefact")-1, 1, (SOPC_Byte*) "http://www.opcfoundation.org/UA/units/un/cefact"},
                 5129559,
                 {{0, 0, NULL}, {sizeof("N")-1, 1, (SOPC_Byte*) "N"}},                 
                 {{0, 0, NULL}, {sizeof("newton")-1, 1, (SOPC_Byte*) "newton"}}}}
            , &OpcUa_EUInformation_EncodeableType}}}
               }},

                  {true,
                   SOPC_ExtensionObject_Id,
                   SOPC_VariantArrayType_SingleValue,
                   {.ExtObject = 
                  (SOPC_ExtensionObject[])
                  {{{{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 886}, {0, 0, NULL}, 0},SOPC_ExtObjBodyEncoding_Object,.Body.Object = {
               (OpcUa_Range[])
               {{&OpcUa_Range_EncodeableType,
                 0.0,
                 30.0}}
            , &OpcUa_Range_EncodeableType}}}
               }},

                  {true,
                   SOPC_String_Id,
                   SOPC_VariantArrayType_SingleValue,
                   {.String = {sizeof("Kistler Instrumente AG")-1, 1, (SOPC_Byte*) "Kistler Instrumente AG"}}},

                  {true,
                   SOPC_String_Id,
                   SOPC_VariantArrayType_SingleValue,
                   {.String = {sizeof("9321C")-1, 1, (SOPC_Byte*) "9321C"}}},

                  {true,
                   SOPC_String_Id,
                   SOPC_VariantArrayType_SingleValue,
                   {.String = {sizeof("5658541")-1, 1, (SOPC_Byte*) "5658541"}}},
{true, SOPC_Null_Id, SOPC_VariantArrayType_SingleValue, {0}},

                  {true,
                   SOPC_ExtensionObject_Id,
                   SOPC_VariantArrayType_SingleValue,
                   {.ExtObject = 
                  (SOPC_ExtensionObject[])
                  {{{{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 889}, {0, 0, NULL}, 0},SOPC_ExtObjBodyEncoding_Object,.Body.Object = {
               (OpcUa_EUInformation[])
               {{&OpcUa_EUInformation_EncodeableType,
                 {sizeof("http://www.opcfoundation.org/UA/units/un/cefact")-1, 1, (SOPC_Byte*) "http://www.opcfoundation.org/UA/units/un/cefact"},
                 5002322,
                 {{0, 0, NULL}, {sizeof("l")-1, 1, (SOPC_Byte*) "l"}},                 
                 {{0, 0, NULL}, {sizeof("litre")-1, 1, (SOPC_Byte*) "litre"}}}}
            , &OpcUa_EUInformation_EncodeableType}}}
               }},

                  {true,
                   SOPC_ExtensionObject_Id,
                   SOPC_VariantArrayType_SingleValue,
                   {.ExtObject = 
                  (SOPC_ExtensionObject[])
                  {{{{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 886}, {0, 0, NULL}, 0},SOPC_ExtObjBodyEncoding_Object,.Body.Object = {
               (OpcUa_Range[])
               {{&OpcUa_Range_EncodeableType,
                 0,
                 3}}
            , &OpcUa_Range_EncodeableType}}}
               }},

                  {true,
                   SOPC_Double_Id,
                   SOPC_VariantArrayType_SingleValue,
                   {.Doublev = 0.8}},

                  {true,
                   SOPC_Double_Id,
                   SOPC_VariantArrayType_SingleValue,
                   {.Doublev = 0.2}},

                  {true,
                   SOPC_Boolean_Id,
                   SOPC_VariantArrayType_SingleValue,
                   {.Boolean = false}},

                  {true,
                   SOPC_Boolean_Id,
                   SOPC_VariantArrayType_SingleValue,
                   {.Boolean = false}},
{true, SOPC_Null_Id, SOPC_VariantArrayType_SingleValue, {0}},

                  {true,
                   SOPC_ExtensionObject_Id,
                   SOPC_VariantArrayType_SingleValue,
                   {.ExtObject = 
                  (SOPC_ExtensionObject[])
                  {{{{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 889}, {0, 0, NULL}, 0},SOPC_ExtObjBodyEncoding_Object,.Body.Object = {
               (OpcUa_EUInformation[])
               {{&OpcUa_EUInformation_EncodeableType,
                 {sizeof("http://www.opcfoundation.org/UA/units/un/cefact")-1, 1, (SOPC_Byte*) "http://www.opcfoundation.org/UA/units/un/cefact"},
                 4933453,
                 {{0, 0, NULL}, {sizeof("kg")-1, 1, (SOPC_Byte*) "kg"}},                 
                 {{0, 0, NULL}, {sizeof("kilogram")-1, 1, (SOPC_Byte*) "kilogram"}}}}
            , &OpcUa_EUInformation_EncodeableType}}}
               }},

                  {true,
                   SOPC_ExtensionObject_Id,
                   SOPC_VariantArrayType_SingleValue,
                   {.ExtObject = 
                  (SOPC_ExtensionObject[])
                  {{{{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 886}, {0, 0, NULL}, 0},SOPC_ExtObjBodyEncoding_Object,.Body.Object = {
               (OpcUa_Range[])
               {{&OpcUa_Range_EncodeableType,
                 0.1,
                 1.1}}
            , &OpcUa_Range_EncodeableType}}}
               }},

                  {true,
                   SOPC_Double_Id,
                   SOPC_VariantArrayType_SingleValue,
                   {.Doublev = 0.4}},

                  {true,
                   SOPC_ExtensionObject_Id,
                   SOPC_VariantArrayType_SingleValue,
                   {.ExtObject = 
                  (SOPC_ExtensionObject[])
                  {{{{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 889}, {0, 0, NULL}, 0},SOPC_ExtObjBodyEncoding_Object,.Body.Object = {
               (OpcUa_EUInformation[])
               {{&OpcUa_EUInformation_EncodeableType,
                 {sizeof("http://www.opcfoundation.org/UA/units/un/cefact")-1, 1, (SOPC_Byte*) "http://www.opcfoundation.org/UA/units/un/cefact"},
                 4933453,
                 {{0, 0, NULL}, {sizeof("kg")-1, 1, (SOPC_Byte*) "kg"}},                 
                 {{0, 0, NULL}, {sizeof("kilogram")-1, 1, (SOPC_Byte*) "kilogram"}}}}
            , &OpcUa_EUInformation_EncodeableType}}}
               }},

                  {true,
                   SOPC_ExtensionObject_Id,
                   SOPC_VariantArrayType_SingleValue,
                   {.ExtObject = 
                  (SOPC_ExtensionObject[])
                  {{{{SOPC_IdentifierType_Numeric, 0, .Data.Numeric = 886}, {0, 0, NULL}, 0},SOPC_ExtObjBodyEncoding_Object,.Body.Object = {
               (OpcUa_Range[])
               {{&OpcUa_Range_EncodeableType,
                 0.0,
                 0.3}}
            , &OpcUa_Range_EncodeableType}}}
               }},
};
const uint32_t SOPC_Embedded_VariableVariant_nb = 58;
