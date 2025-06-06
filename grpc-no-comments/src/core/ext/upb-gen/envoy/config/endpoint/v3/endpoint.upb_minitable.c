
#include <stddef.h>
#include "upb/generated_code_support.h"
#include "envoy/config/endpoint/v3/endpoint.upb_minitable.h"
#include "envoy/config/endpoint/v3/endpoint_components.upb_minitable.h"
#include "envoy/type/v3/percent.upb_minitable.h"
#include "google/protobuf/duration.upb_minitable.h"
#include "google/protobuf/wrappers.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
static const upb_MiniTableSubInternal envoy_config_endpoint_v3_ClusterLoadAssignment__submsgs[3] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__endpoint__v3__LocalityLbEndpoints_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__endpoint__v3__ClusterLoadAssignment__Policy_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__endpoint__v3__ClusterLoadAssignment__NamedEndpointsEntry_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_endpoint_v3_ClusterLoadAssignment__fields[4] = {
  {1, UPB_SIZE(24, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 32), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(16, 40), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(20, 48), 0, 2, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__endpoint__v3__ClusterLoadAssignment_msg_init = {
  &envoy_config_endpoint_v3_ClusterLoadAssignment__submsgs[0],
  &envoy_config_endpoint_v3_ClusterLoadAssignment__fields[0],
  UPB_SIZE(32, 56), 4, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.endpoint.v3.ClusterLoadAssignment",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
    {0x002000003f000012, &upb_prm_1bt_maxmaxb},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__config__endpoint__v3__ClusterLoadAssignment_msg_init_ptr = &envoy__config__endpoint__v3__ClusterLoadAssignment_msg_init;
static const upb_MiniTableSubInternal envoy_config_endpoint_v3_ClusterLoadAssignment_Policy__submsgs[3] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__endpoint__v3__ClusterLoadAssignment__Policy__DropOverload_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__UInt32Value_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__Duration_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_endpoint_v3_ClusterLoadAssignment_Policy__fields[4] = {
  {2, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(16, 24), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(20, 32), 65, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {6, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__endpoint__v3__ClusterLoadAssignment__Policy_msg_init = {
  &envoy_config_endpoint_v3_ClusterLoadAssignment_Policy__submsgs[0],
  &envoy_config_endpoint_v3_ClusterLoadAssignment_Policy__fields[0],
  UPB_SIZE(24, 40), 4, kUpb_ExtMode_NonExtendable, 0, UPB_FASTTABLE_MASK(56), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.endpoint.v3.ClusterLoadAssignment.Policy",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f000012, &upb_prm_1bt_max64b},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000900003f000030, &upb_psb1_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__config__endpoint__v3__ClusterLoadAssignment__Policy_msg_init_ptr = &envoy__config__endpoint__v3__ClusterLoadAssignment__Policy_msg_init;
static const upb_MiniTableSubInternal envoy_config_endpoint_v3_ClusterLoadAssignment_Policy_DropOverload__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &envoy__type__v3__FractionalPercent_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_endpoint_v3_ClusterLoadAssignment_Policy_DropOverload__fields[2] = {
  {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__endpoint__v3__ClusterLoadAssignment__Policy__DropOverload_msg_init = {
  &envoy_config_endpoint_v3_ClusterLoadAssignment_Policy_DropOverload__submsgs[0],
  &envoy_config_endpoint_v3_ClusterLoadAssignment_Policy_DropOverload__fields[0],
  UPB_SIZE(24, 40), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.endpoint.v3.ClusterLoadAssignment.Policy.DropOverload",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
  })
};

const upb_MiniTable* envoy__config__endpoint__v3__ClusterLoadAssignment__Policy__DropOverload_msg_init_ptr = &envoy__config__endpoint__v3__ClusterLoadAssignment__Policy__DropOverload_msg_init;
static const upb_MiniTableSubInternal envoy_config_endpoint_v3_ClusterLoadAssignment_NamedEndpointsEntry__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__endpoint__v3__Endpoint_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_endpoint_v3_ClusterLoadAssignment_NamedEndpointsEntry__fields[2] = {
  {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, 32, 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__endpoint__v3__ClusterLoadAssignment__NamedEndpointsEntry_msg_init = {
  &envoy_config_endpoint_v3_ClusterLoadAssignment_NamedEndpointsEntry__submsgs[0],
  &envoy_config_endpoint_v3_ClusterLoadAssignment_NamedEndpointsEntry__fields[0],
  48, 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.endpoint.v3.ClusterLoadAssignment.NamedEndpointsEntry",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
  })
};

const upb_MiniTable* envoy__config__endpoint__v3__ClusterLoadAssignment__NamedEndpointsEntry_msg_init_ptr = &envoy__config__endpoint__v3__ClusterLoadAssignment__NamedEndpointsEntry_msg_init;
static const upb_MiniTable *messages_layout[4] = {
  &envoy__config__endpoint__v3__ClusterLoadAssignment_msg_init,
  &envoy__config__endpoint__v3__ClusterLoadAssignment__Policy_msg_init,
  &envoy__config__endpoint__v3__ClusterLoadAssignment__Policy__DropOverload_msg_init,
  &envoy__config__endpoint__v3__ClusterLoadAssignment__NamedEndpointsEntry_msg_init,
};

const upb_MiniTableFile envoy_config_endpoint_v3_endpoint_proto_upb_file_layout = {
  messages_layout,
  NULL,
  NULL,
  4,
  0,
  0,
};

#include "upb/port/undef.inc"
