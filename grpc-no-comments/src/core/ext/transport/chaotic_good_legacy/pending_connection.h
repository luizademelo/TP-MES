// Copyright 2024 gRPC authors.

#ifndef GRPC_SRC_CORE_EXT_TRANSPORT_CHAOTIC_GOOD_LEGACY_PENDING_CONNECTION_H
#define GRPC_SRC_CORE_EXT_TRANSPORT_CHAOTIC_GOOD_LEGACY_PENDING_CONNECTION_H

#include <string>

#include "absl/status/statusor.h"
#include "src/core/lib/promise/promise.h"
#include "src/core/lib/transport/promise_endpoint.h"
#include "src/core/util/dual_ref_counted.h"

namespace grpc_core {
namespace chaotic_good_legacy {

class PendingConnection {
 public:
  explicit PendingConnection(absl::string_view id,
                             Promise<absl::StatusOr<PromiseEndpoint>> connector)
      : id_(id), connector_(std::move(connector)) {}

  PendingConnection(const PendingConnection&) = delete;
  PendingConnection& operator=(const PendingConnection&) = delete;
  PendingConnection(PendingConnection&&) = default;
  PendingConnection& operator=(PendingConnection&&) = default;

  absl::string_view id() const { return id_; }
  auto Await() { return std::move(connector_); }

 private:
  std::string id_;
  Promise<absl::StatusOr<PromiseEndpoint>> connector_;
};

class ServerConnectionFactory : public DualRefCounted<ServerConnectionFactory> {
 public:
  using DualRefCounted::DualRefCounted;
  virtual PendingConnection RequestDataConnection() = 0;
};

class ClientConnectionFactory : public DualRefCounted<ClientConnectionFactory> {
 public:
  using DualRefCounted::DualRefCounted;
  virtual PendingConnection Connect(absl::string_view id) = 0;
};

inline PendingConnection ImmediateConnection(absl::string_view id,
                                             PromiseEndpoint endpoint) {
  return PendingConnection(
      id,
      [endpoint = std::move(endpoint)]() mutable
          -> absl::StatusOr<PromiseEndpoint> { return std::move(endpoint); });
}

}
}

#endif
