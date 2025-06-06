
#include <stddef.h>
#include "upb/generated_code_support.h"
#include "src/proto/grpc/gcp/handshaker.upb_minitable.h"
#include "src/proto/grpc/gcp/transport_security_common.upb_minitable.h"

#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
static const upb_MiniTableField grpc_gcp_Endpoint__fields[3] = {
  {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, 8, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {3, 12, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable grpc__gcp__Endpoint_msg_init = {
  NULL,
  &grpc_gcp_Endpoint__fields[0],
  UPB_SIZE(24, 32), 3, kUpb_ExtMode_NonExtendable, 3, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "grpc.gcp.Endpoint",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
    {0x000800003f000010, &upb_psv4_1bt},
    {0x000c00003f000018, &upb_psv4_1bt},
  })
};

const upb_MiniTable* grpc__gcp__Endpoint_msg_init_ptr = &grpc__gcp__Endpoint_msg_init;
static const upb_MiniTableSubInternal grpc_gcp_Identity__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &grpc__gcp__Identity__AttributesEntry_msg_init_ptr},
};

static const upb_MiniTableField grpc_gcp_Identity__fields[3] = {
  {1, 16, UPB_SIZE(-13, -9), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, 16, UPB_SIZE(-13, -9), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(8, 32), 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable grpc__gcp__Identity_msg_init = {
  &grpc_gcp_Identity__submsgs[0],
  &grpc_gcp_Identity__fields[0],
  UPB_SIZE(24, 40), 3, kUpb_ExtMode_NonExtendable, 3, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "grpc.gcp.Identity",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000080100000a, &upb_pos_1bt},
    {0x0010000802000012, &upb_pos_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* grpc__gcp__Identity_msg_init_ptr = &grpc__gcp__Identity_msg_init;
static const upb_MiniTableField grpc_gcp_Identity_AttributesEntry__fields[2] = {
  {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, 32, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
};

const upb_MiniTable grpc__gcp__Identity__AttributesEntry_msg_init = {
  NULL,
  &grpc_gcp_Identity_AttributesEntry__fields[0],
  48, 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "grpc.gcp.Identity.AttributesEntry",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
    {0x002000003f000012, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* grpc__gcp__Identity__AttributesEntry_msg_init_ptr = &grpc__gcp__Identity__AttributesEntry_msg_init;
static const upb_MiniTableSubInternal grpc_gcp_StartClientHandshakeReq__submsgs[6] = {
  {.UPB_PRIVATE(submsg) = &grpc__gcp__Identity_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &grpc__gcp__Identity_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &grpc__gcp__Endpoint_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &grpc__gcp__Endpoint_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &grpc__gcp__RpcProtocolVersions_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &grpc__gcp__TransportProtocolPreferences_msg_init_ptr},
};

static const upb_MiniTableField grpc_gcp_StartClientHandshakeReq__fields[11] = {
  {1, 12, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 40), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(20, 48), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(24, 56), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(28, 64), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {6, UPB_SIZE(32, 72), 65, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {7, UPB_SIZE(36, 80), 66, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {8, UPB_SIZE(52, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {9, UPB_SIZE(40, 88), 67, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {10, UPB_SIZE(44, 16), 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {12, UPB_SIZE(48, 96), 68, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable grpc__gcp__StartClientHandshakeReq_msg_init = {
  &grpc_gcp_StartClientHandshakeReq__submsgs[0],
  &grpc_gcp_StartClientHandshakeReq__fields[0],
  UPB_SIZE(64, 104), 11, kUpb_ExtMode_NonExtendable, 10, UPB_FASTTABLE_MASK(120), 0,
#ifdef UPB_TRACING_ENABLED
  "grpc.gcp.StartClientHandshakeReq",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000c00003f000008, &upb_psv4_1bt},
    {0x002800003f000012, &upb_prs_1bt},
    {0x003000003f00001a, &upb_prs_1bt},
    {0x003800003f000022, &upb_prm_1bt_max64b},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001800003f000042, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f000050, &upb_psv4_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* grpc__gcp__StartClientHandshakeReq_msg_init_ptr = &grpc__gcp__StartClientHandshakeReq_msg_init;
static const upb_MiniTableSubInternal grpc_gcp_ServerHandshakeParameters__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &grpc__gcp__Identity_msg_init_ptr},
};

static const upb_MiniTableField grpc_gcp_ServerHandshakeParameters__fields[2] = {
  {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable grpc__gcp__ServerHandshakeParameters_msg_init = {
  &grpc_gcp_ServerHandshakeParameters__submsgs[0],
  &grpc_gcp_ServerHandshakeParameters__fields[0],
  UPB_SIZE(16, 24), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "grpc.gcp.ServerHandshakeParameters",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f00000a, &upb_prs_1bt},
    {0x001000003f000012, &upb_prm_1bt_max64b},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* grpc__gcp__ServerHandshakeParameters_msg_init_ptr = &grpc__gcp__ServerHandshakeParameters_msg_init;
static const upb_MiniTableSubInternal grpc_gcp_StartServerHandshakeReq__submsgs[5] = {
  {.UPB_PRIVATE(submsg) = &grpc__gcp__StartServerHandshakeReq__HandshakeParametersEntry_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &grpc__gcp__Endpoint_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &grpc__gcp__Endpoint_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &grpc__gcp__RpcProtocolVersions_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &grpc__gcp__TransportProtocolPreferences_msg_init_ptr},
};

static const upb_MiniTableField grpc_gcp_StartServerHandshakeReq__fields[8] = {
  {1, UPB_SIZE(12, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 40), 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(40, 16), 0, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(20, 48), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(24, 56), 65, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {6, UPB_SIZE(28, 64), 66, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {7, UPB_SIZE(32, 12), 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {8, UPB_SIZE(36, 72), 67, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable grpc__gcp__StartServerHandshakeReq_msg_init = {
  &grpc_gcp_StartServerHandshakeReq__submsgs[0],
  &grpc_gcp_StartServerHandshakeReq__fields[0],
  UPB_SIZE(48, 80), 8, kUpb_ExtMode_NonExtendable, 8, UPB_FASTTABLE_MASK(56), 0,
#ifdef UPB_TRACING_ENABLED
  "grpc.gcp.StartServerHandshakeReq",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x002000003f00000a, &upb_prs_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00001a, &upb_psb_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000c00003f000038, &upb_psv4_1bt},
  })
};

const upb_MiniTable* grpc__gcp__StartServerHandshakeReq_msg_init_ptr = &grpc__gcp__StartServerHandshakeReq_msg_init;
static const upb_MiniTableSubInternal grpc_gcp_StartServerHandshakeReq_HandshakeParametersEntry__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &grpc__gcp__ServerHandshakeParameters_msg_init_ptr},
};

static const upb_MiniTableField grpc_gcp_StartServerHandshakeReq_HandshakeParametersEntry__fields[2] = {
  {1, 16, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {2, 32, 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable grpc__gcp__StartServerHandshakeReq__HandshakeParametersEntry_msg_init = {
  &grpc_gcp_StartServerHandshakeReq_HandshakeParametersEntry__submsgs[0],
  &grpc_gcp_StartServerHandshakeReq_HandshakeParametersEntry__fields[0],
  48, 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "grpc.gcp.StartServerHandshakeReq.HandshakeParametersEntry",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f000008, &upb_psv4_1bt},
  })
};

const upb_MiniTable* grpc__gcp__StartServerHandshakeReq__HandshakeParametersEntry_msg_init_ptr = &grpc__gcp__StartServerHandshakeReq__HandshakeParametersEntry_msg_init;
static const upb_MiniTableField grpc_gcp_NextHandshakeMessageReq__fields[1] = {
  {1, 8, 0, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
};

const upb_MiniTable grpc__gcp__NextHandshakeMessageReq_msg_init = {
  NULL,
  &grpc_gcp_NextHandshakeMessageReq__fields[0],
  UPB_SIZE(16, 24), 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "grpc.gcp.NextHandshakeMessageReq",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f00000a, &upb_psb_1bt},
  })
};

const upb_MiniTable* grpc__gcp__NextHandshakeMessageReq_msg_init_ptr = &grpc__gcp__NextHandshakeMessageReq_msg_init;
static const upb_MiniTableSubInternal grpc_gcp_HandshakerReq__submsgs[3] = {
  {.UPB_PRIVATE(submsg) = &grpc__gcp__StartClientHandshakeReq_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &grpc__gcp__StartServerHandshakeReq_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &grpc__gcp__NextHandshakeMessageReq_msg_init_ptr},
};

static const upb_MiniTableField grpc_gcp_HandshakerReq__fields[3] = {
  {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(12, 16), -9, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable grpc__gcp__HandshakerReq_msg_init = {
  &grpc_gcp_HandshakerReq__submsgs[0],
  &grpc_gcp_HandshakerReq__fields[0],
  UPB_SIZE(16, 24), 3, kUpb_ExtMode_NonExtendable, 3, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "grpc.gcp.HandshakerReq",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000080100000a, &upb_pom_1bt_max128b},
    {0x0010000802010012, &upb_pom_1bt_max128b},
    {0x001000080302001a, &upb_pom_1bt_max64b},
  })
};

const upb_MiniTable* grpc__gcp__HandshakerReq_msg_init_ptr = &grpc__gcp__HandshakerReq_msg_init;
static const upb_MiniTableSubInternal grpc_gcp_HandshakerResult__submsgs[4] = {
  {.UPB_PRIVATE(submsg) = &grpc__gcp__Identity_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &grpc__gcp__Identity_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &grpc__gcp__RpcProtocolVersions_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &grpc__gcp__NegotiatedTransportProtocol_msg_init_ptr},
};

static const upb_MiniTableField grpc_gcp_HandshakerResult__fields[9] = {
  {1, UPB_SIZE(32, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(40, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {3, 48, 0, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(12, 64), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(16, 72), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {6, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {7, UPB_SIZE(20, 80), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {8, UPB_SIZE(24, 12), 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {9, UPB_SIZE(28, 88), 67, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable grpc__gcp__HandshakerResult_msg_init = {
  &grpc_gcp_HandshakerResult__submsgs[0],
  &grpc_gcp_HandshakerResult__fields[0],
  UPB_SIZE(56, 96), 9, kUpb_ExtMode_NonExtendable, 9, UPB_FASTTABLE_MASK(120), 0,
#ifdef UPB_TRACING_ENABLED
  "grpc.gcp.HandshakerResult",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
    {0x002000003f000012, &upb_pss_1bt},
    {0x003000003f00001a, &upb_psb_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000900003f000030, &upb_psb1_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000c00003f000040, &upb_psv4_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* grpc__gcp__HandshakerResult_msg_init_ptr = &grpc__gcp__HandshakerResult_msg_init;
static const upb_MiniTableField grpc_gcp_HandshakerStatus__fields[2] = {
  {1, 8, 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
};

const upb_MiniTable grpc__gcp__HandshakerStatus_msg_init = {
  NULL,
  &grpc_gcp_HandshakerStatus__fields[0],
  UPB_SIZE(24, 32), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "grpc.gcp.HandshakerStatus",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f000008, &upb_psv4_1bt},
    {0x001000003f000012, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* grpc__gcp__HandshakerStatus_msg_init_ptr = &grpc__gcp__HandshakerStatus_msg_init;
static const upb_MiniTableSubInternal grpc_gcp_HandshakerResp__submsgs[2] = {
  {.UPB_PRIVATE(submsg) = &grpc__gcp__HandshakerResult_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &grpc__gcp__HandshakerStatus_msg_init_ptr},
};

static const upb_MiniTableField grpc_gcp_HandshakerResp__fields[4] = {
  {1, UPB_SIZE(24, 16), 0, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, 12, 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(16, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(20, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable grpc__gcp__HandshakerResp_msg_init = {
  &grpc_gcp_HandshakerResp__submsgs[0],
  &grpc_gcp_HandshakerResp__fields[0],
  UPB_SIZE(32, 48), 4, kUpb_ExtMode_NonExtendable, 4, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "grpc.gcp.HandshakerResp",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_psb_1bt},
    {0x000c00003f000010, &upb_psv4_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* grpc__gcp__HandshakerResp_msg_init_ptr = &grpc__gcp__HandshakerResp_msg_init;
static const upb_MiniTable *messages_layout[12] = {
  &grpc__gcp__Endpoint_msg_init,
  &grpc__gcp__Identity_msg_init,
  &grpc__gcp__Identity__AttributesEntry_msg_init,
  &grpc__gcp__StartClientHandshakeReq_msg_init,
  &grpc__gcp__ServerHandshakeParameters_msg_init,
  &grpc__gcp__StartServerHandshakeReq_msg_init,
  &grpc__gcp__StartServerHandshakeReq__HandshakeParametersEntry_msg_init,
  &grpc__gcp__NextHandshakeMessageReq_msg_init,
  &grpc__gcp__HandshakerReq_msg_init,
  &grpc__gcp__HandshakerResult_msg_init,
  &grpc__gcp__HandshakerStatus_msg_init,
  &grpc__gcp__HandshakerResp_msg_init,
};

const upb_MiniTableFile src_proto_grpc_gcp_handshaker_proto_upb_file_layout = {
  messages_layout,
  NULL,
  NULL,
  12,
  0,
  0,
};

#include "upb/port/undef.inc"
