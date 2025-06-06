
#include <stddef.h>
#include "upb/generated_code_support.h"
#include "udpa/annotations/versioning.upb_minitable.h"
#include "google/protobuf/descriptor.upb_minitable.h"

#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
static const upb_MiniTableField udpa_annotations_VersioningAnnotation__fields[1] = {
  {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
};

const upb_MiniTable udpa__annotations__VersioningAnnotation_msg_init = {
  NULL,
  &udpa_annotations_VersioningAnnotation__fields[0],
  UPB_SIZE(16, 24), 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "udpa.annotations.VersioningAnnotation",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f00000a, &upb_pss_1bt},
  })
};

const upb_MiniTable* udpa__annotations__VersioningAnnotation_msg_init_ptr = &udpa__annotations__VersioningAnnotation_msg_init;
UPB_LINKARR_APPEND(upb_AllExts)
const upb_MiniTableExtension udpa_annotations_versioning_ext = {
  {7881811, 0, 0, 0, 11, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsExtension | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  &google__protobuf__MessageOptions_msg_init,
  {.UPB_PRIVATE(submsg) = &udpa__annotations__VersioningAnnotation_msg_init},

};
static const upb_MiniTable *messages_layout[1] = {
  &udpa__annotations__VersioningAnnotation_msg_init,
};

static const upb_MiniTableExtension *extensions_layout[1] = {
  &udpa_annotations_versioning_ext,
};

const upb_MiniTableFile udpa_annotations_versioning_proto_upb_file_layout = {
  messages_layout,
  NULL,
  extensions_layout,
  1,
  0,
  1,
};

#include "upb/port/undef.inc"
