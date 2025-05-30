
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_CALL_METADATA_BATCH_H
#define GRPC_SRC_CORE_CALL_METADATA_BATCH_H

#include <grpc/impl/compression_types.h>
#include <grpc/status.h>
#include <grpc/support/port_platform.h>
#include <stdlib.h>

#include <cstdint>
#include <optional>
#include <string>
#include <type_traits>
#include <utility>

#include "absl/container/inlined_vector.h"
#include "absl/functional/function_ref.h"
#include "absl/log/check.h"
#include "absl/meta/type_traits.h"
#include "absl/strings/numbers.h"
#include "absl/strings/string_view.h"
#include "src/core/call/custom_metadata.h"
#include "src/core/call/metadata_compression_traits.h"
#include "src/core/call/parsed_metadata.h"
#include "src/core/call/simple_slice_based_metadata.h"
#include "src/core/lib/compression/compression_internal.h"
#include "src/core/lib/experiments/experiments.h"
#include "src/core/lib/promise/poll.h"
#include "src/core/lib/slice/slice.h"
#include "src/core/util/chunked_vector.h"
#include "src/core/util/if_list.h"
#include "src/core/util/packed_table.h"
#include "src/core/util/time.h"
#include "src/core/util/type_list.h"

namespace grpc_core {

template <typename Key>
size_t EncodedSizeOfKey(Key, const typename Key::ValueType& value) {
  return Key::Encode(value).size();
}

struct GrpcTimeoutMetadata {
  static constexpr bool kRepeatable = false;
  static constexpr bool kTransferOnTrailersOnly = false;
  using ValueType = Timestamp;
  using MementoType = Duration;
  using CompressionTraits = TimeoutCompressor;
  static absl::string_view key() { return "grpc-timeout"; }
  static MementoType ParseMemento(Slice value,
                                  bool will_keep_past_request_lifetime,
                                  MetadataParseErrorFn on_error);
  static ValueType MementoToValue(MementoType timeout);
  static Slice Encode(ValueType x);
  static std::string DisplayValue(ValueType x) { return x.ToString(); }
  static std::string DisplayMemento(MementoType x) { return x.ToString(); }
};

struct TeMetadata {
  static constexpr bool kRepeatable = false;
  static constexpr bool kTransferOnTrailersOnly = false;

  enum ValueType : uint8_t {
    kTrailers,
    kInvalid,
  };
  using MementoType = ValueType;
  using CompressionTraits = KnownValueCompressor<ValueType, kTrailers>;
  static absl::string_view key() { return "te"; }
  static MementoType ParseMemento(Slice value,
                                  bool will_keep_past_request_lifetime,
                                  MetadataParseErrorFn on_error);
  static ValueType MementoToValue(MementoType te) { return te; }
  static StaticSlice Encode(ValueType x) {
    CHECK(x == kTrailers);
    return StaticSlice::FromStaticString("trailers");
  }
  static const char* DisplayValue(ValueType te);
  static const char* DisplayMemento(MementoType te) { return DisplayValue(te); }
};

inline size_t EncodedSizeOfKey(TeMetadata, TeMetadata::ValueType x) {
  return x == TeMetadata::kTrailers ? 8 : 0;
}

struct ContentTypeMetadata {
  static constexpr bool kRepeatable = false;
  static constexpr bool kTransferOnTrailersOnly = true;

  enum ValueType : uint8_t {
    kApplicationGrpc,
    kEmpty,
    kInvalid,
  };
  using MementoType = ValueType;
  using CompressionTraits = KnownValueCompressor<ValueType, kApplicationGrpc>;
  static absl::string_view key() { return "content-type"; }
  static MementoType ParseMemento(Slice value,
                                  bool will_keep_past_request_lifetime,
                                  MetadataParseErrorFn on_error);
  static ValueType MementoToValue(MementoType content_type) {
    return content_type;
  }

  static StaticSlice Encode(ValueType x);
  static const char* DisplayValue(ValueType content_type);
  static const char* DisplayMemento(ValueType content_type) {
    return DisplayValue(content_type);
  }
};

struct HttpSchemeMetadata {
  static constexpr bool kRepeatable = false;
  static constexpr bool kTransferOnTrailersOnly = false;
  enum ValueType : uint8_t {
    kHttp,
    kHttps,
    kInvalid,
  };
  using MementoType = ValueType;
  using CompressionTraits = HttpSchemeCompressor;
  static absl::string_view key() { return ":scheme"; }
  static MementoType ParseMemento(Slice value, bool,
                                  MetadataParseErrorFn on_error) {
    return Parse(value.as_string_view(), on_error);
  }
  static ValueType Parse(absl::string_view value,
                         MetadataParseErrorFn on_error);
  static ValueType MementoToValue(MementoType content_type) {
    return content_type;
  }
  static StaticSlice Encode(ValueType x);
  static const char* DisplayValue(ValueType content_type);
  static const char* DisplayMemento(MementoType content_type) {
    return DisplayValue(content_type);
  }
};

size_t EncodedSizeOfKey(HttpSchemeMetadata, HttpSchemeMetadata::ValueType x);

struct HttpMethodMetadata {
  static constexpr bool kRepeatable = false;
  static constexpr bool kTransferOnTrailersOnly = false;
  enum ValueType : uint8_t {
    kPost,
    kGet,
    kPut,
    kInvalid,
  };
  using MementoType = ValueType;
  using CompressionTraits = HttpMethodCompressor;
  static absl::string_view key() { return ":method"; }
  static MementoType ParseMemento(Slice value,
                                  bool will_keep_past_request_lifetime,
                                  MetadataParseErrorFn on_error);
  static ValueType MementoToValue(MementoType content_type) {
    return content_type;
  }
  static StaticSlice Encode(ValueType x);
  static const char* DisplayValue(ValueType content_type);
  static const char* DisplayMemento(MementoType content_type) {
    return DisplayValue(content_type);
  }
};

struct CompressionAlgorithmBasedMetadata {
  using ValueType = grpc_compression_algorithm;
  using MementoType = ValueType;
  static MementoType ParseMemento(Slice value,
                                  bool will_keep_past_request_lifetime,
                                  MetadataParseErrorFn on_error);
  static ValueType MementoToValue(MementoType x) { return x; }
  static Slice Encode(ValueType x) {
    CHECK(x != GRPC_COMPRESS_ALGORITHMS_COUNT);
    return Slice::FromStaticString(CompressionAlgorithmAsString(x));
  }
  static const char* DisplayValue(ValueType x) {
    if (const char* p = CompressionAlgorithmAsString(x)) {
      return p;
    } else {
      return "<discarded-invalid-value>";
    }
  }
  static const char* DisplayMemento(MementoType x) { return DisplayValue(x); }
};

struct GrpcEncodingMetadata : public CompressionAlgorithmBasedMetadata {
  static constexpr bool kRepeatable = false;
  static constexpr bool kTransferOnTrailersOnly = false;
  using CompressionTraits =
      SmallIntegralValuesCompressor<GRPC_COMPRESS_ALGORITHMS_COUNT>;
  static absl::string_view key() { return "grpc-encoding"; }
};

struct GrpcInternalEncodingRequest : public CompressionAlgorithmBasedMetadata {
  static constexpr bool kRepeatable = false;
  static constexpr bool kTransferOnTrailersOnly = false;
  using CompressionTraits = NoCompressionCompressor;
  static absl::string_view key() { return "grpc-internal-encoding-request"; }
};

struct GrpcAcceptEncodingMetadata {
  static constexpr bool kRepeatable = false;
  static constexpr bool kTransferOnTrailersOnly = false;
  static absl::string_view key() { return "grpc-accept-encoding"; }
  using ValueType = CompressionAlgorithmSet;
  using MementoType = ValueType;
  using CompressionTraits = StableValueCompressor;
  static MementoType ParseMemento(Slice value, bool, MetadataParseErrorFn) {
    return CompressionAlgorithmSet::FromString(value.as_string_view());
  }
  static ValueType MementoToValue(MementoType x) { return x; }
  static Slice Encode(ValueType x) { return x.ToSlice(); }
  static absl::string_view DisplayValue(ValueType x) { return x.ToString(); }
  static absl::string_view DisplayMemento(MementoType x) {
    return DisplayValue(x);
  }
};

struct UserAgentMetadata : public SimpleSliceBasedMetadata {
  static constexpr bool kRepeatable = false;
  static constexpr bool kTransferOnTrailersOnly = false;
  using CompressionTraits = StableValueCompressor;
  static absl::string_view key() { return "user-agent"; }
};

struct GrpcMessageMetadata : public SimpleSliceBasedMetadata {
  static constexpr bool kRepeatable = false;
  static constexpr bool kTransferOnTrailersOnly = false;
  using CompressionTraits = NoCompressionCompressor;
  static absl::string_view key() { return "grpc-message"; }
};

struct HostMetadata : public SimpleSliceBasedMetadata {
  static constexpr bool kRepeatable = false;
  static constexpr bool kTransferOnTrailersOnly = false;
  using CompressionTraits = NoCompressionCompressor;
  static absl::string_view key() { return "host"; }
};

struct EndpointLoadMetricsBinMetadata : public SimpleSliceBasedMetadata {
  static constexpr bool kRepeatable = false;
  static constexpr bool kTransferOnTrailersOnly = false;
  using CompressionTraits = NoCompressionCompressor;
  static absl::string_view key() { return "endpoint-load-metrics-bin"; }
};

struct GrpcServerStatsBinMetadata : public SimpleSliceBasedMetadata {
  static constexpr bool kRepeatable = false;
  static constexpr bool kTransferOnTrailersOnly = false;
  using CompressionTraits = NoCompressionCompressor;
  static absl::string_view key() { return "grpc-server-stats-bin"; }
};

struct GrpcTraceBinMetadata : public SimpleSliceBasedMetadata {
  static constexpr bool kRepeatable = false;
  static constexpr bool kTransferOnTrailersOnly = false;
  using CompressionTraits = FrequentKeyWithNoValueCompressionCompressor;
  static absl::string_view key() { return "grpc-trace-bin"; }
};

struct GrpcTagsBinMetadata : public SimpleSliceBasedMetadata {
  static constexpr bool kRepeatable = false;
  static constexpr bool kTransferOnTrailersOnly = false;
  using CompressionTraits = FrequentKeyWithNoValueCompressionCompressor;
  static absl::string_view key() { return "grpc-tags-bin"; }
};

struct XEnvoyPeerMetadata : public SimpleSliceBasedMetadata {
  static constexpr bool kRepeatable = false;
  static constexpr bool kTransferOnTrailersOnly = true;
  using CompressionTraits = StableValueCompressor;
  static absl::string_view key() { return "x-envoy-peer-metadata"; }
};

struct HttpAuthorityMetadata : public SimpleSliceBasedMetadata {
  static constexpr bool kRepeatable = false;
  static constexpr bool kTransferOnTrailersOnly = false;
  using CompressionTraits = SmallSetOfValuesCompressor;
  static absl::string_view key() { return ":authority"; }
};

struct HttpPathMetadata : public SimpleSliceBasedMetadata {
  static constexpr bool kRepeatable = false;
  static constexpr bool kTransferOnTrailersOnly = false;
  using CompressionTraits = SmallSetOfValuesCompressor;
  static absl::string_view key() { return ":path"; }
};

template <typename Int>
struct SimpleIntBasedMetadataBase {
  using ValueType = Int;
  using MementoType = Int;
  static ValueType MementoToValue(MementoType value) { return value; }
  static Slice Encode(ValueType x) { return Slice::FromInt64(x); }
  static Int DisplayValue(ValueType x) { return x; }
  static Int DisplayMemento(MementoType x) { return x; }
};

template <typename Int, Int kInvalidValue>
struct SimpleIntBasedMetadata : public SimpleIntBasedMetadataBase<Int> {
  static constexpr Int invalid_value() { return kInvalidValue; }
  static Int ParseMemento(Slice value, bool, MetadataParseErrorFn on_error) {
    Int out;
    if (!absl::SimpleAtoi(value.as_string_view(), &out)) {
      on_error("not an integer", value);
      out = kInvalidValue;
    }
    return out;
  }
};

struct GrpcStatusMetadata {
  using ValueType = grpc_status_code;
  using MementoType = grpc_status_code;
  static ValueType MementoToValue(MementoType value) { return value; }
  static Slice Encode(ValueType x) { return Slice::FromInt64(x); }
  static std::string DisplayValue(ValueType x) {
    switch (x) {
      case GRPC_STATUS_OK:
        return "OK";
      case GRPC_STATUS_CANCELLED:
        return "CANCELLED";
      case GRPC_STATUS_UNKNOWN:
        return "UNKNOWN";
      case GRPC_STATUS_INVALID_ARGUMENT:
        return "INVALID_ARGUMENT";
      case GRPC_STATUS_DEADLINE_EXCEEDED:
        return "DEADLINE_EXCEEDED";
      case GRPC_STATUS_NOT_FOUND:
        return "NOT_FOUND";
      case GRPC_STATUS_ALREADY_EXISTS:
        return "ALREADY_EXISTS";
      case GRPC_STATUS_PERMISSION_DENIED:
        return "PERMISSION_DENIED";
      case GRPC_STATUS_RESOURCE_EXHAUSTED:
        return "RESOURCE_EXHAUSTED";
      case GRPC_STATUS_FAILED_PRECONDITION:
        return "FAILED_PRECONDITION";
      case GRPC_STATUS_ABORTED:
        return "ABORTED";
      case GRPC_STATUS_OUT_OF_RANGE:
        return "OUT_OF_RANGE";
      case GRPC_STATUS_UNIMPLEMENTED:
        return "UNIMPLEMENTED";
      case GRPC_STATUS_INTERNAL:
        return "INTERNAL";
      case GRPC_STATUS_UNAVAILABLE:
        return "UNAVAILABLE";
      case GRPC_STATUS_DATA_LOSS:
        return "DATA_LOSS";
      case GRPC_STATUS_UNAUTHENTICATED:
        return "UNAUTHENTICATED";
      default:
        return absl::StrCat("UNKNOWN(", static_cast<int>(x), ")");
    }
  }
  static auto DisplayMemento(MementoType x) { return DisplayValue(x); }
  static constexpr bool kRepeatable = false;
  static constexpr bool kTransferOnTrailersOnly = false;
  using CompressionTraits = SmallIntegralValuesCompressor<16>;
  static absl::string_view key() { return "grpc-status"; }
  static grpc_status_code ParseMemento(Slice value, bool,
                                       MetadataParseErrorFn on_error) {
    int64_t wire_value;
    if (!absl::SimpleAtoi(value.as_string_view(), &wire_value)) {
      on_error("not an integer", value);
      return GRPC_STATUS_UNKNOWN;
    }
    if (wire_value < 0) {
      on_error("negative value", value);
      return GRPC_STATUS_UNKNOWN;
    }
    if (wire_value >= GRPC_STATUS__DO_NOT_USE) {
      on_error("out of range", value);
      return GRPC_STATUS_UNKNOWN;
    }
    return static_cast<grpc_status_code>(wire_value);
  }
};

struct GrpcPreviousRpcAttemptsMetadata
    : public SimpleIntBasedMetadata<uint32_t, 0> {
  static constexpr bool kRepeatable = false;
  static constexpr bool kTransferOnTrailersOnly = false;
  using CompressionTraits = NoCompressionCompressor;
  static absl::string_view key() { return "grpc-previous-rpc-attempts"; }
};

struct GrpcRetryPushbackMsMetadata {
  static constexpr bool kRepeatable = false;
  static constexpr bool kTransferOnTrailersOnly = false;
  static absl::string_view key() { return "grpc-retry-pushback-ms"; }
  using ValueType = Duration;
  using MementoType = Duration;
  using CompressionTraits = NoCompressionCompressor;
  static ValueType MementoToValue(MementoType x) { return x; }
  static Slice Encode(Duration x) { return Slice::FromInt64(x.millis()); }
  static int64_t DisplayValue(Duration x) { return x.millis(); }
  static int64_t DisplayMemento(Duration x) { return DisplayValue(x); }
  static Duration ParseMemento(Slice value,
                               bool will_keep_past_request_lifetime,
                               MetadataParseErrorFn on_error);
};

struct HttpStatusMetadata : public SimpleIntBasedMetadata<uint32_t, 0> {
  static constexpr bool kRepeatable = false;
  static constexpr bool kTransferOnTrailersOnly = true;
  using CompressionTraits = HttpStatusCompressor;
  static absl::string_view key() { return ":status"; }
};

class GrpcLbClientStats;

struct GrpcLbClientStatsMetadata {
  static constexpr bool kRepeatable = false;
  static constexpr bool kTransferOnTrailersOnly = false;
  static absl::string_view key() { return "grpclb_client_stats"; }
  using ValueType = GrpcLbClientStats*;
  using MementoType = ValueType;
  using CompressionTraits = NoCompressionCompressor;
  static ValueType MementoToValue(MementoType value) { return value; }
  static Slice Encode(ValueType) { abort(); }
  static const char* DisplayValue(ValueType) { return "<internal-lb-stats>"; }
  static const char* DisplayMemento(MementoType) {
    return "<internal-lb-stats>";
  }
  static MementoType ParseMemento(Slice, bool, MetadataParseErrorFn error) {
    error("not a valid value for grpclb_client_stats", Slice());
    return nullptr;
  }
};

inline size_t EncodedSizeOfKey(GrpcLbClientStatsMetadata,
                               GrpcLbClientStatsMetadata::ValueType) {
  return 0;
}

struct LbTokenMetadata : public SimpleSliceBasedMetadata {
  static constexpr bool kRepeatable = false;
  static constexpr bool kTransferOnTrailersOnly = false;
  using CompressionTraits = NoCompressionCompressor;
  static absl::string_view key() { return "lb-token"; }
};

struct LbCostBinMetadata {
  static constexpr bool kRepeatable = true;
  static constexpr bool kTransferOnTrailersOnly = false;
  static absl::string_view key() { return "lb-cost-bin"; }
  struct ValueType {
    double cost;
    std::string name;
  };
  using MementoType = ValueType;
  using CompressionTraits = NoCompressionCompressor;
  static ValueType MementoToValue(MementoType value) { return value; }
  static Slice Encode(const ValueType& x);
  static std::string DisplayValue(ValueType x);
  static std::string DisplayMemento(MementoType x) { return DisplayValue(x); }
  static MementoType ParseMemento(Slice value,
                                  bool will_keep_past_request_lifetime,
                                  MetadataParseErrorFn on_error);
};

struct W3CTraceParentMetadata : public SimpleSliceBasedMetadata {
  static constexpr bool kRepeatable = false;
  static constexpr bool kTransferOnTrailersOnly = false;
  using CompressionTraits = NoCompressionCompressor;
  static absl::string_view key() { return "traceparent"; }
};

struct GrpcStreamNetworkState {
  static absl::string_view DebugKey() { return "GrpcStreamNetworkState"; }
  static constexpr bool kRepeatable = false;
  static constexpr bool kTransferOnTrailersOnly = false;
  enum ValueType : uint8_t {
    kNotSentOnWire,
    kNotSeenByServer,
  };
  static std::string DisplayValue(ValueType x);
};

struct PeerString {
  static absl::string_view DebugKey() { return "PeerString"; }
  static constexpr bool kRepeatable = false;
  using ValueType = Slice;
  static std::string DisplayValue(const ValueType& x);
};

struct GrpcStatusContext {
  static absl::string_view DebugKey() { return "GrpcStatusContext"; }
  static constexpr bool kRepeatable = true;
  using ValueType = std::string;
  static const std::string& DisplayValue(const std::string& x);
};

struct GrpcStatusFromWire {
  static absl::string_view DebugKey() { return "GrpcStatusFromWire"; }
  static constexpr bool kRepeatable = false;
  using ValueType = bool;
  static absl::string_view DisplayValue(bool x) { return x ? "true" : "false"; }
};

struct GrpcCallWasCancelled {
  static absl::string_view DebugKey() { return "GrpcCallWasCancelled"; }
  static constexpr bool kRepeatable = false;
  using ValueType = bool;
  static absl::string_view DisplayValue(bool x) { return x ? "true" : "false"; }
};

struct WaitForReady {
  struct ValueType {
    bool value = false;
    bool explicitly_set = false;
  };
  static absl::string_view DebugKey() { return "WaitForReady"; }
  static constexpr bool kRepeatable = false;
  static std::string DisplayValue(ValueType x);
};

struct IsTransparentRetry {
  static absl::string_view DebugKey() { return "IsTransparentRetry"; }
  static constexpr bool kRepeatable = false;
  using ValueType = bool;
  static std::string DisplayValue(ValueType x) { return x ? "true" : "false"; }
};

struct GrpcTrailersOnly {
  static absl::string_view DebugKey() { return "GrpcTrailersOnly"; }
  static constexpr bool kRepeatable = false;
  using ValueType = bool;
  static absl::string_view DisplayValue(bool x) { return x ? "true" : "false"; }
};

struct GrpcRegisteredMethod {
  static absl::string_view DebugKey() { return "GrpcRegisteredMethod"; }
  static constexpr bool kRepeatable = false;
  using ValueType = void*;
  static std::string DisplayValue(void* x);
};

struct GrpcTarPit {
  static absl::string_view DebugKey() { return "GrpcTarPit"; }
  static constexpr bool kRepeatable = false;
  using ValueType = Empty;
  static absl::string_view DisplayValue(Empty) { return "tarpit"; }
};

namespace metadata_detail {

class DebugStringBuilder {
 public:

  void AddAfterRedaction(absl::string_view key, absl::string_view value);

  std::string TakeOutput() { return std::move(out_); }

 private:
  bool IsAllowListed(absl::string_view key) const;
  void Add(absl::string_view key, absl::string_view value);
  std::string out_;
};

template <typename Trait, typename Ignored = void>
struct IsEncodableTrait {
  static const bool value = false;
};

template <typename Trait>
struct IsEncodableTrait<Trait, absl::void_t<decltype(Trait::key())>> {
  static const bool value = true;
};

template <typename MustBeVoid, typename... Traits>
struct EncodableTraits;

template <typename Trait, typename... Traits>
struct EncodableTraits<absl::enable_if_t<IsEncodableTrait<Trait>::value, void>,
                       Trait, Traits...> {
  using List =
      typename EncodableTraits<void,
                               Traits...>::List::template PushFront<Trait>;
};

template <typename Trait, typename... Traits>
struct EncodableTraits<absl::enable_if_t<!IsEncodableTrait<Trait>::value, void>,
                       Trait, Traits...> {
  using List = typename EncodableTraits<void, Traits...>::List;
};

template <>
struct EncodableTraits<void> {
  using List = Typelist<>;
};

template <typename Trait>
struct EncodableNameLookupKeyComparison {
  bool operator()(absl::string_view key) { return key == Trait::key(); }
};

template <typename Trait, typename Op>
struct EncodableNameLookupOnFound {
  auto operator()(Op* op) { return op->Found(Trait()); }
};

template <typename... Traits>
struct EncodableNameLookup {
  template <typename Op>
  static auto Lookup(absl::string_view key, Op* op) {
    return IfList(
        key, op, [key](Op* op) { return op->NotFound(key); },
        EncodableNameLookupKeyComparison<Traits>()...,
        EncodableNameLookupOnFound<Traits, Op>()...);
  }
};

template <typename... Traits>
using NameLookup = typename EncodableTraits<
    void, Traits...>::List::template Instantiate<EncodableNameLookup>;

template <typename ParseMementoFn, typename MementoToValueFn>
struct ParseValue {
  template <ParseMementoFn parse_memento, MementoToValueFn memento_to_value>
  static GPR_ATTRIBUTE_NOINLINE auto Parse(Slice* value,
                                           MetadataParseErrorFn on_error)
      -> decltype(memento_to_value(parse_memento(std::move(*value), false,
                                                 on_error))) {
    return memento_to_value(parse_memento(std::move(*value), false, on_error));
  }
};

template <typename Container>
class ParseHelper {
 public:
  ParseHelper(Slice value, bool will_keep_past_request_lifetime,
              MetadataParseErrorFn on_error, size_t transport_size)
      : value_(std::move(value)),
        will_keep_past_request_lifetime_(will_keep_past_request_lifetime),
        on_error_(on_error),
        transport_size_(transport_size) {}

  template <typename Trait>
  GPR_ATTRIBUTE_NOINLINE ParsedMetadata<Container> Found(Trait trait) {
    return ParsedMetadata<Container>(
        trait,
        ParseValueToMemento<typename Trait::MementoType, Trait::ParseMemento>(),
        static_cast<uint32_t>(transport_size_));
  }

  GPR_ATTRIBUTE_NOINLINE ParsedMetadata<Container> NotFound(
      absl::string_view key) {
    return ParsedMetadata<Container>(
        typename ParsedMetadata<Container>::FromSlicePair{},
        Slice::FromCopiedString(key),
        will_keep_past_request_lifetime_ ? value_.TakeUniquelyOwned()
                                         : std::move(value_),
        transport_size_);
  }

 private:
  template <typename T, T (*parse_memento)(Slice, bool, MetadataParseErrorFn)>
  GPR_ATTRIBUTE_NOINLINE T ParseValueToMemento() {
    return parse_memento(std::move(value_), will_keep_past_request_lifetime_,
                         on_error_);
  }

  Slice value_;
  const bool will_keep_past_request_lifetime_;
  MetadataParseErrorFn on_error_;
  const size_t transport_size_;
};

template <typename Container>
class AppendHelper {
 public:
  AppendHelper(Container* container, Slice value, MetadataParseErrorFn on_error)
      : container_(container), value_(std::move(value)), on_error_(on_error) {}

  template <typename Trait>
  GPR_ATTRIBUTE_NOINLINE void Found(Trait trait) {
    container_->Set(
        trait, ParseValue<decltype(Trait::ParseMemento),
                          decltype(Trait::MementoToValue)>::
                   template Parse<Trait::ParseMemento, Trait::MementoToValue>(
                       &value_, on_error_));
  }

  GPR_ATTRIBUTE_NOINLINE void NotFound(absl::string_view key) {
    container_->unknown_.Append(key, std::move(value_));
  }

 private:
  Container* const container_;
  Slice value_;
  MetadataParseErrorFn on_error_;
};

template <typename Container>
class RemoveHelper {
 public:
  explicit RemoveHelper(Container* container) : container_(container) {}

  template <typename Trait>
  GPR_ATTRIBUTE_NOINLINE void Found(Trait trait) {
    container_->Remove(trait);
  }

  GPR_ATTRIBUTE_NOINLINE void NotFound(absl::string_view key) {
    container_->unknown_.Remove(key);
  }

 private:
  Container* const container_;
};

template <typename Container>
class GetStringValueHelper {
 public:
  explicit GetStringValueHelper(const Container* container,
                                std::string* backing)
      : container_(container), backing_(backing) {}

  template <typename Trait>
  GPR_ATTRIBUTE_NOINLINE absl::enable_if_t<
      Trait::kRepeatable == false &&
          std::is_same<Slice, typename Trait::ValueType>::value,
      std::optional<absl::string_view>>
  Found(Trait) {
    const auto* value = container_->get_pointer(Trait());
    if (value == nullptr) return std::nullopt;
    return value->as_string_view();
  }

  template <typename Trait>
  GPR_ATTRIBUTE_NOINLINE absl::enable_if_t<
      Trait::kRepeatable == true &&
          !std::is_same<Slice, typename Trait::ValueType>::value,
      std::optional<absl::string_view>>
  Found(Trait) {
    const auto* value = container_->get_pointer(Trait());
    if (value == nullptr) return std::nullopt;
    backing_->clear();
    for (const auto& v : *value) {
      if (!backing_->empty()) backing_->push_back(',');
      auto new_segment = Trait::Encode(v);
      backing_->append(new_segment.begin(), new_segment.end());
    }
    return *backing_;
  }

  template <typename Trait>
  GPR_ATTRIBUTE_NOINLINE absl::enable_if_t<
      Trait::kRepeatable == false &&
          !std::is_same<Slice, typename Trait::ValueType>::value,
      std::optional<absl::string_view>>
  Found(Trait) {
    const auto* value = container_->get_pointer(Trait());
    if (value == nullptr) return std::nullopt;
    *backing_ = std::string(Trait::Encode(*value).as_string_view());
    return *backing_;
  }

  GPR_ATTRIBUTE_NOINLINE std::optional<absl::string_view> NotFound(
      absl::string_view key) {
    return container_->unknown_.GetStringValue(key, backing_);
  }

 private:
  const Container* const container_;
  std::string* backing_;
};

using LogFn = absl::FunctionRef<void(absl::string_view, absl::string_view)>;

template <typename T>
struct AdaptDisplayValueToLog {
  static std::string ToString(const T& value) { return std::to_string(value); }
};

template <>
struct AdaptDisplayValueToLog<std::string> {
  static std::string ToString(const std::string& value) { return value; }
};

template <>
struct AdaptDisplayValueToLog<const std::string&> {
  static std::string ToString(const std::string& value) { return value; }
};

template <>
struct AdaptDisplayValueToLog<absl::string_view> {
  static std::string ToString(absl::string_view value) {
    return std::string(value);
  }
};

template <>
struct AdaptDisplayValueToLog<Slice> {
  static std::string ToString(Slice value) {
    return std::string(value.as_string_view());
  }
};

template <>
struct AdaptDisplayValueToLog<const char*> {
  static std::string ToString(const char* value) { return std::string(value); }
};

template <>
struct AdaptDisplayValueToLog<StaticSlice> {
  static absl::string_view ToString(StaticSlice value) {
    return value.as_string_view();
  }
};

template <typename T, typename U, typename V>
GPR_ATTRIBUTE_NOINLINE void LogKeyValueTo(absl::string_view key, const T& value,
                                          V (*display_value)(U), LogFn log_fn) {
  log_fn(key, AdaptDisplayValueToLog<V>::ToString(display_value(value)));
}

template <typename Which, typename Ignored = void>
struct Value;

template <typename Which>
struct Value<Which, absl::enable_if_t<Which::kRepeatable == false &&
                                          IsEncodableTrait<Which>::value,
                                      void>> {
  Value() = default;
  explicit Value(const typename Which::ValueType& value) : value(value) {}
  explicit Value(typename Which::ValueType&& value)
      : value(std::forward<typename Which::ValueType>(value)) {}
  Value(const Value&) = delete;
  Value& operator=(const Value&) = delete;
  Value(Value&&) noexcept = default;
  Value& operator=(Value&& other) noexcept {
    value = std::move(other.value);
    return *this;
  }
  template <typename Encoder>
  void EncodeTo(Encoder* encoder) const {
    encoder->Encode(Which(), value);
  }
  template <typename Encoder>
  void VisitWith(Encoder* encoder) const {
    return EncodeTo(encoder);
  }
  void LogTo(LogFn log_fn) const {
    LogKeyValueTo(Which::key(), value, Which::DisplayValue, log_fn);
  }
  using StorageType = typename Which::ValueType;
  GPR_NO_UNIQUE_ADDRESS StorageType value;
};

template <typename Which>
struct Value<Which, absl::enable_if_t<Which::kRepeatable == false &&
                                          !IsEncodableTrait<Which>::value,
                                      void>> {
  Value() = default;
  explicit Value(const typename Which::ValueType& value) : value(value) {}
  explicit Value(typename Which::ValueType&& value)
      : value(std::forward<typename Which::ValueType>(value)) {}
  Value(const Value&) = delete;
  Value& operator=(const Value&) = delete;
  Value(Value&&) noexcept = default;
  Value& operator=(Value&& other) noexcept {
    value = std::move(other.value);
    return *this;
  }
  template <typename Encoder>
  void EncodeTo(Encoder*) const {}
  template <typename Encoder>
  void VisitWith(Encoder* encoder) const {
    encoder->Encode(Which(), value);
  }
  void LogTo(LogFn log_fn) const {
    LogKeyValueTo(Which::DebugKey(), value, Which::DisplayValue, log_fn);
  }
  using StorageType = typename Which::ValueType;
  GPR_NO_UNIQUE_ADDRESS StorageType value;
};

template <typename Which>
struct Value<Which, absl::enable_if_t<Which::kRepeatable == true &&
                                          IsEncodableTrait<Which>::value,
                                      void>> {
  Value() = default;
  explicit Value(const typename Which::ValueType& value) {
    this->value.push_back(value);
  }
  explicit Value(typename Which::ValueType&& value) {
    this->value.emplace_back(std::forward<typename Which::ValueType>(value));
  }
  Value(const Value&) = delete;
  Value& operator=(const Value&) = delete;
  Value(Value&& other) noexcept : value(std::move(other.value)) {}
  Value& operator=(Value&& other) noexcept {
    value = std::move(other.value);
    return *this;
  }
  template <typename Encoder>
  void EncodeTo(Encoder* encoder) const {
    for (const auto& v : value) {
      encoder->Encode(Which(), v);
    }
  }
  template <typename Encoder>
  void VisitWith(Encoder* encoder) const {
    return EncodeTo(encoder);
  }
  void LogTo(LogFn log_fn) const {
    for (const auto& v : value) {
      LogKeyValueTo(Which::key(), v, Which::Encode, log_fn);
    }
  }
  using StorageType = absl::InlinedVector<typename Which::ValueType, 1>;
  StorageType value;
};

template <typename Which>
struct Value<Which, absl::enable_if_t<Which::kRepeatable == true &&
                                          !IsEncodableTrait<Which>::value,
                                      void>> {
  Value() = default;
  explicit Value(const typename Which::ValueType& value) {
    this->value.push_back(value);
  }
  explicit Value(typename Which::ValueType&& value) {
    this->value.emplace_back(std::forward<typename Which::ValueType>(value));
  }
  Value(const Value&) = delete;
  Value& operator=(const Value&) = delete;
  Value(Value&& other) noexcept : value(std::move(other.value)) {}
  Value& operator=(Value&& other) noexcept {
    value = std::move(other.value);
    return *this;
  }
  template <typename Encoder>
  void EncodeTo(Encoder*) const {}
  template <typename Encoder>
  void VisitWith(Encoder* encoder) const {
    for (const auto& v : value) {
      encoder->Encode(Which(), v);
    }
  }
  void LogTo(LogFn log_fn) const {
    for (const auto& v : value) {
      LogKeyValueTo(Which::DebugKey(), v, Which::DisplayValue, log_fn);
    }
  }
  using StorageType = absl::InlinedVector<typename Which::ValueType, 1>;
  StorageType value;
};

template <typename Output>
class CopySink {
 public:
  explicit CopySink(Output* dst) : dst_(dst) {}

  template <class T, class V>
  void Encode(T trait, V value) {
    dst_->Set(trait, value);
  }

  template <class T>
  void Encode(T trait, const Slice& value) {
    dst_->Set(trait, std::move(value.AsOwned()));
  }

  void Encode(const Slice& key, const Slice& value) {
    dst_->unknown_.Append(key.as_string_view(), value.Ref());
  }

 private:
  Output* dst_;
};

template <typename Encoder>
struct EncodeWrapper {
  Encoder* encoder;
  template <typename Which>
  void operator()(const Value<Which>& which) {
    which.EncodeTo(encoder);
  }
};

template <typename Encoder>
struct ForEachWrapper {
  Encoder* encoder;
  template <typename Which>
  void operator()(const Value<Which>& which) {
    which.VisitWith(encoder);
  }
};

struct LogWrapper {
  LogFn log_fn;
  template <typename Which>
  void operator()(const Value<Which>& which) {
    which.LogTo(log_fn);
  }
};

template <typename Filterer>
struct FilterWrapper {
  Filterer filter_fn;

  template <typename Which,
            absl::enable_if_t<IsEncodableTrait<Which>::value, bool> = true>
  bool operator()(const Value<Which>& ) {
    return filter_fn(Which());
  }

  template <typename Which,
            absl::enable_if_t<!IsEncodableTrait<Which>::value, bool> = true>
  bool operator()(const Value<Which>& ) {
    return true;
  }
};

class TransportSizeEncoder {
 public:
  void Encode(const Slice& key, const Slice& value) {
    size_ += key.length() + value.length() + 32;
  }

  template <typename Which>
  void Encode(Which, const typename Which::ValueType& value) {
    Add(Which(), value);
  }

  void Encode(ContentTypeMetadata,
              const typename ContentTypeMetadata::ValueType& value) {
    if (value == ContentTypeMetadata::kInvalid) return;
    Add(ContentTypeMetadata(), value);
  }

  size_t size() const { return size_; }

 private:
  template <typename Which>
  void Add(Which, const typename Which::ValueType& value) {
    size_ += Which::key().length() + Which::Encode(value).length() + 32;
  }

  uint32_t size_ = 0;
};

class UnknownMap {
 public:
  using BackingType = std::vector<std::pair<Slice, Slice>>;

  void Append(absl::string_view key, Slice value);
  void Remove(absl::string_view key);
  std::optional<absl::string_view> GetStringValue(absl::string_view key,
                                                  std::string* backing) const;

  BackingType::const_iterator begin() const { return unknown_.cbegin(); }
  BackingType::const_iterator end() const { return unknown_.cend(); }

  template <typename Filterer>
  void Filter(Filterer* filter_fn) {
    unknown_.erase(
        std::remove_if(unknown_.begin(), unknown_.end(),
                       [&](auto& pair) {
                         return !(*filter_fn)(pair.first.as_string_view());
                       }),
        unknown_.end());
  }

  bool empty() const { return unknown_.empty(); }
  size_t size() const { return unknown_.size(); }
  void Clear() { unknown_.clear(); }

 private:

  BackingType unknown_;
};

template <template <typename, typename> class Factory,
          typename... MetadataTraits>
struct StatefulCompressor;

template <template <typename, typename> class Factory, typename MetadataTrait,
          bool kEncodable = IsEncodableTrait<MetadataTrait>::value>
struct SpecificStatefulCompressor;

template <template <typename, typename> class Factory, typename MetadataTrait>
struct SpecificStatefulCompressor<Factory, MetadataTrait, true>
    : public Factory<MetadataTrait, typename MetadataTrait::CompressionTraits> {
};

template <template <typename, typename> class Factory, typename MetadataTrait>
struct SpecificStatefulCompressor<Factory, MetadataTrait, false> {};

template <template <typename, typename> class Factory, typename MetadataTrait,
          typename... MetadataTraits>
struct StatefulCompressor<Factory, MetadataTrait, MetadataTraits...>
    : public SpecificStatefulCompressor<Factory, MetadataTrait>,
      public StatefulCompressor<Factory, MetadataTraits...> {};

template <template <typename, typename> class Factory>
struct StatefulCompressor<Factory> {};

}

template <typename Which>
absl::enable_if_t<std::is_same<typename Which::ValueType, Slice>::value,
                  const Slice&>
MetadataValueAsSlice(const Slice& slice) {
  return slice;
}

template <typename Which>
absl::enable_if_t<!std::is_same<typename Which::ValueType, Slice>::value, Slice>
MetadataValueAsSlice(typename Which::ValueType value) {
  return Slice(Which::Encode(value));
}

template <class Derived, typename... Traits>
class MetadataMap {
 public:
  MetadataMap() = default;
  ~MetadataMap();

  template <template <typename, typename> class Factory>
  using StatefulCompressor =
      metadata_detail::StatefulCompressor<Factory, Traits...>;

  MetadataMap(const MetadataMap&) = delete;
  MetadataMap& operator=(const MetadataMap&) = delete;
  MetadataMap(MetadataMap&&) noexcept;

  Derived& operator=(MetadataMap&&) noexcept;

  template <typename Encoder>
  void Encode(Encoder* encoder) const {
    table_.template ForEachIn<metadata_detail::EncodeWrapper<Encoder>,
                              Value<Traits>...>(
        metadata_detail::EncodeWrapper<Encoder>{encoder});
    for (const auto& unk : unknown_) {
      encoder->Encode(unk.first, unk.second);
    }
  }

  template <typename Encoder>
  void ForEach(Encoder* encoder) const {
    table_.ForEach(metadata_detail::ForEachWrapper<Encoder>{encoder});
    for (const auto& unk : unknown_) {
      encoder->Encode(unk.first, unk.second);
    }
  }

  void Log(metadata_detail::LogFn log_fn) const {
    table_.ForEach(metadata_detail::LogWrapper{log_fn});
    for (const auto& unk : unknown_) {
      log_fn(unk.first.as_string_view(), unk.second.as_string_view());
    }
  }

  template <typename Filterer>
  void Filter(Filterer filter_fn) {
    table_.template FilterIn<metadata_detail::FilterWrapper<Filterer>,
                             Value<Traits>...>(
        metadata_detail::FilterWrapper<Filterer>{filter_fn});
    unknown_.Filter<Filterer>(&filter_fn);
  }

  std::string DebugString() const {
    metadata_detail::DebugStringBuilder builder;
    Log([&builder](absl::string_view key, absl::string_view value) {
      builder.AddAfterRedaction(key, value);
    });
    return builder.TakeOutput();
  }

  template <typename Sink>
  friend void AbslStringify(Sink& sink, const MetadataMap& map) {
    sink.Append(map.DebugString());
  }

  template <typename Which>
  const typename metadata_detail::Value<Which>::StorageType* get_pointer(
      Which) const {
    if (auto* p = table_.template get<Value<Which>>()) return &p->value;
    return nullptr;
  }

  template <typename Which>
  typename metadata_detail::Value<Which>::StorageType* get_pointer(Which) {
    if (auto* p = table_.template get<Value<Which>>()) return &p->value;
    return nullptr;
  }

  template <typename Which>
  typename metadata_detail::Value<Which>::StorageType* GetOrCreatePointer(
      Which) {
    return &table_.template get_or_create<Value<Which>>()->value;
  }

  template <typename Which>
  std::optional<typename Which::ValueType> get(Which) const {
    if (auto* p = table_.template get<Value<Which>>()) return p->value;
    return std::nullopt;
  }

  template <typename Which, typename... Args>
  absl::enable_if_t<Which::kRepeatable == false, void> Set(Which,
                                                           Args&&... args) {
    table_.template set<Value<Which>>(std::forward<Args>(args)...);
  }
  template <typename Which, typename... Args>
  absl::enable_if_t<Which::kRepeatable == true, void> Set(Which,
                                                          Args&&... args) {
    GetOrCreatePointer(Which())->emplace_back(std::forward<Args>(args)...);
  }

  template <typename Which>
  void Remove(Which) {
    table_.template clear<Value<Which>>();
  }

  void Remove(absl::string_view key) {
    metadata_detail::RemoveHelper<Derived> helper(static_cast<Derived*>(this));
    metadata_detail::NameLookup<Traits...>::Lookup(key, &helper);
  }

  void Remove(const char* key) { Remove(absl::string_view(key)); }

  std::optional<absl::string_view> GetStringValue(absl::string_view name,
                                                  std::string* buffer) const {
    metadata_detail::GetStringValueHelper<Derived> helper(
        static_cast<const Derived*>(this), buffer);
    return metadata_detail::NameLookup<Traits...>::Lookup(name, &helper);
  }

  template <typename Which>
  absl::enable_if_t<Which::kRepeatable == false,
                    std::optional<typename Which::ValueType>>
  Take(Which which) {
    if (auto* p = get_pointer(which)) {
      std::optional<typename Which::ValueType> value(std::move(*p));
      Remove(which);
      return value;
    }
    return {};
  }

  template <typename Which>
  absl::enable_if_t<Which::kRepeatable == true,
                    typename metadata_detail::Value<Which>::StorageType>
  Take(Which which) {
    if (auto* p = get_pointer(which)) {
      typename Value<Which>::StorageType value = std::move(*p);
      Remove(which);
      return value;
    }
    return {};
  }

  static ParsedMetadata<Derived> Parse(absl::string_view key, Slice value,
                                       bool will_keep_past_request_lifetime,
                                       uint32_t transport_size,
                                       MetadataParseErrorFn on_error) {
    metadata_detail::ParseHelper<Derived> helper(
        value.TakeOwned(), will_keep_past_request_lifetime, on_error,
        transport_size);
    return metadata_detail::NameLookup<Traits...>::Lookup(key, &helper);
  }

  void Set(const ParsedMetadata<Derived>& m) {
    m.SetOnContainer(static_cast<Derived*>(this));
  }

  void Append(absl::string_view key, Slice value,
              MetadataParseErrorFn on_error) {
    metadata_detail::AppendHelper<Derived> helper(static_cast<Derived*>(this),
                                                  value.TakeOwned(), on_error);
    metadata_detail::NameLookup<Traits...>::Lookup(key, &helper);
  }

  void Clear();
  size_t TransportSize() const;
  Derived Copy() const;
  bool empty() const { return table_.empty() && unknown_.empty(); }
  size_t count() const { return table_.count() + unknown_.size(); }

 private:
  friend class metadata_detail::AppendHelper<Derived>;
  friend class metadata_detail::GetStringValueHelper<Derived>;
  friend class metadata_detail::RemoveHelper<Derived>;
  friend class metadata_detail::CopySink<Derived>;
  friend class ParsedMetadata<Derived>;

  template <typename Which>
  using Value = metadata_detail::Value<Which>;

  PackedTable<Value<Traits>...> table_;
  metadata_detail::UnknownMap unknown_;
};

template <typename Derived, typename... Args>
inline bool IsStatusOk(const MetadataMap<Derived, Args...>& m) {
  return m.get(GrpcStatusMetadata()).value_or(GRPC_STATUS_UNKNOWN) ==
         GRPC_STATUS_OK;
}

template <typename Derived, typename... Traits>
MetadataMap<Derived, Traits...>::MetadataMap(MetadataMap&& other) noexcept
    : table_(std::move(other.table_)), unknown_(std::move(other.unknown_)) {}

template <typename Derived, typename... Traits>
Derived& MetadataMap<Derived, Traits...>::operator=(
    MetadataMap&& other) noexcept {
  table_ = std::move(other.table_);
  unknown_ = std::move(other.unknown_);
  return static_cast<Derived&>(*this);
}

template <typename Derived, typename... Traits>
MetadataMap<Derived, Traits...>::~MetadataMap() = default;

template <typename Derived, typename... Traits>
void MetadataMap<Derived, Traits...>::Clear() {
  table_.ClearAll();
  unknown_.Clear();
}

template <typename Derived, typename... Traits>
size_t MetadataMap<Derived, Traits...>::TransportSize() const {
  metadata_detail::TransportSizeEncoder enc;
  Encode(&enc);
  return enc.size();
}

template <typename Derived, typename... Traits>
Derived MetadataMap<Derived, Traits...>::Copy() const {
  Derived out;
  metadata_detail::CopySink<Derived> sink(&out);
  ForEach(&sink);
  return out;
}

}

struct grpc_metadata_batch;

using grpc_metadata_batch_base = grpc_core::MetadataMap<
    grpc_metadata_batch,

    grpc_core::HttpPathMetadata, grpc_core::HttpAuthorityMetadata,
    grpc_core::HttpMethodMetadata, grpc_core::HttpStatusMetadata,
    grpc_core::HttpSchemeMetadata,

    grpc_core::ContentTypeMetadata, grpc_core::TeMetadata,
    grpc_core::GrpcEncodingMetadata, grpc_core::GrpcInternalEncodingRequest,
    grpc_core::GrpcAcceptEncodingMetadata, grpc_core::GrpcStatusMetadata,
    grpc_core::GrpcTimeoutMetadata, grpc_core::GrpcPreviousRpcAttemptsMetadata,
    grpc_core::GrpcRetryPushbackMsMetadata, grpc_core::UserAgentMetadata,
    grpc_core::GrpcMessageMetadata, grpc_core::HostMetadata,
    grpc_core::EndpointLoadMetricsBinMetadata,
    grpc_core::GrpcServerStatsBinMetadata, grpc_core::GrpcTraceBinMetadata,
    grpc_core::GrpcTagsBinMetadata, grpc_core::GrpcLbClientStatsMetadata,
    grpc_core::LbCostBinMetadata, grpc_core::LbTokenMetadata,
    grpc_core::XEnvoyPeerMetadata, grpc_core::W3CTraceParentMetadata,

    grpc_core::GrpcStreamNetworkState, grpc_core::PeerString,
    grpc_core::GrpcStatusContext, grpc_core::GrpcStatusFromWire,
    grpc_core::GrpcCallWasCancelled, grpc_core::WaitForReady,
    grpc_core::IsTransparentRetry, grpc_core::GrpcTrailersOnly,
    grpc_core::GrpcTarPit,
    grpc_core::GrpcRegisteredMethod GRPC_CUSTOM_CLIENT_METADATA
        GRPC_CUSTOM_SERVER_METADATA>;

struct grpc_metadata_batch : public grpc_metadata_batch_base {
  using grpc_metadata_batch_base::grpc_metadata_batch_base;
};

#endif
