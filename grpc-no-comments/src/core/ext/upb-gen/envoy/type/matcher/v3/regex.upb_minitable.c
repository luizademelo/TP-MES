
#include <stddef.h>
#include "upb/generated_code_support.h"
#include "envoy/type/matcher/v3/regex.upb_minitable.h"
#include "google/protobuf/wrappers.upb_minitable.h"
#include "envoy/annotations/deprecation.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
static const upb_MiniTableSubInternal envoy_type_matcher_v3_RegexMatcher__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &envoy__type__matcher__v3__RegexMatcher__GoogleRE2_msg_init_ptr},
};

static const upb_MiniTableField envoy_type_matcher_v3_RegexMatcher__fields[2] = {
  {1, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__type__matcher__v3__RegexMatcher_msg_init = {
  &envoy_type_matcher_v3_RegexMatcher__submsgs[0],
  &envoy_type_matcher_v3_RegexMatcher__fields[0],
  UPB_SIZE(24, 40), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.type.matcher.v3.RegexMatcher",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x002000080100000a, &upb_pom_1bt_max64b},
    {0x001000003f000012, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__type__matcher__v3__RegexMatcher_msg_init_ptr = &envoy__type__matcher__v3__RegexMatcher_msg_init;
static const upb_MiniTableSubInternal envoy_type_matcher_v3_RegexMatcher_GoogleRE2__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__UInt32Value_msg_init_ptr},
};

static const upb_MiniTableField envoy_type_matcher_v3_RegexMatcher_GoogleRE2__fields[1] = {
  {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__type__matcher__v3__RegexMatcher__GoogleRE2_msg_init = {
  &envoy_type_matcher_v3_RegexMatcher_GoogleRE2__submsgs[0],
  &envoy_type_matcher_v3_RegexMatcher_GoogleRE2__fields[0],
  UPB_SIZE(16, 24), 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.type.matcher.v3.RegexMatcher.GoogleRE2",
#endif
};

const upb_MiniTable* envoy__type__matcher__v3__RegexMatcher__GoogleRE2_msg_init_ptr = &envoy__type__matcher__v3__RegexMatcher__GoogleRE2_msg_init;
static const upb_MiniTableSubInternal envoy_type_matcher_v3_RegexMatchAndSubstitute__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &envoy__type__matcher__v3__RegexMatcher_msg_init_ptr},
};

static const upb_MiniTableField envoy_type_matcher_v3_RegexMatchAndSubstitute__fields[2] = {
  {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__type__matcher__v3__RegexMatchAndSubstitute_msg_init = {
  &envoy_type_matcher_v3_RegexMatchAndSubstitute__submsgs[0],
  &envoy_type_matcher_v3_RegexMatchAndSubstitute__fields[0],
  UPB_SIZE(24, 40), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.type.matcher.v3.RegexMatchAndSubstitute",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f000012, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__type__matcher__v3__RegexMatchAndSubstitute_msg_init_ptr = &envoy__type__matcher__v3__RegexMatchAndSubstitute_msg_init;
static const upb_MiniTable *messages_layout[3] = {
  &envoy__type__matcher__v3__RegexMatcher_msg_init,
  &envoy__type__matcher__v3__RegexMatcher__GoogleRE2_msg_init,
  &envoy__type__matcher__v3__RegexMatchAndSubstitute_msg_init,
};

const upb_MiniTableFile envoy_type_matcher_v3_regex_proto_upb_file_layout = {
  messages_layout,
  NULL,
  NULL,
  3,
  0,
  0,
};

#include "upb/port/undef.inc"
