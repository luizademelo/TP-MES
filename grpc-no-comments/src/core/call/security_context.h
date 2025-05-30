
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_CALL_SECURITY_CONTEXT_H
#define GRPC_SRC_CORE_CALL_SECURITY_CONTEXT_H

#include <grpc/credentials.h>
#include <grpc/grpc.h>
#include <grpc/grpc_security.h>
#include <grpc/support/alloc.h>
#include <grpc/support/port_platform.h>
#include <stddef.h>

#include <memory>
#include <utility>

#include "absl/strings/string_view.h"
#include "src/core/credentials/call/call_credentials.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/lib/resource_quota/arena.h"
#include "src/core/lib/surface/connection_context.h"
#include "src/core/transport/auth_context.h"
#include "src/core/util/debug_location.h"
#include "src/core/util/orphanable.h"
#include "src/core/util/ref_counted.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/useful.h"

struct grpc_security_context_extension {
  void* instance = nullptr;
  void (*destroy)(void*) = nullptr;
};

namespace grpc_core {

class SecurityContext {
 public:
  virtual ~SecurityContext() = default;
};

}

struct grpc_client_security_context final : public grpc_core::SecurityContext {
  explicit grpc_client_security_context(
      grpc_core::RefCountedPtr<grpc_call_credentials> creds)
      : creds(std::move(creds)) {}
  ~grpc_client_security_context() override;

  grpc_core::RefCountedPtr<grpc_call_credentials> creds;
  grpc_core::RefCountedPtr<grpc_auth_context> auth_context;
  grpc_security_context_extension extension;
};

grpc_client_security_context* grpc_client_security_context_create(
    grpc_core::Arena* arena, grpc_call_credentials* creds);
void grpc_client_security_context_destroy(void* ctx);

struct grpc_server_security_context final : public grpc_core::SecurityContext {
  grpc_server_security_context() = default;
  ~grpc_server_security_context() override;

  grpc_core::RefCountedPtr<grpc_auth_context> auth_context;
  grpc_security_context_extension extension;
};

grpc_server_security_context* grpc_server_security_context_create(
    grpc_core::Arena* arena);
void grpc_server_security_context_destroy(void* ctx);

namespace grpc_core {
template <>
struct ArenaContextType<SecurityContext> {
  static void Destroy(SecurityContext* p) { p->~SecurityContext(); }
};

template <>
struct ContextSubclass<grpc_client_security_context> {
  using Base = SecurityContext;
};
template <>
struct ContextSubclass<grpc_server_security_context> {
  using Base = SecurityContext;
};
}

#endif
