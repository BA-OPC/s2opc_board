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

import os
from opcua import ua
from opcua.crypto import security_policies

def secure_channels_connect(client, security_policy):
    cert_dir = os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', 'tests', 'data', 'cert')

    if (security_policy == security_policies.SecurityPolicyBasic256):
        client.set_security(security_policy,
        os.path.join(cert_dir, 'client_2k_cert.der'),
        os.path.join(cert_dir, 'client_2k_key.pem'),
        server_certificate_path=os.path.join(cert_dir, 'server_2k_cert.der'),
        mode=ua.MessageSecurityMode.Sign)

    client.connect()
    print('Connected')

