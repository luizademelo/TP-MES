
#include <stddef.h>
#include "upb/generated_code_support.h"
#include "envoy/config/core/v3/proxy_protocol.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
static const upb_MiniTableField envoy_config_core_v3_ProxyProtocolPassThroughTLVs__fields[2] = {
  {1, 8, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 16), 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__core__v3__ProxyProtocolPassThroughTLVs_msg_init = {
  NULL,
  &envoy_config_core_v3_ProxyProtocolPassThroughTLVs__fields[0],
  UPB_SIZE(16, 24), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.core.v3.ProxyProtocolPassThroughTLVs",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f000008, &upb_psv4_1bt},
    {0x001000003f000012, &upb_ppv4_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__config__core__v3__ProxyProtocolPassThroughTLVs_msg_init_ptr = &envoy__config__core__v3__ProxyProtocolPassThroughTLVs_msg_init;
static const upb_MiniTableSubInternal envoy_config_core_v3_ProxyProtocolConfig__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__ProxyProtocolPassThroughTLVs_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_core_v3_ProxyProtocolConfig__fields[2] = {
  {1, 12, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {2, 16, 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__core__v3__ProxyProtocolConfig_msg_init = {
  &envoy_config_core_v3_ProxyProtocolConfig__submsgs[0],
  &envoy_config_core_v3_ProxyProtocolConfig__fields[0],
  24, 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.core.v3.ProxyProtocolConfig",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000c00003f000008, &upb_psv4_1bt},
  })
};

const upb_MiniTable* envoy__config__core__v3__ProxyProtocolConfig_msg_init_ptr = &envoy__config__core__v3__ProxyProtocolConfig_msg_init;
static const upb_MiniTable *messages_layout[2] = {
  &envoy__config__core__v3__ProxyProtocolPassThroughTLVs_msg_init,
  &envoy__config__core__v3__ProxyProtocolConfig_msg_init,
};

const upb_MiniTableFile envoy_config_core_v3_proxy_protocol_proto_upb_file_layout = {
  messages_layout,
  NULL,
  NULL,
  2,
  0,
  0,
};

#include "upb/port/undef.inc"
