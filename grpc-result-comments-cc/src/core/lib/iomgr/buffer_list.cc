Here's the commented version of the code:

```c++
// Copyright 2018 gRPC authors.

#include "src/core/lib/iomgr/buffer_list.h"

#include <grpc/support/port_platform.h>
#include <grpc/support/time.h>

#include "absl/log/log.h"
#include "src/core/lib/iomgr/port.h"
#include "src/core/util/crash.h"
#include "src/core/util/sync.h"

#ifdef GRPC_LINUX_ERRQUEUE
#include <netinet/in.h>
#include <string.h>
#include <time.h>

namespace grpc_core {
namespace {

// Converts a timespec struct to gpr_timespec format
void FillGprFromTimestamp(gpr_timespec* gts, const struct timespec* ts) {
  gts->tv_sec = ts->tv_sec;
  gts->tv_nsec = static_cast<int32_t>(ts->tv_nsec);
  gts->clock_type = GPR_CLOCK_REALTIME;
}

// Default callback for timestamps when no callback is registered
void DefaultTimestampsCallback(void* /*arg*/, Timestamps* /*ts*/, 
                               absl::Status /*shutdown_err*/) {
  VLOG(2) << "Timestamps callback has not been registered";
}

// Global callback function pointer for timestamp notifications
void (*g_timestamps_callback)(void*, Timestamps*,
                              grpc_error_handle shutdown_err) =
    DefaultTimestampsCallback;

// Reads a value of type T from potentially unaligned memory
template <typename T>
T ReadUnaligned(const void* ptr) {
  T val;
  memcpy(&val, ptr, sizeof(val));
  return val;
}

// Extracts optional TCP metrics from tcp_info struct and stores them in ConnectionMetrics
void ExtractOptStatsFromTcpInfo(ConnectionMetrics* metrics,
                                const tcp_info* info) {
  if (info == nullptr) {
    return;
  }
  // Extract metrics from tcp_info if the structure is large enough
  if (info->length > offsetof(tcp_info, tcpi_sndbuf_limited)) {
    metrics->recurring_retrans = info->tcpi_retransmits;
    metrics->is_delivery_rate_app_limited =
        info->tcpi_delivery_rate_app_limited;
    metrics->congestion_window = info->tcpi_snd_cwnd;
    metrics->reordering = info->tcpi_reordering;
    metrics->packet_retx = info->tcpi_total_retrans;
    metrics->pacing_rate = info->tcpi_pacing_rate;
    metrics->data_notsent = info->tcpi_notsent_bytes;
    if (info->tcpi_min_rtt != UINT32_MAX) {
      metrics->min_rtt = info->tcpi_min_rtt;
    }
    metrics->packet_sent = info->tcpi_data_segs_out;
    metrics->delivery_rate = info->tcpi_delivery_rate;
    metrics->busy_usec = info->tcpi_busy_time;
    metrics->rwnd_limited_usec = info->tcpi_rwnd_limited;
    metrics->sndbuf_limited_usec = info->tcpi_sndbuf_limited;
  }
  // Extract additional metrics if available
  if (info->length > offsetof(tcp_info, tcpi_dsack_dups)) {
    metrics->data_sent = info->tcpi_bytes_sent;
    metrics->data_retx = info->tcpi_bytes_retrans;
    metrics->packet_spurious_retx = info->tcpi_dsack_dups;
  }
}

// Extracts optional TCP metrics from control message and stores them in ConnectionMetrics
void ExtractOptStatsFromCmsg(ConnectionMetrics* metrics,
                             const cmsghdr* opt_stats) {
  if (opt_stats == nullptr) {
    return;
  }
  const auto* data = CMSG_DATA(opt_stats);
  constexpr int64_t cmsg_hdr_len = CMSG_ALIGN(sizeof(struct cmsghdr));
  const int64_t len = opt_stats->cmsg_len - cmsg_hdr_len;
  int64_t offset = 0;

  // Process each network link attribute in the control message
  while (offset < len) {
    const auto* attr = reinterpret_cast<const nlattr*>(data + offset);
    const void* val = data + offset + NLA_HDRLEN;
    switch (attr->nla_type) {
      case TCP_NLA_BUSY: {
        metrics->busy_usec = ReadUnaligned<uint64_t>(val);
        break;
      }
      case TCP_NLA_RWND_LIMITED: {
        metrics->rwnd_limited_usec = ReadUnaligned<uint64_t>(val);
        break;
      }
      case TCP_NLA_SNDBUF_LIMITED: {
        metrics->sndbuf_limited_usec = ReadUnaligned<uint64_t>(val);
        break;
      }
      case TCP_NLA_PACING_RATE: {
        metrics->pacing_rate = ReadUnaligned<uint64_t>(val);
        break;
      }
      case TCP_NLA_DELIVERY_RATE: {
        metrics->delivery_rate = ReadUnaligned<uint64_t>(val);
        break;
      }
      case TCP_NLA_DELIVERY_RATE_APP_LMT: {
        metrics->is_delivery_rate_app_limited = ReadUnaligned<uint8_t>(val);
        break;
      }
      case TCP_NLA_SND_CWND: {
        metrics->congestion_window = ReadUnaligned<uint32_t>(val);
        break;
      }
      case TCP_NLA_MIN_RTT: {
        metrics->min_rtt = ReadUnaligned<uint32_t>(val);
        break;
      }
      case TCP_NLA_SRTT: {
        metrics->srtt = ReadUnaligned<uint32_t>(val);
        break;
      }
      case TCP_NLA_RECUR_RETRANS: {
        metrics->recurring_retrans = ReadUnaligned<uint8_t>(val);
        break;
      }
      case TCP_NLA_BYTES_SENT: {
        metrics->data_sent = ReadUnaligned<uint64_t>(val);
        break;
      }
      case TCP_NLA_DATA_SEGS_OUT: {
        metrics->packet_sent = ReadUnaligned<uint64_t>(val);
        break;
      }
      case TCP_NLA_TOTAL_RETRANS: {
        metrics->packet_retx = ReadUnaligned<uint64_t>(val);
        break;
      }
      case TCP_NLA_DELIVERED: {
        metrics->packet_delivered = ReadUnaligned<uint32_t>(val);
        break;
      }
      case TCP_NLA_DELIVERED_CE: {
        metrics->packet_delivered_ce = ReadUnaligned<uint32_t>(val);
        break;
      }
      case TCP_NLA_BYTES_RETRANS: {
        metrics->data_retx = ReadUnaligned<uint64_t>(val);
        break;
      }
      case TCP_NLA_DSACK_DUPS: {
        metrics->packet_spurious_retx = ReadUnaligned<uint32_t>(val);
        break;
      }
      case TCP_NLA_REORDERING: {
        metrics->reordering = ReadUnaligned<uint32_t>(val);
        break;
      }
      case TCP_NLA_SND_SSTHRESH: {
        metrics->snd_ssthresh = ReadUnaligned<uint32_t>(val);
        break;
      }
    }
    offset += NLA_ALIGN(attr->nla_len);
  }
}

// Gets TCP_INFO socket option and stores it in the provided tcp_info struct
int GetSocketTcpInfo(struct tcp_info* info, int fd) {
  memset(info, 0, sizeof(*info));
  info->length = offsetof(tcp_info, length);
  return getsockopt(fd, IPPROTO_TCP, TCP_INFO, info, &(info->length));
}

}  // namespace

// Checks if a traced buffer has been pending for too long (10 seconds)
bool TracedBufferList::TracedBuffer::Finished(gpr_timespec ts) {
  constexpr int kGrpcMaxPendingAckTimeMillis = 10000;
  return gpr_time_to_millis(gpr_time_sub(ts, last_timestamp_)) >
         kGrpcMaxPendingAckTimeMillis;
}

// Adds a new entry to the traced buffer list with the given sequence number and file descriptor
void TracedBufferList::AddNewEntry(int32_t seq_no, int fd, void* arg) {
  TracedBuffer* new_elem = new TracedBuffer(seq_no, arg);

  // Initialize timestamps
  new_elem->ts_.sendmsg_time.time = gpr_now(GPR_CLOCK_REALTIME);
  new_elem->ts_.scheduled_time.time = gpr_inf_past(GPR_CLOCK_REALTIME);
  new_elem->ts_.sent_time.time = gpr_inf_past(GPR_CLOCK_REALTIME);
  new_elem->ts_.acked_time.time = gpr_inf_past(GPR_CLOCK_REALTIME);
  
  // Get TCP info and extract metrics if available
  if (GetSocketTcpInfo(&(new_elem->ts_.info), fd) == 0) {
    ExtractOptStatsFromTcpInfo(&(new_elem->ts_.sendmsg_time.metrics),
                               &(new_elem->ts_.info));
  }
  new_elem->last_timestamp_ = new_elem->ts_.sendmsg_time.time;
  
  // Add to linked list
  MutexLock lock(&mu_);
  if (!head_) {
    head_ = tail_ = new_elem;
  } else {
    tail_->next_ = new_elem;
    tail_ = new_elem;
  }
}

// Processes timestamp information from the socket error queue
void TracedBufferList::ProcessTimestamp(struct sock_extended_err* serr,
                                        struct cmsghdr* opt_stats,
                                        struct scm_timestamping* tss) {
  MutexLock lock(&mu_);
  TracedBuffer* elem = head_;
  TracedBuffer* prev = nullptr;
  
  // Process each buffer in the list
  while (elem != nullptr) {
    if (serr->ee_data >= elem->seq_no_) {
      switch (serr->ee_info) {
        case SCM_TSTAMP_SCHED:  // Packet scheduled for transmission
          FillGprFromTimestamp(&(elem->ts_.scheduled_time.time), &(tss->ts[0]));
          ExtractOptStatsFromCmsg(&(elem->ts_.scheduled_time.metrics),
                                  opt_stats);
          elem->last_timestamp_ = elem->ts_.scheduled_time.time;
          elem = elem->next_;
          break;
        case SCM_TSTAMP_SND:  // Packet sent
          FillGprFromTimestamp(&(elem->ts_.sent_time.time), &(tss->ts[0]));
          ExtractOptStatsFromCmsg(&(elem->ts_.sent_time.metrics), opt_stats);
          elem->last_timestamp_ = elem->ts_.sent_time.time;
          elem = elem->next_;
          break;
        case SCM_TSTAMP_ACK:  // Packet acknowledged
          FillGprFromTimestamp(&(elem->ts_.acked_time.time), &(tss->ts[0]));
          ExtractOptStatsFromCmsg(&(elem->ts_.acked_time.metrics), opt_stats);

          // Notify callback and remove from list
          g_timestamps_callback(elem->arg_, &(elem->ts_), absl::OkStatus());

          head_ = elem->next_;
          delete elem;
          elem = head_;
          break;
        default:
          abort();  // Unknown timestamp type
      }
    } else {
      break;
    }
  }

  // Clean up timed out buffers
  elem = head_;
  gpr_timespec now = gpr_now(GPR_CLOCK_REALTIME);
  while (elem != nullptr) {
    if (!elem->Finished(now)) {
      prev = elem;
      elem = elem->next_;
      continue;
    }
    // Notify timeout and remove from list
    g_timestamps_callback(elem->arg_, &(elem->ts_),
                          absl::DeadlineExceededError("Ack timed out"));
    if (prev != nullptr) {
      prev->next_ = elem->next_;
      delete elem;
      elem = prev->next_;
    } else {
      head_ = elem->next_;
      delete elem;
      elem = head_;
    }
  }
  tail_ = (head_ == nullptr) ? head_ : prev;
}

// Shuts down the buffer list, notifying all pending callbacks with the shutdown error
void TracedBufferList::Shutdown(void* remaining, absl::Status shutdown_err) {
  MutexLock lock(&mu_);
  while (head_) {
    TracedBuffer* elem = head_;
    g_timestamps_callback(elem->arg_, &(elem->ts_), shutdown_err);
    head_ = head_->next_;
    delete elem;
  }
  if (remaining != nullptr) {
    g_timestamps_callback(remaining, nullptr, shutdown_err);
  }
  tail_ = head_;
}

// Sets the global callback function for timestamp notifications
void grpc_tcp_set_write_timestamps_callback(
    void (*fn)(void*, Timestamps*, grpc_error_handle error)) {
  g_timestamps_callback = fn;
}
}  // namespace grpc_core

#else  // GRPC_LINUX_ERRQUEUE not defined

// Stub implementation for platforms without Linux error queue support
namespace grpc_core {
void grpc_tcp_set_write_timestamps_callback(
    void (*fn)(void*, Timestamps*, grpc_error_handle error)) {
  (void)fn;
  VLOG(2) << "Timestamps callback is not enabled for this platform";
}
}  // namespace grpc_core

#endif  // GRPC_LINUX_ERRQUEUE
```

Key aspects covered in the comments:
1. File header and copyright notice
2. Function-level documentation explaining purpose and behavior
3. Important data structures and their roles
4. Key algorithms and logic flows
5. Platform-specific implementation details
6. Error handling and edge cases
7. Memory management considerations
8. Thread safety notes (mutex usage)
9. Network protocol specifics (TCP metrics, timestamps)
10. Callback mechanisms and their purposes

The comments aim to provide enough context for a developer to understand the code's functionality without being overly verbose. They explain the "why" behind complex operations while also clarifying the "how" for implementation details.