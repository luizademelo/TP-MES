
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

#ifndef GRPC_RB_H_
#define GRPC_RB_H_

#include <ruby/ruby.h>

#include <grpc/support/time.h>
#include <stdlib.h>

extern VALUE grpc_rb_mGrpcCore;

extern VALUE grpc_rb_sNewServerRpc;

extern VALUE grpc_rb_sStatus;

extern VALUE sym_code;

extern VALUE sym_details;

extern VALUE sym_metadata;

#define GRPC_RB_GC_NOT_MARKED (RUBY_DATA_FUNC)(NULL)

#define GRPC_RB_GC_DONT_FREE (RUBY_DATA_FUNC)(NULL)

#define GRPC_RB_MEMSIZE_UNAVAILABLE (size_t (*)(const void*))(NULL)

VALUE grpc_rb_cannot_alloc(VALUE cls);

VALUE grpc_rb_cannot_init(VALUE self);

VALUE grpc_rb_cannot_init_copy(VALUE copy, VALUE self);

gpr_timespec grpc_rb_time_timeval(VALUE time, int interval);

void grpc_ruby_fork_guard();

void grpc_rb_fork_unsafe_begin();

void grpc_rb_fork_unsafe_end();

void grpc_ruby_init();

#define GRPC_RUBY_ASSERT(x)                                       \
  if (!(x)) {                                                     \
    fprintf(stderr, "%s:%d assert failed\n", __FILE__, __LINE__); \
    abort();                                                      \
  }

#endif
