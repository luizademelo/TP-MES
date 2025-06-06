
#include <stddef.h>
#include "upb/generated_code_support.h"
#include "envoy/config/core/v3/http_service.upb_minitable.h"
#include "envoy/config/core/v3/base.upb_minitable.h"
#include "envoy/config/core/v3/http_uri.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
static const upb_MiniTableSubInternal envoy_config_core_v3_HttpService__submsgs[2] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__HttpUri_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__HeaderValueOption_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_core_v3_HttpService__fields[2] = {
  {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {2, UPB_SIZE(16, 24), 0, 1, 11, (int)kUpb_FieldMode_Array | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__core__v3__HttpService_msg_init = {
  &envoy_config_core_v3_HttpService__submsgs[0],
  &envoy_config_core_v3_HttpService__fields[0],
  UPB_SIZE(24, 32), 2, kUpb_ExtMode_NonExtendable, 2, UPB_FASTTABLE_MASK(24), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.core.v3.HttpService",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x001800003f010012, &upb_prm_1bt_maxmaxb},
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
  })
};

const upb_MiniTable* envoy__config__core__v3__HttpService_msg_init_ptr = &envoy__config__core__v3__HttpService_msg_init;
static const upb_MiniTable *messages_layout[1] = {
  &envoy__config__core__v3__HttpService_msg_init,
};

const upb_MiniTableFile envoy_config_core_v3_http_service_proto_upb_file_layout = {
  messages_layout,
  NULL,
  NULL,
  1,
  0,
  0,
};

#include "upb/port/undef.inc"
