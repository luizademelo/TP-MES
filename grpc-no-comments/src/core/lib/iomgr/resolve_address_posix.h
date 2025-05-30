
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_IOMGR_RESOLVE_ADDRESS_POSIX_H
#define GRPC_SRC_CORE_LIB_IOMGR_RESOLVE_ADDRESS_POSIX_H

#include <grpc/support/port_platform.h>

#include <functional>
#include <memory>

#include "src/core/lib/iomgr/port.h"
#include "src/core/lib/iomgr/resolve_address.h"
#include "src/core/util/sync.h"

namespace grpc_core {

class NativeDNSResolver : public DNSResolver {
 public:
  NativeDNSResolver() = default;

  TaskHandle LookupHostname(
      std::function<void(absl::StatusOr<std::vector<grpc_resolved_address>>)>
          on_done,
      absl::string_view name, absl::string_view default_port, Duration timeout,
      grpc_pollset_set* interested_parties,
      absl::string_view name_server) override;

  absl::StatusOr<std::vector<grpc_resolved_address>> LookupHostnameBlocking(
      absl::string_view name, absl::string_view default_port) override;

  TaskHandle LookupSRV(
      std::function<void(absl::StatusOr<std::vector<grpc_resolved_address>>)>
          on_resolved,
      absl::string_view name, Duration timeout,
      grpc_pollset_set* interested_parties,
      absl::string_view name_server) override;

  TaskHandle LookupTXT(
      std::function<void(absl::StatusOr<std::string>)> on_resolved,
      absl::string_view name, Duration timeout,
      grpc_pollset_set* interested_parties,
      absl::string_view name_server) override;

  bool Cancel(TaskHandle handle) override;

 private:

  grpc_event_engine::experimental::EventEngine* engine();

  Mutex mu_;
  std::shared_ptr<grpc_event_engine::experimental::EventEngine> engine_
      ABSL_GUARDED_BY(mu_);
  std::atomic<grpc_event_engine::experimental::EventEngine*> engine_ptr_{
      nullptr};
};

}

#endif
