
#include <stddef.h>
#include "upb/generated_code_support.h"
#include "envoy/config/core/v3/address.upb_minitable.h"
#include "envoy/config/core/v3/extension.upb_minitable.h"
#include "envoy/config/core/v3/socket_option.upb_minitable.h"
#include "google/protobuf/wrappers.upb_minitable.h"
#include "envoy/annotations/deprecation.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
static const upb_MiniTableField envoy_config_core_v3_Pipe__fields[2] = {
  {1, UPB_SIZE(12, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, 8, 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__core__v3__Pipe_msg_init = {
  NULL,
  &envoy_config_core_v3_Pipe__fields[0],
  UPB_SIZE(24, 32), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.core.v3.Pipe",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
    {0x000800003f000010, &upb_psv4_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__config__core__v3__Pipe_msg_init_ptr = &envoy__config__core__v3__Pipe_msg_init;
static const upb_MiniTableField envoy_config_core_v3_EnvoyInternalAddress__fields[2] = {
  {1, UPB_SIZE(20, 32), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__core__v3__EnvoyInternalAddress_msg_init = {
  NULL,
  &envoy_config_core_v3_EnvoyInternalAddress__fields[0],
  UPB_SIZE(32, 48), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.core.v3.EnvoyInternalAddress",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x002000080100000a, &upb_pos_1bt},
    {0x001000003f000012, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__config__core__v3__EnvoyInternalAddress_msg_init_ptr = &envoy__config__core__v3__EnvoyInternalAddress_msg_init;
static const upb_MiniTableField envoy_config_core_v3_SocketAddress__fields[6] = {
  {1, 12, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(20, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(36, 56), -17, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(36, 56), -17, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(28, 40), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {6, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__core__v3__SocketAddress_msg_init = {
  NULL,
  &envoy_config_core_v3_SocketAddress__fields[0],
  UPB_SIZE(48, 72), 6, kUpb_ExtMode_NonExtendable, 6, UPB_FASTTABLE_MASK(56), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.core.v3.SocketAddress",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000c00003f000008, &upb_psv4_1bt},
    {0x001800003f000012, &upb_pss_1bt},
    {0x0038001003000018, &upb_pov4_1bt},
    {0x0038001004000022, &upb_pos_1bt},
    {0x002800003f00002a, &upb_pss_1bt},
    {0x000800003f000030, &upb_psb1_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__config__core__v3__SocketAddress_msg_init_ptr = &envoy__config__core__v3__SocketAddress_msg_init;
static const upb_MiniTableSubInternal envoy_config_core_v3_TcpKeepalive__submsgs[3] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__UInt32Value_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__UInt32Value_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__UInt32Value_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_core_v3_TcpKeepalive__fields[3] = {
  {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(20, 32), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__core__v3__TcpKeepalive_msg_init = {
  &envoy_config_core_v3_TcpKeepalive__submsgs[0],
  &envoy_config_core_v3_TcpKeepalive__fields[0],
  UPB_SIZE(24, 40), 3, kUpb_ExtMode_NonExtendable, 3, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.core.v3.TcpKeepalive",
#endif
};

const upb_MiniTable* envoy__config__core__v3__TcpKeepalive_msg_init_ptr = &envoy__config__core__v3__TcpKeepalive_msg_init;
static const upb_MiniTableSubInternal envoy_config_core_v3_ExtraSourceAddress__submsgs[2] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__SocketAddress_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__SocketOptionsOverride_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_core_v3_ExtraSourceAddress__fields[2] = {
  {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__core__v3__ExtraSourceAddress_msg_init = {
  &envoy_config_core_v3_ExtraSourceAddress__submsgs[0],
  &envoy_config_core_v3_ExtraSourceAddress__fields[0],
  UPB_SIZE(24, 32), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.core.v3.ExtraSourceAddress",
#endif
};

const upb_MiniTable* envoy__config__core__v3__ExtraSourceAddress_msg_init_ptr = &envoy__config__core__v3__ExtraSourceAddress_msg_init;
static const upb_MiniTableSubInternal envoy_config_core_v3_BindConfig__submsgs[6] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__SocketAddress_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__BoolValue_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__SocketOption_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__SocketAddress_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__ExtraSourceAddress_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__TypedExtensionConfig_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_core_v3_BindConfig__fields[6] = {
  {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(20, 32), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(24, 40), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(28, 48), 0, 4, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {6, UPB_SIZE(32, 56), 66, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__core__v3__BindConfig_msg_init = {
  &envoy_config_core_v3_BindConfig__submsgs[0],
  &envoy_config_core_v3_BindConfig__fields[0],
  UPB_SIZE(40, 64), 6, kUpb_ExtMode_NonExtendable, 6, UPB_FASTTABLE_MASK(56), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.core.v3.BindConfig",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x002000003f02001a, &upb_prm_1bt_maxmaxb},
    {0x002800003f030022, &upb_prm_1bt_max128b},
    {0x003000003f04002a, &upb_prm_1bt_max64b},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__config__core__v3__BindConfig_msg_init_ptr = &envoy__config__core__v3__BindConfig_msg_init;
static const upb_MiniTableSubInternal envoy_config_core_v3_Address__submsgs[3] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__SocketAddress_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__Pipe_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__EnvoyInternalAddress_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_core_v3_Address__fields[3] = {
  {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(12, 16), -9, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__core__v3__Address_msg_init = {
  &envoy_config_core_v3_Address__submsgs[0],
  &envoy_config_core_v3_Address__fields[0],
  UPB_SIZE(16, 24), 3, kUpb_ExtMode_NonExtendable, 3, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.core.v3.Address",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000080100000a, &upb_pom_1bt_max128b},
    {0x0010000802010012, &upb_pom_1bt_max64b},
    {0x001000080302001a, &upb_pom_1bt_max64b},
  })
};

const upb_MiniTable* envoy__config__core__v3__Address_msg_init_ptr = &envoy__config__core__v3__Address_msg_init;
static const upb_MiniTableSubInternal envoy_config_core_v3_CidrRange__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__UInt32Value_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_core_v3_CidrRange__fields[2] = {
  {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__core__v3__CidrRange_msg_init = {
  &envoy_config_core_v3_CidrRange__submsgs[0],
  &envoy_config_core_v3_CidrRange__fields[0],
  UPB_SIZE(24, 40), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.core.v3.CidrRange",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
  })
};

const upb_MiniTable* envoy__config__core__v3__CidrRange_msg_init_ptr = &envoy__config__core__v3__CidrRange_msg_init;
static const upb_MiniTable *messages_layout[8] = {
  &envoy__config__core__v3__Pipe_msg_init,
  &envoy__config__core__v3__EnvoyInternalAddress_msg_init,
  &envoy__config__core__v3__SocketAddress_msg_init,
  &envoy__config__core__v3__TcpKeepalive_msg_init,
  &envoy__config__core__v3__ExtraSourceAddress_msg_init,
  &envoy__config__core__v3__BindConfig_msg_init,
  &envoy__config__core__v3__Address_msg_init,
  &envoy__config__core__v3__CidrRange_msg_init,
};

const upb_MiniTableFile envoy_config_core_v3_address_proto_upb_file_layout = {
  messages_layout,
  NULL,
  NULL,
  8,
  0,
  0,
};

#include "upb/port/undef.inc"
