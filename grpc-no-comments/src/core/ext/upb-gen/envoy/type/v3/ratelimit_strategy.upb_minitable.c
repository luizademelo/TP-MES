
#include <stddef.h>
#include "upb/generated_code_support.h"
#include "envoy/type/v3/ratelimit_strategy.upb_minitable.h"
#include "envoy/type/v3/ratelimit_unit.upb_minitable.h"
#include "envoy/type/v3/token_bucket.upb_minitable.h"
#include "xds/annotations/v3/status.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
static const upb_MiniTableSubInternal envoy_type_v3_RateLimitStrategy__submsgs[2] = {
  {.UPB_PRIVATE(submsg) = &envoy__type__v3__RateLimitStrategy__RequestsPerTimeUnit_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__type__v3__TokenBucket_msg_init_ptr},
};

static const upb_MiniTableField envoy_type_v3_RateLimitStrategy__fields[3] = {
  {1, UPB_SIZE(12, 16), -9, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__type__v3__RateLimitStrategy_msg_init = {
  &envoy_type_v3_RateLimitStrategy__submsgs[0],
  &envoy_type_v3_RateLimitStrategy__fields[0],
  UPB_SIZE(16, 24), 3, kUpb_ExtMode_NonExtendable, 3, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.type.v3.RateLimitStrategy",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0010000801000008, &upb_pov4_1bt},
    {0x0010000802000012, &upb_pom_1bt_max64b},
    {0x001000080301001a, &upb_pom_1bt_maxmaxb},
  })
};

const upb_MiniTable* envoy__type__v3__RateLimitStrategy_msg_init_ptr = &envoy__type__v3__RateLimitStrategy_msg_init;
static const upb_MiniTableField envoy_type_v3_RateLimitStrategy_RequestsPerTimeUnit__fields[2] = {
  {1, 16, 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {2, 8, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__type__v3__RateLimitStrategy__RequestsPerTimeUnit_msg_init = {
  NULL,
  &envoy_type_v3_RateLimitStrategy_RequestsPerTimeUnit__fields[0],
  24, 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.type.v3.RateLimitStrategy.RequestsPerTimeUnit",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f000008, &upb_psv8_1bt},
    {0x000800003f000010, &upb_psv4_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__type__v3__RateLimitStrategy__RequestsPerTimeUnit_msg_init_ptr = &envoy__type__v3__RateLimitStrategy__RequestsPerTimeUnit_msg_init;
static const upb_MiniTable *messages_layout[2] = {
  &envoy__type__v3__RateLimitStrategy_msg_init,
  &envoy__type__v3__RateLimitStrategy__RequestsPerTimeUnit_msg_init,
};

const upb_MiniTableFile envoy_type_v3_ratelimit_strategy_proto_upb_file_layout = {
  messages_layout,
  NULL,
  NULL,
  2,
  0,
  0,
};

#include "upb/port/undef.inc"
