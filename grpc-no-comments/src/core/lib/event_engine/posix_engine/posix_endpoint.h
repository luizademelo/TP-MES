// Copyright 2022 gRPC Authors

#ifndef GRPC_SRC_CORE_LIB_EVENT_ENGINE_POSIX_ENGINE_POSIX_ENDPOINT_H
#define GRPC_SRC_CORE_LIB_EVENT_ENGINE_POSIX_ENGINE_POSIX_ENDPOINT_H

#include <grpc/support/port_platform.h>

#include <grpc/event_engine/event_engine.h>
#include <grpc/event_engine/memory_allocator.h>
#include <grpc/event_engine/slice_buffer.h>
#include <grpc/support/alloc.h>

#include <atomic>
#include <cstdint>
#include <memory>
#include <new>
#include <optional>
#include <utility>

#include "absl/base/thread_annotations.h"
#include "absl/container/flat_hash_map.h"
#include "absl/functional/any_invocable.h"
#include "absl/hash/hash.h"
#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "src/core/lib/event_engine/extensions/supports_fd.h"
#include "src/core/lib/event_engine/posix.h"
#include "src/core/lib/event_engine/posix_engine/event_poller.h"
#include "src/core/lib/event_engine/posix_engine/posix_engine_closure.h"
#include "src/core/lib/event_engine/posix_engine/tcp_socket_utils.h"
#include "src/core/lib/event_engine/posix_engine/traced_buffer_list.h"
#include "src/core/lib/iomgr/port.h"
#include "src/core/lib/resource_quota/memory_quota.h"
#include "src/core/util/crash.h"
#include "src/core/util/ref_counted.h"
#include "src/core/util/sync.h"

#ifdef GRPC_POSIX_SOCKET_TCP

#include <sys/socket.h>
#include <sys/types.h>

#ifdef GRPC_MSG_IOVLEN_TYPE
typedef GRPC_MSG_IOVLEN_TYPE msg_iovlen_type;
#else
typedef size_t msg_iovlen_type;
#endif

#endif

namespace grpc_event_engine::experimental {

#ifdef GRPC_POSIX_SOCKET_TCP

class TcpZerocopySendRecord {
 public:
  TcpZerocopySendRecord() { buf_.Clear(); };

  ~TcpZerocopySendRecord() { DebugAssertEmpty(); }

  msg_iovlen_type PopulateIovs(size_t* unwind_slice_idx,
                               size_t* unwind_byte_idx, size_t* sending_length,
                               iovec* iov);

  void UnwindIfThrottled(size_t unwind_slice_idx, size_t unwind_byte_idx) {
    out_offset_.byte_idx = unwind_byte_idx;
    out_offset_.slice_idx = unwind_slice_idx;
  }

  void UpdateOffsetForBytesSent(size_t sending_length, size_t actually_sent);

  bool AllSlicesSent() { return out_offset_.slice_idx == buf_.Count(); }

  void PrepareForSends(
      grpc_event_engine::experimental::SliceBuffer& slices_to_send) {
    DebugAssertEmpty();
    out_offset_.slice_idx = 0;
    out_offset_.byte_idx = 0;
    buf_.Swap(slices_to_send);
    Ref();
  }

  void Ref() { ref_.fetch_add(1, std::memory_order_relaxed); }

  bool Unref() {
    const intptr_t prior = ref_.fetch_sub(1, std::memory_order_acq_rel);
    DCHECK_GT(prior, 0);
    if (prior == 1) {
      AllSendsComplete();
      return true;
    }
    return false;
  }

 private:
  struct OutgoingOffset {
    size_t slice_idx = 0;
    size_t byte_idx = 0;
  };

  void DebugAssertEmpty() {
    DCHECK_EQ(buf_.Count(), 0u);
    DCHECK_EQ(buf_.Length(), 0u);
    DCHECK_EQ(ref_.load(std::memory_order_relaxed), 0);
  }

  void AllSendsComplete() {
    DCHECK_EQ(ref_.load(std::memory_order_relaxed), 0);
    buf_.Clear();
  }

  grpc_event_engine::experimental::SliceBuffer buf_;
  std::atomic<intptr_t> ref_{0};
  OutgoingOffset out_offset_;
};

class TcpZerocopySendCtx {
 public:
  static constexpr int kDefaultMaxSends = 4;
  static constexpr size_t kDefaultSendBytesThreshold = 16 * 1024;

  explicit TcpZerocopySendCtx(
      bool zerocopy_enabled, int max_sends = kDefaultMaxSends,
      size_t send_bytes_threshold = kDefaultSendBytesThreshold)
      : max_sends_(max_sends),
        free_send_records_size_(max_sends),
        threshold_bytes_(send_bytes_threshold) {
    send_records_ = static_cast<TcpZerocopySendRecord*>(
        gpr_malloc(max_sends * sizeof(*send_records_)));
    free_send_records_ = static_cast<TcpZerocopySendRecord**>(
        gpr_malloc(max_sends * sizeof(*free_send_records_)));
    if (send_records_ == nullptr || free_send_records_ == nullptr) {
      gpr_free(send_records_);
      gpr_free(free_send_records_);
      VLOG(2) << "Disabling TCP TX zerocopy due to memory pressure.\n";
      memory_limited_ = true;
      enabled_ = false;
    } else {
      for (int idx = 0; idx < max_sends_; ++idx) {
        new (send_records_ + idx) TcpZerocopySendRecord();
        free_send_records_[idx] = send_records_ + idx;
      }
      enabled_ = zerocopy_enabled;
    }
  }

  ~TcpZerocopySendCtx() {
    if (send_records_ != nullptr) {
      for (int idx = 0; idx < max_sends_; ++idx) {
        send_records_[idx].~TcpZerocopySendRecord();
      }
    }
    gpr_free(send_records_);
    gpr_free(free_send_records_);
  }

  bool MemoryLimited() const { return memory_limited_; }

  void NoteSend(TcpZerocopySendRecord* record) {
    record->Ref();
    {
      grpc_core::MutexLock lock(&mu_);
      is_in_write_ = true;
      AssociateSeqWithSendRecordLocked(last_send_, record);
    }
    ++last_send_;
  }

  void UndoSend() {
    --last_send_;
    if (ReleaseSendRecord(last_send_)->Unref()) {

      DCHECK(0);
    }
  }

  void AssociateSeqWithSendRecordLocked(uint32_t seq,
                                        TcpZerocopySendRecord* record)
      ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu_) {
    ctx_lookup_.emplace(seq, record);
  }

  TcpZerocopySendRecord* GetSendRecord() {
    grpc_core::MutexLock lock(&mu_);
    return TryGetSendRecordLocked();
  }

  TcpZerocopySendRecord* ReleaseSendRecord(uint32_t seq) {
    grpc_core::MutexLock lock(&mu_);
    return ReleaseSendRecordLocked(seq);
  }

  void PutSendRecord(TcpZerocopySendRecord* record) {
    grpc_core::MutexLock lock(&mu_);
    DCHECK(record >= send_records_ && record < send_records_ + max_sends_);
    PutSendRecordLocked(record);
  }

  void Shutdown() { shutdown_.store(true, std::memory_order_release); }

  bool AllSendRecordsEmpty() {
    grpc_core::MutexLock lock(&mu_);
    return free_send_records_size_ == max_sends_;
  }

  bool Enabled() const { return enabled_; }

  size_t ThresholdBytes() const { return threshold_bytes_; }

  bool UpdateZeroCopyOptMemStateAfterFree() {
    grpc_core::MutexLock lock(&mu_);
    if (is_in_write_) {
      zcopy_enobuf_state_ = OptMemState::kCheck;
      return false;
    }
    DCHECK(zcopy_enobuf_state_ != OptMemState::kCheck);
    if (zcopy_enobuf_state_ == OptMemState::kFull) {

      zcopy_enobuf_state_ = OptMemState::kOpen;
      return true;
    } else if (zcopy_enobuf_state_ == OptMemState::kOpen) {

      return false;
    } else {

      grpc_core::Crash("OMem state error!");
    }
  }

  bool UpdateZeroCopyOptMemStateAfterSend(bool seen_enobuf, bool& constrained) {
    grpc_core::MutexLock lock(&mu_);
    is_in_write_ = false;
    constrained = false;
    if (seen_enobuf) {
      if (ctx_lookup_.size() == 1) {

        constrained = true;
      }
      if (zcopy_enobuf_state_ == OptMemState::kCheck) {
        zcopy_enobuf_state_ = OptMemState::kOpen;
        return true;
      } else {
        zcopy_enobuf_state_ = OptMemState::kFull;
      }
    } else if (zcopy_enobuf_state_ != OptMemState::kOpen) {
      zcopy_enobuf_state_ = OptMemState::kOpen;
    }
    return false;
  }

 private:

  enum class OptMemState : int8_t {
    kOpen,
    kFull,
    kCheck,

  };

  TcpZerocopySendRecord* ReleaseSendRecordLocked(uint32_t seq)
      ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu_) {
    auto iter = ctx_lookup_.find(seq);
    DCHECK(iter != ctx_lookup_.end());
    TcpZerocopySendRecord* record = iter->second;
    ctx_lookup_.erase(iter);
    return record;
  }

  TcpZerocopySendRecord* TryGetSendRecordLocked()
      ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu_) {
    if (shutdown_.load(std::memory_order_acquire)) {
      return nullptr;
    }
    if (free_send_records_size_ == 0) {
      return nullptr;
    }
    free_send_records_size_--;
    return free_send_records_[free_send_records_size_];
  }

  void PutSendRecordLocked(TcpZerocopySendRecord* record)
      ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu_) {
    DCHECK(free_send_records_size_ < max_sends_);
    free_send_records_[free_send_records_size_] = record;
    free_send_records_size_++;
  }

  TcpZerocopySendRecord* send_records_ ABSL_GUARDED_BY(mu_);
  TcpZerocopySendRecord** free_send_records_ ABSL_GUARDED_BY(mu_);
  int max_sends_;
  int free_send_records_size_ ABSL_GUARDED_BY(mu_);
  grpc_core::Mutex mu_;
  uint32_t last_send_ = 0;
  std::atomic<bool> shutdown_{false};
  bool enabled_ = false;
  size_t threshold_bytes_ = kDefaultSendBytesThreshold;
  absl::flat_hash_map<uint32_t, TcpZerocopySendRecord*> ctx_lookup_
      ABSL_GUARDED_BY(mu_);
  bool memory_limited_ = false;
  bool is_in_write_ ABSL_GUARDED_BY(mu_) = false;
  OptMemState zcopy_enobuf_state_ ABSL_GUARDED_BY(mu_) = OptMemState::kOpen;
};

class PosixEndpointImpl : public grpc_core::RefCounted<PosixEndpointImpl> {
 public:
  PosixEndpointImpl(
      EventHandle* handle, PosixEngineClosure* on_done,
      std::shared_ptr<grpc_event_engine::experimental::EventEngine> engine,
      grpc_event_engine::experimental::MemoryAllocator&& allocator,
      const PosixTcpOptions& options);
  ~PosixEndpointImpl() override;
  bool Read(
      absl::AnyInvocable<void(absl::Status)> on_read,
      grpc_event_engine::experimental::SliceBuffer* buffer,
      grpc_event_engine::experimental::EventEngine::Endpoint::ReadArgs args);
  bool Write(
      absl::AnyInvocable<void(absl::Status)> on_writable,
      grpc_event_engine::experimental::SliceBuffer* data,
      grpc_event_engine::experimental::EventEngine::Endpoint::WriteArgs args);
  const grpc_event_engine::experimental::EventEngine::ResolvedAddress&
  GetPeerAddress() const {
    return peer_address_;
  }
  const grpc_event_engine::experimental::EventEngine::ResolvedAddress&
  GetLocalAddress() const {
    return local_address_;
  }

  int GetWrappedFd() { return fd_; }

  bool CanTrackErrors() const { return poller_->CanTrackErrors(); }

  void MaybeShutdown(
      absl::Status why,
      absl::AnyInvocable<void(absl::StatusOr<int> release_fd)> on_release_fd);

 private:
  void UpdateRcvLowat() ABSL_EXCLUSIVE_LOCKS_REQUIRED(read_mu_);
  void HandleWrite(absl::Status status);
  void HandleError(absl::Status status);
  void HandleRead(absl::Status status) ABSL_NO_THREAD_SAFETY_ANALYSIS;
  bool HandleReadLocked(absl::Status& status)
      ABSL_EXCLUSIVE_LOCKS_REQUIRED(read_mu_);
  void MaybeMakeReadSlices() ABSL_EXCLUSIVE_LOCKS_REQUIRED(read_mu_);
  bool TcpDoRead(absl::Status& status) ABSL_EXCLUSIVE_LOCKS_REQUIRED(read_mu_);
  void FinishEstimate();
  void AddToEstimate(size_t bytes);
  void MaybePostReclaimer() ABSL_EXCLUSIVE_LOCKS_REQUIRED(read_mu_);
  void PerformReclamation() ABSL_LOCKS_EXCLUDED(read_mu_);

  TcpZerocopySendRecord* TcpGetSendZerocopyRecord(
      grpc_event_engine::experimental::SliceBuffer& buf);
  bool DoFlushZerocopy(TcpZerocopySendRecord* record, absl::Status& status);
  bool TcpFlushZerocopy(TcpZerocopySendRecord* record, absl::Status& status);
  bool TcpFlush(absl::Status& status);
  void TcpShutdownTracedBufferList();
  void UnrefMaybePutZerocopySendRecord(TcpZerocopySendRecord* record);
  void ZerocopyDisableAndWaitForRemaining();
  bool WriteWithTimestamps(struct msghdr* msg, size_t sending_length,
                           ssize_t* sent_length, int* saved_errno,
                           int additional_flags);
  absl::Status TcpAnnotateError(absl::Status src_error) const;
#ifdef GRPC_LINUX_ERRQUEUE
  bool ProcessErrors();

  void ProcessZerocopy(struct cmsghdr* cmsg);

  struct cmsghdr* ProcessTimestamp(msghdr* msg, struct cmsghdr* cmsg);
#endif
  grpc_core::Mutex read_mu_;
  PosixSocketWrapper sock_;
  int fd_;
  bool is_first_read_ = true;
  bool has_posted_reclaimer_ ABSL_GUARDED_BY(read_mu_) = false;
  double target_length_;
  int min_read_chunk_size_;
  int max_read_chunk_size_;
  int set_rcvlowat_ = 0;
  double bytes_read_this_round_ = 0;
  std::atomic<int> ref_count_{1};

  grpc_event_engine::experimental::SliceBuffer last_read_buffer_;

  grpc_event_engine::experimental::SliceBuffer* incoming_buffer_
      ABSL_GUARDED_BY(read_mu_) = nullptr;

  int inq_ = 1;

  bool inq_capable_ = false;

  grpc_event_engine::experimental::SliceBuffer* outgoing_buffer_ = nullptr;

  size_t outgoing_byte_idx_ = 0;

  PosixEngineClosure* on_read_ = nullptr;
  PosixEngineClosure* on_write_ = nullptr;
  PosixEngineClosure* on_error_ = nullptr;
  PosixEngineClosure* on_done_ = nullptr;
  absl::AnyInvocable<void(absl::Status)> read_cb_ ABSL_GUARDED_BY(read_mu_);
  absl::AnyInvocable<void(absl::Status)> write_cb_;

  grpc_event_engine::experimental::EventEngine::ResolvedAddress peer_address_;
  grpc_event_engine::experimental::EventEngine::ResolvedAddress local_address_;

  grpc_core::MemoryQuotaRefPtr mem_quota_;
  grpc_core::MemoryOwner memory_owner_;
  grpc_core::MemoryAllocator::Reservation self_reservation_;

  void* outgoing_buffer_arg_ = nullptr;

  absl::AnyInvocable<void(absl::StatusOr<int>)> on_release_fd_ = nullptr;

  int bytes_counter_ = -1;

#ifdef GRPC_LINUX_ERRQUEUE
  bool socket_ts_enabled_ = false;
#endif

  bool ts_capable_ = true;

  std::atomic<bool> stop_error_notification_{false};
  std::unique_ptr<TcpZerocopySendCtx> tcp_zerocopy_send_ctx_;
  TcpZerocopySendRecord* current_zerocopy_send_ = nullptr;

  int min_progress_size_ = 1;
  TracedBufferList traced_buffers_;

  EventHandle* handle_;
  PosixEventPoller* poller_;
  std::shared_ptr<grpc_event_engine::experimental::EventEngine> engine_;
};

class PosixEndpoint : public PosixEndpointWithFdSupport {
 public:
  PosixEndpoint(
      EventHandle* handle, PosixEngineClosure* on_shutdown,
      std::shared_ptr<grpc_event_engine::experimental::EventEngine> engine,
      grpc_event_engine::experimental::MemoryAllocator&& allocator,
      const PosixTcpOptions& options)
      : impl_(new PosixEndpointImpl(handle, on_shutdown, std::move(engine),
                                    std::move(allocator), options)) {}

  bool Read(absl::AnyInvocable<void(absl::Status)> on_read,
            grpc_event_engine::experimental::SliceBuffer* buffer,
            grpc_event_engine::experimental::EventEngine::Endpoint::ReadArgs
                args) override {
    return impl_->Read(std::move(on_read), buffer, std::move(args));
  }

  bool Write(absl::AnyInvocable<void(absl::Status)> on_writable,
             grpc_event_engine::experimental::SliceBuffer* data,
             grpc_event_engine::experimental::EventEngine::Endpoint::WriteArgs
                 args) override {
    return impl_->Write(std::move(on_writable), data, std::move(args));
  }

  std::vector<size_t> AllWriteMetrics() override { return {}; }
  std::optional<absl::string_view> GetMetricName(size_t) override {
    return std::nullopt;
  }
  std::optional<size_t> GetMetricKey(absl::string_view) override {
    return std::nullopt;
  }

  const grpc_event_engine::experimental::EventEngine::ResolvedAddress&
  GetPeerAddress() const override {
    return impl_->GetPeerAddress();
  }
  const grpc_event_engine::experimental::EventEngine::ResolvedAddress&
  GetLocalAddress() const override {
    return impl_->GetLocalAddress();
  }

  int GetWrappedFd() override { return impl_->GetWrappedFd(); }

  bool CanTrackErrors() override { return impl_->CanTrackErrors(); }

  void Shutdown(absl::AnyInvocable<void(absl::StatusOr<int> release_fd)>
                    on_release_fd) override {
    if (!shutdown_.exchange(true, std::memory_order_acq_rel)) {
      impl_->MaybeShutdown(absl::FailedPreconditionError("Endpoint closing"),
                           std::move(on_release_fd));
    }
  }

  ~PosixEndpoint() override {
    if (!shutdown_.exchange(true, std::memory_order_acq_rel)) {
      impl_->MaybeShutdown(absl::FailedPreconditionError("Endpoint closing"),
                           nullptr);
    }
  }

 private:
  PosixEndpointImpl* impl_;
  std::atomic<bool> shutdown_{false};
};

#else

class PosixEndpoint : public PosixEndpointWithFdSupport {
 public:
  PosixEndpoint() = default;

  bool Read(
      absl::AnyInvocable<void(absl::Status)> ,
      grpc_event_engine::experimental::SliceBuffer* ,
      grpc_event_engine::experimental::EventEngine::Endpoint::ReadArgs )
      override {
    grpc_core::Crash("PosixEndpoint::Read not supported on this platform");
  }

  bool Write(absl::AnyInvocable<void(absl::Status)> ,
             grpc_event_engine::experimental::SliceBuffer* ,
             grpc_event_engine::experimental::EventEngine::Endpoint::
                 WriteArgs ) override {
    grpc_core::Crash("PosixEndpoint::Write not supported on this platform");
  }

  const grpc_event_engine::experimental::EventEngine::ResolvedAddress&
  GetPeerAddress() const override {
    grpc_core::Crash(
        "PosixEndpoint::GetPeerAddress not supported on this platform");
  }
  const grpc_event_engine::experimental::EventEngine::ResolvedAddress&
  GetLocalAddress() const override {
    grpc_core::Crash(
        "PosixEndpoint::GetLocalAddress not supported on this platform");
  }

  int GetWrappedFd() override {
    grpc_core::Crash(
        "PosixEndpoint::GetWrappedFd not supported on this platform");
  }

  bool CanTrackErrors() override {
    grpc_core::Crash(
        "PosixEndpoint::CanTrackErrors not supported on this platform");
  }

  void Shutdown(absl::AnyInvocable<void(absl::StatusOr<int> release_fd)>
                    on_release_fd) override {
    grpc_core::Crash("PosixEndpoint::Shutdown not supported on this platform");
  }

  ~PosixEndpoint() override = default;
};

#endif

std::unique_ptr<PosixEndpoint> CreatePosixEndpoint(
    EventHandle* handle, PosixEngineClosure* on_shutdown,
    std::shared_ptr<EventEngine> engine,
    grpc_event_engine::experimental::MemoryAllocator&& allocator,
    const PosixTcpOptions& options);

}

#endif
