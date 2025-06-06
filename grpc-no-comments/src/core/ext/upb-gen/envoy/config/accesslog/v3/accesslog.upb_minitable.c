
#include <stddef.h>
#include "upb/generated_code_support.h"
#include "envoy/config/accesslog/v3/accesslog.upb_minitable.h"
#include "envoy/config/core/v3/base.upb_minitable.h"
#include "envoy/config/route/v3/route_components.upb_minitable.h"
#include "envoy/data/accesslog/v3/accesslog.upb_minitable.h"
#include "envoy/type/matcher/v3/metadata.upb_minitable.h"
#include "envoy/type/v3/percent.upb_minitable.h"
#include "google/protobuf/any.upb_minitable.h"
#include "google/protobuf/wrappers.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
static const upb_MiniTableSubInternal envoy_config_accesslog_v3_AccessLog__submsgs[2] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__accesslog__v3__AccessLogFilter_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__Any_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_accesslog_v3_AccessLog__fields[3] = {
  {1, UPB_SIZE(24, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(20, 40), UPB_SIZE(-17, -13), 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__accesslog__v3__AccessLog_msg_init = {
  &envoy_config_accesslog_v3_AccessLog__submsgs[0],
  &envoy_config_accesslog_v3_AccessLog__fields[0],
  UPB_SIZE(32, 48), 3, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(56), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.accesslog.v3.AccessLog",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0028000c04010022, &upb_pom_1bt_maxmaxb},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__config__accesslog__v3__AccessLog_msg_init_ptr = &envoy__config__accesslog__v3__AccessLog_msg_init;
static const upb_MiniTableSubInternal envoy_config_accesslog_v3_AccessLogFilter__submsgs[13] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__accesslog__v3__StatusCodeFilter_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__accesslog__v3__DurationFilter_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__accesslog__v3__NotHealthCheckFilter_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__accesslog__v3__TraceableFilter_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__accesslog__v3__RuntimeFilter_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__accesslog__v3__AndFilter_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__accesslog__v3__OrFilter_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__accesslog__v3__HeaderFilter_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__accesslog__v3__ResponseFlagFilter_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__accesslog__v3__GrpcStatusFilter_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__accesslog__v3__ExtensionFilter_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__accesslog__v3__MetadataFilter_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__accesslog__v3__LogTypeFilter_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_accesslog_v3_AccessLogFilter__fields[13] = {
  {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(12, 16), -9, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(12, 16), -9, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(12, 16), -9, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {6, UPB_SIZE(12, 16), -9, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {7, UPB_SIZE(12, 16), -9, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {8, UPB_SIZE(12, 16), -9, 7, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {9, UPB_SIZE(12, 16), -9, 8, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {10, UPB_SIZE(12, 16), -9, 9, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {11, UPB_SIZE(12, 16), -9, 10, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {12, UPB_SIZE(12, 16), -9, 11, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {13, UPB_SIZE(12, 16), -9, 12, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__accesslog__v3__AccessLogFilter_msg_init = {
  &envoy_config_accesslog_v3_AccessLogFilter__submsgs[0],
  &envoy_config_accesslog_v3_AccessLogFilter__fields[0],
  UPB_SIZE(16, 24), 13, kUpb_ExtMode_NonExtendable, 13, UPB_FASTTABLE_MASK(120), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.accesslog.v3.AccessLogFilter",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000080100000a, &upb_pom_1bt_max64b},
    {0x0010000802010012, &upb_pom_1bt_max64b},
    {0x001000080302001a, &upb_pom_1bt_max64b},
    {0x0010000804030022, &upb_pom_1bt_max64b},
    {0x001000080504002a, &upb_pom_1bt_max64b},
    {0x0010000806050032, &upb_pom_1bt_max64b},
    {0x001000080706003a, &upb_pom_1bt_max64b},
    {0x0010000808070042, &upb_pom_1bt_max64b},
    {0x001000080908004a, &upb_pom_1bt_max64b},
    {0x001000080a090052, &upb_pom_1bt_max64b},
    {0x001000080b0a005a, &upb_pom_1bt_max64b},
    {0x001000080c0b0062, &upb_pom_1bt_max64b},
    {0x001000080d0c006a, &upb_pom_1bt_max64b},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__config__accesslog__v3__AccessLogFilter_msg_init_ptr = &envoy__config__accesslog__v3__AccessLogFilter_msg_init;
static const upb_MiniTableSubInternal envoy_config_accesslog_v3_ComparisonFilter__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__RuntimeUInt32_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_accesslog_v3_ComparisonFilter__fields[2] = {
  {1, 12, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {2, 16, 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__accesslog__v3__ComparisonFilter_msg_init = {
  &envoy_config_accesslog_v3_ComparisonFilter__submsgs[0],
  &envoy_config_accesslog_v3_ComparisonFilter__fields[0],
  24, 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.accesslog.v3.ComparisonFilter",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000c00003f000008, &upb_psv4_1bt},
  })
};

const upb_MiniTable* envoy__config__accesslog__v3__ComparisonFilter_msg_init_ptr = &envoy__config__accesslog__v3__ComparisonFilter_msg_init;
static const upb_MiniTableSubInternal envoy_config_accesslog_v3_StatusCodeFilter__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__accesslog__v3__ComparisonFilter_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_accesslog_v3_StatusCodeFilter__fields[1] = {
  {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__accesslog__v3__StatusCodeFilter_msg_init = {
  &envoy_config_accesslog_v3_StatusCodeFilter__submsgs[0],
  &envoy_config_accesslog_v3_StatusCodeFilter__fields[0],
  UPB_SIZE(16, 24), 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.accesslog.v3.StatusCodeFilter",
#endif
};

const upb_MiniTable* envoy__config__accesslog__v3__StatusCodeFilter_msg_init_ptr = &envoy__config__accesslog__v3__StatusCodeFilter_msg_init;
static const upb_MiniTableSubInternal envoy_config_accesslog_v3_DurationFilter__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__accesslog__v3__ComparisonFilter_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_accesslog_v3_DurationFilter__fields[1] = {
  {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__accesslog__v3__DurationFilter_msg_init = {
  &envoy_config_accesslog_v3_DurationFilter__submsgs[0],
  &envoy_config_accesslog_v3_DurationFilter__fields[0],
  UPB_SIZE(16, 24), 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.accesslog.v3.DurationFilter",
#endif
};

const upb_MiniTable* envoy__config__accesslog__v3__DurationFilter_msg_init_ptr = &envoy__config__accesslog__v3__DurationFilter_msg_init;
const upb_MiniTable envoy__config__accesslog__v3__NotHealthCheckFilter_msg_init = {
  NULL,
  NULL,
  8, 0, kUpb_ExtMode_NonExtendable, 0, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.accesslog.v3.NotHealthCheckFilter",
#endif
};

const upb_MiniTable* envoy__config__accesslog__v3__NotHealthCheckFilter_msg_init_ptr = &envoy__config__accesslog__v3__NotHealthCheckFilter_msg_init;
const upb_MiniTable envoy__config__accesslog__v3__TraceableFilter_msg_init = {
  NULL,
  NULL,
  8, 0, kUpb_ExtMode_NonExtendable, 0, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.accesslog.v3.TraceableFilter",
#endif
};

const upb_MiniTable* envoy__config__accesslog__v3__TraceableFilter_msg_init_ptr = &envoy__config__accesslog__v3__TraceableFilter_msg_init;
static const upb_MiniTableSubInternal envoy_config_accesslog_v3_RuntimeFilter__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &envoy__type__v3__FractionalPercent_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_accesslog_v3_RuntimeFilter__fields[3] = {
  {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__accesslog__v3__RuntimeFilter_msg_init = {
  &envoy_config_accesslog_v3_RuntimeFilter__submsgs[0],
  &envoy_config_accesslog_v3_RuntimeFilter__fields[0],
  UPB_SIZE(24, 40), 3, kUpb_ExtMode_NonExtendable, 3, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.accesslog.v3.RuntimeFilter",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000900003f000018, &upb_psb1_1bt},
  })
};

const upb_MiniTable* envoy__config__accesslog__v3__RuntimeFilter_msg_init_ptr = &envoy__config__accesslog__v3__RuntimeFilter_msg_init;
static const upb_MiniTableSubInternal envoy_config_accesslog_v3_AndFilter__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__accesslog__v3__AccessLogFilter_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_accesslog_v3_AndFilter__fields[1] = {
  {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__accesslog__v3__AndFilter_msg_init = {
  &envoy_config_accesslog_v3_AndFilter__submsgs[0],
  &envoy_config_accesslog_v3_AndFilter__fields[0],
  16, 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.accesslog.v3.AndFilter",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f00000a, &upb_prm_1bt_max64b},
  })
};

const upb_MiniTable* envoy__config__accesslog__v3__AndFilter_msg_init_ptr = &envoy__config__accesslog__v3__AndFilter_msg_init;
static const upb_MiniTableSubInternal envoy_config_accesslog_v3_OrFilter__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__accesslog__v3__AccessLogFilter_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_accesslog_v3_OrFilter__fields[1] = {
  {2, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__accesslog__v3__OrFilter_msg_init = {
  &envoy_config_accesslog_v3_OrFilter__submsgs[0],
  &envoy_config_accesslog_v3_OrFilter__fields[0],
  16, 1, kUpb_ExtMode_NonExtendable, 0, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.accesslog.v3.OrFilter",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f000012, &upb_prm_1bt_max64b},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__config__accesslog__v3__OrFilter_msg_init_ptr = &envoy__config__accesslog__v3__OrFilter_msg_init;
static const upb_MiniTableSubInternal envoy_config_accesslog_v3_HeaderFilter__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__route__v3__HeaderMatcher_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_accesslog_v3_HeaderFilter__fields[1] = {
  {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__accesslog__v3__HeaderFilter_msg_init = {
  &envoy_config_accesslog_v3_HeaderFilter__submsgs[0],
  &envoy_config_accesslog_v3_HeaderFilter__fields[0],
  UPB_SIZE(16, 24), 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.accesslog.v3.HeaderFilter",
#endif
};

const upb_MiniTable* envoy__config__accesslog__v3__HeaderFilter_msg_init_ptr = &envoy__config__accesslog__v3__HeaderFilter_msg_init;
static const upb_MiniTableField envoy_config_accesslog_v3_ResponseFlagFilter__fields[1] = {
  {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__accesslog__v3__ResponseFlagFilter_msg_init = {
  NULL,
  &envoy_config_accesslog_v3_ResponseFlagFilter__fields[0],
  16, 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.accesslog.v3.ResponseFlagFilter",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f00000a, &upb_prs_1bt},
  })
};

const upb_MiniTable* envoy__config__accesslog__v3__ResponseFlagFilter_msg_init_ptr = &envoy__config__accesslog__v3__ResponseFlagFilter_msg_init;
static const upb_MiniTableField envoy_config_accesslog_v3_GrpcStatusFilter__fields[2] = {
  {1, UPB_SIZE(12, 16), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | (int)kUpb_LabelFlags_IsAlternate | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__accesslog__v3__GrpcStatusFilter_msg_init = {
  NULL,
  &envoy_config_accesslog_v3_GrpcStatusFilter__fields[0],
  UPB_SIZE(16, 24), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.accesslog.v3.GrpcStatusFilter",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_ppv4_1bt},
    {0x000800003f000010, &upb_psb1_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__config__accesslog__v3__GrpcStatusFilter_msg_init_ptr = &envoy__config__accesslog__v3__GrpcStatusFilter_msg_init;
static const upb_MiniTableSubInternal envoy_config_accesslog_v3_MetadataFilter__submsgs[2] = {
  {.UPB_PRIVATE(submsg) = &envoy__type__matcher__v3__MetadataMatcher_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__BoolValue_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_accesslog_v3_MetadataFilter__fields[2] = {
  {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__accesslog__v3__MetadataFilter_msg_init = {
  &envoy_config_accesslog_v3_MetadataFilter__submsgs[0],
  &envoy_config_accesslog_v3_MetadataFilter__fields[0],
  UPB_SIZE(24, 32), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.accesslog.v3.MetadataFilter",
#endif
};

const upb_MiniTable* envoy__config__accesslog__v3__MetadataFilter_msg_init_ptr = &envoy__config__accesslog__v3__MetadataFilter_msg_init;
static const upb_MiniTableField envoy_config_accesslog_v3_LogTypeFilter__fields[2] = {
  {1, UPB_SIZE(12, 16), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Array | (int)kUpb_LabelFlags_IsPacked | (int)kUpb_LabelFlags_IsAlternate | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, 8, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__accesslog__v3__LogTypeFilter_msg_init = {
  NULL,
  &envoy_config_accesslog_v3_LogTypeFilter__fields[0],
  UPB_SIZE(16, 24), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.accesslog.v3.LogTypeFilter",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_ppv4_1bt},
    {0x000800003f000010, &upb_psb1_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__config__accesslog__v3__LogTypeFilter_msg_init_ptr = &envoy__config__accesslog__v3__LogTypeFilter_msg_init;
static const upb_MiniTableSubInternal envoy_config_accesslog_v3_ExtensionFilter__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__Any_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_accesslog_v3_ExtensionFilter__fields[2] = {
  {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__accesslog__v3__ExtensionFilter_msg_init = {
  &envoy_config_accesslog_v3_ExtensionFilter__submsgs[0],
  &envoy_config_accesslog_v3_ExtensionFilter__fields[0],
  UPB_SIZE(24, 40), 2, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.accesslog.v3.ExtensionFilter",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x002000080300001a, &upb_pom_1bt_maxmaxb},
  })
};

const upb_MiniTable* envoy__config__accesslog__v3__ExtensionFilter_msg_init_ptr = &envoy__config__accesslog__v3__ExtensionFilter_msg_init;
static const upb_MiniTable *messages_layout[16] = {
  &envoy__config__accesslog__v3__AccessLog_msg_init,
  &envoy__config__accesslog__v3__AccessLogFilter_msg_init,
  &envoy__config__accesslog__v3__ComparisonFilter_msg_init,
  &envoy__config__accesslog__v3__StatusCodeFilter_msg_init,
  &envoy__config__accesslog__v3__DurationFilter_msg_init,
  &envoy__config__accesslog__v3__NotHealthCheckFilter_msg_init,
  &envoy__config__accesslog__v3__TraceableFilter_msg_init,
  &envoy__config__accesslog__v3__RuntimeFilter_msg_init,
  &envoy__config__accesslog__v3__AndFilter_msg_init,
  &envoy__config__accesslog__v3__OrFilter_msg_init,
  &envoy__config__accesslog__v3__HeaderFilter_msg_init,
  &envoy__config__accesslog__v3__ResponseFlagFilter_msg_init,
  &envoy__config__accesslog__v3__GrpcStatusFilter_msg_init,
  &envoy__config__accesslog__v3__MetadataFilter_msg_init,
  &envoy__config__accesslog__v3__LogTypeFilter_msg_init,
  &envoy__config__accesslog__v3__ExtensionFilter_msg_init,
};

const upb_MiniTableFile envoy_config_accesslog_v3_accesslog_proto_upb_file_layout = {
  messages_layout,
  NULL,
  NULL,
  16,
  0,
  0,
};

#include "upb/port/undef.inc"
