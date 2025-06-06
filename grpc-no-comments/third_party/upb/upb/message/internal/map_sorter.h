
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_MESSAGE_INTERNAL_MAP_SORTER_H_
#define UPB_MESSAGE_INTERNAL_MAP_SORTER_H_

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "upb/base/descriptor_constants.h"
#include "upb/base/string_view.h"
#include "upb/hash/common.h"
#include "upb/mem/alloc.h"
#include "upb/message/internal/extension.h"
#include "upb/message/internal/map.h"
#include "upb/message/internal/map_entry.h"
#include "upb/message/internal/message.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  void const** entries;
  int size;
  int cap;
} _upb_mapsorter;

typedef struct {
  int start;
  int pos;
  int end;
} _upb_sortedmap;

UPB_INLINE void _upb_mapsorter_init(_upb_mapsorter* s) {
  s->entries = NULL;
  s->size = 0;
  s->cap = 0;
}

UPB_INLINE void _upb_mapsorter_destroy(_upb_mapsorter* s) {
  if (s->entries) upb_gfree(s->entries);
}

UPB_INLINE bool _upb_sortedmap_next(_upb_mapsorter* s,
                                    const struct upb_Map* map,
                                    _upb_sortedmap* sorted, upb_MapEntry* ent) {
  if (sorted->pos == sorted->end) return false;
  const upb_tabent* tabent = (const upb_tabent*)s->entries[sorted->pos++];
  if (map->UPB_PRIVATE(is_strtable)) {
    upb_StringView key = upb_key_strview(tabent->key);
    _upb_map_fromkey(key, &ent->k, map->key_size);
  } else {
    uintptr_t key = tabent->key.num;
    memcpy(&ent->k, &key, map->key_size);
  }
  upb_value val = {tabent->val.val};
  _upb_map_fromvalue(val, &ent->v, map->val_size);
  return true;
}

UPB_INLINE bool _upb_sortedmap_nextext(_upb_mapsorter* s,
                                       _upb_sortedmap* sorted,
                                       const upb_Extension** ext) {
  if (sorted->pos == sorted->end) return false;
  *ext = (const upb_Extension*)s->entries[sorted->pos++];
  return true;
}

UPB_INLINE void _upb_mapsorter_popmap(_upb_mapsorter* s,
                                      _upb_sortedmap* sorted) {
  s->size = sorted->start;
}

bool _upb_mapsorter_pushmap(_upb_mapsorter* s, upb_FieldType key_type,
                            const struct upb_Map* map, _upb_sortedmap* sorted);

bool _upb_mapsorter_pushexts(_upb_mapsorter* s, const upb_Message_Internal* in,
                             _upb_sortedmap* sorted);

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
