// Copyright 2024 The gRPC Authors.

#ifndef GRPC_SRC_CORE_TELEMETRY_METRICS_H
#define GRPC_SRC_CORE_TELEMETRY_METRICS_H

#include <grpc/support/metrics.h>
#include <grpc/support/port_platform.h>

#include <cstdint>
#include <memory>
#include <type_traits>
#include <vector>

#include "absl/functional/any_invocable.h"
#include "absl/functional/function_ref.h"
#include "absl/strings/string_view.h"
#include "absl/types/span.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/slice/slice.h"
#include "src/core/telemetry/call_tracer.h"
#include "src/core/util/no_destruct.h"
#include "src/core/util/sync.h"
#include "src/core/util/time.h"

namespace grpc_core {

constexpr absl::string_view kMetricLabelTarget = "grpc.target";

class GlobalInstrumentsRegistry {
 public:
  enum class ValueType {
    kUndefined,
    kInt64,
    kUInt64,
    kDouble,
  };
  enum class InstrumentType {
    kUndefined,
    kCounter,
    kHistogram,
    kCallbackGauge,
  };
  using InstrumentID = uint32_t;
  struct GlobalInstrumentDescriptor {
    ValueType value_type;
    InstrumentType instrument_type;
    InstrumentID index;
    bool enable_by_default;
    absl::string_view name;
    absl::string_view description;
    absl::string_view unit;
    std::vector<absl::string_view> label_keys;
    std::vector<absl::string_view> optional_label_keys;
  };
  struct GlobalInstrumentHandle {

    InstrumentID index;
  };

  template <ValueType V, InstrumentType I, size_t M, size_t N>
  struct TypedGlobalInstrumentHandle : public GlobalInstrumentHandle {};

  template <ValueType V, InstrumentType I, std::size_t M, std::size_t N>
  class RegistrationBuilder {
   public:
    template <typename... Args>
    RegistrationBuilder<V, I, sizeof...(Args), N> Labels(Args&&... args) {
      return RegistrationBuilder<V, I, sizeof...(Args), N>(
          name_, description_, unit_, enable_by_default_,
          std::array<absl::string_view, sizeof...(Args)>({args...}),
          optional_label_keys_);
    }

    template <typename... Args>
    RegistrationBuilder<V, I, M, sizeof...(Args)> OptionalLabels(
        Args&&... args) {
      return RegistrationBuilder<V, I, M, sizeof...(Args)>(
          name_, description_, unit_, enable_by_default_, label_keys_,
          std::array<absl::string_view, sizeof...(Args)>({args...}));
    }

    TypedGlobalInstrumentHandle<V, I, M, N> Build() {
      TypedGlobalInstrumentHandle<V, I, M, N> handle;
      handle.index = RegisterInstrument(V, I, name_, description_, unit_,
                                        enable_by_default_, label_keys_,
                                        optional_label_keys_);
      return handle;
    }

   private:
    friend class GlobalInstrumentsRegistry;

    RegistrationBuilder(absl::string_view name, absl::string_view description,
                        absl::string_view unit, bool enable_by_default)
        : name_(name),
          description_(description),
          unit_(unit),
          enable_by_default_(enable_by_default) {}

    RegistrationBuilder(absl::string_view name, absl::string_view description,
                        absl::string_view unit, bool enable_by_default,
                        std::array<absl::string_view, M> label_keys,
                        std::array<absl::string_view, N> optional_label_keys)
        : name_(name),
          description_(description),
          unit_(unit),
          enable_by_default_(enable_by_default),
          label_keys_(std::move(label_keys)),
          optional_label_keys_(std::move(optional_label_keys)) {}

    absl::string_view name_;
    absl::string_view description_;
    absl::string_view unit_;
    bool enable_by_default_;
    std::array<absl::string_view, M> label_keys_;
    std::array<absl::string_view, N> optional_label_keys_;
  };

  static RegistrationBuilder<ValueType::kUInt64, InstrumentType::kCounter, 0, 0>
  RegisterUInt64Counter(absl::string_view name, absl::string_view description,
                        absl::string_view unit, bool enable_by_default) {
    return RegistrationBuilder<ValueType::kUInt64, InstrumentType::kCounter, 0,
                               0>(name, description, unit, enable_by_default);
  }
  static RegistrationBuilder<ValueType::kDouble, InstrumentType::kCounter, 0, 0>
  RegisterDoubleCounter(absl::string_view name, absl::string_view description,
                        absl::string_view unit, bool enable_by_default) {
    return RegistrationBuilder<ValueType::kDouble, InstrumentType::kCounter, 0,
                               0>(name, description, unit, enable_by_default);
  }
  static RegistrationBuilder<ValueType::kUInt64, InstrumentType::kHistogram, 0,
                             0>
  RegisterUInt64Histogram(absl::string_view name, absl::string_view description,
                          absl::string_view unit, bool enable_by_default) {
    return RegistrationBuilder<ValueType::kUInt64, InstrumentType::kHistogram,
                               0, 0>(name, description, unit,
                                     enable_by_default);
  }
  static RegistrationBuilder<ValueType::kDouble, InstrumentType::kHistogram, 0,
                             0>
  RegisterDoubleHistogram(absl::string_view name, absl::string_view description,
                          absl::string_view unit, bool enable_by_default) {
    return RegistrationBuilder<ValueType::kDouble, InstrumentType::kHistogram,
                               0, 0>(name, description, unit,
                                     enable_by_default);
  }
  static RegistrationBuilder<ValueType::kInt64, InstrumentType::kCallbackGauge,
                             0, 0>
  RegisterCallbackInt64Gauge(absl::string_view name,
                             absl::string_view description,
                             absl::string_view unit, bool enable_by_default) {
    return RegistrationBuilder<ValueType::kInt64,
                               InstrumentType::kCallbackGauge, 0, 0>(
        name, description, unit, enable_by_default);
  }
  static RegistrationBuilder<ValueType::kDouble, InstrumentType::kCallbackGauge,
                             0, 0>
  RegisterCallbackDoubleGauge(absl::string_view name,
                              absl::string_view description,
                              absl::string_view unit, bool enable_by_default) {
    return RegistrationBuilder<ValueType::kDouble,
                               InstrumentType::kCallbackGauge, 0, 0>(
        name, description, unit, enable_by_default);
  }

  static void ForEach(
      absl::FunctionRef<void(const GlobalInstrumentDescriptor&)> f);
  static const GlobalInstrumentDescriptor& GetInstrumentDescriptor(
      GlobalInstrumentHandle handle);
  static std::optional<GlobalInstrumentsRegistry::GlobalInstrumentHandle>
  FindInstrumentByName(absl::string_view name);

 private:
  friend class GlobalInstrumentsRegistryTestPeer;

  GlobalInstrumentsRegistry() = delete;

  static std::vector<GlobalInstrumentsRegistry::GlobalInstrumentDescriptor>&
  GetInstrumentList();
  static InstrumentID RegisterInstrument(
      ValueType value_type, InstrumentType instrument_type,
      absl::string_view name, absl::string_view description,
      absl::string_view unit, bool enable_by_default,
      absl::Span<const absl::string_view> label_keys,
      absl::Span<const absl::string_view> optional_label_keys);
};

class CallbackMetricReporter {
 public:
  virtual ~CallbackMetricReporter() = default;

  template <std::size_t M, std::size_t N>
  void Report(
      GlobalInstrumentsRegistry::TypedGlobalInstrumentHandle<
          GlobalInstrumentsRegistry::ValueType::kInt64,
          GlobalInstrumentsRegistry::InstrumentType::kCallbackGauge, M, N>
          handle,
      int64_t value, std::array<absl::string_view, M> label_values,
      std::array<absl::string_view, N> optional_values) {
    ReportInt64(handle, value, label_values, optional_values);
  }
  template <std::size_t M, std::size_t N>
  void Report(
      GlobalInstrumentsRegistry::TypedGlobalInstrumentHandle<
          GlobalInstrumentsRegistry::ValueType::kDouble,
          GlobalInstrumentsRegistry::InstrumentType::kCallbackGauge, M, N>
          handle,
      double value, std::array<absl::string_view, M> label_values,
      std::array<absl::string_view, N> optional_values) {
    ReportDouble(handle, value, label_values, optional_values);
  }

 private:
  virtual void ReportInt64(
      GlobalInstrumentsRegistry::GlobalInstrumentHandle handle, int64_t value,
      absl::Span<const absl::string_view> label_values,
      absl::Span<const absl::string_view> optional_values) = 0;
  virtual void ReportDouble(
      GlobalInstrumentsRegistry::GlobalInstrumentHandle handle, double value,
      absl::Span<const absl::string_view> label_values,
      absl::Span<const absl::string_view> optional_values) = 0;
};

class RegisteredMetricCallback;

class StatsPlugin {
 public:

  class ScopeConfig {
   public:
    virtual ~ScopeConfig() = default;

    // NOTE: This is safe to invoke ONLY if both ScopeConfig objects

    virtual int Compare(const ScopeConfig& other) const = 0;
  };

  virtual ~StatsPlugin() = default;

  virtual std::pair<bool, std::shared_ptr<ScopeConfig>> IsEnabledForChannel(
      const experimental::StatsPluginChannelScope& scope) const = 0;

  virtual std::pair<bool, std::shared_ptr<ScopeConfig>> IsEnabledForServer(
      const ChannelArgs& args) const = 0;

  virtual std::shared_ptr<StatsPlugin::ScopeConfig> GetChannelScopeConfig(
      const experimental::StatsPluginChannelScope& scope) const = 0;

  virtual std::shared_ptr<StatsPlugin::ScopeConfig> GetServerScopeConfig(
      const ChannelArgs& args) const = 0;

  virtual void AddCounter(
      GlobalInstrumentsRegistry::GlobalInstrumentHandle handle, uint64_t value,
      absl::Span<const absl::string_view> label_values,
      absl::Span<const absl::string_view> optional_label_values) = 0;

  virtual void AddCounter(
      GlobalInstrumentsRegistry::GlobalInstrumentHandle handle, double value,
      absl::Span<const absl::string_view> label_values,
      absl::Span<const absl::string_view> optional_label_values) = 0;

  virtual void RecordHistogram(
      GlobalInstrumentsRegistry::GlobalInstrumentHandle handle, uint64_t value,
      absl::Span<const absl::string_view> label_values,
      absl::Span<const absl::string_view> optional_label_values) = 0;

  virtual void RecordHistogram(
      GlobalInstrumentsRegistry::GlobalInstrumentHandle handle, double value,
      absl::Span<const absl::string_view> label_values,
      absl::Span<const absl::string_view> optional_label_values) = 0;

  virtual void AddCallback(RegisteredMetricCallback* callback) = 0;

  virtual void RemoveCallback(RegisteredMetricCallback* callback) = 0;

  virtual bool IsInstrumentEnabled(
      GlobalInstrumentsRegistry::GlobalInstrumentHandle handle) const = 0;

  virtual ClientCallTracer* GetClientCallTracer(
      const Slice& path, bool registered_method,
      std::shared_ptr<ScopeConfig> scope_config) = 0;

  virtual ServerCallTracer* GetServerCallTracer(
      std::shared_ptr<ScopeConfig> scope_config) = 0;

};

class GlobalStatsPluginRegistry {
 public:

  class StatsPluginGroup
      : public std::enable_shared_from_this<StatsPluginGroup> {
   public:

    void AddStatsPlugin(std::shared_ptr<StatsPlugin> plugin,
                        std::shared_ptr<StatsPlugin::ScopeConfig> config) {
      PluginState plugin_state;
      plugin_state.plugin = std::move(plugin);
      plugin_state.scope_config = std::move(config);
      plugins_state_.push_back(std::move(plugin_state));
    }

    template <std::size_t M, std::size_t N>
    void AddCounter(
        GlobalInstrumentsRegistry::TypedGlobalInstrumentHandle<
            GlobalInstrumentsRegistry::ValueType::kUInt64,
            GlobalInstrumentsRegistry::InstrumentType::kCounter, M, N>
            handle,
        uint64_t value, std::array<absl::string_view, M> label_values,
        std::array<absl::string_view, N> optional_values) {
      for (auto& state : plugins_state_) {
        state.plugin->AddCounter(handle, value, label_values, optional_values);
      }
    }
    template <std::size_t M, std::size_t N>
    void AddCounter(
        GlobalInstrumentsRegistry::TypedGlobalInstrumentHandle<
            GlobalInstrumentsRegistry::ValueType::kDouble,
            GlobalInstrumentsRegistry::InstrumentType::kCounter, M, N>
            handle,
        double value, std::array<absl::string_view, M> label_values,
        std::array<absl::string_view, N> optional_values) {
      for (auto& state : plugins_state_) {
        state.plugin->AddCounter(handle, value, label_values, optional_values);
      }
    }

    template <std::size_t M, std::size_t N>
    void RecordHistogram(
        GlobalInstrumentsRegistry::TypedGlobalInstrumentHandle<
            GlobalInstrumentsRegistry::ValueType::kUInt64,
            GlobalInstrumentsRegistry::InstrumentType::kHistogram, M, N>
            handle,
        uint64_t value, std::array<absl::string_view, M> label_values,
        std::array<absl::string_view, N> optional_values) {
      for (auto& state : plugins_state_) {
        state.plugin->RecordHistogram(handle, value, label_values,
                                      optional_values);
      }
    }
    template <std::size_t M, std::size_t N>
    void RecordHistogram(
        GlobalInstrumentsRegistry::TypedGlobalInstrumentHandle<
            GlobalInstrumentsRegistry::ValueType::kDouble,
            GlobalInstrumentsRegistry::InstrumentType::kHistogram, M, N>
            handle,
        double value, std::array<absl::string_view, M> label_values,
        std::array<absl::string_view, N> optional_values) {
      for (auto& state : plugins_state_) {
        state.plugin->RecordHistogram(handle, value, label_values,
                                      optional_values);
      }
    }

    bool IsInstrumentEnabled(
        GlobalInstrumentsRegistry::GlobalInstrumentHandle handle) const {
      for (auto& state : plugins_state_) {
        if (state.plugin->IsInstrumentEnabled(handle)) {
          return true;
        }
      }
      return false;
    }

    size_t size() const { return plugins_state_.size(); }

    template <typename... Args>
    GRPC_MUST_USE_RESULT std::unique_ptr<RegisteredMetricCallback>
    RegisterCallback(absl::AnyInvocable<void(CallbackMetricReporter&)> callback,
                     Duration min_interval, Args... args);

    void AddClientCallTracers(const Slice& path, bool registered_method,
                              Arena* arena);

    void AddServerCallTracers(Arena* arena);

    static absl::string_view ChannelArgName() {
      return "grpc.internal.stats_plugin_group";
    }
    static int ChannelArgsCompare(const StatsPluginGroup* a,
                                  const StatsPluginGroup* b);

   private:
    friend class RegisteredMetricCallback;

    struct PluginState {
      std::shared_ptr<StatsPlugin::ScopeConfig> scope_config;
      std::shared_ptr<StatsPlugin> plugin;
    };

    template <GlobalInstrumentsRegistry::ValueType V,
              GlobalInstrumentsRegistry::InstrumentType I, size_t M, size_t N>
    static constexpr void AssertIsCallbackGaugeHandle(
        GlobalInstrumentsRegistry::TypedGlobalInstrumentHandle<V, I, M, N>) {
      static_assert(V == GlobalInstrumentsRegistry::ValueType::kInt64 ||
                        V == GlobalInstrumentsRegistry::ValueType::kDouble,
                    "ValueType must be kInt64 or kDouble");
      static_assert(
          I == GlobalInstrumentsRegistry::InstrumentType::kCallbackGauge,
          "InstrumentType must be kCallbackGauge");
    }

    std::vector<PluginState> plugins_state_;
  };

  static void RegisterStatsPlugin(std::shared_ptr<StatsPlugin> plugin);

  static std::shared_ptr<StatsPluginGroup> GetStatsPluginsForChannel(
      const experimental::StatsPluginChannelScope& scope);
  static std::shared_ptr<StatsPluginGroup> GetStatsPluginsForServer(
      const ChannelArgs& args);

 private:
  struct GlobalStatsPluginNode {
    std::shared_ptr<StatsPlugin> plugin;
    GlobalStatsPluginNode* next = nullptr;
  };
  friend class GlobalStatsPluginRegistryTestPeer;

  GlobalStatsPluginRegistry() = default;

  static std::atomic<GlobalStatsPluginNode*> plugins_;
};

class RegisteredMetricCallback {
 public:
  RegisteredMetricCallback(
      GlobalStatsPluginRegistry::StatsPluginGroup& stats_plugin_group,
      absl::AnyInvocable<void(CallbackMetricReporter&)> callback,
      std::vector<GlobalInstrumentsRegistry::GlobalInstrumentHandle> metrics,
      Duration min_interval);

  ~RegisteredMetricCallback();

  void Run(CallbackMetricReporter& reporter) { callback_(reporter); }

  const std::vector<GlobalInstrumentsRegistry::GlobalInstrumentHandle>&
  metrics() const {
    return metrics_;
  }

  Duration min_interval() const { return min_interval_; }

 private:
  GlobalStatsPluginRegistry::StatsPluginGroup& stats_plugin_group_;
  absl::AnyInvocable<void(CallbackMetricReporter&)> callback_;
  std::vector<GlobalInstrumentsRegistry::GlobalInstrumentHandle> metrics_;
  Duration min_interval_;
};

template <typename... Args>
inline std::unique_ptr<RegisteredMetricCallback>
GlobalStatsPluginRegistry::StatsPluginGroup::RegisterCallback(
    absl::AnyInvocable<void(CallbackMetricReporter&)> callback,
    Duration min_interval, Args... args) {
  (AssertIsCallbackGaugeHandle(args), ...);
  return std::make_unique<RegisteredMetricCallback>(
      *this, std::move(callback),
      std::vector<GlobalInstrumentsRegistry::GlobalInstrumentHandle>{args...},
      min_interval);
}

}

#endif
