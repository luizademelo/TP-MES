Here's the commented version of the code:

```c++
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_MINI_TABLE_MESSAGE_H_
#define UPB_MINI_TABLE_MESSAGE_H_

// Include necessary headers for enum, field, and internal message definitions
#include "upb/mini_table/enum.h"
#include "upb/mini_table/field.h"
#include "upb/mini_table/internal/message.h"

// Include platform-specific definitions
#include "upb/port/def.inc"

// Forward declaration of upb_MiniTable structure
typedef struct upb_MiniTable upb_MiniTable;

#ifdef __cplusplus
extern "C" {
#endif

// Finds a field in the mini table by its field number
// m: Pointer to the mini table
// number: Field number to search for
// Returns: Pointer to the field if found, NULL otherwise
UPB_API const upb_MiniTableField* upb_MiniTable_FindFieldByNumber(
    const upb_MiniTable* m, uint32_t number);

// Gets a field from the mini table by its index
// m: Pointer to the mini table
// index: Index of the field to retrieve
// Returns: Pointer to the field at the given index
UPB_API_INLINE const upb_MiniTableField* upb_MiniTable_GetFieldByIndex(
    const upb_MiniTable* m, uint32_t index);

// Returns the total number of fields in the mini table
// m: Pointer to the mini table
// Returns: Count of fields in the table
UPB_API_INLINE int upb_MiniTable_FieldCount(const upb_MiniTable* m);

// Gets the sub-message table for a field that contains a message
// m: Pointer to the mini table
// f: Pointer to the field containing the sub-message
// Returns: Pointer to the sub-message's mini table
UPB_API_INLINE const upb_MiniTable* upb_MiniTable_GetSubMessageTable(
    const upb_MiniTable* m, const upb_MiniTableField* f);

// Alias for upb_MiniTable_GetSubMessageTable (legacy name)
UPB_API_INLINE const upb_MiniTable* upb_MiniTable_SubMessage(
    const upb_MiniTable* m, const upb_MiniTableField* f);

// Gets the sub-message table for a map entry field
// m: Pointer to the mini table
// f: Pointer to the map entry field
// Returns: Pointer to the map entry's sub-message table
UPB_API_INLINE const upb_MiniTable* upb_MiniTable_MapEntrySubMessage(
    const upb_MiniTable* m, const upb_MiniTableField* f);

// Gets the enum table for a field that contains an enum
// m: Pointer to the mini table
// f: Pointer to the field containing the enum
// Returns: Pointer to the enum's mini table
UPB_API_INLINE const upb_MiniTableEnum* upb_MiniTable_GetSubEnumTable(
    const upb_MiniTable* m, const upb_MiniTableField* f);

// Gets the key field of a map
// m: Pointer to the mini table
// Returns: Pointer to the map's key field
UPB_API_INLINE const upb_MiniTableField* upb_MiniTable_MapKey(
    const upb_MiniTable* m);

// Gets the value field of a map
// m: Pointer to the mini table
// Returns: Pointer to the map's value field
UPB_API_INLINE const upb_MiniTableField* upb_MiniTable_MapValue(
    const upb_MiniTable* m);

// Checks if a field is linked (part of a oneof or extension)
// m: Pointer to the mini table
// f: Pointer to the field to check
// Returns: True if the field is linked, false otherwise
UPB_API_INLINE bool upb_MiniTable_FieldIsLinked(const upb_MiniTable* m,
                                                const upb_MiniTableField* f);

// Gets the oneof field containing the given field
// m: Pointer to the mini table
// f: Pointer to a field that might be part of a oneof
// Returns: Pointer to the oneof field if the field is in a oneof, NULL otherwise
const upb_MiniTableField* upb_MiniTable_GetOneof(const upb_MiniTable* m,
                                                 const upb_MiniTableField* f);

// Advances to the next field in a oneof
// m: Pointer to the mini table
// f: Pointer to a pointer to the current field (will be updated)
// Returns: True if there are more fields in the oneof, false otherwise
bool upb_MiniTable_NextOneofField(const upb_MiniTable* m,
                                  const upb_MiniTableField** f);

#ifdef __cplusplus
}
#endif

// Undefine platform-specific definitions
#include "upb/port/undef.inc"

#endif  // UPB_MINI_TABLE_MESSAGE_H_
```