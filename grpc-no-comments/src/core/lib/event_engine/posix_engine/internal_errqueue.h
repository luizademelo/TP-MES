// Copyright 2022 The gRPC Authors

#ifndef GRPC_SRC_CORE_LIB_EVENT_ENGINE_POSIX_ENGINE_INTERNAL_ERRQUEUE_H
#define GRPC_SRC_CORE_LIB_EVENT_ENGINE_POSIX_ENGINE_INTERNAL_ERRQUEUE_H

#include <grpc/support/port_platform.h>
#include <stdint.h>

#include "src/core/lib/iomgr/port.h"

#ifdef GRPC_POSIX_SOCKET_TCP

#include <time.h>

#ifdef GRPC_LINUX_ERRQUEUE
#include <linux/errqueue.h>
#include <sys/socket.h>
#endif

namespace grpc_event_engine::experimental {

#ifdef GRPC_LINUX_ERRQUEUE

struct scm_timestamping {
  struct timespec ts[3];
};

constexpr int SCM_TSTAMP_SND = 0;

constexpr int SCM_TSTAMP_SCHED = 1;

constexpr int SCM_TSTAMP_ACK = 2;

#ifndef SCM_TIMESTAMPING_OPT_STATS
#define SCM_TIMESTAMPING_OPT_STATS 54
#endif

constexpr uint32_t SOF_TIMESTAMPING_TX_SOFTWARE = 1u << 1;
constexpr uint32_t SOF_TIMESTAMPING_SOFTWARE = 1u << 4;
constexpr uint32_t SOF_TIMESTAMPING_OPT_ID = 1u << 7;
constexpr uint32_t SOF_TIMESTAMPING_TX_SCHED = 1u << 8;
constexpr uint32_t SOF_TIMESTAMPING_TX_ACK = 1u << 9;
constexpr uint32_t SOF_TIMESTAMPING_OPT_TSONLY = 1u << 11;
constexpr uint32_t SOF_TIMESTAMPING_OPT_STATS = 1u << 12;

constexpr uint32_t kTimestampingSocketOptions =
    SOF_TIMESTAMPING_SOFTWARE | SOF_TIMESTAMPING_OPT_ID |
    SOF_TIMESTAMPING_OPT_TSONLY | SOF_TIMESTAMPING_OPT_STATS;
constexpr uint32_t kTimestampingRecordingOptions =
    SOF_TIMESTAMPING_TX_SCHED | SOF_TIMESTAMPING_TX_SOFTWARE |
    SOF_TIMESTAMPING_TX_ACK;

enum TCPOptStats {
  TCP_NLA_PAD,
  TCP_NLA_BUSY,
  TCP_NLA_RWND_LIMITED,
  TCP_NLA_SNDBUF_LIMITED,
  TCP_NLA_DATA_SEGS_OUT,
  TCP_NLA_TOTAL_RETRANS,
  TCP_NLA_PACING_RATE,
  TCP_NLA_DELIVERY_RATE,
  TCP_NLA_SND_CWND,
  TCP_NLA_REORDERING,
  TCP_NLA_MIN_RTT,
  TCP_NLA_RECUR_RETRANS,
  TCP_NLA_DELIVERY_RATE_APP_LMT,
  TCP_NLA_SNDQ_SIZE,
  TCP_NLA_CA_STATE,
  TCP_NLA_SND_SSTHRESH,
  TCP_NLA_DELIVERED,
  TCP_NLA_DELIVERED_CE,
  TCP_NLA_BYTES_SENT,
  TCP_NLA_BYTES_RETRANS,
  TCP_NLA_DSACK_DUPS,
  TCP_NLA_REORD_SEEN,
  TCP_NLA_SRTT,
};

struct tcp_info {
  uint8_t tcpi_state;
  uint8_t tcpi_ca_state;
  uint8_t tcpi_retransmits;
  uint8_t tcpi_probes;
  uint8_t tcpi_backoff;
  uint8_t tcpi_options;
  uint8_t tcpi_snd_wscale : 4, tcpi_rcv_wscale : 4;
  uint8_t tcpi_delivery_rate_app_limited : 1;
  uint32_t tcpi_rto;
  uint32_t tcpi_ato;
  uint32_t tcpi_snd_mss;
  uint32_t tcpi_rcv_mss;
  uint32_t tcpi_unacked;
  uint32_t tcpi_sacked;
  uint32_t tcpi_lost;
  uint32_t tcpi_retrans;
  uint32_t tcpi_fackets;

  uint32_t tcpi_last_data_sent;
  uint32_t tcpi_last_ack_sent;
  uint32_t tcpi_last_data_recv;
  uint32_t tcpi_last_ack_recv;

  uint32_t tcpi_pmtu;
  uint32_t tcpi_rcv_ssthresh;
  uint32_t tcpi_rtt;
  uint32_t tcpi_rttvar;
  uint32_t tcpi_snd_ssthresh;
  uint32_t tcpi_snd_cwnd;
  uint32_t tcpi_advmss;
  uint32_t tcpi_reordering;
  uint32_t tcpi_rcv_rtt;
  uint32_t tcpi_rcv_space;
  uint32_t tcpi_total_retrans;
  uint64_t tcpi_pacing_rate;
  uint64_t tcpi_max_pacing_rate;
  uint64_t tcpi_bytes_acked;
  uint64_t tcpi_bytes_received;

  uint32_t tcpi_segs_out;
  uint32_t tcpi_segs_in;
  uint32_t tcpi_notsent_bytes;
  uint32_t tcpi_min_rtt;

  uint32_t tcpi_data_segs_in;
  uint32_t tcpi_data_segs_out;

  uint64_t tcpi_delivery_rate;
  uint64_t tcpi_busy_time;
  uint64_t tcpi_rwnd_limited;
  uint64_t tcpi_sndbuf_limited;

  uint32_t tcpi_delivered;
  uint32_t tcpi_delivered_ce;
  uint64_t tcpi_bytes_sent;
  uint64_t tcpi_bytes_retrans;
  uint32_t tcpi_dsack_dups;
  uint32_t tcpi_reord_seen;
  socklen_t length;
};

#ifndef TCP_INFO
#define TCP_INFO 11
#endif

int GetSocketTcpInfo(tcp_info* info, int fd);

#endif

bool KernelSupportsErrqueue();

}

#endif

#endif
