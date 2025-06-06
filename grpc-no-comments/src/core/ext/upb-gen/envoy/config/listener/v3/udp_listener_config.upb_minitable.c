
#include <stddef.h>
#include "upb/generated_code_support.h"
#include "envoy/config/listener/v3/udp_listener_config.upb_minitable.h"
#include "envoy/config/core/v3/extension.upb_minitable.h"
#include "envoy/config/core/v3/udp_socket_config.upb_minitable.h"
#include "envoy/config/listener/v3/quic_config.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"

#include "upb/port/def.inc"

extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken);
static const upb_MiniTableSubInternal envoy_config_listener_v3_UdpListenerConfig__submsgs[3] = {
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__UdpSocketConfig_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__listener__v3__QuicProtocolOptions_msg_init_ptr},
  {.UPB_PRIVATE(submsg) = &envoy__config__core__v3__TypedExtensionConfig_msg_init_ptr},
};

static const upb_MiniTableField envoy_config_listener_v3_UdpListenerConfig__fields[3] = {
  {5, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {7, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
  {8, UPB_SIZE(20, 32), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)},
};

const upb_MiniTable envoy__config__listener__v3__UdpListenerConfig_msg_init = {
  &envoy_config_listener_v3_UdpListenerConfig__submsgs[0],
  &envoy_config_listener_v3_UdpListenerConfig__fields[0],
  UPB_SIZE(24, 40), 3, kUpb_ExtMode_NonExtendable, 0, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.listener.v3.UdpListenerConfig",
#endif
};

const upb_MiniTable* envoy__config__listener__v3__UdpListenerConfig_msg_init_ptr = &envoy__config__listener__v3__UdpListenerConfig_msg_init;
const upb_MiniTable envoy__config__listener__v3__ActiveRawUdpListenerConfig_msg_init = {
  NULL,
  NULL,
  8, 0, kUpb_ExtMode_NonExtendable, 0, UPB_FASTTABLE_MASK(255), 0,
#ifdef UPB_TRACING_ENABLED
  "envoy.config.listener.v3.ActiveRawUdpListenerConfig",
#endif
};

const upb_MiniTable* envoy__config__listener__v3__ActiveRawUdpListenerConfig_msg_init_ptr = &envoy__config__listener__v3__ActiveRawUdpListenerConfig_msg_init;
static const upb_MiniTable *messages_layout[2] = {
  &envoy__config__listener__v3__UdpListenerConfig_msg_init,
  &envoy__config__listener__v3__ActiveRawUdpListenerConfig_msg_init,
};

const upb_MiniTableFile envoy_config_listener_v3_udp_listener_config_proto_upb_file_layout = {
  messages_layout,
  NULL,
  NULL,
  2,
  0,
  0,
};

#include "upb/port/undef.inc"
