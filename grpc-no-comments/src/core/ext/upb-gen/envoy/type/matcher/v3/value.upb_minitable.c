
#include <stddef.h>
#include "upb/generated_code_support.h"
#include "envoy/type/matcher/v3/value.upb_minitable.h"
#include "envoy/type/matcher/v3/number.upb_minitable.h"
#include "envoy/type/matcher/v3/string.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
static const upb_MiniTableSubInternal envoy_type_matcher_v3_ValueMatcher__submsgs[5] = {
  {.UPB_PRIVATE(submsg) = &envoy__type__matcher__v3__ValueMatcher__NullMatch_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__type__matcher__v3__DoubleMatcher_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__type__matcher__v3__StringMatcher_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__type__matcher__v3__ListMatcher_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__type__matcher__v3__OrMatcher_msg_init_ptr},
};

static const upb_MiniTableField envoy_type_matcher_v3_ValueMatcher__fields[7] = {
  {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(12, 16), -9, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(12, 16), -9, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(12, 16), -9, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {6, UPB_SIZE(12, 16), -9, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {7, UPB_SIZE(12, 16), -9, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__type__matcher__v3__ValueMatcher_msg_init = {
  &envoy_type_matcher_v3_ValueMatcher__submsgs[0],
  &envoy_type_matcher_v3_ValueMatcher__fields[0],
  UPB_SIZE(16, 24), 7, kUpb_ExtMode_NonExtendable, 7, UPB_FASTTABLE_MASK(56), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.type.matcher.v3.ValueMatcher",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000080100000a, &upb_pom_1bt_max64b},
    {0x0010000802010012, &upb_pom_1bt_maxmaxb},
    {0x001000080302001a, &upb_pom_1bt_maxmaxb},
    {0x0010000804000020, &upb_pob1_1bt},
    {0x0010000805000028, &upb_pob1_1bt},
    {0x0010000806030032, &upb_pom_1bt_max64b},
    {0x001000080704003a, &upb_pom_1bt_max64b},
  })
};

const upb_MiniTable* envoy__type__matcher__v3__ValueMatcher_msg_init_ptr = &envoy__type__matcher__v3__ValueMatcher_msg_init;
const upb_MiniTable envoy__type__matcher__v3__ValueMatcher__NullMatch_msg_init = {
  NULL,
  NULL,
  8, 0, kUpb_ExtMode_NonExtendable, 0, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.type.matcher.v3.ValueMatcher.NullMatch",
#endif
};

const upb_MiniTable* envoy__type__matcher__v3__ValueMatcher__NullMatch_msg_init_ptr = &envoy__type__matcher__v3__ValueMatcher__NullMatch_msg_init;
static const upb_MiniTableSubInternal envoy_type_matcher_v3_ListMatcher__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &envoy__type__matcher__v3__ValueMatcher_msg_init_ptr},
};

static const upb_MiniTableField envoy_type_matcher_v3_ListMatcher__fields[1] = {
  {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__type__matcher__v3__ListMatcher_msg_init = {
  &envoy_type_matcher_v3_ListMatcher__submsgs[0],
  &envoy_type_matcher_v3_ListMatcher__fields[0],
  UPB_SIZE(16, 24), 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.type.matcher.v3.ListMatcher",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000080100000a, &upb_pom_1bt_max64b},
  })
};

const upb_MiniTable* envoy__type__matcher__v3__ListMatcher_msg_init_ptr = &envoy__type__matcher__v3__ListMatcher_msg_init;
static const upb_MiniTableSubInternal envoy_type_matcher_v3_OrMatcher__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &envoy__type__matcher__v3__ValueMatcher_msg_init_ptr},
};

static const upb_MiniTableField envoy_type_matcher_v3_OrMatcher__fields[1] = {
  {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__type__matcher__v3__OrMatcher_msg_init = {
  &envoy_type_matcher_v3_OrMatcher__submsgs[0],
  &envoy_type_matcher_v3_OrMatcher__fields[0],
  16, 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.type.matcher.v3.OrMatcher",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f00000a, &upb_prm_1bt_max64b},
  })
};

const upb_MiniTable* envoy__type__matcher__v3__OrMatcher_msg_init_ptr = &envoy__type__matcher__v3__OrMatcher_msg_init;
static const upb_MiniTable *messages_layout[4] = {
  &envoy__type__matcher__v3__ValueMatcher_msg_init,
  &envoy__type__matcher__v3__ValueMatcher__NullMatch_msg_init,
  &envoy__type__matcher__v3__ListMatcher_msg_init,
  &envoy__type__matcher__v3__OrMatcher_msg_init,
};

const upb_MiniTableFile envoy_type_matcher_v3_value_proto_upb_file_layout = {
  messages_layout,
  NULL,
  NULL,
  4,
  0,
  0,
};

#include "upb/port/undef.inc"
