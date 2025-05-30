
// Copyright 2017 gRPC authors.

#ifndef GRPC_SRC_CORE_EXT_TRANSPORT_CHTTP2_TRANSPORT_FLOW_CONTROL_H
#define GRPC_SRC_CORE_EXT_TRANSPORT_CHTTP2_TRANSPORT_FLOW_CONTROL_H

#include <grpc/support/port_platform.h>
#include <limits.h>
#include <stdint.h>

#include <iosfwd>
#include <optional>
#include <string>
#include <utility>

#include "absl/functional/function_ref.h"
#include "absl/log/check.h"
#include "absl/status/status.h"
#include "absl/strings/string_view.h"
#include "src/core/ext/transport/chttp2/transport/http2_settings.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/lib/resource_quota/memory_quota.h"
#include "src/core/lib/transport/bdp_estimator.h"
#include "src/core/util/time.h"

namespace grpc {
namespace testing {
class TrickledCHTTP2;
}
}

namespace grpc_core {
namespace chttp2 {

static constexpr uint32_t kDefaultWindow = 65535;
static constexpr uint32_t kDefaultFrameSize = 16384;
static constexpr int64_t kMaxWindow = static_cast<int64_t>((1u << 31) - 1);

static constexpr uint32_t kMinPositiveInitialWindowSize = 1024;
static constexpr const uint32_t kMaxInitialWindowSize = (1u << 30);

static constexpr const int64_t kMaxWindowDelta = (1u << 20);
static constexpr const int kDefaultPreferredRxCryptoFrameSize = INT_MAX;

static constexpr uint32_t kFrameSize = 1024 * 1024;
static constexpr const uint32_t kMinInitialWindowSize = 128;

class TransportFlowControl;
class StreamFlowControl;

enum class StallEdge { kNoChange, kStalled, kUnstalled };

class GRPC_MUST_USE_RESULT FlowControlAction {
 public:
  enum class Urgency : uint8_t {

    NO_ACTION_NEEDED = 0,

    UPDATE_IMMEDIATELY,

    QUEUE_UPDATE,
  };

  Urgency send_stream_update() const { return send_stream_update_; }
  Urgency send_transport_update() const { return send_transport_update_; }
  Urgency send_initial_window_update() const {
    return send_initial_window_update_;
  }
  Urgency send_max_frame_size_update() const {
    return send_max_frame_size_update_;
  }
  Urgency preferred_rx_crypto_frame_size_update() const {
    return preferred_rx_crypto_frame_size_update_;
  }
  uint32_t initial_window_size() const { return initial_window_size_; }
  uint32_t max_frame_size() const { return max_frame_size_; }
  uint32_t preferred_rx_crypto_frame_size() const {
    return preferred_rx_crypto_frame_size_;
  }

  FlowControlAction& set_send_stream_update(Urgency u) {
    send_stream_update_ = u;
    return *this;
  }
  FlowControlAction& set_send_transport_update(Urgency u) {
    send_transport_update_ = u;
    return *this;
  }
  FlowControlAction& set_send_initial_window_update(Urgency u,
                                                    uint32_t update) {
    send_initial_window_update_ = u;
    initial_window_size_ = update;
    return *this;
  }
  FlowControlAction& set_send_max_frame_size_update(Urgency u,
                                                    uint32_t update) {
    send_max_frame_size_update_ = u;
    max_frame_size_ = update;
    return *this;
  }
  FlowControlAction& set_preferred_rx_crypto_frame_size_update(
      Urgency u, uint32_t update) {
    preferred_rx_crypto_frame_size_update_ = u;
    preferred_rx_crypto_frame_size_ = update;
    return *this;
  }

  static const char* UrgencyString(Urgency u);
  std::string DebugString() const;

  void AssertEmpty() { CHECK(*this == FlowControlAction()); }

  bool operator==(const FlowControlAction& other) const {
    return send_stream_update_ == other.send_stream_update_ &&
           send_transport_update_ == other.send_transport_update_ &&
           send_initial_window_update_ == other.send_initial_window_update_ &&
           send_max_frame_size_update_ == other.send_max_frame_size_update_ &&
           (send_initial_window_update_ == Urgency::NO_ACTION_NEEDED ||
            initial_window_size_ == other.initial_window_size_) &&
           (send_max_frame_size_update_ == Urgency::NO_ACTION_NEEDED ||
            max_frame_size_ == other.max_frame_size_) &&
           (preferred_rx_crypto_frame_size_update_ ==
                Urgency::NO_ACTION_NEEDED ||
            preferred_rx_crypto_frame_size_ ==
                other.preferred_rx_crypto_frame_size_);
  }

 private:
  Urgency send_stream_update_ = Urgency::NO_ACTION_NEEDED;
  Urgency send_transport_update_ = Urgency::NO_ACTION_NEEDED;
  Urgency send_initial_window_update_ = Urgency::NO_ACTION_NEEDED;
  Urgency send_max_frame_size_update_ = Urgency::NO_ACTION_NEEDED;
  Urgency preferred_rx_crypto_frame_size_update_ = Urgency::NO_ACTION_NEEDED;
  uint32_t initial_window_size_ = 0;
  uint32_t max_frame_size_ = 0;
  uint32_t preferred_rx_crypto_frame_size_ = 0;
};

std::ostream& operator<<(std::ostream& out, FlowControlAction::Urgency urgency);
std::ostream& operator<<(std::ostream& out, const FlowControlAction& action);

class TransportFlowControl final {
 public:
  explicit TransportFlowControl(absl::string_view name, bool enable_bdp_probe,
                                MemoryOwner* memory_owner);
  ~TransportFlowControl() {}

  bool bdp_probe() const { return enable_bdp_probe_; }

  uint32_t DesiredAnnounceSize(bool writing_anyway) const;

  void SentUpdate(uint32_t announce);

  uint32_t MaybeSendUpdate(bool writing_anyway) {
    uint32_t n = DesiredAnnounceSize(writing_anyway);
    SentUpdate(n);
    return n;
  }

  class IncomingUpdateContext {
   public:
    explicit IncomingUpdateContext(TransportFlowControl* tfc) : tfc_(tfc) {}
    ~IncomingUpdateContext() { CHECK_EQ(tfc_, nullptr); }

    IncomingUpdateContext(const IncomingUpdateContext&) = delete;
    IncomingUpdateContext& operator=(const IncomingUpdateContext&) = delete;

    FlowControlAction MakeAction() {
      return std::exchange(tfc_, nullptr)->UpdateAction(FlowControlAction());
    }

    absl::Status RecvData(
        int64_t incoming_frame_size, absl::FunctionRef<absl::Status()> stream =
                                         []() { return absl::OkStatus(); });

    void UpdateAnnouncedWindowDelta(int64_t* delta, int64_t change) {
      if (change == 0) return;
      if (*delta > 0) {
        tfc_->announced_stream_total_over_incoming_window_ -= *delta;
      }
      *delta += change;
      if (*delta > 0) {
        tfc_->announced_stream_total_over_incoming_window_ += *delta;
      }
    }

   private:
    TransportFlowControl* tfc_;
  };

  class OutgoingUpdateContext {
   public:
    explicit OutgoingUpdateContext(TransportFlowControl* tfc) : tfc_(tfc) {}
    void StreamSentData(int64_t size) { tfc_->remote_window_ -= size; }

    void RecvUpdate(uint32_t size) { tfc_->remote_window_ += size; }

    StallEdge Finish() {
      bool is_stalled = tfc_->remote_window_ <= 0;
      if (is_stalled != was_stalled_) {
        return is_stalled ? StallEdge::kStalled : StallEdge::kUnstalled;
      } else {
        return StallEdge::kNoChange;
      }
    }

   private:
    TransportFlowControl* tfc_;
    const bool was_stalled_ = tfc_->remote_window_ <= 0;
  };

  FlowControlAction PeriodicUpdate();

  int64_t target_window() const;
  int64_t target_frame_size() const { return target_frame_size_; }
  int64_t target_preferred_rx_crypto_frame_size() const {
    return target_preferred_rx_crypto_frame_size_;
  }

  BdpEstimator* bdp_estimator() { return &bdp_estimator_; }

  uint32_t acked_init_window() const { return acked_init_window_; }
  uint32_t queued_init_window() const { return target_initial_window_size_; }
  uint32_t sent_init_window() const { return sent_init_window_; }

  void FlushedSettings() { sent_init_window_ = queued_init_window(); }

  FlowControlAction SetAckedInitialWindow(uint32_t value);

  void set_target_initial_window_size(uint32_t value) {
    target_initial_window_size_ =
        std::min(value, Http2Settings::max_initial_window_size());
  }

  int64_t remote_window() const { return remote_window_; }
  int64_t announced_window() const { return announced_window_; }

  int64_t announced_stream_total_over_incoming_window() const {
    return announced_stream_total_over_incoming_window_;
  }

  void RemoveAnnouncedWindowDelta(int64_t delta) {
    if (delta > 0) {
      announced_stream_total_over_incoming_window_ -= delta;
    }
  }

  struct Stats {
    int64_t target_window;
    int64_t target_frame_size;
    int64_t target_preferred_rx_crypto_frame_size;
    uint32_t acked_init_window;
    uint32_t queued_init_window;
    uint32_t sent_init_window;
    int64_t remote_window;
    int64_t announced_window;
    int64_t announced_stream_total_over_incoming_window;

    int64_t bdp_accumulator;
    int64_t bdp_estimate;
    double bdp_bw_est;

    std::string ToString() const;
    Json::Object ToJsonObject() {
      Json::Object object;
      object["targetWindow"] = Json::FromNumber(target_window);
      object["targetFrameSize"] = Json::FromNumber(target_frame_size);
      object["targetPreferredRxCryptoFrameSize"] =
          Json::FromNumber(target_preferred_rx_crypto_frame_size);
      object["ackedInitWindow"] = Json::FromNumber(acked_init_window);
      object["queuedInitWindow"] = Json::FromNumber(queued_init_window);
      object["sentInitWindow"] = Json::FromNumber(sent_init_window);
      object["remoteWindow"] = Json::FromNumber(remote_window);
      object["announcedWindow"] = Json::FromNumber(announced_window);
      object["announcedStreamTotalOverIncomingWindow"] =
          Json::FromNumber(announced_stream_total_over_incoming_window);
      object["bdpAccumulator"] = Json::FromNumber(bdp_accumulator);
      object["bdpEstimate"] = Json::FromNumber(bdp_estimate);
      object["bdpBwEst"] = Json::FromNumber(bdp_bw_est);
      return object;
    }
  };

  Stats stats() const {
    Stats stats;
    stats.target_window = target_window();
    stats.target_frame_size = target_frame_size();
    stats.target_preferred_rx_crypto_frame_size =
        target_preferred_rx_crypto_frame_size();
    stats.acked_init_window = acked_init_window();
    stats.queued_init_window = queued_init_window();
    stats.sent_init_window = sent_init_window();
    stats.remote_window = remote_window();
    stats.announced_window = announced_window();
    stats.announced_stream_total_over_incoming_window =
        announced_stream_total_over_incoming_window();
    stats.bdp_accumulator = bdp_estimator_.accumulator();
    stats.bdp_estimate = bdp_estimator_.EstimateBdp();
    stats.bdp_bw_est = bdp_estimator_.EstimateBandwidth();
    return stats;
  }

 private:
  double TargetInitialWindowSizeBasedOnMemoryPressureAndBdp() const;
  static void UpdateSetting(absl::string_view name, int64_t* desired_value,
                            uint32_t new_desired_value,
                            FlowControlAction* action,
                            FlowControlAction& (FlowControlAction::*set)(
                                FlowControlAction::Urgency, uint32_t));

  FlowControlAction UpdateAction(FlowControlAction action);

  MemoryOwner* const memory_owner_;

  int64_t announced_stream_total_over_incoming_window_ = 0;

  const bool enable_bdp_probe_;

  BdpEstimator bdp_estimator_;

  int64_t remote_window_ = kDefaultWindow;
  int64_t target_initial_window_size_ = kDefaultWindow;
  int64_t target_frame_size_ = kDefaultFrameSize;
  int64_t target_preferred_rx_crypto_frame_size_ =
      kDefaultPreferredRxCryptoFrameSize;
  int64_t announced_window_ = kDefaultWindow;
  uint32_t acked_init_window_ = kDefaultWindow;
  uint32_t sent_init_window_ = kDefaultWindow;
};

class StreamFlowControl final {
 public:
  explicit StreamFlowControl(TransportFlowControl* tfc);
  ~StreamFlowControl() {
    tfc_->RemoveAnnouncedWindowDelta(announced_window_delta_);
  }

  class IncomingUpdateContext {
   public:
    explicit IncomingUpdateContext(StreamFlowControl* sfc)
        : tfc_upd_(sfc->tfc_), sfc_(sfc) {}

    FlowControlAction MakeAction() {
      return sfc_->UpdateAction(tfc_upd_.MakeAction());
    }

    absl::Status RecvData(int64_t incoming_frame_size);

    void SetMinProgressSize(int64_t min_progress_size) {
      sfc_->min_progress_size_ = min_progress_size;
    }

    void SetPendingSize(int64_t pending_size);

   private:
    TransportFlowControl::IncomingUpdateContext tfc_upd_;
    StreamFlowControl* const sfc_;
  };

  class OutgoingUpdateContext {
   public:
    explicit OutgoingUpdateContext(StreamFlowControl* sfc)
        : tfc_upd_(sfc->tfc_), sfc_(sfc) {}

    void RecvUpdate(uint32_t size) { sfc_->remote_window_delta_ += size; }

    void SentData(int64_t outgoing_frame_size) {
      tfc_upd_.StreamSentData(outgoing_frame_size);
      sfc_->remote_window_delta_ -= outgoing_frame_size;
    }

   private:
    TransportFlowControl::OutgoingUpdateContext tfc_upd_;
    StreamFlowControl* const sfc_;
  };

  uint32_t DesiredAnnounceSize() const;

  void SentUpdate(uint32_t announce);

  uint32_t MaybeSendUpdate() {
    uint32_t n = DesiredAnnounceSize();
    SentUpdate(n);
    return n;
  }

  int64_t remote_window_delta() const { return remote_window_delta_; }
  int64_t announced_window_delta() const { return announced_window_delta_; }
  int64_t min_progress_size() const { return min_progress_size_; }

  struct Stats {
    int64_t min_progress_size;
    int64_t remote_window_delta;
    int64_t announced_window_delta;
    std::optional<int64_t> pending_size;

    std::string ToString() const;
  };

  Stats stats() const {
    Stats stats;
    stats.min_progress_size = min_progress_size();
    stats.remote_window_delta = remote_window_delta();
    stats.announced_window_delta = announced_window_delta();
    stats.pending_size = pending_size_;
    return stats;
  }

 private:
  TransportFlowControl* const tfc_;
  int64_t min_progress_size_ = 0;
  int64_t remote_window_delta_ = 0;
  int64_t announced_window_delta_ = 0;
  std::optional<int64_t> pending_size_;

  FlowControlAction UpdateAction(FlowControlAction action);
};

class TestOnlyTransportTargetWindowEstimatesMocker {
 public:
  virtual ~TestOnlyTransportTargetWindowEstimatesMocker() {}
  virtual double ComputeNextTargetInitialWindowSizeFromPeriodicUpdate(
      double current_target) = 0;
};

extern TestOnlyTransportTargetWindowEstimatesMocker*
    g_test_only_transport_target_window_estimates_mocker;

}
}

#endif
