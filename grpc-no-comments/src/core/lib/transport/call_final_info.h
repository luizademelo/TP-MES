// Copyright 2024 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_TRANSPORT_CALL_FINAL_INFO_H
#define GRPC_SRC_CORE_LIB_TRANSPORT_CALL_FINAL_INFO_H

#include <grpc/status.h>
#include <grpc/support/port_platform.h>
#include <grpc/support/time.h>

#include <cstdint>

struct grpc_transport_one_way_stats {
  uint64_t framing_bytes = 0;
  uint64_t data_bytes = 0;
  uint64_t header_bytes = 0;
};

struct grpc_transport_stream_stats {
  grpc_transport_one_way_stats incoming;
  grpc_transport_one_way_stats outgoing;
  gpr_timespec latency = gpr_inf_future(GPR_TIMESPAN);
};

void grpc_transport_move_one_way_stats(grpc_transport_one_way_stats* from,
                                       grpc_transport_one_way_stats* to);

void grpc_transport_move_stats(grpc_transport_stream_stats* from,
                               grpc_transport_stream_stats* to);

struct grpc_call_stats {
  grpc_transport_stream_stats transport_stream_stats;
  gpr_timespec latency;
};

struct grpc_call_final_info {
  grpc_call_stats stats;
  grpc_status_code final_status = GRPC_STATUS_OK;
  const char* error_string = nullptr;
};

#endif
