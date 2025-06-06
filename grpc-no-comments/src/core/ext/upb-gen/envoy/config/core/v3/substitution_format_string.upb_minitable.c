
#include <stddef.h>
#include "upb/generated_code_support.h"
#include "envoy/config/core/v3/substitution_format_string.upb_minitable.h"
#include "envoy/config/core/v3/base.upb_minitable.h"
#include "envoy/config/core/v3/extension.upb_minitable.h"
#include "google/protobuf/struct.upb_minitable.h"
#include "envoy/annotations/deprecation.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
static const upb_MiniTableField envoy_config_core_v3_JsonFormatOptions__fields[1] = {
  {1, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__core__v3__JsonFormatOptions_msg_init = {
  NULL,
  &envoy_config_core_v3_JsonFormatOptions__fields[0],
  16, 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.core.v3.JsonFormatOptions",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f000008, &upb_psb1_1bt},
  })
};

const upb_MiniTable* envoy__config__core__v3__JsonFormatOptions_msg_init_ptr = &envoy__config__core__v3__JsonFormatOptions_msg_init;
static const upb_MiniTableSubInternal envoy_config_core_v3_SubstitutionFormatString__submsgs[4] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__Struct_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__DataSource_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__TypedExtensionConfig_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__JsonFormatOptions_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_core_v3_SubstitutionFormatString__fields[7] = {
  {1, 32, UPB_SIZE(-21, -13), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, 32, UPB_SIZE(-21, -13), 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(24, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {5, 32, UPB_SIZE(-21, -13), 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {6, UPB_SIZE(12, 48), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {7, UPB_SIZE(16, 56), 64, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__core__v3__SubstitutionFormatString_msg_init = {
  &envoy_config_core_v3_SubstitutionFormatString__submsgs[0],
  &envoy_config_core_v3_SubstitutionFormatString__fields[0],
  UPB_SIZE(40, 64), 7, kUpb_ExtMode_NonExtendable, 7, UPB_FASTTABLE_MASK(56), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.core.v3.SubstitutionFormatString",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0020000c0100000a, &upb_pos_1bt},
    {0x0020000c02000012, &upb_pom_1bt_maxmaxb},
    {0x000900003f000018, &upb_psb1_1bt},
    {0x001000003f000022, &upb_pss_1bt},
    {0x0020000c0501002a, &upb_pom_1bt_maxmaxb},
    {0x003000003f020032, &upb_prm_1bt_maxmaxb},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__config__core__v3__SubstitutionFormatString_msg_init_ptr = &envoy__config__core__v3__SubstitutionFormatString_msg_init;
static const upb_MiniTable *messages_layout[2] = {
  &envoy__config__core__v3__JsonFormatOptions_msg_init,
  &envoy__config__core__v3__SubstitutionFormatString_msg_init,
};

const upb_MiniTableFile envoy_config_core_v3_substitution_format_string_proto_upb_file_layout = {
  messages_layout,
  NULL,
  NULL,
  2,
  0,
  0,
};

#include "upb/port/undef.inc"
