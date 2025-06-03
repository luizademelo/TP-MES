Here's the commented version of the code:

```c++
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

// Structure to hold sorted map entries
typedef struct {
  void const** entries;  // Array of pointers to map entries
  int size;              // Current number of entries
  int cap;               // Capacity of the entries array
} _upb_mapsorter;

// Structure to represent a sorted map range within _upb_mapsorter
typedef struct {
  int start;  // Starting index of this map in the entries array
  int pos;    // Current position when iterating
  int end;    // Ending index of this map in the entries array
} _upb_sortedmap;

// Initializes a map sorter with default values
UPB_INLINE void _upb_mapsorter_init(_upb_mapsorter* s) {
  s->entries = NULL;
  s->size = 0;
  s->cap = 0;
}

// Frees memory allocated by the map sorter
UPB_INLINE void _upb_mapsorter_destroy(_upb_mapsorter* s) {
  if (s->entries) upb_gfree(s->entries);
}

// Retrieves the next entry from a sorted map
// Returns true if an entry was retrieved, false if no more entries
UPB_INLINE bool _upb_sortedmap_next(_upb_mapsorter* s,
                                    const struct upb_Map* map,
                                    _upb_sortedmap* sorted, upb_MapEntry* ent) {
  if (sorted->pos == sorted->end) return false;
  const upb_tabent* tabent = (const upb_tabent*)s->entries[sorted->pos++];
  
  // Handle string-keyed maps differently from numeric-keyed maps
  if (map->UPB_PRIVATE(is_strtable)) {
    upb_StringView key = upb_key_strview(tabent->key);
    _upb_map_fromkey(key, &ent->k, map->key_size);
  } else {
    uintptr_t key = tabent->key.num;
    memcpy(&ent->k, &key, map->key_size);
  }
  
  // Copy the value from the table entry to the map entry
  upb_value val = {tabent->val.val};
  _upb_map_fromvalue(val, &ent->v, map->val_size);
  return true;
}

// Retrieves the next extension from a sorted map of extensions
// Returns true if an extension was retrieved, false if no more extensions
UPB_INLINE bool _upb_sortedmap_nextext(_upb_mapsorter* s,
                                       _upb_sortedmap* sorted,
                                       const upb_Extension** ext) {
  if (sorted->pos == sorted->end) return false;
  *ext = (const upb_Extension*)s->entries[sorted->pos++];
  return true;
}

// Pops a map from the sorter, resetting the size to before the map was pushed
UPB_INLINE void _upb_mapsorter_popmap(_upb_mapsorter* s,
                                      _upb_sortedmap* sorted) {
  s->size = sorted->start;
}

// Pushes a map into the sorter for sorting and iteration
// Returns true if successful, false otherwise
bool _upb_mapsorter_pushmap(_upb_mapsorter* s, upb_FieldType key_type,
                            const struct upb_Map* map, _upb_sortedmap* sorted);

// Pushes message extensions into the sorter for sorting and iteration
// Returns true if successful, false otherwise
bool _upb_mapsorter_pushexts(_upb_mapsorter* s, const upb_Message_Internal* in,
                             _upb_sortedmap* sorted);

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif  // UPB_MESSAGE_INTERNAL_MAP_SORTER_H_
```

Key aspects of the comments:
1. Added descriptions for each structure and its fields
2. Explained the purpose of each function
3. Detailed the parameters and return values
4. Clarified special cases (like string vs numeric keys)
5. Maintained consistent style with the existing codebase
6. Added a clear header guard comment
7. Explained the behavior of iteration functions
8. Noted memory management responsibilities

The comments aim to help future developers understand:
- The overall purpose of the map sorting functionality
- How to use the provided API
- Memory ownership and management
- The flow of data through the functions
- Special cases and edge conditions