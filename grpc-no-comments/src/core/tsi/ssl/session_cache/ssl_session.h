
// Copyright 2018 gRPC authors.

#ifndef GRPC_SRC_CORE_TSI_SSL_SESSION_CACHE_SSL_SESSION_H
#define GRPC_SRC_CORE_TSI_SSL_SESSION_CACHE_SSL_SESSION_H

#include <grpc/slice.h>
#include <grpc/support/port_platform.h>
#include <openssl/ssl.h>

#include <memory>

#include "src/core/util/ref_counted.h"

namespace tsi {

struct SslSessionDeleter {
  void operator()(SSL_SESSION* session) { SSL_SESSION_free(session); }
};

typedef std::unique_ptr<SSL_SESSION, SslSessionDeleter> SslSessionPtr;

class SslCachedSession {
 public:

  SslCachedSession(const SslCachedSession&) = delete;
  SslCachedSession& operator=(const SslCachedSession&) = delete;

  static std::unique_ptr<SslCachedSession> Create(SslSessionPtr session);

  virtual ~SslCachedSession() = default;

  virtual SslSessionPtr CopySession() const = 0;

 protected:
  SslCachedSession() = default;
};

}

#endif
