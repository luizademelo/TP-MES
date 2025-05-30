
// Copyright 2018 gRPC authors.

#include <grpc/support/port_platform.h>

#include "absl/log/check.h"
#include "src/core/tsi/ssl/session_cache/ssl_session.h"
#include "src/core/util/crash.h"

#ifndef OPENSSL_IS_BORINGSSL

#include "absl/memory/memory.h"
#include "src/core/lib/slice/slice.h"

namespace tsi {
namespace {

class OpenSslCachedSession : public SslCachedSession {
 public:
  OpenSslCachedSession(SslSessionPtr session) {
    int size = i2d_SSL_SESSION(session.get(), nullptr);
    CHECK_GT(size, 0);
    grpc_slice slice = grpc_slice_malloc(size_t(size));
    unsigned char* start = GRPC_SLICE_START_PTR(slice);
    int second_size = i2d_SSL_SESSION(session.get(), &start);
    CHECK(size == second_size);
    serialized_session_ = slice;
  }

  virtual ~OpenSslCachedSession() {
    grpc_core::CSliceUnref(serialized_session_);
  }

  SslSessionPtr CopySession() const override {
    const unsigned char* data = GRPC_SLICE_START_PTR(serialized_session_);
    size_t length = GRPC_SLICE_LENGTH(serialized_session_);
    SSL_SESSION* session = d2i_SSL_SESSION(nullptr, &data, length);
    if (session == nullptr) {
      return SslSessionPtr();
    }
    return SslSessionPtr(session);
  }

 private:
  grpc_slice serialized_session_;
};

}

std::unique_ptr<SslCachedSession> SslCachedSession::Create(
    SslSessionPtr session) {
  return std::make_unique<OpenSslCachedSession>(std::move(session));
}

}

#endif
