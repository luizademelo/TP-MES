
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_MESSAGE_INTERNAL_MAP_ENTRY_H_
#define UPB_MESSAGE_INTERNAL_MAP_ENTRY_H_

#include <stdint.h>

#include "upb/base/string_view.h"
#include "upb/hash/common.h"
#include "upb/message/internal/types.h"

typedef struct {
  struct upb_Message message;

  uint64_t hasbits;
  union {
    upb_StringView str;
    upb_value val;
    double d[2];
  } k;
  union {
    upb_StringView str;
    upb_value val;
    double d[2];
  } v;
} upb_MapEntry;

#endif
