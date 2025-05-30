
// Copyright 2015 gRPC authors.

#include "src/core/load_balancing/pick_first/pick_first.h"

#include <grpc/event_engine/event_engine.h>
#include <grpc/impl/channel_arg_names.h>
#include <grpc/impl/connectivity_state.h>
#include <grpc/support/port_platform.h>
#include <inttypes.h>
#include <string.h>

#include <memory>
#include <optional>
#include <set>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

#include "absl/algorithm/container.h"
#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/random/random.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/string_view.h"
#include "src/core/config/core_configuration.h"
#include "src/core/lib/address_utils/sockaddr_utils.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/lib/experiments/experiments.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/lib/iomgr/iomgr_fwd.h"
#include "src/core/lib/iomgr/resolved_address.h"
#include "src/core/lib/transport/connectivity_state.h"
#include "src/core/load_balancing/health_check_client.h"
#include "src/core/load_balancing/lb_policy.h"
#include "src/core/load_balancing/lb_policy_factory.h"
#include "src/core/load_balancing/subchannel_interface.h"
#include "src/core/resolver/endpoint_addresses.h"
#include "src/core/telemetry/metrics.h"
#include "src/core/util/crash.h"
#include "src/core/util/debug_location.h"
#include "src/core/util/json/json.h"
#include "src/core/util/json/json_args.h"
#include "src/core/util/json/json_object_loader.h"
#include "src/core/util/orphanable.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/shared_bit_gen.h"
#include "src/core/util/time.h"
#include "src/core/util/useful.h"
#include "src/core/util/work_serializer.h"

namespace grpc_core {

namespace {

constexpr absl::string_view kPickFirst = "pick_first";

const auto kMetricDisconnections =
    GlobalInstrumentsRegistry::RegisterUInt64Counter(
        "grpc.lb.pick_first.disconnections",
        "EXPERIMENTAL.  Number of times the selected subchannel becomes "
        "disconnected.",
        "{disconnection}", false)
        .Labels(kMetricLabelTarget)
        .Build();

const auto kMetricConnectionAttemptsSucceeded =
    GlobalInstrumentsRegistry::RegisterUInt64Counter(
        "grpc.lb.pick_first.connection_attempts_succeeded",
        "EXPERIMENTAL.  Number of successful connection attempts.", "{attempt}",
        false)
        .Labels(kMetricLabelTarget)
        .Build();

const auto kMetricConnectionAttemptsFailed =
    GlobalInstrumentsRegistry::RegisterUInt64Counter(
        "grpc.lb.pick_first.connection_attempts_failed",
        "EXPERIMENTAL.  Number of failed connection attempts.", "{attempt}",
        false)
        .Labels(kMetricLabelTarget)
        .Build();

class PickFirstConfig final : public LoadBalancingPolicy::Config {
 public:
  absl::string_view name() const override { return kPickFirst; }
  bool shuffle_addresses() const { return shuffle_addresses_; }

  static const JsonLoaderInterface* JsonLoader(const JsonArgs&) {
    static const auto kJsonLoader =
        JsonObjectLoader<PickFirstConfig>()
            .OptionalField("shuffleAddressList",
                           &PickFirstConfig::shuffle_addresses_)
            .Finish();
    return kJsonLoader;
  }

 private:
  bool shuffle_addresses_ = false;
};

class PickFirst final : public LoadBalancingPolicy {
 public:
  explicit PickFirst(Args args);

  absl::string_view name() const override { return kPickFirst; }

  absl::Status UpdateLocked(UpdateArgs args) override;
  void ExitIdleLocked() override;
  void ResetBackoffLocked() override;

 private:
  ~PickFirst() override;

  class SubchannelList final : public InternallyRefCounted<SubchannelList> {
   public:

    class SubchannelData final {
     public:

      class SubchannelState final
          : public InternallyRefCounted<SubchannelState> {
       public:
        SubchannelState(SubchannelData* subchannel_data,
                        RefCountedPtr<SubchannelInterface> subchannel);

        void Orphan() override;

        SubchannelInterface* subchannel() const { return subchannel_.get(); }

        void RequestConnection() { subchannel_->RequestConnection(); }

        void ResetBackoffLocked() { subchannel_->ResetBackoff(); }

       private:

        class Watcher
            : public SubchannelInterface::ConnectivityStateWatcherInterface {
         public:
          explicit Watcher(RefCountedPtr<SubchannelState> subchannel_state)
              : subchannel_state_(std::move(subchannel_state)) {}

          ~Watcher() override {
            subchannel_state_.reset(DEBUG_LOCATION, "Watcher dtor");
          }

          void OnConnectivityStateChange(grpc_connectivity_state new_state,
                                         absl::Status status) override {
            subchannel_state_->OnConnectivityStateChange(new_state,
                                                         std::move(status));
          }

          grpc_pollset_set* interested_parties() override {
            return subchannel_state_->pick_first_->interested_parties();
          }

         private:
          RefCountedPtr<SubchannelState> subchannel_state_;
        };

        void Select();

        void OnConnectivityStateChange(grpc_connectivity_state new_state,
                                       absl::Status status);

        SubchannelData* subchannel_data_;

        RefCountedPtr<PickFirst> pick_first_;

        RefCountedPtr<SubchannelInterface> subchannel_;
        SubchannelInterface::ConnectivityStateWatcherInterface* watcher_ =
            nullptr;
      };

      SubchannelData(SubchannelList* subchannel_list, size_t index,
                     RefCountedPtr<SubchannelInterface> subchannel);

      std::optional<grpc_connectivity_state> connectivity_state() const {
        return connectivity_state_;
      }
      const absl::Status& connectivity_status() const {
        return connectivity_status_;
      }

      void RequestConnection() { subchannel_state_->RequestConnection(); }

      void ResetBackoffLocked() { subchannel_state_->ResetBackoffLocked(); }

      void RequestConnectionWithTimer();

      bool seen_transient_failure() const { return seen_transient_failure_; }
      void set_seen_transient_failure() { seen_transient_failure_ = true; }

     private:

      void OnConnectivityStateChange(grpc_connectivity_state new_state,
                                     absl::Status status);

      SubchannelList* subchannel_list_;

      const size_t index_;

      OrphanablePtr<SubchannelState> subchannel_state_;

      std::optional<grpc_connectivity_state> connectivity_state_;
      absl::Status connectivity_status_;
      bool seen_transient_failure_ = false;
    };

    SubchannelList(RefCountedPtr<PickFirst> policy,
                   EndpointAddressesIterator* addresses,
                   const ChannelArgs& args, absl::string_view resolution_note);

    ~SubchannelList() override;

    void Orphan() override;

    size_t size() const { return subchannels_.size(); }

    void ResetBackoffLocked();

    bool IsHappyEyeballsPassComplete() const {

      if (attempting_index_ < size()) return false;
      for (const auto& sd : subchannels_) {
        if (!sd->seen_transient_failure()) return false;
      }
      return true;
    }

    void ReportTransientFailure(absl::Status status);

   private:

    bool AllSubchannelsSeenInitialState() const {
      return num_subchannels_seen_initial_notification_ == size();
    }

    void StartConnectingNextSubchannel();

    void MaybeFinishHappyEyeballsPass();

    RefCountedPtr<PickFirst> policy_;

    ChannelArgs args_;
    std::string resolution_note_;

    std::vector<std::unique_ptr<SubchannelData>> subchannels_;

    bool shutting_down_ = false;

    size_t num_subchannels_seen_initial_notification_ = 0;

    size_t attempting_index_ = 0;

    std::optional<grpc_event_engine::experimental::EventEngine::TaskHandle>
        timer_handle_;

    size_t num_failures_ = 0;

    absl::Status last_failure_;
  };

  class HealthWatcher final
      : public SubchannelInterface::ConnectivityStateWatcherInterface {
   public:
    HealthWatcher(RefCountedPtr<PickFirst> policy,
                  absl::string_view resolution_note)
        : policy_(std::move(policy)), resolution_note_(resolution_note) {}

    ~HealthWatcher() override {
      policy_.reset(DEBUG_LOCATION, "HealthWatcher dtor");
    }

    void OnConnectivityStateChange(grpc_connectivity_state new_state,
                                   absl::Status status) override;

    grpc_pollset_set* interested_parties() override {
      return policy_->interested_parties();
    }

   private:
    RefCountedPtr<PickFirst> policy_;
    std::string resolution_note_;
  };

  class Picker final : public SubchannelPicker {
   public:
    explicit Picker(RefCountedPtr<SubchannelInterface> subchannel)
        : subchannel_(std::move(subchannel)) {}

    PickResult Pick(PickArgs ) override {
      return PickResult::Complete(subchannel_);
    }

   private:
    RefCountedPtr<SubchannelInterface> subchannel_;
  };

  void ShutdownLocked() override;

  void UpdateState(grpc_connectivity_state state, const absl::Status& status,
                   RefCountedPtr<SubchannelPicker> picker);

  void AttemptToConnectUsingLatestUpdateArgsLocked();

  void UnsetSelectedSubchannel();

  void GoIdle();

  bool IsIdle() const {
    return state_ == GRPC_CHANNEL_IDLE && subchannel_list_ == nullptr;
  }

  const bool enable_health_watch_;

  const bool omit_status_message_prefix_;

  const Duration connection_attempt_delay_;

  UpdateArgs latest_update_args_;

  OrphanablePtr<SubchannelList> subchannel_list_;

  OrphanablePtr<SubchannelList::SubchannelData::SubchannelState> selected_;

  SubchannelInterface::ConnectivityStateWatcherInterface* health_watcher_ =
      nullptr;
  SubchannelInterface::DataWatcherInterface* health_data_watcher_ = nullptr;

  grpc_connectivity_state state_ = GRPC_CHANNEL_CONNECTING;

  bool shutdown_ = false;
};

PickFirst::PickFirst(Args args)
    : LoadBalancingPolicy(std::move(args)),
      enable_health_watch_(
          channel_args()
              .GetBool(GRPC_ARG_INTERNAL_PICK_FIRST_ENABLE_HEALTH_CHECKING)
              .value_or(false)),
      omit_status_message_prefix_(
          channel_args()
              .GetBool(GRPC_ARG_INTERNAL_PICK_FIRST_OMIT_STATUS_MESSAGE_PREFIX)
              .value_or(false)),
      connection_attempt_delay_(Duration::Milliseconds(
          Clamp(channel_args()
                    .GetInt(GRPC_ARG_HAPPY_EYEBALLS_CONNECTION_ATTEMPT_DELAY_MS)
                    .value_or(250),
                100, 2000))) {
  GRPC_TRACE_LOG(pick_first, INFO) << "Pick First " << this << " created.";
}

PickFirst::~PickFirst() {
  GRPC_TRACE_LOG(pick_first, INFO) << "Destroying Pick First " << this;
  CHECK_EQ(subchannel_list_.get(), nullptr);
}

void PickFirst::ShutdownLocked() {
  GRPC_TRACE_LOG(pick_first, INFO) << "Pick First " << this << " Shutting down";
  shutdown_ = true;
  UnsetSelectedSubchannel();
  subchannel_list_.reset();
}

void PickFirst::ExitIdleLocked() {
  if (shutdown_) return;
  if (IsIdle()) {
    GRPC_TRACE_LOG(pick_first, INFO)
        << "Pick First " << this << " exiting idle";
    AttemptToConnectUsingLatestUpdateArgsLocked();
  }
}

void PickFirst::ResetBackoffLocked() {
  if (subchannel_list_ != nullptr) subchannel_list_->ResetBackoffLocked();
}

void PickFirst::AttemptToConnectUsingLatestUpdateArgsLocked() {

  EndpointAddressesIterator* addresses = nullptr;
  if (latest_update_args_.addresses.ok()) {
    addresses = latest_update_args_.addresses->get();
  }

  if (GRPC_TRACE_FLAG_ENABLED(pick_first) && subchannel_list_ != nullptr) {
    LOG(INFO) << "[PF " << this << "] Shutting down previous subchannel list "
              << subchannel_list_.get();
  }
  subchannel_list_ = MakeOrphanable<SubchannelList>(
      RefAsSubclass<PickFirst>(DEBUG_LOCATION, "SubchannelList"), addresses,
      latest_update_args_.args, latest_update_args_.resolution_note);

  if (subchannel_list_->size() == 0) {
    channel_control_helper()->RequestReresolution();
    absl::Status status = latest_update_args_.addresses.ok()
                              ? absl::UnavailableError("empty address list")
                              : latest_update_args_.addresses.status();
    subchannel_list_->ReportTransientFailure(std::move(status));
    UnsetSelectedSubchannel();
  }
}

absl::string_view GetAddressFamily(const grpc_resolved_address& address) {
  const char* uri_scheme = grpc_sockaddr_get_uri_scheme(&address);
  return absl::string_view(uri_scheme == nullptr ? "other" : uri_scheme);
};

class AddressFamilyIterator final {
 public:
  AddressFamilyIterator(absl::string_view scheme, size_t index)
      : scheme_(scheme), index_(index) {}

  EndpointAddresses* Next(EndpointAddressesList& endpoints,
                          std::vector<bool>* endpoints_moved) {
    for (; index_ < endpoints.size(); ++index_) {
      if (!(*endpoints_moved)[index_] &&
          GetAddressFamily(endpoints[index_].address()) == scheme_) {
        (*endpoints_moved)[index_] = true;
        return &endpoints[index_++];
      }
    }
    return nullptr;
  }

 private:
  absl::string_view scheme_;
  size_t index_;
};

absl::Status PickFirst::UpdateLocked(UpdateArgs args) {
  if (GRPC_TRACE_FLAG_ENABLED(pick_first)) {
    if (args.addresses.ok()) {
      LOG(INFO) << "Pick First " << this << " received update";
    } else {
      LOG(INFO) << "Pick First " << this
                << " received update with address error: "
                << args.addresses.status();
    }
  }

  absl::Status status;
  if (!args.addresses.ok()) {
    status = args.addresses.status();
  } else {
    EndpointAddressesList endpoints;
    (*args.addresses)->ForEach([&](const EndpointAddresses& endpoint) {
      endpoints.push_back(endpoint);
    });
    if (endpoints.empty()) {
      status = absl::UnavailableError("address list must not be empty");
    } else {

      auto config = static_cast<PickFirstConfig*>(args.config.get());
      if (config->shuffle_addresses()) {
        SharedBitGen g;
        absl::c_shuffle(endpoints, g);
      }

      std::set<absl::string_view> address_families;
      std::vector<AddressFamilyIterator> address_family_order;
      EndpointAddressesList flattened_endpoints;
      for (const auto& endpoint : endpoints) {
        for (const auto& address : endpoint.addresses()) {
          flattened_endpoints.emplace_back(address, endpoint.args());
          absl::string_view scheme = GetAddressFamily(address);
          bool inserted = address_families.insert(scheme).second;
          if (inserted) {
            address_family_order.emplace_back(scheme,
                                              flattened_endpoints.size() - 1);
          }
        }
      }
      endpoints = std::move(flattened_endpoints);

      EndpointAddressesList interleaved_endpoints;
      interleaved_endpoints.reserve(endpoints.size());
      std::vector<bool> endpoints_moved(endpoints.size());
      size_t scheme_index = 0;
      for (size_t i = 0; i < endpoints.size(); ++i) {
        EndpointAddresses* endpoint;
        do {
          auto& iterator = address_family_order[scheme_index++ %
                                                address_family_order.size()];
          endpoint = iterator.Next(endpoints, &endpoints_moved);
        } while (endpoint == nullptr);
        interleaved_endpoints.emplace_back(std::move(*endpoint));
      }
      endpoints = std::move(interleaved_endpoints);
      args.addresses =
          std::make_shared<EndpointAddressesListIterator>(std::move(endpoints));
    }
  }

  if (!args.addresses.ok() && latest_update_args_.config != nullptr) {
    args.addresses = std::move(latest_update_args_.addresses);
  }

  latest_update_args_ = std::move(args);

  if (!IsIdle()) {
    AttemptToConnectUsingLatestUpdateArgsLocked();
  }
  return status;
}

void PickFirst::UpdateState(grpc_connectivity_state state,
                            const absl::Status& status,
                            RefCountedPtr<SubchannelPicker> picker) {
  state_ = state;
  channel_control_helper()->UpdateState(state, status, std::move(picker));
}

void PickFirst::UnsetSelectedSubchannel() {
  if (selected_ != nullptr && health_data_watcher_ != nullptr) {
    selected_->subchannel()->CancelDataWatcher(health_data_watcher_);
  }
  selected_.reset();
  health_watcher_ = nullptr;
  health_data_watcher_ = nullptr;
}

void PickFirst::GoIdle() {

  UnsetSelectedSubchannel();

  subchannel_list_.reset();

  channel_control_helper()->RequestReresolution();

  UpdateState(GRPC_CHANNEL_IDLE, absl::OkStatus(),
              MakeRefCounted<QueuePicker>(Ref(DEBUG_LOCATION, "QueuePicker")));
}

void PickFirst::HealthWatcher::OnConnectivityStateChange(
    grpc_connectivity_state new_state, absl::Status status) {
  if (policy_->health_watcher_ != this) return;
  GRPC_TRACE_LOG(pick_first, INFO)
      << "[PF " << policy_.get()
      << "] health watch state update: " << ConnectivityStateName(new_state)
      << " (" << status << ")";
  switch (new_state) {
    case GRPC_CHANNEL_READY:
      policy_->channel_control_helper()->UpdateState(
          GRPC_CHANNEL_READY, absl::OkStatus(),
          MakeRefCounted<Picker>(policy_->selected_->subchannel()->Ref()));
      break;
    case GRPC_CHANNEL_IDLE:

      break;
    case GRPC_CHANNEL_CONNECTING:
      policy_->channel_control_helper()->UpdateState(
          new_state, absl::OkStatus(),
          MakeRefCounted<QueuePicker>(policy_->Ref()));
      break;
    case GRPC_CHANNEL_TRANSIENT_FAILURE: {
      std::string message = absl::StrCat("health watch: ", status.message());
      if (!resolution_note_.empty()) {
        absl::StrAppend(&message, " (", resolution_note_, ")");
      }
      policy_->channel_control_helper()->UpdateState(
          GRPC_CHANNEL_TRANSIENT_FAILURE, status,
          MakeRefCounted<TransientFailurePicker>(
              absl::UnavailableError(message)));
      break;
    }
    case GRPC_CHANNEL_SHUTDOWN:
      Crash("health watcher reported state SHUTDOWN");
  }
}

PickFirst::SubchannelList::SubchannelData::SubchannelState::SubchannelState(
    SubchannelData* subchannel_data,
    RefCountedPtr<SubchannelInterface> subchannel)
    : subchannel_data_(subchannel_data),
      pick_first_(subchannel_data_->subchannel_list_->policy_),
      subchannel_(std::move(subchannel)) {
  GRPC_TRACE_LOG(pick_first, INFO)
      << "[PF " << pick_first_.get() << "] subchannel state " << this
      << " (subchannel " << subchannel_.get() << "): starting watch";
  auto watcher = std::make_unique<Watcher>(Ref(DEBUG_LOCATION, "Watcher"));
  watcher_ = watcher.get();
  subchannel_->WatchConnectivityState(std::move(watcher));
}

void PickFirst::SubchannelList::SubchannelData::SubchannelState::Orphan() {
  GRPC_TRACE_LOG(pick_first, INFO)
      << "[PF " << pick_first_.get() << "] subchannel state " << this
      << " (subchannel " << subchannel_.get()
      << "): cancelling watch and unreffing subchannel";
  subchannel_data_ = nullptr;
  subchannel_->CancelConnectivityStateWatch(watcher_);
  watcher_ = nullptr;
  subchannel_.reset();
  pick_first_.reset();
  Unref();
}

void PickFirst::SubchannelList::SubchannelData::SubchannelState::Select() {
  GRPC_TRACE_LOG(pick_first, INFO)
      << "Pick First " << pick_first_.get() << " selected subchannel "
      << subchannel_.get();
  CHECK_NE(subchannel_data_, nullptr);
  pick_first_->UnsetSelectedSubchannel();
  pick_first_->selected_ = std::move(subchannel_data_->subchannel_state_);

  if (pick_first_->enable_health_watch_) {
    GRPC_TRACE_LOG(pick_first, INFO)
        << "[PF " << pick_first_.get() << "] starting health watch";
    auto watcher = std::make_unique<HealthWatcher>(
        pick_first_.Ref(DEBUG_LOCATION, "HealthWatcher"),
        subchannel_data_->subchannel_list_->resolution_note_);
    pick_first_->health_watcher_ = watcher.get();
    auto health_data_watcher = MakeHealthCheckWatcher(
        pick_first_->work_serializer(),
        subchannel_data_->subchannel_list_->args_, std::move(watcher));
    pick_first_->health_data_watcher_ = health_data_watcher.get();
    subchannel_->AddDataWatcher(std::move(health_data_watcher));
  } else {
    pick_first_->UpdateState(GRPC_CHANNEL_READY, absl::OkStatus(),
                             MakeRefCounted<Picker>(subchannel_));
  }

  if (subchannel_data_->connectivity_state_ == GRPC_CHANNEL_CONNECTING) {
    auto& stats_plugins =
        pick_first_->channel_control_helper()->GetStatsPluginGroup();
    stats_plugins.AddCounter(
        kMetricConnectionAttemptsSucceeded, 1,
        {pick_first_->channel_control_helper()->GetTarget()}, {});
  }

  subchannel_data_ = nullptr;

  pick_first_->subchannel_list_.reset();
}

void PickFirst::SubchannelList::SubchannelData::SubchannelState::
    OnConnectivityStateChange(grpc_connectivity_state new_state,
                              absl::Status status) {
  if (watcher_ == nullptr) return;
  GRPC_TRACE_LOG(pick_first, INFO)
      << "[PF " << pick_first_.get() << "] subchannel state " << this
      << " (subchannel " << subchannel_.get()
      << "): connectivity changed: new_state="
      << ConnectivityStateName(new_state) << ", status=" << status
      << ", watcher=" << watcher_ << ", subchannel_data_=" << subchannel_data_
      << ", pick_first_->selected_=" << pick_first_->selected_.get();

  if (subchannel_data_ != nullptr) {
    CHECK_EQ(pick_first_->subchannel_list_.get(),
             subchannel_data_->subchannel_list_);

    if (new_state == GRPC_CHANNEL_READY) {
      Select();
    } else {
      subchannel_data_->OnConnectivityStateChange(new_state, std::move(status));
    }
    return;
  }

  CHECK_EQ(pick_first_->selected_.get(), this);
  GRPC_TRACE_LOG(pick_first, INFO)
      << "Pick First " << pick_first_.get()
      << " selected subchannel connectivity changed to "
      << ConnectivityStateName(new_state);

  auto& stats_plugins =
      pick_first_->channel_control_helper()->GetStatsPluginGroup();
  stats_plugins.AddCounter(kMetricDisconnections, 1,
                           {pick_first_->channel_control_helper()->GetTarget()},
                           {});

  pick_first_->GoIdle();
}

PickFirst::SubchannelList::SubchannelData::SubchannelData(
    SubchannelList* subchannel_list, size_t index,
    RefCountedPtr<SubchannelInterface> subchannel)
    : subchannel_list_(subchannel_list), index_(index) {
  GRPC_TRACE_LOG(pick_first, INFO)
      << "[PF " << subchannel_list_->policy_.get() << "] subchannel list "
      << subchannel_list_ << " index " << index_
      << ": creating subchannel data";
  subchannel_state_ =
      MakeOrphanable<SubchannelState>(this, std::move(subchannel));
}

void PickFirst::SubchannelList::SubchannelData::OnConnectivityStateChange(
    grpc_connectivity_state new_state, absl::Status status) {
  PickFirst* p = subchannel_list_->policy_.get();
  GRPC_TRACE_LOG(pick_first, INFO)
      << "[PF " << p << "] subchannel list " << subchannel_list_ << " index "
      << index_ << " of " << subchannel_list_->size() << " (subchannel_state "
      << subchannel_state_.get() << "): connectivity changed: old_state="
      << (connectivity_state_.has_value()
              ? ConnectivityStateName(*connectivity_state_)
              : "N/A")
      << ", new_state=" << ConnectivityStateName(new_state)
      << ", status=" << status
      << ", seen_transient_failure=" << seen_transient_failure_
      << ", p->selected_=" << p->selected_.get()
      << ", p->subchannel_list_=" << p->subchannel_list_.get()
      << ", p->subchannel_list_->shutting_down_="
      << p->subchannel_list_->shutting_down_;
  if (subchannel_list_->shutting_down_) return;

  CHECK_EQ(subchannel_list_, p->subchannel_list_.get());

  CHECK_NE(new_state, GRPC_CHANNEL_SHUTDOWN);

  CHECK_NE(new_state, GRPC_CHANNEL_READY);

  std::optional<grpc_connectivity_state> old_state = connectivity_state_;
  connectivity_state_ = new_state;
  connectivity_status_ = std::move(status);

  if (new_state == GRPC_CHANNEL_TRANSIENT_FAILURE) {
    subchannel_list_->last_failure_ = connectivity_status_;
  }

  if (!old_state.has_value()) {
    ++subchannel_list_->num_subchannels_seen_initial_notification_;
  }

  if (!subchannel_list_->AllSubchannelsSeenInitialState()) return;

  if (!old_state.has_value()) {

    if (p->selected_ != nullptr) {
      GRPC_TRACE_LOG(pick_first, INFO)
          << "[PF " << p << "] subchannel list " << subchannel_list_
          << ": new update has no subchannels in state READY; dropping "
             "existing connection and going IDLE";
      p->GoIdle();
    } else {

      subchannel_list_->StartConnectingNextSubchannel();
    }
    return;
  }

  if (new_state == GRPC_CHANNEL_TRANSIENT_FAILURE) {
    auto& stats_plugins = subchannel_list_->policy_->channel_control_helper()
                              ->GetStatsPluginGroup();
    stats_plugins.AddCounter(
        kMetricConnectionAttemptsFailed, 1,
        {subchannel_list_->policy_->channel_control_helper()->GetTarget()}, {});
  }

  switch (*connectivity_state_) {
    case GRPC_CHANNEL_TRANSIENT_FAILURE: {
      bool prev_seen_transient_failure =
          std::exchange(seen_transient_failure_, true);

      if (!prev_seen_transient_failure && seen_transient_failure_) {

        if (index_ == subchannel_list_->attempting_index_) {
          if (subchannel_list_->timer_handle_.has_value()) {
            p->channel_control_helper()->GetEventEngine()->Cancel(
                *subchannel_list_->timer_handle_);
          }
          ++subchannel_list_->attempting_index_;
          subchannel_list_->StartConnectingNextSubchannel();
        } else {

          subchannel_list_->MaybeFinishHappyEyeballsPass();
        }
      } else if (subchannel_list_->IsHappyEyeballsPassComplete()) {

        ++subchannel_list_->num_failures_;
        if (subchannel_list_->num_failures_ % subchannel_list_->size() == 0) {
          p->channel_control_helper()->RequestReresolution();
          status = absl::UnavailableError(absl::StrCat(
              (p->omit_status_message_prefix_
                   ? ""
                   : "failed to connect to all addresses; last error: "),
              connectivity_status_.ToString()));
          subchannel_list_->ReportTransientFailure(std::move(status));
        }
      }
      break;
    }
    case GRPC_CHANNEL_IDLE:

      if (subchannel_list_->IsHappyEyeballsPassComplete()) {
        subchannel_state_->RequestConnection();
      }
      break;
    case GRPC_CHANNEL_CONNECTING:

      if (p->state_ != GRPC_CHANNEL_TRANSIENT_FAILURE) {
        p->UpdateState(GRPC_CHANNEL_CONNECTING, absl::OkStatus(),
                       MakeRefCounted<QueuePicker>(nullptr));
      }
      break;
    default:

      GPR_UNREACHABLE_CODE(break);
  }
}

void PickFirst::SubchannelList::SubchannelData::RequestConnectionWithTimer() {
  CHECK(connectivity_state_.has_value());
  if (connectivity_state_ == GRPC_CHANNEL_IDLE) {
    subchannel_state_->RequestConnection();
  } else {
    CHECK_EQ(connectivity_state_.value(), GRPC_CHANNEL_CONNECTING);
  }

  if (index_ != subchannel_list_->size() - 1) {
    PickFirst* p = subchannel_list_->policy_.get();
    GRPC_TRACE_LOG(pick_first, INFO)
        << "Pick First " << p << " subchannel list " << subchannel_list_
        << ": starting Connection Attempt Delay timer for "
        << p->connection_attempt_delay_.millis() << "ms for index " << index_;
    subchannel_list_->timer_handle_ =
        p->channel_control_helper()->GetEventEngine()->RunAfter(
            p->connection_attempt_delay_,
            [subchannel_list =
                 subchannel_list_->Ref(DEBUG_LOCATION, "timer")]() mutable {
              ExecCtx exec_ctx;
              auto* sl = subchannel_list.get();
              sl->policy_->work_serializer()->Run(
                  [subchannel_list = std::move(subchannel_list)]() {
                    GRPC_TRACE_LOG(pick_first, INFO)
                        << "Pick First " << subchannel_list->policy_.get()
                        << " subchannel list " << subchannel_list.get()
                        << ": Connection Attempt Delay timer fired "
                           "(shutting_down="
                        << subchannel_list->shutting_down_ << ", selected="
                        << subchannel_list->policy_->selected_.get() << ")";
                    if (subchannel_list->shutting_down_) return;
                    if (subchannel_list->policy_->selected_ != nullptr) return;
                    ++subchannel_list->attempting_index_;
                    subchannel_list->StartConnectingNextSubchannel();
                  });
            });
  }
}

PickFirst::SubchannelList::SubchannelList(RefCountedPtr<PickFirst> policy,
                                          EndpointAddressesIterator* addresses,
                                          const ChannelArgs& args,
                                          absl::string_view resolution_note)
    : InternallyRefCounted<SubchannelList>(
          GRPC_TRACE_FLAG_ENABLED(pick_first) ? "SubchannelList" : nullptr),
      policy_(std::move(policy)),
      args_(
          args.Remove(GRPC_ARG_INTERNAL_PICK_FIRST_ENABLE_HEALTH_CHECKING)
              .Remove(GRPC_ARG_INTERNAL_PICK_FIRST_OMIT_STATUS_MESSAGE_PREFIX)),
      resolution_note_(resolution_note) {
  GRPC_TRACE_LOG(pick_first, INFO)
      << "[PF " << policy_.get() << "] Creating subchannel list " << this
      << " - channel args: " << args_.ToString();
  if (addresses == nullptr) return;

  addresses->ForEach([&](const EndpointAddresses& address) {
    CHECK_EQ(address.addresses().size(), 1u);
    RefCountedPtr<SubchannelInterface> subchannel =
        policy_->channel_control_helper()->CreateSubchannel(
            address.address(), address.args(), args_);
    if (subchannel == nullptr) {

      GRPC_TRACE_LOG(pick_first, INFO)
          << "[PF " << policy_.get()
          << "] could not create subchannel for address " << address.ToString()
          << ", ignoring";
      return;
    }
    GRPC_TRACE_LOG(pick_first, INFO)
        << "[PF " << policy_.get() << "] subchannel list " << this << " index "
        << subchannels_.size() << ": Created subchannel " << subchannel.get()
        << " for address " << address.ToString();
    subchannels_.emplace_back(std::make_unique<SubchannelData>(
        this, subchannels_.size(), std::move(subchannel)));
  });
}

PickFirst::SubchannelList::~SubchannelList() {
  GRPC_TRACE_LOG(pick_first, INFO)
      << "[PF " << policy_.get() << "] Destroying subchannel_list " << this;
}

void PickFirst::SubchannelList::Orphan() {
  GRPC_TRACE_LOG(pick_first, INFO)
      << "[PF " << policy_.get() << "] Shutting down subchannel_list " << this;
  CHECK(!shutting_down_);
  shutting_down_ = true;

  subchannels_.clear();

  if (timer_handle_.has_value()) {
    policy_->channel_control_helper()->GetEventEngine()->Cancel(*timer_handle_);
  }
  Unref();
}

void PickFirst::SubchannelList::ResetBackoffLocked() {
  for (auto& sd : subchannels_) {
    sd->ResetBackoffLocked();
  }
}

void PickFirst::SubchannelList::ReportTransientFailure(absl::Status status) {
  if (!resolution_note_.empty()) {
    status = absl::Status(status.code(), absl::StrCat(status.message(), " (",
                                                      resolution_note_, ")"));
  }
  policy_->UpdateState(GRPC_CHANNEL_TRANSIENT_FAILURE, status,
                       MakeRefCounted<TransientFailurePicker>(status));
}

void PickFirst::SubchannelList::StartConnectingNextSubchannel() {

  for (; attempting_index_ < size(); ++attempting_index_) {
    SubchannelData* sc = subchannels_[attempting_index_].get();
    CHECK(sc->connectivity_state().has_value());
    if (sc->connectivity_state() != GRPC_CHANNEL_TRANSIENT_FAILURE) {

      sc->RequestConnectionWithTimer();
      return;
    }
    sc->set_seen_transient_failure();
  }

  MaybeFinishHappyEyeballsPass();
}

void PickFirst::SubchannelList::MaybeFinishHappyEyeballsPass() {

  if (!IsHappyEyeballsPassComplete()) return;

  GRPC_TRACE_LOG(pick_first, INFO)
      << "Pick First " << policy_.get() << " subchannel list " << this
      << " failed to connect to all subchannels";

  policy_->channel_control_helper()->RequestReresolution();
  absl::Status status = absl::UnavailableError(
      absl::StrCat((policy_->omit_status_message_prefix_
                        ? ""
                        : "failed to connect to all addresses; last error: "),
                   last_failure_.ToString()));
  ReportTransientFailure(std::move(status));

  policy_->UnsetSelectedSubchannel();

  for (auto& sd : subchannels_) {
    if (sd->connectivity_state() == GRPC_CHANNEL_IDLE) {
      sd->RequestConnection();
    }
  }
}

class PickFirstFactory final : public LoadBalancingPolicyFactory {
 public:
  OrphanablePtr<LoadBalancingPolicy> CreateLoadBalancingPolicy(
      LoadBalancingPolicy::Args args) const override {
    return MakeOrphanable<PickFirst>(std::move(args));
  }

  absl::string_view name() const override { return kPickFirst; }

  absl::StatusOr<RefCountedPtr<LoadBalancingPolicy::Config>>
  ParseLoadBalancingConfig(const Json& json) const override {
    return LoadFromJson<RefCountedPtr<PickFirstConfig>>(
        json, JsonArgs(), "errors validating pick_first LB policy config");
  }
};

}

void RegisterPickFirstLbPolicy(CoreConfiguration::Builder* builder) {
  builder->lb_policy_registry()->RegisterLoadBalancingPolicyFactory(
      std::make_unique<PickFirstFactory>());
}

}
