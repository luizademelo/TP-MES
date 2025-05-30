
// Copyright 2016 gRPC authors.

#include <grpc/support/port_platform.h>

#ifdef GPR_WINDOWS

#include <grpc/support/alloc.h>
#include <grpc/support/log_windows.h>
#include <grpc/support/string_util.h>
#include <inttypes.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <strsafe.h>
#include <wchar.h>

#include "src/core/util/string.h"
#include "src/core/util/tchar.h"

char* gpr_format_message(int messageid) {
  LPTSTR tmessage;
  DWORD status = FormatMessage(
      FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
          FORMAT_MESSAGE_IGNORE_INSERTS,
      NULL, (DWORD)messageid, MAKELANGID(LANG_ENGLISH, SUBLANG_DEFAULT),
      (LPTSTR)(&tmessage), 0, NULL);
  if (status == 0) return gpr_strdup("Unable to retrieve error string");
  auto message = grpc_core::TcharToChar(tmessage);
  LocalFree(tmessage);
  return gpr_strdup(message.c_str());
}

#endif
