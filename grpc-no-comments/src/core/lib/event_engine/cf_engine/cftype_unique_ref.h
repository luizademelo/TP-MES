// Copyright 2023 The gRPC Authors

#ifndef GRPC_SRC_CORE_LIB_EVENT_ENGINE_CF_ENGINE_CFTYPE_UNIQUE_REF_H
#define GRPC_SRC_CORE_LIB_EVENT_ENGINE_CF_ENGINE_CFTYPE_UNIQUE_REF_H
#include <grpc/support/port_platform.h>

#ifdef GPR_APPLE
#include <AvailabilityMacros.h>
#ifdef AVAILABLE_MAC_OS_X_VERSION_10_12_AND_LATER

#include <CoreFoundation/CoreFoundation.h>

namespace grpc_event_engine::experimental {

template <typename T>
class CFTypeUniqueRef {
  static_assert(std::is_convertible<T, CFTypeRef>::value,
                "T should be `CFXxxRef` type");

 public:

  CFTypeUniqueRef(T cf_type_ref = nullptr) : cf_type_ref_(cf_type_ref) {}
  ~CFTypeUniqueRef() { reset(); }

  CFTypeUniqueRef(CFTypeUniqueRef const&) = delete;
  CFTypeUniqueRef& operator=(CFTypeUniqueRef const&) = delete;

  CFTypeUniqueRef(CFTypeUniqueRef&& other) : cf_type_ref_(other.release()) {};
  CFTypeUniqueRef& operator=(CFTypeUniqueRef&& other) {
    reset(other.release());
    return *this;
  }

  operator T() { return cf_type_ref_; }

  // Note: this is for passing a CFTypeRef as output parameter to a CF API, the

  T* operator&() {
    reset();
    return &cf_type_ref_;
  }

  T release() {
    T old = cf_type_ref_;
    cf_type_ref_ = nullptr;
    return old;
  }

  void reset(T other = nullptr) {
    if (cf_type_ref_ == other) {
      return;
    }
    T old = cf_type_ref_;
    cf_type_ref_ = other;
    if (old) {
      CFRelease(old);
    }
  }

 private:
  T cf_type_ref_;
};

}

#endif
#endif

#endif
