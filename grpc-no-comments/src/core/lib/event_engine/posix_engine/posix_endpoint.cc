// Copyright 2022 gRPC Authors

#include "src/core/lib/event_engine/posix_engine/posix_endpoint.h"

#include <errno.h>
#include <grpc/event_engine/internal/slice_cast.h>
#include <grpc/event_engine/slice.h>
#include <grpc/event_engine/slice_buffer.h>
#include <grpc/status.h>
#include <grpc/support/port_platform.h>
#include <inttypes.h>
#include <limits.h>

#include <algorithm>
#include <cctype>
#include <cstdint>
#include <cstdlib>
#include <memory>
#include <optional>
#include <string>
#include <type_traits>

#include "absl/functional/any_invocable.h"
#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/str_cat.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/lib/event_engine/posix_engine/event_poller.h"
#include "src/core/lib/event_engine/posix_engine/internal_errqueue.h"
#include "src/core/lib/event_engine/posix_engine/tcp_socket_utils.h"
#include "src/core/lib/event_engine/tcp_socket_utils.h"
#include "src/core/lib/experiments/experiments.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/lib/resource_quota/resource_quota.h"
#include "src/core/lib/slice/slice.h"
#include "src/core/telemetry/stats.h"
#include "src/core/util/debug_location.h"
#include "src/core/util/load_file.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/status_helper.h"
#include "src/core/util/strerror.h"
#include "src/core/util/sync.h"
#include "src/core/util/time.h"

#ifdef GRPC_POSIX_SOCKET_TCP
#ifdef GRPC_LINUX_ERRQUEUE
#include <dirent.h>
#include <linux/capability.h>
#include <linux/errqueue.h>
#include <linux/netlink.h>
#include <sys/prctl.h>
#include <sys/resource.h>
#endif
#include <netinet/in.h>

#ifndef SOL_TCP
#define SOL_TCP IPPROTO_TCP
#endif

#ifndef TCP_INQ
#define TCP_INQ 36
#define TCP_CM_INQ TCP_INQ
#endif

#ifdef GRPC_HAVE_MSG_NOSIGNAL
#define SENDMSG_FLAGS MSG_NOSIGNAL
#else
#define SENDMSG_FLAGS 0
#endif

#ifndef MSG_ZEROCOPY
#define MSG_ZEROCOPY 0x4000000
#endif

#define MAX_READ_IOVEC 64

namespace grpc_event_engine::experimental {

namespace {

ssize_t TcpSend(int fd, const struct msghdr* msg, int* saved_errno,
                int additional_flags = 0) {
  GRPC_LATENT_SEE_PARENT_SCOPE("TcpSend");
  ssize_t sent_length;
  do {
    grpc_core::global_stats().IncrementSyscallWrite();
    sent_length = sendmsg(fd, msg, SENDMSG_FLAGS | additional_flags);
  } while (sent_length < 0 && (*saved_errno = errno) == EINTR);
  return sent_length;
}

#ifdef GRPC_LINUX_ERRQUEUE

#define CAP_IS_SUPPORTED(cap) (prctl(PR_CAPBSET_READ, (cap), 0) > 0)

void rtrim(std::string& s) {
  s.erase(std::find_if(s.rbegin(), s.rend(),
                       [](unsigned char ch) { return !std::isspace(ch); })
              .base(),
          s.end());
}

uint64_t ParseUlimitMemLockFromFile(std::string file_name) {
  static std::string kHardMemlockPrefix = "* hard memlock";
  auto result = grpc_core::LoadFile(file_name, false);
  if (!result.ok()) {
    return 0;
  }
  std::string file_contents(reinterpret_cast<const char*>((*result).begin()),
                            (*result).length());

  size_t start = file_contents.find(kHardMemlockPrefix);
  if (start == std::string::npos) {
    return 0;
  }

  size_t end = file_contents.find(start, '\n');

  auto memlock_value_string = file_contents.substr(
      start + kHardMemlockPrefix.length() + 1, end - start);
  rtrim(memlock_value_string);
  if (memlock_value_string == "unlimited" ||
      memlock_value_string == "infinity") {
    return UINT64_MAX;
  } else {
    return std::atoi(memlock_value_string.c_str());
  }
}

uint64_t GetUlimitHardMemLock() {
  static const uint64_t kUlimitHardMemLock = []() -> uint64_t {
    if (CAP_IS_SUPPORTED(CAP_SYS_RESOURCE)) {

      return UINT64_MAX;
    }
    if (auto dir = opendir("/etc/security/limits.d")) {
      while (auto f = readdir(dir)) {
        if (f->d_name[0] == '.') {
          continue;
        }
        uint64_t hard_memlock = ParseUlimitMemLockFromFile(
            absl::StrCat("/etc/security/limits.d/", std::string(f->d_name)));
        if (hard_memlock != 0) {
          return hard_memlock;
        }
      }
      closedir(dir);
    }
    return ParseUlimitMemLockFromFile("/etc/security/limits.conf");
  }();
  return kUlimitHardMemLock;
}

uint64_t GetRLimitMemLockMax() {
  static const uint64_t kRlimitMemLock = []() -> uint64_t {
    if (CAP_IS_SUPPORTED(CAP_SYS_RESOURCE)) {

      return UINT64_MAX;
    }
    struct rlimit limit;
    if (getrlimit(RLIMIT_MEMLOCK, &limit) != 0) {
      return 0;
    }
    return static_cast<uint64_t>(limit.rlim_max);
  }();
  return kRlimitMemLock;
}

bool CmsgIsIpLevel(const cmsghdr& cmsg) {
  return (cmsg.cmsg_level == SOL_IPV6 && cmsg.cmsg_type == IPV6_RECVERR) ||
         (cmsg.cmsg_level == SOL_IP && cmsg.cmsg_type == IP_RECVERR);
}

bool CmsgIsZeroCopy(const cmsghdr& cmsg) {
  if (!CmsgIsIpLevel(cmsg)) {
    return false;
  }
  auto serr = reinterpret_cast<const sock_extended_err*> CMSG_DATA(&cmsg);
  return serr->ee_errno == 0 && serr->ee_origin == SO_EE_ORIGIN_ZEROCOPY;
}
#endif

absl::Status PosixOSError(int error_no, absl::string_view call_name) {
  return absl::UnknownError(absl::StrCat(
      call_name, ": ", grpc_core::StrError(error_no), " (", error_no, ")"));
}

}

#if defined(IOV_MAX) && IOV_MAX < 260
#define MAX_WRITE_IOVEC IOV_MAX
#else
#define MAX_WRITE_IOVEC 260
#endif
msg_iovlen_type TcpZerocopySendRecord::PopulateIovs(size_t* unwind_slice_idx,
                                                    size_t* unwind_byte_idx,
                                                    size_t* sending_length,
                                                    iovec* iov) {
  msg_iovlen_type iov_size;
  *unwind_slice_idx = out_offset_.slice_idx;
  *unwind_byte_idx = out_offset_.byte_idx;
  for (iov_size = 0;
       out_offset_.slice_idx != buf_.Count() && iov_size != MAX_WRITE_IOVEC;
       iov_size++) {
    MutableSlice& slice = internal::SliceCast<MutableSlice>(
        buf_.MutableSliceAt(out_offset_.slice_idx));
    iov[iov_size].iov_base = slice.begin() + out_offset_.byte_idx;
    iov[iov_size].iov_len = slice.length() - out_offset_.byte_idx;
    *sending_length += iov[iov_size].iov_len;
    ++(out_offset_.slice_idx);
    out_offset_.byte_idx = 0;
  }
  DCHECK_GT(iov_size, 0u);
  return iov_size;
}

void TcpZerocopySendRecord::UpdateOffsetForBytesSent(size_t sending_length,
                                                     size_t actually_sent) {
  size_t trailing = sending_length - actually_sent;
  while (trailing > 0) {
    size_t slice_length;
    out_offset_.slice_idx--;
    slice_length = buf_.RefSlice(out_offset_.slice_idx).length();
    if (slice_length > trailing) {
      out_offset_.byte_idx = slice_length - trailing;
      break;
    } else {
      trailing -= slice_length;
    }
  }
}

void PosixEndpointImpl::AddToEstimate(size_t bytes) {
  bytes_read_this_round_ += static_cast<double>(bytes);
}

void PosixEndpointImpl::FinishEstimate() {

  if (bytes_read_this_round_ > target_length_ * 0.8) {
    target_length_ = std::max(2 * target_length_, bytes_read_this_round_);
  } else {
    target_length_ = 0.99 * target_length_ + 0.01 * bytes_read_this_round_;
  }
  bytes_read_this_round_ = 0;
}

absl::Status PosixEndpointImpl::TcpAnnotateError(absl::Status src_error) const {
  grpc_core::StatusSetInt(&src_error, grpc_core::StatusIntProperty::kRpcStatus,
                          GRPC_STATUS_UNAVAILABLE);
  return src_error;
}

bool PosixEndpointImpl::TcpDoRead(absl::Status& status) {
  GRPC_LATENT_SEE_INNER_SCOPE("TcpDoRead");

  struct msghdr msg;
  struct iovec iov[MAX_READ_IOVEC];
  ssize_t read_bytes;
  size_t total_read_bytes = 0;
  size_t iov_len = std::min<size_t>(MAX_READ_IOVEC, incoming_buffer_->Count());
#ifdef GRPC_LINUX_ERRQUEUE
  constexpr size_t cmsg_alloc_space =
      CMSG_SPACE(sizeof(scm_timestamping)) + CMSG_SPACE(sizeof(int));
#else
  constexpr size_t cmsg_alloc_space = 24;
#endif
  char cmsgbuf[cmsg_alloc_space];
  for (size_t i = 0; i < iov_len; i++) {
    MutableSlice& slice =
        internal::SliceCast<MutableSlice>(incoming_buffer_->MutableSliceAt(i));
    iov[i].iov_base = slice.begin();
    iov[i].iov_len = slice.length();
  }

  CHECK_NE(incoming_buffer_->Length(), 0u);
  DCHECK_GT(min_progress_size_, 0);

  do {

    inq_ = 1;

    msg.msg_name = nullptr;
    msg.msg_namelen = 0;
    msg.msg_iov = iov;
    msg.msg_iovlen = static_cast<msg_iovlen_type>(iov_len);
    if (inq_capable_) {
      msg.msg_control = cmsgbuf;
      msg.msg_controllen = sizeof(cmsgbuf);
    } else {
      msg.msg_control = nullptr;
      msg.msg_controllen = 0;
    }
    msg.msg_flags = 0;

    grpc_core::global_stats().IncrementTcpReadOffer(incoming_buffer_->Length());
    grpc_core::global_stats().IncrementTcpReadOfferIovSize(
        incoming_buffer_->Count());
    do {
      grpc_core::global_stats().IncrementSyscallRead();
      read_bytes = recvmsg(fd_, &msg, 0);
    } while (read_bytes < 0 && errno == EINTR);

    if (read_bytes < 0 && errno == EAGAIN) {

      if (total_read_bytes > 0) {
        break;
      }
      FinishEstimate();
      inq_ = 0;
      return false;
    }

    if (read_bytes <= 0 && total_read_bytes >= 1) {
      break;
    }

    if (read_bytes <= 0) {

      incoming_buffer_->Clear();
      if (read_bytes == 0) {
        status = TcpAnnotateError(absl::InternalError("Socket closed"));
      } else {
        status = TcpAnnotateError(absl::InternalError(
            absl::StrCat("recvmsg:", grpc_core::StrError(errno))));
      }
      return true;
    }

    grpc_core::global_stats().IncrementTcpReadSize(read_bytes);
    AddToEstimate(static_cast<size_t>(read_bytes));
    DCHECK((size_t)read_bytes <= incoming_buffer_->Length() - total_read_bytes);

#ifdef GRPC_HAVE_TCP_INQ
    if (inq_capable_) {
      DCHECK(!(msg.msg_flags & MSG_CTRUNC));
      struct cmsghdr* cmsg = CMSG_FIRSTHDR(&msg);
      for (; cmsg != nullptr; cmsg = CMSG_NXTHDR(&msg, cmsg)) {
        if (cmsg->cmsg_level == SOL_TCP && cmsg->cmsg_type == TCP_CM_INQ &&
            cmsg->cmsg_len == CMSG_LEN(sizeof(int))) {
          inq_ = *reinterpret_cast<int*>(CMSG_DATA(cmsg));
          break;
        }
      }
    }
#endif

    total_read_bytes += read_bytes;
    if (inq_ == 0 || total_read_bytes == incoming_buffer_->Length()) {
      break;
    }

    size_t remaining = read_bytes;
    size_t j = 0;
    for (size_t i = 0; i < iov_len; i++) {
      if (remaining >= iov[i].iov_len) {
        remaining -= iov[i].iov_len;
        continue;
      }
      if (remaining > 0) {
        iov[j].iov_base = static_cast<char*>(iov[i].iov_base) + remaining;
        iov[j].iov_len = iov[i].iov_len - remaining;
        remaining = 0;
      } else {
        iov[j].iov_base = iov[i].iov_base;
        iov[j].iov_len = iov[i].iov_len;
      }
      ++j;
    }
    iov_len = j;
  } while (true);

  if (inq_ == 0) {
    FinishEstimate();

    inq_ = 1;
  }

  DCHECK_GT(total_read_bytes, 0u);
  status = absl::OkStatus();
  if (grpc_core::IsTcpFrameSizeTuningEnabled()) {

    min_progress_size_ -= total_read_bytes;
    if (min_progress_size_ > 0) {

      incoming_buffer_->MoveFirstNBytesIntoSliceBuffer(total_read_bytes,
                                                       last_read_buffer_);
      return false;
    } else {

      min_progress_size_ = 1;
      incoming_buffer_->MoveFirstNBytesIntoSliceBuffer(total_read_bytes,
                                                       last_read_buffer_);
      incoming_buffer_->Swap(last_read_buffer_);
      return true;
    }
  }
  if (total_read_bytes < incoming_buffer_->Length()) {
    incoming_buffer_->MoveLastNBytesIntoSliceBuffer(
        incoming_buffer_->Length() - total_read_bytes, last_read_buffer_);
  }
  return true;
}

void PosixEndpointImpl::PerformReclamation() {
  read_mu_.Lock();
  if (incoming_buffer_ != nullptr) {
    incoming_buffer_->Clear();
  }
  has_posted_reclaimer_ = false;
  read_mu_.Unlock();
}

void PosixEndpointImpl::MaybePostReclaimer() {
  if (!has_posted_reclaimer_) {
    has_posted_reclaimer_ = true;
    memory_owner_.PostReclaimer(
        grpc_core::ReclamationPass::kBenign,
        [self = Ref(DEBUG_LOCATION, "Posix Reclaimer")](
            std::optional<grpc_core::ReclamationSweep> sweep) {
          if (sweep.has_value()) {
            self->PerformReclamation();
          }
        });
  }
}

void PosixEndpointImpl::UpdateRcvLowat() {
  if (!grpc_core::IsTcpRcvLowatEnabled()) return;

  static constexpr int kRcvLowatMax = 16 * 1024 * 1024;
  static constexpr int kRcvLowatThreshold = 16 * 1024;

  int remaining = std::min({static_cast<int>(incoming_buffer_->Length()),
                            kRcvLowatMax, min_progress_size_});

  if (remaining < kRcvLowatThreshold) {
    remaining = 0;
  }

  if (!tcp_zerocopy_send_ctx_->Enabled() && remaining > 0) {
    remaining -= kRcvLowatThreshold;
  }

  if (set_rcvlowat_ <= 1 && remaining <= 1) return;

  if (set_rcvlowat_ == remaining) {
    return;
  }
  auto result = sock_.SetSocketRcvLowat(remaining);
  if (result.ok()) {
    set_rcvlowat_ = *result;
  } else {
    LOG(ERROR) << "ERROR in SO_RCVLOWAT: " << result.status().message();
  }
}

void PosixEndpointImpl::MaybeMakeReadSlices() {
  static const int kBigAlloc = 64 * 1024;
  static const int kSmallAlloc = 8 * 1024;
  if (incoming_buffer_->Length() < std::max<size_t>(min_progress_size_, 1)) {
    size_t allocate_length = min_progress_size_;
    const size_t target_length = static_cast<size_t>(target_length_);

    const bool low_memory_pressure =
        memory_owner_.GetPressureInfo().pressure_control_value < 0.8;
    if (low_memory_pressure && target_length > allocate_length) {
      allocate_length = target_length;
    }
    int extra_wanted = std::max<int>(
        1, allocate_length - static_cast<int>(incoming_buffer_->Length()));
    if (extra_wanted >=
        (low_memory_pressure ? kSmallAlloc * 3 / 2 : kBigAlloc)) {
      while (extra_wanted > 0) {
        extra_wanted -= kBigAlloc;
        incoming_buffer_->AppendIndexed(
            Slice(memory_owner_.MakeSlice(kBigAlloc)));
        grpc_core::global_stats().IncrementTcpReadAlloc64k();
      }
    } else {
      while (extra_wanted > 0) {
        extra_wanted -= kSmallAlloc;
        incoming_buffer_->AppendIndexed(
            Slice(memory_owner_.MakeSlice(kSmallAlloc)));
        grpc_core::global_stats().IncrementTcpReadAlloc8k();
      }
    }
    MaybePostReclaimer();
  }
}

bool PosixEndpointImpl::HandleReadLocked(absl::Status& status) {
  if (status.ok() && memory_owner_.is_valid()) {
    MaybeMakeReadSlices();
    if (!TcpDoRead(status)) {
      UpdateRcvLowat();

      return false;
    }
  } else {
    if (!memory_owner_.is_valid() && status.ok()) {
      status = TcpAnnotateError(absl::UnknownError("Shutting down endpoint"));
    }
    incoming_buffer_->Clear();
    last_read_buffer_.Clear();
  }
  return true;
}

void PosixEndpointImpl::HandleRead(absl::Status status) {
  bool ret = false;
  absl::AnyInvocable<void(absl::Status)> cb = nullptr;
  grpc_core::EnsureRunInExecCtx([&, this]() mutable {
    grpc_core::MutexLock lock(&read_mu_);
    ret = HandleReadLocked(status);
    if (ret) {
      GRPC_TRACE_LOG(event_engine_endpoint, INFO)
          << "Endpoint[" << this << "]: Read complete";
      cb = std::move(read_cb_);
      read_cb_ = nullptr;
      incoming_buffer_ = nullptr;
    }
  });
  if (!ret) {
    handle_->NotifyOnRead(on_read_);
    return;
  }
  cb(status);
  Unref();
}

bool PosixEndpointImpl::Read(absl::AnyInvocable<void(absl::Status)> on_read,
                             SliceBuffer* buffer,
                             EventEngine::Endpoint::ReadArgs args) {
  grpc_core::ReleasableMutexLock lock(&read_mu_);
  GRPC_TRACE_LOG(event_engine_endpoint, INFO)
      << "Endpoint[" << this << "]: Read";
  CHECK(read_cb_ == nullptr);
  incoming_buffer_ = buffer;
  incoming_buffer_->Clear();
  incoming_buffer_->Swap(last_read_buffer_);
  if (grpc_core::IsTcpFrameSizeTuningEnabled()) {
    min_progress_size_ = std::max(static_cast<int>(args.read_hint_bytes()), 1);
  } else {
    min_progress_size_ = 1;
  }
  Ref().release();
  if (is_first_read_) {
    read_cb_ = std::move(on_read);
    UpdateRcvLowat();

    is_first_read_ = false;
    lock.Release();
    handle_->NotifyOnRead(on_read_);
  } else if (inq_ == 0) {
    read_cb_ = std::move(on_read);
    UpdateRcvLowat();
    lock.Release();

    handle_->NotifyOnRead(on_read_);
  } else {
    absl::Status status;
    MaybeMakeReadSlices();
    if (!TcpDoRead(status)) {
      UpdateRcvLowat();
      read_cb_ = std::move(on_read);

      lock.Release();
      handle_->NotifyOnRead(on_read_);
      return false;
    }
    if (!status.ok()) {

      lock.Release();
      engine_->Run([on_read = std::move(on_read), status, this]() mutable {
        GRPC_TRACE_LOG(event_engine_endpoint, INFO)
            << "Endpoint[" << this << "]: Read failed immediately: " << status;
        on_read(status);
      });
      Unref();
      return false;
    }

    incoming_buffer_ = nullptr;
    Unref();
    GRPC_TRACE_LOG(event_engine_endpoint, INFO)
        << "Endpoint[" << this << "]: Read succeeded immediately";
    return true;
  }
  return false;
}

#ifdef GRPC_LINUX_ERRQUEUE
TcpZerocopySendRecord* PosixEndpointImpl::TcpGetSendZerocopyRecord(
    SliceBuffer& buf) {
  TcpZerocopySendRecord* zerocopy_send_record = nullptr;
  const bool use_zerocopy =
      tcp_zerocopy_send_ctx_->Enabled() &&
      tcp_zerocopy_send_ctx_->ThresholdBytes() < buf.Length();
  if (use_zerocopy) {
    zerocopy_send_record = tcp_zerocopy_send_ctx_->GetSendRecord();
    if (zerocopy_send_record == nullptr) {
      ProcessErrors();
      zerocopy_send_record = tcp_zerocopy_send_ctx_->GetSendRecord();
    }
    if (zerocopy_send_record != nullptr) {
      zerocopy_send_record->PrepareForSends(buf);
      DCHECK_EQ(buf.Count(), 0u);
      DCHECK_EQ(buf.Length(), 0u);
      outgoing_byte_idx_ = 0;
      outgoing_buffer_ = nullptr;
    }
  }
  return zerocopy_send_record;
}

bool PosixEndpointImpl::ProcessErrors() {
  bool processed_err = false;
  struct iovec iov;
  iov.iov_base = nullptr;
  iov.iov_len = 0;
  struct msghdr msg;
  msg.msg_name = nullptr;
  msg.msg_namelen = 0;
  msg.msg_iov = &iov;
  msg.msg_iovlen = 0;
  msg.msg_flags = 0;

  constexpr size_t cmsg_alloc_space =
      CMSG_SPACE(sizeof(scm_timestamping)) +
      CMSG_SPACE(sizeof(sock_extended_err) + sizeof(sockaddr_in)) +
      CMSG_SPACE(32 * NLA_ALIGN(NLA_HDRLEN + sizeof(uint64_t)));

  union {
    char rbuf[cmsg_alloc_space];
    struct cmsghdr align;
  } aligned_buf;
  msg.msg_control = aligned_buf.rbuf;
  int r, saved_errno;
  while (true) {
    msg.msg_controllen = sizeof(aligned_buf.rbuf);
    do {
      r = recvmsg(fd_, &msg, MSG_ERRQUEUE);
      saved_errno = errno;
    } while (r < 0 && saved_errno == EINTR);

    if (r < 0 && saved_errno == EAGAIN) {
      return processed_err;
    } else if (r < 0) {
      return processed_err;
    }
    if (GPR_UNLIKELY((msg.msg_flags & MSG_CTRUNC) != 0)) {
      LOG(ERROR) << "Error message was truncated.";
    }

    if (msg.msg_controllen == 0) {

      return processed_err;
    }
    bool seen = false;
    for (auto cmsg = CMSG_FIRSTHDR(&msg); cmsg && cmsg->cmsg_len;
         cmsg = CMSG_NXTHDR(&msg, cmsg)) {
      if (CmsgIsZeroCopy(*cmsg)) {
        ProcessZerocopy(cmsg);
        seen = true;
        processed_err = true;
      } else if (cmsg->cmsg_level == SOL_SOCKET &&
                 cmsg->cmsg_type == SCM_TIMESTAMPING) {
        cmsg = ProcessTimestamp(&msg, cmsg);
        seen = true;
        processed_err = true;
      } else {

        return processed_err;
      }
    }
    if (!seen) {
      return processed_err;
    }
  }
}

void PosixEndpointImpl::ZerocopyDisableAndWaitForRemaining() {
  tcp_zerocopy_send_ctx_->Shutdown();
  while (!tcp_zerocopy_send_ctx_->AllSendRecordsEmpty()) {
    ProcessErrors();
  }
}

void PosixEndpointImpl::ProcessZerocopy(struct cmsghdr* cmsg) {
  DCHECK(cmsg);
  auto serr = reinterpret_cast<struct sock_extended_err*>(CMSG_DATA(cmsg));
  DCHECK_EQ(serr->ee_errno, 0u);
  DCHECK(serr->ee_origin == SO_EE_ORIGIN_ZEROCOPY);
  const uint32_t lo = serr->ee_info;
  const uint32_t hi = serr->ee_data;
  for (uint32_t seq = lo; seq <= hi; ++seq) {

    TcpZerocopySendRecord* record =
        tcp_zerocopy_send_ctx_->ReleaseSendRecord(seq);
    DCHECK(record);
    UnrefMaybePutZerocopySendRecord(record);
  }
  if (tcp_zerocopy_send_ctx_->UpdateZeroCopyOptMemStateAfterFree()) {
    handle_->SetWritable();
  }
}

struct cmsghdr* PosixEndpointImpl::ProcessTimestamp(msghdr* msg,
                                                    struct cmsghdr* cmsg) {
  auto next_cmsg = CMSG_NXTHDR(msg, cmsg);
  cmsghdr* opt_stats = nullptr;
  if (next_cmsg == nullptr) {
    return cmsg;
  }

  if (next_cmsg->cmsg_level == SOL_SOCKET &&
      next_cmsg->cmsg_type == SCM_TIMESTAMPING_OPT_STATS) {
    opt_stats = next_cmsg;
    next_cmsg = CMSG_NXTHDR(msg, opt_stats);
    if (next_cmsg == nullptr) {
      return opt_stats;
    }
  }

  if (!(next_cmsg->cmsg_level == SOL_IP || next_cmsg->cmsg_level == SOL_IPV6) ||
      !(next_cmsg->cmsg_type == IP_RECVERR ||
        next_cmsg->cmsg_type == IPV6_RECVERR)) {
    return cmsg;
  }

  auto tss = reinterpret_cast<scm_timestamping*>(CMSG_DATA(cmsg));
  auto serr = reinterpret_cast<struct sock_extended_err*>(CMSG_DATA(next_cmsg));
  if (serr->ee_errno != ENOMSG ||
      serr->ee_origin != SO_EE_ORIGIN_TIMESTAMPING) {
    LOG(ERROR) << "Unexpected control message";
    return cmsg;
  }
  traced_buffers_.ProcessTimestamp(serr, opt_stats, tss);
  return next_cmsg;
}

void PosixEndpointImpl::HandleError(absl::Status status) {
  if (!status.ok() ||
      stop_error_notification_.load(std::memory_order_relaxed)) {

    Unref();
    return;
  }

  if (!ProcessErrors()) {

    handle_->SetReadable();
    handle_->SetWritable();
  }
  handle_->NotifyOnError(on_error_);
}

bool PosixEndpointImpl::WriteWithTimestamps(struct msghdr* msg,
                                            size_t sending_length,
                                            ssize_t* sent_length,
                                            int* saved_errno,
                                            int additional_flags) {
  if (!socket_ts_enabled_) {
    uint32_t opt = kTimestampingSocketOptions;
    if (setsockopt(fd_, SOL_SOCKET, SO_TIMESTAMPING, static_cast<void*>(&opt),
                   sizeof(opt)) != 0) {
      return false;
    }
    bytes_counter_ = -1;
    socket_ts_enabled_ = true;
  }

  union {
    char cmsg_buf[CMSG_SPACE(sizeof(uint32_t))];
    struct cmsghdr align;
  } u;
  cmsghdr* cmsg = reinterpret_cast<cmsghdr*>(u.cmsg_buf);
  cmsg->cmsg_level = SOL_SOCKET;
  cmsg->cmsg_type = SO_TIMESTAMPING;
  cmsg->cmsg_len = CMSG_LEN(sizeof(uint32_t));
  *reinterpret_cast<int*>(CMSG_DATA(cmsg)) = kTimestampingRecordingOptions;
  msg->msg_control = u.cmsg_buf;
  msg->msg_controllen = CMSG_SPACE(sizeof(uint32_t));

  grpc_core::global_stats().IncrementTcpWriteSize(sending_length);
  ssize_t length = TcpSend(fd_, msg, saved_errno, additional_flags);
  *sent_length = length;

  if (sending_length == static_cast<size_t>(length)) {
    traced_buffers_.AddNewEntry(static_cast<uint32_t>(bytes_counter_ + length),
                                fd_, outgoing_buffer_arg_);
    outgoing_buffer_arg_ = nullptr;
  }
  return true;
}

#else
TcpZerocopySendRecord* PosixEndpointImpl::TcpGetSendZerocopyRecord(
    SliceBuffer& ) {
  return nullptr;
}

void PosixEndpointImpl::HandleError(absl::Status ) {
  grpc_core::Crash("Error handling not supported on this platform");
}

void PosixEndpointImpl::ZerocopyDisableAndWaitForRemaining() {}

bool PosixEndpointImpl::WriteWithTimestamps(struct msghdr* ,
                                            size_t ,
                                            ssize_t* ,
                                            int* ,
                                            int ) {
  grpc_core::Crash("Write with timestamps not supported for this platform");
}
#endif

void PosixEndpointImpl::UnrefMaybePutZerocopySendRecord(
    TcpZerocopySendRecord* record) {
  if (record->Unref()) {
    tcp_zerocopy_send_ctx_->PutSendRecord(record);
  }
}

void PosixEndpointImpl::TcpShutdownTracedBufferList() {
  if (outgoing_buffer_arg_ != nullptr) {
    traced_buffers_.Shutdown(outgoing_buffer_arg_,
                             absl::InternalError("TracedBuffer list shutdown"));
    outgoing_buffer_arg_ = nullptr;
  }
}

bool PosixEndpointImpl::DoFlushZerocopy(TcpZerocopySendRecord* record,
                                        absl::Status& status) {
  msg_iovlen_type iov_size;
  ssize_t sent_length = 0;
  size_t sending_length;
  size_t unwind_slice_idx;
  size_t unwind_byte_idx;
  bool tried_sending_message;
  int saved_errno;
  msghdr msg;
  bool constrained;
  status = absl::OkStatus();

  iovec iov[MAX_WRITE_IOVEC];
  while (true) {
    sending_length = 0;
    iov_size = record->PopulateIovs(&unwind_slice_idx, &unwind_byte_idx,
                                    &sending_length, iov);
    msg.msg_name = nullptr;
    msg.msg_namelen = 0;
    msg.msg_iov = iov;
    msg.msg_iovlen = iov_size;
    msg.msg_flags = 0;
    tried_sending_message = false;
    constrained = false;

    tcp_zerocopy_send_ctx_->NoteSend(record);
    saved_errno = 0;
    if (outgoing_buffer_arg_ != nullptr) {
      if (!ts_capable_ ||
          !WriteWithTimestamps(&msg, sending_length, &sent_length, &saved_errno,
                               MSG_ZEROCOPY)) {

        ts_capable_ = false;
        TcpShutdownTracedBufferList();
      } else {
        tried_sending_message = true;
      }
    }
    if (!tried_sending_message) {
      msg.msg_control = nullptr;
      msg.msg_controllen = 0;
      grpc_core::global_stats().IncrementTcpWriteSize(sending_length);
      grpc_core::global_stats().IncrementTcpWriteIovSize(iov_size);
      sent_length = TcpSend(fd_, &msg, &saved_errno, MSG_ZEROCOPY);
    }
    if (tcp_zerocopy_send_ctx_->UpdateZeroCopyOptMemStateAfterSend(
            saved_errno == ENOBUFS, constrained) ||
        constrained) {

      if (!constrained) {
        handle_->SetWritable();
      } else {
#ifdef GRPC_LINUX_ERRQUEUE
        LOG_EVERY_N_SEC(INFO, 1)
            << "Tx0cp encountered an ENOBUFS error possibly because one or "
               "both of RLIMIT_MEMLOCK or hard memlock ulimit values are too "
               "small for the intended user. Current system value of "
               "RLIMIT_MEMLOCK is "
            << GetRLimitMemLockMax() << " and hard memlock ulimit is "
            << GetUlimitHardMemLock()
            << ".Consider increasing these values appropriately for the "
               "intended user.";
#endif
      }
    }
    if (sent_length < 0) {

      tcp_zerocopy_send_ctx_->UndoSend();
      if (saved_errno == EAGAIN || saved_errno == ENOBUFS) {
        record->UnwindIfThrottled(unwind_slice_idx, unwind_byte_idx);
        return false;
      } else {
        status = TcpAnnotateError(PosixOSError(saved_errno, "sendmsg"));
        TcpShutdownTracedBufferList();
        return true;
      }
    }
    bytes_counter_ += sent_length;
    record->UpdateOffsetForBytesSent(sending_length,
                                     static_cast<size_t>(sent_length));
    if (record->AllSlicesSent()) {
      return true;
    }
  }
}

bool PosixEndpointImpl::TcpFlushZerocopy(TcpZerocopySendRecord* record,
                                         absl::Status& status) {
  bool done = DoFlushZerocopy(record, status);
  if (done) {

    UnrefMaybePutZerocopySendRecord(record);
  }
  return done;
}

bool PosixEndpointImpl::TcpFlush(absl::Status& status) {
  struct msghdr msg;
  struct iovec iov[MAX_WRITE_IOVEC];
  msg_iovlen_type iov_size;
  ssize_t sent_length = 0;
  size_t sending_length;
  size_t trailing;
  size_t unwind_slice_idx;
  size_t unwind_byte_idx;
  int saved_errno;
  status = absl::OkStatus();

  size_t outgoing_slice_idx = 0;

  while (true) {
    sending_length = 0;
    unwind_slice_idx = outgoing_slice_idx;
    unwind_byte_idx = outgoing_byte_idx_;
    for (iov_size = 0; outgoing_slice_idx != outgoing_buffer_->Count() &&
                       iov_size != MAX_WRITE_IOVEC;
         iov_size++) {
      MutableSlice& slice = internal::SliceCast<MutableSlice>(
          outgoing_buffer_->MutableSliceAt(outgoing_slice_idx));
      iov[iov_size].iov_base = slice.begin() + outgoing_byte_idx_;
      iov[iov_size].iov_len = slice.length() - outgoing_byte_idx_;

      sending_length += iov[iov_size].iov_len;
      outgoing_slice_idx++;
      outgoing_byte_idx_ = 0;
    }
    CHECK_GT(iov_size, 0u);

    msg.msg_name = nullptr;
    msg.msg_namelen = 0;
    msg.msg_iov = iov;
    msg.msg_iovlen = iov_size;
    msg.msg_flags = 0;
    bool tried_sending_message = false;
    saved_errno = 0;
    if (outgoing_buffer_arg_ != nullptr) {
      if (!ts_capable_ || !WriteWithTimestamps(&msg, sending_length,
                                               &sent_length, &saved_errno, 0)) {

        ts_capable_ = false;
        TcpShutdownTracedBufferList();
      } else {
        tried_sending_message = true;
      }
    }
    if (!tried_sending_message) {
      msg.msg_control = nullptr;
      msg.msg_controllen = 0;
      grpc_core::global_stats().IncrementTcpWriteSize(sending_length);
      grpc_core::global_stats().IncrementTcpWriteIovSize(iov_size);
      sent_length = TcpSend(fd_, &msg, &saved_errno);
    }

    if (sent_length < 0) {
      if (saved_errno == EAGAIN || saved_errno == ENOBUFS) {
        outgoing_byte_idx_ = unwind_byte_idx;

        for (size_t idx = 0; idx < unwind_slice_idx; ++idx) {
          outgoing_buffer_->TakeFirst();
        }
        return false;
      } else {
        status = TcpAnnotateError(PosixOSError(saved_errno, "sendmsg"));
        outgoing_buffer_->Clear();
        TcpShutdownTracedBufferList();
        return true;
      }
    }

    CHECK_EQ(outgoing_byte_idx_, 0u);
    bytes_counter_ += sent_length;
    trailing = sending_length - static_cast<size_t>(sent_length);
    while (trailing > 0) {
      size_t slice_length;
      outgoing_slice_idx--;
      slice_length = outgoing_buffer_->RefSlice(outgoing_slice_idx).length();
      if (slice_length > trailing) {
        outgoing_byte_idx_ = slice_length - trailing;
        break;
      } else {
        trailing -= slice_length;
      }
    }
    if (outgoing_slice_idx == outgoing_buffer_->Count()) {
      outgoing_buffer_->Clear();
      return true;
    }
  }
}

void PosixEndpointImpl::HandleWrite(absl::Status status) {
  if (!status.ok()) {
    GRPC_TRACE_LOG(event_engine_endpoint, INFO)
        << "Endpoint[" << this << "]: Write failed: " << status;
    absl::AnyInvocable<void(absl::Status)> cb_ = std::move(write_cb_);
    write_cb_ = nullptr;
    if (current_zerocopy_send_ != nullptr) {
      UnrefMaybePutZerocopySendRecord(current_zerocopy_send_);
      current_zerocopy_send_ = nullptr;
    }
    cb_(status);
    Unref();
    return;
  }
  bool flush_result = current_zerocopy_send_ != nullptr
                          ? TcpFlushZerocopy(current_zerocopy_send_, status)
                          : TcpFlush(status);
  if (!flush_result) {
    DCHECK(status.ok());
    handle_->NotifyOnWrite(on_write_);
  } else {
    GRPC_TRACE_LOG(event_engine_endpoint, INFO)
        << "Endpoint[" << this << "]: Write complete: " << status;
    absl::AnyInvocable<void(absl::Status)> cb_ = std::move(write_cb_);
    write_cb_ = nullptr;
    current_zerocopy_send_ = nullptr;
    cb_(status);
    Unref();
  }
}

bool PosixEndpointImpl::Write(
    absl::AnyInvocable<void(absl::Status)> on_writable, SliceBuffer* data,
    EventEngine::Endpoint::WriteArgs args) {
  absl::Status status = absl::OkStatus();
  TcpZerocopySendRecord* zerocopy_send_record = nullptr;

  CHECK(write_cb_ == nullptr);
  DCHECK_EQ(current_zerocopy_send_, nullptr);
  DCHECK_NE(data, nullptr);

  GRPC_TRACE_LOG(event_engine_endpoint, INFO)
      << "Endpoint[" << this << "]: Write " << data->Length() << " bytes";

  if (data->Length() == 0) {
    TcpShutdownTracedBufferList();
    if (handle_->IsHandleShutdown()) {
      status = TcpAnnotateError(absl::InternalError("EOF"));
      engine_->Run(
          [on_writable = std::move(on_writable), status, this]() mutable {
            GRPC_TRACE_LOG(event_engine_endpoint, INFO)
                << "Endpoint[" << this << "]: Write failed: " << status;
            on_writable(status);
          });
      return false;
    }
    GRPC_TRACE_LOG(event_engine_endpoint, INFO)
        << "Endpoint[" << this << "]: Write skipped";
    return true;
  }

  zerocopy_send_record = TcpGetSendZerocopyRecord(*data);
  if (zerocopy_send_record == nullptr) {

    outgoing_buffer_ = data;
    outgoing_byte_idx_ = 0;
  }
  outgoing_buffer_arg_ =
      args.GetDeprecatedAndDiscouragedGoogleSpecificPointer();
  if (outgoing_buffer_arg_) {
    CHECK(poller_->CanTrackErrors());
  }

  bool flush_result = zerocopy_send_record != nullptr
                          ? TcpFlushZerocopy(zerocopy_send_record, status)
                          : TcpFlush(status);
  if (!flush_result) {
    Ref().release();
    write_cb_ = std::move(on_writable);
    current_zerocopy_send_ = zerocopy_send_record;
    handle_->NotifyOnWrite(on_write_);
    return false;
  }
  if (!status.ok()) {

    engine_->Run(
        [on_writable = std::move(on_writable), status, this]() mutable {
          GRPC_TRACE_LOG(event_engine_endpoint, INFO)
              << "Endpoint[" << this << "]: Write failed: " << status;
          on_writable(status);
        });
    return false;
  }

  GRPC_TRACE_LOG(event_engine_endpoint, INFO)
      << "Endpoint[" << this << "]: Write succeeded immediately";
  return true;
}

void PosixEndpointImpl::MaybeShutdown(
    absl::Status why,
    absl::AnyInvocable<void(absl::StatusOr<int>)> on_release_fd) {
  if (poller_->CanTrackErrors()) {
    ZerocopyDisableAndWaitForRemaining();
    stop_error_notification_.store(true, std::memory_order_release);
    handle_->SetHasError();
  }
  on_release_fd_ = std::move(on_release_fd);
  grpc_core::StatusSetInt(&why, grpc_core::StatusIntProperty::kRpcStatus,
                          GRPC_STATUS_UNAVAILABLE);
  handle_->ShutdownHandle(why);
  read_mu_.Lock();
  memory_owner_.Reset();
  read_mu_.Unlock();
  Unref();
}

PosixEndpointImpl ::~PosixEndpointImpl() {
  int release_fd = -1;
  handle_->OrphanHandle(on_done_,
                        on_release_fd_ == nullptr ? nullptr : &release_fd, "");
  if (on_release_fd_ != nullptr) {
    engine_->Run([on_release_fd = std::move(on_release_fd_),
                  release_fd]() mutable { on_release_fd(release_fd); });
  }
  delete on_read_;
  delete on_write_;
  delete on_error_;
}

PosixEndpointImpl::PosixEndpointImpl(EventHandle* handle,
                                     PosixEngineClosure* on_done,
                                     std::shared_ptr<EventEngine> engine,
                                     MemoryAllocator&& ,
                                     const PosixTcpOptions& options)
    : sock_(PosixSocketWrapper(handle->WrappedFd())),
      on_done_(on_done),
      traced_buffers_(),
      handle_(handle),
      poller_(handle->Poller()),
      engine_(engine) {
  PosixSocketWrapper sock(handle->WrappedFd());
  fd_ = handle_->WrappedFd();
  CHECK(options.resource_quota != nullptr);
  auto peer_addr_string = sock.PeerAddressString();
  mem_quota_ = options.resource_quota->memory_quota();
  memory_owner_ = mem_quota_->CreateMemoryOwner();
  self_reservation_ = memory_owner_.MakeReservation(sizeof(PosixEndpointImpl));
  auto local_address = sock.LocalAddress();
  if (local_address.ok()) {
    local_address_ = *local_address;
  }
  auto peer_address = sock.PeerAddress();
  if (peer_address.ok()) {
    peer_address_ = *peer_address;
  }
  target_length_ = static_cast<double>(options.tcp_read_chunk_size);
  bytes_read_this_round_ = 0;
  min_read_chunk_size_ = options.tcp_min_read_chunk_size;
  max_read_chunk_size_ = options.tcp_max_read_chunk_size;
  bool zerocopy_enabled =
      options.tcp_tx_zero_copy_enabled && poller_->CanTrackErrors();
#ifdef GRPC_LINUX_ERRQUEUE
  if (zerocopy_enabled) {
    if (GetRLimitMemLockMax() == 0) {
      zerocopy_enabled = false;
      LOG(ERROR) << "Tx zero-copy will not be used by gRPC since RLIMIT_MEMLOCK"
                 << " value is not set. Consider raising its value with "
                 << "setrlimit().";
    } else if (GetUlimitHardMemLock() == 0) {
      zerocopy_enabled = false;
      LOG(ERROR) << "Tx zero-copy will not be used by gRPC since hard memlock "
                 << "ulimit value is not set. Use ulimit -l <value> to set its "
                 << "value.";
    } else {
      const int enable = 1;
      if (setsockopt(fd_, SOL_SOCKET, SO_ZEROCOPY, &enable, sizeof(enable)) !=
          0) {
        zerocopy_enabled = false;
        LOG(ERROR) << "Failed to set zerocopy options on the socket.";
      }
    }

    if (zerocopy_enabled) {
      VLOG(2) << "Tx-zero copy enabled for gRPC sends. RLIMIT_MEMLOCK value "
              << "=" << GetRLimitMemLockMax()
              << ",ulimit hard memlock value = " << GetUlimitHardMemLock();
    }
  }
#endif
  tcp_zerocopy_send_ctx_ = std::make_unique<TcpZerocopySendCtx>(
      zerocopy_enabled, options.tcp_tx_zerocopy_max_simultaneous_sends,
      options.tcp_tx_zerocopy_send_bytes_threshold);
#ifdef GRPC_HAVE_TCP_INQ
  int one = 1;
  if (setsockopt(fd_, SOL_TCP, TCP_INQ, &one, sizeof(one)) == 0) {
    inq_capable_ = true;
  } else {
    VLOG(2) << "cannot set inq fd=" << fd_ << " errno=" << errno;
    inq_capable_ = false;
  }
#else
  inq_capable_ = false;
#endif

  on_read_ = PosixEngineClosure::ToPermanentClosure(
      [this](absl::Status status) { HandleRead(std::move(status)); });
  on_write_ = PosixEngineClosure::ToPermanentClosure(
      [this](absl::Status status) { HandleWrite(std::move(status)); });
  on_error_ = PosixEngineClosure::ToPermanentClosure(
      [this](absl::Status status) { HandleError(std::move(status)); });

  if (poller_->CanTrackErrors()) {
    Ref().release();
    handle_->NotifyOnError(on_error_);
  }
}

std::unique_ptr<PosixEndpoint> CreatePosixEndpoint(
    EventHandle* handle, PosixEngineClosure* on_shutdown,
    std::shared_ptr<EventEngine> engine, MemoryAllocator&& allocator,
    const PosixTcpOptions& options) {
  DCHECK_NE(handle, nullptr);
  return std::make_unique<PosixEndpoint>(handle, on_shutdown, std::move(engine),
                                         std::move(allocator), options);
}

}

#else

namespace grpc_event_engine::experimental {

std::unique_ptr<PosixEndpoint> CreatePosixEndpoint(
    EventHandle* , PosixEngineClosure* ,
    std::shared_ptr<EventEngine> ,
    const PosixTcpOptions& ) {
  grpc_core::Crash("Cannot create PosixEndpoint on this platform");
}

}

#endif
