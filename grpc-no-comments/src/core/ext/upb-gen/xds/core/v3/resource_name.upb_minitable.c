
#include <stddef.h>
#include "upb/generated_code_support.h"
#include "xds/core/v3/resource_name.upb_minitable.h"
#include "xds/annotations/v3/status.upb_minitable.h"
#include "xds/core/v3/context_params.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
static const upb_MiniTableSubInternal xds_core_v3_ResourceName__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &xds__core__v3__ContextParams_msg_init_ptr},
};

static const upb_MiniTableField xds_core_v3_ResourceName__fields[4] = {
  {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(24, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(32, 48), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(12, 64), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable xds__core__v3__ResourceName_msg_init = {
  &xds_core_v3_ResourceName__submsgs[0],
  &xds_core_v3_ResourceName__fields[0],
  UPB_SIZE(40, 72), 4, kUpb_ExtMode_NonExtendable, 4, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "xds.core.v3.ResourceName",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
    {0x002000003f000012, &upb_pss_1bt},
    {0x003000003f00001a, &upb_pss_1bt},
  })
};

const upb_MiniTable* xds__core__v3__ResourceName_msg_init_ptr = &xds__core__v3__ResourceName_msg_init;
static const upb_MiniTable *messages_layout[1] = {
  &xds__core__v3__ResourceName_msg_init,
};

const upb_MiniTableFile xds_core_v3_resource_name_proto_upb_file_layout = {
  messages_layout,
  NULL,
  NULL,
  1,
  0,
  0,
};

#include "upb/port/undef.inc"
