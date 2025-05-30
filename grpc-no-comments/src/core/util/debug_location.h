
// Copyright 2017 gRPC authors.

#ifndef GRPC_SRC_CORE_UTIL_DEBUG_LOCATION_H
#define GRPC_SRC_CORE_UTIL_DEBUG_LOCATION_H

#include <grpc/support/port_platform.h>

#include <utility>

#include "absl/strings/str_cat.h"

#if defined(__has_builtin)
#if __has_builtin(__builtin_FILE)
#define GRPC_DEFAULT_FILE __builtin_FILE()
#endif
#endif
#ifndef GRPC_DEFAULT_FILE
#define GRPC_DEFAULT_FILE "<unknown>"
#endif
#if defined(__has_builtin)
#if __has_builtin(__builtin_LINE)
#define GRPC_DEFAULT_LINE __builtin_LINE()
#endif
#endif
#ifndef GRPC_DEFAULT_LINE
#define GRPC_DEFAULT_LINE -1
#endif

namespace grpc_core {

class SourceLocation {
 public:

  SourceLocation(const char* file = GRPC_DEFAULT_FILE,
                 int line = GRPC_DEFAULT_LINE)
      : file_(file), line_(line) {}
  const char* file() const { return file_; }
  int line() const { return line_; }

 private:
  const char* file_;
  int line_;
};

template <typename Sink>
void AbslStringify(Sink& out, const SourceLocation& location) {
  out.Append(absl::StrCat("[", location.file(), ":", location.line(), "]"));
}

#ifndef NDEBUG
class DebugLocation {
 public:
  DebugLocation(const char* file = GRPC_DEFAULT_FILE,
                int line = GRPC_DEFAULT_LINE)
      : location_(file, line) {}
  explicit DebugLocation(SourceLocation location) : location_(location) {}
  const char* file() const { return location_.file(); }
  int line() const { return location_.line(); }

 private:
  SourceLocation location_;
};
#else
class DebugLocation {
 public:
  DebugLocation() {}
  explicit DebugLocation(SourceLocation) {}
  DebugLocation(const char* , int ) {}
  const char* file() const { return nullptr; }
  int line() const { return -1; }
};
#endif

template <typename T>
struct ValueWithDebugLocation {

  ValueWithDebugLocation(T&& value, DebugLocation debug_location = {})
      : value(std::forward<T>(value)), debug_location(debug_location) {}
  T value;
  GPR_NO_UNIQUE_ADDRESS DebugLocation debug_location;
};

#define DEBUG_LOCATION ::grpc_core::DebugLocation(__FILE__, __LINE__)

}

#endif
