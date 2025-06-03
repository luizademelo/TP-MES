Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

#include <grpc/support/port_platform.h>
#include "src/core/lib/iomgr/port.h"

// TCP implementation for POSIX systems
#ifdef GRPC_POSIX_SOCKET_TCP

#include <errno.h>
#include <grpc/event_engine/endpoint_config.h>
#include <grpc/event_engine/event_engine.h>
#include <grpc/slice.h>
#include <grpc/support/alloc.h>
#include <grpc/support/string_util.h>
#include <grpc/support/sync.h>
#include <grpc/support/time.h>
#include <limits.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <algorithm>
#include <optional>
#include <unordered_map>

// Abseil headers
#include "absl/base/thread_annotations.h"
#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/status/status.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/string_view.h"

// gRPC core headers
#include "src/core/lib/address_utils/sockaddr_utils.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/lib/event_engine/extensions/supports_fd.h"
#include "src/core/lib/event_engine/query_extensions.h"
#include "src/core/lib/event_engine/shim.h"
#include "src/core/lib/experiments/experiments.h"
#include "src/core/lib/iomgr/buffer_list.h"
#include "src/core/lib/iomgr/ev_posix.h"
#include "src/core/lib/iomgr/event_engine_shims/endpoint.h"
#include "src/core/lib/iomgr/tcp_posix.h"
#include "src/core/lib/resource_quota/memory_quota.h"
#include "src/core/lib/slice/slice_internal.h"
#include "src/core/lib/slice/slice_string_helpers.h"
#include "src/core/telemetry/stats.h"
#include "src/core/telemetry/stats_data.h"
#include "src/core/util/crash.h"
#include "src/core/util/event_log.h"
#include "src/core/util/strerror.h"
#include "src/core/util/string.h"
#include "src/core/util/sync.h"
#include "src/core/util/time.h"

// TCP socket options
#ifndef SOL_TCP
#define SOL_TCP IPPROTO_TCP
#endif

#ifndef TCP_INQ
#define TCP_INQ 36
#define TCP_CM_INQ TCP_INQ
#endif

// Send message flags
#ifdef GRPC_HAVE_MSG_NOSIGNAL
#define SENDMSG_FLAGS MSG_NOSIGNAL
#else
#define SENDMSG_FLAGS 0
#endif

#ifndef MSG_ZEROCOPY
#define MSG_ZEROCOPY 0x4000000
#endif

// IOV length type
#ifdef GRPC_MSG_IOVLEN_TYPE
typedef GRPC_MSG_IOVLEN_TYPE msg_iovlen_type;
#else
typedef size_t msg_iovlen_type;
#endif

namespace grpc_core {

// Class for managing zero-copy send records
class TcpZerocopySendRecord {
 public:
  TcpZerocopySendRecord() { grpc_slice_buffer_init(&buf_); }

  ~TcpZerocopySendRecord() {
    AssertEmpty();
    grpc_slice_buffer_destroy(&buf_);
  }

  // Populate I/O vectors for sending
  msg_iovlen_type PopulateIovs(size_t* unwind_slice_idx,
                               size_t* unwind_byte_idx, size_t* sending_length,
                               iovec* iov);

  // Undo a partially sent operation
  void UnwindIfThrottled(size_t unwind_slice_idx, size_t unwind_byte_idx) {
    out_offset_.byte_idx = unwind_byte_idx;
    out_offset_.slice_idx = unwind_slice_idx;
  }

  // Update offsets after bytes are sent
  void UpdateOffsetForBytesSent(size_t sending_length, size_t actually_sent);

  // Check if all slices have been sent
  bool AllSlicesSent() { return out_offset_.slice_idx == buf_.count; }

  // Prepare for sending slices
  void PrepareForSends(grpc_slice_buffer* slices_to_send) {
    AssertEmpty();
    out_offset_.slice_idx = 0;
    out_offset_.byte_idx = 0;
    grpc_slice_buffer_swap(slices_to_send, &buf_);
    Ref();
  }

  // Increment reference count
  void Ref() { ref_.fetch_add(1, std::memory_order_relaxed); }

  // Decrement reference count and cleanup if last reference
  bool Unref() {
    const intptr_t prior = ref_.fetch_sub(1, std::memory_order_acq_rel);
    DCHECK_GT(prior, 0);
    if (prior == 1) {
      AllSendsComplete();
      return true;
    }
    return false;
  }

 private:
  // Tracks offset in outgoing buffer
  struct OutgoingOffset {
    size_t slice_idx = 0;
    size_t byte_idx = 0;
  };

  // Verify buffer is empty
  void AssertEmpty() {
    DCHECK_EQ(buf_.count, 0u);
    DCHECK_EQ(buf_.length, 0u);
    DCHECK_EQ(ref_.load(std::memory_order_relaxed), 0);
  }

  // Cleanup after all sends complete
  void AllSendsComplete() {
    DCHECK_EQ(ref_.load(std::memory_order_relaxed), 0);
    grpc_slice_buffer_reset_and_unref(&buf_);
  }

  grpc_slice_buffer buf_;            // Buffer of slices to send
  std::atomic<intptr_t> ref_{0};     // Reference count
  OutgoingOffset out_offset_;        // Current send position
};

// Context for managing zero-copy sends
class TcpZerocopySendCtx {
 public:
  static constexpr int kDefaultMaxSends = 4;
  static constexpr size_t kDefaultSendBytesThreshold = 16 * 1024;

  explicit TcpZerocopySendCtx(
      int max_sends = kDefaultMaxSends,
      size_t send_bytes_threshold = kDefaultSendBytesThreshold)
      : max_sends_(max_sends),
        free_send_records_size_(max_sends),
        threshold_bytes_(send_bytes_threshold) {
    // Allocate send records
    send_records_ = static_cast<TcpZerocopySendRecord*>(
        gpr_malloc(max_sends * sizeof(*send_records_)));
    free_send_records_ = static_cast<TcpZerocopySendRecord**>(
        gpr_malloc(max_sends * sizeof(*free_send_records_)));
    if (send_records_ == nullptr || free_send_records_ == nullptr) {
      gpr_free(send_records_);
      gpr_free(free_send_records_);
      GRPC_TRACE_LOG(tcp, INFO)
          << "Disabling TCP TX zerocopy due to memory pressure.\n";
      memory_limited_ = true;
    } else {
      // Initialize send records
      for (int idx = 0; idx < max_sends_; ++idx) {
        new (send_records_ + idx) TcpZerocopySendRecord();
        free_send_records_[idx] = send_records_ + idx;
      }
    }
  }

  ~TcpZerocopySendCtx() {
    // Destroy send records
    if (send_records_ != nullptr) {
      for (int idx = 0; idx < max_sends_; ++idx) {
        send_records_[idx].~TcpZerocopySendRecord();
      }
    }
    gpr_free(send_records_);
    gpr_free(free_send_records_);
  }

  bool memory_limited() const { return memory_limited_; }

  // Track a new send operation
  void NoteSend(TcpZerocopySendRecord* record) {
    record->Ref();
    {
      MutexLock guard(&lock_);
      is_in_write_ = true;
      AssociateSeqWithSendRecordLocked(last_send_, record);
    }
    ++last_send_;
  }

  // Undo a send operation
  void UndoSend() {
    --last_send_;
    if (ReleaseSendRecord(last_send_)->Unref()) {
      DCHECK(0);
    }
  }

  // Associate sequence number with send record
  void AssociateSeqWithSendRecordLocked(uint32_t seq,
                                        TcpZerocopySendRecord* record) {
    ctx_lookup_.emplace(seq, record);
  }

  // Get an available send record
  TcpZerocopySendRecord* GetSendRecord() {
    MutexLock guard(&lock_);
    return TryGetSendRecordLocked();
  }

  // Release a send record by sequence number
  TcpZerocopySendRecord* ReleaseSendRecord(uint32_t seq) {
    MutexLock guard(&lock_);
    return ReleaseSendRecordLocked(seq);
  }

  // Return a send record to the pool
  void PutSendRecord(TcpZerocopySendRecord* record) {
    DCHECK(record >= send_records_);
    DCHECK(record < send_records_ + max_sends_);
    MutexLock guard(&lock_);
    PutSendRecordLocked(record);
  }

  // Shutdown the send context
  void Shutdown() { shutdown_.store(true, std::memory_order_release); }

  // Check if all send records are empty
  bool AllSendRecordsEmpty() {
    MutexLock guard(&lock_);
    return free_send_records_size_ == max_sends_;
  }

  bool enabled() const { return enabled_; }

  void set_enabled(bool enabled) {
    DCHECK(!enabled || !memory_limited());
    enabled_ = enabled;
  }

  size_t threshold_bytes() const { return threshold_bytes_; }

  // Update state after freeing memory
  bool UpdateZeroCopyOMemStateAfterFree() {
    MutexLock guard(&lock_);
    if (is_in_write_) {
      zcopy_enobuf_state_ = OMemState::CHECK;
      return false;
    }
    DCHECK(zcopy_enobuf_state_ != OMemState::CHECK);
    if (zcopy_enobuf_state_ == OMemState::FULL) {
      zcopy_enobuf_state_ = OMemState::OPEN;
      return true;
    } else if (zcopy_enobuf_state_ == OMemState::OPEN) {
      return false;
    } else {
      Crash("OMem state error!");
    }
  }

  // Update state after send operation
  bool UpdateZeroCopyOMemStateAfterSend(bool seen_enobuf) {
    MutexLock guard(&lock_);
    is_in_write_ = false;
    if (seen_enobuf) {
      if (zcopy_enobuf_state_ == OMemState::CHECK) {
        zcopy_enobuf_state_ = OMemState::OPEN;
        return true;
      } else {
        zcopy_enobuf_state_ = OMemState::FULL;
      }
    } else if (zcopy_enobuf_state_ != OMemState::OPEN) {
      zcopy_enobuf_state_ = OMemState::OPEN;
    }
    return false;
  }

 private:
  // Out of memory states
  enum class OMemState : int8_t {
    OPEN,    // Memory available
    FULL,    // Out of memory
    CHECK,   // Need to check state
  };

  // Release send record by sequence number
  TcpZerocopySendRecord* ReleaseSendRecordLocked(uint32_t seq) {
    auto iter = ctx_lookup_.find(seq);
    DCHECK(iter != ctx_lookup_.end());
    TcpZerocopySendRecord* record = iter->second;
    ctx_lookup_.erase(iter);
    return record;
  }

  // Try to get an available send record
  TcpZerocopySendRecord* TryGetSendRecordLocked() {
    if (shutdown_.load(std::memory_order_acquire)) {
      return nullptr;
    }
    if (free_send_records_size_ == 0) {
      return nullptr;
    }
    free_send_records_size_--;
    return free_send_records_[free_send_records_size_];
  }

  // Return send record to pool
  void PutSendRecordLocked(TcpZerocopySendRecord* record) {
    DCHECK(free_send_records_size_ < max_sends_);
    free_send_records_[free_send_records_size_] = record;
    free_send_records_size_++;
  }

  TcpZerocopySendRecord* send_records_;           // Array of send records
  TcpZerocopySendRecord** free_send_records_;     // Available records
  int max_sends_;                                 // Max concurrent sends
  int free_send_records_size_;                    // Current available count
  Mutex lock_;                                    // Protects state
  uint32_t last_send_ = 0;                        // Last sequence number
  std::atomic<bool> shutdown_{false};             // Shutdown flag
  bool enabled_ = false;                          // Zero-copy enabled
  size_t threshold_bytes_ = kDefaultSendBytesThreshold; // Min size for zero-copy
  std::unordered_map<uint32_t, TcpZerocopySendRecord*> ctx_lookup_; // Active sends
  bool memory_limited_ = false;                   // Memory allocation failed
  bool is_in_write_ = false;                      // Currently writing
  OMemState zcopy_enobuf_state_ = OMemState::OPEN; // Memory state
};

}  // namespace grpc_core

// TCP endpoint structure
struct grpc_tcp {
  explicit grpc_tcp(const grpc_core::PosixTcpOptions& tcp_options)
      : min_read_chunk_size(tcp_options.tcp_min_read_chunk_size),
        max_read_chunk_size(tcp_options.tcp_max_read_chunk_size),
        tcp_zerocopy_send_ctx(
            tcp_options.tcp_tx_zerocopy_max_simultaneous_sends,
            tcp_options.tcp_tx_zerocopy_send_bytes_threshold) {}
  grpc_endpoint base;                  // Base endpoint structure
  grpc_fd* em_fd;                      // Event manager file descriptor
  int fd;                              // Socket file descriptor
  int inq;                             // Incoming queue status
  double target_length;                // Target read length
  double bytes_read_this_round;        // Bytes read in current round
  grpc_core::RefCount refcount;        // Reference count
  gpr_atm shutdown_count;              // Shutdown counter

  int min_read_chunk_size;             // Minimum read chunk size
  int max_read_chunk_size;             // Maximum read chunk size

  grpc_slice_buffer last_read_buffer;  // Buffer for last read data

  grpc_core::Mutex read_mu;            // Protects read state
  grpc_slice_buffer* incoming_buffer ABSL_GUARDED_BY(read_mu) = nullptr; // Incoming data buffer

  grpc_slice_buffer* outgoing_buffer;  // Outgoing data buffer
  size_t outgoing_byte_idx;            // Current position in outgoing buffer

  grpc_closure* read_cb;               // Read completion callback
  grpc_closure* write_cb;              // Write completion callback
  grpc_closure* release_fd_cb;         // FD release callback
  int* release_fd;                     // FD to release

  grpc_closure read_done_closure;      // Internal read done callback
  grpc_closure write_done_closure;     // Internal write done callback
  grpc_closure error_closure;          // Error handling callback

  std::string peer_string;             // Peer address string
  std::string local_address;           // Local address string

  grpc_core::MemoryOwner memory_owner; // Memory owner for allocations
  grpc_core::MemoryAllocator::Reservation self_reservation; // Memory reservation

  grpc_core::TracedBufferList tb_list; // List of traced buffers

  void* outgoing_buffer_arg;           // Argument for outgoing buffer

  int bytes_counter;                   // Byte counter for timestamps
  int min_progress_size;               // Minimum progress size for reads

  gpr_atm stop_error_notification;     // Flag to stop error notifications

  TcpZerocopySendCtx tcp_zerocopy_send_ctx; // Zero-copy send context
  TcpZerocopySendRecord* current_zerocopy_send = nullptr; // Current zero-copy send

  int set_rcvlowat;                    // SO_RCVLOWAT value

  bool is_first_read;                  // First read flag
  bool has_posted_reclaimer ABSL_GUARDED_BY(read_mu) = false; // Reclaimer posted flag
  bool inq_capable;                    // TCP_INQ capable
  bool socket_ts_enabled;              // Socket timestamps enabled
  bool ts_capable;                     // Timestamps capable
};

// Backup poller structure
struct backup_poller {
  gpr_mu* pollset_mu;                  // Pollset mutex
  grpc_closure done_poller;            // Poller completion callback
  std::shared_ptr<grpc_event_engine::experimental::EventEngine> engine; // Event engine
};

// Log common I/O errors
void LogCommonIOErrors(absl::string_view prefix, int error_no) {
  switch (error_no) {
    case ECONNABORTED:
      grpc_core::global_stats().IncrementEconnabortedCount();
      return;
    case ECONNRESET:
      grpc_core::global_stats().IncrementEconnresetCount();
      return;
    case EPIPE:
      grpc_core::global_stats().IncrementEpipeCount();
      return;
    case ETIMEDOUT:
      grpc_core::global_stats().IncrementEt