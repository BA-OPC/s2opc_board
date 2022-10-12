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

#include <stdbool.h>
#include <stdio.h>

#include "sopc_common_constants.h"
#include "sopc_macros.h"
#include "sopc_mem_alloc.h"
#include "sopc_pubsub_local_sks.h"

struct security_config_type
{
    const char* signing_key;
    const char* encrypt_key;
    const char* key_nonce;

    // Used if configuration static is used.
    // In that case, previous path will be not used
    // by SOPC_LocalSKS_GetSecurityKeys
    bool bUseStaticConfig;
    const uint8_t* sSigningKey;
    uint32_t uwSigningKeySize;
    const uint8_t* sEncryptKey;
    uint32_t uwEncryptKeySize;
    const uint8_t* sKeyNonce;
    uint32_t uwKeyNonceSize;
};

static struct security_config_type pubsub_key_bunch = {.signing_key = NULL,
                                                       .encrypt_key = NULL,
                                                       .key_nonce = NULL,
                                                       .bUseStaticConfig = false,
                                                       .uwSigningKeySize = 0,
                                                       .uwEncryptKeySize = 0,
                                                       .uwKeyNonceSize = 0,
                                                       .sSigningKey = NULL,
                                                       .sEncryptKey = NULL,
                                                       .sKeyNonce = NULL};

void SOPC_KeyBunch_init(const char* pathSigningKey, const char* pathEncryptKey, const char* pathKeyNonce)
{
    // SOPC_LocalSKS_GetSecurityKeys will get key from files
    pubsub_key_bunch.signing_key = pathSigningKey;
    pubsub_key_bunch.encrypt_key = pathEncryptKey;
    pubsub_key_bunch.key_nonce = pathKeyNonce;
    pubsub_key_bunch.bUseStaticConfig = false;
    pubsub_key_bunch.sSigningKey = NULL;
    pubsub_key_bunch.sEncryptKey = NULL;
    pubsub_key_bunch.sKeyNonce = NULL;
    pubsub_key_bunch.uwSigningKeySize = 0;
    pubsub_key_bunch.uwEncryptKeySize = 0;
    pubsub_key_bunch.uwKeyNonceSize = 0;
}

void SOPC_KeyBunch_init_static(const uint8_t* signingKey,
                               uint32_t lenSigningKey,
                               const uint8_t* encryptKey,
                               uint32_t lenEncryptKey,
                               const uint8_t* keyNonce,
                               uint32_t lenKeyNonce)
{
    // SOPC_LocalSKS_GetSecurityKeys will get key from constant uint8_t buffer
    pubsub_key_bunch.signing_key = NULL;
    pubsub_key_bunch.encrypt_key = NULL;
    pubsub_key_bunch.key_nonce = NULL;
    pubsub_key_bunch.bUseStaticConfig = true;
    pubsub_key_bunch.sSigningKey = signingKey;
    pubsub_key_bunch.sEncryptKey = encryptKey;
    pubsub_key_bunch.sKeyNonce = keyNonce;
    pubsub_key_bunch.uwSigningKeySize = lenSigningKey;
    pubsub_key_bunch.uwEncryptKeySize = lenEncryptKey;
    pubsub_key_bunch.uwKeyNonceSize = lenKeyNonce;
}

SOPC_KeyBunch_Keys* SOPC_LocalSKS_GetSecurityKeys(uint32_t groupid, uint32_t tokenId)
{
    if (SOPC_PUBSUB_SKS_DEFAULT_GROUPID != groupid)
    {
        return NULL;
    }
    if (SOPC_PUBSUB_SKS_DEFAULT_TOKENID != tokenId && SOPC_PUBSUB_SKS_CURRENT_TOKENID != tokenId)
    { // Token Id is not managed
        return NULL;
    }
    SOPC_KeyBunch_Keys* keys = SOPC_Calloc(1, sizeof(SOPC_KeyBunch_Keys));
    if (NULL == keys)
    {
        return NULL;
    }
    keys->tokenId = SOPC_PUBSUB_SKS_DEFAULT_TOKENID;

    if (pubsub_key_bunch.bUseStaticConfig)
    {
        SOPC_GCC_DIAGNOSTIC_IGNORE_CAST_CONST

        SOPC_CONSOLE_PRINTF("# Load security signing key from static buffers... slen = %u\n",
                            pubsub_key_bunch.uwSigningKeySize);

        keys->signingKey = SOPC_SecretBuffer_NewFromExposedBuffer((SOPC_ExposedBuffer*) pubsub_key_bunch.sSigningKey,
                                                                  pubsub_key_bunch.uwSigningKeySize);

        SOPC_CONSOLE_PRINTF("# Load security encrypt key from static buffers... slen = %u\n",
                            pubsub_key_bunch.uwEncryptKeySize);

        keys->encryptKey = SOPC_SecretBuffer_NewFromExposedBuffer((SOPC_ExposedBuffer*) pubsub_key_bunch.sEncryptKey,
                                                                  pubsub_key_bunch.uwEncryptKeySize);

        SOPC_CONSOLE_PRINTF("# Load security nonce key from static buffers... slen = %u\n",
                            pubsub_key_bunch.uwKeyNonceSize);

        keys->keyNonce = SOPC_SecretBuffer_NewFromExposedBuffer((SOPC_ExposedBuffer*) pubsub_key_bunch.sKeyNonce,
                                                                pubsub_key_bunch.uwKeyNonceSize);
        SOPC_GCC_DIAGNOSTIC_RESTORE
    }
    else
    {
        keys->signingKey = SOPC_SecretBuffer_NewFromFile(pubsub_key_bunch.signing_key);
        keys->encryptKey = SOPC_SecretBuffer_NewFromFile(pubsub_key_bunch.encrypt_key);
        keys->keyNonce = SOPC_SecretBuffer_NewFromFile(pubsub_key_bunch.key_nonce);
    }

    if (NULL == keys->signingKey || NULL == keys->encryptKey || NULL == keys->keyNonce)
    {
        SOPC_KeyBunch_Keys_Delete(keys);
        SOPC_Free(keys);
        keys = NULL;
    }
    return keys;
}

void SOPC_KeyBunch_Keys_Delete(SOPC_KeyBunch_Keys* keys)
{
    if (NULL != keys)
    {
        SOPC_SecretBuffer_DeleteClear(keys->signingKey);
        keys->signingKey = NULL;
        SOPC_SecretBuffer_DeleteClear(keys->encryptKey);
        keys->encryptKey = NULL;
        SOPC_SecretBuffer_DeleteClear(keys->keyNonce);
        keys->keyNonce = NULL;
    }
}
