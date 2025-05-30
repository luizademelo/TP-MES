
// Copyright 2018 gRPC authors.

#include <grpc/support/port_platform.h>

#include "src/core/tsi/ssl/session_cache/ssl_session.h"

#ifdef OPENSSL_IS_BORINGSSL

#include "absl/memory/memory.h"

namespace tsi {
namespace {

class BoringSslCachedSession : public SslCachedSession {
 public:
  explicit BoringSslCachedSession(SslSessionPtr session)
      : session_(std::move(session)) {}

  SslSessionPtr CopySession() const override {

    SSL_SESSION_up_ref(session_.get());
    return SslSessionPtr(session_.get());
  }

 private:
  SslSessionPtr session_;
};

}

std::unique_ptr<SslCachedSession> SslCachedSession::Create(
    SslSessionPtr session) {
  return std::make_unique<BoringSslCachedSession>(std::move(session));
}

}

#endif
