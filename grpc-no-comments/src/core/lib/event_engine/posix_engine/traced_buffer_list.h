// Copyright 2022 The gRPC Authors

#ifndef GRPC_SRC_CORE_LIB_EVENT_ENGINE_POSIX_ENGINE_TRACED_BUFFER_LIST_H
#define GRPC_SRC_CORE_LIB_EVENT_ENGINE_POSIX_ENGINE_TRACED_BUFFER_LIST_H

#include <grpc/support/port_platform.h>
#include <grpc/support/time.h>
#include <stdint.h>

#include <optional>

#include "absl/functional/any_invocable.h"
#include "absl/status/status.h"
#include "src/core/lib/event_engine/posix_engine/internal_errqueue.h"
#include "src/core/lib/iomgr/port.h"
#include "src/core/util/sync.h"

namespace grpc_event_engine::experimental {

struct ConnectionMetrics {
  std::optional<uint64_t> delivery_rate;

  std::optional<bool> is_delivery_rate_app_limited;

  std::optional<uint32_t> packet_retx;

  std::optional<uint32_t> packet_spurious_retx;

  std::optional<uint32_t> packet_sent;

  std::optional<uint32_t> packet_delivered;

  std::optional<uint32_t> packet_delivered_ce;

  std::optional<uint64_t> data_retx;

  std::optional<uint64_t> data_sent;

  std::optional<uint64_t> data_notsent;

  std::optional<uint64_t> pacing_rate;

  std::optional<uint32_t> min_rtt;

  std::optional<uint32_t> srtt;

  std::optional<uint32_t> congestion_window;

  std::optional<uint32_t> snd_ssthresh;

  std::optional<uint32_t> reordering;

  std::optional<uint8_t> recurring_retrans;

  std::optional<uint64_t> busy_usec;

  std::optional<uint64_t> rwnd_limited_usec;

  std::optional<uint64_t> sndbuf_limited_usec;
};

struct BufferTimestamp {
  gpr_timespec time;
  ConnectionMetrics metrics;
};

struct Timestamps {
  BufferTimestamp sendmsg_time;
  BufferTimestamp scheduled_time;
  BufferTimestamp sent_time;
  BufferTimestamp acked_time;

  uint32_t byte_offset;

#ifdef GRPC_LINUX_ERRQUEUE
  tcp_info info;
#endif
};

#ifdef GRPC_LINUX_ERRQUEUE

class TracedBufferList {
 public:
  TracedBufferList() = default;
  ~TracedBufferList() = default;

  void AddNewEntry(int32_t seq_no, int fd, void* arg);

  void ProcessTimestamp(struct sock_extended_err* serr,
                        struct cmsghdr* opt_stats,
                        struct scm_timestamping* tss);

  int Size() {
    grpc_core::MutexLock lock(&mu_);
    int size = 0;
    TracedBuffer* curr = head_;
    while (curr) {
      ++size;
      curr = curr->next_;
    }
    return size;
  }

  void Shutdown(void* , absl::Status );

 private:
  class TracedBuffer {
   public:
    TracedBuffer(uint32_t seq_no, void* arg) : seq_no_(seq_no), arg_(arg) {}

    bool Finished(gpr_timespec ts);

   private:
    friend class TracedBufferList;
    gpr_timespec last_timestamp_;
    TracedBuffer* next_ = nullptr;
    uint32_t seq_no_;
    void* arg_;
    Timestamps ts_;
  };
  grpc_core::Mutex mu_;

  TracedBuffer* head_ = nullptr;
  TracedBuffer* tail_ = nullptr;
};

#else

class TracedBufferList {
 public:
  void AddNewEntry(int32_t , int , void* ) {}
  void ProcessTimestamp(struct sock_extended_err* ,
                        struct cmsghdr* ,
                        struct scm_timestamping* ) {}
  int Size() { return 0; }
  void Shutdown(void* , absl::Status ) {}
};
#endif

void TcpSetWriteTimestampsCallback(
    absl::AnyInvocable<void(void*, Timestamps*, absl::Status)>);

}

#endif
