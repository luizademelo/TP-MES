
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_REFLECTION_MESSAGE_H_
#define UPB_REFLECTION_MESSAGE_H_

#include <stddef.h>

#include "upb/mem/arena.h"
#include "upb/message/map.h"
#include "upb/message/message.h"
#include "upb/reflection/common.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

UPB_API upb_MutableMessageValue upb_Message_Mutable(upb_Message* msg,
                                                    const upb_FieldDef* f,
                                                    upb_Arena* a);

UPB_API const upb_FieldDef* upb_Message_WhichOneofByDef(const upb_Message* msg,
                                                        const upb_OneofDef* o);

void upb_Message_ClearByDef(upb_Message* msg, const upb_MessageDef* m);

UPB_API void upb_Message_ClearFieldByDef(upb_Message* msg,
                                         const upb_FieldDef* f);

UPB_API bool upb_Message_HasFieldByDef(const upb_Message* msg,
                                       const upb_FieldDef* f);

UPB_API upb_MessageValue upb_Message_GetFieldByDef(const upb_Message* msg,
                                                   const upb_FieldDef* f);

UPB_API bool upb_Message_SetFieldByDef(upb_Message* msg, const upb_FieldDef* f,
                                       upb_MessageValue val, upb_Arena* a);

#define kUpb_Message_Begin -1

UPB_API bool upb_Message_Next(const upb_Message* msg, const upb_MessageDef* m,
                              const upb_DefPool* ext_pool,
                              const upb_FieldDef** f, upb_MessageValue* val,
                              size_t* iter);

UPB_API bool upb_Message_DiscardUnknown(upb_Message* msg,
                                        const upb_MessageDef* m,
                                        const upb_DefPool* ext_pool,
                                        int maxdepth);

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
