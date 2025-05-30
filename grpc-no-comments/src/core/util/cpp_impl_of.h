// Copyright 2021 gRPC authors.

#ifndef GRPC_SRC_CORE_UTIL_CPP_IMPL_OF_H
#define GRPC_SRC_CORE_UTIL_CPP_IMPL_OF_H

namespace grpc_core {

template <typename CppType, typename CType>
class CppImplOf {
 public:

  static CppType* FromC(CType* c_type) {
    return reinterpret_cast<CppType*>(c_type);
  }

  static const CppType* FromC(const CType* c_type) {
    return reinterpret_cast<const CppType*>(c_type);
  }

  CType* c_ptr() {
    return reinterpret_cast<CType*>(static_cast<CppType*>(this));
  }

 protected:
  ~CppImplOf() = default;
};

}

#endif
