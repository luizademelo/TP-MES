Here's the commented version of the code:

```c++
// Copyright 2019 gRPC authors.

#ifndef GRPC_SRC_CORE_XDS_XDS_CLIENT_XDS_BOOTSTRAP_H
#define GRPC_SRC_CORE_XDS_XDS_CLIENT_XDS_BOOTSTRAP_H

#include <grpc/support/port_platform.h>

#include <string>

#include "src/core/util/json/json.h"

namespace grpc_core {

// Returns whether xDS federation is enabled in the build configuration
bool XdsFederationEnabled();

// Returns whether xDS data error handling is enabled in the build configuration
bool XdsDataErrorHandlingEnabled();

// Abstract base class representing xDS bootstrap configuration
// Provides interfaces to access various components of xDS configuration
class XdsBootstrap {
 public:
  // Represents a Node in xDS configuration, containing node-specific information
  class Node {
   public:
    virtual ~Node() = default;

    // Returns the node identifier
    virtual const std::string& id() const = 0;
    // Returns the node's cluster name
    virtual const std::string& cluster() const = 0;
    // Returns the node's locality region
    virtual const std::string& locality_region() const = 0;
    // Returns the node's locality zone
    virtual const std::string& locality_zone() const = 0;
    // Returns the node's locality sub-zone
    virtual const std::string& locality_sub_zone() const = 0;
    // Returns the node's metadata as a JSON object
    virtual const Json::Object& metadata() const = 0;
  };

  // Represents an xDS server target with comparison capabilities
  class XdsServerTarget {
   public:
    virtual ~XdsServerTarget() = default;
    // Returns the server URI
    virtual const std::string& server_uri() const = 0;

    // Returns a unique key for this server target
    virtual std::string Key() const = 0;
    // Compares this server target with another for equality
    virtual bool Equals(const XdsServerTarget& other) const = 0;
    
    // Equality operator overload
    friend bool operator==(const XdsServerTarget& a, const XdsServerTarget& b) {
      return a.Equals(b);
    }
    // Inequality operator overload
    friend bool operator!=(const XdsServerTarget& a, const XdsServerTarget& b) {
      return !a.Equals(b);
    }
  };

  // Represents an xDS server with configuration and comparison capabilities
  class XdsServer {
   public:
    virtual ~XdsServer() = default;

    // Returns the server target information
    virtual std::shared_ptr<const XdsServerTarget> target() const = 0;

    // Returns whether resource deletion should be ignored
    virtual bool IgnoreResourceDeletion() const = 0;
    // Returns whether to fail on data errors
    virtual bool FailOnDataErrors() const = 0;
    // Returns whether resource timer should be considered as transient failure
    virtual bool ResourceTimerIsTransientFailure() const = 0;

    // Compares this server with another for equality
    virtual bool Equals(const XdsServer& other) const = 0;
    // Returns a unique key for this server
    virtual std::string Key() const = 0;

    // Equality operator overload
    friend bool operator==(const XdsServer& a, const XdsServer& b) {
      return a.Equals(b);
    }
    // Inequality operator overload
    friend bool operator!=(const XdsServer& a, const XdsServer& b) {
      return !a.Equals(b);
    }
  };

  // Represents an xDS authority containing multiple servers
  class Authority {
   public:
    virtual ~Authority() = default;

    // Returns the list of servers for this authority
    virtual std::vector<const XdsServer*> servers() const = 0;
  };

  virtual ~XdsBootstrap() = default;

  // Returns a string representation of the bootstrap configuration
  virtual std::string ToString() const = 0;

  // Returns the list of xDS servers
  virtual std::vector<const XdsServer*> servers() const = 0;

  // Returns the node information
  virtual const Node* node() const = 0;

  // Looks up an authority by name
  virtual const Authority* LookupAuthority(const std::string& name) const = 0;
};

}  // namespace grpc_core

#endif  // GRPC_SRC_CORE_XDS_XDS_CLIENT_XDS_BOOTSTRAP_H
```

The comments added:
1. Explain the purpose of each class and its role in the xDS bootstrap configuration
2. Document each virtual method's purpose and return value
3. Clarify the purpose of operator overloads
4. Add namespace closing comment
5. Add header guard closing comment
6. Explain the global configuration functions at the top
7. Maintained consistent style with existing comments

The comments are designed to help future developers understand:
- The overall structure of the xDS bootstrap configuration
- The relationships between different components
- The purpose of each method and when it might be used
- The comparison semantics between objects