
// Copyright 2021 gRPC authors.

#ifndef GRPC_SRC_CORE_XDS_XDS_CLIENT_XDS_RESOURCE_TYPE_H
#define GRPC_SRC_CORE_XDS_XDS_CLIENT_XDS_RESOURCE_TYPE_H
#include <grpc/support/port_platform.h>

#include <memory>
#include <optional>
#include <string>

#include "absl/status/statusor.h"
#include "absl/strings/string_view.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/xds/xds_client/xds_bootstrap.h"
#include "upb/mem/arena.h"
#include "upb/reflection/def.h"

namespace grpc_core {

class XdsClient;

class XdsResourceType {
 public:

  struct DecodeContext {
    XdsClient* client;
    const XdsBootstrap::XdsServer& server;
    upb_DefPool* symtab;
    upb_Arena* arena;
  };

  struct ResourceData {
    virtual ~ResourceData() = default;
  };

  struct DecodeResult {

    std::optional<std::string> name;

    absl::StatusOr<std::shared_ptr<const ResourceData>> resource;
  };

  virtual ~XdsResourceType() = default;

  virtual absl::string_view type_url() const = 0;

  virtual DecodeResult Decode(const DecodeContext& context,
                              absl::string_view serialized_resource) const = 0;

  virtual bool ResourcesEqual(const ResourceData* r1,
                              const ResourceData* r2) const = 0;

  virtual bool AllResourcesRequiredInSotW() const { return false; }

  // Note: This won't actually work properly until upb adds support for

  virtual void InitUpbSymtab(XdsClient*, upb_DefPool*) const {}
};

}

#endif
