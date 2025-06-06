
#include <stddef.h>
#include "upb/generated_code_support.h"
#include "xds/annotations/v3/security.upb_minitable.h"
#include "xds/annotations/v3/status.upb_minitable.h"
#include "google/protobuf/descriptor.upb_minitable.h"

#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
static const upb_MiniTableField xds_annotations_v3_FieldSecurityAnnotation__fields[2] = {
  {1, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {2, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable xds__annotations__v3__FieldSecurityAnnotation_msg_init = {
  NULL,
  &xds_annotations_v3_FieldSecurityAnnotation__fields[0],
  16, 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "xds.annotations.v3.FieldSecurityAnnotation",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f000008, &upb_psb1_1bt},
    {0x000900003f000010, &upb_psb1_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* xds__annotations__v3__FieldSecurityAnnotation_msg_init_ptr = &xds__annotations__v3__FieldSecurityAnnotation_msg_init;
UPB_LINKARR_APPEND(upb_AllExts)
const upb_MiniTableExtension xds_annotations_v3_security_ext = {
  {99044135, 0, 0, 0, 11, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsExtension | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  &google__protobuf__FieldOptions_msg_init,
  {.UPB_PRIVATE(submsg) = &xds__annotations__v3__FieldSecurityAnnotation_msg_init},

};
static const upb_MiniTable *messages_layout[1] = {
  &xds__annotations__v3__FieldSecurityAnnotation_msg_init,
};

static const upb_MiniTableExtension *extensions_layout[1] = {
  &xds_annotations_v3_security_ext,
};

const upb_MiniTableFile xds_annotations_v3_security_proto_upb_file_layout = {
  messages_layout,
  NULL,
  extensions_layout,
  1,
  0,
  1,
};

#include "upb/port/undef.inc"
