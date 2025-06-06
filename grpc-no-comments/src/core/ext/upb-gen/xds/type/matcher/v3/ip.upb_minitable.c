
#include <stddef.h>
#include "upb/generated_code_support.h"
#include "xds/type/matcher/v3/ip.upb_minitable.h"
#include "xds/annotations/v3/status.upb_minitable.h"
#include "xds/core/v3/cidr.upb_minitable.h"
#include "xds/type/matcher/v3/matcher.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
static const upb_MiniTableSubInternal xds_type_matcher_v3_IPMatcher__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &xds__type__matcher__v3__IPMatcher__IPRangeMatcher_msg_init_ptr},
};

static const upb_MiniTableField xds_type_matcher_v3_IPMatcher__fields[1] = {
  {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable xds__type__matcher__v3__IPMatcher_msg_init = {
  &xds_type_matcher_v3_IPMatcher__submsgs[0],
  &xds_type_matcher_v3_IPMatcher__fields[0],
  16, 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "xds.type.matcher.v3.IPMatcher",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f00000a, &upb_prm_1bt_max64b},
  })
};

const upb_MiniTable* xds__type__matcher__v3__IPMatcher_msg_init_ptr = &xds__type__matcher__v3__IPMatcher_msg_init;
static const upb_MiniTableSubInternal xds_type_matcher_v3_IPMatcher_IPRangeMatcher__submsgs[2] = {
  {.UPB_PRIVATE(submsg) = &xds__core__v3__CidrRange_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &xds__type__matcher__v3__Matcher__OnMatch_msg_init_ptr},
};

static const upb_MiniTableField xds_type_matcher_v3_IPMatcher_IPRangeMatcher__fields[3] = {
  {1, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 24), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable xds__type__matcher__v3__IPMatcher__IPRangeMatcher_msg_init = {
  &xds_type_matcher_v3_IPMatcher_IPRangeMatcher__submsgs[0],
  &xds_type_matcher_v3_IPMatcher_IPRangeMatcher__fields[0],
  UPB_SIZE(24, 32), 3, kUpb_ExtMode_NonExtendable, 3, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "xds.type.matcher.v3.IPMatcher.IPRangeMatcher",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_prm_1bt_maxmaxb},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000900003f000018, &upb_psb1_1bt},
  })
};

const upb_MiniTable* xds__type__matcher__v3__IPMatcher__IPRangeMatcher_msg_init_ptr = &xds__type__matcher__v3__IPMatcher__IPRangeMatcher_msg_init;
static const upb_MiniTable *messages_layout[2] = {
  &xds__type__matcher__v3__IPMatcher_msg_init,
  &xds__type__matcher__v3__IPMatcher__IPRangeMatcher_msg_init,
};

const upb_MiniTableFile xds_type_matcher_v3_ip_proto_upb_file_layout = {
  messages_layout,
  NULL,
  NULL,
  2,
  0,
  0,
};

#include "upb/port/undef.inc"
