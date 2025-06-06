
#include <stddef.h>
#include "upb/generated_code_support.h"
#include "envoy/annotations/deprecation.upb_minitable.h"
#include "google/protobuf/descriptor.upb_minitable.h"

#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
UPB_LINKARR_APPEND(upb_AllExts)
const upb_MiniTableExtension envoy_annotations_disallowed_by_default_ext = {
  {189503207, 0, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsExtension | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  &google__protobuf__FieldOptions_msg_init,
  {.UPB_PRIVATE(submsg) = NULL},

};
UPB_LINKARR_APPEND(upb_AllExts)
const upb_MiniTableExtension envoy_annotations_deprecated_at_minor_version_ext = {
  {157299826, 0, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsExtension | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  &google__protobuf__FieldOptions_msg_init,
  {.UPB_PRIVATE(submsg) = NULL},

};
UPB_LINKARR_APPEND(upb_AllExts)
const upb_MiniTableExtension envoy_annotations_disallowed_by_default_enum_ext = {
  {70100853, 0, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsExtension | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  &google__protobuf__EnumValueOptions_msg_init,
  {.UPB_PRIVATE(submsg) = NULL},

};
UPB_LINKARR_APPEND(upb_AllExts)
const upb_MiniTableExtension envoy_annotations_deprecated_at_minor_version_enum_ext = {
  {181198657, 0, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsExtension | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  &google__protobuf__EnumValueOptions_msg_init,
  {.UPB_PRIVATE(submsg) = NULL},

};

static const upb_MiniTableExtension *extensions_layout[4] = {
  &envoy_annotations_disallowed_by_default_ext,
  &envoy_annotations_deprecated_at_minor_version_ext,
  &envoy_annotations_disallowed_by_default_enum_ext,
  &envoy_annotations_deprecated_at_minor_version_enum_ext,
};

const upb_MiniTableFile envoy_annotations_deprecation_proto_upb_file_layout = {
  NULL,
  NULL,
  extensions_layout,
  0,
  0,
  4,
};

#include "upb/port/undef.inc"
