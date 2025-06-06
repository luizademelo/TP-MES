
#ifndef ENVOY_EXTENSIONS_TRANSPORT_SOCKETS_TLS_V3_TLS_PROTO_UPB_H__UPBDEFS_H_
#define ENVOY_EXTENSIONS_TRANSPORT_SOCKETS_TLS_V3_TLS_PROTO_UPB_H__UPBDEFS_H_

#include "upb/reflection/def.h"
#include "upb/reflection/internal/def_pool.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

extern _upb_DefPool_Init envoy_extensions_transport_sockets_tls_v3_tls_proto_upbdefinit;

UPB_INLINE const upb_MessageDef *envoy_extensions_transport_sockets_tls_v3_UpstreamTlsContext_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_extensions_transport_sockets_tls_v3_tls_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.extensions.transport_sockets.tls.v3.UpstreamTlsContext");
}

UPB_INLINE const upb_MessageDef *envoy_extensions_transport_sockets_tls_v3_DownstreamTlsContext_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_extensions_transport_sockets_tls_v3_tls_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.extensions.transport_sockets.tls.v3.DownstreamTlsContext");
}

UPB_INLINE const upb_MessageDef *envoy_extensions_transport_sockets_tls_v3_TlsKeyLog_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_extensions_transport_sockets_tls_v3_tls_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.extensions.transport_sockets.tls.v3.TlsKeyLog");
}

UPB_INLINE const upb_MessageDef *envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_extensions_transport_sockets_tls_v3_tls_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.extensions.transport_sockets.tls.v3.CommonTlsContext");
}

UPB_INLINE const upb_MessageDef *envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProvider_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_extensions_transport_sockets_tls_v3_tls_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.extensions.transport_sockets.tls.v3.CommonTlsContext.CertificateProvider");
}

UPB_INLINE const upb_MessageDef *envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CertificateProviderInstance_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_extensions_transport_sockets_tls_v3_tls_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.extensions.transport_sockets.tls.v3.CommonTlsContext.CertificateProviderInstance");
}

UPB_INLINE const upb_MessageDef *envoy_extensions_transport_sockets_tls_v3_CommonTlsContext_CombinedCertificateValidationContext_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_extensions_transport_sockets_tls_v3_tls_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.extensions.transport_sockets.tls.v3.CommonTlsContext.CombinedCertificateValidationContext");
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
