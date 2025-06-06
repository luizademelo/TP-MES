
#include <stddef.h>
#include "upb/generated_code_support.h"
#include "envoy/config/endpoint/v3/endpoint_components.upb_minitable.h"
#include "envoy/config/core/v3/address.upb_minitable.h"
#include "envoy/config/core/v3/base.upb_minitable.h"
#include "envoy/config/core/v3/config_source.upb_minitable.h"
#include "envoy/config/core/v3/health_check.upb_minitable.h"
#include "google/protobuf/wrappers.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
static const upb_MiniTableSubInternal envoy_config_endpoint_v3_Endpoint__submsgs[3] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__Address_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__endpoint__v3__Endpoint__HealthCheckConfig_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__endpoint__v3__Endpoint__AdditionalAddress_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_endpoint_v3_Endpoint__fields[4] = {
  {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(24, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(20, 48), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__endpoint__v3__Endpoint_msg_init = {
  &envoy_config_endpoint_v3_Endpoint__submsgs[0],
  &envoy_config_endpoint_v3_Endpoint__fields[0],
  UPB_SIZE(32, 56), 4, kUpb_ExtMode_NonExtendable, 4, UPB_FASTTABLE_MASK(56), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.endpoint.v3.Endpoint",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00001a, &upb_pss_1bt},
    {0x003000003f020022, &upb_prm_1bt_max64b},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__config__endpoint__v3__Endpoint_msg_init_ptr = &envoy__config__endpoint__v3__Endpoint_msg_init;
static const upb_MiniTableSubInternal envoy_config_endpoint_v3_Endpoint_HealthCheckConfig__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__Address_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_endpoint_v3_Endpoint_HealthCheckConfig__fields[4] = {
  {1, 12, 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(16, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__endpoint__v3__Endpoint__HealthCheckConfig_msg_init = {
  &envoy_config_endpoint_v3_Endpoint_HealthCheckConfig__submsgs[0],
  &envoy_config_endpoint_v3_Endpoint_HealthCheckConfig__fields[0],
  UPB_SIZE(32, 40), 4, kUpb_ExtMode_NonExtendable, 4, UPB_FASTTABLE_MASK(56), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.endpoint.v3.Endpoint.HealthCheckConfig",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000c00003f000008, &upb_psv4_1bt},
    {0x001000003f000012, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000900003f000020, &upb_psb1_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__config__endpoint__v3__Endpoint__HealthCheckConfig_msg_init_ptr = &envoy__config__endpoint__v3__Endpoint__HealthCheckConfig_msg_init;
static const upb_MiniTableSubInternal envoy_config_endpoint_v3_Endpoint_AdditionalAddress__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__Address_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_endpoint_v3_Endpoint_AdditionalAddress__fields[1] = {
  {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__endpoint__v3__Endpoint__AdditionalAddress_msg_init = {
  &envoy_config_endpoint_v3_Endpoint_AdditionalAddress__submsgs[0],
  &envoy_config_endpoint_v3_Endpoint_AdditionalAddress__fields[0],
  UPB_SIZE(16, 24), 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.endpoint.v3.Endpoint.AdditionalAddress",
#endif
};

const upb_MiniTable* envoy__config__endpoint__v3__Endpoint__AdditionalAddress_msg_init_ptr = &envoy__config__endpoint__v3__Endpoint__AdditionalAddress_msg_init;
static const upb_MiniTableSubInternal envoy_config_endpoint_v3_LbEndpoint__submsgs[3] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__endpoint__v3__Endpoint_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__Metadata_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__UInt32Value_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_endpoint_v3_LbEndpoint__fields[5] = {
  {1, UPB_SIZE(28, 24), UPB_SIZE(-25, -17), 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, 12, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(16, 40), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(20, 48), 65, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(28, 24), UPB_SIZE(-25, -17), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__endpoint__v3__LbEndpoint_msg_init = {
  &envoy_config_endpoint_v3_LbEndpoint__submsgs[0],
  &envoy_config_endpoint_v3_LbEndpoint__fields[0],
  UPB_SIZE(40, 56), 5, kUpb_ExtMode_NonExtendable, 5, UPB_FASTTABLE_MASK(56), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.endpoint.v3.LbEndpoint",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001800100100000a, &upb_pom_1bt_max64b},
    {0x000c00003f000010, &upb_psv4_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001800100500002a, &upb_pos_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__config__endpoint__v3__LbEndpoint_msg_init_ptr = &envoy__config__endpoint__v3__LbEndpoint_msg_init;
static const upb_MiniTableSubInternal envoy_config_endpoint_v3_LedsClusterLocalityConfig__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__ConfigSource_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_endpoint_v3_LedsClusterLocalityConfig__fields[2] = {
  {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__endpoint__v3__LedsClusterLocalityConfig_msg_init = {
  &envoy_config_endpoint_v3_LedsClusterLocalityConfig__submsgs[0],
  &envoy_config_endpoint_v3_LedsClusterLocalityConfig__fields[0],
  UPB_SIZE(24, 40), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.endpoint.v3.LedsClusterLocalityConfig",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f000012, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__config__endpoint__v3__LedsClusterLocalityConfig_msg_init_ptr = &envoy__config__endpoint__v3__LedsClusterLocalityConfig_msg_init;
static const upb_MiniTableSubInternal envoy_config_endpoint_v3_LocalityLbEndpoints__submsgs[7] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__Locality_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__endpoint__v3__LbEndpoint_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__UInt32Value_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__UInt32Value_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__endpoint__v3__LocalityLbEndpoints__LbEndpointList_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__endpoint__v3__LedsClusterLocalityConfig_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__Metadata_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_endpoint_v3_LocalityLbEndpoints__fields[8] = {
  {1, UPB_SIZE(12, 24), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 32), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(20, 40), 65, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(24, 12), 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {6, UPB_SIZE(28, 48), 66, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {7, UPB_SIZE(40, 64), UPB_SIZE(-37, -17), 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {8, UPB_SIZE(40, 64), UPB_SIZE(-37, -17), 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {9, UPB_SIZE(32, 56), 67, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__endpoint__v3__LocalityLbEndpoints_msg_init = {
  &envoy_config_endpoint_v3_LocalityLbEndpoints__submsgs[0],
  &envoy_config_endpoint_v3_LocalityLbEndpoints__fields[0],
  UPB_SIZE(48, 72), 8, kUpb_ExtMode_NonExtendable, 3, UPB_FASTTABLE_MASK(120), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.endpoint.v3.LocalityLbEndpoints",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x002000003f010012, &upb_prm_1bt_max64b},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000c00003f000028, &upb_psv4_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x004000100704003a, &upb_pom_1bt_max64b},
    {0x0040001008050042, &upb_pom_1bt_max64b},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__config__endpoint__v3__LocalityLbEndpoints_msg_init_ptr = &envoy__config__endpoint__v3__LocalityLbEndpoints_msg_init;
static const upb_MiniTableSubInternal envoy_config_endpoint_v3_LocalityLbEndpoints_LbEndpointList__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__endpoint__v3__LbEndpoint_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_endpoint_v3_LocalityLbEndpoints_LbEndpointList__fields[1] = {
  {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__endpoint__v3__LocalityLbEndpoints__LbEndpointList_msg_init = {
  &envoy_config_endpoint_v3_LocalityLbEndpoints_LbEndpointList__submsgs[0],
  &envoy_config_endpoint_v3_LocalityLbEndpoints_LbEndpointList__fields[0],
  16, 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.endpoint.v3.LocalityLbEndpoints.LbEndpointList",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f00000a, &upb_prm_1bt_max64b},
  })
};

const upb_MiniTable* envoy__config__endpoint__v3__LocalityLbEndpoints__LbEndpointList_msg_init_ptr = &envoy__config__endpoint__v3__LocalityLbEndpoints__LbEndpointList_msg_init;
static const upb_MiniTable *messages_layout[7] = {
  &envoy__config__endpoint__v3__Endpoint_msg_init,
  &envoy__config__endpoint__v3__Endpoint__HealthCheckConfig_msg_init,
  &envoy__config__endpoint__v3__Endpoint__AdditionalAddress_msg_init,
  &envoy__config__endpoint__v3__LbEndpoint_msg_init,
  &envoy__config__endpoint__v3__LedsClusterLocalityConfig_msg_init,
  &envoy__config__endpoint__v3__LocalityLbEndpoints_msg_init,
  &envoy__config__endpoint__v3__LocalityLbEndpoints__LbEndpointList_msg_init,
};

const upb_MiniTableFile envoy_config_endpoint_v3_endpoint_components_proto_upb_file_layout = {
  messages_layout,
  NULL,
  NULL,
  7,
  0,
  0,
};

#include "upb/port/undef.inc"
