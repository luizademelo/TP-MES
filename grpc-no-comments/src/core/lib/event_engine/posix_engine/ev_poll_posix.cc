// Copyright 2022 The gRPC Authors

#include "src/core/lib/event_engine/posix_engine/ev_poll_posix.h"

#include <grpc/event_engine/event_engine.h>
#include <grpc/status.h>
#include <grpc/support/port_platform.h>
#include <grpc/support/sync.h>
#include <grpc/support/time.h>
#include <stdint.h>

#include <atomic>
#include <list>
#include <memory>
#include <utility>

#include "absl/container/inlined_vector.h"
#include "absl/functional/any_invocable.h"
#include "absl/log/check.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/str_format.h"
#include "src/core/lib/event_engine/poller.h"
#include "src/core/lib/event_engine/posix_engine/event_poller.h"
#include "src/core/lib/event_engine/posix_engine/posix_engine_closure.h"
#include "src/core/lib/iomgr/port.h"
#include "src/core/util/crash.h"

#ifdef GRPC_POSIX_SOCKET_EV_POLL

#include <errno.h>
#include <grpc/support/alloc.h>
#include <limits.h>
#include <poll.h>
#include <sys/socket.h>
#include <unistd.h>

#include "src/core/lib/event_engine/common_closures.h"
#include "src/core/lib/event_engine/posix_engine/wakeup_fd_posix.h"
#include "src/core/lib/event_engine/posix_engine/wakeup_fd_posix_default.h"
#include "src/core/lib/event_engine/time_util.h"
#include "src/core/util/fork.h"
#include "src/core/util/status_helper.h"
#include "src/core/util/strerror.h"
#include "src/core/util/sync.h"
#include "src/core/util/time.h"

static const intptr_t kClosureNotReady = 0;
static const intptr_t kClosureReady = 1;
static const int kPollinCheck = POLLIN | POLLHUP | POLLERR;
static const int kPolloutCheck = POLLOUT | POLLHUP | POLLERR;

namespace grpc_event_engine::experimental {

using Events = absl::InlinedVector<PollEventHandle*, 5>;

class PollEventHandle : public EventHandle {
 public:
  PollEventHandle(int fd, std::shared_ptr<PollPoller> poller)
      : fd_(fd),
        pending_actions_(0),
        fork_fd_list_(this),
        poller_handles_list_(this),
        scheduler_(poller->GetScheduler()),
        poller_(std::move(poller)),
        is_orphaned_(false),
        is_shutdown_(false),
        closed_(false),
        released_(false),
        pollhup_(false),
        watch_mask_(-1),
        shutdown_error_(absl::OkStatus()),
        exec_actions_closure_([this]() { ExecutePendingActions(); }),
        on_done_(nullptr),
        read_closure_(reinterpret_cast<PosixEngineClosure*>(kClosureNotReady)),
        write_closure_(
            reinterpret_cast<PosixEngineClosure*>(kClosureNotReady)) {
    grpc_core::MutexLock lock(&poller_->mu_);
    poller_->PollerHandlesListAddHandle(this);
  }
  PollPoller* Poller() override { return poller_.get(); }
  bool SetPendingActions(bool pending_read, bool pending_write) {
    pending_actions_ |= pending_read;
    if (pending_write) {
      pending_actions_ |= (1 << 2);
    }
    if (pending_read || pending_write) {

      Ref();
      return true;
    }
    return false;
  }
  void ForceRemoveHandleFromPoller() {
    grpc_core::MutexLock lock(&poller_->mu_);
    poller_->PollerHandlesListRemoveHandle(this);
  }
  int WrappedFd() override { return fd_; }
  bool IsOrphaned() const ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu_) {
    return is_orphaned_;
  }
  void CloseFd() ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu_) {
    if (!released_ && !closed_) {
      closed_ = true;
      close(fd_);
    }
  }
  bool IsPollhup() const ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu_) { return pollhup_; }
  void SetPollhup(bool pollhup) ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu_) {
    pollhup_ = pollhup;
  }
  bool IsWatched(int& watch_mask) const ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu_) {
    watch_mask = watch_mask_;
    return watch_mask_ != -1;
  }
  bool IsWatched() const ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu_) {
    return watch_mask_ != -1;
  }
  void SetWatched(int watch_mask) ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu_) {
    watch_mask_ = watch_mask;
  }
  void OrphanHandle(PosixEngineClosure* on_done, int* release_fd,
                    absl::string_view reason) override;
  void ShutdownHandle(absl::Status why) override;
  void NotifyOnRead(PosixEngineClosure* on_read) override;
  void NotifyOnWrite(PosixEngineClosure* on_write) override;
  void NotifyOnError(PosixEngineClosure* on_error) override;
  void SetReadable() override;
  void SetWritable() override;
  void SetHasError() override;
  bool IsHandleShutdown() override {
    grpc_core::MutexLock lock(&mu_);
    return is_shutdown_;
  };
  inline void ExecutePendingActions() {
    int kick = 0;
    {
      grpc_core::MutexLock lock(&mu_);
      if ((pending_actions_ & 1UL)) {
        if (SetReadyLocked(&read_closure_)) {
          kick = 1;
        }
      }
      if (((pending_actions_ >> 2) & 1UL)) {
        if (SetReadyLocked(&write_closure_)) {
          kick = 1;
        }
      }
      pending_actions_ = 0;
    }
    if (kick) {

      poller_->KickExternal(false);
    }
    Unref();
  }
  void Ref() { ref_count_.fetch_add(1, std::memory_order_relaxed); }
  void Unref() {
    if (ref_count_.fetch_sub(1, std::memory_order_acq_rel) == 1) {
      if (on_done_ != nullptr) {
        scheduler_->Run(on_done_);
      }
      delete this;
    }
  }
  ~PollEventHandle() override = default;
  grpc_core::Mutex* mu() ABSL_LOCK_RETURNED(mu_) { return &mu_; }
  PollPoller::HandlesList& ForkFdListPos() { return fork_fd_list_; }
  PollPoller::HandlesList& PollerHandlesListPos() {
    return poller_handles_list_;
  }
  uint32_t BeginPollLocked(uint32_t read_mask, uint32_t write_mask)
      ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu_);
  bool EndPollLocked(bool got_read, bool got_write)
      ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu_);

 private:
  int SetReadyLocked(PosixEngineClosure** st);
  int NotifyOnLocked(PosixEngineClosure** st, PosixEngineClosure* closure);

  grpc_core::Mutex mu_;
  std::atomic<int> ref_count_{1};
  int fd_;
  int pending_actions_;
  PollPoller::HandlesList fork_fd_list_;
  PollPoller::HandlesList poller_handles_list_;
  Scheduler* scheduler_;
  std::shared_ptr<PollPoller> poller_;
  bool is_orphaned_;
  bool is_shutdown_;
  bool closed_;
  bool released_;
  bool pollhup_;
  int watch_mask_;
  absl::Status shutdown_error_;
  AnyInvocableClosure exec_actions_closure_;
  PosixEngineClosure* on_done_;
  PosixEngineClosure* read_closure_;
  PosixEngineClosure* write_closure_;
};

namespace {

std::list<PollPoller*> fork_poller_list;

gpr_mu fork_fd_list_mu;

void ForkPollerListAddPoller(PollPoller* poller) {
  if (grpc_core::Fork::Enabled()) {
    gpr_mu_lock(&fork_fd_list_mu);
    fork_poller_list.push_back(poller);
    gpr_mu_unlock(&fork_fd_list_mu);
  }
}

void ForkPollerListRemovePoller(PollPoller* poller) {
  if (grpc_core::Fork::Enabled()) {
    gpr_mu_lock(&fork_fd_list_mu);
    fork_poller_list.remove(poller);
    gpr_mu_unlock(&fork_fd_list_mu);
  }
}

int PollElapsedTimeToMillis(grpc_core::Timestamp start) {
  if (start == grpc_core::Timestamp::InfFuture()) return -1;
  grpc_core::Timestamp now =
      grpc_core::Timestamp::FromTimespecRoundDown(gpr_now(GPR_CLOCK_MONOTONIC));
  int64_t delta = (now - start).millis();
  if (delta > INT_MAX) {
    return INT_MAX;
  } else if (delta < 0) {
    return 0;
  } else {
    return static_cast<int>(delta);
  }
}

bool InitPollPollerPosix();

void ResetEventManagerOnFork() {
  gpr_mu_lock(&fork_fd_list_mu);

  while (!fork_poller_list.empty()) {
    PollPoller* poller = fork_poller_list.front();
    fork_poller_list.pop_front();
    poller->Close();
  }
  gpr_mu_unlock(&fork_fd_list_mu);
  InitPollPollerPosix();
}

bool InitPollPollerPosix() {
  if (!grpc_event_engine::experimental::SupportsWakeupFd()) {
    return false;
  }
  if (grpc_core::Fork::Enabled()) {
    if (grpc_core::Fork::RegisterResetChildPollingEngineFunc(
            ResetEventManagerOnFork)) {
      gpr_mu_init(&fork_fd_list_mu);
    }
  }
  return true;
}

}

EventHandle* PollPoller::CreateHandle(int fd, absl::string_view ,
                                      bool track_err) {

  (void)track_err;
  DCHECK(track_err == false);
  PollEventHandle* handle = new PollEventHandle(fd, shared_from_this());

  KickExternal(false);
  return handle;
}

void PollEventHandle::OrphanHandle(PosixEngineClosure* on_done, int* release_fd,
                                   absl::string_view ) {
  ForceRemoveHandleFromPoller();
  {
    grpc_core::ReleasableMutexLock lock(&mu_);
    on_done_ = on_done;
    released_ = release_fd != nullptr;
    if (release_fd != nullptr) {
      *release_fd = fd_;
    }
    CHECK(!is_orphaned_);
    is_orphaned_ = true;

    if (!is_shutdown_) {
      is_shutdown_ = true;
      shutdown_error_ =
          absl::Status(absl::StatusCode::kInternal, "FD Orphaned");
      grpc_core::StatusSetInt(&shutdown_error_,
                              grpc_core::StatusIntProperty::kRpcStatus,
                              GRPC_STATUS_UNAVAILABLE);
      SetReadyLocked(&read_closure_);
      SetReadyLocked(&write_closure_);
    }

    if (!released_) {
      shutdown(fd_, SHUT_RDWR);
    }
    if (!IsWatched()) {
      CloseFd();
    } else {

      SetWatched(-1);
      lock.Release();
      poller_->KickExternal(false);
    }
  }
  Unref();
}

int PollEventHandle::NotifyOnLocked(PosixEngineClosure** st,
                                    PosixEngineClosure* closure) {
  if (is_shutdown_ || pollhup_) {
    closure->SetStatus(shutdown_error_);
    scheduler_->Run(closure);
  } else if (*st == reinterpret_cast<PosixEngineClosure*>(kClosureNotReady)) {

    *st = closure;
    return 0;
  } else if (*st == reinterpret_cast<PosixEngineClosure*>(kClosureReady)) {

    *st = reinterpret_cast<PosixEngineClosure*>(kClosureNotReady);
    closure->SetStatus(shutdown_error_);
    scheduler_->Run(closure);
    return 1;
  } else {

    grpc_core::Crash(
        "User called a notify_on function with a previous callback still "
        "pending");
  }
  return 0;
}

int PollEventHandle::SetReadyLocked(PosixEngineClosure** st) {
  if (*st == reinterpret_cast<PosixEngineClosure*>(kClosureReady)) {

    return 0;
  } else if (*st == reinterpret_cast<PosixEngineClosure*>(kClosureNotReady)) {

    *st = reinterpret_cast<PosixEngineClosure*>(kClosureReady);
    return 0;
  } else {

    PosixEngineClosure* closure = *st;
    *st = reinterpret_cast<PosixEngineClosure*>(kClosureNotReady);
    closure->SetStatus(shutdown_error_);
    scheduler_->Run(closure);
    return 1;
  }
}

void PollEventHandle::ShutdownHandle(absl::Status why) {

  Ref();
  {
    grpc_core::MutexLock lock(&mu_);

    if (!is_shutdown_) {
      is_shutdown_ = true;
      shutdown_error_ = why;
      grpc_core::StatusSetInt(&shutdown_error_,
                              grpc_core::StatusIntProperty::kRpcStatus,
                              GRPC_STATUS_UNAVAILABLE);
      SetReadyLocked(&read_closure_);
      SetReadyLocked(&write_closure_);
    }
  }

  Unref();
}

void PollEventHandle::NotifyOnRead(PosixEngineClosure* on_read) {

  Ref();
  {
    grpc_core::ReleasableMutexLock lock(&mu_);
    if (NotifyOnLocked(&read_closure_, on_read)) {
      lock.Release();

      poller_->KickExternal(false);
    }
  }

  Unref();
}

void PollEventHandle::NotifyOnWrite(PosixEngineClosure* on_write) {

  Ref();
  {
    grpc_core::ReleasableMutexLock lock(&mu_);
    if (NotifyOnLocked(&write_closure_, on_write)) {
      lock.Release();

      poller_->KickExternal(false);
    }
  }

  Unref();
}

void PollEventHandle::NotifyOnError(PosixEngineClosure* on_error) {
  on_error->SetStatus(
      absl::Status(absl::StatusCode::kCancelled,
                   "Polling engine does not support tracking errors"));
  scheduler_->Run(on_error);
}

void PollEventHandle::SetReadable() {
  Ref();
  {
    grpc_core::MutexLock lock(&mu_);
    SetReadyLocked(&read_closure_);
  }
  Unref();
}

void PollEventHandle::SetWritable() {
  Ref();
  {
    grpc_core::MutexLock lock(&mu_);
    SetReadyLocked(&write_closure_);
  }
  Unref();
}

void PollEventHandle::SetHasError() {}

uint32_t PollEventHandle::BeginPollLocked(uint32_t read_mask,
                                          uint32_t write_mask) {
  uint32_t mask = 0;
  bool read_ready = (pending_actions_ & 1UL);
  bool write_ready = ((pending_actions_ >> 2) & 1UL);
  Ref();

  if (is_shutdown_) {
    SetWatched(0);
    return 0;
  }

  if (read_mask && !read_ready &&
      read_closure_ != reinterpret_cast<PosixEngineClosure*>(kClosureReady)) {
    mask |= read_mask;
  }

  if (write_mask && !write_ready &&
      write_closure_ != reinterpret_cast<PosixEngineClosure*>(kClosureReady)) {
    mask |= write_mask;
  }
  SetWatched(mask);
  return mask;
}

bool PollEventHandle::EndPollLocked(bool got_read, bool got_write) {
  if (is_orphaned_ && !IsWatched()) {
    CloseFd();
  } else if (!is_orphaned_) {
    return SetPendingActions(got_read, got_write);
  }
  return false;
}

void PollPoller::KickExternal(bool ext) {
  grpc_core::MutexLock lock(&mu_);
  if (closed_) {
    return;
  }
  if (was_kicked_) {
    if (ext) {
      was_kicked_ext_ = true;
    }
    return;
  }
  was_kicked_ = true;
  was_kicked_ext_ = ext;
  CHECK(wakeup_fd_->Wakeup().ok());
}

void PollPoller::Kick() { KickExternal(true); }

void PollPoller::PollerHandlesListAddHandle(PollEventHandle* handle) {
  handle->PollerHandlesListPos().next = poll_handles_list_head_;
  handle->PollerHandlesListPos().prev = nullptr;
  if (poll_handles_list_head_ != nullptr) {
    poll_handles_list_head_->PollerHandlesListPos().prev = handle;
  }
  poll_handles_list_head_ = handle;
  ++num_poll_handles_;
}

void PollPoller::PollerHandlesListRemoveHandle(PollEventHandle* handle) {
  if (poll_handles_list_head_ == handle) {
    poll_handles_list_head_ = handle->PollerHandlesListPos().next;
  }
  if (handle->PollerHandlesListPos().prev != nullptr) {
    handle->PollerHandlesListPos().prev->PollerHandlesListPos().next =
        handle->PollerHandlesListPos().next;
  }
  if (handle->PollerHandlesListPos().next != nullptr) {
    handle->PollerHandlesListPos().next->PollerHandlesListPos().prev =
        handle->PollerHandlesListPos().prev;
  }
  --num_poll_handles_;
}

PollPoller::PollPoller(Scheduler* scheduler)
    : scheduler_(scheduler),
      use_phony_poll_(false),
      was_kicked_(false),
      was_kicked_ext_(false),
      num_poll_handles_(0),
      poll_handles_list_head_(nullptr),
      closed_(false) {
  wakeup_fd_ = *CreateWakeupFd();
  CHECK(wakeup_fd_ != nullptr);
  ForkPollerListAddPoller(this);
}

PollPoller::PollPoller(Scheduler* scheduler, bool use_phony_poll)
    : scheduler_(scheduler),
      use_phony_poll_(use_phony_poll),
      was_kicked_(false),
      was_kicked_ext_(false),
      num_poll_handles_(0),
      poll_handles_list_head_(nullptr),
      closed_(false) {
  wakeup_fd_ = *CreateWakeupFd();
  CHECK(wakeup_fd_ != nullptr);
  ForkPollerListAddPoller(this);
}

PollPoller::~PollPoller() {

  CHECK_EQ(num_poll_handles_, 0);
  CHECK_EQ(poll_handles_list_head_, nullptr);
}

Poller::WorkResult PollPoller::Work(
    EventEngine::Duration timeout,
    absl::FunctionRef<void()> schedule_poll_again) {

  enum { inline_elements = 96 };
  struct pollfd pollfd_space[inline_elements];
  bool was_kicked_ext = false;
  PollEventHandle* watcher_space[inline_elements];
  Events pending_events;
  pending_events.clear();
  int timeout_ms =
      static_cast<int>(grpc_event_engine::experimental::Milliseconds(timeout));
  mu_.Lock();

  while (pending_events.empty() && timeout_ms >= 0) {
    int r = 0;
    size_t i;
    nfds_t pfd_count;
    struct pollfd* pfds;
    PollEventHandle** watchers;

    grpc_core::Timestamp start = grpc_core::Timestamp::FromTimespecRoundDown(
        gpr_now(GPR_CLOCK_MONOTONIC));
    if (num_poll_handles_ + 2 <= inline_elements) {
      pfds = pollfd_space;
      watchers = watcher_space;
    } else {
      const size_t pfd_size = sizeof(*pfds) * (num_poll_handles_ + 2);
      const size_t watch_size = sizeof(*watchers) * (num_poll_handles_ + 2);
      void* buf = gpr_malloc(pfd_size + watch_size);
      pfds = static_cast<struct pollfd*>(buf);
      watchers = static_cast<PollEventHandle**>(
          static_cast<void*>((static_cast<char*>(buf) + pfd_size)));
      pfds = static_cast<struct pollfd*>(buf);
    }

    pfd_count = 1;
    pfds[0].fd = wakeup_fd_->ReadFd();
    pfds[0].events = POLLIN;
    pfds[0].revents = 0;
    PollEventHandle* head = poll_handles_list_head_;
    while (head != nullptr) {
      {
        grpc_core::MutexLock lock(head->mu());

        CHECK(!head->IsOrphaned());
        if (!head->IsPollhup()) {
          pfds[pfd_count].fd = head->WrappedFd();
          watchers[pfd_count] = head;

          pfds[pfd_count].events = head->BeginPollLocked(POLLIN, POLLOUT);
          pfd_count++;
        }
      }
      head = head->PollerHandlesListPos().next;
    }
    mu_.Unlock();

    if (!use_phony_poll_ || timeout_ms == 0 || pfd_count == 1) {

      r = poll(pfds, pfd_count, timeout_ms);
    } else {
      grpc_core::Crash("Attempted a blocking poll when declared non-polling.");
    }

    if (r <= 0) {
      if (r < 0 && errno != EINTR) {

        grpc_core::Crash(absl::StrFormat(
            "(event_engine) PollPoller:%p encountered poll error: %s", this,
            grpc_core::StrError(errno).c_str()));
      }

      for (i = 1; i < pfd_count; i++) {
        PollEventHandle* head = watchers[i];
        int watch_mask;
        grpc_core::ReleasableMutexLock lock(head->mu());
        if (head->IsWatched(watch_mask)) {
          head->SetWatched(-1);

          if (watch_mask > 0 && r < 0) {

            if (head->EndPollLocked(true, true)) {

              pending_events.push_back(head);
            }
          } else {

            head->EndPollLocked(false, false);
          }
        } else {

          head->EndPollLocked(false, false);
        }
        lock.Release();

        head->Unref();
      }
    } else {
      if (pfds[0].revents & kPollinCheck) {
        CHECK(wakeup_fd_->ConsumeWakeup().ok());
      }
      for (i = 1; i < pfd_count; i++) {
        PollEventHandle* head = watchers[i];
        int watch_mask;
        grpc_core::ReleasableMutexLock lock(head->mu());
        if (!head->IsWatched(watch_mask) || watch_mask == 0) {

          head->SetWatched(-1);
          head->EndPollLocked(false, false);
        } else {

          if (pfds[i].revents & POLLHUP) {
            head->SetPollhup(true);
          }
          head->SetWatched(-1);
          if (head->EndPollLocked(pfds[i].revents & kPollinCheck,
                                  pfds[i].revents & kPolloutCheck)) {

            pending_events.push_back(head);
          }
        }
        lock.Release();

        head->Unref();
      }
    }

    if (pfds != pollfd_space) {
      gpr_free(pfds);
    }

    timeout_ms -= PollElapsedTimeToMillis(start);
    mu_.Lock();
    if (std::exchange(was_kicked_, false) &&
        std::exchange(was_kicked_ext_, false)) {

      was_kicked_ext = true;
      break;
    }
  }
  mu_.Unlock();
  if (pending_events.empty()) {
    if (was_kicked_ext) {
      return Poller::WorkResult::kKicked;
    }
    return Poller::WorkResult::kDeadlineExceeded;
  }

  schedule_poll_again();

  for (auto& it : pending_events) {
    it->ExecutePendingActions();
  }
  return was_kicked_ext ? Poller::WorkResult::kKicked : Poller::WorkResult::kOk;
}

void PollPoller::Shutdown() { ForkPollerListRemovePoller(this); }

void PollPoller::PrepareFork() { Kick(); }

void PollPoller::PostforkParent() {}

void PollPoller::PostforkChild() {}

void PollPoller::Close() {
  grpc_core::MutexLock lock(&mu_);
  closed_ = true;
}

std::shared_ptr<PollPoller> MakePollPoller(Scheduler* scheduler,
                                           bool use_phony_poll) {
  static bool kPollPollerSupported = InitPollPollerPosix();
  if (kPollPollerSupported) {
    return std::make_shared<PollPoller>(scheduler, use_phony_poll);
  }
  return nullptr;
}

}

#else

#include "src/core/util/crash.h"

namespace grpc_event_engine::experimental {

PollPoller::PollPoller(Scheduler* ) {
  grpc_core::Crash("unimplemented");
}

void PollPoller::Shutdown() { grpc_core::Crash("unimplemented"); }

PollPoller::~PollPoller() { grpc_core::Crash("unimplemented"); }

EventHandle* PollPoller::CreateHandle(int , absl::string_view ,
                                      bool ) {
  grpc_core::Crash("unimplemented");
}

Poller::WorkResult PollPoller::Work(
    EventEngine::Duration ,
    absl::FunctionRef<void()> ) {
  grpc_core::Crash("unimplemented");
}

void PollPoller::Kick() { grpc_core::Crash("unimplemented"); }

std::shared_ptr<PollPoller> MakePollPoller(Scheduler* ,
                                           bool ) {
  return nullptr;
}

void PollPoller::PrepareFork() { grpc_core::Crash("unimplemented"); }
void PollPoller::PostforkParent() { grpc_core::Crash("unimplemented"); }
void PollPoller::PostforkChild() { grpc_core::Crash("unimplemented"); }

void PollPoller::Close() { grpc_core::Crash("unimplemented"); }

void PollPoller::KickExternal(bool ) {
  grpc_core::Crash("unimplemented");
}

void PollPoller::PollerHandlesListAddHandle(PollEventHandle* ) {
  grpc_core::Crash("unimplemented");
}

void PollPoller::PollerHandlesListRemoveHandle(PollEventHandle* ) {
  grpc_core::Crash("unimplemented");
}

}

#endif
