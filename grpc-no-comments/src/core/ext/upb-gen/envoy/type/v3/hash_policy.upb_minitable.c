
#include <stddef.h>
#include "upb/generated_code_support.h"
#include "envoy/type/v3/hash_policy.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
static const upb_MiniTableSubInternal envoy_type_v3_HashPolicy__submsgs[2] = {
  {.UPB_PRIVATE(submsg) = &envoy__type__v3__HashPolicy__SourceIp_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__type__v3__HashPolicy__FilterState_msg_init_ptr},
};

static const upb_MiniTableField envoy_type_v3_HashPolicy__fields[2] = {
  {1, UPB_SIZE(12, 16), -9, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 16), -9, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__type__v3__HashPolicy_msg_init = {
  &envoy_type_v3_HashPolicy__submsgs[0],
  &envoy_type_v3_HashPolicy__fields[0],
  UPB_SIZE(16, 24), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.type.v3.HashPolicy",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000080100000a, &upb_pom_1bt_max64b},
    {0x0010000802010012, &upb_pom_1bt_max64b},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__type__v3__HashPolicy_msg_init_ptr = &envoy__type__v3__HashPolicy_msg_init;
const upb_MiniTable envoy__type__v3__HashPolicy__SourceIp_msg_init = {
  NULL,
  NULL,
  8, 0, kUpb_ExtMode_NonExtendable, 0, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.type.v3.HashPolicy.SourceIp",
#endif
};

const upb_MiniTable* envoy__type__v3__HashPolicy__SourceIp_msg_init_ptr = &envoy__type__v3__HashPolicy__SourceIp_msg_init;
static const upb_MiniTableField envoy_type_v3_HashPolicy_FilterState__fields[1] = {
  {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__type__v3__HashPolicy__FilterState_msg_init = {
  NULL,
  &envoy_type_v3_HashPolicy_FilterState__fields[0],
  UPB_SIZE(16, 24), 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.type.v3.HashPolicy.FilterState",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f00000a, &upb_pss_1bt},
  })
};

const upb_MiniTable* envoy__type__v3__HashPolicy__FilterState_msg_init_ptr = &envoy__type__v3__HashPolicy__FilterState_msg_init;
static const upb_MiniTable *messages_layout[3] = {
  &envoy__type__v3__HashPolicy_msg_init,
  &envoy__type__v3__HashPolicy__SourceIp_msg_init,
  &envoy__type__v3__HashPolicy__FilterState_msg_init,
};

const upb_MiniTableFile envoy_type_v3_hash_policy_proto_upb_file_layout = {
  messages_layout,
  NULL,
  NULL,
  3,
  0,
  0,
};

#include "upb/port/undef.inc"
