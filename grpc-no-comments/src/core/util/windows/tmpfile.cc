
// Copyright 2015 gRPC authors.

#include <grpc/support/port_platform.h>

#ifdef GPR_WINDOWS_TMPFILE

#include <grpc/support/alloc.h>
#include <grpc/support/string_util.h>
#include <io.h>
#include <stdio.h>
#include <string.h>
#include <tchar.h>

#include "src/core/util/crash.h"
#include "src/core/util/tchar.h"
#include "src/core/util/tmpfile.h"

FILE* gpr_tmpfile(const char* prefix, char** tmp_filename_out) {
  FILE* result = NULL;
  TCHAR tmp_path[MAX_PATH];
  TCHAR tmp_filename[MAX_PATH];
  DWORD status;
  UINT success;

  if (tmp_filename_out != NULL) *tmp_filename_out = NULL;

  grpc_core::TcharString template_string = grpc_core::CharToTchar(prefix);

  status = GetTempPath(MAX_PATH, tmp_path);
  if (status == 0 || status > MAX_PATH) goto end;

  success = GetTempFileName(tmp_path, template_string.c_str(), 0, tmp_filename);
  if (!success) goto end;

  if (_tfopen_s(&result, tmp_filename, TEXT("wb+")) != 0) goto end;

end:
  if (result && tmp_filename_out) {
    *tmp_filename_out =
        gpr_strdup(grpc_core::TcharToChar(tmp_filename).c_str());
  }

  return result;
}

#endif
