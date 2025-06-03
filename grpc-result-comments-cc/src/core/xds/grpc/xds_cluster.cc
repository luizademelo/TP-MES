Here's the commented version of the code:

```c++
// Copyright 2018 gRPC authors.

#include "src/core/xds/grpc/xds_cluster.h"

#include "absl/strings/str_cat.h"
#include "absl/strings/str_join.h"
#include "src/core/util/json/json_writer.h"
#include "src/core/util/match.h"
#include "src/core/util/time.h"
#include "src/core/xds/grpc/xds_common_types.h"

namespace grpc_core {

// Converts the XdsClusterResource object to a human-readable string representation
// containing all configured fields and their values.
std::string XdsClusterResource::ToString() const {
  std::vector<std::string> contents;  // Stores individual field descriptions
  
  // Handle different cluster types (EDS, LogicalDNS, Aggregate) using pattern matching
  Match(
      type,
      // Case 1: EDS cluster type
      [&](const Eds& eds) {
        contents.push_back("type=EDS");
        // Add EDS service name if specified
        if (!eds.eds_service_name.empty()) {
          contents.push_back(
              absl::StrCat("eds_service_name=", eds.eds_service_name));
        }
      },
      // Case 2: LogicalDNS cluster type
      [&](const LogicalDns& logical_dns) {
        contents.push_back("type=LOGICAL_DNS");
        contents.push_back(absl::StrCat("dns_hostname=", logical_dns.hostname));
      },
      // Case 3: Aggregate cluster type
      [&](const Aggregate& aggregate) {
        contents.push_back("type=AGGREGATE");
        contents.push_back(absl::StrCat(
            "prioritized_cluster_names=[",
            absl::StrJoin(aggregate.prioritized_cluster_names, ", "), "]"));
      });
  
  // Add load balancing policy configuration in JSON format
  contents.push_back(absl::StrCat("lb_policy_config=",
                                  JsonDump(Json::FromArray(lb_policy_config))));
  
  // Add LRS (Load Reporting Service) server name if configured
  if (lrs_load_reporting_server != nullptr) {
    contents.push_back(absl::StrCat("lrs_load_reporting_server_name=",
                                    lrs_load_reporting_server->server_uri()));
  }
  
  // Add backend metric propagation setting if configured
  if (lrs_backend_metric_propagation != nullptr) {
    contents.push_back(
        absl::StrCat("lrs_backend_metric_propagation=",
                     lrs_backend_metric_propagation->AsString()));
  }
  
  // Add HTTP CONNECT usage flag if enabled
  if (use_http_connect) contents.push_back("use_http_connect=true");
  
  // Add TLS context if configured
  if (!common_tls_context.Empty()) {
    contents.push_back(
        absl::StrCat("common_tls_context=", common_tls_context.ToString()));
  }
  
  // Add connection idle timeout if non-zero
  if (connection_idle_timeout != Duration::Zero()) {
    contents.push_back(absl::StrCat("connection_idle_timeout=",
                                    connection_idle_timeout.ToString()));
  }
  
  // Add max concurrent requests setting
  contents.push_back(
      absl::StrCat("max_concurrent_requests=", max_concurrent_requests));
  
  // Add override host statuses
  contents.push_back(absl::StrCat("override_host_statuses=",
                                  override_host_statuses.ToString()));
  
  // Add metadata if present
  if (!metadata.empty()) {
    contents.push_back(absl::StrCat("metadata={", metadata.ToString(), "}"));
  }
  
  // Combine all field descriptions into a single string
  return absl::StrCat("{", absl::StrJoin(contents, ", "), "}");
}

}  // namespace grpc_core
```

Key improvements in the comments:
1. Added a high-level description of what the method does
2. Explained the purpose of the `contents` vector
3. Documented each cluster type case in the pattern matching
4. Added comments for each configuration field being added to the output
5. Explained the final string construction
6. Added namespace closing comment
7. Maintained consistent comment style throughout

The comments now provide a clear understanding of:
- The overall purpose of the method
- What each section of the code is responsible for
- The meaning of each configuration field being included
- The structure of the output string