
#include <stddef.h>
#include "upb/generated_code_support.h"
#include "envoy/admin/v3/config_dump_shared.upb_minitable.h"
#include "google/protobuf/any.upb_minitable.h"
#include "google/protobuf/timestamp.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"

#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
static const upb_MiniTableSubInternal envoy_admin_v3_UpdateFailureState__submsgs[2] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__Any_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__Timestamp_msg_init_ptr},
};

static const upb_MiniTableField envoy_admin_v3_UpdateFailureState__fields[4] = {
  {1, UPB_SIZE(12, 48), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 56), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(28, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__admin__v3__UpdateFailureState_msg_init = {
  &envoy_admin_v3_UpdateFailureState__submsgs[0],
  &envoy_admin_v3_UpdateFailureState__fields[0],
  UPB_SIZE(40, 64), 4, kUpb_ExtMode_NonExtendable, 4, UPB_FASTTABLE_MASK(56), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.admin.v3.UpdateFailureState",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00001a, &upb_pss_1bt},
    {0x002000003f000022, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__admin__v3__UpdateFailureState_msg_init_ptr = &envoy__admin__v3__UpdateFailureState_msg_init;
static const upb_MiniTableSubInternal envoy_admin_v3_ListenersConfigDump__submsgs[2] = {
  {.UPB_PRIVATE(submsg) = &envoy__admin__v3__ListenersConfigDump__StaticListener_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__admin__v3__ListenersConfigDump__DynamicListener_msg_init_ptr},
};

static const upb_MiniTableField envoy_admin_v3_ListenersConfigDump__fields[3] = {
  {1, UPB_SIZE(16, 8), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(8, 24), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(12, 32), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__admin__v3__ListenersConfigDump_msg_init = {
  &envoy_admin_v3_ListenersConfigDump__submsgs[0],
  &envoy_admin_v3_ListenersConfigDump__fields[0],
  UPB_SIZE(24, 40), 3, kUpb_ExtMode_NonExtendable, 3, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.admin.v3.ListenersConfigDump",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f00000a, &upb_pss_1bt},
    {0x001800003f000012, &upb_prm_1bt_max64b},
    {0x002000003f01001a, &upb_prm_1bt_max128b},
  })
};

const upb_MiniTable* envoy__admin__v3__ListenersConfigDump_msg_init_ptr = &envoy__admin__v3__ListenersConfigDump_msg_init;
static const upb_MiniTableSubInternal envoy_admin_v3_ListenersConfigDump_StaticListener__submsgs[2] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__Any_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__Timestamp_msg_init_ptr},
};

static const upb_MiniTableField envoy_admin_v3_ListenersConfigDump_StaticListener__fields[2] = {
  {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__admin__v3__ListenersConfigDump__StaticListener_msg_init = {
  &envoy_admin_v3_ListenersConfigDump_StaticListener__submsgs[0],
  &envoy_admin_v3_ListenersConfigDump_StaticListener__fields[0],
  UPB_SIZE(24, 32), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.admin.v3.ListenersConfigDump.StaticListener",
#endif
};

const upb_MiniTable* envoy__admin__v3__ListenersConfigDump__StaticListener_msg_init_ptr = &envoy__admin__v3__ListenersConfigDump__StaticListener_msg_init;
static const upb_MiniTableSubInternal envoy_admin_v3_ListenersConfigDump_DynamicListenerState__submsgs[2] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__Any_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__Timestamp_msg_init_ptr},
};

static const upb_MiniTableField envoy_admin_v3_ListenersConfigDump_DynamicListenerState__fields[3] = {
  {1, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__admin__v3__ListenersConfigDump__DynamicListenerState_msg_init = {
  &envoy_admin_v3_ListenersConfigDump_DynamicListenerState__submsgs[0],
  &envoy_admin_v3_ListenersConfigDump_DynamicListenerState__fields[0],
  UPB_SIZE(32, 48), 3, kUpb_ExtMode_NonExtendable, 3, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.admin.v3.ListenersConfigDump.DynamicListenerState",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
  })
};

const upb_MiniTable* envoy__admin__v3__ListenersConfigDump__DynamicListenerState_msg_init_ptr = &envoy__admin__v3__ListenersConfigDump__DynamicListenerState_msg_init;
static const upb_MiniTableSubInternal envoy_admin_v3_ListenersConfigDump_DynamicListener__submsgs[4] = {
  {.UPB_PRIVATE(submsg) = &envoy__admin__v3__ListenersConfigDump__DynamicListenerState_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__admin__v3__ListenersConfigDump__DynamicListenerState_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__admin__v3__ListenersConfigDump__DynamicListenerState_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__admin__v3__UpdateFailureState_msg_init_ptr},
};

static const upb_MiniTableField envoy_admin_v3_ListenersConfigDump_DynamicListener__fields[6] = {
  {1, UPB_SIZE(32, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(20, 48), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(24, 56), 67, 3, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {6, UPB_SIZE(28, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__admin__v3__ListenersConfigDump__DynamicListener_msg_init = {
  &envoy_admin_v3_ListenersConfigDump_DynamicListener__submsgs[0],
  &envoy_admin_v3_ListenersConfigDump_DynamicListener__fields[0],
  UPB_SIZE(40, 64), 6, kUpb_ExtMode_NonExtendable, 6, UPB_FASTTABLE_MASK(56), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.admin.v3.ListenersConfigDump.DynamicListener",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000c00003f000030, &upb_psv4_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__admin__v3__ListenersConfigDump__DynamicListener_msg_init_ptr = &envoy__admin__v3__ListenersConfigDump__DynamicListener_msg_init;
static const upb_MiniTableSubInternal envoy_admin_v3_ClustersConfigDump__submsgs[3] = {
  {.UPB_PRIVATE(submsg) = &envoy__admin__v3__ClustersConfigDump__StaticCluster_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__admin__v3__ClustersConfigDump__DynamicCluster_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__admin__v3__ClustersConfigDump__DynamicCluster_msg_init_ptr},
};

static const upb_MiniTableField envoy_admin_v3_ClustersConfigDump__fields[4] = {
  {1, UPB_SIZE(20, 8), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(8, 24), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(12, 32), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(16, 40), 0, 2, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__admin__v3__ClustersConfigDump_msg_init = {
  &envoy_admin_v3_ClustersConfigDump__submsgs[0],
  &envoy_admin_v3_ClustersConfigDump__fields[0],
  UPB_SIZE(32, 48), 4, kUpb_ExtMode_NonExtendable, 4, UPB_FASTTABLE_MASK(56), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.admin.v3.ClustersConfigDump",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f00000a, &upb_pss_1bt},
    {0x001800003f000012, &upb_prm_1bt_max64b},
    {0x002000003f01001a, &upb_prm_1bt_max64b},
    {0x002800003f020022, &upb_prm_1bt_max64b},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__admin__v3__ClustersConfigDump_msg_init_ptr = &envoy__admin__v3__ClustersConfigDump_msg_init;
static const upb_MiniTableSubInternal envoy_admin_v3_ClustersConfigDump_StaticCluster__submsgs[2] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__Any_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__Timestamp_msg_init_ptr},
};

static const upb_MiniTableField envoy_admin_v3_ClustersConfigDump_StaticCluster__fields[2] = {
  {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__admin__v3__ClustersConfigDump__StaticCluster_msg_init = {
  &envoy_admin_v3_ClustersConfigDump_StaticCluster__submsgs[0],
  &envoy_admin_v3_ClustersConfigDump_StaticCluster__fields[0],
  UPB_SIZE(24, 32), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.admin.v3.ClustersConfigDump.StaticCluster",
#endif
};

const upb_MiniTable* envoy__admin__v3__ClustersConfigDump__StaticCluster_msg_init_ptr = &envoy__admin__v3__ClustersConfigDump__StaticCluster_msg_init;
static const upb_MiniTableSubInternal envoy_admin_v3_ClustersConfigDump_DynamicCluster__submsgs[3] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__Any_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__Timestamp_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__admin__v3__UpdateFailureState_msg_init_ptr},
};

static const upb_MiniTableField envoy_admin_v3_ClustersConfigDump_DynamicCluster__fields[5] = {
  {1, UPB_SIZE(28, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(20, 48), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(24, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__admin__v3__ClustersConfigDump__DynamicCluster_msg_init = {
  &envoy_admin_v3_ClustersConfigDump_DynamicCluster__submsgs[0],
  &envoy_admin_v3_ClustersConfigDump_DynamicCluster__fields[0],
  UPB_SIZE(40, 56), 5, kUpb_ExtMode_NonExtendable, 5, UPB_FASTTABLE_MASK(56), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.admin.v3.ClustersConfigDump.DynamicCluster",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000c00003f000028, &upb_psv4_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__admin__v3__ClustersConfigDump__DynamicCluster_msg_init_ptr = &envoy__admin__v3__ClustersConfigDump__DynamicCluster_msg_init;
static const upb_MiniTableSubInternal envoy_admin_v3_RoutesConfigDump__submsgs[2] = {
  {.UPB_PRIVATE(submsg) = &envoy__admin__v3__RoutesConfigDump__StaticRouteConfig_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__admin__v3__RoutesConfigDump__DynamicRouteConfig_msg_init_ptr},
};

static const upb_MiniTableField envoy_admin_v3_RoutesConfigDump__fields[2] = {
  {2, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(12, 16), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__admin__v3__RoutesConfigDump_msg_init = {
  &envoy_admin_v3_RoutesConfigDump__submsgs[0],
  &envoy_admin_v3_RoutesConfigDump__fields[0],
  UPB_SIZE(16, 24), 2, kUpb_ExtMode_NonExtendable, 0, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.admin.v3.RoutesConfigDump",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f000012, &upb_prm_1bt_max64b},
    {0x001000003f01001a, &upb_prm_1bt_max64b},
  })
};

const upb_MiniTable* envoy__admin__v3__RoutesConfigDump_msg_init_ptr = &envoy__admin__v3__RoutesConfigDump_msg_init;
static const upb_MiniTableSubInternal envoy_admin_v3_RoutesConfigDump_StaticRouteConfig__submsgs[2] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__Any_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__Timestamp_msg_init_ptr},
};

static const upb_MiniTableField envoy_admin_v3_RoutesConfigDump_StaticRouteConfig__fields[2] = {
  {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__admin__v3__RoutesConfigDump__StaticRouteConfig_msg_init = {
  &envoy_admin_v3_RoutesConfigDump_StaticRouteConfig__submsgs[0],
  &envoy_admin_v3_RoutesConfigDump_StaticRouteConfig__fields[0],
  UPB_SIZE(24, 32), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.admin.v3.RoutesConfigDump.StaticRouteConfig",
#endif
};

const upb_MiniTable* envoy__admin__v3__RoutesConfigDump__StaticRouteConfig_msg_init_ptr = &envoy__admin__v3__RoutesConfigDump__StaticRouteConfig_msg_init;
static const upb_MiniTableSubInternal envoy_admin_v3_RoutesConfigDump_DynamicRouteConfig__submsgs[3] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__Any_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__Timestamp_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__admin__v3__UpdateFailureState_msg_init_ptr},
};

static const upb_MiniTableField envoy_admin_v3_RoutesConfigDump_DynamicRouteConfig__fields[5] = {
  {1, UPB_SIZE(28, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(20, 48), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(24, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__admin__v3__RoutesConfigDump__DynamicRouteConfig_msg_init = {
  &envoy_admin_v3_RoutesConfigDump_DynamicRouteConfig__submsgs[0],
  &envoy_admin_v3_RoutesConfigDump_DynamicRouteConfig__fields[0],
  UPB_SIZE(40, 56), 5, kUpb_ExtMode_NonExtendable, 5, UPB_FASTTABLE_MASK(56), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.admin.v3.RoutesConfigDump.DynamicRouteConfig",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000c00003f000028, &upb_psv4_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__admin__v3__RoutesConfigDump__DynamicRouteConfig_msg_init_ptr = &envoy__admin__v3__RoutesConfigDump__DynamicRouteConfig_msg_init;
static const upb_MiniTableSubInternal envoy_admin_v3_ScopedRoutesConfigDump__submsgs[2] = {
  {.UPB_PRIVATE(submsg) = &envoy__admin__v3__ScopedRoutesConfigDump__InlineScopedRouteConfigs_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__admin__v3__ScopedRoutesConfigDump__DynamicScopedRouteConfigs_msg_init_ptr},
};

static const upb_MiniTableField envoy_admin_v3_ScopedRoutesConfigDump__fields[2] = {
  {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 16), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__admin__v3__ScopedRoutesConfigDump_msg_init = {
  &envoy_admin_v3_ScopedRoutesConfigDump__submsgs[0],
  &envoy_admin_v3_ScopedRoutesConfigDump__fields[0],
  UPB_SIZE(16, 24), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.admin.v3.ScopedRoutesConfigDump",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f00000a, &upb_prm_1bt_max64b},
    {0x001000003f010012, &upb_prm_1bt_max128b},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__admin__v3__ScopedRoutesConfigDump_msg_init_ptr = &envoy__admin__v3__ScopedRoutesConfigDump_msg_init;
static const upb_MiniTableSubInternal envoy_admin_v3_ScopedRoutesConfigDump_InlineScopedRouteConfigs__submsgs[2] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__Any_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__Timestamp_msg_init_ptr},
};

static const upb_MiniTableField envoy_admin_v3_ScopedRoutesConfigDump_InlineScopedRouteConfigs__fields[3] = {
  {1, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 32), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(16, 40), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__admin__v3__ScopedRoutesConfigDump__InlineScopedRouteConfigs_msg_init = {
  &envoy_admin_v3_ScopedRoutesConfigDump_InlineScopedRouteConfigs__submsgs[0],
  &envoy_admin_v3_ScopedRoutesConfigDump_InlineScopedRouteConfigs__fields[0],
  UPB_SIZE(32, 48), 3, kUpb_ExtMode_NonExtendable, 3, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.admin.v3.ScopedRoutesConfigDump.InlineScopedRouteConfigs",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
    {0x002000003f000012, &upb_prm_1bt_maxmaxb},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__admin__v3__ScopedRoutesConfigDump__InlineScopedRouteConfigs_msg_init_ptr = &envoy__admin__v3__ScopedRoutesConfigDump__InlineScopedRouteConfigs_msg_init;
static const upb_MiniTableSubInternal envoy_admin_v3_ScopedRoutesConfigDump_DynamicScopedRouteConfigs__submsgs[3] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__Any_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__Timestamp_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__admin__v3__UpdateFailureState_msg_init_ptr},
};

static const upb_MiniTableField envoy_admin_v3_ScopedRoutesConfigDump_DynamicScopedRouteConfigs__fields[6] = {
  {1, UPB_SIZE(28, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(36, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(12, 48), 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(16, 56), 64, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(20, 64), 65, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {6, UPB_SIZE(24, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__admin__v3__ScopedRoutesConfigDump__DynamicScopedRouteConfigs_msg_init = {
  &envoy_admin_v3_ScopedRoutesConfigDump_DynamicScopedRouteConfigs__submsgs[0],
  &envoy_admin_v3_ScopedRoutesConfigDump_DynamicScopedRouteConfigs__fields[0],
  UPB_SIZE(48, 72), 6, kUpb_ExtMode_NonExtendable, 6, UPB_FASTTABLE_MASK(56), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.admin.v3.ScopedRoutesConfigDump.DynamicScopedRouteConfigs",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
    {0x002000003f000012, &upb_pss_1bt},
    {0x003000003f00001a, &upb_prm_1bt_maxmaxb},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000c00003f000030, &upb_psv4_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__admin__v3__ScopedRoutesConfigDump__DynamicScopedRouteConfigs_msg_init_ptr = &envoy__admin__v3__ScopedRoutesConfigDump__DynamicScopedRouteConfigs_msg_init;
static const upb_MiniTableSubInternal envoy_admin_v3_EndpointsConfigDump__submsgs[2] = {
  {.UPB_PRIVATE(submsg) = &envoy__admin__v3__EndpointsConfigDump__StaticEndpointConfig_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__admin__v3__EndpointsConfigDump__DynamicEndpointConfig_msg_init_ptr},
};

static const upb_MiniTableField envoy_admin_v3_EndpointsConfigDump__fields[2] = {
  {2, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(12, 16), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__admin__v3__EndpointsConfigDump_msg_init = {
  &envoy_admin_v3_EndpointsConfigDump__submsgs[0],
  &envoy_admin_v3_EndpointsConfigDump__fields[0],
  UPB_SIZE(16, 24), 2, kUpb_ExtMode_NonExtendable, 0, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.admin.v3.EndpointsConfigDump",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f000012, &upb_prm_1bt_max64b},
    {0x001000003f01001a, &upb_prm_1bt_max64b},
  })
};

const upb_MiniTable* envoy__admin__v3__EndpointsConfigDump_msg_init_ptr = &envoy__admin__v3__EndpointsConfigDump_msg_init;
static const upb_MiniTableSubInternal envoy_admin_v3_EndpointsConfigDump_StaticEndpointConfig__submsgs[2] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__Any_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__Timestamp_msg_init_ptr},
};

static const upb_MiniTableField envoy_admin_v3_EndpointsConfigDump_StaticEndpointConfig__fields[2] = {
  {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__admin__v3__EndpointsConfigDump__StaticEndpointConfig_msg_init = {
  &envoy_admin_v3_EndpointsConfigDump_StaticEndpointConfig__submsgs[0],
  &envoy_admin_v3_EndpointsConfigDump_StaticEndpointConfig__fields[0],
  UPB_SIZE(24, 32), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.admin.v3.EndpointsConfigDump.StaticEndpointConfig",
#endif
};

const upb_MiniTable* envoy__admin__v3__EndpointsConfigDump__StaticEndpointConfig_msg_init_ptr = &envoy__admin__v3__EndpointsConfigDump__StaticEndpointConfig_msg_init;
static const upb_MiniTableSubInternal envoy_admin_v3_EndpointsConfigDump_DynamicEndpointConfig__submsgs[3] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__Any_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__Timestamp_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__admin__v3__UpdateFailureState_msg_init_ptr},
};

static const upb_MiniTableField envoy_admin_v3_EndpointsConfigDump_DynamicEndpointConfig__fields[5] = {
  {1, UPB_SIZE(28, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(20, 48), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(24, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__admin__v3__EndpointsConfigDump__DynamicEndpointConfig_msg_init = {
  &envoy_admin_v3_EndpointsConfigDump_DynamicEndpointConfig__submsgs[0],
  &envoy_admin_v3_EndpointsConfigDump_DynamicEndpointConfig__fields[0],
  UPB_SIZE(40, 56), 5, kUpb_ExtMode_NonExtendable, 5, UPB_FASTTABLE_MASK(56), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.admin.v3.EndpointsConfigDump.DynamicEndpointConfig",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000c00003f000028, &upb_psv4_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__admin__v3__EndpointsConfigDump__DynamicEndpointConfig_msg_init_ptr = &envoy__admin__v3__EndpointsConfigDump__DynamicEndpointConfig_msg_init;
static const upb_MiniTableSubInternal envoy_admin_v3_EcdsConfigDump__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &envoy__admin__v3__EcdsConfigDump__EcdsFilterConfig_msg_init_ptr},
};

static const upb_MiniTableField envoy_admin_v3_EcdsConfigDump__fields[1] = {
  {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__admin__v3__EcdsConfigDump_msg_init = {
  &envoy_admin_v3_EcdsConfigDump__submsgs[0],
  &envoy_admin_v3_EcdsConfigDump__fields[0],
  16, 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.admin.v3.EcdsConfigDump",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f00000a, &upb_prm_1bt_max64b},
  })
};

const upb_MiniTable* envoy__admin__v3__EcdsConfigDump_msg_init_ptr = &envoy__admin__v3__EcdsConfigDump_msg_init;
static const upb_MiniTableSubInternal envoy_admin_v3_EcdsConfigDump_EcdsFilterConfig__submsgs[3] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__Any_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &google__protobuf__Timestamp_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__admin__v3__UpdateFailureState_msg_init_ptr},
};

static const upb_MiniTableField envoy_admin_v3_EcdsConfigDump_EcdsFilterConfig__fields[5] = {
  {1, UPB_SIZE(28, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(20, 48), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {5, UPB_SIZE(24, 12), 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__admin__v3__EcdsConfigDump__EcdsFilterConfig_msg_init = {
  &envoy_admin_v3_EcdsConfigDump_EcdsFilterConfig__submsgs[0],
  &envoy_admin_v3_EcdsConfigDump_EcdsFilterConfig__fields[0],
  UPB_SIZE(40, 56), 5, kUpb_ExtMode_NonExtendable, 5, UPB_FASTTABLE_MASK(56), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.admin.v3.EcdsConfigDump.EcdsFilterConfig",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000c00003f000028, &upb_psv4_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__admin__v3__EcdsConfigDump__EcdsFilterConfig_msg_init_ptr = &envoy__admin__v3__EcdsConfigDump__EcdsFilterConfig_msg_init;
static const upb_MiniTable *messages_layout[19] = {
  &envoy__admin__v3__UpdateFailureState_msg_init,
  &envoy__admin__v3__ListenersConfigDump_msg_init,
  &envoy__admin__v3__ListenersConfigDump__StaticListener_msg_init,
  &envoy__admin__v3__ListenersConfigDump__DynamicListenerState_msg_init,
  &envoy__admin__v3__ListenersConfigDump__DynamicListener_msg_init,
  &envoy__admin__v3__ClustersConfigDump_msg_init,
  &envoy__admin__v3__ClustersConfigDump__StaticCluster_msg_init,
  &envoy__admin__v3__ClustersConfigDump__DynamicCluster_msg_init,
  &envoy__admin__v3__RoutesConfigDump_msg_init,
  &envoy__admin__v3__RoutesConfigDump__StaticRouteConfig_msg_init,
  &envoy__admin__v3__RoutesConfigDump__DynamicRouteConfig_msg_init,
  &envoy__admin__v3__ScopedRoutesConfigDump_msg_init,
  &envoy__admin__v3__ScopedRoutesConfigDump__InlineScopedRouteConfigs_msg_init,
  &envoy__admin__v3__ScopedRoutesConfigDump__DynamicScopedRouteConfigs_msg_init,
  &envoy__admin__v3__EndpointsConfigDump_msg_init,
  &envoy__admin__v3__EndpointsConfigDump__StaticEndpointConfig_msg_init,
  &envoy__admin__v3__EndpointsConfigDump__DynamicEndpointConfig_msg_init,
  &envoy__admin__v3__EcdsConfigDump_msg_init,
  &envoy__admin__v3__EcdsConfigDump__EcdsFilterConfig_msg_init,
};

const upb_MiniTableFile envoy_admin_v3_config_dump_shared_proto_upb_file_layout = {
  messages_layout,
  NULL,
  NULL,
  19,
  0,
  0,
};

#include "upb/port/undef.inc"
