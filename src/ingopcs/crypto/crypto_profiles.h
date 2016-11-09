/** \file
 *
 * Defines constants for the cryptographic profiles. CryptoProfiles are defined in crypto_types and
 * are defined as struct of pointers. These immutable struct are extern and const, because they are
 * lib-specific (hence CryptoProfile_Get and these variables are in different translation units).
 * The CryptoProfiles should be accessed through CryptoProfile_Get ONLY.
 *
 *  Copyright (C) 2016 Systerel and others.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as
 *  published by the Free Software Foundation, either version 3 of the
 *  License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef INGOPCS_CRYPTO_PROFILES_H_
#define INGOPCS_CRYPTO_PROFILES_H_


#include "crypto_types.h"


// API
const CryptoProfile * CryptoProfile_Get(const char *uri);

// Crypto profiles uri and ID
#define SecurityPolicy_Invalid_ID           0
#define SecurityPolicy_Basic256Sha256_URI   "http://opcfoundation.org/UA/SecurityPolicy#Basic256Sha256"
#define SecurityPolicy_Basic256Sha256_ID    1

// Basic256Sha256, sizes in bytes
#define SecurityPolicy_Basic256Sha256_SymmLen_Block         16
#define SecurityPolicy_Basic256Sha256_SymmLen_Key           32
#define SecurityPolicy_Basic256Sha256_SymmLen_Signature     32
#define SecurityPolicy_Basic256Sha256_CertLen_Thumbprint    20
#define SecurityPolicy_Basic256Sha256_AsymLen_OAEP_Hash     20 /**< RSA OAEP uses SHA-1 */
#define SecurityPolicy_Basic256Sha256_AsymLen_PSS_Hash      32 /**< RSASS PSS uses SHA-256 */
#define SecurityPolicy_Basic256Sha256_AsymLen_KeyMinBits    2048
#define SecurityPolicy_Basic256Sha256_AsymLen_KeyMaxBits    4096

// CryptoProfiles instances
extern const CryptoProfile g_cpBasic256Sha256;


#endif  /* INGOPCS_CRYPTO_PROFILES_H_ */
