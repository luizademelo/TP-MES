
#include <stddef.h>
#include "upb/generated_code_support.h"
#include "udpa/annotations/sensitive.upb_minitable.h"
#include "google/protobuf/descriptor.upb_minitable.h"

#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
UPB_LINKARR_APPEND(upb_AllExts)
const upb_MiniTableExtension udpa_annotations_sensitive_ext = {
  {76569463, 0, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsExtension | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  &google__protobuf__FieldOptions_msg_init,
  {.UPB_PRIVATE(submsg) = NULL},

};

static const upb_MiniTableExtension *extensions_layout[1] = {
  &udpa_annotations_sensitive_ext,
};

const upb_MiniTableFile udpa_annotations_sensitive_proto_upb_file_layout = {
  NULL,
  NULL,
  extensions_layout,
  0,
  0,
  1,
};

#include "upb/port/undef.inc"
