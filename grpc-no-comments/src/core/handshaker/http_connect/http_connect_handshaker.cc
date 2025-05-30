
// Copyright 2016 gRPC authors.

#include "src/core/handshaker/http_connect/http_connect_handshaker.h"

#include <grpc/slice.h>
#include <grpc/slice_buffer.h>
#include <grpc/support/alloc.h>
#include <grpc/support/port_platform.h>
#include <limits.h>
#include <string.h>

#include <memory>
#include <optional>
#include <string>
#include <utility>

#include "absl/base/thread_annotations.h"
#include "absl/log/log.h"
#include "absl/status/status.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/string_view.h"
#include "src/core/config/core_configuration.h"
#include "src/core/handshaker/handshaker.h"
#include "src/core/handshaker/handshaker_factory.h"
#include "src/core/handshaker/handshaker_registry.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/iomgr/closure.h"
#include "src/core/lib/iomgr/endpoint.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/lib/iomgr/iomgr_fwd.h"
#include "src/core/lib/iomgr/tcp_server.h"
#include "src/core/lib/slice/slice.h"
#include "src/core/lib/slice/slice_buffer.h"
#include "src/core/util/http_client/format_request.h"
#include "src/core/util/http_client/parser.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/string.h"
#include "src/core/util/sync.h"

namespace grpc_core {

namespace {

class HttpConnectHandshaker : public Handshaker {
 public:
  HttpConnectHandshaker();
  absl::string_view name() const override { return "http_connect"; }
  void DoHandshake(
      HandshakerArgs* args,
      absl::AnyInvocable<void(absl::Status)> on_handshake_done) override;
  void Shutdown(absl::Status error) override;

 private:
  ~HttpConnectHandshaker() override;
  void HandshakeFailedLocked(absl::Status error)
      ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu_);
  void FinishLocked(absl::Status error) ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu_);
  void OnWriteDone(absl::Status error);
  void OnReadDone(absl::Status error);
  bool OnReadDoneLocked(absl::Status error) ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu_);
  static void OnWriteDoneScheduler(void* arg, grpc_error_handle error);
  static void OnReadDoneScheduler(void* arg, grpc_error_handle error);

  Mutex mu_;

  HandshakerArgs* args_ = nullptr;
  absl::AnyInvocable<void(absl::Status)> on_handshake_done_
      ABSL_GUARDED_BY(mu_);

  SliceBuffer write_buffer_ ABSL_GUARDED_BY(mu_);
  grpc_closure on_write_done_scheduler_ ABSL_GUARDED_BY(mu_);
  grpc_closure on_read_done_scheduler_ ABSL_GUARDED_BY(mu_);
  grpc_http_parser http_parser_ ABSL_GUARDED_BY(mu_);
  grpc_http_response http_response_ ABSL_GUARDED_BY(mu_);
};

HttpConnectHandshaker::~HttpConnectHandshaker() {
  grpc_http_parser_destroy(&http_parser_);
  grpc_http_response_destroy(&http_response_);
}

void HttpConnectHandshaker::HandshakeFailedLocked(absl::Status error) {
  if (error.ok()) {

    error = GRPC_ERROR_CREATE("Handshaker shutdown");
  }
  absl::string_view peer_string = "[unknown]";
  if (args_ != nullptr && args_->endpoint != nullptr) {
    peer_string = grpc_endpoint_get_peer(args_->endpoint.get());
  }
  LOG_EVERY_N_SEC(ERROR, 60)
      << "HTTP proxy handshake with " << peer_string << " failed: " << error;

  FinishLocked(std::move(error));
}

void HttpConnectHandshaker::FinishLocked(absl::Status error) {
  InvokeOnHandshakeDone(args_, std::move(on_handshake_done_), std::move(error));
}

void HttpConnectHandshaker::OnWriteDoneScheduler(void* arg,
                                                 grpc_error_handle error) {
  auto* handshaker = static_cast<HttpConnectHandshaker*>(arg);
  handshaker->args_->event_engine->Run(
      [handshaker, error = std::move(error)]() mutable {
        ExecCtx exec_ctx;
        handshaker->OnWriteDone(std::move(error));
      });
}

void HttpConnectHandshaker::OnWriteDone(absl::Status error) {
  ReleasableMutexLock lock(&mu_);
  if (!error.ok() || args_->endpoint == nullptr) {

    HandshakeFailedLocked(error);
    lock.Release();
    Unref();
  } else {

    grpc_endpoint_read(
        args_->endpoint.get(), args_->read_buffer.c_slice_buffer(),
        GRPC_CLOSURE_INIT(&on_read_done_scheduler_,
                          &HttpConnectHandshaker::OnReadDoneScheduler, this,
                          grpc_schedule_on_exec_ctx),
        true, 1);
  }
}

void HttpConnectHandshaker::OnReadDoneScheduler(void* arg,
                                                grpc_error_handle error) {
  auto* handshaker = static_cast<HttpConnectHandshaker*>(arg);
  handshaker->args_->event_engine->Run(
      [handshaker, error = std::move(error)]() mutable {
        ExecCtx exec_ctx;
        handshaker->OnReadDone(std::move(error));
      });
}

void HttpConnectHandshaker::OnReadDone(absl::Status error) {
  bool done;
  {
    MutexLock lock(&mu_);
    done = OnReadDoneLocked(std::move(error));
  }
  if (done) Unref();
}

bool HttpConnectHandshaker::OnReadDoneLocked(absl::Status error) {
  if (!error.ok() || args_->endpoint == nullptr) {

    HandshakeFailedLocked(std::move(error));
    return true;
  }

  while (args_->read_buffer.Count() > 0) {
    Slice slice = args_->read_buffer.TakeFirst();
    if (!slice.empty()) {
      size_t body_start_offset = 0;
      error = grpc_http_parser_parse(&http_parser_, slice.c_slice(),
                                     &body_start_offset);
      if (!error.ok()) {
        HandshakeFailedLocked(std::move(error));
        return true;
      }
      if (http_parser_.state == GRPC_HTTP_BODY) {

        SliceBuffer tmp_buffer;
        if (body_start_offset < slice.length()) {
          tmp_buffer.Append(slice.Split(body_start_offset));
        }
        tmp_buffer.TakeAndAppend(args_->read_buffer);
        tmp_buffer.Swap(&args_->read_buffer);
        break;
      }
    }
  }

  if (http_parser_.state != GRPC_HTTP_BODY) {
    args_->read_buffer.Clear();
    grpc_endpoint_read(
        args_->endpoint.get(), args_->read_buffer.c_slice_buffer(),
        GRPC_CLOSURE_INIT(&on_read_done_scheduler_,
                          &HttpConnectHandshaker::OnReadDoneScheduler, this,
                          grpc_schedule_on_exec_ctx),
        true, 1);
    return false;
  }

  if (http_response_.status < 200 || http_response_.status >= 300) {
    error = GRPC_ERROR_CREATE(absl::StrCat("HTTP proxy returned response code ",
                                           http_response_.status));
    HandshakeFailedLocked(std::move(error));
    return true;
  }

  FinishLocked(absl::OkStatus());
  return true;
}

void HttpConnectHandshaker::Shutdown(absl::Status ) {
  MutexLock lock(&mu_);
  if (on_handshake_done_ != nullptr) args_->endpoint.reset();
}

void HttpConnectHandshaker::DoHandshake(
    HandshakerArgs* args,
    absl::AnyInvocable<void(absl::Status)> on_handshake_done) {

  std::optional<absl::string_view> server_name =
      args->args.GetString(GRPC_ARG_HTTP_CONNECT_SERVER);
  if (!server_name.has_value()) {
    InvokeOnHandshakeDone(args, std::move(on_handshake_done), absl::OkStatus());
    return;
  }

  std::optional<absl::string_view> arg_header_string =
      args->args.GetString(GRPC_ARG_HTTP_CONNECT_HEADERS);
  grpc_http_header* headers = nullptr;
  size_t num_headers = 0;
  char** header_strings = nullptr;
  size_t num_header_strings = 0;
  if (arg_header_string.has_value()) {
    std::string buffer(*arg_header_string);
    gpr_string_split(buffer.c_str(), "\n", &header_strings,
                     &num_header_strings);
    headers = static_cast<grpc_http_header*>(
        gpr_malloc(sizeof(grpc_http_header) * num_header_strings));
    for (size_t i = 0; i < num_header_strings; ++i) {
      char* sep = strchr(header_strings[i], ':');
      if (sep == nullptr) {
        LOG(ERROR) << "skipping unparsable HTTP CONNECT header: "
                   << header_strings[i];
        continue;
      }
      *sep = '\0';
      headers[num_headers].key = header_strings[i];
      headers[num_headers].value = sep + 1;
      ++num_headers;
    }
  }

  MutexLock lock(&mu_);
  args_ = args;
  on_handshake_done_ = std::move(on_handshake_done);

  std::string proxy_name(grpc_endpoint_get_peer(args->endpoint.get()));
  std::string server_name_string(*server_name);
  VLOG(2) << "Connecting to server " << server_name_string << " via HTTP proxy "
          << proxy_name;

  grpc_http_request request;
  request.method = const_cast<char*>("CONNECT");
  request.version = GRPC_HTTP_HTTP10;
  request.hdrs = headers;
  request.hdr_count = num_headers;
  request.body_length = 0;
  request.body = nullptr;
  grpc_slice request_slice = grpc_httpcli_format_connect_request(
      &request, server_name_string.c_str(), server_name_string.c_str());
  write_buffer_.Append(Slice(request_slice));

  gpr_free(headers);
  for (size_t i = 0; i < num_header_strings; ++i) {
    gpr_free(header_strings[i]);
  }
  gpr_free(header_strings);

  Ref().release();
  grpc_event_engine::experimental::EventEngine::Endpoint::WriteArgs write_args;
  write_args.set_max_frame_size(INT_MAX);
  grpc_endpoint_write(
      args->endpoint.get(), write_buffer_.c_slice_buffer(),
      GRPC_CLOSURE_INIT(&on_write_done_scheduler_,
                        &HttpConnectHandshaker::OnWriteDoneScheduler, this,
                        grpc_schedule_on_exec_ctx),
      std::move(write_args));
}

HttpConnectHandshaker::HttpConnectHandshaker() {
  grpc_http_parser_init(&http_parser_, GRPC_HTTP_RESPONSE, &http_response_);
}

class HttpConnectHandshakerFactory : public HandshakerFactory {
 public:
  void AddHandshakers(const ChannelArgs& ,
                      grpc_pollset_set* ,
                      HandshakeManager* handshake_mgr) override {
    handshake_mgr->Add(MakeRefCounted<HttpConnectHandshaker>());
  }
  HandshakerPriority Priority() override {
    return HandshakerPriority::kHTTPConnectHandshakers;
  }
  ~HttpConnectHandshakerFactory() override = default;
};

}

void RegisterHttpConnectHandshaker(CoreConfiguration::Builder* builder) {
  builder->handshaker_registry()->RegisterHandshakerFactory(
      HANDSHAKER_CLIENT, std::make_unique<HttpConnectHandshakerFactory>());
}

}
