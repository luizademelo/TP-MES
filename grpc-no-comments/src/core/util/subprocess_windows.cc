
// Copyright 2016 gRPC authors.

#include <grpc/support/port_platform.h>

#ifdef GPR_WINDOWS_SUBPROCESS

#include <grpc/support/alloc.h>
#include <string.h>
#include <tchar.h>
#include <windows.h>

#include "absl/log/log.h"
#include "absl/strings/str_join.h"
#include "absl/types/span.h"
#include "src/core/util/crash.h"
#include "src/core/util/string.h"
#include "src/core/util/subprocess.h"
#include "src/core/util/tchar.h"

struct gpr_subprocess {
  PROCESS_INFORMATION pi;
  int joined;
  int interrupted;
};

const char* gpr_subprocess_binary_extension() { return ".exe"; }

gpr_subprocess* gpr_subprocess_create(int argc, const char** argv) {
  gpr_subprocess* r;

  STARTUPINFO si;
  PROCESS_INFORMATION pi;

  grpc_core::TcharString args = grpc_core::CharToTchar(
      absl::StrJoin(absl::Span<const char*>(argv, argc), " "));

  memset(&si, 0, sizeof(si));
  si.cb = sizeof(si);
  memset(&pi, 0, sizeof(pi));

  if (!CreateProcess(NULL, const_cast<LPTSTR>(args.c_str()), NULL, NULL, FALSE,
                     CREATE_NEW_PROCESS_GROUP, NULL, NULL, &si, &pi)) {
    return NULL;
  }

  r = (gpr_subprocess*)gpr_malloc(sizeof(gpr_subprocess));
  memset(r, 0, sizeof(*r));
  r->pi = pi;
  return r;
}

void gpr_subprocess_destroy(gpr_subprocess* p) {
  if (p) {
    if (!p->joined) {
      gpr_subprocess_interrupt(p);
      gpr_subprocess_join(p);
    }
    if (p->pi.hProcess) {
      CloseHandle(p->pi.hProcess);
    }
    if (p->pi.hThread) {
      CloseHandle(p->pi.hThread);
    }
    gpr_free(p);
  }
}

int gpr_subprocess_join(gpr_subprocess* p) {
  DWORD dwExitCode;
  if (GetExitCodeProcess(p->pi.hProcess, &dwExitCode)) {
    if (dwExitCode == STILL_ACTIVE) {
      if (WaitForSingleObject(p->pi.hProcess, INFINITE) == WAIT_OBJECT_0) {
        p->joined = 1;
        goto getExitCode;
      }
      return -1;
    } else {
      goto getExitCode;
    }
  } else {
    return -1;
  }

getExitCode:
  if (p->interrupted) {
    return 0;
  }
  if (GetExitCodeProcess(p->pi.hProcess, &dwExitCode)) {
    return (int)dwExitCode;
  } else {
    return -1;
  }
}

void gpr_subprocess_interrupt(gpr_subprocess* p) {
  DWORD dwExitCode;
  if (GetExitCodeProcess(p->pi.hProcess, &dwExitCode)) {
    if (dwExitCode == STILL_ACTIVE) {
      VLOG(2) << "sending ctrl-break";
      GenerateConsoleCtrlEvent(CTRL_BREAK_EVENT, p->pi.dwProcessId);
      p->joined = 1;
      p->interrupted = 1;
    }
  }
  return;
}

int gpr_subprocess_get_process_id(gpr_subprocess* p) {
  return p->pi.dwProcessId;
}

#endif
