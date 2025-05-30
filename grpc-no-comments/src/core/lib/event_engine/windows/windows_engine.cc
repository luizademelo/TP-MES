// Copyright 2022 The gRPC Authors

#include <grpc/support/port_platform.h>

#ifdef GPR_WINDOWS

#include <grpc/event_engine/endpoint_config.h>
#include <grpc/event_engine/event_engine.h>
#include <grpc/event_engine/memory_allocator.h>
#include <grpc/event_engine/slice_buffer.h>
#include <grpc/support/cpu.h>

#include <memory>
#include <ostream>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/string_view.h"
#include "src/core/lib/event_engine/channel_args_endpoint_config.h"
#include "src/core/lib/event_engine/common_closures.h"
#include "src/core/lib/event_engine/handle_containers.h"
#include "src/core/lib/event_engine/posix_engine/timer_manager.h"
#include "src/core/lib/event_engine/tcp_socket_utils.h"
#include "src/core/lib/event_engine/thread_pool/thread_pool.h"
#include "src/core/lib/event_engine/utils.h"
#include "src/core/lib/event_engine/windows/grpc_polled_fd_windows.h"
#include "src/core/lib/event_engine/windows/iocp.h"
#include "src/core/lib/event_engine/windows/native_windows_dns_resolver.h"
#include "src/core/lib/event_engine/windows/windows_endpoint.h"
#include "src/core/lib/event_engine/windows/windows_engine.h"
#include "src/core/lib/event_engine/windows/windows_listener.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/lib/resource_quota/resource_quota.h"
#include "src/core/lib/surface/init_internally.h"
#include "src/core/util/crash.h"
#include "src/core/util/dump_args.h"
#include "src/core/util/sync.h"
#include "src/core/util/time.h"

namespace grpc_event_engine::experimental {

std::ostream& operator<<(
    std::ostream& out,
    const WindowsEventEngine::ConnectionState& connection_state) {
  out << "ConnectionState::" << &connection_state
      << ": connection_state.address="
      << ResolvedAddressToURI(connection_state.address_) << ","
      << GRPC_DUMP_ARGS(connection_state.has_run_,
                        connection_state.connection_handle_,
                        connection_state.timer_handle_);
  return out;
}

WindowsEventEngine::ConnectionState::ConnectionState(
    std::shared_ptr<WindowsEventEngine> engine,
    std::unique_ptr<WinSocket> socket, EventEngine::ResolvedAddress address,
    MemoryAllocator allocator,
    EventEngine::OnConnectCallback on_connect_user_callback)
    : socket_(std::move(socket)),
      address_(address),
      allocator_(std::move(allocator)),
      on_connect_user_callback_(std::move(on_connect_user_callback)),
      engine_(std::move(engine)) {
  CHECK(socket_ != nullptr);
  connection_handle_ = ConnectionHandle{reinterpret_cast<intptr_t>(this),
                                        engine_->aba_token_.fetch_add(1)};
}

void WindowsEventEngine::ConnectionState::Start(Duration timeout) {
  on_connected_cb_ =
      std::make_unique<OnConnectedCallback>(engine_.get(), shared_from_this());
  socket_->NotifyOnWrite(on_connected_cb_.get());
  deadline_timer_cb_ = std::make_unique<DeadlineTimerCallback>(
      engine_.get(), shared_from_this());
  timer_handle_ = engine_->RunAfter(timeout, deadline_timer_cb_.get());
}

EventEngine::OnConnectCallback
WindowsEventEngine::ConnectionState::TakeCallback() {
  return std::exchange(on_connect_user_callback_, nullptr);
}

std::unique_ptr<WindowsEndpoint>
WindowsEventEngine::ConnectionState::FinishConnectingAndMakeEndpoint(
    ThreadPool* thread_pool) {
  ChannelArgsEndpointConfig cfg;
  return std::make_unique<WindowsEndpoint>(address_, std::move(socket_),
                                           std::move(allocator_), cfg,
                                           thread_pool, engine_);
}

void WindowsEventEngine::ConnectionState::AbortOnConnect() {
  on_connected_cb_.reset();
}

void WindowsEventEngine::ConnectionState::AbortDeadlineTimer() {
  deadline_timer_cb_.reset();
}

void WindowsEventEngine::ConnectionState::OnConnectedCallback::Run() {
  DCHECK_NE(connection_state_, nullptr)
      << "ConnectionState::OnConnectedCallback::" << this
      << " has already run. It should only ever run once.";
  bool has_run;
  {
    grpc_core::MutexLock lock(&connection_state_->mu_);
    has_run = std::exchange(connection_state_->has_run_, true);
  }

  if (has_run) {
    connection_state_.reset();
    return;
  }
  engine_->OnConnectCompleted(std::move(connection_state_));
}

void WindowsEventEngine::ConnectionState::DeadlineTimerCallback::Run() {
  DCHECK_NE(connection_state_, nullptr)
      << "ConnectionState::DeadlineTimerCallback::" << this
      << " has already run. It should only ever run once.";
  bool has_run;
  {
    grpc_core::MutexLock lock(&connection_state_->mu_);
    has_run = std::exchange(connection_state_->has_run_, true);
  }

  if (has_run) {
    connection_state_.reset();
    return;
  }
  engine_->OnDeadlineTimerFired(std::move(connection_state_));
}

WindowsEventEngine::IOCPWorkClosure::IOCPWorkClosure(ThreadPool* thread_pool,
                                                     IOCP* iocp)
    : thread_pool_(thread_pool), iocp_(iocp) {
  thread_pool_->Run(this);
}

void WindowsEventEngine::IOCPWorkClosure::Run() {
  if (done_signal_.HasBeenNotified()) return;
  auto result = iocp_->Work(std::chrono::seconds(60), [this] {
    workers_.fetch_add(1);
    thread_pool_->Run(this);
  });
  if (result == Poller::WorkResult::kDeadlineExceeded) {

    workers_.fetch_add(1);
    thread_pool_->Run(this);
  }
  if (workers_.fetch_sub(1) == 1) done_signal_.Notify();
}

void WindowsEventEngine::IOCPWorkClosure::WaitForShutdown() {
  done_signal_.WaitForNotification();
}

struct WindowsEventEngine::TimerClosure final : public EventEngine::Closure {
  absl::AnyInvocable<void()> cb;
  Timer timer;
  WindowsEventEngine* engine;
  EventEngine::TaskHandle handle;

  void Run() override {
    GRPC_TRACE_LOG(event_engine, INFO)
        << "WindowsEventEngine:" << engine << " executing callback:" << handle;
    {
      grpc_core::MutexLock lock(&engine->task_mu_);
      engine->known_handles_.erase(handle);
    }
    cb();
    delete this;
  }
};

WindowsEventEngine::WindowsEventEngine()
    : thread_pool_(
          MakeThreadPool(grpc_core::Clamp(gpr_cpu_num_cores(), 4u, 16u))),
      iocp_(thread_pool_.get()),
      timer_manager_(thread_pool_),
      iocp_worker_(thread_pool_.get(), &iocp_) {
  WSADATA wsaData;
  int status = WSAStartup(MAKEWORD(2, 0), &wsaData);
  CHECK_EQ(status, 0);
}

WindowsEventEngine::~WindowsEventEngine() {
  GRPC_TRACE_LOG(event_engine, INFO) << "~WindowsEventEngine::" << this;
  {
    task_mu_.Lock();
    if (!known_handles_.empty()) {
      if (GRPC_TRACE_FLAG_ENABLED(event_engine)) {
        for (auto handle : known_handles_) {
          LOG(ERROR) << "WindowsEventEngine:" << this
                     << " uncleared TaskHandle at shutdown:"
                     << HandleToString<EventEngine::TaskHandle>(handle);
        }
      }

      auto deadline =
          timer_manager_.Now() + grpc_core::Duration::FromSecondsAsDouble(10);
      while (!known_handles_.empty() && timer_manager_.Now() < deadline) {
        if (GRPC_TRACE_FLAG_ENABLED(event_engine)) {
          VLOG_EVERY_N_SEC(2, 1) << "Waiting for timers. "
                                 << known_handles_.size() << " remaining";
        }
        task_mu_.Unlock();
        absl::SleepFor(absl::Milliseconds(200));
        task_mu_.Lock();
      }
    }
    CHECK(GPR_LIKELY(known_handles_.empty()));
    task_mu_.Unlock();
  }
  iocp_.Kick();
  iocp_worker_.WaitForShutdown();
  iocp_.Shutdown();
  CHECK_EQ(WSACleanup(), 0);
  timer_manager_.Shutdown();
  thread_pool_->Quiesce();
}

bool WindowsEventEngine::Cancel(EventEngine::TaskHandle handle) {
  grpc_core::MutexLock lock(&task_mu_);
  if (!known_handles_.contains(handle)) return false;
  GRPC_TRACE_LOG(event_engine, INFO)
      << "WindowsEventEngine::" << this << " cancelling " << handle;
  auto* cd = reinterpret_cast<TimerClosure*>(handle.keys[0]);
  bool r = timer_manager_.TimerCancel(&cd->timer);
  known_handles_.erase(handle);
  if (r) delete cd;
  return r;
}

std::unique_ptr<EventEngine::Endpoint>
WindowsEventEngine::CreateEndpointFromWinSocket(SOCKET socket,
                                                const EndpointConfig& config) {

  auto local_address = SocketToAddress(socket);
  if (!local_address.ok()) {
    LOG(ERROR) << "WindowsEventEngine::" << this
               << ": Error getting local socket address: "
               << local_address.status();
    return nullptr;
  }

  auto winsocket = iocp_.Watch(socket);
  if (winsocket == nullptr) {
    LOG(ERROR) << "WindowsEventEngine::" << this
               << ": Error registering socket with IOCP engine.";
    return nullptr;
  }

  MemoryAllocator allocator;
  auto local_address_string = *ResolvedAddressToURI(*local_address);
  auto* allocator_factory =
      config.GetVoidPointer(GRPC_ARG_EVENT_ENGINE_USE_MEMORY_ALLOCATOR_FACTORY);
  if (allocator_factory != nullptr) {
    allocator = static_cast<MemoryAllocatorFactory*>(allocator_factory)
                    ->CreateMemoryAllocator(local_address_string);
  } else {
    auto* rqv = config.GetVoidPointer(GRPC_ARG_RESOURCE_QUOTA);
    CHECK_NE(rqv, nullptr) << "WindowsEventEngine::" << this
                           << ": config does not contain a resource quota. "
                              "This should not happen.";
    allocator = static_cast<grpc_core::ResourceQuota*>(rqv)
                    ->memory_quota()
                    ->CreateMemoryAllocator(local_address_string);
  }
  return std::make_unique<WindowsEndpoint>(
      std::move(*local_address), std::move(winsocket), std::move(allocator),
      config, thread_pool_.get(), shared_from_this());
}

EventEngine::TaskHandle WindowsEventEngine::RunAfter(
    Duration when, absl::AnyInvocable<void()> closure) {
  return RunAfterInternal(when, std::move(closure));
}

EventEngine::TaskHandle WindowsEventEngine::RunAfter(
    Duration when, EventEngine::Closure* closure) {
  return RunAfterInternal(when, [closure]() { closure->Run(); });
}

void WindowsEventEngine::Run(absl::AnyInvocable<void()> closure) {
  thread_pool_->Run(std::move(closure));
}

void WindowsEventEngine::Run(EventEngine::Closure* closure) {
  thread_pool_->Run(closure);
}

EventEngine::TaskHandle WindowsEventEngine::RunAfterInternal(
    Duration when, absl::AnyInvocable<void()> cb) {
  auto when_ts = ToTimestamp(timer_manager_.Now(), when);
  auto* cd = new TimerClosure;
  cd->cb = std::move(cb);
  cd->engine = this;
  EventEngine::TaskHandle handle{reinterpret_cast<intptr_t>(cd),
                                 aba_token_.fetch_add(1)};
  grpc_core::MutexLock lock(&task_mu_);
  known_handles_.insert(handle);
  cd->handle = handle;
  GRPC_TRACE_LOG(event_engine, INFO)
      << "WindowsEventEngine:" << this << " scheduling callback:" << handle;
  timer_manager_.TimerInit(&cd->timer, when_ts, cd);
  return handle;
}

#if GRPC_ARES == 1 && defined(GRPC_WINDOWS_SOCKET_ARES_EV_DRIVER)

WindowsEventEngine::WindowsDNSResolver::WindowsDNSResolver(
    grpc_core::OrphanablePtr<AresResolver> ares_resolver)
    : ares_resolver_(std::move(ares_resolver)) {}

void WindowsEventEngine::WindowsDNSResolver::LookupHostname(
    LookupHostnameCallback on_resolve, absl::string_view name,
    absl::string_view default_port) {
  ares_resolver_->LookupHostname(std::move(on_resolve), name, default_port);
}

void WindowsEventEngine::WindowsDNSResolver::LookupSRV(
    LookupSRVCallback on_resolve, absl::string_view name) {
  ares_resolver_->LookupSRV(std::move(on_resolve), name);
}

void WindowsEventEngine::WindowsDNSResolver::LookupTXT(
    LookupTXTCallback on_resolve, absl::string_view name) {
  ares_resolver_->LookupTXT(std::move(on_resolve), name);
}

#endif

absl::StatusOr<std::unique_ptr<EventEngine::DNSResolver>>
WindowsEventEngine::GetDNSResolver(
    EventEngine::DNSResolver::ResolverOptions const& options) {
  if (ShouldUseAresDnsResolver()) {
#if GRPC_ARES == 1 && defined(GRPC_WINDOWS_SOCKET_ARES_EV_DRIVER)
    GRPC_TRACE_LOG(event_engine_dns, INFO)
        << "WindowsEventEngine::" << this << " creating AresResolver";
    auto ares_resolver = AresResolver::CreateAresResolver(
        options.dns_server,
        std::make_unique<GrpcPolledFdFactoryWindows>(poller()),
        shared_from_this());
    if (!ares_resolver.ok()) {
      return ares_resolver.status();
    }
    return std::make_unique<WindowsEventEngine::WindowsDNSResolver>(
        std::move(*ares_resolver));
#endif
  }
  GRPC_TRACE_LOG(event_engine_dns, INFO)
      << "WindowsEventEngine::" << this << " creating NativeWindowsDNSResolver";
  return std::make_unique<NativeWindowsDNSResolver>(shared_from_this());
}

bool WindowsEventEngine::IsWorkerThread() { grpc_core::Crash("unimplemented"); }

void WindowsEventEngine::OnConnectCompleted(
    std::shared_ptr<ConnectionState> state) {
  absl::StatusOr<std::unique_ptr<WindowsEndpoint>> endpoint;
  EventEngine::OnConnectCallback cb;
  {

    grpc_core::MutexLock lock(&state->mu());

    int erased_handles = 0;
    {
      grpc_core::MutexLock handle_lock(&connection_mu_);
      erased_handles =
          known_connection_handles_.erase(state->connection_handle());
    }
    if (erased_handles != 1 || !Cancel(state->timer_handle())) {
      GRPC_TRACE_LOG(event_engine, INFO)
          << "Not accepting connection since the deadline timer has fired";
      return;
    }

    state->AbortDeadlineTimer();
    const auto& overlapped_result = state->socket()->write_info()->result();
    if (!overlapped_result.error_status.ok()) {
      state->socket()->Shutdown(DEBUG_LOCATION, "ConnectEx failure");
      endpoint = overlapped_result.error_status;
    } else if (overlapped_result.wsa_error != 0) {
      state->socket()->Shutdown(DEBUG_LOCATION, "ConnectEx failure");
      endpoint = GRPC_WSA_ERROR(overlapped_result.wsa_error, "ConnectEx");
    } else {
      endpoint = state->FinishConnectingAndMakeEndpoint(thread_pool_.get());
    }
    cb = state->TakeCallback();
  }

  state.reset();
  cb(std::move(endpoint));
}

void WindowsEventEngine::OnDeadlineTimerFired(
    std::shared_ptr<ConnectionState> connection_state) {
  bool cancelled = false;
  EventEngine::OnConnectCallback cb;
  {
    grpc_core::MutexLock lock(&connection_state->mu());
    cancelled = CancelConnectFromDeadlineTimer(connection_state.get());
    if (cancelled) cb = connection_state->TakeCallback();
  }
  if (cancelled) {
    connection_state.reset();
    cb(absl::DeadlineExceededError("Connection timed out"));
  }
}

EventEngine::ConnectionHandle WindowsEventEngine::Connect(
    OnConnectCallback on_connect, const ResolvedAddress& addr,
    const EndpointConfig& , MemoryAllocator memory_allocator,
    Duration timeout) {

  absl::Status status;
  int istatus;
  auto uri = ResolvedAddressToURI(addr);
  if (!uri.ok()) {
    Run([on_connect = std::move(on_connect), status = uri.status()]() mutable {
      on_connect(status);
    });
    return EventEngine::ConnectionHandle::kInvalid;
  }
  GRPC_TRACE_LOG(event_engine, INFO)
      << "EventEngine::" << this << " connecting to " << *uri;

  ResolvedAddress address = addr;
  ResolvedAddress addr6_v4mapped;
  if (ResolvedAddressToV4Mapped(addr, &addr6_v4mapped)) {
    address = addr6_v4mapped;
  }
  const int addr_family =
      (address.address()->sa_family == AF_UNIX) ? AF_UNIX : AF_INET6;
  const int protocol = addr_family == AF_UNIX ? 0 : IPPROTO_TCP;
  SOCKET sock = WSASocket(addr_family, SOCK_STREAM, protocol, nullptr, 0,
                          IOCP::GetDefaultSocketFlags());
  if (sock == INVALID_SOCKET) {
    Run([on_connect = std::move(on_connect),
         status = GRPC_WSA_ERROR(WSAGetLastError(), "WSASocket")]() mutable {
      on_connect(status);
    });
    return EventEngine::ConnectionHandle::kInvalid;
  }
  if (addr_family == AF_UNIX) {
    status = SetSocketNonBlock(sock);
  } else {
    status = PrepareSocket(sock);
  }
  if (!status.ok()) {
    Run([on_connect = std::move(on_connect), status]() mutable {
      on_connect(status);
    });
    return EventEngine::ConnectionHandle::kInvalid;
  }

  LPFN_CONNECTEX ConnectEx;
  GUID guid = WSAID_CONNECTEX;
  DWORD ioctl_num_bytes;
  istatus = WSAIoctl(sock, SIO_GET_EXTENSION_FUNCTION_POINTER, &guid,
                     sizeof(guid), &ConnectEx, sizeof(ConnectEx),
                     &ioctl_num_bytes, nullptr, nullptr);
  if (istatus != 0) {
    Run([on_connect = std::move(on_connect),
         status = GRPC_WSA_ERROR(
             WSAGetLastError(),
             "WSAIoctl(SIO_GET_EXTENSION_FUNCTION_POINTER)")]() mutable {
      on_connect(status);
    });
    return EventEngine::ConnectionHandle::kInvalid;
  }

  ResolvedAddress local_address;
  if (addr_family == AF_UNIX) {

    sockaddr addr = {};
    addr.sa_family = AF_UNIX;
    local_address = ResolvedAddress(&addr, sizeof(addr));
  } else {
    local_address = ResolvedAddressMakeWild6(0);
  }
  istatus = bind(sock, local_address.address(), local_address.size());
  if (istatus != 0) {
    Run([on_connect = std::move(on_connect),
         status = GRPC_WSA_ERROR(WSAGetLastError(), "bind")]() mutable {
      on_connect(status);
    });
    return EventEngine::ConnectionHandle::kInvalid;
  }

  auto connection_state = std::make_shared<ConnectionState>(
      std::static_pointer_cast<WindowsEventEngine>(shared_from_this()),
      iocp_.Watch(sock), address,
      std::move(memory_allocator),
      std::move(on_connect));
  grpc_core::MutexLock lock(&connection_state->mu());
  auto* info = connection_state->socket()->write_info();
  {
    grpc_core::MutexLock connection_handle_lock(&connection_mu_);
    known_connection_handles_.insert(connection_state->connection_handle());
  }
  connection_state->Start(timeout);
  bool success =
      ConnectEx(connection_state->socket()->raw_socket(), address.address(),
                address.size(), nullptr, 0, nullptr, info->overlapped());

  if (success) return connection_state->connection_handle();

  int last_error = WSAGetLastError();
  if (last_error == ERROR_IO_PENDING) {

    return connection_state->connection_handle();
  }

  connection_state->AbortOnConnect();
  int erased_handles = 0;
  {
    grpc_core::MutexLock connection_handle_lock(&connection_mu_);
    erased_handles =
        known_connection_handles_.erase(connection_state->connection_handle());
  }
  CHECK_EQ(erased_handles, 1) << "Did not find connection handle "
                              << connection_state->connection_handle()
                              << " after a synchronous connection failure. "
                                 "This should not be possible.";
  connection_state->socket()->Shutdown(DEBUG_LOCATION, "ConnectEx");
  if (!Cancel(connection_state->timer_handle())) {

    return EventEngine::ConnectionHandle::kInvalid;
  }

  connection_state->AbortDeadlineTimer();
  Run([connection_state = std::move(connection_state),
       status = GRPC_WSA_ERROR(WSAGetLastError(), "ConnectEx")]() mutable {
    EventEngine::OnConnectCallback cb;
    {
      grpc_core::MutexLock lock(&connection_state->mu());
      cb = connection_state->TakeCallback();
    }
    connection_state.reset();
    cb(std::move(status));
  });
  return EventEngine::ConnectionHandle::kInvalid;
}

bool WindowsEventEngine::CancelConnect(EventEngine::ConnectionHandle handle) {
  if (handle == EventEngine::ConnectionHandle::kInvalid) {
    GRPC_TRACE_LOG(event_engine, INFO)
        << "Attempted to cancel an invalid connection handle";
    return false;
  }

  {
    grpc_core::MutexLock lock(&connection_mu_);
    if (known_connection_handles_.erase(handle) != 1) {
      GRPC_TRACE_LOG(event_engine, INFO)
          << "Unknown connection handle: " << handle;
      return false;
    }
  }
  auto* connection_state = reinterpret_cast<ConnectionState*>(handle.keys[0]);
  grpc_core::MutexLock state_lock(&connection_state->mu());

  if (!Cancel(connection_state->timer_handle())) return false;

  connection_state->AbortDeadlineTimer();

  return CancelConnectInternalStateLocked(connection_state);
}

bool WindowsEventEngine::CancelConnectFromDeadlineTimer(
    ConnectionState* connection_state) {

  {
    grpc_core::MutexLock lock(&connection_mu_);
    if (known_connection_handles_.erase(
            connection_state->connection_handle()) != 1) {
      return false;
    }
  }
  return CancelConnectInternalStateLocked(connection_state);
}

bool WindowsEventEngine::CancelConnectInternalStateLocked(
    ConnectionState* connection_state) {
  connection_state->socket()->Shutdown(DEBUG_LOCATION, "CancelConnect");

  GRPC_TRACE_LOG(event_engine, INFO) << "Successfully cancelled connection "
                                     << connection_state->connection_handle();
  return true;
}

absl::StatusOr<std::unique_ptr<EventEngine::Listener>>
WindowsEventEngine::CreateListener(
    Listener::AcceptCallback on_accept,
    absl::AnyInvocable<void(absl::Status)> on_shutdown,
    const EndpointConfig& config,
    std::unique_ptr<MemoryAllocatorFactory> memory_allocator_factory) {
  return std::make_unique<WindowsEventEngineListener>(
      &iocp_, std::move(on_accept), std::move(on_shutdown),
      std::move(memory_allocator_factory), shared_from_this(),
      thread_pool_.get(), config);
}
}

#endif
