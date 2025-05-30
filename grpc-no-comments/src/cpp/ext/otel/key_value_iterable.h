
// Copyright 2023 gRPC authors.

#ifndef GRPC_SRC_CPP_EXT_OTEL_KEY_VALUE_ITERABLE_H
#define GRPC_SRC_CPP_EXT_OTEL_KEY_VALUE_ITERABLE_H

#include <grpc/support/port_platform.h>
#include <stddef.h>

#include <optional>
#include <utility>

#include "absl/log/check.h"
#include "absl/strings/string_view.h"
#include "absl/types/span.h"
#include "opentelemetry/common/attribute_value.h"
#include "opentelemetry/common/key_value_iterable.h"
#include "opentelemetry/nostd/function_ref.h"
#include "opentelemetry/nostd/string_view.h"
#include "src/cpp/ext/otel/otel_plugin.h"

namespace grpc {
namespace internal {

inline opentelemetry::nostd::string_view AbslStrViewToOpenTelemetryStrView(
    absl::string_view str) {
  return opentelemetry::nostd::string_view(str.data(), str.size());
}

class OpenTelemetryPluginImpl::KeyValueIterable
    : public opentelemetry::common::KeyValueIterable {
 public:
  KeyValueIterable(
      const std::vector<std::unique_ptr<LabelsIterable>>&
          injected_labels_from_plugin_options,
      absl::Span<const std::pair<absl::string_view, absl::string_view>>
          additional_labels,
      const OpenTelemetryPluginImpl::ActivePluginOptionsView*
          active_plugin_options_view,
      absl::Span<const grpc_core::RefCountedStringValue> optional_labels,
      bool is_client, const OpenTelemetryPluginImpl* otel_plugin)
      : injected_labels_from_plugin_options_(
            injected_labels_from_plugin_options),
        additional_labels_(additional_labels),
        active_plugin_options_view_(active_plugin_options_view),
        optional_labels_(optional_labels),
        is_client_(is_client),
        otel_plugin_(otel_plugin) {}

  bool ForEachKeyValue(opentelemetry::nostd::function_ref<
                       bool(opentelemetry::nostd::string_view,
                            opentelemetry::common::AttributeValue)>
                           callback) const noexcept override {
    if (active_plugin_options_view_ != nullptr &&
        !active_plugin_options_view_->ForEach(
            [callback, this](
                const InternalOpenTelemetryPluginOption& plugin_option,
                size_t ) {
              return plugin_option.labels_injector()->AddOptionalLabels(
                  is_client_, optional_labels_, callback);
            },
            otel_plugin_)) {
      return false;
    }
    for (const auto& plugin_option_injected_iterable :
         injected_labels_from_plugin_options_) {
      if (plugin_option_injected_iterable != nullptr) {
        plugin_option_injected_iterable->ResetIteratorPosition();
        while (const auto& pair = plugin_option_injected_iterable->Next()) {
          if (!callback(AbslStrViewToOpenTelemetryStrView(pair->first),
                        AbslStrViewToOpenTelemetryStrView(pair->second))) {
            return false;
          }
        }
      }
    }
    for (const auto& pair : additional_labels_) {
      if (!callback(AbslStrViewToOpenTelemetryStrView(pair.first),
                    AbslStrViewToOpenTelemetryStrView(pair.second))) {
        return false;
      }
    }

    if (!optional_labels_.empty()) {
      CHECK(optional_labels_.size() ==
            static_cast<size_t>(grpc_core::ClientCallTracer::CallAttemptTracer::
                                    OptionalLabelKey::kSize));
      for (size_t i = 0; i < optional_labels_.size(); ++i) {
        if (!otel_plugin_->per_call_optional_label_bits_.test(i)) {
          continue;
        }
        if (!callback(
                AbslStrViewToOpenTelemetryStrView(OptionalLabelKeyToString(
                    static_cast<grpc_core::ClientCallTracer::CallAttemptTracer::
                                    OptionalLabelKey>(i))),
                AbslStrViewToOpenTelemetryStrView(
                    optional_labels_[i].as_string_view()))) {
          return false;
        }
      }
    }
    return true;
  }

  size_t size() const noexcept override {
    size_t size = 0;
    for (const auto& plugin_option_injected_iterable :
         injected_labels_from_plugin_options_) {
      if (plugin_option_injected_iterable != nullptr) {
        size += plugin_option_injected_iterable->Size();
      }
    }
    size += additional_labels_.size();
    if (active_plugin_options_view_ != nullptr) {
      active_plugin_options_view_->ForEach(
          [&size, this](const InternalOpenTelemetryPluginOption& plugin_option,
                        size_t ) {
            size += plugin_option.labels_injector()->GetOptionalLabelsSize(
                is_client_, optional_labels_);
            return true;
          },
          otel_plugin_);
    }
    return size;
  }

 private:
  const std::vector<std::unique_ptr<LabelsIterable>>&
      injected_labels_from_plugin_options_;
  absl::Span<const std::pair<absl::string_view, absl::string_view>>
      additional_labels_;
  const OpenTelemetryPluginImpl::ActivePluginOptionsView*
      active_plugin_options_view_;
  absl::Span<const grpc_core::RefCountedStringValue> optional_labels_;
  bool is_client_;
  const OpenTelemetryPluginImpl* otel_plugin_;
};

}
}

#endif
