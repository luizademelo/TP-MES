
#include <stddef.h>
#include "upb/generated_code_support.h"
#include "envoy/config/core/v3/base.upb_minitable.h"
#include "envoy/config/core/v3/address.upb_minitable.h"
#include "envoy/config/core/v3/backoff.upb_minitable.h"
#include "envoy/config/core/v3/http_uri.upb_minitable.h"
#include "envoy/type/v3/percent.upb_minitable.h"
#include "envoy/type/v3/semantic_version.upb_minitable.h"
#include "google/protobuf/any.upb_minitable.h"
#include "google/protobuf/struct.upb_minitable.h"
#include "google/protobuf/wrappers.upb_minitable.h"
#include "xds/core/v3/context_params.upb_minitable.h"
#include "envoy/annotations/deprecation.upb_minitable.h"
#include "udpa/annotations/migrate.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
static const upb_MiniTableField envoy_config_core_v3_Locality__fields[3] = {
  {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(24, 40), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__core__v3__Locality_msg_init = {
  NULL,
  &envoy_config_core_v3_Locality__fields[0],
  UPB_SIZE(32, 56), 3, kUpb_ExtMode_NonExtendable, 3, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.core.v3.Locality",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f00000a, &upb_pss_1bt},
    {0x001800003f000012, &upb_pss_1bt},
    {0x002800003f00001a, &upb_pss_1bt},
  })
};

const upb_MiniTable* envoy__config__core__v3__Locality_msg_init_ptr = &envoy__config__core__v3__Locality_msg_init;
static const upb_MiniTableSubInternal envoy_config_core_v3_BuildVersion__submsgs[2] = {
  {.UPB_PRIVATE(submsg) = &envoy__type__v3__SemanticVersion_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__Struct_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_core_v3_BuildVersion__fields[2] = {
  {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__core__v3__BuildVersion_msg_init = {
  &envoy_config_core_v3_BuildVersion__submsgs[0],
  &envoy_config_core_v3_BuildVersion__fields[0],
  UPB_SIZE(24, 32), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.core.v3.BuildVersion",
#endif
};

const upb_MiniTable* envoy__config__core__v3__BuildVersion_msg_init_ptr = &envoy__config__core__v3__BuildVersion_msg_init;
static const upb_MiniTableSubInternal envoy_config_core_v3_Extension__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__BuildVersion_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_core_v3_Extension__fields[6] = {
  {1, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(28, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(36, 48), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(12, 64), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {5, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
  {6, UPB_SIZE(16, 72), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__core__v3__Extension_msg_init = {
  &envoy_config_core_v3_Extension__submsgs[0],
  &envoy_config_core_v3_Extension__fields[0],
  UPB_SIZE(48, 80), 6, kUpb_ExtMode_NonExtendable, 6, UPB_FASTTABLE_MASK(56), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.core.v3.Extension",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
    {0x002000003f000012, &upb_pss_1bt},
    {0x003000003f00001a, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000900003f000028, &upb_psb1_1bt},
    {0x004800003f000032, &upb_prs_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__config__core__v3__Extension_msg_init_ptr = &envoy__config__core__v3__Extension_msg_init;
static const upb_MiniTableSubInternal envoy_config_core_v3_Node__submsgs[6] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__Struct_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__Locality_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__BuildVersion_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__Extension_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__Address_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__Node__DynamicParametersEntry_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_core_v3_Node__fields[11] = {
  {1, UPB_SIZE(40, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(48, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(12, 80), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(16, 88), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {6, UPB_SIZE(56, 48), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {7, 64, UPB_SIZE(-37, -13), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {8, 64, UPB_SIZE(-37, -13), 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {9, UPB_SIZE(20, 96), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {10, UPB_SIZE(24, 104), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {11, UPB_SIZE(28, 112), 0, 4, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {12, UPB_SIZE(32, 120), 0, 5, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__core__v3__Node_msg_init = {
  &envoy_config_core_v3_Node__submsgs[0],
  &envoy_config_core_v3_Node__fields[0],
  UPB_SIZE(72, 128), 11, kUpb_ExtMode_NonExtendable, 4, UPB_FASTTABLE_MASK(120), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.core.v3.Node",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
    {0x002000003f000012, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x003000003f000032, &upb_pss_1bt},
    {0x0040000c0700003a, &upb_pos_1bt},
    {0x0040000c08020042, &upb_pom_1bt_max64b},
    {0x006000003f03004a, &upb_prm_1bt_max128b},
    {0x006800003f000052, &upb_prs_1bt},
    {0x007000003f04005a, &upb_prm_1bt_maxmaxb},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__config__core__v3__Node_msg_init_ptr = &envoy__config__core__v3__Node_msg_init;
static const upb_MiniTableSubInternal envoy_config_core_v3_Node_DynamicParametersEntry__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &xds__core__v3__ContextParams_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_core_v3_Node_DynamicParametersEntry__fields[2] = {
  {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, 32, 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__core__v3__Node__DynamicParametersEntry_msg_init = {
  &envoy_config_core_v3_Node_DynamicParametersEntry__submsgs[0],
  &envoy_config_core_v3_Node_DynamicParametersEntry__fields[0],
  48, 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.core.v3.Node.DynamicParametersEntry",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
  })
};

const upb_MiniTable* envoy__config__core__v3__Node__DynamicParametersEntry_msg_init_ptr = &envoy__config__core__v3__Node__DynamicParametersEntry_msg_init;
static const upb_MiniTableSubInternal envoy_config_core_v3_Metadata__submsgs[2] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__Metadata__FilterMetadataEntry_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__Metadata__TypedFilterMetadataEntry_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_core_v3_Metadata__fields[2] = {
  {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 16), 0, 1, 11, (int)kUpb_FieldMode_Map | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__core__v3__Metadata_msg_init = {
  &envoy_config_core_v3_Metadata__submsgs[0],
  &envoy_config_core_v3_Metadata__fields[0],
  UPB_SIZE(16, 24), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.core.v3.Metadata",
#endif
};

const upb_MiniTable* envoy__config__core__v3__Metadata_msg_init_ptr = &envoy__config__core__v3__Metadata_msg_init;
static const upb_MiniTableSubInternal envoy_config_core_v3_Metadata_FilterMetadataEntry__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__Struct_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_core_v3_Metadata_FilterMetadataEntry__fields[2] = {
  {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, 32, 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__core__v3__Metadata__FilterMetadataEntry_msg_init = {
  &envoy_config_core_v3_Metadata_FilterMetadataEntry__submsgs[0],
  &envoy_config_core_v3_Metadata_FilterMetadataEntry__fields[0],
  48, 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.core.v3.Metadata.FilterMetadataEntry",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
  })
};

const upb_MiniTable* envoy__config__core__v3__Metadata__FilterMetadataEntry_msg_init_ptr = &envoy__config__core__v3__Metadata__FilterMetadataEntry_msg_init;
static const upb_MiniTableSubInternal envoy_config_core_v3_Metadata_TypedFilterMetadataEntry__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__Any_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_core_v3_Metadata_TypedFilterMetadataEntry__fields[2] = {
  {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, 32, 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__core__v3__Metadata__TypedFilterMetadataEntry_msg_init = {
  &envoy_config_core_v3_Metadata_TypedFilterMetadataEntry__submsgs[0],
  &envoy_config_core_v3_Metadata_TypedFilterMetadataEntry__fields[0],
  48, 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.core.v3.Metadata.TypedFilterMetadataEntry",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
  })
};

const upb_MiniTable* envoy__config__core__v3__Metadata__TypedFilterMetadataEntry_msg_init_ptr = &envoy__config__core__v3__Metadata__TypedFilterMetadataEntry_msg_init;
static const upb_MiniTableField envoy_config_core_v3_RuntimeUInt32__fields[2] = {
  {2, 8, 0, kUpb_NoSub, 13, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(12, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__core__v3__RuntimeUInt32_msg_init = {
  NULL,
  &envoy_config_core_v3_RuntimeUInt32__fields[0],
  UPB_SIZE(24, 32), 2, kUpb_ExtMode_NonExtendable, 0, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.core.v3.RuntimeUInt32",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f000010, &upb_psv4_1bt},
    {0x001000003f00001a, &upb_pss_1bt},
  })
};

const upb_MiniTable* envoy__config__core__v3__RuntimeUInt32_msg_init_ptr = &envoy__config__core__v3__RuntimeUInt32_msg_init;
static const upb_MiniTableSubInternal envoy_config_core_v3_RuntimePercent__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &envoy__type__v3__Percent_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_core_v3_RuntimePercent__fields[2] = {
  {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__core__v3__RuntimePercent_msg_init = {
  &envoy_config_core_v3_RuntimePercent__submsgs[0],
  &envoy_config_core_v3_RuntimePercent__fields[0],
  UPB_SIZE(24, 40), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.core.v3.RuntimePercent",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f000012, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__config__core__v3__RuntimePercent_msg_init_ptr = &envoy__config__core__v3__RuntimePercent_msg_init;
static const upb_MiniTableField envoy_config_core_v3_RuntimeDouble__fields[2] = {
  {1, UPB_SIZE(16, 24), 0, kUpb_NoSub, 1, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
  {2, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__core__v3__RuntimeDouble_msg_init = {
  NULL,
  &envoy_config_core_v3_RuntimeDouble__fields[0],
  UPB_SIZE(24, 32), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.core.v3.RuntimeDouble",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001800003f000009, &upb_psf8_1bt},
    {0x000800003f000012, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__config__core__v3__RuntimeDouble_msg_init_ptr = &envoy__config__core__v3__RuntimeDouble_msg_init;
static const upb_MiniTableSubInternal envoy_config_core_v3_RuntimeFeatureFlag__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__BoolValue_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_core_v3_RuntimeFeatureFlag__fields[2] = {
  {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__core__v3__RuntimeFeatureFlag_msg_init = {
  &envoy_config_core_v3_RuntimeFeatureFlag__submsgs[0],
  &envoy_config_core_v3_RuntimeFeatureFlag__fields[0],
  UPB_SIZE(24, 40), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.core.v3.RuntimeFeatureFlag",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f000012, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__config__core__v3__RuntimeFeatureFlag_msg_init_ptr = &envoy__config__core__v3__RuntimeFeatureFlag_msg_init;
static const upb_MiniTableField envoy_config_core_v3_KeyValue__fields[2] = {
  {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__core__v3__KeyValue_msg_init = {
  NULL,
  &envoy_config_core_v3_KeyValue__fields[0],
  UPB_SIZE(24, 40), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.core.v3.KeyValue",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f00000a, &upb_pss_1bt},
    {0x001800003f000012, &upb_psb_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__config__core__v3__KeyValue_msg_init_ptr = &envoy__config__core__v3__KeyValue_msg_init;
static const upb_MiniTableSubInternal envoy_config_core_v3_KeyValuePair__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__Value_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_core_v3_KeyValuePair__fields[2] = {
  {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__core__v3__KeyValuePair_msg_init = {
  &envoy_config_core_v3_KeyValuePair__submsgs[0],
  &envoy_config_core_v3_KeyValuePair__fields[0],
  UPB_SIZE(24, 40), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.core.v3.KeyValuePair",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
  })
};

const upb_MiniTable* envoy__config__core__v3__KeyValuePair_msg_init_ptr = &envoy__config__core__v3__KeyValuePair_msg_init;
static const upb_MiniTableSubInternal envoy_config_core_v3_KeyValueAppend__submsgs[2] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__KeyValue_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__KeyValuePair_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_core_v3_KeyValueAppend__fields[3] = {
  {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(20, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__core__v3__KeyValueAppend_msg_init = {
  &envoy_config_core_v3_KeyValueAppend__submsgs[0],
  &envoy_config_core_v3_KeyValueAppend__fields[0],
  UPB_SIZE(24, 32), 3, kUpb_ExtMode_NonExtendable, 3, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.core.v3.KeyValueAppend",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000c00003f000010, &upb_psv4_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__config__core__v3__KeyValueAppend_msg_init_ptr = &envoy__config__core__v3__KeyValueAppend_msg_init;
static const upb_MiniTableSubInternal envoy_config_core_v3_KeyValueMutation__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__KeyValueAppend_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_core_v3_KeyValueMutation__fields[2] = {
  {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__core__v3__KeyValueMutation_msg_init = {
  &envoy_config_core_v3_KeyValueMutation__submsgs[0],
  &envoy_config_core_v3_KeyValueMutation__fields[0],
  UPB_SIZE(24, 40), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.core.v3.KeyValueMutation",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f000012, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__config__core__v3__KeyValueMutation_msg_init_ptr = &envoy__config__core__v3__KeyValueMutation_msg_init;
static const upb_MiniTableField envoy_config_core_v3_QueryParameter__fields[2] = {
  {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__core__v3__QueryParameter_msg_init = {
  NULL,
  &envoy_config_core_v3_QueryParameter__fields[0],
  UPB_SIZE(24, 40), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.core.v3.QueryParameter",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f00000a, &upb_pss_1bt},
    {0x001800003f000012, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__config__core__v3__QueryParameter_msg_init_ptr = &envoy__config__core__v3__QueryParameter_msg_init;
static const upb_MiniTableField envoy_config_core_v3_HeaderValue__fields[3] = {
  {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(24, 40), 0, kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__core__v3__HeaderValue_msg_init = {
  NULL,
  &envoy_config_core_v3_HeaderValue__fields[0],
  UPB_SIZE(32, 56), 3, kUpb_ExtMode_NonExtendable, 3, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.core.v3.HeaderValue",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f00000a, &upb_pss_1bt},
    {0x001800003f000012, &upb_pss_1bt},
    {0x002800003f00001a, &upb_psb_1bt},
  })
};

const upb_MiniTable* envoy__config__core__v3__HeaderValue_msg_init_ptr = &envoy__config__core__v3__HeaderValue_msg_init;
static const upb_MiniTableSubInternal envoy_config_core_v3_HeaderValueOption__submsgs[2] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__HeaderValue_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__BoolValue_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_core_v3_HeaderValueOption__fields[4] = {
  {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(20, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
  {4, 9, 0, kUpb_NoSub, 8, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_1Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__core__v3__HeaderValueOption_msg_init = {
  &envoy_config_core_v3_HeaderValueOption__submsgs[0],
  &envoy_config_core_v3_HeaderValueOption__fields[0],
  UPB_SIZE(24, 32), 4, kUpb_ExtMode_NonExtendable, 4, UPB_FASTTABLE_MASK(56), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.core.v3.HeaderValueOption",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000c00003f000018, &upb_psv4_1bt},
    {0x000900003f000020, &upb_psb1_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__config__core__v3__HeaderValueOption_msg_init_ptr = &envoy__config__core__v3__HeaderValueOption_msg_init;
static const upb_MiniTableSubInternal envoy_config_core_v3_HeaderMap__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__HeaderValue_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_core_v3_HeaderMap__fields[1] = {
  {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__core__v3__HeaderMap_msg_init = {
  &envoy_config_core_v3_HeaderMap__submsgs[0],
  &envoy_config_core_v3_HeaderMap__fields[0],
  16, 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.core.v3.HeaderMap",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f00000a, &upb_prm_1bt_max64b},
  })
};

const upb_MiniTable* envoy__config__core__v3__HeaderMap_msg_init_ptr = &envoy__config__core__v3__HeaderMap_msg_init;
static const upb_MiniTableField envoy_config_core_v3_WatchedDirectory__fields[1] = {
  {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__core__v3__WatchedDirectory_msg_init = {
  NULL,
  &envoy_config_core_v3_WatchedDirectory__fields[0],
  UPB_SIZE(16, 24), 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.core.v3.WatchedDirectory",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f00000a, &upb_pss_1bt},
  })
};

const upb_MiniTable* envoy__config__core__v3__WatchedDirectory_msg_init_ptr = &envoy__config__core__v3__WatchedDirectory_msg_init;
static const upb_MiniTableSubInternal envoy_config_core_v3_DataSource__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__WatchedDirectory_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_core_v3_DataSource__fields[5] = {
  {1, UPB_SIZE(20, 16), UPB_SIZE(-17, -13), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(20, 16), UPB_SIZE(-17, -13), kUpb_NoSub, 12, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(20, 16), UPB_SIZE(-17, -13), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(20, 16), UPB_SIZE(-17, -13), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__core__v3__DataSource_msg_init = {
  &envoy_config_core_v3_DataSource__submsgs[0],
  &envoy_config_core_v3_DataSource__fields[0],
  UPB_SIZE(32, 40), 5, kUpb_ExtMode_NonExtendable, 5, UPB_FASTTABLE_MASK(56), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.core.v3.DataSource",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0010000c0100000a, &upb_pos_1bt},
    {0x0010000c02000012, &upb_pob_1bt},
    {0x0010000c0300001a, &upb_pos_1bt},
    {0x0010000c04000022, &upb_pos_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__config__core__v3__DataSource_msg_init_ptr = &envoy__config__core__v3__DataSource_msg_init;
static const upb_MiniTableSubInternal envoy_config_core_v3_RetryPolicy__submsgs[4] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__BackoffStrategy_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__UInt32Value_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__RetryPolicy__RetryPriority_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__RetryPolicy__RetryHostPredicate_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_core_v3_RetryPolicy__fields[6] = {
  {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(28, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(20, 48), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(24, 56), 0, 3, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {6, UPB_SIZE(40, 64), 0, kUpb_NoSub, 3, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_8Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__core__v3__RetryPolicy_msg_init = {
  &envoy_config_core_v3_RetryPolicy__submsgs[0],
  &envoy_config_core_v3_RetryPolicy__fields[0],
  UPB_SIZE(48, 72), 6, kUpb_ExtMode_NonExtendable, 6, UPB_FASTTABLE_MASK(56), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.core.v3.RetryPolicy",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00001a, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x003800003f03002a, &upb_prm_1bt_max64b},
    {0x004000003f000030, &upb_psv8_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__config__core__v3__RetryPolicy_msg_init_ptr = &envoy__config__core__v3__RetryPolicy_msg_init;
static const upb_MiniTableSubInternal envoy_config_core_v3_RetryPolicy_RetryPriority__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__Any_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_core_v3_RetryPolicy_RetryPriority__fields[2] = {
  {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__core__v3__RetryPolicy__RetryPriority_msg_init = {
  &envoy_config_core_v3_RetryPolicy_RetryPriority__submsgs[0],
  &envoy_config_core_v3_RetryPolicy_RetryPriority__fields[0],
  UPB_SIZE(24, 40), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.core.v3.RetryPolicy.RetryPriority",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
    {0x0020000802000012, &upb_pom_1bt_maxmaxb},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__config__core__v3__RetryPolicy__RetryPriority_msg_init_ptr = &envoy__config__core__v3__RetryPolicy__RetryPriority_msg_init;
static const upb_MiniTableSubInternal envoy_config_core_v3_RetryPolicy_RetryHostPredicate__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__Any_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_core_v3_RetryPolicy_RetryHostPredicate__fields[2] = {
  {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__core__v3__RetryPolicy__RetryHostPredicate_msg_init = {
  &envoy_config_core_v3_RetryPolicy_RetryHostPredicate__submsgs[0],
  &envoy_config_core_v3_RetryPolicy_RetryHostPredicate__fields[0],
  UPB_SIZE(24, 40), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.core.v3.RetryPolicy.RetryHostPredicate",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
    {0x0020000802000012, &upb_pom_1bt_maxmaxb},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__config__core__v3__RetryPolicy__RetryHostPredicate_msg_init_ptr = &envoy__config__core__v3__RetryPolicy__RetryHostPredicate_msg_init;
static const upb_MiniTableSubInternal envoy_config_core_v3_RemoteDataSource__submsgs[2] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__HttpUri_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__RetryPolicy_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_core_v3_RemoteDataSource__fields[3] = {
  {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__core__v3__RemoteDataSource_msg_init = {
  &envoy_config_core_v3_RemoteDataSource__submsgs[0],
  &envoy_config_core_v3_RemoteDataSource__fields[0],
  UPB_SIZE(32, 48), 3, kUpb_ExtMode_NonExtendable, 3, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.core.v3.RemoteDataSource",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f000012, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__config__core__v3__RemoteDataSource_msg_init_ptr = &envoy__config__core__v3__RemoteDataSource_msg_init;
static const upb_MiniTableSubInternal envoy_config_core_v3_AsyncDataSource__submsgs[2] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__DataSource_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__RemoteDataSource_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_core_v3_AsyncDataSource__fields[2] = {
  {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__core__v3__AsyncDataSource_msg_init = {
  &envoy_config_core_v3_AsyncDataSource__submsgs[0],
  &envoy_config_core_v3_AsyncDataSource__fields[0],
  UPB_SIZE(16, 24), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.core.v3.AsyncDataSource",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000080100000a, &upb_pom_1bt_max64b},
    {0x0010000802010012, &upb_pom_1bt_max64b},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__config__core__v3__AsyncDataSource_msg_init_ptr = &envoy__config__core__v3__AsyncDataSource_msg_init;
static const upb_MiniTableSubInternal envoy_config_core_v3_TransportSocket__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__Any_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_core_v3_TransportSocket__fields[2] = {
  {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(12, 32), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__core__v3__TransportSocket_msg_init = {
  &envoy_config_core_v3_TransportSocket__submsgs[0],
  &envoy_config_core_v3_TransportSocket__fields[0],
  UPB_SIZE(24, 40), 2, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.core.v3.TransportSocket",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x002000080300001a, &upb_pom_1bt_maxmaxb},
  })
};

const upb_MiniTable* envoy__config__core__v3__TransportSocket_msg_init_ptr = &envoy__config__core__v3__TransportSocket_msg_init;
static const upb_MiniTableSubInternal envoy_config_core_v3_RuntimeFractionalPercent__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &envoy__type__v3__FractionalPercent_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_core_v3_RuntimeFractionalPercent__fields[2] = {
  {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__core__v3__RuntimeFractionalPercent_msg_init = {
  &envoy_config_core_v3_RuntimeFractionalPercent__submsgs[0],
  &envoy_config_core_v3_RuntimeFractionalPercent__fields[0],
  UPB_SIZE(24, 40), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.core.v3.RuntimeFractionalPercent",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f000012, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__config__core__v3__RuntimeFractionalPercent_msg_init_ptr = &envoy__config__core__v3__RuntimeFractionalPercent_msg_init;
static const upb_MiniTableField envoy_config_core_v3_ControlPlane__fields[1] = {
  {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__core__v3__ControlPlane_msg_init = {
  NULL,
  &envoy_config_core_v3_ControlPlane__fields[0],
  UPB_SIZE(16, 24), 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.core.v3.ControlPlane",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f00000a, &upb_pss_1bt},
  })
};

const upb_MiniTable* envoy__config__core__v3__ControlPlane_msg_init_ptr = &envoy__config__core__v3__ControlPlane_msg_init;
static const upb_MiniTable *messages_layout[30] = {
  &envoy__config__core__v3__Locality_msg_init,
  &envoy__config__core__v3__BuildVersion_msg_init,
  &envoy__config__core__v3__Extension_msg_init,
  &envoy__config__core__v3__Node_msg_init,
  &envoy__config__core__v3__Node__DynamicParametersEntry_msg_init,
  &envoy__config__core__v3__Metadata_msg_init,
  &envoy__config__core__v3__Metadata__FilterMetadataEntry_msg_init,
  &envoy__config__core__v3__Metadata__TypedFilterMetadataEntry_msg_init,
  &envoy__config__core__v3__RuntimeUInt32_msg_init,
  &envoy__config__core__v3__RuntimePercent_msg_init,
  &envoy__config__core__v3__RuntimeDouble_msg_init,
  &envoy__config__core__v3__RuntimeFeatureFlag_msg_init,
  &envoy__config__core__v3__KeyValue_msg_init,
  &envoy__config__core__v3__KeyValuePair_msg_init,
  &envoy__config__core__v3__KeyValueAppend_msg_init,
  &envoy__config__core__v3__KeyValueMutation_msg_init,
  &envoy__config__core__v3__QueryParameter_msg_init,
  &envoy__config__core__v3__HeaderValue_msg_init,
  &envoy__config__core__v3__HeaderValueOption_msg_init,
  &envoy__config__core__v3__HeaderMap_msg_init,
  &envoy__config__core__v3__WatchedDirectory_msg_init,
  &envoy__config__core__v3__DataSource_msg_init,
  &envoy__config__core__v3__RetryPolicy_msg_init,
  &envoy__config__core__v3__RetryPolicy__RetryPriority_msg_init,
  &envoy__config__core__v3__RetryPolicy__RetryHostPredicate_msg_init,
  &envoy__config__core__v3__RemoteDataSource_msg_init,
  &envoy__config__core__v3__AsyncDataSource_msg_init,
  &envoy__config__core__v3__TransportSocket_msg_init,
  &envoy__config__core__v3__RuntimeFractionalPercent_msg_init,
  &envoy__config__core__v3__ControlPlane_msg_init,
};

const upb_MiniTableFile envoy_config_core_v3_base_proto_upb_file_layout = {
  messages_layout,
  NULL,
  NULL,
  30,
  0,
  0,
};

#include "upb/port/undef.inc"
