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

/** \file sopc_pki.h
 *
 * \brief Defines the common interface that a PKI should provide. This is a minimal interface, as the main
 * API for certificate and key manipulation is provided by KeyManager.
 *
 * The stack will not provide a full-blown configurable PKI.
 * The stack provides only a minimal, always safe validating PKI.
 *
 * The stack will not provide any advanced certificate storage.
 * You can use "user-specific" handles in the PKIProvider struct to implement more options.
 *
 * The pFnValidateCertificate function should not be called directly, but you should call
 * CryptoProvider_Certificate_Validate() instead.
 */

#ifndef SOPC_PKI_H_
#define SOPC_PKI_H_

#include "sopc_crypto_decl.h"
#include "sopc_crypto_provider.h"
#include "sopc_key_manager.h"
#include "sopc_toolkit_constants.h"

typedef SOPC_ReturnStatus (*SOPC_FnValidateCertificate)(const struct SOPC_PKIProvider* pPKI,
                                                        const SOPC_Certificate* pToValidate);

/**
 * \brief   The PKIProvider object defines the common interface for the Public Key Infrastructure.
 */
struct SOPC_PKIProvider
{
    /**
     *  \brief          The validation function, which is wrapped by CryptoProvider_Certificate_Validate().
     *
     *                  It implements the validation of the certificate. The CryptoProvider_Certificate_Validate()
     * assumes that a SOPC_STATUS_OK from this function means that the certificate can be trusted. Parameters are
     * validated by CryptoProvider_Certificate_Validate().
     *
     *  \param pPKI     A valid pointer to the PKIProvider.
     *  \param pToValidate  A valid pointer to the Certificate to validate.
     *
     *  \return         SOPC_STATUS_OK when the certificate is successfully validated, and
     * SOPC_STATUS_INVALID_PARAMETERS or SOPC_STATUS_NOK.
     */
    const SOPC_FnValidateCertificate pFnValidateCertificate;

    /** \brief PKI implementations can use this placeholder to store handles to certificate authorities. */
    void* pUserCertAuthList;
    /** \brief PKI implementations can use this placeholder to store handles to certificate revocation list(s). */
    void* pUserCertRevocList;
    /** \brief PKI implementations can use this placeholder to store more specific data. */
    void* pUserData;
};

#endif /* SOPC_PKI_H_ */
