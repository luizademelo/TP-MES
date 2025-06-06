
// Copyright 2018 gRPC authors.

#include <grpc/support/port_platform.h>

#include "src/core/lib/iomgr/port.h"
#include "src/core/util/memory.h"

#ifdef GRPC_CFSTREAM
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

GrpcLibraryInitHolder::GrpcLibraryInitHolder() { grpc_init(); }

GrpcLibraryInitHolder::~GrpcLibraryInitHolder() { grpc_shutdown(); }

void* CFStreamHandle::Retain(void* info) {
  CFStreamHandle* handle = static_cast<CFStreamHandle*>(info);
  CFSTREAM_HANDLE_REF(handle, "retain");
  return info;
}

void CFStreamHandle::Release(void* info) {
  CFStreamHandle* handle = static_cast<CFStreamHandle*>(info);
  CFSTREAM_HANDLE_UNREF(handle, "release");
}

CFStreamHandle* CFStreamHandle::CreateStreamHandle(
    CFReadStreamRef read_stream, CFWriteStreamRef write_stream) {
  return new CFStreamHandle(read_stream, write_stream);
}

void CFStreamHandle::ReadCallback(CFReadStreamRef stream,
                                  CFStreamEventType type,
                                  void* client_callback_info) {
  grpc_core::ExecCtx exec_ctx;
  grpc_error_handle error;
  CFErrorRef stream_error;
  CFStreamHandle* handle = static_cast<CFStreamHandle*>(client_callback_info);
  GRPC_TRACE_VLOG(tcp, 2) << "CFStream ReadCallback (" << handle << ", "
                          << stream << ", " << type << ", "
                          << client_callback_info << ")";
  switch (type) {
    case kCFStreamEventOpenCompleted:
      handle->open_event_.SetReady();
      break;
    case kCFStreamEventHasBytesAvailable:
    case kCFStreamEventEndEncountered:
      handle->read_event_.SetReady();
      break;
    case kCFStreamEventErrorOccurred:
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
      GPR_UNREACHABLE_CODE(return);
  }
}
void CFStreamHandle::WriteCallback(CFWriteStreamRef stream,
                                   CFStreamEventType type,
                                   void* clientCallBackInfo) {
  grpc_core::ExecCtx exec_ctx;
  grpc_error_handle error;
  CFErrorRef stream_error;
  CFStreamHandle* handle = static_cast<CFStreamHandle*>(clientCallBackInfo);
  GRPC_TRACE_VLOG(tcp, 2) << "CFStream WriteCallback (" << handle << ", "
                          << stream << ", " << type << ", "
                          << clientCallBackInfo << ")";
  switch (type) {
    case kCFStreamEventOpenCompleted:
      handle->open_event_.SetReady();
      break;
    case kCFStreamEventCanAcceptBytes:
    case kCFStreamEventEndEncountered:
      handle->write_event_.SetReady();
      break;
    case kCFStreamEventErrorOccurred:
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
      GPR_UNREACHABLE_CODE(return);
  }
}

CFStreamHandle::CFStreamHandle(CFReadStreamRef read_stream,
                               CFWriteStreamRef write_stream) {
  gpr_ref_init(&refcount_, 1);
  open_event_.InitEvent();
  read_event_.InitEvent();
  write_event_.InitEvent();
  dispatch_queue_ = dispatch_queue_create(nullptr, DISPATCH_QUEUE_SERIAL);
  CFStreamClientContext ctx = {0, static_cast<void*>(this),
                               CFStreamHandle::Retain, CFStreamHandle::Release,
                               nil};
  CFReadStreamSetClient(
      read_stream,
      kCFStreamEventOpenCompleted | kCFStreamEventHasBytesAvailable |
          kCFStreamEventErrorOccurred | kCFStreamEventEndEncountered,
      CFStreamHandle::ReadCallback, &ctx);
  CFWriteStreamSetClient(
      write_stream,
      kCFStreamEventOpenCompleted | kCFStreamEventCanAcceptBytes |
          kCFStreamEventErrorOccurred | kCFStreamEventEndEncountered,
      CFStreamHandle::WriteCallback, &ctx);
  grpc_apple_register_read_stream(read_stream, dispatch_queue_);
  grpc_apple_register_write_stream(write_stream, dispatch_queue_);
}

CFStreamHandle::~CFStreamHandle() {
  open_event_.DestroyEvent();
  read_event_.DestroyEvent();
  write_event_.DestroyEvent();
  dispatch_release(dispatch_queue_);
}

void CFStreamHandle::NotifyOnOpen(grpc_closure* closure) {
  open_event_.NotifyOn(closure);
}

void CFStreamHandle::NotifyOnRead(grpc_closure* closure) {
  read_event_.NotifyOn(closure);
}

void CFStreamHandle::NotifyOnWrite(grpc_closure* closure) {
  write_event_.NotifyOn(closure);
}

void CFStreamHandle::Shutdown(grpc_error_handle error) {
  open_event_.SetShutdown(error);
  read_event_.SetShutdown(error);
  write_event_.SetShutdown(error);
}

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
    delete this;
  }
}

#else

void CFStreamPhony() {}

#endif
