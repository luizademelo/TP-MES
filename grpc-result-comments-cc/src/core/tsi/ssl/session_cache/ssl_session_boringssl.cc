Here's the commented version of the code:

```c++
// Copyright 2018 gRPC authors.

// Include platform-specific configuration
#include <grpc/support/port_platform.h>

// Include the SSL session cache interface
#include "src/core/tsi/ssl/session_cache/ssl_session.h"

// Only compile this code if using BoringSSL
#ifdef OPENSSL_IS_BORINGSSL

// Include absl memory utilities for smart pointers
#include "absl/memory/memory.h"

namespace tsi {
namespace {

// Implementation of SslCachedSession for BoringSSL
class BoringSslCachedSession : public SslCachedSession {
 public:
  // Constructor takes ownership of the SSL session
  explicit BoringSslCachedSession(SslSessionPtr session)
      : session_(std::move(session)) {}

  // Creates a new reference to the stored SSL session and returns it
  SslSessionPtr CopySession() const override {
    // Increment the reference count for the SSL session
    SSL_SESSION_up_ref(session_.get());
    // Return a new smart pointer managing the same SSL session
    return SslSessionPtr(session_.get());
  }

 private:
  // The managed SSL session (automatically freed when this object is destroyed)
  SslSessionPtr session_;
};

}  // namespace

// Factory function to create a BoringSSL-specific cached session
std::unique_ptr<SslCachedSession> SslCachedSession::Create(
    SslSessionPtr session) {
  // Create and return a new BoringSslCachedSession instance
  return std::make_unique<BoringSslCachedSession>(std::move(session));
}

}  // namespace tsi

#endif  // OPENSSL_IS_BORINGSSL
```

Key points explained in the comments:
1. The purpose of each include directive
2. The conditional compilation for BoringSSL
3. The class's role as a BoringSSL-specific implementation of SslCachedSession
4. The ownership semantics of the session_ member
5. The reference counting behavior in CopySession()
6. The factory method's purpose
7. Namespace boundaries

The comments aim to make clear:
- Memory management responsibilities
- The class hierarchy and implementation details
- The purpose of each method
- The context in which this code is used (BoringSSL-specific)