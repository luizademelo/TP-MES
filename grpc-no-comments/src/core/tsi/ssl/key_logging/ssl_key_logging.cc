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

gpr_once g_cache_mutex_init = GPR_ONCE_INIT;
grpc_core::Mutex* g_tls_session_key_log_cache_mu = nullptr;

TlsSessionKeyLoggerCache* g_cache_instance
    ABSL_GUARDED_BY(g_tls_session_key_log_cache_mu) = nullptr;

void do_cache_mutex_init(void) {
  g_tls_session_key_log_cache_mu = new grpc_core::Mutex();
}

}

TlsSessionKeyLoggerCache::TlsSessionKeyLogger::TlsSessionKeyLogger(
    std::string tls_session_key_log_file_path,
    grpc_core::RefCountedPtr<TlsSessionKeyLoggerCache> cache)
    : tls_session_key_log_file_path_(std::move(tls_session_key_log_file_path)),
      cache_(std::move(cache)) {
  CHECK(!tls_session_key_log_file_path_.empty());
  CHECK(cache_ != nullptr);
  fd_ = fopen(tls_session_key_log_file_path_.c_str(), "a");
  if (fd_ == nullptr) {
    grpc_error_handle error = GRPC_OS_ERROR(errno, "fopen");
    LOG(ERROR) << "Ignoring TLS Key logging. ERROR Opening TLS Keylog file: "
               << grpc_core::StatusToString(error);
  }
  cache_->tls_session_key_logger_map_.emplace(tls_session_key_log_file_path_,
                                              this);
};

TlsSessionKeyLoggerCache::TlsSessionKeyLogger::~TlsSessionKeyLogger() {
  {
    grpc_core::MutexLock lock(&lock_);
    if (fd_ != nullptr) fclose(fd_);
  }
  {
    grpc_core::MutexLock lock(g_tls_session_key_log_cache_mu);
    auto it = cache_->tls_session_key_logger_map_.find(
        tls_session_key_log_file_path_);
    if (it != cache_->tls_session_key_logger_map_.end() && it->second == this) {
      cache_->tls_session_key_logger_map_.erase(it);
    }
  }
}

void TlsSessionKeyLoggerCache::TlsSessionKeyLogger::LogSessionKeys(
    SSL_CTX* , const std::string& session_keys_info) {
  grpc_core::MutexLock lock(&lock_);
  if (fd_ == nullptr || session_keys_info.empty()) return;

  bool err =
      fwrite((session_keys_info + "\n").c_str(), sizeof(char),
             session_keys_info.length() + 1, fd_) < session_keys_info.length();

  if (err) {
    grpc_error_handle error = GRPC_OS_ERROR(errno, "fwrite");
    LOG(ERROR) << "Error Appending to TLS session key log file: "
               << grpc_core::StatusToString(error);
    fclose(fd_);
    fd_ = nullptr;
  } else {
    fflush(fd_);
  }
}

TlsSessionKeyLoggerCache::TlsSessionKeyLoggerCache()
    ABSL_EXCLUSIVE_LOCKS_REQUIRED(g_tls_session_key_log_cache_mu) {
  g_cache_instance = this;
}

TlsSessionKeyLoggerCache::~TlsSessionKeyLoggerCache() {
  grpc_core::MutexLock lock(g_tls_session_key_log_cache_mu);
  g_cache_instance = nullptr;
}

grpc_core::RefCountedPtr<TlsSessionKeyLogger> TlsSessionKeyLoggerCache::Get(
    std::string tls_session_key_log_file_path) {
  gpr_once_init(&g_cache_mutex_init, do_cache_mutex_init);
  DCHECK_NE(g_tls_session_key_log_cache_mu, nullptr);
  if (tls_session_key_log_file_path.empty()) {
    return nullptr;
  }
  {
    grpc_core::MutexLock lock(g_tls_session_key_log_cache_mu);
    grpc_core::RefCountedPtr<TlsSessionKeyLoggerCache> cache;
    if (g_cache_instance == nullptr) {

      cache.reset(new TlsSessionKeyLoggerCache());
    } else {
      cache = g_cache_instance->Ref();
    }

    auto it =
        cache->tls_session_key_logger_map_.find(tls_session_key_log_file_path);
    if (it != cache->tls_session_key_logger_map_.end()) {

      auto key_logger = it->second->RefIfNonZero();
      if (key_logger != nullptr) return key_logger;
    }

    return grpc_core::MakeRefCounted<TlsSessionKeyLogger>(
        std::move(tls_session_key_log_file_path), std::move(cache));
  }
}

};
