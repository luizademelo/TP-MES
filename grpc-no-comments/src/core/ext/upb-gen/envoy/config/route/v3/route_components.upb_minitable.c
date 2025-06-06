
#include <stddef.h>
#include "upb/generated_code_support.h"
#include "envoy/config/route/v3/route_components.upb_minitable.h"
#include "envoy/config/core/v3/base.upb_minitable.h"
#include "envoy/config/core/v3/extension.upb_minitable.h"
#include "envoy/config/core/v3/proxy_protocol.upb_minitable.h"
#include "envoy/type/matcher/v3/metadata.upb_minitable.h"
#include "envoy/type/matcher/v3/regex.upb_minitable.h"
#include "envoy/type/matcher/v3/string.upb_minitable.h"
#include "envoy/type/metadata/v3/metadata.upb_minitable.h"
#include "envoy/type/tracing/v3/custom_tag.upb_minitable.h"
#include "envoy/type/v3/percent.upb_minitable.h"
#include "envoy/type/v3/range.upb_minitable.h"
#include "google/protobuf/any.upb_minitable.h"
#include "google/protobuf/duration.upb_minitable.h"
#include "google/protobuf/wrappers.upb_minitable.h"
#include "xds/type/matcher/v3/matcher.upb_minitable.h"
#include "envoy/annotations/deprecation.upb_minitable.h"
#include "udpa/annotations/migrate.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
static const upb_MiniTableSubInternal envoy_config_route_v3_VirtualHost__submsgs[14] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__route__v3__Route_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__route__v3__VirtualCluster_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__route__v3__RateLimit_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__HeaderValueOption_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__route__v3__CorsPolicy_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__HeaderValueOption_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__route__v3__VirtualHost__TypedPerFilterConfigEntry_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__route__v3__RetryPolicy_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__route__v3__HedgePolicy_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__UInt32Value_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__Any_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &xds__type__matcher__v3__Matcher_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__route__v3__RouteAction__RequestMirrorPolicy_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__Metadata_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_route_v3_VirtualHost__fields[22] = {
  {1, UPB_SIZE(84, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(16, 40), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(20, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(24, 48), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {6, UPB_SIZE(28, 56), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {7, UPB_SIZE(32, 64), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {8, UPB_SIZE(36, 72), 64, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {10, UPB_SIZE(40, 80), 0, 5, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {11, UPB_SIZE(44, 88), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {13, UPB_SIZE(48, 96), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {14, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {15, UPB_SIZE(52, 104), 0, 6, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {16, UPB_SIZE(56, 112), 65, 7, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {17, UPB_SIZE(60, 120), 66, 8, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {18, UPB_SIZE(64, 128), 67, 9, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {19, 10, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {20, UPB_SIZE(68, 136), 68, 10, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {21, UPB_SIZE(72, 144), 69, 11, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {22, UPB_SIZE(76, 152), 0, 12, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {23, 11, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {24, UPB_SIZE(80, 160), 70, 13, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__route__v3__VirtualHost_msg_init = {
  &envoy_config_route_v3_VirtualHost__submsgs[0],
  &envoy_config_route_v3_VirtualHost__fields[0],
  UPB_SIZE(96, 168), 22, kUpb_ExtMode_NonExtendable, 8, UPB_FASTTABLE_MASK(248), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.route.v3.VirtualHost",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
    {0x002000003f000012, &upb_prs_1bt},
    {0x002800003f00001a, &upb_prm_1bt_max192b},
    {0x000c00003f000020, &upb_psv4_1bt},
    {0x003000003f01002a, &upb_prm_1bt_max64b},
    {0x003800003f020032, &upb_prm_1bt_max128b},
    {0x004000003f03003a, &upb_prm_1bt_maxmaxb},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x005000003f050052, &upb_prm_1bt_maxmaxb},
    {0x005800003f00005a, &upb_prs_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x006000003f00006a, &upb_prs_1bt},
    {0x000900003f000070, &upb_psb1_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000a00003f000198, &upb_psb1_2bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x009800003f0c01b2, &upb_prm_2bt_max128b},
    {0x000b00003f0001b8, &upb_psb1_2bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__config__route__v3__VirtualHost_msg_init_ptr = &envoy__config__route__v3__VirtualHost_msg_init;
static const upb_MiniTableSubInternal envoy_config_route_v3_VirtualHost_TypedPerFilterConfigEntry__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__Any_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_route_v3_VirtualHost_TypedPerFilterConfigEntry__fields[2] = {
  {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, 32, 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__route__v3__VirtualHost__TypedPerFilterConfigEntry_msg_init = {
  &envoy_config_route_v3_VirtualHost_TypedPerFilterConfigEntry__submsgs[0],
  &envoy_config_route_v3_VirtualHost_TypedPerFilterConfigEntry__fields[0],
  48, 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.route.v3.VirtualHost.TypedPerFilterConfigEntry",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
  })
};

const upb_MiniTable* envoy__config__route__v3__VirtualHost__TypedPerFilterConfigEntry_msg_init_ptr = &envoy__config__route__v3__VirtualHost__TypedPerFilterConfigEntry_msg_init;
static const upb_MiniTableSubInternal envoy_config_route_v3_FilterAction__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__Any_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_route_v3_FilterAction__fields[1] = {
  {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__route__v3__FilterAction_msg_init = {
  &envoy_config_route_v3_FilterAction__submsgs[0],
  &envoy_config_route_v3_FilterAction__fields[0],
  UPB_SIZE(16, 24), 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.route.v3.FilterAction",
#endif
};

const upb_MiniTable* envoy__config__route__v3__FilterAction_msg_init_ptr = &envoy__config__route__v3__FilterAction_msg_init;
static const upb_MiniTableSubInternal envoy_config_route_v3_RouteList__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__route__v3__Route_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_route_v3_RouteList__fields[1] = {
  {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__route__v3__RouteList_msg_init = {
  &envoy_config_route_v3_RouteList__submsgs[0],
  &envoy_config_route_v3_RouteList__fields[0],
  16, 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.route.v3.RouteList",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f00000a, &upb_prm_1bt_max192b},
  })
};

const upb_MiniTable* envoy__config__route__v3__RouteList_msg_init_ptr = &envoy__config__route__v3__RouteList_msg_init;
static const upb_MiniTableSubInternal envoy_config_route_v3_Route__submsgs[13] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__route__v3__RouteMatch_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__route__v3__RouteAction_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__route__v3__RedirectAction_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__Metadata_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__route__v3__Decorator_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__route__v3__DirectResponseAction_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__HeaderValueOption_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__HeaderValueOption_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__route__v3__Route__TypedPerFilterConfigEntry_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__route__v3__Tracing_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__UInt32Value_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__route__v3__FilterAction_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__route__v3__NonForwardingAction_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_route_v3_Route__fields[17] = {
  {1, UPB_SIZE(12, 48), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(56, 128), UPB_SIZE(-53, -13), 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(56, 128), UPB_SIZE(-53, -13), 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(16, 56), 65, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(20, 64), 66, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {7, UPB_SIZE(56, 128), UPB_SIZE(-53, -13), 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {9, UPB_SIZE(24, 72), 0, 6, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {10, UPB_SIZE(28, 80), 0, 7, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {11, UPB_SIZE(32, 88), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {12, UPB_SIZE(36, 96), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {13, UPB_SIZE(40, 104), 0, 8, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {14, UPB_SIZE(60, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {15, UPB_SIZE(44, 112), 67, 9, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {16, UPB_SIZE(48, 120), 68, 10, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {17, UPB_SIZE(56, 128), UPB_SIZE(-53, -13), 11, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {18, UPB_SIZE(56, 128), UPB_SIZE(-53, -13), 12, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {19, UPB_SIZE(68, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__route__v3__Route_msg_init = {
  &envoy_config_route_v3_Route__submsgs[0],
  &envoy_config_route_v3_Route__fields[0],
  UPB_SIZE(80, 136), 17, kUpb_ExtMode_NonExtendable, 5, UPB_FASTTABLE_MASK(248), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.route.v3.Route",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0080000c02010012, &upb_pom_1bt_max256b},
    {0x0080000c0302001a, &upb_pom_1bt_max128b},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0080000c0705003a, &upb_pom_1bt_max64b},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x004800003f06004a, &upb_prm_1bt_maxmaxb},
    {0x005000003f070052, &upb_prm_1bt_maxmaxb},
    {0x005800003f00005a, &upb_prs_1bt},
    {0x006000003f000062, &upb_prs_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f000072, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0080000c110b018a, &upb_pom_2bt_max64b},
    {0x0080000c120c0192, &upb_pom_2bt_max64b},
    {0x002000003f00019a, &upb_pss_2bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__config__route__v3__Route_msg_init_ptr = &envoy__config__route__v3__Route_msg_init;
static const upb_MiniTableSubInternal envoy_config_route_v3_Route_TypedPerFilterConfigEntry__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__Any_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_route_v3_Route_TypedPerFilterConfigEntry__fields[2] = {
  {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, 32, 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__route__v3__Route__TypedPerFilterConfigEntry_msg_init = {
  &envoy_config_route_v3_Route_TypedPerFilterConfigEntry__submsgs[0],
  &envoy_config_route_v3_Route_TypedPerFilterConfigEntry__fields[0],
  48, 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.route.v3.Route.TypedPerFilterConfigEntry",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
  })
};

const upb_MiniTable* envoy__config__route__v3__Route__TypedPerFilterConfigEntry_msg_init_ptr = &envoy__config__route__v3__Route__TypedPerFilterConfigEntry_msg_init;
static const upb_MiniTableSubInternal envoy_config_route_v3_WeightedCluster__submsgs[2] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__route__v3__WeightedCluster__ClusterWeight_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__UInt32Value_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_route_v3_WeightedCluster__fields[4] = {
  {1, UPB_SIZE(12, 48), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(24, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(16, 56), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, 32, UPB_SIZE(-21, -13), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__route__v3__WeightedCluster_msg_init = {
  &envoy_config_route_v3_WeightedCluster__submsgs[0],
  &envoy_config_route_v3_WeightedCluster__fields[0],
  UPB_SIZE(40, 64), 4, kUpb_ExtMode_NonExtendable, 4, UPB_FASTTABLE_MASK(56), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.route.v3.WeightedCluster",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x003000003f00000a, &upb_prm_1bt_max128b},
    {0x001000003f000012, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0020000c04000022, &upb_pos_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__config__route__v3__WeightedCluster_msg_init_ptr = &envoy__config__route__v3__WeightedCluster_msg_init;
static const upb_MiniTableSubInternal envoy_config_route_v3_WeightedCluster_ClusterWeight__submsgs[5] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__UInt32Value_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__Metadata_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__HeaderValueOption_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__HeaderValueOption_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__route__v3__WeightedCluster__ClusterWeight__TypedPerFilterConfigEntry_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_route_v3_WeightedCluster_ClusterWeight__fields[10] = {
  {1, UPB_SIZE(44, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 64), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(16, 72), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(20, 80), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(24, 88), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {6, UPB_SIZE(28, 96), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {9, UPB_SIZE(32, 104), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {10, UPB_SIZE(36, 112), 0, 4, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {11, UPB_SIZE(60, 48), UPB_SIZE(-41, -13), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {12, UPB_SIZE(52, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__route__v3__WeightedCluster__ClusterWeight_msg_init = {
  &envoy_config_route_v3_WeightedCluster_ClusterWeight__submsgs[0],
  &envoy_config_route_v3_WeightedCluster_ClusterWeight__fields[0],
  UPB_SIZE(72, 120), 10, kUpb_ExtMode_NonExtendable, 6, UPB_FASTTABLE_MASK(120), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.route.v3.WeightedCluster.ClusterWeight",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x005000003f020022, &upb_prm_1bt_maxmaxb},
    {0x005800003f03002a, &upb_prm_1bt_maxmaxb},
    {0x006000003f000032, &upb_prs_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x006800003f00004a, &upb_prs_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0030000c0b00005a, &upb_pos_1bt},
    {0x002000003f000062, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__config__route__v3__WeightedCluster__ClusterWeight_msg_init_ptr = &envoy__config__route__v3__WeightedCluster__ClusterWeight_msg_init;
static const upb_MiniTableSubInternal envoy_config_route_v3_WeightedCluster_ClusterWeight_TypedPerFilterConfigEntry__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__Any_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_route_v3_WeightedCluster_ClusterWeight_TypedPerFilterConfigEntry__fields[2] = {
  {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, 32, 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__route__v3__WeightedCluster__ClusterWeight__TypedPerFilterConfigEntry_msg_init = {
  &envoy_config_route_v3_WeightedCluster_ClusterWeight_TypedPerFilterConfigEntry__submsgs[0],
  &envoy_config_route_v3_WeightedCluster_ClusterWeight_TypedPerFilterConfigEntry__fields[0],
  48, 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.route.v3.WeightedCluster.ClusterWeight.TypedPerFilterConfigEntry",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
  })
};

const upb_MiniTable* envoy__config__route__v3__WeightedCluster__ClusterWeight__TypedPerFilterConfigEntry_msg_init_ptr = &envoy__config__route__v3__WeightedCluster__ClusterWeight__TypedPerFilterConfigEntry_msg_init;
static const upb_MiniTableSubInternal envoy_config_route_v3_ClusterSpecifierPlugin__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__TypedExtensionConfig_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_route_v3_ClusterSpecifierPlugin__fields[2] = {
  {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__route__v3__ClusterSpecifierPlugin_msg_init = {
  &envoy_config_route_v3_ClusterSpecifierPlugin__submsgs[0],
  &envoy_config_route_v3_ClusterSpecifierPlugin__fields[0],
  UPB_SIZE(16, 24), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.route.v3.ClusterSpecifierPlugin",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000900003f000010, &upb_psb1_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__config__route__v3__ClusterSpecifierPlugin_msg_init_ptr = &envoy__config__route__v3__ClusterSpecifierPlugin_msg_init;
static const upb_MiniTableSubInternal envoy_config_route_v3_RouteMatch__submsgs[10] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__BoolValue_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__route__v3__HeaderMatcher_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__route__v3__QueryParameterMatcher_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__route__v3__RouteMatch__GrpcRouteMatchOptions_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__RuntimeFractionalPercent_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__type__matcher__v3__RegexMatcher_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__route__v3__RouteMatch__TlsContextMatchOptions_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__route__v3__RouteMatch__ConnectMatcher_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__type__matcher__v3__MetadataMatcher_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__TypedExtensionConfig_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_route_v3_RouteMatch__fields[13] = {
  {1, UPB_SIZE(44, 16), UPB_SIZE(-41, -13), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(44, 16), UPB_SIZE(-41, -13), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {6, UPB_SIZE(16, 40), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {7, UPB_SIZE(20, 48), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {8, UPB_SIZE(24, 56), 65, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {9, UPB_SIZE(28, 64), 66, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {10, UPB_SIZE(44, 16), UPB_SIZE(-41, -13), 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {11, UPB_SIZE(32, 72), 67, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {12, UPB_SIZE(44, 16), UPB_SIZE(-41, -13), 7, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {13, UPB_SIZE(36, 80), 0, 8, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {14, UPB_SIZE(44, 16), UPB_SIZE(-41, -13), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {15, UPB_SIZE(44, 16), UPB_SIZE(-41, -13), 9, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__route__v3__RouteMatch_msg_init = {
  &envoy_config_route_v3_RouteMatch__submsgs[0],
  &envoy_config_route_v3_RouteMatch__fields[0],
  UPB_SIZE(56, 88), 13, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(120), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.route.v3.RouteMatch",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0010000c0100000a, &upb_pos_1bt},
    {0x0010000c02000012, &upb_pos_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x002800003f010032, &upb_prm_1bt_max64b},
    {0x003000003f02003a, &upb_prm_1bt_max64b},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0010000c0a050052, &upb_pom_1bt_maxmaxb},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0010000c0c070062, &upb_pom_1bt_max64b},
    {0x005000003f08006a, &upb_prm_1bt_maxmaxb},
    {0x0010000c0e000072, &upb_pos_1bt},
    {0x0010000c0f09007a, &upb_pom_1bt_maxmaxb},
  })
};

const upb_MiniTable* envoy__config__route__v3__RouteMatch_msg_init_ptr = &envoy__config__route__v3__RouteMatch_msg_init;
const upb_MiniTable envoy__config__route__v3__RouteMatch__GrpcRouteMatchOptions_msg_init = {
  NULL,
  NULL,
  8, 0, kUpb_ExtMode_NonExtendable, 0, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.route.v3.RouteMatch.GrpcRouteMatchOptions",
#endif
};

const upb_MiniTable* envoy__config__route__v3__RouteMatch__GrpcRouteMatchOptions_msg_init_ptr = &envoy__config__route__v3__RouteMatch__GrpcRouteMatchOptions_msg_init;
static const upb_MiniTableSubInternal envoy_config_route_v3_RouteMatch_TlsContextMatchOptions__submsgs[2] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__BoolValue_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__BoolValue_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_route_v3_RouteMatch_TlsContextMatchOptions__fields[2] = {
  {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__route__v3__RouteMatch__TlsContextMatchOptions_msg_init = {
  &envoy_config_route_v3_RouteMatch_TlsContextMatchOptions__submsgs[0],
  &envoy_config_route_v3_RouteMatch_TlsContextMatchOptions__fields[0],
  UPB_SIZE(24, 32), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.route.v3.RouteMatch.TlsContextMatchOptions",
#endif
};

const upb_MiniTable* envoy__config__route__v3__RouteMatch__TlsContextMatchOptions_msg_init_ptr = &envoy__config__route__v3__RouteMatch__TlsContextMatchOptions_msg_init;
const upb_MiniTable envoy__config__route__v3__RouteMatch__ConnectMatcher_msg_init = {
  NULL,
  NULL,
  8, 0, kUpb_ExtMode_NonExtendable, 0, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.route.v3.RouteMatch.ConnectMatcher",
#endif
};

const upb_MiniTable* envoy__config__route__v3__RouteMatch__ConnectMatcher_msg_init_ptr = &envoy__config__route__v3__RouteMatch__ConnectMatcher_msg_init;
static const upb_MiniTableSubInternal envoy_config_route_v3_CorsPolicy__submsgs[6] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__BoolValue_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__RuntimeFractionalPercent_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__RuntimeFractionalPercent_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__type__matcher__v3__StringMatcher_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__BoolValue_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__BoolValue_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_route_v3_CorsPolicy__fields[10] = {
  {2, UPB_SIZE(40, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(48, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(56, 48), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {5, 64, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {6, UPB_SIZE(12, 80), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {9, UPB_SIZE(36, 120), UPB_SIZE(-33, -13), 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {10, UPB_SIZE(16, 88), 65, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {11, UPB_SIZE(20, 96), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {12, UPB_SIZE(24, 104), 66, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {13, UPB_SIZE(28, 112), 67, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__route__v3__CorsPolicy_msg_init = {
  &envoy_config_route_v3_CorsPolicy__submsgs[0],
  &envoy_config_route_v3_CorsPolicy__fields[0],
  UPB_SIZE(72, 128), 10, kUpb_ExtMode_NonExtendable, 0, UPB_FASTTABLE_MASK(120), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.route.v3.CorsPolicy",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f000012, &upb_pss_1bt},
    {0x002000003f00001a, &upb_pss_1bt},
    {0x003000003f000022, &upb_pss_1bt},
    {0x004000003f00002a, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0078000c0901004a, &upb_pom_1bt_maxmaxb},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x006000003f03005a, &upb_prm_1bt_maxmaxb},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__config__route__v3__CorsPolicy_msg_init_ptr = &envoy__config__route__v3__CorsPolicy_msg_init;
static const upb_MiniTableSubInternal envoy_config_route_v3_RouteAction__submsgs[24] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__route__v3__WeightedCluster_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__Metadata_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__BoolValue_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__Duration_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__route__v3__RetryPolicy_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__route__v3__RateLimit_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__BoolValue_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__route__v3__RouteAction__HashPolicy_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__route__v3__CorsPolicy_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__Duration_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__Duration_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__route__v3__RouteAction__UpgradeConfig_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__route__v3__HedgePolicy_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__Duration_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__route__v3__RouteAction__RequestMirrorPolicy_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__UInt32Value_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__type__matcher__v3__RegexMatchAndSubstitute_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__Any_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__route__v3__InternalRedirectPolicy_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__type__matcher__v3__RegexMatchAndSubstitute_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__route__v3__RouteAction__MaxStreamDuration_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__route__v3__ClusterSpecifierPlugin_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__TypedExtensionConfig_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__TypedExtensionConfig_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_route_v3_RouteAction__fields[34] = {
  {1, UPB_SIZE(120, 48), UPB_SIZE(-105, -25), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(120, 48), UPB_SIZE(-105, -25), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(120, 48), UPB_SIZE(-105, -25), 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(12, 80), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(112, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {6, UPB_SIZE(128, 64), UPB_SIZE(-109, -29), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {7, UPB_SIZE(128, 64), UPB_SIZE(-109, -29), 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {8, UPB_SIZE(16, 88), 65, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {9, UPB_SIZE(20, 96), 66, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {11, UPB_SIZE(24, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {13, UPB_SIZE(28, 104), 0, 5, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {14, UPB_SIZE(32, 112), 67, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {15, UPB_SIZE(36, 120), 0, 7, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {17, UPB_SIZE(40, 128), 68, 8, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {20, UPB_SIZE(44, 16), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {23, UPB_SIZE(48, 136), 69, 9, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {24, UPB_SIZE(52, 144), 70, 10, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {25, UPB_SIZE(56, 152), 0, 11, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {26, UPB_SIZE(60, 20), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {27, UPB_SIZE(64, 160), 71, 12, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {28, UPB_SIZE(68, 168), 72, 13, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {29, UPB_SIZE(128, 64), UPB_SIZE(-109, -29), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {30, UPB_SIZE(72, 176), 0, 14, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {31, UPB_SIZE(76, 184), 73, 15, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {32, UPB_SIZE(80, 192), 74, 16, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {33, UPB_SIZE(84, 200), 75, 17, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {34, UPB_SIZE(88, 208), 76, 18, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {35, UPB_SIZE(128, 64), UPB_SIZE(-109, -29), 19, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {36, UPB_SIZE(92, 216), 77, 20, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {37, UPB_SIZE(120, 48), UPB_SIZE(-105, -25), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {38, 10, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {39, UPB_SIZE(120, 48), UPB_SIZE(-105, -25), 21, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {40, UPB_SIZE(96, 224), 78, 22, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {41, UPB_SIZE(100, 232), 79, 23, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__route__v3__RouteAction_msg_init = {
  &envoy_config_route_v3_RouteAction__submsgs[0],
  &envoy_config_route_v3_RouteAction__fields[0],
  UPB_SIZE(136, 240), 34, kUpb_ExtMode_NonExtendable, 9, UPB_FASTTABLE_MASK(248), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.route.v3.RouteAction",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x003000180100000a, &upb_pos_1bt},
    {0x0030001802000012, &upb_pos_1bt},
    {0x003000180300001a, &upb_pom_1bt_max128b},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x002000003f00002a, &upb_pss_1bt},
    {0x0040001c06000032, &upb_pos_1bt},
    {0x0040001c0702003a, &upb_pom_1bt_maxmaxb},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000c00003f000058, &upb_psv4_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x006800003f05006a, &upb_prm_1bt_max128b},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x007800003f07007a, &upb_prm_1bt_max64b},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0040001c2313029a, &upb_pom_2bt_maxmaxb},
    {0x001000003f0001a0, &upb_psv4_2bt},
    {0x00300018250002aa, &upb_pos_2bt},
    {0x000a00003f0002b0, &upb_psb1_2bt},
    {0x00300018271502ba, &upb_pom_2bt_max64b},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x009800003f0b01ca, &upb_prm_2bt_max64b},
    {0x001400003f0001d0, &upb_psv4_2bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0040001c1d0001ea, &upb_pos_2bt},
    {0x00b000003f0e01f2, &upb_prm_2bt_max128b},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__config__route__v3__RouteAction_msg_init_ptr = &envoy__config__route__v3__RouteAction_msg_init;
static const upb_MiniTableSubInternal envoy_config_route_v3_RouteAction_RequestMirrorPolicy__submsgs[2] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__RuntimeFractionalPercent_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__BoolValue_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_route_v3_RouteAction_RequestMirrorPolicy__fields[5] = {
  {1, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(12, 48), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(16, 56), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(28, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {6, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__route__v3__RouteAction__RequestMirrorPolicy_msg_init = {
  &envoy_config_route_v3_RouteAction_RequestMirrorPolicy__submsgs[0],
  &envoy_config_route_v3_RouteAction_RequestMirrorPolicy__fields[0],
  UPB_SIZE(40, 64), 5, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(56), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.route.v3.RouteAction.RequestMirrorPolicy",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x002000003f00002a, &upb_pss_1bt},
    {0x000900003f000030, &upb_psb1_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__config__route__v3__RouteAction__RequestMirrorPolicy_msg_init_ptr = &envoy__config__route__v3__RouteAction__RequestMirrorPolicy_msg_init;
static const upb_MiniTableSubInternal envoy_config_route_v3_RouteAction_HashPolicy__submsgs[5] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__route__v3__RouteAction__HashPolicy__Header_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__route__v3__RouteAction__HashPolicy__Cookie_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__route__v3__RouteAction__HashPolicy__ConnectionProperties_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__route__v3__RouteAction__HashPolicy__QueryParameter_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__route__v3__RouteAction__HashPolicy__FilterState_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_route_v3_RouteAction_HashPolicy__fields[6] = {
  {1, 16, -13, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, 16, -13, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, 16, -13, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {5, 16, -13, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {6, 16, -13, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__route__v3__RouteAction__HashPolicy_msg_init = {
  &envoy_config_route_v3_RouteAction_HashPolicy__submsgs[0],
  &envoy_config_route_v3_RouteAction_HashPolicy__fields[0],
  24, 6, kUpb_ExtMode_NonExtendable, 6, UPB_FASTTABLE_MASK(56), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.route.v3.RouteAction.HashPolicy",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0010000c0100000a, &upb_pom_1bt_max64b},
    {0x0010000c02010012, &upb_pom_1bt_max128b},
    {0x0010000c0302001a, &upb_pom_1bt_max64b},
    {0x000800003f000020, &upb_psb1_1bt},
    {0x0010000c0503002a, &upb_pom_1bt_max64b},
    {0x0010000c06040032, &upb_pom_1bt_max64b},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__config__route__v3__RouteAction__HashPolicy_msg_init_ptr = &envoy__config__route__v3__RouteAction__HashPolicy_msg_init;
static const upb_MiniTableSubInternal envoy_config_route_v3_RouteAction_HashPolicy_Header__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &envoy__type__matcher__v3__RegexMatchAndSubstitute_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_route_v3_RouteAction_HashPolicy_Header__fields[2] = {
  {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__route__v3__RouteAction__HashPolicy__Header_msg_init = {
  &envoy_config_route_v3_RouteAction_HashPolicy_Header__submsgs[0],
  &envoy_config_route_v3_RouteAction_HashPolicy_Header__fields[0],
  UPB_SIZE(24, 40), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.route.v3.RouteAction.HashPolicy.Header",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
  })
};

const upb_MiniTable* envoy__config__route__v3__RouteAction__HashPolicy__Header_msg_init_ptr = &envoy__config__route__v3__RouteAction__HashPolicy__Header_msg_init;
static const upb_MiniTableField envoy_config_route_v3_RouteAction_HashPolicy_CookieAttribute__fields[2] = {
  {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__route__v3__RouteAction__HashPolicy__CookieAttribute_msg_init = {
  NULL,
  &envoy_config_route_v3_RouteAction_HashPolicy_CookieAttribute__fields[0],
  UPB_SIZE(24, 40), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.route.v3.RouteAction.HashPolicy.CookieAttribute",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f00000a, &upb_pss_1bt},
    {0x001800003f000012, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__config__route__v3__RouteAction__HashPolicy__CookieAttribute_msg_init_ptr = &envoy__config__route__v3__RouteAction__HashPolicy__CookieAttribute_msg_init;
static const upb_MiniTableSubInternal envoy_config_route_v3_RouteAction_HashPolicy_Cookie__submsgs[2] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__Duration_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__route__v3__RouteAction__HashPolicy__CookieAttribute_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_route_v3_RouteAction_HashPolicy_Cookie__fields[4] = {
  {1, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 48), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(28, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(16, 56), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__route__v3__RouteAction__HashPolicy__Cookie_msg_init = {
  &envoy_config_route_v3_RouteAction_HashPolicy_Cookie__submsgs[0],
  &envoy_config_route_v3_RouteAction_HashPolicy_Cookie__fields[0],
  UPB_SIZE(40, 64), 4, kUpb_ExtMode_NonExtendable, 4, UPB_FASTTABLE_MASK(56), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.route.v3.RouteAction.HashPolicy.Cookie",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x002000003f00001a, &upb_pss_1bt},
    {0x003800003f010022, &upb_prm_1bt_max64b},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__config__route__v3__RouteAction__HashPolicy__Cookie_msg_init_ptr = &envoy__config__route__v3__RouteAction__HashPolicy__Cookie_msg_init;
static const upb_MiniTableField envoy_config_route_v3_RouteAction_HashPolicy_ConnectionProperties__fields[1] = {
  {1, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__route__v3__RouteAction__HashPolicy__ConnectionProperties_msg_init = {
  NULL,
  &envoy_config_route_v3_RouteAction_HashPolicy_ConnectionProperties__fields[0],
  16, 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.route.v3.RouteAction.HashPolicy.ConnectionProperties",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f000008, &upb_psb1_1bt},
  })
};

const upb_MiniTable* envoy__config__route__v3__RouteAction__HashPolicy__ConnectionProperties_msg_init_ptr = &envoy__config__route__v3__RouteAction__HashPolicy__ConnectionProperties_msg_init;
static const upb_MiniTableField envoy_config_route_v3_RouteAction_HashPolicy_QueryParameter__fields[1] = {
  {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__route__v3__RouteAction__HashPolicy__QueryParameter_msg_init = {
  NULL,
  &envoy_config_route_v3_RouteAction_HashPolicy_QueryParameter__fields[0],
  UPB_SIZE(16, 24), 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.route.v3.RouteAction.HashPolicy.QueryParameter",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f00000a, &upb_pss_1bt},
  })
};

const upb_MiniTable* envoy__config__route__v3__RouteAction__HashPolicy__QueryParameter_msg_init_ptr = &envoy__config__route__v3__RouteAction__HashPolicy__QueryParameter_msg_init;
static const upb_MiniTableField envoy_config_route_v3_RouteAction_HashPolicy_FilterState__fields[1] = {
  {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__route__v3__RouteAction__HashPolicy__FilterState_msg_init = {
  NULL,
  &envoy_config_route_v3_RouteAction_HashPolicy_FilterState__fields[0],
  UPB_SIZE(16, 24), 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.route.v3.RouteAction.HashPolicy.FilterState",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f00000a, &upb_pss_1bt},
  })
};

const upb_MiniTable* envoy__config__route__v3__RouteAction__HashPolicy__FilterState_msg_init_ptr = &envoy__config__route__v3__RouteAction__HashPolicy__FilterState_msg_init;
static const upb_MiniTableSubInternal envoy_config_route_v3_RouteAction_UpgradeConfig__submsgs[2] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__BoolValue_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__route__v3__RouteAction__UpgradeConfig__ConnectConfig_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_route_v3_RouteAction_UpgradeConfig__fields[3] = {
  {1, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__route__v3__RouteAction__UpgradeConfig_msg_init = {
  &envoy_config_route_v3_RouteAction_UpgradeConfig__submsgs[0],
  &envoy_config_route_v3_RouteAction_UpgradeConfig__fields[0],
  UPB_SIZE(32, 48), 3, kUpb_ExtMode_NonExtendable, 3, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.route.v3.RouteAction.UpgradeConfig",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
  })
};

const upb_MiniTable* envoy__config__route__v3__RouteAction__UpgradeConfig_msg_init_ptr = &envoy__config__route__v3__RouteAction__UpgradeConfig_msg_init;
static const upb_MiniTableSubInternal envoy_config_route_v3_RouteAction_UpgradeConfig_ConnectConfig__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__ProxyProtocolConfig_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_route_v3_RouteAction_UpgradeConfig_ConnectConfig__fields[2] = {
  {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__route__v3__RouteAction__UpgradeConfig__ConnectConfig_msg_init = {
  &envoy_config_route_v3_RouteAction_UpgradeConfig_ConnectConfig__submsgs[0],
  &envoy_config_route_v3_RouteAction_UpgradeConfig_ConnectConfig__fields[0],
  UPB_SIZE(16, 24), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.route.v3.RouteAction.UpgradeConfig.ConnectConfig",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000900003f000010, &upb_psb1_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__config__route__v3__RouteAction__UpgradeConfig__ConnectConfig_msg_init_ptr = &envoy__config__route__v3__RouteAction__UpgradeConfig__ConnectConfig_msg_init;
static const upb_MiniTableSubInternal envoy_config_route_v3_RouteAction_MaxStreamDuration__submsgs[3] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__Duration_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__Duration_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__Duration_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_route_v3_RouteAction_MaxStreamDuration__fields[3] = {
  {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(20, 32), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__route__v3__RouteAction__MaxStreamDuration_msg_init = {
  &envoy_config_route_v3_RouteAction_MaxStreamDuration__submsgs[0],
  &envoy_config_route_v3_RouteAction_MaxStreamDuration__fields[0],
  UPB_SIZE(24, 40), 3, kUpb_ExtMode_NonExtendable, 3, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.route.v3.RouteAction.MaxStreamDuration",
#endif
};

const upb_MiniTable* envoy__config__route__v3__RouteAction__MaxStreamDuration_msg_init_ptr = &envoy__config__route__v3__RouteAction__MaxStreamDuration_msg_init;
static const upb_MiniTableSubInternal envoy_config_route_v3_RetryPolicy__submsgs[10] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__UInt32Value_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__Duration_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__route__v3__RetryPolicy__RetryPriority_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__route__v3__RetryPolicy__RetryHostPredicate_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__route__v3__RetryPolicy__RetryBackOff_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__route__v3__HeaderMatcher_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__route__v3__HeaderMatcher_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__route__v3__RetryPolicy__RateLimitedRetryBackOff_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__TypedExtensionConfig_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__Duration_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_route_v3_RetryPolicy__fields[13] = {
  {1, UPB_SIZE(56, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(20, 48), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(24, 56), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {6, 64, 0, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {7, UPB_SIZE(28, 72), 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {8, UPB_SIZE(32, 80), 67, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {9, UPB_SIZE(36, 88), 0, 5, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {10, UPB_SIZE(40, 96), 0, 6, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {11, UPB_SIZE(44, 104), 68, 7, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {12, UPB_SIZE(48, 112), 0, 8, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {13, UPB_SIZE(52, 120), 69, 9, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__route__v3__RetryPolicy_msg_init = {
  &envoy_config_route_v3_RetryPolicy__submsgs[0],
  &envoy_config_route_v3_RetryPolicy__fields[0],
  UPB_SIZE(72, 128), 13, kUpb_ExtMode_NonExtendable, 13, UPB_FASTTABLE_MASK(120), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.route.v3.RetryPolicy",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x003800003f03002a, &upb_prm_1bt_max64b},
    {0x004000003f000030, &upb_psv8_1bt},
    {0x004800003f00003a, &upb_ppv4_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x005800003f05004a, &upb_prm_1bt_max64b},
    {0x006000003f060052, &upb_prm_1bt_max64b},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x007000003f080062, &upb_prm_1bt_maxmaxb},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__config__route__v3__RetryPolicy_msg_init_ptr = &envoy__config__route__v3__RetryPolicy_msg_init;
static const upb_MiniTableSubInternal envoy_config_route_v3_RetryPolicy_RetryPriority__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__Any_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_route_v3_RetryPolicy_RetryPriority__fields[2] = {
  {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__route__v3__RetryPolicy__RetryPriority_msg_init = {
  &envoy_config_route_v3_RetryPolicy_RetryPriority__submsgs[0],
  &envoy_config_route_v3_RetryPolicy_RetryPriority__fields[0],
  UPB_SIZE(24, 40), 2, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.route.v3.RetryPolicy.RetryPriority",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x002000080300001a, &upb_pom_1bt_maxmaxb},
  })
};

const upb_MiniTable* envoy__config__route__v3__RetryPolicy__RetryPriority_msg_init_ptr = &envoy__config__route__v3__RetryPolicy__RetryPriority_msg_init;
static const upb_MiniTableSubInternal envoy_config_route_v3_RetryPolicy_RetryHostPredicate__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__Any_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_route_v3_RetryPolicy_RetryHostPredicate__fields[2] = {
  {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__route__v3__RetryPolicy__RetryHostPredicate_msg_init = {
  &envoy_config_route_v3_RetryPolicy_RetryHostPredicate__submsgs[0],
  &envoy_config_route_v3_RetryPolicy_RetryHostPredicate__fields[0],
  UPB_SIZE(24, 40), 2, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.route.v3.RetryPolicy.RetryHostPredicate",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x002000080300001a, &upb_pom_1bt_maxmaxb},
  })
};

const upb_MiniTable* envoy__config__route__v3__RetryPolicy__RetryHostPredicate_msg_init_ptr = &envoy__config__route__v3__RetryPolicy__RetryHostPredicate_msg_init;
static const upb_MiniTableSubInternal envoy_config_route_v3_RetryPolicy_RetryBackOff__submsgs[2] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__Duration_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__Duration_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_route_v3_RetryPolicy_RetryBackOff__fields[2] = {
  {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__route__v3__RetryPolicy__RetryBackOff_msg_init = {
  &envoy_config_route_v3_RetryPolicy_RetryBackOff__submsgs[0],
  &envoy_config_route_v3_RetryPolicy_RetryBackOff__fields[0],
  UPB_SIZE(24, 32), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.route.v3.RetryPolicy.RetryBackOff",
#endif
};

const upb_MiniTable* envoy__config__route__v3__RetryPolicy__RetryBackOff_msg_init_ptr = &envoy__config__route__v3__RetryPolicy__RetryBackOff_msg_init;
static const upb_MiniTableField envoy_config_route_v3_RetryPolicy_ResetHeader__fields[2] = {
  {1, UPB_SIZE(12, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, 8, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__route__v3__RetryPolicy__ResetHeader_msg_init = {
  NULL,
  &envoy_config_route_v3_RetryPolicy_ResetHeader__fields[0],
  UPB_SIZE(24, 32), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.route.v3.RetryPolicy.ResetHeader",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
    {0x000800003f000010, &upb_psv4_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__config__route__v3__RetryPolicy__ResetHeader_msg_init_ptr = &envoy__config__route__v3__RetryPolicy__ResetHeader_msg_init;
static const upb_MiniTableSubInternal envoy_config_route_v3_RetryPolicy_RateLimitedRetryBackOff__submsgs[2] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__route__v3__RetryPolicy__ResetHeader_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__Duration_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_route_v3_RetryPolicy_RateLimitedRetryBackOff__fields[2] = {
  {1, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 24), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__route__v3__RetryPolicy__RateLimitedRetryBackOff_msg_init = {
  &envoy_config_route_v3_RetryPolicy_RateLimitedRetryBackOff__submsgs[0],
  &envoy_config_route_v3_RetryPolicy_RateLimitedRetryBackOff__fields[0],
  UPB_SIZE(24, 32), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.route.v3.RetryPolicy.RateLimitedRetryBackOff",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_prm_1bt_max64b},
  })
};

const upb_MiniTable* envoy__config__route__v3__RetryPolicy__RateLimitedRetryBackOff_msg_init_ptr = &envoy__config__route__v3__RetryPolicy__RateLimitedRetryBackOff_msg_init;
static const upb_MiniTableSubInternal envoy_config_route_v3_HedgePolicy__submsgs[2] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__UInt32Value_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__type__v3__FractionalPercent_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_route_v3_HedgePolicy__fields[3] = {
  {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__route__v3__HedgePolicy_msg_init = {
  &envoy_config_route_v3_HedgePolicy__submsgs[0],
  &envoy_config_route_v3_HedgePolicy__fields[0],
  UPB_SIZE(24, 32), 3, kUpb_ExtMode_NonExtendable, 3, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.route.v3.HedgePolicy",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000900003f000018, &upb_psb1_1bt},
  })
};

const upb_MiniTable* envoy__config__route__v3__HedgePolicy_msg_init_ptr = &envoy__config__route__v3__HedgePolicy_msg_init;
static const upb_MiniTableSubInternal envoy_config_route_v3_RedirectAction__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &envoy__type__matcher__v3__RegexMatchAndSubstitute_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_route_v3_RedirectAction__fields[9] = {
  {1, UPB_SIZE(28, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(44, 64), -25, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {3, 12, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(36, 48), -21, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(44, 64), -25, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {6, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {7, UPB_SIZE(36, 48), -21, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {8, 16, 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {9, UPB_SIZE(44, 64), -25, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__route__v3__RedirectAction_msg_init = {
  &envoy_config_route_v3_RedirectAction__submsgs[0],
  &envoy_config_route_v3_RedirectAction__fields[0],
  UPB_SIZE(56, 80), 9, kUpb_ExtMode_NonExtendable, 9, UPB_FASTTABLE_MASK(120), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.route.v3.RedirectAction",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x002000003f00000a, &upb_pss_1bt},
    {0x0040001802000012, &upb_pos_1bt},
    {0x000c00003f000018, &upb_psv4_1bt},
    {0x0030001404000020, &upb_pob1_1bt},
    {0x004000180500002a, &upb_pos_1bt},
    {0x000800003f000030, &upb_psb1_1bt},
    {0x003000140700003a, &upb_pos_1bt},
    {0x001000003f000040, &upb_psv4_1bt},
    {0x004000180900004a, &upb_pom_1bt_maxmaxb},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__config__route__v3__RedirectAction_msg_init_ptr = &envoy__config__route__v3__RedirectAction_msg_init;
static const upb_MiniTableSubInternal envoy_config_route_v3_DirectResponseAction__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__DataSource_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_route_v3_DirectResponseAction__fields[2] = {
  {1, 12, 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {2, 16, 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__route__v3__DirectResponseAction_msg_init = {
  &envoy_config_route_v3_DirectResponseAction__submsgs[0],
  &envoy_config_route_v3_DirectResponseAction__fields[0],
  24, 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.route.v3.DirectResponseAction",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000c00003f000008, &upb_psv4_1bt},
  })
};

const upb_MiniTable* envoy__config__route__v3__DirectResponseAction_msg_init_ptr = &envoy__config__route__v3__DirectResponseAction_msg_init;
const upb_MiniTable envoy__config__route__v3__NonForwardingAction_msg_init = {
  NULL,
  NULL,
  8, 0, kUpb_ExtMode_NonExtendable, 0, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.route.v3.NonForwardingAction",
#endif
};

const upb_MiniTable* envoy__config__route__v3__NonForwardingAction_msg_init_ptr = &envoy__config__route__v3__NonForwardingAction_msg_init;
static const upb_MiniTableSubInternal envoy_config_route_v3_Decorator__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__BoolValue_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_route_v3_Decorator__fields[2] = {
  {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__route__v3__Decorator_msg_init = {
  &envoy_config_route_v3_Decorator__submsgs[0],
  &envoy_config_route_v3_Decorator__fields[0],
  UPB_SIZE(24, 40), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.route.v3.Decorator",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
  })
};

const upb_MiniTable* envoy__config__route__v3__Decorator_msg_init_ptr = &envoy__config__route__v3__Decorator_msg_init;
static const upb_MiniTableSubInternal envoy_config_route_v3_Tracing__submsgs[4] = {
  {.UPB_PRIVATE(submsg) = &envoy__type__v3__FractionalPercent_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__type__v3__FractionalPercent_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__type__v3__FractionalPercent_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__type__tracing__v3__CustomTag_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_route_v3_Tracing__fields[4] = {
  {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(20, 32), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(24, 40), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__route__v3__Tracing_msg_init = {
  &envoy_config_route_v3_Tracing__submsgs[0],
  &envoy_config_route_v3_Tracing__fields[0],
  UPB_SIZE(32, 48), 4, kUpb_ExtMode_NonExtendable, 4, UPB_FASTTABLE_MASK(56), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.route.v3.Tracing",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x002800003f030022, &upb_prm_1bt_maxmaxb},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__config__route__v3__Tracing_msg_init_ptr = &envoy__config__route__v3__Tracing_msg_init;
static const upb_MiniTableSubInternal envoy_config_route_v3_VirtualCluster__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__route__v3__HeaderMatcher_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_route_v3_VirtualCluster__fields[2] = {
  {2, UPB_SIZE(12, 8), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(8, 24), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__route__v3__VirtualCluster_msg_init = {
  &envoy_config_route_v3_VirtualCluster__submsgs[0],
  &envoy_config_route_v3_VirtualCluster__fields[0],
  UPB_SIZE(24, 32), 2, kUpb_ExtMode_NonExtendable, 0, UPB_FASTTABLE_MASK(56), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.route.v3.VirtualCluster",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f000012, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001800003f000022, &upb_prm_1bt_max64b},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__config__route__v3__VirtualCluster_msg_init_ptr = &envoy__config__route__v3__VirtualCluster_msg_init;
static const upb_MiniTableSubInternal envoy_config_route_v3_RateLimit__submsgs[4] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__UInt32Value_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__route__v3__RateLimit__Action_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__route__v3__RateLimit__Override_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__route__v3__RateLimit__HitsAddend_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_route_v3_RateLimit__fields[6] = {
  {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(28, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(16, 40), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(20, 48), 65, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(24, 56), 66, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {6, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__route__v3__RateLimit_msg_init = {
  &envoy_config_route_v3_RateLimit__submsgs[0],
  &envoy_config_route_v3_RateLimit__fields[0],
  UPB_SIZE(40, 64), 6, kUpb_ExtMode_NonExtendable, 6, UPB_FASTTABLE_MASK(56), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.route.v3.RateLimit",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f000012, &upb_pss_1bt},
    {0x002800003f01001a, &upb_prm_1bt_max64b},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000900003f000030, &upb_psb1_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__config__route__v3__RateLimit_msg_init_ptr = &envoy__config__route__v3__RateLimit_msg_init;
static const upb_MiniTableSubInternal envoy_config_route_v3_RateLimit_Action__submsgs[12] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__route__v3__RateLimit__Action__SourceCluster_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__route__v3__RateLimit__Action__DestinationCluster_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__route__v3__RateLimit__Action__RequestHeaders_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__route__v3__RateLimit__Action__RemoteAddress_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__route__v3__RateLimit__Action__GenericKey_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__route__v3__RateLimit__Action__HeaderValueMatch_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__route__v3__RateLimit__Action__DynamicMetaData_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__route__v3__RateLimit__Action__MetaData_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__TypedExtensionConfig_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__route__v3__RateLimit__Action__MaskedRemoteAddress_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__route__v3__RateLimit__Action__QueryParameterValueMatch_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__route__v3__RateLimit__Action__QueryParameters_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_route_v3_RateLimit_Action__fields[12] = {
  {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(12, 16), -9, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(12, 16), -9, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(12, 16), -9, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {6, UPB_SIZE(12, 16), -9, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {7, UPB_SIZE(12, 16), -9, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {8, UPB_SIZE(12, 16), -9, 7, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {9, UPB_SIZE(12, 16), -9, 8, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {10, UPB_SIZE(12, 16), -9, 9, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {11, UPB_SIZE(12, 16), -9, 10, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {12, UPB_SIZE(12, 16), -9, 11, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__route__v3__RateLimit__Action_msg_init = {
  &envoy_config_route_v3_RateLimit_Action__submsgs[0],
  &envoy_config_route_v3_RateLimit_Action__fields[0],
  UPB_SIZE(16, 24), 12, kUpb_ExtMode_NonExtendable, 12, UPB_FASTTABLE_MASK(120), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.route.v3.RateLimit.Action",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000080100000a, &upb_pom_1bt_max64b},
    {0x0010000802010012, &upb_pom_1bt_max64b},
    {0x001000080302001a, &upb_pom_1bt_max64b},
    {0x0010000804030022, &upb_pom_1bt_max64b},
    {0x001000080504002a, &upb_pom_1bt_max64b},
    {0x0010000806050032, &upb_pom_1bt_max128b},
    {0x001000080706003a, &upb_pom_1bt_max64b},
    {0x0010000808070042, &upb_pom_1bt_max64b},
    {0x001000080908004a, &upb_pom_1bt_maxmaxb},
    {0x001000080a090052, &upb_pom_1bt_max64b},
    {0x001000080b0a005a, &upb_pom_1bt_max128b},
    {0x001000080c0b0062, &upb_pom_1bt_max64b},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__config__route__v3__RateLimit__Action_msg_init_ptr = &envoy__config__route__v3__RateLimit__Action_msg_init;
const upb_MiniTable envoy__config__route__v3__RateLimit__Action__SourceCluster_msg_init = {
  NULL,
  NULL,
  8, 0, kUpb_ExtMode_NonExtendable, 0, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.route.v3.RateLimit.Action.SourceCluster",
#endif
};

const upb_MiniTable* envoy__config__route__v3__RateLimit__Action__SourceCluster_msg_init_ptr = &envoy__config__route__v3__RateLimit__Action__SourceCluster_msg_init;
const upb_MiniTable envoy__config__route__v3__RateLimit__Action__DestinationCluster_msg_init = {
  NULL,
  NULL,
  8, 0, kUpb_ExtMode_NonExtendable, 0, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.route.v3.RateLimit.Action.DestinationCluster",
#endif
};

const upb_MiniTable* envoy__config__route__v3__RateLimit__Action__DestinationCluster_msg_init_ptr = &envoy__config__route__v3__RateLimit__Action__DestinationCluster_msg_init;
static const upb_MiniTableField envoy_config_route_v3_RateLimit_Action_RequestHeaders__fields[3] = {
  {1, UPB_SIZE(12, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(20, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {3, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__route__v3__RateLimit__Action__RequestHeaders_msg_init = {
  NULL,
  &envoy_config_route_v3_RateLimit_Action_RequestHeaders__fields[0],
  UPB_SIZE(32, 48), 3, kUpb_ExtMode_NonExtendable, 3, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.route.v3.RateLimit.Action.RequestHeaders",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
    {0x002000003f000012, &upb_pss_1bt},
    {0x000800003f000018, &upb_psb1_1bt},
  })
};

const upb_MiniTable* envoy__config__route__v3__RateLimit__Action__RequestHeaders_msg_init_ptr = &envoy__config__route__v3__RateLimit__Action__RequestHeaders_msg_init;
static const upb_MiniTableField envoy_config_route_v3_RateLimit_Action_QueryParameters__fields[3] = {
  {1, UPB_SIZE(12, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(20, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {3, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__route__v3__RateLimit__Action__QueryParameters_msg_init = {
  NULL,
  &envoy_config_route_v3_RateLimit_Action_QueryParameters__fields[0],
  UPB_SIZE(32, 48), 3, kUpb_ExtMode_NonExtendable, 3, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.route.v3.RateLimit.Action.QueryParameters",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
    {0x002000003f000012, &upb_pss_1bt},
    {0x000800003f000018, &upb_psb1_1bt},
  })
};

const upb_MiniTable* envoy__config__route__v3__RateLimit__Action__QueryParameters_msg_init_ptr = &envoy__config__route__v3__RateLimit__Action__QueryParameters_msg_init;
const upb_MiniTable envoy__config__route__v3__RateLimit__Action__RemoteAddress_msg_init = {
  NULL,
  NULL,
  8, 0, kUpb_ExtMode_NonExtendable, 0, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.route.v3.RateLimit.Action.RemoteAddress",
#endif
};

const upb_MiniTable* envoy__config__route__v3__RateLimit__Action__RemoteAddress_msg_init_ptr = &envoy__config__route__v3__RateLimit__Action__RemoteAddress_msg_init;
static const upb_MiniTableSubInternal envoy_config_route_v3_RateLimit_Action_MaskedRemoteAddress__submsgs[2] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__UInt32Value_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__UInt32Value_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_route_v3_RateLimit_Action_MaskedRemoteAddress__fields[2] = {
  {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__route__v3__RateLimit__Action__MaskedRemoteAddress_msg_init = {
  &envoy_config_route_v3_RateLimit_Action_MaskedRemoteAddress__submsgs[0],
  &envoy_config_route_v3_RateLimit_Action_MaskedRemoteAddress__fields[0],
  UPB_SIZE(24, 32), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.route.v3.RateLimit.Action.MaskedRemoteAddress",
#endif
};

const upb_MiniTable* envoy__config__route__v3__RateLimit__Action__MaskedRemoteAddress_msg_init_ptr = &envoy__config__route__v3__RateLimit__Action__MaskedRemoteAddress_msg_init;
static const upb_MiniTableField envoy_config_route_v3_RateLimit_Action_GenericKey__fields[2] = {
  {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__route__v3__RateLimit__Action__GenericKey_msg_init = {
  NULL,
  &envoy_config_route_v3_RateLimit_Action_GenericKey__fields[0],
  UPB_SIZE(24, 40), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.route.v3.RateLimit.Action.GenericKey",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f00000a, &upb_pss_1bt},
    {0x001800003f000012, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__config__route__v3__RateLimit__Action__GenericKey_msg_init_ptr = &envoy__config__route__v3__RateLimit__Action__GenericKey_msg_init;
static const upb_MiniTableSubInternal envoy_config_route_v3_RateLimit_Action_HeaderValueMatch__submsgs[2] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__BoolValue_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__route__v3__HeaderMatcher_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_route_v3_RateLimit_Action_HeaderValueMatch__fields[4] = {
  {1, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 48), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(16, 56), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(28, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__route__v3__RateLimit__Action__HeaderValueMatch_msg_init = {
  &envoy_config_route_v3_RateLimit_Action_HeaderValueMatch__submsgs[0],
  &envoy_config_route_v3_RateLimit_Action_HeaderValueMatch__fields[0],
  UPB_SIZE(40, 64), 4, kUpb_ExtMode_NonExtendable, 4, UPB_FASTTABLE_MASK(56), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.route.v3.RateLimit.Action.HeaderValueMatch",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x003800003f01001a, &upb_prm_1bt_max64b},
    {0x002000003f000022, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__config__route__v3__RateLimit__Action__HeaderValueMatch_msg_init_ptr = &envoy__config__route__v3__RateLimit__Action__HeaderValueMatch_msg_init;
static const upb_MiniTableSubInternal envoy_config_route_v3_RateLimit_Action_DynamicMetaData__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &envoy__type__metadata__v3__MetadataKey_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_route_v3_RateLimit_Action_DynamicMetaData__fields[3] = {
  {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 48), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(24, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__route__v3__RateLimit__Action__DynamicMetaData_msg_init = {
  &envoy_config_route_v3_RateLimit_Action_DynamicMetaData__submsgs[0],
  &envoy_config_route_v3_RateLimit_Action_DynamicMetaData__fields[0],
  UPB_SIZE(32, 56), 3, kUpb_ExtMode_NonExtendable, 3, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.route.v3.RateLimit.Action.DynamicMetaData",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x002000003f00001a, &upb_pss_1bt},
  })
};

const upb_MiniTable* envoy__config__route__v3__RateLimit__Action__DynamicMetaData_msg_init_ptr = &envoy__config__route__v3__RateLimit__Action__DynamicMetaData_msg_init;
static const upb_MiniTableSubInternal envoy_config_route_v3_RateLimit_Action_MetaData__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &envoy__type__metadata__v3__MetadataKey_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_route_v3_RateLimit_Action_MetaData__fields[5] = {
  {1, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 48), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(28, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(16, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {5, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__route__v3__RateLimit__Action__MetaData_msg_init = {
  &envoy_config_route_v3_RateLimit_Action_MetaData__submsgs[0],
  &envoy_config_route_v3_RateLimit_Action_MetaData__fields[0],
  UPB_SIZE(40, 56), 5, kUpb_ExtMode_NonExtendable, 5, UPB_FASTTABLE_MASK(56), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.route.v3.RateLimit.Action.MetaData",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x002000003f00001a, &upb_pss_1bt},
    {0x000c00003f000020, &upb_psv4_1bt},
    {0x000900003f000028, &upb_psb1_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__config__route__v3__RateLimit__Action__MetaData_msg_init_ptr = &envoy__config__route__v3__RateLimit__Action__MetaData_msg_init;
static const upb_MiniTableSubInternal envoy_config_route_v3_RateLimit_Action_QueryParameterValueMatch__submsgs[2] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__BoolValue_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__route__v3__QueryParameterMatcher_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_route_v3_RateLimit_Action_QueryParameterValueMatch__fields[4] = {
  {1, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 48), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(16, 56), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(28, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__route__v3__RateLimit__Action__QueryParameterValueMatch_msg_init = {
  &envoy_config_route_v3_RateLimit_Action_QueryParameterValueMatch__submsgs[0],
  &envoy_config_route_v3_RateLimit_Action_QueryParameterValueMatch__fields[0],
  UPB_SIZE(40, 64), 4, kUpb_ExtMode_NonExtendable, 4, UPB_FASTTABLE_MASK(56), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.route.v3.RateLimit.Action.QueryParameterValueMatch",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x003800003f01001a, &upb_prm_1bt_max64b},
    {0x002000003f000022, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__config__route__v3__RateLimit__Action__QueryParameterValueMatch_msg_init_ptr = &envoy__config__route__v3__RateLimit__Action__QueryParameterValueMatch_msg_init;
static const upb_MiniTableSubInternal envoy_config_route_v3_RateLimit_Override__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__route__v3__RateLimit__Override__DynamicMetadata_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_route_v3_RateLimit_Override__fields[1] = {
  {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__route__v3__RateLimit__Override_msg_init = {
  &envoy_config_route_v3_RateLimit_Override__submsgs[0],
  &envoy_config_route_v3_RateLimit_Override__fields[0],
  UPB_SIZE(16, 24), 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.route.v3.RateLimit.Override",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000080100000a, &upb_pom_1bt_max64b},
  })
};

const upb_MiniTable* envoy__config__route__v3__RateLimit__Override_msg_init_ptr = &envoy__config__route__v3__RateLimit__Override_msg_init;
static const upb_MiniTableSubInternal envoy_config_route_v3_RateLimit_Override_DynamicMetadata__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &envoy__type__metadata__v3__MetadataKey_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_route_v3_RateLimit_Override_DynamicMetadata__fields[1] = {
  {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__route__v3__RateLimit__Override__DynamicMetadata_msg_init = {
  &envoy_config_route_v3_RateLimit_Override_DynamicMetadata__submsgs[0],
  &envoy_config_route_v3_RateLimit_Override_DynamicMetadata__fields[0],
  UPB_SIZE(16, 24), 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.route.v3.RateLimit.Override.DynamicMetadata",
#endif
};

const upb_MiniTable* envoy__config__route__v3__RateLimit__Override__DynamicMetadata_msg_init_ptr = &envoy__config__route__v3__RateLimit__Override__DynamicMetadata_msg_init;
static const upb_MiniTableSubInternal envoy_config_route_v3_RateLimit_HitsAddend__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__UInt64Value_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_route_v3_RateLimit_HitsAddend__fields[2] = {
  {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__route__v3__RateLimit__HitsAddend_msg_init = {
  &envoy_config_route_v3_RateLimit_HitsAddend__submsgs[0],
  &envoy_config_route_v3_RateLimit_HitsAddend__fields[0],
  UPB_SIZE(24, 40), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.route.v3.RateLimit.HitsAddend",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f000012, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__config__route__v3__RateLimit__HitsAddend_msg_init_ptr = &envoy__config__route__v3__RateLimit__HitsAddend_msg_init;
static const upb_MiniTableSubInternal envoy_config_route_v3_HeaderMatcher__submsgs[3] = {
  {.UPB_PRIVATE(submsg) = &envoy__type__v3__Int64Range_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__type__matcher__v3__RegexMatcher_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__type__matcher__v3__StringMatcher_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_route_v3_HeaderMatcher__fields[11] = {
  {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(24, 32), -13, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {6, UPB_SIZE(24, 32), -13, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {7, UPB_SIZE(24, 32), -13, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {8, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {9, UPB_SIZE(24, 32), -13, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {10, UPB_SIZE(24, 32), -13, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {11, UPB_SIZE(24, 32), -13, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {12, UPB_SIZE(24, 32), -13, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {13, UPB_SIZE(24, 32), -13, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {14, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__route__v3__HeaderMatcher_msg_init = {
  &envoy_config_route_v3_HeaderMatcher__submsgs[0],
  &envoy_config_route_v3_HeaderMatcher__fields[0],
  UPB_SIZE(32, 48), 11, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(120), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.route.v3.HeaderMatcher",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0020000c04000022, &upb_pos_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0020000c06000032, &upb_pom_1bt_maxmaxb},
    {0x0020000c07000038, &upb_pob1_1bt},
    {0x000800003f000040, &upb_psb1_1bt},
    {0x0020000c0900004a, &upb_pos_1bt},
    {0x0020000c0a000052, &upb_pos_1bt},
    {0x0020000c0b01005a, &upb_pom_1bt_maxmaxb},
    {0x0020000c0c000062, &upb_pos_1bt},
    {0x0020000c0d02006a, &upb_pom_1bt_maxmaxb},
    {0x000900003f000070, &upb_psb1_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__config__route__v3__HeaderMatcher_msg_init_ptr = &envoy__config__route__v3__HeaderMatcher_msg_init;
static const upb_MiniTableSubInternal envoy_config_route_v3_QueryParameterMatcher__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &envoy__type__matcher__v3__StringMatcher_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_route_v3_QueryParameterMatcher__fields[3] = {
  {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {6, UPB_SIZE(12, 32), -9, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__route__v3__QueryParameterMatcher_msg_init = {
  &envoy_config_route_v3_QueryParameterMatcher__submsgs[0],
  &envoy_config_route_v3_QueryParameterMatcher__fields[0],
  UPB_SIZE(24, 40), 3, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(56), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.route.v3.QueryParameterMatcher",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x002000080500002a, &upb_pom_1bt_maxmaxb},
    {0x0020000806000030, &upb_pob1_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__config__route__v3__QueryParameterMatcher_msg_init_ptr = &envoy__config__route__v3__QueryParameterMatcher_msg_init;
static const upb_MiniTableSubInternal envoy_config_route_v3_InternalRedirectPolicy__submsgs[2] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__UInt32Value_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__TypedExtensionConfig_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_route_v3_InternalRedirectPolicy__fields[5] = {
  {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(20, 32), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(24, 40), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__route__v3__InternalRedirectPolicy_msg_init = {
  &envoy_config_route_v3_InternalRedirectPolicy__submsgs[0],
  &envoy_config_route_v3_InternalRedirectPolicy__fields[0],
  UPB_SIZE(32, 48), 5, kUpb_ExtMode_NonExtendable, 5, UPB_FASTTABLE_MASK(56), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.route.v3.InternalRedirectPolicy",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001800003f000012, &upb_ppv4_1bt},
    {0x002000003f01001a, &upb_prm_1bt_maxmaxb},
    {0x000900003f000020, &upb_psb1_1bt},
    {0x002800003f00002a, &upb_prs_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__config__route__v3__InternalRedirectPolicy_msg_init_ptr = &envoy__config__route__v3__InternalRedirectPolicy_msg_init;
static const upb_MiniTableSubInternal envoy_config_route_v3_FilterConfig__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__Any_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_route_v3_FilterConfig__fields[3] = {
  {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {3, 10, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__route__v3__FilterConfig_msg_init = {
  &envoy_config_route_v3_FilterConfig__submsgs[0],
  &envoy_config_route_v3_FilterConfig__fields[0],
  UPB_SIZE(16, 24), 3, kUpb_ExtMode_NonExtendable, 3, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.route.v3.FilterConfig",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000900003f000010, &upb_psb1_1bt},
    {0x000a00003f000018, &upb_psb1_1bt},
  })
};

const upb_MiniTable* envoy__config__route__v3__FilterConfig_msg_init_ptr = &envoy__config__route__v3__FilterConfig_msg_init;
static const upb_MiniTable *messages_layout[60] = {
  &envoy__config__route__v3__VirtualHost_msg_init,
  &envoy__config__route__v3__VirtualHost__TypedPerFilterConfigEntry_msg_init,
  &envoy__config__route__v3__FilterAction_msg_init,
  &envoy__config__route__v3__RouteList_msg_init,
  &envoy__config__route__v3__Route_msg_init,
  &envoy__config__route__v3__Route__TypedPerFilterConfigEntry_msg_init,
  &envoy__config__route__v3__WeightedCluster_msg_init,
  &envoy__config__route__v3__WeightedCluster__ClusterWeight_msg_init,
  &envoy__config__route__v3__WeightedCluster__ClusterWeight__TypedPerFilterConfigEntry_msg_init,
  &envoy__config__route__v3__ClusterSpecifierPlugin_msg_init,
  &envoy__config__route__v3__RouteMatch_msg_init,
  &envoy__config__route__v3__RouteMatch__GrpcRouteMatchOptions_msg_init,
  &envoy__config__route__v3__RouteMatch__TlsContextMatchOptions_msg_init,
  &envoy__config__route__v3__RouteMatch__ConnectMatcher_msg_init,
  &envoy__config__route__v3__CorsPolicy_msg_init,
  &envoy__config__route__v3__RouteAction_msg_init,
  &envoy__config__route__v3__RouteAction__RequestMirrorPolicy_msg_init,
  &envoy__config__route__v3__RouteAction__HashPolicy_msg_init,
  &envoy__config__route__v3__RouteAction__HashPolicy__Header_msg_init,
  &envoy__config__route__v3__RouteAction__HashPolicy__CookieAttribute_msg_init,
  &envoy__config__route__v3__RouteAction__HashPolicy__Cookie_msg_init,
  &envoy__config__route__v3__RouteAction__HashPolicy__ConnectionProperties_msg_init,
  &envoy__config__route__v3__RouteAction__HashPolicy__QueryParameter_msg_init,
  &envoy__config__route__v3__RouteAction__HashPolicy__FilterState_msg_init,
  &envoy__config__route__v3__RouteAction__UpgradeConfig_msg_init,
  &envoy__config__route__v3__RouteAction__UpgradeConfig__ConnectConfig_msg_init,
  &envoy__config__route__v3__RouteAction__MaxStreamDuration_msg_init,
  &envoy__config__route__v3__RetryPolicy_msg_init,
  &envoy__config__route__v3__RetryPolicy__RetryPriority_msg_init,
  &envoy__config__route__v3__RetryPolicy__RetryHostPredicate_msg_init,
  &envoy__config__route__v3__RetryPolicy__RetryBackOff_msg_init,
  &envoy__config__route__v3__RetryPolicy__ResetHeader_msg_init,
  &envoy__config__route__v3__RetryPolicy__RateLimitedRetryBackOff_msg_init,
  &envoy__config__route__v3__HedgePolicy_msg_init,
  &envoy__config__route__v3__RedirectAction_msg_init,
  &envoy__config__route__v3__DirectResponseAction_msg_init,
  &envoy__config__route__v3__NonForwardingAction_msg_init,
  &envoy__config__route__v3__Decorator_msg_init,
  &envoy__config__route__v3__Tracing_msg_init,
  &envoy__config__route__v3__VirtualCluster_msg_init,
  &envoy__config__route__v3__RateLimit_msg_init,
  &envoy__config__route__v3__RateLimit__Action_msg_init,
  &envoy__config__route__v3__RateLimit__Action__SourceCluster_msg_init,
  &envoy__config__route__v3__RateLimit__Action__DestinationCluster_msg_init,
  &envoy__config__route__v3__RateLimit__Action__RequestHeaders_msg_init,
  &envoy__config__route__v3__RateLimit__Action__QueryParameters_msg_init,
  &envoy__config__route__v3__RateLimit__Action__RemoteAddress_msg_init,
  &envoy__config__route__v3__RateLimit__Action__MaskedRemoteAddress_msg_init,
  &envoy__config__route__v3__RateLimit__Action__GenericKey_msg_init,
  &envoy__config__route__v3__RateLimit__Action__HeaderValueMatch_msg_init,
  &envoy__config__route__v3__RateLimit__Action__DynamicMetaData_msg_init,
  &envoy__config__route__v3__RateLimit__Action__MetaData_msg_init,
  &envoy__config__route__v3__RateLimit__Action__QueryParameterValueMatch_msg_init,
  &envoy__config__route__v3__RateLimit__Override_msg_init,
  &envoy__config__route__v3__RateLimit__Override__DynamicMetadata_msg_init,
  &envoy__config__route__v3__RateLimit__HitsAddend_msg_init,
  &envoy__config__route__v3__HeaderMatcher_msg_init,
  &envoy__config__route__v3__QueryParameterMatcher_msg_init,
  &envoy__config__route__v3__InternalRedirectPolicy_msg_init,
  &envoy__config__route__v3__FilterConfig_msg_init,
};

const upb_MiniTableFile envoy_config_route_v3_route_components_proto_upb_file_layout = {
  messages_layout,
  NULL,
  NULL,
  60,
  0,
  0,
};

#include "upb/port/undef.inc"
