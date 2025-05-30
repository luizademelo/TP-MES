
// Copyright 2022 gRPC authors.

#ifndef GRPC_SRC_CORE_XDS_XDS_CLIENT_XDS_TRANSPORT_H
#define GRPC_SRC_CORE_XDS_XDS_CLIENT_XDS_TRANSPORT_H

#include <memory>
#include <string>

#include "absl/status/status.h"
#include "absl/strings/string_view.h"
#include "src/core/util/dual_ref_counted.h"
#include "src/core/util/orphanable.h"
#include "src/core/xds/xds_client/xds_bootstrap.h"

namespace grpc_core {

class XdsTransportFactory : public DualRefCounted<XdsTransportFactory> {
 public:

  class XdsTransport : public DualRefCounted<XdsTransport> {
   public:

    class StreamingCall : public InternallyRefCounted<StreamingCall> {
     public:

      class EventHandler {
       public:
        virtual ~EventHandler() = default;

        virtual void OnRequestSent(bool ok) = 0;

        virtual void OnRecvMessage(absl::string_view payload) = 0;

        virtual void OnStatusReceived(absl::Status status) = 0;
      };

      virtual void SendMessage(std::string payload) = 0;

      virtual void StartRecvMessage() = 0;
    };

    class ConnectivityFailureWatcher
        : public RefCounted<ConnectivityFailureWatcher> {
     public:

      virtual void OnConnectivityFailure(absl::Status status) = 0;
    };

    explicit XdsTransport(const char* trace = nullptr)
        : DualRefCounted(trace) {}

    virtual void StartConnectivityFailureWatch(
        RefCountedPtr<ConnectivityFailureWatcher> watcher) = 0;

    virtual void StopConnectivityFailureWatch(
        const RefCountedPtr<ConnectivityFailureWatcher>& watcher) = 0;

    virtual OrphanablePtr<StreamingCall> CreateStreamingCall(
        const char* method,
        std::unique_ptr<StreamingCall::EventHandler> event_handler) = 0;

    virtual void ResetBackoff() = 0;
  };

  virtual RefCountedPtr<XdsTransport> GetTransport(
      const XdsBootstrap::XdsServerTarget& server, absl::Status* status) = 0;
};

}

#endif
