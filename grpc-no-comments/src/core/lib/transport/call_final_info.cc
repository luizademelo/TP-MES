// Copyright 2024 gRPC authors.

#include "src/core/lib/transport/call_final_info.h"

#include <grpc/support/port_platform.h>

#include <utility>

static void move64bits(uint64_t* from, uint64_t* to) {
  *to += *from;
  *from = 0;
}

void grpc_transport_move_one_way_stats(grpc_transport_one_way_stats* from,
                                       grpc_transport_one_way_stats* to) {
  move64bits(&from->framing_bytes, &to->framing_bytes);
  move64bits(&from->data_bytes, &to->data_bytes);
  move64bits(&from->header_bytes, &to->header_bytes);
}

void grpc_transport_move_stats(grpc_transport_stream_stats* from,
                               grpc_transport_stream_stats* to) {
  grpc_transport_move_one_way_stats(&from->incoming, &to->incoming);
  grpc_transport_move_one_way_stats(&from->outgoing, &to->outgoing);
  to->latency = std::exchange(from->latency, gpr_inf_future(GPR_TIMESPAN));
}
