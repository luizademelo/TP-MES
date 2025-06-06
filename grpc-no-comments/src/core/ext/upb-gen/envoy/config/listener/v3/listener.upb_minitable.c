
#include <stddef.h>
#include "upb/generated_code_support.h"
#include "envoy/config/listener/v3/listener.upb_minitable.h"
#include "envoy/config/accesslog/v3/accesslog.upb_minitable.h"
#include "envoy/config/core/v3/address.upb_minitable.h"
#include "envoy/config/core/v3/base.upb_minitable.h"
#include "envoy/config/core/v3/extension.upb_minitable.h"
#include "envoy/config/core/v3/socket_option.upb_minitable.h"
#include "envoy/config/listener/v3/api_listener.upb_minitable.h"
#include "envoy/config/listener/v3/listener_components.upb_minitable.h"
#include "envoy/config/listener/v3/udp_listener_config.upb_minitable.h"
#include "google/protobuf/duration.upb_minitable.h"
#include "google/protobuf/wrappers.upb_minitable.h"
#include "xds/annotations/v3/status.upb_minitable.h"
#include "xds/core/v3/collection_entry.upb_minitable.h"
#include "xds/type/matcher/v3/matcher.upb_minitable.h"
#include "envoy/annotations/deprecation.upb_minitable.h"
#include "udpa/annotations/security.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
static const upb_MiniTableSubInternal envoy_config_listener_v3_AdditionalAddress__submsgs[2] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__Address_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__SocketOptionsOverride_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_listener_v3_AdditionalAddress__fields[2] = {
  {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__listener__v3__AdditionalAddress_msg_init = {
  &envoy_config_listener_v3_AdditionalAddress__submsgs[0],
  &envoy_config_listener_v3_AdditionalAddress__fields[0],
  UPB_SIZE(24, 32), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.listener.v3.AdditionalAddress",
#endif
};

const upb_MiniTable* envoy__config__listener__v3__AdditionalAddress_msg_init_ptr = &envoy__config__listener__v3__AdditionalAddress_msg_init;
static const upb_MiniTableSubInternal envoy_config_listener_v3_ListenerCollection__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &xds__core__v3__CollectionEntry_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_listener_v3_ListenerCollection__fields[1] = {
  {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__listener__v3__ListenerCollection_msg_init = {
  &envoy_config_listener_v3_ListenerCollection__submsgs[0],
  &envoy_config_listener_v3_ListenerCollection__fields[0],
  16, 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.listener.v3.ListenerCollection",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f00000a, &upb_prm_1bt_maxmaxb},
  })
};

const upb_MiniTable* envoy__config__listener__v3__ListenerCollection_msg_init_ptr = &envoy__config__listener__v3__ListenerCollection_msg_init;
static const upb_MiniTableSubInternal envoy_config_listener_v3_Listener__submsgs[24] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__Address_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__listener__v3__FilterChain_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__BoolValue_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__UInt32Value_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__Metadata_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__listener__v3__Listener__DeprecatedV1_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__listener__v3__ListenerFilter_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__BoolValue_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__BoolValue_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__UInt32Value_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__SocketOption_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__Duration_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__listener__v3__UdpListenerConfig_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__listener__v3__ApiListener_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__listener__v3__Listener__ConnectionBalanceConfig_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__accesslog__v3__AccessLog_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__UInt32Value_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__listener__v3__FilterChain_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__BoolValue_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__listener__v3__Listener__InternalListenerConfig_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__BoolValue_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &xds__type__matcher__v3__Matcher_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__listener__v3__AdditionalAddress_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__UInt32Value_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_listener_v3_Listener__fields[33] = {
  {1, UPB_SIZE(124, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 64), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(20, 72), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(24, 80), 65, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(28, 88), 66, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {6, UPB_SIZE(32, 96), 67, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {7, UPB_SIZE(36, 104), 68, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {8, UPB_SIZE(40, 16), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {9, UPB_SIZE(44, 112), 0, 6, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {10, UPB_SIZE(48, 120), 69, 7, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {11, UPB_SIZE(52, 128), 70, 8, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {12, UPB_SIZE(56, 136), 71, 9, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {13, UPB_SIZE(60, 144), 0, 10, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {15, UPB_SIZE(64, 152), 72, 11, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {16, UPB_SIZE(68, 20), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {17, 11, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {18, UPB_SIZE(72, 160), 73, 12, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {19, UPB_SIZE(76, 168), 74, 13, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {20, UPB_SIZE(80, 176), 75, 14, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {21, 12, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {22, UPB_SIZE(84, 184), 0, 15, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {24, UPB_SIZE(88, 192), 76, 16, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {25, UPB_SIZE(92, 200), 77, 17, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {26, UPB_SIZE(96, 208), 78, 18, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {27, UPB_SIZE(120, 248), UPB_SIZE(-117, -25), 19, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {28, UPB_SIZE(132, 48), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {29, UPB_SIZE(100, 216), 79, 20, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {30, 13, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {31, 14, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {32, UPB_SIZE(104, 224), 80, 21, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {33, UPB_SIZE(108, 232), 0, 22, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {34, UPB_SIZE(112, 240), 81, 23, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {35, 15, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__listener__v3__Listener_msg_init = {
  &envoy_config_listener_v3_Listener__submsgs[0],
  &envoy_config_listener_v3_Listener__fields[0],
  UPB_SIZE(144, 256), 33, kUpb_ExtMode_NonExtendable, 13, UPB_FASTTABLE_MASK(248), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.listener.v3.Listener",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x002000003f00000a, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x004800003f01001a, &upb_prm_1bt_maxmaxb},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f000040, &upb_psv4_1bt},
    {0x007000003f06004a, &upb_prm_1bt_maxmaxb},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x009000003f0a006a, &upb_prm_1bt_maxmaxb},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001400003f000180, &upb_psv4_2bt},
    {0x000b00003f000188, &upb_psb1_2bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000f00003f000298, &upb_psb1_2bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000c00003f0001a8, &upb_psb1_2bt},
    {0x00b800003f0f01b2, &upb_prm_2bt_maxmaxb},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x00f800181b1301da, &upb_pom_2bt_max64b},
    {0x003000003f0001e2, &upb_pss_2bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000d00003f0001f0, &upb_psb1_2bt},
    {0x000e00003f0001f8, &upb_psb1_2bt},
  })
};

const upb_MiniTable* envoy__config__listener__v3__Listener_msg_init_ptr = &envoy__config__listener__v3__Listener_msg_init;
static const upb_MiniTableSubInternal envoy_config_listener_v3_Listener_DeprecatedV1__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__BoolValue_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_listener_v3_Listener_DeprecatedV1__fields[1] = {
  {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__listener__v3__Listener__DeprecatedV1_msg_init = {
  &envoy_config_listener_v3_Listener_DeprecatedV1__submsgs[0],
  &envoy_config_listener_v3_Listener_DeprecatedV1__fields[0],
  UPB_SIZE(16, 24), 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.listener.v3.Listener.DeprecatedV1",
#endif
};

const upb_MiniTable* envoy__config__listener__v3__Listener__DeprecatedV1_msg_init_ptr = &envoy__config__listener__v3__Listener__DeprecatedV1_msg_init;
static const upb_MiniTableSubInternal envoy_config_listener_v3_Listener_ConnectionBalanceConfig__submsgs[2] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__listener__v3__Listener__ConnectionBalanceConfig__ExactBalance_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__TypedExtensionConfig_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_listener_v3_Listener_ConnectionBalanceConfig__fields[2] = {
  {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__listener__v3__Listener__ConnectionBalanceConfig_msg_init = {
  &envoy_config_listener_v3_Listener_ConnectionBalanceConfig__submsgs[0],
  &envoy_config_listener_v3_Listener_ConnectionBalanceConfig__fields[0],
  UPB_SIZE(16, 24), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.listener.v3.Listener.ConnectionBalanceConfig",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000080100000a, &upb_pom_1bt_max64b},
    {0x0010000802010012, &upb_pom_1bt_maxmaxb},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__config__listener__v3__Listener__ConnectionBalanceConfig_msg_init_ptr = &envoy__config__listener__v3__Listener__ConnectionBalanceConfig_msg_init;
const upb_MiniTable envoy__config__listener__v3__Listener__ConnectionBalanceConfig__ExactBalance_msg_init = {
  NULL,
  NULL,
  8, 0, kUpb_ExtMode_NonExtendable, 0, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.listener.v3.Listener.ConnectionBalanceConfig.ExactBalance",
#endif
};

const upb_MiniTable* envoy__config__listener__v3__Listener__ConnectionBalanceConfig__ExactBalance_msg_init_ptr = &envoy__config__listener__v3__Listener__ConnectionBalanceConfig__ExactBalance_msg_init;
const upb_MiniTable envoy__config__listener__v3__Listener__InternalListenerConfig_msg_init = {
  NULL,
  NULL,
  8, 0, kUpb_ExtMode_NonExtendable, 0, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.listener.v3.Listener.InternalListenerConfig",
#endif
};

const upb_MiniTable* envoy__config__listener__v3__Listener__InternalListenerConfig_msg_init_ptr = &envoy__config__listener__v3__Listener__InternalListenerConfig_msg_init;
const upb_MiniTable envoy__config__listener__v3__ListenerManager_msg_init = {
  NULL,
  NULL,
  8, 0, kUpb_ExtMode_NonExtendable, 0, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.listener.v3.ListenerManager",
#endif
};

const upb_MiniTable* envoy__config__listener__v3__ListenerManager_msg_init_ptr = &envoy__config__listener__v3__ListenerManager_msg_init;
const upb_MiniTable envoy__config__listener__v3__ValidationListenerManager_msg_init = {
  NULL,
  NULL,
  8, 0, kUpb_ExtMode_NonExtendable, 0, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.listener.v3.ValidationListenerManager",
#endif
};

const upb_MiniTable* envoy__config__listener__v3__ValidationListenerManager_msg_init_ptr = &envoy__config__listener__v3__ValidationListenerManager_msg_init;
const upb_MiniTable envoy__config__listener__v3__ApiListenerManager_msg_init = {
  NULL,
  NULL,
  8, 0, kUpb_ExtMode_NonExtendable, 0, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.listener.v3.ApiListenerManager",
#endif
};

const upb_MiniTable* envoy__config__listener__v3__ApiListenerManager_msg_init_ptr = &envoy__config__listener__v3__ApiListenerManager_msg_init;
static const upb_MiniTable *messages_layout[10] = {
  &envoy__config__listener__v3__AdditionalAddress_msg_init,
  &envoy__config__listener__v3__ListenerCollection_msg_init,
  &envoy__config__listener__v3__Listener_msg_init,
  &envoy__config__listener__v3__Listener__DeprecatedV1_msg_init,
  &envoy__config__listener__v3__Listener__ConnectionBalanceConfig_msg_init,
  &envoy__config__listener__v3__Listener__ConnectionBalanceConfig__ExactBalance_msg_init,
  &envoy__config__listener__v3__Listener__InternalListenerConfig_msg_init,
  &envoy__config__listener__v3__ListenerManager_msg_init,
  &envoy__config__listener__v3__ValidationListenerManager_msg_init,
  &envoy__config__listener__v3__ApiListenerManager_msg_init,
};

const upb_MiniTableFile envoy_config_listener_v3_listener_proto_upb_file_layout = {
  messages_layout,
  NULL,
  NULL,
  10,
  0,
  0,
};

#include "upb/port/undef.inc"
