
// Copyright 2023 Google LLC.  All rights reserved.

#include "upb/mini_table/message.h"

#include <stddef.h>
#include <stdint.h>

#include "upb/mini_table/field.h"

#include "upb/port/def.inc"

const upb_MiniTableField* upb_MiniTable_FindFieldByNumber(
    const upb_MiniTable* m, uint32_t number) {
  const size_t i = ((size_t)number) - 1;

  if (i < m->UPB_PRIVATE(dense_below)) {
    UPB_ASSERT(m->UPB_PRIVATE(fields)[i].UPB_PRIVATE(number) == number);
    return &m->UPB_PRIVATE(fields)[i];
  }

  uint32_t lo = m->UPB_PRIVATE(dense_below);
  int32_t hi = m->UPB_PRIVATE(field_count) - 1;
  const upb_MiniTableField* base = m->UPB_PRIVATE(fields);
  while (hi >= (int32_t)lo) {
    uint32_t mid = (hi + lo) / 2;
    uint32_t num = base[mid].UPB_ONLYBITS(number);

    int32_t hi_mid = mid - 1;
    uint32_t lo_mid = mid + 1;
    if (num == number) {
      return &base[mid];
    }
    if (UPB_UNPREDICTABLE(num < number)) {
      lo = lo_mid;
    } else {
      hi = hi_mid;
    }
  }

  return NULL;
}

const upb_MiniTableField* upb_MiniTable_GetOneof(const upb_MiniTable* m,
                                                 const upb_MiniTableField* f) {
  if (UPB_UNLIKELY(!upb_MiniTableField_IsInOneof(f))) {
    return NULL;
  }
  const upb_MiniTableField* ptr = &m->UPB_PRIVATE(fields)[0];
  const upb_MiniTableField* end =
      &m->UPB_PRIVATE(fields)[m->UPB_PRIVATE(field_count)];
  for (; ptr < end; ptr++) {
    if (ptr->presence == (*f).presence) {
      return ptr;
    }
  }
  return NULL;
}

bool upb_MiniTable_NextOneofField(const upb_MiniTable* m,
                                  const upb_MiniTableField** f) {
  const upb_MiniTableField* ptr = *f;
  const upb_MiniTableField* end =
      &m->UPB_PRIVATE(fields)[m->UPB_PRIVATE(field_count)];
  while (++ptr < end) {
    if (ptr->presence == (*f)->presence) {
      *f = ptr;
      return true;
    }
  }
  return false;
}
