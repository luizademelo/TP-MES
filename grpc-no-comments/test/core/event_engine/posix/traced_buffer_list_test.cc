// Copyright 2022 The gRPC Authors

#include "src/core/lib/event_engine/posix_engine/traced_buffer_list.h"

#include <grpc/support/atm.h>
#include <grpc/support/time.h>
#include <time.h>

#include <memory>

#include "absl/log/check.h"
#include "gtest/gtest.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/lib/iomgr/port.h"
#include "src/core/util/time.h"
#include "src/core/util/useful.h"

#ifdef GRPC_LINUX_ERRQUEUE

#include <linux/errqueue.h>

#define NUM_ELEM 5

extern gpr_timespec (*gpr_now_impl)(gpr_clock_type clock_type);

namespace grpc_event_engine {
namespace experimental {
namespace {

constexpr uint64_t kMaxAdvanceTimeMillis = 24ull * 365 * 3600 * 1000;

gpr_timespec g_now;
gpr_timespec now_impl(gpr_clock_type clock_type) {
  CHECK(clock_type != GPR_TIMESPAN);
  gpr_timespec ts = g_now;
  ts.clock_type = clock_type;
  return ts;
}

void InitGlobals() {
  g_now = {1, 0, GPR_CLOCK_MONOTONIC};
  grpc_core::TestOnlySetProcessEpoch(g_now);
  gpr_now_impl = now_impl;
}

void AdvanceClockMillis(uint64_t millis) {
  grpc_core::ExecCtx exec_ctx;
  g_now = gpr_time_add(
      g_now,
      gpr_time_from_millis(grpc_core::Clamp(millis, static_cast<uint64_t>(1),
                                            kMaxAdvanceTimeMillis),
                           GPR_TIMESPAN));
  exec_ctx.InvalidateNow();
}

void TestShutdownFlushesListVerifier(void* arg, Timestamps* ,
                                     absl::Status status) {
  ASSERT_TRUE(status.ok());
  ASSERT_NE(arg, nullptr);
  int* done = reinterpret_cast<int*>(arg);
  *done = 1;
}

}

TEST(BufferListTest, TestShutdownFlushesList) {
  TcpSetWriteTimestampsCallback(TestShutdownFlushesListVerifier);
  TracedBufferList traced_buffers;
  int verifier_called[NUM_ELEM];
  for (auto i = 0; i < NUM_ELEM; i++) {
    verifier_called[i] = 0;
    traced_buffers.AddNewEntry(i, 0, static_cast<void*>(&verifier_called[i]));
  }
  traced_buffers.Shutdown(nullptr, absl::OkStatus());
  for (auto i = 0; i < NUM_ELEM; i++) {
    ASSERT_EQ(verifier_called[i], 1);
  }
  ASSERT_TRUE(traced_buffers.Size() == 0);
}

TEST(BufferListTest, TestVerifierCalledOnAck) {
  struct sock_extended_err serr;
  serr.ee_data = 213;
  serr.ee_info = SCM_TSTAMP_ACK;
  struct scm_timestamping tss;
  tss.ts[0].tv_sec = 123;
  tss.ts[0].tv_nsec = 456;
  TcpSetWriteTimestampsCallback(
      [](void* arg, Timestamps* ts, absl::Status status) {
        ASSERT_TRUE(status.ok());
        ASSERT_NE(arg, nullptr);
        ASSERT_EQ(ts->acked_time.time.clock_type, GPR_CLOCK_REALTIME);
        ASSERT_EQ(ts->acked_time.time.tv_sec, 123);
        ASSERT_EQ(ts->acked_time.time.tv_nsec, 456);
        ASSERT_GT(ts->info.length, 0);
        int* done = reinterpret_cast<int*>(arg);
        *done = 1;
      });
  TracedBufferList traced_buffers;
  int verifier_called = 0;
  traced_buffers.AddNewEntry(213, 0, &verifier_called);
  traced_buffers.ProcessTimestamp(&serr, nullptr, &tss);
  ASSERT_EQ(verifier_called, 1);
  ASSERT_TRUE(traced_buffers.Size() == 0);
  traced_buffers.Shutdown(nullptr, absl::OkStatus());
  ASSERT_TRUE(traced_buffers.Size() == 0);
}

TEST(BufferListTest, TestProcessTimestampAfterShutdown) {
  struct sock_extended_err serr;
  serr.ee_data = 213;
  serr.ee_info = SCM_TSTAMP_ACK;
  struct scm_timestamping tss;
  tss.ts[0].tv_sec = 123;
  tss.ts[0].tv_nsec = 456;
  TcpSetWriteTimestampsCallback(TestShutdownFlushesListVerifier);
  TracedBufferList traced_buffers;
  int verifier_called = 0;

  traced_buffers.AddNewEntry(213, 0, &verifier_called);
  ASSERT_TRUE(traced_buffers.Size() == 1);
  traced_buffers.Shutdown(nullptr, absl::OkStatus());
  ASSERT_TRUE(traced_buffers.Size() == 0);

  ASSERT_EQ(verifier_called, 1);
  verifier_called = 0;
  traced_buffers.Shutdown(nullptr, absl::OkStatus());
  ASSERT_TRUE(traced_buffers.Size() == 0);

  ASSERT_EQ(verifier_called, 0);
  traced_buffers.ProcessTimestamp(&serr, nullptr, &tss);

  ASSERT_EQ(verifier_called, 0);
}

TEST(BufferListTest, TestLongPendingAckForOneTracedBuffer) {
  constexpr int kMaxPendingAckMillis = 10000;
  struct sock_extended_err serr[3];
  gpr_atm verifier_called[3];
  struct scm_timestamping tss;
  TracedBufferList tb_list;
  serr[0].ee_data = 1;
  serr[0].ee_info = SCM_TSTAMP_SCHED;
  serr[1].ee_data = 1;
  serr[1].ee_info = SCM_TSTAMP_SND;
  serr[2].ee_data = 1;
  serr[2].ee_info = SCM_TSTAMP_ACK;
  gpr_atm_rel_store(&verifier_called[0], static_cast<gpr_atm>(0));
  gpr_atm_rel_store(&verifier_called[1], static_cast<gpr_atm>(0));
  gpr_atm_rel_store(&verifier_called[2], static_cast<gpr_atm>(0));

  tb_list.AddNewEntry(1, 0, &verifier_called[0]);
  tb_list.AddNewEntry(2, 0, &verifier_called[1]);
  tb_list.AddNewEntry(3, 0, &verifier_called[2]);

  AdvanceClockMillis(kMaxPendingAckMillis);
  tss.ts[0].tv_sec = g_now.tv_sec;
  tss.ts[0].tv_nsec = g_now.tv_nsec;

  TcpSetWriteTimestampsCallback(
      [](void*, Timestamps*, absl::Status) { ASSERT_TRUE(false); });
  tb_list.ProcessTimestamp(&serr[0], nullptr, &tss);
  ASSERT_EQ(tb_list.Size(), 3);
  ASSERT_EQ(gpr_atm_acq_load(&verifier_called[0]), static_cast<gpr_atm>(0));
  ASSERT_EQ(gpr_atm_acq_load(&verifier_called[1]), static_cast<gpr_atm>(0));
  ASSERT_EQ(gpr_atm_acq_load(&verifier_called[2]), static_cast<gpr_atm>(0));

  AdvanceClockMillis(kMaxPendingAckMillis);
  tss.ts[0].tv_sec = g_now.tv_sec;
  tss.ts[0].tv_nsec = g_now.tv_nsec;

  TcpSetWriteTimestampsCallback([](void* arg, Timestamps*, absl::Status error) {
    ASSERT_EQ(error, absl::DeadlineExceededError("Ack timed out"));
    ASSERT_NE(arg, nullptr);
    gpr_atm* done = reinterpret_cast<gpr_atm*>(arg);
    gpr_atm_rel_store(done, static_cast<gpr_atm>(1));
  });
  tb_list.ProcessTimestamp(&serr[1], nullptr, &tss);
  ASSERT_EQ(tb_list.Size(), 1);
  ASSERT_EQ(gpr_atm_acq_load(&verifier_called[0]), static_cast<gpr_atm>(0));
  ASSERT_EQ(gpr_atm_acq_load(&verifier_called[1]), static_cast<gpr_atm>(1));
  ASSERT_EQ(gpr_atm_acq_load(&verifier_called[2]), static_cast<gpr_atm>(1));

  AdvanceClockMillis(kMaxPendingAckMillis);
  tss.ts[0].tv_sec = g_now.tv_sec;
  tss.ts[0].tv_nsec = g_now.tv_nsec;

  TcpSetWriteTimestampsCallback(
      [](void* arg, Timestamps* ts, absl::Status error) {
        ASSERT_TRUE(error.ok());
        ASSERT_NE(arg, nullptr);
        ASSERT_EQ(ts->acked_time.time.clock_type, GPR_CLOCK_REALTIME);
        ASSERT_EQ(ts->acked_time.time.tv_sec, g_now.tv_sec);
        ASSERT_EQ(ts->acked_time.time.tv_nsec, g_now.tv_nsec);
        ASSERT_GT(ts->info.length, 0);
        gpr_atm* done = reinterpret_cast<gpr_atm*>(arg);
        gpr_atm_rel_store(done, static_cast<gpr_atm>(2));
      });
  tb_list.ProcessTimestamp(&serr[2], nullptr, &tss);
  ASSERT_EQ(tb_list.Size(), 0);
  ASSERT_EQ(gpr_atm_acq_load(&verifier_called[0]), static_cast<gpr_atm>(2));
  ASSERT_EQ(gpr_atm_acq_load(&verifier_called[1]), static_cast<gpr_atm>(1));
  ASSERT_EQ(gpr_atm_acq_load(&verifier_called[2]), static_cast<gpr_atm>(1));

  tb_list.Shutdown(nullptr, absl::OkStatus());
}

TEST(BufferListTest, TestLongPendingAckForSomeTracedBuffers) {
  constexpr int kNumTracedBuffers = 10;
  constexpr int kMaxPendingAckMillis = 10000;
  struct sock_extended_err serr[kNumTracedBuffers];
  gpr_atm verifier_called[kNumTracedBuffers];
  struct scm_timestamping tss;
  tss.ts[0].tv_sec = 123;
  tss.ts[0].tv_nsec = 456;
  TcpSetWriteTimestampsCallback(
      [](void* arg, Timestamps* ts, absl::Status status) {
        ASSERT_NE(arg, nullptr);
        if (status.ok()) {
          ASSERT_EQ(ts->acked_time.time.clock_type, GPR_CLOCK_REALTIME);
          ASSERT_EQ(ts->acked_time.time.tv_sec, 123);
          ASSERT_EQ(ts->acked_time.time.tv_nsec, 456);
          ASSERT_GT(ts->info.length, 0);
          *(reinterpret_cast<int*>(arg)) = 1;
        } else if (status == absl::DeadlineExceededError("Ack timed out")) {
          *(reinterpret_cast<int*>(arg)) = 2;
        } else {
          ASSERT_TRUE(false);
        }
      });
  TracedBufferList tb_list;
  for (int i = 0; i < kNumTracedBuffers; i++) {
    serr[i].ee_data = i + 1;
    serr[i].ee_info = SCM_TSTAMP_ACK;
    gpr_atm_rel_store(&verifier_called[i], static_cast<gpr_atm>(0));
    tb_list.AddNewEntry(i + 1, 0, &verifier_called[i]);
  }
  int elapsed_time_millis = 0;
  int increment_millis = (2 * kMaxPendingAckMillis) / 10;
  for (int i = 0; i < kNumTracedBuffers; i++) {
    AdvanceClockMillis(increment_millis);
    elapsed_time_millis += increment_millis;
    tb_list.ProcessTimestamp(&serr[i], nullptr, &tss);
    if (elapsed_time_millis > kMaxPendingAckMillis) {

      ASSERT_EQ(tb_list.Size(), 0);
      if (elapsed_time_millis - kMaxPendingAckMillis == increment_millis) {

        ASSERT_EQ(gpr_atm_acq_load(&verifier_called[i]),
                  static_cast<gpr_atm>(1));
      } else {
        ASSERT_EQ(gpr_atm_acq_load(&verifier_called[i]),
                  static_cast<gpr_atm>(2));
      }
    } else {
      ASSERT_EQ(tb_list.Size(), kNumTracedBuffers - (i + 1));
      ASSERT_EQ(gpr_atm_acq_load(&verifier_called[i]), static_cast<gpr_atm>(1));
    }
  }
  tb_list.Shutdown(nullptr, absl::OkStatus());
}

}
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  grpc_event_engine::experimental::InitGlobals();
  return RUN_ALL_TESTS();
}

#else

int main(int , char** ) { return 0; }

#endif
