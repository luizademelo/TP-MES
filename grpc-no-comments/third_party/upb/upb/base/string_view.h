
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_BASE_STRING_VIEW_H_
#define UPB_BASE_STRING_VIEW_H_

#include <string.h>

#include "upb/port/def.inc"

#define UPB_STRINGVIEW_INIT(ptr, len) \
  { ptr, len }

#define UPB_STRINGVIEW_FORMAT "%.*s"
#define UPB_STRINGVIEW_ARGS(view) (int)(view).size, (view).data

typedef struct {
  const char* data;
  size_t size;
} upb_StringView;

#ifdef __cplusplus
extern "C" {
#endif

UPB_API_INLINE upb_StringView upb_StringView_FromDataAndSize(const char* data,
                                                             size_t size) {
  upb_StringView ret;
  ret.data = data;
  ret.size = size;
  return ret;
}

UPB_INLINE upb_StringView upb_StringView_FromString(const char* data) {
  return upb_StringView_FromDataAndSize(data, strlen(data));
}

UPB_INLINE bool upb_StringView_IsEqual(upb_StringView a, upb_StringView b) {
  return (a.size == b.size) && (!a.size || !memcmp(a.data, b.data, a.size));
}

UPB_INLINE int upb_StringView_Compare(upb_StringView a, upb_StringView b) {
  int result = memcmp(a.data, b.data, UPB_MIN(a.size, b.size));
  if (result == 0) {
    return a.size - b.size;
  }
  return result;
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
