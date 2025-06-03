Here's the commented version of the code:

```c++
// Copyright 2018 gRPC authors.

// Include necessary platform-specific headers and libraries
#include <grpc/support/port_platform.h>

#include <algorithm>
#include <string>
#include <vector>

// Only compile this code for Linux, Android, FreeBSD, and Apple platforms
#if defined(GPR_LINUX) || defined(GPR_ANDROID) || defined(GPR_FREEBSD) || \
    defined(GPR_APPLE)

#include <dirent.h>
#include <fcntl.h>
#include <grpc/support/alloc.h>
#include <stdio.h>
#include <sys/param.h>
#include <sys/stat.h>
#include <unistd.h>

#include "absl/log/log.h"
#include "src/core/config/config_vars.h"
#include "src/core/credentials/transport/tls/load_system_roots.h"
#include "src/core/credentials/transport/tls/load_system_roots_supported.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/util/load_file.h"
#include "src/core/util/useful.h"

namespace grpc_core {
namespace {

// Platform-specific certificate file paths
#if defined(GPR_LINUX) || defined(GPR_ANDROID)
const char* kCertFiles[] = {
    "/etc/ssl/certs/ca-certificates.crt", "/etc/pki/tls/certs/ca-bundle.crt",
    "/etc/ssl/ca-bundle.pem", "/etc/pki/tls/cacert.pem",
    "/etc/pki/ca-trust/extracted/pem/tls-ca-bundle.pem"};
const char* kCertDirectories[] = {
    "/etc/ssl/certs", "/system/etc/security/cacerts", "/usr/local/share/certs",
    "/etc/pki/tls/certs", "/etc/openssl/certs"};
#elif defined(GPR_FREEBSD)
const char* kCertFiles[] = {"/etc/ssl/cert.pem",
                            "/usr/local/share/certs/ca-root-nss.crt"};
const char* kCertDirectories[] = {""};
#elif defined(GPR_APPLE)
const char* kCertFiles[] = {"/etc/ssl/cert.pem"};
const char* kCertDirectories[] = {""};
#endif

// Attempts to load system root certificates from known file locations
// Returns the certificates as a grpc_slice if found, otherwise returns empty
grpc_slice GetSystemRootCerts() {
  size_t num_cert_files_ = GPR_ARRAY_SIZE(kCertFiles);
  for (size_t i = 0; i < num_cert_files_; i++) {
    auto slice = LoadFile(kCertFiles[i], true);
    if (slice.ok()) return slice->TakeCSlice();
  }
  return grpc_empty_slice();
}

}  // namespace

// Constructs an absolute file path from directory and filename components
// valid_file_dir: The directory path
// file_entry_name: The filename
// path_buffer: Output buffer for the constructed path
void GetAbsoluteFilePath(const char* valid_file_dir,
                         const char* file_entry_name, char* path_buffer) {
  if (valid_file_dir != nullptr && file_entry_name != nullptr) {
    int path_len = snprintf(path_buffer, MAXPATHLEN, "%s/%s", valid_file_dir,
                            file_entry_name);
    if (path_len == 0) {
      LOG(ERROR) << "failed to get absolute path for file: " << file_entry_name;
    }
  }
}

// Creates a bundle of root certificates from files in a directory
// certs_directory: Path to directory containing certificate files
// Returns a grpc_slice containing all certificates concatenated together
grpc_slice CreateRootCertsBundle(const char* certs_directory) {
  grpc_slice bundle_slice = grpc_empty_slice();
  if (certs_directory == nullptr) {
    return bundle_slice;
  }
  
  // Open the certificates directory
  DIR* ca_directory = opendir(certs_directory);
  if (ca_directory == nullptr) {
    return bundle_slice;
  }
  
  // Structure to hold file information
  struct FileData {
    char path[MAXPATHLEN];
    off_t size;
  };
  
  std::vector<FileData> roots_filenames;
  size_t total_bundle_size = 0;
  struct dirent* directory_entry;
  
  // Iterate through directory entries
  while ((directory_entry = readdir(ca_directory)) != nullptr) {
    struct stat dir_entry_stat;
    const char* file_entry_name = directory_entry->d_name;
    FileData file_data;
    
    // Get absolute path and file stats
    GetAbsoluteFilePath(certs_directory, file_entry_name, file_data.path);
    int stat_return = stat(file_data.path, &dir_entry_stat);
    
    // Skip if not a regular file or if stat failed
    if (stat_return == -1 || !S_ISREG(dir_entry_stat.st_mode)) {
      if (stat_return == -1) {
        LOG(ERROR) << "failed to get status for file: " << file_data.path;
      }
      continue;
    }
    
    // Add file to list and accumulate total size
    file_data.size = dir_entry_stat.st_size;
    total_bundle_size += file_data.size;
    roots_filenames.push_back(file_data);
  }
  closedir(ca_directory);
  
  // Allocate buffer for all certificates
  char* bundle_string = static_cast<char*>(gpr_zalloc(total_bundle_size + 1));
  size_t bytes_read = 0;
  
  // Read all certificate files into the buffer
  for (size_t i = 0; i < roots_filenames.size(); i++) {
    int file_descriptor = open(roots_filenames[i].path, O_RDONLY);
    if (file_descriptor != -1) {
      size_t cert_file_size = roots_filenames[i].size;
      int read_ret =
          read(file_descriptor, bundle_string + bytes_read, cert_file_size);
      if (read_ret != -1) {
        bytes_read += read_ret;
      } else {
        LOG(ERROR) << "failed to read file: " << roots_filenames[i].path;
      }
    }
  }
  
  // Create a grpc_slice from the buffer
  bundle_slice = grpc_slice_new(bundle_string, bytes_read, gpr_free);
  return bundle_slice;
}

// Main function to load system root certificates
// Tries different methods in order:
// 1. Custom directory from configuration
// 2. Known certificate files
// 3. Known certificate directories
// Returns a grpc_slice containing the certificates or empty slice if none found
grpc_slice LoadSystemRootCerts() {
  grpc_slice result = grpc_empty_slice();

  // First try custom directory from configuration
  auto custom_dir = ConfigVars::Get().SystemSslRootsDir();
  if (!custom_dir.empty()) {
    result = CreateRootCertsBundle(std::string(custom_dir).c_str());
  }

  // If no custom directory or it failed, try known certificate files
  if (GRPC_SLICE_IS_EMPTY(result)) {
    result = GetSystemRootCerts();
  }
  
  // If still not found, try known certificate directories
  if (GRPC_SLICE_IS_EMPTY(result)) {
    for (size_t i = 0; i < GPR_ARRAY_SIZE(kCertDirectories); i++) {
      result = CreateRootCertsBundle(kCertDirectories[i]);
      if (!GRPC_SLICE_IS_EMPTY(result)) {
        break;
      }
    }
  }
  return result;
}

}  // namespace grpc_core

#endif  // Platform check
```