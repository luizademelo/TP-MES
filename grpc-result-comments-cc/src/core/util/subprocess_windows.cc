Here's the commented version of the code:

```c++
// Copyright 2016 gRPC authors.

// Platform-specific header for portability
#include <grpc/support/port_platform.h>

// Windows-specific subprocess implementation
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

// Structure representing a subprocess on Windows
struct gpr_subprocess {
  PROCESS_INFORMATION pi;      // Windows process information
  int joined;                  // Flag indicating if process was joined
  int interrupted;              // Flag indicating if process was interrupted
};

// Returns the binary extension for Windows executables
const char* gpr_subprocess_binary_extension() { return ".exe"; }

// Creates a new subprocess with the given command line arguments
// argc: Number of arguments
// argv: Array of argument strings
// Returns: Pointer to new subprocess structure, or NULL on failure
gpr_subprocess* gpr_subprocess_create(int argc, const char** argv) {
  gpr_subprocess* r;

  STARTUPINFO si;              // Startup info for the new process
  PROCESS_INFORMATION pi;      // Process information for the new process

  // Convert arguments to Windows TCHAR format and join them into a single string
  grpc_core::TcharString args = grpc_core::CharToTchar(
      absl::StrJoin(absl::Span<const char*>(argv, argc), " "));

  // Initialize structures
  memset(&si, 0, sizeof(si));
  si.cb = sizeof(si);
  memset(&pi, 0, sizeof(pi));

  // Create the new process
  if (!CreateProcess(NULL, const_cast<LPTSTR>(args.c_str()), NULL, NULL, FALSE,
                     CREATE_NEW_PROCESS_GROUP, NULL, NULL, &si, &pi)) {
    return NULL;
  }

  // Allocate and initialize subprocess structure
  r = (gpr_subprocess*)gpr_malloc(sizeof(gpr_subprocess));
  memset(r, 0, sizeof(*r));
  r->pi = pi;
  return r;
}

// Destroys a subprocess and cleans up resources
// p: Pointer to subprocess structure to destroy
void gpr_subprocess_destroy(gpr_subprocess* p) {
  if (p) {
    // If process wasn't joined, interrupt and join it first
    if (!p->joined) {
      gpr_subprocess_interrupt(p);
      gpr_subprocess_join(p);
    }
    // Close process and thread handles
    if (p->pi.hProcess) {
      CloseHandle(p->pi.hProcess);
    }
    if (p->pi.hThread) {
      CloseHandle(p->pi.hThread);
    }
    // Free the subprocess structure
    gpr_free(p);
  }
}

// Waits for a subprocess to complete and returns its exit code
// p: Pointer to subprocess structure
// Returns: Process exit code, or -1 on error
int gpr_subprocess_join(gpr_subprocess* p) {
  DWORD dwExitCode;
  if (GetExitCodeProcess(p->pi.hProcess, &dwExitCode)) {
    if (dwExitCode == STILL_ACTIVE) {
      // Process is still running, wait for it
      if (WaitForSingleObject(p->pi.hProcess, INFINITE) == WAIT_OBJECT_0) {
        p->joined = 1;
        goto getExitCode;
      }
      return -1;
    } else {
      // Process already finished
      goto getExitCode;
    }
  } else {
    // Failed to get exit code
    return -1;
  }

getExitCode:
  // If process was interrupted, return 0
  if (p->interrupted) {
    return 0;
  }
  // Return actual exit code
  if (GetExitCodeProcess(p->pi.hProcess, &dwExitCode)) {
    return (int)dwExitCode;
  } else {
    return -1;
  }
}

// Interrupts a running subprocess by sending CTRL+BREAK signal
// p: Pointer to subprocess structure
void gpr_subprocess_interrupt(gpr_subprocess* p) {
  DWORD dwExitCode;
  if (GetExitCodeProcess(p->pi.hProcess, &dwExitCode)) {
    if (dwExitCode == STILL_ACTIVE) {
      // Process is still running, send interrupt
      VLOG(2) << "sending ctrl-break";
      GenerateConsoleCtrlEvent(CTRL_BREAK_EVENT, p->pi.dwProcessId);
      p->joined = 1;
      p->interrupted = 1;
    }
  }
  return;
}

// Returns the process ID of a subprocess
// p: Pointer to subprocess structure
// Returns: Process ID
int gpr_subprocess_get_process_id(gpr_subprocess* p) {
  return p->pi.dwProcessId;
}

#endif
```

The comments explain:
1. The purpose of each function and structure
2. Key variables and their roles
3. The flow of control in complex functions
4. Windows-specific operations and their purposes
5. Error handling and edge cases
6. Memory management and resource cleanup

The comments are designed to help future developers understand:
- What the code does at a high level
- How the Windows process API is being used
- The lifecycle management of subprocesses
- The interrupt/join/destroy semantics
- The return value conventions