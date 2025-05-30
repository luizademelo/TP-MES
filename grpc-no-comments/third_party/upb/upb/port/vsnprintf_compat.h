
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_PORT_VSNPRINTF_COMPAT_H_
#define UPB_PORT_VSNPRINTF_COMPAT_H_

#include "upb/port/def.inc"

UPB_INLINE int _upb_vsnprintf(char* buf, size_t size, const char* fmt,
                              va_list ap) {
#if defined(__MINGW64__) || defined(__MINGW32__) || defined(_MSC_VER)

  int n = -1;
  if (size != 0) n = _vsnprintf_s(buf, size, _TRUNCATE, fmt, ap);
  if (n == -1) n = _vscprintf(fmt, ap);
  return n;
#else
  return vsnprintf(buf, size, fmt, ap);
#endif
}

#include "upb/port/undef.inc"

#endif
