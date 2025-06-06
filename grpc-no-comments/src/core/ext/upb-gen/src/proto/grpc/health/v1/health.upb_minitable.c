
#include <stddef.h>
#include "upb/generated_code_support.h"
#include "src/proto/grpc/health/v1/health.upb_minitable.h"

#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
static const upb_MiniTableField grpc_health_v1_HealthCheckRequest__fields[1] = {
  {1, 8, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
};

const upb_MiniTable grpc__health__v1__HealthCheckRequest_msg_init = {
  NULL,
  &grpc_health_v1_HealthCheckRequest__fields[0],
  UPB_SIZE(16, 24), 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "grpc.health.v1.HealthCheckRequest",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f00000a, &upb_pss_1bt},
  })
};

const upb_MiniTable* grpc__health__v1__HealthCheckRequest_msg_init_ptr = &grpc__health__v1__HealthCheckRequest_msg_init;
static const upb_MiniTableField grpc_health_v1_HealthCheckResponse__fields[1] = {
  {1, 8, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable grpc__health__v1__HealthCheckResponse_msg_init = {
  NULL,
  &grpc_health_v1_HealthCheckResponse__fields[0],
  16, 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "grpc.health.v1.HealthCheckResponse",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f000008, &upb_psv4_1bt},
  })
};

const upb_MiniTable* grpc__health__v1__HealthCheckResponse_msg_init_ptr = &grpc__health__v1__HealthCheckResponse_msg_init;
static const upb_MiniTable *messages_layout[2] = {
  &grpc__health__v1__HealthCheckRequest_msg_init,
  &grpc__health__v1__HealthCheckResponse_msg_init,
};

const upb_MiniTableFile src_proto_grpc_health_v1_health_proto_upb_file_layout = {
  messages_layout,
  NULL,
  NULL,
  2,
  0,
  0,
};

#include "upb/port/undef.inc"
