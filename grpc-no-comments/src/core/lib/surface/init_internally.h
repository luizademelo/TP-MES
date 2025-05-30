// Copyright 2022 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_SURFACE_INIT_INTERNALLY_H
#define GRPC_SRC_CORE_LIB_SURFACE_INIT_INTERNALLY_H

namespace grpc_core {

extern void (*InitInternally)();
extern void (*ShutdownInternally)();
extern bool (*IsInitializedInternally)();

class KeepsGrpcInitialized {
 public:
  explicit KeepsGrpcInitialized(bool enabled = true) : enabled_(enabled) {
    if (enabled_) {
      InitInternally();
    }
  }
  ~KeepsGrpcInitialized() {
    if (enabled_) {
      ShutdownInternally();
    }
  }
  KeepsGrpcInitialized(const KeepsGrpcInitialized&) = delete;
  KeepsGrpcInitialized& operator=(const KeepsGrpcInitialized&) = delete;

 private:
  bool enabled_;
};

}

#endif
