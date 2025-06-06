
#include <stddef.h>
#include "upb/generated_code_support.h"
#include "envoy/admin/v3/listeners.upb_minitable.h"
#include "envoy/config/core/v3/address.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"

#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
static const upb_MiniTableSubInternal envoy_admin_v3_Listeners__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &envoy__admin__v3__ListenerStatus_msg_init_ptr},
};

static const upb_MiniTableField envoy_admin_v3_Listeners__fields[1] = {
  {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__admin__v3__Listeners_msg_init = {
  &envoy_admin_v3_Listeners__submsgs[0],
  &envoy_admin_v3_Listeners__fields[0],
  16, 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.admin.v3.Listeners",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f00000a, &upb_prm_1bt_max64b},
  })
};

const upb_MiniTable* envoy__admin__v3__Listeners_msg_init_ptr = &envoy__admin__v3__Listeners_msg_init;
static const upb_MiniTableSubInternal envoy_admin_v3_ListenerStatus__submsgs[2] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__Address_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__Address_msg_init_ptr},
};

static const upb_MiniTableField envoy_admin_v3_ListenerStatus__fields[3] = {
  {1, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(16, 40), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__admin__v3__ListenerStatus_msg_init = {
  &envoy_admin_v3_ListenerStatus__submsgs[0],
  &envoy_admin_v3_ListenerStatus__fields[0],
  UPB_SIZE(32, 48), 3, kUpb_ExtMode_NonExtendable, 3, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.admin.v3.ListenerStatus",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x002800003f01001a, &upb_prm_1bt_maxmaxb},
  })
};

const upb_MiniTable* envoy__admin__v3__ListenerStatus_msg_init_ptr = &envoy__admin__v3__ListenerStatus_msg_init;
static const upb_MiniTable *messages_layout[2] = {
  &envoy__admin__v3__Listeners_msg_init,
  &envoy__admin__v3__ListenerStatus_msg_init,
};

const upb_MiniTableFile envoy_admin_v3_listeners_proto_upb_file_layout = {
  messages_layout,
  NULL,
  NULL,
  2,
  0,
  0,
};

#include "upb/port/undef.inc"
