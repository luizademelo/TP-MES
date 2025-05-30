
// Copyright 2016 gRPC authors.

#ifndef GRPC_SRC_CORE_LOAD_BALANCING_GRPCLB_LOAD_BALANCER_API_H
#define GRPC_SRC_CORE_LOAD_BALANCING_GRPCLB_LOAD_BALANCER_API_H
#include <grpc/slice.h>
#include <grpc/support/port_platform.h>
#include <stdint.h>

#include <vector>

#include "absl/strings/string_view.h"
#include "src/core/load_balancing/grpclb/grpclb_client_stats.h"
#include "src/core/util/time.h"
#include "upb/mem/arena.h"

#define GRPC_GRPCLB_SERVICE_NAME_MAX_LENGTH 128
#define GRPC_GRPCLB_SERVER_IP_ADDRESS_MAX_SIZE 16
#define GRPC_GRPCLB_SERVER_LOAD_BALANCE_TOKEN_MAX_SIZE 50

namespace grpc_core {

struct GrpcLbServer {
  int32_t ip_size;
  char ip_addr[GRPC_GRPCLB_SERVER_IP_ADDRESS_MAX_SIZE];
  int32_t port;
  char load_balance_token[GRPC_GRPCLB_SERVER_LOAD_BALANCE_TOKEN_MAX_SIZE];
  bool drop;

  bool operator==(const GrpcLbServer& other) const;
};

struct GrpcLbResponse {
  enum { INITIAL, SERVERLIST, FALLBACK } type;
  Duration client_stats_report_interval;
  std::vector<GrpcLbServer> serverlist;
};

grpc_slice GrpcLbRequestCreate(absl::string_view lb_service_name,
                               upb_Arena* arena);

grpc_slice GrpcLbLoadReportRequestCreate(
    int64_t num_calls_started, int64_t num_calls_finished,
    int64_t num_calls_finished_with_client_failed_to_send,
    int64_t num_calls_finished_known_received,
    const GrpcLbClientStats::DroppedCallCounts* drop_token_counts,
    upb_Arena* arena);

bool GrpcLbResponseParse(const grpc_slice& serialized_response,
                         upb_Arena* arena, GrpcLbResponse* result);

}

#endif
