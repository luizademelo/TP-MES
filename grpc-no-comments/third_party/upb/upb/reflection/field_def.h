
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_REFLECTION_FIELD_DEF_H_
#define UPB_REFLECTION_FIELD_DEF_H_

#include <stdint.h>

#include "upb/base/descriptor_constants.h"
#include "upb/base/string_view.h"
#include "upb/message/value.h"
#include "upb/mini_table/extension.h"
#include "upb/mini_table/field.h"
#include "upb/reflection/common.h"

#include "upb/port/def.inc"

#define kUpb_MaxFieldNumber ((1 << 29) - 1)

#ifdef __cplusplus
extern "C" {
#endif

const upb_OneofDef* upb_FieldDef_ContainingOneof(const upb_FieldDef* f);
UPB_API const upb_MessageDef* upb_FieldDef_ContainingType(
    const upb_FieldDef* f);
UPB_API upb_CType upb_FieldDef_CType(const upb_FieldDef* f);
UPB_API upb_MessageValue upb_FieldDef_Default(const upb_FieldDef* f);
UPB_API const upb_EnumDef* upb_FieldDef_EnumSubDef(const upb_FieldDef* f);
const upb_MessageDef* upb_FieldDef_ExtensionScope(const upb_FieldDef* f);
UPB_API const upb_FileDef* upb_FieldDef_File(const upb_FieldDef* f);
const char* upb_FieldDef_FullName(const upb_FieldDef* f);
bool upb_FieldDef_HasDefault(const upb_FieldDef* f);
bool upb_FieldDef_HasJsonName(const upb_FieldDef* f);
bool upb_FieldDef_HasOptions(const upb_FieldDef* f);
UPB_API bool upb_FieldDef_HasPresence(const upb_FieldDef* f);
bool upb_FieldDef_HasSubDef(const upb_FieldDef* f);
uint32_t upb_FieldDef_Index(const upb_FieldDef* f);
UPB_API bool upb_FieldDef_IsEnum(const upb_FieldDef* f);
bool upb_FieldDef_IsExtension(const upb_FieldDef* f);
UPB_API bool upb_FieldDef_IsMap(const upb_FieldDef* f);
bool upb_FieldDef_IsOptional(const upb_FieldDef* f);
UPB_API bool upb_FieldDef_IsPacked(const upb_FieldDef* f);
bool upb_FieldDef_IsPrimitive(const upb_FieldDef* f);
UPB_API bool upb_FieldDef_IsRepeated(const upb_FieldDef* f);
UPB_API bool upb_FieldDef_IsRequired(const upb_FieldDef* f);
bool upb_FieldDef_IsString(const upb_FieldDef* f);
UPB_API bool upb_FieldDef_IsSubMessage(const upb_FieldDef* f);
UPB_API const char* upb_FieldDef_JsonName(const upb_FieldDef* f);
UPB_API upb_Label upb_FieldDef_Label(const upb_FieldDef* f);
uint32_t upb_FieldDef_LayoutIndex(const upb_FieldDef* f);
UPB_API const upb_MessageDef* upb_FieldDef_MessageSubDef(const upb_FieldDef* f);
bool _upb_FieldDef_ValidateUtf8(const upb_FieldDef* f);
bool _upb_FieldDef_IsGroupLike(const upb_FieldDef* f);

bool upb_FieldDef_MiniDescriptorEncode(const upb_FieldDef* f, upb_Arena* a,
                                       upb_StringView* out);

const upb_MiniTableField* upb_FieldDef_MiniTable(const upb_FieldDef* f);
const upb_MiniTableExtension* upb_FieldDef_MiniTableExtension(
    const upb_FieldDef* f);
UPB_API const char* upb_FieldDef_Name(const upb_FieldDef* f);
UPB_API uint32_t upb_FieldDef_Number(const upb_FieldDef* f);
const UPB_DESC(FieldOptions) * upb_FieldDef_Options(const upb_FieldDef* f);
const UPB_DESC(FeatureSet) *
    upb_FieldDef_ResolvedFeatures(const upb_FieldDef* f);
UPB_API const upb_OneofDef* upb_FieldDef_RealContainingOneof(
    const upb_FieldDef* f);
UPB_API upb_FieldType upb_FieldDef_Type(const upb_FieldDef* f);

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
