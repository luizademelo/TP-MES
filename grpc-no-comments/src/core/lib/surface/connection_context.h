
// Copyright 2024 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_SURFACE_CONNECTION_CONTEXT_H
#define GRPC_SRC_CORE_LIB_SURFACE_CONNECTION_CONTEXT_H

#include <grpc/support/port_platform.h>
#include <stddef.h>

#include <cstdint>
#include <vector>

#include "src/core/util/no_destruct.h"
#include "src/core/util/orphanable.h"

namespace grpc_core {

class ConnectionContext;

template <typename T>
struct ConnectionContextProperty;

namespace connection_context_detail {

class BaseConnectionContextPropertiesTraits {
 public:

  static uint16_t NumProperties() {
    return static_cast<uint16_t>(RegisteredTraits().size());
  }

  static size_t Size() { return NumProperties() * sizeof(void*); }

  static void Destroy(uint16_t id, void* ptr) {
    if (ptr == nullptr) return;
    RegisteredTraits()[id](ptr);
  }

  template <typename T>
  static uint16_t AllocateId(void (*destroy)(void* ptr)) {
    auto& traits = RegisteredTraits();
    const uint16_t id = static_cast<uint16_t>(traits.size());
    traits.push_back(destroy);
    return id;
  }

 private:

  static std::vector<void (*)(void*)>& RegisteredTraits() {
    static NoDestruct<std::vector<void (*)(void*)>> registered_traits;
    return *registered_traits;
  }
};

template <typename T>
class ConnectionContextPropertiesTraits
    : public BaseConnectionContextPropertiesTraits {
 public:
  static uint16_t id() { return id_; }
  template <typename... Args>
  static T* Construct(Args&&... args) {
    return new T(std::forward<Args>(args)...);
  }
  static void Destruct(void* p) { delete reinterpret_cast<T*>(p); }

 protected:
  static const uint16_t id_;
};

template <typename T>
const uint16_t ConnectionContextPropertiesTraits<T>::id_ =
    BaseConnectionContextPropertiesTraits::AllocateId<T>(
        ConnectionContextPropertiesTraits<T>::Destruct);

}

class ConnectionContext final : public Orphanable {
 public:
  static OrphanablePtr<ConnectionContext> Create();

  template <typename Which, typename... Args>
  bool EmplaceIfUnset(Args&&... args) {
    using Traits =
        connection_context_detail::ConnectionContextPropertiesTraits<Which>;
    Which* value = static_cast<Which*>(registered_properties()[Traits::id()]);
    if (value == nullptr) {
      registered_properties()[Traits::id()] = Traits::Construct(args...);
      return true;
    }
    return false;
  }

  template <typename Which, typename... Args>
  void Update(Args&&... args) {
    using Traits =
        connection_context_detail::ConnectionContextPropertiesTraits<Which>;
    Which* prev = static_cast<Which*>(registered_properties()[Traits::id()]);
    if (prev != nullptr) {
      Traits::Destroy(Traits::id(), prev);
    }
    registered_properties()[Traits::id()] = Traits::Construct(args...);
  }

  template <typename Which>
  const Which* Get() {
    return static_cast<Which*>(
        registered_properties()
            [connection_context_detail::ConnectionContextPropertiesTraits<
                Which>::id()]);
  }

  void Orphan() override;

  ~ConnectionContext() override;

 private:
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION void** registered_properties() {
    return reinterpret_cast<void**>(this + 1);
  }

  ConnectionContext();
};

}

#endif
