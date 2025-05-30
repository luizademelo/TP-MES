// Copyright 2022 The gRPC Authors

#include "src/core/lib/event_engine/posix_engine/wakeup_fd_posix.h"

#include <memory>

#include "absl/status/statusor.h"
#include "gtest/gtest.h"
#include "src/core/lib/event_engine/posix_engine/wakeup_fd_eventfd.h"
#include "src/core/lib/event_engine/posix_engine/wakeup_fd_pipe.h"

namespace grpc_event_engine {
namespace experimental {

TEST(WakeupFdPosixTest, PipeWakeupFdTest) {
  if (!PipeWakeupFd::IsSupported()) {
    return;
  }
  auto pipe_wakeup_fd = PipeWakeupFd::CreatePipeWakeupFd();
  EXPECT_TRUE(pipe_wakeup_fd.ok());
  EXPECT_GE((*pipe_wakeup_fd)->ReadFd(), 0);
  EXPECT_GE((*pipe_wakeup_fd)->WriteFd(), 0);
  EXPECT_TRUE((*pipe_wakeup_fd)->Wakeup().ok());
  EXPECT_TRUE((*pipe_wakeup_fd)->ConsumeWakeup().ok());
}

TEST(WakeupFdPosixTest, EventFdWakeupFdTest) {
  if (!EventFdWakeupFd::IsSupported()) {
    return;
  }
  auto eventfd_wakeup_fd = EventFdWakeupFd::CreateEventFdWakeupFd();
  EXPECT_TRUE(eventfd_wakeup_fd.ok());
  EXPECT_GE((*eventfd_wakeup_fd)->ReadFd(), 0);
  EXPECT_EQ((*eventfd_wakeup_fd)->WriteFd(), -1);
  EXPECT_TRUE((*eventfd_wakeup_fd)->Wakeup().ok());
  EXPECT_TRUE((*eventfd_wakeup_fd)->ConsumeWakeup().ok());
}

}
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
