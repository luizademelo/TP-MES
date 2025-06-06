
#include <stddef.h>
#include "upb/generated_code_support.h"
#include "google/api/expr/v1alpha1/checked.upb_minitable.h"
#include "google/api/expr/v1alpha1/syntax.upb_minitable.h"
#include "google/protobuf/empty.upb_minitable.h"
#include "google/protobuf/struct.upb_minitable.h"

#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
static const upb_MiniTableSubInternal google_api_expr_v1alpha1_CheckedExpr__submsgs[4] = {
  {.UPB_PRIVATE(submsg) = &google__api__expr__v1alpha1__CheckedExpr__ReferenceMapEntry_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__api__expr__v1alpha1__CheckedExpr__TypeMapEntry_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__api__expr__v1alpha1__Expr_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__api__expr__v1alpha1__SourceInfo_msg_init_ptr},
};

static const upb_MiniTableField google_api_expr_v1alpha1_CheckedExpr__fields[5] = {
  {2, UPB_SIZE(12, 32), 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(16, 40), 0, 1, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(20, 48), 64, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(24, 56), 65, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {6, UPB_SIZE(28, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
};

const upb_MiniTable google__api__expr__v1alpha1__CheckedExpr_msg_init = {
  &google_api_expr_v1alpha1_CheckedExpr__submsgs[0],
  &google_api_expr_v1alpha1_CheckedExpr__fields[0],
  UPB_SIZE(40, 64), 5, kUpb_ExtMode_NonExtendable, 0, UPB_FASTTABLE_MASK(56), 0,
#ifdef UPB_TRACING_ENABLED
  "google.api.expr.v1alpha1.CheckedExpr",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f000032, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* google__api__expr__v1alpha1__CheckedExpr_msg_init_ptr = &google__api__expr__v1alpha1__CheckedExpr_msg_init;
static const upb_MiniTableSubInternal google_api_expr_v1alpha1_CheckedExpr_ReferenceMapEntry__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &google__api__expr__v1alpha1__Reference_msg_init_ptr},
};

static const upb_MiniTableField google_api_expr_v1alpha1_CheckedExpr_ReferenceMapEntry__fields[2] = {
  {1, 16, 0, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {2, 32, 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable google__api__expr__v1alpha1__CheckedExpr__ReferenceMapEntry_msg_init = {
  &google_api_expr_v1alpha1_CheckedExpr_ReferenceMapEntry__submsgs[0],
  &google_api_expr_v1alpha1_CheckedExpr_ReferenceMapEntry__fields[0],
  48, 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "google.api.expr.v1alpha1.CheckedExpr.ReferenceMapEntry",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f000008, &upb_psv8_1bt},
  })
};

const upb_MiniTable* google__api__expr__v1alpha1__CheckedExpr__ReferenceMapEntry_msg_init_ptr = &google__api__expr__v1alpha1__CheckedExpr__ReferenceMapEntry_msg_init;
static const upb_MiniTableSubInternal google_api_expr_v1alpha1_CheckedExpr_TypeMapEntry__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &google__api__expr__v1alpha1__Type_msg_init_ptr},
};

static const upb_MiniTableField google_api_expr_v1alpha1_CheckedExpr_TypeMapEntry__fields[2] = {
  {1, 16, 0, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {2, 32, 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable google__api__expr__v1alpha1__CheckedExpr__TypeMapEntry_msg_init = {
  &google_api_expr_v1alpha1_CheckedExpr_TypeMapEntry__submsgs[0],
  &google_api_expr_v1alpha1_CheckedExpr_TypeMapEntry__fields[0],
  48, 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "google.api.expr.v1alpha1.CheckedExpr.TypeMapEntry",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f000008, &upb_psv8_1bt},
  })
};

const upb_MiniTable* google__api__expr__v1alpha1__CheckedExpr__TypeMapEntry_msg_init_ptr = &google__api__expr__v1alpha1__CheckedExpr__TypeMapEntry_msg_init;
static const upb_MiniTableSubInternal google_api_expr_v1alpha1_Type__submsgs[7] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__Empty_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__api__expr__v1alpha1__Type__ListType_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__api__expr__v1alpha1__Type__MapType_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__api__expr__v1alpha1__Type__FunctionType_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__api__expr__v1alpha1__Type_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__Empty_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__api__expr__v1alpha1__Type__AbstractType_msg_init_ptr},
};

static const upb_MiniTableField google_api_expr_v1alpha1_Type__fields[13] = {
  {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 16), -9, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(12, 16), -9, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(12, 16), -9, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(12, 16), -9, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {6, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {7, UPB_SIZE(12, 16), -9, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {8, UPB_SIZE(12, 16), -9, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {9, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {10, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {11, UPB_SIZE(12, 16), -9, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {12, UPB_SIZE(12, 16), -9, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {14, UPB_SIZE(12, 16), -9, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable google__api__expr__v1alpha1__Type_msg_init = {
  &google_api_expr_v1alpha1_Type__submsgs[0],
  &google_api_expr_v1alpha1_Type__fields[0],
  UPB_SIZE(24, 32), 13, kUpb_ExtMode_NonExtendable, 12, UPB_FASTTABLE_MASK(120), 0,
#ifdef UPB_TRACING_ENABLED
  "google.api.expr.v1alpha1.Type",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000080100000a, &upb_pom_1bt_maxmaxb},
    {0x0010000802000010, &upb_pov4_1bt},
    {0x0010000803000018, &upb_pov4_1bt},
    {0x0010000804000020, &upb_pov4_1bt},
    {0x0010000805000028, &upb_pov4_1bt},
    {0x0010000806010032, &upb_pom_1bt_max64b},
    {0x001000080702003a, &upb_pom_1bt_max64b},
    {0x0010000808030042, &upb_pom_1bt_max64b},
    {0x001000080900004a, &upb_pos_1bt},
    {0x001000080a000052, &upb_pos_1bt},
    {0x001000080b04005a, &upb_pom_1bt_max64b},
    {0x001000080c050062, &upb_pom_1bt_maxmaxb},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000080e060072, &upb_pom_1bt_max64b},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* google__api__expr__v1alpha1__Type_msg_init_ptr = &google__api__expr__v1alpha1__Type_msg_init;
static const upb_MiniTableSubInternal google_api_expr_v1alpha1_Type_ListType__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &google__api__expr__v1alpha1__Type_msg_init_ptr},
};

static const upb_MiniTableField google_api_expr_v1alpha1_Type_ListType__fields[1] = {
  {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable google__api__expr__v1alpha1__Type__ListType_msg_init = {
  &google_api_expr_v1alpha1_Type_ListType__submsgs[0],
  &google_api_expr_v1alpha1_Type_ListType__fields[0],
  UPB_SIZE(16, 24), 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "google.api.expr.v1alpha1.Type.ListType",
#endif
};

const upb_MiniTable* google__api__expr__v1alpha1__Type__ListType_msg_init_ptr = &google__api__expr__v1alpha1__Type__ListType_msg_init;
static const upb_MiniTableSubInternal google_api_expr_v1alpha1_Type_MapType__submsgs[2] = {
  {.UPB_PRIVATE(submsg) = &google__api__expr__v1alpha1__Type_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__api__expr__v1alpha1__Type_msg_init_ptr},
};

static const upb_MiniTableField google_api_expr_v1alpha1_Type_MapType__fields[2] = {
  {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable google__api__expr__v1alpha1__Type__MapType_msg_init = {
  &google_api_expr_v1alpha1_Type_MapType__submsgs[0],
  &google_api_expr_v1alpha1_Type_MapType__fields[0],
  UPB_SIZE(24, 32), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "google.api.expr.v1alpha1.Type.MapType",
#endif
};

const upb_MiniTable* google__api__expr__v1alpha1__Type__MapType_msg_init_ptr = &google__api__expr__v1alpha1__Type__MapType_msg_init;
static const upb_MiniTableSubInternal google_api_expr_v1alpha1_Type_FunctionType__submsgs[2] = {
  {.UPB_PRIVATE(submsg) = &google__api__expr__v1alpha1__Type_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__api__expr__v1alpha1__Type_msg_init_ptr},
};

static const upb_MiniTableField google_api_expr_v1alpha1_Type_FunctionType__fields[2] = {
  {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 24), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable google__api__expr__v1alpha1__Type__FunctionType_msg_init = {
  &google_api_expr_v1alpha1_Type_FunctionType__submsgs[0],
  &google_api_expr_v1alpha1_Type_FunctionType__fields[0],
  UPB_SIZE(24, 32), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "google.api.expr.v1alpha1.Type.FunctionType",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001800003f010012, &upb_prm_1bt_max64b},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* google__api__expr__v1alpha1__Type__FunctionType_msg_init_ptr = &google__api__expr__v1alpha1__Type__FunctionType_msg_init;
static const upb_MiniTableSubInternal google_api_expr_v1alpha1_Type_AbstractType__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &google__api__expr__v1alpha1__Type_msg_init_ptr},
};

static const upb_MiniTableField google_api_expr_v1alpha1_Type_AbstractType__fields[2] = {
  {1, UPB_SIZE(12, 8), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(8, 24), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable google__api__expr__v1alpha1__Type__AbstractType_msg_init = {
  &google_api_expr_v1alpha1_Type_AbstractType__submsgs[0],
  &google_api_expr_v1alpha1_Type_AbstractType__fields[0],
  UPB_SIZE(24, 32), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "google.api.expr.v1alpha1.Type.AbstractType",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f00000a, &upb_pss_1bt},
    {0x001800003f000012, &upb_prm_1bt_max64b},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* google__api__expr__v1alpha1__Type__AbstractType_msg_init_ptr = &google__api__expr__v1alpha1__Type__AbstractType_msg_init;
static const upb_MiniTableSubInternal google_api_expr_v1alpha1_Decl__submsgs[2] = {
  {.UPB_PRIVATE(submsg) = &google__api__expr__v1alpha1__Decl__IdentDecl_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__api__expr__v1alpha1__Decl__FunctionDecl_msg_init_ptr},
};

static const upb_MiniTableField google_api_expr_v1alpha1_Decl__fields[3] = {
  {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(12, 32), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable google__api__expr__v1alpha1__Decl_msg_init = {
  &google_api_expr_v1alpha1_Decl__submsgs[0],
  &google_api_expr_v1alpha1_Decl__fields[0],
  UPB_SIZE(24, 40), 3, kUpb_ExtMode_NonExtendable, 3, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "google.api.expr.v1alpha1.Decl",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
    {0x0020000802000012, &upb_pom_1bt_max64b},
    {0x002000080301001a, &upb_pom_1bt_max64b},
  })
};

const upb_MiniTable* google__api__expr__v1alpha1__Decl_msg_init_ptr = &google__api__expr__v1alpha1__Decl_msg_init;
static const upb_MiniTableSubInternal google_api_expr_v1alpha1_Decl_IdentDecl__submsgs[2] = {
  {.UPB_PRIVATE(submsg) = &google__api__expr__v1alpha1__Type_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__api__expr__v1alpha1__Constant_msg_init_ptr},
};

static const upb_MiniTableField google_api_expr_v1alpha1_Decl_IdentDecl__fields[3] = {
  {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
};

const upb_MiniTable google__api__expr__v1alpha1__Decl__IdentDecl_msg_init = {
  &google_api_expr_v1alpha1_Decl_IdentDecl__submsgs[0],
  &google_api_expr_v1alpha1_Decl_IdentDecl__fields[0],
  UPB_SIZE(32, 48), 3, kUpb_ExtMode_NonExtendable, 3, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "google.api.expr.v1alpha1.Decl.IdentDecl",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00001a, &upb_pss_1bt},
  })
};

const upb_MiniTable* google__api__expr__v1alpha1__Decl__IdentDecl_msg_init_ptr = &google__api__expr__v1alpha1__Decl__IdentDecl_msg_init;
static const upb_MiniTableSubInternal google_api_expr_v1alpha1_Decl_FunctionDecl__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &google__api__expr__v1alpha1__Decl__FunctionDecl__Overload_msg_init_ptr},
};

static const upb_MiniTableField google_api_expr_v1alpha1_Decl_FunctionDecl__fields[1] = {
  {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable google__api__expr__v1alpha1__Decl__FunctionDecl_msg_init = {
  &google_api_expr_v1alpha1_Decl_FunctionDecl__submsgs[0],
  &google_api_expr_v1alpha1_Decl_FunctionDecl__fields[0],
  16, 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "google.api.expr.v1alpha1.Decl.FunctionDecl",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f00000a, &upb_prm_1bt_max128b},
  })
};

const upb_MiniTable* google__api__expr__v1alpha1__Decl__FunctionDecl_msg_init_ptr = &google__api__expr__v1alpha1__Decl__FunctionDecl_msg_init;
static const upb_MiniTableSubInternal google_api_expr_v1alpha1_Decl_FunctionDecl_Overload__submsgs[2] = {
  {.UPB_PRIVATE(submsg) = &google__api__expr__v1alpha1__Type_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__api__expr__v1alpha1__Type_msg_init_ptr},
};

static const upb_MiniTableField google_api_expr_v1alpha1_Decl_FunctionDecl_Overload__fields[6] = {
  {1, UPB_SIZE(24, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 48), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(16, 56), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(20, 64), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {5, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {6, 32, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
};

const upb_MiniTable google__api__expr__v1alpha1__Decl__FunctionDecl__Overload_msg_init = {
  &google_api_expr_v1alpha1_Decl_FunctionDecl_Overload__submsgs[0],
  &google_api_expr_v1alpha1_Decl_FunctionDecl_Overload__fields[0],
  UPB_SIZE(40, 72), 6, kUpb_ExtMode_NonExtendable, 6, UPB_FASTTABLE_MASK(56), 0,
#ifdef UPB_TRACING_ENABLED
  "google.api.expr.v1alpha1.Decl.FunctionDecl.Overload",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
    {0x003000003f000012, &upb_prm_1bt_max64b},
    {0x003800003f00001a, &upb_prs_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000900003f000028, &upb_psb1_1bt},
    {0x002000003f000032, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* google__api__expr__v1alpha1__Decl__FunctionDecl__Overload_msg_init_ptr = &google__api__expr__v1alpha1__Decl__FunctionDecl__Overload_msg_init;
static const upb_MiniTableSubInternal google_api_expr_v1alpha1_Reference__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &google__api__expr__v1alpha1__Constant_msg_init_ptr},
};

static const upb_MiniTableField google_api_expr_v1alpha1_Reference__fields[3] = {
  {1, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(12, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(16, 40), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable google__api__expr__v1alpha1__Reference_msg_init = {
  &google_api_expr_v1alpha1_Reference__submsgs[0],
  &google_api_expr_v1alpha1_Reference__fields[0],
  UPB_SIZE(32, 48), 3, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "google.api.expr.v1alpha1.Reference",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x002000003f00001a, &upb_prs_1bt},
  })
};

const upb_MiniTable* google__api__expr__v1alpha1__Reference_msg_init_ptr = &google__api__expr__v1alpha1__Reference_msg_init;
static const upb_MiniTable *messages_layout[13] = {
  &google__api__expr__v1alpha1__CheckedExpr_msg_init,
  &google__api__expr__v1alpha1__CheckedExpr__ReferenceMapEntry_msg_init,
  &google__api__expr__v1alpha1__CheckedExpr__TypeMapEntry_msg_init,
  &google__api__expr__v1alpha1__Type_msg_init,
  &google__api__expr__v1alpha1__Type__ListType_msg_init,
  &google__api__expr__v1alpha1__Type__MapType_msg_init,
  &google__api__expr__v1alpha1__Type__FunctionType_msg_init,
  &google__api__expr__v1alpha1__Type__AbstractType_msg_init,
  &google__api__expr__v1alpha1__Decl_msg_init,
  &google__api__expr__v1alpha1__Decl__IdentDecl_msg_init,
  &google__api__expr__v1alpha1__Decl__FunctionDecl_msg_init,
  &google__api__expr__v1alpha1__Decl__FunctionDecl__Overload_msg_init,
  &google__api__expr__v1alpha1__Reference_msg_init,
};

const upb_MiniTableFile google_api_expr_v1alpha1_checked_proto_upb_file_layout = {
  messages_layout,
  NULL,
  NULL,
  13,
  0,
  0,
};

#include "upb/port/undef.inc"
