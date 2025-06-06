
#include <stddef.h>
#include "upb/generated_code_support.h"
#include "envoy/admin/v3/clusters.upb_minitable.h"
#include "envoy/admin/v3/metrics.upb_minitable.h"
#include "envoy/config/cluster/v3/circuit_breaker.upb_minitable.h"
#include "envoy/config/core/v3/address.upb_minitable.h"
#include "envoy/config/core/v3/base.upb_minitable.h"
#include "envoy/config/core/v3/health_check.upb_minitable.h"
#include "envoy/type/v3/percent.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"

#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
static const upb_MiniTableSubInternal envoy_admin_v3_Clusters__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &envoy__admin__v3__ClusterStatus_msg_init_ptr},
};

static const upb_MiniTableField envoy_admin_v3_Clusters__fields[1] = {
  {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__admin__v3__Clusters_msg_init = {
  &envoy_admin_v3_Clusters__submsgs[0],
  &envoy_admin_v3_Clusters__fields[0],
  16, 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.admin.v3.Clusters",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f00000a, &upb_prm_1bt_max128b},
  })
};

const upb_MiniTable* envoy__admin__v3__Clusters_msg_init_ptr = &envoy__admin__v3__Clusters_msg_init;
static const upb_MiniTableSubInternal envoy_admin_v3_ClusterStatus__submsgs[4] = {
  {.UPB_PRIVATE(submsg) = &envoy__type__v3__Percent_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__admin__v3__HostStatus_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__type__v3__Percent_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__cluster__v3__CircuitBreakers_msg_init_ptr},
};

static const upb_MiniTableField envoy_admin_v3_ClusterStatus__fields[8] = {
  {1, UPB_SIZE(28, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(12, 64), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(16, 72), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(20, 80), 65, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {6, UPB_SIZE(24, 88), 66, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {7, UPB_SIZE(36, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {8, UPB_SIZE(44, 48), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__admin__v3__ClusterStatus_msg_init = {
  &envoy_admin_v3_ClusterStatus__submsgs[0],
  &envoy_admin_v3_ClusterStatus__fields[0],
  UPB_SIZE(56, 96), 8, kUpb_ExtMode_NonExtendable, 8, UPB_FASTTABLE_MASK(120), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.admin.v3.ClusterStatus",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
    {0x000900003f000010, &upb_psb1_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x004800003f010022, &upb_prm_1bt_max128b},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x002000003f00003a, &upb_pss_1bt},
    {0x003000003f000042, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__admin__v3__ClusterStatus_msg_init_ptr = &envoy__admin__v3__ClusterStatus_msg_init;
static const upb_MiniTableSubInternal envoy_admin_v3_HostStatus__submsgs[6] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__Address_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__admin__v3__SimpleMetric_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__admin__v3__HostHealthStatus_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__type__v3__Percent_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__type__v3__Percent_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__Locality_msg_init_ptr},
};

static const upb_MiniTableField envoy_admin_v3_HostStatus__fields[9] = {
  {1, UPB_SIZE(12, 40), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 48), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(20, 56), 65, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(24, 64), 66, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(28, 12), 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {6, UPB_SIZE(44, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {7, UPB_SIZE(32, 16), 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {8, UPB_SIZE(36, 72), 67, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {9, UPB_SIZE(40, 80), 68, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__admin__v3__HostStatus_msg_init = {
  &envoy_admin_v3_HostStatus__submsgs[0],
  &envoy_admin_v3_HostStatus__fields[0],
  UPB_SIZE(56, 88), 9, kUpb_ExtMode_NonExtendable, 9, UPB_FASTTABLE_MASK(56), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.admin.v3.HostStatus",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x003000003f010012, &upb_prm_1bt_maxmaxb},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000c00003f000028, &upb_psv4_1bt},
    {0x001800003f000032, &upb_pss_1bt},
    {0x001000003f000038, &upb_psv4_1bt},
  })
};

const upb_MiniTable* envoy__admin__v3__HostStatus_msg_init_ptr = &envoy__admin__v3__HostStatus_msg_init;
static const upb_MiniTableField envoy_admin_v3_HostHealthStatus__fields[8] = {
  {1, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {2, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {3, 16, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {4, 10, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {5, 11, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {6, 12, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {7, 13, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {8, 14, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__admin__v3__HostHealthStatus_msg_init = {
  NULL,
  &envoy_admin_v3_HostHealthStatus__fields[0],
  24, 8, kUpb_ExtMode_NonExtendable, 8, UPB_FASTTABLE_MASK(120), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.admin.v3.HostHealthStatus",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f000008, &upb_psb1_1bt},
    {0x000900003f000010, &upb_psb1_1bt},
    {0x001000003f000018, &upb_psv4_1bt},
    {0x000a00003f000020, &upb_psb1_1bt},
    {0x000b00003f000028, &upb_psb1_1bt},
    {0x000c00003f000030, &upb_psb1_1bt},
    {0x000d00003f000038, &upb_psb1_1bt},
    {0x000e00003f000040, &upb_psb1_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__admin__v3__HostHealthStatus_msg_init_ptr = &envoy__admin__v3__HostHealthStatus_msg_init;
static const upb_MiniTable *messages_layout[4] = {
  &envoy__admin__v3__Clusters_msg_init,
  &envoy__admin__v3__ClusterStatus_msg_init,
  &envoy__admin__v3__HostStatus_msg_init,
  &envoy__admin__v3__HostHealthStatus_msg_init,
};

const upb_MiniTableFile envoy_admin_v3_clusters_proto_upb_file_layout = {
  messages_layout,
  NULL,
  NULL,
  4,
  0,
  0,
};

#include "upb/port/undef.inc"
