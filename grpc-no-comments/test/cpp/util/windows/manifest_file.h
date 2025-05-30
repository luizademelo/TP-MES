// Copyright 2023 The gRPC Authors.

#ifndef GRPC_TEST_CPP_UTIL_WINDOWS_MANIFEST_FILE_H
#define GRPC_TEST_CPP_UTIL_WINDOWS_MANIFEST_FILE_H

#include <grpc/support/port_platform.h>

#ifdef GPR_WINDOWS

#include <fstream>
#include <string>
#include <unordered_map>

namespace grpc {
namespace testing {

std::string NormalizeFilePath(const std::string& filepath);

class ManifestFile {
 public:
  explicit ManifestFile(const std::string& filepath);

  std::string Get(const std::string& key);

 private:
  std::fstream filestream_;
  std::unordered_map<std::string, std::string> cache_;
};

}
}

#endif

#endif
