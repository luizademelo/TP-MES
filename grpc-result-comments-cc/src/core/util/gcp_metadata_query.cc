Here's the commented version of the code:

```c++
// Copyright 2023 gRPC authors.

#include "src/core/util/gcp_metadata_query.h"

#include <grpc/credentials.h>
#include <grpc/grpc.h>
#include <grpc/grpc_security.h>
#include <grpc/support/port_platform.h>
#include <string.h>

#include <memory>
#include <utility>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/str_format.h"
#include "absl/strings/string_view.h"
#include "src/core/credentials/transport/transport_credentials.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/status_helper.h"
#include "src/core/util/time.h"
#include "src/core/util/uri.h"

namespace grpc_core {

// Constants for GCP metadata attributes
constexpr const char GcpMetadataQuery::kZoneAttribute[];
constexpr const char GcpMetadataQuery::kClusterNameAttribute[];
constexpr const char GcpMetadataQuery::kRegionAttribute[];
constexpr const char GcpMetadataQuery::kInstanceIdAttribute[];
constexpr const char GcpMetadataQuery::kIPv6Attribute[];

// Constructor for GCP metadata query with default metadata server name
GcpMetadataQuery::GcpMetadataQuery(
    std::string attribute, grpc_polling_entity* pollent,
    absl::AnyInvocable<void(std::string ,
                            absl::StatusOr<std::string> )>
        callback,
    Duration timeout)
    : GcpMetadataQuery("metadata.google.internal.", std::move(attribute),
                       pollent, std::move(callback), timeout) {}

// Main constructor for GCP metadata query
GcpMetadataQuery::GcpMetadataQuery(
    std::string metadata_server_name, std::string attribute,
    grpc_polling_entity* pollent,
    absl::AnyInvocable<void(std::string ,
                            absl::StatusOr<std::string> )>
        callback,
    Duration timeout)
    : InternallyRefCounted<GcpMetadataQuery>(nullptr, 2),  // Initialize ref count
      attribute_(std::move(attribute)),  // Store the attribute to query
      callback_(std::move(callback)) {   // Store the callback function
  // Initialize closure for when the request completes
  GRPC_CLOSURE_INIT(&on_done_, OnDone, this, nullptr);
  
  // Create URI for the metadata server request
  auto uri =
      URI::Create("http", "", std::move(metadata_server_name),
                  attribute_, {} , "" );
  CHECK(uri.ok());  // Verify URI creation was successful
  
  // Set up HTTP request headers
  grpc_http_request request;
  memset(&request, 0, sizeof(grpc_http_request));
  // Add required GCP metadata header
  grpc_http_header header = {const_cast<char*>("Metadata-Flavor"),
                             const_cast<char*>("Google")};
  request.hdr_count = 1;
  request.hdrs = &header;
  
  // Create and start HTTP request to metadata server
  http_request_ = HttpRequest::Get(
      std::move(*uri), nullptr , pollent, &request,
      Timestamp::Now() + timeout, &on_done_, &response_,
      RefCountedPtr<grpc_channel_credentials>(
          grpc_insecure_credentials_create()));  // Use insecure credentials
  http_request_->Start();
}

// Destructor - cleans up HTTP response
GcpMetadataQuery::~GcpMetadataQuery() {
  grpc_http_response_destroy(&response_);
}

// Orphan handler - cancels any pending request and releases resources
void GcpMetadataQuery::Orphan() {
  http_request_.reset();  // Cancel any pending HTTP request
  Unref();  // Decrement reference count
}

// Callback for when metadata query completes
void GcpMetadataQuery::OnDone(void* arg, grpc_error_handle error) {
  auto* self = static_cast<GcpMetadataQuery*>(arg);
  
  // Log query results
  GRPC_TRACE_LOG(metadata_query, INFO)
      << "MetadataServer Query for " << self->attribute_
      << ": HTTP status: " << self->response_.status
      << ", error: " << StatusToString(error);
  
  absl::StatusOr<std::string> result;
  
  // Handle different error cases
  if (!error.ok()) {
    // Request failed with error
    result = absl::UnavailableError(absl::StrFormat(
        "MetadataServer Query failed for %s: %s", self->attribute_.c_str(),
        StatusToString(error).c_str()));
  } else if (self->response_.status != 200) {
    // Request returned non-200 status
    result = absl::UnavailableError(absl::StrFormat(
        "MetadataServer Query received non-200 status for %s: %s",
        self->attribute_.c_str(), StatusToString(error).c_str()));
  } else if (self->attribute_ == kZoneAttribute) {
    // Special handling for zone attribute which requires parsing
    absl::string_view body(self->response_.body, self->response_.body_length);
    size_t pos = body.find_last_of('/');
    if (pos == body.npos) {
      // Couldn't parse zone information
      result = absl::UnavailableError(
          absl::StrFormat("MetadataServer Could not parse zone: %s",
                          std::string(body).c_str()));
      GRPC_TRACE_LOG(metadata_query, INFO) << result.status();
    } else {
      // Extract zone from path
      result = std::string(body.substr(pos + 1));
    }
  } else {
    // For other attributes, return the raw response body
    result = std::string(self->response_.body, self->response_.body_length);
  }
  
  // Move callback and attribute to local variables before Unref
  auto callback = std::move(self->callback_);
  auto attribute = std::move(self->attribute_);
  
  // Release reference to self
  self->Unref();
  
  // Invoke the callback with results
  return callback(std::move(attribute), std::move(result));
}

}  // namespace grpc_core
```