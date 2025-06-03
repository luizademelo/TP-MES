Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

// Includes necessary headers for HTTP server filter implementation
#include "src/core/ext/filters/http/server/http_server_filter.h"

#include <grpc/impl/channel_arg_names.h>
#include <grpc/status.h>
#include <grpc/support/port_platform.h>

#include <functional>
#include <memory>
#include <optional>
#include <utility>

#include "absl/base/attributes.h"
#include "absl/log/log.h"
#include "absl/strings/string_view.h"
#include "src/core/call/metadata_batch.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/channel/channel_stack.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/lib/promise/activity.h"
#include "src/core/lib/promise/context.h"
#include "src/core/lib/promise/map.h"
#include "src/core/lib/promise/pipe.h"
#include "src/core/lib/promise/poll.h"
#include "src/core/lib/promise/promise.h"
#include "src/core/lib/resource_quota/arena.h"
#include "src/core/lib/slice/percent_encoding.h"
#include "src/core/lib/slice/slice.h"
#include "src/core/util/latent_see.h"

namespace grpc_core {

// Define the HTTP server filter as a promise-based server-side filter
// that examines server initial metadata
const grpc_channel_filter HttpServerFilter::kFilter =
    MakePromiseBasedFilter<HttpServerFilter, FilterEndpoint::kServer,
                           kFilterExaminesServerInitialMetadata>();

namespace {
// Helper function to process outgoing metadata
// Percent-encodes the grpc-message metadata if present
void FilterOutgoingMetadata(ServerMetadata* md) {
  if (Slice* grpc_message = md->get_pointer(GrpcMessageMetadata())) {
    *grpc_message = PercentEncodeSlice(std::move(*grpc_message),
                                       PercentEncodingType::Compatible);
  }
}

// Creates a server metadata handle for malformed requests
// with the given explanation as the error message
ServerMetadataHandle MalformedRequest(absl::string_view explanation) {
  auto* arena = GetContext<Arena>();
  auto hdl = arena->MakePooled<ServerMetadata>();
  hdl->Set(GrpcStatusMetadata(), GRPC_STATUS_UNKNOWN);
  hdl->Set(GrpcMessageMetadata(), Slice::FromStaticString(explanation));
  hdl->Set(GrpcTarPit(), Empty());  // Indicates this is a bad request
  return hdl;
}
}

// Handles client initial metadata validation
// Returns nullptr if metadata is valid, or error metadata if invalid
ServerMetadataHandle HttpServerFilter::Call::OnClientInitialMetadata(
    ClientMetadata& md, HttpServerFilter* filter) {
  GRPC_LATENT_SEE_INNER_SCOPE(
      "HttpServerFilter::Call::OnClientInitialMetadata");
  
  // Validate HTTP method
  auto method = md.get(HttpMethodMetadata());
  if (method.has_value()) {
    switch (*method) {
      case HttpMethodMetadata::kPost:
        break;  // POST is always allowed
      case HttpMethodMetadata::kPut:
        if (filter->allow_put_requests_) {
          break;  // PUT only allowed if explicitly permitted
        }
        [[fallthrough]];
      case HttpMethodMetadata::kInvalid:
      case HttpMethodMetadata::kGet:
        return MalformedRequest("Bad method header");
    }
  } else {
    return MalformedRequest("Missing :method header");
  }

  // Validate TE (transfer-encoding) header
  auto te = md.Take(TeMetadata());
  if (te == TeMetadata::kTrailers) {
    // Valid case - trailers are allowed
  } else if (!te.has_value()) {
    return MalformedRequest("Missing :te header");
  } else {
    return MalformedRequest("Bad :te header");
  }

  // Validate scheme header
  auto scheme = md.Take(HttpSchemeMetadata());
  if (scheme.has_value()) {
    if (*scheme == HttpSchemeMetadata::kInvalid) {
      return MalformedRequest("Bad :scheme header");
    }
  } else {
    return MalformedRequest("Missing :scheme header");
  }

  // Remove content-type header as it's not needed
  md.Remove(ContentTypeMetadata());

  // Validate path header
  Slice* path_slice = md.get_pointer(HttpPathMetadata());
  if (path_slice == nullptr) {
    return MalformedRequest("Missing :path header");
  }

  // Handle authority/host headers (host is legacy, authority is preferred)
  if (md.get_pointer(HttpAuthorityMetadata()) == nullptr) {
    std::optional<Slice> host = md.Take(HostMetadata());
    if (host.has_value()) {
      md.Set(HttpAuthorityMetadata(), std::move(*host));
    }
  }

  // Final authority validation
  if (md.get_pointer(HttpAuthorityMetadata()) == nullptr) {
    return MalformedRequest("Missing :authority header");
  }

  // Optionally remove user-agent header based on configuration
  if (!filter->surface_user_agent_) {
    md.Remove(UserAgentMetadata());
  }

  // Return nullptr to indicate valid metadata
  return nullptr;
}

// Processes server initial metadata before sending to client
void HttpServerFilter::Call::OnServerInitialMetadata(ServerMetadata& md) {
  GRPC_LATENT_SEE_INNER_SCOPE(
      "HttpServerFilter::Call::OnServerInitialMetadata");
  GRPC_TRACE_LOG(call, INFO)
      << GetContext<Activity>()->DebugTag() << "[http-server] Write metadata";
  // Process outgoing metadata and set standard HTTP/2 response headers
  FilterOutgoingMetadata(&md);
  md.Set(HttpStatusMetadata(), 200);  // HTTP 200 OK
  md.Set(ContentTypeMetadata(), ContentTypeMetadata::kApplicationGrpc);
}

// Processes server trailing metadata before sending to client
void HttpServerFilter::Call::OnServerTrailingMetadata(ServerMetadata& md) {
  GRPC_LATENT_SEE_INNER_SCOPE(
      "HttpServerFilter::Call::OnServerTrailingMetadata");
  FilterOutgoingMetadata(&md);
}

// Factory function to create an HTTP server filter instance
// Configures the filter based on channel arguments
absl::StatusOr<std::unique_ptr<HttpServerFilter>> HttpServerFilter::Create(
    const ChannelArgs& args, ChannelFilter::Args) {
  return std::make_unique<HttpServerFilter>(
      args, 
      // Whether to surface user-agent header (default: true)
      args.GetBool(GRPC_ARG_SURFACE_USER_AGENT).value_or(true),
      // Whether to allow PUT requests (default: false)
      args.GetBool(
              GRPC_ARG_DO_NOT_USE_UNLESS_YOU_HAVE_PERMISSION_FROM_GRPC_TEAM_ALLOW_BROKEN_PUT_REQUESTS)
          .value_or(false));
}

}
```