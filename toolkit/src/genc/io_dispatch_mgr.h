/******************************************************************************

 File Name            : io_dispatch_mgr.h

 Date                 : 07/08/2017 10:43:13

 C Translator Version : tradc Java V1.0 (14/03/2012)

******************************************************************************/

#ifndef _io_dispatch_mgr_h
#define _io_dispatch_mgr_h

/*--------------------------
   Added by the Translator
  --------------------------*/
#include "b2c.h"

/*-----------------
   IMPORTS Clause
  -----------------*/
#include "channel_mgr_bs.h"
#include "service_mgr.h"

/*--------------
   SEES Clause
  --------------*/
#include "constants.h"

/*------------------------
   INITIALISATION Clause
  ------------------------*/
extern void io_dispatch_mgr__INITIALISATION(void);

/*-------------------------------
   PROMOTES and EXTENDS Clauses
  -------------------------------*/
#define io_dispatch_mgr__client_activate_session service_mgr__client_activate_session
#define io_dispatch_mgr__client_close_session service_mgr__client_close_session
#define io_dispatch_mgr__client_send_service_request_msg service_mgr__client_send_service_request_msg

/*--------------------------
   LOCAL_OPERATIONS Clause
  --------------------------*/
extern void io_dispatch_mgr__get_msg_header_type(
   const constants__t_msg_type_i io_dispatch_mgr__msg_typ,
   constants__t_msg_header_type * const io_dispatch_mgr__header_type);
extern void io_dispatch_mgr__get_msg_service_class(
   const constants__t_msg_type_i io_dispatch_mgr__msg_typ,
   constants__t_msg_service_class * const io_dispatch_mgr__service_class);

/*--------------------
   OPERATIONS Clause
  --------------------*/
extern void io_dispatch_mgr__client_activate_new_session(
   const constants__t_channel_config_idx_i io_dispatch_mgr__channel_config_idx,
   const constants__t_user_i io_dispatch_mgr__user,
   t_bool * const io_dispatch_mgr__bres);
extern void io_dispatch_mgr__client_channel_connected_event(
   const constants__t_channel_config_idx_i io_dispatch_mgr__channel_config_idx,
   const constants__t_channel_i io_dispatch_mgr__channel);
extern void io_dispatch_mgr__client_secure_channel_timeout(
   const constants__t_channel_config_idx_i io_dispatch_mgr__channel_config_idx);
extern void io_dispatch_mgr__close_all_active_connections(
   t_bool * const io_dispatch_mgr__bres);
extern void io_dispatch_mgr__receive_msg_buffer(
   const constants__t_channel_i io_dispatch_mgr__channel,
   const constants__t_byte_buffer_i io_dispatch_mgr__buffer);
extern void io_dispatch_mgr__secure_channel_lost(
   const constants__t_channel_i io_dispatch_mgr__channel);
extern void io_dispatch_mgr__server_channel_connected_event(
   const constants__t_endpoint_config_idx_i io_dispatch_mgr__endpoint_config_idx,
   const constants__t_channel_config_idx_i io_dispatch_mgr__channel_config_idx,
   const constants__t_channel_i io_dispatch_mgr__channel);

#endif
