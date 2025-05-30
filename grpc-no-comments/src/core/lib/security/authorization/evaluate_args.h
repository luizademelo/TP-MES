// Copyright 2021 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_SECURITY_AUTHORIZATION_EVALUATE_ARGS_H
#define GRPC_SRC_CORE_LIB_SECURITY_AUTHORIZATION_EVALUATE_ARGS_H

#include <grpc/grpc_security.h>
#include <grpc/support/port_platform.h>

#include <optional>
#include <string>
#include <vector>

#include "absl/strings/string_view.h"
#include "src/core/call/metadata_batch.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/iomgr/resolved_address.h"

namespace grpc_core {

class EvaluateArgs final {
 public:

  struct PerChannelArgs {
    struct Address {

      grpc_resolved_address address;

      std::string address_str;
      int port = 0;
    };

    PerChannelArgs(grpc_auth_context* auth_context, const ChannelArgs& args);

    absl::string_view transport_security_type;
    absl::string_view spiffe_id;
    std::vector<absl::string_view> uri_sans;
    std::vector<absl::string_view> dns_sans;
    absl::string_view common_name;
    absl::string_view subject;
    Address local_address;
    Address peer_address;
  };

  EvaluateArgs(grpc_metadata_batch* metadata, PerChannelArgs* channel_args)
      : metadata_(metadata), channel_args_(channel_args) {}

  absl::string_view GetPath() const;
  absl::string_view GetAuthority() const;
  absl::string_view GetMethod() const;

  std::optional<absl::string_view> GetHeaderValue(
      absl::string_view key, std::string* concatenated_value) const;

  grpc_resolved_address GetLocalAddress() const;
  absl::string_view GetLocalAddressString() const;
  int GetLocalPort() const;
  grpc_resolved_address GetPeerAddress() const;
  absl::string_view GetPeerAddressString() const;
  int GetPeerPort() const;
  absl::string_view GetTransportSecurityType() const;
  absl::string_view GetSpiffeId() const;
  std::vector<absl::string_view> GetUriSans() const;
  std::vector<absl::string_view> GetDnsSans() const;
  absl::string_view GetCommonName() const;
  absl::string_view GetSubject() const;

 private:
  grpc_metadata_batch* metadata_;
  PerChannelArgs* channel_args_;
};

}

#endif
