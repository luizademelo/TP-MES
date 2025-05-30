
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_IO_ZERO_COPY_OUTPUT_STREAM_H_
#define UPB_IO_ZERO_COPY_OUTPUT_STREAM_H_

#include "upb/base/status.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct upb_ZeroCopyOutputStream upb_ZeroCopyOutputStream;

typedef struct {

  void* (*Next)(struct upb_ZeroCopyOutputStream* z, size_t* count,
                upb_Status* status);

  void (*BackUp)(struct upb_ZeroCopyOutputStream* z, size_t count);

  size_t (*ByteCount)(const struct upb_ZeroCopyOutputStream* z);
} _upb_ZeroCopyOutputStream_VTable;

struct upb_ZeroCopyOutputStream {
  const _upb_ZeroCopyOutputStream_VTable* vtable;
};

UPB_INLINE void* upb_ZeroCopyOutputStream_Next(upb_ZeroCopyOutputStream* z,
                                               size_t* count,
                                               upb_Status* status) {
  void* out = z->vtable->Next(z, count, status);
  UPB_ASSERT((out == NULL) == (*count == 0));
  return out;
}

UPB_INLINE void upb_ZeroCopyOutputStream_BackUp(upb_ZeroCopyOutputStream* z,
                                                size_t count) {
  return z->vtable->BackUp(z, count);
}

UPB_INLINE size_t
upb_ZeroCopyOutputStream_ByteCount(const upb_ZeroCopyOutputStream* z) {
  return z->vtable->ByteCount(z);
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
