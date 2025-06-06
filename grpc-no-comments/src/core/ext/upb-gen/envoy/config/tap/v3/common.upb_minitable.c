
#include <stddef.h>
#include "upb/generated_code_support.h"
#include "envoy/config/tap/v3/common.upb_minitable.h"
#include "envoy/config/common/matcher/v3/matcher.upb_minitable.h"
#include "envoy/config/core/v3/base.upb_minitable.h"
#include "envoy/config/core/v3/extension.upb_minitable.h"
#include "envoy/config/core/v3/grpc_service.upb_minitable.h"
#include "envoy/config/route/v3/route_components.upb_minitable.h"
#include "google/protobuf/duration.upb_minitable.h"
#include "google/protobuf/wrappers.upb_minitable.h"
#include "envoy/annotations/deprecation.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
static const upb_MiniTableSubInternal envoy_config_tap_v3_TapConfig__submsgs[4] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__tap__v3__MatchPredicate_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__tap__v3__OutputConfig_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__RuntimeFractionalPercent_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__common__matcher__v3__MatchPredicate_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_tap_v3_TapConfig__fields[4] = {
  {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(20, 32), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(24, 40), 67, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__tap__v3__TapConfig_msg_init = {
  &envoy_config_tap_v3_TapConfig__submsgs[0],
  &envoy_config_tap_v3_TapConfig__fields[0],
  UPB_SIZE(32, 48), 4, kUpb_ExtMode_NonExtendable, 4, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.tap.v3.TapConfig",
#endif
};

const upb_MiniTable* envoy__config__tap__v3__TapConfig_msg_init_ptr = &envoy__config__tap__v3__TapConfig_msg_init;
static const upb_MiniTableSubInternal envoy_config_tap_v3_MatchPredicate__submsgs[9] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__tap__v3__MatchPredicate__MatchSet_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__tap__v3__MatchPredicate__MatchSet_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__tap__v3__MatchPredicate_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__tap__v3__HttpHeadersMatch_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__tap__v3__HttpHeadersMatch_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__tap__v3__HttpHeadersMatch_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__tap__v3__HttpHeadersMatch_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__tap__v3__HttpGenericBodyMatch_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__tap__v3__HttpGenericBodyMatch_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_tap_v3_MatchPredicate__fields[10] = {
  {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(12, 16), -9, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(12, 16), -9, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(12, 16), -9, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {6, UPB_SIZE(12, 16), -9, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {7, UPB_SIZE(12, 16), -9, 5, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {8, UPB_SIZE(12, 16), -9, 6, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {9, UPB_SIZE(12, 16), -9, 7, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {10, UPB_SIZE(12, 16), -9, 8, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__tap__v3__MatchPredicate_msg_init = {
  &envoy_config_tap_v3_MatchPredicate__submsgs[0],
  &envoy_config_tap_v3_MatchPredicate__fields[0],
  UPB_SIZE(16, 24), 10, kUpb_ExtMode_NonExtendable, 10, UPB_FASTTABLE_MASK(120), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.tap.v3.MatchPredicate",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000080100000a, &upb_pom_1bt_max64b},
    {0x0010000802010012, &upb_pom_1bt_max64b},
    {0x001000080302001a, &upb_pom_1bt_max64b},
    {0x0010000804000020, &upb_pob1_1bt},
    {0x001000080503002a, &upb_pom_1bt_max64b},
    {0x0010000806040032, &upb_pom_1bt_max64b},
    {0x001000080705003a, &upb_pom_1bt_max64b},
    {0x0010000808060042, &upb_pom_1bt_max64b},
    {0x001000080907004a, &upb_pom_1bt_max64b},
    {0x001000080a080052, &upb_pom_1bt_max64b},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__config__tap__v3__MatchPredicate_msg_init_ptr = &envoy__config__tap__v3__MatchPredicate_msg_init;
static const upb_MiniTableSubInternal envoy_config_tap_v3_MatchPredicate_MatchSet__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__tap__v3__MatchPredicate_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_tap_v3_MatchPredicate_MatchSet__fields[1] = {
  {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__tap__v3__MatchPredicate__MatchSet_msg_init = {
  &envoy_config_tap_v3_MatchPredicate_MatchSet__submsgs[0],
  &envoy_config_tap_v3_MatchPredicate_MatchSet__fields[0],
  16, 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.tap.v3.MatchPredicate.MatchSet",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f00000a, &upb_prm_1bt_max64b},
  })
};

const upb_MiniTable* envoy__config__tap__v3__MatchPredicate__MatchSet_msg_init_ptr = &envoy__config__tap__v3__MatchPredicate__MatchSet_msg_init;
static const upb_MiniTableSubInternal envoy_config_tap_v3_HttpHeadersMatch__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__route__v3__HeaderMatcher_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_tap_v3_HttpHeadersMatch__fields[1] = {
  {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__tap__v3__HttpHeadersMatch_msg_init = {
  &envoy_config_tap_v3_HttpHeadersMatch__submsgs[0],
  &envoy_config_tap_v3_HttpHeadersMatch__fields[0],
  16, 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.tap.v3.HttpHeadersMatch",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f00000a, &upb_prm_1bt_maxmaxb},
  })
};

const upb_MiniTable* envoy__config__tap__v3__HttpHeadersMatch_msg_init_ptr = &envoy__config__tap__v3__HttpHeadersMatch_msg_init;
static const upb_MiniTableSubInternal envoy_config_tap_v3_HttpGenericBodyMatch__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__tap__v3__HttpGenericBodyMatch__GenericTextMatch_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_tap_v3_HttpGenericBodyMatch__fields[2] = {
  {1, 8, 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__tap__v3__HttpGenericBodyMatch_msg_init = {
  &envoy_config_tap_v3_HttpGenericBodyMatch__submsgs[0],
  &envoy_config_tap_v3_HttpGenericBodyMatch__fields[0],
  UPB_SIZE(16, 24), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.tap.v3.HttpGenericBodyMatch",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f000008, &upb_psv4_1bt},
    {0x001000003f000012, &upb_prm_1bt_max64b},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__config__tap__v3__HttpGenericBodyMatch_msg_init_ptr = &envoy__config__tap__v3__HttpGenericBodyMatch_msg_init;
static const upb_MiniTableField envoy_config_tap_v3_HttpGenericBodyMatch_GenericTextMatch__fields[2] = {
  {1, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 16), -9, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__tap__v3__HttpGenericBodyMatch__GenericTextMatch_msg_init = {
  NULL,
  &envoy_config_tap_v3_HttpGenericBodyMatch_GenericTextMatch__fields[0],
  UPB_SIZE(24, 32), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.tap.v3.HttpGenericBodyMatch.GenericTextMatch",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000080100000a, &upb_pos_1bt},
    {0x0010000802000012, &upb_pob_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__config__tap__v3__HttpGenericBodyMatch__GenericTextMatch_msg_init_ptr = &envoy__config__tap__v3__HttpGenericBodyMatch__GenericTextMatch_msg_init;
static const upb_MiniTableSubInternal envoy_config_tap_v3_OutputConfig__submsgs[3] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__tap__v3__OutputSink_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__UInt32Value_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__UInt32Value_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_tap_v3_OutputConfig__fields[4] = {
  {1, UPB_SIZE(12, 16), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 24), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(20, 32), 65, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__tap__v3__OutputConfig_msg_init = {
  &envoy_config_tap_v3_OutputConfig__submsgs[0],
  &envoy_config_tap_v3_OutputConfig__fields[0],
  UPB_SIZE(24, 40), 4, kUpb_ExtMode_NonExtendable, 4, UPB_FASTTABLE_MASK(56), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.tap.v3.OutputConfig",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_prm_1bt_max64b},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000900003f000020, &upb_psb1_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__config__tap__v3__OutputConfig_msg_init_ptr = &envoy__config__tap__v3__OutputConfig_msg_init;
static const upb_MiniTableSubInternal envoy_config_tap_v3_OutputSink__submsgs[5] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__tap__v3__StreamingAdminSink_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__tap__v3__FilePerTapSink_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__tap__v3__StreamingGrpcSink_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__tap__v3__BufferedAdminSink_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__TypedExtensionConfig_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_tap_v3_OutputSink__fields[6] = {
  {1, 8, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {2, 16, -13, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, 16, -13, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, 16, -13, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {5, 16, -13, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {6, 16, -13, 4, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__tap__v3__OutputSink_msg_init = {
  &envoy_config_tap_v3_OutputSink__submsgs[0],
  &envoy_config_tap_v3_OutputSink__fields[0],
  24, 6, kUpb_ExtMode_NonExtendable, 6, UPB_FASTTABLE_MASK(56), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.tap.v3.OutputSink",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f000008, &upb_psv4_1bt},
    {0x0010000c02000012, &upb_pom_1bt_max64b},
    {0x0010000c0301001a, &upb_pom_1bt_max64b},
    {0x0010000c04020022, &upb_pom_1bt_max64b},
    {0x0010000c0503002a, &upb_pom_1bt_max64b},
    {0x0010000c06040032, &upb_pom_1bt_maxmaxb},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__config__tap__v3__OutputSink_msg_init_ptr = &envoy__config__tap__v3__OutputSink_msg_init;
const upb_MiniTable envoy__config__tap__v3__StreamingAdminSink_msg_init = {
  NULL,
  NULL,
  8, 0, kUpb_ExtMode_NonExtendable, 0, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.tap.v3.StreamingAdminSink",
#endif
};

const upb_MiniTable* envoy__config__tap__v3__StreamingAdminSink_msg_init_ptr = &envoy__config__tap__v3__StreamingAdminSink_msg_init;
static const upb_MiniTableSubInternal envoy_config_tap_v3_BufferedAdminSink__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__Duration_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_tap_v3_BufferedAdminSink__fields[2] = {
  {1, 16, 0, kUpb_NoSub, 4, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 24), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__tap__v3__BufferedAdminSink_msg_init = {
  &envoy_config_tap_v3_BufferedAdminSink__submsgs[0],
  &envoy_config_tap_v3_BufferedAdminSink__fields[0],
  UPB_SIZE(24, 32), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.tap.v3.BufferedAdminSink",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f000008, &upb_psv8_1bt},
  })
};

const upb_MiniTable* envoy__config__tap__v3__BufferedAdminSink_msg_init_ptr = &envoy__config__tap__v3__BufferedAdminSink_msg_init;
static const upb_MiniTableField envoy_config_tap_v3_FilePerTapSink__fields[1] = {
  {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__tap__v3__FilePerTapSink_msg_init = {
  NULL,
  &envoy_config_tap_v3_FilePerTapSink__fields[0],
  UPB_SIZE(16, 24), 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.tap.v3.FilePerTapSink",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f00000a, &upb_pss_1bt},
  })
};

const upb_MiniTable* envoy__config__tap__v3__FilePerTapSink_msg_init_ptr = &envoy__config__tap__v3__FilePerTapSink_msg_init;
static const upb_MiniTableSubInternal envoy_config_tap_v3_StreamingGrpcSink__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__GrpcService_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_tap_v3_StreamingGrpcSink__fields[2] = {
  {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__tap__v3__StreamingGrpcSink_msg_init = {
  &envoy_config_tap_v3_StreamingGrpcSink__submsgs[0],
  &envoy_config_tap_v3_StreamingGrpcSink__fields[0],
  UPB_SIZE(24, 40), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.tap.v3.StreamingGrpcSink",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
  })
};

const upb_MiniTable* envoy__config__tap__v3__StreamingGrpcSink_msg_init_ptr = &envoy__config__tap__v3__StreamingGrpcSink_msg_init;
static const upb_MiniTable *messages_layout[12] = {
  &envoy__config__tap__v3__TapConfig_msg_init,
  &envoy__config__tap__v3__MatchPredicate_msg_init,
  &envoy__config__tap__v3__MatchPredicate__MatchSet_msg_init,
  &envoy__config__tap__v3__HttpHeadersMatch_msg_init,
  &envoy__config__tap__v3__HttpGenericBodyMatch_msg_init,
  &envoy__config__tap__v3__HttpGenericBodyMatch__GenericTextMatch_msg_init,
  &envoy__config__tap__v3__OutputConfig_msg_init,
  &envoy__config__tap__v3__OutputSink_msg_init,
  &envoy__config__tap__v3__StreamingAdminSink_msg_init,
  &envoy__config__tap__v3__BufferedAdminSink_msg_init,
  &envoy__config__tap__v3__FilePerTapSink_msg_init,
  &envoy__config__tap__v3__StreamingGrpcSink_msg_init,
};

const upb_MiniTableFile envoy_config_tap_v3_common_proto_upb_file_layout = {
  messages_layout,
  NULL,
  NULL,
  12,
  0,
  0,
};

#include "upb/port/undef.inc"
