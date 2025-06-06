
#include <stddef.h>
#include "upb/generated_code_support.h"
#include "envoy/type/metadata/v3/metadata.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
static const upb_MiniTableSubInternal envoy_type_metadata_v3_MetadataKey__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &envoy__type__metadata__v3__MetadataKey__PathSegment_msg_init_ptr},
};

static const upb_MiniTableField envoy_type_metadata_v3_MetadataKey__fields[2] = {
  {1, UPB_SIZE(12, 8), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(8, 24), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__type__metadata__v3__MetadataKey_msg_init = {
  &envoy_type_metadata_v3_MetadataKey__submsgs[0],
  &envoy_type_metadata_v3_MetadataKey__fields[0],
  UPB_SIZE(24, 32), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.type.metadata.v3.MetadataKey",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f00000a, &upb_pss_1bt},
    {0x001800003f000012, &upb_prm_1bt_max64b},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__type__metadata__v3__MetadataKey_msg_init_ptr = &envoy__type__metadata__v3__MetadataKey_msg_init;
static const upb_MiniTableField envoy_type_metadata_v3_MetadataKey_PathSegment__fields[1] = {
  {1, UPB_SIZE(12, 16), -9, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__type__metadata__v3__MetadataKey__PathSegment_msg_init = {
  NULL,
  &envoy_type_metadata_v3_MetadataKey_PathSegment__fields[0],
  UPB_SIZE(24, 32), 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.type.metadata.v3.MetadataKey.PathSegment",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000080100000a, &upb_pos_1bt},
  })
};

const upb_MiniTable* envoy__type__metadata__v3__MetadataKey__PathSegment_msg_init_ptr = &envoy__type__metadata__v3__MetadataKey__PathSegment_msg_init;
static const upb_MiniTableSubInternal envoy_type_metadata_v3_MetadataKind__submsgs[4] = {
  {.UPB_PRIVATE(submsg) = &envoy__type__metadata__v3__MetadataKind__Request_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__type__metadata__v3__MetadataKind__Route_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__type__metadata__v3__MetadataKind__Cluster_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__type__metadata__v3__MetadataKind__Host_msg_init_ptr},
};

static const upb_MiniTableField envoy_type_metadata_v3_MetadataKind__fields[4] = {
  {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(12, 16), -9, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(12, 16), -9, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__type__metadata__v3__MetadataKind_msg_init = {
  &envoy_type_metadata_v3_MetadataKind__submsgs[0],
  &envoy_type_metadata_v3_MetadataKind__fields[0],
  UPB_SIZE(16, 24), 4, kUpb_ExtMode_NonExtendable, 4, UPB_FASTTABLE_MASK(56), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.type.metadata.v3.MetadataKind",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000080100000a, &upb_pom_1bt_max64b},
    {0x0010000802010012, &upb_pom_1bt_max64b},
    {0x001000080302001a, &upb_pom_1bt_max64b},
    {0x0010000804030022, &upb_pom_1bt_max64b},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__type__metadata__v3__MetadataKind_msg_init_ptr = &envoy__type__metadata__v3__MetadataKind_msg_init;
const upb_MiniTable envoy__type__metadata__v3__MetadataKind__Request_msg_init = {
  NULL,
  NULL,
  8, 0, kUpb_ExtMode_NonExtendable, 0, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.type.metadata.v3.MetadataKind.Request",
#endif
};

const upb_MiniTable* envoy__type__metadata__v3__MetadataKind__Request_msg_init_ptr = &envoy__type__metadata__v3__MetadataKind__Request_msg_init;
const upb_MiniTable envoy__type__metadata__v3__MetadataKind__Route_msg_init = {
  NULL,
  NULL,
  8, 0, kUpb_ExtMode_NonExtendable, 0, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.type.metadata.v3.MetadataKind.Route",
#endif
};

const upb_MiniTable* envoy__type__metadata__v3__MetadataKind__Route_msg_init_ptr = &envoy__type__metadata__v3__MetadataKind__Route_msg_init;
const upb_MiniTable envoy__type__metadata__v3__MetadataKind__Cluster_msg_init = {
  NULL,
  NULL,
  8, 0, kUpb_ExtMode_NonExtendable, 0, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.type.metadata.v3.MetadataKind.Cluster",
#endif
};

const upb_MiniTable* envoy__type__metadata__v3__MetadataKind__Cluster_msg_init_ptr = &envoy__type__metadata__v3__MetadataKind__Cluster_msg_init;
const upb_MiniTable envoy__type__metadata__v3__MetadataKind__Host_msg_init = {
  NULL,
  NULL,
  8, 0, kUpb_ExtMode_NonExtendable, 0, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.type.metadata.v3.MetadataKind.Host",
#endif
};

const upb_MiniTable* envoy__type__metadata__v3__MetadataKind__Host_msg_init_ptr = &envoy__type__metadata__v3__MetadataKind__Host_msg_init;
static const upb_MiniTable *messages_layout[7] = {
  &envoy__type__metadata__v3__MetadataKey_msg_init,
  &envoy__type__metadata__v3__MetadataKey__PathSegment_msg_init,
  &envoy__type__metadata__v3__MetadataKind_msg_init,
  &envoy__type__metadata__v3__MetadataKind__Request_msg_init,
  &envoy__type__metadata__v3__MetadataKind__Route_msg_init,
  &envoy__type__metadata__v3__MetadataKind__Cluster_msg_init,
  &envoy__type__metadata__v3__MetadataKind__Host_msg_init,
};

const upb_MiniTableFile envoy_type_metadata_v3_metadata_proto_upb_file_layout = {
  messages_layout,
  NULL,
  NULL,
  7,
  0,
  0,
};

#include "upb/port/undef.inc"
