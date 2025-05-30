
// Copyright 2015 gRPC authors.

#include <grpc/support/port_platform.h>

#ifdef GPR_WINDOWS_STRING

#include <grpc/support/alloc.h>
#include <grpc/support/string_util.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include "src/core/util/string.h"

int gpr_asprintf(char** strp, const char* format, ...) {
  va_list args;
  int ret;
  size_t strp_buflen;

  va_start(args, format);
  ret = _vscprintf(format, args);
  va_end(args);
  if (ret < 0) {
    *strp = NULL;
    return -1;
  }

  strp_buflen = (size_t)ret + 1;
  if ((*strp = (char*)gpr_malloc(strp_buflen)) == NULL) {

    return -1;
  }

  va_start(args, format);
  ret = vsnprintf_s(*strp, strp_buflen, _TRUNCATE, format, args);
  va_end(args);
  if ((size_t)ret == strp_buflen - 1) {
    return ret;
  }

  gpr_free(*strp);
  *strp = NULL;
  return -1;
}

#endif
