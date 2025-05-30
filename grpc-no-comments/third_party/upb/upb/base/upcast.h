
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_BASE_UPCAST_H_
#define UPB_BASE_UPCAST_H_

#include "upb/port/def.inc"

#define UPB_UPCAST(x) (&(x)->base##_dont_copy_me__upb_internal_use_only)

#include "upb/port/undef.inc"

#endif
