Here's the commented version of the code:

```c++
// Copyright 2018 gRPC authors.

// Include necessary platform-specific headers and libraries
#include <grpc/support/port_platform.h>

// Include core gRPC I/O manager and utility headers
#include "src/core/lib/iomgr/port.h"
#include "src/core/util/memory.h"

// Only compile this code if GRPC_CFSTREAM is defined (Apple CoreFoundation streams support)
#ifdef GRPC_CFSTREAM
// Import Apple CoreFoundation framework
#import <CoreFoundation/CoreFoundation.h>
#include <grpc/grpc.h>
#include <grpc/support/atm.h>
#include <grpc/support/sync.h>

#include "absl/log/log.h"
#include "src/core/lib/debug/trace.h"
#import "src/core/lib/iomgr/cfstream_handle.h"
#include "src/core/lib/iomgr/closure.h"
#include "src/core/lib/iomgr/error_cfstream.h"
#include "src/core/lib/iomgr/ev_apple.h"
#include "src/core/lib/iomgr/exec_ctx.h"

// RAII wrapper for gRPC library initialization
GrpcLibraryInitHolder::GrpcLibraryInitHolder() { grpc_init(); }
GrpcLibraryInitHolder::~GrpcLibraryInitHolder() { grpc_shutdown(); }

// CoreFoundation callback functions for memory management
void* CFStreamHandle::Retain(void* info) {
  CFStreamHandle* handle = static_cast<CFStreamHandle*>(info);
  CFSTREAM_HANDLE_REF(handle, "retain");  // Increment reference count
  return info;
}

void CFStreamHandle::Release(void* info) {
  CFStreamHandle* handle = static_cast<CFStreamHandle*>(info);
  CFSTREAM_HANDLE_UNREF(handle, "release");  // Decrement reference count
}

// Factory method to create a new CFStreamHandle instance
CFStreamHandle* CFStreamHandle::CreateStreamHandle(
    CFReadStreamRef read_stream, CFWriteStreamRef write_stream) {
  return new CFStreamHandle(read_stream, write_stream);
}

// Callback for read stream events
void CFStreamHandle::ReadCallback(CFReadStreamRef stream,
                                  CFStreamEventType type,
                                  void* client_callback_info) {
  grpc_core::ExecCtx exec_ctx;  // Execution context for gRPC operations
  grpc_error_handle error;
  CFErrorRef stream_error;
  CFStreamHandle* handle = static_cast<CFStreamHandle*>(client_callback_info);
  
  // Log callback details for debugging
  GRPC_TRACE_VLOG(tcp, 2) << "CFStream ReadCallback (" << handle << ", "
                          << stream << ", " << type << ", "
                          << client_callback_info << ")";
  
  // Handle different types of stream events
  switch (type) {
    case kCFStreamEventOpenCompleted:
      handle->open_event_.SetReady();  // Stream opened successfully
      break;
    case kCFStreamEventHasBytesAvailable:
    case kCFStreamEventEndEncountered:
      handle->read_event_.SetReady();  // Data available or stream ended
      break;
    case kCFStreamEventErrorOccurred:
      // Handle stream error and propagate shutdown
      stream_error = CFReadStreamCopyError(stream);
      error = grpc_error_set_int(
          GRPC_ERROR_CREATE_FROM_CFERROR(stream_error, "read error"),
          grpc_core::StatusIntProperty::kRpcStatus, GRPC_STATUS_UNAVAILABLE);
      CFRelease(stream_error);
      handle->open_event_.SetShutdown(error);
      handle->write_event_.SetShutdown(error);
      handle->read_event_.SetShutdown(error);
      break;
    default:
      GPR_UNREACHABLE_CODE(return);  // Unexpected event type
  }
}

// Callback for write stream events
void CFStreamHandle::WriteCallback(CFWriteStreamRef stream,
                                   CFStreamEventType type,
                                   void* clientCallBackInfo) {
  grpc_core::ExecCtx exec_ctx;  // Execution context for gRPC operations
  grpc_error_handle error;
  CFErrorRef stream_error;
  CFStreamHandle* handle = static_cast<CFStreamHandle*>(clientCallBackInfo);
  
  // Log callback details for debugging
  GRPC_TRACE_VLOG(tcp, 2) << "CFStream WriteCallback (" << handle << ", "
                          << stream << ", " << type << ", "
                          << clientCallBackInfo << ")";
  
  // Handle different types of stream events
  switch (type) {
    case kCFStreamEventOpenCompleted:
      handle->open_event_.SetReady();  // Stream opened successfully
      break;
    case kCFStreamEventCanAcceptBytes:
    case kCFStreamEventEndEncountered:
      handle->write_event_.SetReady();  // Ready to write or stream ended
      break;
    case kCFStreamEventErrorOccurred:
      // Handle stream error and propagate shutdown
      stream_error = CFWriteStreamCopyError(stream);
      error = grpc_error_set_int(
          GRPC_ERROR_CREATE_FROM_CFERROR(stream_error, "write error"),
          grpc_core::StatusIntProperty::kRpcStatus, GRPC_STATUS_UNAVAILABLE);
      CFRelease(stream_error);
      handle->open_event_.SetShutdown(error);
      handle->write_event_.SetShutdown(error);
      handle->read_event_.SetShutdown(error);
      break;
    default:
      GPR_UNREACHABLE_CODE(return);  // Unexpected event type
  }
}

// Constructor for CFStreamHandle
CFStreamHandle::CFStreamHandle(CFReadStreamRef read_stream,
                               CFWriteStreamRef write_stream) {
  // Initialize reference count and events
  gpr_ref_init(&refcount_, 1);
  open_event_.InitEvent();
  read_event_.InitEvent();
  write_event_.InitEvent();
  
  // Create serial dispatch queue for stream operations
  dispatch_queue_ = dispatch_queue_create(nullptr, DISPATCH_QUEUE_SERIAL);
  
  // Set up client context with retain/release callbacks
  CFStreamClientContext ctx = {0, static_cast<void*>(this),
                               CFStreamHandle::Retain, CFStreamHandle::Release,
                               nil};
  
  // Register callbacks for read stream events
  CFReadStreamSetClient(
      read_stream,
      kCFStreamEventOpenCompleted | kCFStreamEventHasBytesAvailable |
          kCFStreamEventErrorOccurred | kCFStreamEventEndEncountered,
      CFStreamHandle::ReadCallback, &ctx);
  
  // Register callbacks for write stream events
  CFWriteStreamSetClient(
      write_stream,
      kCFStreamEventOpenCompleted | kCFStreamEventCanAcceptBytes |
          kCFStreamEventErrorOccurred | kCFStreamEventEndEncountered,
      CFStreamHandle::WriteCallback, &ctx);
  
  // Register streams with gRPC Apple event system
  grpc_apple_register_read_stream(read_stream, dispatch_queue_);
  grpc_apple_register_write_stream(write_stream, dispatch_queue_);
}

// Destructor for CFStreamHandle
CFStreamHandle::~CFStreamHandle() {
  // Clean up events and dispatch queue
  open_event_.DestroyEvent();
  read_event_.DestroyEvent();
  write_event_.DestroyEvent();
  dispatch_release(dispatch_queue_);
}

// Methods to register callbacks for stream events
void CFStreamHandle::NotifyOnOpen(grpc_closure* closure) {
  open_event_.NotifyOn(closure);
}

void CFStreamHandle::NotifyOnRead(grpc_closure* closure) {
  read_event_.NotifyOn(closure);
}

void CFStreamHandle::NotifyOnWrite(grpc_closure* closure) {
  write_event_.NotifyOn(closure);
}

// Shutdown method to propagate errors to all events
void CFStreamHandle::Shutdown(grpc_error_handle error) {
  open_event_.SetShutdown(error);
  read_event_.SetShutdown(error);
  write_event_.SetShutdown(error);
}

// Reference counting methods with debug logging
void CFStreamHandle::Ref(const char* file, int line, const char* reason) {
  if (GRPC_TRACE_FLAG_ENABLED(tcp)) {
    gpr_atm val = gpr_atm_no_barrier_load(&refcount_.count);
    VLOG(2).AtLocation(file, line) << "CFStream Handle ref " << this << " : "
                                   << reason << " " << val << " -> " << val + 1;
  }
  gpr_ref(&refcount_);
}

void CFStreamHandle::Unref(const char* file, int line, const char* reason) {
  if (GRPC_TRACE_FLAG_ENABLED(tcp)) {
    gpr_atm val = gpr_atm_no_barrier_load(&refcount_.count);
    VLOG(2).AtLocation(file, line) << "CFStream Handle unref " << this << " : "
                                   << reason << " " << val << " -> " << val - 1;
  }
  if (gpr_unref(&refcount_)) {
    delete this;  // Delete instance if reference count reaches zero
  }
}

#else
// Dummy function when GRPC_CFSTREAM is not defined
void CFStreamPhony() {}

#endif
```