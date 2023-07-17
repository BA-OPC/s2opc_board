#!/bin/bash

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

cd `dirname $0`/../../../..
S2OPC_BASE=`pwd`
S2OPC_SRC=${S2OPC_BASE}/src
S2OPC_SAMPLE=${S2OPC_BASE}/samples/embedded
SRC_DIR=${FREERTOS_CORE_DIR}/Src/sopc

echo "Installing S2OPC for freeRTOS samples..."

# Check FreeRTOS

[[ -z ${FREERTOS_CORE_DIR} ]] && echo "[EE] FREERTOS_CORE_DIR must be set to Core folder of FREERTOS installation dir" && exit 1
! [[ -f ${FREERTOS_CORE_DIR}/Src/freertos.c ]] && echo "[EE] FREERTOS_CORE_DIR must point to Core folder of FREERTOS installation dir" && echo FREERTOS_CORE_DIR=$FREERTOS_CORE_DIR && exit 2
echo "[II] FreeRTOS found!"

# Check sample
[[ -z ${FREERTOS_SAMPLE} ]] && echo "[WW] FREERTOS_SAMPLE not defined, using default cli_pubsub_server" && FREERTOS_SAMPLE=cli_pubsub_server
! [[ -d ${S2OPC_SAMPLE}/${FREERTOS_SAMPLE} ]] && echo "[EE] Sample '${FREERTOS_SAMPLE}' not found. Check env var FREERTOS_SAMPLE"

echo "[II] Sample ${FREERTOS_SAMPLE} found!"

rm -fr  ${SRC_DIR} 2> /dev/null
mkdir -p ${SRC_DIR}/sample_src
mkdir -p ${SRC_DIR}/sample_inc

# copy source files to Core/Src
cp -ur ${S2OPC_SAMPLE}/${FREERTOS_SAMPLE}/src/* "${SRC_DIR}/sample_src" || exit 10
cp -ur ${S2OPC_SAMPLE}/platform_dep/freertos/src/* "${SRC_DIR}/sample_src" || exit 10
cp -ur ${S2OPC_SAMPLE}/platform_dep/mbedtls_config "${SRC_DIR}" || exit 11
cp -ur ${S2OPC_SRC}/Common "${SRC_DIR}" || exit 12
cp -ur ${S2OPC_SRC}/PubSub "${SRC_DIR}" || exit 13
cp -ur ${S2OPC_SRC}/ClientServer "${SRC_DIR}" || exit 14

mv ${SRC_DIR}/Common/helpers_platform_dep/freertos/s2opc_common_export.h_ ${SRC_DIR}/Common/helpers_platform_dep/freertos/s2opc_common_export.h

# Remove other platform ports
( cd ${SRC_DIR}/Common/helpers_platform_dep && for f in * ; do [ -d $f ] && [[ $f != freertos ]] && rm -rf $f ; done )
# Remove EXPAT-related files
find  ${SRC_DIR} -name "*expat*.c" -or -name "*config_xml*.c" -or -path "*xml_expat*.c" |xargs rm -fv
echo "[II] Source copied to ${S2OPC_SRC}"

# Move .h files to include folder
find  "${SRC_DIR}" -name "*.h" ! -path "*/sample_inc/*" -exec mv {} ${SRC_DIR}/sample_inc \;
cp -ur ${S2OPC_SAMPLE}/platform_dep/include/*.h ${SRC_DIR}/sample_inc || exit 14
echo "[II] Headers copied to ${SRC_DIR}/sample_inc"

# Patch main entry
sed -i 's/^.*USER CODE BEGIN 5.*$/  extern void sopc_main\(void\); sopc_main\(\);/g' ${FREERTOS_CORE_DIR}/Src/main.c || exit 3
echo "[II] Main entry patched to call S2OPC code"

# Patch freertos hooks
sed -i 's/\bvApplicationTickHook\b/__bvApplicationTickHook__/g' ${FREERTOS_CORE_DIR}/Src/freertos.c 
echo "[II] FreeRTOS hooks patched for 'vApplicationTickHook'"

sed -i 's/configUSE_TICK_HOOK *0/configUSE_TICK_HOOK 1/g' ${FREERTOS_CORE_DIR}/Inc/FreeRTOSConfig.h 
echo "[II] Patched configUSE_TICK_HOOK for FreeRTOS options"

# Patch LWIP_RAM_HEAP_POINTER for LwIP opts (https://github.com/STMicroelectronics/STM32CubeF4/issues/123)
f=$(find $(dirname ${FREERTOS_CORE_DIR}) -name 'lwipopts.h')
! [ -f "$f" ] && echo "could not find 'lwipopts.h'" && exit 20
sed -i 's/^\( *#define LWIP_RAM_HEAP_POINTER\)/\/\/\1/g' "$f"
echo "[II] LWIP_RAM_HEAP_POINTER patched in LwIP_opts"


