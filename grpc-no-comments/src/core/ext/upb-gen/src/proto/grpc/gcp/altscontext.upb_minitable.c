
#include <stddef.h>
#include "upb/generated_code_support.h"
#include "src/proto/grpc/gcp/altscontext.upb_minitable.h"
#include "src/proto/grpc/gcp/transport_security_common.upb_minitable.h"

#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
static const upb_MiniTableSubInternal grpc_gcp_AltsContext__submsgs[2] = {
  {.UPB_PRIVATE(submsg) = &grpc__gcp__RpcProtocolVersions_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &grpc__gcp__AltsContext__PeerAttributesEntry_msg_init_ptr},
};

static const upb_MiniTableField grpc_gcp_AltsContext__fields[7] = {
  {1, UPB_SIZE(24, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, 32, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {3, 12, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(40, 48), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(48, 64), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {6, UPB_SIZE(16, 80), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {7, UPB_SIZE(20, 88), 0, 1, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable grpc__gcp__AltsContext_msg_init = {
  &grpc_gcp_AltsContext__submsgs[0],
  &grpc_gcp_AltsContext__fields[0],
  UPB_SIZE(56, 96), 7, kUpb_ExtMode_NonExtendable, 7, UPB_FASTTABLE_MASK(56), 0,
#ifdef UPB_TRACING_ENABLED
  "grpc.gcp.AltsContext",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
    {0x002000003f000012, &upb_pss_1bt},
    {0x000c00003f000018, &upb_psv4_1bt},
    {0x003000003f000022, &upb_pss_1bt},
    {0x004000003f00002a, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* grpc__gcp__AltsContext_msg_init_ptr = &grpc__gcp__AltsContext_msg_init;
static const upb_MiniTableField grpc_gcp_AltsContext_PeerAttributesEntry__fields[2] = {
  {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, 32, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
};

const upb_MiniTable grpc__gcp__AltsContext__PeerAttributesEntry_msg_init = {
  NULL,
  &grpc_gcp_AltsContext_PeerAttributesEntry__fields[0],
  48, 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "grpc.gcp.AltsContext.PeerAttributesEntry",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
    {0x002000003f000012, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* grpc__gcp__AltsContext__PeerAttributesEntry_msg_init_ptr = &grpc__gcp__AltsContext__PeerAttributesEntry_msg_init;
static const upb_MiniTable *messages_layout[2] = {
  &grpc__gcp__AltsContext_msg_init,
  &grpc__gcp__AltsContext__PeerAttributesEntry_msg_init,
};

const upb_MiniTableFile src_proto_grpc_gcp_altscontext_proto_upb_file_layout = {
  messages_layout,
  NULL,
  NULL,
  2,
  0,
  0,
};

#include "upb/port/undef.inc"
