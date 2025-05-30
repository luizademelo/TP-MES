// Copyright 2023 gRPC Authors

#ifndef GRPC_SRC_CORE_LIB_EVENT_ENGINE_QUERY_EXTENSIONS_H
#define GRPC_SRC_CORE_LIB_EVENT_ENGINE_QUERY_EXTENSIONS_H

#include <grpc/event_engine/event_engine.h>
#include <grpc/support/port_platform.h>

#include <type_traits>

#include "absl/strings/string_view.h"

namespace grpc_event_engine::experimental {

namespace endpoint_detail {

template <typename Querying, typename... Es>
struct QueryExtensionRecursion;

template <typename Querying, typename E, typename... Es>
struct QueryExtensionRecursion<Querying, E, Es...> {
  static void* Query(absl::string_view id, Querying* p) {
    if (id == E::EndpointExtensionName()) return static_cast<E*>(p);
    return QueryExtensionRecursion<Querying, Es...>::Query(id, p);
  }
};

template <typename Querying>
struct QueryExtensionRecursion<Querying> {
  static void* Query(absl::string_view, Querying*) { return nullptr; }
};

}

template <typename EEClass, typename... Exports>
class ExtendedType : public EEClass, public Exports... {
 public:
  void* QueryExtension(absl::string_view id) override {
    return endpoint_detail::QueryExtensionRecursion<ExtendedType,
                                                    Exports...>::Query(id,
                                                                       this);
  }
};

template <typename Extension, class ExtensibleClass>
std::enable_if_t<std::is_base_of_v<Extensible, ExtensibleClass>, Extension*>
QueryExtension(ExtensibleClass* extending_obj) {
  if (extending_obj == nullptr) return nullptr;
  return static_cast<Extension*>(
      extending_obj->QueryExtension(Extension::EndpointExtensionName()));
}

}

#endif
