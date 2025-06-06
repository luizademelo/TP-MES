
#include <stddef.h>
#include "upb/generated_code_support.h"
#include "envoy/config/route/v3/scoped_route.upb_minitable.h"
#include "envoy/config/route/v3/route.upb_minitable.h"
#include "udpa/annotations/migrate.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
static const upb_MiniTableSubInternal envoy_config_route_v3_ScopedRouteConfiguration__submsgs[2] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__route__v3__ScopedRouteConfiguration__Key_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__route__v3__RouteConfiguration_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_route_v3_ScopedRouteConfiguration__fields[5] = {
  {1, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(28, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(12, 48), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(16, 56), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__route__v3__ScopedRouteConfiguration_msg_init = {
  &envoy_config_route_v3_ScopedRouteConfiguration__submsgs[0],
  &envoy_config_route_v3_ScopedRouteConfiguration__fields[0],
  UPB_SIZE(40, 64), 5, kUpb_ExtMode_NonExtendable, 5, UPB_FASTTABLE_MASK(56), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.route.v3.ScopedRouteConfiguration",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
    {0x002000003f000012, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000900003f000020, &upb_psb1_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__config__route__v3__ScopedRouteConfiguration_msg_init_ptr = &envoy__config__route__v3__ScopedRouteConfiguration_msg_init;
static const upb_MiniTableSubInternal envoy_config_route_v3_ScopedRouteConfiguration_Key__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__route__v3__ScopedRouteConfiguration__Key__Fragment_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_route_v3_ScopedRouteConfiguration_Key__fields[1] = {
  {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__route__v3__ScopedRouteConfiguration__Key_msg_init = {
  &envoy_config_route_v3_ScopedRouteConfiguration_Key__submsgs[0],
  &envoy_config_route_v3_ScopedRouteConfiguration_Key__fields[0],
  16, 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.route.v3.ScopedRouteConfiguration.Key",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f00000a, &upb_prm_1bt_max64b},
  })
};

const upb_MiniTable* envoy__config__route__v3__ScopedRouteConfiguration__Key_msg_init_ptr = &envoy__config__route__v3__ScopedRouteConfiguration__Key_msg_init;
static const upb_MiniTableField envoy_config_route_v3_ScopedRouteConfiguration_Key_Fragment__fields[1] = {
  {1, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__route__v3__ScopedRouteConfiguration__Key__Fragment_msg_init = {
  NULL,
  &envoy_config_route_v3_ScopedRouteConfiguration_Key_Fragment__fields[0],
  UPB_SIZE(24, 32), 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.route.v3.ScopedRouteConfiguration.Key.Fragment",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000080100000a, &upb_pos_1bt},
  })
};

const upb_MiniTable* envoy__config__route__v3__ScopedRouteConfiguration__Key__Fragment_msg_init_ptr = &envoy__config__route__v3__ScopedRouteConfiguration__Key__Fragment_msg_init;
static const upb_MiniTable *messages_layout[3] = {
  &envoy__config__route__v3__ScopedRouteConfiguration_msg_init,
  &envoy__config__route__v3__ScopedRouteConfiguration__Key_msg_init,
  &envoy__config__route__v3__ScopedRouteConfiguration__Key__Fragment_msg_init,
};

const upb_MiniTableFile envoy_config_route_v3_scoped_route_proto_upb_file_layout = {
  messages_layout,
  NULL,
  NULL,
  3,
  0,
  0,
};

#include "upb/port/undef.inc"
