
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_BASE_STATUS_HPP_
#define UPB_BASE_STATUS_HPP_

#ifdef __cplusplus

#include "upb/base/status.h"

namespace upb {

class Status final {
 public:
  Status() { upb_Status_Clear(&status_); }

  upb_Status* ptr() { return &status_; }

  bool ok() const { return upb_Status_IsOk(&status_); }

  const char* error_message() const {
    return upb_Status_ErrorMessage(&status_);
  }

  void SetErrorMessage(const char* msg) {
    upb_Status_SetErrorMessage(&status_, msg);
  }
  void SetFormattedErrorMessage(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    upb_Status_VSetErrorFormat(&status_, fmt, args);
    va_end(args);
  }

  void Clear() { upb_Status_Clear(&status_); }

 private:
  upb_Status status_;
};

}

#endif

#endif
