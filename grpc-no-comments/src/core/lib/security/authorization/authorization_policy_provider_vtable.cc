// Copyright 2021 gRPC authors.

#include <grpc/grpc.h>
#include <grpc/grpc_security.h>
#include <grpc/support/port_platform.h>

#include "src/core/lib/security/authorization/authorization_policy_provider.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/useful.h"

namespace {

void* ProviderArgCopy(void* p) {
  grpc_authorization_policy_provider* provider =
      static_cast<grpc_authorization_policy_provider*>(p);
  provider->Ref().release();
  return provider;
}

void ProviderArgDestroy(void* p) {
  grpc_authorization_policy_provider* provider =
      static_cast<grpc_authorization_policy_provider*>(p);
  provider->Unref();
}

int ProviderArgCmp(void* p, void* q) { return grpc_core::QsortCompare(p, q); }

}

const grpc_arg_pointer_vtable* grpc_authorization_policy_provider_arg_vtable() {
  static const grpc_arg_pointer_vtable vtable = {
      ProviderArgCopy, ProviderArgDestroy, ProviderArgCmp};
  return &vtable;
}
