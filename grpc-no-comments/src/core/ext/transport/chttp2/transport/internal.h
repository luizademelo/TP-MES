
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_EXT_TRANSPORT_CHTTP2_TRANSPORT_INTERNAL_H
#define GRPC_SRC_CORE_EXT_TRANSPORT_CHTTP2_TRANSPORT_INTERNAL_H

#include <grpc/event_engine/event_engine.h>
#include <grpc/event_engine/memory_allocator.h>
#include <grpc/grpc.h>
#include <grpc/slice.h>
#include <grpc/support/port_platform.h>
#include <grpc/support/time.h>
#include <stddef.h>
#include <stdint.h>

#include <atomic>
#include <memory>
#include <optional>
#include <utility>
#include <variant>

#include "absl/container/flat_hash_map.h"
#include "absl/random/random.h"
#include "absl/status/status.h"
#include "absl/strings/string_view.h"
#include "src/core/call/metadata_batch.h"
#include "src/core/channelz/channelz.h"
#include "src/core/ext/transport/chttp2/transport/call_tracer_wrapper.h"
#include "src/core/ext/transport/chttp2/transport/flow_control.h"
#include "src/core/ext/transport/chttp2/transport/frame_goaway.h"
#include "src/core/ext/transport/chttp2/transport/frame_ping.h"
#include "src/core/ext/transport/chttp2/transport/frame_rst_stream.h"
#include "src/core/ext/transport/chttp2/transport/frame_security.h"
#include "src/core/ext/transport/chttp2/transport/frame_settings.h"
#include "src/core/ext/transport/chttp2/transport/frame_window_update.h"
#include "src/core/ext/transport/chttp2/transport/hpack_encoder.h"
#include "src/core/ext/transport/chttp2/transport/hpack_parser.h"
#include "src/core/ext/transport/chttp2/transport/http2_settings.h"
#include "src/core/ext/transport/chttp2/transport/http2_ztrace_collector.h"
#include "src/core/ext/transport/chttp2/transport/internal_channel_arg_names.h"
#include "src/core/ext/transport/chttp2/transport/legacy_frame.h"
#include "src/core/ext/transport/chttp2/transport/ping_abuse_policy.h"
#include "src/core/ext/transport/chttp2/transport/ping_callbacks.h"
#include "src/core/ext/transport/chttp2/transport/ping_rate_policy.h"
#include "src/core/ext/transport/chttp2/transport/write_size_policy.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/lib/iomgr/closure.h"
#include "src/core/lib/iomgr/combiner.h"
#include "src/core/lib/iomgr/endpoint.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/lib/iomgr/iomgr_fwd.h"
#include "src/core/lib/resource_quota/arena.h"
#include "src/core/lib/resource_quota/memory_quota.h"
#include "src/core/lib/slice/slice.h"
#include "src/core/lib/slice/slice_buffer.h"
#include "src/core/lib/surface/init_internally.h"
#include "src/core/lib/transport/connectivity_state.h"
#include "src/core/lib/transport/transport.h"
#include "src/core/lib/transport/transport_framing_endpoint_extension.h"
#include "src/core/telemetry/call_tracer.h"
#include "src/core/telemetry/context_list_entry.h"
#include "src/core/telemetry/stats.h"
#include "src/core/util/bitset.h"
#include "src/core/util/debug_location.h"
#include "src/core/util/ref_counted.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/time.h"

#define CLOSURE_BARRIER_MAY_COVER_WRITE (1 << 0)

#define CLOSURE_BARRIER_FIRST_REF_BIT (1 << 16)

typedef enum {

  GRPC_CHTTP2_LIST_WRITABLE,
  GRPC_CHTTP2_LIST_WRITING,

  GRPC_CHTTP2_LIST_STALLED_BY_TRANSPORT,
  GRPC_CHTTP2_LIST_STALLED_BY_STREAM,

  GRPC_CHTTP2_LIST_WAITING_FOR_CONCURRENCY,
  STREAM_LIST_COUNT
} grpc_chttp2_stream_list_id;

typedef enum {
  GRPC_CHTTP2_WRITE_STATE_IDLE,
  GRPC_CHTTP2_WRITE_STATE_WRITING,
  GRPC_CHTTP2_WRITE_STATE_WRITING_WITH_MORE,
} grpc_chttp2_write_state;

typedef enum {
  GRPC_CHTTP2_OPTIMIZE_FOR_LATENCY,
  GRPC_CHTTP2_OPTIMIZE_FOR_THROUGHPUT,
} grpc_chttp2_optimization_target;

typedef enum {
  GRPC_CHTTP2_PCL_INITIATE = 0,
  GRPC_CHTTP2_PCL_NEXT,
  GRPC_CHTTP2_PCL_INFLIGHT,
  GRPC_CHTTP2_PCL_COUNT
} grpc_chttp2_ping_closure_list;

typedef enum {
  GRPC_CHTTP2_INITIATE_WRITE_INITIAL_WRITE,
  GRPC_CHTTP2_INITIATE_WRITE_START_NEW_STREAM,
  GRPC_CHTTP2_INITIATE_WRITE_SEND_MESSAGE,
  GRPC_CHTTP2_INITIATE_WRITE_SEND_INITIAL_METADATA,
  GRPC_CHTTP2_INITIATE_WRITE_SEND_TRAILING_METADATA,
  GRPC_CHTTP2_INITIATE_WRITE_RETRY_SEND_PING,
  GRPC_CHTTP2_INITIATE_WRITE_CONTINUE_PINGS,
  GRPC_CHTTP2_INITIATE_WRITE_GOAWAY_SENT,
  GRPC_CHTTP2_INITIATE_WRITE_RST_STREAM,
  GRPC_CHTTP2_INITIATE_WRITE_CLOSE_FROM_API,
  GRPC_CHTTP2_INITIATE_WRITE_STREAM_FLOW_CONTROL,
  GRPC_CHTTP2_INITIATE_WRITE_TRANSPORT_FLOW_CONTROL,
  GRPC_CHTTP2_INITIATE_WRITE_SEND_SETTINGS,
  GRPC_CHTTP2_INITIATE_WRITE_SETTINGS_ACK,
  GRPC_CHTTP2_INITIATE_WRITE_FLOW_CONTROL_UNSTALLED_BY_SETTING,
  GRPC_CHTTP2_INITIATE_WRITE_FLOW_CONTROL_UNSTALLED_BY_UPDATE,
  GRPC_CHTTP2_INITIATE_WRITE_APPLICATION_PING,
  GRPC_CHTTP2_INITIATE_WRITE_BDP_PING,
  GRPC_CHTTP2_INITIATE_WRITE_KEEPALIVE_PING,
  GRPC_CHTTP2_INITIATE_WRITE_TRANSPORT_FLOW_CONTROL_UNSTALLED,
  GRPC_CHTTP2_INITIATE_WRITE_PING_RESPONSE,
  GRPC_CHTTP2_INITIATE_WRITE_FORCE_RST_STREAM,
} grpc_chttp2_initiate_write_reason;

const char* grpc_chttp2_initiate_write_reason_string(
    grpc_chttp2_initiate_write_reason reason);

typedef enum {

  GRPC_DTS_CLIENT_PREFIX_0 = 0,
  GRPC_DTS_CLIENT_PREFIX_1,
  GRPC_DTS_CLIENT_PREFIX_2,
  GRPC_DTS_CLIENT_PREFIX_3,
  GRPC_DTS_CLIENT_PREFIX_4,
  GRPC_DTS_CLIENT_PREFIX_5,
  GRPC_DTS_CLIENT_PREFIX_6,
  GRPC_DTS_CLIENT_PREFIX_7,
  GRPC_DTS_CLIENT_PREFIX_8,
  GRPC_DTS_CLIENT_PREFIX_9,
  GRPC_DTS_CLIENT_PREFIX_10,
  GRPC_DTS_CLIENT_PREFIX_11,
  GRPC_DTS_CLIENT_PREFIX_12,
  GRPC_DTS_CLIENT_PREFIX_13,
  GRPC_DTS_CLIENT_PREFIX_14,
  GRPC_DTS_CLIENT_PREFIX_15,
  GRPC_DTS_CLIENT_PREFIX_16,
  GRPC_DTS_CLIENT_PREFIX_17,
  GRPC_DTS_CLIENT_PREFIX_18,
  GRPC_DTS_CLIENT_PREFIX_19,
  GRPC_DTS_CLIENT_PREFIX_20,
  GRPC_DTS_CLIENT_PREFIX_21,
  GRPC_DTS_CLIENT_PREFIX_22,
  GRPC_DTS_CLIENT_PREFIX_23,

  GRPC_DTS_FH_0,
  GRPC_DTS_FH_1,
  GRPC_DTS_FH_2,
  GRPC_DTS_FH_3,
  GRPC_DTS_FH_4,
  GRPC_DTS_FH_5,
  GRPC_DTS_FH_6,
  GRPC_DTS_FH_7,

  GRPC_DTS_FH_8,

  GRPC_DTS_FRAME
} grpc_chttp2_deframe_transport_state;

struct grpc_chttp2_stream_list {
  grpc_chttp2_stream* head;
  grpc_chttp2_stream* tail;
};
struct grpc_chttp2_stream_link {
  grpc_chttp2_stream* next;
  grpc_chttp2_stream* prev;
};

typedef enum {
  GRPC_CHTTP2_NO_GOAWAY_SEND,
  GRPC_CHTTP2_GRACEFUL_GOAWAY,
  GRPC_CHTTP2_FINAL_GOAWAY_SEND_SCHEDULED,
  GRPC_CHTTP2_FINAL_GOAWAY_SENT,
} grpc_chttp2_sent_goaway_state;

typedef struct grpc_chttp2_write_cb {
  int64_t call_at_byte;
  grpc_closure* closure;
  struct grpc_chttp2_write_cb* next;
} grpc_chttp2_write_cb;

typedef enum {
  GRPC_CHTTP2_KEEPALIVE_STATE_WAITING,
  GRPC_CHTTP2_KEEPALIVE_STATE_PINGING,
  GRPC_CHTTP2_KEEPALIVE_STATE_DYING,
  GRPC_CHTTP2_KEEPALIVE_STATE_DISABLED,
} grpc_chttp2_keepalive_state;

struct grpc_chttp2_transport final : public grpc_core::FilterStackTransport,
                                     public grpc_core::KeepsGrpcInitialized {
  grpc_chttp2_transport(const grpc_core::ChannelArgs& channel_args,
                        grpc_core::OrphanablePtr<grpc_endpoint> endpoint,
                        bool is_client);
  ~grpc_chttp2_transport() override;

  class ChannelzDataSource final : public grpc_core::channelz::DataSource {
   public:
    explicit ChannelzDataSource(grpc_chttp2_transport* transport)
        : grpc_core::channelz::DataSource(transport->channelz_socket),
          transport_(transport) {}
    ~ChannelzDataSource() { ResetDataSource(); }

    void AddData(grpc_core::channelz::DataSink sink) override;
    std::unique_ptr<grpc_core::channelz::ZTrace> GetZTrace(
        absl::string_view name) override;

   private:
    grpc_chttp2_transport* transport_;
  };

  void Orphan() override;

  grpc_core::RefCountedPtr<grpc_chttp2_transport> Ref() {
    return grpc_core::FilterStackTransport::RefAsSubclass<
        grpc_chttp2_transport>();
  }

  size_t SizeOfStream() const override;
  bool HackyDisableStreamOpBatchCoalescingInConnectedChannel() const override;
  void PerformStreamOp(grpc_stream* gs,
                       grpc_transport_stream_op_batch* op) override;
  void DestroyStream(grpc_stream* gs,
                     grpc_closure* then_schedule_closure) override;

  grpc_core::FilterStackTransport* filter_stack_transport() override {
    return this;
  }
  grpc_core::ClientTransport* client_transport() override { return nullptr; }
  grpc_core::ServerTransport* server_transport() override { return nullptr; }

  absl::string_view GetTransportName() const override;
  grpc_core::RefCountedPtr<grpc_core::channelz::SocketNode> GetSocketNode()
      const override {
    return channelz_socket;
  }
  void InitStream(grpc_stream* gs, grpc_stream_refcount* refcount,
                  const void* server_data, grpc_core::Arena* arena) override;
  void SetPollset(grpc_stream* stream, grpc_pollset* pollset) override;
  void SetPollsetSet(grpc_stream* stream,
                     grpc_pollset_set* pollset_set) override;
  void PerformOp(grpc_transport_op* op) override;

  void WriteSecurityFrame(grpc_core::SliceBuffer* data);
  void WriteSecurityFrameLocked(grpc_core::SliceBuffer* data);

  grpc_core::OrphanablePtr<grpc_endpoint> ep;
  grpc_core::Mutex ep_destroy_mu;

  grpc_core::Slice peer_string;

  grpc_core::TransportFramingEndpointExtension*
      transport_framing_endpoint_extension = nullptr;

  grpc_core::MemoryOwner memory_owner;
  const grpc_core::MemoryAllocator::Reservation self_reservation;
  grpc_core::ReclamationSweep active_reclamation;

  std::shared_ptr<grpc_event_engine::experimental::EventEngine> event_engine;
  grpc_core::Combiner* combiner;

  grpc_pollset_set* interested_parties_until_recv_settings = nullptr;

  grpc_closure* notify_on_receive_settings = nullptr;
  grpc_closure* notify_on_close = nullptr;

  grpc_error_handle closed_with_error;

  grpc_chttp2_stream_list lists[STREAM_LIST_COUNT] = {};

  absl::flat_hash_map<uint32_t, grpc_chttp2_stream*> stream_map;

  size_t extra_streams = 0;

  class RemovedStreamHandle {
   public:
    RemovedStreamHandle() = default;
    explicit RemovedStreamHandle(
        grpc_core::RefCountedPtr<grpc_chttp2_transport> t)
        : transport_(std::move(t)) {
      ++transport_->extra_streams;
    }
    ~RemovedStreamHandle() {
      if (transport_ != nullptr) {
        --transport_->extra_streams;
      }
    }
    RemovedStreamHandle(const RemovedStreamHandle&) = delete;
    RemovedStreamHandle& operator=(const RemovedStreamHandle&) = delete;
    RemovedStreamHandle(RemovedStreamHandle&&) = default;
    RemovedStreamHandle& operator=(RemovedStreamHandle&&) = default;

   private:
    grpc_core::RefCountedPtr<grpc_chttp2_transport> transport_;
  };

  grpc_closure write_action_begin_locked;
  grpc_closure write_action_end_locked;

  grpc_closure read_action_locked;

  grpc_slice_buffer read_buffer;

  grpc_chttp2_stream** accepting_stream = nullptr;

  void (*accept_stream_cb)(void* user_data, grpc_core::Transport* transport,
                           const void* server_data);

  void (*registered_method_matcher_cb)(
      void* user_data, grpc_core::ServerMetadata* metadata) = nullptr;
  void* accept_stream_cb_user_data;

  grpc_core::ConnectivityStateTracker state_tracker;

  grpc_core::SliceBuffer outbuf;

  grpc_core::HPackCompressor hpack_compressor;

  grpc_slice_buffer qbuf;

  size_t max_requests_per_read;

  grpc_error_handle goaway_error;

  grpc_chttp2_sent_goaway_state sent_goaway_state = GRPC_CHTTP2_NO_GOAWAY_SEND;

  grpc_core::Http2SettingsManager settings;

  grpc_event_engine::experimental::EventEngine::TaskHandle
      settings_ack_watchdog =
          grpc_event_engine::experimental::EventEngine::TaskHandle::kInvalid;

  uint32_t next_stream_id = 0;

  uint32_t last_new_stream_id = 0;

  uint32_t num_incoming_streams_before_settings_ack = 0;

  grpc_core::Chttp2PingAbusePolicy ping_abuse_policy;
  grpc_core::Chttp2PingRatePolicy ping_rate_policy;
  grpc_core::Chttp2PingCallbacks ping_callbacks;
  grpc_event_engine::experimental::EventEngine::TaskHandle
      delayed_ping_timer_handle =
          grpc_event_engine::experimental::EventEngine::TaskHandle::kInvalid;
  grpc_closure retry_initiate_ping_locked;

  size_t ping_ack_count = 0;
  size_t ping_ack_capacity = 0;
  uint64_t* ping_acks = nullptr;

  grpc_core::HPackParser hpack_parser;

  union {
    grpc_chttp2_window_update_parser window_update;
    grpc_chttp2_settings_parser settings;
    grpc_chttp2_ping_parser ping;
    grpc_chttp2_rst_stream_parser rst_stream;
  } simple;

  grpc_chttp2_goaway_parser goaway_parser;

  grpc_chttp2_security_frame_parser security_frame_parser;

  grpc_core::chttp2::TransportFlowControl flow_control;

  int64_t initial_window_update = 0;

  grpc_chttp2_deframe_transport_state deframe_state = GRPC_DTS_CLIENT_PREFIX_0;
  uint8_t incoming_frame_type = 0;
  uint8_t incoming_frame_flags = 0;
  uint8_t header_eof = 0;
  bool is_first_frame = true;
  uint32_t expect_continuation_stream_id = 0;
  uint32_t incoming_frame_size = 0;

  int min_tarpit_duration_ms;
  int max_tarpit_duration_ms;
  bool allow_tarpit;

  grpc_chttp2_stream* incoming_stream = nullptr;

  struct Parser {
    const char* name;
    grpc_error_handle (*parser)(void* parser_user_data,
                                grpc_chttp2_transport* t, grpc_chttp2_stream* s,
                                const grpc_slice& slice, int is_last);
    void* user_data = nullptr;
  };
  Parser parser;

  grpc_chttp2_write_cb* write_cb_pool = nullptr;

  grpc_closure next_bdp_ping_timer_expired_locked;
  grpc_closure start_bdp_ping_locked;
  grpc_closure finish_bdp_ping_locked;

  grpc_error_handle close_transport_on_writes_finished;

  grpc_closure_list run_after_write = GRPC_CLOSURE_LIST_INIT;

  grpc_closure benign_reclaimer_locked;

  grpc_closure destructive_reclaimer_locked;

  grpc_event_engine::experimental::EventEngine::TaskHandle
      next_bdp_ping_timer_handle =
          grpc_event_engine::experimental::EventEngine::TaskHandle::kInvalid;

  grpc_closure init_keepalive_ping_locked;

  grpc_closure finish_keepalive_ping_locked;

  grpc_event_engine::experimental::EventEngine::TaskHandle
      keepalive_ping_timer_handle =
          grpc_event_engine::experimental::EventEngine::TaskHandle::kInvalid;

  grpc_core::Duration keepalive_time;

  grpc_core::Timestamp next_adjusted_keepalive_timestamp;

  grpc_core::Duration keepalive_timeout;

  std::atomic<size_t> streams_allocated{0};

  grpc_chttp2_keepalive_state keepalive_state;

  uint32_t max_header_list_size_soft_limit = 0;
  grpc_core::ContextList* context_list = nullptr;
  grpc_core::RefCountedPtr<grpc_core::channelz::SocketNode> channelz_socket;
  std::unique_ptr<ChannelzDataSource> channelz_data_source;
  uint32_t num_messages_in_next_write = 0;

  uint32_t num_pending_induced_frames = 0;
  uint32_t incoming_stream_id = 0;

  grpc_core::Duration ping_timeout;
  grpc_event_engine::experimental::EventEngine::TaskHandle
      keepalive_ping_timeout_handle =
          grpc_event_engine::experimental::EventEngine::TaskHandle::kInvalid;

  grpc_core::Duration settings_timeout;

  uint32_t write_buffer_size = grpc_core::chttp2::kDefaultWindow;

  grpc_chttp2_write_state write_state = GRPC_CHTTP2_WRITE_STATE_IDLE;

  grpc_core::Chttp2WriteSizePolicy write_size_policy;

  bool reading_paused_on_pending_induced_frames = false;

  bool enable_preferred_rx_crypto_frame_advertisement = false;

  uint8_t closure_barrier_may_cover_write = CLOSURE_BARRIER_MAY_COVER_WRITE;

  bool benign_reclaimer_registered = false;

  bool destructive_reclaimer_registered = false;

  bool keepalive_permit_without_calls = false;

  bool bdp_ping_blocked =
      false;

  uint8_t destroying = false;

  bool is_client;

  bool bdp_ping_started = false;

  bool ack_pings = true;

  bool keepalive_incoming_data_wanted = false;

  bool max_concurrent_streams_overload_protection = false;
  bool max_concurrent_streams_reject_on_client = false;

  uint8_t ping_on_rst_stream_percent;

  grpc_core::Timestamp last_window_update_time =
      grpc_core::Timestamp::InfPast();

  grpc_core::Http2StatsCollector http2_stats;
  grpc_core::Http2ZTraceCollector http2_ztrace_collector;

  GPR_NO_UNIQUE_ADDRESS grpc_core::latent_see::Flow write_flow;
};

typedef enum {
  GRPC_METADATA_NOT_PUBLISHED,
  GRPC_METADATA_SYNTHESIZED_FROM_FAKE,
  GRPC_METADATA_PUBLISHED_FROM_WIRE,
  GRPC_METADATA_PUBLISHED_AT_CLOSE
} grpc_published_metadata_method;

struct grpc_chttp2_stream {
  grpc_chttp2_stream(grpc_chttp2_transport* t, grpc_stream_refcount* refcount,
                     const void* server_data, grpc_core::Arena* arena);
  ~grpc_chttp2_stream();

  const grpc_core::RefCountedPtr<grpc_chttp2_transport> t;
  grpc_stream_refcount* refcount;
  grpc_core::Arena* const arena;

  grpc_closure destroy_stream;
  grpc_closure* destroy_stream_arg;

  grpc_chttp2_stream_link links[STREAM_LIST_COUNT];

  uint32_t id = 0;

  grpc_metadata_batch* send_initial_metadata = nullptr;
  grpc_closure* send_initial_metadata_finished = nullptr;
  grpc_metadata_batch* send_trailing_metadata = nullptr;

  bool* sent_trailing_metadata_op = nullptr;
  grpc_closure* send_trailing_metadata_finished = nullptr;

  int64_t next_message_end_offset;
  int64_t flow_controlled_bytes_written = 0;
  int64_t flow_controlled_bytes_flowed = 0;
  grpc_closure* send_message_finished = nullptr;

  grpc_metadata_batch* recv_initial_metadata;
  grpc_closure* recv_initial_metadata_ready = nullptr;
  bool* trailing_metadata_available = nullptr;
  std::optional<grpc_core::SliceBuffer>* recv_message = nullptr;
  uint32_t* recv_message_flags = nullptr;
  bool* call_failed_before_recv_message = nullptr;
  grpc_closure* recv_message_ready = nullptr;
  grpc_metadata_batch* recv_trailing_metadata;
  grpc_closure* recv_trailing_metadata_finished = nullptr;

  grpc_transport_stream_stats* collecting_stats = nullptr;
  grpc_transport_stream_stats stats = grpc_transport_stream_stats();

  bool write_closed = false;

  bool read_closed = false;

  bool all_incoming_byte_streams_finished = false;

  bool seen_error = false;

  bool write_buffering = false;

  bool eos_received = false;
  bool eos_sent = false;

  grpc_core::BitSet<STREAM_LIST_COUNT> included;

  grpc_error_handle read_closed_error;

  grpc_error_handle write_closed_error;

  grpc_published_metadata_method published_metadata[2] = {};

  grpc_metadata_batch initial_metadata_buffer;
  grpc_metadata_batch trailing_metadata_buffer;

  grpc_slice_buffer frame_storage;

  grpc_core::Timestamp deadline = grpc_core::Timestamp::InfFuture();

  int64_t received_bytes = 0;

  grpc_core::chttp2::StreamFlowControl flow_control;

  grpc_slice_buffer flow_controlled_buffer;

  grpc_chttp2_write_cb* on_flow_controlled_cbs = nullptr;
  grpc_chttp2_write_cb* on_write_finished_cbs = nullptr;
  grpc_chttp2_write_cb* finish_after_write = nullptr;
  size_t sending_bytes = 0;

  size_t byte_counter = 0;

  int64_t write_counter = 0;

  grpc_core::Chttp2CallTracerWrapper call_tracer_wrapper;

  grpc_core::RefCountedPtr<grpc_core::channelz::CallNode> channelz_call_node;

  grpc_core::CallTracerInterface* call_tracer = nullptr;

  grpc_core::CallTracerAnnotationInterface* parent_call_tracer = nullptr;

  gpr_timespec creation_time = gpr_now(GPR_CLOCK_MONOTONIC);

  bool parsed_trailers_only = false;

  bool final_metadata_requested = false;
  bool received_last_frame = false;

  uint8_t header_frames_received = 0;

  bool sent_initial_metadata = false;
  bool sent_trailing_metadata = false;

  bool traced = false;

  grpc_core::Timestamp last_window_update_time =
      grpc_core::Timestamp::InfPast();
};

#define GRPC_ARG_MAX_CONCURRENT_STREAMS_OVERLOAD_PROTECTION \
  "grpc.http.overload_protection"

#define GRPC_ARG_MAX_CONCURRENT_STREAMS_REJECT_ON_CLIENT \
  "grpc.http.max_concurrent_streams_reject_on_client"

void grpc_chttp2_initiate_write(grpc_chttp2_transport* t,
                                grpc_chttp2_initiate_write_reason reason);

struct grpc_chttp2_begin_write_result {

  bool writing;

  bool partial;

  bool early_results_scheduled;
};
grpc_chttp2_begin_write_result grpc_chttp2_begin_write(
    grpc_chttp2_transport* t);
void grpc_chttp2_end_write(grpc_chttp2_transport* t, grpc_error_handle error);

std::variant<size_t, absl::Status> grpc_chttp2_perform_read(
    grpc_chttp2_transport* t, const grpc_slice& slice,
    size_t& requests_started);

void grpc_chttp2_act_on_flowctl_action(
    const grpc_core::chttp2::FlowControlAction& action,
    grpc_chttp2_transport* t, grpc_chttp2_stream* s);

inline grpc_chttp2_stream* grpc_chttp2_parsing_lookup_stream(
    grpc_chttp2_transport* t, uint32_t id) {
  auto it = t->stream_map.find(id);
  if (it == t->stream_map.end()) return nullptr;
  return it->second;
}
grpc_chttp2_stream* grpc_chttp2_parsing_accept_stream(grpc_chttp2_transport* t,
                                                      uint32_t id);

void grpc_chttp2_add_incoming_goaway(grpc_chttp2_transport* t,
                                     uint32_t goaway_error,
                                     uint32_t last_stream_id,
                                     absl::string_view goaway_text);

void grpc_chttp2_parsing_become_skip_parser(grpc_chttp2_transport* t);

void grpc_chttp2_complete_closure_step(grpc_chttp2_transport* t,
                                       grpc_closure** pclosure,
                                       grpc_error_handle error,
                                       const char* desc,
                                       grpc_core::DebugLocation whence = {});

void grpc_chttp2_keepalive_timeout(
    grpc_core::RefCountedPtr<grpc_chttp2_transport> t);
void grpc_chttp2_ping_timeout(
    grpc_core::RefCountedPtr<grpc_chttp2_transport> t);

void grpc_chttp2_settings_timeout(
    grpc_core::RefCountedPtr<grpc_chttp2_transport> t);

#define GRPC_HEADER_SIZE_IN_BYTES 5
#define MAX_SIZE_T (~(size_t)0)

#define GRPC_CHTTP2_CLIENT_CONNECT_STRING "PRI * HTTP/2.0\r\n\r\nSM\r\n\r\n"
#define GRPC_CHTTP2_CLIENT_CONNECT_STRLEN \
  (sizeof(GRPC_CHTTP2_CLIENT_CONNECT_STRING) - 1)

#define GRPC_CHTTP2_IF_TRACING(severity) \
  LOG_IF(severity, GRPC_TRACE_FLAG_ENABLED(http))

void grpc_chttp2_fake_status(grpc_chttp2_transport* t,
                             grpc_chttp2_stream* stream,
                             grpc_error_handle error);
grpc_chttp2_transport::RemovedStreamHandle grpc_chttp2_mark_stream_closed(
    grpc_chttp2_transport* t, grpc_chttp2_stream* s, int close_reads,
    int close_writes, grpc_error_handle error);
void grpc_chttp2_start_writing(grpc_chttp2_transport* t);

#ifndef NDEBUG
#define GRPC_CHTTP2_STREAM_REF(stream, reason) \
  grpc_chttp2_stream_ref(stream, reason)
#define GRPC_CHTTP2_STREAM_UNREF(stream, reason) \
  grpc_chttp2_stream_unref(stream, reason)
void grpc_chttp2_stream_ref(grpc_chttp2_stream* s, const char* reason);
void grpc_chttp2_stream_unref(grpc_chttp2_stream* s, const char* reason);
#else
#define GRPC_CHTTP2_STREAM_REF(stream, reason) grpc_chttp2_stream_ref(stream)
#define GRPC_CHTTP2_STREAM_UNREF(stream, reason) \
  grpc_chttp2_stream_unref(stream)
void grpc_chttp2_stream_ref(grpc_chttp2_stream* s);
void grpc_chttp2_stream_unref(grpc_chttp2_stream* s);
#endif

void grpc_chttp2_ack_ping(grpc_chttp2_transport* t, uint64_t id);

void grpc_chttp2_exceeded_ping_strikes(grpc_chttp2_transport* t);

void grpc_chttp2_reset_ping_clock(grpc_chttp2_transport* t);

void grpc_chttp2_mark_stream_writable(grpc_chttp2_transport* t,
                                      grpc_chttp2_stream* s);

void grpc_chttp2_cancel_stream(grpc_chttp2_transport* t, grpc_chttp2_stream* s,
                               grpc_error_handle due_to_error, bool tarpit);

void grpc_chttp2_maybe_complete_recv_initial_metadata(grpc_chttp2_transport* t,
                                                      grpc_chttp2_stream* s);
void grpc_chttp2_maybe_complete_recv_message(grpc_chttp2_transport* t,
                                             grpc_chttp2_stream* s);
void grpc_chttp2_maybe_complete_recv_trailing_metadata(grpc_chttp2_transport* t,
                                                       grpc_chttp2_stream* s);

void grpc_chttp2_fail_pending_writes(grpc_chttp2_transport* t,
                                     grpc_chttp2_stream* s,
                                     grpc_error_handle error);

void grpc_chttp2_config_default_keepalive_args(grpc_channel_args* args,
                                               bool is_client);
void grpc_chttp2_config_default_keepalive_args(
    const grpc_core::ChannelArgs& channel_args, bool is_client);

void grpc_chttp2_retry_initiate_ping(
    grpc_core::RefCountedPtr<grpc_chttp2_transport> t);

void schedule_bdp_ping_locked(
    grpc_core::RefCountedPtr<grpc_chttp2_transport> t);

uint32_t grpc_chttp2_min_read_progress_size(grpc_chttp2_transport* t);

#endif
