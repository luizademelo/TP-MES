
#include <stddef.h>
#include "upb/generated_code_support.h"
#include "src/proto/grpc/lookup/v1/rls_config.upb_minitable.h"
#include "google/protobuf/duration.upb_minitable.h"

#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
static const upb_MiniTableField grpc_lookup_v1_NameMatcher__fields[3] = {
  {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable grpc__lookup__v1__NameMatcher_msg_init = {
  NULL,
  &grpc_lookup_v1_NameMatcher__fields[0],
  UPB_SIZE(24, 40), 3, kUpb_ExtMode_NonExtendable, 3, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "grpc.lookup.v1.NameMatcher",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
    {0x002000003f000012, &upb_prs_1bt},
    {0x000800003f000018, &upb_psb1_1bt},
  })
};

const upb_MiniTable* grpc__lookup__v1__NameMatcher_msg_init_ptr = &grpc__lookup__v1__NameMatcher_msg_init;
static const upb_MiniTableSubInternal grpc_lookup_v1_GrpcKeyBuilder__submsgs[4] = {
  {.UPB_PRIVATE(submsg) = &grpc__lookup__v1__GrpcKeyBuilder__Name_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &grpc__lookup__v1__NameMatcher_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &grpc__lookup__v1__GrpcKeyBuilder__ExtraKeys_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &grpc__lookup__v1__GrpcKeyBuilder__ConstantKeysEntry_msg_init_ptr},
};

static const upb_MiniTableField grpc_lookup_v1_GrpcKeyBuilder__fields[4] = {
  {1, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 24), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(20, 32), 64, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(24, 40), 0, 3, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable grpc__lookup__v1__GrpcKeyBuilder_msg_init = {
  &grpc_lookup_v1_GrpcKeyBuilder__submsgs[0],
  &grpc_lookup_v1_GrpcKeyBuilder__fields[0],
  UPB_SIZE(32, 48), 4, kUpb_ExtMode_NonExtendable, 4, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "grpc.lookup.v1.GrpcKeyBuilder",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_prm_1bt_max64b},
    {0x001800003f010012, &upb_prm_1bt_max64b},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* grpc__lookup__v1__GrpcKeyBuilder_msg_init_ptr = &grpc__lookup__v1__GrpcKeyBuilder_msg_init;
static const upb_MiniTableField grpc_lookup_v1_GrpcKeyBuilder_Name__fields[2] = {
  {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
};

const upb_MiniTable grpc__lookup__v1__GrpcKeyBuilder__Name_msg_init = {
  NULL,
  &grpc_lookup_v1_GrpcKeyBuilder_Name__fields[0],
  UPB_SIZE(24, 40), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "grpc.lookup.v1.GrpcKeyBuilder.Name",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f00000a, &upb_pss_1bt},
    {0x001800003f000012, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* grpc__lookup__v1__GrpcKeyBuilder__Name_msg_init_ptr = &grpc__lookup__v1__GrpcKeyBuilder__Name_msg_init;
static const upb_MiniTableField grpc_lookup_v1_GrpcKeyBuilder_ExtraKeys__fields[3] = {
  {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(24, 40), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
};

const upb_MiniTable grpc__lookup__v1__GrpcKeyBuilder__ExtraKeys_msg_init = {
  NULL,
  &grpc_lookup_v1_GrpcKeyBuilder_ExtraKeys__fields[0],
  UPB_SIZE(32, 56), 3, kUpb_ExtMode_NonExtendable, 3, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "grpc.lookup.v1.GrpcKeyBuilder.ExtraKeys",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f00000a, &upb_pss_1bt},
    {0x001800003f000012, &upb_pss_1bt},
    {0x002800003f00001a, &upb_pss_1bt},
  })
};

const upb_MiniTable* grpc__lookup__v1__GrpcKeyBuilder__ExtraKeys_msg_init_ptr = &grpc__lookup__v1__GrpcKeyBuilder__ExtraKeys_msg_init;
static const upb_MiniTableField grpc_lookup_v1_GrpcKeyBuilder_ConstantKeysEntry__fields[2] = {
  {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, 32, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
};

const upb_MiniTable grpc__lookup__v1__GrpcKeyBuilder__ConstantKeysEntry_msg_init = {
  NULL,
  &grpc_lookup_v1_GrpcKeyBuilder_ConstantKeysEntry__fields[0],
  48, 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "grpc.lookup.v1.GrpcKeyBuilder.ConstantKeysEntry",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
    {0x002000003f000012, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* grpc__lookup__v1__GrpcKeyBuilder__ConstantKeysEntry_msg_init_ptr = &grpc__lookup__v1__GrpcKeyBuilder__ConstantKeysEntry_msg_init;
static const upb_MiniTableSubInternal grpc_lookup_v1_HttpKeyBuilder__submsgs[3] = {
  {.UPB_PRIVATE(submsg) = &grpc__lookup__v1__NameMatcher_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &grpc__lookup__v1__NameMatcher_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &grpc__lookup__v1__HttpKeyBuilder__ConstantKeysEntry_msg_init_ptr},
};

static const upb_MiniTableField grpc_lookup_v1_HttpKeyBuilder__fields[5] = {
  {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(16, 24), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(20, 32), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(24, 40), 0, 2, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable grpc__lookup__v1__HttpKeyBuilder_msg_init = {
  &grpc_lookup_v1_HttpKeyBuilder__submsgs[0],
  &grpc_lookup_v1_HttpKeyBuilder__fields[0],
  UPB_SIZE(32, 48), 5, kUpb_ExtMode_NonExtendable, 5, UPB_FASTTABLE_MASK(56), 0,
#ifdef UPB_TRACING_ENABLED
  "grpc.lookup.v1.HttpKeyBuilder",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f00000a, &upb_prs_1bt},
    {0x001000003f000012, &upb_prs_1bt},
    {0x001800003f00001a, &upb_prm_1bt_max64b},
    {0x002000003f010022, &upb_prm_1bt_max64b},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* grpc__lookup__v1__HttpKeyBuilder_msg_init_ptr = &grpc__lookup__v1__HttpKeyBuilder_msg_init;
static const upb_MiniTableField grpc_lookup_v1_HttpKeyBuilder_ConstantKeysEntry__fields[2] = {
  {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, 32, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
};

const upb_MiniTable grpc__lookup__v1__HttpKeyBuilder__ConstantKeysEntry_msg_init = {
  NULL,
  &grpc_lookup_v1_HttpKeyBuilder_ConstantKeysEntry__fields[0],
  48, 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "grpc.lookup.v1.HttpKeyBuilder.ConstantKeysEntry",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
    {0x002000003f000012, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* grpc__lookup__v1__HttpKeyBuilder__ConstantKeysEntry_msg_init_ptr = &grpc__lookup__v1__HttpKeyBuilder__ConstantKeysEntry_msg_init;
static const upb_MiniTableSubInternal grpc_lookup_v1_RouteLookupConfig__submsgs[5] = {
  {.UPB_PRIVATE(submsg) = &grpc__lookup__v1__HttpKeyBuilder_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &grpc__lookup__v1__GrpcKeyBuilder_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__Duration_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__Duration_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__Duration_msg_init_ptr},
};

static const upb_MiniTableField grpc_lookup_v1_RouteLookupConfig__fields[9] = {
  {1, UPB_SIZE(12, 48), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 56), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(36, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(20, 64), 64, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(24, 72), 65, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {6, UPB_SIZE(28, 80), 66, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {7, UPB_SIZE(56, 88), 0, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {8, UPB_SIZE(32, 96), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {9, UPB_SIZE(44, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
};

const upb_MiniTable grpc__lookup__v1__RouteLookupConfig_msg_init = {
  &grpc_lookup_v1_RouteLookupConfig__submsgs[0],
  &grpc_lookup_v1_RouteLookupConfig__fields[0],
  UPB_SIZE(64, 104), 9, kUpb_ExtMode_NonExtendable, 9, UPB_FASTTABLE_MASK(120), 0,
#ifdef UPB_TRACING_ENABLED
  "grpc.lookup.v1.RouteLookupConfig",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x003000003f00000a, &upb_prm_1bt_max64b},
    {0x003800003f010012, &upb_prm_1bt_max64b},
    {0x001000003f00001a, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x005800003f000038, &upb_psv8_1bt},
    {0x006000003f000042, &upb_prs_1bt},
    {0x002000003f00004a, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* grpc__lookup__v1__RouteLookupConfig_msg_init_ptr = &grpc__lookup__v1__RouteLookupConfig_msg_init;
static const upb_MiniTableSubInternal grpc_lookup_v1_RouteLookupClusterSpecifier__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &grpc__lookup__v1__RouteLookupConfig_msg_init_ptr},
};

static const upb_MiniTableField grpc_lookup_v1_RouteLookupClusterSpecifier__fields[1] = {
  {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable grpc__lookup__v1__RouteLookupClusterSpecifier_msg_init = {
  &grpc_lookup_v1_RouteLookupClusterSpecifier__submsgs[0],
  &grpc_lookup_v1_RouteLookupClusterSpecifier__fields[0],
  UPB_SIZE(16, 24), 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "grpc.lookup.v1.RouteLookupClusterSpecifier",
#endif
};

const upb_MiniTable* grpc__lookup__v1__RouteLookupClusterSpecifier_msg_init_ptr = &grpc__lookup__v1__RouteLookupClusterSpecifier_msg_init;
static const upb_MiniTable *messages_layout[9] = {
  &grpc__lookup__v1__NameMatcher_msg_init,
  &grpc__lookup__v1__GrpcKeyBuilder_msg_init,
  &grpc__lookup__v1__GrpcKeyBuilder__Name_msg_init,
  &grpc__lookup__v1__GrpcKeyBuilder__ExtraKeys_msg_init,
  &grpc__lookup__v1__GrpcKeyBuilder__ConstantKeysEntry_msg_init,
  &grpc__lookup__v1__HttpKeyBuilder_msg_init,
  &grpc__lookup__v1__HttpKeyBuilder__ConstantKeysEntry_msg_init,
  &grpc__lookup__v1__RouteLookupConfig_msg_init,
  &grpc__lookup__v1__RouteLookupClusterSpecifier_msg_init,
};

const upb_MiniTableFile src_proto_grpc_lookup_v1_rls_config_proto_upb_file_layout = {
  messages_layout,
  NULL,
  NULL,
  9,
  0,
  0,
};

#include "upb/port/undef.inc"
