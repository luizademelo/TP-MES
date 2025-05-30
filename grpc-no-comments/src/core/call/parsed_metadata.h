// Copyright 2021 gRPC authors.

#ifndef GRPC_SRC_CORE_CALL_PARSED_METADATA_H
#define GRPC_SRC_CORE_CALL_PARSED_METADATA_H

#include <grpc/slice.h>
#include <grpc/support/port_platform.h>
#include <string.h>

#include <cstdint>
#include <string>
#include <type_traits>
#include <utility>

#include "absl/functional/function_ref.h"
#include "absl/meta/type_traits.h"
#include "absl/strings/escaping.h"
#include "absl/strings/match.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/string_view.h"
#include "src/core/lib/slice/slice.h"
#include "src/core/util/time.h"

namespace grpc_core {

using MetadataParseErrorFn =
    absl::FunctionRef<void(absl::string_view error, const Slice& value)>;

namespace metadata_detail {

template <typename Which>
struct HasSimpleMemento {
  static constexpr bool value =
      (std::is_trivial<typename Which::MementoType>::value &&
       sizeof(typename Which::MementoType) <= sizeof(grpc_slice)) ||
      std::is_same<typename Which::MementoType, Duration>::value;
};

union Buffer {
  uint8_t trivial[sizeof(grpc_slice)];
  void* pointer;
  grpc_slice slice;
};

std::string MakeDebugString(absl::string_view key, absl::string_view value);

template <typename Field, typename CompatibleWithField, typename Display>
GPR_ATTRIBUTE_NOINLINE std::string MakeDebugStringPipeline(
    absl::string_view key, const Buffer& value,
    Field (*field_from_buffer)(const Buffer&),
    Display (*display_from_field)(CompatibleWithField)) {
  return MakeDebugString(
      key, absl::StrCat(display_from_field(field_from_buffer(value))));
}

template <typename Field>
Field FieldFromTrivial(const Buffer& value) {
  Field field;
  memcpy(&field, value.trivial, sizeof(Field));
  return field;
}

template <typename Field>
Field FieldFromPointer(const Buffer& value) {
  return *static_cast<const Field*>(value.pointer);
}

Slice SliceFromBuffer(const Buffer& buffer);

void DestroySliceValue(const Buffer& value);

void DestroyTrivialMemento(const Buffer& value);

template <Slice (*MementoToValue)(Slice)>
void SetSliceValue(Slice* set, const Buffer& value) {
  *set = MementoToValue(SliceFromBuffer(value));
}

}

template <typename MetadataContainer>
class ParsedMetadata {
 public:

  template <typename Which>
  ParsedMetadata(
      Which,
      absl::enable_if_t<metadata_detail::HasSimpleMemento<Which>::value,
                        typename Which::MementoType>
          value,
      uint32_t transport_size)
      : vtable_(ParsedMetadata::template TrivialTraitVTable<Which>()),
        transport_size_(transport_size) {
    memcpy(value_.trivial, &value, sizeof(value));
  }
  template <typename Which>
  ParsedMetadata(
      Which,
      absl::enable_if_t<
          !metadata_detail::HasSimpleMemento<Which>::value &&
              !std::is_convertible<typename Which::MementoType, Slice>::value,
          typename Which::MementoType>
          value,
      uint32_t transport_size)
      : vtable_(ParsedMetadata::template NonTrivialTraitVTable<Which>()),
        transport_size_(transport_size) {
    value_.pointer = new typename Which::MementoType(std::move(value));
  }

  template <typename Which>
  ParsedMetadata(Which, Slice value, uint32_t transport_size)
      : vtable_(ParsedMetadata::template SliceTraitVTable<Which>()),
        transport_size_(transport_size) {
    value_.slice = value.TakeCSlice();
  }

  struct FromSlicePair {};
  ParsedMetadata(FromSlicePair, Slice key, Slice value, uint32_t transport_size)
      : vtable_(ParsedMetadata::KeyValueVTable(key.as_string_view())),
        transport_size_(transport_size) {
    value_.pointer =
        new std::pair<Slice, Slice>(std::move(key), std::move(value));
  }
  ParsedMetadata() : vtable_(EmptyVTable()), transport_size_(0) {}
  ~ParsedMetadata() { vtable_->destroy(value_); }

  ParsedMetadata(const ParsedMetadata&) = delete;
  ParsedMetadata& operator=(const ParsedMetadata&) = delete;
  ParsedMetadata(ParsedMetadata&& other) noexcept
      : vtable_(other.vtable_),
        value_(other.value_),
        transport_size_(other.transport_size_) {
    other.vtable_ = EmptyVTable();
  }
  ParsedMetadata& operator=(ParsedMetadata&& other) noexcept {
    vtable_ = other.vtable_;
    value_ = other.value_;
    transport_size_ = other.transport_size_;
    other.vtable_ = EmptyVTable();
    return *this;
  }

  void SetOnContainer(MetadataContainer* container) const {
    vtable_->set(value_, container);
  }

  bool is_binary_header() const { return vtable_->is_binary_header; }

  uint32_t transport_size() const { return transport_size_; }

  ParsedMetadata WithNewValue(Slice value, bool will_keep_past_request_lifetime,
                              uint32_t value_wire_size,
                              MetadataParseErrorFn on_error) const {
    ParsedMetadata result;
    result.vtable_ = vtable_;
    result.value_ = value_;
    result.transport_size_ =
        TransportSize(static_cast<uint32_t>(key().length()), value_wire_size);
    vtable_->with_new_value(&value, will_keep_past_request_lifetime, on_error,
                            &result);
    return result;
  }
  std::string DebugString() const { return vtable_->debug_string(value_); }
  absl::string_view key() const {
    if (vtable_->key == nullptr) return vtable_->key_value;
    return vtable_->key(value_);
  }

  static uint32_t TransportSize(uint32_t key_size, uint32_t value_size) {

    return key_size + value_size + 32;
  }

 private:
  using Buffer = metadata_detail::Buffer;

  struct VTable {
    const bool is_binary_header;
    void (*const destroy)(const Buffer& value);
    void (*const set)(const Buffer& value, MetadataContainer* container);

    void (*const with_new_value)(Slice* new_value,
                                 bool will_keep_past_request_lifetime,
                                 MetadataParseErrorFn on_error,
                                 ParsedMetadata* result);
    std::string (*const debug_string)(const Buffer& value);

    absl::string_view key_value;
    absl::string_view (*const key)(const Buffer& value);
  };

  static const VTable* EmptyVTable();
  static const VTable* KeyValueVTable(absl::string_view key);
  template <typename Which>
  static const VTable* TrivialTraitVTable();
  template <typename Which>
  static const VTable* NonTrivialTraitVTable();
  template <typename Which>
  static const VTable* SliceTraitVTable();

  template <Slice (*ParseMemento)(Slice, bool, MetadataParseErrorFn)>
  GPR_ATTRIBUTE_NOINLINE static void WithNewValueSetSlice(
      Slice* slice, bool will_keep_past_request_lifetime,
      MetadataParseErrorFn on_error, ParsedMetadata* result) {
    result->value_.slice =
        ParseMemento(std::move(*slice), will_keep_past_request_lifetime,
                     on_error)
            .TakeCSlice();
  }

  template <typename T, T (*ParseMemento)(Slice, bool, MetadataParseErrorFn)>
  GPR_ATTRIBUTE_NOINLINE static void WithNewValueSetTrivial(
      Slice* slice, bool will_keep_past_request_lifetime,
      MetadataParseErrorFn on_error, ParsedMetadata* result) {
    T memento = ParseMemento(std::move(*slice), will_keep_past_request_lifetime,
                             on_error);
    memcpy(result->value_.trivial, &memento, sizeof(memento));
  }

  const VTable* vtable_;
  Buffer value_;
  uint32_t transport_size_;
};

namespace metadata_detail {}

template <typename MetadataContainer>
const typename ParsedMetadata<MetadataContainer>::VTable*
ParsedMetadata<MetadataContainer>::EmptyVTable() {
  static const VTable vtable = {
      false,

      metadata_detail::DestroyTrivialMemento,

      [](const Buffer&, MetadataContainer*) {},

      [](Slice*, bool, MetadataParseErrorFn, ParsedMetadata*) {},

      [](const Buffer&) -> std::string { return "empty"; },

      "",
      nullptr,
  };
  return &vtable;
}

template <typename MetadataContainer>
template <typename Which>
const typename ParsedMetadata<MetadataContainer>::VTable*
ParsedMetadata<MetadataContainer>::TrivialTraitVTable() {
  static const VTable vtable = {
      absl::EndsWith(Which::key(), "-bin"),

      metadata_detail::DestroyTrivialMemento,

      [](const Buffer& value, MetadataContainer* map) {
        map->Set(
            Which(),
            Which::MementoToValue(
                metadata_detail::FieldFromTrivial<typename Which::MementoType>(
                    value)));
      },

      WithNewValueSetTrivial<typename Which::MementoType, Which::ParseMemento>,

      [](const Buffer& value) {
        return metadata_detail::MakeDebugStringPipeline(
            Which::key(), value,
            metadata_detail::FieldFromTrivial<typename Which::MementoType>,
            Which::DisplayMemento);
      },

      Which::key(),
      nullptr,
  };
  return &vtable;
}

template <typename MetadataContainer>
template <typename Which>
const typename ParsedMetadata<MetadataContainer>::VTable*
ParsedMetadata<MetadataContainer>::NonTrivialTraitVTable() {
  static const VTable vtable = {
      absl::EndsWith(Which::key(), "-bin"),

      [](const Buffer& value) {
        delete static_cast<typename Which::MementoType*>(value.pointer);
      },

      [](const Buffer& value, MetadataContainer* map) {
        auto* p = static_cast<typename Which::MementoType*>(value.pointer);
        map->Set(Which(), Which::MementoToValue(*p));
      },

      [](Slice* value, bool will_keep_past_request_lifetime,
         MetadataParseErrorFn on_error, ParsedMetadata* result) {
        result->value_.pointer =
            new typename Which::MementoType(Which::ParseMemento(
                std::move(*value), will_keep_past_request_lifetime, on_error));
      },

      [](const Buffer& value) {
        return metadata_detail::MakeDebugStringPipeline(
            Which::key(), value,
            metadata_detail::FieldFromPointer<typename Which::MementoType>,
            Which::DisplayMemento);
      },

      Which::key(),
      nullptr,
  };
  return &vtable;
}

template <typename MetadataContainer>
template <typename Which>
const typename ParsedMetadata<MetadataContainer>::VTable*
ParsedMetadata<MetadataContainer>::SliceTraitVTable() {
  static const VTable vtable = {
      absl::EndsWith(Which::key(), "-bin"),

      metadata_detail::DestroySliceValue,

      [](const Buffer& value, MetadataContainer* map) {
        metadata_detail::SetSliceValue<Which::MementoToValue>(
            map->GetOrCreatePointer(Which()), value);
      },

      WithNewValueSetSlice<Which::ParseMemento>,

      [](const Buffer& value) {
        return metadata_detail::MakeDebugStringPipeline(
            Which::key(), value, metadata_detail::SliceFromBuffer,
            Which::DisplayMemento);
      },

      Which::key(),
      nullptr,
  };
  return &vtable;
}

template <typename MetadataContainer>
const typename ParsedMetadata<MetadataContainer>::VTable*
ParsedMetadata<MetadataContainer>::KeyValueVTable(absl::string_view key) {
  using KV = std::pair<Slice, Slice>;
  static const auto destroy = [](const Buffer& value) {
    delete static_cast<KV*>(value.pointer);
  };
  static const auto set = [](const Buffer& value, MetadataContainer* map) {
    auto* p = static_cast<KV*>(value.pointer);
    map->unknown_.Append(p->first.as_string_view(), p->second.Ref());
  };
  static const auto with_new_value =
      [](Slice* value, bool will_keep_past_request_lifetime,
         MetadataParseErrorFn, ParsedMetadata* result) {
        auto* p = new KV{
            static_cast<KV*>(result->value_.pointer)->first.Ref(),
            will_keep_past_request_lifetime ? value->TakeUniquelyOwned()
                                            : std::move(*value),
        };
        result->value_.pointer = p;
      };
  static const auto debug_string = [](const Buffer& value) {
    auto* p = static_cast<KV*>(value.pointer);
    return absl::StrCat(p->first.as_string_view(), ": ",
                        p->second.as_string_view());
  };
  static const auto binary_debug_string = [](const Buffer& value) {
    auto* p = static_cast<KV*>(value.pointer);
    return absl::StrCat(p->first.as_string_view(), ": \"",
                        absl::CEscape(p->second.as_string_view()), "\"");
  };
  static const auto key_fn = [](const Buffer& value) {
    return static_cast<KV*>(value.pointer)->first.as_string_view();
  };
  static const VTable vtable[2] = {
      {false, destroy, set, with_new_value, debug_string, "", key_fn},
      {true, destroy, set, with_new_value, binary_debug_string, "", key_fn},
  };
  return &vtable[absl::EndsWith(key, "-bin")];
}

}

#endif
