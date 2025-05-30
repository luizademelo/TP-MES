
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

#include "php_grpc.h"

#include "call.h"
#include "channel.h"
#include "server.h"
#include "timeval.h"
#include "version.h"
#include "channel_credentials.h"
#include "call_credentials.h"
#include "server_credentials.h"
#include "completion_queue.h"
#include <inttypes.h>
#include <grpc/credentials.h>
#include <grpc/grpc_security.h>
#include <grpc/support/alloc.h>
#include <grpc/support/log.h>
#include <grpc/support/string_util.h>
#include <grpc/support/time.h>
#include <ext/spl/spl_exceptions.h>
#include <zend_exceptions.h>

#ifdef GRPC_POSIX_FORK_ALLOW_PTHREAD_ATFORK
#include <pthread.h>
#endif

ZEND_DECLARE_MODULE_GLOBALS(grpc)
static PHP_GINIT_FUNCTION(grpc);
HashTable grpc_persistent_list;
HashTable grpc_target_upper_bound_map;

const zend_function_entry grpc_functions[] = {
    PHP_FE_END
};

ZEND_DECLARE_MODULE_GLOBALS(grpc);

zend_module_entry grpc_module_entry = {
  STANDARD_MODULE_HEADER,
  "grpc",
  grpc_functions,
  PHP_MINIT(grpc),
  PHP_MSHUTDOWN(grpc),
  PHP_RINIT(grpc),
  NULL,
  PHP_MINFO(grpc),
  PHP_GRPC_VERSION,
  PHP_MODULE_GLOBALS(grpc),
  PHP_GINIT(grpc),
  NULL,
  NULL,
  STANDARD_MODULE_PROPERTIES_EX};

#ifdef COMPILE_DL_GRPC
ZEND_GET_MODULE(grpc)
#endif

   PHP_INI_BEGIN()
   STD_PHP_INI_ENTRY("grpc.enable_fork_support", "0", PHP_INI_SYSTEM, OnUpdateBool,
                     enable_fork_support, zend_grpc_globals, grpc_globals)
   STD_PHP_INI_ENTRY("grpc.poll_strategy", NULL, PHP_INI_SYSTEM, OnUpdateString,
                     poll_strategy, zend_grpc_globals, grpc_globals)
   STD_PHP_INI_ENTRY("grpc.grpc_verbosity", NULL, PHP_INI_SYSTEM, OnUpdateString,
                     grpc_verbosity, zend_grpc_globals, grpc_globals)
   STD_PHP_INI_ENTRY("grpc.grpc_trace", NULL, PHP_INI_SYSTEM, OnUpdateString,
                     grpc_trace, zend_grpc_globals, grpc_globals)
   PHP_INI_END()

void create_new_channel(
    wrapped_grpc_channel *channel,
    char *target,
    grpc_channel_args args,
    wrapped_grpc_channel_credentials *creds) {
  if (creds == NULL) {
    grpc_channel_credentials *insecure_creds = grpc_insecure_credentials_create();
    channel->wrapper->wrapped = grpc_channel_create(target, insecure_creds, &args);
    grpc_channel_credentials_release(insecure_creds);
  } else {
    channel->wrapper->wrapped =
        grpc_channel_create(target, creds->wrapped, &args);
  }
}

void acquire_persistent_locks() {
  zval *data;
  PHP_GRPC_HASH_FOREACH_VAL_START(&grpc_persistent_list, data)
    php_grpc_zend_resource *rsrc  =
                (php_grpc_zend_resource*) PHP_GRPC_HASH_VALPTR_TO_VAL(data)
    if (rsrc == NULL) {
      break;
    }
    channel_persistent_le_t* le = rsrc->ptr;

    gpr_mu_lock(&le->channel->mu);
  PHP_GRPC_HASH_FOREACH_END()
}

void release_persistent_locks() {
  zval *data;
  PHP_GRPC_HASH_FOREACH_VAL_START(&grpc_persistent_list, data)
    php_grpc_zend_resource *rsrc  =
                (php_grpc_zend_resource*) PHP_GRPC_HASH_VALPTR_TO_VAL(data)
    if (rsrc == NULL) {
      break;
    }
    channel_persistent_le_t* le = rsrc->ptr;

    gpr_mu_unlock(&le->channel->mu);
  PHP_GRPC_HASH_FOREACH_END()
}

void destroy_grpc_channels() {
  zval *data;
  PHP_GRPC_HASH_FOREACH_VAL_START(&grpc_persistent_list, data)
    php_grpc_zend_resource *rsrc  =
                (php_grpc_zend_resource*) PHP_GRPC_HASH_VALPTR_TO_VAL(data)
    if (rsrc == NULL) {
      break;
    }
    channel_persistent_le_t* le = rsrc->ptr;

    wrapped_grpc_channel wrapped_channel;
    wrapped_channel.wrapper = le->channel;
    grpc_channel_wrapper *channel = wrapped_channel.wrapper;
    grpc_channel_destroy(channel->wrapped);
    channel->wrapped = NULL;
  PHP_GRPC_HASH_FOREACH_END()
}

void prefork() {
  acquire_persistent_locks();
}

void php_grpc_clean_persistent_list(TSRMLS_D) {
    zend_hash_clean(&grpc_persistent_list);
    zend_hash_clean(&grpc_target_upper_bound_map);
}

void postfork_child() {
  TSRMLS_FETCH();

  destroy_grpc_channels();

  release_persistent_locks();

  php_grpc_clean_persistent_list(TSRMLS_C);

  grpc_php_shutdown_completion_queue(TSRMLS_C);

  grpc_shutdown();
  if (grpc_is_initialized() > 0) {
    zend_throw_exception(spl_ce_UnexpectedValueException,
                         "Oops, failed to shutdown gRPC Core after fork()",
                         1 TSRMLS_CC);
  }

  grpc_init();
  grpc_php_init_completion_queue(TSRMLS_C);
}

void postfork_parent() {
  release_persistent_locks();
}

void register_fork_handlers() {
  if (getenv("GRPC_ENABLE_FORK_SUPPORT")) {
#ifdef GRPC_POSIX_FORK_ALLOW_PTHREAD_ATFORK
    pthread_atfork(&prefork, &postfork_parent, &postfork_child);
#endif
  }
}

void apply_ini_settings(TSRMLS_D) {
  if (GRPC_G(enable_fork_support)) {
    char *enable_str = malloc(sizeof("GRPC_ENABLE_FORK_SUPPORT=1"));
    strcpy(enable_str, "GRPC_ENABLE_FORK_SUPPORT=1");
    putenv(enable_str);
  }

  if (GRPC_G(poll_strategy)) {
    char *poll_str = malloc(sizeof("GRPC_POLL_STRATEGY=") +
                            strlen(GRPC_G(poll_strategy)));
    strcpy(poll_str, "GRPC_POLL_STRATEGY=");
    strcat(poll_str, GRPC_G(poll_strategy));
    putenv(poll_str);
  }

  if (GRPC_G(grpc_verbosity)) {
    char *verbosity_str = malloc(sizeof("GRPC_VERBOSITY=") +
                                 strlen(GRPC_G(grpc_verbosity)));
    strcpy(verbosity_str, "GRPC_VERBOSITY=");
    strcat(verbosity_str, GRPC_G(grpc_verbosity));
    putenv(verbosity_str);
  }

  if (GRPC_G(grpc_trace)) {
    char *trace_str = malloc(sizeof("GRPC_TRACE=") +
                             strlen(GRPC_G(grpc_trace)));
    strcpy(trace_str, "GRPC_TRACE=");
    strcat(trace_str, GRPC_G(grpc_trace));
    putenv(trace_str);
  }
}

PHP_MINIT_FUNCTION(grpc) {
  REGISTER_INI_ENTRIES();

  REGISTER_LONG_CONSTANT("Grpc\\CALL_OK", GRPC_CALL_OK,
                         CONST_CS | CONST_PERSISTENT);

  REGISTER_LONG_CONSTANT("Grpc\\CALL_ERROR", GRPC_CALL_ERROR,
                         CONST_CS | CONST_PERSISTENT);

  REGISTER_LONG_CONSTANT("Grpc\\CALL_ERROR_NOT_ON_SERVER",
                         GRPC_CALL_ERROR_NOT_ON_SERVER,
                         CONST_CS | CONST_PERSISTENT);

  REGISTER_LONG_CONSTANT("Grpc\\CALL_ERROR_NOT_ON_CLIENT",
                         GRPC_CALL_ERROR_NOT_ON_CLIENT,
                         CONST_CS | CONST_PERSISTENT);

  REGISTER_LONG_CONSTANT("Grpc\\CALL_ERROR_ALREADY_INVOKED",
                         GRPC_CALL_ERROR_ALREADY_INVOKED,
                         CONST_CS | CONST_PERSISTENT);

  REGISTER_LONG_CONSTANT("Grpc\\CALL_ERROR_NOT_INVOKED",
                         GRPC_CALL_ERROR_NOT_INVOKED,
                         CONST_CS | CONST_PERSISTENT);

  REGISTER_LONG_CONSTANT("Grpc\\CALL_ERROR_ALREADY_FINISHED",
                         GRPC_CALL_ERROR_ALREADY_FINISHED,
                         CONST_CS | CONST_PERSISTENT);

  REGISTER_LONG_CONSTANT("Grpc\\CALL_ERROR_TOO_MANY_OPERATIONS",
                         GRPC_CALL_ERROR_TOO_MANY_OPERATIONS,
                         CONST_CS | CONST_PERSISTENT);

  REGISTER_LONG_CONSTANT("Grpc\\CALL_ERROR_INVALID_FLAGS",
                         GRPC_CALL_ERROR_INVALID_FLAGS,
                         CONST_CS | CONST_PERSISTENT);

  REGISTER_LONG_CONSTANT("Grpc\\WRITE_BUFFER_HINT", GRPC_WRITE_BUFFER_HINT,
                         CONST_CS | CONST_PERSISTENT);

  REGISTER_LONG_CONSTANT("Grpc\\WRITE_NO_COMPRESS", GRPC_WRITE_NO_COMPRESS,
                         CONST_CS | CONST_PERSISTENT);

  REGISTER_LONG_CONSTANT("Grpc\\STATUS_OK", GRPC_STATUS_OK,
                         CONST_CS | CONST_PERSISTENT);

  REGISTER_LONG_CONSTANT("Grpc\\STATUS_CANCELLED", GRPC_STATUS_CANCELLED,
                         CONST_CS | CONST_PERSISTENT);

  REGISTER_LONG_CONSTANT("Grpc\\STATUS_UNKNOWN", GRPC_STATUS_UNKNOWN,
                         CONST_CS | CONST_PERSISTENT);

  REGISTER_LONG_CONSTANT("Grpc\\STATUS_INVALID_ARGUMENT",
                         GRPC_STATUS_INVALID_ARGUMENT,
                         CONST_CS | CONST_PERSISTENT);

  REGISTER_LONG_CONSTANT("Grpc\\STATUS_DEADLINE_EXCEEDED",
                         GRPC_STATUS_DEADLINE_EXCEEDED,
                         CONST_CS | CONST_PERSISTENT);

  REGISTER_LONG_CONSTANT("Grpc\\STATUS_NOT_FOUND", GRPC_STATUS_NOT_FOUND,
                         CONST_CS | CONST_PERSISTENT);

  REGISTER_LONG_CONSTANT("Grpc\\STATUS_ALREADY_EXISTS",
                         GRPC_STATUS_ALREADY_EXISTS,
                         CONST_CS | CONST_PERSISTENT);

  REGISTER_LONG_CONSTANT("Grpc\\STATUS_PERMISSION_DENIED",
                         GRPC_STATUS_PERMISSION_DENIED,
                         CONST_CS | CONST_PERSISTENT);

  REGISTER_LONG_CONSTANT("Grpc\\STATUS_UNAUTHENTICATED",
                         GRPC_STATUS_UNAUTHENTICATED,
                         CONST_CS | CONST_PERSISTENT);

  REGISTER_LONG_CONSTANT("Grpc\\STATUS_RESOURCE_EXHAUSTED",
                         GRPC_STATUS_RESOURCE_EXHAUSTED,
                         CONST_CS | CONST_PERSISTENT);

  REGISTER_LONG_CONSTANT("Grpc\\STATUS_FAILED_PRECONDITION",
                         GRPC_STATUS_FAILED_PRECONDITION,
                         CONST_CS | CONST_PERSISTENT);

  REGISTER_LONG_CONSTANT("Grpc\\STATUS_ABORTED", GRPC_STATUS_ABORTED,
                         CONST_CS | CONST_PERSISTENT);

  REGISTER_LONG_CONSTANT("Grpc\\STATUS_OUT_OF_RANGE",
                         GRPC_STATUS_OUT_OF_RANGE,
                         CONST_CS | CONST_PERSISTENT);

  REGISTER_LONG_CONSTANT("Grpc\\STATUS_UNIMPLEMENTED",
                         GRPC_STATUS_UNIMPLEMENTED,
                         CONST_CS | CONST_PERSISTENT);

  REGISTER_LONG_CONSTANT("Grpc\\STATUS_INTERNAL", GRPC_STATUS_INTERNAL,
                         CONST_CS | CONST_PERSISTENT);

  REGISTER_LONG_CONSTANT("Grpc\\STATUS_UNAVAILABLE", GRPC_STATUS_UNAVAILABLE,
                         CONST_CS | CONST_PERSISTENT);

  REGISTER_LONG_CONSTANT("Grpc\\STATUS_DATA_LOSS", GRPC_STATUS_DATA_LOSS,
                         CONST_CS | CONST_PERSISTENT);

  REGISTER_LONG_CONSTANT("Grpc\\OP_SEND_INITIAL_METADATA",
                         GRPC_OP_SEND_INITIAL_METADATA,
                         CONST_CS | CONST_PERSISTENT);

  REGISTER_LONG_CONSTANT("Grpc\\OP_SEND_MESSAGE",
                         GRPC_OP_SEND_MESSAGE,
                         CONST_CS | CONST_PERSISTENT);

  REGISTER_LONG_CONSTANT("Grpc\\OP_SEND_CLOSE_FROM_CLIENT",
                         GRPC_OP_SEND_CLOSE_FROM_CLIENT,
                         CONST_CS | CONST_PERSISTENT);

  REGISTER_LONG_CONSTANT("Grpc\\OP_SEND_STATUS_FROM_SERVER",
                         GRPC_OP_SEND_STATUS_FROM_SERVER,
                         CONST_CS | CONST_PERSISTENT);

  REGISTER_LONG_CONSTANT("Grpc\\OP_RECV_INITIAL_METADATA",
                         GRPC_OP_RECV_INITIAL_METADATA,
                         CONST_CS | CONST_PERSISTENT);

  REGISTER_LONG_CONSTANT("Grpc\\OP_RECV_MESSAGE",
                         GRPC_OP_RECV_MESSAGE,
                         CONST_CS | CONST_PERSISTENT);

  REGISTER_LONG_CONSTANT("Grpc\\OP_RECV_STATUS_ON_CLIENT",
                         GRPC_OP_RECV_STATUS_ON_CLIENT,
                         CONST_CS | CONST_PERSISTENT);

  REGISTER_LONG_CONSTANT("Grpc\\OP_RECV_CLOSE_ON_SERVER",
                         GRPC_OP_RECV_CLOSE_ON_SERVER,
                         CONST_CS | CONST_PERSISTENT);

  REGISTER_LONG_CONSTANT("Grpc\\CHANNEL_IDLE",
                         GRPC_CHANNEL_IDLE,
                         CONST_CS | CONST_PERSISTENT);

  REGISTER_LONG_CONSTANT("Grpc\\CHANNEL_CONNECTING",
                         GRPC_CHANNEL_CONNECTING,
                         CONST_CS | CONST_PERSISTENT);

  REGISTER_LONG_CONSTANT("Grpc\\CHANNEL_READY",
                         GRPC_CHANNEL_READY,
                         CONST_CS | CONST_PERSISTENT);

  REGISTER_LONG_CONSTANT("Grpc\\CHANNEL_TRANSIENT_FAILURE",
                         GRPC_CHANNEL_TRANSIENT_FAILURE,
                         CONST_CS | CONST_PERSISTENT);

  REGISTER_LONG_CONSTANT("Grpc\\CHANNEL_FATAL_FAILURE",
                         GRPC_CHANNEL_SHUTDOWN,
                         CONST_CS | CONST_PERSISTENT);

  REGISTER_STRING_CONSTANT("Grpc\\VERSION", PHP_GRPC_VERSION,
                           CONST_CS | CONST_PERSISTENT);

  grpc_init_call(TSRMLS_C);
  GRPC_STARTUP(channel);
  grpc_init_server(TSRMLS_C);
  grpc_init_timeval(TSRMLS_C);
  grpc_init_channel_credentials(TSRMLS_C);
  grpc_init_call_credentials(TSRMLS_C);
  grpc_init_server_credentials(TSRMLS_C);
  return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(grpc) {
  UNREGISTER_INI_ENTRIES();

  if (GRPC_G(initialized)) {
    zend_hash_clean(&grpc_persistent_list);
    zend_hash_destroy(&grpc_persistent_list);
    zend_hash_clean(&grpc_target_upper_bound_map);
    zend_hash_destroy(&grpc_target_upper_bound_map);
    grpc_shutdown_timeval(TSRMLS_C);
    grpc_php_shutdown_completion_queue(TSRMLS_C);
    grpc_shutdown();
    GRPC_G(initialized) = 0;
  }
  return SUCCESS;
}

PHP_MINFO_FUNCTION(grpc) {
  php_info_print_table_start();
  php_info_print_table_row(2, "grpc support", "enabled");
  php_info_print_table_row(2, "grpc module version", PHP_GRPC_VERSION);
  php_info_print_table_end();
  DISPLAY_INI_ENTRIES();
}

PHP_RINIT_FUNCTION(grpc) {
  if (!GRPC_G(initialized)) {
    apply_ini_settings(TSRMLS_C);
    grpc_init();
    register_fork_handlers();
    grpc_php_init_completion_queue(TSRMLS_C);
    GRPC_G(initialized) = 1;
  }
  return SUCCESS;
}

static PHP_GINIT_FUNCTION(grpc) {
  grpc_globals->initialized = 0;
  grpc_globals->enable_fork_support = 0;
  grpc_globals->poll_strategy = NULL;
  grpc_globals->grpc_verbosity = NULL;
  grpc_globals->grpc_trace = NULL;
}
