
#include <stddef.h>
#include "upb/generated_code_support.h"
#include "xds/annotations/v3/status.upb_minitable.h"
#include "google/protobuf/descriptor.upb_minitable.h"

#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
static const upb_MiniTableField xds_annotations_v3_FileStatusAnnotation__fields[1] = {
  {1, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable xds__annotations__v3__FileStatusAnnotation_msg_init = {
  NULL,
  &xds_annotations_v3_FileStatusAnnotation__fields[0],
  16, 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "xds.annotations.v3.FileStatusAnnotation",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f000008, &upb_psb1_1bt},
  })
};

const upb_MiniTable* xds__annotations__v3__FileStatusAnnotation_msg_init_ptr = &xds__annotations__v3__FileStatusAnnotation_msg_init;
static const upb_MiniTableField xds_annotations_v3_MessageStatusAnnotation__fields[1] = {
  {1, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable xds__annotations__v3__MessageStatusAnnotation_msg_init = {
  NULL,
  &xds_annotations_v3_MessageStatusAnnotation__fields[0],
  16, 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "xds.annotations.v3.MessageStatusAnnotation",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f000008, &upb_psb1_1bt},
  })
};

const upb_MiniTable* xds__annotations__v3__MessageStatusAnnotation_msg_init_ptr = &xds__annotations__v3__MessageStatusAnnotation_msg_init;
static const upb_MiniTableField xds_annotations_v3_FieldStatusAnnotation__fields[1] = {
  {1, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable xds__annotations__v3__FieldStatusAnnotation_msg_init = {
  NULL,
  &xds_annotations_v3_FieldStatusAnnotation__fields[0],
  16, 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "xds.annotations.v3.FieldStatusAnnotation",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f000008, &upb_psb1_1bt},
  })
};

const upb_MiniTable* xds__annotations__v3__FieldStatusAnnotation_msg_init_ptr = &xds__annotations__v3__FieldStatusAnnotation_msg_init;
static const upb_MiniTableField xds_annotations_v3_StatusAnnotation__fields[2] = {
  {1, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {2, 12, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable xds__annotations__v3__StatusAnnotation_msg_init = {
  NULL,
  &xds_annotations_v3_StatusAnnotation__fields[0],
  16, 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "xds.annotations.v3.StatusAnnotation",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f000008, &upb_psb1_1bt},
    {0x000c00003f000010, &upb_psv4_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* xds__annotations__v3__StatusAnnotation_msg_init_ptr = &xds__annotations__v3__StatusAnnotation_msg_init;
UPB_LINKARR_APPEND(upb_AllExts)
const upb_MiniTableExtension xds_annotations_v3_file_status_ext = {
  {226829418, 0, 0, 0, 11, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsExtension | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  &google__protobuf__FileOptions_msg_init,
  {.UPB_PRIVATE(submsg) = &xds__annotations__v3__FileStatusAnnotation_msg_init},

};
UPB_LINKARR_APPEND(upb_AllExts)
const upb_MiniTableExtension xds_annotations_v3_message_status_ext = {
  {226829418, 0, 0, 0, 11, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsExtension | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  &google__protobuf__MessageOptions_msg_init,
  {.UPB_PRIVATE(submsg) = &xds__annotations__v3__MessageStatusAnnotation_msg_init},

};
UPB_LINKARR_APPEND(upb_AllExts)
const upb_MiniTableExtension xds_annotations_v3_field_status_ext = {
  {226829418, 0, 0, 0, 11, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsExtension | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  &google__protobuf__FieldOptions_msg_init,
  {.UPB_PRIVATE(submsg) = &xds__annotations__v3__FieldStatusAnnotation_msg_init},

};
static const upb_MiniTable *messages_layout[4] = {
  &xds__annotations__v3__FileStatusAnnotation_msg_init,
  &xds__annotations__v3__MessageStatusAnnotation_msg_init,
  &xds__annotations__v3__FieldStatusAnnotation_msg_init,
  &xds__annotations__v3__StatusAnnotation_msg_init,
};

static const upb_MiniTableExtension *extensions_layout[3] = {
  &xds_annotations_v3_file_status_ext,
  &xds_annotations_v3_message_status_ext,
  &xds_annotations_v3_field_status_ext,
};

const upb_MiniTableFile xds_annotations_v3_status_proto_upb_file_layout = {
  messages_layout,
  NULL,
  extensions_layout,
  4,
  0,
  3,
};

#include "upb/port/undef.inc"
