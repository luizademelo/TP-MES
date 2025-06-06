
#include <stddef.h>
#include "upb/generated_code_support.h"
#include "src/proto/grpc/lb/v1/load_balancer.upb_minitable.h"
#include "google/protobuf/duration.upb_minitable.h"
#include "google/protobuf/timestamp.upb_minitable.h"

#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
static const upb_MiniTableSubInternal grpc_lb_v1_LoadBalanceRequest__submsgs[2] = {
  {.UPB_PRIVATE(submsg) = &grpc__lb__v1__InitialLoadBalanceRequest_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &grpc__lb__v1__ClientStats_msg_init_ptr},
};

static const upb_MiniTableField grpc_lb_v1_LoadBalanceRequest__fields[2] = {
  {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable grpc__lb__v1__LoadBalanceRequest_msg_init = {
  &grpc_lb_v1_LoadBalanceRequest__submsgs[0],
  &grpc_lb_v1_LoadBalanceRequest__fields[0],
  UPB_SIZE(16, 24), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "grpc.lb.v1.LoadBalanceRequest",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000080100000a, &upb_pom_1bt_max64b},
    {0x0010000802010012, &upb_pom_1bt_max128b},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* grpc__lb__v1__LoadBalanceRequest_msg_init_ptr = &grpc__lb__v1__LoadBalanceRequest_msg_init;
static const upb_MiniTableField grpc_lb_v1_InitialLoadBalanceRequest__fields[1] = {
  {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
};

const upb_MiniTable grpc__lb__v1__InitialLoadBalanceRequest_msg_init = {
  NULL,
  &grpc_lb_v1_InitialLoadBalanceRequest__fields[0],
  UPB_SIZE(16, 24), 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "grpc.lb.v1.InitialLoadBalanceRequest",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f00000a, &upb_pss_1bt},
  })
};

const upb_MiniTable* grpc__lb__v1__InitialLoadBalanceRequest_msg_init_ptr = &grpc__lb__v1__InitialLoadBalanceRequest_msg_init;
static const upb_MiniTableField grpc_lb_v1_ClientStatsPerToken__fields[2] = {
  {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable grpc__lb__v1__ClientStatsPerToken_msg_init = {
  NULL,
  &grpc_lb_v1_ClientStatsPerToken__fields[0],
  UPB_SIZE(24, 32), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "grpc.lb.v1.ClientStatsPerToken",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f00000a, &upb_pss_1bt},
    {0x001800003f000010, &upb_psv8_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* grpc__lb__v1__ClientStatsPerToken_msg_init_ptr = &grpc__lb__v1__ClientStatsPerToken_msg_init;
static const upb_MiniTableSubInternal grpc_lb_v1_ClientStats__submsgs[2] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__Timestamp_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &grpc__lb__v1__ClientStatsPerToken_msg_init_ptr},
};

static const upb_MiniTableField grpc_lb_v1_ClientStats__fields[6] = {
  {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, 24, 0, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {3, 32, 0, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {6, 40, 0, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {7, 48, 0, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {8, UPB_SIZE(16, 56), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable grpc__lb__v1__ClientStats_msg_init = {
  &grpc_lb_v1_ClientStats__submsgs[0],
  &grpc_lb_v1_ClientStats__fields[0],
  UPB_SIZE(56, 64), 6, kUpb_ExtMode_NonExtendable, 3, UPB_FASTTABLE_MASK(120), 0,
#ifdef UPB_TRACING_ENABLED
  "grpc.lb.v1.ClientStats",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001800003f000010, &upb_psv8_1bt},
    {0x002000003f000018, &upb_psv8_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x002800003f000030, &upb_psv8_1bt},
    {0x003000003f000038, &upb_psv8_1bt},
    {0x003800003f010042, &upb_prm_1bt_max64b},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* grpc__lb__v1__ClientStats_msg_init_ptr = &grpc__lb__v1__ClientStats_msg_init;
static const upb_MiniTableSubInternal grpc_lb_v1_LoadBalanceResponse__submsgs[3] = {
  {.UPB_PRIVATE(submsg) = &grpc__lb__v1__InitialLoadBalanceResponse_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &grpc__lb__v1__ServerList_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &grpc__lb__v1__FallbackResponse_msg_init_ptr},
};

static const upb_MiniTableField grpc_lb_v1_LoadBalanceResponse__fields[3] = {
  {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(12, 16), -9, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable grpc__lb__v1__LoadBalanceResponse_msg_init = {
  &grpc_lb_v1_LoadBalanceResponse__submsgs[0],
  &grpc_lb_v1_LoadBalanceResponse__fields[0],
  UPB_SIZE(16, 24), 3, kUpb_ExtMode_NonExtendable, 3, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "grpc.lb.v1.LoadBalanceResponse",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000080100000a, &upb_pom_1bt_max64b},
    {0x0010000802010012, &upb_pom_1bt_max64b},
    {0x001000080302001a, &upb_pom_1bt_max64b},
  })
};

const upb_MiniTable* grpc__lb__v1__LoadBalanceResponse_msg_init_ptr = &grpc__lb__v1__LoadBalanceResponse_msg_init;
const upb_MiniTable grpc__lb__v1__FallbackResponse_msg_init = {
  NULL,
  NULL,
  8, 0, kUpb_ExtMode_NonExtendable, 0, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "grpc.lb.v1.FallbackResponse",
#endif
};

const upb_MiniTable* grpc__lb__v1__FallbackResponse_msg_init_ptr = &grpc__lb__v1__FallbackResponse_msg_init;
static const upb_MiniTableSubInternal grpc_lb_v1_InitialLoadBalanceResponse__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__Duration_msg_init_ptr},
};

static const upb_MiniTableField grpc_lb_v1_InitialLoadBalanceResponse__fields[1] = {
  {2, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable grpc__lb__v1__InitialLoadBalanceResponse_msg_init = {
  &grpc_lb_v1_InitialLoadBalanceResponse__submsgs[0],
  &grpc_lb_v1_InitialLoadBalanceResponse__fields[0],
  UPB_SIZE(16, 24), 1, kUpb_ExtMode_NonExtendable, 0, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "grpc.lb.v1.InitialLoadBalanceResponse",
#endif
};

const upb_MiniTable* grpc__lb__v1__InitialLoadBalanceResponse_msg_init_ptr = &grpc__lb__v1__InitialLoadBalanceResponse_msg_init;
static const upb_MiniTableSubInternal grpc_lb_v1_ServerList__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &grpc__lb__v1__Server_msg_init_ptr},
};

static const upb_MiniTableField grpc_lb_v1_ServerList__fields[1] = {
  {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable grpc__lb__v1__ServerList_msg_init = {
  &grpc_lb_v1_ServerList__submsgs[0],
  &grpc_lb_v1_ServerList__fields[0],
  16, 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "grpc.lb.v1.ServerList",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f00000a, &upb_prm_1bt_max64b},
  })
};

const upb_MiniTable* grpc__lb__v1__ServerList_msg_init_ptr = &grpc__lb__v1__ServerList_msg_init;
static const upb_MiniTableField grpc_lb_v1_Server__fields[4] = {
  {1, 16, 0, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, 12, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(24, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {4, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable grpc__lb__v1__Server_msg_init = {
  NULL,
  &grpc_lb_v1_Server__fields[0],
  UPB_SIZE(32, 48), 4, kUpb_ExtMode_NonExtendable, 4, UPB_FASTTABLE_MASK(56), 0,
#ifdef UPB_TRACING_ENABLED
  "grpc.lb.v1.Server",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_psb_1bt},
    {0x000c00003f000010, &upb_psv4_1bt},
    {0x002000003f00001a, &upb_pss_1bt},
    {0x000800003f000020, &upb_psb1_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* grpc__lb__v1__Server_msg_init_ptr = &grpc__lb__v1__Server_msg_init;
static const upb_MiniTable *messages_layout[9] = {
  &grpc__lb__v1__LoadBalanceRequest_msg_init,
  &grpc__lb__v1__InitialLoadBalanceRequest_msg_init,
  &grpc__lb__v1__ClientStatsPerToken_msg_init,
  &grpc__lb__v1__ClientStats_msg_init,
  &grpc__lb__v1__LoadBalanceResponse_msg_init,
  &grpc__lb__v1__FallbackResponse_msg_init,
  &grpc__lb__v1__InitialLoadBalanceResponse_msg_init,
  &grpc__lb__v1__ServerList_msg_init,
  &grpc__lb__v1__Server_msg_init,
};

const upb_MiniTableFile src_proto_grpc_lb_v1_load_balancer_proto_upb_file_layout = {
  messages_layout,
  NULL,
  NULL,
  9,
  0,
  0,
};

#include "upb/port/undef.inc"
