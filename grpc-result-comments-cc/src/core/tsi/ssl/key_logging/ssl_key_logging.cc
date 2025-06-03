Here's the commented version of the code:

```c++
// Copyright 2021 gRPC authors.

#include "src/core/tsi/ssl/key_logging/ssl_key_logging.h"

#include <grpc/support/port_platform.h>

#include <map>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/lib/slice/slice_internal.h"
#include "src/core/util/crash.h"
#include "src/core/util/sync.h"

using TlsSessionKeyLogger = tsi::TlsSessionKeyLoggerCache::TlsSessionKeyLogger;

namespace tsi {

namespace {

// Global initialization control for the cache mutex
gpr_once g_cache_mutex_init = GPR_ONCE_INIT;
// Mutex protecting access to the global cache instance
grpc_core::Mutex* g_tls_session_key_log_cache_mu = nullptr;

// Global instance of the TLS session key logger cache
TlsSessionKeyLoggerCache* g_cache_instance
    ABSL_GUARDED_BY(g_tls_session_key_log_cache_mu) = nullptr;

// Initializes the global cache mutex (called once via gpr_once_init)
void do_cache_mutex_init(void) {
  g_tls_session_key_log_cache_mu = new grpc_core::Mutex();
}

}  // namespace

// Constructor for TlsSessionKeyLogger
// Creates a logger that writes to the specified file path and registers itself with the cache
TlsSessionKeyLoggerCache::TlsSessionKeyLogger::TlsSessionKeyLogger(
    std::string tls_session_key_log_file_path,
    grpc_core::RefCountedPtr<TlsSessionKeyLoggerCache> cache)
    : tls_session_key_log_file_path_(std::move(tls_session_key_log_file_path)),
      cache_(std::move(cache)) {
  // Ensure valid file path and cache are provided
  CHECK(!tls_session_key_log_file_path_.empty());
  CHECK(cache_ != nullptr);
  
  // Open the key log file in append mode
  fd_ = fopen(tls_session_key_log_file_path_.c_str(), "a");
  if (fd_ == nullptr) {
    // Log error if file opening fails
    grpc_error_handle error = GRPC_OS_ERROR(errno, "fopen");
    LOG(ERROR) << "Ignoring TLS Key logging. ERROR Opening TLS Keylog file: "
               << grpc_core::StatusToString(error);
  }
  // Register this logger in the cache's map
  cache_->tls_session_key_logger_map_.emplace(tls_session_key_log_file_path_,
                                              this);
};

// Destructor for TlsSessionKeyLogger
// Closes the file and removes itself from the cache
TlsSessionKeyLoggerCache::TlsSessionKeyLogger::~TlsSessionKeyLogger() {
  {
    // Lock to safely close the file
    grpc_core::MutexLock lock(&lock_);
    if (fd_ != nullptr) fclose(fd_);
  }
  {
    // Lock cache to safely remove this logger from the map
    grpc_core::MutexLock lock(g_tls_session_key_log_cache_mu);
    auto it = cache_->tls_session_key_logger_map_.find(
        tls_session_key_log_file_path_);
    if (it != cache_->tls_session_key_logger_map_.end() && it->second == this) {
      cache_->tls_session_key_logger_map_.erase(it);
    }
  }
}

// Logs TLS session keys to the file
void TlsSessionKeyLoggerCache::TlsSessionKeyLogger::LogSessionKeys(
    SSL_CTX* , const std::string& session_keys_info) {
  grpc_core::MutexLock lock(&lock_);
  // Skip if file isn't open or empty session key info
  if (fd_ == nullptr || session_keys_info.empty()) return;

  // Write session key info to file (with newline)
  bool err =
      fwrite((session_keys_info + "\n").c_str(), sizeof(char),
             session_keys_info.length() + 1, fd_) < session_keys_info.length();

  if (err) {
    // Handle write errors by closing the file
    grpc_error_handle error = GRPC_OS_ERROR(errno, "fwrite");
    LOG(ERROR) << "Error Appending to TLS session key log file: "
               << grpc_core::StatusToString(error);
    fclose(fd_);
    fd_ = nullptr;
  } else {
    // Ensure data is flushed to disk
    fflush(fd_);
  }
}

// Constructor for the cache - registers itself as the global instance
TlsSessionKeyLoggerCache::TlsSessionKeyLoggerCache()
    ABSL_EXCLUSIVE_LOCKS_REQUIRED(g_tls_session_key_log_cache_mu) {
  g_cache_instance = this;
}

// Destructor for the cache - clears the global instance
TlsSessionKeyLoggerCache::~TlsSessionKeyLoggerCache() {
  grpc_core::MutexLock lock(g_tls_session_key_log_cache_mu);
  g_cache_instance = nullptr;
}

// Gets or creates a logger for the specified file path
grpc_core::RefCountedPtr<TlsSessionKeyLogger> TlsSessionKeyLoggerCache::Get(
    std::string tls_session_key_log_file_path) {
  // Ensure mutex is initialized
  gpr_once_init(&g_cache_mutex_init, do_cache_mutex_init);
  DCHECK_NE(g_tls_session_key_log_cache_mu, nullptr);
  
  // Return nullptr for empty paths
  if (tls_session_key_log_file_path.empty()) {
    return nullptr;
  }
  
  {
    grpc_core::MutexLock lock(g_tls_session_key_log_cache_mu);
    grpc_core::RefCountedPtr<TlsSessionKeyLoggerCache> cache;
    
    // Create new cache if none exists, otherwise use existing
    if (g_cache_instance == nullptr) {
      cache.reset(new TlsSessionKeyLoggerCache());
    } else {
      cache = g_cache_instance->Ref();
    }

    // Check if logger already exists for this path
    auto it =
        cache->tls_session_key_logger_map_.find(tls_session_key_log_file_path);
    if (it != cache->tls_session_key_logger_map_.end()) {
      // Return existing logger if it hasn't been destroyed
      auto key_logger = it->second->RefIfNonZero();
      if (key_logger != nullptr) return key_logger;
    }

    // Create and return new logger for this path
    return grpc_core::MakeRefCounted<TlsSessionKeyLogger>(
        std::move(tls_session_key_log_file_path), std::move(cache));
  }
}

};  // namespace tsi
```

Key aspects documented in the comments:
1. Purpose of each class and method
2. Thread-safety considerations (mutex usage)
3. Error handling and edge cases
4. Memory management and ownership
5. Important preconditions and postconditions
6. File I/O operations and their potential failures
7. Cache management logic
8. Reference counting behavior

The comments aim to provide future maintainers with clear understanding of:
- Why certain design decisions were made
- What invariants are maintained
- How thread safety is achieved
- The lifecycle of objects
- Error handling strategies