
#include <stddef.h>
#include "upb/generated_code_support.h"
#include "envoy/admin/v3/config_dump.upb_minitable.h"
#include "envoy/admin/v3/config_dump_shared.upb_minitable.h"
#include "envoy/config/bootstrap/v3/bootstrap.upb_minitable.h"
#include "google/protobuf/any.upb_minitable.h"
#include "google/protobuf/timestamp.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"

#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
static const upb_MiniTableSubInternal envoy_admin_v3_ConfigDump__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__Any_msg_init_ptr},
};

static const upb_MiniTableField envoy_admin_v3_ConfigDump__fields[1] = {
  {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__admin__v3__ConfigDump_msg_init = {
  &envoy_admin_v3_ConfigDump__submsgs[0],
  &envoy_admin_v3_ConfigDump__fields[0],
  16, 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.admin.v3.ConfigDump",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f00000a, &upb_prm_1bt_maxmaxb},
  })
};

const upb_MiniTable* envoy__admin__v3__ConfigDump_msg_init_ptr = &envoy__admin__v3__ConfigDump_msg_init;
static const upb_MiniTableSubInternal envoy_admin_v3_BootstrapConfigDump__submsgs[2] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__bootstrap__v3__Bootstrap_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__Timestamp_msg_init_ptr},
};

static const upb_MiniTableField envoy_admin_v3_BootstrapConfigDump__fields[2] = {
  {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__admin__v3__BootstrapConfigDump_msg_init = {
  &envoy_admin_v3_BootstrapConfigDump__submsgs[0],
  &envoy_admin_v3_BootstrapConfigDump__fields[0],
  UPB_SIZE(24, 32), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.admin.v3.BootstrapConfigDump",
#endif
};

const upb_MiniTable* envoy__admin__v3__BootstrapConfigDump_msg_init_ptr = &envoy__admin__v3__BootstrapConfigDump_msg_init;
static const upb_MiniTableSubInternal envoy_admin_v3_SecretsConfigDump__submsgs[3] = {
  {.UPB_PRIVATE(submsg) = &envoy__admin__v3__SecretsConfigDump__StaticSecret_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__admin__v3__SecretsConfigDump__DynamicSecret_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__admin__v3__SecretsConfigDump__DynamicSecret_msg_init_ptr},
};

static const upb_MiniTableField envoy_admin_v3_SecretsConfigDump__fields[3] = {
  {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 16), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(16, 24), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__admin__v3__SecretsConfigDump_msg_init = {
  &envoy_admin_v3_SecretsConfigDump__submsgs[0],
  &envoy_admin_v3_SecretsConfigDump__fields[0],
  UPB_SIZE(24, 32), 3, kUpb_ExtMode_NonExtendable, 3, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.admin.v3.SecretsConfigDump",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f00000a, &upb_prm_1bt_max64b},
    {0x001000003f010012, &upb_prm_1bt_max128b},
    {0x001800003f02001a, &upb_prm_1bt_max128b},
  })
};

const upb_MiniTable* envoy__admin__v3__SecretsConfigDump_msg_init_ptr = &envoy__admin__v3__SecretsConfigDump_msg_init;
static const upb_MiniTableSubInternal envoy_admin_v3_SecretsConfigDump_DynamicSecret__submsgs[3] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__Timestamp_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__Any_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__admin__v3__UpdateFailureState_msg_init_ptr},
};

static const upb_MiniTableField envoy_admin_v3_SecretsConfigDump_DynamicSecret__fields[6] = {
  {1, UPB_SIZE(28, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(36, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(12, 48), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(16, 56), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(20, 64), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {6, UPB_SIZE(24, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__admin__v3__SecretsConfigDump__DynamicSecret_msg_init = {
  &envoy_admin_v3_SecretsConfigDump_DynamicSecret__submsgs[0],
  &envoy_admin_v3_SecretsConfigDump_DynamicSecret__fields[0],
  UPB_SIZE(48, 72), 6, kUpb_ExtMode_NonExtendable, 6, UPB_FASTTABLE_MASK(56), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.admin.v3.SecretsConfigDump.DynamicSecret",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
    {0x002000003f000012, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000c00003f000030, &upb_psv4_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__admin__v3__SecretsConfigDump__DynamicSecret_msg_init_ptr = &envoy__admin__v3__SecretsConfigDump__DynamicSecret_msg_init;
static const upb_MiniTableSubInternal envoy_admin_v3_SecretsConfigDump_StaticSecret__submsgs[2] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__Timestamp_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__Any_msg_init_ptr},
};

static const upb_MiniTableField envoy_admin_v3_SecretsConfigDump_StaticSecret__fields[3] = {
  {1, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__admin__v3__SecretsConfigDump__StaticSecret_msg_init = {
  &envoy_admin_v3_SecretsConfigDump_StaticSecret__submsgs[0],
  &envoy_admin_v3_SecretsConfigDump_StaticSecret__fields[0],
  UPB_SIZE(32, 48), 3, kUpb_ExtMode_NonExtendable, 3, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.admin.v3.SecretsConfigDump.StaticSecret",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
  })
};

const upb_MiniTable* envoy__admin__v3__SecretsConfigDump__StaticSecret_msg_init_ptr = &envoy__admin__v3__SecretsConfigDump__StaticSecret_msg_init;
static const upb_MiniTable *messages_layout[5] = {
  &envoy__admin__v3__ConfigDump_msg_init,
  &envoy__admin__v3__BootstrapConfigDump_msg_init,
  &envoy__admin__v3__SecretsConfigDump_msg_init,
  &envoy__admin__v3__SecretsConfigDump__DynamicSecret_msg_init,
  &envoy__admin__v3__SecretsConfigDump__StaticSecret_msg_init,
};

const upb_MiniTableFile envoy_admin_v3_config_dump_proto_upb_file_layout = {
  messages_layout,
  NULL,
  NULL,
  5,
  0,
  0,
};

#include "upb/port/undef.inc"
