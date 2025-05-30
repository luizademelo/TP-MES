// Copyright 2021 gRPC authors.

#ifndef GRPC_SRC_CORE_TSI_SSL_KEY_LOGGING_SSL_KEY_LOGGING_H
#define GRPC_SRC_CORE_TSI_SSL_KEY_LOGGING_SSL_KEY_LOGGING_H

#include <grpc/grpc_security.h>
#include <grpc/slice.h>
#include <grpc/support/port_platform.h>
#include <grpc/support/sync.h>
#include <openssl/ssl.h>

#include <iostream>
#include <map>

#include "absl/base/thread_annotations.h"
#include "src/core/util/memory.h"
#include "src/core/util/ref_counted.h"
#include "src/core/util/sync.h"

namespace tsi {

class TlsSessionKeyLoggerCache
    : public grpc_core::RefCounted<TlsSessionKeyLoggerCache> {
 public:
  TlsSessionKeyLoggerCache();
  ~TlsSessionKeyLoggerCache() override;

  class TlsSessionKeyLogger
      : public grpc_core::RefCounted<TlsSessionKeyLogger> {
   public:

    TlsSessionKeyLogger(
        std::string tls_session_key_log_file_path,
        grpc_core::RefCountedPtr<TlsSessionKeyLoggerCache> cache);
    ~TlsSessionKeyLogger() override;

    TlsSessionKeyLogger(const TlsSessionKeyLogger&) = delete;
    TlsSessionKeyLogger& operator=(const TlsSessionKeyLogger&) = delete;

    void LogSessionKeys(SSL_CTX* ssl_context,
                        const std::string& session_keys_info);

   private:
    grpc_core::Mutex lock_;
    FILE* fd_ ABSL_GUARDED_BY(lock_);
    std::string tls_session_key_log_file_path_;
    grpc_core::RefCountedPtr<TlsSessionKeyLoggerCache> cache_;
  };

  static grpc_core::RefCountedPtr<TlsSessionKeyLogger> Get(
      std::string tls_session_key_log_file_path);

 private:
  std::map<std::string, TlsSessionKeyLogger*> tls_session_key_logger_map_;
};

}

#endif
