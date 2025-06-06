
#include <stddef.h>
#include "upb/generated_code_support.h"
#include "envoy/type/v3/percent.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
static const upb_MiniTableField envoy_type_v3_Percent__fields[1] = {
  {1, 8, 0, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__type__v3__Percent_msg_init = {
  NULL,
  &envoy_type_v3_Percent__fields[0],
  16, 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.type.v3.Percent",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f000009, &upb_psf8_1bt},
  })
};

const upb_MiniTable* envoy__type__v3__Percent_msg_init_ptr = &envoy__type__v3__Percent_msg_init;
static const upb_MiniTableField envoy_type_v3_FractionalPercent__fields[2] = {
  {1, 8, 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {2, 12, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__type__v3__FractionalPercent_msg_init = {
  NULL,
  &envoy_type_v3_FractionalPercent__fields[0],
  16, 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.type.v3.FractionalPercent",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f000008, &upb_psv4_1bt},
    {0x000c00003f000010, &upb_psv4_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__type__v3__FractionalPercent_msg_init_ptr = &envoy__type__v3__FractionalPercent_msg_init;
static const upb_MiniTable *messages_layout[2] = {
  &envoy__type__v3__Percent_msg_init,
  &envoy__type__v3__FractionalPercent_msg_init,
};

const upb_MiniTableFile envoy_type_v3_percent_proto_upb_file_layout = {
  messages_layout,
  NULL,
  NULL,
  2,
  0,
  0,
};

#include "upb/port/undef.inc"
