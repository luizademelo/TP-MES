
#include <stddef.h>
#include "upb/generated_code_support.h"
#include "envoy/config/trace/v3/skywalking.upb_minitable.h"
#include "envoy/config/core/v3/grpc_service.upb_minitable.h"
#include "google/protobuf/wrappers.upb_minitable.h"
#include "udpa/annotations/migrate.upb_minitable.h"
#include "udpa/annotations/sensitive.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
static const upb_MiniTableSubInternal envoy_config_trace_v3_SkyWalkingConfig__submsgs[2] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__GrpcService_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__trace__v3__ClientConfig_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_trace_v3_SkyWalkingConfig__fields[2] = {
  {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__trace__v3__SkyWalkingConfig_msg_init = {
  &envoy_config_trace_v3_SkyWalkingConfig__submsgs[0],
  &envoy_config_trace_v3_SkyWalkingConfig__fields[0],
  UPB_SIZE(24, 32), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.trace.v3.SkyWalkingConfig",
#endif
};

const upb_MiniTable* envoy__config__trace__v3__SkyWalkingConfig_msg_init_ptr = &envoy__config__trace__v3__SkyWalkingConfig_msg_init;
static const upb_MiniTableSubInternal envoy_config_trace_v3_ClientConfig__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__UInt32Value_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_trace_v3_ClientConfig__fields[4] = {
  {1, UPB_SIZE(20, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(28, 32), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(36, 48), UPB_SIZE(-17, -13), kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(12, 64), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__trace__v3__ClientConfig_msg_init = {
  &envoy_config_trace_v3_ClientConfig__submsgs[0],
  &envoy_config_trace_v3_ClientConfig__fields[0],
  UPB_SIZE(48, 72), 4, kUpb_ExtMode_NonExtendable, 4, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.trace.v3.ClientConfig",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
    {0x002000003f000012, &upb_pss_1bt},
    {0x0030000c0300001a, &upb_pos_1bt},
  })
};

const upb_MiniTable* envoy__config__trace__v3__ClientConfig_msg_init_ptr = &envoy__config__trace__v3__ClientConfig_msg_init;
static const upb_MiniTable *messages_layout[2] = {
  &envoy__config__trace__v3__SkyWalkingConfig_msg_init,
  &envoy__config__trace__v3__ClientConfig_msg_init,
};

const upb_MiniTableFile envoy_config_trace_v3_skywalking_proto_upb_file_layout = {
  messages_layout,
  NULL,
  NULL,
  2,
  0,
  0,
};

#include "upb/port/undef.inc"
