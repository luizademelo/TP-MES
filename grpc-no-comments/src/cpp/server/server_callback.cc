
// Copyright 2019 gRPC authors.

#include <grpcpp/support/server_callback.h>

namespace grpc {
namespace internal {

void ServerCallbackCall::ScheduleOnDone(bool inline_ondone) {
  if (inline_ondone) {
    CallOnDone();
    return;
  }
  RunAsync([this]() { CallOnDone(); });
}

void ServerCallbackCall::CallOnCancel(ServerReactor* reactor) {
  if (reactor->InternalInlineable()) {
    reactor->OnCancel();
    return;
  }
  Ref();
  RunAsync([this, reactor]() {
    reactor->OnCancel();
    MaybeDone();
  });
}

}
}
