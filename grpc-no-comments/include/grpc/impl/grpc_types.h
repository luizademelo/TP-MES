
/*
 *
 * Copyright 2015 gRPC authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#ifndef GRPC_IMPL_GRPC_TYPES_H
#define GRPC_IMPL_GRPC_TYPES_H

#include <grpc/impl/channel_arg_names.h>
#include <grpc/impl/compression_types.h>
#include <grpc/slice.h>
#include <grpc/status.h>
#include <grpc/support/port_platform.h>
#include <grpc/support/time.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
  GRPC_BB_RAW

} grpc_byte_buffer_type;

typedef struct grpc_byte_buffer {
  void* reserved;
  grpc_byte_buffer_type type;
  union grpc_byte_buffer_data {
    struct  {
      void* reserved[8];
    } reserved;
    struct grpc_compressed_buffer {
      grpc_compression_algorithm compression;
      grpc_slice_buffer slice_buffer;
    } raw;
  } data;
} grpc_byte_buffer;

typedef struct grpc_completion_queue grpc_completion_queue;

typedef struct grpc_channel grpc_channel;

typedef struct grpc_server grpc_server;

typedef struct grpc_call grpc_call;

typedef struct grpc_socket_mutator grpc_socket_mutator;

typedef struct grpc_socket_factory grpc_socket_factory;

typedef enum {
  GRPC_ARG_STRING,
  GRPC_ARG_INTEGER,
  GRPC_ARG_POINTER
} grpc_arg_type;

typedef struct grpc_arg_pointer_vtable {
  void* (*copy)(void* p);
  void (*destroy)(void* p);
  int (*cmp)(void* p, void* q);
} grpc_arg_pointer_vtable;

typedef struct {
  grpc_arg_type type;
  char* key;
  union grpc_arg_value {
    char* string;
    int integer;
    struct grpc_arg_pointer {
      void* p;
      const grpc_arg_pointer_vtable* vtable;
    } pointer;
  } value;
} grpc_arg;

typedef struct {
  size_t num_args;
  grpc_arg* args;
} grpc_channel_args;

typedef enum grpc_call_error {

  GRPC_CALL_OK = 0,

  GRPC_CALL_ERROR,

  GRPC_CALL_ERROR_NOT_ON_SERVER,

  GRPC_CALL_ERROR_NOT_ON_CLIENT,

  GRPC_CALL_ERROR_ALREADY_ACCEPTED,

  GRPC_CALL_ERROR_ALREADY_INVOKED,

  GRPC_CALL_ERROR_NOT_INVOKED,

  GRPC_CALL_ERROR_ALREADY_FINISHED,

  GRPC_CALL_ERROR_TOO_MANY_OPERATIONS,

  GRPC_CALL_ERROR_INVALID_FLAGS,

  GRPC_CALL_ERROR_INVALID_METADATA,

  GRPC_CALL_ERROR_INVALID_MESSAGE,

  GRPC_CALL_ERROR_NOT_SERVER_COMPLETION_QUEUE,

  GRPC_CALL_ERROR_BATCH_TOO_BIG,

  GRPC_CALL_ERROR_PAYLOAD_TYPE_MISMATCH,

  GRPC_CALL_ERROR_COMPLETION_QUEUE_SHUTDOWN
} grpc_call_error;

#define GRPC_DEFAULT_MAX_SEND_MESSAGE_LENGTH (-1)
#define GRPC_DEFAULT_MAX_RECV_MESSAGE_LENGTH (4 * 1024 * 1024)

#define GRPC_WRITE_BUFFER_HINT (0x00000001u)

#define GRPC_WRITE_NO_COMPRESS (0x00000002u)

#define GRPC_WRITE_THROUGH (0x00000004u)

#define GRPC_WRITE_USED_MASK \
  (GRPC_WRITE_BUFFER_HINT | GRPC_WRITE_NO_COMPRESS | GRPC_WRITE_THROUGH)

#define GRPC_INITIAL_METADATA_WAIT_FOR_READY (0x00000020u)

#define GRPC_INITIAL_METADATA_WAIT_FOR_READY_EXPLICITLY_SET (0x00000080u)

#define GRPC_INITIAL_METADATA_USED_MASK                  \
  (GRPC_INITIAL_METADATA_WAIT_FOR_READY_EXPLICITLY_SET | \
   GRPC_INITIAL_METADATA_WAIT_FOR_READY | GRPC_WRITE_THROUGH)

typedef struct grpc_metadata {

  grpc_slice key;
  grpc_slice value;

  struct  {
    void* obfuscated[4];
  } internal_data;
} grpc_metadata;

typedef enum grpc_completion_type {

  GRPC_QUEUE_SHUTDOWN,

  GRPC_QUEUE_TIMEOUT,

  GRPC_OP_COMPLETE
} grpc_completion_type;

typedef struct grpc_event {

  grpc_completion_type type;

  int success;

  void* tag;
} grpc_event;

typedef struct {
  size_t count;
  size_t capacity;
  grpc_metadata* metadata;
} grpc_metadata_array;

typedef struct {
  grpc_slice method;
  grpc_slice host;
  gpr_timespec deadline;
} grpc_call_details;

typedef enum {

  GRPC_OP_SEND_INITIAL_METADATA = 0,

  GRPC_OP_SEND_MESSAGE,

  GRPC_OP_SEND_CLOSE_FROM_CLIENT,

  GRPC_OP_SEND_STATUS_FROM_SERVER,

  GRPC_OP_RECV_INITIAL_METADATA,

  GRPC_OP_RECV_MESSAGE,

  GRPC_OP_RECV_STATUS_ON_CLIENT,

  GRPC_OP_RECV_CLOSE_ON_SERVER
} grpc_op_type;

struct grpc_byte_buffer;

typedef struct grpc_op {

  grpc_op_type op;

  uint32_t flags;

  void* reserved;
  union grpc_op_data {

    struct  {
      void* reserved[8];
    } reserved;
    struct grpc_op_send_initial_metadata {
      size_t count;
      grpc_metadata* metadata;

      struct grpc_op_send_initial_metadata_maybe_compression_level {
        uint8_t is_set;
        grpc_compression_level level;
      } maybe_compression_level;
    } send_initial_metadata;
    struct grpc_op_send_message {

      struct grpc_byte_buffer* send_message;
    } send_message;
    struct grpc_op_send_status_from_server {
      size_t trailing_metadata_count;
      grpc_metadata* trailing_metadata;
      grpc_status_code status;

      grpc_slice* status_details;
    } send_status_from_server;

    struct grpc_op_recv_initial_metadata {
      grpc_metadata_array* recv_initial_metadata;
    } recv_initial_metadata;

    struct grpc_op_recv_message {
      struct grpc_byte_buffer** recv_message;
    } recv_message;
    struct grpc_op_recv_status_on_client {

      grpc_metadata_array* trailing_metadata;
      grpc_status_code* status;
      grpc_slice* status_details;

      const char** error_string;
    } recv_status_on_client;
    struct grpc_op_recv_close_on_server {

      int* cancelled;
    } recv_close_on_server;
  } data;
} grpc_op;

typedef struct {

  char** lb_policy_name;

  char** service_config_json;
} grpc_channel_info;

typedef struct grpc_resource_quota grpc_resource_quota;

typedef enum {

  GRPC_CQ_DEFAULT_POLLING,

  GRPC_CQ_NON_LISTENING,

  GRPC_CQ_NON_POLLING
} grpc_cq_polling_type;

typedef enum {

  GRPC_CQ_NEXT,

  GRPC_CQ_PLUCK,

  GRPC_CQ_CALLBACK
} grpc_cq_completion_type;

typedef struct grpc_completion_queue_functor {

  void (*functor_run)(struct grpc_completion_queue_functor*, int);

  int inlineable;

  int internal_success;
  struct grpc_completion_queue_functor* internal_next;
} grpc_completion_queue_functor;

#define GRPC_CQ_CURRENT_VERSION 2
#define GRPC_CQ_VERSION_MINIMUM_FOR_CALLBACKABLE 2
typedef struct grpc_completion_queue_attributes {

  int version;

  grpc_cq_completion_type cq_completion_type;

  grpc_cq_polling_type cq_polling_type;

  grpc_completion_queue_functor* cq_shutdown_cb;

} grpc_completion_queue_attributes;

typedef struct grpc_completion_queue_factory grpc_completion_queue_factory;

#ifdef __cplusplus
}
#endif

#endif
