
#include <stddef.h>
#include "upb/generated_code_support.h"
#include "envoy/config/listener/v3/api_listener.upb_minitable.h"
#include "google/protobuf/any.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"

#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
static const upb_MiniTableSubInternal envoy_config_listener_v3_ApiListener__submsgs[1] = {
  {.UPB_PRIVATE(submsg) = &google__protobuf__Any_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_listener_v3_ApiListener__fields[1] = {
  {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__listener__v3__ApiListener_msg_init = {
  &envoy_config_listener_v3_ApiListener__submsgs[0],
  &envoy_config_listener_v3_ApiListener__fields[0],
  UPB_SIZE(16, 24), 1, kUpb_ExtMode_NonExtendable, 1, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.listener.v3.ApiListener",
#endif
};

const upb_MiniTable* envoy__config__listener__v3__ApiListener_msg_init_ptr = &envoy__config__listener__v3__ApiListener_msg_init;
static const upb_MiniTable *messages_layout[1] = {
  &envoy__config__listener__v3__ApiListener_msg_init,
};

const upb_MiniTableFile envoy_config_listener_v3_api_listener_proto_upb_file_layout = {
  messages_layout,
  NULL,
  NULL,
  1,
  0,
  0,
};

#include "upb/port/undef.inc"
