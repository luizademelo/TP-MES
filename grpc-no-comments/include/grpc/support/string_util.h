
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

#ifndef GRPC_SUPPORT_STRING_UTIL_H
#define GRPC_SUPPORT_STRING_UTIL_H

#include <grpc/support/port_platform.h>
#include <grpc/support/time.h>

#ifdef __cplusplus
extern "C" {
#endif

GPRAPI char* gpr_strdup(const char* src);

GPRAPI int gpr_asprintf(char** strp, const char* format, ...)
    GPR_PRINT_FORMAT_CHECK(2, 3);

#ifdef __cplusplus
}
#endif

#endif
