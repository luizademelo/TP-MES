Here's the commented version of the code:

```c++
// Copyright 2023 gRPC authors.

#include "src/core/lib/event_engine/thready_event_engine/thready_event_engine.h"

#include <grpc/support/port_platform.h>

#include <memory>
#include <string>
#include <type_traits>
#include <vector>

#include "src/core/util/crash.h"
#include "src/core/util/sync.h"
#include "src/core/util/thd.h"

namespace grpc_event_engine::experimental {

// Executes the given function asynchronously in a new thread
// The thread is non-joinable and automatically cleans up after execution
void ThreadyEventEngine::Asynchronously(absl::AnyInvocable<void()> fn) {
  grpc_core::Thread t("thready_event_engine", std::move(fn), nullptr,
                      grpc_core::Thread::Options().set_joinable(false));
  t.Start();
}

// Creates a listener that wraps the provided callbacks to execute them
// asynchronously in separate threads. Manages pending accept operations.
absl::StatusOr<std::unique_ptr<EventEngine::Listener>>
ThreadyEventEngine::CreateListener(
    Listener::AcceptCallback on_accept,
    absl::AnyInvocable<void(absl::Status)> on_shutdown,
    const EndpointConfig& config,
    std::unique_ptr<MemoryAllocatorFactory> memory_allocator_factory) {
  // Shared state to track pending accept operations
  struct AcceptState {
    grpc_core::Mutex mu_;                // Mutex for thread safety
    grpc_core::CondVar cv_;              // Condition variable for synchronization
    int pending_accepts_ ABSL_GUARDED_BY(mu_) = 0;  // Count of pending accepts
  };
  auto accept_state = std::make_shared<AcceptState>();

  // Create the listener with wrapped callbacks that execute asynchronously
  return impl_->CreateListener(
      [this, accept_state,
       on_accept = std::make_shared<Listener::AcceptCallback>(
           std::move(on_accept))](std::unique_ptr<Endpoint> endpoint,
                                  MemoryAllocator memory_allocator) {
        // Increment pending accepts count under lock
        {
          grpc_core::MutexLock lock(&accept_state->mu_);
          ++accept_state->pending_accepts_;
        }
        // Execute the accept callback asynchronously
        Asynchronously(
            [on_accept, accept_state, endpoint = std::move(endpoint),
             memory_allocator = std::move(memory_allocator)]() mutable {
              (*on_accept)(std::move(endpoint), std::move(memory_allocator));
              // Decrement pending accepts and signal if none left
              {
                grpc_core::MutexLock lock(&accept_state->mu_);
                --accept_state->pending_accepts_;
                if (accept_state->pending_accepts_ == 0) {
                  accept_state->cv_.Signal();
                }
              }
            });
      },
      // Wrapped shutdown callback that waits for pending accepts to complete
      [this, accept_state,
       on_shutdown = std::move(on_shutdown)](absl::Status status) mutable {
        Asynchronously([accept_state, on_shutdown = std::move(on_shutdown),
                        status = std::move(status)]() mutable {
          // Wait for all pending accepts to complete
          while (true) {
            grpc_core::MutexLock lock(&accept_state->mu_);
            if (accept_state->pending_accepts_ == 0) {
              break;
            }
            accept_state->cv_.Wait(&accept_state->mu_);
          }
          on_shutdown(std::move(status));
        });
      },
      config, std::move(memory_allocator_factory));
}

// Initiates a connection and executes the callback asynchronously
EventEngine::ConnectionHandle ThreadyEventEngine::Connect(
    OnConnectCallback on_connect, const ResolvedAddress& addr,
    const EndpointConfig& args, MemoryAllocator memory_allocator,
    Duration timeout) {
  return impl_->Connect(
      [this, on_connect = std::move(on_connect)](
          absl::StatusOr<std::unique_ptr<Endpoint>> c) mutable {
        Asynchronously(
            [on_connect = std::move(on_connect), c = std::move(c)]() mutable {
              on_connect(std::move(c));
            });
      },
      addr, args, std::move(memory_allocator), timeout);
}

// Cancels an ongoing connection attempt
bool ThreadyEventEngine::CancelConnect(ConnectionHandle handle) {
  return impl_->CancelConnect(handle);
}

// Placeholder method - intentionally crashes if called
bool ThreadyEventEngine::IsWorkerThread() {
  grpc_core::Crash("we should remove this");
}

// Creates a DNS resolver that executes callbacks asynchronously
absl::StatusOr<std::unique_ptr<EventEngine::DNSResolver>>
ThreadyEventEngine::GetDNSResolver(
    const DNSResolver::ResolverOptions& options) {
  return std::make_unique<ThreadyDNSResolver>(
      *impl_->GetDNSResolver(options),
      std::static_pointer_cast<ThreadyEventEngine>(shared_from_this()));
}

// Runs a closure asynchronously (overload for Closure* type)
void ThreadyEventEngine::Run(Closure* closure) {
  Run([closure]() { closure->Run(); });
}

// Runs an invocable asynchronously
void ThreadyEventEngine::Run(absl::AnyInvocable<void()> closure) {
  Asynchronously(std::move(closure));
}

// Schedules a closure to run after a delay (overload for Closure* type)
EventEngine::TaskHandle ThreadyEventEngine::RunAfter(Duration when,
                                                     Closure* closure) {
  return RunAfter(when, [closure]() { closure->Run(); });
}

// Schedules an invocable to run after a delay
EventEngine::TaskHandle ThreadyEventEngine::RunAfter(
    Duration when, absl::AnyInvocable<void()> closure) {
  return impl_->RunAfter(when, [this, closure = std::move(closure)]() mutable {
    Asynchronously(std::move(closure));
  });
}

// Cancels a scheduled task
bool ThreadyEventEngine::Cancel(TaskHandle handle) {
  return impl_->Cancel(handle);
}

// DNS Resolver implementation that executes callbacks asynchronously

// Performs a hostname lookup and executes callback asynchronously
void ThreadyEventEngine::ThreadyDNSResolver::LookupHostname(
    LookupHostnameCallback on_resolve, absl::string_view name,
    absl::string_view default_port) {
  return impl_->LookupHostname(
      [engine = engine_, on_resolve = std::move(on_resolve)](
          absl::StatusOr<std::vector<ResolvedAddress>> addresses) mutable {
        engine->Asynchronously([on_resolve = std::move(on_resolve),
                                addresses = std::move(addresses)]() mutable {
          on_resolve(std::move(addresses));
        });
      },
      name, default_port);
}

// Performs an SRV record lookup and executes callback asynchronously
void ThreadyEventEngine::ThreadyDNSResolver::LookupSRV(
    LookupSRVCallback on_resolve, absl::string_view name) {
  return impl_->LookupSRV(
      [engine = engine_, on_resolve = std::move(on_resolve)](
          absl::StatusOr<std::vector<SRVRecord>> records) mutable {
        return engine->Asynchronously([on_resolve = std::move(on_resolve),
                                       records = std::move(records)]() mutable {
          on_resolve(std::move(records));
        });
      },
      name);
}

// Performs a TXT record lookup and executes callback asynchronously
void ThreadyEventEngine::ThreadyDNSResolver::LookupTXT(
    LookupTXTCallback on_resolve, absl::string_view name) {
  return impl_->LookupTXT(
      [engine = engine_, on_resolve = std::move(on_resolve)](
          absl::StatusOr<std::vector<std::string>> record) mutable {
        return engine->Asynchronously([on_resolve = std::move(on_resolve),
                                       record = std::move(record)]() mutable {
          on_resolve(std::move(record));
        });
      },
      name);
}

}  // namespace grpc_event_engine::experimental
```