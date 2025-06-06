
#include <stddef.h>
#include "upb/generated_code_support.h"
#include "envoy/service/load_stats/v3/lrs.upb_minitable.h"
#include "envoy/config/core/v3/base.upb_minitable.h"
#include "envoy/config/endpoint/v3/load_report.upb_minitable.h"
#include "google/protobuf/duration.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"

#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
static const upb_MiniTableSubInternal envoy_service_load_stats_v3_LoadStatsRequest__submsgs[2] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__Node_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__endpoint__v3__ClusterStats_msg_init_ptr},
};

static const upb_MiniTableField envoy_service_load_stats_v3_LoadStatsRequest__fields[2] = {
  {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 24), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__service__load_0stats__v3__LoadStatsRequest_msg_init = {
  &envoy_service_load_stats_v3_LoadStatsRequest__submsgs[0],
  &envoy_service_load_stats_v3_LoadStatsRequest__fields[0],
  UPB_SIZE(24, 32), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.service.load_stats.v3.LoadStatsRequest",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001800003f010012, &upb_prm_1bt_maxmaxb},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__service__load_0stats__v3__LoadStatsRequest_msg_init_ptr = &envoy__service__load_0stats__v3__LoadStatsRequest_msg_init;
static const upb_MiniTableSubInternal envoy_service_load_stats_v3_LoadStatsResponse__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__Duration_msg_init_ptr},
};

static const upb_MiniTableField envoy_service_load_stats_v3_LoadStatsResponse__fields[4] = {
  {1, UPB_SIZE(12, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 24), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {4, 10, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__service__load_0stats__v3__LoadStatsResponse_msg_init = {
  &envoy_service_load_stats_v3_LoadStatsResponse__submsgs[0],
  &envoy_service_load_stats_v3_LoadStatsResponse__fields[0],
  UPB_SIZE(24, 32), 4, kUpb_ExtMode_NonExtendable, 4, UPB_FASTTABLE_MASK(56), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.service.load_stats.v3.LoadStatsResponse",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_prs_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000900003f000018, &upb_psb1_1bt},
    {0x000a00003f000020, &upb_psb1_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__service__load_0stats__v3__LoadStatsResponse_msg_init_ptr = &envoy__service__load_0stats__v3__LoadStatsResponse_msg_init;
static const upb_MiniTable *messages_layout[2] = {
  &envoy__service__load_0stats__v3__LoadStatsRequest_msg_init,
  &envoy__service__load_0stats__v3__LoadStatsResponse_msg_init,
};

const upb_MiniTableFile envoy_service_load_stats_v3_lrs_proto_upb_file_layout = {
  messages_layout,
  NULL,
  NULL,
  2,
  0,
  0,
};

#include "upb/port/undef.inc"
