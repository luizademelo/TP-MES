
// Copyright 2015 gRPC authors.

#include <grpc/support/port_platform.h>

#ifdef GPR_MSYS_TMPFILE

#include <grpc/support/alloc.h>
#include <grpc/support/string_util.h>
#include <io.h>
#include <stdio.h>
#include <string.h>
#include <tchar.h>

#include "src/core/util/crash.h"
#include "src/core/util/string_windows.h"
#include "src/core/util/tmpfile.h"

FILE* gpr_tmpfile(const char* prefix, char** tmp_filename_out) {
  FILE* result = NULL;
  char tmp_filename[MAX_PATH];
  UINT success;

  if (tmp_filename_out != NULL) *tmp_filename_out = NULL;

  success = GetTempFileNameA(".", prefix, 0, tmp_filename);
  fprintf(stderr, "success = %d\n", success);

  if (success) {

    result = fopen(tmp_filename, "wb+");
    fprintf(stderr, "result = %p\n", result);
  }
  if (result != NULL && tmp_filename_out) {
    *tmp_filename_out = gpr_strdup(tmp_filename);
  }

  return result;
}

#endif
