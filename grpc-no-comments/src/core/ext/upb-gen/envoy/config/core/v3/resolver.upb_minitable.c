
#include <stddef.h>
#include "upb/generated_code_support.h"
#include "envoy/config/core/v3/resolver.upb_minitable.h"
#include "envoy/config/core/v3/address.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
static const upb_MiniTableField envoy_config_core_v3_DnsResolverOptions__fields[2] = {
  {1, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {2, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__core__v3__DnsResolverOptions_msg_init = {
  NULL,
  &envoy_config_core_v3_DnsResolverOptions__fields[0],
  16, 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.core.v3.DnsResolverOptions",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f000008, &upb_psb1_1bt},
    {0x000900003f000010, &upb_psb1_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__config__core__v3__DnsResolverOptions_msg_init_ptr = &envoy__config__core__v3__DnsResolverOptions_msg_init;
static const upb_MiniTableSubInternal envoy_config_core_v3_DnsResolutionConfig__submsgs[2] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__Address_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__DnsResolverOptions_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_core_v3_DnsResolutionConfig__fields[2] = {
  {1, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 24), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__core__v3__DnsResolutionConfig_msg_init = {
  &envoy_config_core_v3_DnsResolutionConfig__submsgs[0],
  &envoy_config_core_v3_DnsResolutionConfig__fields[0],
  UPB_SIZE(24, 32), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.core.v3.DnsResolutionConfig",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_prm_1bt_maxmaxb},
  })
};

const upb_MiniTable* envoy__config__core__v3__DnsResolutionConfig_msg_init_ptr = &envoy__config__core__v3__DnsResolutionConfig_msg_init;
static const upb_MiniTable *messages_layout[2] = {
  &envoy__config__core__v3__DnsResolverOptions_msg_init,
  &envoy__config__core__v3__DnsResolutionConfig_msg_init,
};

const upb_MiniTableFile envoy_config_core_v3_resolver_proto_upb_file_layout = {
  messages_layout,
  NULL,
  NULL,
  2,
  0,
  0,
};

#include "upb/port/undef.inc"
