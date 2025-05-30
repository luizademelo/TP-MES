
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_IO_CHUNKED_INPUT_STREAM_H_
#define UPB_IO_CHUNKED_INPUT_STREAM_H_

#include "upb/io/zero_copy_input_stream.h"
#include "upb/mem/arena.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

upb_ZeroCopyInputStream* upb_ChunkedInputStream_New(const void* data,
                                                    size_t size, size_t limit,
                                                    upb_Arena* arena);

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
