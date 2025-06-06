
#include <stddef.h>
#include "upb/generated_code_support.h"
#include "xds/type/matcher/v3/cel.upb_minitable.h"
#include "xds/annotations/v3/status.upb_minitable.h"
#include "xds/type/v3/cel.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
static const upb_MiniTableSubInternal xds_type_matcher_v3_CelMatcher__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &xds__type__v3__CelExpression_msg_init_ptr},
};

static const upb_MiniTableField xds_type_matcher_v3_CelMatcher__fields[2] = {
  {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
};

const upb_MiniTable xds__type__matcher__v3__CelMatcher_msg_init = {
  &xds_type_matcher_v3_CelMatcher__submsgs[0],
  &xds_type_matcher_v3_CelMatcher__fields[0],
  UPB_SIZE(24, 40), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "xds.type.matcher.v3.CelMatcher",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f000012, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* xds__type__matcher__v3__CelMatcher_msg_init_ptr = &xds__type__matcher__v3__CelMatcher_msg_init;
static const upb_MiniTable *messages_layout[1] = {
  &xds__type__matcher__v3__CelMatcher_msg_init,
};

const upb_MiniTableFile xds_type_matcher_v3_cel_proto_upb_file_layout = {
  messages_layout,
  NULL,
  NULL,
  1,
  0,
  0,
};

#include "upb/port/undef.inc"
