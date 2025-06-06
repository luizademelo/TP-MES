
// Copyright 2015 gRPC authors.

#include <grpc/support/port_platform.h>

#ifdef GPR_POSIX_TMPFILE

#include <errno.h>
#include <grpc/support/alloc.h>
#include <grpc/support/string_util.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "src/core/util/crash.h"
#include "src/core/util/strerror.h"
#include "src/core/util/string.h"
#include "src/core/util/tmpfile.h"

FILE* gpr_tmpfile(const char* prefix, char** tmp_filename) {
  FILE* result = nullptr;
  char* filename_template;
  int fd;

  if (tmp_filename != nullptr) *tmp_filename = nullptr;

  gpr_asprintf(&filename_template, "/tmp/%s_XXXXXX", prefix);
  CHECK_NE(filename_template, nullptr);

  fd = mkstemp(filename_template);
  if (fd == -1) {
    LOG(ERROR) << "mkstemp failed for filename_template " << filename_template
               << " with error " << grpc_core::StrError(errno);
    goto end;
  }
  result = fdopen(fd, "w+");
  if (result == nullptr) {
    LOG(ERROR) << "Could not open file " << filename_template << " from fd "
               << fd << " (error = " << grpc_core::StrError(errno) << ").";
    unlink(filename_template);
    close(fd);
    goto end;
  }

end:
  if (result != nullptr && tmp_filename != nullptr) {
    *tmp_filename = filename_template;
  } else {
    gpr_free(filename_template);
  }
  return result;
}

#endif
