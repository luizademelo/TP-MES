
#include <stddef.h>
#include "upb/generated_code_support.h"
#include "envoy/service/status/v3/csds.upb_minitable.h"
#include "envoy/admin/v3/config_dump_shared.upb_minitable.h"
#include "envoy/config/core/v3/base.upb_minitable.h"
#include "envoy/type/matcher/v3/node.upb_minitable.h"
#include "google/api/annotations.upb_minitable.h"
#include "google/protobuf/any.upb_minitable.h"
#include "google/protobuf/timestamp.upb_minitable.h"
#include "envoy/annotations/deprecation.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"

#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
static const upb_MiniTableSubInternal envoy_service_status_v3_ClientStatusRequest__submsgs[2] = {
  {.UPB_PRIVATE(submsg) = &envoy__type__matcher__v3__NodeMatcher_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__Node_msg_init_ptr},
};

static const upb_MiniTableField envoy_service_status_v3_ClientStatusRequest__fields[3] = {
  {1, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 24), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__service__status__v3__ClientStatusRequest_msg_init = {
  &envoy_service_status_v3_ClientStatusRequest__submsgs[0],
  &envoy_service_status_v3_ClientStatusRequest__fields[0],
  UPB_SIZE(24, 32), 3, kUpb_ExtMode_NonExtendable, 3, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.service.status.v3.ClientStatusRequest",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_prm_1bt_maxmaxb},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000900003f000018, &upb_psb1_1bt},
  })
};

const upb_MiniTable* envoy__service__status__v3__ClientStatusRequest_msg_init_ptr = &envoy__service__status__v3__ClientStatusRequest_msg_init;
static const upb_MiniTableSubInternal envoy_service_status_v3_PerXdsConfig__submsgs[5] = {
  {.UPB_PRIVATE(submsg) = &envoy__admin__v3__ListenersConfigDump_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__admin__v3__ClustersConfigDump_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__admin__v3__RoutesConfigDump_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__admin__v3__ScopedRoutesConfigDump_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__admin__v3__EndpointsConfigDump_msg_init_ptr},
};

static const upb_MiniTableField envoy_service_status_v3_PerXdsConfig__fields[7] = {
  {1, 8, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(20, 24), -17, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(20, 24), -17, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(20, 24), -17, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(20, 24), -17, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {6, UPB_SIZE(20, 24), -17, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {7, 12, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__service__status__v3__PerXdsConfig_msg_init = {
  &envoy_service_status_v3_PerXdsConfig__submsgs[0],
  &envoy_service_status_v3_PerXdsConfig__fields[0],
  UPB_SIZE(24, 32), 7, kUpb_ExtMode_NonExtendable, 7, UPB_FASTTABLE_MASK(56), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.service.status.v3.PerXdsConfig",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f000008, &upb_psv4_1bt},
    {0x0018001002000012, &upb_pom_1bt_maxmaxb},
    {0x001800100301001a, &upb_pom_1bt_maxmaxb},
    {0x0018001004020022, &upb_pom_1bt_maxmaxb},
    {0x001800100503002a, &upb_pom_1bt_maxmaxb},
    {0x0018001006040032, &upb_pom_1bt_maxmaxb},
    {0x000c00003f000038, &upb_psv4_1bt},
  })
};

const upb_MiniTable* envoy__service__status__v3__PerXdsConfig_msg_init_ptr = &envoy__service__status__v3__PerXdsConfig_msg_init;
static const upb_MiniTableSubInternal envoy_service_status_v3_ClientConfig__submsgs[3] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__Node_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__service__status__v3__PerXdsConfig_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__service__status__v3__ClientConfig__GenericXdsConfig_msg_init_ptr},
};

static const upb_MiniTableField envoy_service_status_v3_ClientConfig__fields[4] = {
  {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 40), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(20, 48), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(24, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__service__status__v3__ClientConfig_msg_init = {
  &envoy_service_status_v3_ClientConfig__submsgs[0],
  &envoy_service_status_v3_ClientConfig__fields[0],
  UPB_SIZE(32, 56), 4, kUpb_ExtMode_NonExtendable, 4, UPB_FASTTABLE_MASK(56), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.service.status.v3.ClientConfig",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x002800003f010012, &upb_prm_1bt_max64b},
    {0x003000003f02001a, &upb_prm_1bt_max128b},
    {0x001000003f000022, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__service__status__v3__ClientConfig_msg_init_ptr = &envoy__service__status__v3__ClientConfig_msg_init;
static const upb_MiniTableSubInternal envoy_service_status_v3_ClientConfig_GenericXdsConfig__submsgs[3] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__Any_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__Timestamp_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__admin__v3__UpdateFailureState_msg_init_ptr},
};

static const upb_MiniTableField envoy_service_status_v3_ClientConfig_GenericXdsConfig__fields[9] = {
  {1, UPB_SIZE(32, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, 40, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(48, 56), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(12, 72), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(16, 80), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {6, UPB_SIZE(20, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {7, UPB_SIZE(24, 16), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {8, UPB_SIZE(28, 88), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {9, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__service__status__v3__ClientConfig__GenericXdsConfig_msg_init = {
  &envoy_service_status_v3_ClientConfig_GenericXdsConfig__submsgs[0],
  &envoy_service_status_v3_ClientConfig_GenericXdsConfig__fields[0],
  UPB_SIZE(56, 96), 9, kUpb_ExtMode_NonExtendable, 9, UPB_FASTTABLE_MASK(120), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.service.status.v3.ClientConfig.GenericXdsConfig",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001800003f00000a, &upb_pss_1bt},
    {0x002800003f000012, &upb_pss_1bt},
    {0x003800003f00001a, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000c00003f000030, &upb_psv4_1bt},
    {0x001000003f000038, &upb_psv4_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000900003f000048, &upb_psb1_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__service__status__v3__ClientConfig__GenericXdsConfig_msg_init_ptr = &envoy__service__status__v3__ClientConfig__GenericXdsConfig_msg_init;
static const upb_MiniTableSubInternal envoy_service_status_v3_ClientStatusResponse__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &envoy__service__status__v3__ClientConfig_msg_init_ptr},
};

static const upb_MiniTableField envoy_service_status_v3_ClientStatusResponse__fields[1] = {
  {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__service__status__v3__ClientStatusResponse_msg_init = {
  &envoy_service_status_v3_ClientStatusResponse__submsgs[0],
  &envoy_service_status_v3_ClientStatusResponse__fields[0],
  16, 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.service.status.v3.ClientStatusResponse",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f00000a, &upb_prm_1bt_max64b},
  })
};

const upb_MiniTable* envoy__service__status__v3__ClientStatusResponse_msg_init_ptr = &envoy__service__status__v3__ClientStatusResponse_msg_init;
static const upb_MiniTable *messages_layout[5] = {
  &envoy__service__status__v3__ClientStatusRequest_msg_init,
  &envoy__service__status__v3__PerXdsConfig_msg_init,
  &envoy__service__status__v3__ClientConfig_msg_init,
  &envoy__service__status__v3__ClientConfig__GenericXdsConfig_msg_init,
  &envoy__service__status__v3__ClientStatusResponse_msg_init,
};

const upb_MiniTableFile envoy_service_status_v3_csds_proto_upb_file_layout = {
  messages_layout,
  NULL,
  NULL,
  5,
  0,
  0,
};

#include "upb/port/undef.inc"
