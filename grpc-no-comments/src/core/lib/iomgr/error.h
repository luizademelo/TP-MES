
// Copyright 2016 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_IOMGR_ERROR_H
#define GRPC_SRC_CORE_LIB_IOMGR_ERROR_H

#include <grpc/slice.h>
#include <grpc/status.h>
#include <grpc/support/port_platform.h>
#include <grpc/support/time.h>
#include <inttypes.h>
#include <stdbool.h>

#include "absl/log/check.h"
#include "absl/status/status.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/lib/slice/slice_internal.h"
#include "src/core/util/crash.h"
#include "src/core/util/spinlock.h"
#include "src/core/util/status_helper.h"

typedef absl::Status grpc_error_handle;

#define GRPC_ERROR_CREATE(desc) \
  StatusCreate(absl::StatusCode::kUnknown, desc, DEBUG_LOCATION, {})

absl::Status grpc_status_create(absl::StatusCode code, absl::string_view msg,
                                const grpc_core::DebugLocation& location,
                                size_t children_count, absl::Status* children);

#define GRPC_ERROR_CREATE_REFERENCING(desc, errs, count)                      \
  grpc_status_create(absl::StatusCode::kUnknown, desc, DEBUG_LOCATION, count, \
                     errs)

template <typename VectorType>
static absl::Status grpc_status_create_from_vector(
    const grpc_core::DebugLocation& location, absl::string_view desc,
    VectorType* error_list) {
  absl::Status error;
  if (error_list->size() != 0) {
    error = grpc_status_create(absl::StatusCode::kUnknown, desc, location,
                               error_list->size(), error_list->data());
    error_list->clear();
  }
  return error;
}

#define GRPC_ERROR_CREATE_FROM_VECTOR(desc, error_list) \
  grpc_status_create_from_vector(DEBUG_LOCATION, desc, error_list)

absl::Status grpc_os_error(const grpc_core::DebugLocation& location, int err,
                           const char* call_name);

inline absl::Status grpc_assert_never_ok(absl::Status error) {
  CHECK(!error.ok());
  return error;
}

#define GRPC_OS_ERROR(err, call_name) \
  grpc_assert_never_ok(grpc_os_error(DEBUG_LOCATION, err, call_name))

absl::Status grpc_wsa_error(const grpc_core::DebugLocation& location, int err,
                            absl::string_view call_name);

#define GRPC_WSA_ERROR(err, call_name) \
  grpc_wsa_error(DEBUG_LOCATION, err, call_name)

grpc_error_handle grpc_error_set_int(grpc_error_handle src,
                                     grpc_core::StatusIntProperty which,
                                     intptr_t value);

bool grpc_error_get_int(grpc_error_handle error,
                        grpc_core::StatusIntProperty which, intptr_t* p);
grpc_error_handle grpc_error_set_str(grpc_error_handle src,
                                     grpc_core::StatusStrProperty which,
                                     absl::string_view str);

bool grpc_error_get_str(grpc_error_handle error,
                        grpc_core::StatusStrProperty which, std::string* str);

grpc_error_handle grpc_error_add_child(grpc_error_handle src,
                                       grpc_error_handle child);

bool grpc_log_error(const char* what, grpc_error_handle error, const char* file,
                    int line);
inline bool grpc_log_if_error(const char* what, grpc_error_handle error,
                              const char* file, int line) {
  return error.ok() ? true : grpc_log_error(what, error, file, line);
}

#define GRPC_LOG_IF_ERROR(what, error) \
  (grpc_log_if_error((what), (error), __FILE__, __LINE__))

class AtomicError {
 public:
  AtomicError() = default;
  explicit AtomicError(grpc_error_handle error) { error_ = error; }

  AtomicError(const AtomicError&) = delete;
  AtomicError& operator=(const AtomicError&) = delete;

  bool ok() {
    gpr_spinlock_lock(&lock_);
    bool ret = error_.ok();
    gpr_spinlock_unlock(&lock_);
    return ret;
  }

  grpc_error_handle get() {
    gpr_spinlock_lock(&lock_);
    grpc_error_handle ret = error_;
    gpr_spinlock_unlock(&lock_);
    return ret;
  }

  void set(grpc_error_handle error) {
    gpr_spinlock_lock(&lock_);
    error_ = error;
    gpr_spinlock_unlock(&lock_);
  }

 private:
  grpc_error_handle error_;
  gpr_spinlock lock_ = GPR_SPINLOCK_STATIC_INITIALIZER;
};

#endif
