
// Copyright 2019 gRPC authors.

#ifndef GRPC_SRC_CORE_RESOLVER_XDS_XDS_RESOLVER_ATTRIBUTES_H
#define GRPC_SRC_CORE_RESOLVER_XDS_XDS_RESOLVER_ATTRIBUTES_H

#include <grpc/support/port_platform.h>

#include "absl/strings/string_view.h"
#include "src/core/service_config/service_config_call_data.h"
#include "src/core/util/unique_type_name.h"
#include "src/core/xds/grpc/xds_route_config.h"

namespace grpc_core {

class XdsClusterAttribute final
    : public ServiceConfigCallData::CallAttributeInterface {
 public:
  static UniqueTypeName TypeName() {
    static UniqueTypeName::Factory kFactory("xds_cluster_name");
    return kFactory.Create();
  }

  explicit XdsClusterAttribute(absl::string_view cluster) : cluster_(cluster) {}

  absl::string_view cluster() const { return cluster_; }
  void set_cluster(absl::string_view cluster) { cluster_ = cluster; }

 private:
  UniqueTypeName type() const override { return TypeName(); }

  absl::string_view cluster_;
};

class XdsRouteStateAttribute
    : public ServiceConfigCallData::CallAttributeInterface {
 public:
  static UniqueTypeName TypeName() {
    static UniqueTypeName::Factory factory("xds_route_state");
    return factory.Create();
  }

  UniqueTypeName type() const override { return TypeName(); }

  virtual bool HasClusterForRoute(absl::string_view cluster_name) const = 0;

  virtual const XdsRouteConfigResource::Route& route() const = 0;
};

}

#endif
