
#include <stddef.h>
#include "upb/generated_code_support.h"
#include "src/proto/grpc/lookup/v1/rls.upb_minitable.h"

#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
static const upb_MiniTableSubInternal grpc_lookup_v1_RouteLookupRequest__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &grpc__lookup__v1__RouteLookupRequest__KeyMapEntry_msg_init_ptr},
};

static const upb_MiniTableField grpc_lookup_v1_RouteLookupRequest__fields[4] = {
  {3, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(8, 48), 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(12, 8), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {6, UPB_SIZE(24, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
};

const upb_MiniTable grpc__lookup__v1__RouteLookupRequest_msg_init = {
  &grpc_lookup_v1_RouteLookupRequest__submsgs[0],
  &grpc_lookup_v1_RouteLookupRequest__fields[0],
  UPB_SIZE(32, 56), 4, kUpb_ExtMode_NonExtendable, 0, UPB_FASTTABLE_MASK(56), 0,
#ifdef UPB_TRACING_ENABLED
  "grpc.lookup.v1.RouteLookupRequest",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00001a, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f000028, &upb_psv4_1bt},
    {0x002000003f000032, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* grpc__lookup__v1__RouteLookupRequest_msg_init_ptr = &grpc__lookup__v1__RouteLookupRequest_msg_init;
static const upb_MiniTableField grpc_lookup_v1_RouteLookupRequest_KeyMapEntry__fields[2] = {
  {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, 32, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
};

const upb_MiniTable grpc__lookup__v1__RouteLookupRequest__KeyMapEntry_msg_init = {
  NULL,
  &grpc_lookup_v1_RouteLookupRequest_KeyMapEntry__fields[0],
  48, 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "grpc.lookup.v1.RouteLookupRequest.KeyMapEntry",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
    {0x002000003f000012, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* grpc__lookup__v1__RouteLookupRequest__KeyMapEntry_msg_init_ptr = &grpc__lookup__v1__RouteLookupRequest__KeyMapEntry_msg_init;
static const upb_MiniTableField grpc_lookup_v1_RouteLookupResponse__fields[2] = {
  {2, UPB_SIZE(12, 8), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(8, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable grpc__lookup__v1__RouteLookupResponse_msg_init = {
  NULL,
  &grpc_lookup_v1_RouteLookupResponse__fields[0],
  UPB_SIZE(24, 32), 2, kUpb_ExtMode_NonExtendable, 0, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "grpc.lookup.v1.RouteLookupResponse",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f000012, &upb_pss_1bt},
    {0x001800003f00001a, &upb_prs_1bt},
  })
};

const upb_MiniTable* grpc__lookup__v1__RouteLookupResponse_msg_init_ptr = &grpc__lookup__v1__RouteLookupResponse_msg_init;
static const upb_MiniTable *messages_layout[3] = {
  &grpc__lookup__v1__RouteLookupRequest_msg_init,
  &grpc__lookup__v1__RouteLookupRequest__KeyMapEntry_msg_init,
  &grpc__lookup__v1__RouteLookupResponse_msg_init,
};

const upb_MiniTableFile src_proto_grpc_lookup_v1_rls_proto_upb_file_layout = {
  messages_layout,
  NULL,
  NULL,
  3,
  0,
  0,
};

#include "upb/port/undef.inc"
