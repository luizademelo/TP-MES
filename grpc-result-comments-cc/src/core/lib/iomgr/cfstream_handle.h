Here's the commented version of the code:

```c++
// Copyright 2018 gRPC authors.

// Header guard to prevent multiple inclusions
#ifndef GRPC_SRC_CORE_LIB_IOMGR_CFSTREAM_HANDLE_H
#define GRPC_SRC_CORE_LIB_IOMGR_CFSTREAM_HANDLE_H

#include <grpc/support/port_platform.h>  // Platform-specific configuration

#include "src/core/lib/iomgr/port.h"    // I/O manager port configuration

// Only include this implementation if CFStream is enabled
#ifdef GRPC_CFSTREAM
#import <CoreFoundation/CoreFoundation.h>  // CoreFoundation framework for CFStream

#include "src/core/lib/iomgr/closure.h"    // gRPC closure utilities
#include "src/core/lib/iomgr/lockfree_event.h"  // Lock-free event implementation
#include "src/core/util/memory.h"          // Memory utilities

// RAII class to ensure gRPC library initialization
class GrpcLibraryInitHolder {
 public:
  GrpcLibraryInitHolder();      // Constructor initializes gRPC library
  virtual ~GrpcLibraryInitHolder();  // Destructor cleans up gRPC library
};

// Class for managing CoreFoundation stream handles with gRPC integration
class CFStreamHandle : public GrpcLibraryInitHolder {
 public:
  // Factory method to create a new CFStreamHandle instance
  static CFStreamHandle* CreateStreamHandle(CFReadStreamRef read_stream,
                                            CFWriteStreamRef write_stream);

  // Constructor taking read and write streams
  CFStreamHandle(CFReadStreamRef read_stream, CFWriteStreamRef write_stream);
  // Disable copy and move constructors/assignment
  CFStreamHandle(const CFStreamHandle& ref) = delete;
  CFStreamHandle(CFStreamHandle&& ref) = delete;
  CFStreamHandle& operator=(const CFStreamHandle& rhs) = delete;
  ~CFStreamHandle() override;  // Destructor cleans up resources

  // Methods to register callbacks for stream events
  void NotifyOnOpen(grpc_closure* closure);   // Called when stream opens
  void NotifyOnRead(grpc_closure* closure);   // Called when read is available
  void NotifyOnWrite(grpc_closure* closure);  // Called when write is possible
  void Shutdown(grpc_error_handle error);     // Shuts down the stream

  // Reference counting methods with optional debug information
  void Ref(const char* file = "", int line = 0, const char* reason = nullptr);
  void Unref(const char* file = "", int line = 0, const char* reason = nullptr);

 private:
  // Static callback methods for CFStream events
  static void ReadCallback(CFReadStreamRef stream, CFStreamEventType type,
                           void* client_callback_info);
  static void WriteCallback(CFWriteStreamRef stream, CFStreamEventType type,
                            void* client_callback_info);
  
  // Memory management callbacks for CFStream context
  static void* Retain(void* info);  // Called when context is retained
  static void Release(void* info);  // Called when context is released

  // Lock-free events for stream state tracking
  grpc_core::LockfreeEvent open_event_;   // Tracks open state
  grpc_core::LockfreeEvent read_event_;   // Tracks read availability
  grpc_core::LockfreeEvent write_event_;  // Tracks write availability

  dispatch_queue_t dispatch_queue_;  // GCD queue for handling callbacks

  gpr_refcount refcount_;  // Reference counter for the handle
};

// Debug and non-debug versions of ref/unref macros
#ifdef DEBUG
// Debug version includes file, line, and reason information
#define CFSTREAM_HANDLE_REF(handle, reason) \
  (handle)->Ref(__FILE__, __LINE__, (reason))
#define CFSTREAM_HANDLE_UNREF(handle, reason) \
  (handle)->Unref(__FILE__, __LINE__, (reason))
#else
// Non-debug version is simplified
#define CFSTREAM_HANDLE_REF(handle, reason) (handle)->Ref()
#define CFSTREAM_HANDLE_UNREF(handle, reason) (handle)->Unref()
#endif

#endif  // GRPC_CFSTREAM

#endif  // GRPC_SRC_CORE_LIB_IOMGR_CFSTREAM_HANDLE_H
```