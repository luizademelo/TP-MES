
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_MESSAGE_MESSAGE_H_
#define UPB_MESSAGE_MESSAGE_H_

#include <stddef.h>
#include <stdint.h>

#include "upb/base/string_view.h"
#include "upb/mem/arena.h"
#include "upb/message/array.h"
#include "upb/message/internal/extension.h"
#include "upb/message/internal/message.h"
#include "upb/message/internal/types.h"
#include "upb/mini_table/extension.h"
#include "upb/mini_table/message.h"

#include "upb/port/def.inc"

typedef struct upb_Message upb_Message;

#ifdef __cplusplus
extern "C" {
#endif

UPB_API upb_Message* upb_Message_New(const upb_MiniTable* m, upb_Arena* arena);

#define kUpb_Message_UnknownBegin 0
#define kUpb_Message_ExtensionBegin 0

UPB_INLINE bool upb_Message_NextUnknown(const upb_Message* msg,
                                        upb_StringView* data, uintptr_t* iter);

UPB_INLINE bool upb_Message_HasUnknown(const upb_Message* msg);

typedef enum upb_Message_DeleteUnknownStatus {
  kUpb_DeleteUnknown_DeletedLast,
  kUpb_DeleteUnknown_IterUpdated,
  kUpb_DeleteUnknown_AllocFail,
} upb_Message_DeleteUnknownStatus;
upb_Message_DeleteUnknownStatus upb_Message_DeleteUnknown(upb_Message* msg,
                                                          upb_StringView* data,
                                                          uintptr_t* iter,
                                                          upb_Arena* arena);

size_t upb_Message_ExtensionCount(const upb_Message* msg);

UPB_INLINE bool upb_Message_NextExtension(const upb_Message* msg,
                                          const upb_MiniTableExtension** out_e,
                                          upb_MessageValue* out_v,
                                          uintptr_t* iter);

UPB_INLINE bool UPB_PRIVATE(_upb_Message_NextExtensionReverse)(
    const struct upb_Message* msg, const upb_MiniTableExtension** out_e,
    upb_MessageValue* out_v, uintptr_t* iter);

UPB_API void upb_Message_Freeze(upb_Message* msg, const upb_MiniTable* m);

UPB_API_INLINE bool upb_Message_IsFrozen(const upb_Message* msg);

#ifdef UPB_TRACING_ENABLED
UPB_API void upb_Message_LogNewMessage(const upb_MiniTable* m,
                                       const upb_Arena* arena);

UPB_API void upb_Message_SetNewMessageTraceHandler(
    void (*handler)(const upb_MiniTable* m, const upb_Arena* arena));
#endif

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
