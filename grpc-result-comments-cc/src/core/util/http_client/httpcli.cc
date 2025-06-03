Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

// Includes necessary headers for HTTP client functionality
#include "src/core/util/http_client/httpcli.h"

#include <grpc/grpc.h>
#include <grpc/slice_buffer.h>
#include <grpc/support/alloc.h>
#include <grpc/support/port_platform.h>
#include <limits.h>

#include <string>
#include <utility>

#include "absl/functional/bind_front.h"
#include "absl/log/check.h"
#include "absl/status/status.h"
#include "absl/strings/str_format.h"
#include "src/core/config/core_configuration.h"
#include "src/core/credentials/transport/security_connector.h"
#include "src/core/credentials/transport/transport_credentials.h"
#include "src/core/handshaker/handshaker.h"
#include "src/core/handshaker/handshaker_registry.h"
#include "src/core/handshaker/tcp_connect/tcp_connect_handshaker.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/channel/channel_args_preconditioning.h"
#include "src/core/lib/event_engine/resolved_address_internal.h"
#include "src/core/lib/event_engine/shim.h"
#include "src/core/lib/event_engine/tcp_socket_utils.h"
#include "src/core/lib/iomgr/endpoint.h"
#include "src/core/lib/iomgr/iomgr_internal.h"
#include "src/core/lib/iomgr/pollset_set.h"
#include "src/core/lib/iomgr/resolve_address.h"
#include "src/core/lib/resource_quota/api.h"
#include "src/core/lib/slice/slice.h"
#include "src/core/lib/transport/error_utils.h"
#include "src/core/util/http_client/format_request.h"
#include "src/core/util/http_client/parser.h"
#include "src/core/util/status_helper.h"

namespace grpc_core {

namespace {

using grpc_event_engine::experimental::EventEngine;
using grpc_event_engine::experimental::ResolvedAddressToURI;

// Global override functions for HTTP methods (used for testing)
grpc_httpcli_get_override g_get_override;
grpc_httpcli_post_override g_post_override;
grpc_httpcli_put_override g_put_override;
// Global intercept function for handshake completion (used for testing)
void (*g_test_only_on_handshake_done_intercept)(HttpRequest* req);

}  // namespace

// Creates and returns an HTTP GET request
OrphanablePtr<HttpRequest> HttpRequest::Get(
    URI uri, const grpc_channel_args* channel_args,
    grpc_polling_entity* pollent, const grpc_http_request* request,
    Timestamp deadline, grpc_closure* on_done, grpc_http_response* response,
    RefCountedPtr<grpc_channel_credentials> channel_creds) {
  std::optional<std::function<bool()>> test_only_generate_response;
  // Check if there's a GET override function (for testing)
  if (g_get_override != nullptr) {
    test_only_generate_response = [request, uri, deadline, on_done,
                                   response]() {
      return g_get_override(request, uri, deadline, on_done, response);
    };
  }
  // Create a name for the request for debugging/tracing purposes
  std::string name =
      absl::StrFormat("HTTP:GET:%s:%s", uri.authority(), uri.path());
  // Format the HTTP GET request
  const grpc_slice request_text =
      grpc_httpcli_format_get_request(request, uri.authority().c_str(),
                                      uri.EncodedPathAndQueryParams().c_str());
  // Create and return the HTTP request object
  return MakeOrphanable<HttpRequest>(
      std::move(uri), request_text, response, deadline, channel_args, on_done,
      pollent, name.c_str(), std::move(test_only_generate_response),
      std::move(channel_creds));
}

// Creates and returns an HTTP POST request
OrphanablePtr<HttpRequest> HttpRequest::Post(
    URI uri, const grpc_channel_args* channel_args,
    grpc_polling_entity* pollent, const grpc_http_request* request,
    Timestamp deadline, grpc_closure* on_done, grpc_http_response* response,
    RefCountedPtr<grpc_channel_credentials> channel_creds) {
  std::optional<std::function<bool()>> test_only_generate_response;
  // Check if there's a POST override function (for testing)
  if (g_post_override != nullptr) {
    test_only_generate_response = [request, uri, deadline, on_done,
                                   response]() {
      return g_post_override(
          request, uri, absl::string_view(request->body, request->body_length),
          deadline, on_done, response);
    };
  }
  // Create a name for the request for debugging/tracing purposes
  std::string name =
      absl::StrFormat("HTTP:POST:%s:%s", uri.authority(), uri.path());
  // Format the HTTP POST request
  const grpc_slice request_text =
      grpc_httpcli_format_post_request(request, uri.authority().c_str(),
                                       uri.EncodedPathAndQueryParams().c_str());
  // Create and return the HTTP request object
  return MakeOrphanable<HttpRequest>(
      std::move(uri), request_text, response, deadline, channel_args, on_done,
      pollent, name.c_str(), std::move(test_only_generate_response),
      std::move(channel_creds));
}

// Creates and returns an HTTP PUT request
OrphanablePtr<HttpRequest> HttpRequest::Put(
    URI uri, const grpc_channel_args* channel_args,
    grpc_polling_entity* pollent, const grpc_http_request* request,
    Timestamp deadline, grpc_closure* on_done, grpc_http_response* response,
    RefCountedPtr<grpc_channel_credentials> channel_creds) {
  std::optional<std::function<bool()>> test_only_generate_response;
  // Check if there's a PUT override function (for testing)
  if (g_put_override != nullptr) {
    test_only_generate_response = [request, uri, deadline, on_done,
                                   response]() {
      return g_put_override(
          request, uri, absl::string_view(request->body, request->body_length),
          deadline, on_done, response);
    };
  }
  // Create a name for the request for debugging/tracing purposes
  std::string name =
      absl::StrFormat("HTTP:PUT:%s:%s", uri.authority(), uri.path());
  // Format the HTTP PUT request
  const grpc_slice request_text =
      grpc_httpcli_format_put_request(request, uri.authority().c_str(),
                                      uri.EncodedPathAndQueryParams().c_str());
  // Create and return the HTTP request object
  return MakeOrphanable<HttpRequest>(
      std::move(uri), request_text, response, deadline, channel_args, on_done,
      pollent, name.c_str(), std::move(test_only_generate_response),
      std::move(channel_creds));
}

// Sets global override functions for HTTP methods (used for testing)
void HttpRequest::SetOverride(grpc_httpcli_get_override get,
                              grpc_httpcli_post_override post,
                              grpc_httpcli_put_override put) {
  g_get_override = get;
  g_post_override = post;
  g_put_override = put;
}

// Sets a global intercept function for handshake completion (used for testing)
void HttpRequest::TestOnlySetOnHandshakeDoneIntercept(
    void (*intercept)(HttpRequest* req)) {
  g_test_only_on_handshake_done_intercept = intercept;
}

// HttpRequest constructor
HttpRequest::HttpRequest(
    URI uri, const grpc_slice& request_text, grpc_http_response* response,
    Timestamp deadline, const grpc_channel_args* channel_args,
    grpc_closure* on_done, grpc_polling_entity* pollent, const char* name,
    std::optional<std::function<bool()>> test_only_generate_response,
    RefCountedPtr<grpc_channel_credentials> channel_creds)
    : uri_(std::move(uri)),
      request_text_(request_text),
      deadline_(deadline),
      channel_args_(CoreConfiguration::Get()
                        .channel_args_preconditioning()
                        .PreconditionChannelArgs(channel_args)
                        .ToC()
                        .release()),
      channel_creds_(std::move(channel_creds)),
      on_done_(on_done),
      resource_quota_(ResourceQuotaFromChannelArgs(channel_args_)),
      pollent_(pollent),
      pollset_set_(grpc_pollset_set_create()),
      test_only_generate_response_(std::move(test_only_generate_response)),
      use_event_engine_dns_resolver_(
          IsEventEngineDnsNonClientChannelEnabled() &&
          !grpc_event_engine::experimental::
              EventEngineExperimentDisabledForPython()),
      resolver_(!use_event_engine_dns_resolver_ ? GetDNSResolver() : nullptr),
      ee_resolver_(
          use_event_engine_dns_resolver_
              ? ChannelArgs::FromC(channel_args_)
                    .GetObjectRef<EventEngine>()
                    ->GetDNSResolver(
                        EventEngine::DNSResolver::ResolverOptions())
              : absl::InternalError("EventEngine DNS is not enabled")) {
  // Initialize HTTP parser, slice buffers, and closures
  grpc_http_parser_init(&parser_, GRPC_HTTP_RESPONSE, response);
  grpc_slice_buffer_init(&incoming_);
  grpc_slice_buffer_init(&outgoing_);
  grpc_iomgr_register_object(&iomgr_obj_, name);
  GRPC_CLOSURE_INIT(&on_read_, OnRead, this, grpc_schedule_on_exec_ctx);
  GRPC_CLOSURE_INIT(&continue_on_read_after_schedule_on_exec_ctx_,
                    ContinueOnReadAfterScheduleOnExecCtx, this,
                    grpc_schedule_on_exec_ctx);
  GRPC_CLOSURE_INIT(&done_write_, DoneWrite, this, grpc_schedule_on_exec_ctx);
  GRPC_CLOSURE_INIT(&continue_done_write_after_schedule_on_exec_ctx_,
                    ContinueDoneWriteAfterScheduleOnExecCtx, this,
                    grpc_schedule_on_exec_ctx);
  CHECK(pollent);
  grpc_polling_entity_add_to_pollset_set(pollent, pollset_set_);
}

// HttpRequest destructor
HttpRequest::~HttpRequest() {
  // Clean up allocated resources
  grpc_channel_args_destroy(channel_args_);
  grpc_http_parser_destroy(&parser_);
  ep_.reset();
  CSliceUnref(request_text_);
  grpc_iomgr_unregister_object(&iomgr_obj_);
  grpc_slice_buffer_destroy(&incoming_);
  grpc_slice_buffer_destroy(&outgoing_);
  grpc_pollset_set_destroy(pollset_set_);
}

// Starts the HTTP request
void HttpRequest::Start() {
  MutexLock lock(&mu_);
  // If there's a test response generator, use it and return if successful
  if (test_only_generate_response_.has_value()) {
    if (test_only_generate_response_.value()()) return;
  }
  // Check if EventEngine DNS resolver is enabled but not available
  if (use_event_engine_dns_resolver_ && !ee_resolver_.ok()) {
    Finish(ee_resolver_.status());
    return;
  }
  Ref().release();
  // Start DNS resolution
  if (use_event_engine_dns_resolver_) {
    (*ee_resolver_)
        ->LookupHostname(
            [this](absl::StatusOr<std::vector<EventEngine::ResolvedAddress>>
                       addresses_or) {
              ExecCtx exec_ctx;
              OnResolved(addresses_or);
            },
            uri_.authority(), uri_.scheme());
  } else {
    dns_request_handle_ = resolver_->LookupHostname(
        [this](absl::StatusOr<std::vector<grpc_resolved_address>> addresses) {
          if (addresses.ok()) {
            std::vector<EventEngine::ResolvedAddress> ee_addresses;
            for (const auto& addr : *addresses) {
              ee_addresses.push_back(
                  grpc_event_engine::experimental::CreateResolvedAddress(addr));
            }
            OnResolved(ee_addresses);
          } else {
            OnResolved(addresses.status());
          }
        },
        uri_.authority(), uri_.scheme(), kDefaultDNSRequestTimeout,
        pollset_set_,
        "");
  }
}

// Cancels the HTTP request
void HttpRequest::Orphan() {
  {
    MutexLock lock(&mu_);
    CHECK(!cancelled_);
    cancelled_ = true;

    // Cancel DNS resolution if in progress
    if (use_event_engine_dns_resolver_) {
      if (*ee_resolver_ != nullptr) {
        ee_resolver_->reset();
      }
    } else {
      if (dns_request_handle_.has_value() &&
          resolver_->Cancel(dns_request_handle_.value())) {
        Finish(GRPC_ERROR_CREATE("cancelled during DNS resolution"));
        Unref();
      }
    }
    // Shutdown handshake if in progress
    if (handshake_mgr_ != nullptr) {
      handshake_mgr_->Shutdown(
          GRPC_ERROR_CREATE("HTTP request cancelled during handshake"));
    }
    ep_.reset();
  }
  Unref();
}

// Appends an error to the overall error status
void HttpRequest::AppendError(grpc_error_handle error) {
  if (overall_error_.ok()) {
    overall_error_ = GRPC_ERROR_CREATE("Failed HTTP/1 client request");
  }
  auto addr_text = ResolvedAddressToURI(addresses_[next_address_ - 1]);
  if (addr_text.ok()) error = AddMessagePrefix(*addr_text, error);
  overall_error_ = grpc_error_add_child(overall_error_, std::move(error));
}

// Handles incoming data from the HTTP response
void HttpRequest::OnReadInternal(grpc_error_handle error) {
  // Process each incoming slice
  for (size_t i = 0; i < incoming_.count; i++) {
    GRPC_TRACE_LOG(http1, INFO)
        << "HTTP response data: " << StringViewFromSlice(incoming_.slices[i]);
    if (GRPC_SLICE_LENGTH(incoming_.slices[i])) {
      have_read_byte_ = 1;
      grpc_error_handle err =
          grpc_http_parser_parse(&parser_, incoming_.slices[i], nullptr);
      if (!err.ok()) {
        Finish(err);
        return;
      }
    }
  }
  // Handle various read completion scenarios
  if (cancelled_) {
    Finish(GRPC_ERROR_CREATE_REFERENCING("HTTP1 request cancelled during read",
                                         &overall_error_, 1));
  } else if (error.ok()) {
    DoRead();
  } else if (!have_read_byte_) {
    NextAddress(error);
  } else {
    Finish(grpc_http_parser_eof(&parser_));
  }
}

// Continues write operation after scheduling on execution context
void HttpRequest::ContinueDoneWriteAfterScheduleOnExecCtx(
    void* arg, grpc_error_handle error) {
  RefCountedPtr<HttpRequest> req(static_cast<HttpRequest*>(arg));
  MutexLock lock(&req->mu_);
  if (error.ok() && !req->cancelled_) {
    req->OnWritten();
  } else {
    req->NextAddress(error);
  }
}

// Starts writing the HTTP request
void HttpRequest::StartWrite() {
  GRPC_TRACE_LOG(http1, INFO)
      << "Sending HTTP1 request: " << StringViewFromSlice(request_text_);
  CSliceRef(request_text_);
  grpc_slice_buffer_add(&outgoing_, request_text_);
  Ref().release();
  grpc_event_engine::experimental::EventEngine::Endpoint::WriteArgs args;
  args.set_max_frame_size(INT_MAX);
  grpc_endpoint_write(ep_.get(), &outgoing_, &done_write_, std::move(args));
}

// Handles handshake completion
void HttpRequest::OnHandshakeDone(absl::StatusOr<HandshakerArgs*> result) {
  // Call test intercept if set
  if (g_test_only_on_handshake_done_intercept != nullptr) {
    g_test_only_on_handshake_done_intercept(this);
  }
  MutexLock lock(&mu_);
  if (!result.ok()) {
    handshake_mgr_.reset();
    NextAddress(result.status());
    return;
  }

  // Store the endpoint and clean up handshake manager
  ep_ = std::move((*result)->endpoint);
  handshake_mgr_.reset();
  if (cancelled_) {
    NextAddress(GRPC_ERROR_CREATE("HTTP request cancelled during handshake"));
    return;
  }
  StartWrite();
}

// Performs the TLS handshake
void HttpRequest::DoHandshake(const EventEngine::ResolvedAddress& addr) {
  // Create security connector
  ChannelArgs args = ChannelArgs::FromC(channel_args_);
  RefCountedPtr<grpc_channel_security_connector> sc =
      channel_creds_->create_security_connector(
          nullptr , uri_.authority().c_str(), &args);
  if (sc == nullptr) {
    Finish(GRPC_ERROR_CREATE_REFERENCING("failed to create security connector",
                                         &overall_error_, 1));
    return;
  }
  // Convert resolved address to URI
  absl::StatusOr<std::string> address = ResolvedAddressToURI(addr);
  if (!address.ok()) {
    Finish(GRPC_ERROR_CREATE_REFERENCING("Failed to extract URI from address",
                                         &overall_error_, 1));
    return;
  }
  // Update channel args with security connector and address
  args = args.SetObject(std::move(sc))
             .Set(GRPC_ARG_TCP_HANDSHAKER_RESOLVED_ADDRESS, address.value());

  // Create and