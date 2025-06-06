
#include <stddef.h>
#include "upb/generated_code_support.h"
#include "envoy/extensions/load_balancing_policies/common/v3/common.upb_minitable.h"
#include "envoy/config/core/v3/base.upb_minitable.h"
#include "envoy/type/v3/percent.upb_minitable.h"
#include "google/protobuf/duration.upb_minitable.h"
#include "google/protobuf/wrappers.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
static const upb_MiniTableSubInternal envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig__submsgs[2] = {
  {.UPB_PRIVATE(submsg) = &envoy__extensions__load_0balancing_0policies__common__v3__LocalityLbConfig__ZoneAwareLbConfig_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__extensions__load_0balancing_0policies__common__v3__LocalityLbConfig__LocalityWeightedLbConfig_msg_init_ptr},
};

static const upb_MiniTableField envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig__fields[2] = {
  {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__extensions__load_0balancing_0policies__common__v3__LocalityLbConfig_msg_init = {
  &envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig__submsgs[0],
  &envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig__fields[0],
  UPB_SIZE(16, 24), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.extensions.load_balancing_policies.common.v3.LocalityLbConfig",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000080100000a, &upb_pom_1bt_max64b},
    {0x0010000802010012, &upb_pom_1bt_max64b},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__extensions__load_0balancing_0policies__common__v3__LocalityLbConfig_msg_init_ptr = &envoy__extensions__load_0balancing_0policies__common__v3__LocalityLbConfig_msg_init;
static const upb_MiniTableSubInternal envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_ZoneAwareLbConfig__submsgs[2] = {
  {.UPB_PRIVATE(submsg) = &envoy__type__v3__Percent_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__UInt64Value_msg_init_ptr},
};

static const upb_MiniTableField envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_ZoneAwareLbConfig__fields[3] = {
  {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__extensions__load_0balancing_0policies__common__v3__LocalityLbConfig__ZoneAwareLbConfig_msg_init = {
  &envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_ZoneAwareLbConfig__submsgs[0],
  &envoy_extensions_load_balancing_policies_common_v3_LocalityLbConfig_ZoneAwareLbConfig__fields[0],
  UPB_SIZE(24, 32), 3, kUpb_ExtMode_NonExtendable, 3, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.extensions.load_balancing_policies.common.v3.LocalityLbConfig.ZoneAwareLbConfig",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000900003f000018, &upb_psb1_1bt},
  })
};

const upb_MiniTable* envoy__extensions__load_0balancing_0policies__common__v3__LocalityLbConfig__ZoneAwareLbConfig_msg_init_ptr = &envoy__extensions__load_0balancing_0policies__common__v3__LocalityLbConfig__ZoneAwareLbConfig_msg_init;
const upb_MiniTable envoy__extensions__load_0balancing_0policies__common__v3__LocalityLbConfig__LocalityWeightedLbConfig_msg_init = {
  NULL,
  NULL,
  8, 0, kUpb_ExtMode_NonExtendable, 0, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.extensions.load_balancing_policies.common.v3.LocalityLbConfig.LocalityWeightedLbConfig",
#endif
};

const upb_MiniTable* envoy__extensions__load_0balancing_0policies__common__v3__LocalityLbConfig__LocalityWeightedLbConfig_msg_init_ptr = &envoy__extensions__load_0balancing_0policies__common__v3__LocalityLbConfig__LocalityWeightedLbConfig_msg_init;
static const upb_MiniTableSubInternal envoy_extensions_load_balancing_policies_common_v3_SlowStartConfig__submsgs[3] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__Duration_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__RuntimeDouble_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__type__v3__Percent_msg_init_ptr},
};

static const upb_MiniTableField envoy_extensions_load_balancing_policies_common_v3_SlowStartConfig__fields[3] = {
  {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(20, 32), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__extensions__load_0balancing_0policies__common__v3__SlowStartConfig_msg_init = {
  &envoy_extensions_load_balancing_policies_common_v3_SlowStartConfig__submsgs[0],
  &envoy_extensions_load_balancing_policies_common_v3_SlowStartConfig__fields[0],
  UPB_SIZE(24, 40), 3, kUpb_ExtMode_NonExtendable, 3, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.extensions.load_balancing_policies.common.v3.SlowStartConfig",
#endif
};

const upb_MiniTable* envoy__extensions__load_0balancing_0policies__common__v3__SlowStartConfig_msg_init_ptr = &envoy__extensions__load_0balancing_0policies__common__v3__SlowStartConfig_msg_init;
static const upb_MiniTableSubInternal envoy_extensions_load_balancing_policies_common_v3_ConsistentHashingLbConfig__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__UInt32Value_msg_init_ptr},
};

static const upb_MiniTableField envoy_extensions_load_balancing_policies_common_v3_ConsistentHashingLbConfig__fields[2] = {
  {1, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__extensions__load_0balancing_0policies__common__v3__ConsistentHashingLbConfig_msg_init = {
  &envoy_extensions_load_balancing_policies_common_v3_ConsistentHashingLbConfig__submsgs[0],
  &envoy_extensions_load_balancing_policies_common_v3_ConsistentHashingLbConfig__fields[0],
  UPB_SIZE(16, 24), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.extensions.load_balancing_policies.common.v3.ConsistentHashingLbConfig",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000900003f000008, &upb_psb1_1bt},
  })
};

const upb_MiniTable* envoy__extensions__load_0balancing_0policies__common__v3__ConsistentHashingLbConfig_msg_init_ptr = &envoy__extensions__load_0balancing_0policies__common__v3__ConsistentHashingLbConfig_msg_init;
static const upb_MiniTable *messages_layout[5] = {
  &envoy__extensions__load_0balancing_0policies__common__v3__LocalityLbConfig_msg_init,
  &envoy__extensions__load_0balancing_0policies__common__v3__LocalityLbConfig__ZoneAwareLbConfig_msg_init,
  &envoy__extensions__load_0balancing_0policies__common__v3__LocalityLbConfig__LocalityWeightedLbConfig_msg_init,
  &envoy__extensions__load_0balancing_0policies__common__v3__SlowStartConfig_msg_init,
  &envoy__extensions__load_0balancing_0policies__common__v3__ConsistentHashingLbConfig_msg_init,
};

const upb_MiniTableFile envoy_extensions_load_balancing_policies_common_v3_common_proto_upb_file_layout = {
  messages_layout,
  NULL,
  NULL,
  5,
  0,
  0,
};

#include "upb/port/undef.inc"
