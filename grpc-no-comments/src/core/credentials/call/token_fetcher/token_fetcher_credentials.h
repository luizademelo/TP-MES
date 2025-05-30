
// Copyright 2016 gRPC authors.

#ifndef GRPC_SRC_CORE_CREDENTIALS_CALL_TOKEN_FETCHER_TOKEN_FETCHER_CREDENTIALS_H
#define GRPC_SRC_CORE_CREDENTIALS_CALL_TOKEN_FETCHER_TOKEN_FETCHER_CREDENTIALS_H

#include <grpc/event_engine/event_engine.h>

#include <atomic>
#include <memory>
#include <utility>
#include <variant>

#include "absl/container/flat_hash_set.h"
#include "absl/functional/any_invocable.h"
#include "absl/status/statusor.h"
#include "src/core/call/metadata.h"
#include "src/core/credentials/call/call_credentials.h"
#include "src/core/lib/iomgr/polling_entity.h"
#include "src/core/lib/promise/arena_promise.h"
#include "src/core/util/backoff.h"
#include "src/core/util/http_client/httpcli.h"
#include "src/core/util/orphanable.h"
#include "src/core/util/ref_counted.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/sync.h"
#include "src/core/util/time.h"
#include "src/core/util/useful.h"

namespace grpc_core {

class TokenFetcherCredentials : public grpc_call_credentials {
 public:

  class Token : public RefCounted<Token> {
   public:
    Token(Slice token, Timestamp expiration);

    Timestamp ExpirationTime() const { return expiration_; }

    void AddTokenToClientInitialMetadata(ClientMetadata& metadata) const;

   private:
    Slice token_;
    Timestamp expiration_;
  };

  ~TokenFetcherCredentials() override;

  void Orphaned() override;

  ArenaPromise<absl::StatusOr<ClientMetadataHandle>> GetRequestMetadata(
      ClientMetadataHandle initial_metadata,
      const GetRequestMetadataArgs* args) override;

 protected:

  class FetchRequest : public InternallyRefCounted<FetchRequest> {};

  explicit TokenFetcherCredentials(
      std::shared_ptr<grpc_event_engine::experimental::EventEngine>
          event_engine = nullptr,
      bool test_only_use_backoff_jitter = true);

  virtual OrphanablePtr<FetchRequest> FetchToken(
      Timestamp deadline,
      absl::AnyInvocable<void(absl::StatusOr<RefCountedPtr<Token>>)>
          on_done) = 0;

  grpc_event_engine::experimental::EventEngine& event_engine() const {
    return *event_engine_;
  }

  grpc_polling_entity* pollent() { return &pollent_; }

 private:

  struct QueuedCall : public RefCounted<QueuedCall> {
    std::atomic<bool> done{false};
    Waker waker;
    grpc_polling_entity* pollent;
    ClientMetadataHandle md;
    absl::StatusOr<RefCountedPtr<Token>> result;
  };

  class FetchState : public InternallyRefCounted<FetchState> {
   public:
    explicit FetchState(WeakRefCountedPtr<TokenFetcherCredentials> creds)
        ABSL_EXCLUSIVE_LOCKS_REQUIRED(&TokenFetcherCredentials::mu_);

    void Orphan() override ABSL_NO_THREAD_SAFETY_ANALYSIS;

    absl::Status status() const;

    RefCountedPtr<QueuedCall> QueueCall(ClientMetadataHandle initial_metadata)
        ABSL_EXCLUSIVE_LOCKS_REQUIRED(&TokenFetcherCredentials::mu_);

   private:
    class BackoffTimer : public InternallyRefCounted<BackoffTimer> {
     public:
      BackoffTimer(RefCountedPtr<FetchState> fetch_state, absl::Status status)
          ABSL_EXCLUSIVE_LOCKS_REQUIRED(&TokenFetcherCredentials::mu_);

      void Orphan() override ABSL_NO_THREAD_SAFETY_ANALYSIS;

      absl::Status status() const { return status_; }

     private:
      void OnTimer();

      RefCountedPtr<FetchState> fetch_state_;
      const absl::Status status_;
      std::optional<grpc_event_engine::experimental::EventEngine::TaskHandle>
          timer_handle_ ABSL_GUARDED_BY(&TokenFetcherCredentials::mu_);
    };

    struct Shutdown {};

    void StartFetchAttempt()
        ABSL_EXCLUSIVE_LOCKS_REQUIRED(&TokenFetcherCredentials::mu_);
    void TokenFetchComplete(absl::StatusOr<RefCountedPtr<Token>> token);
    void ResumeQueuedCalls(absl::StatusOr<RefCountedPtr<Token>> token)
        ABSL_EXCLUSIVE_LOCKS_REQUIRED(&TokenFetcherCredentials::mu_);

    WeakRefCountedPtr<TokenFetcherCredentials> creds_;

    std::variant<OrphanablePtr<FetchRequest>, OrphanablePtr<BackoffTimer>,
                 Shutdown>
        state_ ABSL_GUARDED_BY(&TokenFetcherCredentials::mu_);

    absl::flat_hash_set<RefCountedPtr<QueuedCall>> queued_calls_
        ABSL_GUARDED_BY(&TokenFetcherCredentials::mu_);

    BackOff backoff_ ABSL_GUARDED_BY(&TokenFetcherCredentials::mu_);
  };

  int cmp_impl(const grpc_call_credentials* other) const override {

    return QsortCompare(static_cast<const grpc_call_credentials*>(this), other);
  }

  std::shared_ptr<grpc_event_engine::experimental::EventEngine> event_engine_;
  const bool test_only_use_backoff_jitter_;

  Mutex mu_;

  RefCountedPtr<Token> token_ ABSL_GUARDED_BY(&mu_);

  OrphanablePtr<FetchState> fetch_state_ ABSL_GUARDED_BY(&mu_);

  grpc_polling_entity pollent_ ABSL_GUARDED_BY(&mu_);
};

}

#endif
