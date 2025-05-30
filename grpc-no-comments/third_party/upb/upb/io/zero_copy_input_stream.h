
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_IO_ZERO_COPY_INPUT_STREAM_H_
#define UPB_IO_ZERO_COPY_INPUT_STREAM_H_

#include "upb/base/status.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct upb_ZeroCopyInputStream upb_ZeroCopyInputStream;

typedef struct {

  const void* (*Next)(struct upb_ZeroCopyInputStream* z, size_t* count,
                      upb_Status* status);

  void (*BackUp)(struct upb_ZeroCopyInputStream* z, size_t count);

  bool (*Skip)(struct upb_ZeroCopyInputStream* z, size_t count);

  size_t (*ByteCount)(const struct upb_ZeroCopyInputStream* z);
} _upb_ZeroCopyInputStream_VTable;

struct upb_ZeroCopyInputStream {
  const _upb_ZeroCopyInputStream_VTable* vtable;
};

UPB_INLINE const void* upb_ZeroCopyInputStream_Next(upb_ZeroCopyInputStream* z,
                                                    size_t* count,
                                                    upb_Status* status) {
  const void* out = z->vtable->Next(z, count, status);
  UPB_ASSERT((out == NULL) == (*count == 0));
  return out;
}

UPB_INLINE void upb_ZeroCopyInputStream_BackUp(upb_ZeroCopyInputStream* z,
                                               size_t count) {
  return z->vtable->BackUp(z, count);
}

UPB_INLINE bool upb_ZeroCopyInputStream_Skip(upb_ZeroCopyInputStream* z,
                                             size_t count) {
  return z->vtable->Skip(z, count);
}

UPB_INLINE size_t
upb_ZeroCopyInputStream_ByteCount(const upb_ZeroCopyInputStream* z) {
  return z->vtable->ByteCount(z);
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
