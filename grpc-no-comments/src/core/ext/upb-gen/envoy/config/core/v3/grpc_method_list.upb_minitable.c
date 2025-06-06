
#include <stddef.h>
#include "upb/generated_code_support.h"
#include "envoy/config/core/v3/grpc_method_list.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
static const upb_MiniTableSubInternal envoy_config_core_v3_GrpcMethodList__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__GrpcMethodList__Service_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_core_v3_GrpcMethodList__fields[1] = {
  {1, 8, 0, 0, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__core__v3__GrpcMethodList_msg_init = {
  &envoy_config_core_v3_GrpcMethodList__submsgs[0],
  &envoy_config_core_v3_GrpcMethodList__fields[0],
  16, 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.core.v3.GrpcMethodList",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f00000a, &upb_prm_1bt_max64b},
  })
};

const upb_MiniTable* envoy__config__core__v3__GrpcMethodList_msg_init_ptr = &envoy__config__core__v3__GrpcMethodList_msg_init;
static const upb_MiniTableField envoy_config_core_v3_GrpcMethodList_Service__fields[2] = {
  {1, UPB_SIZE(12, 8), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(8, 24), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__core__v3__GrpcMethodList__Service_msg_init = {
  NULL,
  &envoy_config_core_v3_GrpcMethodList_Service__fields[0],
  UPB_SIZE(24, 32), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.core.v3.GrpcMethodList.Service",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f00000a, &upb_pss_1bt},
    {0x001800003f000012, &upb_prs_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__config__core__v3__GrpcMethodList__Service_msg_init_ptr = &envoy__config__core__v3__GrpcMethodList__Service_msg_init;
static const upb_MiniTable *messages_layout[2] = {
  &envoy__config__core__v3__GrpcMethodList_msg_init,
  &envoy__config__core__v3__GrpcMethodList__Service_msg_init,
};

const upb_MiniTableFile envoy_config_core_v3_grpc_method_list_proto_upb_file_layout = {
  messages_layout,
  NULL,
  NULL,
  2,
  0,
  0,
};

#include "upb/port/undef.inc"
