
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_HASH_INT_TABLE_H_
#define UPB_HASH_INT_TABLE_H_

#include <stddef.h>
#include <stdint.h>

#include "upb/hash/common.h"
#include "upb/mem/arena.h"

#include "upb/port/def.inc"

typedef struct {
  upb_table t;

  const upb_value* array;

  const uint8_t* presence_mask;
  uint32_t array_size;
  uint32_t array_count;
} upb_inttable;

#ifdef __cplusplus
extern "C" {
#endif

bool upb_inttable_init(upb_inttable* table, upb_Arena* a);

size_t upb_inttable_count(const upb_inttable* t);

bool upb_inttable_insert(upb_inttable* t, uintptr_t key, upb_value val,
                         upb_Arena* a);

bool upb_inttable_lookup(const upb_inttable* t, uintptr_t key, upb_value* v);

bool upb_inttable_remove(upb_inttable* t, uintptr_t key, upb_value* val);

bool upb_inttable_replace(upb_inttable* t, uintptr_t key, upb_value val);

bool upb_inttable_compact(upb_inttable* t, upb_Arena* a);

void upb_inttable_clear(upb_inttable* t);

#define UPB_INTTABLE_BEGIN -1

bool upb_inttable_next(const upb_inttable* t, uintptr_t* key, upb_value* val,
                       intptr_t* iter);
void upb_inttable_removeiter(upb_inttable* t, intptr_t* iter);
void upb_inttable_setentryvalue(upb_inttable* t, intptr_t iter, upb_value v);
bool upb_inttable_done(const upb_inttable* t, intptr_t i);
uintptr_t upb_inttable_iter_key(const upb_inttable* t, intptr_t iter);
upb_value upb_inttable_iter_value(const upb_inttable* t, intptr_t iter);

UPB_INLINE bool upb_inttable_arrhas(const upb_inttable* t, uintptr_t key) {
  return (t->presence_mask[key / 8] & (1 << (key % 8))) != 0;
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
