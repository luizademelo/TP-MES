
// Copyright 2023 Google LLC.  All rights reserved.

#include "upb/reflection/internal/strdup2.h"

#include <string.h>

#include "upb/mem/arena.h"

#include "upb/port/def.inc"

char* upb_strdup2(const char* s, size_t len, upb_Arena* a) {
  size_t n;
  char* p;

  if (len == SIZE_MAX) return NULL;

  n = len + 1;
  p = upb_Arena_Malloc(a, n);
  if (p) {
    if (len != 0) memcpy(p, s, len);
    p[len] = 0;
  }
  return p;
}
