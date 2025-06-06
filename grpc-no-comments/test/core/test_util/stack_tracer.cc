
// Copyright 2020 the gRPC authors.

#include "test/core/test_util/stack_tracer.h"

#include <grpc/support/port_platform.h>

#include <cstdio>
#include <string>

#include "absl/debugging/stacktrace.h"
#include "absl/debugging/symbolize.h"
#include "src/core/util/examine_stack.h"

namespace {

constexpr int kPrintfPointerFieldWidth = 2 + (2 * sizeof(void*));

void DumpPCAndFrameSizeAndSymbol(void (*writerfn)(const char*, void*),
                                 void* writerfn_arg, void* pc,
                                 void* symbolize_pc, int framesize,
                                 const char* const prefix) {
  char tmp[1024];
  const char* symbol = "(unknown)";
  if (absl::Symbolize(symbolize_pc, tmp, sizeof(tmp))) {
    symbol = tmp;
  }
  char buf[1024];
  if (framesize <= 0) {
    snprintf(buf, sizeof(buf), "%s@ %*p  (unknown)  %s\n", prefix,
             kPrintfPointerFieldWidth, pc, symbol);
  } else {
    snprintf(buf, sizeof(buf), "%s@ %*p  %9d  %s\n", prefix,
             kPrintfPointerFieldWidth, pc, framesize, symbol);
  }
  writerfn(buf, writerfn_arg);
}

void DumpPCAndFrameSize(void (*writerfn)(const char*, void*),
                        void* writerfn_arg, void* pc, int framesize,
                        const char* const prefix) {
  char buf[100];
  if (framesize <= 0) {
    snprintf(buf, sizeof(buf), "%s@ %*p  (unknown)\n", prefix,
             kPrintfPointerFieldWidth, pc);
  } else {
    snprintf(buf, sizeof(buf), "%s@ %*p  %9d\n", prefix,
             kPrintfPointerFieldWidth, pc, framesize);
  }
  writerfn(buf, writerfn_arg);
}

void DumpStackTrace(void* const stack[], int frame_sizes[], int depth,
                    bool symbolize_stacktrace,
                    void (*writerfn)(const char*, void*), void* writerfn_arg) {
  for (int i = 0; i < depth; i++) {
    if (symbolize_stacktrace) {
      DumpPCAndFrameSizeAndSymbol(writerfn, writerfn_arg, stack[i],
                                  reinterpret_cast<char*>(stack[i]) - 1,
                                  frame_sizes[i], "    ");
    } else {
      DumpPCAndFrameSize(writerfn, writerfn_arg, stack[i], frame_sizes[i],
                         "    ");
    }
  }
}

void DebugWriteToString(const char* data, void* str) {
  reinterpret_cast<std::string*>(str)->append(data);
}

}

namespace grpc_core {
namespace testing {

std::string GetCurrentStackTrace() {
  std::string result = "Stack trace:\n";
  constexpr int kNumStackFrames = 32;
  void* stack[kNumStackFrames];
  int frame_sizes[kNumStackFrames];
  int depth = absl::GetStackFrames(stack, frame_sizes, kNumStackFrames, 1);
  DumpStackTrace(stack, frame_sizes, depth, true, DebugWriteToString, &result);
  return result;
}

void InitializeStackTracer(const char* argv0) {
  absl::InitializeSymbolizer(argv0);
  SetCurrentStackTraceProvider(&GetCurrentStackTrace);
}

}
}
