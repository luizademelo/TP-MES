Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

// Includes necessary headers for gRPC HTTP/2 transport implementation
#include <grpc/event_engine/event_engine.h>
#include <grpc/slice_buffer.h>
#include <grpc/support/port_platform.h>
#include <grpc/support/time.h>
#include <inttypes.h>
#include <stddef.h>

#include <algorithm>
#include <limits>
#include <memory>
#include <optional>
#include <string>
#include <utility>

// Includes various gRPC core and HTTP/2 transport implementation headers
#include "absl/container/flat_hash_map.h"
#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/status/status.h"
#include "src/core/call/metadata_batch.h"
#include "src/core/channelz/channelz.h"
#include "src/core/ext/transport/chttp2/transport/call_tracer_wrapper.h"
#include "src/core/ext/transport/chttp2/transport/chttp2_transport.h"
#include "src/core/ext/transport/chttp2/transport/flow_control.h"
#include "src/core/ext/transport/chttp2/transport/frame_data.h"
#include "src/core/ext/transport/chttp2/transport/frame_ping.h"
#include "src/core/ext/transport/chttp2/transport/frame_rst_stream.h"
#include "src/core/ext/transport/chttp2/transport/frame_settings.h"
#include "src/core/ext/transport/chttp2/transport/frame_window_update.h"
#include "src/core/ext/transport/chttp2/transport/hpack_encoder.h"
#include "src/core/ext/transport/chttp2/transport/http2_settings.h"
#include "src/core/ext/transport/chttp2/transport/http2_status.h"
#include "src/core/ext/transport/chttp2/transport/http2_ztrace_collector.h"
#include "src/core/ext/transport/chttp2/transport/internal.h"
#include "src/core/ext/transport/chttp2/transport/legacy_frame.h"
#include "src/core/ext/transport/chttp2/transport/ping_callbacks.h"
#include "src/core/ext/transport/chttp2/transport/ping_rate_policy.h"
#include "src/core/ext/transport/chttp2/transport/stream_lists.h"
#include "src/core/ext/transport/chttp2/transport/write_size_policy.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/lib/experiments/experiments.h"
#include "src/core/lib/iomgr/endpoint.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/lib/slice/slice.h"
#include "src/core/lib/slice/slice_buffer.h"
#include "src/core/lib/transport/bdp_estimator.h"
#include "src/core/lib/transport/transport.h"
#include "src/core/telemetry/call_tracer.h"
#include "src/core/telemetry/context_list_entry.h"
#include "src/core/telemetry/stats.h"
#include "src/core/telemetry/stats_data.h"
#include "src/core/util/match.h"
#include "src/core/util/ref_counted.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/shared_bit_gen.h"
#include "src/core/util/time.h"
#include "src/core/util/useful.h"

using grpc_core::http2::Http2ErrorCode;

// Adds a write callback to the linked list of callbacks
static void add_to_write_list(grpc_chttp2_write_cb** list,
                              grpc_chttp2_write_cb* cb) {
  cb->next = *list;
  *list = cb;
}

// Completes a write callback and returns it to the pool
static void finish_write_cb(grpc_chttp2_transport* t, grpc_chttp2_write_cb* cb,
                            grpc_error_handle error) {
  grpc_chttp2_complete_closure_step(t, &cb->closure, error, "finish_write_cb");
  cb->next = t->write_cb_pool;
  t->write_cb_pool = cb;
}

// Calculates the next allowed ping interval based on transport state
static grpc_core::Duration NextAllowedPingInterval(grpc_chttp2_transport* t) {
  if (t->is_client) {
    return (t->keepalive_permit_without_calls == 0 && t->stream_map.empty())
               ? grpc_core::Duration::Hours(2)  // No calls allowed - long interval
               : grpc_core::Duration::Seconds(1);  // Normal interval
  }
  if (t->sent_goaway_state != GRPC_CHTTP2_GRACEFUL_GOAWAY) {
    if (grpc_core::IsMultipingEnabled()) {
      return grpc_core::Duration::Seconds(1);
    }
    return t->keepalive_time == grpc_core::Duration::Infinity()
               ? grpc_core::Duration::Seconds(20)  // Default server interval
               : t->keepalive_time / 2;  // Half of configured keepalive time
  }
  return grpc_core::Duration::Zero();  // In graceful GOAWAY - no pings
}

// Initiates a ping if one is requested and allowed by rate policy
static void maybe_initiate_ping(grpc_chttp2_transport* t) {
  if (!t->ping_callbacks.ping_requested()) {
    return;  // No ping requested
  }

  grpc_core::ExecCtx::Get()->InvalidateNow();
  Match(
      t->ping_rate_policy.RequestSendPing(NextAllowedPingInterval(t),
                                          t->ping_callbacks.pings_inflight()),
      [t](grpc_core::Chttp2PingRatePolicy::SendGranted) {
        // Ping granted - send it
        t->ping_rate_policy.SentPing();
        grpc_core::SharedBitGen g;
        const uint64_t id = t->ping_callbacks.StartPing(g);
        t->http2_ztrace_collector.Append(
            grpc_core::H2PingTrace<false>{false, id});
        grpc_slice_buffer_add(t->outbuf.c_slice_buffer(),
                              grpc_chttp2_ping_create(false, id));
        t->keepalive_incoming_data_wanted = true;
        if (t->channelz_socket != nullptr) {
          t->channelz_socket->RecordKeepaliveSent();
        }
        grpc_core::global_stats().IncrementHttp2PingsSent();
        if (GRPC_TRACE_FLAG_ENABLED(http) ||
            GRPC_TRACE_FLAG_ENABLED(bdp_estimator) ||
            GRPC_TRACE_FLAG_ENABLED(http_keepalive) ||
            GRPC_TRACE_FLAG_ENABLED(http2_ping)) {
          LOG(INFO) << (t->is_client ? "CLIENT" : "SERVER") << "[" << t
                    << "]: Ping " << id << " sent ["
                    << std::string(t->peer_string.as_string_view())
                    << "]: " << t->ping_rate_policy.GetDebugString();
        }
      },
      [t](grpc_core::Chttp2PingRatePolicy::TooManyRecentPings) {
        // Too many pings recently - log and delay
        if (GRPC_TRACE_FLAG_ENABLED(http) ||
            GRPC_TRACE_FLAG_ENABLED(bdp_estimator) ||
            GRPC_TRACE_FLAG_ENABLED(http_keepalive) ||
            GRPC_TRACE_FLAG_ENABLED(http2_ping)) {
          LOG(INFO) << (t->is_client ? "CLIENT" : "SERVER") << "[" << t
                    << "]: Ping delayed ["
                    << std::string(t->peer_string.as_string_view())
                    << "]: too many recent pings: "
                    << t->ping_rate_policy.GetDebugString();
        }
      },
      [t](grpc_core::Chttp2PingRatePolicy::TooSoon too_soon) {
        // Not enough time since last ping - schedule delayed ping
        if (GRPC_TRACE_FLAG_ENABLED(http) ||
            GRPC_TRACE_FLAG_ENABLED(bdp_estimator) ||
            GRPC_TRACE_FLAG_ENABLED(http_keepalive) ||
            GRPC_TRACE_FLAG_ENABLED(http2_ping)) {
          LOG(INFO) << (t->is_client ? "CLIENT" : "SERVER") << "[" << t
                    << "]: Ping delayed ["
                    << std::string(t->peer_string.as_string_view())
                    << "]: not enough time elapsed since last "
                       "ping. Last ping:"
                    << too_soon.last_ping
                    << ", minimum wait:" << too_soon.next_allowed_ping_interval
                    << ", need to wait:" << too_soon.wait;
        }
        if (t->delayed_ping_timer_handle ==
            grpc_event_engine::experimental::EventEngine::TaskHandle::
                kInvalid) {
          t->delayed_ping_timer_handle = t->event_engine->RunAfter(
              too_soon.wait, [t = t->Ref()]() mutable {
                grpc_core::ExecCtx exec_ctx;
                grpc_chttp2_retry_initiate_ping(std::move(t));
              });
        }
      });
}

// Updates a list of write callbacks, executing those that are ready
static bool update_list(grpc_chttp2_transport* t, int64_t send_bytes,
                        grpc_chttp2_write_cb** list, int64_t* ctr,
                        grpc_error_handle error) {
  bool sched_any = false;
  grpc_chttp2_write_cb* cb = *list;
  *list = nullptr;
  *ctr += send_bytes;
  while (cb) {
    grpc_chttp2_write_cb* next = cb->next;
    if (cb->call_at_byte <= *ctr) {
      sched_any = true;
      finish_write_cb(t, cb, error);
    } else {
      add_to_write_list(list, cb);
    }
    cb = next;
  }
  return sched_any;
}

// Reports flow control stall information for debugging
static void report_stall(grpc_chttp2_transport* t, grpc_chttp2_stream* s,
                         const char* staller) {
  GRPC_TRACE_VLOG(flowctl, 2)
      << t->peer_string.as_string_view() << ":" << t << " stream " << s->id
      << " moved to stalled list by " << staller
      << ". This is FULLY expected to happen in a healthy program that is not "
         "seeing flow control stalls. However, if you know that there are "
         "unwanted stalls, here is some helpful data: [fc:pending="
      << s->flow_controlled_buffer.length
      << ":flowed=" << s->flow_controlled_bytes_flowed
      << ":peer_initwin=" << t->settings.acked().initial_window_size()
      << ":t_win=" << t->flow_control.remote_window() << ":s_win="
      << static_cast<uint32_t>(std::max(
             int64_t{0}, s->flow_control.remote_window_delta() +
                             static_cast<int64_t>(
                                 t->settings.peer().initial_window_size())))
      << ":s_delta=" << s->flow_control.remote_window_delta() << "]";
}

namespace {

// Helper class to count default metadata entries
class CountDefaultMetadataEncoder {
 public:
  size_t count() const { return count_; }

  void Encode(const grpc_core::Slice&, const grpc_core::Slice&) {}

  template <typename Which>
  void Encode(Which, const typename Which::ValueType&) {
    count_++;
  }

 private:
  size_t count_ = 0;
};

}

// Checks if metadata contains only default values
static bool is_default_initial_metadata(grpc_metadata_batch* initial_metadata) {
  CountDefaultMetadataEncoder enc;
  initial_metadata->Encode(&enc);
  return enc.count() == initial_metadata->count();
}

namespace {

// Context for managing a write operation
class WriteContext {
 public:
  explicit WriteContext(grpc_chttp2_transport* t) : t_(t) {
    t->http2_stats.IncrementHttp2WritesBegun();
    t->http2_stats.IncrementHttp2WriteTargetSize(target_write_size_);
  }

  // Flushes pending settings updates
  void FlushSettings() {
    auto update = t_->settings.MaybeSendUpdate();
    if (update.has_value()) {
      t_->http2_ztrace_collector.Append([&update]() {
        return grpc_core::H2SettingsTrace<false>{false, update->settings};
      });
      grpc_core::Http2Frame frame(std::move(*update));
      Serialize(absl::Span<grpc_core::Http2Frame>(&frame, 1), t_->outbuf);
      if (t_->keepalive_timeout != grpc_core::Duration::Infinity()) {
        CHECK(
            t_->settings_ack_watchdog ==
            grpc_event_engine::experimental::EventEngine::TaskHandle::kInvalid);

        t_->settings_ack_watchdog = t_->event_engine->RunAfter(
            t_->settings_timeout, [t = t_->Ref()]() mutable {
              grpc_core::ExecCtx exec_ctx;
              grpc_chttp2_settings_timeout(std::move(t));
            });
      }
      t_->flow_control.FlushedSettings();
      grpc_core::global_stats().IncrementHttp2SettingsWrites();
    }
  }

  // Flushes queued buffers to the output
  void FlushQueuedBuffers() {
    grpc_slice_buffer_move_into(&t_->qbuf, t_->outbuf.c_slice_buffer());
    t_->num_pending_induced_frames = 0;
    CHECK_EQ(t_->qbuf.count, 0u);
  }

  // Flushes window updates for the transport
  void FlushWindowUpdates() {
    uint32_t transport_announce = t_->flow_control.MaybeSendUpdate(
        t_->outbuf.c_slice_buffer()->count > 0);
    if (transport_announce) {
      t_->http2_ztrace_collector.Append(
          grpc_core::H2WindowUpdateTrace<false>{0, transport_announce});
      grpc_slice_buffer_add(
          t_->outbuf.c_slice_buffer(),
          grpc_chttp2_window_update_create(0, transport_announce, nullptr));
      grpc_chttp2_reset_ping_clock(t_);
    }
  }

  // Flushes ping acknowledgements
  void FlushPingAcks() {
    if (t_->ping_ack_count == 0) return;

    target_write_size_ = 0;
    for (size_t i = 0; i < t_->ping_ack_count; i++) {
      t_->http2_ztrace_collector.Append(
          grpc_core::H2PingTrace<false>{true, t_->ping_acks[i]});
      grpc_slice_buffer_add(t_->outbuf.c_slice_buffer(),
                            grpc_chttp2_ping_create(true, t_->ping_acks[i]));
    }
    t_->ping_ack_count = 0;
  }

  // Applies HPACK settings changes
  void EnactHpackSettings() {
    t_->hpack_compressor.SetMaxTableSize(
        t_->settings.peer().header_table_size());
  }

  // Moves streams from stalled to writable list if flow control allows
  void UpdateStreamsNoLongerStalled() {
    grpc_chttp2_stream* s;
    while (grpc_chttp2_list_pop_stalled_by_transport(t_, &s)) {
      if (t_->closed_with_error.ok() &&
          grpc_chttp2_list_add_writable_stream(t_, s)) {
        if (!s->refcount->refs.RefIfNonZero()) {
          grpc_chttp2_list_remove_writable_stream(t_, s);
        }
      }
    }
  }

  // Gets the next stream to write, respecting target write size
  grpc_chttp2_stream* NextStream() {
    if (t_->outbuf.c_slice_buffer()->length > target_write_size_) {
      result_.partial = true;
      return nullptr;
    }

    grpc_chttp2_stream* s;
    if (!grpc_chttp2_list_pop_writable_stream(t_, &s)) {
      return nullptr;
    }

    return s;
  }

  // Metrics tracking
  void IncInitialMetadataWrites() { ++initial_metadata_writes_; }
  void IncWindowUpdateWrites() { ++flow_control_writes_; }
  void IncMessageWrites() { ++message_writes_; }
  void IncTrailingMetadataWrites() { ++trailing_metadata_writes_; }

  void NoteScheduledResults() { result_.early_results_scheduled = true; }

  grpc_chttp2_transport* transport() const { return t_; }

  // Returns the result of the write operation
  grpc_chttp2_begin_write_result Result() {
    result_.writing = t_->outbuf.c_slice_buffer()->count > 0;
    return result_;
  }

  size_t target_write_size() const { return target_write_size_; }

 private:
  grpc_chttp2_transport* const t_;
  size_t target_write_size_ = t_->write_size_policy.WriteTargetSize();

  // Counters for different frame types written
  int flow_control_writes_ = 0;
  int initial_metadata_writes_ = 0;
  int trailing_metadata_writes_ = 0;
  int message_writes_ = 0;
  grpc_chttp2_begin_write_result result_ = {false, false, false};
};

// Context for managing data frame sending
class DataSendContext {
 public:
  DataSendContext(WriteContext* write_context, grpc_chttp2_transport* t,
                  grpc_chttp2_stream* s)
      : write_context_(write_context),
        t_(t),
        s_(s),
        sending_bytes_before_(s_->sending_bytes) {}

  // Calculates available stream window size
  uint32_t