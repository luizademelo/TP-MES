
#ifndef ENVOY_EXTENSIONS_TRANSPORT_SOCKETS_HTTP_11_PROXY_V3_UPSTREAM_HTTP_11_CONNECT_PROTO_UPB_H__UPB_H_
#define ENVOY_EXTENSIONS_TRANSPORT_SOCKETS_HTTP_11_PROXY_V3_UPSTREAM_HTTP_11_CONNECT_PROTO_UPB_H__UPB_H_

#include "upb/generated_code_support.h"

#include "envoy/extensions/transport_sockets/http_11_proxy/v3/upstream_http_11_connect.upb_minitable.h"

#include "envoy/config/core/v3/base.upb_minitable.h"
#include "udpa/annotations/status.upb_minitable.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct envoy_extensions_transport_sockets_http_11_proxy_v3_Http11ProxyUpstreamTransport { upb_Message UPB_PRIVATE(base); } envoy_extensions_transport_sockets_http_11_proxy_v3_Http11ProxyUpstreamTransport;
struct envoy_config_core_v3_TransportSocket;

UPB_INLINE envoy_extensions_transport_sockets_http_11_proxy_v3_Http11ProxyUpstreamTransport* envoy_extensions_transport_sockets_http_11_proxy_v3_Http11ProxyUpstreamTransport_new(upb_Arena* arena) {
  return (envoy_extensions_transport_sockets_http_11_proxy_v3_Http11ProxyUpstreamTransport*)_upb_Message_New(&envoy__extensions__transport_0sockets__http_011_0proxy__v3__Http11ProxyUpstreamTransport_msg_init, arena);
}
UPB_INLINE envoy_extensions_transport_sockets_http_11_proxy_v3_Http11ProxyUpstreamTransport* envoy_extensions_transport_sockets_http_11_proxy_v3_Http11ProxyUpstreamTransport_parse(const char* buf, size_t size, upb_Arena* arena) {
  envoy_extensions_transport_sockets_http_11_proxy_v3_Http11ProxyUpstreamTransport* ret = envoy_extensions_transport_sockets_http_11_proxy_v3_Http11ProxyUpstreamTransport_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__transport_0sockets__http_011_0proxy__v3__Http11ProxyUpstreamTransport_msg_init, NULL, 0, arena) !=
      kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE envoy_extensions_transport_sockets_http_11_proxy_v3_Http11ProxyUpstreamTransport* envoy_extensions_transport_sockets_http_11_proxy_v3_Http11ProxyUpstreamTransport_parse_ex(const char* buf, size_t size,
                           const upb_ExtensionRegistry* extreg,
                           int options, upb_Arena* arena) {
  envoy_extensions_transport_sockets_http_11_proxy_v3_Http11ProxyUpstreamTransport* ret = envoy_extensions_transport_sockets_http_11_proxy_v3_Http11ProxyUpstreamTransport_new(arena);
  if (!ret) return NULL;
  if (upb_Decode(buf, size, UPB_UPCAST(ret), &envoy__extensions__transport_0sockets__http_011_0proxy__v3__Http11ProxyUpstreamTransport_msg_init, extreg, options,
                 arena) != kUpb_DecodeStatus_Ok) {
    return NULL;
  }
  return ret;
}
UPB_INLINE char* envoy_extensions_transport_sockets_http_11_proxy_v3_Http11ProxyUpstreamTransport_serialize(const envoy_extensions_transport_sockets_http_11_proxy_v3_Http11ProxyUpstreamTransport* msg, upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__transport_0sockets__http_011_0proxy__v3__Http11ProxyUpstreamTransport_msg_init, 0, arena, &ptr, len);
  return ptr;
}
UPB_INLINE char* envoy_extensions_transport_sockets_http_11_proxy_v3_Http11ProxyUpstreamTransport_serialize_ex(const envoy_extensions_transport_sockets_http_11_proxy_v3_Http11ProxyUpstreamTransport* msg, int options,
                                 upb_Arena* arena, size_t* len) {
  char* ptr;
  (void)upb_Encode(UPB_UPCAST(msg), &envoy__extensions__transport_0sockets__http_011_0proxy__v3__Http11ProxyUpstreamTransport_msg_init, options, arena, &ptr, len);
  return ptr;
}
UPB_INLINE void envoy_extensions_transport_sockets_http_11_proxy_v3_Http11ProxyUpstreamTransport_clear_transport_socket(envoy_extensions_transport_sockets_http_11_proxy_v3_Http11ProxyUpstreamTransport* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  upb_Message_ClearBaseField(UPB_UPCAST(msg), &field);
}
UPB_INLINE const struct envoy_config_core_v3_TransportSocket* envoy_extensions_transport_sockets_http_11_proxy_v3_Http11ProxyUpstreamTransport_transport_socket(const envoy_extensions_transport_sockets_http_11_proxy_v3_Http11ProxyUpstreamTransport* msg) {
  const struct envoy_config_core_v3_TransportSocket* default_val = NULL;
  const struct envoy_config_core_v3_TransportSocket* ret;
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TransportSocket_msg_init);
  _upb_Message_GetNonExtensionField(UPB_UPCAST(msg), &field,
                                    &default_val, &ret);
  return ret;
}
UPB_INLINE bool envoy_extensions_transport_sockets_http_11_proxy_v3_Http11ProxyUpstreamTransport_has_transport_socket(const envoy_extensions_transport_sockets_http_11_proxy_v3_Http11ProxyUpstreamTransport* msg) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  return upb_Message_HasBaseField(UPB_UPCAST(msg), &field);
}

UPB_INLINE void envoy_extensions_transport_sockets_http_11_proxy_v3_Http11ProxyUpstreamTransport_set_transport_socket(envoy_extensions_transport_sockets_http_11_proxy_v3_Http11ProxyUpstreamTransport *msg, struct envoy_config_core_v3_TransportSocket* value) {
  const upb_MiniTableField field = {1, UPB_SIZE(12, 16), 64, 0, 11, (int)kUpb_FieldMode_Scalar | ((int)UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte) << kUpb_FieldRep_Shift)};
  UPB_PRIVATE(_upb_MiniTable_StrongReference)(&envoy__config__core__v3__TransportSocket_msg_init);
  upb_Message_SetBaseField((upb_Message *)msg, &field, &value);
}
UPB_INLINE struct envoy_config_core_v3_TransportSocket* envoy_extensions_transport_sockets_http_11_proxy_v3_Http11ProxyUpstreamTransport_mutable_transport_socket(envoy_extensions_transport_sockets_http_11_proxy_v3_Http11ProxyUpstreamTransport* msg, upb_Arena* arena) {
  struct envoy_config_core_v3_TransportSocket* sub = (struct envoy_config_core_v3_TransportSocket*)envoy_extensions_transport_sockets_http_11_proxy_v3_Http11ProxyUpstreamTransport_transport_socket(msg);
  if (sub == NULL) {
    sub = (struct envoy_config_core_v3_TransportSocket*)_upb_Message_New(&envoy__config__core__v3__TransportSocket_msg_init, arena);
    if (sub) envoy_extensions_transport_sockets_http_11_proxy_v3_Http11ProxyUpstreamTransport_set_transport_socket(msg, sub);
  }
  return sub;
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
