
// Copyright 2015 gRPC authors.

#include <grpc/support/port_platform.h>

#ifdef GPR_POSIX_STRING

#include <grpc/support/alloc.h>
#include <grpc/support/string_util.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

int gpr_asprintf(char** strp, const char* format, ...) {
  va_list args;
  int ret;
  char buf[64];
  size_t strp_buflen;

  va_start(args, format);
  ret = vsnprintf(buf, sizeof(buf), format, args);
  va_end(args);
  if (ret < 0) {
    *strp = nullptr;
    return -1;
  }

  strp_buflen = static_cast<size_t>(ret) + 1;
  if ((*strp = static_cast<char*>(gpr_malloc(strp_buflen))) == nullptr) {

    return -1;
  }

  if (strp_buflen <= sizeof(buf)) {
    memcpy(*strp, buf, strp_buflen);
    return ret;
  }

  va_start(args, format);
  ret = vsnprintf(*strp, strp_buflen, format, args);
  va_end(args);
  if (static_cast<size_t>(ret) == strp_buflen - 1) {
    return ret;
  }

  gpr_free(*strp);
  *strp = nullptr;
  return -1;
}

#endif
