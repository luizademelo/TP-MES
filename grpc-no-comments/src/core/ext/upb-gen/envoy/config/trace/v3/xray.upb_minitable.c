
#include <stddef.h>
#include "upb/generated_code_support.h"
#include "envoy/config/trace/v3/xray.upb_minitable.h"
#include "envoy/config/core/v3/address.upb_minitable.h"
#include "envoy/config/core/v3/base.upb_minitable.h"
#include "google/protobuf/struct.upb_minitable.h"
#include "udpa/annotations/migrate.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
static const upb_MiniTableSubInternal envoy_config_trace_v3_XRayConfig__submsgs[3] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__SocketAddress_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__DataSource_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__trace__v3__XRayConfig__SegmentFields_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_trace_v3_XRayConfig__fields[4] = {
  {1, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(24, 16), 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {3, UPB_SIZE(16, 40), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {4, UPB_SIZE(20, 48), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__trace__v3__XRayConfig_msg_init = {
  &envoy_config_trace_v3_XRayConfig__submsgs[0],
  &envoy_config_trace_v3_XRayConfig__fields[0],
  UPB_SIZE(32, 56), 4, kUpb_ExtMode_NonExtendable, 4, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.trace.v3.XRayConfig",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f000012, &upb_pss_1bt},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__config__trace__v3__XRayConfig_msg_init_ptr = &envoy__config__trace__v3__XRayConfig_msg_init;
static const upb_MiniTableSubInternal envoy_config_trace_v3_XRayConfig_SegmentFields__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__Struct_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_trace_v3_XRayConfig_SegmentFields__fields[2] = {
  {1, 16, 0, kUpb_NoSub, 9, (int)kUpb_FieldMode_Scalar | ((int)kUpb_FieldRep_StringView << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(12, 32), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__trace__v3__XRayConfig__SegmentFields_msg_init = {
  &envoy_config_trace_v3_XRayConfig_SegmentFields__submsgs[0],
  &envoy_config_trace_v3_XRayConfig_SegmentFields__fields[0],
  UPB_SIZE(24, 40), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.trace.v3.XRayConfig.SegmentFields",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001000003f00000a, &upb_pss_1bt},
  })
};

const upb_MiniTable* envoy__config__trace__v3__XRayConfig__SegmentFields_msg_init_ptr = &envoy__config__trace__v3__XRayConfig__SegmentFields_msg_init;
static const upb_MiniTable *messages_layout[2] = {
  &envoy__config__trace__v3__XRayConfig_msg_init,
  &envoy__config__trace__v3__XRayConfig__SegmentFields_msg_init,
};

const upb_MiniTableFile envoy_config_trace_v3_xray_proto_upb_file_layout = {
  messages_layout,
  NULL,
  NULL,
  2,
  0,
  0,
};

#include "upb/port/undef.inc"
