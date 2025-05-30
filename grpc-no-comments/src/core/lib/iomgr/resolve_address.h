
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_IOMGR_RESOLVE_ADDRESS_H
#define GRPC_SRC_CORE_LIB_IOMGR_RESOLVE_ADDRESS_H

#include <grpc/event_engine/event_engine.h>
#include <grpc/support/port_platform.h>
#include <stddef.h>

#include "absl/container/flat_hash_set.h"
#include "absl/status/statusor.h"
#include "src/core/lib/event_engine/handle_containers.h"
#include "src/core/lib/iomgr/pollset_set.h"
#include "src/core/lib/iomgr/port.h"
#include "src/core/lib/iomgr/resolved_address.h"
#include "src/core/util/orphanable.h"
#include "src/core/util/time.h"

#define GRPC_MAX_SOCKADDR_SIZE 128

namespace grpc_core {
extern const char* kDefaultSecurePort;
constexpr int kDefaultSecurePortInt = 443;
constexpr Duration kDefaultDNSRequestTimeout = Duration::Minutes(2);

class DNSResolver {
 public:

  struct LookupTaskHandle {
    intptr_t keys[2];
    static const LookupTaskHandle kInvalid;
    friend bool operator==(const LookupTaskHandle& lhs,
                           const LookupTaskHandle& rhs);
    friend bool operator!=(const LookupTaskHandle& lhs,
                           const LookupTaskHandle& rhs);
  };
  using TaskHandle = LookupTaskHandle;
  using TaskHandleSet = absl::flat_hash_set<
      TaskHandle,
      grpc_event_engine::experimental::TaskHandleComparator<TaskHandle>::Hash>;

  static const TaskHandle kNullHandle;

  virtual ~DNSResolver() {}

  static std::string HandleToString(TaskHandle handle);

  virtual TaskHandle LookupHostname(
      std::function<void(absl::StatusOr<std::vector<grpc_resolved_address>>)>
          on_resolved,
      absl::string_view name, absl::string_view default_port, Duration timeout,
      grpc_pollset_set* interested_parties, absl::string_view name_server) = 0;

  virtual absl::StatusOr<std::vector<grpc_resolved_address>>
  LookupHostnameBlocking(absl::string_view name,
                         absl::string_view default_port) = 0;

  virtual TaskHandle LookupSRV(
      std::function<void(absl::StatusOr<std::vector<grpc_resolved_address>>)>
          on_resolved,
      absl::string_view name, Duration timeout,
      grpc_pollset_set* interested_parties, absl::string_view name_server) = 0;

  virtual TaskHandle LookupTXT(
      std::function<void(absl::StatusOr<std::string>)> on_resolved,
      absl::string_view name, Duration timeout,
      grpc_pollset_set* interested_parties, absl::string_view name_server) = 0;

  virtual bool Cancel(TaskHandle handle) = 0;
};

void ResetDNSResolver(std::shared_ptr<DNSResolver> resolver);

std::shared_ptr<DNSResolver> GetDNSResolver();

}

#endif
