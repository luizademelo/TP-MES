// Copyright 2022 The gRPC Authors

#include "src/core/lib/event_engine/posix_engine/posix_engine.h"

#include <grpc/event_engine/event_engine.h>
#include <grpc/event_engine/memory_allocator.h>
#include <grpc/event_engine/slice_buffer.h>
#include <grpc/support/cpu.h>
#include <grpc/support/port_platform.h>

#include <algorithm>
#include <atomic>
#include <chrono>
#include <cstdint>
#include <cstring>
#include <memory>
#include <string>
#include <type_traits>
#include <utility>

#include "absl/cleanup/cleanup.h"
#include "absl/functional/any_invocable.h"
#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/status/status.h"
#include "absl/strings/match.h"
#include "absl/strings/str_cat.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/lib/event_engine/ares_resolver.h"
#include "src/core/lib/event_engine/forkable.h"
#include "src/core/lib/event_engine/grpc_polled_fd.h"
#include "src/core/lib/event_engine/poller.h"
#include "src/core/lib/event_engine/posix.h"
#include "src/core/lib/event_engine/posix_engine/grpc_polled_fd_posix.h"
#include "src/core/lib/event_engine/posix_engine/native_posix_dns_resolver.h"
#include "src/core/lib/event_engine/posix_engine/tcp_socket_utils.h"
#include "src/core/lib/event_engine/posix_engine/timer.h"
#include "src/core/lib/event_engine/tcp_socket_utils.h"
#include "src/core/lib/event_engine/utils.h"
#include "src/core/lib/experiments/experiments.h"
#include "src/core/util/crash.h"
#include "src/core/util/no_destruct.h"
#include "src/core/util/sync.h"
#include "src/core/util/useful.h"

#ifdef GRPC_POSIX_SOCKET_TCP
#include <errno.h>
#include <stdint.h>
#include <sys/socket.h>

#include "src/core/lib/event_engine/posix_engine/event_poller.h"
#include "src/core/lib/event_engine/posix_engine/event_poller_posix_default.h"
#include "src/core/lib/event_engine/posix_engine/posix_endpoint.h"
#include "src/core/lib/event_engine/posix_engine/posix_engine_listener.h"
#endif

#if defined(GRPC_POSIX_SOCKET_TCP) && \
    !defined(GRPC_DO_NOT_INSTANTIATE_POSIX_POLLER)
#define GRPC_PLATFORM_SUPPORTS_POSIX_POLLING true
#else
#define GRPC_PLATFORM_SUPPORTS_POSIX_POLLING false
#endif

using namespace std::chrono_literals;

namespace grpc_event_engine::experimental {

namespace {

grpc_core::NoDestruct<ObjectGroupForkHandler> g_timer_fork_manager;

class TimerForkCallbackMethods {
 public:
  static void Prefork() { g_timer_fork_manager->Prefork(); }
  static void PostforkParent() { g_timer_fork_manager->PostforkParent(); }
  static void PostforkChild() { g_timer_fork_manager->PostforkChild(); }
};

}

#ifdef GRPC_POSIX_SOCKET_TCP

void AsyncConnect::Start(EventEngine::Duration timeout) {
  on_writable_ = PosixEngineClosure::ToPermanentClosure(
      [this](absl::Status status) { OnWritable(std::move(status)); });
  alarm_handle_ = engine_->RunAfter(timeout, [this]() {
    OnTimeoutExpired(absl::DeadlineExceededError("connect() timed out"));
  });
  fd_->NotifyOnWrite(on_writable_);
}

AsyncConnect ::~AsyncConnect() { delete on_writable_; }

void AsyncConnect::OnTimeoutExpired(absl::Status status) {
  bool done = false;
  {
    grpc_core::MutexLock lock(&mu_);
    if (fd_ != nullptr) {
      fd_->ShutdownHandle(std::move(status));
    }
    done = (--refs_ == 0);
  }
  if (done) {
    delete this;
  }
}

void AsyncConnect::OnWritable(absl::Status status)
    ABSL_NO_THREAD_SAFETY_ANALYSIS {
  int so_error = 0;
  socklen_t so_error_size;
  int err;
  int done;
  int consumed_refs = 1;
  EventHandle* fd;
  absl::StatusOr<std::unique_ptr<EventEngine::Endpoint>> ep;

  mu_.Lock();
  CHECK_NE(fd_, nullptr);
  fd = std::exchange(fd_, nullptr);
  bool connect_cancelled = connect_cancelled_;
  if (fd->IsHandleShutdown() && status.ok()) {
    if (!connect_cancelled) {

      status = absl::DeadlineExceededError("connect() timed out");
    } else {

      status = absl::FailedPreconditionError("Connection cancelled");
    }
  }
  mu_.Unlock();

  if (engine_->Cancel(alarm_handle_)) {
    ++consumed_refs;
  }

  auto on_writable_finish = absl::MakeCleanup([&]() -> void {
    mu_.AssertHeld();
    if (!connect_cancelled) {
      reinterpret_cast<PosixEventEngine*>(engine_.get())
          ->OnConnectFinishInternal(connection_handle_);
    }
    if (fd != nullptr) {
      fd->OrphanHandle(nullptr, nullptr, "tcp_client_orphan");
      fd = nullptr;
    }
    if (!status.ok()) {
      ep = absl::UnknownError(
          absl::StrCat("Failed to connect to remote host: ", status.message()));
    }

    if (!connect_cancelled) {
      executor_->Run(
          [ep = std::move(ep), on_connect = std::move(on_connect_)]() mutable {
            if (on_connect) {
              on_connect(std::move(ep));
            }
          });
    }
    done = ((refs_ -= consumed_refs) == 0);
    mu_.Unlock();
    if (done) {
      delete this;
    }
  });

  mu_.Lock();
  if (!status.ok() || connect_cancelled) {
    return;
  }

  do {
    so_error_size = sizeof(so_error);
    err = getsockopt(fd->WrappedFd(), SOL_SOCKET, SO_ERROR, &so_error,
                     &so_error_size);
  } while (err < 0 && errno == EINTR);
  if (err < 0) {
    status = absl::FailedPreconditionError(
        absl::StrCat("getsockopt: ", std::strerror(errno)));
    return;
  }

  switch (so_error) {
    case 0:
      ep = CreatePosixEndpoint(fd, nullptr, engine_, std::move(allocator_),
                               options_);
      fd = nullptr;
      break;
    case ENOBUFS:

      LOG(ERROR) << "kernel out of buffers";
      mu_.Unlock();
      fd->NotifyOnWrite(on_writable_);

      std::move(on_writable_finish).Cancel();
      return;
    case ECONNREFUSED:

      status = absl::FailedPreconditionError(std::strerror(so_error));
      break;
    default:

      status = absl::FailedPreconditionError(
          absl::StrCat("getsockopt(SO_ERROR): ", std::strerror(so_error)));
      break;
  }
}

EventEngine::ConnectionHandle
PosixEventEngine::CreateEndpointFromUnconnectedFdInternal(
    int fd, EventEngine::OnConnectCallback on_connect,
    const EventEngine::ResolvedAddress& addr,
    const PosixTcpOptions& tcp_options, MemoryAllocator memory_allocator,
    EventEngine::Duration timeout) {
  int err;
  int connect_errno;
  do {
    err = connect(fd, addr.address(), addr.size());
  } while (err < 0 && errno == EINTR);
  connect_errno = (err < 0) ? errno : 0;

  auto addr_uri = ResolvedAddressToURI(addr);
  if (!addr_uri.ok()) {
    Run([on_connect = std::move(on_connect),
         ep = absl::FailedPreconditionError(absl::StrCat(
             "connect failed: ", "invalid addr: ",
             addr_uri.value()))]() mutable { on_connect(std::move(ep)); });
    return EventEngine::ConnectionHandle::kInvalid;
  }

  std::string name = absl::StrCat("tcp-client:", addr_uri.value());
  PosixEventPoller* poller = poller_manager_->Poller();
  EventHandle* handle =
      poller->CreateHandle(fd, name, poller->CanTrackErrors());

  if (connect_errno == 0) {

    Run([on_connect = std::move(on_connect),
         ep = CreatePosixEndpoint(
             handle, nullptr, shared_from_this(), std::move(memory_allocator),
             tcp_options)]() mutable { on_connect(std::move(ep)); });
    return EventEngine::ConnectionHandle::kInvalid;
  }
  if (connect_errno != EWOULDBLOCK && connect_errno != EINPROGRESS) {

    handle->OrphanHandle(nullptr, nullptr, "tcp_client_connect_error");
    Run([on_connect = std::move(on_connect),
         ep = absl::FailedPreconditionError(absl::StrCat(
             "connect failed: ", "addr: ", addr_uri.value(),
             " error: ", std::strerror(connect_errno)))]() mutable {
      on_connect(std::move(ep));
    });
    return EventEngine::ConnectionHandle::kInvalid;
  }

  int64_t connection_id =
      last_connection_id_.fetch_add(1, std::memory_order_acq_rel);
  AsyncConnect* ac =
      new AsyncConnect(std::move(on_connect), shared_from_this(),
                       executor_.get(), handle, std::move(memory_allocator),
                       tcp_options, addr_uri.value(), connection_id);
  int shard_number = connection_id % connection_shards_.size();
  struct ConnectionShard* shard = &connection_shards_[shard_number];
  {
    grpc_core::MutexLock lock(&shard->mu);
    shard->pending_connections.insert_or_assign(connection_id, ac);
  }

  ac->Start(timeout);
  return {static_cast<intptr_t>(connection_id), 0};
}

void PosixEventEngine::OnConnectFinishInternal(int connection_handle) {
  int shard_number = connection_handle % connection_shards_.size();
  struct ConnectionShard* shard = &connection_shards_[shard_number];
  {
    grpc_core::MutexLock lock(&shard->mu);
    shard->pending_connections.erase(connection_handle);
  }
}

PosixEnginePollerManager::PosixEnginePollerManager(
    std::shared_ptr<ThreadPool> executor)
    : poller_(grpc_event_engine::experimental::MakeDefaultPoller(this)),
      executor_(std::move(executor)),
      trigger_shutdown_called_(false) {}

PosixEnginePollerManager::PosixEnginePollerManager(
    std::shared_ptr<PosixEventPoller> poller)
    : poller_(std::move(poller)),
      poller_state_(PollerState::kExternal),
      executor_(nullptr),
      trigger_shutdown_called_(false) {
  DCHECK_NE(poller_, nullptr);
}

void PosixEnginePollerManager::Run(
    experimental::EventEngine::Closure* closure) {
  if (executor_ != nullptr) {
    executor_->Run(closure);
  }
}

void PosixEnginePollerManager::Run(absl::AnyInvocable<void()> cb) {
  if (executor_ != nullptr) {
    executor_->Run(std::move(cb));
  }
}

void PosixEnginePollerManager::TriggerShutdown() {
  DCHECK(trigger_shutdown_called_ == false);
  trigger_shutdown_called_ = true;

  if (poller_state_.exchange(PollerState::kShuttingDown) ==
      PollerState::kExternal) {
    poller_ = nullptr;
    return;
  }
  poller_->Kick();
}

std::shared_ptr<PosixEventEngine> PosixEventEngine::MakePosixEventEngine() {

  return std::shared_ptr<PosixEventEngine>(new PosixEventEngine());
}

#ifdef GRPC_POSIX_SOCKET_TCP

std::shared_ptr<PosixEventEngine>
PosixEventEngine::MakeTestOnlyPosixEventEngine(
    std::shared_ptr<grpc_event_engine::experimental::PosixEventPoller>
        test_only_poller) {

  return std::shared_ptr<PosixEventEngine>(
      new PosixEventEngine(std::move(test_only_poller)));
}
#endif

PosixEnginePollerManager::~PosixEnginePollerManager() {
  if (poller_ != nullptr) {
    poller_->Shutdown();
  }
}

PosixEventEngine::PosixEventEngine(std::shared_ptr<PosixEventPoller> poller)
    : grpc_core::KeepsGrpcInitialized(
          !grpc_core::IsPosixEeSkipGrpcInitEnabled()),
      connection_shards_(std::max(2 * gpr_cpu_num_cores(), 1u)),
      executor_(MakeThreadPool(grpc_core::Clamp(gpr_cpu_num_cores(), 4u, 16u))),
      timer_manager_(std::make_shared<TimerManager>(executor_)) {
  g_timer_fork_manager->RegisterForkable(
      timer_manager_, TimerForkCallbackMethods::Prefork,
      TimerForkCallbackMethods::PostforkParent,
      TimerForkCallbackMethods::PostforkChild);
#if GRPC_PLATFORM_SUPPORTS_POSIX_POLLING
  poller_manager_ = std::make_shared<PosixEnginePollerManager>(poller);
#endif
}

PosixEventEngine::PosixEventEngine()
    : grpc_core::KeepsGrpcInitialized(
          !grpc_core::IsPosixEeSkipGrpcInitEnabled()),
      connection_shards_(std::max(2 * gpr_cpu_num_cores(), 1u)),
      executor_(MakeThreadPool(grpc_core::Clamp(gpr_cpu_num_cores(), 4u, 16u))),
      timer_manager_(std::make_shared<TimerManager>(executor_)) {
  g_timer_fork_manager->RegisterForkable(
      timer_manager_, TimerForkCallbackMethods::Prefork,
      TimerForkCallbackMethods::PostforkParent,
      TimerForkCallbackMethods::PostforkChild);
#if GRPC_PLATFORM_SUPPORTS_POSIX_POLLING
  poller_manager_ = std::make_shared<PosixEnginePollerManager>(executor_);

  if (poller_manager_->Poller() != nullptr) {
    executor_->Run([poller_manager = poller_manager_]() {
      PollerWorkInternal(poller_manager);
    });
  }
#endif
}

void PosixEventEngine::PollerWorkInternal(
    std::shared_ptr<PosixEnginePollerManager> poller_manager) {

  PosixEventPoller* poller = poller_manager->Poller();
  ThreadPool* executor = poller_manager->Executor();
  auto result = poller->Work(24h, [executor, &poller_manager]() {
    executor->Run([poller_manager]() mutable {
      PollerWorkInternal(std::move(poller_manager));
    });
  });
  if (result == Poller::WorkResult::kDeadlineExceeded) {

    executor->Run([poller_manager = std::move(poller_manager)]() {
      PollerWorkInternal(poller_manager);
    });
  } else if (result == Poller::WorkResult::kKicked &&
             poller_manager->IsShuttingDown()) {

    if (poller_manager.use_count() > 1) {
      poller->Kick();
    }
  }
}

#endif

struct PosixEventEngine::ClosureData final : public EventEngine::Closure {
  absl::AnyInvocable<void()> cb;
  Timer timer;
  PosixEventEngine* engine;
  EventEngine::TaskHandle handle;

  void Run() override {
    GRPC_TRACE_LOG(event_engine, INFO)
        << "PosixEventEngine:" << engine << " executing callback:" << handle;
    {
      grpc_core::MutexLock lock(&engine->mu_);
      engine->known_handles_.erase(handle);
    }
    cb();
    delete this;
  }
};

PosixEventEngine::~PosixEventEngine() {
  {
    grpc_core::MutexLock lock(&mu_);
    if (GRPC_TRACE_FLAG_ENABLED(event_engine)) {
      for (auto handle : known_handles_) {
        LOG(ERROR) << "(event_engine) PosixEventEngine:" << this
                   << " uncleared TaskHandle at shutdown:"
                   << HandleToString(handle);
      }
    }
    CHECK(GPR_LIKELY(known_handles_.empty()));
  }
  timer_manager_->Shutdown();
#if GRPC_PLATFORM_SUPPORTS_POSIX_POLLING
  if (poller_manager_ != nullptr) {
    poller_manager_->TriggerShutdown();
  }
#endif
  executor_->Quiesce();
}

bool PosixEventEngine::Cancel(EventEngine::TaskHandle handle) {
  grpc_core::MutexLock lock(&mu_);
  if (!known_handles_.contains(handle)) return false;
  auto* cd = reinterpret_cast<ClosureData*>(handle.keys[0]);
  bool r = timer_manager_->TimerCancel(&cd->timer);
  known_handles_.erase(handle);
  if (r) delete cd;
  return r;
}

EventEngine::TaskHandle PosixEventEngine::RunAfter(
    Duration when, absl::AnyInvocable<void()> closure) {
  return RunAfterInternal(when, std::move(closure));
}

EventEngine::TaskHandle PosixEventEngine::RunAfter(
    Duration when, EventEngine::Closure* closure) {
  return RunAfterInternal(when, [closure]() { closure->Run(); });
}

void PosixEventEngine::Run(absl::AnyInvocable<void()> closure) {
  executor_->Run(std::move(closure));
}

void PosixEventEngine::Run(EventEngine::Closure* closure) {
  executor_->Run(closure);
}

EventEngine::TaskHandle PosixEventEngine::RunAfterInternal(
    Duration when, absl::AnyInvocable<void()> cb) {
  if (when <= Duration::zero()) {
    Run(std::move(cb));
    return TaskHandle::kInvalid;
  }
  auto when_ts = ToTimestamp(timer_manager_->Now(), when);
  auto* cd = new ClosureData;
  cd->cb = std::move(cb);
  cd->engine = this;
  EventEngine::TaskHandle handle{reinterpret_cast<intptr_t>(cd),
                                 aba_token_.fetch_add(1)};
  grpc_core::MutexLock lock(&mu_);
  known_handles_.insert(handle);
  cd->handle = handle;
  GRPC_TRACE_LOG(event_engine, INFO)
      << "PosixEventEngine:" << this << " scheduling callback:" << handle;
  timer_manager_->TimerInit(&cd->timer, when_ts, cd);
  return handle;
}

PosixEventEngine::PosixDNSResolver::PosixDNSResolver(
    grpc_core::OrphanablePtr<RefCountedDNSResolverInterface> dns_resolver)
    : dns_resolver_(std::move(dns_resolver)) {}

void PosixEventEngine::PosixDNSResolver::LookupHostname(
    LookupHostnameCallback on_resolve, absl::string_view name,
    absl::string_view default_port) {
  dns_resolver_->LookupHostname(std::move(on_resolve), name, default_port);
}

void PosixEventEngine::PosixDNSResolver::LookupSRV(LookupSRVCallback on_resolve,
                                                   absl::string_view name) {
  dns_resolver_->LookupSRV(std::move(on_resolve), name);
}

void PosixEventEngine::PosixDNSResolver::LookupTXT(LookupTXTCallback on_resolve,
                                                   absl::string_view name) {
  dns_resolver_->LookupTXT(std::move(on_resolve), name);
}

absl::StatusOr<std::unique_ptr<EventEngine::DNSResolver>>
PosixEventEngine::GetDNSResolver(
    GRPC_UNUSED const EventEngine::DNSResolver::ResolverOptions& options) {
#ifndef GRPC_POSIX_SOCKET_RESOLVE_ADDRESS
  grpc_core::Crash("Unable to get DNS resolver for this platform.");
#else

  if (ShouldUseAresDnsResolver()) {
#if GRPC_ARES == 1 && defined(GRPC_POSIX_SOCKET_ARES_EV_DRIVER)
    GRPC_TRACE_LOG(event_engine_dns, INFO)
        << "PosixEventEngine::" << this << " creating AresResolver";
    auto ares_resolver = AresResolver::CreateAresResolver(
        options.dns_server,
        std::make_unique<GrpcPolledFdFactoryPosix>(poller_manager_->Poller()),
        shared_from_this());
    if (!ares_resolver.ok()) {
      return ares_resolver.status();
    }
    return std::make_unique<PosixEventEngine::PosixDNSResolver>(
        std::move(*ares_resolver));
#endif
  }
  GRPC_TRACE_LOG(event_engine_dns, INFO)
      << "PosixEventEngine::" << this << " creating NativePosixDNSResolver";
  return std::make_unique<NativePosixDNSResolver>(shared_from_this());
#endif
}

bool PosixEventEngine::IsWorkerThread() { grpc_core::Crash("unimplemented"); }

bool PosixEventEngine::CancelConnect(EventEngine::ConnectionHandle handle) {
#if GRPC_PLATFORM_SUPPORTS_POSIX_POLLING
  int connection_handle = handle.keys[0];
  if (connection_handle <= 0) {
    return false;
  }
  int shard_number = connection_handle % connection_shards_.size();
  struct ConnectionShard* shard = &connection_shards_[shard_number];
  AsyncConnect* ac = nullptr;
  {
    grpc_core::MutexLock lock(&shard->mu);
    auto it = shard->pending_connections.find(connection_handle);
    if (it != shard->pending_connections.end()) {
      ac = it->second;
      CHECK_NE(ac, nullptr);

      ++ac->refs_;

      shard->pending_connections.erase(it);
    }
  }
  if (ac == nullptr) {
    return false;
  }
  ac->mu_.Lock();
  bool connection_cancel_success = (ac->fd_ != nullptr);
  if (connection_cancel_success) {

    ac->connect_cancelled_ = true;

    ac->fd_->ShutdownHandle(
        absl::FailedPreconditionError("Connection cancelled"));
  }
  bool done = (--ac->refs_ == 0);
  ac->mu_.Unlock();
  if (done) {
    delete ac;
  }
  return connection_cancel_success;
#else
  grpc_core::Crash(
      "EventEngine::CancelConnect is not supported on this platform");
#endif
}

EventEngine::ConnectionHandle PosixEventEngine::Connect(
    OnConnectCallback on_connect, const ResolvedAddress& addr,
    const EndpointConfig& args, MemoryAllocator memory_allocator,
    Duration timeout) {
#if GRPC_PLATFORM_SUPPORTS_POSIX_POLLING
  CHECK_NE(poller_manager_, nullptr);
  PosixTcpOptions options = TcpOptionsFromEndpointConfig(args);
  absl::StatusOr<PosixSocketWrapper::PosixSocketCreateResult> socket =
      PosixSocketWrapper::CreateAndPrepareTcpClientSocket(options, addr);
  if (!socket.ok()) {
    Run([on_connect = std::move(on_connect),
         status = socket.status()]() mutable { on_connect(status); });
    return EventEngine::ConnectionHandle::kInvalid;
  }
  return CreateEndpointFromUnconnectedFdInternal(
      (*socket).sock.Fd(), std::move(on_connect), (*socket).mapped_target_addr,
      options, std::move(memory_allocator), timeout);
#else
  grpc_core::Crash("EventEngine::Connect is not supported on this platform");
#endif
}

EventEngine::ConnectionHandle PosixEventEngine::CreateEndpointFromUnconnectedFd(
    int fd, EventEngine::OnConnectCallback on_connect,
    const EventEngine::ResolvedAddress& addr, const EndpointConfig& config,
    MemoryAllocator memory_allocator, EventEngine::Duration timeout) {
#if GRPC_PLATFORM_SUPPORTS_POSIX_POLLING
  return CreateEndpointFromUnconnectedFdInternal(
      fd, std::move(on_connect), addr, TcpOptionsFromEndpointConfig(config),
      std::move(memory_allocator), timeout);
#else
  grpc_core::Crash(
      "EventEngine::CreateEndpointFromUnconnectedFd is not supported on this "
      "platform");
#endif
}

std::unique_ptr<EventEngine::Endpoint>
PosixEventEngine::CreatePosixEndpointFromFd(int fd,
                                            const EndpointConfig& config,
                                            MemoryAllocator memory_allocator) {
#if GRPC_PLATFORM_SUPPORTS_POSIX_POLLING
  DCHECK_GT(fd, 0);
  PosixEventPoller* poller = poller_manager_->Poller();
  DCHECK_NE(poller, nullptr);
  EventHandle* handle =
      poller->CreateHandle(fd, "tcp-client", poller->CanTrackErrors());
  return CreatePosixEndpoint(handle, nullptr, shared_from_this(),
                             std::move(memory_allocator),
                             TcpOptionsFromEndpointConfig(config));
#else
  grpc_core::Crash(
      "PosixEventEngine::CreatePosixEndpointFromFd is not supported on "
      "this platform");
#endif
}

std::unique_ptr<EventEngine::Endpoint> PosixEventEngine::CreateEndpointFromFd(
    int fd, const EndpointConfig& config) {
  auto options = TcpOptionsFromEndpointConfig(config);
  MemoryAllocator allocator;
  if (options.memory_allocator_factory != nullptr) {
    return CreatePosixEndpointFromFd(
        fd, config,
        options.memory_allocator_factory->CreateMemoryAllocator(
            absl::StrCat("allocator:", fd)));
  }
  return CreatePosixEndpointFromFd(
      fd, config,
      options.resource_quota->memory_quota()->CreateMemoryAllocator(
          absl::StrCat("allocator:", fd)));
}

absl::StatusOr<std::unique_ptr<EventEngine::Listener>>
PosixEventEngine::CreateListener(
    Listener::AcceptCallback on_accept,
    absl::AnyInvocable<void(absl::Status)> on_shutdown,
    const EndpointConfig& config,
    std::unique_ptr<MemoryAllocatorFactory> memory_allocator_factory) {
#if GRPC_PLATFORM_SUPPORTS_POSIX_POLLING
  PosixEventEngineWithFdSupport::PosixAcceptCallback posix_on_accept =
      [on_accept_cb = std::move(on_accept)](
          int , std::unique_ptr<EventEngine::Endpoint> ep,
          bool , MemoryAllocator allocator,
          SliceBuffer* ) mutable {
        on_accept_cb(std::move(ep), std::move(allocator));
      };
  return std::make_unique<PosixEngineListener>(
      std::move(posix_on_accept), std::move(on_shutdown), config,
      std::move(memory_allocator_factory), poller_manager_->Poller(),
      shared_from_this());
#else
  grpc_core::Crash(
      "EventEngine::CreateListener is not supported on this platform");
#endif
}

absl::StatusOr<std::unique_ptr<EventEngine::Listener>>
PosixEventEngine::CreatePosixListener(
    PosixEventEngineWithFdSupport::PosixAcceptCallback on_accept,
    absl::AnyInvocable<void(absl::Status)> on_shutdown,
    const EndpointConfig& config,
    std::unique_ptr<MemoryAllocatorFactory> memory_allocator_factory) {
#if GRPC_PLATFORM_SUPPORTS_POSIX_POLLING
  return std::make_unique<PosixEngineListener>(
      std::move(on_accept), std::move(on_shutdown), config,
      std::move(memory_allocator_factory), poller_manager_->Poller(),
      shared_from_this());
#else
  grpc_core::Crash(
      "EventEngine::CreateListener is not supported on this platform");
#endif
}

}
