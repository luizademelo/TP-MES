Here's the commented version of the code:

```c++
// Copyright 2024 gRPC authors.

#include "src/core/client_channel/retry_interceptor.h"

#include "src/core/lib/promise/cancel_callback.h"
#include "src/core/lib/promise/for_each.h"
#include "src/core/lib/promise/map.h"
#include "src/core/lib/promise/sleep.h"
#include "src/core/service_config/service_config_call_data.h"

namespace grpc_core {

namespace {
// Returns the maximum buffer size for retry attempts per RPC call
// Uses channel args to get the configured size or falls back to default (256KB)
size_t GetMaxPerRpcRetryBufferSize(const ChannelArgs& args) {
  // Default buffer size is 256KB
  static constexpr int kDefaultPerRpcRetryBufferSize = (256 << 10);
  // Clamp the value between 0 and INT_MAX to ensure it's valid
  return Clamp(args.GetInt(GRPC_ARG_PER_RPC_RETRY_BUFFER_SIZE)
                   .value_or(kDefaultPerRpcRetryBufferSize),
               0, INT_MAX);
}
}

namespace retry_detail {

// RetryState manages the retry policy and state for an RPC call
RetryState::RetryState(
    const internal::RetryMethodConfig* retry_policy,
    RefCountedPtr<internal::ServerRetryThrottleData> retry_throttle_data)
    : retry_policy_(retry_policy),
      retry_throttle_data_(std::move(retry_throttle_data)),
      // Initialize backoff with configured or default values
      retry_backoff_(
          BackOff::Options()
              .set_initial_backoff(retry_policy_ == nullptr
                                       ? Duration::Zero()
                                       : retry_policy_->initial_backoff())
              .set_multiplier(retry_policy_ == nullptr
                                  ? 0
                                  : retry_policy_->backoff_multiplier())
              .set_jitter(0.2)  // Add 20% jitter to backoff
              .set_max_backoff(retry_policy_ == nullptr
                                   ? Duration::Zero()
                                   : retry_policy_->max_backoff())) {}

// Determines whether a call should be retried based on server response
// Returns the delay before next retry attempt if retry should happen,
// or nullopt if no retry should be performed
std::optional<Duration> RetryState::ShouldRetry(
    const ServerMetadata& md, bool committed,
    absl::FunctionRef<std::string()> lazy_attempt_debug_string) {
  // If no retry policy is configured, don't retry
  if (retry_policy_ == nullptr) {
    GRPC_TRACE_LOG(retry, INFO)
        << lazy_attempt_debug_string() << " no retry policy";
    return std::nullopt;
  }
  
  // Check the status code from server metadata
  const auto status = md.get(GrpcStatusMetadata());
  if (status.has_value()) {
    // If status is OK, record success and don't retry
    if (GPR_LIKELY(*status == GRPC_STATUS_OK)) {
      if (retry_throttle_data_ != nullptr) {
        retry_throttle_data_->RecordSuccess();
      }
      GRPC_TRACE_LOG(retry, INFO)
          << lazy_attempt_debug_string() << " call succeeded";
      return std::nullopt;
    }

    // Check if status code is configured as retryable
    if (!retry_policy_->retryable_status_codes().Contains(*status)) {
      GRPC_TRACE_LOG(retry, INFO) << lazy_attempt_debug_string() << ": status "
                                  << grpc_status_code_to_string(*status)
                                  << " not configured as retryable";
      return std::nullopt;
    }
  }

  // Check if retries are throttled
  if (retry_throttle_data_ != nullptr &&
      !retry_throttle_data_->RecordFailure()) {
    GRPC_TRACE_LOG(retry, INFO)
        << lazy_attempt_debug_string() << " retries throttled";
    return std::nullopt;
  }

  // Don't retry if already committed
  if (committed) {
    GRPC_TRACE_LOG(retry, INFO)
        << lazy_attempt_debug_string() << " retries already committed";
    return std::nullopt;
  }

  // Increment attempt counter and check max attempts
  ++num_attempts_completed_;
  if (num_attempts_completed_ >= retry_policy_->max_attempts()) {
    GRPC_TRACE_LOG(retry, INFO)
        << lazy_attempt_debug_string() << " exceeded "
        << retry_policy_->max_attempts() << " retry attempts";
    return std::nullopt;
  }

  // Check for server pushback
  const auto server_pushback = md.get(GrpcRetryPushbackMsMetadata());
  if (server_pushback.has_value() && server_pushback < Duration::Zero()) {
    GRPC_TRACE_LOG(retry, INFO) << lazy_attempt_debug_string()
                                << " not retrying due to server push-back";
    return std::nullopt;
  }

  // Calculate next attempt delay
  Duration next_attempt_timeout;
  if (server_pushback.has_value()) {
    // Use server-specified pushback delay
    CHECK_GE(*server_pushback, Duration::Zero());
    next_attempt_timeout = *server_pushback;
    retry_backoff_.Reset();
  } else {
    // Use calculated backoff delay
    next_attempt_timeout = retry_backoff_.NextAttemptDelay();
  }
  GRPC_TRACE_LOG(retry, INFO)
      << lazy_attempt_debug_string() << " server push-back: retry in "
      << next_attempt_timeout;
  return next_attempt_timeout;
}

// Retrieves server retry throttle data from channel args
absl::StatusOr<RefCountedPtr<internal::ServerRetryThrottleData>>
ServerRetryThrottleDataFromChannelArgs(const ChannelArgs& args) {
  // Get service config from channel args
  auto* service_config = args.GetObject<ServiceConfig>();
  if (service_config == nullptr) return nullptr;
  
  // Get retry global config from service config
  const auto* config = static_cast<const internal::RetryGlobalConfig*>(
      service_config->GetGlobalParsedConfig(
          internal::RetryServiceConfigParser::ParserIndex()));
  if (config == nullptr) return nullptr;

  // Get server URI from channel args
  auto server_uri = args.GetString(GRPC_ARG_SERVER_URI);
  if (!server_uri.has_value()) {
    return GRPC_ERROR_CREATE(
        "server URI channel arg missing or wrong type in client channel "
        "filter");
  }
  
  // Parse URI to get server name
  absl::StatusOr<URI> uri = URI::Parse(*server_uri);
  if (!uri.ok() || uri->path().empty()) {
    return GRPC_ERROR_CREATE("could not extract server name from target URI");
  }
  std::string server_name(absl::StripPrefix(uri->path(), "/"));

  // Get or create throttle data for this server
  return internal::ServerRetryThrottleMap::Get()->GetDataForServer(
      server_name, config->max_milli_tokens(), config->milli_token_ratio());
}

}

// Creates a new RetryInterceptor instance
absl::StatusOr<RefCountedPtr<RetryInterceptor>> RetryInterceptor::Create(
    const ChannelArgs& args, const FilterArgs&) {
  // Get retry throttle data from channel args
  auto retry_throttle_data =
      retry_detail::ServerRetryThrottleDataFromChannelArgs(args);
  if (!retry_throttle_data.ok()) {
    return retry_throttle_data.status();
  }
  return MakeRefCounted<RetryInterceptor>(args,
                                          std::move(*retry_throttle_data));
}

// RetryInterceptor constructor
RetryInterceptor::RetryInterceptor(
    const ChannelArgs& args,
    RefCountedPtr<internal::ServerRetryThrottleData> retry_throttle_data)
    : per_rpc_retry_buffer_size_(GetMaxPerRpcRetryBufferSize(args)),
      service_config_parser_index_(
          internal::RetryServiceConfigParser::ParserIndex()),
      retry_throttle_data_(std::move(retry_throttle_data)) {}

// Intercepts a call and starts retry logic
void RetryInterceptor::InterceptCall(
    UnstartedCallHandler unstarted_call_handler) {
  // Start the call and create a Call object to manage retries
  auto call_handler = unstarted_call_handler.StartCall();
  auto* arena = call_handler.arena();
  auto call = arena->MakeRefCounted<Call>(RefAsSubclass<RetryInterceptor>(),
                                          std::move(call_handler));
  call->StartAttempt();  // Start first attempt
  call->Start();         // Start processing
}

// Gets the retry policy from service config
const internal::RetryMethodConfig* RetryInterceptor::GetRetryPolicy() {
  auto* svc_cfg_call_data = MaybeGetContext<ServiceConfigCallData>();
  if (svc_cfg_call_data == nullptr) return nullptr;
  return static_cast<const internal::RetryMethodConfig*>(
      svc_cfg_call_data->GetMethodParsedConfig(service_config_parser_index_));
}

// Call constructor - manages state for a single RPC call with retries
RetryInterceptor::Call::Call(RefCountedPtr<RetryInterceptor> interceptor,
                             CallHandler call_handler)
    : call_handler_(std::move(call_handler)),
      interceptor_(std::move(interceptor)),
      retry_state_(interceptor_->GetRetryPolicy(),
                   interceptor_->retry_throttle_data_) {
  GRPC_TRACE_LOG(retry, INFO)
      << DebugTag() << " retry call created: " << retry_state_;
}

// Handles client-to-server message flow with buffering for retries
auto RetryInterceptor::Call::ClientToBuffer() {
  return TrySeq(
      // Pull initial metadata from client
      call_handler_.PullClientInitialMetadata(),
      [self = Ref()](ClientMetadataHandle metadata) mutable {
        GRPC_TRACE_LOG(retry, INFO)
            << self->DebugTag()
            << " got client initial metadata: " << metadata->DebugString();
        // Push metadata to buffer
        return self->request_buffer_.PushClientInitialMetadata(
            std::move(metadata));
      },
      [self = Ref()](size_t buffered) {
        // Check if we should commit based on buffer size
        self->MaybeCommit(buffered);
        // Process client messages
        return ForEach(
            MessagesFrom(self->call_handler_), [self](MessageHandle message) {
              GRPC_TRACE_LOG(retry, INFO)
                  << self->DebugTag() << " got client message "
                  << message->DebugString();
              return TrySeq(
                  // Push message to buffer
                  self->request_buffer_.PushMessage(std::move(message)),
                  [self](size_t buffered) {
                    // Check if we should commit after each message
                    self->MaybeCommit(buffered);
                    return absl::OkStatus();
                  });
            });
      });
}

// Starts the call processing
void RetryInterceptor::Call::Start() {
  call_handler_.SpawnGuarded("client_to_buffer", [self = Ref()]() {
    return OnCancel(Map(self->ClientToBuffer(),
                        [self](absl::Status status) {
                          // When complete, either finish or cancel the buffer
                          if (status.ok()) {
                            self->request_buffer_.FinishSends();
                          } else {
                            self->request_buffer_.Cancel(status);
                          }
                          return status;
                        }),
                    [self]() { self->request_buffer_.Cancel(); });
  });
}

// Starts a new retry attempt
void RetryInterceptor::Call::StartAttempt() {
  // Cancel previous attempt if exists
  if (current_attempt_ != nullptr) {
    current_attempt_->Cancel();
  }
  // Create and start new attempt
  auto current_attempt = call_handler_.arena()->MakeRefCounted<Attempt>(Ref());
  current_attempt_ = current_attempt.get();
  current_attempt->Start();
}

// Commits the attempt if buffer size exceeds threshold
void RetryInterceptor::Call::MaybeCommit(size_t buffered) {
  GRPC_TRACE_LOG(retry, INFO) << DebugTag() << " buffered:" << buffered << "/"
                              << interceptor_->per_rpc_retry_buffer_size_;
  if (buffered >= interceptor_->per_rpc_retry_buffer_size_) {
    std::ignore = current_attempt_->Commit();
  }
}

// Creates debug tag for logging
std::string RetryInterceptor::Call::DebugTag() {
  return absl::StrFormat("%s call:%p", Activity::current()->DebugTag(), this);
}

// Attempt constructor - manages a single retry attempt
RetryInterceptor::Attempt::Attempt(RefCountedPtr<Call> call)
    : call_(std::move(call)), reader_(call_->request_buffer()) {
  GRPC_TRACE_LOG(retry, INFO) << DebugTag() << " retry attempt created";
}

// Attempt destructor - removes itself from parent call
RetryInterceptor::Attempt::~Attempt() { call_->RemoveAttempt(this); }

// Handles server initial metadata response
auto RetryInterceptor::Attempt::ServerToClientGotInitialMetadata(
    ServerMetadataHandle md) {
  GRPC_TRACE_LOG(retry, INFO)
      << DebugTag() << " get server initial metadata " << md->DebugString();
  const bool committed = Commit();
  return If(
      committed,
      [&]() {
        // If committed, forward metadata and messages to client
        call_->call_handler()->SpawnPushServerInitialMetadata(std::move(md));
        return Seq(ForEach(MessagesFrom(initiator_),
                   [call = call_](MessageHandle message) {
                     GRPC_TRACE_LOG(retry, INFO)
                         << call->DebugTag() << " got server message "
                         << message->DebugString();
                     call->call_handler()->SpawnPushMessage(
                         std::move(message));
                     return Success{};
                   }),
                   initiator_.PullServerTrailingMetadata(),
                   [call = call_](ServerMetadataHandle md) {
                     GRPC_TRACE_LOG(retry, INFO)
                         << call->DebugTag()
                         << " got server trailing metadata: "
                         << md->DebugString();
                     call->call_handler()->SpawnPushServerTrailingMetadata(
                         std::move(md));
                     return absl::OkStatus();
                   });
      },
      [&]() { return []() { return absl::CancelledError(); }; });
}

// Handles trailers-only server response
auto RetryInterceptor::Attempt::ServerToClientGotTrailersOnlyResponse() {
  GRPC_TRACE_LOG(retry, INFO) << DebugTag() << " got trailers only response";
  return Seq(
      initiator_.PullServerTrailingMetadata(),
      [self = Ref()](ServerMetadataHandle md) {
        GRPC_TRACE_LOG(retry, INFO)
            << self->DebugTag()
            << " got server trailing metadata: " << md->DebugString();
        // Check if we should retry
        auto delay = self->call_->ShouldRetry(
            *md,
            [self = self.get()]() -> std::string { return self->DebugTag(); });
        return If(
            delay.has_value(),
            [self, delay]() {
              // If retrying, sleep then start new attempt
              return Map(Sleep(*delay), [call = self->call_](absl::Status) {
                call->StartAttempt();
                return absl::OkStatus();
              });
            },
            [self, md = std::move(md)]() mutable {
              // If not retrying, commit and forward metadata
              if (!self->Commit()) return absl::CancelledError();
              self->call_->call_handler()->SpawnPushServerTrailingMetadata(
                  std::move(md));
              return absl::OkStatus();
            });
      });
}

// Main server-to-client message flow handler
auto RetryInterceptor::Attempt::ServerToClient() {
  return TrySeq(
      initiator_.PullServerInitialMetadata(),
      [self = Ref()](std::optional<ServerMetadataHandle> metadata) {
        const bool has_md = metadata.has_value();
        return If(
            has_md,
            [self = self.get(), md = std::move(metadata)]() mutable {
              // Handle full response (with initial metadata)
              return self->ServerToClientGotInitialMetadata(std::move(*md));
            },
            [self = self.get()]() {
              // Handle trailers-only response
              return self->ServerToClientGotTrailersOnlyResponse();
            });
      });
}

// Commits the current attempt
bool RetryInterceptor::Attempt::Commit(SourceLocation whence) {
  if (committed_) return true;
  GRPC_TRACE_LOG(retry, INFO) << DebugTag() << " commit attempt from "
                              << whence.file() << ":" << whence.line();
  if (!call_->IsCurrentAttempt(this)) return false;
  committed_ = true;
  call_->request_buffer()->Commit(reader());
  return true;
}

// Handles client-to-server message flow for this attempt
auto RetryInterceptor::Attempt::ClientToServer() {
  return TrySeq(
      reader_.PullClientInitialMetadata(),
      [self = Ref()](ClientMetadataHandle metadata) {
        // Add previous attempts count to metadata if this is a retry
        int num_attempts_completed = self->call_->num_attempts_completed();
        if (GPR_UNLIKELY(num_attempts_completed > 0)) {
          metadata->Set(GrpcPreviousRpcAttemptsMetadata(),
                        num_attempts_completed);
        } else {
          metadata->Remove(GrpcPreviousRpcAttemptsMetadata());
        }
        // Create child call for this attempt
        self->initiator_ = self->call_->interceptor()->MakeChildCall(
            std::move(metadata), self->call_->call_handler()->arena()->Ref());
        self->call_->call_handler()->AddChildCall(self->initiator_);
        // Start server-to-client processing
        self->initiator_.SpawnGuarded(
            "server_to_client", [self]() { return self->ServerToClient(); });
        // Forward messages to server
        return ForEach(MessagesFrom(&self->reader_),
                       [self](MessageHandle message) {
                         self->initiator_.