
#ifndef ENVOY_EXTENSIONS_TRANSPORT_SOCKETS_TLS_V3_COMMON_PROTO_UPB_H__UPBDEFS_H_
#define ENVOY_EXTENSIONS_TRANSPORT_SOCKETS_TLS_V3_COMMON_PROTO_UPB_H__UPBDEFS_H_

#include "upb/reflection/def.h"
#include "upb/reflection/internal/def_pool.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

extern _upb_DefPool_Init envoy_extensions_transport_sockets_tls_v3_common_proto_upbdefinit;

UPB_INLINE const upb_MessageDef *envoy_extensions_transport_sockets_tls_v3_TlsParameters_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_extensions_transport_sockets_tls_v3_common_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.extensions.transport_sockets.tls.v3.TlsParameters");
}

UPB_INLINE const upb_MessageDef *envoy_extensions_transport_sockets_tls_v3_PrivateKeyProvider_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_extensions_transport_sockets_tls_v3_common_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.extensions.transport_sockets.tls.v3.PrivateKeyProvider");
}

UPB_INLINE const upb_MessageDef *envoy_extensions_transport_sockets_tls_v3_TlsCertificate_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_extensions_transport_sockets_tls_v3_common_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.extensions.transport_sockets.tls.v3.TlsCertificate");
}

UPB_INLINE const upb_MessageDef *envoy_extensions_transport_sockets_tls_v3_TlsSessionTicketKeys_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_extensions_transport_sockets_tls_v3_common_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.extensions.transport_sockets.tls.v3.TlsSessionTicketKeys");
}

UPB_INLINE const upb_MessageDef *envoy_extensions_transport_sockets_tls_v3_CertificateProviderPluginInstance_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_extensions_transport_sockets_tls_v3_common_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.extensions.transport_sockets.tls.v3.CertificateProviderPluginInstance");
}

UPB_INLINE const upb_MessageDef *envoy_extensions_transport_sockets_tls_v3_SubjectAltNameMatcher_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_extensions_transport_sockets_tls_v3_common_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.extensions.transport_sockets.tls.v3.SubjectAltNameMatcher");
}

UPB_INLINE const upb_MessageDef *envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_extensions_transport_sockets_tls_v3_common_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.extensions.transport_sockets.tls.v3.CertificateValidationContext");
}

UPB_INLINE const upb_MessageDef *envoy_extensions_transport_sockets_tls_v3_CertificateValidationContext_SystemRootCerts_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_extensions_transport_sockets_tls_v3_common_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.extensions.transport_sockets.tls.v3.CertificateValidationContext.SystemRootCerts");
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
