
// Copyright 2022 gRPC authors.

#include "test/cpp/interop/istio_echo_server_lib.h"

#include <grpcpp/client_context.h>
#include <grpcpp/grpcpp.h>

#include <thread>

#include "absl/log/log.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_format.h"
#include "absl/strings/str_split.h"
#include "absl/synchronization/blocking_counter.h"
#include "src/core/util/host_port.h"
#include "src/proto/grpc/testing/istio_echo.pb.h"

using proto::EchoRequest;
using proto::EchoResponse;
using proto::EchoTestService;
using proto::ForwardEchoRequest;
using proto::ForwardEchoResponse;

namespace grpc {
namespace testing {
namespace {

const absl::string_view kRequestIdField = "x-request-id";
const absl::string_view kServiceVersionField = "ServiceVersion";

const absl::string_view kStatusCodeField = "StatusCode";

const absl::string_view kHostField = "Host";
const absl::string_view kHostnameField = "Hostname";

const absl::string_view kRequestHeader = "RequestHeader";

const absl::string_view kIpField = "IP";

absl::string_view StringRefToStringView(const string_ref& r) {
  return absl::string_view(r.data(), r.size());
}

struct EchoCall {
  grpc::ClientContext context;
  proto::EchoResponse response;
  Status status;
};

}

EchoTestServiceImpl::EchoTestServiceImpl(std::string hostname,
                                         std::string service_version,
                                         std::string forwarding_address)
    : hostname_(std::move(hostname)),
      service_version_(std::move(service_version)),
      forwarding_address_(std::move(forwarding_address)) {
  forwarding_stub_ = EchoTestService::NewStub(
      CreateChannel(forwarding_address_, InsecureChannelCredentials()));
}

Status EchoTestServiceImpl::Echo(ServerContext* context,
                                 const EchoRequest* request,
                                 EchoResponse* response) {
  std::string s;
  absl::StrAppend(&s, kHostField, "=",
                  StringRefToStringView(context->ExperimentalGetAuthority()),
                  "\n");
  const std::multimap<string_ref, string_ref> metadata =
      context->client_metadata();
  for (const auto& kv : metadata) {

    if (kv.first.ends_with("-bin")) {
      continue;
    }
    absl::StrAppend(&s, kRequestHeader, "=", StringRefToStringView(kv.first),
                    ":", StringRefToStringView(kv.second), "\n");
  }
  absl::string_view host;
  absl::string_view port;
  std::string peer = context->peer();
  grpc_core::SplitHostPort(peer, &host, &port);

  absl::StrAppend(&s, kServiceVersionField, "=", this->service_version_, "\n");
  absl::StrAppend(&s, kIpField, "=", host, "\n");
  absl::StrAppend(&s, kStatusCodeField, "=", std::to_string(200), "\n");
  absl::StrAppend(&s, kHostnameField, "=", this->hostname_, "\n");
  absl::StrAppend(&s, "Echo=", request->message(), "\n");
  response->set_message(s);
  LOG(INFO) << "Echo response:\n" << s;
  return Status::OK;
}

Status EchoTestServiceImpl::ForwardEcho(ServerContext* context,
                                        const ForwardEchoRequest* request,
                                        ForwardEchoResponse* response) {
  std::string raw_url = request->url();
  size_t colon = raw_url.find_first_of(':');
  std::string scheme;
  if (colon == std::string::npos) {
    return Status(
        StatusCode::INVALID_ARGUMENT,
        absl::StrFormat("No protocol configured for url %s", raw_url));
  }
  scheme = raw_url.substr(0, colon);
  std::shared_ptr<Channel> channel;
  if (scheme == "xds") {

    LOG(INFO) << "Creating channel to " << raw_url << " using xDS Creds";
    channel =
        CreateChannel(raw_url, XdsCredentials(InsecureChannelCredentials()));
  } else if (scheme == "grpc") {

    absl::string_view address = absl::StripPrefix(raw_url, "grpc://");
    LOG(INFO) << "Creating channel to " << address;
    channel = CreateChannel(std::string(address), InsecureChannelCredentials());
  } else {
    LOG(INFO) << "Protocol " << scheme << " not supported. Forwarding to "
              << forwarding_address_;
    ClientContext forwarding_ctx;
    forwarding_ctx.set_deadline(context->deadline());
    return forwarding_stub_->ForwardEcho(&forwarding_ctx, *request, response);
  }
  auto stub = EchoTestService::NewStub(channel);
  auto count = request->count() == 0 ? 1 : request->count();

  std::chrono::duration<double> duration_per_query =
      std::chrono::nanoseconds::zero();
  if (request->qps() > 0) {
    duration_per_query =
        std::chrono::nanoseconds(std::chrono::seconds(1)) / request->qps();
  }
  std::vector<EchoCall> calls(count);
  EchoRequest echo_request;
  echo_request.set_message(request->message());
  absl::BlockingCounter counter(count);
  for (int i = 0; i < count; ++i) {
    calls[i].context.AddMetadata(std::string(kRequestIdField),
                                 std::to_string(i));
    for (const auto& header : request->headers()) {
      if (header.key() != kHostField) {
        calls[i].context.AddMetadata(header.key(), header.value());
      }
    }
    constexpr int kDefaultTimeout = 5 * 1000 * 1000 ;
    std::chrono::system_clock::time_point deadline =
        std::chrono::system_clock::now() +
        std::chrono::microseconds(request->timeout_micros() > 0
                                      ? request->timeout_micros()
                                      : kDefaultTimeout);
    calls[i].context.set_deadline(deadline);
    stub->async()->Echo(&calls[i].context, &echo_request, &calls[i].response,
                        [&, index = i](Status s) {
                          calls[index].status = s;
                          counter.DecrementCount();
                        });
    std::this_thread::sleep_for(duration_per_query);
  }

  counter.Wait();
  for (int i = 0; i < count; ++i) {
    if (calls[i].status.ok()) {
      std::string body;

      absl::StrAppend(&body, absl::StrFormat("[%d] grpcecho.Echo(%s)\n", i,
                                             request->message()));
      auto contents =
          absl::StrSplit(calls[i].response.message(), '\n', absl::SkipEmpty());
      for (const auto& line : contents) {
        absl::StrAppend(&body, absl::StrFormat("[%d body] %s\n", i, line));
      }
      response->add_output(body);
      LOG(INFO) << "Forward Echo response:" << i << "\n" << body;
    } else {
      LOG(ERROR) << "RPC " << i << " failed " << calls[i].status.error_code()
                 << ": " << calls[i].status.error_message();
      response->clear_output();
      return calls[i].status;
    }
  }
  return Status::OK;
}

}
}
