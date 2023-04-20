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

/** \file pki_stack.c
 *
 * The minimal PKI implementation provided by the stack. It is lib-specific.
 *
 * This is not the role of the stack to provide a full-blown configurable PKI.
 * The stack provides only a minimal, always safe validating PKI.
 */

#include <stdio.h>
#include <string.h>

#include "sopc_assert.h"
#include "sopc_crypto_provider.h"
#include "sopc_key_manager.h"
#include "sopc_logger.h"
#include "sopc_macros.h"
#include "sopc_mem_alloc.h"
#include "sopc_pki.h"
#include "sopc_pki_stack.h"

#include "key_manager_lib.h"
#include "mbedtls_common.h"

#include "mbedtls/oid.h"
#include "mbedtls/ssl.h"
#include "mbedtls/x509.h"

/**
 * The minimal profile supported by the PKIProviderStack. It requires cacert signed with
 *  at least SHA-256, with an RSA key of at least 2048 bits.
 */
static const mbedtls_x509_crt_profile mbedtls_x509_crt_profile_minimal = {
    /* Hashes from SHA-256 and above */
    .allowed_mds = MBEDTLS_X509_ID_FLAG(MBEDTLS_MD_SHA256) | MBEDTLS_X509_ID_FLAG(MBEDTLS_MD_SHA384) |
                   MBEDTLS_X509_ID_FLAG(MBEDTLS_MD_SHA512),
    .allowed_pks = 0xFFFFFFF,     /* Any PK alg */
    .allowed_curves = 0xFFFFFFFF, /* Any curve  */
    .rsa_min_bitlen = 2048,
};

static uint32_t PKIProviderStack_GetCertificateValidationError(uint32_t failure_reasons)
{
    // Order compliant with part 4 (1.04) Table 106

    /* Certificate structure */
    if ((failure_reasons & MBEDTLS_X509_BADCERT_MISSING) != 0)
    {
        return SOPC_CertificateValidationError_Invalid;
    }
    else if ((failure_reasons & MBEDTLS_X509_BADCERT_KEY_USAGE) != 0)
    {
        return SOPC_CertificateValidationError_Invalid;
    }
    else if ((failure_reasons & MBEDTLS_X509_BADCERT_EXT_KEY_USAGE) != 0)
    {
        return SOPC_CertificateValidationError_Invalid;
    }
    else if ((failure_reasons & MBEDTLS_X509_BADCERT_NS_CERT_TYPE) != 0)
    {
        return SOPC_CertificateValidationError_Invalid;
    }
    else if ((failure_reasons & MBEDTLS_X509_BADCERT_SKIP_VERIFY) != 0)
    {
        return SOPC_CertificateValidationError_UseNotAllowed;
    }

    /* Signature */
    else if ((failure_reasons & MBEDTLS_X509_BADCERT_BAD_KEY) != 0)
    {
        return SOPC_CertificateValidationError_Invalid;
    }
    else if ((failure_reasons & MBEDTLS_X509_BADCERT_BAD_MD) != 0)
    {
        return SOPC_CertificateValidationError_Invalid;
    }
    else if ((failure_reasons & MBEDTLS_X509_BADCERT_BAD_PK) != 0)
    {
        return SOPC_CertificateValidationError_Invalid;
    }

    /* Trust list check*/

    /* Generic signature error */
    if ((failure_reasons & MBEDTLS_X509_BADCERT_NOT_TRUSTED) != 0)
    {
        return SOPC_CertificateValidationError_Untrusted;
    }

    /* Validity period */
    else if ((failure_reasons & MBEDTLS_X509_BADCERT_EXPIRED) != 0)
    {
        return SOPC_CertificateValidationError_TimeInvalid;
    }
    else if ((failure_reasons & MBEDTLS_X509_BADCERT_FUTURE) != 0)
    {
        return SOPC_CertificateValidationError_TimeInvalid;
    }

    /* Host Name */
    else if ((failure_reasons & MBEDTLS_X509_BADCERT_CN_MISMATCH) != 0)
    {
        return SOPC_CertificateValidationError_HostNameInvalid;
    }
    /* URI */

    /* Certificate Usage */
    // Checked in PKIProviderStack_ValidateCertificate

    /* (Find) Revocation List */
    else if ((failure_reasons & MBEDTLS_X509_BADCRL_NOT_TRUSTED) != 0)
    {
        return SOPC_CertificateValidationError_RevocationUnknown;
    }
    else if ((failure_reasons & MBEDTLS_X509_BADCRL_EXPIRED) != 0)
    {
        return SOPC_CertificateValidationError_RevocationUnknown;
    }
    else if ((failure_reasons & MBEDTLS_X509_BADCRL_FUTURE) != 0)
    {
        return SOPC_CertificateValidationError_RevocationUnknown;
    }
    else if ((failure_reasons & MBEDTLS_X509_BADCRL_BAD_MD) != 0)
    {
        return SOPC_CertificateValidationError_RevocationUnknown;
    }
    else if ((failure_reasons & MBEDTLS_X509_BADCRL_BAD_PK) != 0)
    {
        return SOPC_CertificateValidationError_RevocationUnknown;
    }
    else if ((failure_reasons & MBEDTLS_X509_BADCRL_BAD_KEY) != 0)
    {
        return SOPC_CertificateValidationError_RevocationUnknown;
    }

    /* Revocation check */
    else if ((failure_reasons & MBEDTLS_X509_BADCERT_REVOKED) != 0)
    {
        return SOPC_CertificateValidationError_Revoked;
    }
    else if ((failure_reasons & MBEDTLS_X509_BADCERT_OTHER) != 0)
    {
        return SOPC_CertificateValidationError_Untrusted;
    }

    return SOPC_CertificateValidationError_Unkown;
}

static int verify_cert(void* is_issued, mbedtls_x509_crt* crt, int certificate_depth, uint32_t* flags)
{
    /* The purpose of this callback is solely to treat self-signed issued certificates.
     * When a certificate is issued and self-signed, mbedtls does not find its parent,
     * and marks it as NOT_TRUSTED.
     * So, for issued certificates that are NOT_TRUSTED, we verify:
     * - it is self-signed
     * - its signature is correct
     * - (dates are already checked by mbedtls)
     * - (signature algorithms are also already checked)
     */
    bool bIssued = *(bool*) is_issued;
    if (bIssued && 0 == certificate_depth &&
        MBEDTLS_X509_BADCERT_NOT_TRUSTED == (*flags & MBEDTLS_X509_BADCERT_NOT_TRUSTED))
    {
        /* Is it self-signed? Issuer and subject are the same.
         * Note: this verification is not sufficient by itself to conclude that the certificate is self-signed,
         * but the self-signature verification is.
         */
        if (crt->issuer_raw.len == crt->subject_raw.len &&
            0 == memcmp(crt->issuer_raw.p, crt->subject_raw.p, crt->issuer_raw.len))
        {
            /* Is it correctly signed? Inspired by x509_crt_check_signature */
            const mbedtls_md_info_t* md_info = mbedtls_md_info_from_type(crt->sig_md);
            unsigned char hash[MBEDTLS_MD_MAX_SIZE];

            /* First hash the certificate, then verify it is signed */
            if (mbedtls_md(md_info, crt->tbs.p, crt->tbs.len, hash) == 0)
            {
                if (mbedtls_pk_verify_ext(crt->sig_pk, crt->sig_opts, &crt->pk, crt->sig_md, hash,
                                          mbedtls_md_get_size(md_info), crt->sig.p, crt->sig.len) == 0)
                {
                    /* Finally set the certificate as trusted */
                    *flags = (*flags & ~(uint32_t) MBEDTLS_X509_BADCERT_NOT_TRUSTED);
                }
            }
        }
    }

    /* Only fatal errors could be returned here, as this error code will be forwarded to the caller of
     * mbedtls_x509_crt_verify_with_profile, and the verification stopped.
     * Errors may be MBEDTLS_ERR_X509_FATAL_ERROR, or application specific */
    return 0;
}

/* Returns 0 if all key usages and extended key usages are ok */
static SOPC_ReturnStatus check_key_usages(const mbedtls_x509_crt* crt, bool isUserPki)
{
    int err = 0;
    unsigned int usages = 0;
    if (!isUserPki)
    {
        usages = MBEDTLS_X509_KU_DIGITAL_SIGNATURE | MBEDTLS_X509_KU_NON_REPUDIATION |
                 MBEDTLS_X509_KU_KEY_ENCIPHERMENT | MBEDTLS_X509_KU_DATA_ENCIPHERMENT;
        err = mbedtls_x509_crt_check_key_usage(crt, usages);

        /* If the ext usage is neither server auth nor client auth, it shall be rejected */
        /* TODO: check whether the crt is for a server or a client, and only check the corresponding ext usage */
        bool missSer = mbedtls_x509_crt_check_extended_key_usage(crt, MBEDTLS_OID_SERVER_AUTH,
                                                                 MBEDTLS_OID_SIZE(MBEDTLS_OID_SERVER_AUTH));
        bool missCli = mbedtls_x509_crt_check_extended_key_usage(crt, MBEDTLS_OID_CLIENT_AUTH,
                                                                 MBEDTLS_OID_SIZE(MBEDTLS_OID_CLIENT_AUTH));
        if (missSer && missCli)
        {
            err = 1;
        }
    }
    else
    {
        /* Check the key usages for user certificate (it is not part of the OPC UA but it makes sense to keep it). */
        usages = MBEDTLS_X509_KU_DIGITAL_SIGNATURE;
        err = mbedtls_x509_crt_check_key_usage(crt, usages);
        if (0 == err)
        {
            /* The CA flag shall be FALSE for user certificate */
            err = crt->ca_istrue;
        }
    }

    if (0 == err)
    {
        return SOPC_STATUS_OK;
    }
    else
    {
        return SOPC_STATUS_NOK;
    }
}

static SOPC_ReturnStatus PKIProviderStack_ValidateCertificate(const SOPC_PKIProvider* pPKI,
                                                              const SOPC_CertificateList* pToValidate,
                                                              uint32_t* error)
{
    if (NULL == pPKI || NULL == pToValidate || NULL == error)
    {
        return SOPC_STATUS_INVALID_PARAMETERS;
    }
    *error = SOPC_CertificateValidationError_Unkown;

    /* There are two cases for the validation process:
     * - if pToValidate is an issued certificate, we validate it with untrusted CAs + trusted CAs
     * - otherwise, we validate pToValidate only with the trusted CAs
     * The CRL list always contains CRLs from both untrusted and trusted CA lists
     */
    bool bIssued = false;
    SOPC_ReturnStatus status =
        SOPC_KeyManager_CertificateList_FindCertInList(pPKI->pIssuedCertsList, pToValidate, &bIssued);
    if (SOPC_STATUS_OK != status)
    {
        return SOPC_STATUS_INVALID_PARAMETERS;
    }

    SOPC_CertificateList* trust_list = bIssued ? pPKI->pUntrustedIssuerRootsList : pPKI->pTrustedIssuerRootsList;
    SOPC_CRLList* cert_crl = pPKI->pCertRevocList;
    if ((NULL == trust_list || NULL == cert_crl) && !bIssued)
    {
        // Empty trust list is not valid if the certificate is not issued (only possibility to be valid if self-signed)
        return SOPC_STATUS_INVALID_PARAMETERS;
    }

    /* Assumes that mbedtls does not modify the certificates */
    mbedtls_x509_crt* mbed_ca = (mbedtls_x509_crt*) (NULL != trust_list ? &trust_list->crt : NULL);
    SOPC_GCC_DIAGNOSTIC_IGNORE_CAST_CONST
    mbedtls_x509_crt* mbed_chall = (mbedtls_x509_crt*) (&pToValidate->crt);
    mbedtls_x509_crl* mbed_crl = (mbedtls_x509_crl*) (NULL != cert_crl ? &cert_crl->crl : NULL);
    SOPC_GCC_DIAGNOSTIC_RESTORE

    /* Check certificate usages */
    bool isUserPki = (bool) pPKI->pUserData;
    status = check_key_usages(mbed_chall, isUserPki);
    if (SOPC_STATUS_OK != status)
    {
        *error = SOPC_CertificateValidationError_UseNotAllowed;
    }

    /* Link certificate to validate with intermediate certificates (trusted links or untrusted links) */
    mbedtls_x509_crt* end_of_chall = mbed_chall;
    SOPC_ASSERT(NULL != end_of_chall);
    while (NULL != end_of_chall->next)
    {
        end_of_chall = end_of_chall->next;
    }
    /* end_of_chall is now the last certificate of the chain, link it with links */
    end_of_chall->next = bIssued ? pPKI->pUntrustedIssuerLinksList : pPKI->pTrustedIssuerLinksList;

    /* Verify the certificate chain */
    if (SOPC_STATUS_OK == status)
    {
        uint32_t failure_reasons = 0;
        if (mbedtls_x509_crt_verify_with_profile(mbed_chall, mbed_ca, mbed_crl, &mbedtls_x509_crt_profile_minimal,
                                                 NULL /* You can specify an expected Common Name here */,
                                                 &failure_reasons, verify_cert, &bIssued) != 0)
        {
            *error = PKIProviderStack_GetCertificateValidationError(failure_reasons);
            status = SOPC_STATUS_NOK;
        }
    }

    /* Unlink end_of_chall, otherwise destroying the pToValidate will also destroy trusted or untrusted links */
    end_of_chall->next = NULL;

    return status;
}

static void PKIProviderStack_Free(SOPC_PKIProvider* pPKI)
{
    if (pPKI == NULL)
    {
        return;
    }

    /* Deleting the untrusted list will also clear the trusted list, as they are linked.
     * Hence mbedtls will call free on (&pPKI->pUserTrustedIssuersList.crt), which is pPKI->pUserTrustedIssuersList.
     */
    /* TODO: As the lists are not always generated the same way, there may be cases were they are not linked.
     *       (see Create, as opposed to CreateFromPaths).
     */
    if (NULL != pPKI->pUntrustedIssuerRootsList)
    {
        SOPC_KeyManager_Certificate_Free(pPKI->pUntrustedIssuerRootsList);
    }
    else
    {
        SOPC_KeyManager_Certificate_Free(pPKI->pTrustedIssuerRootsList);
    }
    if (NULL != pPKI->pUntrustedIssuerLinksList)
    {
        SOPC_KeyManager_Certificate_Free(pPKI->pUntrustedIssuerLinksList);
    }
    else
    {
        SOPC_KeyManager_Certificate_Free(pPKI->pTrustedIssuerLinksList);
    }
    SOPC_KeyManager_Certificate_Free(pPKI->pIssuedCertsList);
    SOPC_KeyManager_CRL_Free(pPKI->pCertRevocList);
    SOPC_Free(pPKI);
}

static SOPC_PKIProvider* create_pkistack(SOPC_CertificateList* lRootsTrusted,
                                         SOPC_CertificateList* lLinksTrusted,
                                         SOPC_CertificateList* lRootsUntrusted,
                                         SOPC_CertificateList* lLinksUntrusted,
                                         SOPC_CertificateList* lIssued,
                                         SOPC_CRLList* lCrl,
                                         bool isUserPki)
{
    SOPC_PKIProvider* pki = SOPC_Malloc(sizeof(SOPC_PKIProvider));

    if (NULL != pki)
    {
        /* The pki function pointer shall be const after this init */
        SOPC_GCC_DIAGNOSTIC_IGNORE_CAST_CONST
        *((SOPC_PKIProvider_Free_Func**) (&pki->pFnFree)) = &PKIProviderStack_Free;
        *((SOPC_FnValidateCertificate**) (&pki->pFnValidateCertificate)) = &PKIProviderStack_ValidateCertificate;
        SOPC_GCC_DIAGNOSTIC_RESTORE

        pki->pTrustedIssuerRootsList = lRootsTrusted;
        pki->pTrustedIssuerLinksList = lLinksTrusted;
        pki->pUntrustedIssuerRootsList = lRootsUntrusted;
        pki->pUntrustedIssuerLinksList = lLinksUntrusted;
        pki->pIssuedCertsList = lIssued;
        pki->pCertRevocList = lCrl;
        pki->pUserData = (uintptr_t) isUserPki;
    }

    return pki;
}

SOPC_ReturnStatus SOPC_PKIProviderStack_SetUserCert(SOPC_PKIProvider* pPKI, bool bIsUserPki)
{
    if (NULL == pPKI)
    {
        return SOPC_STATUS_INVALID_PARAMETERS;
    }

    pPKI->pUserData = (uintptr_t) bIsUserPki;
    return SOPC_STATUS_OK;
}

SOPC_ReturnStatus SOPC_PKIProviderStack_Create(SOPC_SerializedCertificate* pCertAuth,
                                               SOPC_CRLList* pRevocationList,
                                               SOPC_PKIProvider** ppPKI)
{
    if (NULL == pCertAuth || NULL == ppPKI)
    {
        return SOPC_STATUS_INVALID_PARAMETERS;
    }

    SOPC_CertificateList* caCert = NULL;
    SOPC_PKIProvider* pki = NULL;
    SOPC_ReturnStatus status = SOPC_KeyManager_SerializedCertificate_Deserialize(pCertAuth, &caCert);

    /* Check the CRL-CA association before creating the PKI */
    if (SOPC_STATUS_OK == status)
    {
        /* mbedtls does not verify that each CA has a CRL, so we must do it ourselves */
        bool match = false;
        status = SOPC_KeyManager_CertificateList_RemoveUnmatchedCRL(caCert, pRevocationList, &match);
        if (SOPC_STATUS_OK == status && !match)
        {
            fprintf(
                stderr,
                "> PKI creation warning: Not all certificate authorities have a single certificate revocation list! "
                "Certificates issued by these CAs will be refused.\n");
        }
    }

    if (SOPC_STATUS_OK == status)
    {
        pki = create_pkistack(caCert, NULL, NULL, NULL, NULL, pRevocationList, false);
        if (NULL == pki)
        {
            status = SOPC_STATUS_OUT_OF_MEMORY;
        }
    }

    if (SOPC_STATUS_OK == status)
    {
        *ppPKI = pki;
    }
    /* Clear partial alloc */
    else
    {
        SOPC_KeyManager_Certificate_Free(caCert);
        SOPC_Free(pki);
    }

    return status;
}

static SOPC_CertificateList* load_certificate_list(char** paths, SOPC_ReturnStatus* status)
{
    SOPC_ASSERT(NULL != paths && NULL != status);

    SOPC_CertificateList* certs = NULL;
    char* cur = *paths;
    while (NULL != cur && SOPC_STATUS_OK == *status)
    {
        *status = SOPC_KeyManager_Certificate_CreateOrAddFromFile(cur, &certs);
        ++paths;
        cur = *paths;
    }

    return certs;
}

/** \brief Create the prev list if required */
static SOPC_ReturnStatus link_certificates(SOPC_CertificateList** ppPrev, SOPC_CertificateList** ppNext)
{
    SOPC_ASSERT(NULL != ppPrev && NULL != ppNext);

    SOPC_ReturnStatus status = SOPC_STATUS_OK;
    SOPC_CertificateList* prev = *ppPrev;
    SOPC_CertificateList* next = *ppNext;
    /* Link two existing lists */
    if (NULL != prev && NULL != next)
    {
        mbedtls_x509_crt* crt = &prev->crt;
        /* crt should not be NULL, as either untrusted is NULL or at least one cert was created */
        SOPC_ASSERT(NULL != crt);
        while (NULL != crt->next)
        {
            crt = crt->next;
        }
        /* crt is now the last certificate of the chain, link it with trusted */
        crt->next = &next->crt;
    }
    /* The second list exists, but not the first */
    else if (NULL != next)
    {
        /* When there are no untrusted, we must create the structure */
        /* TODO: avoid the duplication of the first element of trusted */
        status = SOPC_KeyManager_Certificate_CreateOrAddFromDER(next->crt.raw.p, (uint32_t) next->crt.raw.len, ppPrev);
        if (SOPC_STATUS_OK == status)
        {
            prev = *ppPrev;
            prev->crt.next = &next->crt;
        }
    }
    /* else: The first list exists, but not the second, or both don't exist: nothing to do */

    return status;
}

SOPC_ReturnStatus SOPC_PKIProviderStack_CreateFromPaths(char** lPathTrustedIssuerRoots,
                                                        char** lPathTrustedIssuerLinks,
                                                        char** lPathUntrustedIssuerRoots,
                                                        char** lPathUntrustedIssuerLinks,
                                                        char** lPathIssuedCerts,
                                                        char** lPathCRL,
                                                        SOPC_PKIProvider** ppPKI)
{
    if (NULL == lPathTrustedIssuerRoots || NULL == lPathTrustedIssuerLinks || NULL == lPathUntrustedIssuerRoots ||
        NULL == lPathUntrustedIssuerLinks || NULL == lPathIssuedCerts || NULL == lPathCRL || NULL == ppPKI)
    {
        return SOPC_STATUS_INVALID_PARAMETERS;
    }

    /* Creates chains of issuers which will be used to verify the issued certificates.
     * Create the root lists which are separated between untrusted and trusted.
     * Untrusted roots are used to verify issued certificates.
     * Trusted roots are used to verify unknown certificates.
     * Links issuers are used to complete the chain between end-entry certificates
     * (certificate received in the OPN process) and the roots.
     *
     * In practice, as certificates are linked lists in mbedtls,
     * to verify issued certificates, we chain untrusted and trusted certificates,
     * we create a single list, and chain them: untrusted -> trusted.
     */
    SOPC_ReturnStatus status = SOPC_STATUS_OK;
    SOPC_CertificateList* lRootsTrusted = load_certificate_list(lPathTrustedIssuerRoots, &status);
    SOPC_CertificateList* lLinksTrusted = load_certificate_list(lPathTrustedIssuerLinks, &status);
    SOPC_CertificateList* lRootsUntrusted = load_certificate_list(lPathUntrustedIssuerRoots, &status);
    SOPC_CertificateList* lLinksUntrusted = load_certificate_list(lPathUntrustedIssuerLinks, &status);
    SOPC_CertificateList* lIssued = load_certificate_list(lPathIssuedCerts, &status);

    SOPC_CRLList* lCrls = NULL;
    char* cur = *lPathCRL;
    while (NULL != cur && SOPC_STATUS_OK == status)
    {
        status = SOPC_KeyManager_CRL_CreateOrAddFromFile(cur, &lCrls);
        ++lPathCRL;
        cur = *lPathCRL;
    }

    /* Check the CRL-CA association before creating the PKI.
     * Untrusted root list contains all known root CAs,
     * and untrusted link list contains all intermediate CAs. */
    bool bTrustedRootsCRL = false;
    bool bUntrustedRootsCRL = false;
    bool bTrustedLinksCRL = false;
    bool bUntrustedLinksCRL = false;
    if (SOPC_STATUS_OK == status)
    {
        if (NULL != lRootsTrusted)
        {
            /* mbedtls does not verify that each CA has a CRL, so we must do it ourselves.
             * We must fail here, otherwise we can't report misconfigurations to the users */
            status = SOPC_KeyManager_CertificateList_RemoveUnmatchedCRL(lRootsTrusted, lCrls, &bTrustedRootsCRL);
        }
        else
        {
            bTrustedRootsCRL = true;
        }
    }
    if (SOPC_STATUS_OK == status)
    {
        if (NULL != lRootsUntrusted)
        {
            status = SOPC_KeyManager_CertificateList_RemoveUnmatchedCRL(lRootsUntrusted, lCrls, &bUntrustedRootsCRL);
        }
        else
        {
            bUntrustedRootsCRL = true;
        }
    }
    if (SOPC_STATUS_OK == status)
    {
        if (NULL != lLinksTrusted)
        {
            status = SOPC_KeyManager_CertificateList_RemoveUnmatchedCRL(lLinksTrusted, lCrls, &bTrustedLinksCRL);
        }
        else
        {
            bTrustedLinksCRL = true;
        }
    }
    if (SOPC_STATUS_OK == status)
    {
        if (NULL != lLinksUntrusted)
        {
            status = SOPC_KeyManager_CertificateList_RemoveUnmatchedCRL(lLinksUntrusted, lCrls, &bUntrustedLinksCRL);
        }
        else
        {
            bUntrustedLinksCRL = true;
        }
    }
    if (SOPC_STATUS_OK == status &&
        (!bTrustedRootsCRL || !bUntrustedRootsCRL || !bTrustedLinksCRL || !bUntrustedLinksCRL))
    {
        if (!bTrustedRootsCRL)
        {
            fprintf(stderr,
                    "> PKI creation warning: Not all certificate authorities in given trusted roots have a single "
                    "certificate revocation list! Certificates issued by these CAs will be refused.\n");
        }
        if (!bUntrustedRootsCRL)
        {
            fprintf(stderr,
                    "> PKI creation warning: Not all certificate authorities in given untrusted roots have a single "
                    "certificate revocation list! Certificates issued by these CAs will be refused.\n");
        }
        if (!bTrustedLinksCRL)
        {
            fprintf(
                stderr,
                "> PKI creation warning: Not all certificate authorities in given trusted issuer links have a single "
                "certificate revocation list! Certificates issued by these CAs will be refused.\n");
        }
        if (!bUntrustedLinksCRL)
        {
            fprintf(
                stderr,
                "> PKI creation warning: Not all certificate authorities in given untrusted issuer links have a single "
                "certificate revocation list! Certificates issued by these CAs will be refused.\n");
        }
    }

    // Display warning in case no root issuer defined and trusted issued defined
    if (NULL == lRootsTrusted && NULL == lRootsUntrusted && NULL != lIssued)
    {
        SOPC_Logger_TraceWarning(SOPC_LOG_MODULE_COMMON,
                                 "No root issuer (CA) defined in PKI: only trusted self-signed issued "
                                 "certificates will be accepted without possibility to revoke them (no issuer CRL).");
    }

    /* Link the untrusted lists with the trusted lists
     * (untrusted roots -> trusted roots, untrusted links -> trusted links) */
    if (SOPC_STATUS_OK == status)
    {
        status = link_certificates(&lRootsUntrusted, &lRootsTrusted);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = link_certificates(&lLinksUntrusted, &lLinksTrusted);
    }

    /* TODO: Check that all issued certificates are either self-signed or have a CA in the untrusted+trusted list.
     * This is checked when receiving an issued certificate,
     * but it would be useful to report this misconfiguration.
     */

    /* Simpler case: check and warn that there is untrusted issuers but no issued certificates */
    if (SOPC_STATUS_OK == status)
    {
        // Use paths for untrusted issuers since the certificate list will never be empty (chained to trusted)
        bool bUntrustedAndNoIssued = (NULL != *lPathUntrustedIssuerRoots) && (NULL == lIssued);
        if (bUntrustedAndNoIssued)
        {
            fprintf(stderr,
                    "> PKI creation warning: untrusted certificates are given but no issued certificates are given.\n");
        }
    }

    SOPC_PKIProvider* pki = NULL;
    if (SOPC_STATUS_OK == status)
    {
        pki = create_pkistack(lRootsTrusted, lLinksTrusted, lRootsUntrusted, lLinksUntrusted, lIssued, lCrls, false);
        if (NULL == pki)
        {
            status = SOPC_STATUS_OUT_OF_MEMORY;
        }
    }

    if (SOPC_STATUS_OK == status)
    {
        *ppPKI = pki;
    }
    /* Clear partial alloc */
    else
    {
        /* Deleting the untrusted list will also clear the trusted list, as they are linked.
         * Hence mbedtls will call free on (&pPKI->pTrustedIssuerRootsList.crt), which is pPKI->pTrustedIssuerRootsList.
         */
        SOPC_KeyManager_Certificate_Free(lRootsUntrusted);
        SOPC_KeyManager_Certificate_Free(lLinksUntrusted);
        SOPC_KeyManager_Certificate_Free(lIssued);
        SOPC_KeyManager_CRL_Free(lCrls);
        SOPC_Free(pki);
    }

    return status;
}

/* ****************************************************************** */
/* ************************* NEW API ******************************** */
#include "sopc_assert.h"
#include "sopc_crypto_profiles.h"
#include "sopc_filesystem.h"
#include "sopc_helper_string.h"

#define STR_DEFAULT "/default"
#define STR_TRUSTLIST "/trustList"
#define STR_TRUSTED "/trusted"
#define STR_TRUSTED_CERTS "/trusted/certs"
#define STR_TRUSTED_CRL "/trusted/crl"
#define STR_ISSUERS "/issuers"
#define STR_ISSUERS_CERTS "/issuers/certs"
#define STR_ISSUERS_CRL "/issuers/crl"

/*
TODO RBA:

    - Handled that the security level of the update is not higher than the security level of the endpoint
    - Add a new crypto interface to rule certificates
    - Add unit test for file system API
    - Add unit test for PKI API
    - Add WriteToList function (embedded system)
    - Add mutex in API
*/

/**
 * \brief The PKIProvider object for the Public Key Infrastructure.
 */
struct SOPC_PKIProviderNew
{
    const SOPC_PKI_Config* pConfig;
    char* directoryStorePath;
    SOPC_CertificateList* pTrustedCerts;
    SOPC_CertificateList* pTrustedRoots;
    SOPC_CRLList* pTrustedCrl;
    SOPC_CertificateList* pIssuerCerts;
    SOPC_CertificateList* pIssuerRoots;
    SOPC_CRLList* pIssuerCrl;

    SOPC_CertificateList* pAllCerts; /* Use to validate trusted certificate */
    SOPC_CertificateList* pAllRoots; /* Use to validate trusted certificate*/
    SOPC_CRLList* pAllCrl;
};

static const SOPC_PKI_LeafProfile g_leaf_profile_rsa_sha256_2048_4096 = {
    .mdSign = SOPC_PKI_MD_SHA256_OR_ABOVE,
    .pkAlgo = SOPC_PKI_PK_RSA,
    .RSAMinimumKeySize = 2048,
    .RSAMaximumKeySize = 4096,
};

static const SOPC_PKI_LeafProfile g_leaf_profile_rsa_sha1_1024_2048 = {
    .mdSign = SOPC_PKI_MD_SHA1_OR_ABOVE,
    .pkAlgo = SOPC_PKI_PK_RSA,
    .RSAMinimumKeySize = 1024,
    .RSAMaximumKeySize = 2048,
};
static const SOPC_PKI_ChainProfile g_chain_profile_rsa_sha256_2048 = {.curves = SOPC_PKI_CURVES_ANY,
                                                                      .mdSign = SOPC_PKI_MD_SHA256_OR_ABOVE,
                                                                      .pkAlgo = SOPC_PKI_PK_RSA,
                                                                      .RSAMinimumKeySize = 2048};
static const SOPC_PKI_ChainProfile g_chain_profile_rsa_sha1_1024 = {.curves = SOPC_PKI_CURVES_ANY,
                                                                    .mdSign = SOPC_PKI_MD_SHA1_OR_ABOVE,
                                                                    .pkAlgo = SOPC_PKI_PK_RSA,
                                                                    .RSAMinimumKeySize = 1024};
static const SOPC_PKI_Profile g_profile_rsa_sha256_2048_4096 = {
    .leafProfile = &g_leaf_profile_rsa_sha256_2048_4096,
    .chainProfile = &g_chain_profile_rsa_sha256_2048,
};
static const SOPC_PKI_Profile g_profile_rsa_sha1_1024_2048 = {
    .leafProfile = &g_leaf_profile_rsa_sha1_1024_2048,
    .chainProfile = &g_chain_profile_rsa_sha1_1024,
};
static const SOPC_PKI_Config g_config_user = {
    .type = SOPC_PKI_TYPE_USER,
    .bBackwardInteroperability = false,
    .keyUsage = SOPC_PKI_KU_DIGITAL_SIGNATURE, // it is not part of the OPC UA but it makes sense to keep it
};
/* TODO RBA: Removed const properties for client and server configuration structures (URI + HostName to configure later
 * by user) */
static const SOPC_PKI_Config g_config_client_app = {
    .type = SOPC_PKI_TYPE_CLIENT_APP,
    .bBackwardInteroperability = true,
    .keyUsage = SOPC_PKI_KU_KEY_ENCIPHERMENT | SOPC_PKI_KU_KEY_DATA_ENCIPHERMENT | SOPC_PKI_KU_DIGITAL_SIGNATURE |
                SOPC_PKI_KU_NON_REPUDIATION,
};
static const SOPC_PKI_Config g_config_server_app = {
    .type = SOPC_PKI_TYPE_SERVER_APP,
    .bBackwardInteroperability = true,
    .keyUsage = SOPC_PKI_KU_KEY_ENCIPHERMENT | SOPC_PKI_KU_KEY_DATA_ENCIPHERMENT | SOPC_PKI_KU_DIGITAL_SIGNATURE |
                SOPC_PKI_KU_NON_REPUDIATION,
};
static const SOPC_PKI_Config g_config_client_server_app = {
    .type = SOPC_PKI_TYPE_CLIENT_SERVER_APP,
    .bBackwardInteroperability = true,
    .keyUsage = SOPC_PKI_KU_KEY_ENCIPHERMENT | SOPC_PKI_KU_KEY_DATA_ENCIPHERMENT | SOPC_PKI_KU_DIGITAL_SIGNATURE |
                SOPC_PKI_KU_NON_REPUDIATION,
};

const SOPC_PKI_LeafProfile* SOPC_PKIProviderNew_GetLeafProfile(const char* uri)
{
    if (NULL == uri)
    {
        return NULL;
    }

    if (SOPC_strncmp_ignore_case(uri, SOPC_SecurityPolicy_Aes256Sha256RsaPss_URI,
                                 strlen(SOPC_SecurityPolicy_Aes256Sha256RsaPss_URI) + 1) == 0)
    {
        return &g_leaf_profile_rsa_sha256_2048_4096;
    }
    if (SOPC_strncmp_ignore_case(uri, SOPC_SecurityPolicy_Aes128Sha256RsaOaep_URI,
                                 strlen(SOPC_SecurityPolicy_Aes128Sha256RsaOaep_URI) + 1) == 0)
    {
        return &g_leaf_profile_rsa_sha256_2048_4096;
    }
    if (SOPC_strncmp_ignore_case(uri, SOPC_SecurityPolicy_Basic256Sha256_URI,
                                 strlen(SOPC_SecurityPolicy_Basic256Sha256_URI) + 1) == 0)
    {
        return &g_leaf_profile_rsa_sha256_2048_4096;
    }
    if (SOPC_strncmp_ignore_case(uri, SOPC_SecurityPolicy_Basic256_URI, strlen(SOPC_SecurityPolicy_Basic256_URI) + 1) ==
        0)
    {
        return &g_leaf_profile_rsa_sha1_1024_2048;
    }

    return NULL;
}

const SOPC_PKI_Profile* SOPC_PKIProviderNew_GetProfile(const char* uri)
{
    if (NULL == uri)
    {
        return NULL;
    }

    if (SOPC_strncmp_ignore_case(uri, SOPC_SecurityPolicy_Aes256Sha256RsaPss_URI,
                                 strlen(SOPC_SecurityPolicy_Aes256Sha256RsaPss_URI) + 1) == 0)
    {
        return &g_profile_rsa_sha256_2048_4096;
    }
    if (SOPC_strncmp_ignore_case(uri, SOPC_SecurityPolicy_Aes128Sha256RsaOaep_URI,
                                 strlen(SOPC_SecurityPolicy_Aes128Sha256RsaOaep_URI) + 1) == 0)
    {
        return &g_profile_rsa_sha256_2048_4096;
    }
    if (SOPC_strncmp_ignore_case(uri, SOPC_SecurityPolicy_Basic256Sha256_URI,
                                 strlen(SOPC_SecurityPolicy_Basic256Sha256_URI) + 1) == 0)
    {
        return &g_profile_rsa_sha256_2048_4096;
    }
    if (SOPC_strncmp_ignore_case(uri, SOPC_SecurityPolicy_Basic256_URI, strlen(SOPC_SecurityPolicy_Basic256_URI) + 1) ==
        0)
    {
        return &g_profile_rsa_sha1_1024_2048;
    }

    return NULL;
}

const SOPC_PKI_Profile* SOPC_PKIProviderNew_GetMinimalUserProfile(void)
{
    /* Minimal profile for the chain.
       The leaf profile is not used for users during the validation process but the user certificate properties
       are checked according to the security policy during the activation session */
    return &g_profile_rsa_sha256_2048_4096;
}

const SOPC_PKI_Config* SOPC_PKIProviderNew_GetConfig(const SOPC_PKI_Type type)
{
    switch (type)
    {
    case SOPC_PKI_TYPE_USER:
        return &g_config_user;
        break;
    case SOPC_PKI_TYPE_CLIENT_APP:
        return &g_config_client_app;
        break;
    case SOPC_PKI_TYPE_SERVER_APP:
        return &g_config_server_app;
        break;
    case SOPC_PKI_TYPE_CLIENT_SERVER_APP:
        return &g_config_client_server_app;
        break;
    default:
        break;
    }
    return NULL;
}

static bool cert_is_self_sign(mbedtls_x509_crt* crt);

static SOPC_ReturnStatus check_security_policy(const SOPC_CertificateList* pToValidate,
                                               const SOPC_PKI_LeafProfile* pConfig)
{
    SOPC_AsymmetricKey pub_key;
    size_t keyLenBits = 0;
    bool bErr = false;
    // Retrieve key
    SOPC_ReturnStatus status = KeyManager_Certificate_GetPublicKey(pToValidate, &pub_key);
    if (SOPC_STATUS_OK != status)
    {
        return status;
    }
    char* thumbprint = SOPC_KeyManager_Certificate_GetCstring_SHA1(pToValidate);
    if (NULL == thumbprint)
    {
        return SOPC_STATUS_INVALID_STATE;
    }
    // Retrieve key type
    mbedtls_pk_type_t key_type = mbedtls_pk_get_type(&pub_key.pk);
    // Verifies key type: RSA
    switch (pConfig->pkAlgo)
    {
    case SOPC_PKI_PK_ANY:
        break;
    case SOPC_PKI_PK_RSA:
        if (SOPC_PKI_PK_RSA == pConfig->pkAlgo && MBEDTLS_PK_RSA != key_type)
        {
            bErr = true;
        }
        break;
    default:
        bErr = true;
    }
    if (bErr)
    {
        SOPC_Logger_TraceError(SOPC_LOG_MODULE_COMMON,
                               "> PKI validation failed : unexpected key type for certificate thumbprint %s",
                               thumbprint);
        SOPC_Free(thumbprint);
        return SOPC_STATUS_NOK;
    }
    // Retrieve key length
    keyLenBits = mbedtls_pk_get_bitlen(&pub_key.pk);
    // Verifies key length: min-max
    if (keyLenBits < pConfig->RSAMinimumKeySize || keyLenBits > pConfig->RSAMaximumKeySize)
    {
        SOPC_Logger_TraceError(SOPC_LOG_MODULE_COMMON,
                               "> PKI validation failed : unexpected key size for certificate thumbprint %s",
                               thumbprint);
        SOPC_Free(thumbprint);
        return SOPC_STATUS_NOK;
    }
    // Verifies signing algorithm:
    mbedtls_md_type_t md = pToValidate->crt.sig_md;
    switch (pConfig->mdSign)
    {
    case SOPC_PKI_MD_SHA1_OR_ABOVE:
        if (MBEDTLS_MD_SHA1 != md && MBEDTLS_MD_SHA224 != md && MBEDTLS_MD_SHA256 != md && MBEDTLS_MD_SHA384 != md &&
            MBEDTLS_MD_SHA512 != md)
        {
            bErr = true;
        }
        break;
    case SOPC_PKI_MD_SHA256_OR_ABOVE:
        if (MBEDTLS_MD_SHA256 != md && MBEDTLS_MD_SHA384 != md && MBEDTLS_MD_SHA512 != md)
        {
            bErr = true;
        }
        break;
    case SOPC_PKI_MD_SHA1:
        if (MBEDTLS_MD_SHA1 != md)
        {
            bErr = true;
        }
        break;
    case SOPC_PKI_MD_SHA256:
        if (MBEDTLS_MD_SHA256 != md)
        {
            bErr = true;
        }
        break;
    default:
        bErr = true;
    }
    if (bErr)
    {
        SOPC_Logger_TraceError(SOPC_LOG_MODULE_COMMON,
                               "> PKI validation failed : unexpected signing algorithm for certificate thumbprint %s",
                               thumbprint);
    }

    SOPC_Free(thumbprint);
    return bErr ? SOPC_STATUS_NOK : SOPC_STATUS_OK;
}

static unsigned int get_lib_ku_from_sopc_ku(const SOPC_PKI_KeyUsage_Mask sopc_pki_ku)
{
    unsigned int usages = 0;
    if (SOPC_PKI_KU_DISABLE_CHECK & sopc_pki_ku)
    {
        usages = UINT32_MAX; // All allowed
        return usages;
    }
    if (SOPC_PKI_KU_DIGITAL_SIGNATURE & sopc_pki_ku)
    {
        usages |= MBEDTLS_X509_KU_DIGITAL_SIGNATURE;
    }
    if (SOPC_PKI_KU_NON_REPUDIATION & sopc_pki_ku)
    {
        usages |= MBEDTLS_X509_KU_NON_REPUDIATION;
    }
    if (SOPC_PKI_KU_KEY_ENCIPHERMENT & sopc_pki_ku)
    {
        usages |= MBEDTLS_X509_KU_KEY_ENCIPHERMENT;
    }
    if (SOPC_PKI_KU_KEY_DATA_ENCIPHERMENT & sopc_pki_ku)
    {
        usages |= MBEDTLS_X509_KU_DATA_ENCIPHERMENT;
    }
    if (SOPC_PKI_KU_KEY_CERT_SIGN & sopc_pki_ku)
    {
        usages |= MBEDTLS_X509_KU_KEY_CERT_SIGN;
    }
    if (SOPC_PKI_KU_KEY_CRL_SIGN & sopc_pki_ku)
    {
        usages |= MBEDTLS_X509_KU_CRL_SIGN;
    }

    return usages;
}

static SOPC_ReturnStatus check_certificate_usage(const SOPC_CertificateList* pToValidate,
                                                 const SOPC_PKI_Config* pConfig)
{
    SOPC_ASSERT(NULL != pToValidate);
    SOPC_ASSERT(NULL != pConfig);

    char* thumbprint = SOPC_KeyManager_Certificate_GetCstring_SHA1(pToValidate);
    if (NULL == thumbprint)
    {
        return SOPC_STATUS_INVALID_STATE;
    }
    unsigned int usages = 0;
    int err = 0;
    /* Check key usages */
    if (SOPC_PKI_KU_DISABLE_CHECK != pConfig->keyUsage)
    {
        usages = get_lib_ku_from_sopc_ku(pConfig->keyUsage);
        err = mbedtls_x509_crt_check_key_usage(&pToValidate->crt, usages);
        if (err)
        {
            SOPC_Logger_TraceError(
                SOPC_LOG_MODULE_COMMON,
                "> PKI validation failed : missing expected key usage for certificate thumbprint %s", thumbprint);
        }
    }
    /* Check extended key usages for client or server cert */
    if (0 == err)
    {
        bool missing = false;
        if (SOPC_PKI_TYPE_SERVER_APP == pConfig->type)
        {
            missing |= mbedtls_x509_crt_check_extended_key_usage(&pToValidate->crt, MBEDTLS_OID_SERVER_AUTH,
                                                                 MBEDTLS_OID_SIZE(MBEDTLS_OID_SERVER_AUTH));
        }
        if (SOPC_PKI_TYPE_CLIENT_APP == pConfig->type)
        {
            missing |= mbedtls_x509_crt_check_extended_key_usage(&pToValidate->crt, MBEDTLS_OID_CLIENT_AUTH,
                                                                 MBEDTLS_OID_SIZE(MBEDTLS_OID_CLIENT_AUTH));
        }
        if (SOPC_PKI_TYPE_CLIENT_SERVER_APP == pConfig->type)
        {
            missing |= mbedtls_x509_crt_check_extended_key_usage(&pToValidate->crt, MBEDTLS_OID_SERVER_AUTH,
                                                                 MBEDTLS_OID_SIZE(MBEDTLS_OID_SERVER_AUTH));
            missing |= mbedtls_x509_crt_check_extended_key_usage(&pToValidate->crt, MBEDTLS_OID_CLIENT_AUTH,
                                                                 MBEDTLS_OID_SIZE(MBEDTLS_OID_CLIENT_AUTH));
        }
        if (missing)
        {
            SOPC_Logger_TraceError(
                SOPC_LOG_MODULE_COMMON,
                "> PKI validation : missing expected extended key usage for certificate thumbprint %s", thumbprint);
            err = 1;
        }
    }
    SOPC_Free(thumbprint);
    if (0 == err)
    {
        return SOPC_STATUS_OK;
    }
    else
    {
        return SOPC_STATUS_NOK;
    }
}

static SOPC_ReturnStatus set_profile_from_configuration(const SOPC_PKI_ChainProfile* pConfig,
                                                        mbedtls_x509_crt_profile* pProfile)
{
    /* Set hashes allowed */
    if (SOPC_PKI_MD_SHA1_OR_ABOVE == pConfig->mdSign)
    {
        pProfile->allowed_mds = MBEDTLS_X509_ID_FLAG(MBEDTLS_MD_SHA1) | MBEDTLS_X509_ID_FLAG(MBEDTLS_MD_SHA224) |
                                MBEDTLS_X509_ID_FLAG(MBEDTLS_MD_SHA256) | MBEDTLS_X509_ID_FLAG(MBEDTLS_MD_SHA384) |
                                MBEDTLS_X509_ID_FLAG(MBEDTLS_MD_SHA512);
    }
    else if (SOPC_PKI_MD_SHA256_OR_ABOVE == pConfig->mdSign)
    {
        pProfile->allowed_mds = MBEDTLS_X509_ID_FLAG(MBEDTLS_MD_SHA256) | MBEDTLS_X509_ID_FLAG(MBEDTLS_MD_SHA384) |
                                MBEDTLS_X509_ID_FLAG(MBEDTLS_MD_SHA512);
    }
    else if (SOPC_PKI_MD_SHA1 == pConfig->mdSign)
    {
        pProfile->allowed_mds = MBEDTLS_X509_ID_FLAG(MBEDTLS_MD_SHA1);
    }
    else if (SOPC_PKI_MD_SHA256 == pConfig->mdSign)
    {
        pProfile->allowed_mds = MBEDTLS_X509_ID_FLAG(MBEDTLS_MD_SHA256);
    }
    else
    {
        return SOPC_STATUS_INVALID_PARAMETERS;
    }
    /* Set PK algo allowed */
    if (SOPC_PKI_PK_ANY == pConfig->pkAlgo)
    {
        pProfile->allowed_pks = UINT32_MAX;
    }
    else if (SOPC_PKI_PK_RSA == pConfig->pkAlgo)
    {
        pProfile->allowed_pks = MBEDTLS_X509_ID_FLAG(MBEDTLS_PK_RSA);
    }
    else
    {
        return SOPC_STATUS_INVALID_PARAMETERS;
    }
    /* Set curve allowed */
    if (SOPC_PKI_CURVES_ANY == pConfig->curves)
    {
        pProfile->allowed_curves = UINT32_MAX;
    }
    else
    {
        return SOPC_STATUS_INVALID_PARAMETERS;
    }
    /* Set minimum RSA key size allowed */
    pProfile->rsa_min_bitlen = pConfig->RSAMinimumKeySize;

    return SOPC_STATUS_OK;
}

SOPC_ReturnStatus SOPC_PKIProviderNew_ValidateCertificate(const SOPC_PKIProviderNew* pPKI,
                                                          const SOPC_CertificateList* pToValidate,
                                                          const SOPC_PKI_Profile* pConfig,
                                                          uint32_t* error)
{
    if (NULL == pPKI || NULL == pToValidate || NULL == pConfig || NULL == error)
    {
        return SOPC_STATUS_INVALID_PARAMETERS;
    }

    *error = SOPC_CertificateValidationError_Unkown;
    char* thumbprint = SOPC_KeyManager_Certificate_GetCstring_SHA1(pToValidate);
    if (NULL == thumbprint)
    {
        return SOPC_STATUS_INVALID_STATE;
    }
    SOPC_ReturnStatus status = SOPC_STATUS_OK;
    bool bIsTrusted = false;
    mbedtls_x509_crt crt = pToValidate->crt;
    bool bIsSelfSign = cert_is_self_sign(&crt);
    /* CA certificates that are not roots are always rejected */
    if (pToValidate->crt.ca_istrue && !bIsSelfSign)
    {
        *error = SOPC_CertificateValidationError_UseNotAllowed;
        SOPC_Logger_TraceError(SOPC_LOG_MODULE_COMMON,
                               "> PKI validation failed : certificate thumbprint %s is a CA root", thumbprint);
        SOPC_Free(thumbprint);
        return SOPC_STATUS_NOK;
    }
    /* If CA root and backward interoperability */
    if (pToValidate->crt.ca_istrue && bIsSelfSign && pPKI->pConfig->bBackwardInteroperability)
    {
        /* Root is trusted? */
        status = SOPC_KeyManager_CertificateList_FindCertInList(pPKI->pTrustedRoots, pToValidate, &bIsTrusted);
        if (SOPC_STATUS_OK != status)
        {
            return SOPC_STATUS_INVALID_STATE;
        }
    }
    else
    {
        /* Cert is trusted? */
        status = SOPC_KeyManager_CertificateList_FindCertInList(pPKI->pTrustedCerts, pToValidate, &bIsTrusted);
        if (SOPC_STATUS_OK != status)
        {
            return SOPC_STATUS_INVALID_STATE;
        }
    }
    /* Apply verification on the certificate */
    if (SOPC_PKI_TYPE_USER != pPKI->pConfig->type)
    {
        status = SOPC_PKIProviderNew_CheckLeafCertificate(pPKI->pConfig, pToValidate, pConfig->leafProfile, error);
        if (SOPC_STATUS_OK != status)
        {
            SOPC_Logger_TraceError(SOPC_LOG_MODULE_COMMON,
                                   "> PKI validation failed : bad properties of certificate thumbprint %s",
                                   thumbprint);
            SOPC_Free(thumbprint);
            return SOPC_STATUS_NOK;
        }
    }
    /* Set the profile from configuration */
    mbedtls_x509_crt_profile crt_profile = {0};
    set_profile_from_configuration(pConfig->chainProfile, &crt_profile);

    SOPC_CertificateList* trust_list = bIsTrusted ? pPKI->pAllRoots : pPKI->pTrustedRoots;
    SOPC_CRLList* cert_crl = pPKI->pAllCrl;
    /* Assumes that mbedtls does not modify the certificates */
    mbedtls_x509_crt* mbed_ca_root = (mbedtls_x509_crt*) (NULL != trust_list ? &trust_list->crt : NULL);
    SOPC_GCC_DIAGNOSTIC_IGNORE_CAST_CONST
    mbedtls_x509_crt* mbed_cert_list = (mbedtls_x509_crt*) (&pToValidate->crt);
    mbedtls_x509_crl* mbed_crl = (mbedtls_x509_crl*) (NULL != cert_crl ? &cert_crl->crl : NULL);
    SOPC_GCC_DIAGNOSTIC_RESTORE

    /* Link certificate to validate with intermediate CA certificates (linked with pPKI->pAllCerts or
     * pPKI->pTrustedCerts) */
    /* pPKI->pAllCerts is a trusted link to validate a trusted certificate. (pPKI->pAllCerts = pPKI->pTrustedCerts +
     * pPKI->pIssuersCerts) */
    /* pPKI->pTrustedCerts is an untrusted link to validate an untrusted certificate  */

    /* List length already check in SOPC_KeyManager_CertificateList_FindCertInList */
    SOPC_ASSERT(NULL == mbed_cert_list->next);
    mbed_cert_list->next = bIsTrusted ? &pPKI->pAllCerts->crt : &pPKI->pTrustedCerts->crt;
    /* Verify the certificate chain */
    if (SOPC_STATUS_OK == status)
    {
        uint32_t failure_reasons = 0;
        if (mbedtls_x509_crt_verify_with_profile(mbed_cert_list, mbed_ca_root, mbed_crl, &crt_profile,
                                                 NULL /* You can specify an expected Common Name here */,
                                                 &failure_reasons, verify_cert, &bIsTrusted) != 0)
        {
            *error = PKIProviderStack_GetCertificateValidationError(failure_reasons);
            SOPC_Logger_TraceError(SOPC_LOG_MODULE_COMMON,
                                   "> PKI validation failed with error code %u for certificate thumbprint %s", *error,
                                   thumbprint);
            status = SOPC_STATUS_NOK;
        }
    }
    /* Unlink mbed_cert_list, otherwise destroying the pToValidate will also destroy trusted or untrusted links */
    mbed_cert_list->next = NULL;

    SOPC_Free(thumbprint);
    return status;
}

/*
    TODO RBA: add URI and hostName check functions according the order of part 4 v1.04
        1. check_security_policy(pToValidate, pProfile)
        2. check_host_name(pToValidate, pConfig)
        3. check_uri(pToValidate, pConfig)
        4. check_certificate_usage(pToValidate, pConfig)
*/
SOPC_ReturnStatus SOPC_PKIProviderNew_CheckLeafCertificate(const SOPC_PKI_Config* pConfig,
                                                           const SOPC_CertificateList* pToValidate,
                                                           const SOPC_PKI_LeafProfile* pProfile,
                                                           uint32_t* error)
{
    if (NULL == pConfig || NULL == pToValidate || NULL == pProfile || NULL == error)
    {
        return SOPC_STATUS_INVALID_PARAMETERS;
    }

    *error = SOPC_CertificateValidationError_Unkown;

    SOPC_ReturnStatus status = check_security_policy(pToValidate, pProfile);
    if (SOPC_STATUS_OK != status)
    {
        *error = SOPC_CertificateValidationError_Invalid; // TODO RBA: Replace by Bad_CertificatePolicyCheckFailed?
    }
    if (SOPC_STATUS_OK == status)
    {
        status = check_certificate_usage(pToValidate, pConfig);
        if (SOPC_STATUS_OK != status)
        {
            *error = SOPC_CertificateValidationError_UseNotAllowed;
        }
    }

    return status;
}

static SOPC_ReturnStatus load_certificate_or_crl_list(const char* basePath,
                                                      SOPC_CertificateList** ppCerts,
                                                      SOPC_CRLList** ppCrl,
                                                      bool bIscrl)
{
    SOPC_ASSERT(NULL != basePath);
    if (bIscrl)
    {
        SOPC_ASSERT(NULL != ppCrl && NULL == ppCerts);
    }
    else
    {
        SOPC_ASSERT(NULL == ppCrl && NULL != ppCerts);
    }
    SOPC_ReturnStatus status = SOPC_STATUS_OK;
    SOPC_Array* pFilePaths = NULL;
    SOPC_CertificateList* pCerts = NULL;
    SOPC_CRLList* pCrl = NULL;
    char* pFilePath = NULL;
    /* Get the array of path from basePath */
    SOPC_FileSystem_GetDirResult dirRes = SOPC_FileSystem_GetDirFilePaths(basePath, &pFilePaths);
    if (SOPC_FileSystem_GetDir_OK != dirRes)
    {
        SOPC_Logger_TraceError(SOPC_LOG_MODULE_COMMON, "> PKI creation error: failed to open directory <%s>.",
                               basePath);
        return SOPC_STATUS_NOK;
    }
    /* Get the size and iterate for each item */
    size_t nbFiles = SOPC_Array_Size(pFilePaths);
    for (size_t idx = 0; idx < nbFiles && SOPC_STATUS_OK == status; idx++)
    {
        pFilePath = SOPC_Array_Get(pFilePaths, char*, idx);
        SOPC_Logger_TraceDebug(SOPC_LOG_MODULE_COMMON, "> PKI loading file <%s>", pFilePath);
        if (bIscrl)
        {
            /* Load CRL */
            status = SOPC_KeyManager_CRL_CreateOrAddFromFile(pFilePath, &pCrl);
        }
        else
        {
            /* Load CERT */
            status = SOPC_KeyManager_Certificate_CreateOrAddFromFile(pFilePath, &pCerts);
        }
    }
    /* Clear in case of error */
    if (SOPC_STATUS_OK != status)
    {
        SOPC_KeyManager_Certificate_Free(pCerts);
        SOPC_KeyManager_CRL_Free(pCrl);
    }
    if (bIscrl)
    {
        *ppCrl = pCrl;
    }
    else
    {
        *ppCerts = pCerts;
    }
    /* Always clear */
    SOPC_Array_Delete(pFilePaths);
    return status;
}

static SOPC_ReturnStatus load_certificate_and_crl_list_from_store(const char* basePath,
                                                                  SOPC_CertificateList** ppTrustedCerts,
                                                                  SOPC_CRLList** ppTrustedCrl,
                                                                  SOPC_CertificateList** ppIssuerCerts,
                                                                  SOPC_CRLList** ppIssuerCrl)
{
    SOPC_ASSERT(NULL != basePath);
    SOPC_ASSERT(NULL != ppTrustedCerts);
    SOPC_ASSERT(NULL != ppTrustedCrl);
    SOPC_ASSERT(NULL != ppIssuerCerts);
    SOPC_ASSERT(NULL != ppIssuerCrl);
    /* Trusted Certs */
    char* trustedCertsPath = NULL;
    SOPC_ReturnStatus status = SOPC_StrConcat(basePath, STR_TRUSTED_CERTS, &trustedCertsPath);
    if (SOPC_STATUS_OK == status)
    {
        status = load_certificate_or_crl_list(trustedCertsPath, ppTrustedCerts, NULL, false);
    }
    SOPC_Free(trustedCertsPath);
    /* Trusted Crl */
    if (SOPC_STATUS_OK == status)
    {
        char* trustedCrlPath = NULL;
        status = SOPC_StrConcat(basePath, STR_TRUSTED_CRL, &trustedCrlPath);
        if (SOPC_STATUS_OK == status)
        {
            status = load_certificate_or_crl_list(trustedCrlPath, NULL, ppTrustedCrl, true);
        }
        SOPC_Free(trustedCrlPath);
    }
    /* Issuer Certs */
    if (SOPC_STATUS_OK == status)
    {
        char* issuerCertsPath = NULL;
        status = SOPC_StrConcat(basePath, STR_ISSUERS_CERTS, &issuerCertsPath);
        if (SOPC_STATUS_OK == status)
        {
            status = load_certificate_or_crl_list(issuerCertsPath, ppIssuerCerts, NULL, false);
        }
        SOPC_Free(issuerCertsPath);
    }
    /* Issuer Crl */
    if (SOPC_STATUS_OK == status)
    {
        char* issuerCrlPath = NULL;
        status = SOPC_StrConcat(basePath, STR_ISSUERS_CRL, &issuerCrlPath);
        if (SOPC_STATUS_OK == status)
        {
            status = load_certificate_or_crl_list(issuerCrlPath, NULL, ppIssuerCrl, true);
        }
        SOPC_Free(issuerCrlPath);
    }

    return status;
}

/* TODO RBA: Add into sop_key_manager.h */
static bool cert_is_self_sign(mbedtls_x509_crt* crt)
{
    SOPC_ASSERT(NULL != crt);

    bool is_self_sign = false;
    /* Verify that the CA is self sign */
    int res = memcmp(crt->issuer_raw.p, crt->subject_raw.p, crt->issuer_raw.len);
    if (crt->issuer_raw.len == crt->subject_raw.len && 0 == res)
    {
        /* Is it correctly signed? Inspired by x509_crt_check_signature */
        const mbedtls_md_info_t* md_info = mbedtls_md_info_from_type(crt->sig_md);
        unsigned char hash[MBEDTLS_MD_MAX_SIZE];

        /* First hash the certificate, then verify it is signed */
        res = mbedtls_md(md_info, crt->tbs.p, crt->tbs.len, hash);
        if (0 == res)
        {
            res = mbedtls_pk_verify_ext(crt->sig_pk, crt->sig_opts, &crt->pk, crt->sig_md, hash,
                                        mbedtls_md_get_size(md_info), crt->sig.p, crt->sig.len);
            if (0 == res)
            {
                /* Finally accept the certificate */
                is_self_sign = true;
            }
        }
    }
    return is_self_sign;
}

/**
 * \brief Delete the roots of the list ppCerts. Create a new list ppRootCa with all roots from ppCerts.
 *        If there is no root, the content of ppRootCa is set to NULL.
 *        If ppCerts becomes empty, its content is set to NULL.
 */
static SOPC_ReturnStatus split_root_from_cert_list(SOPC_CertificateList** ppCerts, SOPC_CertificateList** ppRootCa)
{
    SOPC_ASSERT(NULL != ppCerts);
    SOPC_ASSERT(NULL != ppRootCa);

    SOPC_CertificateList* pHeadCerts = *ppCerts;
    if (NULL == pHeadCerts)
    {
        /* The certificate list is empty */
        return SOPC_STATUS_OK;
    }
    SOPC_CertificateList* pHeadRoots = NULL;
    mbedtls_x509_crt* cur = &pHeadCerts->crt; /* Start from the HEAD*/
    mbedtls_x509_crt* prev = NULL;            /* Parent of current cert */
    SOPC_ReturnStatus status = SOPC_STATUS_OK;

    while (NULL != cur && SOPC_STATUS_OK == status)
    {
        bool is_root = true;
        bool self_sign = false;

        /* Skip certificates that are not authorities */
        if (!cur->ca_istrue)
        {
            is_root = false;
        }
        self_sign = cert_is_self_sign(cur);
        if (!self_sign && is_root)
        {
            is_root = false;
        }
        if (is_root)
        {
            status = SOPC_KeyManager_Certificate_CreateOrAddFromDER(cur->raw.p, (uint32_t) cur->raw.len, &pHeadRoots);

            if (SOPC_STATUS_OK == status)
            {
                /* Remove the certificate from the chain and safely delete it */
                mbedtls_x509_crt* next = cur->next;
                cur->next = NULL;
                mbedtls_x509_crt_free(cur);
                /* Set new next certificate (if possible) */
                if (NULL == prev)
                {
                    if (NULL == next)

                    {
                        /* The list is empty, Free it */
                        SOPC_Free(pHeadCerts);
                        pHeadCerts = NULL;
                        cur = NULL; // make iteration stop
                    }
                    else
                    {
                        /* Head of the chain is a special case */
                        pHeadCerts->crt = *next; /* Use an assignment operator to do the copy */
                        /* We have to free the new next certificate */
                        SOPC_Free(next);

                        /* Do not iterate: current certificate has changed */
                    }
                }
                else
                {
                    /* We have to free the certificate if it is not the first in the list */
                    SOPC_Free(cur);
                    prev->next = next;
                    /* Iterate */
                    cur = next;
                }
            }
        }
        else
        {
            /* Prepare next iteration */
            prev = cur;
            cur = cur->next;
        }
    }

    if (SOPC_STATUS_OK != status)
    {
        SOPC_KeyManager_Certificate_Free(pHeadRoots);
        pHeadRoots = NULL;
    }

    *ppRootCa = pHeadRoots;
    *ppCerts = pHeadCerts;

    return status;
}

/* TODO RBA: Add into sop_key_manager.h */
static SOPC_ReturnStatus copy_certificate(SOPC_CertificateList* pCert, SOPC_CertificateList** ppCertCopy)
{
    SOPC_ReturnStatus status = SOPC_STATUS_OK;
    if (NULL == pCert && NULL == ppCertCopy)
    {
        return SOPC_STATUS_INVALID_PARAMETERS;
    }
    SOPC_CertificateList* pCertCopy = *ppCertCopy;
    mbedtls_x509_crt* crt = &pCert->crt;
    while (NULL != crt && SOPC_STATUS_OK == status)
    {
        status = SOPC_KeyManager_Certificate_CreateOrAddFromDER(crt->raw.p, (uint32_t) crt->raw.len, &pCertCopy);
        crt = crt->next;
    }
    /* clear if error */
    if (SOPC_STATUS_OK != status)
    {
        SOPC_KeyManager_Certificate_Free(pCertCopy);
        pCertCopy = NULL;
    }
    *ppCertCopy = pCertCopy;
    return status;
}

static SOPC_ReturnStatus merge_certificates(SOPC_CertificateList* pLeft,
                                            SOPC_CertificateList* pRight,
                                            SOPC_CertificateList** ppRes)
{
    SOPC_ReturnStatus status = SOPC_STATUS_OK;
    if (NULL == ppRes)
    {
        return SOPC_STATUS_INVALID_PARAMETERS;
    }
    SOPC_CertificateList* pRes = *ppRes;
    /* Left part */
    if (NULL != pLeft)
    {
        status = copy_certificate(pLeft, &pRes);
    }
    /* Right part */
    if (NULL != pRight && SOPC_STATUS_OK == status)
    {
        status = copy_certificate(pRight, &pRes);
    }
    /* clear if error */
    if (SOPC_STATUS_OK != status)
    {
        SOPC_KeyManager_Certificate_Free(pRes);
        pRes = NULL;
    }
    *ppRes = pRes;
    return status;
}

/* TODO RBA: Add into sop_key_manager.h */
static SOPC_ReturnStatus copy_crl(SOPC_CRLList* pCrl, SOPC_CRLList** ppCrlCopy)
{
    SOPC_ReturnStatus status = SOPC_STATUS_OK;
    if (NULL == pCrl && NULL == ppCrlCopy)
    {
        return SOPC_STATUS_INVALID_PARAMETERS;
    }
    SOPC_CRLList* pCrlCopy = *ppCrlCopy;
    mbedtls_x509_crl* crl = &pCrl->crl;
    while (NULL != crl && SOPC_STATUS_OK == status)
    {
        status = SOPC_KeyManager_CRL_CreateOrAddFromDER(crl->raw.p, (uint32_t) crl->raw.len, &pCrlCopy);
        crl = crl->next;
    }
    /* clear if error */
    if (SOPC_STATUS_OK != status)
    {
        SOPC_KeyManager_CRL_Free(pCrlCopy);
        pCrlCopy = NULL;
    }
    *ppCrlCopy = pCrlCopy;
    return status;
}

static SOPC_ReturnStatus merge_crls(SOPC_CRLList* pLeft, SOPC_CRLList* pRight, SOPC_CRLList** ppRes)
{
    SOPC_ReturnStatus status = SOPC_STATUS_OK;
    if (NULL == ppRes)
    {
        return SOPC_STATUS_INVALID_PARAMETERS;
    }
    SOPC_CRLList* pRes = *ppRes;
    /* Left part */
    if (NULL != pLeft)
    {
        status = copy_crl(pLeft, &pRes);
    }
    /* Right part */
    if (NULL != pRight && SOPC_STATUS_OK == status)
    {
        status = copy_crl(pRight, &pRes);
    }
    /* clear if error */
    if (SOPC_STATUS_OK != status)
    {
        SOPC_KeyManager_CRL_Free(pRes);
        pRes = NULL;
    }
    *ppRes = pRes;
    return status;
}

static void get_list_stats(SOPC_CertificateList* pCert, uint32_t* caCount, uint32_t* listLength, uint32_t* rootCount)
{
    if (NULL == pCert)
    {
        return;
    }
    bool is_self_sign = false;
    mbedtls_x509_crt* crt = &pCert->crt;
    while (NULL != crt)
    {
        *listLength = *listLength + 1;
        if (crt->ca_istrue)
        {
            *caCount = *caCount + 1;
            is_self_sign = cert_is_self_sign(crt);
            if (is_self_sign)
            {
                *rootCount = *rootCount + 1;
            }
        }
        crt = crt->next;
    }
}

static SOPC_ReturnStatus check_lists(SOPC_CertificateList* pTrustedCerts,
                                     SOPC_CertificateList* pIssuerCerts,
                                     SOPC_CRLList* pTrustedCrl,
                                     SOPC_CRLList* pIssuerCrl)
{
    SOPC_ReturnStatus status = SOPC_STATUS_OK;
    /* Trusted stats */
    uint32_t trusted_ca_count = 0;
    uint32_t trusted_list_length = 0;
    uint32_t issued_cert_count = 0;
    uint32_t trusted_root_count = 0;
    /* Issuer stats */
    uint32_t issuer_ca_count = 0;
    uint32_t issuer_list_length = 0;
    uint32_t issuer_root_count = 0;

    if (NULL == pTrustedCerts)
    {
        SOPC_Logger_TraceError(SOPC_LOG_MODULE_COMMON, "> PKI creation error: no trusted certificate is provided.");
        return SOPC_STATUS_INVALID_PARAMETERS;
    }
    get_list_stats(pTrustedCerts, &trusted_ca_count, &trusted_list_length, &trusted_root_count);
    issued_cert_count = trusted_list_length - trusted_ca_count;
    /* trusted CA => trusted CRL*/
    if (0 != trusted_ca_count && NULL == pTrustedCrl)
    {
        SOPC_Logger_TraceError(SOPC_LOG_MODULE_COMMON,
                               "> PKI creation error: trusted CA certificates are provided but no CRL.");
        return SOPC_STATUS_INVALID_PARAMETERS;
    }
    /* check and warn in case there is no trusted certificates and no trusted root (only trusted intermediate CA). */
    if ((0 == issued_cert_count) && (0 == trusted_root_count))
    {
        /* In this case, no certificates will be accepted. */
        SOPC_Logger_TraceError(SOPC_LOG_MODULE_COMMON,
                               "> PKI creation error: no trusted certificate and no trusted root is given: no "
                               "certificates will be accepted.");
        return SOPC_STATUS_INVALID_PARAMETERS;
    }

    get_list_stats(pIssuerCerts, &issuer_ca_count, &issuer_list_length, &issuer_root_count);
    /* issuer CA => issuer CRL*/
    if (0 != issuer_ca_count && NULL == pIssuerCrl)
    {
        SOPC_Logger_TraceError(SOPC_LOG_MODULE_COMMON,
                               "> PKI creation error: issuer CA certificates are provided but no CRL.");
        return SOPC_STATUS_INVALID_PARAMETERS;
    }
    /* Check if issuerCerts list is only filled with CA. */
    if (issuer_list_length != issuer_ca_count)
    {
        SOPC_Logger_TraceError(SOPC_LOG_MODULE_COMMON, "> PKI creation error: not all issuer certificates are CAs.");
        return SOPC_STATUS_INVALID_PARAMETERS;
    }
    /* check and warn in case there is no trusted certificates but issuer certificates. */
    if ((0 != issuer_ca_count) && (0 == issued_cert_count))
    {
        /* In this case, only trusted root CA will be accepted (if Backward interoperability is enabled). */
        SOPC_Logger_TraceWarning(SOPC_LOG_MODULE_COMMON,
                                 "> PKI creation warning: issuer certificates are given but no trusted certificates: "
                                 "only trusted root CA will be accepted (if backward interoperability is enabled)");
    }
    /* check and warn in case no root defined and trusted certificates defined. */
    if ((0 == issuer_root_count) && (0 == trusted_root_count) && (0 != issued_cert_count))
    {
        /* In this case, only trusted self-signed issued certificates will be accepted. */
        SOPC_Logger_TraceWarning(SOPC_LOG_MODULE_COMMON,
                                 "> PKI creation warning: no root (CA) defined: only trusted self-signed issued "
                                 "certificates will be accepted without possibility to revoke them (no CRL).");
    }
    return status;
}

SOPC_ReturnStatus SOPC_PKIProviderNew_CreateFromList(SOPC_CertificateList* pTrustedCerts,
                                                     SOPC_CRLList* pTrustedCrl,
                                                     SOPC_CertificateList* pIssuerCerts,
                                                     SOPC_CRLList* pIssuerCrl,
                                                     const SOPC_PKI_Config* pConfig,
                                                     SOPC_PKIProviderNew** ppPKI)
{
    SOPC_ReturnStatus status = SOPC_STATUS_OK;
    SOPC_PKIProviderNew* pPKI = NULL;
    SOPC_CertificateList* tmp_pTrustedRoots = NULL; /* trusted root CA */
    SOPC_CertificateList* tmp_pIssuerRoots = NULL;  /* issuer root CA */
    SOPC_CertificateList* tmp_pAllRoots = NULL;     /* issuer + trusted roots */
    SOPC_CertificateList* tmp_pAllCerts = NULL;     /* issuer + trusted certs */
    SOPC_CRLList* tmp_pAllCrl = NULL;               /* issuer crl + trusted crl  */

    SOPC_CertificateList* tmp_pTrustedCerts = NULL; /* trusted intermediate CA + trusted certificates */
    SOPC_CRLList* tmp_pTrustedCrl = NULL;           /* CRLs of trusted intermediate CA and trusted root CA */
    SOPC_CertificateList* tmp_pIssuerCerts = NULL;  /* issuer intermediate CA + issuer root CA */
    SOPC_CRLList* tmp_pIssuerCrl = NULL;            /* CRLs of issuer intermediate CA and issuer root CA */

    if (NULL == pConfig || NULL == ppPKI)
    {
        return SOPC_STATUS_INVALID_PARAMETERS;
    }
    /*
       - Check that pTrustedCerts is not empty.
       - Check if there are CAs but no CRLs.
       - Check if issuerCerts list is only filled with CA.
       - Check and warn if issuerCerts is not empty but pTrustedCerts is only filed with CA.
         In this case, if there is no root into pTrustedCerts then
         no certificates will be accepted during validation process.
       - Check and warn in case no root defined but trusted certificates defined.
         In this case, only trusted self-signed issued certificates will be accepted.
    */
    if (SOPC_STATUS_OK == status)
    {
        status = check_lists(pTrustedCerts, pIssuerCerts, pTrustedCrl, pIssuerCrl);
        if (SOPC_STATUS_OK != status)
        {
            return status;
        }
    }
    /* Copy the lists */
    status = copy_certificate(pTrustedCerts, &tmp_pTrustedCerts);
    if (SOPC_STATUS_OK == status)
    {
        status = copy_crl(pTrustedCrl, &tmp_pTrustedCrl);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = copy_certificate(pIssuerCerts, &tmp_pIssuerCerts);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = copy_crl(pIssuerCrl, &tmp_pIssuerCrl);
    }

    /* Check the CRL-CA association before creating the PKI. */
    bool bTrustedCRL = false;
    bool bIssuerCRL = false;
    if (SOPC_STATUS_OK == status)
    {
        if (NULL != tmp_pTrustedCerts)
        {
            status =
                SOPC_KeyManager_CertificateList_RemoveUnmatchedCRL(tmp_pTrustedCerts, tmp_pTrustedCrl, &bTrustedCRL);
        }
        else
        {
            bTrustedCRL = true;
        }
    }
    if (SOPC_STATUS_OK == status)
    {
        if (NULL != tmp_pIssuerCerts)
        {
            status = SOPC_KeyManager_CertificateList_RemoveUnmatchedCRL(tmp_pIssuerCerts, tmp_pIssuerCrl, &bIssuerCRL);
        }
        else
        {
            bIssuerCRL = true;
        }
    }
    if (SOPC_STATUS_OK == status && (!bTrustedCRL || !bIssuerCRL))
    {
        if (!bTrustedCRL)
        {
            SOPC_Logger_TraceWarning(
                SOPC_LOG_MODULE_COMMON,
                "> PKI creation warning: Not all certificate authorities in given trusted certificates have a single "
                "certificate revocation list! Certificates issued by these CAs will be refused.");
        }
        if (!bIssuerCRL)
        {
            SOPC_Logger_TraceWarning(
                SOPC_LOG_MODULE_COMMON,
                "> PKI creation warning: Not all certificate authorities in given issuer certificates have a single "
                "certificate revocation list! Certificates issued by these CAs will be refused.");
        }
    }
    /* Retrieve the root from list */
    if (SOPC_STATUS_OK == status)
    {
        status = split_root_from_cert_list(&tmp_pTrustedCerts, &tmp_pTrustedRoots);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = split_root_from_cert_list(&tmp_pIssuerCerts, &tmp_pIssuerRoots);
    }
    /* Merge trusted and issuer list */
    if (SOPC_STATUS_OK == status)
    {
        status = merge_certificates(tmp_pIssuerCerts, tmp_pTrustedCerts, &tmp_pAllCerts);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = merge_certificates(tmp_pIssuerRoots, tmp_pTrustedRoots, &tmp_pAllRoots);
    }
    if (SOPC_STATUS_OK == status)
    {
        status = merge_crls(tmp_pIssuerCrl, tmp_pTrustedCrl, &tmp_pAllCrl);
    }

    /* Create the PKI */
    if (SOPC_STATUS_OK == status)
    {
        pPKI = SOPC_Calloc(1, sizeof(SOPC_PKIProviderNew));
        if (NULL == pPKI)
        {
            status = SOPC_STATUS_OUT_OF_MEMORY;
        }
    }

    if (SOPC_STATUS_OK == status)
    {
        pPKI->pTrustedRoots = tmp_pTrustedRoots;
        pPKI->pTrustedCerts = tmp_pTrustedCerts;
        pPKI->pTrustedCrl = tmp_pTrustedCrl;
        pPKI->pIssuerRoots = tmp_pIssuerRoots;
        pPKI->pIssuerCerts = tmp_pIssuerCerts;
        pPKI->pIssuerCrl = tmp_pIssuerCrl;
        pPKI->pAllCerts = tmp_pAllCerts;
        pPKI->pAllRoots = tmp_pAllRoots;
        pPKI->pAllCrl = tmp_pAllCrl;
        pPKI->directoryStorePath = NULL;
        pPKI->pConfig = pConfig;
    }
    else
    {
        SOPC_KeyManager_Certificate_Free(tmp_pTrustedRoots);
        SOPC_KeyManager_Certificate_Free(tmp_pIssuerRoots);
        SOPC_KeyManager_Certificate_Free(tmp_pAllRoots);
        SOPC_KeyManager_Certificate_Free(tmp_pTrustedCerts);
        SOPC_KeyManager_Certificate_Free(tmp_pIssuerCerts);
        SOPC_KeyManager_Certificate_Free(tmp_pAllCerts);
        SOPC_KeyManager_CRL_Free(tmp_pTrustedCrl);
        SOPC_KeyManager_CRL_Free(tmp_pIssuerCrl);
        SOPC_KeyManager_CRL_Free(tmp_pAllCrl);
        SOPC_Free(pPKI);
    }

    *ppPKI = pPKI;
    return status;
}

static SOPC_ReturnStatus pki_create_from_store(const char* directoryStorePath,
                                               bool bDefaultBuild,
                                               const SOPC_PKI_Config* pConfig,
                                               SOPC_PKIProviderNew** ppPKI)
{
    SOPC_ASSERT(NULL != directoryStorePath);
    SOPC_ASSERT(NULL != pConfig);
    SOPC_ASSERT(NULL != ppPKI);

    SOPC_ReturnStatus status = SOPC_STATUS_OK;
    SOPC_CertificateList* pTrustedCerts = NULL; /* trusted intermediate CA + trusted certificates */
    SOPC_CertificateList* pIssuerCerts = NULL;  /* issuer intermediate CA */
    SOPC_CRLList* pTrustedCrl = NULL;           /* CRLs of trusted intermediate CA and trusted root CA */
    SOPC_CRLList* pIssuerCrl = NULL;            /* CRLs of issuer intermediate CA and issuer root CA */
    const char* basePath = NULL;
    char* path = NULL;

    /* Select the right folder*/
    if (bDefaultBuild)
    {
        status = SOPC_StrConcat(directoryStorePath, STR_DEFAULT, &path);
        if (SOPC_STATUS_OK != status)
        {
            return status;
        }
        basePath = path;
    }
    else
    {
        status = SOPC_StrConcat(directoryStorePath, STR_TRUSTLIST, &path);
        if (SOPC_STATUS_OK != status)
        {
            return status;
        }
        basePath = path;
    }
    /* Load the files from the directory Store path */
    status =
        load_certificate_and_crl_list_from_store(basePath, &pTrustedCerts, &pTrustedCrl, &pIssuerCerts, &pIssuerCrl);
    /* Check if the trustList is empty */
    if (SOPC_STATUS_OK == status && NULL == pTrustedCerts && NULL == pTrustedCrl && NULL == pIssuerCerts &&
        NULL == pIssuerCrl)
    {
        status = SOPC_STATUS_NOK;
        SOPC_Logger_TraceError(SOPC_LOG_MODULE_COMMON, "> PKI creation error: certificate store is empty (%s).",
                               path);
    }
    if (SOPC_STATUS_OK == status)
    {
        status =
            SOPC_PKIProviderNew_CreateFromList(pTrustedCerts, pTrustedCrl, pIssuerCerts, pIssuerCrl, pConfig, ppPKI);
    }
    /* if error then try with default build */
    if (!bDefaultBuild && SOPC_STATUS_OK != status)
    {
        SOPC_Logger_TraceWarning(SOPC_LOG_MODULE_COMMON,
                                 "> PKI creation warning: trustList missing or bad build switch to default store.");
        status = pki_create_from_store(directoryStorePath, true, pConfig, ppPKI);
    }
    /* Copy the directoryStorePath */
    if (SOPC_STATUS_OK == status)
    {
        /* Copy only if not done during the recursive call. */
        if (NULL == (*ppPKI)->directoryStorePath)
        {
            (*ppPKI)->directoryStorePath = SOPC_strdup(directoryStorePath);
            if (NULL == (*ppPKI)->directoryStorePath)
            {
                SOPC_PKIProviderNew_Free(*ppPKI);
                status = SOPC_STATUS_OUT_OF_MEMORY;
            }
        }
    }

    /* Clear */
    SOPC_Free(path);

    SOPC_KeyManager_Certificate_Free(pTrustedCerts);
    SOPC_KeyManager_Certificate_Free(pIssuerCerts);
    SOPC_KeyManager_CRL_Free(pTrustedCrl);
    SOPC_KeyManager_CRL_Free(pIssuerCrl);

    return status;
}

SOPC_ReturnStatus SOPC_PKIProviderNew_CreateFromStore(const char* directoryStorePath,
                                                      const SOPC_PKI_Config* pConfig,
                                                      SOPC_PKIProviderNew** ppPKI)
{
    if (NULL == directoryStorePath || NULL == pConfig || NULL == ppPKI)
    {
        return SOPC_STATUS_INVALID_PARAMETERS;
    }

    SOPC_ReturnStatus status = pki_create_from_store(directoryStorePath, false, pConfig, ppPKI);
    return status;
}

static void sopc_pki_clear(SOPC_PKIProviderNew* pPKI)
{
    if (NULL == pPKI)
    {
        return;
    }
    SOPC_KeyManager_Certificate_Free(pPKI->pTrustedRoots);
    SOPC_KeyManager_Certificate_Free(pPKI->pIssuerRoots);
    SOPC_KeyManager_Certificate_Free(pPKI->pAllRoots);
    SOPC_KeyManager_Certificate_Free(pPKI->pTrustedCerts);
    SOPC_KeyManager_Certificate_Free(pPKI->pIssuerCerts);
    SOPC_KeyManager_Certificate_Free(pPKI->pAllCerts);
    SOPC_KeyManager_CRL_Free(pPKI->pTrustedCrl);
    SOPC_KeyManager_CRL_Free(pPKI->pIssuerCrl);
    SOPC_KeyManager_CRL_Free(pPKI->pAllCrl);
    SOPC_Free(pPKI->directoryStorePath);
}

void SOPC_PKIProviderNew_Free(SOPC_PKIProviderNew* pPKI)
{
    if (NULL == pPKI)
    {
        return;
    }
    sopc_pki_clear(pPKI);
    SOPC_Free(pPKI);
    pPKI = NULL;
}

static SOPC_ReturnStatus remove_files(const char* directoryPath)
{
    SOPC_ASSERT(NULL != directoryPath);

    SOPC_ReturnStatus status = SOPC_STATUS_OK;
    SOPC_Array* pFilePaths = NULL;
    char* pFilePath = NULL;
    int res = -1;
    /* Get the array of file paths from the given directory */
    SOPC_FileSystem_GetDirResult dirRes = SOPC_FileSystem_GetDirFilePaths(directoryPath, &pFilePaths);
    if (SOPC_FileSystem_GetDir_OK != dirRes)
    {
        SOPC_Logger_TraceError(SOPC_LOG_MODULE_COMMON, "> PKI write to store: failed to open directory <%s>.",
                               directoryPath);
        return SOPC_STATUS_NOK;
    }
    size_t nbFiles = SOPC_Array_Size(pFilePaths);
    for (size_t idx = 0; idx < nbFiles && SOPC_STATUS_OK == status; idx++)
    {
        pFilePath = SOPC_Array_Get(pFilePaths, char*, idx);
        res = remove(pFilePath);
        if (0 != res)
        {
            status = SOPC_STATUS_NOK;
        }
    }
    SOPC_Array_Delete(pFilePaths);
    return status;
}

static SOPC_ReturnStatus write_cert_to_der_files(SOPC_CertificateList* pRoots,
                                                 SOPC_CertificateList* pCerts,
                                                 const char* directoryPath,
                                                 const bool bEraseExistingFiles)
{
    SOPC_ASSERT(NULL != directoryPath);
    SOPC_ReturnStatus status = SOPC_STATUS_OK;
    if (bEraseExistingFiles)
    {
        status = remove_files(directoryPath);
    }
    if (SOPC_STATUS_OK == status && NULL != pRoots)
    {
        status = SOPC_KeyManager_Certificate_ToDER_Files(pRoots, directoryPath);
    }
    if (SOPC_STATUS_OK == status && NULL != pCerts)
    {
        status = SOPC_KeyManager_Certificate_ToDER_Files(pCerts, directoryPath);
    }
    return status;
}

static SOPC_ReturnStatus write_crl_to_der_files(SOPC_CRLList* pCrl,
                                                const char* directoryPath,
                                                const bool bEraseExistingFiles)
{
    SOPC_ASSERT(NULL != directoryPath);
    SOPC_ReturnStatus status = SOPC_STATUS_OK;
    if (bEraseExistingFiles)
    {
        status = remove_files(directoryPath);
    }
    if (SOPC_STATUS_OK == status && NULL != pCrl)
    {
        status = SOPC_KeyManager_CRL_ToDER_Files(pCrl, directoryPath);
    }
    return status;
}

static SOPC_ReturnStatus may_create_pki_folder(const char* pBasePath, const char* pSubPath, char** ppPath)
{
    SOPC_FileSystem_CreationResult mkdir_res = SOPC_FileSystem_Creation_Error_UnknownIssue;
    char* pPath = NULL;
    SOPC_ReturnStatus status = SOPC_StrConcat(pBasePath, pSubPath, &pPath);
    if (SOPC_STATUS_OK == status)
    {
        mkdir_res = SOPC_FileSystem_mkdir(pPath);
        if (SOPC_FileSystem_Creation_Error_PathAlreadyExists != mkdir_res && SOPC_FileSystem_Creation_OK != mkdir_res)
        {
            status = SOPC_STATUS_NOK;
        }
    }
    if (SOPC_STATUS_OK != status)
    {
        SOPC_Free(pPath);
        pPath = NULL;
    }
    *ppPath = pPath;
    return status;
}

SOPC_ReturnStatus SOPC_PKIProviderNew_WriteToStore(const SOPC_PKIProviderNew* pPKI, const bool bEraseExistingFiles)
{
    if (NULL == pPKI)
    {
        return SOPC_STATUS_INVALID_PARAMETERS;
    }
    /* The case of the PKI is built from buffer (there is no store) */
    if (NULL == pPKI->directoryStorePath)
    {
        return SOPC_STATUS_INVALID_PARAMETERS;
    }
    char* basePath = NULL;
    char* path = NULL;
    SOPC_ReturnStatus status = may_create_pki_folder(pPKI->directoryStorePath, STR_TRUSTLIST, &basePath);
    if (SOPC_STATUS_OK != status)
    {
        return status;
    }
    status = may_create_pki_folder(basePath, STR_TRUSTED, &path);
    if (SOPC_STATUS_OK == status)
    {
        SOPC_Free(path);
        status = may_create_pki_folder(basePath, STR_TRUSTED_CERTS, &path);
        if (SOPC_STATUS_OK == status)
        {
            status = write_cert_to_der_files(pPKI->pTrustedRoots, pPKI->pTrustedCerts, path, bEraseExistingFiles);
        }
    }
    if (SOPC_STATUS_OK == status)
    {
        SOPC_Free(path);
        status = may_create_pki_folder(basePath, STR_TRUSTED_CRL, &path);
        if (SOPC_STATUS_OK == status)
        {
            status = write_crl_to_der_files(pPKI->pTrustedCrl, path, bEraseExistingFiles);
        }
    }
    if (SOPC_STATUS_OK == status)
    {
        SOPC_Free(path);
        status = may_create_pki_folder(basePath, STR_ISSUERS, &path);
    }
    if (SOPC_STATUS_OK == status)
    {
        SOPC_Free(path);
        status = may_create_pki_folder(basePath, STR_ISSUERS_CERTS, &path);
        if (SOPC_STATUS_OK == status)
        {
            status = write_cert_to_der_files(pPKI->pIssuerRoots, pPKI->pIssuerCerts, path, bEraseExistingFiles);
        }
    }
    if (SOPC_STATUS_OK == status)
    {
        SOPC_Free(path);
        status = may_create_pki_folder(basePath, STR_ISSUERS_CRL, &path);
        if (SOPC_STATUS_OK == status)
        {
            status = write_crl_to_der_files(pPKI->pIssuerCrl, path, bEraseExistingFiles);
        }
    }

    SOPC_Free(basePath);
    SOPC_Free(path);

    return status;
}

SOPC_ReturnStatus SOPC_PKIProviderNew_UpdateFromList(SOPC_PKIProviderNew** ppPKI,
                                                     SOPC_CertificateList* pTrustedCerts,
                                                     SOPC_CRLList* pTrustedCrl,
                                                     SOPC_CertificateList* pIssuerCerts,
                                                     SOPC_CRLList* pIssuerCrl,
                                                     const bool bIncludeExistingList)
{
    SOPC_PKIProviderNew* pPKI = *ppPKI;
    /* Check parameters */
    if (NULL == pPKI)
    {
        return SOPC_STATUS_INVALID_PARAMETERS;
    }

    SOPC_ReturnStatus status = SOPC_STATUS_OK;
    SOPC_PKIProviderNew* pTmpPKI = NULL;
    SOPC_CertificateList* tmp_pTrustedCerts = NULL; /* trusted intermediate CA + trusted certificates */
    SOPC_CertificateList* tmp_pTrustedCertsTmp = NULL;
    SOPC_CRLList* tmp_pTrustedCrl = NULL;          /* CRLs of trusted intermediate CA and trusted root CA */
    SOPC_CertificateList* tmp_pIssuerCerts = NULL; /* issuer intermediate CA + issuer root CA */
    SOPC_CertificateList* tmp_pIssuerCertsTmp = NULL;
    SOPC_CRLList* tmp_pIssuerCrl = NULL; /* CRLs of issuer intermediate CA and issuer root CA */

    /* Includes the existing TrustList plus any updates */
    if (bIncludeExistingList)
    {
        /* tmp_pTrustedCerts = pTrustedCerts + pPKI->pTrustedCerts + pPKI->pTrustedRoot */
        status = merge_certificates(pPKI->pTrustedCerts, pTrustedCerts, &tmp_pTrustedCertsTmp);
        if (SOPC_STATUS_OK == status)
        {
            status = merge_certificates(pPKI->pTrustedRoots, tmp_pTrustedCertsTmp, &tmp_pTrustedCerts);
        }
        /* tmp_pTrustedCrl = pTrustedCrl + pPKI->pTrustedCrl */
        if (SOPC_STATUS_OK == status)
        {
            status = merge_crls(pPKI->pTrustedCrl, pTrustedCrl, &tmp_pTrustedCrl);
        }
        /* tmp_pIssuerCerts = pIssuerCerts + pPKI->pIssuerCerts + pPKI->pIssuerRoot */
        if (SOPC_STATUS_OK == status)
        {
            status = merge_certificates(pPKI->pIssuerCerts, pIssuerCerts, &tmp_pIssuerCertsTmp);
        }
        if (SOPC_STATUS_OK == status)
        {
            status = merge_certificates(pPKI->pIssuerRoots, tmp_pIssuerCertsTmp, &tmp_pIssuerCerts);
        }
        /* tmp_pIssuerCrl = pIssuerCrl + pPKI->pIssuerCrl */
        if (SOPC_STATUS_OK == status)
        {
            status = merge_crls(pPKI->pIssuerCrl, pIssuerCrl, &tmp_pIssuerCrl);
        }
        /* Create a new tmp PKI */
        if (SOPC_STATUS_OK == status)
        {
            status = SOPC_PKIProviderNew_CreateFromList(tmp_pTrustedCerts, tmp_pTrustedCrl, tmp_pIssuerCerts,
                                                        tmp_pIssuerCrl, pPKI->pConfig, &pTmpPKI);
        }
    }
    else
    {
        /* Create a new tmp PKI */
        status = SOPC_PKIProviderNew_CreateFromList(pTrustedCerts, pTrustedCrl, pIssuerCerts, pIssuerCrl, pPKI->pConfig,
                                                    &pTmpPKI);
    }
    /* Copy the  directory store path before exchange the data */
    if (SOPC_STATUS_OK == status)
    {
        pTmpPKI->directoryStorePath = SOPC_strdup(pPKI->directoryStorePath);
        if (NULL == pTmpPKI->directoryStorePath)
        {
            SOPC_PKIProviderNew_Free(pTmpPKI);
            status = SOPC_STATUS_OUT_OF_MEMORY;
        }
    }
    /* Exchange the internal data */
    if (SOPC_STATUS_OK == status)
    {
        sopc_pki_clear(pPKI);
        pPKI->pTrustedRoots = pTmpPKI->pTrustedRoots;
        pPKI->pTrustedCerts = pTmpPKI->pTrustedCerts;
        pPKI->pTrustedCrl = pTmpPKI->pTrustedCrl;
        pPKI->pIssuerRoots = pTmpPKI->pIssuerRoots;
        pPKI->pIssuerCerts = pTmpPKI->pIssuerCerts;
        pPKI->pIssuerCrl = pTmpPKI->pIssuerCrl;
        pPKI->pAllCerts = pTmpPKI->pAllCerts;
        pPKI->pAllRoots = pTmpPKI->pAllRoots;
        pPKI->pAllCrl = pTmpPKI->pAllCrl;
        pPKI->directoryStorePath = pTmpPKI->directoryStorePath;
        pPKI->pConfig = pTmpPKI->pConfig;
        SOPC_Free(pTmpPKI);
    }

    SOPC_KeyManager_Certificate_Free(tmp_pTrustedCerts);
    SOPC_KeyManager_Certificate_Free(tmp_pTrustedCertsTmp);
    SOPC_KeyManager_Certificate_Free(tmp_pIssuerCerts);
    SOPC_KeyManager_Certificate_Free(tmp_pIssuerCertsTmp);
    SOPC_KeyManager_CRL_Free(tmp_pTrustedCrl);
    SOPC_KeyManager_CRL_Free(tmp_pIssuerCrl);

    return status;
}
