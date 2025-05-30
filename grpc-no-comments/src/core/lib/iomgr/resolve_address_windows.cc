
// Copyright 2015 gRPC authors.

#include <grpc/support/port_platform.h>

#include "src/core/lib/iomgr/port.h"
#ifdef GRPC_WINSOCK_SOCKET

#include <grpc/support/alloc.h>
#include <grpc/support/log_windows.h>
#include <grpc/support/string_util.h>
#include <grpc/support/time.h>
#include <inttypes.h>
#include <string.h>
#include <sys/types.h>

#include <string>

#include "absl/strings/str_format.h"
#include "src/core/lib/address_utils/sockaddr_utils.h"
#include "src/core/lib/event_engine/default_event_engine.h"
#include "src/core/lib/iomgr/block_annotate.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/lib/iomgr/iomgr_internal.h"
#include "src/core/lib/iomgr/resolve_address.h"
#include "src/core/lib/iomgr/resolve_address_windows.h"
#include "src/core/lib/iomgr/sockaddr.h"
#include "src/core/lib/transport/error_utils.h"
#include "src/core/util/crash.h"
#include "src/core/util/host_port.h"
#include "src/core/util/string.h"
#include "src/core/util/thd.h"

namespace grpc_core {

grpc_event_engine::experimental::EventEngine* NativeDNSResolver::engine() {

  auto engine_ptr = engine_ptr_.load(std::memory_order_relaxed);
  if (engine_ptr != nullptr) return engine_ptr;

  MutexLock lock(&mu_);
  if (engine_ != nullptr) return engine_.get();
  engine_ = grpc_event_engine::experimental::GetDefaultEventEngine();
  engine_ptr_.store(engine_.get(), std::memory_order_relaxed);
  return engine_.get();
}

DNSResolver::TaskHandle NativeDNSResolver::LookupHostname(
    std::function<void(absl::StatusOr<std::vector<grpc_resolved_address>>)>
        on_resolved,
    absl::string_view name, absl::string_view default_port,
    Duration , grpc_pollset_set* ,
    absl::string_view ) {
  engine()->Run([on_resolved = std::move(on_resolved), name = std::string(name),
                 default_port = std::string(default_port)]() {
    ExecCtx exec_ctx;
    auto result = GetDNSResolver()->LookupHostnameBlocking(name, default_port);
    on_resolved(std::move(result));
  });
  return kNullHandle;
}

absl::StatusOr<std::vector<grpc_resolved_address>>
NativeDNSResolver::LookupHostnameBlocking(absl::string_view name,
                                          absl::string_view default_port) {
  ExecCtx exec_ctx;
  struct addrinfo hints;
  struct addrinfo *result = NULL, *resp;
  int s;
  grpc_error_handle error;
  std::vector<grpc_resolved_address> addresses;

  std::string host;
  std::string port;
  SplitHostPort(name, &host, &port);
  if (host.empty()) {
    error =
        GRPC_ERROR_CREATE(absl::StrFormat("unparsable host:port: '%s'", name));
    goto done;
  }
  if (port.empty()) {
    if (default_port.empty()) {
      error = GRPC_ERROR_CREATE(absl::StrFormat("no port in name '%s'", name));
      goto done;
    }
    port = std::string(default_port);
  }

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  GRPC_SCHEDULING_START_BLOCKING_REGION;
  s = getaddrinfo(host.c_str(), port.c_str(), &hints, &result);
  GRPC_SCHEDULING_END_BLOCKING_REGION;
  if (s != 0) {
    error = GRPC_WSA_ERROR(WSAGetLastError(), "getaddrinfo");
    goto done;
  }

  for (resp = result; resp != NULL; resp = resp->ai_next) {
    grpc_resolved_address addr;
    memcpy(&addr.addr, resp->ai_addr, resp->ai_addrlen);
    addr.len = resp->ai_addrlen;
    addresses.push_back(addr);
  }

done:
  if (result) {
    freeaddrinfo(result);
  }
  if (error.ok()) {
    return addresses;
  }
  auto error_result = grpc_error_to_absl_status(error);
  return error_result;
}

DNSResolver::TaskHandle NativeDNSResolver::LookupSRV(
    std::function<void(absl::StatusOr<std::vector<grpc_resolved_address>>)>
        on_resolved,
    absl::string_view , Duration ,
    grpc_pollset_set* ,
    absl::string_view ) {
  engine()->Run([on_resolved] {
    ExecCtx exec_ctx;
    on_resolved(absl::UnimplementedError(
        "The Native resolver does not support looking up SRV records"));
  });
  return kNullHandle;
};

DNSResolver::TaskHandle NativeDNSResolver::LookupTXT(
    std::function<void(absl::StatusOr<std::string>)> on_resolved,
    absl::string_view , Duration ,
    grpc_pollset_set* ,
    absl::string_view ) {

  engine()->Run([on_resolved] {
    ExecCtx exec_ctx;
    on_resolved(absl::UnimplementedError(
        "The Native resolver does not support looking up TXT records"));
  });
  return kNullHandle;
};

bool NativeDNSResolver::Cancel(TaskHandle ) { return false; }

}

#endif
