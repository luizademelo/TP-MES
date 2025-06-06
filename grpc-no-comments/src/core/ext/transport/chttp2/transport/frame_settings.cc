
// Copyright 2015 gRPC authors.

#include "src/core/ext/transport/chttp2/transport/frame_settings.h"

#include <grpc/slice_buffer.h>
#include <grpc/support/port_platform.h>
#include <string.h>

#include <string>

#include "absl/base/attributes.h"
#include "absl/log/log.h"
#include "absl/status/status.h"
#include "absl/strings/str_format.h"
#include "src/core/ext/transport/chttp2/transport/flow_control.h"
#include "src/core/ext/transport/chttp2/transport/frame_goaway.h"
#include "src/core/ext/transport/chttp2/transport/http2_settings.h"
#include "src/core/ext/transport/chttp2/transport/http2_ztrace_collector.h"
#include "src/core/ext/transport/chttp2/transport/internal.h"
#include "src/core/ext/transport/chttp2/transport/legacy_frame.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/lib/slice/slice.h"
#include "src/core/telemetry/stats.h"
#include "src/core/util/debug_location.h"
#include "src/core/util/useful.h"

using grpc_core::http2::Http2ErrorCode;

static uint8_t* fill_header(uint8_t* out, uint32_t length, uint8_t flags) {
  *out++ = static_cast<uint8_t>(length >> 16);
  *out++ = static_cast<uint8_t>(length >> 8);
  *out++ = static_cast<uint8_t>(length);
  *out++ = GRPC_CHTTP2_FRAME_SETTINGS;
  *out++ = flags;
  *out++ = 0;
  *out++ = 0;
  *out++ = 0;
  *out++ = 0;
  return out;
}

grpc_slice grpc_chttp2_settings_ack_create(void) {
  grpc_slice output = GRPC_SLICE_MALLOC(9);
  fill_header(GRPC_SLICE_START_PTR(output), 0, GRPC_CHTTP2_FLAG_ACK);
  return output;
}

grpc_error_handle grpc_chttp2_settings_parser_begin_frame(
    grpc_chttp2_settings_parser* parser, uint32_t length, uint8_t flags,
    grpc_core::Http2Settings& settings) {
  parser->target_settings = &settings;
  parser->incoming_settings.Init(settings);
  parser->is_ack = 0;
  parser->state = GRPC_CHTTP2_SPS_ID0;
  if (flags == GRPC_CHTTP2_FLAG_ACK) {
    parser->is_ack = 1;
    if (length != 0) {
      return GRPC_ERROR_CREATE("non-empty settings ack frame received");
    }
    return absl::OkStatus();
  } else if (flags != 0) {
    return GRPC_ERROR_CREATE("invalid flags on settings frame");
  } else if (length % 6 != 0) {
    return GRPC_ERROR_CREATE("settings frames must be a multiple of six bytes");
  } else {
    return absl::OkStatus();
  }
}

grpc_error_handle grpc_chttp2_settings_parser_parse(void* p,
                                                    grpc_chttp2_transport* t,
                                                    grpc_chttp2_stream* ,
                                                    const grpc_slice& slice,
                                                    int is_last) {
  grpc_chttp2_settings_parser* parser =
      static_cast<grpc_chttp2_settings_parser*>(p);
  const uint8_t* cur = GRPC_SLICE_START_PTR(slice);
  const uint8_t* end = GRPC_SLICE_END_PTR(slice);

  if (parser->is_ack) {
    t->http2_ztrace_collector.Append(
        grpc_core::H2SettingsTrace<true>{true, {}});
    return absl::OkStatus();
  }

  for (;;) {
    switch (parser->state) {
      case GRPC_CHTTP2_SPS_ID0:
        if (cur == end) {
          parser->state = GRPC_CHTTP2_SPS_ID0;
          if (is_last) {
            grpc_core::Http2Settings* target_settings =
                parser->incoming_settings.get();
            grpc_core::global_stats().IncrementHttp2HeaderTableSize(
                target_settings->header_table_size());
            grpc_core::global_stats().IncrementHttp2InitialWindowSize(
                target_settings->initial_window_size());
            grpc_core::global_stats().IncrementHttp2MaxConcurrentStreams(
                target_settings->max_concurrent_streams());
            grpc_core::global_stats().IncrementHttp2MaxFrameSize(
                target_settings->max_frame_size());
            grpc_core::global_stats().IncrementHttp2MaxHeaderListSize(
                target_settings->max_header_list_size());
            grpc_core::global_stats()
                .IncrementHttp2PreferredReceiveCryptoMessageSize(
                    target_settings->preferred_receive_crypto_message_size());
            t->http2_ztrace_collector.Append([parser]() {
              grpc_core::H2SettingsTrace<true> settings{false, {}};

              parser->incoming_settings->Diff(
                  false, *parser->target_settings,
                  [&settings](uint16_t key, uint32_t value) {
                    settings.settings.push_back({key, value});
                  });
              return settings;
            });
            t->http2_ztrace_collector.Append(
                []() { return grpc_core::H2SettingsTrace<false>{true, {}}; });
            *parser->target_settings = *parser->incoming_settings;
            t->num_pending_induced_frames++;
            grpc_slice_buffer_add(&t->qbuf, grpc_chttp2_settings_ack_create());
            grpc_chttp2_initiate_write(t,
                                       GRPC_CHTTP2_INITIATE_WRITE_SETTINGS_ACK);
            if (t->notify_on_receive_settings != nullptr) {
              if (t->interested_parties_until_recv_settings != nullptr) {
                grpc_endpoint_delete_from_pollset_set(
                    t->ep.get(), t->interested_parties_until_recv_settings);
                t->interested_parties_until_recv_settings = nullptr;
              }
              grpc_core::ExecCtx::Run(DEBUG_LOCATION,
                                      t->notify_on_receive_settings,
                                      absl::OkStatus());
              t->notify_on_receive_settings = nullptr;
            }
          }
          return absl::OkStatus();
        }
        parser->id = static_cast<uint16_t>((static_cast<uint16_t>(*cur)) << 8);
        cur++;
        [[fallthrough]];
      case GRPC_CHTTP2_SPS_ID1:
        if (cur == end) {
          parser->state = GRPC_CHTTP2_SPS_ID1;
          return absl::OkStatus();
        }
        parser->id = static_cast<uint16_t>(parser->id | (*cur));
        cur++;
        [[fallthrough]];
      case GRPC_CHTTP2_SPS_VAL0:
        if (cur == end) {
          parser->state = GRPC_CHTTP2_SPS_VAL0;
          return absl::OkStatus();
        }
        parser->value = (static_cast<uint32_t>(*cur)) << 24;
        cur++;
        [[fallthrough]];
      case GRPC_CHTTP2_SPS_VAL1:
        if (cur == end) {
          parser->state = GRPC_CHTTP2_SPS_VAL1;
          return absl::OkStatus();
        }
        parser->value |= (static_cast<uint32_t>(*cur)) << 16;
        cur++;
        [[fallthrough]];
      case GRPC_CHTTP2_SPS_VAL2:
        if (cur == end) {
          parser->state = GRPC_CHTTP2_SPS_VAL2;
          return absl::OkStatus();
        }
        parser->value |= (static_cast<uint32_t>(*cur)) << 8;
        cur++;
        [[fallthrough]];
      case GRPC_CHTTP2_SPS_VAL3: {
        if (cur == end) {
          parser->state = GRPC_CHTTP2_SPS_VAL3;
          return absl::OkStatus();
        } else {
          parser->state = GRPC_CHTTP2_SPS_ID0;
        }
        parser->value |= *cur;
        cur++;

        if (parser->id == grpc_core::Http2Settings::kInitialWindowSizeWireId) {
          t->initial_window_update +=
              static_cast<int64_t>(parser->value) -
              parser->incoming_settings->initial_window_size();
          if (GRPC_TRACE_FLAG_ENABLED(http) ||
              GRPC_TRACE_FLAG_ENABLED(flowctl)) {
            LOG(INFO) << t << "[" << (t->is_client ? "cli" : "svr")
                      << "] adding " << t->initial_window_update
                      << " for initial_window change";
          }
        }
        auto error =
            parser->incoming_settings->Apply(parser->id, parser->value);
        if (error != Http2ErrorCode::kNoError) {
          grpc_chttp2_goaway_append(
              t->last_new_stream_id, static_cast<uint32_t>(error),
              grpc_slice_from_static_string("HTTP2 settings error"), &t->qbuf,
              &t->http2_ztrace_collector);
          return GRPC_ERROR_CREATE(absl::StrFormat(
              "invalid value %u passed for %s", parser->value,
              grpc_core::Http2Settings::WireIdToName(parser->id).c_str()));
        }
        GRPC_TRACE_LOG(http, INFO)
            << "CHTTP2:" << (t->is_client ? "CLI" : "SVR") << ":"
            << t->peer_string.as_string_view() << ": got setting "
            << grpc_core::Http2Settings::WireIdToName(parser->id) << " = "
            << parser->value;
      } break;
    }
  }
}
