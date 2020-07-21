#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# Licensed to Systerel under one or more contributor license
# agreements. See the NOTICE file distributed with this work
# for additional information regarding copyright ownership.
# Systerel licenses this file to you under the Apache
# License, Version 2.0 (the "License"); you may not use this
# file except in compliance with the License. You may obtain
# a copy of the License at
#
#   http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing,
# software distributed under the License is distributed on an
# "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
# KIND, either express or implied.  See the License for the
# specific language governing permissions and limitations
# under the License.


from cffi import FFI
import os

ffibuilder = FFI()
# TODO: generate this file
header = open('./s2opc_expanded.h').read()
ffibuilder.cdef(header + r'''
    # 1 "cffi-cdef"
    extern "Python" void _callback_log(SOPC_Log_Level log_level, SOPC_LibSub_CstString text);
    extern "Python" void _callback_disconnected(SOPC_LibSub_ConnectionId c_id);
    extern "Python" void _callback_datachanged(SOPC_LibSub_ConnectionId c_id, SOPC_LibSub_DataId d_id, SOPC_LibSub_Value* value);
    extern "Python" void _callback_client_event(SOPC_LibSub_ConnectionId c_id, SOPC_LibSub_ApplicativeEvent event, SOPC_StatusCode status, const void* response, uintptr_t responseContext);

    void SOPC_DataValue_Delete(SOPC_DataValue *datavalue);
''')

source = r'''
    #include "s2opc_expanded.h"

    const char* SOPC_SecurityPolicy_None_URI = "http://opcfoundation.org/UA/SecurityPolicy#None";
    const char* SOPC_SecurityPolicy_Basic128Rsa15 = "http://opcfoundation.org/UA/SecurityPolicy#Basic128Rsa15";
    const char* SOPC_SecurityPolicy_Basic256_URI = "http://opcfoundation.org/UA/SecurityPolicy#Basic256";
    const char* SOPC_SecurityPolicy_Basic256Sha256_URI = "http://opcfoundation.org/UA/SecurityPolicy#Basic256Sha256";
    const uint8_t SOPC_SecurityMode_None_Mask = 0x01;
    const uint8_t SOPC_SecurityMode_Sign_Mask = 0x02;
    const uint8_t SOPC_SecurityMode_SignAndEncrypt_Mask = 0x04;
    const uint8_t SOPC_SecurityMode_Any_Mask = 0x07;
    const uint8_t SOPC_MaxSecuPolicies_CFG = 5;

    void SOPC_DataValue_Delete(SOPC_DataValue *datavalue)
    {
        SOPC_DataValue_Clear(datavalue);
        free(datavalue);
    }
'''

# It (is said to) produces faster code with set_source, and checks what it can on the types.
# However, it requires a gcc.
# The other way, dlopen, loads the ABI, is less safe, slower, but only requires the .so/.dll
# TODO: automatize configuration

if os.name == 'nt':
# Windows
    ffibuilder.set_source('_pys2opc',
                      source,
                      extra_link_args=['Advapi32.lib', 'ws2_32.lib', 's2opc_clientwrapper.lib', 's2opc_clientserver.lib', 's2opc_common.lib', 'mbedcrypto.lib', 'mbedtls.lib', 'mbedx509.lib'],
                      include_dirs=['.'],
                      library_dirs=['../lib/', # working dir should be located in build dir
                                    '../mbedtls_dir' #mbedtls libraries shall be copied here
                                    '.'],  # Ease compilation outside of the S2OPC project
                     )
else:
# Linux
    ffibuilder.set_source('_pys2opc',
                      source,
                      extra_link_args=['-ls2opc_clientwrapper', '-ls2opc_clientserver', '-ls2opc_common', '-lmbedcrypto', '-lmbedtls', '-lmbedx509'],
                      include_dirs=['.'],
                      library_dirs=['../lib/', # working dir should be located in build dir
                                    '.'],  # Ease compilation outside of the S2OPC project
                     )

if __name__ == '__main__':
    ffibuilder.compile(tmpdir='out')
