
// Copyright 2023 gRPC authors.

#include <grpc/support/port_platform.h>

#include <memory>

#include "absl/functional/function_ref.h"
#include "absl/status/status.h"
#include "absl/strings/string_view.h"

#if defined(GPR_LINUX) || defined(GPR_ANDROID) || defined(GPR_FREEBSD) || \
    defined(GPR_APPLE) || defined(GPR_NETBSD)

#include <dirent.h>

#include <string>

#include "src/core/util/directory_reader.h"

namespace grpc_core {

namespace {
const char kSkipEntriesSelf[] = ".";
const char kSkipEntriesParent[] = "..";
}

class DirectoryReaderImpl : public DirectoryReader {
 public:
  explicit DirectoryReaderImpl(absl::string_view directory_path)
      : directory_path_(directory_path) {}
  absl::string_view Name() const override { return directory_path_; }
  absl::Status ForEach(absl::FunctionRef<void(absl::string_view)>) override;

 private:
  const std::string directory_path_;
};

std::unique_ptr<DirectoryReader> MakeDirectoryReader(
    absl::string_view filename) {
  return std::make_unique<DirectoryReaderImpl>(filename);
}

absl::Status DirectoryReaderImpl::ForEach(
    absl::FunctionRef<void(absl::string_view)> callback) {

  DIR* directory = opendir(directory_path_.c_str());
  if (directory == nullptr) {
    return absl::InternalError("Could not read crl directory.");
  }
  struct dirent* directory_entry;

  while ((directory_entry = readdir(directory)) != nullptr) {
    const absl::string_view file_name = directory_entry->d_name;

    if (file_name == kSkipEntriesParent || file_name == kSkipEntriesSelf) {
      continue;
    }

    callback(file_name);
  }
  closedir(directory);
  return absl::OkStatus();
}
}

#endif
