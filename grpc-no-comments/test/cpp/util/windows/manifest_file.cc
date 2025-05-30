// Copyright 2023 The gRPC Authors.

#include "test/cpp/util/windows/manifest_file.h"

#include <grpc/support/port_platform.h>

#ifdef GPR_WINDOWS

#include <Windows.h>

#include <fstream>
#include <string>
#include <vector>

#include "absl/log/check.h"
#include "absl/strings/str_format.h"
#include "absl/strings/str_replace.h"
#include "absl/strings/str_split.h"
#include "src/core/util/crash.h"

namespace grpc {
namespace testing {

std::string NormalizeFilePath(const std::string& filepath) {
  return absl::StrReplaceAll(filepath, {{"/", "\\"}});
}

ManifestFile::ManifestFile(const std::string& filepath)
    : filestream_(filepath, std::ios::in | std::ios::binary) {
  if (!filestream_.is_open()) {
    grpc_core::Crash(absl::StrFormat("Failed to open: %s, error code: %d",
                                     filepath, GetLastError()));
  }
}

std::string ManifestFile::Get(const std::string& key) {
  auto iter = cache_.find(key);
  if (iter != cache_.end()) {
    return iter->second;
  }
  do {
    std::string line;
    std::getline(filestream_, line);
    if (!line.empty()) {
      std::vector<std::string> kv = absl::StrSplit(line, " ");
      CHECK_EQ(kv.size(), 2u);
      cache_.emplace(kv[0], kv[1]);
      if (kv[0] == key) {
        return kv[1];
      }
    }
  } while (!filestream_.eof() && !filestream_.fail());
  grpc_core::Crash(
      absl::StrFormat("Failed to find key: %s in MANIFEST file", key));
}

}  // namespace testing
}  // namespace grpc

#endif  // GPR_WINDOWS
