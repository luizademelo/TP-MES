// Copyright 2024 gRPC authors.

#ifndef GRPC_SRC_CORE_UTIL_LATENT_SEE_H
#define GRPC_SRC_CORE_UTIL_LATENT_SEE_H

#include <grpc/support/port_platform.h>

#ifdef GRPC_ENABLE_LATENT_SEE
#include <sys/syscall.h>
#include <unistd.h>

#include <atomic>
#include <chrono>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <optional>
#include <string>
#include <utility>
#include <vector>

#include "absl/base/thread_annotations.h"
#include "absl/functional/any_invocable.h"
#include "absl/functional/function_ref.h"
#include "absl/log/log.h"
#include "absl/strings/string_view.h"
#include "src/core/util/per_cpu.h"
#include "src/core/util/sync.h"

#define TAGGED_POINTER_SIZE_BITS 48

namespace grpc_core {
namespace latent_see {

struct Metadata {
  const char* file;
  int line;
  const char* name;
};

enum class EventType : uint8_t { kBegin, kEnd, kFlowStart, kFlowEnd, kMark };

struct Bin {
  struct Event {
    const Metadata* metadata;
    std::chrono::steady_clock::time_point timestamp;
    uint64_t id;
    EventType type;
  };

  void Append(const Metadata* metadata, EventType type, uint64_t id) {
    events.push_back(
        Event{metadata, std::chrono::steady_clock::now(), id, type});
  }

  std::vector<Event> events;
  uintptr_t next_free = 0;
};

class Log {
 public:
  static constexpr uintptr_t kTagMask = (1ULL << TAGGED_POINTER_SIZE_BITS) - 1;

  struct RecordedEvent {
    uint64_t thread_id;
    uint64_t batch_id;
    Bin::Event event;
  };

  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION static uintptr_t IncrementTag(
      uintptr_t input) {
    return input + (1UL << TAGGED_POINTER_SIZE_BITS);
  }

  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION static Bin* ToBin(uintptr_t ptr) {
    return reinterpret_cast<Bin*>(ptr & kTagMask);
  }

  static uintptr_t StartBin(void* owner) {
    uintptr_t bin_descriptor = free_bins_.load(std::memory_order_acquire);
    Bin* bin;
    do {
      if (bin_descriptor == 0) {
        bin = new Bin();
        break;
      }
      bin = ToBin(bin_descriptor);
    } while (!free_bins_.compare_exchange_strong(bin_descriptor, bin->next_free,
                                                 std::memory_order_acq_rel));
    bin_ = bin;
    bin_owner_ = owner;
    return reinterpret_cast<uintptr_t>(bin);
  }

  static void EndBin(uintptr_t bin_descriptor, void* owner) {
    if (bin_owner_ != owner || bin_descriptor == 0) return;
    FlushBin(ToBin(bin_descriptor));
    uintptr_t next_free = free_bins_.load(std::memory_order_acquire);
    while (!free_bins_.compare_exchange_strong(
        next_free, IncrementTag(bin_descriptor), std::memory_order_acq_rel)) {
    }
    bin_ = nullptr;
    bin_owner_ = nullptr;
  }

  static Bin* CurrentThreadBin() { return bin_; }

  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION static Log& Get() {
    static Log* log = new Log();
    return *log;
  }

  void TryPullEventsAndFlush(
      absl::FunctionRef<void(absl::Span<const RecordedEvent>)> callback);
  std::optional<std::string> TryGenerateJson();

  void OverrideStatsFlusher(
      absl::AnyInvocable<void(absl::string_view)> stats_exporter) {
    stats_flusher_ = std::move(stats_exporter);
  }

  static void InstallAtExitHandler();

 private:
  Log() = default;

  static void FlushBin(Bin* bin);

  std::atomic<uint64_t> next_thread_id_{1};
  std::atomic<uint64_t> next_batch_id_{1};
  static thread_local uint64_t thread_id_;
  static thread_local Bin* bin_;
  static thread_local void* bin_owner_;
  static std::atomic<uintptr_t> free_bins_;
  absl::AnyInvocable<void(absl::string_view)> stats_flusher_ = nullptr;
  Mutex mu_flushing_;
  struct Fragment {
    Mutex mu_active ABSL_ACQUIRED_AFTER(mu_flushing_);
    std::vector<RecordedEvent> active ABSL_GUARDED_BY(mu_active);
    std::vector<RecordedEvent> flushing ABSL_GUARDED_BY(&Log::mu_flushing_);
  };
  PerCpu<Fragment> fragments_{PerCpuOptions()};
};

template <bool kParent>
class Scope {
 public:
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION explicit Scope(const Metadata* metadata)
      : metadata_(metadata) {
    bin_ = Log::CurrentThreadBin();
    if (kParent && bin_ == nullptr) {
      bin_descriptor_ = Log::StartBin(this);
      bin_ = Log::ToBin(bin_descriptor_);
    }
    CHECK_NE(bin_, nullptr);
    bin_->Append(metadata_, EventType::kBegin, 0);
  }
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION ~Scope() {
    bin_->Append(metadata_, EventType::kEnd, 0);
    if (kParent) Log::EndBin(bin_descriptor_, this);
  }

  Scope(const Scope&) = delete;
  Scope& operator=(const Scope&) = delete;

 private:
  const Metadata* const metadata_;
  uintptr_t bin_descriptor_ = 0;
  Bin* bin_ = nullptr;
};

using ParentScope = Scope<true>;
using InnerScope = Scope<false>;

class Flow {
 public:
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION Flow() : metadata_(nullptr) {}
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION explicit Flow(const Metadata* metadata)
      : metadata_(metadata),
        id_(next_flow_id_.fetch_add(1, std::memory_order_relaxed)) {
    Log::CurrentThreadBin()->Append(metadata_, EventType::kFlowStart, id_);
  }
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION ~Flow() {
    if (metadata_ != nullptr) {
      Log::CurrentThreadBin()->Append(metadata_, EventType::kFlowEnd, id_);
    }
  }

  Flow(const Flow&) = delete;
  Flow& operator=(const Flow&) = delete;
  Flow(Flow&& other) noexcept
      : metadata_(std::exchange(other.metadata_, nullptr)), id_(other.id_) {}
  Flow& operator=(Flow&& other) noexcept {
    if (metadata_ != nullptr) {
      Log::CurrentThreadBin()->Append(metadata_, EventType::kFlowEnd, id_);
    }
    metadata_ = std::exchange(other.metadata_, nullptr);
    id_ = other.id_;
    return *this;
  }

  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION bool is_active() const {
    return metadata_ != nullptr;
  }
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION void End() {
    if (metadata_ == nullptr) return;
    Log::CurrentThreadBin()->Append(metadata_, EventType::kFlowEnd, id_);
    metadata_ = nullptr;
  }
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION void Begin(const Metadata* metadata) {
    auto* bin = Log::CurrentThreadBin();
    if (metadata_ != nullptr) {
      bin->Append(metadata_, EventType::kFlowEnd, id_);
    }
    metadata_ = metadata;
    if (metadata_ == nullptr) return;
    id_ = next_flow_id_.fetch_add(1, std::memory_order_relaxed);
    bin->Append(metadata_, EventType::kFlowStart, id_);
  }

 private:
  const Metadata* metadata_;
  uint64_t id_;
  static std::atomic<uint64_t> next_flow_id_;
};

GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION inline void Mark(const Metadata* md) {
  Log::CurrentThreadBin()->Append(md, EventType::kMark, 0);
}

template <typename P>
GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION auto Promise(const Metadata* md_poll,
                                                  const Metadata* md_flow,
                                                  P promise) {
  return [md_poll, md_flow, promise = std::move(promise),
          flow = Flow(md_flow)]() mutable {
    InnerScope scope(md_poll);
    flow.End();
    auto r = promise();
    flow.Begin(md_flow);
    return r;
  };
}

}
}
#define GRPC_LATENT_SEE_METADATA(name)                                     \
  []() {                                                                   \
    static grpc_core::latent_see::Metadata metadata = {__FILE__, __LINE__, \
                                                       name};              \
    return &metadata;                                                      \
  }()

#define GRPC_LATENT_SEE_PARENT_SCOPE(name)                       \
  grpc_core::latent_see::ParentScope latent_see_scope##__LINE__( \
      GRPC_LATENT_SEE_METADATA(name))

#define GRPC_LATENT_SEE_INNER_SCOPE(name)                       \
  grpc_core::latent_see::InnerScope latent_see_scope##__LINE__( \
      GRPC_LATENT_SEE_METADATA(name))

#define GRPC_LATENT_SEE_MARK(name) \
  grpc_core::latent_see::Mark(GRPC_LATENT_SEE_METADATA(name))
#define GRPC_LATENT_SEE_PROMISE(name, promise)                                 \
  grpc_core::latent_see::Promise(GRPC_LATENT_SEE_METADATA("Poll:" name),       \
                                 GRPC_LATENT_SEE_METADATA(name), [&]() {       \
                                   GRPC_LATENT_SEE_INNER_SCOPE("Setup:" name); \
                                   return promise;                             \
                                 }())
#else
namespace grpc_core {
namespace latent_see {
struct Metadata {};
struct Flow {
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION bool is_active() const { return false; }
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION void End() {}
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION void Begin(Metadata*) {}
};
struct ParentScope {
  explicit ParentScope(Metadata*) {}
};
struct InnerScope {
  explicit InnerScope(Metadata*) {}
};
}
}
#define GRPC_LATENT_SEE_METADATA(name) nullptr
#define GRPC_LATENT_SEE_METADATA_RAW(name) nullptr
#define GRPC_LATENT_SEE_PARENT_SCOPE(name) \
  do {                                     \
  } while (0)
#define GRPC_LATENT_SEE_INNER_SCOPE(name) \
  do {                                    \
  } while (0)
#define GRPC_LATENT_SEE_MARK(name) \
  do {                             \
  } while (0)
#define GRPC_LATENT_SEE_PROMISE(name, promise) promise
#endif

#endif
