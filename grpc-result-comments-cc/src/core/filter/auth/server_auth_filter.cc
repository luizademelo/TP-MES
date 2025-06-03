Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

// Include necessary gRPC and other library headers
#include <grpc/credentials.h>
#include <grpc/grpc.h>
#include <grpc/grpc_security.h>
#include <grpc/status.h>
#include <grpc/support/alloc.h>
#include <grpc/support/port_platform.h>

#include <algorithm>
#include <atomic>
#include <cstddef>
#include <functional>
#include <memory>
#include <utility>

// Include Abseil and internal gRPC headers
#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "src/core/call/metadata_batch.h"
#include "src/core/call/security_context.h"
#include "src/core/credentials/transport/transport_credentials.h"
#include "src/core/filter/auth/auth_filters.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/channel/channel_fwd.h"
#include "src/core/lib/channel/channel_stack.h"
#include "src/core/lib/channel/promise_based_filter.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/lib/promise/activity.h"
#include "src/core/lib/promise/arena_promise.h"
#include "src/core/lib/promise/context.h"
#include "src/core/lib/promise/poll.h"
#include "src/core/lib/promise/try_seq.h"
#include "src/core/lib/resource_quota/arena.h"
#include "src/core/lib/slice/slice.h"
#include "src/core/lib/slice/slice_internal.h"
#include "src/core/lib/transport/transport.h"
#include "src/core/transport/auth_context.h"
#include "src/core/util/debug_location.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/status_helper.h"

namespace grpc_core {

// Define the server auth filter
const grpc_channel_filter ServerAuthFilter::kFilter =
    MakePromiseBasedFilter<ServerAuthFilter, FilterEndpoint::kServer>();

namespace {

// Helper class for encoding metadata into a grpc_metadata_array
class ArrayEncoder {
 public:
  // Constructor takes a pointer to the result metadata array
  explicit ArrayEncoder(grpc_metadata_array* result) : result_(result) {}

  // Encode a key-value pair as slices
  void Encode(const Slice& key, const Slice& value) {
    Append(key.Ref(), value.Ref());
  }

  // Encode a typed metadata value
  template <typename Which>
  void Encode(Which, const typename Which::ValueType& value) {
    Append(Slice(StaticSlice::FromStaticString(Which::key())),
           Slice(Which::Encode(value)));
  }

  // Special case: HttpMethodMetadata doesn't need encoding
  void Encode(HttpMethodMetadata,
              const typename HttpMethodMetadata::ValueType&) {}

 private:
  // Append a key-value pair to the metadata array, resizing if necessary
  void Append(Slice key, Slice value) {
    if (result_->count == result_->capacity) {
      result_->capacity =
          std::max(result_->capacity + 8, result_->capacity * 2);
      result_->metadata = static_cast<grpc_metadata*>(gpr_realloc(
          result_->metadata, result_->capacity * sizeof(grpc_metadata)));
    }
    auto* usr_md = &result_->metadata[result_->count++];
    usr_md->key = key.TakeCSlice();
    usr_md->value = value.TakeCSlice();
  }

  grpc_metadata_array* result_;
};

// Convert a metadata batch to a grpc_metadata_array
grpc_metadata_array MetadataBatchToMetadataArray(
    const grpc_metadata_batch* batch) {
  grpc_metadata_array result;
  grpc_metadata_array_init(&result);
  ArrayEncoder encoder(&result);
  batch->Encode(&encoder);
  return result;
}

}  // namespace

// State for running application code during auth processing
struct ServerAuthFilter::RunApplicationCode::State {
  explicit State(ClientMetadata& client_metadata)
      : client_metadata(&client_metadata) {}
  Waker waker{GetContext<Activity>()->MakeOwningWaker()};
  absl::StatusOr<ClientMetadata*> client_metadata;
  grpc_metadata_array md = MetadataBatchToMetadataArray(*client_metadata);
  std::atomic<bool> done{false};
};

// Constructor for RunApplicationCode
ServerAuthFilter::RunApplicationCode::RunApplicationCode(
    ServerAuthFilter* filter, ClientMetadata& metadata)
    : state_(GetContext<Arena>()->ManagedNew<State>(metadata)) {
  GRPC_TRACE_LOG(call, ERROR)
      << GetContext<Activity>()->DebugTag()
      << "[server-auth]: Delegate to application: filter=" << filter
      << " this=" << this << " auth_ctx=" << filter->auth_context_.get();
  // Invoke the auth metadata processor
  filter->server_credentials_->auth_metadata_processor().process(
      filter->server_credentials_->auth_metadata_processor().state,
      filter->auth_context_.get(), state_->md.metadata, state_->md.count,
      OnMdProcessingDone, state_);
}

// Polling function for async operation
Poll<absl::Status> ServerAuthFilter::RunApplicationCode::operator()() {
  if (state_->done.load(std::memory_order_acquire)) {
    return Poll<absl::Status>(std::move(state_->client_metadata).status());
  }
  return Pending{};
}

// Callback for when metadata processing is complete
void ServerAuthFilter::RunApplicationCode::OnMdProcessingDone(
    void* user_data, const grpc_metadata* consumed_md, size_t num_consumed_md,
    const grpc_metadata* response_md, size_t num_response_md,
    grpc_status_code status, const char* error_details) {
  ExecCtx exec_ctx;

  auto* state = static_cast<State*>(user_data);

  // Currently unsupported feature warning
  if (response_md != nullptr && num_response_md > 0) {
    LOG(ERROR) << "response_md in auth metadata processing not supported for "
                  "now. Ignoring...";
  }

  if (status == GRPC_STATUS_OK) {
    // Remove consumed metadata from the client metadata
    ClientMetadata& md = **state->client_metadata;
    for (size_t i = 0; i < num_consumed_md; i++) {
      md.Remove(StringViewFromSlice(consumed_md[i].key));
    }
  } else {
    // Handle authentication failure
    if (error_details == nullptr) {
      error_details = "Authentication metadata processing failed.";
    }
    state->client_metadata = grpc_error_set_int(
        absl::Status(static_cast<absl::StatusCode>(status), error_details),
        StatusIntProperty::kRpcStatus, status);
  }

  // Clean up metadata array
  for (size_t i = 0; i < state->md.count; i++) {
    CSliceUnref(state->md.metadata[i].key);
    CSliceUnref(state->md.metadata[i].value);
  }
  grpc_metadata_array_destroy(&state->md);

  // Mark operation as done and wake up waiting activity
  auto waker = std::move(state->waker);
  state->done.store(true, std::memory_order_release);
  waker.Wakeup();
}

// Constructor for ServerAuthFilter::Call
ServerAuthFilter::Call::Call(ServerAuthFilter* filter) {
  // Create and set up security context
  grpc_server_security_context* server_ctx =
      grpc_server_security_context_create(GetContext<Arena>());
  server_ctx->auth_context =
      filter->auth_context_->Ref(DEBUG_LOCATION, "server_auth_filter");
  SetContext<SecurityContext>(server_ctx);
}

// Constructor for ServerAuthFilter
ServerAuthFilter::ServerAuthFilter(
    RefCountedPtr<grpc_server_credentials> server_credentials,
    RefCountedPtr<grpc_auth_context> auth_context)
    : server_credentials_(server_credentials), auth_context_(auth_context) {}

// Factory method for creating ServerAuthFilter
absl::StatusOr<std::unique_ptr<ServerAuthFilter>> ServerAuthFilter::Create(
    const ChannelArgs& args, ChannelFilter::Args) {
  auto auth_context = args.GetObjectRef<grpc_auth_context>();
  CHECK(auth_context != nullptr);
  auto creds = args.GetObjectRef<grpc_server_credentials>();
  return std::make_unique<ServerAuthFilter>(std::move(creds),
                                            std::move(auth_context));
}

}  // namespace grpc_core
```

The comments explain:
1. The purpose of each major component (classes, structs, functions)
2. Key operations being performed
3. Important control flow and error handling
4. Memory management considerations
5. Asynchronous operation handling
6. Security context setup
7. The overall flow of authentication processing

The comments are designed to help future maintainers understand:
- What the code does at a high level
- Why certain operations are performed
- How different components interact
- Important implementation details
- Current limitations (like unsupported response_md)