
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

#ifndef PHP_GRPC_H
#define PHP_GRPC_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdbool.h>

#include <php.h>
#include <php_ini.h>
#include <ext/standard/info.h>

#include <grpc/grpc.h>

#include "php7_wrapper.h"
#include "version.h"

extern zend_module_entry grpc_module_entry;
#define phpext_grpc_ptr &grpc_module_entry

#ifdef PHP_WIN32
#define PHP_GRPC_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#define PHP_GRPC_API __attribute__((visibility("default")))
#else
#define PHP_GRPC_API
#endif

#if PHP_MAJOR_VERSION >= 8
#define TSRMLS_CC
#define TSRMLS_C
#define TSRMLS_DC
#define TSRMLS_D
#define TSRMLS_FETCH()
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

PHP_MINIT_FUNCTION(grpc);

PHP_MSHUTDOWN_FUNCTION(grpc);

PHP_MINFO_FUNCTION(grpc);

PHP_RINIT_FUNCTION(grpc);

ZEND_BEGIN_MODULE_GLOBALS(grpc)
  zend_bool initialized;
  zend_bool enable_fork_support;
  char *poll_strategy;
  char *grpc_verbosity;
  char *grpc_trace;
  char *log_filename;
ZEND_END_MODULE_GLOBALS(grpc)

ZEND_EXTERN_MODULE_GLOBALS(grpc);

#ifdef ZTS
#define GRPC_G(v) TSRMG(grpc_globals_id, zend_grpc_globals *, v)
#else
#define GRPC_G(v) (grpc_globals.v)
#endif

#define GRPC_STARTUP_FUNCTION(module)  ZEND_MINIT_FUNCTION(grpc_##module)
#define GRPC_STARTUP(module)           \
  ZEND_MODULE_STARTUP_N(grpc_##module)(INIT_FUNC_ARGS_PASSTHRU)

#endif
