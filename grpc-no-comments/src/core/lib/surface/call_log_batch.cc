
// Copyright 2015 gRPC authors.

#include <grpc/grpc.h>
#include <grpc/support/alloc.h>
#include <grpc/support/port_platform.h>
#include <inttypes.h>
#include <stddef.h>

#include <algorithm>
#include <string>
#include <vector>

#include "absl/strings/str_format.h"
#include "absl/strings/str_join.h"
#include "src/core/lib/slice/slice_internal.h"
#include "src/core/lib/slice/slice_string_helpers.h"
#include "src/core/lib/surface/call.h"
#include "src/core/util/string.h"

static void add_metadata(const grpc_metadata* md, size_t count,
                         std::vector<std::string>* b) {
  if (md == nullptr) {
    b->push_back("(nil)");
    return;
  }
  for (size_t i = 0; i < count; i++) {
    b->push_back("\nkey=");
    b->push_back(std::string(grpc_core::StringViewFromSlice(md[i].key)));
    b->push_back(" value=");
    char* dump = grpc_dump_slice(md[i].value, GPR_DUMP_HEX | GPR_DUMP_ASCII);
    b->push_back(dump);
    gpr_free(dump);
  }
}

static std::string grpc_op_string(const grpc_op* op) {
  std::vector<std::string> parts;
  switch (op->op) {
    case GRPC_OP_SEND_INITIAL_METADATA:
      parts.push_back("SEND_INITIAL_METADATA");
      add_metadata(op->data.send_initial_metadata.metadata,
                   op->data.send_initial_metadata.count, &parts);
      break;
    case GRPC_OP_SEND_MESSAGE:
      parts.push_back(absl::StrFormat("SEND_MESSAGE ptr=%p",
                                      op->data.send_message.send_message));
      break;
    case GRPC_OP_SEND_CLOSE_FROM_CLIENT:
      parts.push_back("SEND_CLOSE_FROM_CLIENT");
      break;
    case GRPC_OP_SEND_STATUS_FROM_SERVER:
      parts.push_back(
          absl::StrFormat("SEND_STATUS_FROM_SERVER status=%d details=",
                          op->data.send_status_from_server.status));
      if (op->data.send_status_from_server.status_details != nullptr) {
        char* dump = grpc_dump_slice(
            *op->data.send_status_from_server.status_details, GPR_DUMP_ASCII);
        parts.push_back(dump);
        gpr_free(dump);
      } else {
        parts.push_back("(null)");
      }
      add_metadata(op->data.send_status_from_server.trailing_metadata,
                   op->data.send_status_from_server.trailing_metadata_count,
                   &parts);
      break;
    case GRPC_OP_RECV_INITIAL_METADATA:
      parts.push_back(absl::StrFormat(
          "RECV_INITIAL_METADATA ptr=%p",
          op->data.recv_initial_metadata.recv_initial_metadata));
      break;
    case GRPC_OP_RECV_MESSAGE:
      parts.push_back(absl::StrFormat("RECV_MESSAGE ptr=%p",
                                      op->data.recv_message.recv_message));
      break;
    case GRPC_OP_RECV_STATUS_ON_CLIENT:
      parts.push_back(absl::StrFormat(
          "RECV_STATUS_ON_CLIENT metadata=%p status=%p details=%p",
          op->data.recv_status_on_client.trailing_metadata,
          op->data.recv_status_on_client.status,
          op->data.recv_status_on_client.status_details));
      break;
    case GRPC_OP_RECV_CLOSE_ON_SERVER:
      parts.push_back(absl::StrFormat("RECV_CLOSE_ON_SERVER cancelled=%p",
                                      op->data.recv_close_on_server.cancelled));
  }
  return absl::StrJoin(parts, "");
}

void grpc_call_log_batch(const char* file, int line, const grpc_op* ops,
                         size_t nops) {
  for (size_t i = 0; i < nops; i++) {
    LOG(INFO).AtLocation(file, line)
        << "ops[" << i << "]: " << grpc_op_string(&ops[i]);
  }
}
