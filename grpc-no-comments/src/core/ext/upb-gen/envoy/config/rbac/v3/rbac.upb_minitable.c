
#include <stddef.h>
#include "upb/generated_code_support.h"
#include "envoy/config/rbac/v3/rbac.upb_minitable.h"
#include "envoy/config/core/v3/address.upb_minitable.h"
#include "envoy/config/core/v3/extension.upb_minitable.h"
#include "envoy/config/route/v3/route_components.upb_minitable.h"
#include "envoy/type/matcher/v3/filter_state.upb_minitable.h"
#include "envoy/type/matcher/v3/metadata.upb_minitable.h"
#include "envoy/type/matcher/v3/path.upb_minitable.h"
#include "envoy/type/matcher/v3/string.upb_minitable.h"
#include "envoy/type/v3/range.upb_minitable.h"
#include "google/api/expr/v1alpha1/checked.upb_minitable.h"
#include "google/api/expr/v1alpha1/syntax.upb_minitable.h"
#include "envoy/annotations/deprecation.upb_minitable.h"
#include "udpa/annotations/migrate.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
static const upb_MiniTableSubInternal envoy_config_rbac_v3_RBAC__submsgs[2] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__rbac__v3__RBAC__PoliciesEntry_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__rbac__v3__RBAC__AuditLoggingOptions_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_rbac_v3_RBAC__fields[3] = {
  {1, 12, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {2, 16, 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(20, 24), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__rbac__v3__RBAC_msg_init = {
  &envoy_config_rbac_v3_RBAC__submsgs[0],
  &envoy_config_rbac_v3_RBAC__fields[0],
  UPB_SIZE(24, 32), 3, kUpb_ExtMode_NonExtendable, 3, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.rbac.v3.RBAC",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000c00003f000008, &upb_psv4_1bt},
  })
};

const upb_MiniTable* envoy__config__rbac__v3__RBAC_msg_init_ptr = &envoy__config__rbac__v3__RBAC_msg_init;
static const upb_MiniTableSubInternal envoy_config_rbac_v3_RBAC_AuditLoggingOptions__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__rbac__v3__RBAC__AuditLoggingOptions__AuditLoggerConfig_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_rbac_v3_RBAC_AuditLoggingOptions__fields[2] = {
  {1, 8, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__rbac__v3__RBAC__AuditLoggingOptions_msg_init = {
  &envoy_config_rbac_v3_RBAC_AuditLoggingOptions__submsgs[0],
  &envoy_config_rbac_v3_RBAC_AuditLoggingOptions__fields[0],
  UPB_SIZE(16, 24), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.rbac.v3.RBAC.AuditLoggingOptions",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f000008, &upb_psv4_1bt},
    {0x001000003f000012, &upb_prm_1bt_max64b},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__config__rbac__v3__RBAC__AuditLoggingOptions_msg_init_ptr = &envoy__config__rbac__v3__RBAC__AuditLoggingOptions_msg_init;
static const upb_MiniTableSubInternal envoy_config_rbac_v3_RBAC_AuditLoggingOptions_AuditLoggerConfig__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__TypedExtensionConfig_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_rbac_v3_RBAC_AuditLoggingOptions_AuditLoggerConfig__fields[2] = {
  {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__rbac__v3__RBAC__AuditLoggingOptions__AuditLoggerConfig_msg_init = {
  &envoy_config_rbac_v3_RBAC_AuditLoggingOptions_AuditLoggerConfig__submsgs[0],
  &envoy_config_rbac_v3_RBAC_AuditLoggingOptions_AuditLoggerConfig__fields[0],
  UPB_SIZE(16, 24), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.rbac.v3.RBAC.AuditLoggingOptions.AuditLoggerConfig",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000900003f000010, &upb_psb1_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__config__rbac__v3__RBAC__AuditLoggingOptions__AuditLoggerConfig_msg_init_ptr = &envoy__config__rbac__v3__RBAC__AuditLoggingOptions__AuditLoggerConfig_msg_init;
static const upb_MiniTableSubInternal envoy_config_rbac_v3_RBAC_PoliciesEntry__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__rbac__v3__Policy_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_rbac_v3_RBAC_PoliciesEntry__fields[2] = {
  {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, 32, 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__rbac__v3__RBAC__PoliciesEntry_msg_init = {
  &envoy_config_rbac_v3_RBAC_PoliciesEntry__submsgs[0],
  &envoy_config_rbac_v3_RBAC_PoliciesEntry__fields[0],
  48, 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.rbac.v3.RBAC.PoliciesEntry",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
  })
};

const upb_MiniTable* envoy__config__rbac__v3__RBAC__PoliciesEntry_msg_init_ptr = &envoy__config__rbac__v3__RBAC__PoliciesEntry_msg_init;
static const upb_MiniTableSubInternal envoy_config_rbac_v3_Policy__submsgs[4] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__rbac__v3__Permission_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__rbac__v3__Principal_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__api__expr__v1alpha1__Expr_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__api__expr__v1alpha1__CheckedExpr_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_rbac_v3_Policy__fields[4] = {
  {1, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 24), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(20, 32), 64, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(24, 40), 65, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__rbac__v3__Policy_msg_init = {
  &envoy_config_rbac_v3_Policy__submsgs[0],
  &envoy_config_rbac_v3_Policy__fields[0],
  UPB_SIZE(32, 48), 4, kUpb_ExtMode_NonExtendable, 4, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.rbac.v3.Policy",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_prm_1bt_max64b},
    {0x001800003f010012, &upb_prm_1bt_max64b},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__config__rbac__v3__Policy_msg_init_ptr = &envoy__config__rbac__v3__Policy_msg_init;
static const upb_MiniTableSubInternal envoy_config_rbac_v3_SourcedMetadata__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &envoy__type__matcher__v3__MetadataMatcher_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_rbac_v3_SourcedMetadata__fields[2] = {
  {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__rbac__v3__SourcedMetadata_msg_init = {
  &envoy_config_rbac_v3_SourcedMetadata__submsgs[0],
  &envoy_config_rbac_v3_SourcedMetadata__fields[0],
  24, 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.rbac.v3.SourcedMetadata",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000c00003f000010, &upb_psv4_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__config__rbac__v3__SourcedMetadata_msg_init_ptr = &envoy__config__rbac__v3__SourcedMetadata_msg_init;
static const upb_MiniTableSubInternal envoy_config_rbac_v3_Permission__submsgs[12] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__rbac__v3__Permission__Set_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__rbac__v3__Permission__Set_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__route__v3__HeaderMatcher_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__CidrRange_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__type__matcher__v3__MetadataMatcher_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__rbac__v3__Permission_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__type__matcher__v3__StringMatcher_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__type__matcher__v3__PathMatcher_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__type__v3__Int32Range_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__TypedExtensionConfig_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__TypedExtensionConfig_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__rbac__v3__SourcedMetadata_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_rbac_v3_Permission__fields[14] = {
  {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(12, 16), -9, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(12, 16), -9, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(12, 16), -9, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {6, UPB_SIZE(12, 16), -9, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {7, UPB_SIZE(12, 16), -9, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {8, UPB_SIZE(12, 16), -9, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {9, UPB_SIZE(12, 16), -9, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {10, UPB_SIZE(12, 16), -9, 7, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {11, UPB_SIZE(12, 16), -9, 8, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {12, UPB_SIZE(12, 16), -9, 9, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {13, UPB_SIZE(12, 16), -9, 10, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {14, UPB_SIZE(12, 16), -9, 11, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__rbac__v3__Permission_msg_init = {
  &envoy_config_rbac_v3_Permission__submsgs[0],
  &envoy_config_rbac_v3_Permission__fields[0],
  UPB_SIZE(16, 24), 14, kUpb_ExtMode_NonExtendable, 14, UPB_FASTTABLE_MASK(120), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.rbac.v3.Permission",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000080100000a, &upb_pom_1bt_max64b},
    {0x0010000802010012, &upb_pom_1bt_max64b},
    {0x0010000803000018, &upb_pob1_1bt},
    {0x0010000804020022, &upb_pom_1bt_maxmaxb},
    {0x001000080503002a, &upb_pom_1bt_maxmaxb},
    {0x0010000806000030, &upb_pov4_1bt},
    {0x001000080704003a, &upb_pom_1bt_maxmaxb},
    {0x0010000808050042, &upb_pom_1bt_max64b},
    {0x001000080906004a, &upb_pom_1bt_maxmaxb},
    {0x001000080a070052, &upb_pom_1bt_maxmaxb},
    {0x001000080b08005a, &upb_pom_1bt_maxmaxb},
    {0x001000080c090062, &upb_pom_1bt_maxmaxb},
    {0x001000080d0a006a, &upb_pom_1bt_maxmaxb},
    {0x001000080e0b0072, &upb_pom_1bt_max64b},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__config__rbac__v3__Permission_msg_init_ptr = &envoy__config__rbac__v3__Permission_msg_init;
static const upb_MiniTableSubInternal envoy_config_rbac_v3_Permission_Set__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__rbac__v3__Permission_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_rbac_v3_Permission_Set__fields[1] = {
  {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__rbac__v3__Permission__Set_msg_init = {
  &envoy_config_rbac_v3_Permission_Set__submsgs[0],
  &envoy_config_rbac_v3_Permission_Set__fields[0],
  16, 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.rbac.v3.Permission.Set",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f00000a, &upb_prm_1bt_max64b},
  })
};

const upb_MiniTable* envoy__config__rbac__v3__Permission__Set_msg_init_ptr = &envoy__config__rbac__v3__Permission__Set_msg_init;
static const upb_MiniTableSubInternal envoy_config_rbac_v3_Principal__submsgs[12] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__rbac__v3__Principal__Set_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__rbac__v3__Principal__Set_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__rbac__v3__Principal__Authenticated_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__CidrRange_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__route__v3__HeaderMatcher_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__type__matcher__v3__MetadataMatcher_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__rbac__v3__Principal_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__type__matcher__v3__PathMatcher_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__CidrRange_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__CidrRange_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__type__matcher__v3__FilterStateMatcher_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__rbac__v3__SourcedMetadata_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_rbac_v3_Principal__fields[13] = {
  {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(12, 16), -9, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(12, 16), -9, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(12, 16), -9, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {6, UPB_SIZE(12, 16), -9, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {7, UPB_SIZE(12, 16), -9, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {8, UPB_SIZE(12, 16), -9, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {9, UPB_SIZE(12, 16), -9, 7, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {10, UPB_SIZE(12, 16), -9, 8, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {11, UPB_SIZE(12, 16), -9, 9, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {12, UPB_SIZE(12, 16), -9, 10, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {13, UPB_SIZE(12, 16), -9, 11, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__rbac__v3__Principal_msg_init = {
  &envoy_config_rbac_v3_Principal__submsgs[0],
  &envoy_config_rbac_v3_Principal__fields[0],
  UPB_SIZE(16, 24), 13, kUpb_ExtMode_NonExtendable, 13, UPB_FASTTABLE_MASK(120), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.rbac.v3.Principal",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000080100000a, &upb_pom_1bt_max64b},
    {0x0010000802010012, &upb_pom_1bt_max64b},
    {0x0010000803000018, &upb_pob1_1bt},
    {0x0010000804020022, &upb_pom_1bt_max64b},
    {0x001000080503002a, &upb_pom_1bt_maxmaxb},
    {0x0010000806040032, &upb_pom_1bt_maxmaxb},
    {0x001000080705003a, &upb_pom_1bt_maxmaxb},
    {0x0010000808060042, &upb_pom_1bt_max64b},
    {0x001000080907004a, &upb_pom_1bt_maxmaxb},
    {0x001000080a080052, &upb_pom_1bt_maxmaxb},
    {0x001000080b09005a, &upb_pom_1bt_maxmaxb},
    {0x001000080c0a0062, &upb_pom_1bt_maxmaxb},
    {0x001000080d0b006a, &upb_pom_1bt_max64b},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__config__rbac__v3__Principal_msg_init_ptr = &envoy__config__rbac__v3__Principal_msg_init;
static const upb_MiniTableSubInternal envoy_config_rbac_v3_Principal_Set__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__rbac__v3__Principal_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_rbac_v3_Principal_Set__fields[1] = {
  {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__rbac__v3__Principal__Set_msg_init = {
  &envoy_config_rbac_v3_Principal_Set__submsgs[0],
  &envoy_config_rbac_v3_Principal_Set__fields[0],
  16, 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.rbac.v3.Principal.Set",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f00000a, &upb_prm_1bt_max64b},
  })
};

const upb_MiniTable* envoy__config__rbac__v3__Principal__Set_msg_init_ptr = &envoy__config__rbac__v3__Principal__Set_msg_init;
static const upb_MiniTableSubInternal envoy_config_rbac_v3_Principal_Authenticated__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &envoy__type__matcher__v3__StringMatcher_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_rbac_v3_Principal_Authenticated__fields[1] = {
  {2, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__rbac__v3__Principal__Authenticated_msg_init = {
  &envoy_config_rbac_v3_Principal_Authenticated__submsgs[0],
  &envoy_config_rbac_v3_Principal_Authenticated__fields[0],
  UPB_SIZE(16, 24), 1, kUpb_ExtMode_NonExtendable, 0, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.rbac.v3.Principal.Authenticated",
#endif
};

const upb_MiniTable* envoy__config__rbac__v3__Principal__Authenticated_msg_init_ptr = &envoy__config__rbac__v3__Principal__Authenticated_msg_init;
static const upb_MiniTableField envoy_config_rbac_v3_Action__fields[2] = {
  {1, UPB_SIZE(12, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, 8, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__rbac__v3__Action_msg_init = {
  NULL,
  &envoy_config_rbac_v3_Action__fields[0],
  UPB_SIZE(24, 32), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.rbac.v3.Action",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
    {0x000800003f000010, &upb_psv4_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__config__rbac__v3__Action_msg_init_ptr = &envoy__config__rbac__v3__Action_msg_init;
static const upb_MiniTable *messages_layout[12] = {
  &envoy__config__rbac__v3__RBAC_msg_init,
  &envoy__config__rbac__v3__RBAC__AuditLoggingOptions_msg_init,
  &envoy__config__rbac__v3__RBAC__AuditLoggingOptions__AuditLoggerConfig_msg_init,
  &envoy__config__rbac__v3__RBAC__PoliciesEntry_msg_init,
  &envoy__config__rbac__v3__Policy_msg_init,
  &envoy__config__rbac__v3__SourcedMetadata_msg_init,
  &envoy__config__rbac__v3__Permission_msg_init,
  &envoy__config__rbac__v3__Permission__Set_msg_init,
  &envoy__config__rbac__v3__Principal_msg_init,
  &envoy__config__rbac__v3__Principal__Set_msg_init,
  &envoy__config__rbac__v3__Principal__Authenticated_msg_init,
  &envoy__config__rbac__v3__Action_msg_init,
};

const upb_MiniTableFile envoy_config_rbac_v3_rbac_proto_upb_file_layout = {
  messages_layout,
  NULL,
  NULL,
  12,
  0,
  0,
};

#include "upb/port/undef.inc"
