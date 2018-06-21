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

from time import sleep

def secure_channel_renew(client, logger):
    # Define renew time to 1 second
    client.secure_channel_timeout=1000
    # Renew with 1 second
    client.open_secure_channel(renew=True)
    print('Open Secure Channel renewed')
    # Check revised time
    logger.add_test('OPN renew test - renewed with given timeout value', client.secure_channel_timeout == 1000)
    # Change revised time to avoid client to renew the security token in time
    client.secure_channel_timeout=10000
    # Read a node to be sure we are using the new security token
    nid = 1001
    node = client.get_node(nid)
    value = node.get_value()
    print(' Value for Node {:03d}:'.format(nid), value)
    # Wait timeout of the security token
    sleep(2)
    print(' Error expected on next read:')
    # Try to read a node again
    try:
        node = client.get_node(nid)
        value = node.get_value()
    except:
        logger.add_test('OPN renew test - read refused after timeout', True)
    else:
        logger.add_test('OPN renew test - read refused after timeout', False)
    try:
        client.disconnect()
    except:
        None
