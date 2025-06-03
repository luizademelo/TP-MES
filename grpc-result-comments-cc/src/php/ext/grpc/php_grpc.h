Here's the commented version of the code:

```c++
/*
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
 */

#ifndef PHP_GRPC_H
#define PHP_GRPC_H

// Include configuration file if available
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdbool.h>

// Standard PHP includes
#include <php.h>
#include <php_ini.h>
#include <ext/standard/info.h>

// gRPC core library
#include <grpc/grpc.h>

// Project-specific includes
#include "php7_wrapper.h"
#include "version.h"

// Module entry declaration for PHP extension
extern zend_module_entry grpc_module_entry;
#define phpext_grpc_ptr &grpc_module_entry

// Platform-specific API export definitions
#ifdef PHP_WIN32
#define PHP_GRPC_API __declspec(dllexport)  // Windows DLL export
#elif defined(__GNUC__) && __GNUC__ >= 4
#define PHP_GRPC_API __attribute__((visibility("default")))  // GCC visibility attribute
#else
#define PHP_GRPC_API  // Default empty definition
#endif

// Thread-safe resource management macros for PHP 8+ compatibility
#if PHP_MAJOR_VERSION >= 8
#define TSRMLS_CC
#define TSRMLS_C
#define TSRMLS_DC
#define TSRMLS_D
#define TSRMLS_FETCH()
#endif

// Include Thread Safe Resource Manager if ZTS (Zend Thread Safety) is enabled
#ifdef ZTS
#include "TSRM.h"
#endif

// PHP module lifecycle function declarations
PHP_MINIT_FUNCTION(grpc);       // Module initialization
PHP_MSHUTDOWN_FUNCTION(grpc);   // Module shutdown
PHP_MINFO_FUNCTION(grpc);       // Module information
PHP_RINIT_FUNCTION(grpc);       // Request initialization

// Definition of module-level global variables
ZEND_BEGIN_MODULE_GLOBALS(grpc)
  zend_bool initialized;           // Flag indicating if module is initialized
  zend_bool enable_fork_support;   // Flag for fork support
  char *poll_strategy;             // gRPC polling strategy
  char *grpc_verbosity;            // Verbosity level for gRPC
  char *grpc_trace;                // Trace configuration
  char *log_filename;              // Log file path
ZEND_END_MODULE_GLOBALS(grpc)

// Declaration of module globals
ZEND_EXTERN_MODULE_GLOBALS(grpc);

// Thread-safe or non-thread-safe access to module globals
#ifdef ZTS
#define GRPC_G(v) TSRMG(grpc_globals_id, zend_grpc_globals *, v)  // Thread-safe access
#else
#define GRPC_G(v) (grpc_globals.v)  // Direct access in non-thread-safe mode
#endif

// Macros for module startup functions
#define GRPC_STARTUP_FUNCTION(module)  ZEND_MINIT_FUNCTION(grpc_##module)
#define GRPC_STARTUP(module)           \
  ZEND_MODULE_STARTUP_N(grpc_##module)(INIT_FUNC_ARGS_PASSTHRU)

#endif  // PHP_GRPC_H
```

Key improvements in the comments:
1. Added explanations for platform-specific macros (Windows vs GCC)
2. Documented the purpose of each PHP module lifecycle function
3. Explained the module global variables and their purposes
4. Clarified the thread-safety related macros and includes
5. Added section headers to group related functionality
6. Explained the version compatibility macros for PHP 8+
7. Documented the purpose of each include file

The comments are concise but provide enough context for future maintainers to understand the structure and purpose of this header file.