
#include <stddef.h>
#include "upb/generated_code_support.h"
#include "validate/validate.upb_minitable.h"
#include "google/protobuf/descriptor.upb_minitable.h"
#include "google/protobuf/duration.upb_minitable.h"
#include "google/protobuf/timestamp.upb_minitable.h"

#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
static const upb_MiniTableSubInternal validate_FieldRules__submsgs[22] = {
  {.UPB_PRIVATE(submsg) = &validate__FloatRules_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &validate__DoubleRules_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &validate__Int32Rules_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &validate__Int64Rules_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &validate__UInt32Rules_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &validate__UInt64Rules_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &validate__SInt32Rules_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &validate__SInt64Rules_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &validate__Fixed32Rules_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &validate__Fixed64Rules_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &validate__SFixed32Rules_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &validate__SFixed64Rules_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &validate__BoolRules_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &validate__StringRules_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &validate__BytesRules_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &validate__EnumRules_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &validate__MessageRules_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &validate__RepeatedRules_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &validate__MapRules_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &validate__AnyRules_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &validate__DurationRules_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &validate__TimestampRules_msg_init_ptr},
};

static const upb_MiniTableField validate_FieldRules__fields[22] = {
  {1, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {6, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {7, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {8, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 7, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {9, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 8, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {10, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 9, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {11, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 10, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {12, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 11, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {13, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 12, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {14, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 13, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {15, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 14, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {16, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 15, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {17, UPB_SIZE(12, 16), 64, 16, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {18, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 17, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {19, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 18, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {20, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 19, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {21, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 20, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {22, UPB_SIZE(20, 24), UPB_SIZE(-17, -13), 21, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable validate__FieldRules_msg_init = {
  &validate_FieldRules__submsgs[0],
  &validate_FieldRules__fields[0],
  UPB_SIZE(24, 32), 22, kUpb_ExtMode_NonExtendable, 22, UPB_FASTTABLE_MASK(248), 0,
#ifdef UPB_TRACING_ENABLED
  "validate.FieldRules",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0018000c0100000a, &upb_pom_1bt_max64b},
    {0x0018000c02010012, &upb_pom_1bt_max128b},
    {0x0018000c0302001a, &upb_pom_1bt_max64b},
    {0x0018000c04030022, &upb_pom_1bt_max128b},
    {0x0018000c0504002a, &upb_pom_1bt_max64b},
    {0x0018000c06050032, &upb_pom_1bt_max128b},
    {0x0018000c0706003a, &upb_pom_1bt_max64b},
    {0x0018000c08070042, &upb_pom_1bt_max128b},
    {0x0018000c0908004a, &upb_pom_1bt_max64b},
    {0x0018000c0a090052, &upb_pom_1bt_max128b},
    {0x0018000c0b0a005a, &upb_pom_1bt_max64b},
    {0x0018000c0c0b0062, &upb_pom_1bt_max128b},
    {0x0018000c0d0c006a, &upb_pom_1bt_max64b},
    {0x0018000c0e0d0072, &upb_pom_1bt_max192b},
    {0x0018000c0f0e007a, &upb_pom_1bt_max192b},
    {0x0018000c100f0182, &upb_pom_2bt_max64b},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0018000c12110192, &upb_pom_2bt_max64b},
    {0x0018000c1312019a, &upb_pom_2bt_max64b},
    {0x0018000c141301a2, &upb_pom_2bt_max64b},
    {0x0018000c151401aa, &upb_pom_2bt_max128b},
    {0x0018000c161501b2, &upb_pom_2bt_max128b},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
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

const upb_MiniTable* validate__FieldRules_msg_init_ptr = &validate__FieldRules_msg_init;
static const upb_MiniTableField validate_FloatRules__fields[8] = {
  {1, 12, 64, kUpb_NoSub, 2, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {2, 16, 65, kUpb_NoSub, 2, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {3, 20, 66, kUpb_NoSub, 2, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {4, 24, 67, kUpb_NoSub, 2, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {5, 28, 68, kUpb_NoSub, 2, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {6, 32, 0, kUpb_NoSub, 2, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {7, UPB_SIZE(36, 40), 0, kUpb_NoSub, 2, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {8, 9, 69, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable validate__FloatRules_msg_init = {
  NULL,
  &validate_FloatRules__fields[0],
  UPB_SIZE(40, 48), 8, kUpb_ExtMode_NonExtendable, 8, UPB_FASTTABLE_MASK(56), 0,
#ifdef UPB_TRACING_ENABLED
  "validate.FloatRules",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x002000003f000035, &upb_prf4_1bt},
    {0x002800003f00003d, &upb_prf4_1bt},
  })
};

const upb_MiniTable* validate__FloatRules_msg_init_ptr = &validate__FloatRules_msg_init;
static const upb_MiniTableField validate_DoubleRules__fields[8] = {
  {1, UPB_SIZE(24, 16), 64, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(32, 24), 65, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(40, 32), 66, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(48, 40), 67, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(56, 48), 68, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {6, UPB_SIZE(12, 56), 0, kUpb_NoSub, 1, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {7, UPB_SIZE(16, 64), 0, kUpb_NoSub, 1, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {8, 9, 69, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable validate__DoubleRules_msg_init = {
  NULL,
  &validate_DoubleRules__fields[0],
  UPB_SIZE(64, 72), 8, kUpb_ExtMode_NonExtendable, 8, UPB_FASTTABLE_MASK(56), 0,
#ifdef UPB_TRACING_ENABLED
  "validate.DoubleRules",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x003800003f000031, &upb_prf8_1bt},
    {0x004000003f000039, &upb_prf8_1bt},
  })
};

const upb_MiniTable* validate__DoubleRules_msg_init_ptr = &validate__DoubleRules_msg_init;
static const upb_MiniTableField validate_Int32Rules__fields[8] = {
  {1, 12, 64, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {2, 16, 65, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {3, 20, 66, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {4, 24, 67, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {5, 28, 68, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {6, 32, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {7, UPB_SIZE(36, 40), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {8, 9, 69, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable validate__Int32Rules_msg_init = {
  NULL,
  &validate_Int32Rules__fields[0],
  UPB_SIZE(40, 48), 8, kUpb_ExtMode_NonExtendable, 8, UPB_FASTTABLE_MASK(56), 0,
#ifdef UPB_TRACING_ENABLED
  "validate.Int32Rules",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x002000003f000030, &upb_prv4_1bt},
    {0x002800003f000038, &upb_prv4_1bt},
  })
};

const upb_MiniTable* validate__Int32Rules_msg_init_ptr = &validate__Int32Rules_msg_init;
static const upb_MiniTableField validate_Int64Rules__fields[8] = {
  {1, UPB_SIZE(24, 16), 64, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(32, 24), 65, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(40, 32), 66, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(48, 40), 67, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(56, 48), 68, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {6, UPB_SIZE(12, 56), 0, kUpb_NoSub, 3, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {7, UPB_SIZE(16, 64), 0, kUpb_NoSub, 3, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {8, 9, 69, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable validate__Int64Rules_msg_init = {
  NULL,
  &validate_Int64Rules__fields[0],
  UPB_SIZE(64, 72), 8, kUpb_ExtMode_NonExtendable, 8, UPB_FASTTABLE_MASK(56), 0,
#ifdef UPB_TRACING_ENABLED
  "validate.Int64Rules",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x003800003f000030, &upb_prv8_1bt},
    {0x004000003f000038, &upb_prv8_1bt},
  })
};

const upb_MiniTable* validate__Int64Rules_msg_init_ptr = &validate__Int64Rules_msg_init;
static const upb_MiniTableField validate_UInt32Rules__fields[8] = {
  {1, 12, 64, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {2, 16, 65, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {3, 20, 66, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {4, 24, 67, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {5, 28, 68, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {6, 32, 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {7, UPB_SIZE(36, 40), 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {8, 9, 69, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable validate__UInt32Rules_msg_init = {
  NULL,
  &validate_UInt32Rules__fields[0],
  UPB_SIZE(40, 48), 8, kUpb_ExtMode_NonExtendable, 8, UPB_FASTTABLE_MASK(56), 0,
#ifdef UPB_TRACING_ENABLED
  "validate.UInt32Rules",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x002000003f000030, &upb_prv4_1bt},
    {0x002800003f000038, &upb_prv4_1bt},
  })
};

const upb_MiniTable* validate__UInt32Rules_msg_init_ptr = &validate__UInt32Rules_msg_init;
static const upb_MiniTableField validate_UInt64Rules__fields[8] = {
  {1, UPB_SIZE(24, 16), 64, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(32, 24), 65, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(40, 32), 66, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(48, 40), 67, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(56, 48), 68, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {6, UPB_SIZE(12, 56), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {7, UPB_SIZE(16, 64), 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {8, 9, 69, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable validate__UInt64Rules_msg_init = {
  NULL,
  &validate_UInt64Rules__fields[0],
  UPB_SIZE(64, 72), 8, kUpb_ExtMode_NonExtendable, 8, UPB_FASTTABLE_MASK(56), 0,
#ifdef UPB_TRACING_ENABLED
  "validate.UInt64Rules",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x003800003f000030, &upb_prv8_1bt},
    {0x004000003f000038, &upb_prv8_1bt},
  })
};

const upb_MiniTable* validate__UInt64Rules_msg_init_ptr = &validate__UInt64Rules_msg_init;
static const upb_MiniTableField validate_SInt32Rules__fields[8] = {
  {1, 12, 64, kUpb_NoSub, 17, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {2, 16, 65, kUpb_NoSub, 17, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {3, 20, 66, kUpb_NoSub, 17, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {4, 24, 67, kUpb_NoSub, 17, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {5, 28, 68, kUpb_NoSub, 17, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {6, 32, 0, kUpb_NoSub, 17, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {7, UPB_SIZE(36, 40), 0, kUpb_NoSub, 17, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {8, 9, 69, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable validate__SInt32Rules_msg_init = {
  NULL,
  &validate_SInt32Rules__fields[0],
  UPB_SIZE(40, 48), 8, kUpb_ExtMode_NonExtendable, 8, UPB_FASTTABLE_MASK(56), 0,
#ifdef UPB_TRACING_ENABLED
  "validate.SInt32Rules",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x002000003f000030, &upb_prz4_1bt},
    {0x002800003f000038, &upb_prz4_1bt},
  })
};

const upb_MiniTable* validate__SInt32Rules_msg_init_ptr = &validate__SInt32Rules_msg_init;
static const upb_MiniTableField validate_SInt64Rules__fields[8] = {
  {1, UPB_SIZE(24, 16), 64, kUpb_NoSub, 18, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(32, 24), 65, kUpb_NoSub, 18, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(40, 32), 66, kUpb_NoSub, 18, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(48, 40), 67, kUpb_NoSub, 18, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(56, 48), 68, kUpb_NoSub, 18, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {6, UPB_SIZE(12, 56), 0, kUpb_NoSub, 18, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {7, UPB_SIZE(16, 64), 0, kUpb_NoSub, 18, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {8, 9, 69, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable validate__SInt64Rules_msg_init = {
  NULL,
  &validate_SInt64Rules__fields[0],
  UPB_SIZE(64, 72), 8, kUpb_ExtMode_NonExtendable, 8, UPB_FASTTABLE_MASK(56), 0,
#ifdef UPB_TRACING_ENABLED
  "validate.SInt64Rules",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x003800003f000030, &upb_prz8_1bt},
    {0x004000003f000038, &upb_prz8_1bt},
  })
};

const upb_MiniTable* validate__SInt64Rules_msg_init_ptr = &validate__SInt64Rules_msg_init;
static const upb_MiniTableField validate_Fixed32Rules__fields[8] = {
  {1, 12, 64, kUpb_NoSub, 7, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {2, 16, 65, kUpb_NoSub, 7, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {3, 20, 66, kUpb_NoSub, 7, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {4, 24, 67, kUpb_NoSub, 7, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {5, 28, 68, kUpb_NoSub, 7, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {6, 32, 0, kUpb_NoSub, 7, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {7, UPB_SIZE(36, 40), 0, kUpb_NoSub, 7, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {8, 9, 69, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable validate__Fixed32Rules_msg_init = {
  NULL,
  &validate_Fixed32Rules__fields[0],
  UPB_SIZE(40, 48), 8, kUpb_ExtMode_NonExtendable, 8, UPB_FASTTABLE_MASK(56), 0,
#ifdef UPB_TRACING_ENABLED
  "validate.Fixed32Rules",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x002000003f000035, &upb_prf4_1bt},
    {0x002800003f00003d, &upb_prf4_1bt},
  })
};

const upb_MiniTable* validate__Fixed32Rules_msg_init_ptr = &validate__Fixed32Rules_msg_init;
static const upb_MiniTableField validate_Fixed64Rules__fields[8] = {
  {1, UPB_SIZE(24, 16), 64, kUpb_NoSub, 6, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(32, 24), 65, kUpb_NoSub, 6, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(40, 32), 66, kUpb_NoSub, 6, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(48, 40), 67, kUpb_NoSub, 6, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(56, 48), 68, kUpb_NoSub, 6, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {6, UPB_SIZE(12, 56), 0, kUpb_NoSub, 6, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {7, UPB_SIZE(16, 64), 0, kUpb_NoSub, 6, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {8, 9, 69, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable validate__Fixed64Rules_msg_init = {
  NULL,
  &validate_Fixed64Rules__fields[0],
  UPB_SIZE(64, 72), 8, kUpb_ExtMode_NonExtendable, 8, UPB_FASTTABLE_MASK(56), 0,
#ifdef UPB_TRACING_ENABLED
  "validate.Fixed64Rules",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x003800003f000031, &upb_prf8_1bt},
    {0x004000003f000039, &upb_prf8_1bt},
  })
};

const upb_MiniTable* validate__Fixed64Rules_msg_init_ptr = &validate__Fixed64Rules_msg_init;
static const upb_MiniTableField validate_SFixed32Rules__fields[8] = {
  {1, 12, 64, kUpb_NoSub, 15, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {2, 16, 65, kUpb_NoSub, 15, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {3, 20, 66, kUpb_NoSub, 15, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {4, 24, 67, kUpb_NoSub, 15, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {5, 28, 68, kUpb_NoSub, 15, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {6, 32, 0, kUpb_NoSub, 15, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {7, UPB_SIZE(36, 40), 0, kUpb_NoSub, 15, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {8, 9, 69, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable validate__SFixed32Rules_msg_init = {
  NULL,
  &validate_SFixed32Rules__fields[0],
  UPB_SIZE(40, 48), 8, kUpb_ExtMode_NonExtendable, 8, UPB_FASTTABLE_MASK(56), 0,
#ifdef UPB_TRACING_ENABLED
  "validate.SFixed32Rules",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x002000003f000035, &upb_prf4_1bt},
    {0x002800003f00003d, &upb_prf4_1bt},
  })
};

const upb_MiniTable* validate__SFixed32Rules_msg_init_ptr = &validate__SFixed32Rules_msg_init;
static const upb_MiniTableField validate_SFixed64Rules__fields[8] = {
  {1, UPB_SIZE(24, 16), 64, kUpb_NoSub, 16, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(32, 24), 65, kUpb_NoSub, 16, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(40, 32), 66, kUpb_NoSub, 16, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(48, 40), 67, kUpb_NoSub, 16, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(56, 48), 68, kUpb_NoSub, 16, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {6, UPB_SIZE(12, 56), 0, kUpb_NoSub, 16, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {7, UPB_SIZE(16, 64), 0, kUpb_NoSub, 16, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {8, 9, 69, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable validate__SFixed64Rules_msg_init = {
  NULL,
  &validate_SFixed64Rules__fields[0],
  UPB_SIZE(64, 72), 8, kUpb_ExtMode_NonExtendable, 8, UPB_FASTTABLE_MASK(56), 0,
#ifdef UPB_TRACING_ENABLED
  "validate.SFixed64Rules",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x003800003f000031, &upb_prf8_1bt},
    {0x004000003f000039, &upb_prf8_1bt},
  })
};

const upb_MiniTable* validate__SFixed64Rules_msg_init_ptr = &validate__SFixed64Rules_msg_init;
static const upb_MiniTableField validate_BoolRules__fields[1] = {
  {1, 9, 64, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable validate__BoolRules_msg_init = {
  NULL,
  &validate_BoolRules__fields[0],
  16, 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "validate.BoolRules",
#endif
};

const upb_MiniTable* validate__BoolRules_msg_init_ptr = &validate__BoolRules_msg_init;
static const upb_MiniTableSubInternal validate_StringRules__submsgs[1] = {
  {.UPB_PRIVATE(subenum) = &validate__KnownRegex_enum_init},
};

static const upb_MiniTableField validate_StringRules__fields[26] = {
  {1, UPB_SIZE(28, 24), 64, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(80, 120), 65, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(88, 128), 66, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(96, 136), 67, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(104, 144), 68, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {6, UPB_SIZE(36, 40), 69, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {7, UPB_SIZE(44, 56), 70, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {8, UPB_SIZE(52, 72), 71, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {9, UPB_SIZE(60, 88), 72, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {10, UPB_SIZE(12, 152), 0, kUpb_NoSub, 12, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsAlternate | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {11, UPB_SIZE(16, 160), 0, kUpb_NoSub, 12, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsAlternate | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {12, UPB_SIZE(24, 16), UPB_SIZE(-21, -13), kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {13, UPB_SIZE(24, 16), UPB_SIZE(-21, -13), kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {14, UPB_SIZE(24, 16), UPB_SIZE(-21, -13), kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {15, UPB_SIZE(24, 16), UPB_SIZE(-21, -13), kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {16, UPB_SIZE(24, 16), UPB_SIZE(-21, -13), kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {17, UPB_SIZE(24, 16), UPB_SIZE(-21, -13), kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {18, UPB_SIZE(24, 16), UPB_SIZE(-21, -13), kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {19, UPB_SIZE(112, 168), 73, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {20, UPB_SIZE(120, 176), 74, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {21, UPB_SIZE(24, 16), UPB_SIZE(-21, -13), kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {22, UPB_SIZE(24, 16), UPB_SIZE(-21, -13), kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {23, UPB_SIZE(68, 104), 75, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {24, UPB_SIZE(24, 16), UPB_SIZE(-21, -13), 0, 14, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {25, 10, 76, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {26, 11, 77, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable validate__StringRules_msg_init = {
  &validate_StringRules__submsgs[0],
  &validate_StringRules__fields[0],
  UPB_SIZE(128, 184), 26, kUpb_ExtMode_NonExtendable, 26, UPB_FASTTABLE_MASK(248), 0,
#ifdef UPB_TRACING_ENABLED
  "validate.StringRules",
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
    {0x009800003f000052, &upb_prs_1bt},
    {0x00a000003f00005a, &upb_prs_1bt},
    {0x0010000c0c000060, &upb_pob1_1bt},
    {0x0010000c0d000068, &upb_pob1_1bt},
    {0x0010000c0e000070, &upb_pob1_1bt},
    {0x0010000c0f000078, &upb_pob1_1bt},
    {0x0010000c10000180, &upb_pob1_2bt},
    {0x0010000c11000188, &upb_pob1_2bt},
    {0x0010000c12000190, &upb_pob1_2bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0010000c150001a8, &upb_pob1_2bt},
    {0x0010000c160001b0, &upb_pob1_2bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
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

const upb_MiniTable* validate__StringRules_msg_init_ptr = &validate__StringRules_msg_init;
static const upb_MiniTableField validate_BytesRules__fields[14] = {
  {1, UPB_SIZE(24, 16), 64, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(64, 96), 65, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(72, 104), 66, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {4, 32, 67, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(40, 48), 68, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {6, UPB_SIZE(48, 64), 69, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {7, UPB_SIZE(56, 80), 70, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {8, UPB_SIZE(12, 112), 0, kUpb_NoSub, 12, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {9, UPB_SIZE(16, 120), 0, kUpb_NoSub, 12, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {10, 11, UPB_SIZE(-21, -13), kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {11, 11, UPB_SIZE(-21, -13), kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {12, 11, UPB_SIZE(-21, -13), kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {13, UPB_SIZE(80, 128), 71, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {14, 10, 72, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable validate__BytesRules_msg_init = {
  NULL,
  &validate_BytesRules__fields[0],
  UPB_SIZE(88, 136), 14, kUpb_ExtMode_NonExtendable, 14, UPB_FASTTABLE_MASK(120), 0,
#ifdef UPB_TRACING_ENABLED
  "validate.BytesRules",
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
    {0x007000003f000042, &upb_prb_1bt},
    {0x007800003f00004a, &upb_prb_1bt},
    {0x000b000c0a000050, &upb_pob1_1bt},
    {0x000b000c0b000058, &upb_pob1_1bt},
    {0x000b000c0c000060, &upb_pob1_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* validate__BytesRules_msg_init_ptr = &validate__BytesRules_msg_init;
static const upb_MiniTableField validate_EnumRules__fields[4] = {
  {1, 12, 64, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {2, 9, 65, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {3, 16, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(20, 24), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable validate__EnumRules_msg_init = {
  NULL,
  &validate_EnumRules__fields[0],
  UPB_SIZE(24, 32), 4, kUpb_ExtMode_NonExtendable, 4, UPB_FASTTABLE_MASK(56), 0,
#ifdef UPB_TRACING_ENABLED
  "validate.EnumRules",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f000018, &upb_prv4_1bt},
    {0x001800003f000020, &upb_prv4_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* validate__EnumRules_msg_init_ptr = &validate__EnumRules_msg_init;
static const upb_MiniTableField validate_MessageRules__fields[2] = {
  {1, 9, 64, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {2, 10, 65, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable validate__MessageRules_msg_init = {
  NULL,
  &validate_MessageRules__fields[0],
  16, 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "validate.MessageRules",
#endif
};

const upb_MiniTable* validate__MessageRules_msg_init_ptr = &validate__MessageRules_msg_init;
static const upb_MiniTableSubInternal validate_RepeatedRules__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &validate__FieldRules_msg_init_ptr},
};

static const upb_MiniTableField validate_RepeatedRules__fields[5] = {
  {1, 16, 64, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {2, 24, 65, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {3, 9, 66, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(12, 32), 67, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {5, 10, 68, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable validate__RepeatedRules_msg_init = {
  &validate_RepeatedRules__submsgs[0],
  &validate_RepeatedRules__fields[0],
  UPB_SIZE(32, 40), 5, kUpb_ExtMode_NonExtendable, 5, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "validate.RepeatedRules",
#endif
};

const upb_MiniTable* validate__RepeatedRules_msg_init_ptr = &validate__RepeatedRules_msg_init;
static const upb_MiniTableSubInternal validate_MapRules__submsgs[2] = {
  {.UPB_PRIVATE(submsg) = &validate__FieldRules_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &validate__FieldRules_msg_init_ptr},
};

static const upb_MiniTableField validate_MapRules__fields[6] = {
  {1, UPB_SIZE(24, 16), 64, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(32, 24), 65, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {3, 9, 66, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(12, 32), 67, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(16, 40), 68, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {6, 10, 69, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable validate__MapRules_msg_init = {
  &validate_MapRules__submsgs[0],
  &validate_MapRules__fields[0],
  UPB_SIZE(40, 48), 6, kUpb_ExtMode_NonExtendable, 6, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "validate.MapRules",
#endif
};

const upb_MiniTable* validate__MapRules_msg_init_ptr = &validate__MapRules_msg_init;
static const upb_MiniTableField validate_AnyRules__fields[3] = {
  {1, 9, 64, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 16), 0, kUpb_NoSub, 12, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsAlternate | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(16, 24), 0, kUpb_NoSub, 12, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsAlternate | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable validate__AnyRules_msg_init = {
  NULL,
  &validate_AnyRules__fields[0],
  UPB_SIZE(24, 32), 3, kUpb_ExtMode_NonExtendable, 3, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "validate.AnyRules",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f000012, &upb_prs_1bt},
    {0x001800003f00001a, &upb_prs_1bt},
  })
};

const upb_MiniTable* validate__AnyRules_msg_init_ptr = &validate__AnyRules_msg_init;
static const upb_MiniTableSubInternal validate_DurationRules__submsgs[7] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__Duration_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__Duration_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__Duration_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__Duration_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__Duration_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__Duration_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__Duration_msg_init_ptr},
};

static const upb_MiniTableField validate_DurationRules__fields[8] = {
  {1, 9, 64, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 16), 65, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(16, 24), 66, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(20, 32), 67, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(24, 40), 68, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {6, UPB_SIZE(28, 48), 69, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {7, UPB_SIZE(32, 56), 0, 5, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {8, UPB_SIZE(36, 64), 0, 6, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable validate__DurationRules_msg_init = {
  &validate_DurationRules__submsgs[0],
  &validate_DurationRules__fields[0],
  UPB_SIZE(40, 72), 8, kUpb_ExtMode_NonExtendable, 8, UPB_FASTTABLE_MASK(120), 0,
#ifdef UPB_TRACING_ENABLED
  "validate.DurationRules",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x003800003f05003a, &upb_prm_1bt_maxmaxb},
    {0x004000003f060042, &upb_prm_1bt_maxmaxb},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* validate__DurationRules_msg_init_ptr = &validate__DurationRules_msg_init;
static const upb_MiniTableSubInternal validate_TimestampRules__submsgs[6] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__Timestamp_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__Timestamp_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__Timestamp_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__Timestamp_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__Timestamp_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__Duration_msg_init_ptr},
};

static const upb_MiniTableField validate_TimestampRules__fields[9] = {
  {1, 10, 64, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {2, 16, 65, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(20, 24), 66, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(24, 32), 67, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(28, 40), 68, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {6, UPB_SIZE(32, 48), 69, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {7, 11, 70, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {8, 12, 71, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {9, UPB_SIZE(36, 56), 72, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable validate__TimestampRules_msg_init = {
  &validate_TimestampRules__submsgs[0],
  &validate_TimestampRules__fields[0],
  UPB_SIZE(40, 64), 9, kUpb_ExtMode_NonExtendable, 9, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "validate.TimestampRules",
#endif
};

const upb_MiniTable* validate__TimestampRules_msg_init_ptr = &validate__TimestampRules_msg_init;
const upb_MiniTableEnum validate__KnownRegex_enum_init = {
    64,
    0,
    {
        0x7,
        0x0,
    },
};

UPB_LINKARR_APPEND(upb_AllExts)
const upb_MiniTableExtension validate_disabled_ext = {
  {1071, 0, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsExtension | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  &google__protobuf__MessageOptions_msg_init,
  {.UPB_PRIVATE(submsg) = NULL},

};
UPB_LINKARR_APPEND(upb_AllExts)
const upb_MiniTableExtension validate_ignored_ext = {
  {1072, 0, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsExtension | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  &google__protobuf__MessageOptions_msg_init,
  {.UPB_PRIVATE(submsg) = NULL},

};
UPB_LINKARR_APPEND(upb_AllExts)
const upb_MiniTableExtension validate_required_ext = {
  {1071, 0, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsExtension | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  &google__protobuf__OneofOptions_msg_init,
  {.UPB_PRIVATE(submsg) = NULL},

};
UPB_LINKARR_APPEND(upb_AllExts)
const upb_MiniTableExtension validate_rules_ext = {
  {1071, 0, 0, 0, 11, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsExtension | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  &google__protobuf__FieldOptions_msg_init,
  {.UPB_PRIVATE(submsg) = &validate__FieldRules_msg_init},

};
static const upb_MiniTable *messages_layout[23] = {
  &validate__FieldRules_msg_init,
  &validate__FloatRules_msg_init,
  &validate__DoubleRules_msg_init,
  &validate__Int32Rules_msg_init,
  &validate__Int64Rules_msg_init,
  &validate__UInt32Rules_msg_init,
  &validate__UInt64Rules_msg_init,
  &validate__SInt32Rules_msg_init,
  &validate__SInt64Rules_msg_init,
  &validate__Fixed32Rules_msg_init,
  &validate__Fixed64Rules_msg_init,
  &validate__SFixed32Rules_msg_init,
  &validate__SFixed64Rules_msg_init,
  &validate__BoolRules_msg_init,
  &validate__StringRules_msg_init,
  &validate__BytesRules_msg_init,
  &validate__EnumRules_msg_init,
  &validate__MessageRules_msg_init,
  &validate__RepeatedRules_msg_init,
  &validate__MapRules_msg_init,
  &validate__AnyRules_msg_init,
  &validate__DurationRules_msg_init,
  &validate__TimestampRules_msg_init,
};

static const upb_MiniTableEnum *enums_layout[1] = {
  &validate__KnownRegex_enum_init,
};

static const upb_MiniTableExtension *extensions_layout[4] = {
  &validate_disabled_ext,
  &validate_ignored_ext,
  &validate_required_ext,
  &validate_rules_ext,
};

const upb_MiniTableFile validate_validate_proto_upb_file_layout = {
  messages_layout,
  enums_layout,
  extensions_layout,
  23,
  1,
  4,
};

#include "upb/port/undef.inc"
