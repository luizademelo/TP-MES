
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_UTIL_THD_H
#define GRPC_SRC_CORE_UTIL_THD_H

#include <grpc/support/port_platform.h>
#include <grpc/support/thd_id.h>
#include <stddef.h>

#include <memory>
#include <utility>

#include "absl/functional/any_invocable.h"
#include "absl/log/check.h"

namespace grpc_core {
namespace internal {

class ThreadInternalsInterface {
 public:
  virtual ~ThreadInternalsInterface() {}
  virtual void Start() = 0;
  virtual void Join() = 0;
};

}

class Thread {
 public:

  static void Signal(gpr_thd_id tid, int sig);

  static void Kill(gpr_thd_id tid);

  class Options {
   public:
    Options() : joinable_(true), tracked_(true), stack_size_(0) {}

    Options& set_joinable(bool joinable) {
      joinable_ = joinable;
      return *this;
    }
    bool joinable() const { return joinable_; }

    Options& set_tracked(bool tracked) {
      tracked_ = tracked;
      return *this;
    }
    bool tracked() const { return tracked_; }

    Options& set_stack_size(size_t bytes) {
      stack_size_ = bytes;
      return *this;
    }
    size_t stack_size() const { return stack_size_; }

   private:
    bool joinable_;
    bool tracked_;
    size_t stack_size_;
  };

  Thread() : state_(FAKE), impl_(nullptr) {}

  Thread(const char* thd_name, void (*thd_body)(void* arg), void* arg,
         bool* success = nullptr, const Options& options = Options());

  Thread(const char* thd_name, absl::AnyInvocable<void()> fn,
         bool* success = nullptr, const Options& options = Options())
      : Thread(
            thd_name,
            [](void* p) {
              std::unique_ptr<absl::AnyInvocable<void()>> fn_from_p(
                  static_cast<absl::AnyInvocable<void()>*>(p));
              (*fn_from_p)();
            },
            new absl::AnyInvocable<void()>(std::move(fn)), success, options) {}

  Thread(Thread&& other) noexcept
      : state_(other.state_), impl_(other.impl_), options_(other.options_) {
    other.state_ = MOVED;
    other.impl_ = nullptr;
    other.options_ = Options();
  }

  Thread& operator=(Thread&& other) noexcept {
    if (this != &other) {

      state_ = other.state_;
      impl_ = other.impl_;
      options_ = other.options_;
      other.state_ = MOVED;
      other.impl_ = nullptr;
      other.options_ = Options();
    }
    return *this;
  }

  ~Thread() { CHECK(!options_.joinable() || impl_ == nullptr); }

  void Start() {
    if (impl_ != nullptr) {
      CHECK(state_ == ALIVE);
      state_ = STARTED;
      impl_->Start();

    } else {
      CHECK(state_ == FAILED);
    }
  }

  void Join() {
    if (impl_ != nullptr) {
      impl_->Join();
      delete impl_;
      state_ = DONE;
      impl_ = nullptr;
    } else {
      CHECK(state_ == FAILED);
    }
  }

 private:
  Thread(const Thread&) = delete;
  Thread& operator=(const Thread&) = delete;

  enum ThreadState { FAKE, ALIVE, STARTED, DONE, FAILED, MOVED };
  ThreadState state_;
  internal::ThreadInternalsInterface* impl_;
  Options options_;
};

}

#endif
