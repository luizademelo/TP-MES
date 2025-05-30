
// Copyright 2018 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_IOMGR_DYNAMIC_ANNOTATIONS_H
#define GRPC_SRC_CORE_LIB_IOMGR_DYNAMIC_ANNOTATIONS_H

#include <grpc/support/port_platform.h>

#ifdef GRPC_TSAN_ENABLED

#define TSAN_ANNOTATE_HAPPENS_BEFORE(addr) \
  AnnotateHappensBefore(__FILE__, __LINE__, (void*)(addr))
#define TSAN_ANNOTATE_HAPPENS_AFTER(addr) \
  AnnotateHappensAfter(__FILE__, __LINE__, (void*)(addr))
#define TSAN_ANNOTATE_RWLOCK_CREATE(addr) \
  AnnotateRWLockCreate(__FILE__, __LINE__, (void*)(addr))
#define TSAN_ANNOTATE_RWLOCK_DESTROY(addr) \
  AnnotateRWLockDestroy(__FILE__, __LINE__, (void*)(addr))
#define TSAN_ANNOTATE_RWLOCK_ACQUIRED(addr, is_w) \
  AnnotateRWLockAcquired(__FILE__, __LINE__, (void*)(addr), (is_w))
#define TSAN_ANNOTATE_RWLOCK_RELEASED(addr, is_w) \
  AnnotateRWLockReleased(__FILE__, __LINE__, (void*)(addr), (is_w))

#ifdef __cplusplus
extern "C" {
#endif
void AnnotateHappensBefore(const char* file, int line, const volatile void* cv);
void AnnotateHappensAfter(const char* file, int line, const volatile void* cv);
void AnnotateRWLockCreate(const char* file, int line,
                          const volatile void* lock);
void AnnotateRWLockDestroy(const char* file, int line,
                           const volatile void* lock);
void AnnotateRWLockAcquired(const char* file, int line,
                            const volatile void* lock, long is_w);
void AnnotateRWLockReleased(const char* file, int line,
                            const volatile void* lock, long is_w);
#ifdef __cplusplus
}
#endif

#else

#define TSAN_ANNOTATE_HAPPENS_BEFORE(addr)
#define TSAN_ANNOTATE_HAPPENS_AFTER(addr)
#define TSAN_ANNOTATE_RWLOCK_CREATE(addr)
#define TSAN_ANNOTATE_RWLOCK_DESTROY(addr)
#define TSAN_ANNOTATE_RWLOCK_ACQUIRED(addr, is_w)
#define TSAN_ANNOTATE_RWLOCK_RELEASED(addr, is_w)

#endif

#endif
