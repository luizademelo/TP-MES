
#include <stddef.h>
#include "upb/generated_code_support.h"
#include "envoy/type/matcher/v3/status_code_input.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"

#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
const upb_MiniTable envoy__type__matcher__v3__HttpResponseStatusCodeMatchInput_msg_init = {
  NULL,
  NULL,
  8, 0, kUpb_ExtMode_NonExtendable, 0, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.type.matcher.v3.HttpResponseStatusCodeMatchInput",
#endif
};

const upb_MiniTable* envoy__type__matcher__v3__HttpResponseStatusCodeMatchInput_msg_init_ptr = &envoy__type__matcher__v3__HttpResponseStatusCodeMatchInput_msg_init;
const upb_MiniTable envoy__type__matcher__v3__HttpResponseStatusCodeClassMatchInput_msg_init = {
  NULL,
  NULL,
  8, 0, kUpb_ExtMode_NonExtendable, 0, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.type.matcher.v3.HttpResponseStatusCodeClassMatchInput",
#endif
};

const upb_MiniTable* envoy__type__matcher__v3__HttpResponseStatusCodeClassMatchInput_msg_init_ptr = &envoy__type__matcher__v3__HttpResponseStatusCodeClassMatchInput_msg_init;
static const upb_MiniTable *messages_layout[2] = {
  &envoy__type__matcher__v3__HttpResponseStatusCodeMatchInput_msg_init,
  &envoy__type__matcher__v3__HttpResponseStatusCodeClassMatchInput_msg_init,
};

const upb_MiniTableFile envoy_type_matcher_v3_status_code_input_proto_upb_file_layout = {
  messages_layout,
  NULL,
  NULL,
  2,
  0,
  0,
};

#include "upb/port/undef.inc"
