
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

#ifndef GRPC_SLICE_H
#define GRPC_SLICE_H

#include <grpc/impl/slice_type.h>
#include <grpc/support/port_platform.h>
#include <grpc/support/sync.h>

#ifdef __cplusplus
extern "C" {
#endif

GPRAPI grpc_slice grpc_slice_ref(grpc_slice s);

GPRAPI void grpc_slice_unref(grpc_slice s);

GPRAPI grpc_slice grpc_slice_copy(grpc_slice s);

GPRAPI grpc_slice grpc_slice_new(void* p, size_t len, void (*destroy)(void*));

GPRAPI grpc_slice grpc_slice_new_with_user_data(void* p, size_t len,
                                                void (*destroy)(void*),
                                                void* user_data);

GPRAPI grpc_slice grpc_slice_new_with_len(void* p, size_t len,
                                          void (*destroy)(void*, size_t));

GPRAPI grpc_slice grpc_slice_malloc(size_t length);
GPRAPI grpc_slice grpc_slice_malloc_large(size_t length);

#define GRPC_SLICE_MALLOC(len) grpc_slice_malloc(len)

GPRAPI grpc_slice grpc_slice_from_copied_string(const char* source);

GPRAPI grpc_slice grpc_slice_from_copied_buffer(const char* source, size_t len);

GPRAPI grpc_slice grpc_slice_from_static_string(const char* source);

GPRAPI grpc_slice grpc_slice_from_static_buffer(const void* source, size_t len);

GPRAPI grpc_slice grpc_slice_sub(grpc_slice s, size_t begin, size_t end);

GPRAPI grpc_slice grpc_slice_sub_no_ref(grpc_slice s, size_t begin, size_t end);

GPRAPI grpc_slice grpc_slice_split_tail(grpc_slice* s, size_t split);

typedef enum {
  GRPC_SLICE_REF_TAIL = 1,
  GRPC_SLICE_REF_HEAD = 2,
  GRPC_SLICE_REF_BOTH = 1 + 2
} grpc_slice_ref_whom;

GPRAPI grpc_slice grpc_slice_split_tail_maybe_ref(grpc_slice* s, size_t split,
                                                  grpc_slice_ref_whom ref_whom);

GPRAPI grpc_slice grpc_slice_split_head(grpc_slice* s, size_t split);

GPRAPI grpc_slice grpc_empty_slice(void);

GPRAPI int grpc_slice_eq(grpc_slice a, grpc_slice b);

GPRAPI int grpc_slice_cmp(grpc_slice a, grpc_slice b);
GPRAPI int grpc_slice_str_cmp(grpc_slice a, const char* b);

GPRAPI int grpc_slice_buf_start_eq(grpc_slice a, const void* b, size_t blen);

GPRAPI int grpc_slice_rchr(grpc_slice s, char c);
GPRAPI int grpc_slice_chr(grpc_slice s, char c);

GPRAPI int grpc_slice_slice(grpc_slice haystack, grpc_slice needle);

GPRAPI int grpc_slice_is_equivalent(grpc_slice a, grpc_slice b);

GPRAPI grpc_slice grpc_slice_dup(grpc_slice a);

GPRAPI char* grpc_slice_to_c_string(grpc_slice s);

#ifdef __cplusplus
}
#endif

#endif
