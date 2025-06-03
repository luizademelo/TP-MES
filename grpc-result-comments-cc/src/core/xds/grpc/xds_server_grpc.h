Here's the commented version of the code:

```c++
// Copyright 2019 gRPC authors.

#ifndef GRPC_SRC_CORE_XDS_GRPC_XDS_SERVER_GRPC_H
#define GRPC_SRC_CORE_XDS_GRPC_XDS_SERVER_GRPC_H

#include <set>
#include <string>

#include "src/core/credentials/transport/channel_creds_registry.h"
#include "src/core/util/json/json.h"
#include "src/core/util/json/json_args.h"
#include "src/core/util/json/json_object_loader.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/validation_errors.h"
#include "src/core/xds/grpc/xds_server_grpc_interface.h"
#include "src/core/xds/xds_client/xds_bootstrap.h"

namespace grpc_core {

// Represents a gRPC XDS server target with its URI and channel credentials configuration
class GrpcXdsServerTarget final : public GrpcXdsServerInterface {
 public:
  // Constructs a GrpcXdsServerTarget with the given server URI and channel credentials
  explicit GrpcXdsServerTarget(
      std::string server_uri,
      RefCountedPtr<ChannelCredsConfig> channel_creds_config)
      : server_uri_(std::move(server_uri)),
        channel_creds_config_(std::move(channel_creds_config)) {}

  // Compares this server target with another for equality
  bool Equals(const XdsServerTarget& other) const override;
  // Returns a unique key identifying this server target
  std::string Key() const override;
  // Returns the server URI
  const std::string& server_uri() const override { return server_uri_; }
  // Returns the channel credentials configuration
  RefCountedPtr<ChannelCredsConfig> channel_creds_config() const override {
    return channel_creds_config_;
  }

 private:
  std::string server_uri_;  // The URI of the XDS server
  RefCountedPtr<ChannelCredsConfig> channel_creds_config_;  // Channel credentials configuration
};

// Represents a gRPC XDS server with its configuration and features
class GrpcXdsServer final : public XdsBootstrap::XdsServer {
 public:
  // Whether to ignore resource deletion notifications from this server
  bool IgnoreResourceDeletion() const override;
  // Whether to fail on data errors from this server
  bool FailOnDataErrors() const override;
  // Whether resource timer failures should be treated as transient
  bool ResourceTimerIsTransientFailure() const override;
  // Whether this is a trusted XDS server
  bool TrustedXdsServer() const;
  // Compares this XDS server with another for equality
  bool Equals(const XdsServer& other) const override;
  // Returns a unique key identifying this XDS server
  std::string Key() const override;
  // Returns the server target configuration
  std::shared_ptr<const XdsBootstrap::XdsServerTarget> target() const override {
    return server_target_;
  }
  // Returns the JSON loader interface for parsing server configuration
  static const JsonLoaderInterface* JsonLoader(const JsonArgs&);
  // Handles post-load processing of JSON configuration
  void JsonPostLoad(const Json& json, const JsonArgs& args,
                    ValidationErrors* errors);

 private:
  std::shared_ptr<GrpcXdsServerTarget> server_target_;  // The server target configuration
  std::set<std::string> server_features_;  // Set of features supported by this server
};

}

#endif
```

Key improvements in the comments:
1. Added class-level descriptions explaining the purpose of each class
2. Added detailed comments for each public method explaining their functionality
3. Added comments for private member variables
4. Maintained consistency in comment style
5. Ensured comments explain both what the code does and why (where relevant)
6. Kept existing copyright notice and include guards unchanged

The comments now provide a clear understanding of the class hierarchy, purpose of each component, and how they interact with each other.