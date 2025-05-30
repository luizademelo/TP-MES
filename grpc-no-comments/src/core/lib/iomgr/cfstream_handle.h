
// Copyright 2018 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_IOMGR_CFSTREAM_HANDLE_H
#define GRPC_SRC_CORE_LIB_IOMGR_CFSTREAM_HANDLE_H

#include <grpc/support/port_platform.h>

#include "src/core/lib/iomgr/port.h"

#ifdef GRPC_CFSTREAM
#import <CoreFoundation/CoreFoundation.h>

#include "src/core/lib/iomgr/closure.h"
#include "src/core/lib/iomgr/lockfree_event.h"
#include "src/core/util/memory.h"

class GrpcLibraryInitHolder {
 public:
  GrpcLibraryInitHolder();
  virtual ~GrpcLibraryInitHolder();
};

class CFStreamHandle : public GrpcLibraryInitHolder {
 public:
  static CFStreamHandle* CreateStreamHandle(CFReadStreamRef read_stream,
                                            CFWriteStreamRef write_stream);

  CFStreamHandle(CFReadStreamRef read_stream, CFWriteStreamRef write_stream);
  CFStreamHandle(const CFStreamHandle& ref) = delete;
  CFStreamHandle(CFStreamHandle&& ref) = delete;
  CFStreamHandle& operator=(const CFStreamHandle& rhs) = delete;
  ~CFStreamHandle() override;

  void NotifyOnOpen(grpc_closure* closure);
  void NotifyOnRead(grpc_closure* closure);
  void NotifyOnWrite(grpc_closure* closure);
  void Shutdown(grpc_error_handle error);

  void Ref(const char* file = "", int line = 0, const char* reason = nullptr);
  void Unref(const char* file = "", int line = 0, const char* reason = nullptr);

 private:
  static void ReadCallback(CFReadStreamRef stream, CFStreamEventType type,
                           void* client_callback_info);
  static void WriteCallback(CFWriteStreamRef stream, CFStreamEventType type,
                            void* client_callback_info);
  static void* Retain(void* info);
  static void Release(void* info);

  grpc_core::LockfreeEvent open_event_;
  grpc_core::LockfreeEvent read_event_;
  grpc_core::LockfreeEvent write_event_;

  dispatch_queue_t dispatch_queue_;

  gpr_refcount refcount_;
};

#ifdef DEBUG
#define CFSTREAM_HANDLE_REF(handle, reason) \
  (handle)->Ref(__FILE__, __LINE__, (reason))
#define CFSTREAM_HANDLE_UNREF(handle, reason) \
  (handle)->Unref(__FILE__, __LINE__, (reason))
#else
#define CFSTREAM_HANDLE_REF(handle, reason) (handle)->Ref()
#define CFSTREAM_HANDLE_UNREF(handle, reason) (handle)->Unref()
#endif

#endif

#endif
