
// Copyright 2015 gRPC authors.

#include "src/core/credentials/call/token_fetcher/token_fetcher_credentials.h"

#include "src/core/lib/debug/trace.h"
#include "src/core/lib/event_engine/default_event_engine.h"
#include "src/core/lib/iomgr/pollset_set.h"
#include "src/core/lib/promise/context.h"
#include "src/core/lib/promise/poll.h"
#include "src/core/lib/promise/promise.h"

namespace grpc_core {

namespace {

constexpr Duration kTokenExpirationAdjustmentDuration = Duration::Seconds(30);

constexpr Duration kTokenRefreshDuration = Duration::Seconds(60);

}

TokenFetcherCredentials::Token::Token(Slice token, Timestamp expiration)
    : token_(std::move(token)),
      expiration_(expiration - kTokenExpirationAdjustmentDuration) {}

void TokenFetcherCredentials::Token::AddTokenToClientInitialMetadata(
    ClientMetadata& metadata) const {
  metadata.Append(GRPC_AUTHORIZATION_METADATA_KEY, token_.Ref(),
                  [](absl::string_view, const Slice&) { abort(); });
}

TokenFetcherCredentials::FetchState::BackoffTimer::BackoffTimer(
    RefCountedPtr<FetchState> fetch_state, absl::Status status)
    : fetch_state_(std::move(fetch_state)), status_(status) {
  const Duration delay = fetch_state_->backoff_.NextAttemptDelay();
  GRPC_TRACE_LOG(token_fetcher_credentials, INFO)
      << "[TokenFetcherCredentials " << fetch_state_->creds_.get()
      << "]: fetch_state=" << fetch_state_.get() << " backoff_timer=" << this
      << ": starting backoff timer for " << delay;
  timer_handle_ = fetch_state_->creds_->event_engine().RunAfter(
      delay, [self = Ref()]() mutable {
        ExecCtx exec_ctx;
        self->OnTimer();
        self.reset();
      });
}

void TokenFetcherCredentials::FetchState::BackoffTimer::Orphan() {
  GRPC_TRACE_LOG(token_fetcher_credentials, INFO)
      << "[TokenFetcherCredentials " << fetch_state_->creds_.get()
      << "]: fetch_state=" << fetch_state_.get() << " backoff_timer=" << this
      << ": backoff timer shut down";
  if (timer_handle_.has_value()) {
    GRPC_TRACE_LOG(token_fetcher_credentials, INFO)
        << "[TokenFetcherCredentials " << fetch_state_->creds_.get()
        << "]: fetch_state=" << fetch_state_.get() << " backoff_timer=" << this
        << ": cancelling timer";
    fetch_state_->creds_->event_engine().Cancel(*timer_handle_);
    timer_handle_.reset();
    fetch_state_->ResumeQueuedCalls(
        absl::CancelledError("credentials shutdown"));
  }
  Unref();
}

void TokenFetcherCredentials::FetchState::BackoffTimer::OnTimer() {
  MutexLock lock(&fetch_state_->creds_->mu_);
  if (!timer_handle_.has_value()) return;
  timer_handle_.reset();
  GRPC_TRACE_LOG(token_fetcher_credentials, INFO)
      << "[TokenFetcherCredentials " << fetch_state_->creds_.get()
      << "]: fetch_state=" << fetch_state_.get() << " backoff_timer=" << this
      << ": backoff timer fired";
  auto* self_ptr =
      std::get_if<OrphanablePtr<BackoffTimer>>(&fetch_state_->state_);

  if (self_ptr != nullptr && self_ptr->get() == this) {

    self_ptr->reset();
  }
}

TokenFetcherCredentials::FetchState::FetchState(
    WeakRefCountedPtr<TokenFetcherCredentials> creds)
    : creds_(std::move(creds)),
      backoff_(BackOff::Options()
                   .set_initial_backoff(Duration::Seconds(1))
                   .set_multiplier(1.6)
                   .set_jitter(creds_->test_only_use_backoff_jitter_ ? 0.2 : 0)
                   .set_max_backoff(Duration::Seconds(120))) {
  StartFetchAttempt();
}

void TokenFetcherCredentials::FetchState::Orphan() {
  GRPC_TRACE_LOG(token_fetcher_credentials, INFO)
      << "[TokenFetcherCredentials " << creds_.get()
      << "]: fetch_state=" << this << ": shutting down";

  state_ = Shutdown{};
  Unref();
}

absl::Status TokenFetcherCredentials::FetchState::status() const {
  auto* backoff_ptr = std::get_if<OrphanablePtr<BackoffTimer>>(&state_);
  if (backoff_ptr == nullptr || *backoff_ptr == nullptr) {
    return absl::OkStatus();
  }
  return (*backoff_ptr)->status();
}

void TokenFetcherCredentials::FetchState::StartFetchAttempt() {
  GRPC_TRACE_LOG(token_fetcher_credentials, INFO)
      << "[TokenFetcherCredentials " << creds_.get()
      << "]: fetch_state=" << this << ": starting fetch";
  state_ = creds_->FetchToken(
      Timestamp::Now() + kTokenRefreshDuration,
      [self = Ref()](absl::StatusOr<RefCountedPtr<Token>> token) mutable {
        self->TokenFetchComplete(std::move(token));
      });
}

void TokenFetcherCredentials::FetchState::TokenFetchComplete(
    absl::StatusOr<RefCountedPtr<Token>> token) {
  MutexLock lock(&creds_->mu_);

  if (std::holds_alternative<Shutdown>(state_)) {
    if (token.ok()) token = absl::CancelledError("credentials shutdown");
    GRPC_TRACE_LOG(token_fetcher_credentials, INFO)
        << "[TokenFetcherCredentials " << creds_.get()
        << "]: fetch_state=" << this
        << ": shut down before fetch completed: " << token.status();
    ResumeQueuedCalls(std::move(token));
    return;
  }

  if (token.ok()) {
    GRPC_TRACE_LOG(token_fetcher_credentials, INFO)
        << "[TokenFetcherCredentials " << creds_.get()
        << "]: fetch_state=" << this << ": token fetch succeeded";
    creds_->token_ = *token;
    creds_->fetch_state_.reset();
  } else {
    GRPC_TRACE_LOG(token_fetcher_credentials, INFO)
        << "[TokenFetcherCredentials " << creds_.get()
        << "]: fetch_state=" << this
        << ": token fetch failed: " << token.status();

    state_ =
        OrphanablePtr<BackoffTimer>(new BackoffTimer(Ref(), token.status()));
  }
  ResumeQueuedCalls(std::move(token));
}

void TokenFetcherCredentials::FetchState::ResumeQueuedCalls(
    absl::StatusOr<RefCountedPtr<Token>> token) {

  for (auto& queued_call : queued_calls_) {
    queued_call->result = token;
    queued_call->done.store(true, std::memory_order_release);
    queued_call->waker.Wakeup();
    grpc_polling_entity_del_from_pollset_set(
        queued_call->pollent,
        grpc_polling_entity_pollset_set(&creds_->pollent_));
  }
  queued_calls_.clear();
}

RefCountedPtr<TokenFetcherCredentials::QueuedCall>
TokenFetcherCredentials::FetchState::QueueCall(
    ClientMetadataHandle initial_metadata) {
  auto queued_call = MakeRefCounted<QueuedCall>();
  queued_call->waker = GetContext<Activity>()->MakeNonOwningWaker();
  queued_call->pollent = GetContext<grpc_polling_entity>();
  grpc_polling_entity_add_to_pollset_set(
      queued_call->pollent, grpc_polling_entity_pollset_set(&creds_->pollent_));
  queued_call->md = std::move(initial_metadata);
  queued_calls_.insert(queued_call);

  auto* backoff_ptr = std::get_if<OrphanablePtr<BackoffTimer>>(&state_);
  if (backoff_ptr != nullptr && backoff_ptr->get() == nullptr) {
    StartFetchAttempt();
  }
  return queued_call;
}

TokenFetcherCredentials::TokenFetcherCredentials(
    std::shared_ptr<grpc_event_engine::experimental::EventEngine> event_engine,
    bool test_only_use_backoff_jitter)
    : event_engine_(
          event_engine == nullptr
              ? grpc_event_engine::experimental::GetDefaultEventEngine()
              : std::move(event_engine)),
      test_only_use_backoff_jitter_(test_only_use_backoff_jitter),
      pollent_(grpc_polling_entity_create_from_pollset_set(
          grpc_pollset_set_create())) {}

TokenFetcherCredentials::~TokenFetcherCredentials() {
  grpc_pollset_set_destroy(grpc_polling_entity_pollset_set(&pollent_));
}

void TokenFetcherCredentials::Orphaned() {
  MutexLock lock(&mu_);
  fetch_state_.reset();
}

ArenaPromise<absl::StatusOr<ClientMetadataHandle>>
TokenFetcherCredentials::GetRequestMetadata(
    ClientMetadataHandle initial_metadata, const GetRequestMetadataArgs*) {
  RefCountedPtr<QueuedCall> queued_call;
  {
    MutexLock lock(&mu_);

    if ((token_ == nullptr || (token_->ExpirationTime() - Timestamp::Now()) <=
                                  kTokenRefreshDuration) &&
        fetch_state_ == nullptr) {
      GRPC_TRACE_LOG(token_fetcher_credentials, INFO)
          << "[TokenFetcherCredentials " << this
          << "]: " << GetContext<Activity>()->DebugTag()
          << " triggering new token fetch";
      fetch_state_ = OrphanablePtr<FetchState>(
          new FetchState(WeakRefAsSubclass<TokenFetcherCredentials>()));
    }

    if (token_ != nullptr &&
        (token_->ExpirationTime() - Timestamp::Now()) > Duration::Zero()) {
      GRPC_TRACE_LOG(token_fetcher_credentials, INFO)
          << "[TokenFetcherCredentials " << this
          << "]: " << GetContext<Activity>()->DebugTag()
          << " using cached token";
      token_->AddTokenToClientInitialMetadata(*initial_metadata);
      return Immediate(std::move(initial_metadata));
    }

    if (fetch_state_ != nullptr) {
      absl::Status status = fetch_state_->status();
      if (!status.ok()) return Immediate(std::move(status));
    }

    GRPC_TRACE_LOG(token_fetcher_credentials, INFO)
        << "[TokenFetcherCredentials " << this
        << "]: " << GetContext<Activity>()->DebugTag()
        << " no cached token; queuing call";
    queued_call = fetch_state_->QueueCall(std::move(initial_metadata));
  }
  return [this, queued_call = std::move(queued_call)]()
             -> Poll<absl::StatusOr<ClientMetadataHandle>> {
    if (!queued_call->done.load(std::memory_order_acquire)) {
      return Pending{};
    }
    if (!queued_call->result.ok()) {
      GRPC_TRACE_LOG(token_fetcher_credentials, INFO)
          << "[TokenFetcherCredentials " << this
          << "]: " << GetContext<Activity>()->DebugTag()
          << " token fetch failed; failing call";
      return queued_call->result.status();
    }
    GRPC_TRACE_LOG(token_fetcher_credentials, INFO)
        << "[TokenFetcherCredentials " << this
        << "]: " << GetContext<Activity>()->DebugTag()
        << " token fetch complete; resuming call";
    (*queued_call->result)->AddTokenToClientInitialMetadata(*queued_call->md);
    return std::move(queued_call->md);
  };
}

}
