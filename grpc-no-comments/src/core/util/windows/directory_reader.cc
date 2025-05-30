
// Copyright 2023 gRPC authors.

#include <grpc/support/port_platform.h>

#if defined(GPR_WINDOWS)

#include <sys/stat.h>
#include <windows.h>

#include <string>
#include <vector>

#include "absl/status/statusor.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/string_view.h"
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
  std::string search_path = absl::StrCat(directory_path_, "/*");
  WIN32_FIND_DATAA find_data;
  HANDLE hFind = ::FindFirstFileA(search_path.c_str(), &find_data);
  if (hFind == INVALID_HANDLE_VALUE) {
    return absl::InternalError("Could not read crl directory.");
  }
  do {
    if (!(find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
      callback(find_data.cFileName);
    }
  } while (::FindNextFileA(hFind, &find_data));
  ::FindClose(hFind);
  return absl::OkStatus();
}

}

#endif
