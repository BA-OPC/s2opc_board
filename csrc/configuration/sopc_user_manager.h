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

/** \file
 *
 * \brief Defines the user manager, the applicative interface used to authenticate user,
 *        and authorize read/write operations in the address space.
 *
 * These structure are only used on the server side.
 *
 * The developer shall follow these steps to use the user authentication and authorization:
 *  - create a static const instance of the _Functions structures,
 *  - define a free function, if needed, which free instance of private data,
 *  - define a creation function which mallocs a new _Manager structure, the private date, if needed
 *    and use the private _Function instance.
 */

#ifndef SOPC_USER_MANAGER_H_
#define SOPC_USER_MANAGER_H_

#include <stdbool.h>

#include "sopc_builtintypes.h"

/** Logged in user structure */
typedef struct SOPC_User
{
    bool anonymous;
    SOPC_String username;
} SOPC_User;

typedef struct SOPC_UserAuthentication_Manager SOPC_UserAuthentication_Manager;
typedef struct SOPC_UserAuthorization_Manager SOPC_UserAuthorization_Manager;

typedef void (*SOPC_UserAuthentication_Free_Func)(SOPC_UserAuthentication_Manager* pAuthen);
typedef SOPC_ReturnStatus (*SOPC_UserAuthentication_ValidateUserIdentity_Func)(SOPC_UserAuthentication_Manager* pAuthen,
                                                                               const SOPC_ExtensionObject* pUser,
                                                                               bool* pbUserAuthentified);

typedef void (*SOPC_UserAuthorization_Free_Func)(SOPC_UserAuthorization_Manager* pAuthor);
typedef SOPC_ReturnStatus (*SOPC_UserAuthorization_AuthorizeOperation_Func)(SOPC_UserAuthorization_Manager* pAuthor,
                                                                            const bool bWriteOperation,
                                                                            const SOPC_NodeId* pNid,
                                                                            const uint32_t attributeId,
                                                                            const SOPC_User* pUser,
                                                                            bool* pbOperationAuthorized);

typedef struct SOPC_UserAuthentication_Functions
{
    /**
     * \brief Deallocation function, called upon SOPC_UserAuthentication_Manager destruction.
     *
     * This function can be the standard \p free function if nothing is stored in \p pData.
     */
    SOPC_UserAuthentication_Free_Func pFuncFree;

    /**
     * \brief Called to authorize a user connection, when receiving an ActivateSession request.
     *
     * \warning This callback should not block the thread that calls it, and shall return immediately.
     *
     * \param pAuthen   The SOPC_UserAuthentication_Manager instance.
     * \param pUser     The user identity token which was received in the ActivateSession request.
     * \param pbUserAuthentified  A valid pointer to the uninitialized result of the operation.
     *                            The callback shall set it to false when the connection is refused.
     *
     * \return SOPC_STATUS_OK when \p pbUserAuthentified was set.
     */
    SOPC_UserAuthentication_ValidateUserIdentity_Func pFuncValidateUserIdentity;
} SOPC_UserAuthentication_Functions;

typedef struct SOPC_UserAuthorization_Functions
{
    /**
     * \brief Deallocation function, called upon SOPC_UserAuthorization_Manager destruction.
     *
     * This function can be the standard \p free function if nothing is stored in \p pData.
     */
    SOPC_UserAuthorization_Free_Func pFuncFree;

    /**
     * \brief Called to authorize a read or a write operation in the address space.
     *
     * \warning This callback should not block the thread that calls it, and shall return immediately.
     *
     * \param pAuthor   The SOPC_UserAuthorization_Manager instance.
     * \param bWriteOperation  Set to false for a read operation, or true for a write operation.
     * \param pNid      The operation reads/write this NodeId.
     * \param attributeId  The operation reads/write this attribute.
     * \param pUser     The connected SOPC_User which attempts the operation.
     * \param pbOperationAuthorized  A valid pointer to the uninitialized result of the operation.
     *                               The callback shall set it to false when the operation is refused.
     *
     * \return SOPC_STATUS_OK when \p pbUserAuthorized was set.
     */
    SOPC_UserAuthorization_AuthorizeOperation_Func pFuncAuthorizeOperation;
} SOPC_UserAuthorization_Functions;

struct SOPC_UserAuthentication_Manager
{
    /** It is recommended to have a pointer to a static const instance */
    const SOPC_UserAuthentication_Functions* pFunctions;

    /** This field may be used to store additional and specific data. */
    void* pData;
};

struct SOPC_UserAuthorization_Manager
{
    /** It is recommended to have a pointer to a static const instance */
    const SOPC_UserAuthorization_Functions* pFunctions;

    /** This field may be used to store additional and specific data. */
    void* pData;
};

/**
 * \brief Authenticate a user with the chosen authentication manager.
 *
 * \param pAuthen   The SOPC_UserAuthentication_Manager instance.
 * \param pUser     The user identity token which was received in the ActivateSession request.
 * \param pbUserAuthentified  A valid pointer to the uninitialized result of the operation.
 *                            The callback shall set it to false when the connection is refused.
 *
 * \return SOPC_STATUS_OK when \p pbUserAuthentified was set.
 */
SOPC_ReturnStatus SOPC_UserAuthentication_IsValidUserIdentity(SOPC_UserAuthentication_Manager* pAuthen,
                                                              const SOPC_ExtensionObject* pUser,
                                                              bool* pbUserAuthentified);

/**
 * \brief Authorize an operation with the chosen authorization manager.
 *
 * \param pAuthor   The SOPC_UserAuthorization_Manager instance.
 * \param bWriteOperation  Set to false for a read operation, or true for a write operation.
 * \param pNid      The operation reads/write this NodeId.
 * \param attributeId  The operation reads/write this attribute.
 * \param pUser     The connected SOPC_User which attempts the operation.
 * \param pbOperationAuthorized  A valid pointer to the uninitialized result of the operation.
 *                               The callback shall set it to false when the operation is refused.
 *
 * \return SOPC_STATUS_OK when \p pbUserAuthorized was set.
 */
SOPC_ReturnStatus SOPC_UserAuthorization_IsAuthorizedOperation(SOPC_UserAuthorization_Manager* pAuthor,
                                                               const bool bWriteOperation,
                                                               const SOPC_NodeId* pNid,
                                                               const uint32_t attributeId,
                                                               const SOPC_User* pUser,
                                                               bool* pbOperationAuthorized);
/**
 * \brief Deletes a SOPC_UserAuthentication_Manager using its pFuncFree.
 */
void SOPC_UserAuthentication_FreeManager(SOPC_UserAuthentication_Manager** ppAuthen);

/**
 * \brief Deletes a SOPC_UserAuthorization_Manager using its pFuncFree.
 */
void SOPC_UserAuthorization_FreeManager(SOPC_UserAuthorization_Manager** ppAuthor);

/** \brief A helper implementation that always authentication positively a user. */
SOPC_UserAuthentication_Manager* SOPC_UserAuthentication_CreateManager_UserAlwaysValid(void);

/** \brief A helper implementation that always authorize an operation. */
SOPC_UserAuthorization_Manager* SOPC_UserAuthorization_CreateManager_OperationAlwaysValid(void);

#endif /* SOPC_USER_MANAGER_H_ */
