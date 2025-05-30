
// Copyright 2025 gRPC authors.

#ifndef GRPC_SRC_CORE_EXT_TRANSPORT_CHTTP2_TRANSPORT_WRITABLE_STREAM_LIST_H
#define GRPC_SRC_CORE_EXT_TRANSPORT_CHTTP2_TRANSPORT_WRITABLE_STREAM_LIST_H

#include "absl/log/check.h"
#include "absl/log/log.h"

namespace grpc_core {
namespace http2 {

class WritableStreamList {
 public:
  ~WritableStreamList() = default;

  WritableStreamList(WritableStreamList&& rhs) = delete;
  WritableStreamList& operator=(WritableStreamList&& rhs) = delete;
  WritableStreamList(const WritableStreamList&) = delete;
  WritableStreamList& operator=(const WritableStreamList&) = delete;

 private:

};

}
}

#endif
