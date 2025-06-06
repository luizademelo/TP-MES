
#include <stddef.h>
#include "upb/generated_code_support.h"
#include "envoy/type/matcher/v3/string.upb_minitable.h"
#include "envoy/type/matcher/v3/regex.upb_minitable.h"
#include "xds/core/v3/extension.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
static const upb_MiniTableSubInternal envoy_type_matcher_v3_StringMatcher__submsgs[2] = {
  {.UPB_PRIVATE(submsg) = &envoy__type__matcher__v3__RegexMatcher_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &xds__core__v3__TypedExtensionConfig_msg_init_ptr},
};

static const upb_MiniTableField envoy_type_matcher_v3_StringMatcher__fields[7] = {
  {1, 16, -13, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, 16, -13, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {3, 16, -13, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {5, 16, -13, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {6, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {7, 16, -13, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {8, 16, -13, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__type__matcher__v3__StringMatcher_msg_init = {
  &envoy_type_matcher_v3_StringMatcher__submsgs[0],
  &envoy_type_matcher_v3_StringMatcher__fields[0],
  UPB_SIZE(24, 32), 7, kUpb_ExtMode_NonExtendable, 3, UPB_FASTTABLE_MASK(120), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.type.matcher.v3.StringMatcher",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0010000c0100000a, &upb_pos_1bt},
    {0x0010000c02000012, &upb_pos_1bt},
    {0x0010000c0300001a, &upb_pos_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0010000c0500002a, &upb_pom_1bt_maxmaxb},
    {0x000800003f000030, &upb_psb1_1bt},
    {0x0010000c0700003a, &upb_pos_1bt},
    {0x0010000c08010042, &upb_pom_1bt_maxmaxb},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__type__matcher__v3__StringMatcher_msg_init_ptr = &envoy__type__matcher__v3__StringMatcher_msg_init;
static const upb_MiniTableSubInternal envoy_type_matcher_v3_ListStringMatcher__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &envoy__type__matcher__v3__StringMatcher_msg_init_ptr},
};

static const upb_MiniTableField envoy_type_matcher_v3_ListStringMatcher__fields[1] = {
  {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__type__matcher__v3__ListStringMatcher_msg_init = {
  &envoy_type_matcher_v3_ListStringMatcher__submsgs[0],
  &envoy_type_matcher_v3_ListStringMatcher__fields[0],
  16, 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.type.matcher.v3.ListStringMatcher",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f00000a, &upb_prm_1bt_max64b},
  })
};

const upb_MiniTable* envoy__type__matcher__v3__ListStringMatcher_msg_init_ptr = &envoy__type__matcher__v3__ListStringMatcher_msg_init;
static const upb_MiniTable *messages_layout[2] = {
  &envoy__type__matcher__v3__StringMatcher_msg_init,
  &envoy__type__matcher__v3__ListStringMatcher_msg_init,
};

const upb_MiniTableFile envoy_type_matcher_v3_string_proto_upb_file_layout = {
  messages_layout,
  NULL,
  NULL,
  2,
  0,
  0,
};

#include "upb/port/undef.inc"
