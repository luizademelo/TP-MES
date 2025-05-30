
// Copyright 2018 gRPC authors.

#include "test/core/tsi/alts/fake_handshaker/fake_handshaker_server.h"

#include <grpc/grpc.h>
#include <grpcpp/impl/sync.h>
#include <grpcpp/security/server_credentials.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>
#include <grpcpp/support/async_stream.h>

#include <memory>
#include <sstream>
#include <string>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/strings/str_format.h"
#include "src/core/util/crash.h"
#include "test/core/tsi/alts/fake_handshaker/handshaker.grpc.pb.h"
#include "test/core/tsi/alts/fake_handshaker/handshaker.pb.h"
#include "test/core/tsi/alts/fake_handshaker/transport_security_common.pb.h"

constexpr char kClientInitFrame[] = "ClientInit";
constexpr char kServerFrame[] = "ServerInitAndFinished";
constexpr char kClientFinishFrame[] = "ClientFinished";

constexpr char kInvalidFrameError[] = "Invalid input frame.";
constexpr char kWrongStateError[] = "Wrong handshake state.";

namespace grpc {
namespace gcp {

class FakeHandshakerService : public HandshakerService::Service {
 public:
  explicit FakeHandshakerService(const std::string& peer_identity)
      : peer_identity_(peer_identity) {}

  Status DoHandshake(
      ServerContext* ,
      ServerReaderWriter<HandshakerResp, HandshakerReq>* stream) override {
    Status status;
    HandshakerContext context;
    HandshakerReq request;
    HandshakerResp response;
    VLOG(2) << "Start a new handshake.";
    while (stream->Read(&request)) {
      status = ProcessRequest(&context, request, &response);
      if (!status.ok()) return WriteErrorResponse(stream, status);
      stream->Write(response);
      if (context.state == COMPLETED) return Status::OK;
      request.Clear();
    }
    return Status::OK;
  }

 private:

  enum HandshakeState { INITIAL, STARTED, SENT, COMPLETED };

  struct HandshakerContext {
    bool is_client = true;
    HandshakeState state = INITIAL;
  };

  Status ProcessRequest(HandshakerContext* context,
                        const HandshakerReq& request,
                        HandshakerResp* response) {
    CHECK(context != nullptr);
    CHECK_NE(response, nullptr);
    response->Clear();
    if (request.has_client_start()) {
      VLOG(2) << "Process client start request.";
      return ProcessClientStart(context, request.client_start(), response);
    } else if (request.has_server_start()) {
      VLOG(2) << "Process server start request.";
      return ProcessServerStart(context, request.server_start(), response);
    } else if (request.has_next()) {
      VLOG(2) << "Process next request.";
      return ProcessNext(context, request.next(), response);
    }
    return Status(StatusCode::INVALID_ARGUMENT, "Request is empty.");
  }

  Status ProcessClientStart(HandshakerContext* context,
                            const StartClientHandshakeReq& request,
                            HandshakerResp* response) {
    CHECK(context != nullptr);
    CHECK_NE(response, nullptr);

    if (context->state != INITIAL) {
      return Status(StatusCode::FAILED_PRECONDITION, kWrongStateError);
    }
    if (request.application_protocols_size() == 0) {
      return Status(StatusCode::INVALID_ARGUMENT,
                    "At least one application protocol needed.");
    }
    if (request.record_protocols_size() == 0) {
      return Status(StatusCode::INVALID_ARGUMENT,
                    "At least one record protocol needed.");
    }

    response->set_out_frames(kClientInitFrame);
    response->set_bytes_consumed(0);
    response->mutable_status()->set_code(StatusCode::OK);

    context->is_client = true;
    context->state = SENT;
    return Status::OK;
  }

  Status ProcessServerStart(HandshakerContext* context,
                            const StartServerHandshakeReq& request,
                            HandshakerResp* response) {
    CHECK(context != nullptr);
    CHECK_NE(response, nullptr);

    if (context->state != INITIAL) {
      return Status(StatusCode::FAILED_PRECONDITION, kWrongStateError);
    }
    if (request.application_protocols_size() == 0) {
      return Status(StatusCode::INVALID_ARGUMENT,
                    "At least one application protocol needed.");
    }
    if (request.handshake_parameters().empty()) {
      return Status(StatusCode::INVALID_ARGUMENT,
                    "At least one set of handshake parameters needed.");
    }

    if (request.in_bytes().empty()) {

      response->set_bytes_consumed(0);
      context->state = STARTED;
    } else {

      if (request.in_bytes() == kClientInitFrame) {
        response->set_out_frames(kServerFrame);
        response->set_bytes_consumed(strlen(kClientInitFrame));
        context->state = SENT;
      } else {
        return Status(StatusCode::UNKNOWN, kInvalidFrameError);
      }
    }
    response->mutable_status()->set_code(StatusCode::OK);
    context->is_client = false;
    return Status::OK;
  }

  Status ProcessNext(HandshakerContext* context,
                     const NextHandshakeMessageReq& request,
                     HandshakerResp* response) {
    CHECK(context != nullptr);
    CHECK_NE(response, nullptr);
    if (context->is_client) {

      if (context->state != SENT) {
        return Status(StatusCode::FAILED_PRECONDITION, kWrongStateError);
      }
      if (request.in_bytes() != kServerFrame) {
        return Status(StatusCode::UNKNOWN, kInvalidFrameError);
      }
      response->set_out_frames(kClientFinishFrame);
      response->set_bytes_consumed(strlen(kServerFrame));
      context->state = COMPLETED;
    } else {

      HandshakeState current_state = context->state;
      if (current_state == STARTED) {
        if (request.in_bytes() != kClientInitFrame) {
          return Status(StatusCode::UNKNOWN, kInvalidFrameError);
        }
        response->set_out_frames(kServerFrame);
        response->set_bytes_consumed(strlen(kClientInitFrame));
        context->state = SENT;
      } else if (current_state == SENT) {

        if (request.in_bytes().substr(0, strlen(kClientFinishFrame)) !=
            kClientFinishFrame) {
          return Status(StatusCode::UNKNOWN, kInvalidFrameError);
        }
        response->set_bytes_consumed(strlen(kClientFinishFrame));
        context->state = COMPLETED;
      } else {
        return Status(StatusCode::FAILED_PRECONDITION, kWrongStateError);
      }
    }

    response->mutable_status()->set_code(StatusCode::OK);
    if (context->state == COMPLETED) {
      *response->mutable_result() = GetHandshakerResult();
    }
    return Status::OK;
  }

  Status WriteErrorResponse(
      ServerReaderWriter<HandshakerResp, HandshakerReq>* stream,
      const Status& status) {
    CHECK(!status.ok());
    HandshakerResp response;
    response.mutable_status()->set_code(status.error_code());
    response.mutable_status()->set_details(status.error_message());
    stream->Write(response);
    return status;
  }

  HandshakerResult GetHandshakerResult() {
    HandshakerResult result;
    result.set_application_protocol("grpc");
    result.set_record_protocol("ALTSRP_GCM_AES128_REKEY");
    result.mutable_peer_identity()->set_service_account(peer_identity_);
    result.mutable_local_identity()->set_service_account("local_identity");
    string key(1024, '\0');
    result.set_key_data(key);
    result.set_max_frame_size(16384);
    result.mutable_peer_rpc_versions()->mutable_max_rpc_version()->set_major(2);
    result.mutable_peer_rpc_versions()->mutable_max_rpc_version()->set_minor(1);
    result.mutable_peer_rpc_versions()->mutable_min_rpc_version()->set_major(2);
    result.mutable_peer_rpc_versions()->mutable_min_rpc_version()->set_minor(1);
    return result;
  }

  const std::string peer_identity_;
};

std::unique_ptr<grpc::Service> CreateFakeHandshakerService(
    const std::string& peer_identity) {
  return std::unique_ptr<grpc::Service>{
      new grpc::gcp::FakeHandshakerService(peer_identity)};
}

}
}
