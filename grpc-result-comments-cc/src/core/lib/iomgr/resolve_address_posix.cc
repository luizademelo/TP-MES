Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

// Include platform-specific portability headers
#include <grpc/support/port_platform.h>

// Include core I/O manager port definitions
#include "src/core/lib/iomgr/port.h"

// Only compile this file if using POSIX sockets for address resolution
#ifdef GRPC_POSIX_SOCKET_RESOLVE_ADDRESS

// Standard includes for event engine, memory management, strings, and system types
#include <grpc/event_engine/event_engine.h>
#include <grpc/support/alloc.h>
#include <grpc/support/string_util.h>
#include <grpc/support/time.h>
#include <string.h>
#include <sys/types.h>

// C++ standard library includes
#include <atomic>
#include <functional>
#include <memory>
#include <string>
#include <utility>
#include <vector>

// Abseil status and string utilities
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/string_view.h"

// Core gRPC I/O manager and utility headers
#include "src/core/lib/iomgr/block_annotate.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/lib/iomgr/resolve_address.h"
#include "src/core/lib/iomgr/resolve_address_posix.h"
#include "src/core/lib/iomgr/resolved_address.h"
#include "src/core/lib/transport/error_utils.h"
#include "src/core/util/host_port.h"
#include "src/core/util/time.h"
#include "src/core/util/useful.h"

namespace grpc_core {

// Returns the event engine instance, initializing it if necessary
grpc_event_engine::experimental::EventEngine* NativeDNSResolver::engine() {
  // First try relaxed atomic load
  auto engine_ptr = engine_ptr_.load(std::memory_order_relaxed);
  if (engine_ptr != nullptr) return engine_ptr;

  // If not initialized, acquire lock and initialize
  MutexLock lock(&mu_);
  if (engine_ != nullptr) return engine_.get();
  engine_ = grpc_event_engine::experimental::GetDefaultEventEngine();
  engine_ptr_.store(engine_.get(), std::memory_order_relaxed);
  return engine_.get();
}

// Asynchronously looks up a hostname and returns resolved addresses
DNSResolver::TaskHandle NativeDNSResolver::LookupHostname(
    std::function<void(absl::StatusOr<std::vector<grpc_resolved_address>>)>
        on_done,
    absl::string_view name, absl::string_view default_port,
    Duration /* timeout */, grpc_pollset_set* /* interested_parties */,
    absl::string_view /* name_server */) {
  // Schedule the lookup on the event engine
  engine()->Run([on_done = std::move(on_done), name = std::string(name),
                 default_port = std::string(default_port)]() {
    // Create execution context for the operation
    ExecCtx exec_ctx;
    // Perform blocking hostname lookup
    auto result = GetDNSResolver()->LookupHostnameBlocking(name, default_port);
    // Invoke callback with results
    on_done(std::move(result));
  });
  return kNullHandle; // Return null handle as this implementation doesn't support cancellation
}

// Synchronously looks up a hostname and returns resolved addresses
absl::StatusOr<std::vector<grpc_resolved_address>>
NativeDNSResolver::LookupHostnameBlocking(absl::string_view name,
                                          absl::string_view default_port) {
  ExecCtx exec_ctx;
  struct addrinfo hints;
  struct addrinfo *result = nullptr, *resp;
  int s;
  size_t i;
  grpc_error_handle err;
  std::vector<grpc_resolved_address> addresses;
  std::string host;
  std::string port;

  // Split input into host and port components
  SplitHostPort(name, &host, &port);
  if (host.empty()) {
    err =
        GRPC_ERROR_CREATE(absl::StrCat("unparsable host:port \"", name, "\""));
    goto done;
  }
  if (port.empty()) {
    if (default_port.empty()) {
      err = GRPC_ERROR_CREATE(absl::StrCat("no port in name \"", name, "\""));
      goto done;
    }
    port = std::string(default_port);
  }

  // Initialize hints for getaddrinfo
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;     // Accept IPv4 or IPv6
  hints.ai_socktype = SOCK_STREAM; // Stream socket type
  hints.ai_flags = AI_PASSIVE;     // For wildcard IP address

  // Perform blocking DNS resolution
  GRPC_SCHEDULING_START_BLOCKING_REGION;
  s = getaddrinfo(host.c_str(), port.c_str(), &hints, &result);
  GRPC_SCHEDULING_END_BLOCKING_REGION;

  // If resolution failed, try common service ports
  if (s != 0) {
    const char* svc[][2] = {{"http", "80"}, {"https", "443"}};
    for (i = 0; i < GPR_ARRAY_SIZE(svc); i++) {
      if (port == svc[i][0]) {
        GRPC_SCHEDULING_START_BLOCKING_REGION;
        s = getaddrinfo(host.c_str(), svc[i][1], &hints, &result);
        GRPC_SCHEDULING_END_BLOCKING_REGION;
        break;
      }
    }
  }

  // Handle resolution errors
  if (s != 0) {
    err = absl::UnknownError(absl::StrCat(
        "getaddrinfo(\"", name, "\"): ", gai_strerror(s), " (", s, ")"));
    goto done;
  }

  // Convert addrinfo results to grpc_resolved_address format
  for (resp = result; resp != nullptr; resp = resp->ai_next) {
    grpc_resolved_address addr;
    memcpy(&addr.addr, resp->ai_addr, resp->ai_addrlen);
    addr.len = resp->ai_addrlen;
    addresses.push_back(addr);
  }
  err = absl::OkStatus();

done:
  // Clean up and return results
  if (result) {
    freeaddrinfo(result);
  }
  if (err.ok()) {
    return addresses;
  }
  auto error_result = grpc_error_to_absl_status(err);
  return error_result;
}

// Asynchronous SRV record lookup (not implemented)
DNSResolver::TaskHandle NativeDNSResolver::LookupSRV(
    std::function<void(absl::StatusOr<std::vector<grpc_resolved_address>>)>
        on_resolved,
    absl::string_view /* name */, Duration /* timeout */,
    grpc_pollset_set* /* interested_parties */,
    absl::string_view /* name_server */) {
  engine()->Run([on_resolved] {
    ExecCtx exec_ctx;
    on_resolved(absl::UnimplementedError(
        "The Native resolver does not support looking up SRV records"));
  });
  return kNullHandle;
};

// Asynchronous TXT record lookup (not implemented)
DNSResolver::TaskHandle NativeDNSResolver::LookupTXT(
    std::function<void(absl::StatusOr<std::string>)> on_resolved,
    absl::string_view /* name */, Duration /* timeout */,
    grpc_pollset_set* /* interested_parties */,
    absl::string_view /* name_server */) {
  engine()->Run([on_resolved] {
    ExecCtx exec_ctx;
    on_resolved(absl::UnimplementedError(
        "The Native resolver does not support looking up TXT records"));
  });
  return kNullHandle;
};

// Task cancellation (not implemented)
bool NativeDNSResolver::Cancel(TaskHandle /* handle */) { return false; }

}  // namespace grpc_core

#endif  // GRPC_POSIX_SOCKET_RESOLVE_ADDRESS
```