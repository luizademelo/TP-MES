
// Copyright 2023 gRPC authors.

#ifndef GRPC_SRC_CORE_UTIL_DIRECTORY_READER_H
#define GRPC_SRC_CORE_UTIL_DIRECTORY_READER_H

#include <grpc/support/port_platform.h>

#include <memory>

#include "absl/functional/function_ref.h"
#include "absl/status/status.h"
#include "absl/strings/string_view.h"

namespace grpc_core {

class DirectoryReader {
 public:
  virtual ~DirectoryReader() = default;

  virtual absl::string_view Name() const = 0;

  virtual absl::Status ForEach(
      absl::FunctionRef<void(absl::string_view)> callback) = 0;
};

std::unique_ptr<DirectoryReader> MakeDirectoryReader(
    absl::string_view filename);

}

#endif