
#include <stddef.h>
#include "upb/generated_code_support.h"
#include "envoy/admin/v3/tap.upb_minitable.h"
#include "envoy/config/tap/v3/common.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
static const upb_MiniTableSubInternal envoy_admin_v3_TapRequest__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__tap__v3__TapConfig_msg_init_ptr},
};

static const upb_MiniTableField envoy_admin_v3_TapRequest__fields[2] = {
  {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__admin__v3__TapRequest_msg_init = {
  &envoy_admin_v3_TapRequest__submsgs[0],
  &envoy_admin_v3_TapRequest__fields[0],
  UPB_SIZE(24, 40), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.admin.v3.TapRequest",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
  })
};

const upb_MiniTable* envoy__admin__v3__TapRequest_msg_init_ptr = &envoy__admin__v3__TapRequest_msg_init;
static const upb_MiniTable *messages_layout[1] = {
  &envoy__admin__v3__TapRequest_msg_init,
};

const upb_MiniTableFile envoy_admin_v3_tap_proto_upb_file_layout = {
  messages_layout,
  NULL,
  NULL,
  1,
  0,
  0,
};

#include "upb/port/undef.inc"
