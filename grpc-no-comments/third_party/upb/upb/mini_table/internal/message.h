
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_MINI_TABLE_INTERNAL_MESSAGE_H_
#define UPB_MINI_TABLE_INTERNAL_MESSAGE_H_

#include <stddef.h>
#include <stdint.h>

#include "upb/base/descriptor_constants.h"
#include "upb/mini_table/internal/field.h"
#include "upb/mini_table/internal/sub.h"

#include "upb/port/def.inc"

struct upb_Decoder;
struct upb_Message;
typedef const char* _upb_FieldParser(struct upb_Decoder* d, const char* ptr,
                                     struct upb_Message* msg, intptr_t table,
                                     uint64_t hasbits, uint64_t data);
typedef struct {
  uint64_t field_data;
  _upb_FieldParser* field_parser;
} _upb_FastTable_Entry;

typedef enum {
  kUpb_ExtMode_NonExtendable = 0,
  kUpb_ExtMode_Extendable = 1,
  kUpb_ExtMode_IsMessageSet = 2,
  kUpb_ExtMode_IsMessageSet_ITEM =
      3,

  kUpb_ExtMode_IsMapEntry = 4,
} upb_ExtMode;

struct upb_MiniTable {
  const upb_MiniTableSubInternal* UPB_PRIVATE(subs);
  const struct upb_MiniTableField* UPB_ONLYBITS(fields);

  uint16_t UPB_PRIVATE(size);

  uint16_t UPB_ONLYBITS(field_count);

  uint8_t UPB_PRIVATE(ext);
  uint8_t UPB_PRIVATE(dense_below);
  uint8_t UPB_PRIVATE(table_mask);
  uint8_t UPB_PRIVATE(required_count);

#ifdef UPB_TRACING_ENABLED
  const char* UPB_PRIVATE(full_name);
#endif

#ifdef UPB_FASTTABLE

  _upb_FastTable_Entry UPB_PRIVATE(fasttable)[];
#endif
};

#ifdef __cplusplus
extern "C" {
#endif

UPB_INLINE const struct upb_MiniTable* UPB_PRIVATE(
    _upb_MiniTable_StrongReference)(const struct upb_MiniTable* mt) {
#if defined(__GNUC__)
  __asm__("" : : "r"(mt));
#else
  const struct upb_MiniTable* volatile unused = mt;
  (void)&unused;
#endif
  return mt;
}

UPB_INLINE const struct upb_MiniTable* UPB_PRIVATE(_upb_MiniTable_Empty)(void) {
  extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_Empty);

  return &UPB_PRIVATE(_kUpb_MiniTable_Empty);
}

UPB_API_INLINE int upb_MiniTable_FieldCount(const struct upb_MiniTable* m) {
  return m->UPB_ONLYBITS(field_count);
}

UPB_INLINE bool UPB_PRIVATE(_upb_MiniTable_IsEmpty)(
    const struct upb_MiniTable* m) {
  extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_Empty);

  return m == &UPB_PRIVATE(_kUpb_MiniTable_Empty);
}

UPB_API_INLINE const struct upb_MiniTableField* upb_MiniTable_GetFieldByIndex(
    const struct upb_MiniTable* m, uint32_t i) {
  return &m->UPB_ONLYBITS(fields)[i];
}

UPB_INLINE const struct upb_MiniTable* UPB_PRIVATE(
    _upb_MiniTable_GetSubTableByIndex)(const struct upb_MiniTable* m,
                                       uint32_t i) {
  return *m->UPB_PRIVATE(subs)[i].UPB_PRIVATE(submsg);
}

UPB_API_INLINE const struct upb_MiniTable* upb_MiniTable_SubMessage(
    const struct upb_MiniTable* m, const struct upb_MiniTableField* f) {
  if (upb_MiniTableField_CType(f) != kUpb_CType_Message) {
    return NULL;
  }
  return UPB_PRIVATE(_upb_MiniTable_GetSubTableByIndex)(
      m, f->UPB_PRIVATE(submsg_index));
}

UPB_API_INLINE const struct upb_MiniTable* upb_MiniTable_GetSubMessageTable(
    const struct upb_MiniTable* m, const struct upb_MiniTableField* f) {
  UPB_ASSUME(upb_MiniTableField_CType(f) == kUpb_CType_Message);
  const struct upb_MiniTable* ret = upb_MiniTable_SubMessage(m, f);
  UPB_ASSUME(ret);
  return UPB_PRIVATE(_upb_MiniTable_IsEmpty)(ret) ? NULL : ret;
}

UPB_API_INLINE bool upb_MiniTable_FieldIsLinked(
    const struct upb_MiniTable* m, const struct upb_MiniTableField* f) {
  return upb_MiniTable_GetSubMessageTable(m, f) != NULL;
}

UPB_API_INLINE const struct upb_MiniTable* upb_MiniTable_MapEntrySubMessage(
    const struct upb_MiniTable* m, const struct upb_MiniTableField* f) {
  UPB_ASSERT(upb_MiniTable_FieldIsLinked(m, f));
  UPB_ASSERT(upb_MiniTableField_IsMap(f));
  return upb_MiniTable_SubMessage(m, f);
}

UPB_API_INLINE const struct upb_MiniTableEnum* upb_MiniTable_GetSubEnumTable(
    const struct upb_MiniTable* m, const struct upb_MiniTableField* f) {
  UPB_ASSERT(upb_MiniTableField_CType(f) == kUpb_CType_Enum);
  return m->UPB_PRIVATE(subs)[f->UPB_PRIVATE(submsg_index)].UPB_PRIVATE(
      subenum);
}

UPB_API_INLINE const struct upb_MiniTableField* upb_MiniTable_MapKey(
    const struct upb_MiniTable* m) {
  UPB_ASSERT(upb_MiniTable_FieldCount(m) == 2);
  const struct upb_MiniTableField* f = upb_MiniTable_GetFieldByIndex(m, 0);
  UPB_ASSERT(upb_MiniTableField_Number(f) == 1);
  return f;
}

UPB_API_INLINE const struct upb_MiniTableField* upb_MiniTable_MapValue(
    const struct upb_MiniTable* m) {
  UPB_ASSERT(upb_MiniTable_FieldCount(m) == 2);
  const struct upb_MiniTableField* f = upb_MiniTable_GetFieldByIndex(m, 1);
  UPB_ASSERT(upb_MiniTableField_Number(f) == 2);
  return f;
}

UPB_INLINE uint64_t
UPB_PRIVATE(_upb_MiniTable_RequiredMask)(const struct upb_MiniTable* m) {
  int n = m->UPB_PRIVATE(required_count);
  UPB_ASSERT(0 < n && n <= 64);
  return (1ULL << n) - 1;
}

#ifdef UPB_TRACING_ENABLED
UPB_INLINE const char* upb_MiniTable_FullName(
    const struct upb_MiniTable* mini_table) {
  return mini_table->UPB_PRIVATE(full_name);
}

UPB_INLINE void upb_MiniTable_SetFullName(struct upb_MiniTable* mini_table,
                                          const char* full_name) {
  mini_table->UPB_PRIVATE(full_name) = full_name;
}
#endif

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
