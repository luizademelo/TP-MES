
// Copyright 2023 gRPC authors.

#ifndef GRPC_SRC_CORE_UTIL_REF_COUNTED_STRING_H
#define GRPC_SRC_CORE_UTIL_REF_COUNTED_STRING_H

#include <grpc/support/port_platform.h>
#include <stddef.h>

#include <string>

#include "absl/strings/string_view.h"
#include "src/core/util/ref_counted.h"
#include "src/core/util/ref_counted_ptr.h"

namespace grpc_core {

class RefCountedString {
 public:
  static RefCountedPtr<RefCountedString> Make(absl::string_view src);

  RefCountedString(const RefCountedString&) = delete;
  RefCountedString& operator=(const RefCountedString&) = delete;

  RefCountedPtr<RefCountedString> Ref() {
    IncrementRefCount();
    return RefCountedPtr<RefCountedString>(this);
  }
  void Unref() {
    if (header_.rc.Unref()) Destroy();
  }

  absl::string_view as_string_view() const {
    return absl::string_view(payload_, header_.length);
  }

  char* c_str() { return payload_; }

 private:

  template <typename T>
  friend class RefCountedPtr;

  explicit RefCountedString(absl::string_view src);
  void IncrementRefCount() { header_.rc.Ref(); }
  void Destroy();

  struct Header {
    RefCount rc;
    size_t length;
  };
  Header header_;
  char payload_[];
};

class RefCountedStringValue {
 public:
  RefCountedStringValue() : str_{} {}
  explicit RefCountedStringValue(absl::string_view str)
      : str_(RefCountedString::Make(str)) {}

  absl::string_view as_string_view() const {
    return str_ == nullptr ? absl::string_view() : str_->as_string_view();
  }

  const char* c_str() const { return str_ == nullptr ? "" : str_->c_str(); }

 private:
  RefCountedPtr<RefCountedString> str_;
};

inline bool operator==(const RefCountedStringValue& lhs,
                       absl::string_view rhs) {
  return lhs.as_string_view() == rhs;
}
inline bool operator==(absl::string_view lhs,
                       const RefCountedStringValue& rhs) {
  return lhs == rhs.as_string_view();
}
inline bool operator==(const RefCountedStringValue& lhs,
                       const RefCountedStringValue& rhs) {
  return lhs.as_string_view() == rhs.as_string_view();
}

inline bool operator!=(const RefCountedStringValue& lhs,
                       absl::string_view rhs) {
  return lhs.as_string_view() != rhs;
}
inline bool operator!=(absl::string_view lhs,
                       const RefCountedStringValue& rhs) {
  return lhs != rhs.as_string_view();
}
inline bool operator!=(const RefCountedStringValue& lhs,
                       const RefCountedStringValue& rhs) {
  return lhs.as_string_view() != rhs.as_string_view();
}

inline bool operator<(const RefCountedStringValue& lhs, absl::string_view rhs) {
  return lhs.as_string_view() < rhs;
}
inline bool operator<(absl::string_view lhs, const RefCountedStringValue& rhs) {
  return lhs < rhs.as_string_view();
}
inline bool operator<(const RefCountedStringValue& lhs,
                      const RefCountedStringValue& rhs) {
  return lhs.as_string_view() < rhs.as_string_view();
}

inline bool operator>(const RefCountedStringValue& lhs, absl::string_view rhs) {
  return lhs.as_string_view() > rhs;
}
inline bool operator>(absl::string_view lhs, const RefCountedStringValue& rhs) {
  return lhs > rhs.as_string_view();
}
inline bool operator>(const RefCountedStringValue& lhs,
                      const RefCountedStringValue& rhs) {
  return lhs.as_string_view() > rhs.as_string_view();
}

struct RefCountedStringValueLessThan {
  using is_transparent = void;
  bool operator()(const RefCountedStringValue& lhs,
                  const RefCountedStringValue& rhs) const {
    return lhs < rhs;
  }
  bool operator()(absl::string_view lhs,
                  const RefCountedStringValue& rhs) const {
    return lhs < rhs;
  }
  bool operator()(const RefCountedStringValue& lhs,
                  absl::string_view rhs) const {
    return lhs < rhs;
  }
};

}

#endif
