// Copyright 2022 The gRPC Authors

#include "src/core/lib/event_engine/posix_engine/traced_buffer_list.h"

#include <grpc/support/port_platform.h>
#include <grpc/support/time.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <utility>

#include "absl/functional/any_invocable.h"
#include "absl/log/log.h"
#include "src/core/lib/iomgr/port.h"
#include "src/core/util/sync.h"

#ifdef GRPC_LINUX_ERRQUEUE
#include <linux/errqueue.h>
#include <linux/netlink.h>
#include <sys/socket.h>

namespace grpc_event_engine::experimental {

namespace {

void FillGprFromTimestamp(gpr_timespec* gts, const struct timespec* ts) {
  gts->tv_sec = ts->tv_sec;
  gts->tv_nsec = static_cast<int32_t>(ts->tv_nsec);
  gts->clock_type = GPR_CLOCK_REALTIME;
}

void DefaultTimestampsCallback(void* , Timestamps* ,
                               absl::Status ) {
  VLOG(2) << "Timestamps callback has not been registered";
}

absl::AnyInvocable<void(void*, Timestamps*, absl::Status)>
    g_timestamps_callback =
        []() -> absl::AnyInvocable<void(void*, Timestamps*, absl::Status)> {
  return DefaultTimestampsCallback;
}();

template <typename T>
T ReadUnaligned(const void* ptr) {
  T val;
  memcpy(&val, ptr, sizeof(val));
  return val;
}

void ExtractOptStatsFromTcpInfo(ConnectionMetrics* metrics,
                                const tcp_info* info) {
  if (info == nullptr) {
    return;
  }
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
  if (info->length > offsetof(tcp_info, tcpi_dsack_dups)) {
    metrics->data_sent = info->tcpi_bytes_sent;
    metrics->data_retx = info->tcpi_bytes_retrans;
    metrics->packet_spurious_retx = info->tcpi_dsack_dups;
  }
}

void ExtractOptStatsFromCmsg(ConnectionMetrics* metrics,
                             const cmsghdr* opt_stats) {
  if (opt_stats == nullptr) {
    return;
  }
  const auto* data = CMSG_DATA(opt_stats);
  constexpr int64_t cmsg_hdr_len = CMSG_ALIGN(sizeof(struct cmsghdr));
  const int64_t len = opt_stats->cmsg_len - cmsg_hdr_len;
  int64_t offset = 0;

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
}

bool TracedBufferList::TracedBuffer::Finished(gpr_timespec ts) {
  constexpr int kGrpcMaxPendingAckTimeMillis = 10000;
  return gpr_time_to_millis(gpr_time_sub(ts, last_timestamp_)) >
         kGrpcMaxPendingAckTimeMillis;
}

void TracedBufferList::AddNewEntry(int32_t seq_no, int fd, void* arg) {
  TracedBuffer* new_elem = new TracedBuffer(seq_no, arg);

  new_elem->ts_.sendmsg_time.time = gpr_now(GPR_CLOCK_REALTIME);
  new_elem->ts_.scheduled_time.time = gpr_inf_past(GPR_CLOCK_REALTIME);
  new_elem->ts_.sent_time.time = gpr_inf_past(GPR_CLOCK_REALTIME);
  new_elem->ts_.acked_time.time = gpr_inf_past(GPR_CLOCK_REALTIME);
  if (GetSocketTcpInfo(&(new_elem->ts_.info), fd) == 0) {
    ExtractOptStatsFromTcpInfo(&(new_elem->ts_.sendmsg_time.metrics),
                               &(new_elem->ts_.info));
  }
  new_elem->last_timestamp_ = new_elem->ts_.sendmsg_time.time;
  grpc_core::MutexLock lock(&mu_);
  if (!head_) {
    head_ = tail_ = new_elem;
  } else {
    tail_->next_ = new_elem;
    tail_ = new_elem;
  }
}

void TracedBufferList::ProcessTimestamp(struct sock_extended_err* serr,
                                        struct cmsghdr* opt_stats,
                                        struct scm_timestamping* tss) {
  grpc_core::MutexLock lock(&mu_);
  TracedBuffer* elem = head_;
  TracedBuffer* prev = nullptr;
  while (elem != nullptr) {

    if (serr->ee_data >= elem->seq_no_) {
      switch (serr->ee_info) {
        case SCM_TSTAMP_SCHED:
          FillGprFromTimestamp(&(elem->ts_.scheduled_time.time), &(tss->ts[0]));
          ExtractOptStatsFromCmsg(&(elem->ts_.scheduled_time.metrics),
                                  opt_stats);
          elem->last_timestamp_ = elem->ts_.scheduled_time.time;
          elem = elem->next_;
          break;
        case SCM_TSTAMP_SND:
          FillGprFromTimestamp(&(elem->ts_.sent_time.time), &(tss->ts[0]));
          ExtractOptStatsFromCmsg(&(elem->ts_.sent_time.metrics), opt_stats);
          elem->last_timestamp_ = elem->ts_.sent_time.time;
          elem = elem->next_;
          break;
        case SCM_TSTAMP_ACK:
          FillGprFromTimestamp(&(elem->ts_.acked_time.time), &(tss->ts[0]));
          ExtractOptStatsFromCmsg(&(elem->ts_.acked_time.metrics), opt_stats);

          g_timestamps_callback(elem->arg_, &(elem->ts_), absl::OkStatus());

          head_ = elem->next_;
          delete elem;
          elem = head_;
          break;
        default:
          abort();
      }
    } else {
      break;
    }
  }

  elem = head_;
  gpr_timespec now = gpr_now(GPR_CLOCK_REALTIME);
  while (elem != nullptr) {
    if (!elem->Finished(now)) {
      prev = elem;
      elem = elem->next_;
      continue;
    }
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

void TracedBufferList::Shutdown(void* remaining, absl::Status shutdown_err) {
  grpc_core::MutexLock lock(&mu_);
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

void TcpSetWriteTimestampsCallback(
    absl::AnyInvocable<void(void*, Timestamps*, absl::Status)> fn) {
  g_timestamps_callback = std::move(fn);
}

}

#else

#include "src/core/util/crash.h"

namespace grpc_event_engine::experimental {

void TcpSetWriteTimestampsCallback(
    absl::AnyInvocable<void(void*, Timestamps*, absl::Status)> ) {
  grpc_core::Crash("Timestamps callback is not enabled for this platform");
}

}

#endif
