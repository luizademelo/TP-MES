
// Copyright 2018 gRPC authors.

#include "src/core/load_balancing/ring_hash/ring_hash.h"

#include <grpc/impl/channel_arg_names.h>
#include <grpc/impl/connectivity_state.h>
#include <grpc/support/json.h>
#include <grpc/support/port_platform.h>
#include <inttypes.h>
#include <stdlib.h>

#include <algorithm>
#include <cmath>
#include <map>
#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <vector>

#include "absl/base/attributes.h"
#include "absl/container/inlined_vector.h"
#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/random/random.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/string_view.h"
#include "src/core/client_channel/client_channel_internal.h"
#include "src/core/config/core_configuration.h"
#include "src/core/lib/address_utils/sockaddr_utils.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/lib/iomgr/closure.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/lib/iomgr/pollset_set.h"
#include "src/core/lib/iomgr/resolved_address.h"
#include "src/core/lib/transport/connectivity_state.h"
#include "src/core/load_balancing/delegating_helper.h"
#include "src/core/load_balancing/lb_policy.h"
#include "src/core/load_balancing/lb_policy_factory.h"
#include "src/core/load_balancing/lb_policy_registry.h"
#include "src/core/load_balancing/pick_first/pick_first.h"
#include "src/core/resolver/endpoint_addresses.h"
#include "src/core/util/crash.h"
#include "src/core/util/debug_location.h"
#include "src/core/util/env.h"
#include "src/core/util/json/json.h"
#include "src/core/util/orphanable.h"
#include "src/core/util/ref_counted.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/ref_counted_string.h"
#include "src/core/util/unique_type_name.h"
#include "src/core/util/work_serializer.h"
#include "src/core/util/xxhash_inline.h"

namespace grpc_core {

UniqueTypeName RequestHashAttribute::TypeName() {
  static UniqueTypeName::Factory kFactory("request_hash");
  return kFactory.Create();
}

namespace {

constexpr absl::string_view kRingHash = "ring_hash_experimental";

bool XdsRingHashSetRequestHashKeyEnabled() {
  auto value = GetEnv("GRPC_EXPERIMENTAL_RING_HASH_SET_REQUEST_HASH_KEY");
  if (!value.has_value()) return false;
  bool parsed_value;
  bool parse_succeeded = gpr_parse_bool_value(value->c_str(), &parsed_value);
  return parse_succeeded && parsed_value;
}

class RingHashJsonArgs final : public JsonArgs {
 public:
  bool IsEnabled(absl::string_view key) const override {
    if (key == "request_hash_header") {
      return XdsRingHashSetRequestHashKeyEnabled();
    }
    return true;
  }
};

class RingHashLbConfig final : public LoadBalancingPolicy::Config {
 public:
  RingHashLbConfig() = default;

  RingHashLbConfig(const RingHashLbConfig&) = delete;
  RingHashLbConfig& operator=(const RingHashLbConfig&) = delete;

  RingHashLbConfig(RingHashLbConfig&& other) = delete;
  RingHashLbConfig& operator=(RingHashLbConfig&& other) = delete;

  absl::string_view name() const override { return kRingHash; }
  size_t min_ring_size() const { return min_ring_size_; }
  size_t max_ring_size() const { return max_ring_size_; }
  absl::string_view request_hash_header() const { return request_hash_header_; }

  static const JsonLoaderInterface* JsonLoader(const JsonArgs&) {
    static const auto* loader =
        JsonObjectLoader<RingHashLbConfig>()
            .OptionalField("minRingSize", &RingHashLbConfig::min_ring_size_)
            .OptionalField("maxRingSize", &RingHashLbConfig::max_ring_size_)
            .OptionalField("requestHashHeader",
                           &RingHashLbConfig::request_hash_header_,
                           "request_hash_header")
            .Finish();
    return loader;
  }

  void JsonPostLoad(const Json&, const JsonArgs&, ValidationErrors* errors) {
    {
      ValidationErrors::ScopedField field(errors, ".minRingSize");
      if (!errors->FieldHasErrors() &&
          (min_ring_size_ == 0 || min_ring_size_ > 8388608)) {
        errors->AddError("must be in the range [1, 8388608]");
      }
    }
    {
      ValidationErrors::ScopedField field(errors, ".maxRingSize");
      if (!errors->FieldHasErrors() &&
          (max_ring_size_ == 0 || max_ring_size_ > 8388608)) {
        errors->AddError("must be in the range [1, 8388608]");
      }
    }
    if (min_ring_size_ > max_ring_size_) {
      errors->AddError("maxRingSize cannot be smaller than minRingSize");
    }
  }

 private:
  uint64_t min_ring_size_ = 1024;
  uint64_t max_ring_size_ = 4096;
  std::string request_hash_header_;
};

constexpr size_t kRingSizeCapDefault = 4096;

class RingHash final : public LoadBalancingPolicy {
 public:
  explicit RingHash(Args args);

  absl::string_view name() const override { return kRingHash; }

  absl::Status UpdateLocked(UpdateArgs args) override;
  void ResetBackoffLocked() override;

 private:

  class Ring final : public RefCounted<Ring> {
   public:
    struct RingEntry {
      uint64_t hash;
      size_t endpoint_index;
    };

    Ring(RingHash* ring_hash, RingHashLbConfig* config);

    const std::vector<RingEntry>& ring() const { return ring_; }

   private:
    std::vector<RingEntry> ring_;
  };

  class RingHashEndpoint final : public InternallyRefCounted<RingHashEndpoint> {
   public:

    RingHashEndpoint(RefCountedPtr<RingHash> ring_hash, size_t index)
        : ring_hash_(std::move(ring_hash)), index_(index) {}

    void Orphan() override;

    size_t index() const { return index_; }

    absl::Status UpdateLocked(size_t index);

    grpc_connectivity_state connectivity_state() const {
      return connectivity_state_;
    }

    struct EndpointInfo {
      RefCountedPtr<RingHashEndpoint> endpoint;
      RefCountedPtr<SubchannelPicker> picker;
      grpc_connectivity_state state;
      absl::Status status;
    };
    EndpointInfo GetInfoForPicker() {
      return {Ref(), picker_, connectivity_state_, status_};
    }

    void ResetBackoffLocked();

    void RequestConnectionLocked();

   private:
    class Helper;

    void CreateChildPolicy();
    absl::Status UpdateChildPolicyLocked();

    void OnStateUpdate(grpc_connectivity_state new_state,
                       const absl::Status& status,
                       RefCountedPtr<SubchannelPicker> picker);

    RefCountedPtr<RingHash> ring_hash_;
    size_t index_;

    OrphanablePtr<LoadBalancingPolicy> child_policy_;

    grpc_connectivity_state connectivity_state_ = GRPC_CHANNEL_IDLE;
    absl::Status status_;
    RefCountedPtr<SubchannelPicker> picker_;
  };

  class Picker final : public SubchannelPicker {
   public:
    explicit Picker(RefCountedPtr<RingHash> ring_hash)
        : ring_hash_(std::move(ring_hash)),
          ring_(ring_hash_->ring_),
          endpoints_(ring_hash_->endpoints_.size()),
          resolution_note_(ring_hash_->resolution_note_),
          request_hash_header_(ring_hash_->request_hash_header_) {
      for (const auto& [_, endpoint] : ring_hash_->endpoint_map_) {
        endpoints_[endpoint->index()] = endpoint->GetInfoForPicker();
        if (endpoints_[endpoint->index()].state == GRPC_CHANNEL_CONNECTING) {
          has_endpoint_in_connecting_state_ = true;
        }
      }
    }

    PickResult Pick(PickArgs args) override;

   private:

    class EndpointConnectionAttempter final {
     public:
      EndpointConnectionAttempter(RefCountedPtr<RingHash> ring_hash,
                                  RefCountedPtr<RingHashEndpoint> endpoint)
          : ring_hash_(std::move(ring_hash)), endpoint_(std::move(endpoint)) {

        GRPC_CLOSURE_INIT(&closure_, RunInExecCtx, this, nullptr);
        ExecCtx::Run(DEBUG_LOCATION, &closure_, absl::OkStatus());
      }

     private:
      static void RunInExecCtx(void* arg, grpc_error_handle ) {
        auto* self = static_cast<EndpointConnectionAttempter*>(arg);
        self->ring_hash_->work_serializer()->Run([self]() {
          if (!self->ring_hash_->shutdown_) {
            self->endpoint_->RequestConnectionLocked();
          }
          delete self;
        });
      }

      RefCountedPtr<RingHash> ring_hash_;
      RefCountedPtr<RingHashEndpoint> endpoint_;
      grpc_closure closure_;
    };

    RefCountedPtr<RingHash> ring_hash_;
    RefCountedPtr<Ring> ring_;
    std::vector<RingHashEndpoint::EndpointInfo> endpoints_;
    bool has_endpoint_in_connecting_state_ = false;
    std::string resolution_note_;
    RefCountedStringValue request_hash_header_;
  };

  ~RingHash() override;

  void ShutdownLocked() override;

  void UpdateAggregatedConnectivityStateLocked(absl::Status status);

  EndpointAddressesList endpoints_;
  ChannelArgs args_;
  RefCountedStringValue request_hash_header_;
  RefCountedPtr<Ring> ring_;

  std::map<EndpointAddressSet, OrphanablePtr<RingHashEndpoint>> endpoint_map_;
  std::string resolution_note_;

  absl::Status last_failure_;

  bool shutdown_ = false;
};

RingHash::PickResult RingHash::Picker::Pick(PickArgs args) {

  bool using_random_hash = false;
  uint64_t request_hash;
  if (request_hash_header_.as_string_view().empty()) {

    auto* call_state = static_cast<ClientChannelLbCallState*>(args.call_state);
    auto* hash_attribute = call_state->GetCallAttribute<RequestHashAttribute>();
    if (hash_attribute == nullptr) {
      return PickResult::Fail(
          absl::InternalError("hash attribute not present"));
    }
    request_hash = hash_attribute->request_hash();
  } else {
    std::string buffer;
    auto header_value = args.initial_metadata->Lookup(
        request_hash_header_.as_string_view(), &buffer);
    if (header_value.has_value()) {
      request_hash = XXH64(header_value->data(), header_value->size(), 0);
    } else {
      request_hash = absl::Uniform<uint64_t>(absl::BitGen());
      using_random_hash = true;
    }
  }

  const auto& ring = ring_->ring();
  int64_t lowp = 0;
  int64_t highp = ring.size();
  int64_t index = 0;
  while (true) {
    index = (lowp + highp) / 2;
    if (index == static_cast<int64_t>(ring.size())) {
      index = 0;
      break;
    }
    uint64_t midval = ring[index].hash;
    uint64_t midval1 = index == 0 ? 0 : ring[index - 1].hash;
    if (request_hash <= midval && request_hash > midval1) {
      break;
    }
    if (midval < request_hash) {
      lowp = index + 1;
    } else {
      highp = index - 1;
    }
    if (lowp > highp) {
      index = 0;
      break;
    }
  }

  if (!using_random_hash) {
    for (size_t i = 0; i < ring.size(); ++i) {
      const auto& entry = ring[(index + i) % ring.size()];
      const auto& endpoint_info = endpoints_[entry.endpoint_index];
      switch (endpoint_info.state) {
        case GRPC_CHANNEL_READY:
          return endpoint_info.picker->Pick(args);
        case GRPC_CHANNEL_IDLE:
          new EndpointConnectionAttempter(
              ring_hash_.Ref(DEBUG_LOCATION, "EndpointConnectionAttempter"),
              endpoint_info.endpoint);
          [[fallthrough]];
        case GRPC_CHANNEL_CONNECTING:
          return PickResult::Queue();
        default:
          break;
      }
    }
  } else {

    bool requested_connection = has_endpoint_in_connecting_state_;
    for (size_t i = 0; i < ring.size(); ++i) {
      const auto& entry = ring[(index + i) % ring.size()];
      const auto& endpoint_info = endpoints_[entry.endpoint_index];
      if (endpoint_info.state == GRPC_CHANNEL_READY) {
        return endpoint_info.picker->Pick(args);
      }
      if (!requested_connection && endpoint_info.state == GRPC_CHANNEL_IDLE) {
        new EndpointConnectionAttempter(
            ring_hash_.Ref(DEBUG_LOCATION, "EndpointConnectionAttempter"),
            endpoint_info.endpoint);
        requested_connection = true;
      }
    }
    if (requested_connection) return PickResult::Queue();
  }
  std::string message = absl::StrCat(
      "ring hash cannot find a connected endpoint; first failure: ",
      endpoints_[ring[index].endpoint_index].status.message());
  if (!resolution_note_.empty()) {
    absl::StrAppend(&message, " (", resolution_note_, ")");
  }
  return PickResult::Fail(absl::UnavailableError(message));
}

RingHash::Ring::Ring(RingHash* ring_hash, RingHashLbConfig* config) {

  struct EndpointWeight {
    std::string hash_key;

    uint32_t weight = 1;
    double normalized_weight;
  };
  std::vector<EndpointWeight> endpoint_weights;
  size_t sum = 0;
  const EndpointAddressesList& endpoints = ring_hash->endpoints_;
  endpoint_weights.reserve(endpoints.size());
  for (const auto& endpoint : endpoints) {
    EndpointWeight endpoint_weight;
    auto hash_key =
        endpoint.args().GetString(GRPC_ARG_RING_HASH_ENDPOINT_HASH_KEY);
    if (hash_key.has_value()) {
      endpoint_weight.hash_key = std::string(*hash_key);
    } else {
      endpoint_weight.hash_key =
          grpc_sockaddr_to_string(&endpoint.addresses().front(), false).value();
    }

    auto weight_arg = endpoint.args().GetInt(GRPC_ARG_ADDRESS_WEIGHT);
    if (weight_arg.value_or(0) > 0) {
      endpoint_weight.weight = *weight_arg;
    }
    sum += endpoint_weight.weight;
    endpoint_weights.push_back(std::move(endpoint_weight));
  }

  double min_normalized_weight = 1.0;
  double max_normalized_weight = 0.0;
  for (auto& endpoint_weight : endpoint_weights) {
    endpoint_weight.normalized_weight =
        static_cast<double>(endpoint_weight.weight) / sum;
    min_normalized_weight =
        std::min(endpoint_weight.normalized_weight, min_normalized_weight);
    max_normalized_weight =
        std::max(endpoint_weight.normalized_weight, max_normalized_weight);
  }

  const size_t ring_size_cap =
      ring_hash->args_.GetInt(GRPC_ARG_RING_HASH_LB_RING_SIZE_CAP)
          .value_or(kRingSizeCapDefault);
  const size_t min_ring_size = std::min(config->min_ring_size(), ring_size_cap);
  const size_t max_ring_size = std::min(config->max_ring_size(), ring_size_cap);
  const double scale = std::min(
      std::ceil(min_normalized_weight * min_ring_size) / min_normalized_weight,
      static_cast<double>(max_ring_size));

  const uint64_t ring_size = std::ceil(scale);
  ring_.reserve(ring_size);

  absl::InlinedVector<char, 196> hash_key_buffer;
  double current_hashes = 0.0;
  double target_hashes = 0.0;
  uint64_t min_hashes_per_host = ring_size;
  uint64_t max_hashes_per_host = 0;
  for (size_t i = 0; i < endpoints.size(); ++i) {
    const std::string& hash_key = endpoint_weights[i].hash_key;
    hash_key_buffer.assign(hash_key.begin(), hash_key.end());
    hash_key_buffer.emplace_back('_');
    auto offset_start = hash_key_buffer.end();
    target_hashes += scale * endpoint_weights[i].normalized_weight;
    size_t count = 0;
    while (current_hashes < target_hashes) {
      const std::string count_str = absl::StrCat(count);
      hash_key_buffer.insert(offset_start, count_str.begin(), count_str.end());
      absl::string_view hash_key(hash_key_buffer.data(),
                                 hash_key_buffer.size());
      const uint64_t hash = XXH64(hash_key.data(), hash_key.size(), 0);
      ring_.push_back({hash, i});
      ++count;
      ++current_hashes;
      hash_key_buffer.erase(offset_start, hash_key_buffer.end());
    }
    min_hashes_per_host =
        std::min(static_cast<uint64_t>(i), min_hashes_per_host);
    max_hashes_per_host =
        std::max(static_cast<uint64_t>(i), max_hashes_per_host);
  }
  std::sort(ring_.begin(), ring_.end(),
            [](const RingEntry& lhs, const RingEntry& rhs) -> bool {
              return lhs.hash < rhs.hash;
            });
}

class RingHash::RingHashEndpoint::Helper final
    : public LoadBalancingPolicy::DelegatingChannelControlHelper {
 public:
  explicit Helper(RefCountedPtr<RingHashEndpoint> endpoint)
      : endpoint_(std::move(endpoint)) {}

  ~Helper() override { endpoint_.reset(DEBUG_LOCATION, "Helper"); }

  void UpdateState(
      grpc_connectivity_state state, const absl::Status& status,
      RefCountedPtr<LoadBalancingPolicy::SubchannelPicker> picker) override {
    endpoint_->OnStateUpdate(state, status, std::move(picker));
  }

 private:
  LoadBalancingPolicy::ChannelControlHelper* parent_helper() const override {
    return endpoint_->ring_hash_->channel_control_helper();
  }

  RefCountedPtr<RingHashEndpoint> endpoint_;
};

void RingHash::RingHashEndpoint::Orphan() {
  if (child_policy_ != nullptr) {

    grpc_pollset_set_del_pollset_set(child_policy_->interested_parties(),
                                     ring_hash_->interested_parties());
    child_policy_.reset();
    picker_.reset();
  }
  Unref();
}

absl::Status RingHash::RingHashEndpoint::UpdateLocked(size_t index) {
  index_ = index;
  if (child_policy_ == nullptr) return absl::OkStatus();
  return UpdateChildPolicyLocked();
}

void RingHash::RingHashEndpoint::ResetBackoffLocked() {
  if (child_policy_ != nullptr) child_policy_->ResetBackoffLocked();
}

void RingHash::RingHashEndpoint::RequestConnectionLocked() {
  if (child_policy_ == nullptr) {
    CreateChildPolicy();
  } else {
    child_policy_->ExitIdleLocked();
  }
}

void RingHash::RingHashEndpoint::CreateChildPolicy() {
  CHECK(child_policy_ == nullptr);
  LoadBalancingPolicy::Args lb_policy_args;
  lb_policy_args.work_serializer = ring_hash_->work_serializer();
  lb_policy_args.args =
      ring_hash_->args_
          .Set(GRPC_ARG_INTERNAL_PICK_FIRST_ENABLE_HEALTH_CHECKING, true)
          .Set(GRPC_ARG_INTERNAL_PICK_FIRST_OMIT_STATUS_MESSAGE_PREFIX, true);
  lb_policy_args.channel_control_helper =
      std::make_unique<Helper>(Ref(DEBUG_LOCATION, "Helper"));
  child_policy_ =
      CoreConfiguration::Get().lb_policy_registry().CreateLoadBalancingPolicy(
          "pick_first", std::move(lb_policy_args));
  if (GRPC_TRACE_FLAG_ENABLED(ring_hash_lb)) {
    const EndpointAddresses& endpoint = ring_hash_->endpoints_[index_];
    LOG(INFO) << "[RH " << ring_hash_.get() << "] endpoint " << this
              << " (index " << index_ << " of " << ring_hash_->endpoints_.size()
              << ", " << endpoint.ToString() << "): created child policy "
              << child_policy_.get();
  }

  grpc_pollset_set_add_pollset_set(child_policy_->interested_parties(),
                                   ring_hash_->interested_parties());

  absl::Status status = UpdateChildPolicyLocked();
  if (!status.ok()) {
    ring_hash_->channel_control_helper()->RequestReresolution();
  }
}

absl::Status RingHash::RingHashEndpoint::UpdateChildPolicyLocked() {

  auto config =
      CoreConfiguration::Get().lb_policy_registry().ParseLoadBalancingConfig(
          Json::FromArray(
              {Json::FromObject({{"pick_first", Json::FromObject({})}})}));
  CHECK(config.ok());

  LoadBalancingPolicy::UpdateArgs update_args;
  update_args.addresses =
      std::make_shared<SingleEndpointIterator>(ring_hash_->endpoints_[index_]);
  update_args.args = ring_hash_->args_;
  update_args.config = std::move(*config);
  return child_policy_->UpdateLocked(std::move(update_args));
}

void RingHash::RingHashEndpoint::OnStateUpdate(
    grpc_connectivity_state new_state, const absl::Status& status,
    RefCountedPtr<SubchannelPicker> picker) {
  GRPC_TRACE_LOG(ring_hash_lb, INFO)
      << "[RH " << ring_hash_.get() << "] connectivity changed for endpoint "
      << this << " (" << ring_hash_->endpoints_[index_].ToString()
      << ", child_policy=" << child_policy_.get()
      << "): prev_state=" << ConnectivityStateName(connectivity_state_)
      << " new_state=" << ConnectivityStateName(new_state) << " (" << status
      << ")";
  if (child_policy_ == nullptr) return;

  connectivity_state_ = new_state;
  status_ = status;
  picker_ = std::move(picker);

  ring_hash_->UpdateAggregatedConnectivityStateLocked(status);
}

RingHash::RingHash(Args args) : LoadBalancingPolicy(std::move(args)) {
  GRPC_TRACE_LOG(ring_hash_lb, INFO) << "[RH " << this << "] Created";
}

RingHash::~RingHash() {
  GRPC_TRACE_LOG(ring_hash_lb, INFO)
      << "[RH " << this << "] Destroying Ring Hash policy";
}

void RingHash::ShutdownLocked() {
  GRPC_TRACE_LOG(ring_hash_lb, INFO) << "[RH " << this << "] Shutting down";
  shutdown_ = true;
  endpoint_map_.clear();
}

void RingHash::ResetBackoffLocked() {
  for (const auto& [_, endpoint] : endpoint_map_) {
    endpoint->ResetBackoffLocked();
  }
}

absl::Status RingHash::UpdateLocked(UpdateArgs args) {

  if (args.addresses.ok()) {
    GRPC_TRACE_LOG(ring_hash_lb, INFO) << "[RH " << this << "] received update";

    endpoints_.clear();
    std::map<EndpointAddressSet, size_t> endpoint_indices;
    (*args.addresses)->ForEach([&](const EndpointAddresses& endpoint) {
      const EndpointAddressSet key(endpoint.addresses());
      auto [it, inserted] = endpoint_indices.emplace(key, endpoints_.size());
      if (!inserted) {

        EndpointAddresses& prev_endpoint = endpoints_[it->second];
        int weight_arg =
            endpoint.args().GetInt(GRPC_ARG_ADDRESS_WEIGHT).value_or(1);
        int prev_weight_arg =
            prev_endpoint.args().GetInt(GRPC_ARG_ADDRESS_WEIGHT).value_or(1);
        GRPC_TRACE_LOG(ring_hash_lb, INFO)
            << "[RH " << this << "] merging duplicate endpoint for "
            << key.ToString() << ", combined weight "
            << weight_arg + prev_weight_arg;
        prev_endpoint = EndpointAddresses(
            prev_endpoint.addresses(),
            prev_endpoint.args().Set(GRPC_ARG_ADDRESS_WEIGHT,
                                     weight_arg + prev_weight_arg));
      } else {
        endpoints_.push_back(endpoint);
      }
    });
  } else {
    GRPC_TRACE_LOG(ring_hash_lb, INFO)
        << "[RH " << this << "] received update with addresses error: "
        << args.addresses.status();

    if (!endpoints_.empty()) return args.addresses.status();
  }

  args_ = std::move(args.args);

  auto* config = DownCast<RingHashLbConfig*>(args.config.get());
  request_hash_header_ = RefCountedStringValue(config->request_hash_header());

  ring_ = MakeRefCounted<Ring>(this, config);

  std::map<EndpointAddressSet, OrphanablePtr<RingHashEndpoint>> endpoint_map;
  std::vector<std::string> errors;
  for (size_t i = 0; i < endpoints_.size(); ++i) {
    const EndpointAddresses& addresses = endpoints_[i];
    const EndpointAddressSet address_set(addresses.addresses());

    auto it = endpoint_map_.find(address_set);
    if (it != endpoint_map_.end()) {
      absl::Status status = it->second->UpdateLocked(i);
      if (!status.ok()) {
        errors.emplace_back(absl::StrCat("endpoint ", address_set.ToString(),
                                         ": ", status.ToString()));
      }
      endpoint_map.emplace(address_set, std::move(it->second));
    } else {
      endpoint_map.emplace(address_set, MakeOrphanable<RingHashEndpoint>(
                                            RefAsSubclass<RingHash>(), i));
    }
  }
  endpoint_map_ = std::move(endpoint_map);

  resolution_note_ = std::move(args.resolution_note);

  if (endpoints_.empty()) {
    absl::Status status = args.addresses.ok()
                              ? absl::UnavailableError(absl::StrCat(
                                    "empty address list: ", resolution_note_))
                              : args.addresses.status();
    channel_control_helper()->UpdateState(
        GRPC_CHANNEL_TRANSIENT_FAILURE, status,
        MakeRefCounted<TransientFailurePicker>(status));
    return status;
  }

  UpdateAggregatedConnectivityStateLocked(absl::OkStatus());
  if (!errors.empty()) {
    return absl::UnavailableError(absl::StrCat(
        "errors from children: [", absl::StrJoin(errors, "; "), "]"));
  }
  return absl::OkStatus();
}

void RingHash::UpdateAggregatedConnectivityStateLocked(absl::Status status) {

  size_t num_idle = 0;
  size_t num_connecting = 0;
  size_t num_ready = 0;
  size_t num_transient_failure = 0;
  RingHashEndpoint* idle_endpoint = nullptr;
  for (const auto& [_, endpoint] : endpoint_map_) {
    switch (endpoint->connectivity_state()) {
      case GRPC_CHANNEL_READY:
        ++num_ready;
        break;
      case GRPC_CHANNEL_IDLE:
        ++num_idle;
        if (idle_endpoint == nullptr) idle_endpoint = endpoint.get();
        break;
      case GRPC_CHANNEL_CONNECTING:
        ++num_connecting;
        break;
      case GRPC_CHANNEL_TRANSIENT_FAILURE:
        ++num_transient_failure;
        break;
      default:
        Crash("child policy should never report SHUTDOWN");
    }
  }

  grpc_connectivity_state state;
  if (num_ready > 0) {
    state = GRPC_CHANNEL_READY;
  } else if (num_transient_failure >= 2) {
    state = GRPC_CHANNEL_TRANSIENT_FAILURE;
  } else if (num_connecting > 0) {
    state = GRPC_CHANNEL_CONNECTING;
  } else if (num_transient_failure == 1 && endpoints_.size() > 1) {
    state = GRPC_CHANNEL_CONNECTING;
  } else if (num_idle > 0) {
    state = GRPC_CHANNEL_IDLE;
  } else {
    state = GRPC_CHANNEL_TRANSIENT_FAILURE;
  }
  GRPC_TRACE_LOG(ring_hash_lb, INFO)
      << "[RH " << this << "] setting connectivity state to "
      << ConnectivityStateName(state) << " (num_idle=" << num_idle
      << ", num_connecting=" << num_connecting << ", num_ready=" << num_ready
      << ", num_transient_failure=" << num_transient_failure
      << ", size=" << endpoints_.size() << ")";

  if (state == GRPC_CHANNEL_TRANSIENT_FAILURE) {
    if (!status.ok()) {
      last_failure_ = absl::UnavailableError(absl::StrCat(
          "no reachable endpoints; last error: ", status.message()));
    }
    status = last_failure_;
  } else {
    status = absl::OkStatus();
  }

  channel_control_helper()->UpdateState(
      state, status,
      MakeRefCounted<Picker>(
          RefAsSubclass<RingHash>(DEBUG_LOCATION, "RingHashPicker")));

  if ((state == GRPC_CHANNEL_CONNECTING ||
       state == GRPC_CHANNEL_TRANSIENT_FAILURE) &&
      num_connecting == 0 && idle_endpoint != nullptr) {
    GRPC_TRACE_LOG(ring_hash_lb, INFO)
        << "[RH " << this
        << "] triggering internal connection attempt for endpoint "
        << idle_endpoint << " ("
        << endpoints_[idle_endpoint->index()].ToString() << ") (index "
        << idle_endpoint->index() << " of " << endpoints_.size() << ")";
    idle_endpoint->RequestConnectionLocked();
  }
}

class RingHashFactory final : public LoadBalancingPolicyFactory {
 public:
  OrphanablePtr<LoadBalancingPolicy> CreateLoadBalancingPolicy(
      LoadBalancingPolicy::Args args) const override {
    return MakeOrphanable<RingHash>(std::move(args));
  }

  absl::string_view name() const override { return kRingHash; }

  absl::StatusOr<RefCountedPtr<LoadBalancingPolicy::Config>>
  ParseLoadBalancingConfig(const Json& json) const override {
    return LoadFromJson<RefCountedPtr<RingHashLbConfig>>(
        json, RingHashJsonArgs(),
        "errors validating ring_hash LB policy config");
  }
};

}

void RegisterRingHashLbPolicy(CoreConfiguration::Builder* builder) {
  builder->lb_policy_registry()->RegisterLoadBalancingPolicyFactory(
      std::make_unique<RingHashFactory>());
}

}
