
#include <stddef.h>
#include "upb/generated_code_support.h"
#include "envoy/annotations/resource.upb_minitable.h"
#include "google/protobuf/descriptor.upb_minitable.h"

#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
static const upb_MiniTableField envoy_annotations_ResourceAnnotation__fields[1] = {
  {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__annotations__ResourceAnnotation_msg_init = {
  NULL,
  &envoy_annotations_ResourceAnnotation__fields[0],
  UPB_SIZE(16, 24), 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.annotations.ResourceAnnotation",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f00000a, &upb_pss_1bt},
  })
};

const upb_MiniTable* envoy__annotations__ResourceAnnotation_msg_init_ptr = &envoy__annotations__ResourceAnnotation_msg_init;
UPB_LINKARR_APPEND(upb_AllExts)
const upb_MiniTableExtension envoy_annotations_resource_ext = {
  {265073217, 0, 0, 0, 11, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsExtension | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  &google__protobuf__ServiceOptions_msg_init,
  {.UPB_PRIVATE(submsg) = &envoy__annotations__ResourceAnnotation_msg_init},

};
static const upb_MiniTable *messages_layout[1] = {
  &envoy__annotations__ResourceAnnotation_msg_init,
};

static const upb_MiniTableExtension *extensions_layout[1] = {
  &envoy_annotations_resource_ext,
};

const upb_MiniTableFile envoy_annotations_resource_proto_upb_file_layout = {
  messages_layout,
  NULL,
  extensions_layout,
  1,
  0,
  1,
};

#include "upb/port/undef.inc"
