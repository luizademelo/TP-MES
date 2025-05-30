
// Copyright 2016 gRPC authors.

#ifndef GRPC_SRC_CORE_RESOLVER_DNS_C_ARES_GRPC_ARES_WRAPPER_H
#define GRPC_SRC_CORE_RESOLVER_DNS_C_ARES_GRPC_ARES_WRAPPER_H

#include <ares.h>
#include <grpc/support/port_platform.h>
#include <stddef.h>

#include <memory>

#include "absl/base/thread_annotations.h"
#include "absl/log/log.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/lib/iomgr/closure.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/lib/iomgr/iomgr_fwd.h"
#include "src/core/resolver/endpoint_addresses.h"
#include "src/core/util/sync.h"

#if GRPC_ARES == 1

#define GRPC_DNS_ARES_DEFAULT_QUERY_TIMEOUT_MS 120000

typedef struct grpc_ares_ev_driver grpc_ares_ev_driver;

struct grpc_ares_request {

  grpc_core::Mutex mu;

  struct ares_addr_port_node dns_server_addr ABSL_GUARDED_BY(mu);

  grpc_closure* on_done ABSL_GUARDED_BY(mu) = nullptr;

  std::unique_ptr<grpc_core::EndpointAddressesList>* addresses_out
      ABSL_GUARDED_BY(mu);

  std::unique_ptr<grpc_core::EndpointAddressesList>* balancer_addresses_out
      ABSL_GUARDED_BY(mu);

  char** service_config_json_out ABSL_GUARDED_BY(mu) = nullptr;

  grpc_ares_ev_driver* ev_driver ABSL_GUARDED_BY(mu) = nullptr;

  size_t pending_queries ABSL_GUARDED_BY(mu) = 0;

  grpc_error_handle error ABSL_GUARDED_BY(mu);
};

extern grpc_ares_request* (*grpc_dns_lookup_hostname_ares)(
    const char* dns_server, const char* name, const char* default_port,
    grpc_pollset_set* interested_parties, grpc_closure* on_done,
    std::unique_ptr<grpc_core::EndpointAddressesList>* addresses,
    int query_timeout_ms);

extern grpc_ares_request* (*grpc_dns_lookup_srv_ares)(
    const char* dns_server, const char* name,
    grpc_pollset_set* interested_parties, grpc_closure* on_done,
    std::unique_ptr<grpc_core::EndpointAddressesList>* balancer_addresses,
    int query_timeout_ms);

extern grpc_ares_request* (*grpc_dns_lookup_txt_ares)(
    const char* dns_server, const char* name,
    grpc_pollset_set* interested_parties, grpc_closure* on_done,
    char** service_config_json, int query_timeout_ms);

extern void (*grpc_cancel_ares_request)(grpc_ares_request* request);

grpc_error_handle grpc_ares_init(void);

void grpc_ares_cleanup(void);

bool grpc_ares_query_ipv6();

void grpc_cares_wrapper_address_sorting_sort(
    const grpc_ares_request* request,
    grpc_core::EndpointAddressesList* addresses);

extern void (*grpc_ares_test_only_inject_config)(ares_channel* channel);

extern bool g_grpc_ares_test_only_force_tcp;

#endif

#endif
