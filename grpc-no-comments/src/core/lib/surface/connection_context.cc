
// Copyright 2024 gRPC authors.

#include "src/core/lib/surface/connection_context.h"

#include <grpc/support/alloc.h>
#include <grpc/support/port_platform.h>

#include <cstddef>

#include "src/core/util/alloc.h"
#include "src/core/util/orphanable.h"

namespace grpc_core {

namespace {

void* ConnectionContextStorage() {
  size_t base_size = sizeof(ConnectionContext) +
                     GPR_ROUND_UP_TO_ALIGNMENT_SIZE(
                         connection_context_detail::
                             BaseConnectionContextPropertiesTraits::Size());
  static constexpr size_t alignment =
      (GPR_CACHELINE_SIZE > GPR_MAX_ALIGNMENT &&
       GPR_CACHELINE_SIZE % GPR_MAX_ALIGNMENT == 0)
          ? GPR_CACHELINE_SIZE
          : GPR_MAX_ALIGNMENT;
  return gpr_malloc_aligned(base_size, alignment);
}

}

OrphanablePtr<ConnectionContext> ConnectionContext::Create() {
  void* p = ConnectionContextStorage();
  return OrphanablePtr<ConnectionContext>(new (p) ConnectionContext());
}

ConnectionContext::ConnectionContext() {
  for (size_t i = 0;
       i < connection_context_detail::BaseConnectionContextPropertiesTraits::
               NumProperties();
       ++i) {
    registered_properties()[i] = nullptr;
  }
}

void ConnectionContext::Orphan() {
  this->~ConnectionContext();
  gpr_free_aligned(const_cast<ConnectionContext*>(this));
}

ConnectionContext::~ConnectionContext() {
  for (size_t i = 0;
       i < connection_context_detail::BaseConnectionContextPropertiesTraits::
               NumProperties();
       ++i) {
    connection_context_detail::BaseConnectionContextPropertiesTraits::Destroy(
        i, registered_properties()[i]);
  }
}

}
