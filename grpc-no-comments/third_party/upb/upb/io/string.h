
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_IO_STRING_H_
#define UPB_IO_STRING_H_

#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "upb/mem/arena.h"
#include "upb/port/vsnprintf_compat.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

// TODO: Add a small (16 bytes, maybe?) internal buffer so we can avoid

typedef struct {
  size_t size_;
  size_t capacity_;
  char* data_;
  upb_Arena* arena_;
} upb_String;

UPB_INLINE bool upb_String_Init(upb_String* s, upb_Arena* a) {
  static const int kDefaultCapacity = 16;

  s->size_ = 0;
  s->capacity_ = kDefaultCapacity;
  s->data_ = (char*)upb_Arena_Malloc(a, kDefaultCapacity);
  s->arena_ = a;
  if (!s->data_) return false;
  s->data_[0] = '\0';
  return true;
}

UPB_INLINE void upb_String_Clear(upb_String* s) {
  s->size_ = 0;
  s->data_[0] = '\0';
}

UPB_INLINE char* upb_String_Data(const upb_String* s) { return s->data_; }

UPB_INLINE size_t upb_String_Size(const upb_String* s) { return s->size_; }

UPB_INLINE bool upb_String_Empty(const upb_String* s) { return s->size_ == 0; }

UPB_INLINE void upb_String_Erase(upb_String* s, size_t pos, size_t len) {
  if (pos >= s->size_) return;
  char* des = s->data_ + pos;
  if (pos + len > s->size_) len = s->size_ - pos;
  char* src = des + len;
  memmove(des, src, s->size_ - (src - s->data_) + 1);
  s->size_ -= len;
}

UPB_INLINE bool upb_String_Reserve(upb_String* s, size_t size) {
  if (s->capacity_ <= size) {
    const size_t new_cap = size + 1;
    s->data_ =
        (char*)upb_Arena_Realloc(s->arena_, s->data_, s->capacity_, new_cap);
    if (!s->data_) return false;
    s->capacity_ = new_cap;
  }
  return true;
}

UPB_INLINE bool upb_String_Append(upb_String* s, const char* data,
                                  size_t size) {
  if (s->capacity_ <= s->size_ + size) {
    const size_t new_cap = 2 * (s->size_ + size) + 1;
    if (!upb_String_Reserve(s, new_cap)) return false;
  }

  memcpy(s->data_ + s->size_, data, size);
  s->size_ += size;
  s->data_[s->size_] = '\0';
  return true;
}

UPB_PRINTF(2, 0)
UPB_INLINE bool upb_String_AppendFmtV(upb_String* s, const char* fmt,
                                      va_list args) {
  size_t capacity = 1000;
  char* buf = (char*)malloc(capacity);
  bool out = false;
  for (;;) {
    const int n = _upb_vsnprintf(buf, capacity, fmt, args);
    if (n < 0) break;
    if (n < capacity) {
      out = upb_String_Append(s, buf, n);
      break;
    }
    capacity *= 2;
    buf = (char*)realloc(buf, capacity);
  }
  free(buf);
  return out;
}

UPB_PRINTF(2, 3)
UPB_INLINE bool upb_String_AppendFmt(upb_String* s, const char* fmt, ...) {
  va_list args;
  va_start(args, fmt);
  const bool ok = upb_String_AppendFmtV(s, fmt, args);
  va_end(args);
  return ok;
}

UPB_INLINE bool upb_String_Assign(upb_String* s, const char* data,
                                  size_t size) {
  upb_String_Clear(s);
  return upb_String_Append(s, data, size);
}

UPB_INLINE bool upb_String_Copy(upb_String* des, const upb_String* src) {
  return upb_String_Assign(des, src->data_, src->size_);
}

UPB_INLINE bool upb_String_PushBack(upb_String* s, char ch) {
  return upb_String_Append(s, &ch, 1);
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
