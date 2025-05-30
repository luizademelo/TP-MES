
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_REFLECTION_MESSAGE_DEF_H_
#define UPB_REFLECTION_MESSAGE_DEF_H_

#include "upb/base/string_view.h"
#include "upb/reflection/common.h"

#include "upb/port/def.inc"

#define kUpb_MapEntry_KeyFieldNumber 1
#define kUpb_MapEntry_ValueFieldNumber 2

#define kUpb_Any_TypeFieldNumber 1
#define kUpb_Any_ValueFieldNumber 2

#define kUpb_Duration_SecondsFieldNumber 1
#define kUpb_Duration_NanosFieldNumber 2

#define kUpb_Timestamp_SecondsFieldNumber 1
#define kUpb_Timestamp_NanosFieldNumber 2

typedef enum {
  kUpb_WellKnown_Unspecified,
  kUpb_WellKnown_Any,
  kUpb_WellKnown_FieldMask,
  kUpb_WellKnown_Duration,
  kUpb_WellKnown_Timestamp,

  kUpb_WellKnown_DoubleValue,
  kUpb_WellKnown_FloatValue,
  kUpb_WellKnown_Int64Value,
  kUpb_WellKnown_UInt64Value,
  kUpb_WellKnown_Int32Value,
  kUpb_WellKnown_UInt32Value,

  kUpb_WellKnown_StringValue,
  kUpb_WellKnown_BytesValue,
  kUpb_WellKnown_BoolValue,
  kUpb_WellKnown_Value,
  kUpb_WellKnown_ListValue,
  kUpb_WellKnown_Struct,
} upb_WellKnown;

#ifdef __cplusplus
extern "C" {
#endif

const upb_MessageDef* upb_MessageDef_ContainingType(const upb_MessageDef* m);

const upb_ExtensionRange* upb_MessageDef_ExtensionRange(const upb_MessageDef* m,
                                                        int i);
int upb_MessageDef_ExtensionRangeCount(const upb_MessageDef* m);

UPB_API const upb_FieldDef* upb_MessageDef_Field(const upb_MessageDef* m,
                                                 int i);
UPB_API int upb_MessageDef_FieldCount(const upb_MessageDef* m);

UPB_API const upb_FileDef* upb_MessageDef_File(const upb_MessageDef* m);

const upb_FieldDef* upb_MessageDef_FindByJsonNameWithSize(
    const upb_MessageDef* m, const char* name, size_t size);
UPB_INLINE const upb_FieldDef* upb_MessageDef_FindByJsonName(
    const upb_MessageDef* m, const char* name) {
  return upb_MessageDef_FindByJsonNameWithSize(m, name, strlen(name));
}

UPB_API bool upb_MessageDef_FindByNameWithSize(const upb_MessageDef* m,
                                               const char* name, size_t size,
                                               const upb_FieldDef** f,
                                               const upb_OneofDef** o);
UPB_INLINE bool upb_MessageDef_FindByName(const upb_MessageDef* m,
                                          const char* name,
                                          const upb_FieldDef** f,
                                          const upb_OneofDef** o) {
  return upb_MessageDef_FindByNameWithSize(m, name, strlen(name), f, o);
}

const upb_FieldDef* upb_MessageDef_FindFieldByName(const upb_MessageDef* m,
                                                   const char* name);
UPB_API const upb_FieldDef* upb_MessageDef_FindFieldByNameWithSize(
    const upb_MessageDef* m, const char* name, size_t size);
UPB_API const upb_FieldDef* upb_MessageDef_FindFieldByNumber(
    const upb_MessageDef* m, uint32_t i);
const upb_OneofDef* upb_MessageDef_FindOneofByName(const upb_MessageDef* m,
                                                   const char* name);
UPB_API const upb_OneofDef* upb_MessageDef_FindOneofByNameWithSize(
    const upb_MessageDef* m, const char* name, size_t size);
UPB_API const char* upb_MessageDef_FullName(const upb_MessageDef* m);
bool upb_MessageDef_HasOptions(const upb_MessageDef* m);
bool upb_MessageDef_IsMapEntry(const upb_MessageDef* m);
bool upb_MessageDef_IsMessageSet(const upb_MessageDef* m);

bool upb_MessageDef_MiniDescriptorEncode(const upb_MessageDef* m, upb_Arena* a,
                                         upb_StringView* out);

UPB_API const upb_MiniTable* upb_MessageDef_MiniTable(const upb_MessageDef* m);
const char* upb_MessageDef_Name(const upb_MessageDef* m);

const upb_EnumDef* upb_MessageDef_NestedEnum(const upb_MessageDef* m, int i);
const upb_FieldDef* upb_MessageDef_NestedExtension(const upb_MessageDef* m,
                                                   int i);
const upb_MessageDef* upb_MessageDef_NestedMessage(const upb_MessageDef* m,
                                                   int i);

int upb_MessageDef_NestedEnumCount(const upb_MessageDef* m);
int upb_MessageDef_NestedExtensionCount(const upb_MessageDef* m);
int upb_MessageDef_NestedMessageCount(const upb_MessageDef* m);

UPB_API const upb_OneofDef* upb_MessageDef_Oneof(const upb_MessageDef* m,
                                                 int i);
UPB_API int upb_MessageDef_OneofCount(const upb_MessageDef* m);
int upb_MessageDef_RealOneofCount(const upb_MessageDef* m);

const UPB_DESC(MessageOptions) *
    upb_MessageDef_Options(const upb_MessageDef* m);
const UPB_DESC(FeatureSet) *
    upb_MessageDef_ResolvedFeatures(const upb_MessageDef* m);

upb_StringView upb_MessageDef_ReservedName(const upb_MessageDef* m, int i);
int upb_MessageDef_ReservedNameCount(const upb_MessageDef* m);

const upb_MessageReservedRange* upb_MessageDef_ReservedRange(
    const upb_MessageDef* m, int i);
int upb_MessageDef_ReservedRangeCount(const upb_MessageDef* m);

UPB_API upb_Syntax upb_MessageDef_Syntax(const upb_MessageDef* m);
UPB_API upb_WellKnown upb_MessageDef_WellKnownType(const upb_MessageDef* m);

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
