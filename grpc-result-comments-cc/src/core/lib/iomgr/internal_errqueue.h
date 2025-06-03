Here's the commented version of the code:

```c++
// Copyright 2018 gRPC authors.

// Header guard to prevent multiple inclusions
#ifndef GRPC_SRC_CORE_LIB_IOMGR_INTERNAL_ERRQUEUE_H
#define GRPC_SRC_CORE_LIB_IOMGR_INTERNAL_ERRQUEUE_H

// Platform-specific support
#include <grpc/support/port_platform.h>

// Include port-specific configuration
#include "src/core/lib/iomgr/port.h"

// Only include this file for POSIX socket TCP implementations
#ifdef GRPC_POSIX_SOCKET_TCP

#include <sys/types.h>
#include <time.h>

// Linux-specific error queue support
#ifdef GRPC_LINUX_ERRQUEUE
#include <linux/errqueue.h>      // Linux error queue definitions
#include <linux/net_tstamp.h>    // Network timestamping
#include <linux/netlink.h>       // Netlink communication
#include <sys/socket.h>          // Socket operations
#endif

namespace grpc_core {

#ifdef GRPC_LINUX_ERRQUEUE

// Structure for storing timestamp information from the kernel
struct scm_timestamping {
  struct timespec ts[3];  // Array of timestamps for different events
};

// Constants for timestamp types
constexpr int SCM_TSTAMP_SND = 0;    // Timestamp when data was sent
constexpr int SCM_TSTAMP_SCHED = 1;  // Timestamp when data was scheduled for transmission
constexpr int SCM_TSTAMP_ACK = 2;    // Timestamp when ACK was received

// Define SCM_TIMESTAMPING_OPT_STATS if not already defined by system headers
#ifndef SCM_TIMESTAMPING_OPT_STATS
#define SCM_TIMESTAMPING_OPT_STATS 54
#endif

// Bitmask flags for socket timestamping options
constexpr uint32_t SOF_TIMESTAMPING_TX_SOFTWARE = 1u << 1;   // SW transmit timestamps
constexpr uint32_t SOF_TIMESTAMPING_SOFTWARE = 1u << 4;      // SW timestamps
constexpr uint32_t SOF_TIMESTAMPING_OPT_ID = 1u << 7;        // Include socket ID
constexpr uint32_t SOF_TIMESTAMPING_TX_SCHED = 1u << 8;      // Scheduled transmit timestamp
constexpr uint32_t SOF_TIMESTAMPING_TX_ACK = 1u << 9;        // ACK transmit timestamp
constexpr uint32_t SOF_TIMESTAMPING_OPT_TSONLY = 1u << 11;   // Only timestamps, no payload
constexpr uint32_t SOF_TIMESTAMPING_OPT_STATS = 1u << 12;    // Include statistics

// Combined socket options for timestamping
constexpr uint32_t kTimestampingSocketOptions =
    SOF_TIMESTAMPING_SOFTWARE | SOF_TIMESTAMPING_OPT_ID |
    SOF_TIMESTAMPING_OPT_TSONLY | SOF_TIMESTAMPING_OPT_STATS;

// Combined options for recording timestamps
constexpr uint32_t kTimestampingRecordingOptions =
    SOF_TIMESTAMPING_TX_SCHED | SOF_TIMESTAMPING_TX_SOFTWARE |
    SOF_TIMESTAMPING_TX_ACK;

// Enumeration of TCP statistics available via TCP_OPT_STATS
enum TCPOptStats {
  TCP_NLA_PAD,                    // Padding
  TCP_NLA_BUSY,                   // Time busy sending data
  TCP_NLA_RWND_LIMITED,           // Time limited by receive window
  TCP_NLA_SNDBUF_LIMITED,         // Time limited by send buffer
  TCP_NLA_DATA_SEGS_OUT,          // Data segments sent
  TCP_NLA_TOTAL_RETRANS,          // Total retransmits
  TCP_NLA_PACING_RATE,            // Current pacing rate
  TCP_NLA_DELIVERY_RATE,          // Current delivery rate
  TCP_NLA_SND_CWND,               // Send congestion window
  TCP_NLA_REORDERING,             // Reordering metric
  TCP_NLA_MIN_RTT,                // Minimum RTT
  TCP_NLA_RECUR_RETRANS,          // Recurring retransmits
  TCP_NLA_DELIVERY_RATE_APP_LMT,  // Application limited flag
  TCP_NLA_SNDQ_SIZE,              // Send queue size
  TCP_NLA_CA_STATE,               // Congestion avoidance state
  TCP_NLA_SND_SSTHRESH,           // Slow start threshold
  TCP_NLA_DELIVERED,              // Packets delivered
  TCP_NLA_DELIVERED_CE,           // Packets delivered with CE marks
  TCP_NLA_BYTES_SENT,             // Bytes sent
  TCP_NLA_BYTES_RETRANS,          // Bytes retransmitted
  TCP_NLA_DSACK_DUPS,             // DSACK blocks received
  TCP_NLA_REORD_SEEN,             // Reordering events seen
  TCP_NLA_SRTT,                   // Smoothed RTT
};

// Structure mirroring Linux's tcp_info for TCP statistics
struct tcp_info {
  // Basic connection information
  uint8_t tcpi_state;
  uint8_t tcpi_ca_state;
  uint8_t tcpi_retransmits;
  uint8_t tcpi_probes;
  uint8_t tcpi_backoff;
  uint8_t tcpi_options;
  uint8_t tcpi_snd_wscale : 4, tcpi_rcv_wscale : 4;
  uint8_t tcpi_delivery_rate_app_limited : 1;

  // Timing information
  uint32_t tcpi_rto;
  uint32_t tcpi_ato;
  uint32_t tcpi_snd_mss;
  uint32_t tcpi_rcv_mss;

  // Packet statistics
  uint32_t tcpi_unacked;
  uint32_t tcpi_sacked;
  uint32_t tcpi_lost;
  uint32_t tcpi_retrans;
  uint32_t tcpi_fackets;

  // Last packet timestamps
  uint32_t tcpi_last_data_sent;
  uint32_t tcpi_last_ack_sent;
  uint32_t tcpi_last_data_recv;
  uint32_t tcpi_last_ack_recv;

  // Path MTU and congestion control
  uint32_t tcpi_pmtu;
  uint32_t tcpi_rcv_ssthresh;
  uint32_t tcpi_rtt;
  uint32_t tcpi_rttvar;
  uint32_t tcpi_snd_ssthresh;
  uint32_t tcpi_snd_cwnd;
  uint32_t tcpi_advmss;
  uint32_t tcpi_reordering;

  // Receiver-side metrics
  uint32_t tcpi_rcv_rtt;
  uint32_t tcpi_rcv_space;
  uint32_t tcpi_total_retrans;

  // Rate metrics
  uint64_t tcpi_pacing_rate;
  uint64_t tcpi_max_pacing_rate;

  // Byte counters
  uint64_t tcpi_bytes_acked;
  uint64_t tcpi_bytes_received;

  // Segment counters
  uint32_t tcpi_segs_out;
  uint32_t tcpi_segs_in;
  uint32_t tcpi_notsent_bytes;
  uint32_t tcpi_min_rtt;

  // Data segment counters
  uint32_t tcpi_data_segs_in;
  uint32_t tcpi_data_segs_out;

  // Delivery metrics
  uint64_t tcpi_delivery_rate;
  uint64_t tcpi_busy_time;
  uint64_t tcpi_rwnd_limited;
  uint64_t tcpi_sndbuf_limited;

  // Additional delivery information
  uint32_t tcpi_delivered;
  uint32_t tcpi_delivered_ce;
  uint64_t tcpi_bytes_sent;
  uint64_t tcpi_bytes_retrans;
  uint32_t tcpi_dsack_dups;
  uint32_t tcpi_reord_seen;
  socklen_t length;  // Length of the structure
};

// Define TCP_INFO if not already defined by system headers
#ifndef TCP_INFO
#define TCP_INFO 11
#endif
#endif  // GRPC_LINUX_ERRQUEUE

// Function declaration to check if kernel supports error queue
bool KernelSupportsErrqueue();

}  // namespace grpc_core

#endif  // GRPC_POSIX_SOCKET_TCP

#endif  // GRPC_SRC_CORE_LIB_IOMGR_INTERNAL_ERRQUEUE_H
```