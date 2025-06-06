
#include <stddef.h>
#include "upb/generated_code_support.h"
#include "envoy/type/v3/semantic_version.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"

#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
static const upb_MiniTableField envoy_type_v3_SemanticVersion__fields[3] = {
  {1, 8, 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {2, 12, 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {3, 16, 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__type__v3__SemanticVersion_msg_init = {
  NULL,
  &envoy_type_v3_SemanticVersion__fields[0],
  24, 3, kUpb_ExtMode_NonExtendable, 3, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.type.v3.SemanticVersion",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f000008, &upb_psv4_1bt},
    {0x000c00003f000010, &upb_psv4_1bt},
    {0x001000003f000018, &upb_psv4_1bt},
  })
};

const upb_MiniTable* envoy__type__v3__SemanticVersion_msg_init_ptr = &envoy__type__v3__SemanticVersion_msg_init;
static const upb_MiniTable *messages_layout[1] = {
  &envoy__type__v3__SemanticVersion_msg_init,
};

const upb_MiniTableFile envoy_type_v3_semantic_version_proto_upb_file_layout = {
  messages_layout,
  NULL,
  NULL,
  1,
  0,
  0,
};

#include "upb/port/undef.inc"
