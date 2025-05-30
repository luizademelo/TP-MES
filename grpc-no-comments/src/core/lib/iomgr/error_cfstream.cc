
// Copyright 2018 gRPC authors.

#include <grpc/support/port_platform.h>

#ifdef GRPC_CFSTREAM
#include <CoreFoundation/CoreFoundation.h>
#include <grpc/support/alloc.h>

#include <string>

#include "absl/strings/str_format.h"
#include "src/core/lib/iomgr/error.h"

#define MAX_ERROR_DESCRIPTION 256

grpc_error_handle grpc_error_create_from_cferror(const char* file, int line,
                                                 void* arg,
                                                 const char* custom_desc) {
  CFErrorRef error = static_cast<CFErrorRef>(arg);
  char buf_domain[MAX_ERROR_DESCRIPTION];
  char buf_desc[MAX_ERROR_DESCRIPTION];
  CFErrorDomain domain = CFErrorGetDomain((error));
  CFIndex code = CFErrorGetCode((error));
  CFStringRef desc = CFErrorCopyDescription((error));
  CFStringGetCString(domain, buf_domain, MAX_ERROR_DESCRIPTION,
                     kCFStringEncodingUTF8);
  CFStringGetCString(desc, buf_desc, MAX_ERROR_DESCRIPTION,
                     kCFStringEncodingUTF8);
  std::string error_msg =
      absl::StrFormat("%s (error domain:%s, code:%ld, description:%s)",
                      custom_desc, buf_domain, code, buf_desc);
  CFRelease(desc);
  return StatusCreate(absl::StatusCode::kUnknown, error_msg,
                      grpc_core::DebugLocation(file, line), {});
}
#endif
