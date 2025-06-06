
#ifndef ENVOY_CONFIG_LISTENER_V3_UDP_LISTENER_CONFIG_PROTO_UPB_H__UPB_H_
#define ENVOY_CONFIG_LISTENER_V3_UDP_LISTENER_CONFIG_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "envoy/config/listener/v3/udp_listener_config.upb_minitable.h"

#include "envoy/config/core/v3/extension.upb_minitable.h"
#include "envoy/config/core/v3/udp_socket_config.upb_minitable.h"
#include "envoy/config/listener/v3/quic_config.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"
#include "udpa/annotations/versioning.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct envoy_config_listener_v3_UdpListenerConfig { upb_Message UPB_PRIVATE(base); } envoy_config_listener_v3_UdpListenerConfig;
typedef struct envoy_config_listener_v3_ActiveRawUdpListenerConfig { upb_Message UPB_PRIVATE(base); } envoy_config_listener_v3_ActiveRawUdpListenerConfig;
struct envoy_config_core_v3_TypedExtensionConfig;
struct envoy_config_core_v3_UdpSocketConfig;
struct envoy_config_listener_v3_QuicProtocolOptions;

UPB_INLINE envoy_config_listener_v3_UdpListenerConfig* envoy_config_listener_v3_UdpListenerConfig_new(upb_Arena* arena) {
  return (envoy_config_listener_v3_UdpListenerConfig*)_upb_Message_New(&envoy__config__listener__v3__UdpListenerConfig_msg_init, arena);
}
UPB_INLINE envoy_config_listener_v3_UdpListenerConfig* envoy_config_listener_v3_UdpListenerConfig_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_listener_v3_UdpListenerConfig* ret = envoy_config_listener_v3_UdpListenerConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__listener__v3__UdpListenerConfig_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_listener_v3_UdpListenerConfig* envoy_config_listener_v3_UdpListenerConfig_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_listener_v3_UdpListenerConfig* ret = envoy_config_listener_v3_UdpListenerConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__listener__v3__UdpListenerConfig_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_listener_v3_UdpListenerConfig_serialize(const envoy_config_listener_v3_UdpListenerConfig* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__listener__v3__UdpListenerConfig_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_listener_v3_UdpListenerConfig_serialize_ex(const envoy_config_listener_v3_UdpListenerConfig* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__listener__v3__UdpListenerConfig_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_config_listener_v3_UdpListenerConfig_clear_downstream_socket_config(envoy_config_listener_v3_UdpListenerConfig* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_UdpSocketConfig* envoy_config_listener_v3_UdpListenerConfig_downstream_socket_config(const envoy_config_listener_v3_UdpListenerConfig* msg) {
  const struct envoy_config_core_v3_UdpSocketConfig* default_val = NULL;
  const struct envoy_config_core_v3_UdpSocketConfig* ret;
  const upb_MiniTableField field = {5, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__UdpSocketConfig_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_listener_v3_UdpListenerConfig_has_downstream_socket_config(const envoy_config_listener_v3_UdpListenerConfig* msg) {
  const upb_MiniTableField field = {5, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_listener_v3_UdpListenerConfig_clear_quic_options(envoy_config_listener_v3_UdpListenerConfig* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_listener_v3_QuicProtocolOptions* envoy_config_listener_v3_UdpListenerConfig_quic_options(const envoy_config_listener_v3_UdpListenerConfig* msg) {
  const struct envoy_config_listener_v3_QuicProtocolOptions* default_val = NULL;
  const struct envoy_config_listener_v3_QuicProtocolOptions* ret;
  const upb_MiniTableField field = {7, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__listener__v3__QuicProtocolOptions_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_listener_v3_UdpListenerConfig_has_quic_options(const envoy_config_listener_v3_UdpListenerConfig* msg) {
  const upb_MiniTableField field = {7, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE void envoy_config_listener_v3_UdpListenerConfig_clear_udp_packet_packet_writer_config(envoy_config_listener_v3_UdpListenerConfig* msg) {
  const upb_MiniTableField field = {8, UPB_SIZE(20, 32), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_TypedExtensionConfig* envoy_config_listener_v3_UdpListenerConfig_udp_packet_packet_writer_config(const envoy_config_listener_v3_UdpListenerConfig* msg) {
  const struct envoy_config_core_v3_TypedExtensionConfig* default_val = NULL;
  const struct envoy_config_core_v3_TypedExtensionConfig* ret;
  const upb_MiniTableField field = {8, UPB_SIZE(20, 32), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_config_listener_v3_UdpListenerConfig_has_udp_packet_packet_writer_config(const envoy_config_listener_v3_UdpListenerConfig* msg) {
  const upb_MiniTableField field = {8, UPB_SIZE(20, 32), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_config_listener_v3_UdpListenerConfig_set_downstream_socket_config(envoy_config_listener_v3_UdpListenerConfig *msg, struct envoy_config_core_v3_UdpSocketConfig* value) {
  const upb_MiniTableField field = {5, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__UdpSocketConfig_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_UdpSocketConfig* envoy_config_listener_v3_UdpListenerConfig_mutable_downstream_socket_config(envoy_config_listener_v3_UdpListenerConfig* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_UdpSocketConfig* sub = (struct envoy_config_core_v3_UdpSocketConfig*)envoy_config_listener_v3_UdpListenerConfig_downstream_socket_config(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_UdpSocketConfig*)_upb_Message_New(&envoy__config__core__v3__UdpSocketConfig_msg_init, arena);
    if (sub) envoy_config_listener_v3_UdpListenerConfig_set_downstream_socket_config(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_listener_v3_UdpListenerConfig_set_quic_options(envoy_config_listener_v3_UdpListenerConfig *msg, struct envoy_config_listener_v3_QuicProtocolOptions* value) {
  const upb_MiniTableField field = {7, UPB_SIZE(16, 24), 65, 1, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__listener__v3__QuicProtocolOptions_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_listener_v3_QuicProtocolOptions* envoy_config_listener_v3_UdpListenerConfig_mutable_quic_options(envoy_config_listener_v3_UdpListenerConfig* msg, upb_Arena* arena) {
  struct envoy_config_listener_v3_QuicProtocolOptions* sub = (struct envoy_config_listener_v3_QuicProtocolOptions*)envoy_config_listener_v3_UdpListenerConfig_quic_options(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_listener_v3_QuicProtocolOptions*)_upb_Message_New(&envoy__config__listener__v3__QuicProtocolOptions_msg_init, arena);
    if (sub) envoy_config_listener_v3_UdpListenerConfig_set_quic_options(msg, sub);
  }
  return sub;
}
UPB_INLINE void envoy_config_listener_v3_UdpListenerConfig_set_udp_packet_packet_writer_config(envoy_config_listener_v3_UdpListenerConfig *msg, struct envoy_config_core_v3_TypedExtensionConfig* value) {
  const upb_MiniTableField field = {8, UPB_SIZE(20, 32), 66, 2, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TypedExtensionConfig_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_TypedExtensionConfig* envoy_config_listener_v3_UdpListenerConfig_mutable_udp_packet_packet_writer_config(envoy_config_listener_v3_UdpListenerConfig* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_TypedExtensionConfig* sub = (struct envoy_config_core_v3_TypedExtensionConfig*)envoy_config_listener_v3_UdpListenerConfig_udp_packet_packet_writer_config(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_TypedExtensionConfig*)_upb_Message_New(&envoy__config__core__v3__TypedExtensionConfig_msg_init, arena);
    if (sub) envoy_config_listener_v3_UdpListenerConfig_set_udp_packet_packet_writer_config(msg, sub);
  }
  return sub;
}

UPB_INLINE envoy_config_listener_v3_ActiveRawUdpListenerConfig* envoy_config_listener_v3_ActiveRawUdpListenerConfig_new(upb_Arena* arena) {
  return (envoy_config_listener_v3_ActiveRawUdpListenerConfig*)_upb_Message_New(&envoy__config__listener__v3__ActiveRawUdpListenerConfig_msg_init, arena);
}
UPB_INLINE envoy_config_listener_v3_ActiveRawUdpListenerConfig* envoy_config_listener_v3_ActiveRawUdpListenerConfig_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_config_listener_v3_ActiveRawUdpListenerConfig* ret = envoy_config_listener_v3_ActiveRawUdpListenerConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__listener__v3__ActiveRawUdpListenerConfig_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_config_listener_v3_ActiveRawUdpListenerConfig* envoy_config_listener_v3_ActiveRawUdpListenerConfig_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_config_listener_v3_ActiveRawUdpListenerConfig* ret = envoy_config_listener_v3_ActiveRawUdpListenerConfig_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__config__listener__v3__ActiveRawUdpListenerConfig_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_config_listener_v3_ActiveRawUdpListenerConfig_serialize(const envoy_config_listener_v3_ActiveRawUdpListenerConfig* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__listener__v3__ActiveRawUdpListenerConfig_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_config_listener_v3_ActiveRawUdpListenerConfig_serialize_ex(const envoy_config_listener_v3_ActiveRawUdpListenerConfig* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__config__listener__v3__ActiveRawUdpListenerConfig_msg_init, options, arena, &ptr, len);
  return ptr;
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
