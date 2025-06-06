
#include <stddef.h>
#include "upb/generated_code_support.h"
#include "envoy/type/matcher/v3/number.upb_minitable.h"
#include "envoy/type/v3/range.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
static const upb_MiniTableSubInternal envoy_type_matcher_v3_DoubleMatcher__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &envoy__type__v3__DoubleRange_msg_init_ptr},
};

static const upb_MiniTableField envoy_type_matcher_v3_DoubleMatcher__fields[2] = {
  {1, 16, -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, 16, -9, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__type__matcher__v3__DoubleMatcher_msg_init = {
  &envoy_type_matcher_v3_DoubleMatcher__submsgs[0],
  &envoy_type_matcher_v3_DoubleMatcher__fields[0],
  24, 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.type.matcher.v3.DoubleMatcher",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000080100000a, &upb_pom_1bt_maxmaxb},
    {0x0010000802000011, &upb_pof8_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__type__matcher__v3__DoubleMatcher_msg_init_ptr = &envoy__type__matcher__v3__DoubleMatcher_msg_init;
static const upb_MiniTable *messages_layout[1] = {
  &envoy__type__matcher__v3__DoubleMatcher_msg_init,
};

const upb_MiniTableFile envoy_type_matcher_v3_number_proto_upb_file_layout = {
  messages_layout,
  NULL,
  NULL,
  1,
  0,
  0,
};

#include "upb/port/undef.inc"
