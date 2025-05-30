
// Copyright 2016 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_SURFACE_CHANNEL_INIT_H
#define GRPC_SRC_CORE_LIB_SURFACE_CHANNEL_INIT_H

#include <grpc/support/port_platform.h>
#include <stdint.h>

#include <initializer_list>
#include <memory>
#include <ostream>
#include <utility>
#include <vector>

#include "absl/functional/any_invocable.h"
#include "absl/log/check.h"
#include "src/core/call/call_filters.h"
#include "src/core/call/interception_chain.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/channel/channel_fwd.h"
#include "src/core/lib/channel/channel_stack_builder.h"
#include "src/core/lib/surface/channel_stack_type.h"
#include "src/core/util/debug_location.h"
#include "src/core/util/unique_type_name.h"

namespace grpc_core {

extern UniqueTypeName (*NameFromChannelFilter)(const grpc_channel_filter*);

class ChannelInit {
 private:

  enum class Version : uint8_t {
    kAny,
    kV2,
    kV3,
  };
  static const char* VersionToString(Version version) {
    switch (version) {
      case Version::kAny:
        return "Any";
      case Version::kV2:
        return "V2";
      case Version::kV3:
        return "V3";
    }
    return "Unknown";
  }
  template <typename Sink>
  friend void AbslStringify(Sink& sink, Version version) {
    sink.Append(VersionToString(version));
  }
  friend std::ostream& operator<<(std::ostream& out, Version version) {
    return out << VersionToString(version);
  }
  static bool SkipV3(Version version) {
    switch (version) {
      case Version::kAny:
      case Version::kV3:
        return false;
      case Version::kV2:
        return true;
    }
    GPR_UNREACHABLE_CODE(return false);
  }
  static bool SkipV2(Version version) {
    switch (version) {
      case Version::kAny:
      case Version::kV2:
        return false;
      case Version::kV3:
        return true;
    }
    GPR_UNREACHABLE_CODE(return false);
  }

 public:

  using InclusionPredicate = absl::AnyInvocable<bool(const ChannelArgs&) const>;

  using PostProcessor = absl::AnyInvocable<void(ChannelStackBuilder&) const>;

  using FilterAdder = void (*)(InterceptionChainBuilder&);

  enum class PostProcessorSlot : uint8_t {
    kAuthSubstitution,
    kXdsChannelStackModifier,
    kCount
  };
  static const char* PostProcessorSlotName(PostProcessorSlot slot) {
    switch (slot) {
      case PostProcessorSlot::kAuthSubstitution:
        return "AuthSubstitution";
      case PostProcessorSlot::kXdsChannelStackModifier:
        return "XdsChannelStackModifier";
      case PostProcessorSlot::kCount:
        return "---count---";
    }
    return "Unknown";
  }
  template <typename Sink>
  friend void AbslStringify(Sink& sink, PostProcessorSlot slot) {
    sink.Append(PostProcessorSlotName(slot));
  }

  enum class Ordering : uint8_t { kTop, kDefault, kBottom };
  static const char* OrderingToString(Ordering ordering) {
    switch (ordering) {
      case Ordering::kTop:
        return "Top";
      case Ordering::kDefault:
        return "Default";
      case Ordering::kBottom:
        return "Bottom";
    }
    return "Unknown";
  }
  template <typename Sink>
  friend void AbslStringify(Sink& sink, Ordering ordering) {
    sink.Append(OrderingToString(ordering));
  };
  friend std::ostream& operator<<(std::ostream& out, Ordering ordering) {
    return out << OrderingToString(ordering);
  }

  class FilterRegistration {
   public:

    explicit FilterRegistration(UniqueTypeName name,
                                const grpc_channel_filter* filter,
                                FilterAdder filter_adder,
                                SourceLocation registration_source)
        : name_(name),
          filter_(filter),
          filter_adder_(filter_adder),
          registration_source_(registration_source) {}
    FilterRegistration(const FilterRegistration&) = delete;
    FilterRegistration& operator=(const FilterRegistration&) = delete;

    template <typename Filter>
    FilterRegistration& After() {
      return After({UniqueTypeNameFor<Filter>()});
    }

    template <typename Filter>
    FilterRegistration& Before() {
      return Before({UniqueTypeNameFor<Filter>()});
    }

    FilterRegistration& After(std::initializer_list<UniqueTypeName> filters);

    FilterRegistration& Before(std::initializer_list<UniqueTypeName> filters);

    FilterRegistration& If(InclusionPredicate predicate);
    FilterRegistration& IfNot(InclusionPredicate predicate);

    FilterRegistration& IfHasChannelArg(const char* arg);

    FilterRegistration& IfChannelArg(const char* arg, bool default_value);

    FilterRegistration& Terminal() {
      terminal_ = true;
      return *this;
    }

    FilterRegistration& BeforeAll() {
      before_all_ = true;
      return *this;
    }

    FilterRegistration& ExcludeFromMinimalStack();
    FilterRegistration& SkipV3() {
      CHECK_EQ(version_, Version::kAny);
      version_ = Version::kV2;
      return *this;
    }
    FilterRegistration& SkipV2() {
      CHECK_EQ(version_, Version::kAny);
      version_ = Version::kV3;
      return *this;
    }

    FilterRegistration& FloatToTop() {
      CHECK_EQ(ordering_, Ordering::kDefault);
      ordering_ = Ordering::kTop;
      return *this;
    }

    FilterRegistration& SinkToBottom() {
      CHECK_EQ(ordering_, Ordering::kDefault);
      ordering_ = Ordering::kBottom;
      return *this;
    }

   private:
    friend class ChannelInit;
    const UniqueTypeName name_;
    const grpc_channel_filter* const filter_;
    const FilterAdder filter_adder_;
    std::vector<UniqueTypeName> after_;
    std::vector<UniqueTypeName> before_;
    std::vector<InclusionPredicate> predicates_;
    bool terminal_ = false;
    bool before_all_ = false;
    Version version_ = Version::kAny;
    Ordering ordering_ = Ordering::kDefault;
    SourceLocation registration_source_;
  };

  class Builder {
   public:

    FilterRegistration& RegisterFilter(grpc_channel_stack_type type,
                                       UniqueTypeName name,
                                       const grpc_channel_filter* filter,
                                       FilterAdder filter_adder = nullptr,
                                       SourceLocation registration_source = {});
    FilterRegistration& RegisterFilter(
        grpc_channel_stack_type type, const grpc_channel_filter* filter,
        SourceLocation registration_source = {}) {
      CHECK(filter != nullptr);
      return RegisterFilter(type, NameFromChannelFilter(filter), filter,
                            nullptr, registration_source);
    }
    template <typename Filter>
    FilterRegistration& RegisterFilter(
        grpc_channel_stack_type type, SourceLocation registration_source = {}) {
      return RegisterFilter(
          type, UniqueTypeNameFor<Filter>(), &Filter::kFilter,
          [](InterceptionChainBuilder& builder) { builder.Add<Filter>(); },
          registration_source);
    }

    template <typename Filter>
    FilterRegistration& RegisterV2Filter(
        grpc_channel_stack_type type, SourceLocation registration_source = {}) {
      return RegisterFilter(type, &Filter::kFilter, registration_source)
          .SkipV3();
    }

    void RegisterPostProcessor(grpc_channel_stack_type type,
                               PostProcessorSlot slot,
                               PostProcessor post_processor) {
      auto& slot_value = post_processors_[type][static_cast<int>(slot)];
      CHECK(slot_value == nullptr);
      slot_value = std::move(post_processor);
    }

    ChannelInit Build();

   private:
    std::vector<std::unique_ptr<FilterRegistration>>
        filters_[GRPC_NUM_CHANNEL_STACK_TYPES];
    PostProcessor post_processors_[GRPC_NUM_CHANNEL_STACK_TYPES]
                                  [static_cast<int>(PostProcessorSlot::kCount)];
  };

  GRPC_MUST_USE_RESULT
  bool CreateStack(ChannelStackBuilder* builder) const;

  void AddToInterceptionChainBuilder(grpc_channel_stack_type type,
                                     InterceptionChainBuilder& builder) const;

 private:

  template <typename T>
  using CreatedType =
      typename decltype(T::Create(ChannelArgs(), {}))::value_type;

  class DependencyTracker;

  struct Filter {
    Filter(UniqueTypeName name, const grpc_channel_filter* filter,
           FilterAdder filter_adder, std::vector<InclusionPredicate> predicates,
           Version version, Ordering ordering,
           SourceLocation registration_source)
        : name(name),
          filter(filter),
          filter_adder(filter_adder),
          predicates(std::move(predicates)),
          registration_source(registration_source),
          version(version),
          ordering(ordering) {}
    UniqueTypeName name;
    const grpc_channel_filter* filter;
    const FilterAdder filter_adder;
    std::vector<InclusionPredicate> predicates;
    SourceLocation registration_source;
    Version version;
    Ordering ordering;
    bool CheckPredicates(const ChannelArgs& args) const;
  };
  struct StackConfig {
    std::vector<Filter> filters;
    std::vector<Filter> terminators;
    std::vector<PostProcessor> post_processors;
  };

  StackConfig stack_configs_[GRPC_NUM_CHANNEL_STACK_TYPES];

  static StackConfig BuildStackConfig(
      const std::vector<std::unique_ptr<FilterRegistration>>& registrations,
      PostProcessor* post_processors, grpc_channel_stack_type type);
  static void PrintChannelStackTrace(
      grpc_channel_stack_type type,
      const std::vector<std::unique_ptr<ChannelInit::FilterRegistration>>&
          registrations,
      const DependencyTracker& dependencies, const std::vector<Filter>& filters,
      const std::vector<Filter>& terminal_filters);
};

}

#endif
