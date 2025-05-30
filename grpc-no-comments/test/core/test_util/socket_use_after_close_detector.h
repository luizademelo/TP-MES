
// Copyright 2017 gRPC authors.

#ifndef GRPC_TEST_CORE_TEST_UTIL_SOCKET_USE_AFTER_CLOSE_DETECTOR_H
#define GRPC_TEST_CORE_TEST_UTIL_SOCKET_USE_AFTER_CLOSE_DETECTOR_H

#include <grpc/support/port_platform.h>
#include <grpc/support/sync_generic.h>

#include <memory>
#include <thread>

namespace grpc_core {
namespace testing {

// Note: this will not give false positives but may give false negatives.

class SocketUseAfterCloseDetector {
 public:
  SocketUseAfterCloseDetector();
  ~SocketUseAfterCloseDetector();

 private:
  std::unique_ptr<std::thread> thread_;
  gpr_event done_ev_;
};

}
}

#endif
