
#include <stddef.h>
#include "upb/generated_code_support.h"
#include "envoy/type/v3/http_status.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"
#include "validate/validate.upb_minitable.h"

#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
static const upb_MiniTableField envoy_type_v3_HttpStatus__fields[1] = {
  {1, 8, 0, kUpb_NoSub, 5, (int)kUpb_FieldMode_Scalar | (int)kUpb_LabelFlags_IsAlternate | ((int)kUpb_FieldRep_4Byte << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__type__v3__HttpStatus_msg_init = {
  NULL,
  &envoy_type_v3_HttpStatus__fields[0],
  16, 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(8), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.type.v3.HttpStatus",
#endif
  UPB_FASTTABLE_INIT({
    {0x0000000000000000, &_upb_FastDecoder_DecodeGeneric},
    {0x000800003f000008, &upb_psv4_1bt},
  })
};

const upb_MiniTable* envoy__type__v3__HttpStatus_msg_init_ptr = &envoy__type__v3__HttpStatus_msg_init;
static const upb_MiniTable *messages_layout[1] = {
  &envoy__type__v3__HttpStatus_msg_init,
};

const upb_MiniTableFile envoy_type_v3_http_status_proto_upb_file_layout = {
  messages_layout,
  NULL,
  NULL,
  1,
  0,
  0,
};

#include "upb/port/undef.inc"
