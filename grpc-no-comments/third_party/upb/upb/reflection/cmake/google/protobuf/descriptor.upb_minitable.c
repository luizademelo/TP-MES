
#include <stddef.h>
#include "upb/generated_code_support.h"
#include "google/protobuf/descriptor.upb_minitable.h"

#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
static const upb_MiniTableSubInternal google_protobuf_FileDescriptorSet__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__FileDescriptorProto_msg_init_ptr},
};

static const upb_MiniTableField google_protobuf_FileDescriptorSet__fields[1] = {
  {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable google__protobuf__FileDescriptorSet_msg_init = {
  &google_protobuf_FileDescriptorSet__submsgs[0],
  &google_protobuf_FileDescriptorSet__fields[0],
  16, 1, kUpb_ExtMode_Extendable, 1, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "google.protobuf.FileDescriptorSet",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f00000a, &upb_prm_1bt_max192b},
  })
};

const upb_MiniTable* google__protobuf__FileDescriptorSet_msg_init_ptr = &google__protobuf__FileDescriptorSet_msg_init;
static const upb_MiniTableSubInternal google_protobuf_FileDescriptorProto__submsgs[7] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__DescriptorProto_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__EnumDescriptorProto_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__ServiceDescriptorProto_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__FieldDescriptorProto_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__FileOptions_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__SourceCodeInfo_msg_init_ptr},
  {.UPB_PRIVATE(subenum) = &google__protobuf__Edition_enum_init},
};

static const upb_MiniTableField google_protobuf_FileDescriptorProto__fields[14] = {
  {1, UPB_SIZE(56, 16), 64, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(64, 32), 65, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(12, 64), 0, kUpb_NoSub, 12, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsAlternate | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(16, 72), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(20, 80), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {6, UPB_SIZE(24, 88), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {7, UPB_SIZE(28, 96), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {8, UPB_SIZE(32, 104), 66, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {9, UPB_SIZE(36, 112), 67, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {10, UPB_SIZE(40, 120), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {11, UPB_SIZE(44, 128), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {12, UPB_SIZE(72, 48), 68, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {14, UPB_SIZE(48, 12), 69, 6, 14, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {15, UPB_SIZE(52, 136), 0, kUpb_NoSub, 12, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsAlternate | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable google__protobuf__FileDescriptorProto_msg_init = {
  &google_protobuf_FileDescriptorProto__submsgs[0],
  &google_protobuf_FileDescriptorProto__fields[0],
  UPB_SIZE(80, 144), 14, kUpb_ExtMode_NonExtendable, 12, UPB_FASTTABLE_MASK(120), 0,
#ifdef UPB_TRACING_ENABLED
  "google.protobuf.FileDescriptorProto",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x004000003f00001a, &upb_prs_1bt},
    {0x004800003f000022, &upb_prm_1bt_max128b},
    {0x005000003f01002a, &upb_prm_1bt_max128b},
    {0x005800003f020032, &upb_prm_1bt_max64b},
    {0x006000003f03003a, &upb_prm_1bt_max128b},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x007800003f000050, &upb_prv4_1bt},
    {0x008000003f000058, &upb_prv4_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x008800003f00007a, &upb_prs_1bt},
  })
};

const upb_MiniTable* google__protobuf__FileDescriptorProto_msg_init_ptr = &google__protobuf__FileDescriptorProto_msg_init;
static const upb_MiniTableSubInternal google_protobuf_DescriptorProto__submsgs[9] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__FieldDescriptorProto_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__DescriptorProto_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__EnumDescriptorProto_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__DescriptorProto__ExtensionRange_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__FieldDescriptorProto_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__MessageOptions_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__OneofDescriptorProto_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__DescriptorProto__ReservedRange_msg_init_ptr},
  {.UPB_PRIVATE(subenum) = &google__protobuf__SymbolVisibility_enum_init},
};

static const upb_MiniTableField google_protobuf_DescriptorProto__fields[11] = {
  {1, UPB_SIZE(52, 16), 64, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 32), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(16, 40), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(20, 48), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(24, 56), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {6, UPB_SIZE(28, 64), 0, 4, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {7, UPB_SIZE(32, 72), 65, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {8, UPB_SIZE(36, 80), 0, 6, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {9, UPB_SIZE(40, 88), 0, 7, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {10, UPB_SIZE(44, 96), 0, kUpb_NoSub, 12, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsAlternate | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {11, UPB_SIZE(48, 12), 66, 8, 14, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable google__protobuf__DescriptorProto_msg_init = {
  &google_protobuf_DescriptorProto__submsgs[0],
  &google_protobuf_DescriptorProto__fields[0],
  UPB_SIZE(64, 104), 11, kUpb_ExtMode_NonExtendable, 11, UPB_FASTTABLE_MASK(120), 0,
#ifdef UPB_TRACING_ENABLED
  "google.protobuf.DescriptorProto",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x002000003f000012, &upb_prm_1bt_max128b},
    {0x002800003f01001a, &upb_prm_1bt_max128b},
    {0x003000003f020022, &upb_prm_1bt_max128b},
    {0x003800003f03002a, &upb_prm_1bt_max64b},
    {0x004000003f040032, &upb_prm_1bt_max128b},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x005000003f060042, &upb_prm_1bt_max64b},
    {0x005800003f07004a, &upb_prm_1bt_max64b},
    {0x006000003f000052, &upb_prs_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* google__protobuf__DescriptorProto_msg_init_ptr = &google__protobuf__DescriptorProto_msg_init;
static const upb_MiniTableSubInternal google_protobuf_DescriptorProto_ExtensionRange__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__ExtensionRangeOptions_msg_init_ptr},
};

static const upb_MiniTableField google_protobuf_DescriptorProto_ExtensionRange__fields[3] = {
  {1, 12, 64, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {2, 16, 65, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(20, 24), 66, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable google__protobuf__DescriptorProto__ExtensionRange_msg_init = {
  &google_protobuf_DescriptorProto_ExtensionRange__submsgs[0],
  &google_protobuf_DescriptorProto_ExtensionRange__fields[0],
  UPB_SIZE(24, 32), 3, kUpb_ExtMode_NonExtendable, 3, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "google.protobuf.DescriptorProto.ExtensionRange",
#endif
};

const upb_MiniTable* google__protobuf__DescriptorProto__ExtensionRange_msg_init_ptr = &google__protobuf__DescriptorProto__ExtensionRange_msg_init;
static const upb_MiniTableField google_protobuf_DescriptorProto_ReservedRange__fields[2] = {
  {1, 12, 64, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {2, 16, 65, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable google__protobuf__DescriptorProto__ReservedRange_msg_init = {
  NULL,
  &google_protobuf_DescriptorProto_ReservedRange__fields[0],
  24, 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "google.protobuf.DescriptorProto.ReservedRange",
#endif
};

const upb_MiniTable* google__protobuf__DescriptorProto__ReservedRange_msg_init_ptr = &google__protobuf__DescriptorProto__ReservedRange_msg_init;
static const upb_MiniTableSubInternal google_protobuf_ExtensionRangeOptions__submsgs[4] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__ExtensionRangeOptions__Declaration_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__FeatureSet_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__UninterpretedOption_msg_init_ptr},
  {.UPB_PRIVATE(subenum) = &google__protobuf__ExtensionRangeOptions__VerificationState_enum_init},
};

static const upb_MiniTableField google_protobuf_ExtensionRangeOptions__fields[4] = {
  {2, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(16, 12), 64, 3, 14, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {50, UPB_SIZE(20, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {999, UPB_SIZE(24, 32), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable google__protobuf__ExtensionRangeOptions_msg_init = {
  &google_protobuf_ExtensionRangeOptions__submsgs[0],
  &google_protobuf_ExtensionRangeOptions__fields[0],
  UPB_SIZE(32, 40), 4, kUpb_ExtMode_Extendable, 0, UPB_FASTTABLE_MASK(248), 0,
#ifdef UPB_TRACING_ENABLED
  "google.protobuf.ExtensionRangeOptions",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f000012, &upb_prm_1bt_max64b},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x002000003f023eba, &upb_prm_2bt_max128b},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* google__protobuf__ExtensionRangeOptions_msg_init_ptr = &google__protobuf__ExtensionRangeOptions_msg_init;
static const upb_MiniTableField google_protobuf_ExtensionRangeOptions_Declaration__fields[5] = {
  {1, 12, 64, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {2, 16, 65, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(24, 32), 66, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {5, 9, 67, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {6, 10, 68, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable google__protobuf__ExtensionRangeOptions__Declaration_msg_init = {
  NULL,
  &google_protobuf_ExtensionRangeOptions_Declaration__fields[0],
  UPB_SIZE(32, 48), 5, kUpb_ExtMode_NonExtendable, 3, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "google.protobuf.ExtensionRangeOptions.Declaration",
#endif
};

const upb_MiniTable* google__protobuf__ExtensionRangeOptions__Declaration_msg_init_ptr = &google__protobuf__ExtensionRangeOptions__Declaration_msg_init;
static const upb_MiniTableSubInternal google_protobuf_FieldDescriptorProto__submsgs[3] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__FieldOptions_msg_init_ptr},
  {.UPB_PRIVATE(subenum) = &google__protobuf__FieldDescriptorProto__Label_enum_init},
  {.UPB_PRIVATE(subenum) = &google__protobuf__FieldDescriptorProto__Type_enum_init},
};

static const upb_MiniTableField google_protobuf_FieldDescriptorProto__fields[11] = {
  {1, 32, 64, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(40, 48), 65, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {3, 12, 66, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {4, 16, 67, 1, 14, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {5, 20, 68, 2, 14, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {6, UPB_SIZE(48, 64), 69, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {7, UPB_SIZE(56, 80), 70, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {8, UPB_SIZE(24, 112), 71, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {9, UPB_SIZE(28, 24), 72, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {10, UPB_SIZE(64, 96), 73, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {17, 10, 74, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable google__protobuf__FieldDescriptorProto_msg_init = {
  &google_protobuf_FieldDescriptorProto__submsgs[0],
  &google_protobuf_FieldDescriptorProto__fields[0],
  UPB_SIZE(72, 120), 11, kUpb_ExtMode_NonExtendable, 10, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "google.protobuf.FieldDescriptorProto",
#endif
};

const upb_MiniTable* google__protobuf__FieldDescriptorProto_msg_init_ptr = &google__protobuf__FieldDescriptorProto_msg_init;
static const upb_MiniTableSubInternal google_protobuf_OneofDescriptorProto__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__OneofOptions_msg_init_ptr},
};

static const upb_MiniTableField google_protobuf_OneofDescriptorProto__fields[2] = {
  {1, 16, 64, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 32), 65, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable google__protobuf__OneofDescriptorProto_msg_init = {
  &google_protobuf_OneofDescriptorProto__submsgs[0],
  &google_protobuf_OneofDescriptorProto__fields[0],
  UPB_SIZE(24, 40), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "google.protobuf.OneofDescriptorProto",
#endif
};

const upb_MiniTable* google__protobuf__OneofDescriptorProto_msg_init_ptr = &google__protobuf__OneofDescriptorProto_msg_init;
static const upb_MiniTableSubInternal google_protobuf_EnumDescriptorProto__submsgs[4] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__EnumValueDescriptorProto_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__EnumOptions_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__EnumDescriptorProto__EnumReservedRange_msg_init_ptr},
  {.UPB_PRIVATE(subenum) = &google__protobuf__SymbolVisibility_enum_init},
};

static const upb_MiniTableField google_protobuf_EnumDescriptorProto__fields[6] = {
  {1, UPB_SIZE(32, 16), 64, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 32), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(20, 48), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(24, 56), 0, kUpb_NoSub, 12, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsAlternate | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {6, UPB_SIZE(28, 12), 66, 3, 14, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable google__protobuf__EnumDescriptorProto_msg_init = {
  &google_protobuf_EnumDescriptorProto__submsgs[0],
  &google_protobuf_EnumDescriptorProto__fields[0],
  UPB_SIZE(40, 64), 6, kUpb_ExtMode_NonExtendable, 6, UPB_FASTTABLE_MASK(56), 0,
#ifdef UPB_TRACING_ENABLED
  "google.protobuf.EnumDescriptorProto",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x002000003f000012, &upb_prm_1bt_max64b},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x003000003f020022, &upb_prm_1bt_max64b},
    {0x003800003f00002a, &upb_prs_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* google__protobuf__EnumDescriptorProto_msg_init_ptr = &google__protobuf__EnumDescriptorProto_msg_init;
static const upb_MiniTableField google_protobuf_EnumDescriptorProto_EnumReservedRange__fields[2] = {
  {1, 12, 64, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {2, 16, 65, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable google__protobuf__EnumDescriptorProto__EnumReservedRange_msg_init = {
  NULL,
  &google_protobuf_EnumDescriptorProto_EnumReservedRange__fields[0],
  24, 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "google.protobuf.EnumDescriptorProto.EnumReservedRange",
#endif
};

const upb_MiniTable* google__protobuf__EnumDescriptorProto__EnumReservedRange_msg_init_ptr = &google__protobuf__EnumDescriptorProto__EnumReservedRange_msg_init;
static const upb_MiniTableSubInternal google_protobuf_EnumValueDescriptorProto__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__EnumValueOptions_msg_init_ptr},
};

static const upb_MiniTableField google_protobuf_EnumValueDescriptorProto__fields[3] = {
  {1, UPB_SIZE(20, 16), 64, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, 12, 65, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(16, 32), 66, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable google__protobuf__EnumValueDescriptorProto_msg_init = {
  &google_protobuf_EnumValueDescriptorProto__submsgs[0],
  &google_protobuf_EnumValueDescriptorProto__fields[0],
  UPB_SIZE(32, 40), 3, kUpb_ExtMode_NonExtendable, 3, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "google.protobuf.EnumValueDescriptorProto",
#endif
};

const upb_MiniTable* google__protobuf__EnumValueDescriptorProto_msg_init_ptr = &google__protobuf__EnumValueDescriptorProto_msg_init;
static const upb_MiniTableSubInternal google_protobuf_ServiceDescriptorProto__submsgs[2] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__MethodDescriptorProto_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__ServiceOptions_msg_init_ptr},
};

static const upb_MiniTableField google_protobuf_ServiceDescriptorProto__fields[3] = {
  {1, UPB_SIZE(20, 16), 64, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 32), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable google__protobuf__ServiceDescriptorProto_msg_init = {
  &google_protobuf_ServiceDescriptorProto__submsgs[0],
  &google_protobuf_ServiceDescriptorProto__fields[0],
  UPB_SIZE(32, 48), 3, kUpb_ExtMode_NonExtendable, 3, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "google.protobuf.ServiceDescriptorProto",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x002000003f000012, &upb_prm_1bt_max128b},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* google__protobuf__ServiceDescriptorProto_msg_init_ptr = &google__protobuf__ServiceDescriptorProto_msg_init;
static const upb_MiniTableSubInternal google_protobuf_MethodDescriptorProto__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__MethodOptions_msg_init_ptr},
};

static const upb_MiniTableField google_protobuf_MethodDescriptorProto__fields[6] = {
  {1, 16, 64, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(24, 32), 65, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(32, 48), 66, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(12, 64), 67, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {5, 9, 68, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {6, 10, 69, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable google__protobuf__MethodDescriptorProto_msg_init = {
  &google_protobuf_MethodDescriptorProto__submsgs[0],
  &google_protobuf_MethodDescriptorProto__fields[0],
  UPB_SIZE(40, 72), 6, kUpb_ExtMode_NonExtendable, 6, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "google.protobuf.MethodDescriptorProto",
#endif
};

const upb_MiniTable* google__protobuf__MethodDescriptorProto_msg_init_ptr = &google__protobuf__MethodDescriptorProto_msg_init;
static const upb_MiniTableSubInternal google_protobuf_FileOptions__submsgs[3] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__FeatureSet_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__UninterpretedOption_msg_init_ptr},
  {.UPB_PRIVATE(subenum) = &google__protobuf__FileOptions__OptimizeMode_enum_init},
};

static const upb_MiniTableField google_protobuf_FileOptions__fields[21] = {
  {1, UPB_SIZE(32, 24), 64, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {8, 40, 65, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {9, 20, 66, 2, 14, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {10, 11, 67, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {11, UPB_SIZE(48, 56), 68, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {16, 12, 69, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {17, 13, 70, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {18, 14, 71, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {20, 15, 72, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {23, 16, 73, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {27, 17, 74, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {31, 18, 75, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {36, UPB_SIZE(56, 72), 76, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {37, UPB_SIZE(64, 88), 77, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {39, UPB_SIZE(72, 104), 78, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {40, UPB_SIZE(80, 120), 79, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {41, UPB_SIZE(88, 136), 80, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {44, UPB_SIZE(96, 152), 81, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {45, UPB_SIZE(104, 168), 82, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {50, UPB_SIZE(24, 184), 83, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {999, UPB_SIZE(28, 192), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable google__protobuf__FileOptions_msg_init = {
  &google_protobuf_FileOptions__submsgs[0],
  &google_protobuf_FileOptions__fields[0],
  UPB_SIZE(112, 200), 21, kUpb_ExtMode_Extendable, 1, UPB_FASTTABLE_MASK(248), 0,
#ifdef UPB_TRACING_ENABLED
  "google.protobuf.FileOptions",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x00c000003f013eba, &upb_prm_2bt_max128b},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* google__protobuf__FileOptions_msg_init_ptr = &google__protobuf__FileOptions_msg_init;
static const upb_MiniTableSubInternal google_protobuf_MessageOptions__submsgs[2] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__FeatureSet_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__UninterpretedOption_msg_init_ptr},
};

static const upb_MiniTableField google_protobuf_MessageOptions__fields[7] = {
  {1, 9, 64, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {2, 10, 65, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {3, 11, 66, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {7, 12, 67, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {11, 13, 68, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {12, 16, 69, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {999, UPB_SIZE(20, 24), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable google__protobuf__MessageOptions_msg_init = {
  &google_protobuf_MessageOptions__submsgs[0],
  &google_protobuf_MessageOptions__fields[0],
  UPB_SIZE(24, 32), 7, kUpb_ExtMode_Extendable, 3, UPB_FASTTABLE_MASK(248), 0,
#ifdef UPB_TRACING_ENABLED
  "google.protobuf.MessageOptions",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001800003f013eba, &upb_prm_2bt_max128b},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* google__protobuf__MessageOptions_msg_init_ptr = &google__protobuf__MessageOptions_msg_init;
static const upb_MiniTableSubInternal google_protobuf_FieldOptions__submsgs[8] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__FieldOptions__EditionDefault_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__FeatureSet_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__FieldOptions__FeatureSupport_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__UninterpretedOption_msg_init_ptr},
  {.UPB_PRIVATE(subenum) = &google__protobuf__FieldOptions__CType_enum_init},
  {.UPB_PRIVATE(subenum) = &google__protobuf__FieldOptions__JSType_enum_init},
  {.UPB_PRIVATE(subenum) = &google__protobuf__FieldOptions__OptionRetention_enum_init},
  {.UPB_PRIVATE(subenum) = &google__protobuf__FieldOptions__OptionTargetType_enum_init},
};

static const upb_MiniTableField google_protobuf_FieldOptions__fields[14] = {
  {1, 16, 64, 4, 14, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {2, 10, 65, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {3, 11, 66, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {5, 12, 67, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {6, 20, 68, 5, 14, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {10, 13, 69, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {15, 14, 70, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {16, 15, 71, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {17, 24, 72, 6, 14, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {19, UPB_SIZE(28, 32), 0, 7, 14, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {20, UPB_SIZE(32, 40), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {21, UPB_SIZE(36, 48), 73, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {22, UPB_SIZE(40, 56), 74, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {999, UPB_SIZE(44, 64), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable google__protobuf__FieldOptions_msg_init = {
  &google_protobuf_FieldOptions__submsgs[0],
  &google_protobuf_FieldOptions__fields[0],
  UPB_SIZE(48, 72), 14, kUpb_ExtMode_Extendable, 3, UPB_FASTTABLE_MASK(248), 0,
#ifdef UPB_TRACING_ENABLED
  "google.protobuf.FieldOptions",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x002800003f0001a2, &upb_prm_2bt_max64b},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x004000003f033eba, &upb_prm_2bt_max128b},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* google__protobuf__FieldOptions_msg_init_ptr = &google__protobuf__FieldOptions_msg_init;
static const upb_MiniTableSubInternal google_protobuf_FieldOptions_EditionDefault__submsgs[1] = {
  {.UPB_PRIVATE(subenum) = &google__protobuf__Edition_enum_init},
};

static const upb_MiniTableField google_protobuf_FieldOptions_EditionDefault__fields[2] = {
  {2, 16, 64, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {3, 12, 65, 0, 14, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable google__protobuf__FieldOptions__EditionDefault_msg_init = {
  &google_protobuf_FieldOptions_EditionDefault__submsgs[0],
  &google_protobuf_FieldOptions_EditionDefault__fields[0],
  UPB_SIZE(24, 32), 2, kUpb_ExtMode_NonExtendable, 0, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "google.protobuf.FieldOptions.EditionDefault",
#endif
};

const upb_MiniTable* google__protobuf__FieldOptions__EditionDefault_msg_init_ptr = &google__protobuf__FieldOptions__EditionDefault_msg_init;
static const upb_MiniTableSubInternal google_protobuf_FieldOptions_FeatureSupport__submsgs[3] = {
  {.UPB_PRIVATE(subenum) = &google__protobuf__Edition_enum_init},
  {.UPB_PRIVATE(subenum) = &google__protobuf__Edition_enum_init},
  {.UPB_PRIVATE(subenum) = &google__protobuf__Edition_enum_init},
};

static const upb_MiniTableField google_protobuf_FieldOptions_FeatureSupport__fields[4] = {
  {1, 12, 64, 0, 14, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {2, 16, 65, 1, 14, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {3, 24, 66, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {4, 20, 67, 2, 14, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable google__protobuf__FieldOptions__FeatureSupport_msg_init = {
  &google_protobuf_FieldOptions_FeatureSupport__submsgs[0],
  &google_protobuf_FieldOptions_FeatureSupport__fields[0],
  UPB_SIZE(32, 40), 4, kUpb_ExtMode_NonExtendable, 4, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "google.protobuf.FieldOptions.FeatureSupport",
#endif
};

const upb_MiniTable* google__protobuf__FieldOptions__FeatureSupport_msg_init_ptr = &google__protobuf__FieldOptions__FeatureSupport_msg_init;
static const upb_MiniTableSubInternal google_protobuf_OneofOptions__submsgs[2] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__FeatureSet_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__UninterpretedOption_msg_init_ptr},
};

static const upb_MiniTableField google_protobuf_OneofOptions__fields[2] = {
  {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {999, UPB_SIZE(16, 24), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable google__protobuf__OneofOptions_msg_init = {
  &google_protobuf_OneofOptions__submsgs[0],
  &google_protobuf_OneofOptions__fields[0],
  UPB_SIZE(24, 32), 2, kUpb_ExtMode_Extendable, 1, UPB_FASTTABLE_MASK(248), 0,
#ifdef UPB_TRACING_ENABLED
  "google.protobuf.OneofOptions",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001800003f013eba, &upb_prm_2bt_max128b},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* google__protobuf__OneofOptions_msg_init_ptr = &google__protobuf__OneofOptions_msg_init;
static const upb_MiniTableSubInternal google_protobuf_EnumOptions__submsgs[2] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__FeatureSet_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__UninterpretedOption_msg_init_ptr},
};

static const upb_MiniTableField google_protobuf_EnumOptions__fields[5] = {
  {2, 9, 64, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {3, 10, 65, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {6, 11, 66, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {7, UPB_SIZE(12, 16), 67, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {999, UPB_SIZE(16, 24), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable google__protobuf__EnumOptions_msg_init = {
  &google_protobuf_EnumOptions__submsgs[0],
  &google_protobuf_EnumOptions__fields[0],
  UPB_SIZE(24, 32), 5, kUpb_ExtMode_Extendable, 0, UPB_FASTTABLE_MASK(248), 0,
#ifdef UPB_TRACING_ENABLED
  "google.protobuf.EnumOptions",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001800003f013eba, &upb_prm_2bt_max128b},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* google__protobuf__EnumOptions_msg_init_ptr = &google__protobuf__EnumOptions_msg_init;
static const upb_MiniTableSubInternal google_protobuf_EnumValueOptions__submsgs[3] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__FeatureSet_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__FieldOptions__FeatureSupport_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__UninterpretedOption_msg_init_ptr},
};

static const upb_MiniTableField google_protobuf_EnumValueOptions__fields[5] = {
  {1, 9, 64, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 16), 65, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, 10, 66, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(16, 24), 67, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {999, UPB_SIZE(20, 32), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable google__protobuf__EnumValueOptions_msg_init = {
  &google_protobuf_EnumValueOptions__submsgs[0],
  &google_protobuf_EnumValueOptions__fields[0],
  UPB_SIZE(24, 40), 5, kUpb_ExtMode_Extendable, 4, UPB_FASTTABLE_MASK(248), 0,
#ifdef UPB_TRACING_ENABLED
  "google.protobuf.EnumValueOptions",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x002000003f023eba, &upb_prm_2bt_max128b},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* google__protobuf__EnumValueOptions_msg_init_ptr = &google__protobuf__EnumValueOptions_msg_init;
static const upb_MiniTableSubInternal google_protobuf_ServiceOptions__submsgs[2] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__FeatureSet_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__UninterpretedOption_msg_init_ptr},
};

static const upb_MiniTableField google_protobuf_ServiceOptions__fields[3] = {
  {33, 9, 64, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {34, UPB_SIZE(12, 16), 65, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {999, UPB_SIZE(16, 24), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable google__protobuf__ServiceOptions_msg_init = {
  &google_protobuf_ServiceOptions__submsgs[0],
  &google_protobuf_ServiceOptions__fields[0],
  UPB_SIZE(24, 32), 3, kUpb_ExtMode_Extendable, 0, UPB_FASTTABLE_MASK(248), 0,
#ifdef UPB_TRACING_ENABLED
  "google.protobuf.ServiceOptions",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001800003f013eba, &upb_prm_2bt_max128b},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* google__protobuf__ServiceOptions_msg_init_ptr = &google__protobuf__ServiceOptions_msg_init;
static const upb_MiniTableSubInternal google_protobuf_MethodOptions__submsgs[3] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__FeatureSet_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__UninterpretedOption_msg_init_ptr},
  {.UPB_PRIVATE(subenum) = &google__protobuf__MethodOptions__IdempotencyLevel_enum_init},
};

static const upb_MiniTableField google_protobuf_MethodOptions__fields[4] = {
  {33, 9, 64, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {34, 12, 65, 2, 14, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {35, 16, 66, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {999, UPB_SIZE(20, 24), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable google__protobuf__MethodOptions_msg_init = {
  &google_protobuf_MethodOptions__submsgs[0],
  &google_protobuf_MethodOptions__fields[0],
  UPB_SIZE(24, 32), 4, kUpb_ExtMode_Extendable, 0, UPB_FASTTABLE_MASK(248), 0,
#ifdef UPB_TRACING_ENABLED
  "google.protobuf.MethodOptions",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001800003f013eba, &upb_prm_2bt_max128b},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* google__protobuf__MethodOptions_msg_init_ptr = &google__protobuf__MethodOptions_msg_init;
static const upb_MiniTableSubInternal google_protobuf_UninterpretedOption__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__UninterpretedOption__NamePart_msg_init_ptr},
};

static const upb_MiniTableField google_protobuf_UninterpretedOption__fields[7] = {
  {2, UPB_SIZE(12, 64), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, 16, 64, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(40, 72), 65, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(48, 80), 66, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {6, UPB_SIZE(56, 88), 67, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {7, UPB_SIZE(24, 32), 68, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {8, UPB_SIZE(32, 48), 69, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
};

const upb_MiniTable google__protobuf__UninterpretedOption_msg_init = {
  &google_protobuf_UninterpretedOption__submsgs[0],
  &google_protobuf_UninterpretedOption__fields[0],
  UPB_SIZE(64, 96), 7, kUpb_ExtMode_NonExtendable, 0, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "google.protobuf.UninterpretedOption",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x004000003f000012, &upb_prm_1bt_max64b},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* google__protobuf__UninterpretedOption_msg_init_ptr = &google__protobuf__UninterpretedOption_msg_init;
static const upb_MiniTableField google_protobuf_UninterpretedOption_NamePart__fields[2] = {
  {1, UPB_SIZE(12, 16), 64, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, 9, 65, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable google__protobuf__UninterpretedOption__NamePart_msg_init = {
  NULL,
  &google_protobuf_UninterpretedOption_NamePart__fields[0],
  UPB_SIZE(24, 32), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(255), 2,
#ifdef UPB_TRACING_ENABLED
  "google.protobuf.UninterpretedOption.NamePart",
#endif
};

const upb_MiniTable* google__protobuf__UninterpretedOption__NamePart_msg_init_ptr = &google__protobuf__UninterpretedOption__NamePart_msg_init;
static const upb_MiniTableSubInternal google_protobuf_FeatureSet__submsgs[8] = {
  {.UPB_PRIVATE(subenum) = &google__protobuf__FeatureSet__FieldPresence_enum_init},
  {.UPB_PRIVATE(subenum) = &google__protobuf__FeatureSet__EnumType_enum_init},
  {.UPB_PRIVATE(subenum) = &google__protobuf__FeatureSet__RepeatedFieldEncoding_enum_init},
  {.UPB_PRIVATE(subenum) = &google__protobuf__FeatureSet__Utf8Validation_enum_init},
  {.UPB_PRIVATE(subenum) = &google__protobuf__FeatureSet__MessageEncoding_enum_init},
  {.UPB_PRIVATE(subenum) = &google__protobuf__FeatureSet__JsonFormat_enum_init},
  {.UPB_PRIVATE(subenum) = &google__protobuf__FeatureSet__EnforceNamingStyle_enum_init},
  {.UPB_PRIVATE(subenum) = &google__protobuf__FeatureSet__VisibilityFeature__DefaultSymbolVisibility_enum_init},
};

static const upb_MiniTableField google_protobuf_FeatureSet__fields[8] = {
  {1, 12, 64, 0, 14, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {2, 16, 65, 1, 14, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {3, 20, 66, 2, 14, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {4, 24, 67, 3, 14, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {5, 28, 68, 4, 14, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {6, 32, 69, 5, 14, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {7, 36, 70, 6, 14, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {8, 40, 71, 7, 14, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable google__protobuf__FeatureSet_msg_init = {
  &google_protobuf_FeatureSet__submsgs[0],
  &google_protobuf_FeatureSet__fields[0],
  48, 8, kUpb_ExtMode_Extendable, 8, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "google.protobuf.FeatureSet",
#endif
};

const upb_MiniTable* google__protobuf__FeatureSet_msg_init_ptr = &google__protobuf__FeatureSet_msg_init;
const upb_MiniTable google__protobuf__FeatureSet__VisibilityFeature_msg_init = {
  NULL,
  NULL,
  8, 0, kUpb_ExtMode_NonExtendable, 0, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "google.protobuf.FeatureSet.VisibilityFeature",
#endif
};

const upb_MiniTable* google__protobuf__FeatureSet__VisibilityFeature_msg_init_ptr = &google__protobuf__FeatureSet__VisibilityFeature_msg_init;
static const upb_MiniTableSubInternal google_protobuf_FeatureSetDefaults__submsgs[3] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__FeatureSetDefaults__FeatureSetEditionDefault_msg_init_ptr},
  {.UPB_PRIVATE(subenum) = &google__protobuf__Edition_enum_init},
  {.UPB_PRIVATE(subenum) = &google__protobuf__Edition_enum_init},
};

static const upb_MiniTableField google_protobuf_FeatureSetDefaults__fields[3] = {
  {1, UPB_SIZE(12, 24), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(16, 12), 64, 1, 14, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(20, 16), 65, 2, 14, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable google__protobuf__FeatureSetDefaults_msg_init = {
  &google_protobuf_FeatureSetDefaults__submsgs[0],
  &google_protobuf_FeatureSetDefaults__fields[0],
  UPB_SIZE(24, 32), 3, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "google.protobuf.FeatureSetDefaults",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001800003f00000a, &upb_prm_1bt_max64b},
  })
};

const upb_MiniTable* google__protobuf__FeatureSetDefaults_msg_init_ptr = &google__protobuf__FeatureSetDefaults_msg_init;
static const upb_MiniTableSubInternal google_protobuf_FeatureSetDefaults_FeatureSetEditionDefault__submsgs[3] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__FeatureSet_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__FeatureSet_msg_init_ptr},
  {.UPB_PRIVATE(subenum) = &google__protobuf__Edition_enum_init},
};

static const upb_MiniTableField google_protobuf_FeatureSetDefaults_FeatureSetEditionDefault__fields[3] = {
  {3, 12, 64, 2, 14, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {4, 16, 65, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(20, 24), 66, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable google__protobuf__FeatureSetDefaults__FeatureSetEditionDefault_msg_init = {
  &google_protobuf_FeatureSetDefaults_FeatureSetEditionDefault__submsgs[0],
  &google_protobuf_FeatureSetDefaults_FeatureSetEditionDefault__fields[0],
  UPB_SIZE(24, 32), 3, kUpb_ExtMode_NonExtendable, 0, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "google.protobuf.FeatureSetDefaults.FeatureSetEditionDefault",
#endif
};

const upb_MiniTable* google__protobuf__FeatureSetDefaults__FeatureSetEditionDefault_msg_init_ptr = &google__protobuf__FeatureSetDefaults__FeatureSetEditionDefault_msg_init;
static const upb_MiniTableSubInternal google_protobuf_SourceCodeInfo__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__SourceCodeInfo__Location_msg_init_ptr},
};

static const upb_MiniTableField google_protobuf_SourceCodeInfo__fields[1] = {
  {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable google__protobuf__SourceCodeInfo_msg_init = {
  &google_protobuf_SourceCodeInfo__submsgs[0],
  &google_protobuf_SourceCodeInfo__fields[0],
  16, 1, kUpb_ExtMode_Extendable, 1, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "google.protobuf.SourceCodeInfo",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f00000a, &upb_prm_1bt_max128b},
  })
};

const upb_MiniTable* google__protobuf__SourceCodeInfo_msg_init_ptr = &google__protobuf__SourceCodeInfo_msg_init;
static const upb_MiniTableField google_protobuf_SourceCodeInfo_Location__fields[5] = {
  {1, UPB_SIZE(12, 48), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 56), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(24, 16), 64, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {4, 32, 65, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {6, UPB_SIZE(20, 64), 0, kUpb_NoSub, 12, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsAlternate | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable google__protobuf__SourceCodeInfo__Location_msg_init = {
  NULL,
  &google_protobuf_SourceCodeInfo_Location__fields[0],
  UPB_SIZE(40, 72), 5, kUpb_ExtMode_NonExtendable, 4, UPB_FASTTABLE_MASK(56), 0,
#ifdef UPB_TRACING_ENABLED
  "google.protobuf.SourceCodeInfo.Location",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x003000003f00000a, &upb_ppv4_1bt},
    {0x003800003f000012, &upb_ppv4_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x004000003f000032, &upb_prs_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* google__protobuf__SourceCodeInfo__Location_msg_init_ptr = &google__protobuf__SourceCodeInfo__Location_msg_init;
static const upb_MiniTableSubInternal google_protobuf_GeneratedCodeInfo__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__GeneratedCodeInfo__Annotation_msg_init_ptr},
};

static const upb_MiniTableField google_protobuf_GeneratedCodeInfo__fields[1] = {
  {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable google__protobuf__GeneratedCodeInfo_msg_init = {
  &google_protobuf_GeneratedCodeInfo__submsgs[0],
  &google_protobuf_GeneratedCodeInfo__fields[0],
  16, 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "google.protobuf.GeneratedCodeInfo",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f00000a, &upb_prm_1bt_max64b},
  })
};

const upb_MiniTable* google__protobuf__GeneratedCodeInfo_msg_init_ptr = &google__protobuf__GeneratedCodeInfo_msg_init;
static const upb_MiniTableSubInternal google_protobuf_GeneratedCodeInfo_Annotation__submsgs[1] = {
  {.UPB_PRIVATE(subenum) = &google__protobuf__GeneratedCodeInfo__Annotation__Semantic_enum_init},
};

static const upb_MiniTableField google_protobuf_GeneratedCodeInfo_Annotation__fields[5] = {
  {1, UPB_SIZE(12, 40), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(28, 24), 64, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(16, 12), 65, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(20, 16), 66, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(24, 20), 67, 0, 14, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable google__protobuf__GeneratedCodeInfo__Annotation_msg_init = {
  &google_protobuf_GeneratedCodeInfo_Annotation__submsgs[0],
  &google_protobuf_GeneratedCodeInfo_Annotation__fields[0],
  UPB_SIZE(40, 48), 5, kUpb_ExtMode_NonExtendable, 5, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "google.protobuf.GeneratedCodeInfo.Annotation",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x002800003f00000a, &upb_ppv4_1bt},
  })
};

const upb_MiniTable* google__protobuf__GeneratedCodeInfo__Annotation_msg_init_ptr = &google__protobuf__GeneratedCodeInfo__Annotation_msg_init;
const upb_MiniTableEnum google__protobuf__Edition_enum_init = {
    64,
    9,
    {
        0x7,
        0x0,
        0x384,
        0x3e6,
        0x3e7,
        0x3e8,
        0x3e9,
        0x1869d,
        0x1869e,
        0x1869f,
        0x7fffffff,
    },
};

const upb_MiniTableEnum google__protobuf__ExtensionRangeOptions__VerificationState_enum_init = {
    64,
    0,
    {
        0x3,
        0x0,
    },
};

const upb_MiniTableEnum google__protobuf__FeatureSet__EnforceNamingStyle_enum_init = {
    64,
    0,
    {
        0x7,
        0x0,
    },
};

const upb_MiniTableEnum google__protobuf__FeatureSet__EnumType_enum_init = {
    64,
    0,
    {
        0x7,
        0x0,
    },
};

const upb_MiniTableEnum google__protobuf__FeatureSet__FieldPresence_enum_init = {
    64,
    0,
    {
        0xf,
        0x0,
    },
};

const upb_MiniTableEnum google__protobuf__FeatureSet__JsonFormat_enum_init = {
    64,
    0,
    {
        0x7,
        0x0,
    },
};

const upb_MiniTableEnum google__protobuf__FeatureSet__MessageEncoding_enum_init = {
    64,
    0,
    {
        0x7,
        0x0,
    },
};

const upb_MiniTableEnum google__protobuf__FeatureSet__RepeatedFieldEncoding_enum_init = {
    64,
    0,
    {
        0x7,
        0x0,
    },
};

const upb_MiniTableEnum google__protobuf__FeatureSet__Utf8Validation_enum_init = {
    64,
    0,
    {
        0xd,
        0x0,
    },
};

const upb_MiniTableEnum google__protobuf__FeatureSet__VisibilityFeature__DefaultSymbolVisibility_enum_init = {
    64,
    0,
    {
        0x1f,
        0x0,
    },
};

const upb_MiniTableEnum google__protobuf__FieldDescriptorProto__Label_enum_init = {
    64,
    0,
    {
        0xe,
        0x0,
    },
};

const upb_MiniTableEnum google__protobuf__FieldDescriptorProto__Type_enum_init = {
    64,
    0,
    {
        0x7fffe,
        0x0,
    },
};

const upb_MiniTableEnum google__protobuf__FieldOptions__CType_enum_init = {
    64,
    0,
    {
        0x7,
        0x0,
    },
};

const upb_MiniTableEnum google__protobuf__FieldOptions__JSType_enum_init = {
    64,
    0,
    {
        0x7,
        0x0,
    },
};

const upb_MiniTableEnum google__protobuf__FieldOptions__OptionRetention_enum_init = {
    64,
    0,
    {
        0x7,
        0x0,
    },
};

const upb_MiniTableEnum google__protobuf__FieldOptions__OptionTargetType_enum_init = {
    64,
    0,
    {
        0x3ff,
        0x0,
    },
};

const upb_MiniTableEnum google__protobuf__FileOptions__OptimizeMode_enum_init = {
    64,
    0,
    {
        0xe,
        0x0,
    },
};

const upb_MiniTableEnum google__protobuf__GeneratedCodeInfo__Annotation__Semantic_enum_init = {
    64,
    0,
    {
        0x7,
        0x0,
    },
};

const upb_MiniTableEnum google__protobuf__MethodOptions__IdempotencyLevel_enum_init = {
    64,
    0,
    {
        0x7,
        0x0,
    },
};

const upb_MiniTableEnum google__protobuf__SymbolVisibility_enum_init = {
    64,
    0,
    {
        0x7,
        0x0,
    },
};

static const upb_MiniTable *messages_layout[34] = {
  &google__protobuf__FileDescriptorSet_msg_init,
  &google__protobuf__FileDescriptorProto_msg_init,
  &google__protobuf__DescriptorProto_msg_init,
  &google__protobuf__DescriptorProto__ExtensionRange_msg_init,
  &google__protobuf__DescriptorProto__ReservedRange_msg_init,
  &google__protobuf__ExtensionRangeOptions_msg_init,
  &google__protobuf__ExtensionRangeOptions__Declaration_msg_init,
  &google__protobuf__FieldDescriptorProto_msg_init,
  &google__protobuf__OneofDescriptorProto_msg_init,
  &google__protobuf__EnumDescriptorProto_msg_init,
  &google__protobuf__EnumDescriptorProto__EnumReservedRange_msg_init,
  &google__protobuf__EnumValueDescriptorProto_msg_init,
  &google__protobuf__ServiceDescriptorProto_msg_init,
  &google__protobuf__MethodDescriptorProto_msg_init,
  &google__protobuf__FileOptions_msg_init,
  &google__protobuf__MessageOptions_msg_init,
  &google__protobuf__FieldOptions_msg_init,
  &google__protobuf__FieldOptions__EditionDefault_msg_init,
  &google__protobuf__FieldOptions__FeatureSupport_msg_init,
  &google__protobuf__OneofOptions_msg_init,
  &google__protobuf__EnumOptions_msg_init,
  &google__protobuf__EnumValueOptions_msg_init,
  &google__protobuf__ServiceOptions_msg_init,
  &google__protobuf__MethodOptions_msg_init,
  &google__protobuf__UninterpretedOption_msg_init,
  &google__protobuf__UninterpretedOption__NamePart_msg_init,
  &google__protobuf__FeatureSet_msg_init,
  &google__protobuf__FeatureSet__VisibilityFeature_msg_init,
  &google__protobuf__FeatureSetDefaults_msg_init,
  &google__protobuf__FeatureSetDefaults__FeatureSetEditionDefault_msg_init,
  &google__protobuf__SourceCodeInfo_msg_init,
  &google__protobuf__SourceCodeInfo__Location_msg_init,
  &google__protobuf__GeneratedCodeInfo_msg_init,
  &google__protobuf__GeneratedCodeInfo__Annotation_msg_init,
};

static const upb_MiniTableEnum *enums_layout[20] = {
  &google__protobuf__Edition_enum_init,
  &google__protobuf__ExtensionRangeOptions__VerificationState_enum_init,
  &google__protobuf__FeatureSet__EnforceNamingStyle_enum_init,
  &google__protobuf__FeatureSet__EnumType_enum_init,
  &google__protobuf__FeatureSet__FieldPresence_enum_init,
  &google__protobuf__FeatureSet__JsonFormat_enum_init,
  &google__protobuf__FeatureSet__MessageEncoding_enum_init,
  &google__protobuf__FeatureSet__RepeatedFieldEncoding_enum_init,
  &google__protobuf__FeatureSet__Utf8Validation_enum_init,
  &google__protobuf__FeatureSet__VisibilityFeature__DefaultSymbolVisibility_enum_init,
  &google__protobuf__FieldDescriptorProto__Label_enum_init,
  &google__protobuf__FieldDescriptorProto__Type_enum_init,
  &google__protobuf__FieldOptions__CType_enum_init,
  &google__protobuf__FieldOptions__JSType_enum_init,
  &google__protobuf__FieldOptions__OptionRetention_enum_init,
  &google__protobuf__FieldOptions__OptionTargetType_enum_init,
  &google__protobuf__FileOptions__OptimizeMode_enum_init,
  &google__protobuf__GeneratedCodeInfo__Annotation__Semantic_enum_init,
  &google__protobuf__MethodOptions__IdempotencyLevel_enum_init,
  &google__protobuf__SymbolVisibility_enum_init,
};

const upb_MiniTableFile google_protobuf_descriptor_proto_upb_file_layout = {
  messages_layout,
  enums_layout,
  NULL,
  34,
  20,
  0,
};

#include "upb/port/undef.inc"
