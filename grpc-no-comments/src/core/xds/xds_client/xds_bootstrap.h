
// Copyright 2019 gRPC authors.

#ifndef GRPC_SRC_CORE_XDS_XDS_CLIENT_XDS_BOOTSTRAP_H
#define GRPC_SRC_CORE_XDS_XDS_CLIENT_XDS_BOOTSTRAP_H

#include <grpc/support/port_platform.h>

#include <string>

#include "src/core/util/json/json.h"

namespace grpc_core {

bool XdsFederationEnabled();
bool XdsDataErrorHandlingEnabled();

class XdsBootstrap {
 public:
  class Node {
   public:
    virtual ~Node() = default;

    virtual const std::string& id() const = 0;
    virtual const std::string& cluster() const = 0;
    virtual const std::string& locality_region() const = 0;
    virtual const std::string& locality_zone() const = 0;
    virtual const std::string& locality_sub_zone() const = 0;
    virtual const Json::Object& metadata() const = 0;
  };

  class XdsServerTarget {
   public:
    virtual ~XdsServerTarget() = default;
    virtual const std::string& server_uri() const = 0;

    virtual std::string Key() const = 0;
    virtual bool Equals(const XdsServerTarget& other) const = 0;
    friend bool operator==(const XdsServerTarget& a, const XdsServerTarget& b) {
      return a.Equals(b);
    }
    friend bool operator!=(const XdsServerTarget& a, const XdsServerTarget& b) {
      return !a.Equals(b);
    }
  };

  class XdsServer {
   public:
    virtual ~XdsServer() = default;

    virtual std::shared_ptr<const XdsServerTarget> target() const = 0;

    virtual bool IgnoreResourceDeletion() const = 0;

    virtual bool FailOnDataErrors() const = 0;
    virtual bool ResourceTimerIsTransientFailure() const = 0;

    virtual bool Equals(const XdsServer& other) const = 0;

    virtual std::string Key() const = 0;

    friend bool operator==(const XdsServer& a, const XdsServer& b) {
      return a.Equals(b);
    }
    friend bool operator!=(const XdsServer& a, const XdsServer& b) {
      return !a.Equals(b);
    }
  };

  class Authority {
   public:
    virtual ~Authority() = default;

    virtual std::vector<const XdsServer*> servers() const = 0;
  };

  virtual ~XdsBootstrap() = default;

  virtual std::string ToString() const = 0;

  virtual std::vector<const XdsServer*> servers() const = 0;

  virtual const Node* node() const = 0;

  virtual const Authority* LookupAuthority(const std::string& name) const = 0;
};

}

#endif
