
#include <stddef.h>
#include "upb/generated_code_support.h"
#include "envoy/service/discovery/v3/discovery.upb_minitable.h"
#include "envoy/config/core/v3/base.upb_minitable.h"
#include "google/protobuf/any.upb_minitable.h"
#include "google/protobuf/duration.upb_minitable.h"
#include "google/rpc/status.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
static const upb_MiniTableSubInternal envoy_service_discovery_v3_ResourceLocator__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &envoy__service__discovery__v3__ResourceLocator__DynamicParametersEntry_msg_init_ptr},
};

static const upb_MiniTableField envoy_service_discovery_v3_ResourceLocator__fields[2] = {
  {1, UPB_SIZE(12, 8), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(8, 24), 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__service__discovery__v3__ResourceLocator_msg_init = {
  &envoy_service_discovery_v3_ResourceLocator__submsgs[0],
  &envoy_service_discovery_v3_ResourceLocator__fields[0],
  UPB_SIZE(24, 32), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.service.discovery.v3.ResourceLocator",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f00000a, &upb_pss_1bt},
  })
};

const upb_MiniTable* envoy__service__discovery__v3__ResourceLocator_msg_init_ptr = &envoy__service__discovery__v3__ResourceLocator_msg_init;
static const upb_MiniTableField envoy_service_discovery_v3_ResourceLocator_DynamicParametersEntry__fields[2] = {
  {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, 32, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__service__discovery__v3__ResourceLocator__DynamicParametersEntry_msg_init = {
  NULL,
  &envoy_service_discovery_v3_ResourceLocator_DynamicParametersEntry__fields[0],
  48, 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.service.discovery.v3.ResourceLocator.DynamicParametersEntry",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
    {0x002000003f000012, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__service__discovery__v3__ResourceLocator__DynamicParametersEntry_msg_init_ptr = &envoy__service__discovery__v3__ResourceLocator__DynamicParametersEntry_msg_init;
static const upb_MiniTableSubInternal envoy_service_discovery_v3_ResourceName__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &envoy__service__discovery__v3__DynamicParameterConstraints_msg_init_ptr},
};

static const upb_MiniTableField envoy_service_discovery_v3_ResourceName__fields[2] = {
  {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__service__discovery__v3__ResourceName_msg_init = {
  &envoy_service_discovery_v3_ResourceName__submsgs[0],
  &envoy_service_discovery_v3_ResourceName__fields[0],
  UPB_SIZE(24, 40), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.service.discovery.v3.ResourceName",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
  })
};

const upb_MiniTable* envoy__service__discovery__v3__ResourceName_msg_init_ptr = &envoy__service__discovery__v3__ResourceName_msg_init;
static const upb_MiniTableSubInternal envoy_service_discovery_v3_ResourceError__submsgs[2] = {
  {.UPB_PRIVATE(submsg) = &envoy__service__discovery__v3__ResourceName_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__rpc__Status_msg_init_ptr},
};

static const upb_MiniTableField envoy_service_discovery_v3_ResourceError__fields[2] = {
  {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__service__discovery__v3__ResourceError_msg_init = {
  &envoy_service_discovery_v3_ResourceError__submsgs[0],
  &envoy_service_discovery_v3_ResourceError__fields[0],
  UPB_SIZE(24, 32), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.service.discovery.v3.ResourceError",
#endif
};

const upb_MiniTable* envoy__service__discovery__v3__ResourceError_msg_init_ptr = &envoy__service__discovery__v3__ResourceError_msg_init;
static const upb_MiniTableSubInternal envoy_service_discovery_v3_DiscoveryRequest__submsgs[3] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__Node_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__rpc__Status_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__service__discovery__v3__ResourceLocator_msg_init_ptr},
};

static const upb_MiniTableField envoy_service_discovery_v3_DiscoveryRequest__fields[7] = {
  {1, UPB_SIZE(28, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 64), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(16, 72), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(36, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(44, 48), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {6, UPB_SIZE(20, 80), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {7, UPB_SIZE(24, 88), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__service__discovery__v3__DiscoveryRequest_msg_init = {
  &envoy_service_discovery_v3_DiscoveryRequest__submsgs[0],
  &envoy_service_discovery_v3_DiscoveryRequest__fields[0],
  UPB_SIZE(56, 96), 7, kUpb_ExtMode_NonExtendable, 7, UPB_FASTTABLE_MASK(56), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.service.discovery.v3.DiscoveryRequest",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x004800003f00001a, &upb_prs_1bt},
    {0x002000003f000022, &upb_pss_1bt},
    {0x003000003f00002a, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x005800003f02003a, &upb_prm_1bt_max64b},
  })
};

const upb_MiniTable* envoy__service__discovery__v3__DiscoveryRequest_msg_init_ptr = &envoy__service__discovery__v3__DiscoveryRequest_msg_init;
static const upb_MiniTableSubInternal envoy_service_discovery_v3_DiscoveryResponse__submsgs[3] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__Any_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__ControlPlane_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__service__discovery__v3__ResourceError_msg_init_ptr},
};

static const upb_MiniTableField envoy_service_discovery_v3_DiscoveryResponse__fields[7] = {
  {1, UPB_SIZE(24, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 64), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {4, 32, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(40, 48), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {6, UPB_SIZE(16, 72), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {7, UPB_SIZE(20, 80), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__service__discovery__v3__DiscoveryResponse_msg_init = {
  &envoy_service_discovery_v3_DiscoveryResponse__submsgs[0],
  &envoy_service_discovery_v3_DiscoveryResponse__fields[0],
  UPB_SIZE(48, 88), 7, kUpb_ExtMode_NonExtendable, 7, UPB_FASTTABLE_MASK(56), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.service.discovery.v3.DiscoveryResponse",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
    {0x004000003f000012, &upb_prm_1bt_maxmaxb},
    {0x000900003f000018, &upb_psb1_1bt},
    {0x002000003f000022, &upb_pss_1bt},
    {0x003000003f00002a, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x005000003f02003a, &upb_prm_1bt_max64b},
  })
};

const upb_MiniTable* envoy__service__discovery__v3__DiscoveryResponse_msg_init_ptr = &envoy__service__discovery__v3__DiscoveryResponse_msg_init;
static const upb_MiniTableSubInternal envoy_service_discovery_v3_DeltaDiscoveryRequest__submsgs[5] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__Node_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__service__discovery__v3__DeltaDiscoveryRequest__InitialResourceVersionsEntry_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__rpc__Status_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__service__discovery__v3__ResourceLocator_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__service__discovery__v3__ResourceLocator_msg_init_ptr},
};

static const upb_MiniTableField envoy_service_discovery_v3_DeltaDiscoveryRequest__fields[9] = {
  {1, UPB_SIZE(12, 48), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(40, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(16, 56), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(20, 64), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(24, 72), 0, 1, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {6, UPB_SIZE(48, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {7, UPB_SIZE(28, 80), 65, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {8, UPB_SIZE(32, 88), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {9, UPB_SIZE(36, 96), 0, 4, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__service__discovery__v3__DeltaDiscoveryRequest_msg_init = {
  &envoy_service_discovery_v3_DeltaDiscoveryRequest__submsgs[0],
  &envoy_service_discovery_v3_DeltaDiscoveryRequest__fields[0],
  UPB_SIZE(56, 104), 9, kUpb_ExtMode_NonExtendable, 9, UPB_FASTTABLE_MASK(120), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.service.discovery.v3.DeltaDiscoveryRequest",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f000012, &upb_pss_1bt},
    {0x003800003f00001a, &upb_prs_1bt},
    {0x004000003f000022, &upb_prs_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x002000003f000032, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x005800003f030042, &upb_prm_1bt_max64b},
    {0x006000003f04004a, &upb_prm_1bt_max64b},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__service__discovery__v3__DeltaDiscoveryRequest_msg_init_ptr = &envoy__service__discovery__v3__DeltaDiscoveryRequest_msg_init;
static const upb_MiniTableField envoy_service_discovery_v3_DeltaDiscoveryRequest_InitialResourceVersionsEntry__fields[2] = {
  {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, 32, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__service__discovery__v3__DeltaDiscoveryRequest__InitialResourceVersionsEntry_msg_init = {
  NULL,
  &envoy_service_discovery_v3_DeltaDiscoveryRequest_InitialResourceVersionsEntry__fields[0],
  48, 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.service.discovery.v3.DeltaDiscoveryRequest.InitialResourceVersionsEntry",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
    {0x002000003f000012, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__service__discovery__v3__DeltaDiscoveryRequest__InitialResourceVersionsEntry_msg_init_ptr = &envoy__service__discovery__v3__DeltaDiscoveryRequest__InitialResourceVersionsEntry_msg_init;
static const upb_MiniTableSubInternal envoy_service_discovery_v3_DeltaDiscoveryResponse__submsgs[4] = {
  {.UPB_PRIVATE(submsg) = &envoy__service__discovery__v3__Resource_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__ControlPlane_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__service__discovery__v3__ResourceName_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__service__discovery__v3__ResourceError_msg_init_ptr},
};

static const upb_MiniTableField envoy_service_discovery_v3_DeltaDiscoveryResponse__fields[8] = {
  {1, UPB_SIZE(32, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 64), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(40, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {5, 48, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {6, UPB_SIZE(16, 72), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {7, UPB_SIZE(20, 80), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {8, UPB_SIZE(24, 88), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {9, UPB_SIZE(28, 96), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__service__discovery__v3__DeltaDiscoveryResponse_msg_init = {
  &envoy_service_discovery_v3_DeltaDiscoveryResponse__submsgs[0],
  &envoy_service_discovery_v3_DeltaDiscoveryResponse__fields[0],
  UPB_SIZE(56, 104), 8, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(120), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.service.discovery.v3.DeltaDiscoveryResponse",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
    {0x004000003f000012, &upb_prm_1bt_max128b},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x002000003f000022, &upb_pss_1bt},
    {0x003000003f00002a, &upb_pss_1bt},
    {0x004800003f000032, &upb_prs_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x005800003f020042, &upb_prm_1bt_max64b},
    {0x006000003f03004a, &upb_prm_1bt_max64b},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__service__discovery__v3__DeltaDiscoveryResponse_msg_init_ptr = &envoy__service__discovery__v3__DeltaDiscoveryResponse_msg_init;
static const upb_MiniTableSubInternal envoy_service_discovery_v3_DynamicParameterConstraints__submsgs[4] = {
  {.UPB_PRIVATE(submsg) = &envoy__service__discovery__v3__DynamicParameterConstraints__SingleConstraint_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__service__discovery__v3__DynamicParameterConstraints__ConstraintList_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__service__discovery__v3__DynamicParameterConstraints__ConstraintList_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__service__discovery__v3__DynamicParameterConstraints_msg_init_ptr},
};

static const upb_MiniTableField envoy_service_discovery_v3_DynamicParameterConstraints__fields[4] = {
  {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(12, 16), -9, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(12, 16), -9, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__service__discovery__v3__DynamicParameterConstraints_msg_init = {
  &envoy_service_discovery_v3_DynamicParameterConstraints__submsgs[0],
  &envoy_service_discovery_v3_DynamicParameterConstraints__fields[0],
  UPB_SIZE(16, 24), 4, kUpb_ExtMode_NonExtendable, 4, UPB_FASTTABLE_MASK(56), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.service.discovery.v3.DynamicParameterConstraints",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000080100000a, &upb_pom_1bt_max64b},
    {0x0010000802010012, &upb_pom_1bt_max64b},
    {0x001000080302001a, &upb_pom_1bt_max64b},
    {0x0010000804030022, &upb_pom_1bt_max64b},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__service__discovery__v3__DynamicParameterConstraints_msg_init_ptr = &envoy__service__discovery__v3__DynamicParameterConstraints_msg_init;
static const upb_MiniTableSubInternal envoy_service_discovery_v3_DynamicParameterConstraints_SingleConstraint__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &envoy__service__discovery__v3__DynamicParameterConstraints__SingleConstraint__Exists_msg_init_ptr},
};

static const upb_MiniTableField envoy_service_discovery_v3_DynamicParameterConstraints_SingleConstraint__fields[3] = {
  {1, UPB_SIZE(12, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(20, 32), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(20, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__service__discovery__v3__DynamicParameterConstraints__SingleConstraint_msg_init = {
  &envoy_service_discovery_v3_DynamicParameterConstraints_SingleConstraint__submsgs[0],
  &envoy_service_discovery_v3_DynamicParameterConstraints_SingleConstraint__fields[0],
  UPB_SIZE(32, 48), 3, kUpb_ExtMode_NonExtendable, 3, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.service.discovery.v3.DynamicParameterConstraints.SingleConstraint",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
    {0x0020000802000012, &upb_pos_1bt},
    {0x002000080300001a, &upb_pom_1bt_max64b},
  })
};

const upb_MiniTable* envoy__service__discovery__v3__DynamicParameterConstraints__SingleConstraint_msg_init_ptr = &envoy__service__discovery__v3__DynamicParameterConstraints__SingleConstraint_msg_init;
const upb_MiniTable envoy__service__discovery__v3__DynamicParameterConstraints__SingleConstraint__Exists_msg_init = {
  NULL,
  NULL,
  8, 0, kUpb_ExtMode_NonExtendable, 0, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.service.discovery.v3.DynamicParameterConstraints.SingleConstraint.Exists",
#endif
};

const upb_MiniTable* envoy__service__discovery__v3__DynamicParameterConstraints__SingleConstraint__Exists_msg_init_ptr = &envoy__service__discovery__v3__DynamicParameterConstraints__SingleConstraint__Exists_msg_init;
static const upb_MiniTableSubInternal envoy_service_discovery_v3_DynamicParameterConstraints_ConstraintList__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &envoy__service__discovery__v3__DynamicParameterConstraints_msg_init_ptr},
};

static const upb_MiniTableField envoy_service_discovery_v3_DynamicParameterConstraints_ConstraintList__fields[1] = {
  {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__service__discovery__v3__DynamicParameterConstraints__ConstraintList_msg_init = {
  &envoy_service_discovery_v3_DynamicParameterConstraints_ConstraintList__submsgs[0],
  &envoy_service_discovery_v3_DynamicParameterConstraints_ConstraintList__fields[0],
  16, 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.service.discovery.v3.DynamicParameterConstraints.ConstraintList",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f00000a, &upb_prm_1bt_max64b},
  })
};

const upb_MiniTable* envoy__service__discovery__v3__DynamicParameterConstraints__ConstraintList_msg_init_ptr = &envoy__service__discovery__v3__DynamicParameterConstraints__ConstraintList_msg_init;
static const upb_MiniTableSubInternal envoy_service_discovery_v3_Resource__submsgs[5] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__Any_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__Duration_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__service__discovery__v3__Resource__CacheControl_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__service__discovery__v3__ResourceName_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__Metadata_msg_init_ptr},
};

static const upb_MiniTableField envoy_service_discovery_v3_Resource__fields[8] = {
  {1, UPB_SIZE(36, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 48), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(44, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(16, 56), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {6, UPB_SIZE(20, 64), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {7, UPB_SIZE(24, 72), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {8, UPB_SIZE(28, 80), 67, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {9, UPB_SIZE(32, 88), 68, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__service__discovery__v3__Resource_msg_init = {
  &envoy_service_discovery_v3_Resource__submsgs[0],
  &envoy_service_discovery_v3_Resource__fields[0],
  UPB_SIZE(56, 96), 8, kUpb_ExtMode_NonExtendable, 4, UPB_FASTTABLE_MASK(56), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.service.discovery.v3.Resource",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x002000003f00001a, &upb_pss_1bt},
    {0x003800003f000022, &upb_prs_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__service__discovery__v3__Resource_msg_init_ptr = &envoy__service__discovery__v3__Resource_msg_init;
static const upb_MiniTableField envoy_service_discovery_v3_Resource_CacheControl__fields[1] = {
  {1, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__service__discovery__v3__Resource__CacheControl_msg_init = {
  NULL,
  &envoy_service_discovery_v3_Resource_CacheControl__fields[0],
  16, 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.service.discovery.v3.Resource.CacheControl",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f000008, &upb_psb1_1bt},
  })
};

const upb_MiniTable* envoy__service__discovery__v3__Resource__CacheControl_msg_init_ptr = &envoy__service__discovery__v3__Resource__CacheControl_msg_init;
static const upb_MiniTable *messages_layout[15] = {
  &envoy__service__discovery__v3__ResourceLocator_msg_init,
  &envoy__service__discovery__v3__ResourceLocator__DynamicParametersEntry_msg_init,
  &envoy__service__discovery__v3__ResourceName_msg_init,
  &envoy__service__discovery__v3__ResourceError_msg_init,
  &envoy__service__discovery__v3__DiscoveryRequest_msg_init,
  &envoy__service__discovery__v3__DiscoveryResponse_msg_init,
  &envoy__service__discovery__v3__DeltaDiscoveryRequest_msg_init,
  &envoy__service__discovery__v3__DeltaDiscoveryRequest__InitialResourceVersionsEntry_msg_init,
  &envoy__service__discovery__v3__DeltaDiscoveryResponse_msg_init,
  &envoy__service__discovery__v3__DynamicParameterConstraints_msg_init,
  &envoy__service__discovery__v3__DynamicParameterConstraints__SingleConstraint_msg_init,
  &envoy__service__discovery__v3__DynamicParameterConstraints__SingleConstraint__Exists_msg_init,
  &envoy__service__discovery__v3__DynamicParameterConstraints__ConstraintList_msg_init,
  &envoy__service__discovery__v3__Resource_msg_init,
  &envoy__service__discovery__v3__Resource__CacheControl_msg_init,
};

const upb_MiniTableFile envoy_service_discovery_v3_discovery_proto_upb_file_layout = {
  messages_layout,
  NULL,
  NULL,
  15,
  0,
  0,
};

#include "upb/port/undef.inc"
