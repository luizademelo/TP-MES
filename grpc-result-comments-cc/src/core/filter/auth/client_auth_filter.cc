Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

// Include necessary gRPC headers for security functionality
#include <grpc/credentials.h>
#include <grpc/grpc_security.h>
#include <grpc/grpc_security_constants.h>
#include <grpc/support/alloc.h>
#include <grpc/support/port_platform.h>
#include <grpc/support/string_util.h>
#include <string.h>

// Standard C++ headers
#include <functional>
#include <memory>
#include <type_traits>
#include <utility>

// Abseil status headers
#include "absl/status/status.h"
#include "absl/status/statusor.h"

// gRPC core implementation headers
#include "src/core/call/metadata_batch.h"
#include "src/core/call/security_context.h"
#include "src/core/call/status_util.h"
#include "src/core/credentials/call/call_credentials.h"
#include "src/core/credentials/transport/security_connector.h"
#include "src/core/filter/auth/auth_filters.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/channel/channel_fwd.h"
#include "src/core/lib/channel/channel_stack.h"
#include "src/core/lib/channel/promise_based_filter.h"
#include "src/core/lib/promise/arena_promise.h"
#include "src/core/lib/promise/context.h"
#include "src/core/lib/promise/promise.h"
#include "src/core/lib/promise/seq.h"
#include "src/core/lib/promise/try_seq.h"
#include "src/core/lib/resource_quota/arena.h"
#include "src/core/lib/transport/transport.h"
#include "src/core/transport/auth_context.h"
#include "src/core/util/debug_location.h"
#include "src/core/util/ref_counted_ptr.h"

// Maximum number of credentials metadata entries allowed
#define MAX_CREDENTIALS_METADATA_COUNT 4

// Copies contents of one auth metadata context to another
// Handles proper reference counting for channel_auth_context
void grpc_auth_metadata_context_copy(grpc_auth_metadata_context* from,
                                     grpc_auth_metadata_context* to) {
  grpc_auth_metadata_context_reset(to);
  to->channel_auth_context = from->channel_auth_context;
  if (to->channel_auth_context != nullptr) {
    const_cast<grpc_auth_context*>(to->channel_auth_context)
        ->Ref(DEBUG_LOCATION, "grpc_auth_metadata_context_copy")
        .release();
  }
  to->service_url = gpr_strdup(from->service_url);
  to->method_name = gpr_strdup(from->method_name);
}

// Resets and cleans up an auth metadata context
// Frees allocated memory and releases references
void grpc_auth_metadata_context_reset(
    grpc_auth_metadata_context* auth_md_context) {
  if (auth_md_context->service_url != nullptr) {
    gpr_free(const_cast<char*>(auth_md_context->service_url));
    auth_md_context->service_url = nullptr;
  }
  if (auth_md_context->method_name != nullptr) {
    gpr_free(const_cast<char*>(auth_md_context->method_name));
    auth_md_context->method_name = nullptr;
  }
  if (auth_md_context->channel_auth_context != nullptr) {
    const_cast<grpc_auth_context*>(auth_md_context->channel_auth_context)
        ->Unref(DEBUG_LOCATION, "grpc_auth_metadata_context");
    auth_md_context->channel_auth_context = nullptr;
  }
}

// Converts security level string to enum value
static grpc_security_level convert_security_level_string_to_enum(
    const char* security_level) {
  if (strcmp(security_level, "TSI_INTEGRITY_ONLY") == 0) {
    return GRPC_INTEGRITY_ONLY;
  } else if (strcmp(security_level, "TSI_PRIVACY_AND_INTEGRITY") == 0) {
    return GRPC_PRIVACY_AND_INTEGRITY;
  }
  return GRPC_SECURITY_NONE;
}

// Checks if channel security level meets or exceeds call credential requirements
bool grpc_check_security_level(grpc_security_level channel_level,
                               grpc_security_level call_cred_level) {
  return static_cast<int>(channel_level) >= static_cast<int>(call_cred_level);
}

namespace grpc_core {

// ClientAuthFilter implementation

// Constructor for ClientAuthFilter
ClientAuthFilter::ClientAuthFilter(
    RefCountedPtr<grpc_channel_security_connector> security_connector,
    RefCountedPtr<grpc_auth_context> auth_context)
    : args_{std::move(security_connector), std::move(auth_context)} {}

// Retrieves call credentials, combining channel and call credentials if needed
// Performs security level validation between channel and call credentials
absl::StatusOr<RefCountedPtr<grpc_call_credentials>>
ClientAuthFilter::GetCallCreds() {
  auto* ctx = GetContext<grpc_client_security_context>();
  grpc_call_credentials* channel_call_creds =
      args_.security_connector->mutable_request_metadata_creds();
  const bool call_creds_has_md = (ctx != nullptr) && (ctx->creds != nullptr);

  // Return nullptr if no credentials are available
  if (channel_call_creds == nullptr && !call_creds_has_md) {
    return nullptr;
  }

  RefCountedPtr<grpc_call_credentials> creds;
  // Combine channel and call credentials if both exist
  if (channel_call_creds != nullptr && call_creds_has_md) {
    creds = RefCountedPtr<grpc_call_credentials>(
        grpc_composite_call_credentials_create(channel_call_creds,
                                               ctx->creds.get(), nullptr));
    if (creds == nullptr) {
      return absl::UnauthenticatedError(
          "Incompatible credentials set on channel and call.");
    }
  } else if (call_creds_has_md) {
    creds = ctx->creds->Ref();
  } else {
    creds = channel_call_creds->Ref();
  }

  // Check security level requirements
  grpc_auth_property_iterator it = grpc_auth_context_find_properties_by_name(
      args_.auth_context.get(), GRPC_TRANSPORT_SECURITY_LEVEL_PROPERTY_NAME);
  const grpc_auth_property* prop = grpc_auth_property_iterator_next(&it);
  if (prop == nullptr) {
    return absl::UnauthenticatedError(
        "Established channel does not have an auth "
        "property representing a security level.");
  }
  const grpc_security_level call_cred_security_level =
      creds->min_security_level();
  const bool is_security_level_ok = grpc_check_security_level(
      convert_security_level_string_to_enum(prop->value),
      call_cred_security_level);
  if (!is_security_level_ok) {
    return absl::UnauthenticatedError(
        "Established channel does not have a sufficient security level to "
        "transfer call credential.");
  }

  return std::move(creds);
}

// Installs security context in the call if not already present
void ClientAuthFilter::InstallContext() {
  auto* sec_ctx = MaybeGetContext<grpc_client_security_context>();
  if (sec_ctx == nullptr) {
    sec_ctx = grpc_client_security_context_create(GetContext<Arena>(),
                                                  nullptr);
    SetContext<SecurityContext>(sec_ctx);
  }
  sec_ctx->auth_context = args_.auth_context;
}

// Factory method for creating ClientAuthFilter
absl::StatusOr<std::unique_ptr<ClientAuthFilter>> ClientAuthFilter::Create(
    const ChannelArgs& args, ChannelFilter::Args) {
  auto* sc = args.GetObject<grpc_security_connector>();
  if (sc == nullptr) {
    return absl::InvalidArgumentError(
        "Security connector missing from client auth filter args");
  }
  auto* auth_context = args.GetObject<grpc_auth_context>();
  if (auth_context == nullptr) {
    return absl::InvalidArgumentError(
        "Auth context missing from client auth filter args");
  }
  return std::make_unique<ClientAuthFilter>(
      sc->RefAsSubclass<grpc_channel_security_connector>(),
      auth_context->Ref());
}

// Static filter definition
const grpc_channel_filter ClientAuthFilter::kFilter =
    MakePromiseBasedFilter<ClientAuthFilter, FilterEndpoint::kClient>();

// LegacyClientAuthFilter implementation

// Constructor for LegacyClientAuthFilter
LegacyClientAuthFilter::LegacyClientAuthFilter(
    RefCountedPtr<grpc_channel_security_connector> security_connector,
    RefCountedPtr<grpc_auth_context> auth_context)
    : args_{std::move(security_connector), std::move(auth_context)} {}

// Gets call credentials metadata for legacy filter
ArenaPromise<absl::StatusOr<CallArgs>>
LegacyClientAuthFilter::GetCallCredsMetadata(CallArgs call_args) {
  auto* ctx = GetContext<grpc_client_security_context>();
  grpc_call_credentials* channel_call_creds =
      args_.security_connector->mutable_request_metadata_creds();
  const bool call_creds_has_md = (ctx != nullptr) && (ctx->creds != nullptr);

  // Return immediately if no credentials are needed
  if (channel_call_creds == nullptr && !call_creds_has_md) {
    return Immediate(absl::StatusOr<CallArgs>(std::move(call_args)));
  }

  RefCountedPtr<grpc_call_credentials> creds;
  // Combine or select appropriate credentials
  if (channel_call_creds != nullptr && call_creds_has_md) {
    creds = RefCountedPtr<grpc_call_credentials>(
        grpc_composite_call_credentials_create(channel_call_creds,
                                               ctx->creds.get(), nullptr));
    if (creds == nullptr) {
      return Immediate(absl::UnauthenticatedError(
          "Incompatible credentials set on channel and call."));
    }
  } else if (call_creds_has_md) {
    creds = ctx->creds->Ref();
  } else {
    creds = channel_call_creds->Ref();
  }

  // Validate security level
  grpc_auth_property_iterator it = grpc_auth_context_find_properties_by_name(
      args_.auth_context.get(), GRPC_TRANSPORT_SECURITY_LEVEL_PROPERTY_NAME);
  const grpc_auth_property* prop = grpc_auth_property_iterator_next(&it);
  if (prop == nullptr) {
    return Immediate(
        absl::UnauthenticatedError("Established channel does not have an auth "
                                   "property representing a security level."));
  }
  const grpc_security_level call_cred_security_level =
      creds->min_security_level();
  const bool is_security_level_ok = grpc_check_security_level(
      convert_security_level_string_to_enum(prop->value),
      call_cred_security_level);
  if (!is_security_level_ok) {
    return Immediate(absl::UnauthenticatedError(
        "Established channel does not have a sufficient security level to "
        "transfer call credential."));
  }

  // Process metadata and return promise chain
  auto client_initial_metadata = std::move(call_args.client_initial_metadata);
  return TrySeq(
      Seq(creds->GetRequestMetadata(std::move(client_initial_metadata), &args_),
          [](absl::StatusOr<ClientMetadataHandle> new_metadata) mutable {
            if (!new_metadata.ok()) {
              return absl::StatusOr<ClientMetadataHandle>(
                  MaybeRewriteIllegalStatusCode(new_metadata.status(),
                                                "call credentials"));
            }
            return new_metadata;
          }),
      [call_args =
           std::move(call_args)](ClientMetadataHandle new_metadata) mutable {
        call_args.client_initial_metadata = std::move(new_metadata);
        return Immediate<absl::StatusOr<CallArgs>>(
            absl::StatusOr<CallArgs>(std::move(call_args)));
      });
}

// Creates promise chain for legacy auth filter
ArenaPromise<ServerMetadataHandle> LegacyClientAuthFilter::MakeCallPromise(
    CallArgs call_args, NextPromiseFactory next_promise_factory) {
  // Install security context if not present
  auto* sec_ctx = MaybeGetContext<grpc_client_security_context>();
  if (sec_ctx == nullptr) {
    sec_ctx = grpc_client_security_context_create(GetContext<Arena>(),
                                                  nullptr);
    SetContext<SecurityContext>(sec_ctx);
  }
  sec_ctx->auth_context = args_.auth_context;

  // Check if host is specified in metadata
  auto* host =
      call_args.client_initial_metadata->get_pointer(HttpAuthorityMetadata());
  if (host == nullptr) {
    return next_promise_factory(std::move(call_args));
  }
  
  // Create promise chain: check host -> get credentials -> next promise
  return TrySeq(
      args_.security_connector->CheckCallHost(host->as_string_view(),
                                              args_.auth_context.get()),
      [this, call_args = std::move(call_args)]() mutable {
        return GetCallCredsMetadata(std::move(call_args));
      },
      next_promise_factory);
}

// Factory method for creating LegacyClientAuthFilter
absl::StatusOr<std::unique_ptr<ClientAuthFilter>>
LegacyClientAuthFilter::Create(const ChannelArgs& args, ChannelFilter::Args) {
  auto* sc = args.GetObject<grpc_security_connector>();
  if (sc == nullptr) {
    return absl::InvalidArgumentError(
        "Security connector missing from client auth filter args");
  }
  auto* auth_context = args.GetObject<grpc_auth_context>();
  if (auth_context == nullptr) {
    return absl::InvalidArgumentError(
        "Auth context missing from client auth filter args");
  }
  return std::make_unique<ClientAuthFilter>(
      sc->RefAsSubclass<grpc_channel_security_connector>(),
      auth_context->Ref());
}

// Static filter definition for legacy version
const grpc_channel_filter LegacyClientAuthFilter::kFilter =
    MakePromiseBasedFilter<ClientAuthFilter, FilterEndpoint::kClient>();

}  // namespace grpc_core
```